//
// Created by Rohan Rao on 12/4/22.
//

#ifndef ORDEREDMAPIMPLEMENTATION_VERTEX_H
#define ORDEREDMAPIMPLEMENTATION_VERTEX_H
#include <string>
#include <unordered_map>


class Vertex {
public:
    float x = 0;
    float y = 0;
    float z = 0;
    std::string name;

    Vertex(){
        std::string name;
        float x = 0;
        float y = 0;
        float z = 0;
    }

    Vertex(float lat, float lon, float parameter, std::string i_name){
        this->name = i_name;
        x = lat;
        y = parameter;
        z = lon;
    }

    bool operator>(const Vertex &rhs) const{
        if(this->y > rhs.y){
            return true;
        }
        else{
            return false;
        }

    }

    bool operator<(const Vertex &rhs) const{
        if(this->y < rhs.y){
            return true;
        }
        else{
            return false;
        }

    }

    bool operator==(const Vertex &rhs) const{
        if(this->y == rhs.y){
            return true;
        }
        else{
            return false;
        }
    }



};



#endif //ORDEREDMAPIMPLEMENTATION_VERTEX_H
