#include <iostream>
#include "Predictor.h"

Predictor::Predictor(Config config){

    this->net = NetCreator::createNet(config.netConfig);
    if(this->net == nullptr){
        printf("NetCreator::createNet fail!\n");
    }

    config.preConfig->targetSize = std::array<int, 2>{config.netConfig->inputShape[0], config.netConfig->inputShape[1]};
    this->preProcessor = new PreProcessor(config.preConfig);
    
    this->postProcessor = new PostProcessor(config.postConfig);

    this->ptrTensor = new unsigned char[config.netConfig->inputShape[0] * config.netConfig->inputShape[1] * 3];

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

    if(this->ptrTensor){
        delete[] this->ptrTensor;
    }
    this->ptrTensor = nullptr;
}

int Predictor::run(const PreProcessor::Tensor& input, PostUnit::Output& output){
    
    PreProcessor::Tensor outputTensor;
    outputTensor.data = this->ptrTensor; // 预分配内存
    this->preProcessor->run(input, outputTensor);

    NetInput netInput = {outputTensor.data, outputTensor.dataW, outputTensor.dataH};
    NetOutput netOuptut;
    this->net->run(netInput, netOuptut);

    PostUnit::Input postInput = {netOuptut.data, netInput.dataW, netInput.dataH, input.dataW, input.dataH};
    this->postProcessor->run(postInput, output);

    return 0;
}
