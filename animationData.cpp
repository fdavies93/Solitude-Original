#include "animationData.h"
using namespace std;

animationData::animationData(string myFileName){
    fileName = myFileName;
}

animationData::animationData(){
}

string animationData::getFileName(){
    return fileName;
}

bool animationData::addFrame(frameData myFrame){
    if(myFrame.x >= 0 && myFrame.y >= 0 && myFrame.height > 0 && myFrame.width > 0){
        frames.push_back(myFrame);
        return true;
    }
    return false;
}

int animationData::getNumberOfFrames(){
    return frames.size();
}

frameData animationData::getFrameData(int frameIndex){
    return frames[frameIndex];
}

bool animationData::addFrame(int x, int y, int width, int height){
    frameData newFrame;
    newFrame.x = x;
    newFrame.y = y;
    newFrame.width = width;
    newFrame.height = height;
    return addFrame(newFrame);
}
