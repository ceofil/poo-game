#pragma once
#include "Graphics.h"
#include "Keyboard.h"
class Face
{
public:
	void contain();
	void draw(Graphics & gfx) const;
	void Update(const Keyboard& kbd);
	void MoveRight();
	void MoveLeft();
	void MoveDown();
	void MoveUp();
	void moveto(int x2,int y2);
	int GetX()const;
	int GetY()const;
	int GetW()const;
	int GetH()const;
	void centerxy();
private:
	int x = Graphics::ScreenWidth / 2 - w/2; 
	int y= Graphics::ScreenHeight / 2 - h/2;
	int speed = 3;
	static constexpr int w = 24;
	static constexpr int h = 24;
};

