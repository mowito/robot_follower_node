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
ROS Melodic/Neotic (ROS1)<br/>
Rviz (present by default if not refer to the [link](http://wiki.ros.org/rviz/UserGuide))<br/>
For further information on Mowito navigation stack refer to the [link](https://mowito-navstack.readthedocs.io/en/latest/Introduction.html)
#### Repository requirement
For running the simulation you must have mw_maxl_planner installed which is mention above. For information regarding how to use navigation stack refer to the [link](https://mowito-navstack.readthedocs.io/en/latest/how_to_use_mowito.html)<br/>
For installing Maxl planner refer to the [link](https://mowito-navstack.readthedocs.io/en/latest/Installation.html)
### Launch simulation
After building and sourcing the repo on terminal type follwing commands 
1. ```roslaunch rosbot_description rosbot_nav_with_map.launch ```
2. ```roslaunch robot_follower maxl_robot_follower_with_tracker_sim.launch ```
3. On same terminal as launching ```robot_follower``` give commands as given in "input" section above to move robot <br/>
4. You will see result as below

# Result
![out](https://user-images.githubusercontent.com/51331480/113501537-83b5a880-9543-11eb-8aba-99b28ba33679.gif)