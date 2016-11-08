#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
	ofSetWindowShape(1280, 1080);

	// init gui
	gui.setup();
	gui.add(showDepth.setup("show depth", false));
	gui.add(threshold.setup("threshold", 127, 0, 255));
	
	
	// init kinect
	kinect.setRegistration(true);
	kinect.init();
	kinect.open();
	
	// init edge detection tools
	colorImage.allocate(kinect.width, kinect.height);
	grayImage.allocate(kinect.width, kinect.height);
}

//--------------------------------------------------------------
void ofApp::update(){
	
	kinect.update();
	
	if (kinect.isFrameNew()) {
		
		// load grayscale depth image from the kinect source
		grayImage.setFromPixels(kinect.getDepthPixels());
		
		// apply threshold filter
		grayImage.threshold(threshold);
		
		// contour detection using opencv
		grayImage.flagImageChanged();
		contourFinder.findContours(grayImage, 100, (kinect.width*kinect.height)/2, 20, false);
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	ofClear(0);
	
	if (showDepth) {
		ofPushMatrix();
		
		ofTranslate(300, 0);
		kinect.drawDepth(0, 0, kinect.width, kinect.height);
		
		ofTranslate(0, kinect.height);
		grayImage.draw(0, 0);
		contourFinder.draw(0, 0);
		
		ofPopMatrix();
	}
	
	int numCopy = 5;
	for (int i = 0; i < numCopy; i++) {
		
		float t = (float)i / numCopy;
		ofColor c = ofColor(0).getLerped(ofColor(255), t);
		ofSetColor(c);
		
		for (auto& blob : contourFinder.blobs) {
			line.clear();
			line.addVertices(blob.pts);
			line.close();
			line.getSmoothed(i * 8.0).draw();
		}
	}
	
	gui.draw();
}
