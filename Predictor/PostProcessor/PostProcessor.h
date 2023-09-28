#pragma once

#include <vector>
#include <array>
#include <string>
#include <map>
#include "PostUnit.h"

class PostProcessor{

public:

// struct Config{
//     PostType postType;
// };

public:
    PostProcessor(PostUnit::Config* config);
    ~PostProcessor();

    int run(const PostUnit::Input& input, PostUnit::Output& output);

private:

    PostUnit* postUnit = nullptr;

};