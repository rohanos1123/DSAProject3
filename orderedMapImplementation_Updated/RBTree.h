//
// Created by Rohan Rao on 11/11/22.
//

#ifndef ORDEREDMAPIMPLEMENTATION_RBTREE_H
#define ORDEREDMAPIMPLEMENTATION_RBTREE_H

#include "TreeNode.h"
#include <queue>

template <typename T, typename l, typename r>
class RBTree {
private:
    TreeNode<T>* leftRotate(TreeNode<T> *node);
    TreeNode<T>* rightRotate(TreeNode<T> *node);
    int size;
    TreeNode<T>* insertHelper(TreeNode<T> *subRoot, TreeNode<T> *n_node);
    void iotHelper(TreeNode<T> *node, std::vector<T> &outputData);
    void postOrderHelper(TreeNode<T> *node);


    // Flags for tree rotations (all set to false intiaially) (switched on insert)
    bool leftleft = false;
    bool rightright = false;
    bool leftright = false;
    bool rightleft = false;


public:
    TreeNode<T> *root;
    RBTree();
    void insert(T &n_node);
    r* Search(TreeNode<T>* omar, l i_key);

    void inOrderTraversal(std::vector<T> &insertionVector);
    ~RBTree();


};

template <typename T, typename l, typename r>
RBTree<T, l, r>::RBTree(){
    this->root = nullptr;
    this->size = 0;


}

//AVL tree rotation
template <typename T, typename l, typename r>
TreeNode<T>* RBTree<T, l, r>::leftRotate(TreeNode<T> *node){
    //Take the unbalanced node (*node) and rotate to make the right child the new root of the subtree

    //Take the right child of the node
    TreeNode<T> *rc = node->right;

    //Take the left child of the right node (so no node is lost)
    TreeNode<T> *rlc = rc->left;


    //make the right child the overall parent
    rc->left = node;

    //Assign the right child of node to the left child of the right child of node
    node->right = rlc;

    //Reassign the parents node to rc
    node->parent = rc;

    //take the left child of the right and reassign its parent to node(if it exists)
    if(rlc != nullptr){
        rlc->parent = node;
    }

    return rc;
}

//AVL tree rotation
template <typename T, typename l, typename r>
TreeNode<T>* RBTree<T, l, r>::rightRotate(TreeNode<T> *node){
    // Take the left child of node
    TreeNode<T> *lc = node->left;
    //take the remaining right child of the left node
    TreeNode<T> *lrc = lc->right;


    //Make the left child right node the node as node > lc
    lc->right = node;

    //Transfer the left node of the left child to the right child
    node->left = lrc;

    //Reassign the parents the parent node
    node->parent = lc;

    if(lrc != nullptr){
        lrc->parent = node;
    }

    //return the new parent to the subtree
    return lc;
}

