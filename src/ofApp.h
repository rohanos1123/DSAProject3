#pragma once

#include "ofMain.h"
#include "Hashmap.h"
#include "RBTree.h"
#include "Vertex.h"
#include <filesystem>
#include <map>
#include <iostream>
#include "ofxGui.h"
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
	ofxGuiGroup gui;
	ofxButton results;
	ofxButton parameter;
	ofxButton dataStruct;




};
class Line {
public:
	void drawLine(float x, float y, float z, float x2, float y2, float z2);
};


class USMesh {
private:

	float maxParameter;
public:
	// Map goes here
	// unordered_map_imp<std::string, Vertex> unordered_map;
	// ordered_map<Vertex, std::string> ordered_map;
	RBTree<Vertex> *ordered_map = new RBTree<Vertex>;
	Hashmap<Vertex> *hashmap = new Hashmap<Vertex>;
	std::map<std::string, Vertex> orderedMap;
	std::unordered_map<std::string, Vertex> unorderedMap;
	bool usingOrderedmap = false;
	ofVboMesh USmesh; // A collection of vertices, each vertex = a city in the us, plus some other vertices to define the shape better
	void setup(void);
	void draw(void);
	void addCity(std::string name, float lat, float lon, float parameter);
	void clearCities();
	void drawCities();
	void printResults();
	void citySetup(int parameter);
};