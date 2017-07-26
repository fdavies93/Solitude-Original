#ifndef _SOL_TEMPLATE_STATIC_BITMAP_INCLUDED_
#define _SOL_TEMPLATE_STATIC_BITMAP_INCLUDED_
#include <string>
using namespace std;

class sol_templateStaticBitmap{
    protected:
        string name, bitmapName;
        double width, height;
    public:
        sol_templateStaticBitmap(string, string, double, double);//my name, bitmap name, width, height
        string getBitmapName();
        string getName();
        double getWidth(){return width;};
        double getHeight(){return height;};
};

#endif

