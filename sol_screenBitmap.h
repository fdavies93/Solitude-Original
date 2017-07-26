#ifndef _SOL_SCREENBITMAP_DEFINED
#define _SOL_SCREENBITMAP_DEFINED
#include "sol_graphicsStorage.h"
#include "sol_graphicsConstants.h"
#include "sol_virtualGraphicsObject.h"
using namespace std;

class sol_screenBitmap : public sol_virtualGraphicsObject{
    private:
        sol_bitmap* bitmap;
    public:
        int x, y;
        sol_bitmap* getBitmap();
        sol_screenBitmap();
        sol_screenBitmap(sol_bitmap*, int, int);//pointer to bitmap, x, y
        ~sol_screenBitmap();
        int type();
        bool print();
};

#endif
