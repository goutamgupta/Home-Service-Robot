#!/bin/sh

xterm -e "roslaunch turtlebot_gazebo  turtlebot_world.launch world_file:="$(rospack find World)/room.world"" &
sleep 5
xterm -e "roslaunch turtlebot_gazebo amcl_demo.launch map_file:="$(rospack find World)/wall_room_follower.yaml"" &
sleep 5 
xterm -e "rosrun rviz rviz -d  $(rospack find rvizconfig)/model.rviz" &
#xterm -e "roslaunch turtlebot_rviz_launchers view_navigation.launch" &  
sleep 5 
xterm -e "rosrun add_markers add_markers" &
sleep 5 
xterm -e "rosrun pick_objects pick_objects" &





