#include "ofApp.h"
#define originX -ofGetWidth()/2.0f
#define originY -ofGetHeight()/2.0f
//--------------------------------------------------------------
USMesh US; //
ofSpherePrimitive sphere;
Line debug = Line();
void ofApp::setup(){
	//This function gets called once
    float lat = 25.7617;
    float lon = 80.1918; // Miami
    US.setup();
    US.addCity(lat, lon);


}
//--------------------------------------------------------------
void ofApp::update(){

}

//-------------------------------------------------------------- This function will be called multiple times per second, and is where the hashMap integration will be
void ofApp::draw(){
    
    camera.begin();
    ofSetColor(255, 0, 0);
    ofFill();
   
    US.draw();
    sphere.draw();
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
    //USmesh.setupIndicesAuto();
 

}
void USMesh::draw(void) {
    ofPushMatrix();
        ofSetColor(00, 00, 0x80); //Navy Blue
        ofFill();
        ofScale(20, 0, 20);
        USmesh.draw();
    ofPopMatrix();

}
void USMesh::addCity(float lat, float lon){
    sphere.setRadius(2.0f);
    sphere.setPosition((lat -39.50)/20.0f, 10, (lon-98.35)/20.0f);

    //Middle of the US is 39.50 N 98.35 W, but for our mesh this is 0,0, so we have to subtract that.
}