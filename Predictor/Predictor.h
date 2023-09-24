#pragma once

#include <opencv2/opencv.hpp>
#include "Net/NetCreator.h"
#include "PreProcessor/PreProcessor.h"
#include "PostProcessor/PostProcessor.h"

class Predictor{
public:
    struct Config{
        NetType netType;
        NetConfig* netConfig;
        PostType postType;
    };

    struct Input{
        unsigned char* data;
        int dataW;
        int dataH;
    };

public:
    Predictor(Config config);
    virtual ~Predictor();

    int run(Input input, PostUnit::Output& output);
    // virtual int preProcessor(const cv::Mat& srcMat, cv::Mat& dstMat) = 0;
    // virtual int postProcessor() = 0;

private:
    Net* net = nullptr;
    PreProcessor* preProcessor = nullptr;
    PostProcessor* postProcessor = nullptr;

    PreProcessor::Tensor preTensor;
};