//
// Created by user on 16/10/18.
//

#ifndef OBJECTDETECTION_1_YOLO_H
#define OBJECTDETECTION_1_YOLO_H

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/video.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/dnn/shape_utils.hpp>
#include <opencv2/highgui.hpp>
#include <fstream>

#include <jni.h>


class Yolo {

private:
    cv::dnn::Net my_net;
    const double my_confidence_threshold;
    std::vector<cv::String> class_names;

    cv::String getOutputsNames();
    void readClassNames(cv::String path);


public:
    Yolo(const cv::String& cfg_file,
         const cv::String& weights_file,
         const float conf_thr,
         const cv::String classNames_file);
    cv::Mat classify(const cv::Mat& frame);

};


#endif //OBJECTDETECTION_1_YOLO_H
