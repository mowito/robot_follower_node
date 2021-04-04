/**
* @file : robot_follower_node.cpp
@brief: robot will follow given goal at runtime
@author: neha marne nehamarne27@gmail.com 
@date: 4/04/2021
@company: Mowito
**/

#include <mw_maxl_planner/mw_maxl_planner_ros1.h>

class RobotFollower
{

    const double POS_EPS = 0.001;
    geometry_msgs::PoseStamped previous_goal_;
    bool initialized_ = false;
    boost::shared_ptr<tf2_ros::Buffer> tf2Buf_;
    double goalXYTolerance_ = 0;
    bool first_goal_recieved_ = false;
    tf::TransformListener listener_;
    std::string map_frame_, robot_frame_;
    bool rel_motion_mode_;

    bool differentPose(const geometry_msgs::PoseStamped& pose_1, const geometry_msgs::PoseStamped& pose_2)
    {
        double diff_x = fabs(pose_1.pose.position.x - pose_2.pose.position.x);
        double diff_y = fabs(pose_1.pose.position.y - pose_2.pose.position.y);

        if (diff_x >= POS_EPS || diff_y >= POS_EPS)
        {
            return true;
        }
        return false;
    }

public:
    boost::shared_ptr<mw_maxl_planner::MwMaxlPlanner> mw_maxl;

    RobotFollower(double goalXYTolerance, std::string map_frame, std::string robot_frame, bool rel_motion_mode)
    :goalXYTolerance_(goalXYTolerance),
     map_frame_(map_frame),
     robot_frame_(robot_frame),
     rel_motion_mode_(rel_motion_mode)
    {
        mw_maxl.reset(new mw_maxl_planner::MwMaxlPlanner());
        tf2Buf_.reset(new tf2_ros::Buffer());
        mw_maxl->initialize("mw_maxl_planner", tf2Buf_);
        while (!mw_maxl->isInitialized())
        {
            ROS_INFO_THROTTLE(1, "[MAXL][robot_follower Node]: waiting for maxl to initalise");
        }

        initialized_ = true;
    }

    void goalCB(const geometry_msgs::PoseStamped::ConstPtr& goal)
    {
        if(rel_motion_mode_ == false)
        {
            geometry_msgs::PoseStamped robot_pose_in, robot_pose_out;
            robot_pose_in = *goal;
           
            try
            {
              listener_.waitForTransform(robot_pose_in.header.frame_id, map_frame_, robot_pose_in.header.stamp, ros::Duration(0.1));
              listener_.transformPose(map_frame_, ros::Time(0), robot_pose_in, robot_pose_in.header.frame_id, robot_pose_out);
            }
            catch(tf2::TransformException &ex)
            {
              ROS_WARN("[MAXL] [robot_follower Node]: Exception while transforming %s frame to %s frame. Error message: %s",robot_pose_in.header.frame_id.c_str(), map_frame_.c_str(), ex.what());
            }
            if(!first_goal_recieved_)
            {
                mw_maxl->setGoal(robot_pose_out);
                previous_goal_.pose.position.x = robot_pose_out.pose.position.x;
                previous_goal_.pose.position.y = robot_pose_out.pose.position.y;
                first_goal_recieved_ = true;
            }
            else
            {
                if(differentPose(robot_pose_out, previous_goal_))
                {
                    mw_maxl->setGoal(robot_pose_out);
                    previous_goal_.pose.position.x = robot_pose_out.pose.position.x;
                    previous_goal_.pose.position.y = robot_pose_out.pose.position.y;
                }
            }
        }
        else
        {
            geometry_msgs::PoseStamped robot_pose_in, robot_pose_out;
            robot_pose_in = *goal;

            //The goal we get from the follow_me_goal_pub here would be in map frame (for eg). We convert the pose in robot frame and provide the 
            // relative goal directly to the maxl_lib            
            try
            {
              listener_.waitForTransform(robot_pose_in.header.frame_id, robot_frame_, robot_pose_in.header.stamp, ros::Duration(0.1));
              listener_.transformPose(robot_frame_, ros::Time(0), robot_pose_in, robot_pose_in.header.frame_id, robot_pose_out);
            }
            catch(tf2::TransformException &ex)
            {
              ROS_WARN("[MAXL] [robot_follower Node]: Exception while transforming %s frame to %s frame. Error message: %s",robot_pose_in.header.frame_id.c_str(), robot_frame_.c_str(), ex.what());
            }
            if(!first_goal_recieved_)
            {
                mw_maxl->setRelativeGoal(robot_pose_out);
                previous_goal_.pose.position.x = robot_pose_out.pose.position.x;
                previous_goal_.pose.position.y = robot_pose_out.pose.position.y;
                first_goal_recieved_ = true;
            }
            else
            {
                if(differentPose(robot_pose_out, previous_goal_))
                {
                    mw_maxl->setRelativeGoal(robot_pose_out);
                    previous_goal_.pose.position.x = robot_pose_out.pose.position.x;
                    previous_goal_.pose.position.y = robot_pose_out.pose.position.y;
                }
            }
        }
    }

