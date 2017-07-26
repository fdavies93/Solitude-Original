#ifndef _TEMPLATE_BST_DEFINED_
#define _TEMPLATE_BST_DEFINED_
#include <string>
#include <vector>
#include <allegro5/allegro.h>
#include "templateBstNode.h"
using namespace std;

template <typename myType> class templateBst{
    private:
        templateBstNode<myType>* root;
        void killNode(templateBstNode<myType>*);
    public:
        myType* insert(string, myType);//key, data; inserts object with key string, returns pointer to object inserted or NULL on failure
        bool remove(string);//key; removes object with key string; returns true on success or false on failure
        myType* get(string);//key; returns data object with key string or NULL on failure
        void clear();//removes all things from tree
        vector<myType *> returnAsVector();
        templateBst();
};

template <typename myType> class templateBst <myType *>{
    private:
        templateBstNode<myType*>* root;
        void killNode(templateBstNode<myType*>*);
    public:
        myType* insert(string, myType*);//key, data; inserts object with key string, returns pointer to object inserted or NULL on failure
        bool remove(string);//key; removes object with key string; returns true on success or false on failure
        myType* get(string);//key; returns data object with key string or NULL on failure
        void clear();//removes all things from tree
        vector<myType *> returnAsVector();
        templateBst();
};

#include "templateBst.cpp"
#endif
