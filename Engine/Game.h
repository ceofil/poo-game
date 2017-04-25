/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include <cmath>
#include "Poop.h"
#include "Face.h"
#include <random>
#include <fstream>


class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	
	/********************************/
	/*  User Functions              */
	void gameover(int x, int y);
	float howmanpoopz();

	float seglen(int x1, int y1, int x2, int y2);
	void drawCircle(int x, int y, int r);

	void drawEmptyCircle(int x, int y, int r);

	void drawrect(int x, int y, int w, int h,Color c);

	void drawemptyrect(int x, int y, int w, int h, Color c);

	void trackpoop(int target);

	void choosetarget(int range);

	void nonrecursiontrack();

	void recursiontry(int x1, int y1, int x2, int y2);

	void drawline(int x1, int y1, int x2, int y2);

	
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */


	std::random_device rd;
	std::mt19937 rng;
	std::uniform_int_distribution<int> xrange;
	std::uniform_int_distribution<int> yrange;
	std::uniform_int_distribution<int> vrange;
	static constexpr int n = 100;

	Face face;

	bool gameisover = false;
	int target = 1;
	Poop poopz[n];
	int previoustarget = 1;
	int range = 10;
	bool breakrange = false;
	int centerx = gfx.ScreenWidth / 2;
	int centery = gfx.ScreenHeight / 2;
	int currentcadran = 1;
	Color c1 = Colors::Blue;
	Color c2 = Colors::Blue;
	Color c3 = Colors::Blue;
	Color c4 = Colors::Blue;

	
	/********************************/
};


