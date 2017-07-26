#ifndef _TEMPLATE_BST_NODE_DEFINED_
#define _TEMPLATE_BST_NODE_DEFINED_
#include <string>
#include <vector>
#include <allegro5/allegro.h>
using namespace std;

template <typename myType> class templateBstNode{
    public:
        string key;
        myType data;
        templateBstNode<myType>* left;
        templateBstNode<myType>* right;
        templateBstNode<myType>* parent;
        ~templateBstNode();
        myType* getData();
        vector<myType*> returnVector();
};

template <typename myType> class templateBstNode<myType *>{
    public:
        string key;
        myType* data;
        templateBstNode<myType*>* left;
        templateBstNode<myType*>* right;
        templateBstNode<myType*>* parent;
        ~templateBstNode();
        myType* getData();
        vector<myType*> returnVector();
};

template <> class templateBstNode<ALLEGRO_BITMAP*>{//more an expansion on the generic model than anything else
    public:
        string key;
        ALLEGRO_BITMAP* data;
        templateBstNode<ALLEGRO_BITMAP*>* left;
        templateBstNode<ALLEGRO_BITMAP*>* right;
        templateBstNode<ALLEGRO_BITMAP*>* parent;
        ~templateBstNode();
        ALLEGRO_BITMAP* getData();
        vector<ALLEGRO_BITMAP*> returnVector();
};

template <typename myType> templateBstNode<myType>::~templateBstNode(){

}

template <typename myType> myType* templateBstNode<myType>::getData(){
    return &data;
}

template <typename myType> vector<myType*> templateBstNode<myType>::returnVector(){
    vector<myType*> leftArray;
    vector<myType*> rightArray;
    vector<myType*> returnArray;
    if(left){
        leftArray = left->returnVector();
        for(unsigned int i = 0; i < leftArray.size(); i++){
            returnArray.push_back(leftArray[i]);
        }
    }
    returnArray.push_back(&data);
    if(right){
        rightArray = right->returnVector();
        for(unsigned int i = 0; i < rightArray.size(); i++){
            returnArray.push_back(rightArray[i]);
        }
    }
    return returnArray;
}

template <typename myType> templateBstNode<myType *>::~templateBstNode(){
    delete data;
}

template <typename myType> myType* templateBstNode<myType *>::getData(){
    return data;
}

template <typename myType> vector<myType*> templateBstNode<myType*>::returnVector(){
    vector<myType*> leftArray;
    vector<myType*> rightArray;
    vector<myType*> returnArray;
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
#endif
