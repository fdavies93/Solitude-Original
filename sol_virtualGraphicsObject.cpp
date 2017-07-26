#include "sol_virtualGraphicsObject.h"
using namespace std;

int sol_virtualGraphicsObject::type(){
    return -1;
}

bool sol_virtualGraphicsObject::setId(int64_t newId){
    id = newId;
    return true;
}

int64_t sol_virtualGraphicsObject::getId(){
    return id;
}

bool sol_virtualGraphicsObject::print(){
    return false;
}
