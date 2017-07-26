#ifndef _SOL_TEMPLATE_STATIC_ANIMATION_
#define _SOL_TEMPLATE_STATIC_ANIMATION_
#include <string>
using namespace std;

class sol_templateStaticAnimation{
    protected:
        string name, animationName;
        double width, height;
    public:
        sol_templateStaticAnimation(string, string, double, double);//my name, animation name, width, height
        string getAnimationName();
        string getName();
        double getWidth(){return width;};
        double getHeight(){return height;};
};

#endif
