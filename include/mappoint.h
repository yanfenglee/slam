//
// Created by lyfpcy on 23/08/2018.
//

#ifndef SLAM_MAPPOINT_H
#define SLAM_MAPPOINT_H

#include "common.h"

namespace slam
{

    class Frame;
    class MapPoint
    {
    public:
        typedef shared_ptr<MapPoint> Ptr;
        unsigned long      id_; // ID
        Vector3d    pos_;       // Position in world
        Vector3d    norm_;      // Normal of viewing direction
        Mat         descriptor_; // Descriptor for matching
        int         observed_times_;    // being observed by feature matching algo.
        int         correct_times_;     // being an inliner in pose estimation

        MapPoint();
        MapPoint( long id, Vector3d position, Vector3d norm );

        // factory function
        static MapPoint::Ptr createMapPoint();
    };
}

#endif //SLAM_MAPPOINT_H
