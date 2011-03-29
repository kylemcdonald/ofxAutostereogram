#include "testApp.h"

void testApp::setup(){
	tile.loadImage("tile.png");
	tile.resize(128, 128);
	 
	depth.loadImage("shark.png");
	depth.setImageType(OF_IMAGE_GRAYSCALE);
	sis.allocate(depth.getWidth() + tile.getWidth(), depth.getHeight(), OF_IMAGE_COLOR);
}

void testApp::update(){
}

void testApp::draw(){
	ofBackground(0);
	float depthMultiplier = .2;
	if(ofGetMousePressed()) {
		depthMultiplier = ofMap(mouseX, 0, ofGetWidth(), 0, +1);
	}
	ofxAutostereogram::makeAutostereogram(tile, depth, depthMultiplier, sis);
	ofSetColor(255);
	sis.update();
	sis.draw(0, 0);
	
	ofSetColor(0);
	ofRect(5, 5, 35, 25);
	ofSetColor(255);
	ofDrawBitmapString(ofToString((int) ofGetFrameRate()), 10, 20);
	ofDrawBitmapString("Click and hold to change the depth multiplier.", 10, 40);
}
