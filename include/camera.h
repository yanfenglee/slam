//
// Created by lyfpcy on 23/08/2018.
//

#ifndef SLAM_CAMERA_H
#define SLAM_CAMERA_H

#include "common.h"

namespace slam
{
    class Camera
    {
    public:
        typedef shared_ptr<Camera> Ptr;
        double fx_, fy_, cx_, cy_, depth_scale_;

    public:
        Camera();
        Camera(double fx, double fy, double cx, double cy, float depth_scale = 0) :
            fx_(fx), fy_(fy), cx_(cx), cy_(cy), depth_scale_(depth_scale)
        {}

        // coordinate transform: world, camera, pixel
        Vector3d world2camera( const Vector3d& pos, const SE3& transform );
        Vector3d camera2world( const Vector3d& pos, const SE3& transform );
        Vector2d camera2pixel( const Vector3d& pos );
        Vector3d pixel2camera( const Vector2d& uv, double depth=1 );
        Vector3d pixel2world ( const Vector2d& uv, const SE3& transform, double depth=1 );
        Vector2d world2pixel ( const Vector3d& pos, const SE3& transform );
    };
}

#endif //SLAM_CAMERA_H
