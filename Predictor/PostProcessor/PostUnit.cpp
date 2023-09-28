#include <cmath>
#include "PostUnit.h"

// int PostUnit::nms(std::vector<Object>& nmsObjVec, std::vector<Object>& objVec, std::vector<float>& objScoreVec, bool isMultiClassNMS){

//     if(isMultiClassNMS){
//         this->multiClassNMS(nmsObjVec, objVec, objScoreVec);
//     }else{
//         this->singleClassNMS(nmsObjVec, objVec, objScoreVec);
//     }

//     return 0;
// }

// void PostUnit::singleClassNMS(std::vector<Object>& nmsObjVec, std::vector<Object>& objVec, std::vector<float>& objScoreVec){
//     nmsObjVec.clear();
    
//     this->qsortDescentInplace(objVec, objScoreVec);

//     std::map<int, std::vector<Object>> objMap;
//     std::map<int, std::vector<float>> objScoreMap;
//     for(int i = 0; i < objVec.size(); i++){
//         Object obj = objVec[i];
//         objMap[obj.label].push_back(obj);
//         objScoreMap[obj.label].push_back(objScoreVec[i]);
//     }

//     for(const auto& item : objMap){
//         const auto& label = item.first;
//         const auto& objVec = item.second; 

//         // apply nms
//         std::vector<size_t> picked;
//         this->nmsSortedBBoxes(objVec, picked, m_stCfg.nms_thresh);

//         int count = picked.size();

//         float h_ratio = float(inputData.imgHeight) / m_stCfg.baseCfg.netHeight;
//         float w_ratio = float(inputData.imgWidth) / m_stCfg.baseCfg.netWidth;

        
//         for (int i = 0; i < count; i++) {
//             Object obj = objVec[picked[i]];

//             obj.xmin *= w_ratio;
//             obj.ymin *= h_ratio;
//             obj.xmax *= w_ratio;
//             obj.ymax *= h_ratio;
//             if (!m_stCfg.allow_cross_border) {
//                 obj.xmin = BSJ_MAX(BSJ_MIN(obj.xmin, (float)inputData.imgWidth - 1), 0.f);
//                 obj.ymin = BSJ_MAX(BSJ_MIN(obj.ymin, (float)inputData.imgHeight - 1), 0.f);
//                 obj.xmax = BSJ_MAX(BSJ_MIN(obj.xmax, (float)inputData.imgWidth - 1), 0.f);
//                 obj.ymax = BSJ_MAX(BSJ_MIN(obj.ymax, (float)inputData.imgHeight - 1), 0.f);
//             }

//             // vecObjects[i] = obj;
//             vecObjects.push_back(obj);
//         }
//     }
// }

// void PostUnit::multiClassNMS(std::vector<Object>& nmsObjVec, std::vector<Object>& objVec, std::vector<float>& objScoreVec){

// }

// void PostUnit::qsortDescentInplace(std::vector<Object>& datas, std::vector<float>& scores){
//     if (datas.empty() || scores.empty())
//         return;
//     this->qsortDescentInplace(datas, scores, 0, static_cast<int>(scores.size() - 1));
// }

// void PostUnit::qsortDescentInplace(std::vector<Object>& datas, std::vector<float>& scores, int left, int right){
//     int   i = left;
//     int   j = right;
//     float p = scores[(left + right) / 2];

//     while (i <= j) {
//         while (scores[i] > p)
//             i++;

//         while (scores[j] < p)
//             j--;

//         if (i <= j) {
//             // swap
//             std::swap(datas[i], datas[j]);
//             std::swap(scores[i], scores[j]);

//             i++;
//             j--;
//         }
//     }

//     if (left < j)
//         this->qsortDescentInplace(datas, scores, left, j);

//     if (i < right)
//         this->qsortDescentInplace(datas, scores, i, right);
// }

// void PostUnit::nmsSortedBBoxes(const std::vector<Object>& bboxes, std::vector<size_t>& picked, float nmsThres){
//     picked.clear();

//     const size_t n = bboxes.size();

//     std::vector<float> areas(n);
//     for (size_t i = 0; i < n; i++) {
//         const Object &r = bboxes[i];

//         float width  = r.xmax - r.xmin;
//         float height = r.ymax - r.ymin;

//         areas[i] = width * height;
//     }

//     for (size_t i = 0; i < n; i++) {
//         const Object &a = bboxes[i];

//         int keep = 1;
//         for (int j = 0; j < (int)picked.size(); j++) {
//             const Object &b = bboxes[picked[j]];

//             // intersection over union
//             float inter_area = this->intersectionArea(a, b);
//             float union_area = areas[i] + areas[picked[j]] - inter_area;
//             //             float IoU = inter_area / union_area
//             if (inter_area / union_area > nmsThres)
//                 keep = 0;
//         }

//         if (keep)
//             picked.push_back(i);
//     }
// }

// float PostUnit::intersectionArea(const Object& a, const Object& b){
//     if (a.xmin > b.xmax || a.xmax < b.xmin || a.ymin > b.ymax || a.ymax < b.ymin) {
//         // no intersection
//         return 0.f;
//     }

//     float inter_width  = std::min(a.xmax, b.xmax) - std::max(a.xmin, b.xmin);
//     float inter_height = std::min(a.ymax, b.ymax) - std::max(a.ymin, b.ymin);

//     return inter_width * inter_height;
// }

int PostDMSMTFace::run(const Input& input, Output& output){

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

int PostDMSMTYolox::run(const Input& input, Output& output){
    std::vector<double> strides{8.0f, 16.0f, 32.0f, 64.0f};
    double threshold = 0.4;
    int classNum = 8;

    std::vector<Object> objVec;
    std::vector<float> objScoreVec;
    for(int i = 0; i < strides.size(); i++){
        int gridW = ceil(input.netInputSize[0] / strides[i]);
        int gridH = ceil(input.netInputSize[1] / strides[i]);

        for(int y = 0; y < gridH; y++){
            for(int x = 0; x < gridW; x++){
                int p = y * gridW + x;
                float objScore = input.data[i*3+1][p];
                if(objScore < threshold) continue; //todo
                for(int m = 0; m < classNum; m++){
                    float clsScore = input.data[i*3+2][p+m*gridW*gridH];
                    clsScore *= objScore;
                    if(clsScore < threshold) continue;

                    float xCenter = (input.data[i*3+0][p+0*gridW*gridH] + x) * strides[i];
                    float yCenter = (input.data[i*3+0][p+1*gridW*gridH] + y) * strides[i];
                    int w = std::exp(input.data[i*3+0][p+2*gridW*gridH]) * strides[i];
                    int h = std::exp(input.data[i*3+0][p+3*gridW*gridH]) * strides[i];
                    float xmin = xCenter - w * 0.5f;
                    float ymin = yCenter - h * 0.5f;

                    Object obj;
                    obj.xmin = xmin;
                    obj.ymin = ymin;
                    obj.xmax = xmin + w;
                    obj.ymax = ymin + h;
                    obj.label = m;
                    obj.score = clsScore;

                    objVec.push_back(obj);
                    objScoreVec.push_back(clsScore);
                }
                
            }
        }
    }

    // nms
    std::vector<Object> nmsObjVec;
    // this->nms(nmsObjVec, objVec, objScoreVec, false);

    return 0;
}