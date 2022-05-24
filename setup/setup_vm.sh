#!/bin/bash

set -e

while getopts a:hk flag
do
    case "${flag}" in
        a) RPI_IP=${OPTARG};;
        h) echo "Anticarium first time setup script for Ubuntu 20.04 development Virtual Machine
  Arguments:
  -a <ip address>      local ip address of Raspberry Pi
  -k                   perform SSH keys setup for Raspberry Pi"; 

            exit 0;;
        k) SETUP_SSH=True
    esac
done

if [ -z "$RPI_IP" ]
then
    >&2 echo "Error: RPI_IP environment variable not set! Use -a flag to pass and set it!"
    exit -1
fi

cd $HOME
if [ -z "$SETUP_SSH" ]
then
    echo -e "Performing Anticarium setup for Ubuntu 20.04 development Virtual Machine...\n"

    echo "export RPI_IP=$RPI_IP" >> .profile
    source .profile

    #-----------------------------------------------------------------
    echo "Updating apt..."
    sudo apt update
    sudo apt upgrade -y
    echo -e "apt successfully updated\n\n"

    #-----------------------------------------------------------------
    echo "Installing C++ build tools..."
    sudo apt install -y gcc g++ make
    echo -e "C++ build tools sucessfully installed\n\n"

    #-----------------------------------------------------------------
    echo "Installing Qt5..."
    sudo apt install -y qtbase5-dev qtchooser qt5-qmake qtbase5-dev-tools
    echo -e "Qt5 successfully installed\n\n"

    #-----------------------------------------------------------------
    echo "Installing cmake..."
    set +e
    cmake --version &> /dev/null
    CMAKE_EXIT_CODE=$?
    set -e
    if [ $CMAKE_EXIT_CODE == 0 ]
    then
        echo -e "cmake is already installed\n\n"
    else
        sudo apt install -y libssl-dev
        mkdir $HOME/cmake
        cd $HOME/cmake
        wget https://github.com/Kitware/CMake/releases/download/v3.22.4/cmake-3.22.4-linux-x86_64.sh
        wget https://github.com/Kitware/CMake/releases/download/v3.22.4/cmake-3.22.4-linux-x86_64.tar.gz
        chmod +x cmake-3.22.4-linux-x86_64.sh
        ./cmake-3.22.4-linux-x86_64.sh --prefix=.
    
        rm cmake-3.22.4-linux-x86_64.sh
        rm cmake-3.22.4-linux-x86_64.tar.gz
        sudo ln --symbolic ${HOME}/cmake/bin/cmake /usr/bin/cmake
        cd $HOME
        echo -e "cmake successfully installed\n\n"   
    fi

    #-----------------------------------------------------------------
    echo "Installing git..."
    sudo apt install -y git
    echo -e "git successfully installed\n\n"

    #-----------------------------------------------------------------
    echo "Installing Visual Studio Code..."
    mkdir --parents code
    cd code
    wget "https://code.visualstudio.com/sha/download?build=stable&os=linux-deb-x64"
    files=(*)
    sudo dpkg -i ${files[0]}
    cd $HOME
    rm -rf code
    echo -e "Visual Studio Code successfully installed\n\n"

    #-----------------------------------------------------------------
    echo "Setting up Anticarium_Pi..."
    git clone https://github.com/Anticarium/Anticarium_Pi.git
    cd Anticarium_Pi
    wget "https://raw.githubusercontent.com/cpp-pm/gate/master/cmake/HunterGate.cmake" -O cmake/HunterGate.cmake
    wget "https://raw.githubusercontent.com/Anticarium/Anticarium_Doc/main/.clang-format-9" -O .clang-format
    cd $HOME
    echo -e "Anticarium_Pi successfully set up\n\n"

    #-----------------------------------------------------------------
    echo "Setting up raspbian toolchain.."
    wget "https://github.com/Pro/raspi-toolchain/releases/latest/download/raspi-toolchain.tar.gz"
    sudo tar xfz raspi-toolchain.tar.gz --strip-components=1 -C /opt
    rm raspi-toolchain.tar.gz
    echo "export PATH=$PATH:/opt/cross-pi-gcc/bin" >> .profile
    source .profile
    echo "raspbian toolchain successfully set up\n\n"

    #-----------------------------------------------------------------
    echo "Installing raspicam..."
    git clone https://github.com/cedricve/raspicam.git
    cd raspicam
    mkdir build
    cd build
    cmake ..
    make
    sudo make install
    sudo ldconfig
    cd $HOME
    rm -rf raspicam
    echo -e "raspicam sucessfully installed\n\n"

    #-----------------------------------------------------------------
    echo "Installing virtualbox-guest-x11..."
    sudo apt install -y virtualbox-guest-x11
    echo -e "virtualbox-guest-x11 sucessfully installed\n\n"

    #-----------------------------------------------------------------
    echo "Installing clang-format..."
    sudo apt install -y clang-format
    echo -e "clang-format sucessfully installed\n\n"

    #-----------------------------------------------------------------
    REBOOT_SECONDS=60
    echo "Anticarium setup for buntu 20.04 development Virtual Machine successfully completed! Rebooting after $REBOOT_SECONDS seconds..."
    sleep $REBOOT_SECONDS
    sudo reboot now

else
    echo -e "Performing SSH keys setup. Make sure Raspberry Pi is available on LAN...\n"
    scp .ssh/id_rsa.pub pi@$RPI_IP:/home/pi/
    ssh -t pi@$RPI_IP 'mkdir --parents /home/pi/.ssh; cat /home/pi/id_rsa.pub >> .ssh/authorized_keys; rm /home/pi/id_rsa.pub'
    echo "SSH keys successfully set up"
fi