#include "ofApp.h"
#include <fstream>
#define originX -ofGetWidth()/2.0f
#define originY -ofGetHeight()/2.0f

//--------------------------------------------------------------
USMesh US;
void ofApp::setup(){
	//This function gets called once
    US.setup();
    std::ifstream cityFile;
    cityFile.open("../bin/data/Cities.csv");
    std::string buffer;
    std::getline(cityFile, buffer); //Ignore header data
    
    while (cityFile.is_open()) { //Adds 1000 Cities to the map
        std::string line;
        std::getline(cityFile, line);
        if (line.size() > 0) {
            std::stringstream stream(line);
            std::string name;
            std::getline(stream, name, ',');
            std::string lat;
            std::getline(stream, lat, ',');
            std::string lon;
            std::getline(stream, lon, ',');
            std::string population;
            std::getline(stream, population, ',');
            US.addCity(name, std::stof(lat), std::stof(lon),std::stof(population));
        }
        else {
            cityFile.close();
        }
    }
    ofEnableDepthTest();


}
//--------------------------------------------------------------
void ofApp::update(){
    
}

//-------------------------------------------------------------- This function will be called multiple times per second, and is where the hashMap integration will be
void ofApp::draw(){
    
    camera.begin();
    
  
    US.draw();
    
    ofPushMatrix();
        ofRotateY(90);
        ofScale(1.2,1, 0.85);
        ofTranslate(3, 0, 197);
        US.drawCities();
    ofPopMatrix();

    camera.end();
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



void ofApp::drawGrid() {
    Line line;
    //Draw Grid
    for (int i = 0; i < 10; i++) {
        if (i == 0) {
            //stroke(255, 0, 0);
        }
        else {
            //stroke(0);
        }
        line.drawLine(-100, 10 * i, 0, 100, 10 * i, 0);
        line.drawLine(-100, -10 * i, 0, 100, -10 * i, 0);

    }
    for (int j = 0; j < 10; j++) {
        if (j == 0) {
            // stroke(0, 0, 255);

        }
        else {
            // stroke(0);
        }
        line.drawLine(10 * j, -100, 0, 10 * j, 100, 0);
        line.drawLine(-10 * j, -100, 0, -10 * j, 100, 0);
    }


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
    tempVertex.x = lat;
    tempVertex.y = parameter;
    tempVertex.z = lon;
    orderedMap[name]=tempVertex;
    if (parameter > maxParameter) {
        maxParameter = parameter;
    }
}
void USMesh::drawCities(){
    //Middle of the US is 39.50 N 98.35 W, but for our mesh this is 0,0, so we have to subtract that.
    Line line;
    ofSetColor(255, 0, 0);
    ofFill();
    for (auto iter = orderedMap.begin(); iter != orderedMap.end(); iter++) {
        float linex = iter->second.x - 39.50;
        float linez = iter->second.z - 98.35;
        line.drawLine(linex,0,linez,linex, (iter->second.y/maxParameter) * 10, linez);
    }
}