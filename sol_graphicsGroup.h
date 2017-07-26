#ifndef _SOL_GRAPHICSGROUP_DEFINED_
#define _SOL_GRAPHICSGROUP_DEFINED_
#include "sol_virtualGraphicsObject.h"
#include "sol_screenAnimation.h"
#include "sol_screenBitmap.h"
#include <vector>
using namespace std;

class sol_graphicsGroup : public sol_virtualGraphicsObject{
    public:
        vector <sol_screenAnimation> animations;
        vector <sol_screenBitmap*> bitmaps;
        long x, y;//NOT relative to layer but absolute; layers have no position
};

#endif
