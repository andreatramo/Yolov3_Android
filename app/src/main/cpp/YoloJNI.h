//
// Created by user on 19/10/18.
//

#ifndef YOLOV3_OBJECTDETECTOR_YOLOJNI_H
#define YOLOV3_OBJECTDETECTOR_YOLOJNI_H

#include <jni.h>
#include "Yolo.h"

#ifdef __cplusplus
extern "C" {
#endif

//class YoloJNI

#define JULAYOM(rettype, name)                                             \
  rettype JNIEXPORT JNICALL Java_uk_lcas_andreatramo_yolov3_1objectdetector_MainActivity_##name


    Yolo* yolo_classifier;

    std::string jstr2str(JNIEnv * env, jobject obj, jstring jstr);
    jstring str2jstr(JNIEnv * env, jobject obj, std::string str);
    cv::String jstr2ostr(JNIEnv * env, jobject obj, jstring jstr);

JULAYOM(void, create)(JNIEnv * env, jobject obj,
                       jstring cfg_file,
                       jstring weights_file,
                       jfloat conf_thr,
                       jstring classNames_file);

JULAYOM(void, classify)(JNIEnv * env, jobject obj,
                           jlong input_frame, jlong output_frame);

#ifdef __cplusplus
}
#endif

#endif //YOLOV3_OBJECTDETECTOR_YOLOJNI_H
