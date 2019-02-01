#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetWindowTitle("RobServer");
	ofSetFrameRate(60); // run at 60 fps
	ofSetVerticalSync(true);

	// listen on the given port
	std::cout << "LISTENING : " << PORT << std::endl;
	receiver.setup(PORT);
	sender.setup(HOST,PORT);
}

//--------------------------------------------------------------
void ofApp::update(){
	while (receiver.hasWaitingMessages()) {
		ofxOscMessage m;
		receiver.getNextMessage(m);

		if (m.getAddress() == "/up/new") {
			clients.push_back(
				client(		m.getArgAsString(0),
							totalConns++, //SET ID HERE
							m.getArgAsFloat(1),
							m.getArgAsFloat(2),
							m.getArgAsFloat(3),
							m.getArgAsFloat(4),
							m.getArgAsFloat(5),
							m.getArgAsFloat(6),
							m.getArgAsBool(7),
							m.getArgAsInt(8)
						)
			);

			ofxOscMessage init;
			init.setAddress("/down/new");
			init.addIntArg(clients.back().ID);
			sender.sendMessage(init, false);

		}

		//check through IDs to see if any match the most recent message and if they do update the vector with the details
		for (int i = 0; i < clients.size(); i++) {
			string addr = "/up/" + clients[i].ID;
			if (m.getAddress() == addr) { // << THIS MIGHT NOT WORK
				clients[i].update(	m.getArgAsString(0),
									m.getArgAsFloat(1),
									m.getArgAsFloat(2),
									m.getArgAsFloat(3),
									m.getArgAsFloat(4),
									m.getArgAsFloat(5),
									m.getArgAsFloat(6),
									m.getArgAsBool(7),
									m.getArgAsInt(8)
				);
			}
		}

		//SOMEWHERE IN UPDATE CHECK IF CONNECTED = FALSE and REMOVE DISCONNECTED USERS
		// it'll work without this for now

		// for every MSG, eventually only unrecognised messages
		string msgString;
		msgString = m.getAddress();
		msgString += ":";
		for (size_t i = 0; i < m.getNumArgs(); i++) {

			// get the argument type
			msgString += " ";
			msgString += m.getArgTypeName(i);
			msgString += ":";

			// display the argument - make sure we get the right type
			if (m.getArgType(i) == OFXOSC_TYPE_INT32) {
				msgString += ofToString(m.getArgAsInt32(i));
			}
			else if (m.getArgType(i) == OFXOSC_TYPE_FLOAT) {
				msgString += ofToString(m.getArgAsFloat(i));
			}
			else if (m.getArgType(i) == OFXOSC_TYPE_STRING) {
				msgString += m.getArgAsString(i);
			}
			else {
				msgString += "unhandled argument type " + m.getArgTypeName(i);
			}
			//std::cout << msgString << std::endl;
		}
	}

	ofxOscMessage ret;
	for (int i = 0; i < clients.size(); i++) {
		string addr = "/down";
		ret.setAddress(addr);
		ret.addIntArg(clients[i].ID);
		ret.addStringArg(clients[i].name);
		ret.addFloatArg(clients[i].posx);
		ret.addFloatArg(clients[i].posy);
		ret.addFloatArg(clients[i].posz);
		ret.addFloatArg(clients[i].sizex);
		ret.addFloatArg(clients[i].sizey);
		ret.addFloatArg(clients[i].sizez);
		ret.addBoolArg(clients[i].connected);
		ret.addIntArg(clients[i].hue);
	}

}

//--------------------------------------------------------------
void ofApp::draw(){
	for (int i = 0; i < clients.size(); i++) {
		ofSetColor(ofColor::fromHsb(clients[i].hue,255,255));
		ofDrawEllipse(	ofMap(clients[i].posx, 0, 1, 0, ofGetWidth()),
						ofMap(clients[i].posy, 0, 1, 0, ofGetHeight()),
						ofMap(clients[i].sizex, 0, 1, 0, ofGetWidth()),
						ofMap(clients[i].sizey, 0, 1, 0, ofGetHeight())
		);
		ofDrawBitmapString(clients[i].name, ofMap(clients[i].posx, 0, 1, 0, ofGetWidth()) + ofMap(clients[i].sizex, 0, 1, 0, ofGetWidth()) + 20, ofMap(clients[i].posy, 0, 1, 0, ofGetHeight()));
		
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
