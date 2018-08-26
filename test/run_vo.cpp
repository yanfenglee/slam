//
// Created by lyfpcy on 23/08/2018.
//
// -------------- test the visual odometry -------------
#include <fstream>
#include <boost/timer.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/viz.hpp>

#include "Config.h"
#include "vo.h"

int main ( int argc, char** argv )
{
    if ( argc != 2 )
    {
        cout<<"usage: run_vo parameter_file"<<endl;
        return 1;
    }

    slam::Config::setParameterFile ( argv[1] );
    slam::VO::Ptr vo ( new slam::VO );

    string dataset_dir = slam::Config::get<string> ( "dataset_dir" );
    cout<<"dataset: "<<dataset_dir<<endl;
    ifstream fin ( dataset_dir+"/associate.txt" );
    if ( !fin )
    {
        cout<<"please generate the associate file called associate.txt!"<<endl;
        return 1;
    }

    vector<string> rgb_files, depth_files;
    vector<double> rgb_times, depth_times;
    while ( !fin.eof() )
    {
        string rgb_time, rgb_file, depth_time, depth_file;
        fin>>rgb_time>>rgb_file>>depth_time>>depth_file;
        rgb_times.push_back ( atof ( rgb_time.c_str() ) );
        depth_times.push_back ( atof ( depth_time.c_str() ) );
        rgb_files.push_back ( dataset_dir+"/"+rgb_file );
        depth_files.push_back ( dataset_dir+"/"+depth_file );

        if ( fin.good() == false )
            break;
    }

    slam::Camera::Ptr camera ( new slam::Camera );

    // visualization
    cv::viz::Viz3d vis("vo with bundle adjustment");
    cv::viz::WCoordinateSystem world_coor(1.0), camera_coor(0.5);
    cv::Point3d cam_pos( 0, -1.0, -1.0 ), cam_focal_point(0,0,0), cam_y_dir(0,1,0);
    cv::Affine3d cam_pose = cv::viz::makeCameraPose( cam_pos, cam_focal_point, cam_y_dir );
    vis.setViewerPose( cam_pose );

    world_coor.setRenderingProperty(cv::viz::LINE_WIDTH, 2.0);
    camera_coor.setRenderingProperty(cv::viz::LINE_WIDTH, 1.0);
    vis.showWidget( "World", world_coor );
    vis.showWidget( "Camera", camera_coor );

    cout<<"read total "<<rgb_files.size() <<" entries"<<endl;
    for ( int i=0; i<rgb_files.size(); i++ )
    {
        Mat color = cv::imread ( rgb_files[i] );
        Mat depth = cv::imread ( depth_files[i], -1 );
        if ( color.data==nullptr || depth.data==nullptr )
        {
            cout << "read image null" << endl;
            break;
        }

        slam::Frame::Ptr pFrame = slam::Frame::createFrame();
        pFrame->camera_ = camera;
        pFrame->color_ = color;
        pFrame->depth_ = depth;
        pFrame->time_stamp_ = rgb_times[i];

        boost::timer timer;
        vo->addFrame ( pFrame );
        cout<<"VO costs time: "<<timer.elapsed()<<endl;

        if ( vo->state_ == slam::VO::LOST )
        {
            cout << "vo state lost" << endl;
            break;
        }

        SE3 Tcw = pFrame->transform_.inverse();

        // show the map and the camera pose
        Eigen::Matrix3d m = Tcw.rotation_matrix();
        Eigen::Vector3d v =  Tcw.translation();

        cv::Affine3d camPos(cv::Affine3d::Mat3(
                        m(0,0), m(0,1), m(0,2),
                        m(1,0), m(1,1), m(1,2),
                        m(2,0), m(2,1), m(2,2)
                ),
                cv::Affine3d::Vec3(v(0), v(1), v(2))
        );

        cv::imshow("image", color );
        cv::waitKey(1);
        vis.setWidgetPose( "Camera", camPos);
        vis.setWindowSize(cv::Size(800,800));
        vis.spinOnce(1, false);
    }

    return 0;
}

