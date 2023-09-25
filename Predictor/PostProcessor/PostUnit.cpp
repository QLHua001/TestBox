#include <cmath>
#include "PostUnit.h"

int PostDmsMTFace::run(const Input& input, Output& output){

    const std::vector<float>& landmarkRawVec = input.data[0];
    std::vector<float> landmarkVec;
    for(int i = 0; i < 20; i++){
        landmarkVec.push_back(landmarkRawVec[i*2]*input.srcInputSize[0]);
        landmarkVec.push_back(landmarkRawVec[i*2+1]*input.srcInputSize[1]);
    }

    const std::vector<float>& eulerRawVec = input.data[1];
    std::vector<float> eulerVec(3);
    eulerVec[0] = eulerRawVec[0] * 180 / M_PI;
    eulerVec[1] = eulerRawVec[1] * 180 / M_PI;
    eulerVec[2] = eulerRawVec[2] * 180 / M_PI;

    const std::vector<float>& cls1RawVec = input.data[2];
    const std::vector<float>& cls2RawVec = input.data[3];
    std::vector<float> clsVec(7);
    clsVec[0] = cls1RawVec[0];
    clsVec[1] = cls1RawVec[1];
    clsVec[2] = cls1RawVec[2];
    clsVec[3] = cls2RawVec[0];
    clsVec[4] = cls2RawVec[1];
    clsVec[5] = cls2RawVec[2];
    clsVec[6] = cls2RawVec[3];
    
    output.reg["landmark"] = landmarkVec;
    output.reg["euler"] = eulerVec;
    output.cls["smoke"] = clsVec[0];
    output.cls["yawn"] = clsVec[1];
    output.cls["mask"] = clsVec[2];
    output.cls["IRBlock"] = clsVec[3];
    output.cls["leftEyeInvisible"] = clsVec[4];
    output.cls["rightEyeInvisible"] = clsVec[5];
    output.cls["mouthInvisible"] = clsVec[6];

    return 0;
}