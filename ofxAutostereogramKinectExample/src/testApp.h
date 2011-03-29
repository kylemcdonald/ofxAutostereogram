#pragma once

#include "ofMain.h"

#include "ofxKinect.h"
#include "ofxAutostereogram.h"
#include "ofxAutoControlPanel.h"

class testApp : public ofBaseApp {
public:

	void setup();
	void update();
	void draw();
	void exit();

	ofxKinect kinect;

	ofxAutoControlPanel panel;

	ofImage tile, kinectDepth, sis;
};
