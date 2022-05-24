#!/usr/bin/python3

import os
import sys
from subprocess import Popen
from argparse import ArgumentParser

RPI_UNAME = "pi"
RPI_IP = "192.168.1.102"
REMOTE_PATH = "/home/pi/Anticarium_Pi"

APPS = {
    "pi":"anticarium_pi_server_app",
    "cam":"anticarium_pi_camera_app",
    "test":"anticarium_pi_tests"
}

def parseArguments():
    parser = ArgumentParser(description = "Commands for building and installing Anticarium applications on Raspberry Pi")

    subparsers = parser.add_subparsers(dest = "action")

    subparsers.add_parser("install", help = "Upload and compile all projects")

    subparsers.add_parser("build", help = "Build all projects")

    subparsers.add_parser("upload", help = "Upload passed project. Uses git status as default way on how to detect changed files")

    runParser = subparsers.add_parser("run", help = "Run selected app")
    runParser.add_argument("--app", help = "App to run", choices = APPS)

    subparsers.add_parser("shell", help = "Open Raspberry Pi bash shell using ssh")

    subparsers.add_parser("cmd", help = "Pass command to execute on Raspberry Pi")
    
    return parser.parse_known_args()

# Main function for executing commands from this script
def executeProcess(command):
    process = Popen(command, shell = True)
    process.communicate()

def upload():
    # Path to current directory
    rootDir = os.path.dirname(os.path.realpath(__file__))
    files = f"{rootDir}/*"

    executeProcess(f"scp -rp {files} {RPI_UNAME}@{RPI_IP}:{REMOTE_PATH}")

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

def install():
    upload()
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

def cmd(argv):
    sshCommand(f"'{' '.join(argv)}'")

def execute():
    args, _ = parseArguments()
    action = args.action
    
    if action == "install":
        install()
    elif action == "build":
        build()
    elif action == "upload":
        upload()
    elif action == "run":
        run(args.app)
    elif action == "shell":
        shell()
    elif action == "cmd":
        cmd(sys.argv[2:])

execute()
