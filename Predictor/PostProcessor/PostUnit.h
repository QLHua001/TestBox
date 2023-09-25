#pragma once

#include <vector>
#include <string>
#include <map>

class PostUnit{
public:

struct Input{
    std::vector<std::vector<float>> data;
    std::array<int, 2> netInputSize;
    std::array<int, 2> srcInputSize;
};

struct Output{
    std::map<std::string, std::vector<float>> reg;
    std::map<std::string, double> cls;
};

public:
    PostUnit(){};
    virtual ~PostUnit(){};

    virtual int run(const Input& input, Output& output) = 0;

};

class PostDmsMTFace : public PostUnit{
public:
    virtual int run(const Input& input, Output& output);
};