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

int Predictor::run(Input input, PostUnit::Output& output){

    PreProcessor::Tensor preTensor;
    preTensor.data = input.data;
    preTensor.dataW = input.dataW;
    preTensor.dataH = input.dataH;
    this->preProcessor->run(preTensor, this->preTensor);

    printf("output: %d, %d, %f, %f\n", this->preTensor.dataW, this->preTensor.dataH, this->preTensor.sx, this->preTensor.sy);

    NetInput netInput;
    netInput.data = this->preTensor.data;
    netInput.dataW = this->preTensor.dataW;
    netInput.dataH = this->preTensor.dataH;

    NetOutput netOuptut;
    this->net->run(netInput, netOuptut);


    PostUnit::Input postInput;
    postInput.data = netOuptut.data;
    postInput.netInputSize = std::array<int, 2>{netInput.dataW, netInput.dataH};
    postInput.srcInputSize = std::array<int, 2>{input.dataW, input.dataH};

    // PostUnit::Output postOutput;
    this->postProcessor->run(postInput, output);

    return 0;
}
