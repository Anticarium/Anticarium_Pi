#!/bin/bash

if [ $ANTICARIUM_RUN_ON_BOOT ]
then
    nohup $HOME/Anticarium_Pi/build/apps/server_app/anticarium_pi_server_app &
    echo "Started anticarium_pi_server_app"
    nohup $HOME/Anticarium_Pi/build/apps/camera_app/anticarium_pi_camera_app &
    echo "Started anticarium_pi_camera_app"
else
    echo "No Anticarium apps set to run on boot"
fi