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

public:
    Predictor(Config config);
    ~Predictor();

    int run(const PreProcessor::Tensor& input, PostUnit::Output& output);

private:
    Net* net = nullptr;
    PreProcessor* preProcessor = nullptr;
    PostProcessor* postProcessor = nullptr;
};