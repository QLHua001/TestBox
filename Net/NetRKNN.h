#pragma once

#include "Net.h"

struct NetRKNNConfig : NetConfig{

};

class NetRKNN : public Net{
public:
    NetRKNN();
    virtual ~NetRKNN();

    virtual int init(NetConfig* netConfig);

    virtual int run(const NetInput& input, NetOutput& output);
};