//
// Created by Rohan Rao on 12/1/22.
//
#include <string>
#include <math.h>

//This hashmap only works with string Keys (due to the hash function)


#ifndef ORDEREDMAPIMPLEMENTATION_HASHMAP_H
#define ORDEREDMAPIMPLEMENTATION_HASHMAP_H


template <typename T, typename r, typename l>
class Hashmap {
private:
    //Initialze the variables

    T** hashTable;
    float loadFactor;

    //Load factor
    float currLF;

    //Size at a time
    int size;

    //Capacity
    int capacity;

    //THESE TWO NEED THE SAME input DATA type (you might also need to change the hash function)

    int hFunction(std::string &name);
    int quadProbing(int currIndex);
    void rehash();
    void initList(T**, int size);
    int quadProbing2(int currIndex, T** array);
public:
    Hashmap(int initSize, float loadFactor);
    ~Hashmap();
    void sortedList(std::vector<T> &inputVector);
    void insert(T &insertItem);

    l* operator[](r name);


};

// hashmap initialization
template <typename T, typename r, typename  l>
Hashmap<T, r, l>::Hashmap(int initSize, float lf){
    this->hashTable = new T*[initSize];
    this->loadFactor = lf;
    this->size = 0;
    this->capacity = initSize;

    int i = 0;

    //Initialize all values in dynamically allocated array to nullptr
    initList(hashTable,capacity);

}

//Hash function, it is based on each letter in string and making it a polynomial
template <typename T, typename r, typename l>
int Hashmap<T, r, l>::hFunction(std::string &name) {
    float index = 0;
    for(int i = 0 ; i < name.length(); i++){
        index +=  int(name.at(i)) + pow(2, i);
    }
    //Modulated to fit into the array
    index = (int)index%this->capacity;
    return index;
}


//Insertion method (uses quadratic probing on collision)
template <typename T, typename r, typename l>
void Hashmap<T, r, l>::insert(T &n_obj){
     std::string name = n_obj.getKey();
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

//Quadratic probing method on the main hashMap
template <typename T, typename r, typename l>
int Hashmap<T, r, l>::quadProbing(int currIndex){
    int i = 0;
    while(hashTable[currIndex] != nullptr){
        currIndex = (currIndex + (int)pow(i, 2))%this->capacity;
        i++;
    }
    return currIndex;
}

//Does quadratic probing on a seperate array (for rehashing purposes)
template <typename T, typename r, typename l>
int Hashmap<T, r, l>::quadProbing2(int currIndex, T** array){
    int i = 0;
    while(array[currIndex] != nullptr){
        currIndex = (currIndex + (int)pow(i, 2))%this->capacity;
        i++;
    }
    return currIndex;
}


//Operator overloaded method for retrieval (Must be a name)
template <typename T, typename r, typename l>
l* Hashmap<T, r, l>::operator[](r name){
    int index = hFunction(name);

    if(hashTable[index]->getKey().compare(name) != 0){
        int i = 0;
        T* currentAddress = hashTable[index];
        while(currentAddress->getKey() != name) {
            index = int(index + (int)pow(i, 2))%capacity;
            if(i >= capacity){
                std::cout<<name<<" "<<"could not be found!"<<std::endl;
                return nullptr;
            }
            if(hashTable[index] != nullptr){
                currentAddress = hashTable[index];
            }
            i++;
        }
        return &(hashTable[index]->getValue());
    }
    else{
        return &(hashTable[index]->getValue());
    }
}

//Rehashing method// dynamically allocates new list and prints it out
template <typename T, typename r, typename l>
void Hashmap<T, r, l>::rehash(){
    int n_index = 0;
    int oldCapacity = capacity;
    T** temp = new T*[capacity * 2];
    this->capacity *= 2;
    initList(temp, this->capacity);
    for(int i = 0; i < oldCapacity; i++){
        if(hashTable[i] != nullptr){
           std::string name = hashTable[i]->getKey();
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

//hashMap destructor
template <typename T, typename r, typename l>
Hashmap<T, r, l>::~Hashmap<T, r, l>() {
    delete this->hashTable;
}

//hashmaps cannot sort themselves, so we used quicksort and stored in seperate vector (
//Vector is inputted as a reference



template <typename T, typename r, typename l>
void Hashmap<T, r, l>::sortedList(std::vector<T> &inputVector){
     for(int i = 0; i < this->capacity; i++){
         if(hashTable[i] != nullptr){
             inputVector.push_back(*hashTable[i]);
         }
     }
     std::sort(inputVector.begin(), inputVector.end());
}

//Set all values of array to nullptr
template <typename T, typename r, typename l>
void Hashmap<T, r, l>::initList(T** head, int i_size){
    for(int i = 0; i < i_size; i++){
        head[i] = nullptr;
    }
}




#endif //ORDEREDMAPIMPLEMENTATION_HASHMAP_H
