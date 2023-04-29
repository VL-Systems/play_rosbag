#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>

class OdomFilter
{
public:
    OdomFilter(ros::NodeHandle *nodehandle);

private:
    ros::NodeHandle nh_;
    ros::Subscriber odom_iput;
    ros::Publisher odom_output;
    tf::TransformBroadcaster odom_broadcaster;

    void initialSubscribers();
    void initialPublisher();
    void callback(const nav_msgs::Odometry::ConstPtr &msg);
};

OdomFilter::OdomFilter(ros::NodeHandle *nodehandle) : nh_(*nodehandle)
{ // Конструктор класса
    initialSubscribers();
    initialPublisher();
}

// Запуск subscribers
void OdomFilter::initialSubscribers()
{
    odom_iput = nh_.subscribe("/odom_input", 1, &OdomFilter::callback, this);
}

// Запуск publishers
void OdomFilter::initialPublisher()
{
    odom_output = nh_.advertise<nav_msgs::Odometry>("/odom_output", 1, true);
}

// Функция оправляет данные в /tf и формирует копию одометрию
void OdomFilter::callback(const nav_msgs::Odometry::ConstPtr &msg)
{
    ros::Time current_time, last_time;
    current_time = msg->header.stamp;
    last_time = ros::Time::now();

    geometry_msgs::TransformStamped odom_trans;
    odom_trans.header.stamp = current_time;
    odom_trans.header.frame_id = "odom";
    odom_trans.child_frame_id = "base_link";

    odom_trans.transform.translation.x = msg->pose.pose.position.x;
    odom_trans.transform.translation.y = msg->pose.pose.position.y;
    odom_trans.transform.translation.z = msg->pose.pose.position.z;
    odom_trans.transform.rotation = msg->pose.pose.orientation;
    odom_broadcaster.sendTransform(odom_trans);

    nav_msgs::Odometry odom;
    odom.header.stamp = current_time;
    odom.header.frame_id = "odom";
    odom.child_frame_id = "base_link";

    odom.pose.pose.position = msg->pose.pose.position;
    odom.pose.pose.orientation = msg->pose.pose.orientation;
    odom.twist.twist = msg->twist.twist;
    odom_output.publish(odom);
}

int main(int argc, char *argv[])
{

    ros::init(argc, argv, "Odometry");
    ros::NodeHandle nh2;
    OdomFilter odomfilter(&nh2);
    ros::Rate rate(30);
    while (nh2.ok())
    {
        rate.sleep();
        ros::spin();
    }
    ros::shutdown();
    return 0;
}