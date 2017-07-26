#ifndef _SOL_GRAPHICSLAYER_DEFINED_
#define _SOL_GRAPHICSLAYER_DEFINED_
#include "sol_screenAnimation.h"
#include "sol_screenBitmap.h"
#include <vector>
#include <queue>
#include <string>
using namespace std;



class sol_graphicsLayer : public sol_virtualGraphicsObject{
    private:
        int depth;//in layer depth: 0 is the play layer, all negative depths are background, all positive depths are foreground
        string name;
        vector <sol_screenAnimation*> animations;
        vector <sol_screenBitmap*> bitmaps;
        //double scrollSpeed;
        //not in use YET: but will have use in determining how much layers 'move' relative to 0 layer; 0 layer always scrolls at 1.
        //in a side-scroller like solitude foreground layers move faster than 1.0 while background move slower.
        //view is a gameplay object, however, not a graphics object
    public:
        //vector <sol_graphicsGroup> groups;
        sol_graphicsLayer();
        sol_graphicsLayer(string,int);//name, depth
        //ALL THIS MUST GO ^
        int addObject(sol_virtualGraphicsObject*);//object; returns id of given object
        void addAnimation(sol_screenAnimation*);
        void addBitmap(sol_screenBitmap*);
        int getDepth(){return depth;}
        string getName(){return name;}
        //bool removeBitmap(int);//id; removes object with given id
        //bool removeAnimation(int);//id; removes object with given id
        void clearLayer();//removes all objects from layer
        bool print();
};

#endif
