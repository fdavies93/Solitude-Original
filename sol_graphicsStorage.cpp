#include "sol_graphicsStorage.h"
#include "genericFunctions.h"
#include <allegro5/allegro.h>
#include <string>
#include <iostream>
#include <stdexcept>
#include <allegro5/allegro_image.h>
#include "sol_graphicsConstants.h"
using namespace std;

bitmapData* sol_graphicsStorage::getBitmapData(string name){
    return bitmapFiles.get(name);
}

animationData* sol_graphicsStorage::getAnimationData(string name){
    return animationFiles.get(name);
}

bool sol_graphicsStorage::loadAnimationDataFromCSV(string fileName){
    vector <string> fileVector = LoadCsvToVector(fileName);
    string curName;
    bool doNotAdd = false;
    if(fileVector.size() >= 6 && (fileVector.size()-2)%4 == 0){
        curName = fileVector[0];
        animationData newAnimation(fileVector[1]);
        frameData curFrame;
        for(unsigned int fileCounter=2; fileCounter < fileVector.size(); fileCounter++){
            switch((fileCounter-2) % 4){//x, y, width, height
                case 0:
                    doNotAdd = false;
                    try{curFrame.x = atoi(fileVector[fileCounter].c_str());}
                    catch(const invalid_argument& ia){doNotAdd = true;}
                break;
                case 1:
                    try{curFrame.y = atoi(fileVector[fileCounter].c_str());}
                    catch(const invalid_argument& ia){doNotAdd = true;}
                break;
                case 2:
                    try{curFrame.width = atoi(fileVector[fileCounter].c_str());}
                    catch(const invalid_argument& ia){doNotAdd = true;}
                break;
                case 3:
                    try{curFrame.height = atoi(fileVector[fileCounter].c_str());}
                    catch(const invalid_argument& ia){doNotAdd = true;}
                    if(!doNotAdd){newAnimation.addFrame(curFrame);}
                break;
            }
        }
        animationFiles.insert(curName,newAnimation);
        return true;
    }
    else{
        cerr << fileName << " has wrong number of entries in sol_graphicsStorage::loadAnimationData (did you forget a comma?)\n";
        return false;
    }
}

bool sol_graphicsStorage::loadAllAnimationDataFromCSV(string fileName){
    vector <string> fileVector = LoadCsvToVector(fileName);
    for(unsigned int entryCounter = 0; entryCounter < fileVector.size(); entryCounter++){
        loadAnimationDataFromCSV(fileVector[entryCounter]);
    }
}

bool sol_graphicsStorage::loadBitmapDataFromCSV(string fileName){
    bitmapData newBitmap;
    string curName;
    vector <string> fileVector = LoadCsvToVector(fileName);
    if(fileVector.size() % 6 == 0){
        for(int curBitmapIndex = 0; curBitmapIndex < fileVector.size(); curBitmapIndex++){
            switch(curBitmapIndex % 6){
                case 0:
                    newBitmap.fileName = fileVector[curBitmapIndex];
                break;
                case 1:
                    curName = fileVector[curBitmapIndex];
                break;
                case 2:
                    newBitmap.x = atoi(fileVector[curBitmapIndex].c_str());
                break;
                case 3:
                    newBitmap.y = atoi(fileVector[curBitmapIndex].c_str());
                break;
                case 4:
                    newBitmap.width = atoi(fileVector[curBitmapIndex].c_str());
                break;
                case 5:
                    newBitmap.height = atoi(fileVector[curBitmapIndex].c_str());
                    bitmapFiles.insert(curName,newBitmap);
                break;
            }
        }
    }
    else{
        cerr << fileName << " has wrong number of entries in sol_graphicsStorage::loadBitmapData (did you forget a comma?)\n";
        return false;
    }
}

sol_graphicsStorage::sol_graphicsStorage(string animationFilename, string bitmapFilename){
    loadAllAnimationDataFromCSV(animationFilename);
    loadBitmapDataFromCSV(bitmapFilename);
}
