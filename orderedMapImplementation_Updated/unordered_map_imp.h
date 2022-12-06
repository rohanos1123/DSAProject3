//
// Created by Rohan Rao on 12/6/22.
//

#ifndef ORDEREDMAPIMPLEMENTATION_UNORDERED_MAPI_H
#define ORDEREDMAPIMPLEMENTATION_UNORDERED_MAPI_H
#include "Hashmap.h"

template<typename T1, typename T2>
class unordered_map_imp {
private:


    struct mapNode{

    private:
        bool orderByKey = false;
    public:
        T1 key;
        T2 value;


        mapNode(T1 i_key, T2 i_value, bool i_orderByKey){
            this->key = i_key;
            this->value = i_value;
            this->orderByKey = i_orderByKey;
        }

        bool operator<(const mapNode &rhs)const{
            if(orderByKey) {
                return this->key < rhs.key;
            }
            else{
                return this->value < rhs.value;
            }

        }

        bool operator>(const mapNode &rhs)const{
            if(orderByKey) {
                return this->key > rhs.key;
            }
            else{
                return this->value > rhs.value;
            }

        }

        bool operator==(const mapNode &rhs)const{
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

        T1& getKey(){
            return this->key;
        }

    };

    Hashmap<mapNode, T1, T2> *hMap;
    std::vector<mapNode> *sortedList = new std::vector<mapNode> ;
    bool orderByKey;

public:
    unordered_map_imp<T1, T2>(bool i_orderByKey){
        hMap = new Hashmap<mapNode, T1, T2>(4, 0.5);
        this->orderByKey = i_orderByKey;
    }


    void emplace(T1 const &key, T2 const &value){
        mapNode *m = new mapNode(key, value, this->orderByKey);
        hMap->insert(*m);
    }

    T2 operator[](T1 key){
        if((*hMap)[key] != nullptr){
            return *(*hMap)[key];
        }
        else{
            return T2();
        }

    }


    void descendingSort(std::vector<std::pair<T1, T2>> &i_vector){
        this->hMap->sortedList(*this->sortedList);
        for(int i = this->sortedList->size() - 1; i >= 0; i--){
            std::pair<T1, T2> *n_pair = new std::pair<T1, T2>(sortedList->at(i).key, sortedList->at(i).value);
            i_vector.push_back(*n_pair);
        }
    }






};


#endif //ORDEREDMAPIMPLEMENTATION_UNORDERED_MAP_H
