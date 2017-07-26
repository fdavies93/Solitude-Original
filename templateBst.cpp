#ifndef _DEFINE_TEMPLATE_BST_INLINE_
#define _DEFINE_TEMPLATE_BST_INLINE_
#include "templateBst.h"
#include <iostream>
using namespace std;

template <typename myType> myType* templateBst<myType>::insert(string keyName, myType myData){
    templateBstNode<myType>* curNode = root;
    bool end = false;
    while(end != true){
        if(curNode == NULL){
            //cout << "blah\n";
            curNode = new templateBstNode<myType>;
            curNode->key = keyName;
            curNode->data = myData;
            curNode->left = NULL;
            curNode->right = NULL;
            curNode->parent = NULL;
            root = curNode;
            //cout << root->key << "\n";
            //cout << curNode << "\n";
            end = true;
            return curNode->getData();
        }
        else{
            if(keyName.compare(curNode->key) == 0){
                //cout << keyName << " already exists in templateBst::insert\n";
                return NULL;
            }
            else if(keyName.compare(curNode->key) < 0){
                if(curNode->left == NULL){
                    curNode->left = new templateBstNode<myType>;
                    curNode->left->key = keyName;
                    curNode->left->data = myData;
                    curNode->left->left = NULL;
                    curNode->left->right = NULL;
                    curNode->left->parent = curNode;
                    end = true;
                    return curNode->left->getData();
                }
                curNode = curNode->left;
            }
            else if(keyName.compare(curNode->key) > 0){
                if(curNode->right == NULL){
                    curNode->right = new templateBstNode<myType>;
                    curNode->right->key = keyName;
                    curNode->right->data = myData;
                    curNode->right->parent = curNode;
                    curNode->right->left = NULL;
                    curNode->right->right = NULL;
                    end = true;
                    return curNode->right->getData();
                }
                curNode = curNode->right;
            }
        }
    }
}

template <typename myType> bool templateBst<myType>::remove(string keyName){
    templateBstNode<myType>* curNode = root;
    templateBstNode<myType>* curNode2;
    bool end = false;
    bool deleteFinished = false;
    //bool nameCheckBypass = false;
    while(end != true){
        if(curNode == NULL){
            cout << "Object with key " << keyName << " not found in templateBst::remove.\n";
            return false;
        }
        else{
            if(keyName == curNode->key){
                if(curNode->left == NULL && curNode->right == NULL){
                    if(curNode->parent != NULL){
                        if(curNode->parent->left == curNode){
                            curNode->parent->left = NULL;
                        }
                        else{
                            curNode->parent->right = NULL;
                        }
                    }
                    delete curNode;
                    return true;
                }
                else if(curNode->right == NULL && curNode->left != NULL){
                    curNode->left->parent = curNode->parent;
                    if(curNode->parent != NULL){
                        if(curNode->parent->left == curNode){
                            curNode->parent->left = curNode->left;
                        }
                        else{
                            curNode->parent->right = curNode->left;
                        }
                    }
                    delete curNode;
                    return true;
                }
                else if(curNode->left == NULL && curNode->right != NULL){
                    curNode->right->parent = curNode->parent;
                    if(curNode->parent != NULL){
                        if(curNode->parent->left == curNode){
                            curNode->parent->left = curNode->right;
                        }
                        else{
                            curNode->parent->right = curNode->right;
                        }
                    }
                    delete curNode;
                    return true;
                }
                //EVERYTHING FINE UP TO HERE: JUST NEED TO IMPLEMENT DELETE FOR NODES WITH 2 CHILDREN
                //DELETION INCORRECT: DOES NOT MAKE IN-ORDER PREDECESSOR REPLACE IT
                else if(curNode->left != NULL && curNode->right != NULL){
                    //nameCheckBypass = true;
                    //curNode->data = curNode->left->data;
                    //curNode->key = curNode->left->key;
                    //curNode = curNode->left;
                    curNode2 = curNode->left;
                    while(!deleteFinished){
                        if(curNode2->right != NULL){
                            curNode2 = curNode2->right;
                        }
                        else{
                            deleteFinished = true;
                            if(curNode2->left == NULL){
                                curNode->data = curNode2->data;
                                curNode->key = curNode2->key;
                                curNode2->parent->right = NULL;
                            }
                            else{
                                curNode->data = curNode2->data;
                                curNode->key = curNode2->key;
                                curNode2->parent->right = curNode2->left;
                                curNode2->left->parent = curNode2->parent;
                            }
                            delete curNode2;
                        }
                    }
                    return true;
                }
            }
            else if(keyName < curNode->key){
                curNode = curNode->left;
            }
            else if(keyName > curNode->key){
                curNode = curNode->right;
            }
        }
    }
}

