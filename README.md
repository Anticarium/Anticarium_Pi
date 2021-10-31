# Anticarium_PI

# Development environment setup

This guide is made assuming you have Raspbian OS and you are member of Anticarium organization.

## Git repository setup
1. Generate your ssh key and add it to github according to this tutorial: https://docs.github.com/en/authentication/connecting-to-github-with-ssh/generating-a-new-ssh-key-and-adding-it-to-the-ssh-agent
2. `$ cd ~/Desktop`
3. `$ git config --global user.email "you@example.com"`
4. `$ git config --global user.name "Your Name"`
5. `$ mkdir ./Anticarium_Pi`
6. `$ cd ./Anticarium_Pi`
7. `$ git clone https://github.com/Anticarium/Anticarium_Pi.git	`
8. `$ git remote set-url origin git@github.com:Anticarium/Anticarium_Pi.git`
9. `$ cd`
10. `$ git clone https://github.com/Anticarium/Anticarium_Doc.git`
11. `$ cp ~/Desktop/Anticarium_Doc/.clang-format ~/Desktop/Anticarium_Pi/Anticarium_Pi`

## Install cmake
1. `$ sudo apt install libssl-dev`
2. Go to https://cmake.org/download/ and download latest CMake source for linux
3. Create folder `cmake` in your home directory
4. Move downloaded file to `cmake` folder
5. Export
6. `$ cd ~/cmake/<your_exported_cmake_source_library>
7. `$ ./bootstrap`
8. `$ make`
9. `$ sudo make install`

## Add HunterGate
- In Anticarium_Pi source folder `wget https://raw.githubusercontent.com/cpp-pm/gate/master/cmake/HunterGate.cmake -O cmake/HunterGate.cmake` 

## I2C connection
1. `sudo mousepad /boot/config.txt`
2. Find the line containing “dtparam=i2c_arm=on” and uncomment it
3. Add “,i2c_arm_baudrate=9600” where 9600 is the new speed (9,6 Kbit/s). Note the comma.
4. Should look like this: `dtparam=i2c_arm=on,i2c_arm_baudrate=9600`
5. Save
6. `reboot`

## Install Qt5 and Qt creator
1. `$ sudo apt install qt5-default` 
2. `$ sudo apt install qtcreator`

## Install clang-format-9
1. `$ sudo apt install clang-format-9`
2. Using Anticarium_Doc clang format setup in qt, link against this clang-format binary 

## CLang formatter setup in QT creator
1. Open Qt creator
2. Help->About Plugins
3. Find `Beautifier`
4. Check `Beautifier` checkbox
5. Close dialog and restart QT creator
6. In Qt creator Tools->Options->Beautifier->CLang Format
7. `clang-format` executable path: `/usr/bin/clang-format-9`
8. In `Use predefined style` choose `File`
9. Go to General Tab
10. Check `Enable auto format on file save`
11. Under `Tool:` select `ClangFormat`
12. Ok
13. Put `.clang-format-9` file found in Anticarium_Doc, into your source directory and rename to `.clang-format`
