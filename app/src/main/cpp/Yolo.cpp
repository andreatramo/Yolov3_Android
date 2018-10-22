//
// Created by user on 16/10/18.
//

#include "Yolo.h"

using namespace cv;
using namespace std;

Yolo::Yolo(const cv::String& cfg_file,
        const cv::String& weights_file,
        const float conf_thr,
        const String classNames_file):
        my_confidence_threshold(conf_thr) {

    readClassNames(classNames_file);

    try {
        std::cout << "Model cfg: " << cfg_file << std::endl;
        std::cout << "Model weigth: " << weights_file << std::endl;
        //import the model of the network
        my_net = cv::dnn::readNetFromDarknet(cfg_file, weights_file);
        my_net.setPreferableBackend(cv::dnn::DNN_BACKEND_OPENCV);
        my_net.setPreferableTarget(cv::dnn::DNN_TARGET_CPU);
    }
    catch (cv::Exception& e) {
        std::cout << "WARNING: YOLOClassifier not initialized correctly!"
                  << std::endl;
        std::cout << e.what() << std::endl;
    }

}


Mat Yolo::classify(const Mat &frame) {

    Mat result(frame.clone());

    if (result.channels() == 4)
        cvtColor(result, result, COLOR_BGRA2BGR);

    //create the blob for the network
    Mat blob = dnn::blobFromImage(result, 1/255.F, Size(416,416), Scalar(), true, false);
    my_net.setInput(blob, "data");
    Mat output = my_net.forward(getOutputsNames());

    for (int i=0; i<output.rows; i++) {
        Mat scores = output.row(i).colRange(5, output.cols);

        Point maxLoc;
        double maxVal;
        minMaxLoc(scores, 0, &maxVal, 0, &maxLoc);

        //draw box over the subject found
        if (maxVal > my_confidence_threshold) {

            int idx = (int) maxLoc.x;
            int x = (int) (output.at<float>(i, 0) * frame.cols);
            int y = (int) (output.at<float>(i, 1) * frame.rows);
            int w = (int) (output.at<float>(i, 2) * frame.cols);
            int h = (int) (output.at<float>(i, 3) * frame.rows);

            Point p1(cvRound(x - w / 2), cvRound(y - h / 2));
            Point p2(cvRound(x + w / 2), cvRound(y + h / 2));

            Rect object(p1, p2);

            Scalar object_roi_color(0, 255, 0);

            rectangle(result, object, object_roi_color);
            putText(result, class_names[idx], p1, FONT_HERSHEY_SIMPLEX, 0.75, Scalar(0,255,0), 2);

        }

    }
    return result;

}


String Yolo::getOutputsNames() {

    vector<int> outLayers = my_net.getUnconnectedOutLayers();
    vector<String> layers = my_net.getLayerNames();
    vector<String> names = vector<String>(outLayers.size());
    for (int i=0; i<outLayers.size(); i++)
        names[i] = layers[outLayers[i]-1];

    return names[1];

}


void Yolo::readClassNames(String path) {

    ifstream infile(path);
    string line;
    while( getline(infile, line) )
        class_names.push_back(line);

}