template <typename T, typename l, typename r>
TreeNode<T>* RBTree<T, l, r>::insertHelper(TreeNode<T> *subRoot, TreeNode<T> *n_node){
    //If a red parent has a red child
    bool errorFlag = false;

    //Perform normal tree insertion
    if(subRoot == nullptr) {
        size++;
        return n_node;
    }
    else if(subRoot->getData() > n_node->getData()){
       subRoot->left =  insertHelper(subRoot->left, n_node);
       //Assign Parent after recursive calls are done (Subroot is parent of last added root)
       subRoot->left->parent = subRoot;
       if(subRoot != this->root){
           //if x's uncle is red and the parent is not black:
           if(subRoot->colorState) {
               if (subRoot->left->colorState) {
                   errorFlag = true;
               }
           }
       }
    }
    else if (subRoot->getData() < n_node->getData()){
        subRoot->right =  insertHelper(subRoot->right, n_node);
        //Assign parent of n_node after recursive calls are done
        subRoot->right->parent = subRoot;
        if(subRoot != this->root){

            if(subRoot->colorState) {
                if (subRoot->right->colorState) {
                    errorFlag = true;
                }
            }
        }
    }
    else if(subRoot->getData() == n_node->getData()){
        subRoot->addNeighbor(n_node);
        return n_node;
    }

    //Left left rotation and color reset
    if(this->leftleft == true){
        //left rotate once
        subRoot = this->leftRotate(subRoot);
        //set new parent to black
        subRoot->colorState = false;
        //set new child to red
        subRoot->left->colorState = true;
        this->leftleft = false;
    }
    //Right right rotate and color reset
    else if(this->rightright == true){
        //left rotate once
        subRoot = this->rightRotate(subRoot);
        //set new parent to black
        subRoot->colorState = false;
        //set new child to red
        subRoot->right->colorState = true;

        this->rightright = false;
    }
    //Right left rotate and color reset
    else if(this->rightleft == true){
        subRoot->right = rightRotate(subRoot->right);
        subRoot->right->parent = subRoot;
        subRoot = leftRotate(subRoot);
        subRoot->colorState = false;
        subRoot->left->colorState = true;
        this->rightleft = false;
    }
    //left right rotate and color reset
    else if(this->leftright == true){
        subRoot->left = leftRotate(subRoot->left);
        subRoot->left->parent = subRoot;
        subRoot = rightRotate(subRoot);
        subRoot->colorState = false;
        subRoot->right->colorState = true;
        this->leftright = false;
    }



    //If the parent and grandparent are red, then set a flag for a repair function
    if(errorFlag){
        //If the subroot is the right child of the grandfather
        TreeNode<T> *grandfather = subRoot->parent;
        if(grandfather->right == subRoot) {
            //If the uncle of the current node is black, then:
            if (grandfather->left == nullptr || grandfather->left->colorState == false){
                if(subRoot->left != nullptr){
                    //If the left of the subroot child is red (2 red children)
                    if(subRoot->left->colorState){
                        //Perform a right left rotation to move the parent up and cahnge color of subroot (parent) to black
                        this->rightleft = true;
                    }
                }

                else if(subRoot->right != nullptr){
                    //If the node that was inserted is a child and is red, do right rotation to parent as root (black)
                    if(subRoot->right->colorState){
                        this->leftleft = true;
                    }
                }
            }
            else{
                //if the uncle is red, then make the switch the children/parents color (if not red)
                subRoot->colorState = false;
                grandfather->left->colorState = false;
                if(grandfather != this->root){
                    grandfather->colorState = true;
                }
            }
        }
        else{
            //If the parent is a right child of the grandfather, if both are black
            if (grandfather->right == nullptr || grandfather->right->colorState == false){

                //Perform the color switch
                if(subRoot->left != nullptr){
                    if(subRoot->left->colorState){
                        this->rightright = true;
                    }
                }
                //Left right if the subroot is right
                else if(subRoot->right != nullptr){
                    if(subRoot->right->colorState){
                        this->leftright = true;
                    }
                }
            }
            else{
                subRoot->parent->right->colorState = false;
                subRoot->colorState = false;
                if(subRoot->parent != this->root){
                    subRoot->parent->colorState = true;
                }
            }
        }
        errorFlag = false;
    }
    return subRoot;
}


template <typename T, typename l, typename r>
void RBTree<T, l, r>::insert(T &nObj){
    //Perform a normal BST insertion (with recency Queue)
    auto *n_node = new TreeNode<T>(&nObj);
    if(this->size == 0){
        size++;
        this->root = n_node;
        n_node->colorState = false;
    }
    else {
        this->root = insertHelper(this->root, n_node);
    }
}

//In order traversal helper method due to rescursion
template <typename T, typename l, typename r>
void RBTree<T, l, r>::iotHelper(TreeNode<T> *node, std::vector<T> &outputData){
    if(node == nullptr){
        return;
    }
    iotHelper(node->left, outputData);
    outputData.push_back(node->getData());
    iotHelper(node->right, outputData);
}

//In orderTraversal copies values into a list and prints it out
template <typename T, typename l, typename r>
void RBTree<T, l, r>::inOrderTraversal(std::vector<T> &insertionVector){
    iotHelper(this->root, insertionVector);
}

//post order traversal node deletion
template <typename T, typename l, typename r>
void RBTree<T, l, r>::postOrderHelper(TreeNode<T> *node) {
    if(node == nullptr){
        return;
    }
    postOrderHelper(node->left);
    postOrderHelper(node->right);
    delete node;
}

//Destructor that deletes nodes with postOrder
template <typename T, typename l, typename r>
RBTree<T, l ,r>::~RBTree(){
    postOrderHelper(this->root);
}

//Search method
template <typename T, typename l, typename r>
r* RBTree<T, l, r>::Search(TreeNode<T> *subRoot, l i_key){
    if(subRoot == nullptr){
        std::cout<<"Could not find data!"<<std::endl;
        return nullptr;
    }

    if(subRoot->getData().getKey() == i_key){
        return &subRoot->getData().getValue();
    }

    if(subRoot->getData().getKey() > i_key){
       return  Search(subRoot->left, i_key);
    }
    else {
        return Search(subRoot->right, i_key);
    }

}













#endif //ORDEREDMAPIMPLEMENTATION_RBTREE_H
