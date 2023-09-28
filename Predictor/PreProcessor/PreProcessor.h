#pragma once

#include <array>

class PreProcessor{
public:

struct Config{
    std::array<int, 2> targetSize{-1, -1};
};

struct Tensor{
    unsigned char* data{nullptr};
    int dataW{-1};
    int dataH{-1};
    double sx{-1};
    double sy{-1};
};

public:
    PreProcessor(Config* config);
    virtual ~PreProcessor();

    virtual int run(const Tensor& input, Tensor& output);

private:
    Config config;

};