//
// Created by lj on 2022/6/28.
//

#include "string"
#include <iostream>
#include <vector>
#include "ros/ros.h"
#include <ros/package.h>

#include "std_msgs/String.h"

#include "BehaviorManager.h"
#include <BehaviorModule/need_msg.h>

class BehaviorNode
{
public:
    BehaviorNode(ros::NodeHandle& n);
    void readinBehaviorLibrary(const string &config_file){
        behaviorManager_->readinBehaviorLibrary(config_file);
        // behaviorManager_->printAllBehaviors();
    };

private:
    ros::NodeHandle n_;
    BehaviorManager *behaviorManager_;
    ros::Subscriber subscriber_need_;
    void need_for_behavior_callback(const BehaviorModule::need_msg &msg);
};

BehaviorNode::BehaviorNode(ros::NodeHandle& n)
{
    n_ = n;
    subscriber_need_ = n_.subscribe("need_lists", 1000, &BehaviorNode::need_for_behavior_callback, this);
    behaviorManager_ = new BehaviorManager(n_);
}

void BehaviorNode::need_for_behavior_callback(const BehaviorModule::need_msg &msg)
{
    cout << "【Received need_msg】" << msg.need_name << endl << endl;
    behaviorManager_->readInNewNeed(msg);
    return;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "behavior_node");
    ros::NodeHandle n;
    std::string config_file = ros::package::getPath("BehaviorModule") + "/data/behaviourData.json";
    // string config_file = "/home/lj/Documents/Indoor-mobile-robot-with-arms/src/BehaviorModule/data/behaviourData.json";
    BehaviorNode behavior_node(n);
    behavior_node.readinBehaviorLibrary(config_file);
    ros::spin();
    return 0;
}