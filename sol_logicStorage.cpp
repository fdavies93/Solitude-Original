#include "sol_logicStorage.h"
#include <string>
#include <iostream>
using namespace std;

int sol_logicStorage::addStaticAnimation(string templateName, string animationName, double width, double height){
    sol_templateStaticAnimation newTemplate(templateName,animationName,width,height);
    staticAnimations.push_back(newTemplate);
    return staticAnimations.size()-1;
}

int sol_logicStorage::addStaticBitmap(string templateName, string bitmapName, double width, double height){
    sol_templateStaticBitmap newTemplate(templateName,bitmapName,width, height);
    staticBitmaps.push_back(newTemplate);
    return staticBitmaps.size()-1;
}

sol_templateStaticAnimation* sol_logicStorage::getStaticAnimation(string templateName){
    for(int i = 0; i < staticAnimations.size(); i++){
        if(staticAnimations[i].getName() == templateName){
            return &staticAnimations[i];
        }
    }
    cout << "Failed to find template " << templateName << "in sol_logicStorage::getStaticAnimation\n";
    return NULL;
}

sol_templateStaticBitmap* sol_logicStorage::getStaticBitmap(string templateName){
    for(int i = 0; i < staticBitmaps.size(); i++){
        if(staticBitmaps[i].getName() == templateName){
            return &staticBitmaps[i];
        }
    }
    cout << "Failed to find template " << templateName << "in sol_logicStorage::getStaticBitmap\n";
    return NULL;
}
