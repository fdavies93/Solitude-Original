#ifndef _SOL_LOGIC_TO_GRAPHICS_CONVERTER_
#define _SOL_LOGIC_TO_GRAPHICS_CONVERTER_
#include "sol_graphicsControl.h"
#include "sol_scene.h"
using namespace std;

class sol_logicToGraphicsConverter{
    private:
        unsigned int pixelsPerMetre;
        ALLEGRO_TIMER* timer;
        sol_graphicsControl* graphicsPointer;
    public:
        sol_logicToGraphicsConverter(sol_graphicsControl*,unsigned int, ALLEGRO_TIMER*);//graphics control, pixels per metre, timer
        bool buildGraphics(sol_scene*);
};


#endif
