//
// Created by lyfpcy on 23/08/2018.
//

#include "camera.h"
#include "Config.h"

namespace slam
{
    Camera::Camera()
    {
        fx_ = Config::get<float>("camera.fx");
        fy_ = Config::get<float>("camera.fy");
        cx_ = Config::get<float>("camera.cx");
        cy_ = Config::get<float>("camera.cy");
        depth_scale_ = Config::get<float>("camera.depth_scale");
    }

    Vector3d Camera::world2camera ( const Vector3d& pos, const SE3& transform )
    {
        return transform * pos;
    }

    Vector3d Camera::camera2world ( const Vector3d& pos, const SE3& transform )
    {
        return transform.inverse() * pos;
    }

    Vector2d Camera::camera2pixel ( const Vector3d& pos )
    {
        return Vector2d (
            fx_ * pos(0) / pos(2) + cx_,
            fy_ * pos(1) / pos(2) + cy_
        );
    }

    Vector3d Camera::pixel2camera ( const Vector2d& uv, double depth )
    {
        return Vector3d (
            (uv(0) - cx_) * depth / fx_,
            (uv(1) - cy_) * depth / fy_,
            depth
        );
    }

    Vector2d Camera::world2pixel ( const Vector3d& pos, const SE3& transform )
    {
        return camera2pixel ( world2camera ( pos, transform ) );
    }

    Vector3d Camera::pixel2world ( const Vector2d& uv, const SE3& transform, double depth )
    {
        return camera2world ( pixel2camera ( uv, depth ), transform );
    }
}