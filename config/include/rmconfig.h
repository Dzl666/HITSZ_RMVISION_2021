#include<glog/logging.h>
#include<json/json.h>
#include<constants.h>
#include<fstream>
#include<opencv2/opencv.hpp>
#ifndef H_RMCONFIG
#define H_RMCONFIG

//程序运行时各参数设置类
class CameraConfig{
public:
    double fx,fy,cx,cy,k1,k2,p1,p2,k3;
    cv::Mat mtx,dist,mapx,mapy;
    cv::Mat getCameraMatrix(){
        return mtx;
    }   
    cv::Mat getDistCoeff(){
        return dist;
    }
    void init();
    void undistort(cv::Mat& frame){
        remap(frame,frame,mapx,mapy, cv::INTER_LINEAR);
    }
    
};
class RmConfig{
public:
    const char* configPath = "rmconfig.json";
    //config
    bool show_origin = false;
    bool show_armor_box = false;
    bool show_light_box = false;
    bool show_class_id = false;
    bool wait_uart = false;
    bool save_video = false;
    bool show_light_blobs = false;
    bool save_labelled_boxes = false;
    bool show_pnp_axies = false;

    //DATA
    int ARMOR_CAMERA_EXPOSURE = 4000;
    int ARMOR_CAMERA_GAIN = 8;
    int ENERGY_CAMERA_EXPOSURE = 4000;
    int ENERGY_CAMERA_GAIN = 5;
    int ENEMY_COLOR = ENEMY_RED;
    int ANTI_TOP = 0;
    int ARMOR_H = 127;
    int ARMOR_W = 230;

    
    //Camera
    CameraConfig camConfig;

    void init_from_file();
    void write_to_file();
};

#endif