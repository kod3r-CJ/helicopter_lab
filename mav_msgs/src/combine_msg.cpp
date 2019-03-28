#include <ros/ros.h>
#include <mavros_msgs/Altitude.h>
#include <sensor_msgs/BatteryState.h>
#include <sensor_msgs/NavSatFix.h>
#include <mavros_msgs/HomePosition.h>
#include <sensor_msgs/Imu.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/TwistStamped.h>
#include <mavros_msgs/WaypointReached.h>
#include <mavros_msgs/State.h>
#include <mavros_msgs/WaypointList.h>
#include <iostream>
#include <mav_msgs/comb.h>
#include <mav_msgs/waypoint.h>
using namespace std;

mav_msgs::comb mav_msg;
mav_msgs::waypoint mav_way;

void altitude_cb(const mavros_msgs::Altitude::ConstPtr& msg){
    mav_msg.amsl = msg->amsl;
    mav_msg.relative = msg->relative;
}

void battery_cb(const sensor_msgs::BatteryState::ConstPtr& msg){
    mav_msg.voltage = msg->voltage;
}

void global_position_cb(const sensor_msgs::NavSatFix::ConstPtr& msg){
    mav_msg.global_latitude  = msg->latitude;
    mav_msg.global_longitude = msg->longitude;
    mav_msg.global_altitude  = msg->altitude;
}

void global_home_cb(const mavros_msgs::HomePosition::ConstPtr& msg){
    mav_msg.home_latitude  = msg->geo.latitude;
    mav_msg.home_longitude = msg->geo.longitude;
    mav_msg.home_altitude  = msg->geo.altitude;
    mav_msg.home_position  = msg->position;
    mav_msg.home_orientation  = msg->orientation;
}

void imuCallback(const sensor_msgs::Imu::ConstPtr &msg){

    mav_msg.orientation=msg->orientation;

}

void locpose_cb(const geometry_msgs::PoseStamped::ConstPtr &msg){

    mav_msg.loc_pose=msg->pose;

}

void loctwist_cb(const geometry_msgs::TwistStamped::ConstPtr &msg){

    mav_msg.loc_twist=msg->twist;
}

void mission_cb(const mavros_msgs::WaypointReached::ConstPtr &msg){

    mav_msg.wp_seq=msg->wp_seq;
}

void state_cb(const mavros_msgs::State::ConstPtr& msg){

    mav_msg.connected=msg->connected;
    mav_msg.armed=msg->armed;
    mav_msg.guided=msg->guided;
    mav_msg.mode=msg->mode;
    mav_msg.system_status=msg->system_status;

}

void waypoint_cb(const mavros_msgs::WaypointList::ConstPtr &msg){
    mav_way.waypointlist=*msg;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "mav_msgs");
    ros::NodeHandle nh;
 
    ros::Subscriber alt_sub = nh.subscribe<mavros_msgs::Altitude>
            ("/mavros/atitue", 10, altitude_cb);
    ros::Subscriber bat_sub = nh.subscribe<sensor_msgs::BatteryState>
            ("/mavros/battery", 10, battery_cb);
    ros::Subscriber gpos_sub = nh.subscribe<sensor_msgs::NavSatFix>
            ("/mavros/global_position/global", 10, global_position_cb);
    ros::Subscriber ghom_sub = nh.subscribe<mavros_msgs::HomePosition>
            ("/mavros/global_position/home", 10, global_home_cb);
    ros::Subscriber imu_sub = nh.subscribe<sensor_msgs::Imu>
            ("/mavros/imu/data",10,imuCallback);
    ros::Subscriber loc_pose_sub = nh.subscribe<geometry_msgs::PoseStamped>
            ("/mavros/local_position/pose", 10, locpose_cb);
    ros::Subscriber loc_twist_sub = nh.subscribe<geometry_msgs::TwistStamped>
            ("/mavros/local_position/velocity",10,loctwist_cb);
    ros::Subscriber mission_sub = nh.subscribe<mavros_msgs::WaypointReached>
            ("/mavros/mission/reached",10,mission_cb);
    ros::Subscriber state_sub = nh.subscribe<mavros_msgs::State>
            ("mavros/state", 10, state_cb);
    ros::Subscriber waypoint_sub = nh.subscribe<mavros_msgs::WaypointList>
            ("mavros/mission/waypoints", 10, waypoint_cb);
    
    ros::Publisher msg_pub = nh.advertise<mav_msgs::comb>
            ("mav_msgs", 100);
    //ros::Publisher msg_pub = nh.advertise<mav_msgs::comb>
     //       ("mav_waypoints", 100);
   
    //the setpoint publishing rate MUST be faster than 2Hz
    ros::Rate rate(20.0);
  
    mav_msg.header.stamp=ros::Time::now();
    //ros::Time last_request = ros::Time::now();

    while(ros::ok()){

        msg_pub.publish(mav_msg);

        ros::spinOnce();
        rate.sleep();
    }

    return 0;
}