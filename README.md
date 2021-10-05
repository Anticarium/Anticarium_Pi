# Anticarium_PI

## Setup

**Add HunterGate**
- In main folder `wget https://raw.githubusercontent.com/cpp-pm/gate/master/cmake/HunterGate.cmake -O cmake/HunterGate.cmake` 

**I2C connection**
1. `sudo mousepad /boot/config.txt`
2. Find the line containing “dtparam=i2c_arm=on” and uncomment it
3. Add “,i2c_arm_baudrate=9600” where 9600 is the new speed (9,6 Kbit/s). Note the comma.
4. Should look like this: `dtparam=i2c_arm=on,i2c_arm_baudrate=9600`
5. Save
6. `reboot`

