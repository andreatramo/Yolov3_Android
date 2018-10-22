//
// Created by user on 19/10/18.
//

#include <string>
#include "YoloJNI.h"
#include "Yolo.h"

JULAYOM(void, create)(JNIEnv * env, jobject obj,
                      jstring cfg,
                      jstring weights,
                      jfloat conf_t,
                      jstring classNames ){


    const cv::String& cfg_file = jstr2ostr(env, obj, cfg);
    const cv::String& weights_file = jstr2ostr(env, obj, weights);
    const float conf_thr = conf_t;
    const cv::String classNames_file = jstr2ostr(env, obj, classNames);

    yolo_classifier = new Yolo(cfg_file, weights_file, conf_thr, classNames_file);

}

JULAYOM(void, classify)(JNIEnv * env, jobject obj,
                           jlong input_frame, jlong output_frame){

    cv::Mat& in_frame = *(cv::Mat*) input_frame;
    cv::Mat out_frame = yolo_classifier->classify(in_frame);
    output_frame = (jlong) &out_frame;

}

std::string jstr2str(JNIEnv * env, jobject obj, jstring jstr) {

    const char *str = env->GetStringUTFChars(jstr, 0);
    return str;

}

jstring str2jstr(JNIEnv * env, jobject obj, std::string str) {

    return env->NewStringUTF(str.c_str());

}

cv::String jstr2ostr(JNIEnv * env, jobject obj, jstring jstr) {

    return cv::String(jstr2str(env, obj, jstr));

}

