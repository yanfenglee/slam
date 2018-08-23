//
// Created by lyfpcy on 23/08/2018.
//

#include "Config.h"

namespace slam
{

    shared_ptr<Config> Config::config_ = nullptr;

    void Config::setParameterFile( const std::string& filename )
    {
        if ( config_ == nullptr )
            config_ = shared_ptr<Config>(new Config);

        config_->file_ = cv::FileStorage( filename.c_str(), cv::FileStorage::READ );
        if ( config_->file_.isOpened() == false )
        {
            std::cerr<<"parameter file "<<filename<<" does not exist."<<std::endl;
            config_->file_.release();
            return;
        }
    }

    template<typename T> T Config::get( const std::string& key )
    {
        if ( config_ == nullptr )
            setParameterFile("slam.conf");

        return T( Config::config_->file_[key] );
    }

    Config::~Config()
    {
        if ( file_.isOpened() )
            file_.release();
    }

}