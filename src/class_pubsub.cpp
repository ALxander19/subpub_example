#include <ros/ros.h>
#include <std_msgs/Int64.h>
#include <std_srvs/SetBool.h>

class NumberCounter {

  private:
    int counter;
    ros::Publisher pub;
    ros::Subscriber number_subscriber;
  
  public:
    NumberCounter(ros::NodeHandle *nh) {
      counter = 0;
      pub = nh->advertise<std_msgs::Int64>("/number_count", 10);    
      number_subscriber = nh->subscribe("/number", 1000, &NumberCounter::callback_number, this);
    }
  
    void callback_number(const std_msgs::Int64& msg) {
      counter += msg.data;
      std_msgs::Int64 new_msg;
      new_msg.data = counter;
      pub.publish(new_msg);
    }
};

int main (int argc, char **argv)
{
  ros::init(argc, argv, "number_counter");
  ros::NodeHandle nh;
  NumberCounter nc = NumberCounter(&nh);
  ros::spin();
}
