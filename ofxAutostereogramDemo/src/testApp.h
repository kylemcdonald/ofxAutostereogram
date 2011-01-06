#pragma once

#include "ofMain.h"
#include "ofxAutostereogram.h"

class testApp : public ofBaseApp{
public:
	void setup();
	void update();
	void draw();
	
	ofImage tile, depth, sis;
};
