//
// Created by Rohan Rao on 12/4/22.
//

#ifndef ORDEREDMAPIMPLEMENTATION_CITY_H
#define ORDEREDMAPIMPLEMENTATION_CITY_H
#include <map>
#include <string>
#include <vector>
#include <iostream>

//USE THIS FOR ALPHABETICAL ORDERING
class City {
private:
    std::map<std::string, float> *cityData = new std::map<std::string, float>;
    std::string name;
    float parameter = 0;
    bool parameterEnabled = false;
    std::string parameterName;
public:
    City(std::string &name){
        this->name = name;
    }

    void setParameter(std::string p){
        if(this->cityData->find(p) != this->cityData->end()){
            parameterEnabled = true;
            parameterName = p;
            parameter = this->cityData->at(p);
        }
        else{
            std::cout<<"Could not find parameter"<<std::endl;
            parameterEnabled = false;
        }

    }

    void setAlphabetical(){
        parameterEnabled = false;
        parameter = 0;
    }

    bool operator<(const City &rhs)const{
        if(!parameterEnabled) {
            int size = std::min(this->name.length(), rhs.name.length());
            for (int i = 0; i < size; i++) {
                if (this->name.at(i) < rhs.name.at(i)) {
                    return true;
                } else if (this->name.at(i) > rhs.name.at(i)) {
                    return false;
                }
            }

            return false;
        }
        else{
            if(this->parameter < rhs.parameter){
                return true;
            }
            else{
                return false;
            }
        }

    }


    bool operator>(const City &rhs)const{
        if(!parameterEnabled) {
            int size = std::min(this->name.length(), rhs.name.length());
            for (int i = 0; i < size; i++) {
                if (this->name.at(i) > rhs.name.at(i)) {
                    return true;
                } else if (this->name.at(i) < rhs.name.at(i)) {
                    return false;
                }
            }

            return false;
        }
        else{
            if(this->parameter > rhs.parameter){
                return true;
            }
            else{
                return false;
            }
        }
    }


    bool operator==(const City &rhs) const{
        if(this->parameterName != rhs.parameterName){

        }


        if(parameterEnabled) {
            if (this->name.length() != rhs.name.length()) {
                return false;
            } else {
                for (int i = 0; i < this->name.length(); i++) {
                    if (this->name.at(i) != rhs.name.at(i)) {
                        return false;
                    }
                }
                return true;
            }
        }
        else{
            if(this->parameter == rhs.parameter){
                return true;
            }
            else{
                return false;
            }
        }

    }

    void addParameter(std::string pName, float val){
        this->cityData->at(pName) = val;
    }

    std::pair<std::string, std::vector<std::pair<std::string, float>>> returnData(){

        auto iter = this->cityData->begin();
        std::vector<std::pair<std::string, float>> vectorCityData;
        for(; iter != this->cityData->end(); iter++){
            std::string category = iter->first;
            float parameter = iter->second;
            std::pair<std::string, float> n_pair(category, parameter);
            vectorCityData.push_back(n_pair);
        }
        std::pair<std::string, std::vector<std::pair<std::string, float>>> dataPair(name, vectorCityData);
        return dataPair;
    }

};


#endif //ORDEREDMAPIMPLEMENTATION_CITY_H
