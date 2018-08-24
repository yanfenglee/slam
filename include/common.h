//
// Created by lyfpcy on 23/08/2018.
//

#ifndef SLAM_COMMON_H
#define SLAM_COMMON_H

#include <Eigen/Core>
#include <Eigen/Geometry>
using Eigen::Vector2d;
using Eigen::Vector3d;

// for Sophus
#include <sophus/so3.h>
#include <sophus/se3.h>
using Sophus::SE3;
using Sophus::SO3;

// for cv
#include <opencv2/core/core.hpp>
using cv::Mat;

// std
#include <vector>
#include <list>
#include <memory>
#include <string>
#include <iostream>
#include <set>
#include <unordered_map>
#include <map>

using namespace std;

#endif //SLAM_COMMON_H
