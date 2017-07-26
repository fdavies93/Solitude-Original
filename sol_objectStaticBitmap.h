#ifndef _SOL_OBJECT_STATIC_BITMAP_INCLUDED_
#define _SOL_OBJECT_STATIC_BITMAP_INCLUDED_
#include "sol_templateStaticBitmap.h"
#include "sol_gameObject.h"
using namespace std;

class sol_objectStaticBitmap: public sol_gameObject{
    protected:
        sol_templateStaticBitmap* type;//links object with template: very important
    public:
        sol_objectStaticBitmap(sol_templateStaticBitmap*,int64_t);//template pointer
        int getSuperType();
        sol_templateStaticBitmap* getType(){return type;};
        double getWidth(){return type->getWidth();};
        double getHeight(){return type->getHeight();};
};

#endif
