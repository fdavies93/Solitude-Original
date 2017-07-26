#ifndef _SOL_SCREENANIMATION_DEFINED_
#define _SOL_SCREENANIMATION_DEFINED_
#include "sol_virtualGraphicsObject.h"
#include "sol_graphicsStorage.h"
#include "animation.h"
using namespace std;

class sol_screenAnimation : public sol_virtualGraphicsObject{
    private:
        animation* storedAnimation;//multiple screenAnimations can point the same object (i.e. animation)
    public:
        animation* GetAnimation();
        int64_t id;
        int x, y;
        int curFrame;
        int type();
        int nextFrame();
        bool print();
        sol_screenAnimation(animation*, int, int, int);//pointer to animation, x, y, frame
        ~sol_screenAnimation();
};

#endif
