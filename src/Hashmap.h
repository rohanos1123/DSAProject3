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
    struct Node{
        T* vertex;
        bool isTouched;

        Node(){
            vertex = nullptr;
            isTouched = false;
        }

        Node(T* n_vertex){
            vertex = n_vertex;
            isTouched = true;
        }
    };

    T** hashTable;
    float loadFactor;
    float currLF;
    int size;
    int capacity;

    //THESE TWO NEED THE SAME input DATA type (you might also need to change the hash function)
    int hFunction(std::string &name);
    int quadProbing(int currIndex);
    int linearProbing(int currIndex);
    void rehash();
    void initList(T**, int size);
    int quadProbing2(int currIndex, T** array);
public:
    Hashmap();
    Hashmap(int initSize, float loadFactor);
    ~Hashmap();
    void sortedList(std::vector<T> &inputVector);
    void insert(T &insertItem);

    T operator[](std::string name);


};
template <typename T>
Hashmap<T>::Hashmap() {
    this->hashTable = new T * [4];
    this->loadFactor = 0.5;
    this->size = 0;
    this->capacity = 4;
    initList(hashTable, capacity);
}
template <typename T>
Hashmap<T>::Hashmap(int initSize, float lf){
    this->hashTable = new T*[initSize];
    this->loadFactor = lf;
    this->size = 0;
    this->capacity = initSize;

    int i = 0;
    initList(hashTable,capacity);

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
     std::string name = n_obj.name;
     int index = hFunction(name);

     if(hashTable[index] != nullptr){
         index = quadProbing(index);
         //index == linearProbing(index);
     }

     hashTable[index] = &n_obj;


     this->size++;
     currLF = (float)this->size/ this->capacity;
     if(currLF >= loadFactor){
         this->rehash();
     }
}

template<typename T>
int Hashmap<T>::quadProbing(int currIndex){
    int i = 0;
    while(hashTable[currIndex] != nullptr){
        currIndex = (currIndex + (int)pow(i, 2))%this->capacity;
        i++;
    }
    return currIndex;
}

template<typename T>
int Hashmap<T>::quadProbing2(int currIndex, T** array){
    int i = 0;
    while(array[currIndex] != nullptr){
        currIndex = (currIndex + (int)pow(i, 2))%this->capacity;
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
T Hashmap<T>::operator[](std::string name){
    int index = hFunction(name);
    if(hashTable[index]->name != name){
        int i = 0;
        int oldIndex = 0;
        int t_index = index;
        T* currentAddress = hashTable[index];
        while(currentAddress->name != name) {
            index = int(index + (int)pow(i, 2))%capacity;
            if(i >= capacity){
                std::cout<<name<<" "<<"could not be found!"<<std::endl;
                return T();
            }
            if(hashTable[index] != nullptr){
                currentAddress = hashTable[index];
            }
            i++;
        }
        return *hashTable[index];
    }
    else{
        return *hashTable[index];
    }
}

template<typename T>
void Hashmap<T>::rehash(){
    int n_index = 0;
    int oldCapacity = capacity;
    T** temp = new T*[capacity * 2];
    this->capacity *= 2;
    initList(temp, this->capacity);
    for(int i = 0; i < oldCapacity; i++){
        if(hashTable[i] != nullptr){
           std::string name = hashTable[i]->name;
           T* copy = hashTable[i];
           n_index = this->hFunction(name);
           if(temp[n_index] != nullptr){
               n_index = quadProbing2(n_index, temp);
           }
           temp[n_index] = copy;
        }
    }
    delete[] this->hashTable;
    this->hashTable = temp;
    currLF = (float)size/capacity;
}

template <typename T>
Hashmap<T>::~Hashmap<T>() {
    delete this->hashTable;
}

template <typename T>
void Hashmap<T>::sortedList(std::vector<T> &inputVector){
     for(int i = 0; i < this->capacity; i++){
         if(hashTable[i] != nullptr){
             inputVector.push_back(*hashTable[i]);
         }
     }
     std::sort(inputVector.begin(), inputVector.end());
}

template <typename T>
void Hashmap<T>::initList(T** head, int i_size){
    int i = 0;
    for(i = 0; i < i_size; i++){
        head[i] = nullptr;
    }
}




#endif //ORDEREDMAPIMPLEMENTATION_HASHMAP_H
