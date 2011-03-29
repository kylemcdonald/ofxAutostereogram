#include "testApp.h"
#include "ofAppGlutWindow.h"

int main() {
	ofAppGlutWindow window;
	ofSetupOpenGL(&window, 873, 427, OF_WINDOW);
	ofRunApp(new testApp());
}
