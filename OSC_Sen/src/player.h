#pragma once
#include "ofMain.h"

class player {
	public:
		ofVec3f loc;
		ofVec3f vel;
		ofVec3f acc;
		ofVec3f size;
		ofColor playerColor;
		bool local;
		string playerName;
		int ID;

		player(ofVec3f _loc, bool _local, string _playerName);
		void update();
		void update(ofVec3f _loc, ofVec3f _size, ofColor playerColor);
		void update(ofVec3f _vel);
		void draw();

		// make player setup func for other clients
		//make update simmilarly

};