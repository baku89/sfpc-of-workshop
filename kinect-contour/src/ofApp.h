#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxKinect.h"
#include "ofxOpenCv.h"

class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();
	
	// gui
	ofxPanel gui;
	ofxFloatSlider threshold;
	ofxToggle showDepth;
	
	// kinect
	ofxKinect kinect;
	
	// edge detection
	ofxCvColorImage colorImage;
	ofxCvGrayscaleImage grayImage;
	
	ofxCvContourFinder contourFinder;
	
	// polyline
	ofPolyline line;
};
