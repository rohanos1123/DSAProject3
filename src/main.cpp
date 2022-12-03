#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
	ofSetupOpenGL(1000,1000,OF_WINDOW);			// <-------- setup the GL context
	ofSetWindowTitle("Topography Map");

	// this kicks off the running of my app
	ofRunApp(new ofApp());

}
