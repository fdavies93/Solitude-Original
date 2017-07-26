#ifndef _SOL_OBJECT_STATIC_ANIMATION_
#define _SOL_OBJECT_STATIC_ANIMATION_
#include <string>
#include "sol_gameObject.h"
#include "sol_templateStaticAnimation.h"
using namespace std;

class sol_objectStaticAnimation : public sol_gameObject{
    protected:
        sol_templateStaticAnimation* type;//links object with template: very important
        //string layer;
    public:
        sol_objectStaticAnimation(sol_templateStaticAnimation*,int64_t);//template pointer, timer
        int getSuperType();
        sol_templateStaticAnimation* getType(){return type;};
        double getWidth(){return type->getWidth();};
        double getHeight(){return type->getHeight();};
};

#endif
