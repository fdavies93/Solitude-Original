#ifndef _SOL_SPACEFILLINGVECTOR_DEFINED_
#define _SOL_SPACEFILLINGVECTOR_DEFINED_
#include <vector>
#include <queue>
using namespace std;

template <typename myType> class spaceFillingVector{//must delete things in code if using it to store pointers
    private:
        vector <myType> dataObject;
        vector <bool> spaceVector;
        queue <int> spacesFree;
        int elements;
    public:
        int addObject(myType);//object to add; returns position
        void removeObject(int);//id of object to remove
        void destroyLast();
        myType getObject(int);//id of object; object
        int nextAvailablePosition();//returns next available position
        bool spaceFull(int);//index; returns if it's got an object in it
        int size();//returns size of dataObject vector
        spaceFillingVector();
};
#include "sol_spaceFillingVector.cpp"
#endif
