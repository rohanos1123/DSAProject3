#include <iostream>
#include "RBTree.h"
#include "TreeNode.h"
#include "Hashmap.h"
#include "Vertex.h"
#include <algorithm>

using namespace std;


int main() {

    //List of Verticies

    //Intialization of verticies
    /*
     * Sample code on how to use the hashmap and ordered tree.
     * The hashmap also has functionality of searching while the Ordered tree does not
     *(I will try to impliment this if I can, but it is not required for the assignment
     * Both are capable of returning sorted lists as shown below
     * depending on preference you can leave it like this or pack them into a separate ordered and unordered
     * map class. Let me know if there are any issues
     */
    Vertex V1 = Vertex(1.3, 1.2, 3013, "Tampa");
    Vertex V2 = Vertex(2.1, 5.6, 5812, "Gainseville");
    Vertex V3 = Vertex(12.1, 15.6, 91712,"new york");
    Vertex V4 = Vertex(491, 19331, 134712, "chicago");
    Vertex V5 = Vertex(491, 19331, 1213712, "philly");
    Vertex V6 = Vertex(1.3, 1.2, 30132, "Tampa2");
    Vertex V7 = Vertex(2.1, 5.6, 58122, "Gainseville2");
    Vertex V8 = Vertex(12.1, 15.6, 917122,"new york2");
    Vertex V9 = Vertex(491, 19331, 1347122, "Indiago2");
    Vertex V11 = Vertex(491, 19331, 12137212, "India");
    Vertex V10 = Vertex(491, 19331, 12137122, "omaly2");


    //Create the RB Tree (Ordered map)
    RBTree<Vertex> RBTree;

    //Insert verticies into RB Tree
    RBTree.insert(V1);
    RBTree.insert(V2);
    RBTree.insert(V3);
    RBTree.insert(V4);
    RBTree.insert(V5);

    //Build the hashmap
    Hashmap<Vertex> hashmap(4, 0.5);

    //Insert into hashmap (unordered_map)
    hashmap.insert(V1);
    hashmap.insert(V2);
    hashmap.insert(V3);
    hashmap.insert(V4);
    hashmap.insert(V5);
    hashmap.insert(V6);
    hashmap.insert(V7);
    hashmap.insert(V8);
    hashmap.insert(V9);
    hashmap.insert(V10);
    hashmap.insert(V11);



    cout<<"Hashmap sorting: "<<endl;
    vector<Vertex> hashMapOrdered;
    hashmap.sortedList(hashMapOrdered);

    for(int i = 0; i < hashMapOrdered.size(); i++){
        cout<<hashMapOrdered[i].name<<" "<<hashMapOrdered[i].y<<endl;
    }
    cout<<endl;
    cout<<endl;
    cout<<endl;

    cout<<"RB Tree (ordered Map) sorting"<<endl;
    vector<Vertex> RBTreeOrdered;
    RBTree.inOrderTraversal(RBTreeOrdered);

    for(int i = 0; i < RBTreeOrdered.size(); i++){
        cout<<RBTreeOrdered[i].name<<" "<<RBTreeOrdered[i].y<<endl;
    }



}
