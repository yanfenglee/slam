//
// Created by lyfpcy on 23/08/2018.
//

#ifndef SLAM_MAP_H
#define SLAM_MAP_H

#include "common.h"
#include "frame.h"
#include "mappoint.h"

namespace slam
{
    class Map
    {
    public:
        typedef shared_ptr<Map> Ptr;
        map<unsigned long, MapPoint::Ptr >  map_points_;        // all landmarks
        map<unsigned long, Frame::Ptr >     keyframes_;         // all key-frames

    public:
        Map() {}

        void insertKeyFrame( Frame::Ptr frame );
        void insertMapPoint( MapPoint::Ptr map_point );
    };
}

#endif //SLAM_MAP_H
