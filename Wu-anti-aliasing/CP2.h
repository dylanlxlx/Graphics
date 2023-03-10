#pragma once
class CP2 {
public:
	CP2() {};
	virtual ~CP2() {};
	CP2(int x, int y) {
		this->x = x;
		this->y = y;
	};
public:
	int x;
	int y;
};