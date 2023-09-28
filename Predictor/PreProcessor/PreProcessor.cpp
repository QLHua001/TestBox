#include <iostream>
#include <opencv2/opencv.hpp>
#include "PreProcessor.h"

PreProcessor::PreProcessor(Config* config){
    this->config = Config(*config);
}

PreProcessor::~PreProcessor(){

}

int PreProcessor::run(const Tensor& input, Tensor& output){

    //! 外部申请的数据内存，cv::Mat不参与内存管理，引用计数不起作用。
    cv::Mat srcMat(cv::Size(input.dataW, input.dataH), CV_8UC3, input.data);

    cv::Mat scaledMat(cv::Size(this->config.targetSize[0], this->config.targetSize[1]), CV_8UC3, output.data);
    cv::resize(srcMat, scaledMat, cv::Size(this->config.targetSize[0], this->config.targetSize[1]));
    output.dataW = scaledMat.cols;
    output.dataH = scaledMat.rows;
    output.sx = (double)srcMat.cols / scaledMat.cols;
    output.sy = (double)srcMat.rows / scaledMat.rows;

    return 0;

}