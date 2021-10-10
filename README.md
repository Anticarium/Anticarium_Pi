# Anticarium_PI

## Development environment setup

This guide is made assuming you have Raspbian OS and you are member of Anticarium organization.

### Git repository setup
1. Generate your ssh key and add it to github according to this tutorial: https://docs.github.com/en/authentication/connecting-to-github-with-ssh/generating-a-new-ssh-key-and-adding-it-to-the-ssh-agent
2. `$ cd ~/Desktop`
3. `$ git config --global user.email "you@example.com"`
4. `$ git config --global user.name "Your Name"`
5. `$ mkdir ./Anticarium_Pi`
6. `$ cd ./Anticarium_Pi`
7. `$ git clone https://github.com/Anticarium/Anticarium_Pi.git	`
8. `$ git remote set-url origin git@github.com:Anticarium/Anticarium_Pi.git`
9. `$ cd`
9. `$ git clone `https://github.com/Anticarium/Anticarium_Doc.git`
10. $ cp ~/Desktop/Anticarium_Doc/.clang-format ~/Desktop/Anticarium_Pi/Anticarium_Pi`

### Install cmake


**Add HunterGate**
- In main folder `wget https://raw.githubusercontent.com/cpp-pm/gate/master/cmake/HunterGate.cmake -O cmake/HunterGate.cmake` 

**I2C connection**
1. `sudo mousepad /boot/config.txt`
2. Find the line containing “dtparam=i2c_arm=on” and uncomment it
3. Add “,i2c_arm_baudrate=9600” where 9600 is the new speed (9,6 Kbit/s). Note the comma.
4. Should look like this: `dtparam=i2c_arm=on,i2c_arm_baudrate=9600`
5. Save
6. `reboot`

