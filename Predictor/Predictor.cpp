#include <iostream>
#include "Predictor.h"

Predictor::Predictor(Config config){

    this->net = NetCreator::createNet(config.netType, config.netConfig);
    if(this->net == nullptr){
        printf("NetCreator::createNet fail!\n");
    }

    PreProcessor::Config preConfig;
    preConfig.targetSize = std::array<int, 2>{config.netConfig->inputShape[0], config.netConfig->inputShape[1]};
    this->preProcessor = new PreProcessor(&preConfig);

    PostProcessor::Config postConfig;
    postConfig.postType = config.postType;
    this->postProcessor = new PostProcessor(&postConfig);

}

Predictor::~Predictor(){
    if(this->net){
        delete this->net;
    }
    this->net = nullptr;

    if(this->preProcessor){
        delete this->preProcessor;
    }
    this->preProcessor = nullptr;

    if(this->postProcessor){
        delete this->postProcessor;
    }
    this->postProcessor = nullptr;
}

int Predictor::run(const PreProcessor::Tensor& input, PostUnit::Output& output){
    
    PreProcessor::Tensor outputTensor;
    this->preProcessor->run(input, outputTensor);

    NetInput netInput = {outputTensor.data, outputTensor.dataW, outputTensor.dataH};
    NetOutput netOuptut;
    this->net->run(netInput, netOuptut);

    PostUnit::Input postInput = {netOuptut.data, netInput.dataW, netInput.dataH, input.dataW, input.dataH};
    this->postProcessor->run(postInput, output);

    return 0;
}
