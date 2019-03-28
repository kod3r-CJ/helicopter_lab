# Package for combinig different interested topics in to a single publisher (mav_msgs).
custom message contains

#header
```
std_msgs/Header header
```
#altitude
```
float32 amsl
float32 relative
```
#battery
```
float32 voltage
```
#Global_postion_global (check covariance needed)_
```
float64 global_latitude
float64 global_longitude
float64 global_altitude
```
#Global_postition_home
```
float64 home_latitude
float64 home_longitude
float64 home_altitude
geometry_msgs/Quaternion home_orientation
geometry_msgs/Point home_position
```
#imu
```
geometry_msgs/Quaternion orientation
```

#local_pose
```
geometry_msgs/Pose loc_pose
```

#local_velocity
```
geometry_msgs/Twist loc_twist
```

#mission_reached
```
uint16 wp_seq
```

#mavros_state
```
bool connected
bool armed
bool guided
string mode
uint8 system_status
```

waypoints topic is not added , (they contain a array of points), they can be taken seperately subcribed (they not had headers) or can differectly acces this topic
```
mavros/mission/waypoints
```
