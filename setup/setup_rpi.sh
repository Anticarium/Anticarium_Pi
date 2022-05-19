#!/bin/bash
#-----------------------------------------------------------------
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
cd ${HOME}
echo "export ANTICARIUM_SERVER_IP=$ANTICARIUM_SERVER_IP" >> .profile
source .profile

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
sudo apt install -y libssl-dev
mkdir ${HOME}/cmake
cd ${HOME}/cmake
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
cd ${HOME}
echo -e "cmake successfully installed\n\n"

#-----------------------------------------------------------------
echo "Installing Qt5..."
sudo apt install -y qtbase5-dev qtchooser qt5-qmake qtbase5-dev-tools
echo -e "Qt5 successfully installed\n\n"

#-----------------------------------------------------------------
echo "Installing git..."
sudo apt install -y git
echo -e "git successfully installed\n\n"

#-----------------------------------------------------------------
echo "Installing apache2..."
sudo apt install -y apache2
echo -e "apache2 successfully installed\n\n"

#-----------------------------------------------------------------
echo "Installing libapache2-mod-wsgi-py3..."
sudo apt-get install -y libapache2-mod-wsgi-py3
echo -e "libapache2-mod-wsgi-py3 successfully installed\n\n"

#-----------------------------------------------------------------
echo "Installing python-dev..."
sudo apt-get install -y python-dev
echo -e "python-dev successfully installed\n\n"

#-----------------------------------------------------------------
echo "Installing python3-pip..."
sudo apt-get install -y python3-pip
echo -e "python3-pip successfully installed\n\n"

#-----------------------------------------------------------------
echo "Installing flask..."
pip3 install flask
echo -e "flask successfully installed\n\n"

#-----------------------------------------------------------------
echo "Cloning Anticarium_Web..."
git clone https://github.com/Anticarium/Anticarium_Web.git
echo "export ANTICARIUM_WEB_PATH=/home/pi/Anticarium_Web" >> .profile
source .profile
echo -e "Anticarium_Web successfully cloned\n\n"

#-----------------------------------------------------------------
echo "Configuring apache2..."
cd ${HOME}/Anticarium_Web
mv anticarium_web.example anticarium_web.conf
sudo mv ./anticarium_web.conf /etc/apache2/sites-available
sudo mv ./apache2.conf.example /etc/apache2/apache2.conf
sudo a2ensite /etc/apache2/sites-available/anticarium_web.conf
sudo service apache2 reload
cd ${HOME}
echo -e "Configured apache2\n\n"

#-----------------------------------------------------------------
echo "Installing raspicam..."
git clone https://github.com/cedricve/raspicam.git
cd raspicam
mkdir build
cd build
cmake ..
make
sudo make install
cd ${HOME}
rm -rf raspicam
echo -e "raspicam sucessfully installed\n\n"

#-----------------------------------------------------------------
REBOOT_SECONDS=60
echo "Anticarium setup for Raspberry Pi successfully completed! Rebooting after $REBOOT_SECONDS seconds..."
sleep $REBOOT_SECONDS
sudo reboot now