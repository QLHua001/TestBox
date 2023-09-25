#pragma once

#include <vector>
#include <array>
#include <string>
#include <map>
#include "PostUnit.h"

enum PostType{
    POST_DMS_MTFACE
};

class PostProcessor{

public:

struct Config{
    PostType postType;
};

public:
    PostProcessor(Config* config);
    ~PostProcessor();

    int run(const PostUnit::Input& input, PostUnit::Output& output);

private:
    Config config;
    PostUnit* postUnit = nullptr;

};