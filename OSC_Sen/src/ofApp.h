#pragma once

#include "ofMain.h"
#include "player.h"
#include "ofxOsc.h"

// send host (aka ip address)
#define HOST "localhost"

// send port
#define PORT 12345


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		bool initiated = false;

		ofxOscReceiver receiver;
		ofxOscSender sender;
		vector<player> players;
		
		string name = "Player " + ofToString(ofRandom(0, 100));

		player localPlayer{ ofVec2f(100,100) , true, name};
		
};
