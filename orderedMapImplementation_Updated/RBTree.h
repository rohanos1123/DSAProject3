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
    TreeNode<T>* leftRotate(TreeNode<T> *node);
    TreeNode<T>* rightRotate(TreeNode<T> *node);
    int size;
    TreeNode<T>* insertHelper(TreeNode<T> *subRoot, TreeNode<T> *n_node);
    void iotHelper(TreeNode<T> *node, std::vector<T> &outputData);
    void postOrderHelper(TreeNode<T> *node);



    bool ll = false;
    bool rr = false;
    bool lr = false;
    bool rl = false;


public:
    RBTree();
    void insert(T &n_node);
    float operator[](std::string);
    void inOrderTraversal(std::vector<T> &insertionVector);
    ~RBTree();


};

template <typename T>
RBTree<T>::RBTree(){
    this->root = nullptr;
    this->size = 0;


}

//AVL tree rotation
template <typename T>
TreeNode<T>* RBTree<T>::leftRotate(TreeNode<T> *node){
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
template <typename T>
TreeNode<T>* RBTree<T>::rightRotate(TreeNode<T> *node){
    // Take the left child of node
    TreeNode<T> *lc = node->left;
    //take the remaining right child of the left node
    TreeNode<T> *lrc = lc->right;
    //TreeNode
    TreeNode<T> *np = node->parent;


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

template <typename T>
TreeNode<T>* RBTree<T>::insertHelper(TreeNode<T> *subRoot, TreeNode<T> *n_node){
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
    //perform a left rotation if the
    if(this->ll == true){
        //performs a left rotation on the subroot:
        subRoot = this->leftRotate(subRoot);
        subRoot->colorState = false;
        subRoot->left->colorState = true;
        this->ll = false;
    }
    else if(this->rr == true){
        //Right rotate the root
        subRoot = this->rightRotate(subRoot);
        subRoot->right->colorState = true;
        subRoot->colorState = false;
        this->rr = false;
    }
    else if(this->rightleft == true){
        //Perform first rotation
        subRoot->right = rightRotate(subRoot->right);
        //Reassign parents
        subRoot->right->parent = subRoot;
        //Perform second ration on new left root
        subRoot = leftRotate(subRoot);

        //switch color of father and son
        subRoot->colorState = false;
        subRoot->left->colorState = true;
        this->rightleft = false;
    }
    else if(this->lr == true){
        //Left rotation on subroot, left child and reassign
        subRoot->left = leftRotate(subRoot->left);
        subRoot->left->parent = subRoot;
        //Re assign parent of subroot left to form rr case
        //Right rotate
        subRoot = rightRotate(subRoot);
        //Swotch colors
        subRoot->colorState = false;
        subRoot->right->colorState = true;
        this->lr = false;
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
                        this->ll = true;
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
            //If the parent is a right child of the grandfather, and both are black
            if (grandfather->right == nullptr || grandfather->right->colorState == false){

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

//Bst insertion with insert helper.
template <typename T>
void RBTree<T>::insert(T &nObj){
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

//Inorder traversal helper
template <typename T>
void RBTree<T>::iotHelper(TreeNode<T> *node, std::vector<T> &outputData){
    if(node == nullptr){
        return;
    }
    iotHelper(node->left, outputData);
    outputData.push_back(node->getData());
    iotHelper(node->right, outputData);
}

//In order traversal for sorting
template <typename T>
void RBTree<T>::inOrderTraversal(std::vector<T> &insertionVector){
    iotHelper(this->root, insertionVector);
}

//Post order helper used for deletion
template <typename T>
void RBTree<T>::postOrderHelper(TreeNode<T> *node) {
    if(node == nullptr){
        return;
    }
    postOrderHelper(node->left);
    postOrderHelper(node->right);
    delete node;
}

template <typename T>
RBTree<T>::~RBTree(){
    postOrderHelper(this->root);
}










#endif //ORDEREDMAPIMPLEMENTATION_RBTREE_H
