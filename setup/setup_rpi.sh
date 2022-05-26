#!/bin/bash

set -e

while getopts a:h flag
do
    case "${flag}" in
        a) ANTICARIUM_SERVER_IP=${OPTARG};;
        h) echo "Anticarium first time setup script for Raspberry Pi
  Arguments:
  -a        public ip address of Raspberry Pi's router for WEB server"; 
            exit 0;;
    esac
done

if [ -z "$ANTICARIUM_SERVER_IP" ]
then
    >&2 echo "Error: ANTICARIUM_SERVER_IP environment variable not set! Use -a flag to pass and set it!"
    exit -1
fi

echo -e "Performing Anticarium setup for Raspberry Pi...\n"
cd $HOME

#-----------------------------------------------------------------
echo "Updating apt..."
sudo apt update
sudo apt upgrade -y
echo -e "apt successfully updated\n\n"

#-----------------------------------------------------------------
echo "Enabling ssh..."
sudo touch /boot/ssh
echo -e "ssh will be available after next boot\n\n"

#-----------------------------------------------------------------
echo "Installing cmake..."
set +e
cmake --version &> /dev/null
CMAKE_EXIT_CODE=$?
set -e
if [ CMAKE_EXIT_CODE == 0 ]
then
    echo -e "cmake is already installed\n\n"
else
    sudo apt install -y libssl-dev
    mkdir $HOME/cmake
    cd $HOME/cmake
    wget https://github.com/Kitware/CMake/releases/download/v3.22.4/cmake-3.22.4.tar.gz
    tar -xf cmake-3.22.4.tar.gz
    mv cmake-3.22.4/* .

    # The pattern .[!.]* is used to also match hidden files that start with dot
    mv cmake-3.22.4/.[!.]* .

    rm -rf cmake-3.22.4
    rm cmake-3.22.4.tar.gz
    chmod +x bootstrap
    ./bootstrap
    make
    sudo make install
    cd $HOME
    echo -e "cmake successfully installed\n\n"    
fi

#-----------------------------------------------------------------
echo "Installing Qt5..."
sudo apt install -y qtbase5-dev qtchooser qt5-qmake qtbase5-dev-tools
echo -e "Qt5 successfully installed\n\n"

#-----------------------------------------------------------------
echo "Installing git..."
sudo apt install -y git
echo -e "git successfully installed\n\n"

#-----------------------------------------------------------------
echo "Configuring Anticarium_Web"
wget https://raw.githubusercontent.com/Anticarium/Anticarium_Web/main/setup_web.sh
chmod +x setup_web.sh
./setup_web.sh -a $ANTICARIUM_SERVER_IP
rm setup_web.sh
echo -e "Anticarium_Web successfully configured\n\n"

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
echo -e "Setting up boot configuration..."
wget https://raw.githubusercontent.com/Anticarium/Anticarium_Pi/master/setup/config.txt.example
sudo mv config.txt.example /boot/config.txt
sudo sh -c "echo i2c-dev >> /etc/modules"
wget https://raw.githubusercontent.com/Anticarium/Anticarium_Pi/master/setup/run_on_boot.sh
chmod 755 run_on_boot.sh
echo "export ANTICARIUM_RUN_ON_BOOT=" >> .profile
echo "$HOME/run_on_boot.sh" >> .profile
echo -e "Boot configuration successfully set up\n\n"

#-----------------------------------------------------------------
REBOOT_SECONDS=60
echo "Anticarium setup for Raspberry Pi successfully completed! Rebooting after $REBOOT_SECONDS seconds..."
sleep $REBOOT_SECONDS
sudo reboot now