    bool isInitialized()
    {
        return initialized_;
    }
    
    bool isGoalReached()
    {
        double dummy_angle_goal_tolerance = -1;
        if (mw_maxl->isGoalReached(goalXYTolerance_, dummy_angle_goal_tolerance))
        {
            return true;
        }
        return false;
    }
};

int main(int argc, char **argv) {
    ros::init(argc, argv, "robot_follower_node");
    ros::NodeHandle private_nh("~");
    ros::NodeHandle global_nh("/");

    //set cmd_vel publisher
    ros::Publisher cmd_vel_pub = global_nh.advertise<geometry_msgs::Twist>("cmd_vel", 5);

    std::string mobileGoalTopic;
    std::string robot_frame;
    std::string map_frame;
    double goalXYTolerance;
    double loopRateValue;
    bool rel_motion_mode;

    //obtain and store value of params
    private_nh.param("dist_tolerance", goalXYTolerance, 0.2);
    private_nh.param("loop_rate_value", loopRateValue, 10.0);
    private_nh.param<std::string>("mobileGoalTopic", mobileGoalTopic, "/move_base_simple/goal");
    private_nh.param<std::string>("robot_frame", robot_frame, "base_link");
    private_nh.param<std::string>("map_frame", map_frame, "map");
    private_nh.param("rel_motion_mode", rel_motion_mode, false);

    boost::shared_ptr<RobotFollower> robot_follower(new RobotFollower(goalXYTolerance, map_frame, robot_frame, rel_motion_mode));

    ros::Subscriber mobileGoalSub = global_nh.subscribe(mobileGoalTopic, 1, &RobotFollower::goalCB, robot_follower);
    geometry_msgs::TwistStamped cmd_vel;
    ros::Rate loopRate(loopRateValue);

    while (ros::ok() && robot_follower->isInitialized()) {
        
        if(rel_motion_mode == false)
        {
            //angle tolerance does not have any effect in robot_follower mode.
            if (!robot_follower->isGoalReached()) {
                 ROS_INFO_THROTTLE(5, "[MAXL][robot_follower Node]: Goal Not Reached Yet");
                 //get command velocity
                 robot_follower->mw_maxl->computeVelocityForGoal(cmd_vel);
                 cmd_vel_pub.publish(cmd_vel.twist);

            }
            else
            {
                // publish zero command velocity
                geometry_msgs::TwistStamped zero_cmd_vel;
                cmd_vel_pub.publish(zero_cmd_vel.twist);
                ROS_INFO_THROTTLE(5, "[MAXL][robot_follower Node]: Goal Reached");
            }
        }
        else
        {
            if (!robot_follower->isGoalReached()) {
                 ROS_INFO_THROTTLE(5, "[MAXL][robot_follower Node]: Goal Not Reached Yet");
                 robot_follower->mw_maxl->computeVelocityForGoal(cmd_vel);
                 cmd_vel_pub.publish(cmd_vel.twist);
            }
            else
            {
                // publish zero command velocity
                geometry_msgs::TwistStamped zero_cmd_vel;
                cmd_vel_pub.publish(zero_cmd_vel.twist);
                ROS_INFO_THROTTLE(5, "[MAXL][robot_follower Node]: Goal Reached");
            }            
        }
        ros::spinOnce();
        loopRate.sleep();
    }
    return 0;
}
