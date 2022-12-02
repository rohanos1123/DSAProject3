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
    T data;
    std::pair<float, float> coords;
    //Stores the pointer to a linked list containing similar values.
    T* neighbor = nullptr;
    //Recency queue stores the parent and grandfather for each node (has a size of 2)
    std::queue<TreeNode> *RecencyQueue;

public:
    bool colorState = false;
    TreeNode<T> *left;
    TreeNode<T> *right;
    TreeNode<T> *parent;
    TreeNode(std::pair<float, float> coords, T i_data);
    std::pair<float, float> getCoords();
    T getData();
    void setCoords(std::pair<float, float>  &n_coords);
    void setData(T &n_data);
    void switchColor();
    void setColor(bool n_color);
    void setRecencyQueue(std::queue<TreeNode<T>> *n_queue);
    bool operator<(TreeNode &rhs);
    bool operator>(TreeNode &rhs);
    bool operator=(TreeNode &rhs);
};

//When a TreeNode is initialized, its colorstats is true (RED)
template<typename T>
TreeNode<T>::TreeNode(std::pair<float, float> coords, T i_data){
    this->coords = coords;
    this->data = i_data;
    colorState = true;
    RecencyQueue = nullptr;
    this->left = nullptr;
    this->right = nullptr;
}

template<typename T>
T TreeNode<T>::getData() {
    return this->data;
}

template<typename T>
std::pair<float, float> TreeNode<T>::getCoords(){
    return this->coords;
}

template<typename T>
void TreeNode<T>::setCoords(std::pair<float, float> &n_coords) {
    this->coords = n_coords;
}

template<typename T>
void TreeNode<T>::setData(T &n_data){
    this->data = n_data;
}

template<typename T>
void TreeNode<T>::switchColor(){
    if(this->colorState){
        colorState = false;
    }
    else{
        colorState = true;
    }
}

template<typename T>
void TreeNode<T>::setColor(bool n_Color){
    this->colorState = n_Color;
}

template<typename T>
bool TreeNode<T>::operator<(TreeNode &rhs){
    if(this->getData() < rhs.getData()){
        return true;
    }
    else{
        return false;
    }

}

template<typename T>
bool TreeNode<T>::operator>(TreeNode &rhs){
    if(this->getData() >  rhs.getData()){
        return true;
    }
    else{
        return false;
    }

}

template<typename T>
bool TreeNode<T>::operator=(TreeNode &rhs){
    if(this->getData() == rhs.getData()){
        return true;
    }
    else{
        return false;
    }

}

template <typename T>
void TreeNode<T>::setRecencyQueue(std::queue<TreeNode<T>> *n_queue){
    this->RecencyQueue = n_queue;
}







#endif //ORDEREDMAPIMPLEMENTATION_TREENODE_H
