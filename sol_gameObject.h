#ifndef _SOL_GAME_OBJECT_DEFINED
#define _SOL_GAME_OBJECT_DEFINED
#include <allegro5/allegro.h>
using namespace std;

class sol_gameObject{//virtual
    protected:
        int64_t tickCreated;
    public:
        double x, y;
        unsigned int id;
        virtual int getSuperType();
        virtual void setId(unsigned int);//newId
        virtual double getHeight(){return -1;};
        virtual double getWidth(){return -1;};
        int64_t getTickCreated(){return tickCreated;};
        sol_gameObject();
};

#endif
