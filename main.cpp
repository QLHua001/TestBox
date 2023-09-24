#include <iostream>
#include <cmath>
#include <string>
#include <array>
#include <ncnn/net.h>
#include <opencv2/opencv.hpp>
#include "models/ncnn/DFMTN/DFMTN_16f.param.h"
#include "models/ncnn/DFMTN/DFMTN_16f.bin.h"

#include "Predictor/Predictor.h"

void test_ncnn_example(){
    std::string srcImgPath{"./imgs/face004.jpg"};

    const unsigned char* modelParam = DFMTN_16f_param_bin;
    const unsigned char* modelBin = DFMTN_16f_bin;
    std::vector<int> inputNodeVec{DFMTN_16f_param_id::BLOB_input};
    std::vector<int> outputNodeVec{DFMTN_16f_param_id::BLOB_lds, DFMTN_16f_param_id::BLOB_euler, DFMTN_16f_param_id::BLOB_cls1, DFMTN_16f_param_id::BLOB_cls2};
    std::array<int, 2> inputShape{160, 160}; // w, h
    std::array<float, 3> meanVal{127.5f, 127.5f, 127.5f};
    std::array<float, 3> stdVal{0.0078125f, 0.0078125f, 0.0078125f};


    // imread
    cv::Mat srcImg = cv::imread(srcImgPath);
    if(srcImg.empty()){
        printf("imread %s fail!\n", srcImgPath.c_str());
        return;
    }
    int srcImgW = srcImg.cols;
    int srcImgH = srcImg.rows;

    int ret;

    // init
    ncnn::Net net;
    ret = net.load_param(modelParam);
    if(ret == -1){
        printf("ncnn load_param fail!\n");
        return;
    }
    ret = net.load_model(modelBin);
    if(ret == -1){
        printf("ncnn load_model fail!\n");
        return;
    }

    // run
    cv::Mat scaledImg;
    cv::resize(srcImg, scaledImg, cv::Size(inputShape[0], inputShape[1]));
    ncnn::Mat inputData = ncnn::Mat::from_pixels(scaledImg.data, ncnn::Mat::PIXEL_BGR, scaledImg.cols, scaledImg.rows);
    inputData.substract_mean_normalize(meanVal.data(), stdVal.data());
    
    ncnn::Extractor ex = net.create_extractor();
    ex.set_light_mode(true);
    ex.set_num_threads(1);

    std::vector<ncnn::Mat> outputDataVec(outputNodeVec.size());
    ex.input(inputNodeVec[0], inputData);
    for(int i = 0; i < outputNodeVec.size(); i++){
        ex.extract(outputNodeVec[i], outputDataVec[i]);
    }

    // parse
    // # landmark
    std::array<cv::Point2f, 20> landmark; 
    for(int i = 0; i < landmark.size(); i++){
        float x = outputDataVec[0][i*2] * srcImgW;
        float y = outputDataVec[0][i*2+1] * srcImgH;
        landmark[i] = cv::Point2f(x, y);
    }

    // # euler
    std::array<float, 3> euler;
    for(int i = 0; i < euler.size(); i++){
        euler[i] = outputDataVec[1][i] * 180 / M_PI;
    }

    std::array<float, 7> cls;
    // # cls1, cls2
    cls[0] = outputDataVec[2][0];
    cls[1] = outputDataVec[2][1];
    cls[2] = outputDataVec[2][2];
    cls[3] = outputDataVec[3][0];
    cls[4] = outputDataVec[3][1];
    cls[5] = outputDataVec[3][2];
    cls[6] = outputDataVec[3][3];

    // show
    cv::Mat showImg = srcImg.clone();
    for(const auto& pt : landmark){
        cv::circle(showImg, pt, 1, cv::Scalar(0, 255, 0), -1);
    }
    for(const auto& angle : euler){
        printf("%.2f\t", angle);
    }
    printf("\n");
    for(const auto& score : cls){
        printf("%.2f\t", score);
    }
    cv::imwrite("./temp/showImg.jpg", showImg);
}

void test_Predictor(){
    std::string srcImgPath{"./imgs/face001.jpg"};

    NetNCNNConfig netConfig;
    netConfig.inputShape = std::array<int, 2>{160, 160};
    netConfig.meanVal = std::array<float, 3>{127.5f, 127.5f, 127.5f};
    netConfig.stdVal = std::array<float, 3>{0.0078125f, 0.0078125f, 0.0078125f};
    netConfig.modelParam = DFMTN_16f_param_bin;
    netConfig.modelBin = DFMTN_16f_bin;
    netConfig.inputNodeVec = std::vector<int>{DFMTN_16f_param_id::BLOB_input};
    netConfig.outputNodeVec = std::vector<int>{DFMTN_16f_param_id::BLOB_lds, DFMTN_16f_param_id::BLOB_euler, DFMTN_16f_param_id::BLOB_cls1, DFMTN_16f_param_id::BLOB_cls2};

    // imread
    cv::Mat srcImg = cv::imread(srcImgPath);
    if(srcImg.empty()){
        printf("imread %s fail!\n", srcImgPath.c_str());
        return;
    }
    int srcImgW = srcImg.cols;
    int srcImgH = srcImg.rows;

    Predictor::Config config;
    config.netType = NetType::NET_NCNN;
    config.netConfig = &netConfig;
    config.postType = PostType::POST_DMS_MTFACE;

    Predictor* predictor = new Predictor(config);

    Predictor::Input input;
    input.data = srcImg.data;
    input.dataW = srcImgW;
    input.dataH = srcImgH;

    // Predictor::Output output;
    PostUnit::Output output;
    predictor->run(input, output);

    // show
    cv::Mat showImg = srcImg.clone();
    const std::vector<float>& landmark = output.reg["landmark"];
    for(int i = 0; i < 20; i++){
        cv::Point2f pt(landmark[i*2], landmark[i*2+1]);
        cv::circle(showImg, pt, 1, cv::Scalar(0, 255, 0), -1);
    }
    const std::vector<float>& euler = output.reg["euler"];
    for(const auto& angle : euler){
        printf("%.2f\t", angle);
    }
    printf("\n");

    cv::imwrite("./temp/showImg.jpg", showImg);

    delete predictor;

}

int main(int argc, char* argv[]) {
    std::cout << "Hello, world!\n";

    // test_ncnn_example();

    test_Predictor();

}
