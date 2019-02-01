#pragma once
#include "ofMain.h"


class client {
	public:
		string name;
		int ID;
		float posx;
		float posy;
		float posz;
		float sizex;
		float sizey;
		float sizez;
		bool connected;
		int timesSentDisConnected;
		int hue;

		client(			string _name,
						int _ID,
						float _posx,
						float _posy,
						float _posz,
						float _sizex,
						float _sizey,
						float _sizez,
						bool _connected,
						int _hue
		);

		void update(string _name,
			float _posx,
			float _posy,
			float _posz,
			float _sizex,
			float _sizey,
			float _sizez,
			bool _connected,
			int _hue
		);
};