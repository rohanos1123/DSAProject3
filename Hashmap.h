//
// Created by Rohan Rao on 12/1/22.
//
#include <string>
#include <math.h>

#ifndef ORDEREDMAPIMPLEMENTATION_HASHMAP_H
#define ORDEREDMAPIMPLEMENTATION_HASHMAP_H


template <typename T>
class Hashmap {
private:
    T* hashTable;
    float loadFactor;
    float currLF;
    int size;
    int capacity;
public:
    Hashmap(int initSize, float loadFactor);
    void rehash();
    void remove(std::string);
    void insert(T &insertItem);

    //THESE TWO NEED THE SAME input DATA type (you might also need to change the hash function)
    T* operator[](std::string &name);
    int hFunction(std::string &name);
    int quadProbing(int currIndex);
    int quadSearch(int currIndex, std::string &name);
    int linSearch(int currIndex, std::string &name);
    int linearProbing(int currIndex);
};

template <typename T>
Hashmap<T>::Hashmap(int initSize, float lf){
    this->hashTable = new T[initSize]();
    this-loadFactor = lf;
    this->size = 0;
    this->capacity = initSize;
}

template <typename T>
int Hashmap<T>::hFunction(std::string &name) {
    float index = 0;
    for(int i = 0 ; i < name.length(); i++){
        index +=  int(name.at(i)) + pow(2, i);
    }
    index = (int)index%this->capacity;
    return index;
}

template <typename T>
void Hashmap<T>::insert(T &n_obj){
     std::string name = n_obj->name;
     int index = hFunction(name);

     if(hashTable[index] != nullptr){
         index = quadProbing(index);
         //index == linearProbing(index);
     }
     hashTable[index] = n_obj;

     this->size++;
     currLF = this->capacity/this->size;
     if(currLF >= loadFactor){
         this->rehash();
     }
}

template<typename T>
int Hashmap<T>::quadProbing(int currIndex){
    int i = 0;
    while(hashTable[currIndex] != nullptr){
        currIndex = (currIndex + pow(i, 2))%this->capacity;
        i++;
    }
    return currIndex;
}

template <typename T>
int Hashmap<T>::linearProbing(int currIndex) {
    while(hashTable[currIndex] != nullptr){
        currIndex = currIndex + 1;
    }
    return currIndex;
}

template<typename T>
T* Hashmap<T>::operator[](std::string &name){
    int index = hFunction(name);
    if(hashTable[index]->getName() != name){
        int i = 0;
        int t_index = index;

        while(hashTable[index]->getName() != name) {
            index = int(t_index + pow(i, 2))%capacity;
            i++;
        }
    }
    else{
        return hashTable[index];
    }
}

template<typename T>
int Hashmap<T>::quadSearch(int currIndex, std::string &name){
    int index = 0;
    int t_index = currIndex;
    int i = 0;
    while(hashTable[index]->getName() != name) {
        index = int(t_index + pow(i, 2))%capacity;
        i++;
    }
    return index;
}

template<typename T>
int Hashmap<T>::linSearch(int currIndex, std::string &name) {
    int index = 0;
    int t_index = currIndex;
    int i = 0;
    whiile(hashTable[index]->getName() != name){
        index = int(t_index + pow(i, 2))%capacity;
        i++;
    }
}

template<typename T>
void Hashmap<T>::rehash(){
    T* temp = new T[capacity * 2];
    this->capacity *= 2;
    for(int i = 0; i < this->capacity; i++){
        if(hashTable[i] != nullptr){
           std::string name = hashTable[i]->name;
           T* copy = hashTable[i];
           index = hFunction(name);
           temp[index] = copy;
        }
    }
    delete[] this->hashTable;
    this->hashTable = temp;
    currLF = size/capacity;
}

#endif //ORDEREDMAPIMPLEMENTATION_HASHMAP_H
