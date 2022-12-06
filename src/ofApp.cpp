#include "ofApp.h"
#include <fstream>

#define originX -ofGetWidth()/2.0f
#define originY -ofGetHeight()/2.0f

//--------------------------------------------------------------
USMesh US;
int currentParameter = 1;
void ofApp::setup() {
    //This function gets called once
    US.setup();
    US.citySetup(currentParameter);
    
   
    gui.setup();
    gui.add(results.setup("Show Results"));
    gui.add(parameter.setup("Change Parameter"));
    gui.add(dataStruct.setup("Change Data structure"));
    gui.unregisterMouseEvents();
    
    results.setSize(1/20.0f, 1/20.0f);
    parameter.setSize(1/20.0f, 1/20.0f);
    dataStruct.setSize(1 / 20.0f, 1 / 20.0f);

    results.setPosition(10, 50);
    parameter.setPosition(10, 90);
    dataStruct.setPosition(10, 130);

    results.registerMouseEvents();
    parameter.registerMouseEvents();
    dataStruct.registerMouseEvents();

    ofEnableDepthTest();

}
//--------------------------------------------------------------
void ofApp::update(){
    
}

//-------------------------------------------------------------- This function will be called multiple times per second, and is where the hashMap integration will be
void ofApp::draw(){
    if (results) {
        US.printResults();
        for (int i = 0; i < 100000000; i++); //Delay
    }
    if (parameter) {
        std::cout << "What Parameter would you like to see?" << std::endl;
        std::cout << "1. Population" << std::endl << "2. Population Density (km^2)" << std::endl;
        std::string choice;
        std::cin >> choice;
        currentParameter = std::stoi(choice);
        US.clearCities();
        US.citySetup(currentParameter);
    }
    if (dataStruct) {
        std::cout << "Changing structure from ";
        if (US.usingOrderedmap) {
            std::cout << " ordered map to unordered map." << std::endl;
            US.usingOrderedmap = false;
        }
        else {
            std::cout << " unordered map to ordered map." << std::endl;
            US.usingOrderedmap = true;
        }
        US.citySetup(currentParameter);
        for (int i = 0; i < 100000000; i++); //Delay
    }
    camera.begin();
    
    US.draw();
    ofPushMatrix();
        ofRotateY(90);
        ofScale(1.2,1, 0.85);
        ofTranslate(3, 0, 197);
        US.drawCities();
    ofPopMatrix();

    camera.end();
    results.draw();
    parameter.draw();
    dataStruct.draw();
    gui.draw();
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
 
  
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){


}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void Line::drawLine(float x, float y, float z, float x2, float y2, float z2) {
    ofPolyline line;
    ofVec3f start(x, y, z);
    ofVec3f end(x2, y2, z2);
    line.addVertex(start);
    line.addVertex(end);
    line.draw();
    line.clear();
}
void USMesh::setup(void) {
    USmesh.load("USMeshFLAT.ply");
    USmesh.setMode(OF_PRIMITIVE_TRIANGLES);
    USmesh.enableColors();
    
 

}
void USMesh::draw(void) {
    ofPushMatrix();
        ofSetColor(00, 00, 0x80); //Navy Blue
        ofScale(10, 0, 10);
        ofFill();
        USmesh.draw();
    ofPopMatrix();

}
void USMesh::addCity(std::string name, float lat, float lon,float parameter){
    Vertex tempVertex;
    tempVertex.name = name;
    tempVertex.x = lat;
    tempVertex.y = parameter;
    tempVertex.z = lon;
    if (usingOrderedmap) {
        
        orderedMap[name] = tempVertex;
        
    }
    else {
        unorderedMap[name] = tempVertex;
    }
    if (parameter > maxParameter) {
        maxParameter = parameter;
    }

}
void USMesh::drawCities(){
    //Middle of the US is 39.50 N 98.35 W, but for our mesh this is 0,0, so we have to subtract that.
    Line line;
    ofSetColor(255, 0, 0);
    ofFill();
    if (usingOrderedmap) {
       
        for (auto iter = orderedMap.begin(); iter != orderedMap.end(); iter++) {
            float linex = iter->second.x - 39.50;
            float linez = iter->second.z - 98.35;
            line.drawLine(linex, 0, linez, linex, (iter->second.y / maxParameter) * 10, linez);
        }
    }
    else {
        for (auto iter = unorderedMap.begin(); iter != unorderedMap.end(); iter++) {
            float linex = iter->second.x - 39.50;
            float linez = iter->second.z - 98.35;
            line.drawLine(linex, 0, linez, linex, (iter->second.y / maxParameter) * 10, linez);
        }
    }
}
void USMesh::printResults() {
    std::cout << "-----Rankings-----" << std::endl;
    //Using RBTree
    if (usingOrderedmap) {
        int i = 1;
        for (auto iter = orderedMap.begin(); iter != orderedMap.end() && i <= 20; iter++, i++) {
            std::cout << i << ". " << iter->first << std::endl;
        }
    
    }
    else {
    //Using a hash table
        int i = 1;
        for (auto iter = unorderedMap.begin(); iter != unorderedMap.end() && i <= 20; iter++, i++) {
            std::cout << i << ". " << iter->first << std::endl;
        }
    
    }
    




}
void USMesh::citySetup(int parameter) {
    //The parameter is the colum in the csv file after name,lat,lon. Parameter 1 = population for example.
    std::ifstream cityFile;
    cityFile.open("../bin/data/uscities.csv");
    std::string buffer;
    std::getline(cityFile, buffer); //Ignore header data

    while (cityFile.is_open()) { //Adds 1000 Cities to the map
        std::string line;
        std::getline(cityFile, line);
        if (line.size() > 0) {
            std::stringstream stream(line);
            std::string name;
           
            std::getline(stream, name, ',');
            if (name == "Newport") {
                cityFile.close();
                break;
            }
            std::string lat;
            std::getline(stream, lat, ',');
            std::string lon;
            std::getline(stream, lon, ',');
            std::string population;
            std::getline(stream, population, ',');
            std::string density;
            std::getline(stream, density, ',');
            switch (parameter) {
            case 1:
                US.addCity(name, std::stof(lat), std::stof(lon), std::stof(population));
                break;
            case 2:
                US.addCity(name, std::stof(lat), std::stof(lon), std::stof(density));
                
                break;
            case 3:
                break;
            default:
                break;
            }
        }
        else {
            cityFile.close();
        }
    }






}
void USMesh::clearCities() {
    US.maxParameter = 0;
    orderedMap.clear();
    unorderedMap.clear();

}