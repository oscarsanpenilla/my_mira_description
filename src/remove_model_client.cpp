#include <iostream>
#include <ros/ros.h>
#include <gazebo_msgs/DeleteModel.h>

class RemoveModelClient
{
private:
    ros::ServiceClient remove_robot_client_;
    bool removeModel(std::string model);

public:
    RemoveModelClient(std::string model);
};

bool RemoveModelClient::removeModel(std::string model)
{
    ROS_INFO("Waiting for service...");
    remove_robot_client_.waitForExistence(ros::Duration(3.0));
    gazebo_msgs::DeleteModel srv;
    srv.request.model_name = model.c_str();
    if (remove_robot_client_.call(srv))
    {
        ROS_INFO("[SUCCESS]: Model %s deleted.", model.c_str());
        return true;
    }
    else
    {
        ROS_ERROR("Deleting the model.");
        return false;
    }
}

RemoveModelClient::RemoveModelClient(std::string model)
{
    ros::NodeHandle n;
    remove_robot_client_ = n.serviceClient<gazebo_msgs::DeleteModel::Request, gazebo_msgs::DeleteModel::Response>("gazebo/delete_model", this);
    removeModel(model);
}

int main(int argc, char **args)
{
    ros::init(argc, args, "remove_robot_client");
    if (argc != 2)
    {
        ROS_INFO("[ERROR]: Model name required");
        return -1;
    }
    std::string model = args[1];
    RemoveModelClient remove_model(model);
}