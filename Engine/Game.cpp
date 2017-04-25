/******************************************************************************************
 *	Chili DirectX Framework Version 16.07.20											  *
 *	Game.cpp																			  *
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
#include "MainWindow.h"
#include "Game.h"
#include <cmath>
#include <random>

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	rng(rd()),
	xrange(0, gfx.ScreenWidth - 30),
	yrange(0, gfx.ScreenHeight - 30),
	vrange(-1, 1)
{
	for (int i = 0; i < n; i++) {
		int vex = vrange(rng);
		if (vex == 0) vex = 1;
		int vey = vrange(rng);
		if (vey == 0) vey = 1;
		poopz[i].initialize(xrange(rng), yrange(rng), vex, vey);
	}
}

void Game::Go()
{
	gfx.BeginFrame();
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{

	if (wnd.kbd.KeyIsPressed(VK_ESCAPE)) {
		gameisover = true;
	}
	if (!gameisover)
	{









		if (!(wnd.kbd.KeyIsPressed(VK_UP) ||
			wnd.kbd.KeyIsPressed(VK_DOWN) ||
			wnd.kbd.KeyIsPressed(VK_LEFT) ||
			wnd.kbd.KeyIsPressed(VK_RIGHT)
			))
		{
			if (poopz[target].isEaten() == true) 
			{
				if (range <= 100) {
					range += 3;
				}
				nonrecursiontrack();
				choosetarget(range);
			}
			else 
			{

				choosetarget(range);
				if (range > 6) {
					range -=3;
				}
				trackpoop(target);
			}


			
		}


		face.Update(wnd.kbd);


		for (int i = 0; i < n; i++) {
			poopz[i].eatingProcess(face);
			poopz[i].Update();
		}



		face.contain();
		if (face.GetX() < 50 && face.GetY() < 50) {
			poopz[target].setEaten(true);
		}

		if (!gameisover) {
			gameisover = poopz[0].isEaten();
			for (int i = 1; i < n; i++) {
				gameisover = gameisover && poopz[i].isEaten();
			}
		}

	}

	else {
		if (wnd.kbd.KeyIsPressed(VK_RETURN)) {
			gameisover = false;
			for (int i = 0; i < n; i++) {
				poopz[i].setEaten(false);
			}
		}
	}
}



void Game::ComposeFrame()
{
	

	if (!gameisover) {

		//target stuff//
		{
			//vision range
			drawCircle(face.GetX() + 10, face.GetY() + 10, range);



			//visualize target
			if (poopz[target].isEaten() == false) {
				drawemptyrect(poopz[target].getx() + 12, poopz[target].gety() + 12, 30, 30, Colors::Yellow);
			}
		}

		
		face.draw(gfx);

		//draw poopz
		for (int i = 0; i < n; i++) {
			if (!poopz[i].isEaten()) {
				poopz[i].draw(gfx);
			}
		}

		//progress
		{
			const int howmany = howmanpoopz() + 25;
			for (int i = 25; i <= howmany; i++) {
				for (int j = 25; j <= 35; j++) {
					gfx.PutPixel(i, j, Colors::Green);
				}
			}
		}


	}
	else {
		{
			for (int i = 25; i <= Graphics::ScreenWidth-25; i++) {
				for (int j = 25; j <= 35; j++) {
					gfx.PutPixel(i, j, Colors::Green);
				}
			}
		}
		face.centerxy();
		gameover(358, 268);
	}
	
	//draw vertical lines
	{
		for (int i = 25; i < Graphics::ScreenWidth; i += 75){
			for (int j = 15; j <= 45; j++) {
				gfx.PutPixel(i, j, Colors::Green);
			}
		}
	}


	
}







void Game::gameover(int x, int y)
{
	gfx.PutPixel(49 + x, 0 + y, 0, 146, 14);
	gfx.PutPixel(50 + x, 0 + y, 0, 146, 14);
	gfx.PutPixel(51 + x, 0 + y, 0, 146, 14);
	gfx.PutPixel(49 + x, 1 + y, 0, 146, 14);
	gfx.PutPixel(50 + x, 1 + y, 0, 146, 14);
	gfx.PutPixel(51 + x, 1 + y, 0, 146, 14);
	gfx.PutPixel(52 + x, 1 + y, 0, 146, 14);
	gfx.PutPixel(38 + x, 2 + y, 0, 146, 14);
	gfx.PutPixel(39 + x, 2 + y, 0, 146, 14);
	gfx.PutPixel(40 + x, 2 + y, 0, 146, 14);
	gfx.PutPixel(41 + x, 2 + y, 0, 146, 14);
	gfx.PutPixel(50 + x, 2 + y, 0, 146, 14);
	gfx.PutPixel(51 + x, 2 + y, 0, 146, 14);
	gfx.PutPixel(52 + x, 2 + y, 0, 146, 14);
	gfx.PutPixel(36 + x, 3 + y, 0, 146, 14);
	gfx.PutPixel(37 + x, 3 + y, 0, 146, 14);
	gfx.PutPixel(38 + x, 3 + y, 0, 146, 14);
	gfx.PutPixel(39 + x, 3 + y, 0, 146, 14);
	gfx.PutPixel(40 + x, 3 + y, 0, 146, 14);
	gfx.PutPixel(41 + x, 3 + y, 0, 146, 14);
	gfx.PutPixel(42 + x, 3 + y, 0, 146, 14);
	gfx.PutPixel(43 + x, 3 + y, 0, 146, 14);
	gfx.PutPixel(50 + x, 3 + y, 0, 146, 14);
	gfx.PutPixel(51 + x, 3 + y, 0, 146, 14);
	gfx.PutPixel(52 + x, 3 + y, 0, 146, 14);
	gfx.PutPixel(53 + x, 3 + y, 0, 146, 14);
	gfx.PutPixel(35 + x, 4 + y, 0, 146, 14);
	gfx.PutPixel(36 + x, 4 + y, 0, 146, 14);
	gfx.PutPixel(37 + x, 4 + y, 0, 146, 14);
	gfx.PutPixel(38 + x, 4 + y, 0, 146, 14);
	gfx.PutPixel(39 + x, 4 + y, 0, 146, 14);
	gfx.PutPixel(40 + x, 4 + y, 0, 146, 14);
	gfx.PutPixel(41 + x, 4 + y, 0, 146, 14);
	gfx.PutPixel(42 + x, 4 + y, 0, 146, 14);
	gfx.PutPixel(43 + x, 4 + y, 0, 146, 14);
	gfx.PutPixel(44 + x, 4 + y, 0, 146, 14);
	gfx.PutPixel(51 + x, 4 + y, 0, 146, 14);
	gfx.PutPixel(52 + x, 4 + y, 0, 146, 14);
	gfx.PutPixel(53 + x, 4 + y, 0, 146, 14);
	gfx.PutPixel(68 + x, 4 + y, 0, 146, 14);
	gfx.PutPixel(69 + x, 4 + y, 0, 146, 14);
	gfx.PutPixel(70 + x, 4 + y, 0, 146, 14);
	gfx.PutPixel(71 + x, 4 + y, 0, 146, 14);
	gfx.PutPixel(72 + x, 4 + y, 0, 146, 14);
	gfx.PutPixel(73 + x, 4 + y, 0, 146, 14);
	gfx.PutPixel(74 + x, 4 + y, 0, 146, 14);
	gfx.PutPixel(75 + x, 4 + y, 0, 146, 14);
	gfx.PutPixel(76 + x, 4 + y, 0, 146, 14);
	gfx.PutPixel(77 + x, 4 + y, 0, 146, 14);
	gfx.PutPixel(78 + x, 4 + y, 0, 146, 14);
	gfx.PutPixel(79 + x, 4 + y, 0, 146, 14);
	gfx.PutPixel(34 + x, 5 + y, 0, 118, 11);
	gfx.PutPixel(35 + x, 5 + y, 0, 146, 14);
	gfx.PutPixel(36 + x, 5 + y, 0, 146, 14);
	gfx.PutPixel(37 + x, 5 + y, 0, 146, 14);
	gfx.PutPixel(38 + x, 5 + y, 0, 146, 14);
	gfx.PutPixel(39 + x, 5 + y, 0, 146, 14);
	gfx.PutPixel(40 + x, 5 + y, 0, 146, 14);
	gfx.PutPixel(41 + x, 5 + y, 0, 146, 14);
	gfx.PutPixel(42 + x, 5 + y, 0, 146, 14);
	gfx.PutPixel(43 + x, 5 + y, 0, 146, 14);
	gfx.PutPixel(44 + x, 5 + y, 0, 146, 14);
	gfx.PutPixel(51 + x, 5 + y, 0, 142, 13);
	gfx.PutPixel(52 + x, 5 + y, 0, 146, 14);
	gfx.PutPixel(53 + x, 5 + y, 0, 146, 14);
	gfx.PutPixel(54 + x, 5 + y, 0, 146, 14);
	gfx.PutPixel(66 + x, 5 + y, 0, 146, 14);
	gfx.PutPixel(67 + x, 5 + y, 0, 146, 14);
	gfx.PutPixel(68 + x, 5 + y, 0, 146, 14);
	gfx.PutPixel(69 + x, 5 + y, 0, 146, 14);
	gfx.PutPixel(70 + x, 5 + y, 0, 146, 14);
	gfx.PutPixel(71 + x, 5 + y, 0, 146, 14);
	gfx.PutPixel(72 + x, 5 + y, 0, 146, 14);
	gfx.PutPixel(73 + x, 5 + y, 0, 146, 14);
	gfx.PutPixel(74 + x, 5 + y, 0, 146, 14);
	gfx.PutPixel(75 + x, 5 + y, 0, 146, 14);
	gfx.PutPixel(76 + x, 5 + y, 0, 146, 14);
	gfx.PutPixel(77 + x, 5 + y, 0, 146, 14);
	gfx.PutPixel(78 + x, 5 + y, 0, 146, 14);
	gfx.PutPixel(79 + x, 5 + y, 0, 146, 14);
	gfx.PutPixel(80 + x, 5 + y, 0, 146, 14);
	gfx.PutPixel(34 + x, 6 + y, 0, 146, 14);
	gfx.PutPixel(35 + x, 6 + y, 0, 146, 14);
	gfx.PutPixel(36 + x, 6 + y, 0, 146, 14);
	gfx.PutPixel(37 + x, 6 + y, 0, 146, 14);
	gfx.PutPixel(38 + x, 6 + y, 0, 146, 14);
	gfx.PutPixel(39 + x, 6 + y, 0, 146, 14);
	gfx.PutPixel(40 + x, 6 + y, 0, 146, 14);
	gfx.PutPixel(41 + x, 6 + y, 0, 146, 14);
	gfx.PutPixel(42 + x, 6 + y, 0, 146, 14);
	gfx.PutPixel(43 + x, 6 + y, 0, 146, 14);
	gfx.PutPixel(44 + x, 6 + y, 0, 146, 14);
	gfx.PutPixel(45 + x, 6 + y, 0, 146, 14);
	gfx.PutPixel(52 + x, 6 + y, 0, 146, 14);
	gfx.PutPixel(53 + x, 6 + y, 0, 146, 14);
	gfx.PutPixel(54 + x, 6 + y, 0, 146, 14);
	gfx.PutPixel(55 + x, 6 + y, 0, 146, 14);
	gfx.PutPixel(65 + x, 6 + y, 0, 146, 14);
	gfx.PutPixel(66 + x, 6 + y, 0, 146, 14);
	gfx.PutPixel(67 + x, 6 + y, 0, 146, 14);
	gfx.PutPixel(68 + x, 6 + y, 0, 146, 14);
	gfx.PutPixel(69 + x, 6 + y, 0, 146, 14);
	gfx.PutPixel(70 + x, 6 + y, 0, 146, 14);
	gfx.PutPixel(71 + x, 6 + y, 0, 146, 14);
	gfx.PutPixel(72 + x, 6 + y, 0, 146, 14);
	gfx.PutPixel(73 + x, 6 + y, 0, 146, 14);
	gfx.PutPixel(74 + x, 6 + y, 0, 146, 14);
	gfx.PutPixel(75 + x, 6 + y, 0, 146, 14);
	gfx.PutPixel(76 + x, 6 + y, 0, 146, 14);
	gfx.PutPixel(77 + x, 6 + y, 0, 146, 14);
	gfx.PutPixel(78 + x, 6 + y, 0, 146, 14);
	gfx.PutPixel(79 + x, 6 + y, 0, 146, 14);
	gfx.PutPixel(80 + x, 6 + y, 0, 146, 14);
	gfx.PutPixel(81 + x, 6 + y, 0, 146, 14);
	gfx.PutPixel(34 + x, 7 + y, 0, 146, 14);
	gfx.PutPixel(35 + x, 7 + y, 0, 146, 14);
	gfx.PutPixel(36 + x, 7 + y, 0, 146, 14);
	gfx.PutPixel(37 + x, 7 + y, 0, 146, 14);
	gfx.PutPixel(38 + x, 7 + y, 0, 146, 14);
	gfx.PutPixel(39 + x, 7 + y, 0, 146, 14);
	gfx.PutPixel(40 + x, 7 + y, 0, 146, 14);
	gfx.PutPixel(41 + x, 7 + y, 0, 146, 14);
	gfx.PutPixel(42 + x, 7 + y, 0, 146, 14);
	gfx.PutPixel(43 + x, 7 + y, 0, 146, 14);
	gfx.PutPixel(44 + x, 7 + y, 0, 146, 14);
	gfx.PutPixel(45 + x, 7 + y, 0, 146, 14);
	gfx.PutPixel(53 + x, 7 + y, 0, 146, 14);
	gfx.PutPixel(54 + x, 7 + y, 0, 146, 14);
	gfx.PutPixel(55 + x, 7 + y, 0, 146, 14);
	gfx.PutPixel(65 + x, 7 + y, 0, 146, 14);
	gfx.PutPixel(66 + x, 7 + y, 0, 146, 14);
	gfx.PutPixel(67 + x, 7 + y, 0, 146, 14);
	gfx.PutPixel(68 + x, 7 + y, 0, 142, 13);
	gfx.PutPixel(79 + x, 7 + y, 0, 146, 14);
	gfx.PutPixel(80 + x, 7 + y, 0, 146, 14);
	gfx.PutPixel(81 + x, 7 + y, 0, 146, 14);
	gfx.PutPixel(82 + x, 7 + y, 0, 146, 14);
	gfx.PutPixel(34 + x, 8 + y, 0, 146, 14);
	gfx.PutPixel(35 + x, 8 + y, 0, 146, 14);
	gfx.PutPixel(36 + x, 8 + y, 0, 146, 14);
	gfx.PutPixel(37 + x, 8 + y, 0, 146, 14);
	gfx.PutPixel(38 + x, 8 + y, 0, 146, 14);
	gfx.PutPixel(39 + x, 8 + y, 0, 146, 14);
	gfx.PutPixel(40 + x, 8 + y, 0, 146, 14);
	gfx.PutPixel(41 + x, 8 + y, 0, 146, 14);
	gfx.PutPixel(42 + x, 8 + y, 0, 146, 14);
	gfx.PutPixel(43 + x, 8 + y, 0, 146, 14);
	gfx.PutPixel(44 + x, 8 + y, 0, 146, 14);
	gfx.PutPixel(45 + x, 8 + y, 0, 146, 14);
	gfx.PutPixel(53 + x, 8 + y, 0, 146, 14);
	gfx.PutPixel(54 + x, 8 + y, 0, 146, 14);
	gfx.PutPixel(55 + x, 8 + y, 0, 146, 14);
	gfx.PutPixel(56 + x, 8 + y, 0, 146, 14);
	gfx.PutPixel(64 + x, 8 + y, 0, 146, 14);
	gfx.PutPixel(65 + x, 8 + y, 0, 146, 14);
	gfx.PutPixel(66 + x, 8 + y, 0, 146, 14);
	gfx.PutPixel(67 + x, 8 + y, 0, 146, 14);
	gfx.PutPixel(80 + x, 8 + y, 0, 146, 14);
	gfx.PutPixel(81 + x, 8 + y, 0, 146, 14);
	gfx.PutPixel(82 + x, 8 + y, 0, 146, 14);
	gfx.PutPixel(34 + x, 9 + y, 0, 146, 14);
	gfx.PutPixel(35 + x, 9 + y, 0, 146, 14);
	gfx.PutPixel(36 + x, 9 + y, 0, 146, 14);
	gfx.PutPixel(37 + x, 9 + y, 0, 146, 14);
	gfx.PutPixel(38 + x, 9 + y, 0, 146, 14);
	gfx.PutPixel(39 + x, 9 + y, 0, 146, 14);
	gfx.PutPixel(40 + x, 9 + y, 0, 146, 14);
	gfx.PutPixel(41 + x, 9 + y, 0, 146, 14);
	gfx.PutPixel(42 + x, 9 + y, 0, 146, 14);
	gfx.PutPixel(43 + x, 9 + y, 0, 146, 14);
	gfx.PutPixel(44 + x, 9 + y, 0, 146, 14);
	gfx.PutPixel(45 + x, 9 + y, 0, 146, 14);
	gfx.PutPixel(54 + x, 9 + y, 0, 146, 14);
	gfx.PutPixel(55 + x, 9 + y, 0, 146, 14);
	gfx.PutPixel(56 + x, 9 + y, 0, 146, 14);
	gfx.PutPixel(57 + x, 9 + y, 0, 146, 14);
	gfx.PutPixel(64 + x, 9 + y, 0, 146, 14);
	gfx.PutPixel(65 + x, 9 + y, 0, 146, 14);
	gfx.PutPixel(66 + x, 9 + y, 0, 146, 14);
	gfx.PutPixel(80 + x, 9 + y, 0, 146, 14);
	gfx.PutPixel(81 + x, 9 + y, 0, 146, 14);
	gfx.PutPixel(82 + x, 9 + y, 0, 146, 14);
	gfx.PutPixel(83 + x, 9 + y, 0, 118, 11);
	gfx.PutPixel(34 + x, 10 + y, 0, 146, 14);
	gfx.PutPixel(35 + x, 10 + y, 0, 146, 14);
	gfx.PutPixel(36 + x, 10 + y, 0, 146, 14);
	gfx.PutPixel(37 + x, 10 + y, 0, 146, 14);
	gfx.PutPixel(38 + x, 10 + y, 0, 146, 14);
	gfx.PutPixel(39 + x, 10 + y, 0, 146, 14);
	gfx.PutPixel(40 + x, 10 + y, 0, 146, 14);
	gfx.PutPixel(41 + x, 10 + y, 0, 146, 14);
	gfx.PutPixel(42 + x, 10 + y, 0, 146, 14);
	gfx.PutPixel(43 + x, 10 + y, 0, 146, 14);
	gfx.PutPixel(44 + x, 10 + y, 0, 146, 14);
	gfx.PutPixel(45 + x, 10 + y, 0, 146, 14);
	gfx.PutPixel(55 + x, 10 + y, 0, 146, 14);
	gfx.PutPixel(56 + x, 10 + y, 0, 146, 14);
	gfx.PutPixel(57 + x, 10 + y, 0, 146, 14);
	gfx.PutPixel(64 + x, 10 + y, 0, 146, 14);
	gfx.PutPixel(65 + x, 10 + y, 0, 146, 14);
	gfx.PutPixel(66 + x, 10 + y, 0, 146, 14);
	gfx.PutPixel(81 + x, 10 + y, 0, 146, 14);
	gfx.PutPixel(82 + x, 10 + y, 0, 146, 14);
	gfx.PutPixel(83 + x, 10 + y, 0, 146, 14);
	gfx.PutPixel(28 + x, 11 + y, 0, 146, 14);
	gfx.PutPixel(29 + x, 11 + y, 0, 146, 14);
	gfx.PutPixel(30 + x, 11 + y, 0, 146, 14);
	gfx.PutPixel(31 + x, 11 + y, 0, 146, 14);
	gfx.PutPixel(32 + x, 11 + y, 0, 146, 14);
	gfx.PutPixel(35 + x, 11 + y, 0, 146, 14);
	gfx.PutPixel(36 + x, 11 + y, 0, 146, 14);
	gfx.PutPixel(37 + x, 11 + y, 0, 146, 14);
	gfx.PutPixel(38 + x, 11 + y, 0, 146, 14);
	gfx.PutPixel(39 + x, 11 + y, 0, 146, 14);
	gfx.PutPixel(40 + x, 11 + y, 0, 146, 14);
	gfx.PutPixel(41 + x, 11 + y, 0, 146, 14);
	gfx.PutPixel(42 + x, 11 + y, 0, 146, 14);
	gfx.PutPixel(43 + x, 11 + y, 0, 146, 14);
	gfx.PutPixel(44 + x, 11 + y, 0, 146, 14);
	gfx.PutPixel(55 + x, 11 + y, 0, 146, 14);
	gfx.PutPixel(56 + x, 11 + y, 0, 146, 14);
	gfx.PutPixel(57 + x, 11 + y, 0, 146, 14);
	gfx.PutPixel(58 + x, 11 + y, 0, 146, 14);
	gfx.PutPixel(64 + x, 11 + y, 0, 146, 14);
	gfx.PutPixel(65 + x, 11 + y, 0, 146, 14);
	gfx.PutPixel(66 + x, 11 + y, 0, 146, 14);
	gfx.PutPixel(81 + x, 11 + y, 0, 146, 14);
	gfx.PutPixel(82 + x, 11 + y, 0, 146, 14);
	gfx.PutPixel(83 + x, 11 + y, 0, 146, 14);
	gfx.PutPixel(27 + x, 12 + y, 0, 146, 14);
	gfx.PutPixel(28 + x, 12 + y, 0, 146, 14);
	gfx.PutPixel(29 + x, 12 + y, 0, 146, 14);
	gfx.PutPixel(30 + x, 12 + y, 0, 146, 14);
	gfx.PutPixel(31 + x, 12 + y, 0, 146, 14);
	gfx.PutPixel(32 + x, 12 + y, 0, 146, 14);
	gfx.PutPixel(33 + x, 12 + y, 0, 146, 14);
	gfx.PutPixel(35 + x, 12 + y, 0, 142, 13);
	gfx.PutPixel(36 + x, 12 + y, 0, 146, 14);
	gfx.PutPixel(37 + x, 12 + y, 0, 146, 14);
	gfx.PutPixel(38 + x, 12 + y, 0, 146, 14);
	gfx.PutPixel(39 + x, 12 + y, 0, 146, 14);
	gfx.PutPixel(40 + x, 12 + y, 0, 146, 14);
	gfx.PutPixel(41 + x, 12 + y, 0, 146, 14);
	gfx.PutPixel(42 + x, 12 + y, 0, 146, 14);
	gfx.PutPixel(43 + x, 12 + y, 0, 146, 14);
	gfx.PutPixel(56 + x, 12 + y, 0, 146, 14);
	gfx.PutPixel(57 + x, 12 + y, 0, 146, 14);
	gfx.PutPixel(58 + x, 12 + y, 0, 146, 14);
	gfx.PutPixel(64 + x, 12 + y, 0, 146, 14);
	gfx.PutPixel(65 + x, 12 + y, 0, 146, 14);
	gfx.PutPixel(66 + x, 12 + y, 0, 146, 14);
	gfx.PutPixel(67 + x, 12 + y, 0, 146, 14);
	gfx.PutPixel(68 + x, 12 + y, 0, 146, 14);
	gfx.PutPixel(69 + x, 12 + y, 0, 146, 14);
	gfx.PutPixel(70 + x, 12 + y, 0, 146, 14);
	gfx.PutPixel(71 + x, 12 + y, 0, 146, 14);
	gfx.PutPixel(72 + x, 12 + y, 0, 146, 14);
	gfx.PutPixel(73 + x, 12 + y, 0, 146, 14);
	gfx.PutPixel(74 + x, 12 + y, 0, 146, 14);
	gfx.PutPixel(75 + x, 12 + y, 0, 146, 14);
	gfx.PutPixel(76 + x, 12 + y, 0, 146, 14);
	gfx.PutPixel(77 + x, 12 + y, 0, 146, 14);
	gfx.PutPixel(78 + x, 12 + y, 0, 146, 14);
	gfx.PutPixel(79 + x, 12 + y, 0, 146, 14);
	gfx.PutPixel(80 + x, 12 + y, 0, 146, 14);
	gfx.PutPixel(81 + x, 12 + y, 0, 146, 14);
	gfx.PutPixel(82 + x, 12 + y, 0, 146, 14);
	gfx.PutPixel(83 + x, 12 + y, 0, 146, 14);
	gfx.PutPixel(26 + x, 13 + y, 0, 146, 14);
	gfx.PutPixel(27 + x, 13 + y, 0, 146, 14);
	gfx.PutPixel(28 + x, 13 + y, 0, 146, 14);
	gfx.PutPixel(29 + x, 13 + y, 0, 146, 14);
	gfx.PutPixel(30 + x, 13 + y, 0, 146, 14);
	gfx.PutPixel(31 + x, 13 + y, 0, 146, 14);
	gfx.PutPixel(32 + x, 13 + y, 0, 146, 14);
	gfx.PutPixel(33 + x, 13 + y, 0, 146, 14);
	gfx.PutPixel(34 + x, 13 + y, 0, 146, 14);
	gfx.PutPixel(37 + x, 13 + y, 0, 146, 14);
	gfx.PutPixel(38 + x, 13 + y, 0, 146, 14);
	gfx.PutPixel(39 + x, 13 + y, 0, 146, 14);
	gfx.PutPixel(40 + x, 13 + y, 0, 146, 14);
	gfx.PutPixel(41 + x, 13 + y, 0, 146, 14);
	gfx.PutPixel(42 + x, 13 + y, 0, 146, 14);
	gfx.PutPixel(56 + x, 13 + y, 0, 142, 13);
	gfx.PutPixel(57 + x, 13 + y, 0, 146, 14);
	gfx.PutPixel(58 + x, 13 + y, 0, 146, 14);
	gfx.PutPixel(59 + x, 13 + y, 0, 146, 14);
	gfx.PutPixel(64 + x, 13 + y, 0, 146, 14);
	gfx.PutPixel(65 + x, 13 + y, 0, 146, 14);
	gfx.PutPixel(66 + x, 13 + y, 0, 146, 14);
	gfx.PutPixel(67 + x, 13 + y, 0, 146, 14);
	gfx.PutPixel(68 + x, 13 + y, 0, 146, 14);
	gfx.PutPixel(69 + x, 13 + y, 0, 146, 14);
	gfx.PutPixel(70 + x, 13 + y, 0, 146, 14);
	gfx.PutPixel(71 + x, 13 + y, 0, 146, 14);
	gfx.PutPixel(72 + x, 13 + y, 0, 146, 14);
	gfx.PutPixel(73 + x, 13 + y, 0, 146, 14);
	gfx.PutPixel(74 + x, 13 + y, 0, 146, 14);
	gfx.PutPixel(75 + x, 13 + y, 0, 146, 14);
	gfx.PutPixel(76 + x, 13 + y, 0, 146, 14);
	gfx.PutPixel(77 + x, 13 + y, 0, 146, 14);
	gfx.PutPixel(78 + x, 13 + y, 0, 146, 14);
	gfx.PutPixel(79 + x, 13 + y, 0, 146, 14);
	gfx.PutPixel(80 + x, 13 + y, 0, 146, 14);
	gfx.PutPixel(81 + x, 13 + y, 0, 146, 14);
	gfx.PutPixel(82 + x, 13 + y, 0, 146, 14);
	gfx.PutPixel(83 + x, 13 + y, 0, 146, 14);
	gfx.PutPixel(25 + x, 14 + y, 0, 146, 14);
	gfx.PutPixel(26 + x, 14 + y, 0, 146, 14);
	gfx.PutPixel(27 + x, 14 + y, 0, 146, 14);
	gfx.PutPixel(28 + x, 14 + y, 0, 146, 14);
	gfx.PutPixel(29 + x, 14 + y, 0, 146, 14);
	gfx.PutPixel(30 + x, 14 + y, 0, 146, 14);
	gfx.PutPixel(31 + x, 14 + y, 0, 146, 14);
	gfx.PutPixel(32 + x, 14 + y, 0, 146, 14);
	gfx.PutPixel(33 + x, 14 + y, 0, 146, 14);
	gfx.PutPixel(34 + x, 14 + y, 0, 146, 14);
	gfx.PutPixel(57 + x, 14 + y, 0, 146, 14);
	gfx.PutPixel(58 + x, 14 + y, 0, 146, 14);
	gfx.PutPixel(59 + x, 14 + y, 0, 146, 14);
	gfx.PutPixel(60 + x, 14 + y, 0, 146, 14);
	gfx.PutPixel(64 + x, 14 + y, 0, 146, 14);
	gfx.PutPixel(65 + x, 14 + y, 0, 146, 14);
	gfx.PutPixel(66 + x, 14 + y, 0, 146, 14);
	gfx.PutPixel(67 + x, 14 + y, 0, 146, 14);
	gfx.PutPixel(68 + x, 14 + y, 0, 146, 14);
	gfx.PutPixel(69 + x, 14 + y, 0, 146, 14);
	gfx.PutPixel(70 + x, 14 + y, 0, 146, 14);
	gfx.PutPixel(71 + x, 14 + y, 0, 146, 14);
	gfx.PutPixel(72 + x, 14 + y, 0, 146, 14);
	gfx.PutPixel(73 + x, 14 + y, 0, 146, 14);
	gfx.PutPixel(74 + x, 14 + y, 0, 146, 14);
	gfx.PutPixel(75 + x, 14 + y, 0, 146, 14);
	gfx.PutPixel(76 + x, 14 + y, 0, 146, 14);
	gfx.PutPixel(77 + x, 14 + y, 0, 146, 14);
	gfx.PutPixel(78 + x, 14 + y, 0, 146, 14);
	gfx.PutPixel(79 + x, 14 + y, 0, 146, 14);
	gfx.PutPixel(80 + x, 14 + y, 0, 146, 14);
	gfx.PutPixel(81 + x, 14 + y, 0, 146, 14);
	gfx.PutPixel(82 + x, 14 + y, 0, 146, 14);
	gfx.PutPixel(83 + x, 14 + y, 0, 146, 14);
	gfx.PutPixel(24 + x, 15 + y, 0, 25, 2);
	gfx.PutPixel(25 + x, 15 + y, 0, 146, 14);
	gfx.PutPixel(26 + x, 15 + y, 0, 146, 14);
	gfx.PutPixel(27 + x, 15 + y, 0, 146, 14);
	gfx.PutPixel(28 + x, 15 + y, 0, 146, 14);
	gfx.PutPixel(29 + x, 15 + y, 0, 146, 14);
	gfx.PutPixel(30 + x, 15 + y, 0, 146, 14);
	gfx.PutPixel(31 + x, 15 + y, 0, 146, 14);
	gfx.PutPixel(32 + x, 15 + y, 0, 146, 14);
	gfx.PutPixel(33 + x, 15 + y, 0, 146, 14);
	gfx.PutPixel(34 + x, 15 + y, 0, 146, 14);
	gfx.PutPixel(58 + x, 15 + y, 0, 146, 14);
	gfx.PutPixel(59 + x, 15 + y, 0, 146, 14);
	gfx.PutPixel(60 + x, 15 + y, 0, 146, 14);
	gfx.PutPixel(64 + x, 15 + y, 0, 146, 14);
	gfx.PutPixel(65 + x, 15 + y, 0, 146, 14);
	gfx.PutPixel(66 + x, 15 + y, 0, 146, 14);
	gfx.PutPixel(81 + x, 15 + y, 0, 146, 14);
	gfx.PutPixel(82 + x, 15 + y, 0, 146, 14);
	gfx.PutPixel(83 + x, 15 + y, 0, 146, 14);
	gfx.PutPixel(24 + x, 16 + y, 0, 146, 14);
	gfx.PutPixel(25 + x, 16 + y, 0, 146, 14);
	gfx.PutPixel(26 + x, 16 + y, 0, 146, 14);
	gfx.PutPixel(27 + x, 16 + y, 0, 146, 14);
	gfx.PutPixel(28 + x, 16 + y, 0, 146, 14);
	gfx.PutPixel(29 + x, 16 + y, 0, 146, 14);
	gfx.PutPixel(30 + x, 16 + y, 0, 146, 14);
	gfx.PutPixel(31 + x, 16 + y, 0, 146, 14);
	gfx.PutPixel(32 + x, 16 + y, 0, 146, 14);
	gfx.PutPixel(33 + x, 16 + y, 0, 146, 14);
	gfx.PutPixel(34 + x, 16 + y, 0, 146, 14);
	gfx.PutPixel(58 + x, 16 + y, 0, 146, 14);
	gfx.PutPixel(59 + x, 16 + y, 0, 146, 14);
	gfx.PutPixel(60 + x, 16 + y, 0, 146, 14);
	gfx.PutPixel(61 + x, 16 + y, 0, 146, 14);
	gfx.PutPixel(64 + x, 16 + y, 0, 146, 14);
	gfx.PutPixel(65 + x, 16 + y, 0, 146, 14);
	gfx.PutPixel(66 + x, 16 + y, 0, 146, 14);
	gfx.PutPixel(81 + x, 16 + y, 0, 146, 14);
	gfx.PutPixel(82 + x, 16 + y, 0, 146, 14);
	gfx.PutPixel(83 + x, 16 + y, 0, 146, 14);
	gfx.PutPixel(23 + x, 17 + y, 0, 146, 14);
	gfx.PutPixel(24 + x, 17 + y, 0, 146, 14);
	gfx.PutPixel(25 + x, 17 + y, 0, 146, 14);
	gfx.PutPixel(26 + x, 17 + y, 0, 146, 14);
	gfx.PutPixel(27 + x, 17 + y, 0, 146, 14);
	gfx.PutPixel(28 + x, 17 + y, 0, 146, 14);
	gfx.PutPixel(29 + x, 17 + y, 0, 146, 14);
	gfx.PutPixel(30 + x, 17 + y, 0, 146, 14);
	gfx.PutPixel(31 + x, 17 + y, 0, 146, 14);
	gfx.PutPixel(32 + x, 17 + y, 0, 146, 14);
	gfx.PutPixel(33 + x, 17 + y, 0, 146, 14);
	gfx.PutPixel(34 + x, 17 + y, 0, 146, 14);
	gfx.PutPixel(59 + x, 17 + y, 0, 146, 14);
	gfx.PutPixel(60 + x, 17 + y, 0, 146, 14);
	gfx.PutPixel(61 + x, 17 + y, 0, 146, 14);
	gfx.PutPixel(62 + x, 17 + y, 0, 146, 14);
	gfx.PutPixel(64 + x, 17 + y, 0, 146, 14);
	gfx.PutPixel(65 + x, 17 + y, 0, 146, 14);
	gfx.PutPixel(66 + x, 17 + y, 0, 146, 14);
	gfx.PutPixel(81 + x, 17 + y, 0, 146, 14);
	gfx.PutPixel(82 + x, 17 + y, 0, 146, 14);
	gfx.PutPixel(83 + x, 17 + y, 0, 146, 14);
	gfx.PutPixel(22 + x, 18 + y, 0, 146, 14);
	gfx.PutPixel(23 + x, 18 + y, 0, 146, 14);
	gfx.PutPixel(24 + x, 18 + y, 0, 146, 14);
	gfx.PutPixel(25 + x, 18 + y, 0, 146, 14);
	gfx.PutPixel(26 + x, 18 + y, 0, 146, 14);
	gfx.PutPixel(27 + x, 18 + y, 0, 146, 14);
	gfx.PutPixel(28 + x, 18 + y, 0, 146, 14);
	gfx.PutPixel(29 + x, 18 + y, 0, 146, 14);
	gfx.PutPixel(30 + x, 18 + y, 0, 146, 14);
	gfx.PutPixel(31 + x, 18 + y, 0, 146, 14);
	gfx.PutPixel(32 + x, 18 + y, 0, 146, 14);
	gfx.PutPixel(33 + x, 18 + y, 0, 146, 14);
	gfx.PutPixel(34 + x, 18 + y, 0, 146, 14);
	gfx.PutPixel(60 + x, 18 + y, 0, 146, 14);
	gfx.PutPixel(61 + x, 18 + y, 0, 146, 14);
	gfx.PutPixel(62 + x, 18 + y, 0, 146, 14);
	gfx.PutPixel(64 + x, 18 + y, 0, 146, 14);
	gfx.PutPixel(65 + x, 18 + y, 0, 146, 14);
	gfx.PutPixel(66 + x, 18 + y, 0, 146, 14);
	gfx.PutPixel(81 + x, 18 + y, 0, 146, 14);
	gfx.PutPixel(82 + x, 18 + y, 0, 146, 14);
	gfx.PutPixel(83 + x, 18 + y, 0, 146, 14);
	gfx.PutPixel(21 + x, 19 + y, 0, 146, 14);
	gfx.PutPixel(22 + x, 19 + y, 0, 146, 14);
	gfx.PutPixel(23 + x, 19 + y, 0, 146, 14);
	gfx.PutPixel(24 + x, 19 + y, 0, 146, 14);
	gfx.PutPixel(25 + x, 19 + y, 0, 146, 14);
	gfx.PutPixel(26 + x, 19 + y, 0, 146, 14);
	gfx.PutPixel(27 + x, 19 + y, 0, 146, 14);
	gfx.PutPixel(28 + x, 19 + y, 0, 146, 14);
	gfx.PutPixel(29 + x, 19 + y, 0, 146, 14);
	gfx.PutPixel(30 + x, 19 + y, 0, 146, 14);
	gfx.PutPixel(31 + x, 19 + y, 0, 146, 14);
	gfx.PutPixel(32 + x, 19 + y, 0, 146, 14);
	gfx.PutPixel(33 + x, 19 + y, 0, 146, 14);
	gfx.PutPixel(34 + x, 19 + y, 0, 146, 14);
	gfx.PutPixel(60 + x, 19 + y, 0, 146, 14);
	gfx.PutPixel(61 + x, 19 + y, 0, 146, 14);
	gfx.PutPixel(62 + x, 19 + y, 0, 146, 14);
	gfx.PutPixel(63 + x, 19 + y, 0, 146, 14);
	gfx.PutPixel(64 + x, 19 + y, 0, 146, 14);
	gfx.PutPixel(65 + x, 19 + y, 0, 146, 14);
	gfx.PutPixel(66 + x, 19 + y, 0, 146, 14);
	gfx.PutPixel(81 + x, 19 + y, 0, 146, 14);
	gfx.PutPixel(82 + x, 19 + y, 0, 146, 14);
	gfx.PutPixel(83 + x, 19 + y, 0, 146, 14);
	gfx.PutPixel(20 + x, 20 + y, 0, 146, 14);
	gfx.PutPixel(21 + x, 20 + y, 0, 146, 14);
	gfx.PutPixel(22 + x, 20 + y, 0, 146, 14);
	gfx.PutPixel(23 + x, 20 + y, 0, 146, 14);
	gfx.PutPixel(24 + x, 20 + y, 0, 146, 14);
	gfx.PutPixel(25 + x, 20 + y, 0, 146, 14);
	gfx.PutPixel(26 + x, 20 + y, 0, 146, 14);
	gfx.PutPixel(27 + x, 20 + y, 0, 146, 14);
	gfx.PutPixel(28 + x, 20 + y, 0, 146, 14);
	gfx.PutPixel(29 + x, 20 + y, 0, 146, 14);
	gfx.PutPixel(30 + x, 20 + y, 0, 146, 14);
	gfx.PutPixel(31 + x, 20 + y, 0, 146, 14);
	gfx.PutPixel(32 + x, 20 + y, 0, 146, 14);
	gfx.PutPixel(33 + x, 20 + y, 0, 146, 14);
	gfx.PutPixel(34 + x, 20 + y, 0, 146, 14);
	gfx.PutPixel(61 + x, 20 + y, 0, 146, 14);
	gfx.PutPixel(62 + x, 20 + y, 0, 146, 14);
	gfx.PutPixel(63 + x, 20 + y, 0, 146, 14);
	gfx.PutPixel(64 + x, 20 + y, 0, 146, 14);
	gfx.PutPixel(65 + x, 20 + y, 0, 146, 14);
	gfx.PutPixel(66 + x, 20 + y, 0, 146, 14);
	gfx.PutPixel(81 + x, 20 + y, 0, 146, 14);
	gfx.PutPixel(82 + x, 20 + y, 0, 146, 14);
	gfx.PutPixel(83 + x, 20 + y, 0, 146, 14);
	gfx.PutPixel(19 + x, 21 + y, 0, 146, 14);
	gfx.PutPixel(20 + x, 21 + y, 0, 146, 14);
	gfx.PutPixel(21 + x, 21 + y, 0, 146, 14);
	gfx.PutPixel(22 + x, 21 + y, 0, 146, 14);
	gfx.PutPixel(23 + x, 21 + y, 0, 146, 14);
	gfx.PutPixel(24 + x, 21 + y, 0, 146, 14);
	gfx.PutPixel(25 + x, 21 + y, 0, 146, 14);
	gfx.PutPixel(26 + x, 21 + y, 0, 146, 14);
	gfx.PutPixel(27 + x, 21 + y, 0, 146, 14);
	gfx.PutPixel(28 + x, 21 + y, 0, 146, 14);
	gfx.PutPixel(29 + x, 21 + y, 0, 146, 14);
	gfx.PutPixel(30 + x, 21 + y, 0, 146, 14);
	gfx.PutPixel(31 + x, 21 + y, 0, 146, 14);
	gfx.PutPixel(32 + x, 21 + y, 0, 146, 14);
	gfx.PutPixel(33 + x, 21 + y, 0, 146, 14);
	gfx.PutPixel(34 + x, 21 + y, 0, 146, 14);
	gfx.PutPixel(61 + x, 21 + y, 0, 146, 14);
	gfx.PutPixel(62 + x, 21 + y, 0, 146, 14);
	gfx.PutPixel(63 + x, 21 + y, 0, 146, 14);
	gfx.PutPixel(64 + x, 21 + y, 0, 146, 14);
	gfx.PutPixel(65 + x, 21 + y, 0, 146, 14);
	gfx.PutPixel(66 + x, 21 + y, 0, 146, 14);
	gfx.PutPixel(81 + x, 21 + y, 0, 146, 14);
	gfx.PutPixel(82 + x, 21 + y, 0, 146, 14);
	gfx.PutPixel(83 + x, 21 + y, 0, 146, 14);
	gfx.PutPixel(18 + x, 22 + y, 0, 146, 14);
	gfx.PutPixel(19 + x, 22 + y, 0, 146, 14);
	gfx.PutPixel(20 + x, 22 + y, 0, 146, 14);
	gfx.PutPixel(21 + x, 22 + y, 0, 146, 14);
	gfx.PutPixel(22 + x, 22 + y, 0, 146, 14);
	gfx.PutPixel(23 + x, 22 + y, 0, 146, 14);
	gfx.PutPixel(24 + x, 22 + y, 0, 146, 14);
	gfx.PutPixel(25 + x, 22 + y, 0, 146, 14);
	gfx.PutPixel(26 + x, 22 + y, 0, 146, 14);
	gfx.PutPixel(27 + x, 22 + y, 0, 146, 14);
	gfx.PutPixel(28 + x, 22 + y, 0, 146, 14);
	gfx.PutPixel(29 + x, 22 + y, 0, 146, 14);
	gfx.PutPixel(30 + x, 22 + y, 0, 146, 14);
	gfx.PutPixel(31 + x, 22 + y, 0, 146, 14);
	gfx.PutPixel(32 + x, 22 + y, 0, 146, 14);
	gfx.PutPixel(33 + x, 22 + y, 0, 146, 14);
	gfx.PutPixel(34 + x, 22 + y, 0, 146, 14);
	gfx.PutPixel(35 + x, 22 + y, 0, 25, 2);
	gfx.PutPixel(62 + x, 22 + y, 0, 146, 14);
	gfx.PutPixel(63 + x, 22 + y, 0, 146, 14);
	gfx.PutPixel(64 + x, 22 + y, 0, 146, 14);
	gfx.PutPixel(65 + x, 22 + y, 0, 146, 14);
	gfx.PutPixel(66 + x, 22 + y, 0, 146, 14);
	gfx.PutPixel(81 + x, 22 + y, 0, 146, 14);
	gfx.PutPixel(82 + x, 22 + y, 0, 146, 14);
	gfx.PutPixel(83 + x, 22 + y, 0, 146, 14);
	gfx.PutPixel(17 + x, 23 + y, 0, 3, 0);
	gfx.PutPixel(18 + x, 23 + y, 0, 146, 14);
	gfx.PutPixel(19 + x, 23 + y, 0, 146, 14);
	gfx.PutPixel(20 + x, 23 + y, 0, 146, 14);
	gfx.PutPixel(21 + x, 23 + y, 0, 146, 14);
	gfx.PutPixel(22 + x, 23 + y, 0, 146, 14);
	gfx.PutPixel(23 + x, 23 + y, 0, 146, 14);
	gfx.PutPixel(24 + x, 23 + y, 0, 146, 14);
	gfx.PutPixel(25 + x, 23 + y, 0, 146, 14);
	gfx.PutPixel(26 + x, 23 + y, 0, 146, 14);
	gfx.PutPixel(27 + x, 23 + y, 0, 146, 14);
	gfx.PutPixel(28 + x, 23 + y, 0, 146, 14);
	gfx.PutPixel(30 + x, 23 + y, 0, 146, 14);
	gfx.PutPixel(31 + x, 23 + y, 0, 146, 14);
	gfx.PutPixel(32 + x, 23 + y, 0, 146, 14);
	gfx.PutPixel(33 + x, 23 + y, 0, 146, 14);
	gfx.PutPixel(34 + x, 23 + y, 0, 146, 14);
	gfx.PutPixel(35 + x, 23 + y, 0, 25, 2);
	gfx.PutPixel(63 + x, 23 + y, 0, 146, 14);
	gfx.PutPixel(64 + x, 23 + y, 0, 146, 14);
	gfx.PutPixel(65 + x, 23 + y, 0, 146, 14);
	gfx.PutPixel(66 + x, 23 + y, 0, 146, 14);
	gfx.PutPixel(81 + x, 23 + y, 0, 146, 14);
	gfx.PutPixel(82 + x, 23 + y, 0, 146, 14);
	gfx.PutPixel(83 + x, 23 + y, 0, 146, 14);
	gfx.PutPixel(17 + x, 24 + y, 0, 146, 14);
	gfx.PutPixel(18 + x, 24 + y, 0, 146, 14);
	gfx.PutPixel(19 + x, 24 + y, 0, 146, 14);
	gfx.PutPixel(20 + x, 24 + y, 0, 146, 14);
	gfx.PutPixel(21 + x, 24 + y, 0, 146, 14);
	gfx.PutPixel(22 + x, 24 + y, 0, 146, 14);
	gfx.PutPixel(23 + x, 24 + y, 0, 146, 14);
	gfx.PutPixel(24 + x, 24 + y, 0, 146, 14);
	gfx.PutPixel(25 + x, 24 + y, 0, 146, 14);
	gfx.PutPixel(26 + x, 24 + y, 0, 146, 14);
	gfx.PutPixel(27 + x, 24 + y, 0, 146, 14);
	gfx.PutPixel(30 + x, 24 + y, 0, 146, 14);
	gfx.PutPixel(31 + x, 24 + y, 0, 146, 14);
	gfx.PutPixel(32 + x, 24 + y, 0, 146, 14);
	gfx.PutPixel(33 + x, 24 + y, 0, 146, 14);
	gfx.PutPixel(34 + x, 24 + y, 0, 146, 14);
	gfx.PutPixel(35 + x, 24 + y, 0, 146, 14);
	gfx.PutPixel(36 + x, 24 + y, 0, 146, 14);
	gfx.PutPixel(37 + x, 24 + y, 0, 146, 14);
	gfx.PutPixel(38 + x, 24 + y, 0, 146, 14);
	gfx.PutPixel(39 + x, 24 + y, 0, 146, 14);
	gfx.PutPixel(40 + x, 24 + y, 0, 146, 14);
	gfx.PutPixel(41 + x, 24 + y, 0, 146, 14);
	gfx.PutPixel(42 + x, 24 + y, 0, 146, 14);
	gfx.PutPixel(43 + x, 24 + y, 0, 146, 14);
	gfx.PutPixel(44 + x, 24 + y, 0, 146, 14);
	gfx.PutPixel(45 + x, 24 + y, 0, 146, 14);
	gfx.PutPixel(46 + x, 24 + y, 0, 146, 14);
	gfx.PutPixel(47 + x, 24 + y, 0, 146, 14);
	gfx.PutPixel(48 + x, 24 + y, 0, 146, 14);
	gfx.PutPixel(49 + x, 24 + y, 0, 146, 14);
	gfx.PutPixel(50 + x, 24 + y, 0, 146, 14);
	gfx.PutPixel(51 + x, 24 + y, 0, 146, 14);
	gfx.PutPixel(52 + x, 24 + y, 0, 146, 14);
	gfx.PutPixel(53 + x, 24 + y, 0, 146, 14);
	gfx.PutPixel(54 + x, 24 + y, 0, 146, 14);
	gfx.PutPixel(55 + x, 24 + y, 0, 146, 14);
	gfx.PutPixel(56 + x, 24 + y, 0, 146, 14);
	gfx.PutPixel(57 + x, 24 + y, 0, 146, 14);
	gfx.PutPixel(58 + x, 24 + y, 0, 146, 14);
	gfx.PutPixel(59 + x, 24 + y, 0, 146, 14);
	gfx.PutPixel(60 + x, 24 + y, 0, 146, 14);
	gfx.PutPixel(61 + x, 24 + y, 0, 146, 14);
	gfx.PutPixel(62 + x, 24 + y, 0, 146, 14);
	gfx.PutPixel(63 + x, 24 + y, 0, 146, 14);
	gfx.PutPixel(64 + x, 24 + y, 0, 146, 14);
	gfx.PutPixel(65 + x, 24 + y, 0, 146, 14);
	gfx.PutPixel(66 + x, 24 + y, 0, 146, 14);
	gfx.PutPixel(81 + x, 24 + y, 0, 146, 14);
	gfx.PutPixel(82 + x, 24 + y, 0, 146, 14);
	gfx.PutPixel(83 + x, 24 + y, 0, 146, 14);
	gfx.PutPixel(16 + x, 25 + y, 0, 146, 14);
	gfx.PutPixel(17 + x, 25 + y, 0, 146, 14);
	gfx.PutPixel(18 + x, 25 + y, 0, 146, 14);
	gfx.PutPixel(19 + x, 25 + y, 0, 146, 14);
	gfx.PutPixel(20 + x, 25 + y, 0, 146, 14);
	gfx.PutPixel(21 + x, 25 + y, 0, 146, 14);
	gfx.PutPixel(22 + x, 25 + y, 0, 146, 14);
	gfx.PutPixel(23 + x, 25 + y, 0, 146, 14);
	gfx.PutPixel(24 + x, 25 + y, 0, 146, 14);
	gfx.PutPixel(25 + x, 25 + y, 0, 146, 14);
	gfx.PutPixel(26 + x, 25 + y, 0, 146, 14);
	gfx.PutPixel(30 + x, 25 + y, 0, 146, 14);
	gfx.PutPixel(31 + x, 25 + y, 0, 146, 14);
	gfx.PutPixel(32 + x, 25 + y, 0, 146, 14);
	gfx.PutPixel(33 + x, 25 + y, 0, 146, 14);
	gfx.PutPixel(34 + x, 25 + y, 0, 146, 14);
	gfx.PutPixel(35 + x, 25 + y, 0, 146, 14);
	gfx.PutPixel(36 + x, 25 + y, 0, 146, 14);
	gfx.PutPixel(37 + x, 25 + y, 0, 146, 14);
	gfx.PutPixel(38 + x, 25 + y, 0, 146, 14);
	gfx.PutPixel(39 + x, 25 + y, 0, 146, 14);
	gfx.PutPixel(40 + x, 25 + y, 0, 146, 14);
	gfx.PutPixel(41 + x, 25 + y, 0, 146, 14);
	gfx.PutPixel(42 + x, 25 + y, 0, 146, 14);
	gfx.PutPixel(43 + x, 25 + y, 0, 146, 14);
	gfx.PutPixel(44 + x, 25 + y, 0, 146, 14);
	gfx.PutPixel(45 + x, 25 + y, 0, 146, 14);
	gfx.PutPixel(46 + x, 25 + y, 0, 146, 14);
	gfx.PutPixel(47 + x, 25 + y, 0, 146, 14);
	gfx.PutPixel(48 + x, 25 + y, 0, 146, 14);
	gfx.PutPixel(49 + x, 25 + y, 0, 146, 14);
	gfx.PutPixel(50 + x, 25 + y, 0, 146, 14);
	gfx.PutPixel(51 + x, 25 + y, 0, 146, 14);
	gfx.PutPixel(52 + x, 25 + y, 0, 146, 14);
	gfx.PutPixel(53 + x, 25 + y, 0, 146, 14);
	gfx.PutPixel(54 + x, 25 + y, 0, 146, 14);
	gfx.PutPixel(55 + x, 25 + y, 0, 146, 14);
	gfx.PutPixel(56 + x, 25 + y, 0, 146, 14);
	gfx.PutPixel(57 + x, 25 + y, 0, 146, 14);
	gfx.PutPixel(58 + x, 25 + y, 0, 146, 14);
	gfx.PutPixel(59 + x, 25 + y, 0, 146, 14);
	gfx.PutPixel(60 + x, 25 + y, 0, 146, 14);
	gfx.PutPixel(61 + x, 25 + y, 0, 146, 14);
	gfx.PutPixel(62 + x, 25 + y, 0, 146, 14);
	gfx.PutPixel(63 + x, 25 + y, 0, 146, 14);
	gfx.PutPixel(64 + x, 25 + y, 0, 146, 14);
	gfx.PutPixel(65 + x, 25 + y, 0, 146, 14);
	gfx.PutPixel(66 + x, 25 + y, 0, 146, 14);
	gfx.PutPixel(81 + x, 25 + y, 0, 146, 14);
	gfx.PutPixel(82 + x, 25 + y, 0, 146, 14);
	gfx.PutPixel(83 + x, 25 + y, 0, 146, 14);
	gfx.PutPixel(15 + x, 26 + y, 0, 146, 14);
	gfx.PutPixel(16 + x, 26 + y, 0, 146, 14);
	gfx.PutPixel(17 + x, 26 + y, 0, 146, 14);
	gfx.PutPixel(18 + x, 26 + y, 0, 146, 14);
	gfx.PutPixel(19 + x, 26 + y, 0, 146, 14);
	gfx.PutPixel(20 + x, 26 + y, 0, 146, 14);
	gfx.PutPixel(21 + x, 26 + y, 0, 146, 14);
	gfx.PutPixel(22 + x, 26 + y, 0, 146, 14);
	gfx.PutPixel(23 + x, 26 + y, 0, 146, 14);
	gfx.PutPixel(24 + x, 26 + y, 0, 146, 14);
	gfx.PutPixel(25 + x, 26 + y, 0, 146, 14);
	gfx.PutPixel(30 + x, 26 + y, 0, 146, 14);
	gfx.PutPixel(31 + x, 26 + y, 0, 146, 14);
	gfx.PutPixel(32 + x, 26 + y, 0, 146, 14);
	gfx.PutPixel(33 + x, 26 + y, 0, 146, 14);
	gfx.PutPixel(34 + x, 26 + y, 0, 146, 14);
	gfx.PutPixel(35 + x, 26 + y, 0, 146, 14);
	gfx.PutPixel(36 + x, 26 + y, 0, 146, 14);
	gfx.PutPixel(37 + x, 26 + y, 0, 146, 14);
	gfx.PutPixel(38 + x, 26 + y, 0, 146, 14);
	gfx.PutPixel(39 + x, 26 + y, 0, 146, 14);
	gfx.PutPixel(40 + x, 26 + y, 0, 146, 14);
	gfx.PutPixel(41 + x, 26 + y, 0, 146, 14);
	gfx.PutPixel(42 + x, 26 + y, 0, 146, 14);
	gfx.PutPixel(43 + x, 26 + y, 0, 146, 14);
	gfx.PutPixel(44 + x, 26 + y, 0, 146, 14);
	gfx.PutPixel(45 + x, 26 + y, 0, 146, 14);
	gfx.PutPixel(46 + x, 26 + y, 0, 146, 14);
	gfx.PutPixel(47 + x, 26 + y, 0, 146, 14);
	gfx.PutPixel(48 + x, 26 + y, 0, 146, 14);
	gfx.PutPixel(49 + x, 26 + y, 0, 146, 14);
	gfx.PutPixel(50 + x, 26 + y, 0, 146, 14);
	gfx.PutPixel(51 + x, 26 + y, 0, 146, 14);
	gfx.PutPixel(52 + x, 26 + y, 0, 146, 14);
	gfx.PutPixel(53 + x, 26 + y, 0, 146, 14);
	gfx.PutPixel(54 + x, 26 + y, 0, 146, 14);
	gfx.PutPixel(55 + x, 26 + y, 0, 146, 14);
	gfx.PutPixel(56 + x, 26 + y, 0, 146, 14);
	gfx.PutPixel(57 + x, 26 + y, 0, 146, 14);
	gfx.PutPixel(58 + x, 26 + y, 0, 146, 14);
	gfx.PutPixel(59 + x, 26 + y, 0, 146, 14);
	gfx.PutPixel(60 + x, 26 + y, 0, 146, 14);
	gfx.PutPixel(61 + x, 26 + y, 0, 146, 14);
	gfx.PutPixel(62 + x, 26 + y, 0, 146, 14);
	gfx.PutPixel(63 + x, 26 + y, 0, 146, 14);
	gfx.PutPixel(64 + x, 26 + y, 0, 146, 14);
	gfx.PutPixel(65 + x, 26 + y, 0, 146, 14);
	gfx.PutPixel(66 + x, 26 + y, 0, 146, 14);
	gfx.PutPixel(81 + x, 26 + y, 0, 146, 14);
	gfx.PutPixel(82 + x, 26 + y, 0, 146, 14);
	gfx.PutPixel(83 + x, 26 + y, 0, 146, 14);
	gfx.PutPixel(14 + x, 27 + y, 0, 146, 14);
	gfx.PutPixel(15 + x, 27 + y, 0, 146, 14);
	gfx.PutPixel(16 + x, 27 + y, 0, 146, 14);
	gfx.PutPixel(17 + x, 27 + y, 0, 146, 14);
	gfx.PutPixel(18 + x, 27 + y, 0, 146, 14);
	gfx.PutPixel(19 + x, 27 + y, 0, 146, 14);
	gfx.PutPixel(20 + x, 27 + y, 0, 146, 14);
	gfx.PutPixel(21 + x, 27 + y, 0, 146, 14);
	gfx.PutPixel(22 + x, 27 + y, 0, 146, 14);
	gfx.PutPixel(23 + x, 27 + y, 0, 146, 14);
	gfx.PutPixel(24 + x, 27 + y, 0, 146, 14);
	gfx.PutPixel(30 + x, 27 + y, 0, 146, 14);
	gfx.PutPixel(31 + x, 27 + y, 0, 146, 14);
	gfx.PutPixel(32 + x, 27 + y, 0, 146, 14);
	gfx.PutPixel(33 + x, 27 + y, 0, 146, 14);
	gfx.PutPixel(34 + x, 27 + y, 0, 146, 14);
	gfx.PutPixel(35 + x, 27 + y, 0, 146, 14);
	gfx.PutPixel(36 + x, 27 + y, 0, 146, 14);
	gfx.PutPixel(37 + x, 27 + y, 0, 146, 14);
	gfx.PutPixel(38 + x, 27 + y, 0, 146, 14);
	gfx.PutPixel(39 + x, 27 + y, 0, 146, 14);
	gfx.PutPixel(40 + x, 27 + y, 0, 146, 14);
	gfx.PutPixel(41 + x, 27 + y, 0, 146, 14);
	gfx.PutPixel(42 + x, 27 + y, 0, 146, 14);
	gfx.PutPixel(43 + x, 27 + y, 0, 146, 14);
	gfx.PutPixel(44 + x, 27 + y, 0, 146, 14);
	gfx.PutPixel(45 + x, 27 + y, 0, 146, 14);
	gfx.PutPixel(46 + x, 27 + y, 0, 146, 14);
	gfx.PutPixel(64 + x, 27 + y, 0, 146, 14);
	gfx.PutPixel(65 + x, 27 + y, 0, 146, 14);
	gfx.PutPixel(66 + x, 27 + y, 0, 146, 14);
	gfx.PutPixel(81 + x, 27 + y, 0, 146, 14);
	gfx.PutPixel(82 + x, 27 + y, 0, 146, 14);
	gfx.PutPixel(83 + x, 27 + y, 0, 146, 14);
	gfx.PutPixel(13 + x, 28 + y, 0, 146, 14);
	gfx.PutPixel(14 + x, 28 + y, 0, 146, 14);
	gfx.PutPixel(15 + x, 28 + y, 0, 146, 14);
	gfx.PutPixel(16 + x, 28 + y, 0, 146, 14);
	gfx.PutPixel(17 + x, 28 + y, 0, 146, 14);
	gfx.PutPixel(18 + x, 28 + y, 0, 146, 14);
	gfx.PutPixel(19 + x, 28 + y, 0, 146, 14);
	gfx.PutPixel(20 + x, 28 + y, 0, 146, 14);
	gfx.PutPixel(21 + x, 28 + y, 0, 146, 14);
	gfx.PutPixel(22 + x, 28 + y, 0, 146, 14);
	gfx.PutPixel(23 + x, 28 + y, 0, 146, 14);
	gfx.PutPixel(30 + x, 28 + y, 0, 146, 14);
	gfx.PutPixel(31 + x, 28 + y, 0, 146, 14);
	gfx.PutPixel(32 + x, 28 + y, 0, 146, 14);
	gfx.PutPixel(33 + x, 28 + y, 0, 146, 14);
	gfx.PutPixel(34 + x, 28 + y, 0, 146, 14);
	gfx.PutPixel(35 + x, 28 + y, 0, 146, 14);
	gfx.PutPixel(36 + x, 28 + y, 0, 146, 14);
	gfx.PutPixel(37 + x, 28 + y, 0, 146, 14);
	gfx.PutPixel(38 + x, 28 + y, 0, 146, 14);
	gfx.PutPixel(39 + x, 28 + y, 0, 146, 14);
	gfx.PutPixel(40 + x, 28 + y, 0, 146, 14);
	gfx.PutPixel(41 + x, 28 + y, 0, 146, 14);
	gfx.PutPixel(42 + x, 28 + y, 0, 146, 14);
	gfx.PutPixel(43 + x, 28 + y, 0, 146, 14);
	gfx.PutPixel(44 + x, 28 + y, 0, 146, 14);
	gfx.PutPixel(45 + x, 28 + y, 0, 146, 14);
	gfx.PutPixel(46 + x, 28 + y, 0, 146, 14);
	gfx.PutPixel(47 + x, 28 + y, 0, 146, 14);
	gfx.PutPixel(64 + x, 28 + y, 0, 146, 14);
	gfx.PutPixel(65 + x, 28 + y, 0, 146, 14);
	gfx.PutPixel(66 + x, 28 + y, 0, 146, 14);
	gfx.PutPixel(81 + x, 28 + y, 0, 146, 14);
	gfx.PutPixel(82 + x, 28 + y, 0, 146, 14);
	gfx.PutPixel(83 + x, 28 + y, 0, 146, 14);
	gfx.PutPixel(12 + x, 29 + y, 0, 146, 14);
	gfx.PutPixel(13 + x, 29 + y, 0, 146, 14);
	gfx.PutPixel(14 + x, 29 + y, 0, 146, 14);
	gfx.PutPixel(15 + x, 29 + y, 0, 146, 14);
	gfx.PutPixel(16 + x, 29 + y, 0, 146, 14);
	gfx.PutPixel(17 + x, 29 + y, 0, 146, 14);
	gfx.PutPixel(18 + x, 29 + y, 0, 146, 14);
	gfx.PutPixel(19 + x, 29 + y, 0, 146, 14);
	gfx.PutPixel(20 + x, 29 + y, 0, 146, 14);
	gfx.PutPixel(21 + x, 29 + y, 0, 146, 14);
	gfx.PutPixel(22 + x, 29 + y, 0, 146, 14);
	gfx.PutPixel(23 + x, 29 + y, 0, 146, 14);
	gfx.PutPixel(30 + x, 29 + y, 0, 146, 14);
	gfx.PutPixel(31 + x, 29 + y, 0, 146, 14);
	gfx.PutPixel(32 + x, 29 + y, 0, 146, 14);
	gfx.PutPixel(33 + x, 29 + y, 0, 146, 14);
	gfx.PutPixel(34 + x, 29 + y, 0, 146, 14);
	gfx.PutPixel(35 + x, 29 + y, 0, 146, 14);
	gfx.PutPixel(36 + x, 29 + y, 0, 146, 14);
	gfx.PutPixel(37 + x, 29 + y, 0, 146, 14);
	gfx.PutPixel(38 + x, 29 + y, 0, 146, 14);
	gfx.PutPixel(39 + x, 29 + y, 0, 146, 14);
	gfx.PutPixel(40 + x, 29 + y, 0, 146, 14);
	gfx.PutPixel(41 + x, 29 + y, 0, 146, 14);
	gfx.PutPixel(42 + x, 29 + y, 0, 146, 14);
	gfx.PutPixel(43 + x, 29 + y, 0, 146, 14);
	gfx.PutPixel(44 + x, 29 + y, 0, 146, 14);
	gfx.PutPixel(45 + x, 29 + y, 0, 146, 14);
	gfx.PutPixel(46 + x, 29 + y, 0, 146, 14);
	gfx.PutPixel(47 + x, 29 + y, 0, 146, 14);
	gfx.PutPixel(63 + x, 29 + y, 0, 25, 2);
	gfx.PutPixel(64 + x, 29 + y, 0, 146, 14);
	gfx.PutPixel(65 + x, 29 + y, 0, 146, 14);
	gfx.PutPixel(66 + x, 29 + y, 0, 146, 14);
	gfx.PutPixel(81 + x, 29 + y, 0, 146, 14);
	gfx.PutPixel(82 + x, 29 + y, 0, 146, 14);
	gfx.PutPixel(83 + x, 29 + y, 0, 146, 14);
	gfx.PutPixel(11 + x, 30 + y, 0, 146, 14);
	gfx.PutPixel(12 + x, 30 + y, 0, 146, 14);
	gfx.PutPixel(13 + x, 30 + y, 0, 146, 14);
	gfx.PutPixel(14 + x, 30 + y, 0, 146, 14);
	gfx.PutPixel(15 + x, 30 + y, 0, 146, 14);
	gfx.PutPixel(16 + x, 30 + y, 0, 146, 14);
	gfx.PutPixel(17 + x, 30 + y, 0, 146, 14);
	gfx.PutPixel(18 + x, 30 + y, 0, 146, 14);
	gfx.PutPixel(19 + x, 30 + y, 0, 146, 14);
	gfx.PutPixel(20 + x, 30 + y, 0, 146, 14);
	gfx.PutPixel(21 + x, 30 + y, 0, 146, 14);
	gfx.PutPixel(22 + x, 30 + y, 0, 146, 14);
	gfx.PutPixel(30 + x, 30 + y, 0, 146, 14);
	gfx.PutPixel(31 + x, 30 + y, 0, 146, 14);
	gfx.PutPixel(32 + x, 30 + y, 0, 146, 14);
	gfx.PutPixel(33 + x, 30 + y, 0, 146, 14);
	gfx.PutPixel(34 + x, 30 + y, 0, 146, 14);
	gfx.PutPixel(35 + x, 30 + y, 0, 146, 14);
	gfx.PutPixel(36 + x, 30 + y, 0, 146, 14);
	gfx.PutPixel(37 + x, 30 + y, 0, 146, 14);
	gfx.PutPixel(38 + x, 30 + y, 0, 146, 14);
	gfx.PutPixel(39 + x, 30 + y, 0, 146, 14);
	gfx.PutPixel(40 + x, 30 + y, 0, 146, 14);
	gfx.PutPixel(41 + x, 30 + y, 0, 146, 14);
	gfx.PutPixel(42 + x, 30 + y, 0, 146, 14);
	gfx.PutPixel(43 + x, 30 + y, 0, 146, 14);
	gfx.PutPixel(44 + x, 30 + y, 0, 146, 14);
	gfx.PutPixel(45 + x, 30 + y, 0, 146, 14);
	gfx.PutPixel(46 + x, 30 + y, 0, 146, 14);
	gfx.PutPixel(47 + x, 30 + y, 0, 146, 14);
	gfx.PutPixel(63 + x, 30 + y, 0, 146, 14);
	gfx.PutPixel(64 + x, 30 + y, 0, 146, 14);
	gfx.PutPixel(65 + x, 30 + y, 0, 146, 14);
	gfx.PutPixel(66 + x, 30 + y, 0, 146, 14);
	gfx.PutPixel(80 + x, 30 + y, 0, 25, 2);
	gfx.PutPixel(81 + x, 30 + y, 0, 146, 14);
	gfx.PutPixel(82 + x, 30 + y, 0, 146, 14);
	gfx.PutPixel(83 + x, 30 + y, 0, 146, 14);
	gfx.PutPixel(10 + x, 31 + y, 0, 70, 6);
	gfx.PutPixel(11 + x, 31 + y, 0, 146, 14);
	gfx.PutPixel(12 + x, 31 + y, 0, 146, 14);
	gfx.PutPixel(13 + x, 31 + y, 0, 146, 14);
	gfx.PutPixel(14 + x, 31 + y, 0, 146, 14);
	gfx.PutPixel(15 + x, 31 + y, 0, 146, 14);
	gfx.PutPixel(16 + x, 31 + y, 0, 146, 14);
	gfx.PutPixel(17 + x, 31 + y, 0, 146, 14);
	gfx.PutPixel(18 + x, 31 + y, 0, 146, 14);
	gfx.PutPixel(19 + x, 31 + y, 0, 146, 14);
	gfx.PutPixel(20 + x, 31 + y, 0, 146, 14);
	gfx.PutPixel(21 + x, 31 + y, 0, 146, 14);
	gfx.PutPixel(30 + x, 31 + y, 0, 146, 14);
	gfx.PutPixel(31 + x, 31 + y, 0, 146, 14);
	gfx.PutPixel(32 + x, 31 + y, 0, 146, 14);
	gfx.PutPixel(33 + x, 31 + y, 0, 146, 14);
	gfx.PutPixel(34 + x, 31 + y, 0, 146, 14);
	gfx.PutPixel(35 + x, 31 + y, 0, 146, 14);
	gfx.PutPixel(36 + x, 31 + y, 0, 146, 14);
	gfx.PutPixel(37 + x, 31 + y, 0, 146, 14);
	gfx.PutPixel(38 + x, 31 + y, 0, 146, 14);
	gfx.PutPixel(39 + x, 31 + y, 0, 146, 14);
	gfx.PutPixel(40 + x, 31 + y, 0, 146, 14);
	gfx.PutPixel(41 + x, 31 + y, 0, 146, 14);
	gfx.PutPixel(42 + x, 31 + y, 0, 146, 14);
	gfx.PutPixel(43 + x, 31 + y, 0, 146, 14);
	gfx.PutPixel(44 + x, 31 + y, 0, 146, 14);
	gfx.PutPixel(45 + x, 31 + y, 0, 146, 14);
	gfx.PutPixel(46 + x, 31 + y, 0, 146, 14);
	gfx.PutPixel(47 + x, 31 + y, 0, 146, 14);
	gfx.PutPixel(63 + x, 31 + y, 0, 146, 14);
	gfx.PutPixel(64 + x, 31 + y, 0, 146, 14);
	gfx.PutPixel(65 + x, 31 + y, 0, 146, 14);
	gfx.PutPixel(66 + x, 31 + y, 0, 146, 14);
	gfx.PutPixel(67 + x, 31 + y, 0, 146, 14);
	gfx.PutPixel(80 + x, 31 + y, 0, 146, 14);
	gfx.PutPixel(81 + x, 31 + y, 0, 146, 14);
	gfx.PutPixel(82 + x, 31 + y, 0, 146, 14);
	gfx.PutPixel(10 + x, 32 + y, 0, 146, 14);
	gfx.PutPixel(11 + x, 32 + y, 0, 146, 14);
	gfx.PutPixel(12 + x, 32 + y, 0, 146, 14);
	gfx.PutPixel(13 + x, 32 + y, 0, 146, 14);
	gfx.PutPixel(14 + x, 32 + y, 0, 146, 14);
	gfx.PutPixel(15 + x, 32 + y, 0, 146, 14);
	gfx.PutPixel(16 + x, 32 + y, 0, 146, 14);
	gfx.PutPixel(17 + x, 32 + y, 0, 146, 14);
	gfx.PutPixel(18 + x, 32 + y, 0, 146, 14);
	gfx.PutPixel(19 + x, 32 + y, 0, 146, 14);
	gfx.PutPixel(20 + x, 32 + y, 0, 146, 14);
	gfx.PutPixel(32 + x, 32 + y, 0, 146, 14);
	gfx.PutPixel(33 + x, 32 + y, 0, 146, 14);
	gfx.PutPixel(34 + x, 32 + y, 0, 146, 14);
	gfx.PutPixel(35 + x, 32 + y, 0, 146, 14);
	gfx.PutPixel(36 + x, 32 + y, 0, 146, 14);
	gfx.PutPixel(37 + x, 32 + y, 0, 146, 14);
	gfx.PutPixel(38 + x, 32 + y, 0, 146, 14);
	gfx.PutPixel(39 + x, 32 + y, 0, 146, 14);
	gfx.PutPixel(40 + x, 32 + y, 0, 146, 14);
	gfx.PutPixel(41 + x, 32 + y, 0, 146, 14);
	gfx.PutPixel(42 + x, 32 + y, 0, 146, 14);
	gfx.PutPixel(43 + x, 32 + y, 0, 146, 14);
	gfx.PutPixel(44 + x, 32 + y, 0, 146, 14);
	gfx.PutPixel(45 + x, 32 + y, 0, 146, 14);
	gfx.PutPixel(46 + x, 32 + y, 0, 118, 11);
	gfx.PutPixel(62 + x, 32 + y, 0, 146, 14);
	gfx.PutPixel(63 + x, 32 + y, 0, 146, 14);
	gfx.PutPixel(64 + x, 32 + y, 0, 146, 14);
	gfx.PutPixel(65 + x, 32 + y, 0, 146, 14);
	gfx.PutPixel(66 + x, 32 + y, 0, 146, 14);
	gfx.PutPixel(67 + x, 32 + y, 0, 146, 14);
	gfx.PutPixel(68 + x, 32 + y, 0, 25, 2);
	gfx.PutPixel(79 + x, 32 + y, 0, 146, 14);
	gfx.PutPixel(80 + x, 32 + y, 0, 146, 14);
	gfx.PutPixel(81 + x, 32 + y, 0, 146, 14);
	gfx.PutPixel(82 + x, 32 + y, 0, 146, 14);
	gfx.PutPixel(9 + x, 33 + y, 0, 146, 14);
	gfx.PutPixel(10 + x, 33 + y, 0, 146, 14);
	gfx.PutPixel(11 + x, 33 + y, 0, 146, 14);
	gfx.PutPixel(12 + x, 33 + y, 0, 146, 14);
	gfx.PutPixel(13 + x, 33 + y, 0, 146, 14);
	gfx.PutPixel(14 + x, 33 + y, 0, 146, 14);
	gfx.PutPixel(15 + x, 33 + y, 0, 146, 14);
	gfx.PutPixel(16 + x, 33 + y, 0, 146, 14);
	gfx.PutPixel(17 + x, 33 + y, 0, 146, 14);
	gfx.PutPixel(18 + x, 33 + y, 0, 146, 14);
	gfx.PutPixel(19 + x, 33 + y, 0, 146, 14);
	gfx.PutPixel(35 + x, 33 + y, 0, 146, 14);
	gfx.PutPixel(36 + x, 33 + y, 0, 146, 14);
	gfx.PutPixel(37 + x, 33 + y, 0, 146, 14);
	gfx.PutPixel(62 + x, 33 + y, 0, 146, 14);
	gfx.PutPixel(63 + x, 33 + y, 0, 146, 14);
	gfx.PutPixel(64 + x, 33 + y, 0, 146, 14);
	gfx.PutPixel(65 + x, 33 + y, 0, 146, 14);
	gfx.PutPixel(66 + x, 33 + y, 0, 146, 14);
	gfx.PutPixel(67 + x, 33 + y, 0, 146, 14);
	gfx.PutPixel(68 + x, 33 + y, 0, 146, 14);
	gfx.PutPixel(69 + x, 33 + y, 0, 146, 14);
	gfx.PutPixel(70 + x, 33 + y, 0, 146, 14);
	gfx.PutPixel(71 + x, 33 + y, 0, 146, 14);
	gfx.PutPixel(72 + x, 33 + y, 0, 146, 14);
	gfx.PutPixel(73 + x, 33 + y, 0, 146, 14);
	gfx.PutPixel(74 + x, 33 + y, 0, 146, 14);
	gfx.PutPixel(75 + x, 33 + y, 0, 146, 14);
	gfx.PutPixel(76 + x, 33 + y, 0, 146, 14);
	gfx.PutPixel(77 + x, 33 + y, 0, 146, 14);
	gfx.PutPixel(78 + x, 33 + y, 0, 146, 14);
	gfx.PutPixel(79 + x, 33 + y, 0, 146, 14);
	gfx.PutPixel(80 + x, 33 + y, 0, 146, 14);
	gfx.PutPixel(81 + x, 33 + y, 0, 146, 14);
	gfx.PutPixel(82 + x, 33 + y, 0, 25, 2);
	gfx.PutPixel(8 + x, 34 + y, 0, 146, 14);
	gfx.PutPixel(9 + x, 34 + y, 0, 146, 14);
	gfx.PutPixel(10 + x, 34 + y, 0, 146, 14);
	gfx.PutPixel(11 + x, 34 + y, 0, 146, 14);
	gfx.PutPixel(12 + x, 34 + y, 0, 146, 14);
	gfx.PutPixel(13 + x, 34 + y, 0, 146, 14);
	gfx.PutPixel(14 + x, 34 + y, 0, 146, 14);
	gfx.PutPixel(15 + x, 34 + y, 0, 146, 14);
	gfx.PutPixel(16 + x, 34 + y, 0, 146, 14);
	gfx.PutPixel(17 + x, 34 + y, 0, 146, 14);
	gfx.PutPixel(18 + x, 34 + y, 0, 146, 14);
	gfx.PutPixel(35 + x, 34 + y, 0, 146, 14);
	gfx.PutPixel(36 + x, 34 + y, 0, 146, 14);
	gfx.PutPixel(37 + x, 34 + y, 0, 146, 14);
	gfx.PutPixel(38 + x, 34 + y, 0, 146, 14);
	gfx.PutPixel(61 + x, 34 + y, 0, 146, 14);
	gfx.PutPixel(62 + x, 34 + y, 0, 146, 14);
	gfx.PutPixel(63 + x, 34 + y, 0, 146, 14);
	gfx.PutPixel(64 + x, 34 + y, 0, 146, 14);
	gfx.PutPixel(65 + x, 34 + y, 0, 146, 14);
	gfx.PutPixel(66 + x, 34 + y, 0, 146, 14);
	gfx.PutPixel(67 + x, 34 + y, 0, 146, 14);
	gfx.PutPixel(68 + x, 34 + y, 0, 146, 14);
	gfx.PutPixel(69 + x, 34 + y, 0, 146, 14);
	gfx.PutPixel(70 + x, 34 + y, 0, 146, 14);
	gfx.PutPixel(71 + x, 34 + y, 0, 146, 14);
	gfx.PutPixel(72 + x, 34 + y, 0, 146, 14);
	gfx.PutPixel(73 + x, 34 + y, 0, 146, 14);
	gfx.PutPixel(74 + x, 34 + y, 0, 146, 14);
	gfx.PutPixel(75 + x, 34 + y, 0, 146, 14);
	gfx.PutPixel(76 + x, 34 + y, 0, 146, 14);
	gfx.PutPixel(77 + x, 34 + y, 0, 146, 14);
	gfx.PutPixel(78 + x, 34 + y, 0, 146, 14);
	gfx.PutPixel(79 + x, 34 + y, 0, 146, 14);
	gfx.PutPixel(80 + x, 34 + y, 0, 146, 14);
	gfx.PutPixel(81 + x, 34 + y, 0, 146, 14);
	gfx.PutPixel(8 + x, 35 + y, 0, 146, 14);
	gfx.PutPixel(9 + x, 35 + y, 0, 146, 14);
	gfx.PutPixel(10 + x, 35 + y, 0, 146, 14);
	gfx.PutPixel(11 + x, 35 + y, 0, 146, 14);
	gfx.PutPixel(12 + x, 35 + y, 0, 146, 14);
	gfx.PutPixel(13 + x, 35 + y, 0, 146, 14);
	gfx.PutPixel(14 + x, 35 + y, 0, 146, 14);
	gfx.PutPixel(15 + x, 35 + y, 0, 146, 14);
	gfx.PutPixel(16 + x, 35 + y, 0, 146, 14);
	gfx.PutPixel(17 + x, 35 + y, 0, 146, 14);
	gfx.PutPixel(36 + x, 35 + y, 0, 146, 14);
	gfx.PutPixel(37 + x, 35 + y, 0, 146, 14);
	gfx.PutPixel(38 + x, 35 + y, 0, 146, 14);
	gfx.PutPixel(39 + x, 35 + y, 0, 146, 14);
	gfx.PutPixel(60 + x, 35 + y, 0, 146, 14);
	gfx.PutPixel(61 + x, 35 + y, 0, 146, 14);
	gfx.PutPixel(62 + x, 35 + y, 0, 146, 14);
	gfx.PutPixel(63 + x, 35 + y, 0, 146, 14);
	gfx.PutPixel(64 + x, 35 + y, 0, 146, 14);
	gfx.PutPixel(65 + x, 35 + y, 0, 146, 14);
	gfx.PutPixel(66 + x, 35 + y, 0, 146, 14);
	gfx.PutPixel(67 + x, 35 + y, 0, 146, 14);
	gfx.PutPixel(68 + x, 35 + y, 0, 146, 14);
	gfx.PutPixel(69 + x, 35 + y, 0, 146, 14);
	gfx.PutPixel(70 + x, 35 + y, 0, 146, 14);
	gfx.PutPixel(71 + x, 35 + y, 0, 146, 14);
	gfx.PutPixel(72 + x, 35 + y, 0, 146, 14);
	gfx.PutPixel(73 + x, 35 + y, 0, 146, 14);
	gfx.PutPixel(74 + x, 35 + y, 0, 146, 14);
	gfx.PutPixel(75 + x, 35 + y, 0, 146, 14);
	gfx.PutPixel(76 + x, 35 + y, 0, 146, 14);
	gfx.PutPixel(77 + x, 35 + y, 0, 146, 14);
	gfx.PutPixel(78 + x, 35 + y, 0, 146, 14);
	gfx.PutPixel(79 + x, 35 + y, 0, 146, 14);
	gfx.PutPixel(8 + x, 36 + y, 0, 146, 14);
	gfx.PutPixel(9 + x, 36 + y, 0, 146, 14);
	gfx.PutPixel(10 + x, 36 + y, 0, 146, 14);
	gfx.PutPixel(11 + x, 36 + y, 0, 146, 14);
	gfx.PutPixel(12 + x, 36 + y, 0, 146, 14);
	gfx.PutPixel(13 + x, 36 + y, 0, 146, 14);
	gfx.PutPixel(14 + x, 36 + y, 0, 146, 14);
	gfx.PutPixel(15 + x, 36 + y, 0, 146, 14);
	gfx.PutPixel(16 + x, 36 + y, 0, 146, 14);
	gfx.PutPixel(17 + x, 36 + y, 0, 146, 14);
	gfx.PutPixel(18 + x, 36 + y, 0, 146, 14);
	gfx.PutPixel(37 + x, 36 + y, 0, 146, 14);
	gfx.PutPixel(38 + x, 36 + y, 0, 146, 14);
	gfx.PutPixel(39 + x, 36 + y, 0, 146, 14);
	gfx.PutPixel(40 + x, 36 + y, 0, 146, 14);
	gfx.PutPixel(59 + x, 36 + y, 0, 146, 14);
	gfx.PutPixel(60 + x, 36 + y, 0, 146, 14);
	gfx.PutPixel(61 + x, 36 + y, 0, 146, 14);
	gfx.PutPixel(62 + x, 36 + y, 0, 146, 14);
	gfx.PutPixel(63 + x, 36 + y, 0, 146, 14);
	gfx.PutPixel(64 + x, 36 + y, 0, 146, 14);
	gfx.PutPixel(65 + x, 36 + y, 0, 146, 14);
	gfx.PutPixel(66 + x, 36 + y, 0, 146, 14);
	gfx.PutPixel(67 + x, 36 + y, 0, 146, 14);
	gfx.PutPixel(68 + x, 36 + y, 0, 146, 14);
	gfx.PutPixel(69 + x, 36 + y, 0, 146, 14);
	gfx.PutPixel(70 + x, 36 + y, 0, 146, 14);
	gfx.PutPixel(71 + x, 36 + y, 0, 146, 14);
	gfx.PutPixel(72 + x, 36 + y, 0, 146, 14);
	gfx.PutPixel(73 + x, 36 + y, 0, 146, 14);
	gfx.PutPixel(74 + x, 36 + y, 0, 146, 14);
	gfx.PutPixel(9 + x, 37 + y, 0, 146, 14);
	gfx.PutPixel(10 + x, 37 + y, 0, 146, 14);
	gfx.PutPixel(11 + x, 37 + y, 0, 146, 14);
	gfx.PutPixel(12 + x, 37 + y, 0, 146, 14);
	gfx.PutPixel(13 + x, 37 + y, 0, 146, 14);
	gfx.PutPixel(14 + x, 37 + y, 0, 146, 14);
	gfx.PutPixel(15 + x, 37 + y, 0, 146, 14);
	gfx.PutPixel(16 + x, 37 + y, 0, 146, 14);
	gfx.PutPixel(17 + x, 37 + y, 0, 146, 14);
	gfx.PutPixel(18 + x, 37 + y, 0, 146, 14);
	gfx.PutPixel(19 + x, 37 + y, 0, 146, 14);
	gfx.PutPixel(37 + x, 37 + y, 0, 70, 6);
	gfx.PutPixel(38 + x, 37 + y, 0, 146, 14);
	gfx.PutPixel(39 + x, 37 + y, 0, 146, 14);
	gfx.PutPixel(40 + x, 37 + y, 0, 146, 14);
	gfx.PutPixel(41 + x, 37 + y, 0, 146, 14);
	gfx.PutPixel(58 + x, 37 + y, 0, 146, 14);
	gfx.PutPixel(59 + x, 37 + y, 0, 146, 14);
	gfx.PutPixel(60 + x, 37 + y, 0, 146, 14);
	gfx.PutPixel(61 + x, 37 + y, 0, 146, 14);
	gfx.PutPixel(62 + x, 37 + y, 0, 146, 14);
	gfx.PutPixel(63 + x, 37 + y, 0, 146, 14);
	gfx.PutPixel(64 + x, 37 + y, 0, 146, 14);
	gfx.PutPixel(65 + x, 37 + y, 0, 146, 14);
	gfx.PutPixel(66 + x, 37 + y, 0, 146, 14);
	gfx.PutPixel(67 + x, 37 + y, 0, 146, 14);
	gfx.PutPixel(68 + x, 37 + y, 0, 146, 14);
	gfx.PutPixel(69 + x, 37 + y, 0, 146, 14);
	gfx.PutPixel(70 + x, 37 + y, 0, 146, 14);
	gfx.PutPixel(71 + x, 37 + y, 0, 146, 14);
	gfx.PutPixel(72 + x, 37 + y, 0, 146, 14);
	gfx.PutPixel(73 + x, 37 + y, 0, 146, 14);
	gfx.PutPixel(74 + x, 37 + y, 0, 146, 14);
	gfx.PutPixel(9 + x, 38 + y, 0, 146, 14);
	gfx.PutPixel(10 + x, 38 + y, 0, 146, 14);
	gfx.PutPixel(11 + x, 38 + y, 0, 146, 14);
	gfx.PutPixel(12 + x, 38 + y, 0, 146, 14);
	gfx.PutPixel(13 + x, 38 + y, 0, 146, 14);
	gfx.PutPixel(14 + x, 38 + y, 0, 146, 14);
	gfx.PutPixel(15 + x, 38 + y, 0, 146, 14);
	gfx.PutPixel(16 + x, 38 + y, 0, 146, 14);
	gfx.PutPixel(17 + x, 38 + y, 0, 146, 14);
	gfx.PutPixel(18 + x, 38 + y, 0, 146, 14);
	gfx.PutPixel(19 + x, 38 + y, 0, 146, 14);
	gfx.PutPixel(20 + x, 38 + y, 0, 146, 14);
	gfx.PutPixel(38 + x, 38 + y, 0, 70, 6);
	gfx.PutPixel(39 + x, 38 + y, 0, 146, 14);
	gfx.PutPixel(40 + x, 38 + y, 0, 146, 14);
	gfx.PutPixel(41 + x, 38 + y, 0, 146, 14);
	gfx.PutPixel(42 + x, 38 + y, 0, 146, 14);
	gfx.PutPixel(43 + x, 38 + y, 0, 146, 14);
	gfx.PutPixel(56 + x, 38 + y, 0, 146, 14);
	gfx.PutPixel(57 + x, 38 + y, 0, 146, 14);
	gfx.PutPixel(58 + x, 38 + y, 0, 146, 14);
	gfx.PutPixel(59 + x, 38 + y, 0, 146, 14);
	gfx.PutPixel(60 + x, 38 + y, 0, 146, 14);
	gfx.PutPixel(61 + x, 38 + y, 0, 146, 14);
	gfx.PutPixel(62 + x, 38 + y, 0, 146, 14);
	gfx.PutPixel(63 + x, 38 + y, 0, 146, 14);
	gfx.PutPixel(64 + x, 38 + y, 0, 146, 14);
	gfx.PutPixel(65 + x, 38 + y, 0, 146, 14);
	gfx.PutPixel(66 + x, 38 + y, 0, 146, 14);
	gfx.PutPixel(67 + x, 38 + y, 0, 146, 14);
	gfx.PutPixel(68 + x, 38 + y, 0, 146, 14);
	gfx.PutPixel(69 + x, 38 + y, 0, 146, 14);
	gfx.PutPixel(70 + x, 38 + y, 0, 146, 14);
	gfx.PutPixel(71 + x, 38 + y, 0, 146, 14);
	gfx.PutPixel(72 + x, 38 + y, 0, 146, 14);
	gfx.PutPixel(73 + x, 38 + y, 0, 146, 14);
	gfx.PutPixel(74 + x, 38 + y, 0, 146, 14);
	gfx.PutPixel(10 + x, 39 + y, 0, 146, 14);
	gfx.PutPixel(11 + x, 39 + y, 0, 146, 14);
	gfx.PutPixel(12 + x, 39 + y, 0, 146, 14);
	gfx.PutPixel(13 + x, 39 + y, 0, 146, 14);
	gfx.PutPixel(14 + x, 39 + y, 0, 146, 14);
	gfx.PutPixel(15 + x, 39 + y, 0, 146, 14);
	gfx.PutPixel(16 + x, 39 + y, 0, 146, 14);
	gfx.PutPixel(17 + x, 39 + y, 0, 146, 14);
	gfx.PutPixel(18 + x, 39 + y, 0, 146, 14);
	gfx.PutPixel(19 + x, 39 + y, 0, 146, 14);
	gfx.PutPixel(20 + x, 39 + y, 0, 146, 14);
	gfx.PutPixel(21 + x, 39 + y, 0, 146, 14);
	gfx.PutPixel(40 + x, 39 + y, 0, 146, 14);
	gfx.PutPixel(41 + x, 39 + y, 0, 146, 14);
	gfx.PutPixel(42 + x, 39 + y, 0, 146, 14);
	gfx.PutPixel(43 + x, 39 + y, 0, 146, 14);
	gfx.PutPixel(44 + x, 39 + y, 0, 146, 14);
	gfx.PutPixel(45 + x, 39 + y, 0, 146, 14);
	gfx.PutPixel(46 + x, 39 + y, 0, 146, 14);
	gfx.PutPixel(53 + x, 39 + y, 0, 146, 14);
	gfx.PutPixel(54 + x, 39 + y, 0, 146, 14);
	gfx.PutPixel(55 + x, 39 + y, 0, 146, 14);
	gfx.PutPixel(56 + x, 39 + y, 0, 146, 14);
	gfx.PutPixel(57 + x, 39 + y, 0, 146, 14);
	gfx.PutPixel(58 + x, 39 + y, 0, 146, 14);
	gfx.PutPixel(59 + x, 39 + y, 0, 146, 14);
	gfx.PutPixel(60 + x, 39 + y, 0, 146, 14);
	gfx.PutPixel(61 + x, 39 + y, 0, 146, 14);
	gfx.PutPixel(62 + x, 39 + y, 0, 146, 14);
	gfx.PutPixel(63 + x, 39 + y, 0, 146, 14);
	gfx.PutPixel(64 + x, 39 + y, 0, 146, 14);
	gfx.PutPixel(65 + x, 39 + y, 0, 146, 14);
	gfx.PutPixel(66 + x, 39 + y, 0, 146, 14);
	gfx.PutPixel(67 + x, 39 + y, 0, 146, 14);
	gfx.PutPixel(68 + x, 39 + y, 0, 146, 14);
	gfx.PutPixel(69 + x, 39 + y, 0, 146, 14);
	gfx.PutPixel(70 + x, 39 + y, 0, 146, 14);
	gfx.PutPixel(71 + x, 39 + y, 0, 146, 14);
	gfx.PutPixel(72 + x, 39 + y, 0, 146, 14);
	gfx.PutPixel(73 + x, 39 + y, 0, 146, 14);
	gfx.PutPixel(74 + x, 39 + y, 0, 146, 14);
	gfx.PutPixel(11 + x, 40 + y, 0, 146, 14);
	gfx.PutPixel(12 + x, 40 + y, 0, 146, 14);
	gfx.PutPixel(13 + x, 40 + y, 0, 146, 14);
	gfx.PutPixel(14 + x, 40 + y, 0, 146, 14);
	gfx.PutPixel(15 + x, 40 + y, 0, 146, 14);
	gfx.PutPixel(16 + x, 40 + y, 0, 146, 14);
	gfx.PutPixel(17 + x, 40 + y, 0, 146, 14);
	gfx.PutPixel(18 + x, 40 + y, 0, 146, 14);
	gfx.PutPixel(19 + x, 40 + y, 0, 146, 14);
	gfx.PutPixel(20 + x, 40 + y, 0, 146, 14);
	gfx.PutPixel(21 + x, 40 + y, 0, 146, 14);
	gfx.PutPixel(22 + x, 40 + y, 0, 146, 14);
	gfx.PutPixel(41 + x, 40 + y, 0, 146, 14);
	gfx.PutPixel(42 + x, 40 + y, 0, 146, 14);
	gfx.PutPixel(43 + x, 40 + y, 0, 146, 14);
	gfx.PutPixel(44 + x, 40 + y, 0, 146, 14);
	gfx.PutPixel(45 + x, 40 + y, 0, 146, 14);
	gfx.PutPixel(46 + x, 40 + y, 0, 146, 14);
	gfx.PutPixel(47 + x, 40 + y, 0, 146, 14);
	gfx.PutPixel(48 + x, 40 + y, 0, 146, 14);
	gfx.PutPixel(49 + x, 40 + y, 0, 146, 14);
	gfx.PutPixel(50 + x, 40 + y, 0, 146, 14);
	gfx.PutPixel(51 + x, 40 + y, 0, 146, 14);
	gfx.PutPixel(52 + x, 40 + y, 0, 146, 14);
	gfx.PutPixel(53 + x, 40 + y, 0, 146, 14);
	gfx.PutPixel(54 + x, 40 + y, 0, 146, 14);
	gfx.PutPixel(55 + x, 40 + y, 0, 146, 14);
	gfx.PutPixel(56 + x, 40 + y, 0, 146, 14);
	gfx.PutPixel(57 + x, 40 + y, 0, 146, 14);
	gfx.PutPixel(58 + x, 40 + y, 0, 146, 14);
	gfx.PutPixel(59 + x, 40 + y, 0, 146, 14);
	gfx.PutPixel(60 + x, 40 + y, 0, 146, 14);
	gfx.PutPixel(61 + x, 40 + y, 0, 146, 14);
	gfx.PutPixel(62 + x, 40 + y, 0, 146, 14);
	gfx.PutPixel(63 + x, 40 + y, 0, 146, 14);
	gfx.PutPixel(64 + x, 40 + y, 0, 146, 14);
	gfx.PutPixel(65 + x, 40 + y, 0, 146, 14);
	gfx.PutPixel(66 + x, 40 + y, 0, 146, 14);
	gfx.PutPixel(67 + x, 40 + y, 0, 146, 14);
	gfx.PutPixel(68 + x, 40 + y, 0, 146, 14);
	gfx.PutPixel(69 + x, 40 + y, 0, 146, 14);
	gfx.PutPixel(70 + x, 40 + y, 0, 146, 14);
	gfx.PutPixel(71 + x, 40 + y, 0, 146, 14);
	gfx.PutPixel(72 + x, 40 + y, 0, 146, 14);
	gfx.PutPixel(73 + x, 40 + y, 0, 146, 14);
	gfx.PutPixel(74 + x, 40 + y, 0, 146, 14);
	gfx.PutPixel(75 + x, 40 + y, 0, 146, 14);
	gfx.PutPixel(76 + x, 40 + y, 0, 146, 14);
	gfx.PutPixel(77 + x, 40 + y, 0, 70, 6);
	gfx.PutPixel(12 + x, 41 + y, 0, 146, 14);
	gfx.PutPixel(13 + x, 41 + y, 0, 146, 14);
	gfx.PutPixel(14 + x, 41 + y, 0, 146, 14);
	gfx.PutPixel(15 + x, 41 + y, 0, 146, 14);
	gfx.PutPixel(16 + x, 41 + y, 0, 146, 14);
	gfx.PutPixel(17 + x, 41 + y, 0, 146, 14);
	gfx.PutPixel(18 + x, 41 + y, 0, 146, 14);
	gfx.PutPixel(19 + x, 41 + y, 0, 146, 14);
	gfx.PutPixel(20 + x, 41 + y, 0, 146, 14);
	gfx.PutPixel(21 + x, 41 + y, 0, 146, 14);
	gfx.PutPixel(22 + x, 41 + y, 0, 146, 14);
	gfx.PutPixel(23 + x, 41 + y, 0, 146, 14);
	gfx.PutPixel(40 + x, 41 + y, 0, 146, 14);
	gfx.PutPixel(41 + x, 41 + y, 0, 146, 14);
	gfx.PutPixel(42 + x, 41 + y, 0, 146, 14);
	gfx.PutPixel(43 + x, 41 + y, 0, 146, 14);
	gfx.PutPixel(44 + x, 41 + y, 0, 146, 14);
	gfx.PutPixel(45 + x, 41 + y, 0, 146, 14);
	gfx.PutPixel(46 + x, 41 + y, 0, 146, 14);
	gfx.PutPixel(47 + x, 41 + y, 0, 146, 14);
	gfx.PutPixel(48 + x, 41 + y, 0, 146, 14);
	gfx.PutPixel(49 + x, 41 + y, 0, 146, 14);
	gfx.PutPixel(50 + x, 41 + y, 0, 146, 14);
	gfx.PutPixel(51 + x, 41 + y, 0, 146, 14);
	gfx.PutPixel(52 + x, 41 + y, 0, 146, 14);
	gfx.PutPixel(53 + x, 41 + y, 0, 146, 14);
	gfx.PutPixel(54 + x, 41 + y, 0, 146, 14);
	gfx.PutPixel(55 + x, 41 + y, 0, 146, 14);
	gfx.PutPixel(56 + x, 41 + y, 0, 146, 14);
	gfx.PutPixel(57 + x, 41 + y, 0, 146, 14);
	gfx.PutPixel(58 + x, 41 + y, 0, 146, 14);
	gfx.PutPixel(59 + x, 41 + y, 0, 146, 14);
	gfx.PutPixel(60 + x, 41 + y, 0, 146, 14);
	gfx.PutPixel(61 + x, 41 + y, 0, 146, 14);
	gfx.PutPixel(62 + x, 41 + y, 0, 146, 14);
	gfx.PutPixel(63 + x, 41 + y, 0, 146, 14);
	gfx.PutPixel(64 + x, 41 + y, 0, 146, 14);
	gfx.PutPixel(65 + x, 41 + y, 0, 146, 14);
	gfx.PutPixel(66 + x, 41 + y, 0, 146, 14);
	gfx.PutPixel(67 + x, 41 + y, 0, 146, 14);
	gfx.PutPixel(68 + x, 41 + y, 0, 146, 14);
	gfx.PutPixel(69 + x, 41 + y, 0, 146, 14);
	gfx.PutPixel(70 + x, 41 + y, 0, 146, 14);
	gfx.PutPixel(71 + x, 41 + y, 0, 146, 14);
	gfx.PutPixel(72 + x, 41 + y, 0, 146, 14);
	gfx.PutPixel(73 + x, 41 + y, 0, 146, 14);
	gfx.PutPixel(74 + x, 41 + y, 0, 146, 14);
	gfx.PutPixel(75 + x, 41 + y, 0, 146, 14);
	gfx.PutPixel(76 + x, 41 + y, 0, 146, 14);
	gfx.PutPixel(77 + x, 41 + y, 0, 146, 14);
	gfx.PutPixel(78 + x, 41 + y, 0, 146, 14);
	gfx.PutPixel(3 + x, 42 + y, 0, 25, 2);
	gfx.PutPixel(4 + x, 42 + y, 0, 146, 14);
	gfx.PutPixel(5 + x, 42 + y, 0, 146, 14);
	gfx.PutPixel(6 + x, 42 + y, 0, 25, 2);
	gfx.PutPixel(13 + x, 42 + y, 0, 146, 14);
	gfx.PutPixel(14 + x, 42 + y, 0, 146, 14);
	gfx.PutPixel(15 + x, 42 + y, 0, 146, 14);
	gfx.PutPixel(16 + x, 42 + y, 0, 146, 14);
	gfx.PutPixel(17 + x, 42 + y, 0, 146, 14);
	gfx.PutPixel(18 + x, 42 + y, 0, 146, 14);
	gfx.PutPixel(19 + x, 42 + y, 0, 146, 14);
	gfx.PutPixel(20 + x, 42 + y, 0, 146, 14);
	gfx.PutPixel(21 + x, 42 + y, 0, 146, 14);
	gfx.PutPixel(22 + x, 42 + y, 0, 146, 14);
	gfx.PutPixel(23 + x, 42 + y, 0, 146, 14);
	gfx.PutPixel(24 + x, 42 + y, 0, 146, 14);
	gfx.PutPixel(39 + x, 42 + y, 0, 146, 14);
	gfx.PutPixel(40 + x, 42 + y, 0, 146, 14);
	gfx.PutPixel(41 + x, 42 + y, 0, 146, 14);
	gfx.PutPixel(42 + x, 42 + y, 0, 146, 14);
	gfx.PutPixel(43 + x, 42 + y, 0, 146, 14);
	gfx.PutPixel(44 + x, 42 + y, 0, 146, 14);
	gfx.PutPixel(45 + x, 42 + y, 0, 146, 14);
	gfx.PutPixel(46 + x, 42 + y, 0, 146, 14);
	gfx.PutPixel(47 + x, 42 + y, 0, 146, 14);
	gfx.PutPixel(48 + x, 42 + y, 0, 146, 14);
	gfx.PutPixel(49 + x, 42 + y, 0, 146, 14);
	gfx.PutPixel(50 + x, 42 + y, 0, 146, 14);
	gfx.PutPixel(51 + x, 42 + y, 0, 146, 14);
	gfx.PutPixel(52 + x, 42 + y, 0, 146, 14);
	gfx.PutPixel(53 + x, 42 + y, 0, 146, 14);
	gfx.PutPixel(54 + x, 42 + y, 0, 146, 14);
	gfx.PutPixel(55 + x, 42 + y, 0, 146, 14);
	gfx.PutPixel(56 + x, 42 + y, 0, 146, 14);
	gfx.PutPixel(57 + x, 42 + y, 0, 146, 14);
	gfx.PutPixel(58 + x, 42 + y, 0, 146, 14);
	gfx.PutPixel(59 + x, 42 + y, 0, 146, 14);
	gfx.PutPixel(60 + x, 42 + y, 0, 146, 14);
	gfx.PutPixel(61 + x, 42 + y, 0, 146, 14);
	gfx.PutPixel(62 + x, 42 + y, 0, 146, 14);
	gfx.PutPixel(63 + x, 42 + y, 0, 146, 14);
	gfx.PutPixel(64 + x, 42 + y, 0, 146, 14);
	gfx.PutPixel(65 + x, 42 + y, 0, 146, 14);
	gfx.PutPixel(66 + x, 42 + y, 0, 146, 14);
	gfx.PutPixel(67 + x, 42 + y, 0, 146, 14);
	gfx.PutPixel(68 + x, 42 + y, 0, 146, 14);
	gfx.PutPixel(69 + x, 42 + y, 0, 146, 14);
	gfx.PutPixel(70 + x, 42 + y, 0, 146, 14);
	gfx.PutPixel(71 + x, 42 + y, 0, 146, 14);
	gfx.PutPixel(72 + x, 42 + y, 0, 146, 14);
	gfx.PutPixel(73 + x, 42 + y, 0, 146, 14);
	gfx.PutPixel(74 + x, 42 + y, 0, 146, 14);
	gfx.PutPixel(75 + x, 42 + y, 0, 146, 14);
	gfx.PutPixel(76 + x, 42 + y, 0, 146, 14);
	gfx.PutPixel(77 + x, 42 + y, 0, 146, 14);
	gfx.PutPixel(78 + x, 42 + y, 0, 146, 14);
	gfx.PutPixel(79 + x, 42 + y, 0, 146, 14);
	gfx.PutPixel(1 + x, 43 + y, 0, 146, 14);
	gfx.PutPixel(2 + x, 43 + y, 0, 146, 14);
	gfx.PutPixel(3 + x, 43 + y, 0, 146, 14);
	gfx.PutPixel(4 + x, 43 + y, 0, 146, 14);
	gfx.PutPixel(5 + x, 43 + y, 0, 146, 14);
	gfx.PutPixel(6 + x, 43 + y, 0, 146, 14);
	gfx.PutPixel(7 + x, 43 + y, 0, 146, 14);
	gfx.PutPixel(8 + x, 43 + y, 0, 146, 14);
	gfx.PutPixel(9 + x, 43 + y, 0, 146, 14);
	gfx.PutPixel(10 + x, 43 + y, 0, 146, 14);
	gfx.PutPixel(11 + x, 43 + y, 0, 146, 14);
	gfx.PutPixel(12 + x, 43 + y, 0, 146, 14);
	gfx.PutPixel(13 + x, 43 + y, 0, 146, 14);
	gfx.PutPixel(14 + x, 43 + y, 0, 146, 14);
	gfx.PutPixel(15 + x, 43 + y, 0, 146, 14);
	gfx.PutPixel(16 + x, 43 + y, 0, 146, 14);
	gfx.PutPixel(17 + x, 43 + y, 0, 146, 14);
	gfx.PutPixel(18 + x, 43 + y, 0, 146, 14);
	gfx.PutPixel(19 + x, 43 + y, 0, 146, 14);
	gfx.PutPixel(20 + x, 43 + y, 0, 146, 14);
	gfx.PutPixel(21 + x, 43 + y, 0, 146, 14);
	gfx.PutPixel(22 + x, 43 + y, 0, 146, 14);
	gfx.PutPixel(23 + x, 43 + y, 0, 146, 14);
	gfx.PutPixel(24 + x, 43 + y, 0, 146, 14);
	gfx.PutPixel(25 + x, 43 + y, 0, 146, 14);
	gfx.PutPixel(38 + x, 43 + y, 0, 146, 14);
	gfx.PutPixel(39 + x, 43 + y, 0, 146, 14);
	gfx.PutPixel(40 + x, 43 + y, 0, 146, 14);
	gfx.PutPixel(41 + x, 43 + y, 0, 146, 14);
	gfx.PutPixel(77 + x, 43 + y, 0, 146, 14);
	gfx.PutPixel(78 + x, 43 + y, 0, 146, 14);
	gfx.PutPixel(79 + x, 43 + y, 0, 146, 14);
	gfx.PutPixel(0 + x, 44 + y, 0, 146, 14);
	gfx.PutPixel(1 + x, 44 + y, 0, 146, 14);
	gfx.PutPixel(2 + x, 44 + y, 0, 146, 14);
	gfx.PutPixel(3 + x, 44 + y, 0, 146, 14);
	gfx.PutPixel(4 + x, 44 + y, 0, 146, 14);
	gfx.PutPixel(5 + x, 44 + y, 0, 146, 14);
	gfx.PutPixel(6 + x, 44 + y, 0, 146, 14);
	gfx.PutPixel(7 + x, 44 + y, 0, 146, 14);
	gfx.PutPixel(8 + x, 44 + y, 0, 146, 14);
	gfx.PutPixel(9 + x, 44 + y, 0, 146, 14);
	gfx.PutPixel(10 + x, 44 + y, 0, 146, 14);
	gfx.PutPixel(11 + x, 44 + y, 0, 146, 14);
	gfx.PutPixel(12 + x, 44 + y, 0, 146, 14);
	gfx.PutPixel(13 + x, 44 + y, 0, 146, 14);
	gfx.PutPixel(14 + x, 44 + y, 0, 146, 14);
	gfx.PutPixel(15 + x, 44 + y, 0, 146, 14);
	gfx.PutPixel(16 + x, 44 + y, 0, 146, 14);
	gfx.PutPixel(17 + x, 44 + y, 0, 146, 14);
	gfx.PutPixel(18 + x, 44 + y, 0, 146, 14);
	gfx.PutPixel(19 + x, 44 + y, 0, 146, 14);
	gfx.PutPixel(20 + x, 44 + y, 0, 146, 14);
	gfx.PutPixel(21 + x, 44 + y, 0, 146, 14);
	gfx.PutPixel(22 + x, 44 + y, 0, 146, 14);
	gfx.PutPixel(23 + x, 44 + y, 0, 146, 14);
	gfx.PutPixel(24 + x, 44 + y, 0, 146, 14);
	gfx.PutPixel(25 + x, 44 + y, 0, 146, 14);
	gfx.PutPixel(26 + x, 44 + y, 0, 146, 14);
	gfx.PutPixel(38 + x, 44 + y, 0, 146, 14);
	gfx.PutPixel(39 + x, 44 + y, 0, 146, 14);
	gfx.PutPixel(40 + x, 44 + y, 0, 146, 14);
	gfx.PutPixel(77 + x, 44 + y, 0, 3, 0);
	gfx.PutPixel(78 + x, 44 + y, 0, 146, 14);
	gfx.PutPixel(79 + x, 44 + y, 0, 146, 14);
	gfx.PutPixel(80 + x, 44 + y, 0, 146, 14);
	gfx.PutPixel(0 + x, 45 + y, 0, 146, 14);
	gfx.PutPixel(1 + x, 45 + y, 0, 146, 14);
	gfx.PutPixel(2 + x, 45 + y, 0, 146, 14);
	gfx.PutPixel(3 + x, 45 + y, 0, 146, 14);
	gfx.PutPixel(4 + x, 45 + y, 0, 146, 14);
	gfx.PutPixel(5 + x, 45 + y, 0, 146, 14);
	gfx.PutPixel(6 + x, 45 + y, 0, 146, 14);
	gfx.PutPixel(7 + x, 45 + y, 0, 146, 14);
	gfx.PutPixel(8 + x, 45 + y, 0, 146, 14);
	gfx.PutPixel(9 + x, 45 + y, 0, 146, 14);
	gfx.PutPixel(10 + x, 45 + y, 0, 146, 14);
	gfx.PutPixel(11 + x, 45 + y, 0, 146, 14);
	gfx.PutPixel(12 + x, 45 + y, 0, 146, 14);
	gfx.PutPixel(13 + x, 45 + y, 0, 146, 14);
	gfx.PutPixel(14 + x, 45 + y, 0, 146, 14);
	gfx.PutPixel(15 + x, 45 + y, 0, 146, 14);
	gfx.PutPixel(16 + x, 45 + y, 0, 146, 14);
	gfx.PutPixel(17 + x, 45 + y, 0, 146, 14);
	gfx.PutPixel(18 + x, 45 + y, 0, 146, 14);
	gfx.PutPixel(19 + x, 45 + y, 0, 146, 14);
	gfx.PutPixel(20 + x, 45 + y, 0, 146, 14);
	gfx.PutPixel(21 + x, 45 + y, 0, 146, 14);
	gfx.PutPixel(22 + x, 45 + y, 0, 146, 14);
	gfx.PutPixel(23 + x, 45 + y, 0, 146, 14);
	gfx.PutPixel(24 + x, 45 + y, 0, 146, 14);
	gfx.PutPixel(25 + x, 45 + y, 0, 146, 14);
	gfx.PutPixel(26 + x, 45 + y, 0, 146, 14);
	gfx.PutPixel(27 + x, 45 + y, 0, 118, 11);
	gfx.PutPixel(38 + x, 45 + y, 0, 146, 14);
	gfx.PutPixel(39 + x, 45 + y, 0, 146, 14);
	gfx.PutPixel(40 + x, 45 + y, 0, 146, 14);
	gfx.PutPixel(78 + x, 45 + y, 0, 146, 14);
	gfx.PutPixel(79 + x, 45 + y, 0, 146, 14);
	gfx.PutPixel(80 + x, 45 + y, 0, 146, 14);
	gfx.PutPixel(0 + x, 46 + y, 0, 146, 14);
	gfx.PutPixel(1 + x, 46 + y, 0, 146, 14);
	gfx.PutPixel(2 + x, 46 + y, 0, 146, 14);
	gfx.PutPixel(3 + x, 46 + y, 0, 146, 14);
	gfx.PutPixel(4 + x, 46 + y, 0, 146, 14);
	gfx.PutPixel(5 + x, 46 + y, 0, 146, 14);
	gfx.PutPixel(6 + x, 46 + y, 0, 146, 14);
	gfx.PutPixel(7 + x, 46 + y, 0, 146, 14);
	gfx.PutPixel(8 + x, 46 + y, 0, 146, 14);
	gfx.PutPixel(9 + x, 46 + y, 0, 146, 14);
	gfx.PutPixel(10 + x, 46 + y, 0, 146, 14);
	gfx.PutPixel(11 + x, 46 + y, 0, 146, 14);
	gfx.PutPixel(12 + x, 46 + y, 0, 146, 14);
	gfx.PutPixel(13 + x, 46 + y, 0, 146, 14);
	gfx.PutPixel(14 + x, 46 + y, 0, 146, 14);
	gfx.PutPixel(15 + x, 46 + y, 0, 146, 14);
	gfx.PutPixel(16 + x, 46 + y, 0, 146, 14);
	gfx.PutPixel(17 + x, 46 + y, 0, 146, 14);
	gfx.PutPixel(18 + x, 46 + y, 0, 146, 14);
	gfx.PutPixel(19 + x, 46 + y, 0, 146, 14);
	gfx.PutPixel(20 + x, 46 + y, 0, 146, 14);
	gfx.PutPixel(21 + x, 46 + y, 0, 146, 14);
	gfx.PutPixel(22 + x, 46 + y, 0, 146, 14);
	gfx.PutPixel(23 + x, 46 + y, 0, 146, 14);
	gfx.PutPixel(24 + x, 46 + y, 0, 146, 14);
	gfx.PutPixel(25 + x, 46 + y, 0, 146, 14);
	gfx.PutPixel(26 + x, 46 + y, 0, 146, 14);
	gfx.PutPixel(27 + x, 46 + y, 0, 146, 14);
	gfx.PutPixel(38 + x, 46 + y, 0, 146, 14);
	gfx.PutPixel(39 + x, 46 + y, 0, 146, 14);
	gfx.PutPixel(40 + x, 46 + y, 0, 146, 14);
	gfx.PutPixel(77 + x, 46 + y, 0, 118, 11);
	gfx.PutPixel(78 + x, 46 + y, 0, 146, 14);
	gfx.PutPixel(79 + x, 46 + y, 0, 146, 14);
	gfx.PutPixel(80 + x, 46 + y, 0, 146, 14);
	gfx.PutPixel(0 + x, 47 + y, 0, 146, 14);
	gfx.PutPixel(1 + x, 47 + y, 0, 146, 14);
	gfx.PutPixel(2 + x, 47 + y, 0, 146, 14);
	gfx.PutPixel(3 + x, 47 + y, 0, 146, 14);
	gfx.PutPixel(4 + x, 47 + y, 0, 146, 14);
	gfx.PutPixel(5 + x, 47 + y, 0, 146, 14);
	gfx.PutPixel(6 + x, 47 + y, 0, 146, 14);
	gfx.PutPixel(7 + x, 47 + y, 0, 146, 14);
	gfx.PutPixel(8 + x, 47 + y, 0, 146, 14);
	gfx.PutPixel(9 + x, 47 + y, 0, 146, 14);
	gfx.PutPixel(10 + x, 47 + y, 0, 146, 14);
	gfx.PutPixel(11 + x, 47 + y, 0, 146, 14);
	gfx.PutPixel(12 + x, 47 + y, 0, 146, 14);
	gfx.PutPixel(13 + x, 47 + y, 0, 146, 14);
	gfx.PutPixel(14 + x, 47 + y, 0, 146, 14);
	gfx.PutPixel(15 + x, 47 + y, 0, 146, 14);
	gfx.PutPixel(16 + x, 47 + y, 0, 146, 14);
	gfx.PutPixel(17 + x, 47 + y, 0, 146, 14);
	gfx.PutPixel(18 + x, 47 + y, 0, 146, 14);
	gfx.PutPixel(19 + x, 47 + y, 0, 146, 14);
	gfx.PutPixel(20 + x, 47 + y, 0, 146, 14);
	gfx.PutPixel(21 + x, 47 + y, 0, 146, 14);
	gfx.PutPixel(22 + x, 47 + y, 0, 146, 14);
	gfx.PutPixel(23 + x, 47 + y, 0, 146, 14);
	gfx.PutPixel(24 + x, 47 + y, 0, 146, 14);
	gfx.PutPixel(25 + x, 47 + y, 0, 146, 14);
	gfx.PutPixel(26 + x, 47 + y, 0, 146, 14);
	gfx.PutPixel(27 + x, 47 + y, 0, 146, 14);
	gfx.PutPixel(38 + x, 47 + y, 0, 146, 14);
	gfx.PutPixel(39 + x, 47 + y, 0, 146, 14);
	gfx.PutPixel(40 + x, 47 + y, 0, 146, 14);
	gfx.PutPixel(41 + x, 47 + y, 0, 146, 14);
	gfx.PutPixel(77 + x, 47 + y, 0, 146, 14);
	gfx.PutPixel(78 + x, 47 + y, 0, 146, 14);
	gfx.PutPixel(79 + x, 47 + y, 0, 146, 14);
	gfx.PutPixel(0 + x, 48 + y, 0, 146, 14);
	gfx.PutPixel(1 + x, 48 + y, 0, 146, 14);
	gfx.PutPixel(2 + x, 48 + y, 0, 146, 14);
	gfx.PutPixel(3 + x, 48 + y, 0, 146, 14);
	gfx.PutPixel(4 + x, 48 + y, 0, 146, 14);
	gfx.PutPixel(5 + x, 48 + y, 0, 146, 14);
	gfx.PutPixel(6 + x, 48 + y, 0, 146, 14);
	gfx.PutPixel(7 + x, 48 + y, 0, 146, 14);
	gfx.PutPixel(8 + x, 48 + y, 0, 146, 14);
	gfx.PutPixel(9 + x, 48 + y, 0, 146, 14);
	gfx.PutPixel(10 + x, 48 + y, 0, 146, 14);
	gfx.PutPixel(11 + x, 48 + y, 0, 146, 14);
	gfx.PutPixel(12 + x, 48 + y, 0, 146, 14);
	gfx.PutPixel(13 + x, 48 + y, 0, 146, 14);
	gfx.PutPixel(14 + x, 48 + y, 0, 146, 14);
	gfx.PutPixel(15 + x, 48 + y, 0, 146, 14);
	gfx.PutPixel(16 + x, 48 + y, 0, 146, 14);
	gfx.PutPixel(17 + x, 48 + y, 0, 146, 14);
	gfx.PutPixel(18 + x, 48 + y, 0, 146, 14);
	gfx.PutPixel(19 + x, 48 + y, 0, 146, 14);
	gfx.PutPixel(20 + x, 48 + y, 0, 146, 14);
	gfx.PutPixel(21 + x, 48 + y, 0, 146, 14);
	gfx.PutPixel(22 + x, 48 + y, 0, 146, 14);
	gfx.PutPixel(23 + x, 48 + y, 0, 146, 14);
	gfx.PutPixel(24 + x, 48 + y, 0, 146, 14);
	gfx.PutPixel(25 + x, 48 + y, 0, 146, 14);
	gfx.PutPixel(26 + x, 48 + y, 0, 146, 14);
	gfx.PutPixel(39 + x, 48 + y, 0, 146, 14);
	gfx.PutPixel(40 + x, 48 + y, 0, 146, 14);
	gfx.PutPixel(41 + x, 48 + y, 0, 146, 14);
	gfx.PutPixel(42 + x, 48 + y, 0, 146, 14);
	gfx.PutPixel(43 + x, 48 + y, 0, 146, 14);
	gfx.PutPixel(44 + x, 48 + y, 0, 146, 14);
	gfx.PutPixel(45 + x, 48 + y, 0, 146, 14);
	gfx.PutPixel(46 + x, 48 + y, 0, 146, 14);
	gfx.PutPixel(47 + x, 48 + y, 0, 146, 14);
	gfx.PutPixel(48 + x, 48 + y, 0, 146, 14);
	gfx.PutPixel(49 + x, 48 + y, 0, 146, 14);
	gfx.PutPixel(50 + x, 48 + y, 0, 146, 14);
	gfx.PutPixel(51 + x, 48 + y, 0, 146, 14);
	gfx.PutPixel(52 + x, 48 + y, 0, 146, 14);
	gfx.PutPixel(53 + x, 48 + y, 0, 146, 14);
	gfx.PutPixel(54 + x, 48 + y, 0, 146, 14);
	gfx.PutPixel(55 + x, 48 + y, 0, 146, 14);
	gfx.PutPixel(56 + x, 48 + y, 0, 146, 14);
	gfx.PutPixel(57 + x, 48 + y, 0, 146, 14);
	gfx.PutPixel(58 + x, 48 + y, 0, 146, 14);
	gfx.PutPixel(59 + x, 48 + y, 0, 146, 14);
	gfx.PutPixel(60 + x, 48 + y, 0, 146, 14);
	gfx.PutPixel(61 + x, 48 + y, 0, 146, 14);
	gfx.PutPixel(62 + x, 48 + y, 0, 146, 14);
	gfx.PutPixel(63 + x, 48 + y, 0, 146, 14);
	gfx.PutPixel(64 + x, 48 + y, 0, 146, 14);
	gfx.PutPixel(65 + x, 48 + y, 0, 146, 14);
	gfx.PutPixel(66 + x, 48 + y, 0, 146, 14);
	gfx.PutPixel(67 + x, 48 + y, 0, 146, 14);
	gfx.PutPixel(68 + x, 48 + y, 0, 146, 14);
	gfx.PutPixel(69 + x, 48 + y, 0, 146, 14);
	gfx.PutPixel(70 + x, 48 + y, 0, 146, 14);
	gfx.PutPixel(71 + x, 48 + y, 0, 146, 14);
	gfx.PutPixel(72 + x, 48 + y, 0, 146, 14);
	gfx.PutPixel(73 + x, 48 + y, 0, 146, 14);
	gfx.PutPixel(74 + x, 48 + y, 0, 146, 14);
	gfx.PutPixel(75 + x, 48 + y, 0, 146, 14);
	gfx.PutPixel(76 + x, 48 + y, 0, 146, 14);
	gfx.PutPixel(77 + x, 48 + y, 0, 146, 14);
	gfx.PutPixel(78 + x, 48 + y, 0, 146, 14);
	gfx.PutPixel(79 + x, 48 + y, 0, 146, 14);
	gfx.PutPixel(0 + x, 49 + y, 0, 142, 13);
	gfx.PutPixel(1 + x, 49 + y, 0, 146, 14);
	gfx.PutPixel(2 + x, 49 + y, 0, 146, 14);
	gfx.PutPixel(3 + x, 49 + y, 0, 146, 14);
	gfx.PutPixel(4 + x, 49 + y, 0, 146, 14);
	gfx.PutPixel(5 + x, 49 + y, 0, 146, 14);
	gfx.PutPixel(6 + x, 49 + y, 0, 146, 14);
	gfx.PutPixel(7 + x, 49 + y, 0, 146, 14);
	gfx.PutPixel(8 + x, 49 + y, 0, 146, 14);
	gfx.PutPixel(9 + x, 49 + y, 0, 146, 14);
	gfx.PutPixel(10 + x, 49 + y, 0, 146, 14);
	gfx.PutPixel(11 + x, 49 + y, 0, 146, 14);
	gfx.PutPixel(12 + x, 49 + y, 0, 146, 14);
	gfx.PutPixel(13 + x, 49 + y, 0, 146, 14);
	gfx.PutPixel(14 + x, 49 + y, 0, 146, 14);
	gfx.PutPixel(15 + x, 49 + y, 0, 146, 14);
	gfx.PutPixel(16 + x, 49 + y, 0, 146, 14);
	gfx.PutPixel(17 + x, 49 + y, 0, 146, 14);
	gfx.PutPixel(18 + x, 49 + y, 0, 146, 14);
	gfx.PutPixel(19 + x, 49 + y, 0, 146, 14);
	gfx.PutPixel(20 + x, 49 + y, 0, 146, 14);
	gfx.PutPixel(21 + x, 49 + y, 0, 146, 14);
	gfx.PutPixel(22 + x, 49 + y, 0, 146, 14);
	gfx.PutPixel(23 + x, 49 + y, 0, 146, 14);
	gfx.PutPixel(24 + x, 49 + y, 0, 146, 14);
	gfx.PutPixel(25 + x, 49 + y, 0, 146, 14);
	gfx.PutPixel(26 + x, 49 + y, 0, 146, 14);
	gfx.PutPixel(40 + x, 49 + y, 0, 146, 14);
	gfx.PutPixel(41 + x, 49 + y, 0, 146, 14);
	gfx.PutPixel(42 + x, 49 + y, 0, 146, 14);
	gfx.PutPixel(43 + x, 49 + y, 0, 146, 14);
	gfx.PutPixel(44 + x, 49 + y, 0, 146, 14);
	gfx.PutPixel(45 + x, 49 + y, 0, 146, 14);
	gfx.PutPixel(46 + x, 49 + y, 0, 146, 14);
	gfx.PutPixel(47 + x, 49 + y, 0, 146, 14);
	gfx.PutPixel(48 + x, 49 + y, 0, 146, 14);
	gfx.PutPixel(49 + x, 49 + y, 0, 146, 14);
	gfx.PutPixel(50 + x, 49 + y, 0, 146, 14);
	gfx.PutPixel(51 + x, 49 + y, 0, 146, 14);
	gfx.PutPixel(52 + x, 49 + y, 0, 146, 14);
	gfx.PutPixel(53 + x, 49 + y, 0, 146, 14);
	gfx.PutPixel(54 + x, 49 + y, 0, 146, 14);
	gfx.PutPixel(55 + x, 49 + y, 0, 146, 14);
	gfx.PutPixel(56 + x, 49 + y, 0, 146, 14);
	gfx.PutPixel(57 + x, 49 + y, 0, 146, 14);
	gfx.PutPixel(58 + x, 49 + y, 0, 146, 14);
	gfx.PutPixel(59 + x, 49 + y, 0, 146, 14);
	gfx.PutPixel(60 + x, 49 + y, 0, 146, 14);
	gfx.PutPixel(61 + x, 49 + y, 0, 146, 14);
	gfx.PutPixel(62 + x, 49 + y, 0, 146, 14);
	gfx.PutPixel(63 + x, 49 + y, 0, 146, 14);
	gfx.PutPixel(64 + x, 49 + y, 0, 146, 14);
	gfx.PutPixel(65 + x, 49 + y, 0, 146, 14);
	gfx.PutPixel(66 + x, 49 + y, 0, 146, 14);
	gfx.PutPixel(67 + x, 49 + y, 0, 146, 14);
	gfx.PutPixel(68 + x, 49 + y, 0, 146, 14);
	gfx.PutPixel(69 + x, 49 + y, 0, 146, 14);
	gfx.PutPixel(70 + x, 49 + y, 0, 146, 14);
	gfx.PutPixel(71 + x, 49 + y, 0, 146, 14);
	gfx.PutPixel(72 + x, 49 + y, 0, 146, 14);
	gfx.PutPixel(73 + x, 49 + y, 0, 146, 14);
	gfx.PutPixel(74 + x, 49 + y, 0, 146, 14);
	gfx.PutPixel(75 + x, 49 + y, 0, 146, 14);
	gfx.PutPixel(76 + x, 49 + y, 0, 146, 14);
	gfx.PutPixel(77 + x, 49 + y, 0, 146, 14);
	gfx.PutPixel(78 + x, 49 + y, 0, 146, 14);
	gfx.PutPixel(2 + x, 50 + y, 0, 146, 14);
	gfx.PutPixel(3 + x, 50 + y, 0, 146, 14);
	gfx.PutPixel(4 + x, 50 + y, 0, 146, 14);
	gfx.PutPixel(5 + x, 50 + y, 0, 146, 14);
	gfx.PutPixel(6 + x, 50 + y, 0, 146, 14);
	gfx.PutPixel(7 + x, 50 + y, 0, 146, 14);
	gfx.PutPixel(8 + x, 50 + y, 0, 146, 14);
	gfx.PutPixel(9 + x, 50 + y, 0, 146, 14);
	gfx.PutPixel(10 + x, 50 + y, 0, 146, 14);
	gfx.PutPixel(11 + x, 50 + y, 0, 146, 14);
	gfx.PutPixel(12 + x, 50 + y, 0, 146, 14);
	gfx.PutPixel(13 + x, 50 + y, 0, 146, 14);
	gfx.PutPixel(14 + x, 50 + y, 0, 146, 14);
	gfx.PutPixel(15 + x, 50 + y, 0, 146, 14);
	gfx.PutPixel(16 + x, 50 + y, 0, 146, 14);
	gfx.PutPixel(17 + x, 50 + y, 0, 146, 14);
	gfx.PutPixel(18 + x, 50 + y, 0, 146, 14);
	gfx.PutPixel(19 + x, 50 + y, 0, 146, 14);
	gfx.PutPixel(20 + x, 50 + y, 0, 146, 14);
	gfx.PutPixel(21 + x, 50 + y, 0, 146, 14);
	gfx.PutPixel(22 + x, 50 + y, 0, 146, 14);
	gfx.PutPixel(23 + x, 50 + y, 0, 146, 14);
	gfx.PutPixel(24 + x, 50 + y, 0, 146, 14);
	gfx.PutPixel(25 + x, 50 + y, 0, 142, 13);
	gfx.PutPixel(41 + x, 50 + y, 0, 146, 14);
	gfx.PutPixel(42 + x, 50 + y, 0, 146, 14);
	gfx.PutPixel(43 + x, 50 + y, 0, 146, 14);
	gfx.PutPixel(44 + x, 50 + y, 0, 146, 14);
	gfx.PutPixel(45 + x, 50 + y, 0, 146, 14);
	gfx.PutPixel(46 + x, 50 + y, 0, 146, 14);
	gfx.PutPixel(47 + x, 50 + y, 0, 146, 14);
	gfx.PutPixel(48 + x, 50 + y, 0, 146, 14);
	gfx.PutPixel(49 + x, 50 + y, 0, 146, 14);
	gfx.PutPixel(50 + x, 50 + y, 0, 146, 14);
	gfx.PutPixel(51 + x, 50 + y, 0, 146, 14);
	gfx.PutPixel(52 + x, 50 + y, 0, 146, 14);
	gfx.PutPixel(53 + x, 50 + y, 0, 146, 14);
	gfx.PutPixel(54 + x, 50 + y, 0, 146, 14);
	gfx.PutPixel(55 + x, 50 + y, 0, 146, 14);
	gfx.PutPixel(56 + x, 50 + y, 0, 146, 14);
	gfx.PutPixel(57 + x, 50 + y, 0, 146, 14);
	gfx.PutPixel(58 + x, 50 + y, 0, 146, 14);
	gfx.PutPixel(59 + x, 50 + y, 0, 146, 14);
	gfx.PutPixel(60 + x, 50 + y, 0, 146, 14);
	gfx.PutPixel(61 + x, 50 + y, 0, 146, 14);
	gfx.PutPixel(62 + x, 50 + y, 0, 146, 14);
	gfx.PutPixel(63 + x, 50 + y, 0, 146, 14);
	gfx.PutPixel(64 + x, 50 + y, 0, 146, 14);
	gfx.PutPixel(65 + x, 50 + y, 0, 146, 14);
	gfx.PutPixel(66 + x, 50 + y, 0, 146, 14);
	gfx.PutPixel(67 + x, 50 + y, 0, 146, 14);
	gfx.PutPixel(68 + x, 50 + y, 0, 146, 14);
	gfx.PutPixel(69 + x, 50 + y, 0, 146, 14);
	gfx.PutPixel(70 + x, 50 + y, 0, 146, 14);
	gfx.PutPixel(71 + x, 50 + y, 0, 146, 14);
	gfx.PutPixel(72 + x, 50 + y, 0, 146, 14);
	gfx.PutPixel(73 + x, 50 + y, 0, 146, 14);
	gfx.PutPixel(74 + x, 50 + y, 0, 146, 14);
	gfx.PutPixel(75 + x, 50 + y, 0, 146, 14);
	gfx.PutPixel(76 + x, 50 + y, 0, 146, 14);
	gfx.PutPixel(2 + x, 55 + y, 0, 146, 14);
	gfx.PutPixel(3 + x, 55 + y, 0, 146, 14);
	gfx.PutPixel(4 + x, 55 + y, 0, 146, 14);
	gfx.PutPixel(5 + x, 55 + y, 0, 146, 14);
	gfx.PutPixel(6 + x, 55 + y, 0, 146, 14);
	gfx.PutPixel(7 + x, 55 + y, 0, 146, 14);
	gfx.PutPixel(12 + x, 55 + y, 0, 146, 14);
	gfx.PutPixel(13 + x, 55 + y, 0, 146, 14);
	gfx.PutPixel(14 + x, 55 + y, 0, 146, 14);
	gfx.PutPixel(19 + x, 55 + y, 0, 146, 14);
	gfx.PutPixel(20 + x, 55 + y, 0, 146, 14);
	gfx.PutPixel(25 + x, 55 + y, 0, 146, 14);
	gfx.PutPixel(26 + x, 55 + y, 0, 146, 14);
	gfx.PutPixel(28 + x, 55 + y, 0, 146, 14);
	gfx.PutPixel(29 + x, 55 + y, 0, 146, 14);
	gfx.PutPixel(30 + x, 55 + y, 0, 146, 14);
	gfx.PutPixel(31 + x, 55 + y, 0, 146, 14);
	gfx.PutPixel(32 + x, 55 + y, 0, 146, 14);
	gfx.PutPixel(33 + x, 55 + y, 0, 146, 14);
	gfx.PutPixel(34 + x, 55 + y, 0, 146, 14);
	gfx.PutPixel(35 + x, 55 + y, 0, 146, 14);
	gfx.PutPixel(36 + x, 55 + y, 0, 146, 14);
	gfx.PutPixel(48 + x, 55 + y, 0, 118, 11);
	gfx.PutPixel(49 + x, 55 + y, 0, 146, 14);
	gfx.PutPixel(50 + x, 55 + y, 0, 146, 14);
	gfx.PutPixel(51 + x, 55 + y, 0, 146, 14);
	gfx.PutPixel(52 + x, 55 + y, 0, 146, 14);
	gfx.PutPixel(53 + x, 55 + y, 0, 146, 14);
	gfx.PutPixel(54 + x, 55 + y, 0, 146, 14);
	gfx.PutPixel(57 + x, 55 + y, 0, 146, 14);
	gfx.PutPixel(58 + x, 55 + y, 0, 146, 14);
	gfx.PutPixel(63 + x, 55 + y, 0, 146, 14);
	gfx.PutPixel(64 + x, 55 + y, 0, 146, 14);
	gfx.PutPixel(66 + x, 55 + y, 0, 3, 0);
	gfx.PutPixel(67 + x, 55 + y, 0, 146, 14);
	gfx.PutPixel(68 + x, 55 + y, 0, 146, 14);
	gfx.PutPixel(69 + x, 55 + y, 0, 146, 14);
	gfx.PutPixel(70 + x, 55 + y, 0, 146, 14);
	gfx.PutPixel(71 + x, 55 + y, 0, 146, 14);
	gfx.PutPixel(72 + x, 55 + y, 0, 146, 14);
	gfx.PutPixel(73 + x, 55 + y, 0, 146, 14);
	gfx.PutPixel(74 + x, 55 + y, 0, 146, 14);
	gfx.PutPixel(76 + x, 55 + y, 0, 146, 14);
	gfx.PutPixel(77 + x, 55 + y, 0, 146, 14);
	gfx.PutPixel(78 + x, 55 + y, 0, 146, 14);
	gfx.PutPixel(79 + x, 55 + y, 0, 146, 14);
	gfx.PutPixel(80 + x, 55 + y, 0, 146, 14);
	gfx.PutPixel(81 + x, 55 + y, 0, 146, 14);
	gfx.PutPixel(82 + x, 55 + y, 0, 146, 14);
	gfx.PutPixel(1 + x, 56 + y, 0, 146, 14);
	gfx.PutPixel(2 + x, 56 + y, 0, 146, 14);
	gfx.PutPixel(3 + x, 56 + y, 0, 146, 14);
	gfx.PutPixel(4 + x, 56 + y, 0, 146, 14);
	gfx.PutPixel(5 + x, 56 + y, 0, 146, 14);
	gfx.PutPixel(6 + x, 56 + y, 0, 146, 14);
	gfx.PutPixel(7 + x, 56 + y, 0, 146, 14);
	gfx.PutPixel(11 + x, 56 + y, 0, 146, 14);
	gfx.PutPixel(12 + x, 56 + y, 0, 146, 14);
	gfx.PutPixel(13 + x, 56 + y, 0, 146, 14);
	gfx.PutPixel(14 + x, 56 + y, 0, 146, 14);
	gfx.PutPixel(15 + x, 56 + y, 0, 146, 14);
	gfx.PutPixel(16 + x, 56 + y, 0, 142, 13);
	gfx.PutPixel(19 + x, 56 + y, 0, 146, 14);
	gfx.PutPixel(20 + x, 56 + y, 0, 146, 14);
	gfx.PutPixel(21 + x, 56 + y, 0, 146, 14);
	gfx.PutPixel(24 + x, 56 + y, 0, 146, 14);
	gfx.PutPixel(25 + x, 56 + y, 0, 146, 14);
	gfx.PutPixel(26 + x, 56 + y, 0, 146, 14);
	gfx.PutPixel(28 + x, 56 + y, 0, 146, 14);
	gfx.PutPixel(29 + x, 56 + y, 0, 146, 14);
	gfx.PutPixel(30 + x, 56 + y, 0, 146, 14);
	gfx.PutPixel(31 + x, 56 + y, 0, 146, 14);
	gfx.PutPixel(32 + x, 56 + y, 0, 146, 14);
	gfx.PutPixel(33 + x, 56 + y, 0, 146, 14);
	gfx.PutPixel(34 + x, 56 + y, 0, 146, 14);
	gfx.PutPixel(35 + x, 56 + y, 0, 146, 14);
	gfx.PutPixel(36 + x, 56 + y, 0, 142, 13);
	gfx.PutPixel(47 + x, 56 + y, 0, 146, 14);
	gfx.PutPixel(48 + x, 56 + y, 0, 146, 14);
	gfx.PutPixel(49 + x, 56 + y, 0, 146, 14);
	gfx.PutPixel(50 + x, 56 + y, 0, 25, 2);
	gfx.PutPixel(51 + x, 56 + y, 0, 25, 2);
	gfx.PutPixel(52 + x, 56 + y, 0, 146, 14);
	gfx.PutPixel(53 + x, 56 + y, 0, 146, 14);
	gfx.PutPixel(54 + x, 56 + y, 0, 146, 14);
	gfx.PutPixel(55 + x, 56 + y, 0, 146, 14);
	gfx.PutPixel(57 + x, 56 + y, 0, 146, 14);
	gfx.PutPixel(58 + x, 56 + y, 0, 146, 14);
	gfx.PutPixel(63 + x, 56 + y, 0, 146, 14);
	gfx.PutPixel(64 + x, 56 + y, 0, 146, 14);
	gfx.PutPixel(65 + x, 56 + y, 0, 146, 14);
	gfx.PutPixel(66 + x, 56 + y, 0, 146, 14);
	gfx.PutPixel(67 + x, 56 + y, 0, 146, 14);
	gfx.PutPixel(68 + x, 56 + y, 0, 146, 14);
	gfx.PutPixel(69 + x, 56 + y, 0, 146, 14);
	gfx.PutPixel(70 + x, 56 + y, 0, 146, 14);
	gfx.PutPixel(71 + x, 56 + y, 0, 146, 14);
	gfx.PutPixel(72 + x, 56 + y, 0, 146, 14);
	gfx.PutPixel(73 + x, 56 + y, 0, 146, 14);
	gfx.PutPixel(74 + x, 56 + y, 0, 146, 14);
	gfx.PutPixel(76 + x, 56 + y, 0, 146, 14);
	gfx.PutPixel(77 + x, 56 + y, 0, 146, 14);
	gfx.PutPixel(78 + x, 56 + y, 0, 146, 14);
	gfx.PutPixel(79 + x, 56 + y, 0, 25, 2);
	gfx.PutPixel(80 + x, 56 + y, 0, 146, 14);
	gfx.PutPixel(81 + x, 56 + y, 0, 146, 14);
	gfx.PutPixel(82 + x, 56 + y, 0, 146, 14);
	gfx.PutPixel(83 + x, 56 + y, 0, 146, 14);
	gfx.PutPixel(0 + x, 57 + y, 0, 146, 14);
	gfx.PutPixel(1 + x, 57 + y, 0, 146, 14);
	gfx.PutPixel(9 + x, 57 + y, 0, 25, 2);
	gfx.PutPixel(10 + x, 57 + y, 0, 146, 14);
	gfx.PutPixel(11 + x, 57 + y, 0, 146, 14);
	gfx.PutPixel(15 + x, 57 + y, 0, 146, 14);
	gfx.PutPixel(16 + x, 57 + y, 0, 146, 14);
	gfx.PutPixel(17 + x, 57 + y, 0, 118, 11);
	gfx.PutPixel(19 + x, 57 + y, 0, 146, 14);
	gfx.PutPixel(20 + x, 57 + y, 0, 146, 14);
	gfx.PutPixel(21 + x, 57 + y, 0, 146, 14);
	gfx.PutPixel(22 + x, 57 + y, 0, 146, 14);
	gfx.PutPixel(23 + x, 57 + y, 0, 146, 14);
	gfx.PutPixel(24 + x, 57 + y, 0, 146, 14);
	gfx.PutPixel(25 + x, 57 + y, 0, 146, 14);
	gfx.PutPixel(26 + x, 57 + y, 0, 146, 14);
	gfx.PutPixel(28 + x, 57 + y, 0, 146, 14);
	gfx.PutPixel(29 + x, 57 + y, 0, 146, 14);
	gfx.PutPixel(30 + x, 57 + y, 0, 146, 14);
	gfx.PutPixel(47 + x, 57 + y, 0, 146, 14);
	gfx.PutPixel(48 + x, 57 + y, 0, 146, 14);
	gfx.PutPixel(49 + x, 57 + y, 0, 146, 14);
	gfx.PutPixel(54 + x, 57 + y, 0, 146, 14);
	gfx.PutPixel(55 + x, 57 + y, 0, 146, 14);
	gfx.PutPixel(57 + x, 57 + y, 0, 146, 14);
	gfx.PutPixel(58 + x, 57 + y, 0, 146, 14);
	gfx.PutPixel(63 + x, 57 + y, 0, 146, 14);
	gfx.PutPixel(64 + x, 57 + y, 0, 146, 14);
	gfx.PutPixel(65 + x, 57 + y, 0, 25, 2);
	gfx.PutPixel(66 + x, 57 + y, 0, 146, 14);
	gfx.PutPixel(67 + x, 57 + y, 0, 146, 14);
	gfx.PutPixel(68 + x, 57 + y, 0, 146, 14);
	gfx.PutPixel(76 + x, 57 + y, 0, 146, 14);
	gfx.PutPixel(77 + x, 57 + y, 0, 146, 14);
	gfx.PutPixel(82 + x, 57 + y, 0, 146, 14);
	gfx.PutPixel(83 + x, 57 + y, 0, 146, 14);
	gfx.PutPixel(0 + x, 58 + y, 0, 146, 14);
	gfx.PutPixel(1 + x, 58 + y, 0, 146, 14);
	gfx.PutPixel(9 + x, 58 + y, 0, 146, 14);
	gfx.PutPixel(10 + x, 58 + y, 0, 146, 14);
	gfx.PutPixel(11 + x, 58 + y, 0, 118, 11);
	gfx.PutPixel(15 + x, 58 + y, 0, 25, 2);
	gfx.PutPixel(16 + x, 58 + y, 0, 146, 14);
	gfx.PutPixel(17 + x, 58 + y, 0, 146, 14);
	gfx.PutPixel(19 + x, 58 + y, 0, 146, 14);
	gfx.PutPixel(20 + x, 58 + y, 0, 146, 14);
	gfx.PutPixel(21 + x, 58 + y, 0, 146, 14);
	gfx.PutPixel(22 + x, 58 + y, 0, 146, 14);
	gfx.PutPixel(23 + x, 58 + y, 0, 146, 14);
	gfx.PutPixel(24 + x, 58 + y, 0, 146, 14);
	gfx.PutPixel(25 + x, 58 + y, 0, 146, 14);
	gfx.PutPixel(26 + x, 58 + y, 0, 146, 14);
	gfx.PutPixel(28 + x, 58 + y, 0, 146, 14);
	gfx.PutPixel(29 + x, 58 + y, 0, 146, 14);
	gfx.PutPixel(30 + x, 58 + y, 0, 146, 14);
	gfx.PutPixel(47 + x, 58 + y, 0, 146, 14);
	gfx.PutPixel(48 + x, 58 + y, 0, 146, 14);
	gfx.PutPixel(49 + x, 58 + y, 0, 146, 14);
	gfx.PutPixel(54 + x, 58 + y, 0, 146, 14);
	gfx.PutPixel(55 + x, 58 + y, 0, 146, 14);
	gfx.PutPixel(57 + x, 58 + y, 0, 146, 14);
	gfx.PutPixel(58 + x, 58 + y, 0, 146, 14);
	gfx.PutPixel(63 + x, 58 + y, 0, 146, 14);
	gfx.PutPixel(64 + x, 58 + y, 0, 146, 14);
	gfx.PutPixel(65 + x, 58 + y, 0, 25, 2);
	gfx.PutPixel(66 + x, 58 + y, 0, 146, 14);
	gfx.PutPixel(67 + x, 58 + y, 0, 146, 14);
	gfx.PutPixel(68 + x, 58 + y, 0, 146, 14);
	gfx.PutPixel(76 + x, 58 + y, 0, 146, 14);
	gfx.PutPixel(77 + x, 58 + y, 0, 146, 14);
	gfx.PutPixel(82 + x, 58 + y, 0, 146, 14);
	gfx.PutPixel(83 + x, 58 + y, 0, 146, 14);
	gfx.PutPixel(0 + x, 59 + y, 0, 146, 14);
	gfx.PutPixel(1 + x, 59 + y, 0, 146, 14);
	gfx.PutPixel(5 + x, 59 + y, 0, 146, 14);
	gfx.PutPixel(6 + x, 59 + y, 0, 146, 14);
	gfx.PutPixel(7 + x, 59 + y, 0, 146, 14);
	gfx.PutPixel(9 + x, 59 + y, 0, 146, 14);
	gfx.PutPixel(10 + x, 59 + y, 0, 146, 14);
	gfx.PutPixel(11 + x, 59 + y, 0, 25, 2);
	gfx.PutPixel(15 + x, 59 + y, 0, 70, 6);
	gfx.PutPixel(16 + x, 59 + y, 0, 146, 14);
	gfx.PutPixel(17 + x, 59 + y, 0, 146, 14);
	gfx.PutPixel(19 + x, 59 + y, 0, 146, 14);
	gfx.PutPixel(20 + x, 59 + y, 0, 146, 14);
	gfx.PutPixel(22 + x, 59 + y, 0, 146, 14);
	gfx.PutPixel(23 + x, 59 + y, 0, 146, 14);
	gfx.PutPixel(24 + x, 59 + y, 0, 25, 2);
	gfx.PutPixel(25 + x, 59 + y, 0, 146, 14);
	gfx.PutPixel(26 + x, 59 + y, 0, 146, 14);
	gfx.PutPixel(28 + x, 59 + y, 0, 146, 14);
	gfx.PutPixel(29 + x, 59 + y, 0, 146, 14);
	gfx.PutPixel(30 + x, 59 + y, 0, 146, 14);
	gfx.PutPixel(31 + x, 59 + y, 0, 146, 14);
	gfx.PutPixel(32 + x, 59 + y, 0, 146, 14);
	gfx.PutPixel(33 + x, 59 + y, 0, 146, 14);
	gfx.PutPixel(34 + x, 59 + y, 0, 146, 14);
	gfx.PutPixel(35 + x, 59 + y, 0, 146, 14);
	gfx.PutPixel(47 + x, 59 + y, 0, 146, 14);
	gfx.PutPixel(48 + x, 59 + y, 0, 146, 14);
	gfx.PutPixel(49 + x, 59 + y, 0, 146, 14);
	gfx.PutPixel(54 + x, 59 + y, 0, 146, 14);
	gfx.PutPixel(55 + x, 59 + y, 0, 146, 14);
	gfx.PutPixel(57 + x, 59 + y, 0, 146, 14);
	gfx.PutPixel(58 + x, 59 + y, 0, 146, 14);
	gfx.PutPixel(59 + x, 59 + y, 0, 146, 14);
	gfx.PutPixel(63 + x, 59 + y, 0, 146, 14);
	gfx.PutPixel(64 + x, 59 + y, 0, 146, 14);
	gfx.PutPixel(65 + x, 59 + y, 0, 25, 2);
	gfx.PutPixel(66 + x, 59 + y, 0, 146, 14);
	gfx.PutPixel(67 + x, 59 + y, 0, 146, 14);
	gfx.PutPixel(68 + x, 59 + y, 0, 146, 14);
	gfx.PutPixel(69 + x, 59 + y, 0, 146, 14);
	gfx.PutPixel(70 + x, 59 + y, 0, 146, 14);
	gfx.PutPixel(71 + x, 59 + y, 0, 146, 14);
	gfx.PutPixel(72 + x, 59 + y, 0, 146, 14);
	gfx.PutPixel(73 + x, 59 + y, 0, 146, 14);
	gfx.PutPixel(76 + x, 59 + y, 0, 146, 14);
	gfx.PutPixel(77 + x, 59 + y, 0, 146, 14);
	gfx.PutPixel(82 + x, 59 + y, 0, 146, 14);
	gfx.PutPixel(83 + x, 59 + y, 0, 146, 14);
	gfx.PutPixel(0 + x, 60 + y, 0, 146, 14);
	gfx.PutPixel(1 + x, 60 + y, 0, 146, 14);
	gfx.PutPixel(6 + x, 60 + y, 0, 146, 14);
	gfx.PutPixel(7 + x, 60 + y, 0, 146, 14);
	gfx.PutPixel(9 + x, 60 + y, 0, 146, 14);
	gfx.PutPixel(10 + x, 60 + y, 0, 146, 14);
	gfx.PutPixel(11 + x, 60 + y, 0, 146, 14);
	gfx.PutPixel(12 + x, 60 + y, 0, 146, 14);
	gfx.PutPixel(13 + x, 60 + y, 0, 146, 14);
	gfx.PutPixel(14 + x, 60 + y, 0, 146, 14);
	gfx.PutPixel(15 + x, 60 + y, 0, 146, 14);
	gfx.PutPixel(16 + x, 60 + y, 0, 146, 14);
	gfx.PutPixel(17 + x, 60 + y, 0, 146, 14);
	gfx.PutPixel(19 + x, 60 + y, 0, 146, 14);
	gfx.PutPixel(20 + x, 60 + y, 0, 146, 14);
	gfx.PutPixel(25 + x, 60 + y, 0, 146, 14);
	gfx.PutPixel(26 + x, 60 + y, 0, 146, 14);
	gfx.PutPixel(28 + x, 60 + y, 0, 146, 14);
	gfx.PutPixel(29 + x, 60 + y, 0, 146, 14);
	gfx.PutPixel(30 + x, 60 + y, 0, 146, 14);
	gfx.PutPixel(47 + x, 60 + y, 0, 146, 14);
	gfx.PutPixel(48 + x, 60 + y, 0, 146, 14);
	gfx.PutPixel(49 + x, 60 + y, 0, 146, 14);
	gfx.PutPixel(54 + x, 60 + y, 0, 146, 14);
	gfx.PutPixel(55 + x, 60 + y, 0, 146, 14);
	gfx.PutPixel(57 + x, 60 + y, 0, 146, 14);
	gfx.PutPixel(58 + x, 60 + y, 0, 146, 14);
	gfx.PutPixel(59 + x, 60 + y, 0, 146, 14);
	gfx.PutPixel(60 + x, 60 + y, 0, 146, 14);
	gfx.PutPixel(61 + x, 60 + y, 0, 146, 14);
	gfx.PutPixel(62 + x, 60 + y, 0, 146, 14);
	gfx.PutPixel(63 + x, 60 + y, 0, 146, 14);
	gfx.PutPixel(64 + x, 60 + y, 0, 146, 14);
	gfx.PutPixel(66 + x, 60 + y, 0, 146, 14);
	gfx.PutPixel(67 + x, 60 + y, 0, 146, 14);
	gfx.PutPixel(68 + x, 60 + y, 0, 146, 14);
	gfx.PutPixel(76 + x, 60 + y, 0, 146, 14);
	gfx.PutPixel(77 + x, 60 + y, 0, 146, 14);
	gfx.PutPixel(78 + x, 60 + y, 0, 146, 14);
	gfx.PutPixel(80 + x, 60 + y, 0, 146, 14);
	gfx.PutPixel(81 + x, 60 + y, 0, 146, 14);
	gfx.PutPixel(82 + x, 60 + y, 0, 146, 14);
	gfx.PutPixel(83 + x, 60 + y, 0, 146, 14);
	gfx.PutPixel(0 + x, 61 + y, 0, 146, 14);
	gfx.PutPixel(1 + x, 61 + y, 0, 146, 14);
	gfx.PutPixel(6 + x, 61 + y, 0, 146, 14);
	gfx.PutPixel(7 + x, 61 + y, 0, 146, 14);
	gfx.PutPixel(9 + x, 61 + y, 0, 146, 14);
	gfx.PutPixel(10 + x, 61 + y, 0, 146, 14);
	gfx.PutPixel(11 + x, 61 + y, 0, 146, 14);
	gfx.PutPixel(12 + x, 61 + y, 0, 146, 14);
	gfx.PutPixel(13 + x, 61 + y, 0, 146, 14);
	gfx.PutPixel(14 + x, 61 + y, 0, 146, 14);
	gfx.PutPixel(15 + x, 61 + y, 0, 146, 14);
	gfx.PutPixel(16 + x, 61 + y, 0, 146, 14);
	gfx.PutPixel(17 + x, 61 + y, 0, 146, 14);
	gfx.PutPixel(19 + x, 61 + y, 0, 146, 14);
	gfx.PutPixel(20 + x, 61 + y, 0, 146, 14);
	gfx.PutPixel(25 + x, 61 + y, 0, 146, 14);
	gfx.PutPixel(26 + x, 61 + y, 0, 146, 14);
	gfx.PutPixel(28 + x, 61 + y, 0, 146, 14);
	gfx.PutPixel(29 + x, 61 + y, 0, 146, 14);
	gfx.PutPixel(30 + x, 61 + y, 0, 146, 14);
	gfx.PutPixel(47 + x, 61 + y, 0, 146, 14);
	gfx.PutPixel(48 + x, 61 + y, 0, 146, 14);
	gfx.PutPixel(49 + x, 61 + y, 0, 146, 14);
	gfx.PutPixel(54 + x, 61 + y, 0, 146, 14);
	gfx.PutPixel(55 + x, 61 + y, 0, 146, 14);
	gfx.PutPixel(58 + x, 61 + y, 0, 146, 14);
	gfx.PutPixel(59 + x, 61 + y, 0, 146, 14);
	gfx.PutPixel(60 + x, 61 + y, 0, 146, 14);
	gfx.PutPixel(61 + x, 61 + y, 0, 146, 14);
	gfx.PutPixel(62 + x, 61 + y, 0, 146, 14);
	gfx.PutPixel(63 + x, 61 + y, 0, 146, 14);
	gfx.PutPixel(66 + x, 61 + y, 0, 146, 14);
	gfx.PutPixel(67 + x, 61 + y, 0, 146, 14);
	gfx.PutPixel(68 + x, 61 + y, 0, 146, 14);
	gfx.PutPixel(76 + x, 61 + y, 0, 146, 14);
	gfx.PutPixel(77 + x, 61 + y, 0, 146, 14);
	gfx.PutPixel(78 + x, 61 + y, 0, 146, 14);
	gfx.PutPixel(79 + x, 61 + y, 0, 146, 14);
	gfx.PutPixel(80 + x, 61 + y, 0, 146, 14);
	gfx.PutPixel(81 + x, 61 + y, 0, 146, 14);
	gfx.PutPixel(82 + x, 61 + y, 0, 146, 14);
	gfx.PutPixel(0 + x, 62 + y, 0, 142, 13);
	gfx.PutPixel(1 + x, 62 + y, 0, 146, 14);
	gfx.PutPixel(2 + x, 62 + y, 0, 146, 14);
	gfx.PutPixel(6 + x, 62 + y, 0, 146, 14);
	gfx.PutPixel(7 + x, 62 + y, 0, 146, 14);
	gfx.PutPixel(9 + x, 62 + y, 0, 146, 14);
	gfx.PutPixel(10 + x, 62 + y, 0, 146, 14);
	gfx.PutPixel(11 + x, 62 + y, 0, 146, 14);
	gfx.PutPixel(15 + x, 62 + y, 0, 70, 6);
	gfx.PutPixel(16 + x, 62 + y, 0, 146, 14);
	gfx.PutPixel(17 + x, 62 + y, 0, 146, 14);
	gfx.PutPixel(19 + x, 62 + y, 0, 146, 14);
	gfx.PutPixel(20 + x, 62 + y, 0, 146, 14);
	gfx.PutPixel(25 + x, 62 + y, 0, 146, 14);
	gfx.PutPixel(26 + x, 62 + y, 0, 146, 14);
	gfx.PutPixel(28 + x, 62 + y, 0, 146, 14);
	gfx.PutPixel(29 + x, 62 + y, 0, 146, 14);
	gfx.PutPixel(30 + x, 62 + y, 0, 146, 14);
	gfx.PutPixel(47 + x, 62 + y, 0, 146, 14);
	gfx.PutPixel(48 + x, 62 + y, 0, 146, 14);
	gfx.PutPixel(49 + x, 62 + y, 0, 146, 14);
	gfx.PutPixel(53 + x, 62 + y, 0, 3, 0);
	gfx.PutPixel(54 + x, 62 + y, 0, 146, 14);
	gfx.PutPixel(55 + x, 62 + y, 0, 146, 14);
	gfx.PutPixel(59 + x, 62 + y, 0, 146, 14);
	gfx.PutPixel(60 + x, 62 + y, 0, 146, 14);
	gfx.PutPixel(61 + x, 62 + y, 0, 146, 14);
	gfx.PutPixel(62 + x, 62 + y, 0, 146, 14);
	gfx.PutPixel(66 + x, 62 + y, 0, 146, 14);
	gfx.PutPixel(67 + x, 62 + y, 0, 146, 14);
	gfx.PutPixel(68 + x, 62 + y, 0, 146, 14);
	gfx.PutPixel(76 + x, 62 + y, 0, 146, 14);
	gfx.PutPixel(77 + x, 62 + y, 0, 146, 14);
	gfx.PutPixel(80 + x, 62 + y, 0, 146, 14);
	gfx.PutPixel(81 + x, 62 + y, 0, 146, 14);
	gfx.PutPixel(82 + x, 62 + y, 0, 146, 14);
	gfx.PutPixel(83 + x, 62 + y, 0, 70, 6);
	gfx.PutPixel(1 + x, 63 + y, 0, 142, 13);
	gfx.PutPixel(2 + x, 63 + y, 0, 146, 14);
	gfx.PutPixel(3 + x, 63 + y, 0, 146, 14);
	gfx.PutPixel(4 + x, 63 + y, 0, 146, 14);
	gfx.PutPixel(5 + x, 63 + y, 0, 146, 14);
	gfx.PutPixel(6 + x, 63 + y, 0, 146, 14);
	gfx.PutPixel(7 + x, 63 + y, 0, 146, 14);
	gfx.PutPixel(9 + x, 63 + y, 0, 146, 14);
	gfx.PutPixel(10 + x, 63 + y, 0, 146, 14);
	gfx.PutPixel(11 + x, 63 + y, 0, 146, 14);
	gfx.PutPixel(15 + x, 63 + y, 0, 25, 2);
	gfx.PutPixel(16 + x, 63 + y, 0, 146, 14);
	gfx.PutPixel(17 + x, 63 + y, 0, 146, 14);
	gfx.PutPixel(19 + x, 63 + y, 0, 146, 14);
	gfx.PutPixel(20 + x, 63 + y, 0, 146, 14);
	gfx.PutPixel(25 + x, 63 + y, 0, 146, 14);
	gfx.PutPixel(26 + x, 63 + y, 0, 146, 14);
	gfx.PutPixel(28 + x, 63 + y, 0, 146, 14);
	gfx.PutPixel(29 + x, 63 + y, 0, 146, 14);
	gfx.PutPixel(30 + x, 63 + y, 0, 146, 14);
	gfx.PutPixel(31 + x, 63 + y, 0, 146, 14);
	gfx.PutPixel(32 + x, 63 + y, 0, 146, 14);
	gfx.PutPixel(33 + x, 63 + y, 0, 146, 14);
	gfx.PutPixel(34 + x, 63 + y, 0, 146, 14);
	gfx.PutPixel(35 + x, 63 + y, 0, 146, 14);
	gfx.PutPixel(36 + x, 63 + y, 0, 146, 14);
	gfx.PutPixel(48 + x, 63 + y, 0, 146, 14);
	gfx.PutPixel(49 + x, 63 + y, 0, 146, 14);
	gfx.PutPixel(50 + x, 63 + y, 0, 146, 14);
	gfx.PutPixel(51 + x, 63 + y, 0, 146, 14);
	gfx.PutPixel(52 + x, 63 + y, 0, 146, 14);
	gfx.PutPixel(53 + x, 63 + y, 0, 146, 14);
	gfx.PutPixel(54 + x, 63 + y, 0, 146, 14);
	gfx.PutPixel(60 + x, 63 + y, 0, 146, 14);
	gfx.PutPixel(61 + x, 63 + y, 0, 146, 14);
	gfx.PutPixel(66 + x, 63 + y, 0, 146, 14);
	gfx.PutPixel(67 + x, 63 + y, 0, 146, 14);
	gfx.PutPixel(68 + x, 63 + y, 0, 146, 14);
	gfx.PutPixel(69 + x, 63 + y, 0, 146, 14);
	gfx.PutPixel(70 + x, 63 + y, 0, 146, 14);
	gfx.PutPixel(71 + x, 63 + y, 0, 146, 14);
	gfx.PutPixel(72 + x, 63 + y, 0, 146, 14);
	gfx.PutPixel(73 + x, 63 + y, 0, 146, 14);
	gfx.PutPixel(74 + x, 63 + y, 0, 146, 14);
	gfx.PutPixel(76 + x, 63 + y, 0, 146, 14);
	gfx.PutPixel(77 + x, 63 + y, 0, 146, 14);
	gfx.PutPixel(82 + x, 63 + y, 0, 146, 14);
	gfx.PutPixel(83 + x, 63 + y, 0, 146, 14);

}

float Game::howmanpoopz()
{
	int k = 0;
	for (int i = 0; i < n; i++) {
		if (poopz[i].isEaten()) {
			k++;
		}
	}
	return float(750*k/n);
}
float Game::seglen(int x1, int y1, int x2, int y2) {
	return float(sqrt
	(
		(x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1)
			)
				);
}
void Game::drawCircle(int x, int y, int r) {
	for (int i = x - r; i <= x + r; i++) {
		for (int j = y - r; j <= y + r; j++) {
			if (i>0 && j>0 && i<gfx.ScreenWidth && j < gfx.ScreenHeight) {
				if (seglen(i, j, x, y) < r) {
					gfx.PutPixel(i, j, 55, 55, 55);
				}
			}
		}
	}
}
void Game::drawEmptyCircle(int x, int y, int r) {
	for (int i = x - r; i <= x + r; i++) {
		for (int j = y - r; j <= y + r; j++) {
			if (i>0 && j>0 && i<gfx.ScreenWidth && j < gfx.ScreenHeight) {
				int dist = seglen(i, j, x, y);
				if (dist >= r-1 && dist <=r+1) {
					gfx.PutPixel(i, j, 0,0,200);
				}
			}
		}
	}
}
void Game::drawrect(int x,int y,int w,int h,Color c) {
	for (int i = x - w / 2; i <= x + w / 2; i++) {
		for (int j = y - h / 2; j <= y + h / 2; j++) {
			if (i > 0 && i < gfx.ScreenWidth && j>0 && j < gfx.ScreenHeight) {
				gfx.PutPixel(i, j, c);
			}
		}
	}
}
void Game::drawemptyrect(int x, int y, int w, int h, Color c) {
	w = w / 2;
	h = h / 2;
	for (int i = x - w; i <= x + w; i++) {
		if (i > 0 && i < gfx.ScreenWidth && y - h>0) {
			gfx.PutPixel(i, y - h, c);
		}
		if (i > 0 && i < gfx.ScreenWidth && y + h <gfx.ScreenHeight) {
			gfx.PutPixel(i, y + h, c);
		}
	}

	for (int i = y - h; i <=y + h; i++){
		if (i > 0 && i < gfx.ScreenHeight && x - w>0) {
			gfx.PutPixel(x - w, i, c);
		}
		if (i > 0 && i < gfx.ScreenHeight && x + w < gfx.ScreenWidth){
			gfx.PutPixel(x+w, i, c);
		}
	}

}

void Game::trackpoop(int target) {
	const int xnextpoz = poopz[target].getx() + poopz[target].getvx();
	const int ynextpoz = poopz[target].gety() + poopz[target].getvy();

	face.moveto(xnextpoz, ynextpoz);
}
void Game::choosetarget(int range) {
	for (int j = 0; j < n; j++)
	{
		if (!poopz[j].isEaten())
		{
			if (poopz[j].colliding(face, range))
			{
				previoustarget = target;
				target = j;
			}
		}
	}
}

/*
void Game::drawline(int x1, int x2, int y1, int y2) {
	int dx = x2 - x1;
	int dy = y2 - y1;
	for (int x = x1; x <= x2; x++) {

		int y = y1 + dy * (x - x1) / dx;
		gfx.PutPixel(x, y, 255, 255, 255);
	}
}
*/

// call   recursiontry(1,1,SW,SH);
void Game::nonrecursiontrack() {
	if (face.GetX() > 0 && face.GetX() <= centerx) {
		if (face.GetY() > 0 && face.GetY() <= centery) {
			face.moveto(centerx / 2, centery + centery / 2); // cadran 2 to cadran 3
		}
		else {
			face.moveto(centerx + centerx / 2, centery + centery / 2); //cadran 3 to cadran 4
		}
	}
	else {
		if (face.GetY() > 0 && face.GetY() <= centery) {
			face.moveto(centerx / 2, centery / 2);  // cadran 1 to cadran 2
		}
		else {
			face.moveto(centerx + centerx / 2, centery / 2); //cadran 4 to cadran 1
		}
	}
}
