//
// Created by Rohan Rao on 12/5/22.
//

#ifndef ORDEREDMAPIMPLEMENTATION_ORDERED_MAP_H
#define ORDEREDMAPIMPLEMENTATION_ORDERED_MAP_H

#include "RBTree.cpp"
#include "Vertex.cpp"

template <typename T, typename T2>
class ordered_map {

    struct mapNode{

    private:
        bool orderByKey = false;
    public:
        T key;
        T2 value;


        mapNode(T i_key, T2 i_value, bool i_orderByKey){
            this->key = i_key;
            this->value = i_value;
            this->orderByKey = i_orderByKey;
        }

        bool operator<(mapNode &rhs){
            if(orderByKey) {
                return this->key < rhs.key;
            }
            else{
                return this->value < rhs.value;
            }

        }

        bool operator>(mapNode &rhs){
            if(orderByKey) {
                return this->key > rhs.key;
            }
            else{
                return this->value > rhs.value;
            }

        }

        bool operator==(mapNode &rhs){
            if(orderByKey) {
                return this->key == rhs.key;
            }
            else{
                return this->value == rhs.value;
            }

        }

        T2& getValue(){
            return this->value;
        }

        T& getKey(){
            return this->key;
        }

    };

private:
    RBTree<mapNode, T, T2> *rbTree;
    std::vector<mapNode> *sortedList = new std::vector<mapNode> ;
    bool orderByKey;

public:

    ordered_map<T, T2>(bool i_orderByKey = true){
        rbTree = new RBTree<mapNode, T, T2>;
        this->orderByKey = i_orderByKey;
    }

    void emplace(T const &key, T2 const &value){
        mapNode *m = new mapNode(key, value, this->orderByKey);
        rbTree->insert(*m);
    }

    T2 operator[](T key){
        if(rbTree->Search(rbTree->root, key) != nullptr){
            return *rbTree->Search(rbTree->root, key);
        }
        else{
            return T2();
        }

    }

    void descendingSort(std::vector<std::pair<T, T2>> &i_vector){
        this->rbTree->inOrderTraversal(*this->sortedList);
        for(int i = this->sortedList->size() - 1; i >= 0; i--){
            std::pair<T, T2> *n_pair = new std::pair<T, T2>(sortedList->at(i).key, sortedList->at(i).value);
            i_vector.push_back(*n_pair);
        }
    }



};


#endif //ORDEREDMAPIMPLEMENTATION_ORDERED_MAP_H
