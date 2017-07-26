#ifndef _SOL_VIRTUALGRAPHICSOBJECT_DEFINED_
#define _SOL_VIRTUALGRAPHICSOBJECT_DEFINED_
#include <iostream>
using namespace std;

class sol_virtualGraphicsObject{
    private:
        int* position;
        int64_t id;
    public:
        bool setPosition(int,int);
        int* getPosition();
        bool setId(int64_t);
        int64_t getId();
        virtual int type();
        virtual bool print();
};

#endif
