#ifndef _SOL_LOGIC_STORAGE_DEFINED_
#define _SOL_LOGIC_STORAGE_DEFINED_
#include <string>
#include <vector>
#include "sol_templateStaticAnimation.h"
#include "sol_templateStaticBitmap.h"
using namespace std;

class sol_logicStorage{
    private:
        vector <sol_templateStaticAnimation> staticAnimations;
        vector <sol_templateStaticBitmap> staticBitmaps;
    public:
        int addStaticAnimation(string, string, double, double);//name, animation, width, height; returns index
        int addStaticBitmap(string, string, double, double);//name, animation, width, height; returns index
        sol_templateStaticAnimation* getStaticAnimation(string);//name; returns pointer to template
        sol_templateStaticBitmap* getStaticBitmap(string);
};

#endif
