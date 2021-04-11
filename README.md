# Description
This is package devloped by Mowito company. <br/>
It is aimed at making robot follow command given at real time.<br/> 
Uses local planner which is used for short range path planning (like 3-4m)<br/>
Controller : Maxl (devloped at Mowito)<br/>
planner : MaxlPlanner (devloped at Mowito)
### input
Keyboard innput can be given at run time<br/> 
robot will update path taking obstacle avoidance in account as goal is changed by keys i , l j to move it forword backword rigth left 

# How to launch
### System requirement
Ubuntu 18/20<br/>
ROS Melodic/Neotic (Ros1)<br/>
Rviz (present by default if not [refer](http://wiki.ros.org/rviz/UserGuide))<br/>
For further ROS package dependencies [refer](https://docs.google.com/document/d/1ax2jxiBoe7LoIBfpz3iLcvHPjz6RKT2QiCndPhsWyjA/edit)
#### Repository requirement
For running the simulation you must have Maxl Planner install which is mention above<br/>
For installing Maxl planner [refer](https://docs.google.com/document/d/1ax2jxiBoe7LoIBfpz3iLcvHPjz6RKT2QiCndPhsWyjA/edit)
For further information on work visit [Mowito](https://mowito.in/)
### Launch simulation
After building and sourcing the repo on terminal type follwing commands 
1. ```roslaunch rosbot_description rosbot_nav_with_map.launch <br/>```
2. ```roslaunch robot_follower maxl_robot_follower_with_tracker_sim.launch <br/>```
3. On same terminal as launching ```robot_follower``` give commands as given in "input" section above to move robot <br/>

# Result
![out](https://user-images.githubusercontent.com/51331480/113501537-83b5a880-9543-11eb-8aba-99b28ba33679.gif)