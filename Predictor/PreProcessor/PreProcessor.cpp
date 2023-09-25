#include <iostream>
#include <opencv2/opencv.hpp>
#include "PreProcessor.h"

PreProcessor::PreProcessor(Config* config){
    this->config = Config(*config);
}

PreProcessor::~PreProcessor(){

}

int PreProcessor::run(const Tensor& input, Tensor& output){

    cv::Mat srcMat = cv::Mat(cv::Size(input.dataW, input.dataH), CV_8UC3, input.data);

    cv::Mat scaledMat;
    cv::resize(srcMat, scaledMat, cv::Size(this->config.targetSize[0], this->config.targetSize[1]));

    output.data = scaledMat.data;
    output.dataW = scaledMat.cols;
    output.dataH = scaledMat.rows;
    output.sx = (double)srcMat.cols / scaledMat.cols;
    output.sy = (double)srcMat.rows / scaledMat.rows;

    // printf("input: %d, %d, %f, %f\n", input.dataW, input.dataH, input.sx, input.sy);
    // printf("output: %d, %d, %f, %f\n", output.dataW, output.dataH, output.sx, output.sy);

    return 0;

}