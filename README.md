# Description
This is package devloped by Mowito company. <br/>
It is aimed at making robot follow command given at real time.<br/> 
* For further information on Mowito navigation stack refer to the [link](https://mowito-navstack.readthedocs.io/en/latest/Introduction.html)<br/>
* By tuning parameters for Maxl you can deploy navigation stack on your robot. For tunning parameters refer to this [link](https://mowito-navstack.readthedocs.io/en/latest/tune_maxl.html)<br/>
* Instruction guide for running navigation stack on actual robot can be found [here](https://mowito-navstack.readthedocs.io/en/latest/rosbot_real.html)<br/>
* It Uses local planner which is used for short range path planning (3-4m)<br/>
    * Planner : MaxlPlanner (devloped at Mowito)<br/>
    * Controller : Maxl (devloped at Mowito)<br/>

### Input
Keyboard innput can be given at run time<br/> 
robot will update path taking obstacle avoidance in account as goal is changed by keys i , l j to move it forword backword rigth left 

# How to launch
### System requirement
* Ubuntu 18/20<br/>
* ROS Melodic/Neotic (ROS1)<br/>
* Rviz (present by default if not refer to the [link](http://wiki.ros.org/rviz/UserGuide))<br/>

#### Repository requirement
* For running the simulation you must have mw_maxl_planner repository installed.<br/>
* Information regarding how to use navigation stack can be found here on [link](https://mowito-navstack.readthedocs.io/en/latest/how_to_use_mowito.html)<br/>
* For installing Maxl planner refer to the [link](https://mowito-navstack.readthedocs.io/en/latest/Installation.html)
* Information regarding parameters used in Maxl Planner is on [link](https://mowito-navstack.readthedocs.io/en/latest/config_maxl.html)
### Launch simulation
After building and sourcing the repo on terminal type follwing commands 
1. ```roslaunch rosbot_description rosbot_nav_with_map.launch ```
2. ```roslaunch robot_follower maxl_robot_follower_with_tracker_sim.launch ```
3. On same terminal as launching ```robot_follower``` give commands as given in "input" section above to move robot <br/>
4. You will see result as below

# Result
![out](https://user-images.githubusercontent.com/51331480/113501537-83b5a880-9543-11eb-8aba-99b28ba33679.gif)