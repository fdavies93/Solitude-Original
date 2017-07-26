#ifndef _SOL_SPACEFILLINGVECTOR_INLINE_DEFINED_
#define _SOL_SPACEFILLINGVECTOR_INLINE_DEFINED_
#include "sol_spaceFillingVector.h"
#include <iostream>
using namespace std;

template <typename myType> spaceFillingVector<myType> :: spaceFillingVector(){
    elements = 0;
}

template <typename myType> int spaceFillingVector<myType> :: addObject(myType theObject){
    if(spacesFree.size() > 0){
        int spaceIndex = spacesFree.front();
        dataObject[spaceIndex] = theObject;
        spaceVector[spaceIndex] = true;
        spacesFree.pop();
        return spaceIndex;
    }
    else{
        dataObject.push_back(theObject);
        spaceVector.push_back(true);
        return dataObject.size()-1;
    }
}

template <typename myType> void spaceFillingVector<myType> :: destroyLast(){
    dataObject.pop_back();
    spaceVector.pop_back();
}

template <typename myType> void spaceFillingVector<myType> :: removeObject(int id){
    if(id < dataObject.size() && id > -1){
        if(spaceVector[id] == true){
                //delete dataObject[id];//causes bad juju (crash) with non-pointer types
            if(id == dataObject.size()-1){
                dataObject.pop_back();
                spaceVector.pop_back();
            }
            else{
                spaceVector[id] = false;
            }
        }
        else{
            cout << "Object already removed in spaceFillingVector::removeObject.\n";
        }
    }
    else{
        cout << "Out-of-bounds object id in spaceFillingVector::removeObject.\n";
    }
}

template <typename myType> myType spaceFillingVector<myType> :: getObject(int id){
    if(id > -1 && id < dataObject.size()){
        return dataObject[id];
    }
    else{
        cout << "Out-of-bounds object id in spaceFillingVector::getObject.\n";
        return NULL;
    }
}

template <typename myType> bool spaceFillingVector<myType> :: spaceFull(int index){
    if(index > -1 && index < dataObject.size()){
        return spaceVector[index];
    }
    else{
        cout << "Out-of-bounds object id in spaceFillingVector::spaceEmpty.\n";
        return false;
    }
}

template <typename myType> int spaceFillingVector<myType> :: size(){
    return dataObject.size();
}

#endif
