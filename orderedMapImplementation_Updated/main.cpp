#include <iostream>
#include "RBTree.h"
#include "TreeNode.h"
#include "Hashmap.h"
#include "Vertex.h"
#include <algorithm>
#include "ordered_map.h"
#include "unordered_map_imp.h"

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
    vector<std::string> names;
    names.push_back("Tampa");
    names.push_back("Gainseville");
    names.push_back("new york");
    names.push_back("chicago");
    names.push_back("philly");




    Vertex V1 = Vertex(1.3, 1.2, 12013, "Tampa");
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

    //Boolean argument key determines if you want to sort by key or not (if not then sorted by value)
    ordered_map<Vertex, std::string> omar(true);
    omar.emplace(V1, V1.name);
    omar.emplace(V2, V2.name);
    omar.emplace(V3, V3.name);
    omar.emplace(V4, V4.name);
    omar.emplace(V5, V5.name);
    omar.emplace(V6, V6.name);
    omar.emplace(V7, V7.name);
    omar.emplace(V8, V8.name);
    omar.emplace(V9, V9.name);




    vector<std::pair<Vertex, std::string>> orderedSet_M;
    omar.descendingSort(orderedSet_M);

    for(int i = 0; i < orderedSet_M.size(); i++) {
        cout << orderedSet_M.at(i).second <<" "<<orderedSet_M.at(i).first.y << endl;
    }


    // You can order maps by Key
    unordered_map_imp<std::string, Vertex> omar2(false);
    omar2.emplace(V1.name, V1);
    omar2.emplace(V2.name, V2);
    omar2.emplace(V3.name, V3);
    omar2.emplace(V4.name, V4);
    omar2.emplace(V5.name, V5);
    omar2.emplace(V6.name, V6);
    omar2.emplace(V7.name, V7);
    omar2.emplace(V8.name, V8);
    omar2.emplace(V9.name, V9);

    cout<<" "<<endl;

    vector<std::pair<std::string, Vertex>> orderedSet_H;
    omar2.descendingSort(orderedSet_H);

    for(int i = 0; i < orderedSet_H.size(); i++){
        cout<<orderedSet_H.at(i).first<<" "<<orderedSet_H.at(i).second.y<<endl;
    }
    cout<<" "<<endl;

    //Instant Access
    cout<<omar[V1]<<endl;
    cout<<omar2["Tampa2"].y<<endl;







}
