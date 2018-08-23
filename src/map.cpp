//
// Created by lyfpcy on 23/08/2018.
//

#include "map.h"

namespace slam
{

    void Map::insertKeyFrame ( Frame::Ptr frame )
    {
        cout<<"Key frame size = "<<keyframes_.size()<<endl;

        keyframes_[ frame->id_ ] = frame;
    }

    void Map::insertMapPoint ( MapPoint::Ptr map_point )
    {
        map_points_[map_point->id_] = map_point;
    }
}