template <typename myType> myType* templateBst<myType>::get(string keyName){
    templateBstNode<myType>* curNode = root;
    bool end = false;
    while(end != true){
        if(curNode == NULL){
            //cerr << "Object with key " << keyName << " not found in templateBst::get.\n";
            return NULL;
        }
        else{
            //cout << curNode->key << "\n";
            if(keyName == curNode->key){
                return curNode->getData();
            }
            else if(keyName < curNode->key){
                curNode = curNode->left;
                //cout << "<-\n";
            }
            else if(keyName > curNode->key){
                curNode = curNode->right;
                //cout << "->\n";
            }
        }
    }
}

template <typename myType> void templateBst<myType>::clear(){
    killNode(root);
    root = NULL;
}

template <typename myType> void templateBst<myType>::killNode(templateBstNode<myType>* theNode){
    if(theNode != NULL){
        killNode(theNode->left);
        killNode(theNode->right);
        delete theNode;
    }
    return;
}

template <typename myType> vector<myType*> templateBst<myType>::returnAsVector(){
    vector<myType*> returnVector;
    if(root != NULL){
        returnVector = root->returnVector();
    }
    return returnVector;
    //either: a recursive algorithm or a
}

template <typename myType> templateBst<myType>::templateBst(){
    root = NULL;
}

//POINTER TEMPLATE BELOW

template <typename myType> myType* templateBst<myType *>::insert(string keyName, myType* myData){
    templateBstNode<myType*>* curNode = root;
    bool end = false;
    while(end != true){
        if(curNode == NULL){
            //cout << "blah\n";
            curNode = new templateBstNode<myType*>;
            curNode->key = keyName;
            curNode->data = myData;
            curNode->left = NULL;
            curNode->right = NULL;
            curNode->parent = NULL;
            root = curNode;
            //cout << root->key << "\n";
            //cout << curNode << "\n";
            end = true;
            return curNode->getData();
        }
        else{
            if(keyName.compare(curNode->key) == 0){
                //cout << keyName << " already exists in templateBst::insert\n";
                return NULL;
            }
            else if(keyName.compare(curNode->key) < 0){
                if(curNode->left == NULL){
                    curNode->left = new templateBstNode<myType*>;
                    curNode->left->key = keyName;
                    curNode->left->data = myData;
                    curNode->left->left = NULL;
                    curNode->left->right = NULL;
                    curNode->left->parent = curNode;
                    end = true;
                    return curNode->left->getData();
                }
                curNode = curNode->left;
            }
            else if(keyName.compare(curNode->key) > 0){
                if(curNode->right == NULL){
                    curNode->right = new templateBstNode<myType*>;
                    curNode->right->key = keyName;
                    curNode->right->data = myData;
                    curNode->right->parent = curNode;
                    curNode->right->left = NULL;
                    curNode->right->right = NULL;
                    end = true;
                    return curNode->right->getData();
                }
                curNode = curNode->right;
            }
        }
    }
}

