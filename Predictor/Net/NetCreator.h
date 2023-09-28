#pragma once

#include "NetNCNN.h"
#include "NetRKNN.h"

class NetCreator{

public:
    static Net* createNet(NetConfig* netConfig){
        int ret;
        Net* net = nullptr;

        try{
            switch(netConfig->netType){
            case NetType::NET_NCNN:{
                net = new NetNCNN();
                break;
            }
            case NetType::NET_RKNN:{
                net = new NetRKNN(); 
                break;
            }
            }

            ret =net->init(netConfig);
            if(ret != 0){
                throw "Net init fail!";
            }
        }
        catch(const char* msg){
            printf("err: %s\n", msg);
            delete net;
            net = nullptr;
        }

        return net;
    }

};