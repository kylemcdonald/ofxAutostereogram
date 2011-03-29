#include "testApp.h"

void testApp::setup() {
	kinect.init();
	kinect.setVerbose(true);
	kinect.open();
	
	tile.loadImage("tile.png");
	tile.resize(128, 128);
	sis.allocate(640 + 128, 480, OF_IMAGE_COLOR);
	kinectDepth.allocate(640, 480, OF_IMAGE_GRAYSCALE);
}

void testApp::update() {
	ofBackground(128, 128, 128);
	kinect.update();
	
	memcpy(kinectDepth.getPixels(), kinect.getDepthPixels(), 640 * 480);
	kinectDepth.update();
	
	float depthMultiplier = (float) mouseX / ofGetWidth();
	ofxAutostereogram::makeAutostereogram(tile, kinectDepth, depthMultiplier, sis);
	sis.update();
}

void testApp::draw() {
	ofSetColor(255);
	
	kinectDepth.draw(128, 0);
	sis.draw(0, 480);
	
	ofDrawBitmapString(ofToString((int) ofGetFrameRate()), 10, 20);
}

void testApp::exit(){
	kinect.close();
}

void testApp::keyPressed (int key) {
}

void testApp::mouseMoved(int x, int y) {}

void testApp::mouseDragged(int x, int y, int button) {
	ofxKinectCalibration::setClippingInCentimeters(mouseX, mouseY);
}

void testApp::mousePressed(int x, int y, int button) {
	mouseDragged(x, y, button);
}

void testApp::mouseReleased(int x, int y, int button) {}

void testApp::windowResized(int w, int h) {}

