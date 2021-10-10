# Anticarium_PI

## Development environment setup

This guide is made assuming you have Raspbian OS and you are member of Anticarium organization.

### Git repositories setup
1. Generate your ssh key and add it to github according to this tutorial: https://docs.github.com/en/authentication/connecting-to-github-with-ssh/generating-a-new-ssh-key-and-adding-it-to-the-ssh-agent
2. `$ cd ~/Desktop`
3. `$ mkdir ./Anticarium_Pi`
4. `$ cd ./Anticarium_Pi`
5. `$ git clone <web_url>`

7. 

**Add HunterGate**
- In main folder `wget https://raw.githubusercontent.com/cpp-pm/gate/master/cmake/HunterGate.cmake -O cmake/HunterGate.cmake` 

**I2C connection**
1. `sudo mousepad /boot/config.txt`
2. Find the line containing “dtparam=i2c_arm=on” and uncomment it
3. Add “,i2c_arm_baudrate=9600” where 9600 is the new speed (9,6 Kbit/s). Note the comma.
4. Should look like this: `dtparam=i2c_arm=on,i2c_arm_baudrate=9600`
5. Save
6. `reboot`

