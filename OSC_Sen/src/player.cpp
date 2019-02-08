#include "player.h"

player::player(ofVec3f _loc, bool _local, string _playerName) {
	loc = _loc;
	local = _local;
	playerColor.setHsb(ofRandom(255), 255, 255);
	size = ofVec3f(100, 100, 100);
	playerName = _playerName;
}

player::player(ofVec3f _loc, ofVec3f _size, string _playerName, int _hue, bool _local, int _ID) {
	loc = _loc;
	size = _size;
	playerName = _playerName;
	playerColor.setHsb(_hue, 255, 255);
	local = _local;
	ID = _ID;
}

void player::update() {
	vel += acc;
	loc += vel;
	vel += 0.01*-vel;
}


void player::update(ofVec3f _vel) {
	if (local) {
		vel += _vel;
		vel += acc;
		loc += vel;
		vel += 0.01*-vel;
	}
	else {
		loc = _vel;
	}
}

void player::update(ofVec3f _loc, ofVec3f _size, int _hue, string _playerName) {
	loc = _loc;
	size = _size;
	playerColor.setHsb(_hue, 255, 255);
	playerName = _playerName;
} 

void player::draw() {
	ofSetColor(playerColor);
	ofDrawRectangle(loc, size.x, size.y);
	ofPushMatrix();
	ofTranslate(loc);
	ofTranslate(size.x + 20, 0, 0);
	ofDrawBitmapString(playerName, 0, 0);
	ofPopMatrix();
}
