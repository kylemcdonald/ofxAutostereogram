#include "testApp.h"

void testApp::setup() {
	ofSetVerticalSync(true);

	panel.setup("Control Panel", 0, 0, 250, 480 - 20);
	panel.addPanel("Controls");
	panel.addSlider("Depth Multiplier", "depthMultiplier", .2, 0, 1);
	panel.addSlider("Near Clipping", "nearClipping", 50, 20, 400);
	panel.addSlider("Far Clipping", "farClipping", 100, 20, 400);
	panel.addToggle("Realtime", "realtime", false);
	panel.addToggle("Snapshot", "snapshot", false);
	panel.addToggle("Export", "export", false);

	kinect.init();
	kinect.setVerbose(true);
	kinect.open();
	
	tile.loadImage("tile.png");
	tile.resize(128, 128);
	sis.allocate(640 + 128, 480, OF_IMAGE_COLOR);
	kinectDepth.allocate(640, 480, OF_IMAGE_GRAYSCALE);
}

#include "Poco/DateTimeFormatter.h"
void testApp::update() {
	bool newMultiplier = panel.hasValueChanged("depthMultiplier");

	if(panel.hasValueChanged("nearClipping") || panel.hasValueChanged("farClipping")) {
		ofxKinectCalibration::setClippingInCentimeters(
			panel.getValueF("nearClipping"),
			panel.getValueF("farClipping"));
	}
	
	kinect.update();
	
	memcpy(kinectDepth.getPixels(), kinect.getDepthPixels(), 640 * 480);
	kinectDepth.update();
			
	if(panel.getValueB("realtime") || panel.getValueB("snapshot") || newMultiplier) {
		float depthMultiplier = (float) mouseX / ofGetWidth();
		ofxAutostereogram::makeAutostereogram(tile, kinectDepth, panel.getValueF("depthMultiplier"), sis);
		sis.update();
		panel.setValueB("snapshot", false);
	}
	
	if(panel.getValueB("export")) {
		string pocoTime = Poco::DateTimeFormatter::format(Poco::LocalDateTime(), "%Y-%m-%d at %H.%M.%S");
		sis.saveImage("Autostereogram Export " + pocoTime + ".png");
		panel.setValueB("export", false);
	}
	
	panel.clearAllChanged();
}

void testApp::draw() {
	ofBackground(128);
	
	ofSetColor(255);
	
	ofPushMatrix();
	ofTranslate(250 - 128, 0);
	kinectDepth.draw(128, 0);
	sis.draw(0, 480);
	ofPopMatrix();
}

void testApp::exit(){
	kinect.close();
}


