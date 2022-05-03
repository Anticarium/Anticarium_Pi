#!/usr/bin/python3

import os
from subprocess import Popen, PIPE
from git import Repo
from argparse import ArgumentParser

RPI_UNAME = "pi"
RPI_IP = "192.168.1.103"
REMOTE_PATH = "/home/pi/Desktop/Anticarium_Pi/Anticarium_Pi"

APPS = {
    "pi":"anticarium_pi_server_app",
    "cam":"anticarium_pi_camera_app",
    "test":"anticarium_pi_tests"
}

def parseArguments():
    appChoices = list(APPS.keys())

    parser = ArgumentParser(description = "Commands for building and installing Anticarium applications on Raspberry Pi")
    parser.add_argument("--verbose", help = "Print more output", action = "store_true")

    subparsers = parser.add_subparsers(dest = "action")

    subparsers.add_parser("install", help = "Upload and compile all projects")

    subparsers.add_parser("build", help = "Build all projects")

    uploadParser = subparsers.add_parser("upload", help = "Upload passed project. Uses git status as default way on how to detect changed files")
    uploadParser.add_argument("--force", help = "Upload all files ignoring git changes", action = "store_true")

    runParser = subparsers.add_parser("run", help = "Run selected app")
    runParser.add_argument("--app", help = "App to run", choices = APPS)

    subparsers.add_parser("shell", help = "Open Raspberry Pi bash shell using ssh")
    
    return parser.parse_args()

# Main function for executing commands from this script
def executeProcess(command, stdout = None):
    process = Popen(command, stdout = stdout, shell = True)
    process.communicate()

def upload(force, verbose = False):
    # Path to current directory
    rootDir = os.path.dirname(os.path.realpath(__file__))

    files = None
    if force:
        print("Force upload")
        files = f"{rootDir}/*"
    else:
        print("Git diff upload")

        # Check which files changed using git diff
        repo = Repo(rootDir)
        filesList = [ item.a_path for item in repo.index.diff(None) ]
        
        files = ' '.join(filesList)

    # Print file uploading process on verbose output
    pipe = PIPE
    if verbose:
        pipe = None

    executeProcess(f"scp -rp {files} {RPI_UNAME}@{RPI_IP}:{REMOTE_PATH}", stdout = pipe)

# Prepends ssh command related stuff tu passed command
def sshCommand(command = ""):
    # -t parameter is used to kill ssh process started with Popen (https://stackoverflow.com/questions/51233859/python-subprocess-kill-is-not-affecting-ssh-command-as-same-as-manually-killing#comment89477894_51233859)
    sshExecutableCommand = f"ssh -t {RPI_UNAME}@{RPI_IP}"

    fullCommand = ' '.join([sshExecutableCommand, command])
    
    executeProcess(fullCommand)

def build():
    sshCommand(f"'mkdir --parents {REMOTE_PATH}/build; \
                  cd {REMOTE_PATH}/build; \
                  cmake -DADD_anticarium_pi_TESTS=ON {REMOTE_PATH}; \
                  cmake --build . --target all'")

def install(verbose):
    upload(verbose)
    build()

def run(app):
    appName = APPS[app]
    print(f"Running app: {appName}")

    if app == "pi":
        sshCommand(f"'{REMOTE_PATH}/build/apps/server_app/{appName}'")
    elif app == "cam":
        sshCommand(f"'{REMOTE_PATH}/build/apps/camera_app/{appName}'")
    elif app == "test":
        sshCommand(f"'{REMOTE_PATH}/build/tests/{appName}'")

# Opens ssh shell, goes to remote directory, starts bash
def shell():
    sshCommand(f"'cd {REMOTE_PATH}; bash'")

def execute():
    args = parseArguments()
    action = args.action
    
    if action == "install":
        install(args.verbose)
    elif action == "build":
        build()
    elif action == "upload":
        upload(args.force, args.verbose)
    elif action == "run":
        run(args.app)
    elif action == "shell":
        shell()

execute()
