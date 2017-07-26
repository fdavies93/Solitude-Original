#include "sol_templateStaticAnimation.h"
#include <allegro5/allegro.h>
using namespace std;

sol_templateStaticAnimation::sol_templateStaticAnimation(string myName, string myAnimation, double myWidth, double myHeight){
    name = myName;
    animationName = myAnimation;
    width = myWidth;
    height = myHeight;
}

string sol_templateStaticAnimation::getName(){
    return name;
}

string sol_templateStaticAnimation::getAnimationName(){
    return animationName;
}
