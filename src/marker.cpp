#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <geometry_msgs/PoseStamped.h>
#include <nav_msgs/Odometry.h>
#include <vector>
#include <math.h>
using namespace std;

geometry_msgs::PoseStamped current_pose, set_point, target;
vector<geometry_msgs::PoseStamped> list_current_pose;
vector<double> list_distance;

void pose_cb(const geometry_msgs::PoseStamped::ConstPtr& msg) {

    list_current_pose.push_back(*msg);
}

double cal_distance(double x, double y, double z) {
    return sqrt(x*x+y*y+z*z);
}

int main( int argc, char** argv ) {
    ros::init(argc, argv, "error_init_pos");
    ros::NodeHandle nh;
    list_current_pose.clear();
    list_distance.clear();
    double total_distance = 0;
    ros::Subscriber local_pose_sub = nh.subscribe<geometry_msgs::PoseStamped>("/mavros/local_position/pose", 100, pose_cb);

    ros::Rate r(5);

    int count = 0;

    //600
    while ((ros::ok()) && (count < 600)) {
        ros::spinOnce();
        r.sleep();
        count ++;
        
    }

    //cout << "Length of vector = " << list_current_pose.size() << endl;
    int length = list_current_pose.size();
    for(int i=0; i<length; i++) {
        
        cout << "Diem thu " << i+1 << ":\nx = " << list_current_pose[i].pose.position.x
                            << "\ny = " << list_current_pose[i].pose.position.y
                            << "\nz = " << list_current_pose[i].pose.position.z << endl;

        double error_x = list_current_pose[i].pose.position.x - list_current_pose[0].pose.position.x;
        double error_y = list_current_pose[i].pose.position.y - list_current_pose[0].pose.position.y;
        double error_z = list_current_pose[i].pose.position.z - list_current_pose[0].pose.position.z;

        double distance = cal_distance(error_x, error_y, error_z);
        total_distance += distance;
        list_distance.push_back(distance);
    }
    cout << "Length of vector = " << list_current_pose.size() << endl;
    cout << "Length of distance = " << list_distance.size() << endl;
    cout << "Sai so trung binh tuyet doi = " << total_distance/(list_distance.size()) << endl;
     
}