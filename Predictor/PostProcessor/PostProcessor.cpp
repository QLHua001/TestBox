#include "PostProcessor.h"

PostProcessor::PostProcessor(Config* config){
    this->config = Config(*config);

    switch(this->config.postType){
    case POST_DMS_MTFACE:{
        this->postUnit = new PostDmsMTFace();
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