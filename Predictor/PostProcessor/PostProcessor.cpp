#include "PostProcessor.h"

PostProcessor::PostProcessor(PostUnit::Config* config){
    // this->config = Config(*config);

    switch(config->postType){
    case POST_DMS_MTFACE:{
        this->postUnit = new PostDMSMTFace();
        break;
    }
    case POST_DMS_MTYOLOX:{
        this->postUnit = new PostDMSMTYolox();
        break;
    }
    }

}

PostProcessor::~PostProcessor(){
    if(this->postUnit){
        delete this->postUnit;
    }
    this->postUnit = nullptr;
}

int PostProcessor::run(const PostUnit::Input& input, PostUnit::Output& output){

    this->postUnit->run(input, output);
    
    return 0;
}