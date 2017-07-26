#include "templateBstNode.h"
using namespace std;

templateBstNode<ALLEGRO_BITMAP*>::~templateBstNode(){
    al_destroy_bitmap(data);
}

ALLEGRO_BITMAP* templateBstNode<ALLEGRO_BITMAP *>::getData(){
    return data;
}

vector<ALLEGRO_BITMAP*> templateBstNode<ALLEGRO_BITMAP *>::returnVector(){
    vector<ALLEGRO_BITMAP*> leftArray;
    vector<ALLEGRO_BITMAP*> rightArray;
    vector<ALLEGRO_BITMAP*> returnArray;
    if(left){
        leftArray = left->returnVector();
        for(unsigned int i = 0; i < leftArray.size(); i++){
            returnArray.push_back(leftArray[i]);
        }
    }
    returnArray.push_back(data);
    if(right){
        rightArray = right->returnVector();
        for(unsigned int i = 0; i < rightArray.size(); i++){
            returnArray.push_back(rightArray[i]);
        }
    }
    return returnArray;
}

/*
*/
