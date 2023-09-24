#pragma once

#include <vector>
#include "Net.h"

typedef long long HANDLE;

struct NetNCNNConfig : NetConfig{
    const unsigned char* modelParam;
    const unsigned char* modelBin;
    std::vector<int> inputNodeVec;
    std::vector<int> outputNodeVec;
};

class NetNCNN : public Net{
public:
    NetNCNN();
    virtual ~NetNCNN();

    virtual int init(NetConfig* netConfig);

    virtual int run(const NetInput& input, NetOutput& output);

private:
    NetNCNNConfig config;
    
    HANDLE net;
};