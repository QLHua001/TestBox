#include <iostream>
#include <string>
#include <unordered_map>
#include <ncnn/net.h>
#include "NetNCNN.h"

NetNCNN::NetNCNN(){
    this->net = (HANDLE)(new ncnn::Net);
}

NetNCNN::~NetNCNN(){
    if(this->net){
        delete ((ncnn::Net*)this->net);
    }
    this->net = 0;
}

int NetNCNN::init(NetConfig* netConfig){

    int ret;
    NetNCNNConfig* config = (NetNCNNConfig*)netConfig;
    this->config = NetNCNNConfig(*config);

    ret = ((ncnn::Net*)this->net)->load_param(this->config.modelParam);
    if(ret == -1){
        printf("ncnn load_param fail!");
        return -1;
    }
    ret = ((ncnn::Net*)this->net)->load_model(this->config.modelBin);
    if(ret == -1){
        printf("ncnn load_model fail!");
        return -2;
    }

    return 0;
}

int NetNCNN::run(const NetInput& input, NetOutput& output){

    ncnn::Mat inputData = ncnn::Mat::from_pixels(input.data, ncnn::Mat::PIXEL_BGR, input.dataW, input.dataH);
    inputData.substract_mean_normalize(this->config.meanVal.data(), this->config.stdVal.data());

    ncnn::Extractor ex = ((ncnn::Net*)this->net)->create_extractor();
    ex.set_light_mode(true);
    ex.set_num_threads(1);

    output.data.resize(this->config.outputNodeVec.size());

    std::vector<ncnn::Mat> outputDataVec(this->config.outputNodeVec.size());
    ex.input(this->config.inputNodeVec[0], inputData);
    for(int i = 0; i < this->config.outputNodeVec.size(); i++){
        ex.extract(this->config.outputNodeVec[i], outputDataVec[i]);

        float* ptrData = (float*)outputDataVec[i].data;
        int dataLen = outputDataVec[i].d * outputDataVec[i].c * outputDataVec[i].h * outputDataVec[i].w;
        for(int j = 0; j < dataLen; j++){
            output.data[i].push_back(ptrData[j]);
        }
    }

    return 0;
}