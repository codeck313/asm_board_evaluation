#include "ros/ros.h"
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Twist.h>
#include <string>
#include<iostream>
using namespace std;

ros::Publisher pub;

string status = "" ;
float linear_x = 0;
float angular_z = 0;

geometry_msgs::Twist message;


void checkcase(float right , float center , float left)
{
    if ( right >1.5  and center > 1.5 and left >1.5)
    {
        status = "NO OBSTACLE!";
        linear_x=0.6;
        angular_z=0;
    }
    else if ( right > 1.5  and center < 1.5 and left > 1.5 )
    {
        status = "OBSTACLE CENTER!";
        linear_x=0;
        angular_z=-0.5;
    }
    else if ( right < 1.5  and center > 1.5 and left > 1.5 )
    {
        status = "OBSTACLE RIGHT!";
        linear_x=0;
        angular_z=0.5;
    }
    else if ( right > 1.5  and center > 1.5 and left < 1.5 )
    {
        status = "OBSTACLE LEFT!";
        linear_x=0;
        angular_z=-0.5;
    }
    else if ( right < 1.5  and center > 1.5 and left < 1.5 )
    {
        status = "OBSTACLE RIGHT AND LEFT!";
        linear_x=0.6;
        angular_z=0;
    }
    else if ( right > 1.5  and center < 1.5 and left < 1.5 )
    {
        status = "OBSTACLE CENTER AND LEFT!";
        linear_x=0;
        angular_z=-0.5;
    }
    else if ( right < 1.5  and center < 1.5 and left > 1.5 )
    {
        status = "OBSTACLE CENTER AND RIGHT!";
        linear_x=0;
        angular_z=0.5;
    }
    else if ( right < 1.5  and center < 1.5 and left < 1.5 )
    {
        status = "OBSTACLE AHEAD!";
        linear_x=0;
        angular_z=0.8;
    }

    message.linear.x=linear_x;
    message.angular.z=angular_z;
    pub.publish(message);

    
    //ROS_WARN("%s",status);
    cout<<"  "<<status;
    cout<<"  "<<right;
    cout<<"  "<<center;
    cout<<"   "<<left;
    cout<<"\n"; 

}


float smallestofarray(float arr[] , int n)
{
    float temp = 2.0;
    cout<<"START\n";
    for(int i=0; i<n; i++) 
    {
      cout<<arr[i]<<" ";
      if(temp>arr[i]) 
      {
         temp=arr[i];
      }
   }
    cout<<"\n";
   return temp;
}

void laser_callback(const sensor_msgs::LaserScan::ConstPtr& msg)
{
    int length = msg->ranges.size();
    int lendiv3 = (length)/3;
    float right[length/3]={1000} , center[length/3] = {1000} , left[length/3] = {1000};
    for( int i=0 ; i < length ; i++)
    {
        if(i < lendiv3)
        {
            right[i] = msg->ranges[i];
        }
        else if ((i > lendiv3-1) && (i < 2*lendiv3))
        {
            center[i-90] =  msg->ranges[i]; 
        }
        else if (((2*lendiv3)-1) && (i < length))
        {
            left[i - 180] = msg->ranges[i]; 
        }        
    }
    float rightmin = smallestofarray(right , length/3);
    float centermin = smallestofarray(center , length/3);
    float leftmin = smallestofarray(left , length/3);

    checkcase(rightmin , centermin , leftmin);



}


int main(int argc, char **argv)
{
    ros::init(argc, argv, "obstacle_avoid");
    ros::NodeHandle n;

    pub = n.advertise<geometry_msgs::Twist>("robot5/cmd_vel", 10);
    ros::Subscriber sub = n.subscribe("robot5/scan_filtered", 10, laser_callback);

    ros::spin();
    return 0;
}
