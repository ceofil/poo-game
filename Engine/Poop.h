#pragma once
#include "Graphics.h"
#include "Face.h"
class Poop
{
public:
	void initialize(int xin, int yin, int vxin, int vyin);
	void Update();
	void eatingProcess(Face& face);
	bool colliding(Face& face, int range);
	void draw(Graphics & gfx) const;
	bool isEaten() const;
	void setEaten(bool b);
	int getx();
	int gety();
	int getvx();
	int getvy();
private:
	int x;
	int y;
	int vx;
	int vy;
	static constexpr int w = 24;
	static constexpr int h = 24;
	bool eat=true;
};