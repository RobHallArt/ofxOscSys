#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "client.h"

// listening port
#define SENPORT 12345
#define RECPORT 12346

// send host (aka ip address)
#define HOST "localhost"

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
		int totalConns = 100;
		
		ofxOscSenderSettings senset;

		ofxOscReceiver receiver;
		ofxOscSender sender;
		vector<client> clients;
};
