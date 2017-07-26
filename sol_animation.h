#ifndef _SOL_ANIMATION_DEFINED_
#define _SOL_ANIMATION_DEFINED_
#include <string>
#include <vector>
#include "sol_frame.h"
using namespace std;

class sol_animation{
    private:
        string name;
        double animationTicks;
        int width, height;
        vector <sol_frame> frames;
    public:
        bool LoadFromCsv(string);//loads animation from CSV file; string filename
        sol_frame* getFrame(int);//frame number; returns frame
        int getNumberOfFrames();//returns number of frames
        int getWidth();
        int getHeight();
        string getName();
        sol_animation(string);
        sol_animation();
};
/*CSV FORMAT: first line is name of animation, filename of bitmap. all subsequent lines are one frame of the animation.
        transparency defined by top-left pixel of spritesheet.
        This allows for multiple animations to use the same spritesheet. Lines are structured as follows:
        x, y, width, height, start, end WHERE x, y start @ top-left corner, start/end are ticks*/

#endif
