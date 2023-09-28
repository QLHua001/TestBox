#pragma once

#include <array>
#include <vector>

typedef long long HANDLE;

enum NetType{
    NET_NCNN,
    NET_RKNN
};

struct NetConfig{
    NetType netType;
    std::array<int, 2> inputShape;
    std::array<float, 3> meanVal;
    std::array<float, 3> stdVal;
};

struct NetInput{
    unsigned char* data{nullptr};
    int dataW{-1};
    int dataH{-1};
};

struct NetOutput{
    std::vector<std::vector<float>> data;
};

class Net{
public:
    Net(){};
    virtual ~Net(){};

    virtual int init(NetConfig* netConfig) = 0;
    virtual int run(const NetInput& input, NetOutput& output) = 0;
};