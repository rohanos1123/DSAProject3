//
// Created by Rohan Rao on 11/11/22.
//

#ifndef ORDEREDMAPIMPLEMENTATION_RBTREE_H
#define ORDEREDMAPIMPLEMENTATION_RBTREE_H

#include "TreeNode.h"
#include <queue>

template <typename T>
class RBTree {
private:
    TreeNode<T> *root;
    TreeNode<T>* leftRotate(TreeNode<T> *subRoot);
    TreeNode<T>* rightRotate(TreeNode<T> *subRoot);
    int size;
    TreeNode<T>* insertHelper(TreeNode<T> *subRoot, TreeNode<T> *n_node);

    //list of states
    bool ll = false;
    bool rr = false;
    bool lr = false;
    bool rl = false;


public:
    RBTree();
    void insert(TreeNode<T> *n_node);
};

template <typename T>
RBTree<T>::RBTree(){
    this->root = nullptr;
    this->size = 0;
}

template <typename T>
TreeNode<T>* RBTree<T>::leftRotate(TreeNode<T> *node){
    TreeNode<T> *rc = node->right;
    TreeNode<T> *rlc = rc->left;
    rc->left = node;
    node->right = rlc;
    node->parent = rc;
    if(rlc != nullptr){
        rlc->parent = node;
    }
    return rc;
}

template <typename T>
TreeNode<T>* RBTree<T>::rightRotate(TreeNode<T> *node){
    TreeNode<T> *lc = node->left;
    TreeNode<T> *lrc = lc->right;
    lc->right = node;
    node->left = lrc;
    node->parent = lc;
    if(lrc != nullptr){
        lrc->parent = node;
    }
    return lc;
}

template <typename T>
TreeNode<T>* RBTree<T>::insertHelper(TreeNode<T> *subRoot, TreeNode<T> *n_node){
    //If a red parent has a red child
    bool errorFlag = false;

    if(subRoot == nullptr) {
        size++;
        this->root = n_node;
        n_node->parent == nullptr;
        return n_node;
    }
    else if(subRoot->getData() > n_node->getData()){
       subRoot->left =  insertHelper(subRoot->left, n_node);
       //Assign Parent after recursive calls are done
       subRoot->left->parent = subRoot;
       if(subRoot != this->root){
           if(subRoot->colorState && subRoot->left->colorState){
               errorFlag = true;
           }
       }
    }
    else if (subRoot->getData() < n_node->getData()){
        subRoot->right =  insertHelper(subRoot->right, n_node);
        //Assign parent of n_node after recursive calls are done
        subRoot->right->parent = subRoot;
        if(subRoot != this->root){
            if(subRoot->colorState && subRoot->right->colorState){
                errorFlag = true;
            }
        }
    }

    //Perform Necessary rotations:
    if(this->ll == true){
        subRoot = this->leftRotate(subRoot);
        subRoot->left->colorState = true;
        subRoot->colorState = false;
        this->ll = false;
    }
    else if(this->rr == true){
        subRoot = this->rightRotate(subRoot);
        subRoot->colorState = false;
        subRoot->right->colorState = true;
        this->rr = false;
    }
    else if(this->rl == true){
        subRoot->right = rightRotate(subRoot->right);
        subRoot->right->parent = subRoot;
        subRoot = leftRotate(subRoot);
        subRoot->colorState = false;
        subRoot->left->colorState = true;
        this->rl = false;
    }
    else if(this->lr == true){
        subRoot->left = leftRotate(subRoot->left);
        subRoot->left->parent = subRoot;
        subRoot = rightRotate(subRoot);
        subRoot->colorState = false;
        subRoot->right->colorState = true;
        this->lr = false;
    }






    //If a red parent has a red child, then perform a correcting action:
    if(errorFlag){
        //Both children are black
        //If the root is the right child (after rotation)
        if(subRoot->parent->right == subRoot) {
            if (subRoot->parent->left == nullptr || subRoot->parent->left->colorState == false){

                if(subRoot->left != nullptr){
                    if(subRoot->left->colorState){
                        this->rl = true;
                    }
                }
                else if(subRoot->right != nullptr){
                    if(subRoot->right->colorState){
                        this->ll = true;
                    }
                }
            }
            else{
                subRoot->colorState = false;
                subRoot->parent->left->colorState = false;
                if(subRoot->parent != this->root){
                    subRoot->parent->colorState = true;
                }
            }
        }
        else{
            if (subRoot->parent->right == nullptr || subRoot->parent->right->colorState == false){

                if(subRoot->left != nullptr){
                    if(subRoot->left->colorState){
                        this->rr = true;
                    }
                }
                else if(subRoot->right != nullptr){
                    if(subRoot->right->colorState){
                        this->lr = true;
                    }
                }
            }
            else{
                subRoot->colorState = false;
                subRoot->parent->right->colorState = false;
                if(subRoot->parent != this->root){
                    subRoot->parent->colorState = true;
                }
            }
        }

        errorFlag = false;
    }
    return subRoot;
}


template <typename T>
void RBTree<T>::insert(TreeNode<T> *n_node){
    //Perform a normal BST insertion (with recency Queue)
    if(this->size == 0){
        size++;
        this->root = n_node;
        n_node->colorState = false;
    }
    else {
        this->root = insertHelper(this->root, n_node);
    }
}






#endif //ORDEREDMAPIMPLEMENTATION_RBTREE_H
