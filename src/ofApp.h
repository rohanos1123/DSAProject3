#pragma once

#include "ofMain.h"
#include <filesystem>
#include <map>
#include <iostream>
class ofApp : public ofBaseApp {

public:
	//Program Variables
	ofEasyCam camera;
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	//Debug Tools
	void drawGrid();



};
class Line {
public:
	void drawLine(float x, float y, float z, float x2, float y2, float z2);
};
struct Vertex {
	float x;
	float y;
	float z;
};

class USMesh {
private:
	std::map<std::string,Vertex> orderedMap;
	float maxParameter;
public:
	ofVboMesh USmesh; // A collection of vertices, each vertex = a city in the us, plus some other vertices to define the shape better
	
	void setup(void);
	void draw(void);
	void addCity(std::string name, float lat, float lon, float parameter);
	void USMesh::drawCities();

};