template <typename myType> bool templateBst<myType *>::remove(string keyName){
    templateBstNode<myType>* curNode = root;
    templateBstNode<myType>* curNode2;
    bool end = false;
    bool deleteFinished = false;
    //bool nameCheckBypass = false;
    while(end != true){
        if(curNode == NULL){
            cout << "Object with key " << keyName << " not found in templateBst::remove.\n";
            return false;
        }
        else{
            if(keyName == curNode->key){
                if(curNode->left == NULL && curNode->right == NULL){
                    if(curNode->parent != NULL){
                        if(curNode->parent->left == curNode){
                            curNode->parent->left = NULL;
                        }
                        else{
                            curNode->parent->right = NULL;
                        }
                    }
                    delete curNode;
                    return true;
                }
                else if(curNode->right == NULL && curNode->left != NULL){
                    curNode->left->parent = curNode->parent;
                    if(curNode->parent != NULL){
                        if(curNode->parent->left == curNode){
                            curNode->parent->left = curNode->left;
                        }
                        else{
                            curNode->parent->right = curNode->left;
                        }
                    }
                    delete curNode;
                    return true;
                }
                else if(curNode->left == NULL && curNode->right != NULL){
                    curNode->right->parent = curNode->parent;
                    if(curNode->parent != NULL){
                        if(curNode->parent->left == curNode){
                            curNode->parent->left = curNode->right;
                        }
                        else{
                            curNode->parent->right = curNode->right;
                        }
                    }
                    delete curNode;
                    return true;
                }
                //EVERYTHING FINE UP TO HERE: JUST NEED TO IMPLEMENT DELETE FOR NODES WITH 2 CHILDREN
                //DELETION INCORRECT: DOES NOT MAKE IN-ORDER PREDECESSOR REPLACE IT
                else if(curNode->left != NULL && curNode->right != NULL){
                    //nameCheckBypass = true;
                    //curNode->data = curNode->left->data;
                    //curNode->key = curNode->left->key;
                    //curNode = curNode->left;
                    curNode2 = curNode->left;
                    while(!deleteFinished){
                        if(curNode2->right != NULL){
                            curNode2 = curNode2->right;
                        }
                        else{
                            deleteFinished = true;
                            if(curNode2->left == NULL){
                                curNode->data = curNode2->data;
                                curNode->key = curNode2->key;
                                curNode2->parent->right = NULL;
                            }
                            else{
                                curNode->data = curNode2->data;
                                curNode->key = curNode2->key;
                                curNode2->parent->right = curNode2->left;
                                curNode2->left->parent = curNode2->parent;
                            }
                            delete curNode2;
                        }
                    }
                    return true;
                }
            }
            else if(keyName < curNode->key){
                curNode = curNode->left;
            }
            else if(keyName > curNode->key){
                curNode = curNode->right;
            }
        }
    }
}

template <typename myType> myType* templateBst<myType *>::get(string keyName){
    templateBstNode<myType*>* curNode = root;
    bool end = false;
    while(end != true){
        if(curNode == NULL){
            //cerr << "Object with key " << keyName << " not found in templateBst::get.\n";
            return NULL;
        }
        else{
            //cout << curNode->key << "\n";
            if(keyName == curNode->key){
                return curNode->getData();
            }
            else if(keyName < curNode->key){
                curNode = curNode->left;
                //cout << "<-\n";
            }
            else if(keyName > curNode->key){
                curNode = curNode->right;
                //cout << "->\n";
            }
        }
    }
}

template <typename myType> void templateBst<myType *>::clear(){
    killNode(root);
    root = NULL;
}

template <typename myType> void templateBst<myType *>::killNode(templateBstNode<myType*>* theNode){
    if(theNode != NULL){
        killNode(theNode->left);
        killNode(theNode->right);
        delete theNode;
    }
    return;
}

template <typename myType> vector<myType*> templateBst<myType *>::returnAsVector(){
    vector<myType*> returnVector;
    if(root != NULL){
        returnVector = root->returnVector();
    }
    return returnVector;
}

template <typename myType> templateBst<myType *>::templateBst(){
    root = NULL;
}



#endif
