#include "ofMain.h"
#include "testApp.h"
#include "ofAppGlutWindow.h"

int main() {
	ofAppGlutWindow window;
	ofSetupOpenGL(&window, 640 + 250, 480 * 2, OF_WINDOW);
	ofRunApp(new testApp());
}
