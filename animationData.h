#ifndef _ANIMATIONDATA_DEFINED_
#define _ANIMATIONDATA_DEFINED_
#include <string>
#include <vector>
#include "frameData.h"
using namespace std;

class animationData{
        string fileName;
        vector<frameData> frames;
    public:
        animationData(string);//filename
        animationData();
        bool addFrame(frameData);//frame data
        bool addFrame(int, int, int, int);//x, y, width, height
        frameData getFrameData(int);
        int getNumberOfFrames();
        string getFileName();
};

#endif
