//
// Created by Rohan Rao on 11/11/22.
//

#ifndef ORDEREDMAPIMPLEMENTATION_TREENODE_H
#define ORDEREDMAPIMPLEMENTATION_TREENODE_H
#include <iostream>
#include <queue>

/*
 * THIS IS THE NODE FOR A RED BLACK TREE
 */

/*
 * THE COLORSTATE DENOTES THE NODE COLOR
 */

/*
 * RED = TRUE, BLACK = FALSE
 */

template<typename T>
class TreeNode {
private:
    T* data;
    std::pair<float, float> coords;

    //Stores the pointer to a linked list containing similar values.
    std::vector<TreeNode<T>*> *neighbor = new std::vector<TreeNode<T>*>;

public:
    //Tree Nodes
    bool colorState = false;
    TreeNode<T> *left;
    TreeNode<T> *right;
    TreeNode<T> *parent;
    explicit TreeNode(T *i_data);
    ~TreeNode();
    T& getData();
    void addNeighbor(TreeNode<T> *n_node);
    bool operator<(TreeNode const &rhs)const;
    bool operator>(TreeNode const &rhs)const;
    bool operator==(TreeNode const &rhs)const;
};

//When a TreeNode is initialized, its colorstats is true (RED)
template<typename T>
TreeNode<T>::TreeNode(T *i_data){
    colorState = true;
    this->left = nullptr;
    this->right = nullptr;
    this->data = i_data;
}

//returns data stored i node (usually mapNode)
template<typename T>
T& TreeNode<T>::getData() {
    return *this->data;
}

//All comparison operators are overloaded for the Tree
template<typename T>
bool TreeNode<T>::operator<(TreeNode const &rhs)const{
    if(this->getData() < rhs.getData()){
        return true;
    }
    else{
        return false;
    }

}


template<typename T>
bool TreeNode<T>::operator>(TreeNode const &rhs)const{
    if(this->getData() >  rhs.getData()){
        return true;
    }
    else{
        return false;
    }

}

template<typename T>
bool TreeNode<T>::operator==(TreeNode const &rhs)const{
    if(this->getData() == rhs.getData()){
        return true;
    }
    else{
        return false;
    }

}

//add same key values (if they exist)
template<typename T>
void TreeNode<T>::addNeighbor(TreeNode<T> *n_node) {
    this->neighbor->push_back(n_node);
}

//TreeNode destructor
template<typename T>
TreeNode<T>::~TreeNode<T>() {
    delete this->neighbor;
}










#endif //ORDEREDMAPIMPLEMENTATION_TREENODE_H
