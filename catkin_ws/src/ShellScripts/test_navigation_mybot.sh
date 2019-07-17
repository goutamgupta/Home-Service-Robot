#!/bin/sh

xterm -e "roslaunch my_bot  mybot_world.launch world_file:="$(rospack find World)/color_room.world" " &  
sleep 5
xterm -e "rosrun my_bot navigation_goal"  



