#pragma once

#include <vector>
#include <string>
#include <map>

enum PostType{
    POST_DMS_MTFACE,
    POST_DMS_MTYOLOX
};

class PostUnit{
public:
struct Config{
    PostType postType;
};

struct Object{
    float xmin = 0.0f;
    float ymin = 0.0f;
    float xmax = 0.0f;
    float ymax = 0.0f;
    float score = 0.0f;
    int label = -1;
};

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
    // virtual int nms(std::vector<Object>& nmsObjVec, std::vector<Object>& objVec, std::vector<float>& objScoreVec, bool isMultiClassNMS);

private:
    // void singleClassNMS(std::vector<Object>& nmsObjVec, std::vector<Object>& objVec, std::vector<float>& objScoreVec);
    // void multiClassNMS(std::vector<Object>& nmsObjVec, std::vector<Object>& objVec, std::vector<float>& objScoreVec);
    // void qsortDescentInplace(std::vector<Object>& datas, std::vector<float>& scores);
    // void qsortDescentInplace(std::vector<Object>& datas, std::vector<float>& scores, int left, int right);
    // void nmsSortedBBoxes(const std::vector<Object>& bboxes, std::vector<size_t>& picked, float nmsThres);
    // float intersectionArea(const Object& a, const Object& b);
};

class PostDMSMTFace : public PostUnit{
public:
struct Config : PostUnit::Config{ 
    std::string aa;
    std::string bb;
    std::string cc;
};

public:
    virtual int run(const Input& input, Output& output);
};

class PostDMSMTYolox : public PostUnit{
public:
struct Config : PostUnit::Config{ 
    std::string xx;
    std::string yy;
    std::string zz;
};

public:
    virtual int run(const Input& input, Output& output);
};