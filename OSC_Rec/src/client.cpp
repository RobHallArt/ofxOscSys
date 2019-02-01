#include "client.h"



client::client(string _name,
	int _ID,
	float _posx,
	float _posy,
	float _posz,
	float _sizex,
	float _sizey,
	float _sizez,
	bool _connected,
	int _hue
) {
	name = _name;
	ID = _ID;
	posx = _posx;
	posy = _posy;
	posz = _posz;
	sizex = _sizex;
	sizey = _sizey;
	sizez = _sizez;
	connected = _connected;
	hue = _hue;
}

void client::update(string _name,
	float _posx,
	float _posy,
	float _posz,
	float _sizex,
	float _sizey,
	float _sizez,
	bool _connected,
	int _hue
) {
	name = _name;
	posx = _posx;
	posy = _posy;
	posz = _posz;
	sizex = _sizex;
	sizey = _sizey;
	sizez = _sizez;
	connected = _connected;
	hue = _hue;
}