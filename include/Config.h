//
// Created by lyfpcy on 23/08/2018.
//

#ifndef SLAM_CONFIG_H
#define SLAM_CONFIG_H

#include "common.h"

namespace slam
{
    class Config
    {
    private:
        static std::shared_ptr<Config> config_;
        cv::FileStorage file_;

        Config () {} // private constructor makes a singleton
    public:
        ~Config();  // close the file when deconstructing

        // set a new config file
        static void setParameterFile( const std::string& filename );

        // access the parameter values
        template< typename T >
        static T get( const std::string& key )
        {
            if ( config_ == nullptr )
                setParameterFile("slam.yaml");

            return T( Config::config_->file_[key] );
        }
    };
}

#endif //SLAM_CONFIG_H
