#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetWindowTitle("RobClient");
	ofSetFrameRate(60); // run at 60 fps
	ofSetVerticalSync(true);

	// listen on the given port
	std::cout << "LISTENING : " << RECPORT << std::endl;
	receiver.setup(RECPORT);
	sender.setup(HOST, SENPORT);

	ofxOscMessage init;
	init.setAddress("/up/new");
	init.addStringArg(localPlayer.playerName);
	init.addFloatArg(ofMap(localPlayer.loc.x, 0, ofGetWidth(), 0, 1));
	init.addFloatArg(ofMap(localPlayer.loc.y, 0, ofGetHeight(), 0, 1));
	init.addFloatArg(ofMap(localPlayer.loc.z, 0, 100, 0, 1));
	init.addFloatArg(ofMap(localPlayer.size.x, 0, ofGetWidth(), 0, 1));
	init.addFloatArg(ofMap(localPlayer.size.y, 0, ofGetHeight(), 0, 1));
	init.addFloatArg(ofMap(localPlayer.size.z, 0, 100, 0, 1));
	init.addBoolArg(true);
	init.addIntArg(localPlayer.playerColor.getHue());
	sender.sendMessage(init, false);
}

//--------------------------------------------------------------
void ofApp::update(){

	ofxOscMessage upd;
	string addr = "/up/" + localPlayer.ID;
	upd.setAddress(addr);
	upd.addStringArg(localPlayer.playerName);
	upd.addFloatArg(ofMap(localPlayer.loc.x, 0, ofGetWidth(), 0, 1));
	upd.addFloatArg(ofMap(localPlayer.loc.y, 0, ofGetHeight(), 0, 1));
	upd.addFloatArg(ofMap(localPlayer.loc.z, 0, 100, 0, 1));
	upd.addFloatArg(ofMap(localPlayer.size.x, 0, ofGetWidth(), 0, 1));
	upd.addFloatArg(ofMap(localPlayer.size.y, 0, ofGetHeight(), 0, 1));
	upd.addFloatArg(ofMap(localPlayer.size.z, 0, 100, 0, 1));
	upd.addBoolArg(true);
	upd.addIntArg(localPlayer.playerColor.getHue());
	upd.addIntArg(localPlayer.ID);
	sender.sendMessage(upd, false);

	while (receiver.hasWaitingMessages()) {
		ofxOscMessage m;
		receiver.getNextMessage(m);
		//std::cout << m.getAddress() << " : " << m.getArgAsInt(0) << std::endl;

		if (m.getAddress() == "/down/new" && !initiated) {
			initiated = true;
			localPlayer.ID = m.getArgAsInt(0);
		}

		//std::cout << m.getAddress() << " : " << m.getArgAsInt(0) << std::endl;
		if (m.getAddress() == "/down" && m.getArgAsInt(0) != localPlayer.ID) {
			
			bool exists = false;
			for (int i = 0; i < players.size(); i++) {
				
				if (m.getArgAsInt(0) == players[i].ID) { // << THIS MIGHT NOT WORK
					players[i].update(
						ofVec3f(
						m.getArgAsFloat(2),
						m.getArgAsFloat(3),
						m.getArgAsFloat(4)),
						ofVec3f(
						m.getArgAsFloat(5),
						m.getArgAsFloat(6),
						m.getArgAsFloat(7)),
						m.getArgAsInt(9),
						m.getArgAsString(1)
					);

					exists = true;
				}
				
			}
			if (!exists) {
				players.push_back(
					player(
						ofVec3f(
							m.getArgAsFloat(2),
							m.getArgAsFloat(3),
							m.getArgAsFloat(4)),
						ofVec3f(
							m.getArgAsFloat(5),
							m.getArgAsFloat(6),
							m.getArgAsFloat(7)),
						m.getArgAsString(1),
						m.getArgAsInt(9),
						false,
						m.getArgAsInt(0)
					)
				);
			}
		}
		

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
				std::cout << msgString << std::endl;
			}
		
	}
	
	localPlayer.update();
	//std::cout << players.size() << std::endl;
}

//--------------------------------------------------------------
void ofApp::draw(){
	localPlayer.draw();

	for (int i = 0; i < players.size(); i++) {
		players[i].draw();
	}

	ofDrawBitmapString(localPlayer.ID,100,100);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'd') {
		localPlayer.update(ofVec3f(1, 0,0));
	}

	if (key == 's') {
		localPlayer.update(ofVec3f(0, 1,0));
	}

	if (key == 'a') {
		localPlayer.update(ofVec3f(-1, 0,0));
	}
	
	if (key == 'w') {
		localPlayer.update(ofVec3f(0, -1,0));
	}
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
