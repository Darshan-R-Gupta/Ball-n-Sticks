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
#include <random>
#define	VK_W 87
#define VK_S 83
#define VK_A 65
#define VK_D 68
Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd )
{
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution <int> xDist(50, 750);
	std::uniform_int_distribution <int> yDist(50, 550);
	ballx = xDist(rng);
	bally = yDist(rng);
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
	/*------------Racket1 movement-------------------*/
	if (wnd.kbd.KeyIsPressed(VK_LEFT)) {
		if (racket1x >= 55) racket1x -= 3;
		else { racket1x = 55; }
	}
	if (wnd.kbd.KeyIsPressed(VK_RIGHT)) {
		if (racket1x <= (395 - racket_width))	racket1x += 3;
		else { racket1x = 395 - racket_width; }
	}
	if (wnd.kbd.KeyIsPressed(VK_UP)) {
		if(racket1y >= (55 + racket_height)) racket1y -= 3;
		else racket1y = 55;
	}
	if (wnd.kbd.KeyIsPressed(VK_DOWN)) {
		if(racket1y <= (545 - racket_height)) racket1y += 3;
		else racket1y = 545- racket_height;
	}
	if (isracket1Colliding(racket1x,racket1y,racket_width,racket_height, ballx, bally,ball_width, ball_height, ballvx, ballvy) ) {
		collided = true;
		
	}

	/*---------------------------------------------*/

	/*------------Racket2 movement-------------------*/
	if (wnd.kbd.KeyIsPressed(VK_D)) {
		if (racket2x <= 745 - racket_width)	racket2x += 3;
		else racket2x = 745 - racket_width;
	}
	if (wnd.kbd.KeyIsPressed(VK_A)) {
		if(racket2x >= 405) racket2x -= 3;
		else { racket2x = 405; }
	}
	if (wnd.kbd.KeyIsPressed(VK_W)) {
		if(racket2y >= 55 + racket_height)racket2y -= 3;
		else racket2y = 55;
	}
	if (wnd.kbd.KeyIsPressed(VK_S)) {
		if(racket2y <= 545 - racket_height) racket2y += 3;
		else racket2y = 545 - racket_height;
	}
	if (isracket2colliding(racket2x, racket2y, racket_width, racket_height,
		ballx, bally, ball_width, ball_height, ballvx, ballvy)) {
		collided = true;
	}
	/*---------------------------------------------*/
	ballx += ballvx;
	bally += ballvy;
	{
		const int balloldx = ballx;
		const int balloldy = bally;
		ballx = checkboundary_x(ballx, 16, 55, 750);
		bally = checkboundary_y(bally, 18, 55, 550);
		if (ballx != balloldx) {
			ballvx *= -1;
		}
		if (bally != balloldy) {
			ballvy *= -1;
		}
	}
	
}

void Game::drawracket(int x, int y, int type)
{
	if (type == 1) {
		gfx.PutPixel(0 + x, 0 + y, 255, 0, 0);
		gfx.PutPixel(1 + x, 0 + y, 255, 0, 0);
		gfx.PutPixel(2 + x, 0 + y, 255, 0, 0);
		gfx.PutPixel(3 + x, 0 + y, 255, 0, 0);
		gfx.PutPixel(4 + x, 0 + y, 255, 0, 0);
		gfx.PutPixel(5 + x, 0 + y, 255, 0, 0);
		gfx.PutPixel(6 + x, 0 + y, 255, 0, 0);
		gfx.PutPixel(7 + x, 0 + y, 255, 0, 0);
		gfx.PutPixel(8 + x, 0 + y, 255, 0, 0);
		gfx.PutPixel(0 + x, 1 + y, 255, 0, 0);
		gfx.PutPixel(1 + x, 1 + y, 255, 0, 0);
		gfx.PutPixel(2 + x, 1 + y, 255, 0, 0);
		gfx.PutPixel(3 + x, 1 + y, 255, 0, 0);
		gfx.PutPixel(4 + x, 1 + y, 255, 0, 0);
		gfx.PutPixel(5 + x, 1 + y, 255, 0, 0);
		gfx.PutPixel(6 + x, 1 + y, 255, 0, 0);
		gfx.PutPixel(7 + x, 1 + y, 255, 0, 0);
		gfx.PutPixel(8 + x, 1 + y, 255, 0, 0);
		gfx.PutPixel(0 + x, 2 + y, 255, 0, 0);
		gfx.PutPixel(1 + x, 2 + y, 255, 0, 0);
		gfx.PutPixel(2 + x, 2 + y, 255, 0, 0);
		gfx.PutPixel(3 + x, 2 + y, 255, 0, 0);
		gfx.PutPixel(4 + x, 2 + y, 255, 0, 0);
		gfx.PutPixel(5 + x, 2 + y, 255, 0, 0);
		gfx.PutPixel(6 + x, 2 + y, 255, 0, 0);
		gfx.PutPixel(7 + x, 2 + y, 255, 0, 0);
		gfx.PutPixel(8 + x, 2 + y, 255, 0, 0);
		gfx.PutPixel(0 + x, 3 + y, 255, 0, 0);
		gfx.PutPixel(1 + x, 3 + y, 255, 0, 0);
		gfx.PutPixel(2 + x, 3 + y, 255, 0, 0);
		gfx.PutPixel(3 + x, 3 + y, 255, 0, 0);
		gfx.PutPixel(4 + x, 3 + y, 255, 0, 0);
		gfx.PutPixel(5 + x, 3 + y, 255, 0, 0);
		gfx.PutPixel(6 + x, 3 + y, 255, 0, 0);
		gfx.PutPixel(7 + x, 3 + y, 255, 0, 0);
		gfx.PutPixel(8 + x, 3 + y, 255, 0, 0);
		gfx.PutPixel(0 + x, 4 + y, 255, 0, 0);
		gfx.PutPixel(1 + x, 4 + y, 255, 0, 0);
		gfx.PutPixel(2 + x, 4 + y, 255, 0, 0);
		gfx.PutPixel(3 + x, 4 + y, 255, 0, 0);
		gfx.PutPixel(4 + x, 4 + y, 255, 0, 0);
		gfx.PutPixel(5 + x, 4 + y, 255, 0, 0);
		gfx.PutPixel(6 + x, 4 + y, 255, 0, 0);
		gfx.PutPixel(7 + x, 4 + y, 255, 0, 0);
		gfx.PutPixel(8 + x, 4 + y, 255, 0, 0);
		gfx.PutPixel(0 + x, 5 + y, 255, 0, 0);
		gfx.PutPixel(1 + x, 5 + y, 255, 0, 0);
		gfx.PutPixel(2 + x, 5 + y, 255, 0, 0);
		gfx.PutPixel(3 + x, 5 + y, 255, 0, 0);
		gfx.PutPixel(4 + x, 5 + y, 255, 0, 0);
		gfx.PutPixel(5 + x, 5 + y, 255, 0, 0);
		gfx.PutPixel(6 + x, 5 + y, 255, 0, 0);
		gfx.PutPixel(7 + x, 5 + y, 255, 0, 0);
		gfx.PutPixel(8 + x, 5 + y, 255, 0, 0);
		gfx.PutPixel(0 + x, 6 + y, 255, 0, 0);
		gfx.PutPixel(1 + x, 6 + y, 255, 0, 0);
		gfx.PutPixel(2 + x, 6 + y, 255, 0, 0);
		gfx.PutPixel(3 + x, 6 + y, 255, 0, 0);
		gfx.PutPixel(4 + x, 6 + y, 255, 0, 0);
		gfx.PutPixel(5 + x, 6 + y, 255, 0, 0);
		gfx.PutPixel(6 + x, 6 + y, 255, 0, 0);
		gfx.PutPixel(7 + x, 6 + y, 255, 0, 0);
		gfx.PutPixel(8 + x, 6 + y, 255, 0, 0);
		gfx.PutPixel(0 + x, 7 + y, 255, 0, 0);
		gfx.PutPixel(1 + x, 7 + y, 255, 0, 0);
		gfx.PutPixel(2 + x, 7 + y, 255, 0, 0);
		gfx.PutPixel(3 + x, 7 + y, 255, 0, 0);
		gfx.PutPixel(4 + x, 7 + y, 255, 0, 0);
		gfx.PutPixel(5 + x, 7 + y, 255, 0, 0);
		gfx.PutPixel(6 + x, 7 + y, 255, 0, 0);
		gfx.PutPixel(7 + x, 7 + y, 255, 0, 0);
		gfx.PutPixel(8 + x, 7 + y, 255, 0, 0);
		gfx.PutPixel(0 + x, 8 + y, 255, 0, 0);
		gfx.PutPixel(1 + x, 8 + y, 255, 0, 0);
		gfx.PutPixel(2 + x, 8 + y, 255, 0, 0);
		gfx.PutPixel(3 + x, 8 + y, 255, 0, 0);
		gfx.PutPixel(4 + x, 8 + y, 255, 0, 0);
		gfx.PutPixel(5 + x, 8 + y, 255, 0, 0);
		gfx.PutPixel(6 + x, 8 + y, 255, 0, 0);
		gfx.PutPixel(7 + x, 8 + y, 255, 0, 0);
		gfx.PutPixel(8 + x, 8 + y, 255, 0, 0);
		gfx.PutPixel(0 + x, 9 + y, 255, 0, 0);
		gfx.PutPixel(1 + x, 9 + y, 255, 0, 0);
		gfx.PutPixel(2 + x, 9 + y, 255, 0, 0);
		gfx.PutPixel(3 + x, 9 + y, 255, 0, 0);
		gfx.PutPixel(4 + x, 9 + y, 255, 0, 0);
		gfx.PutPixel(5 + x, 9 + y, 255, 0, 0);
		gfx.PutPixel(6 + x, 9 + y, 255, 0, 0);
		gfx.PutPixel(7 + x, 9 + y, 255, 0, 0);
		gfx.PutPixel(8 + x, 9 + y, 255, 0, 0);
		gfx.PutPixel(0 + x, 10 + y, 255, 0, 0);
		gfx.PutPixel(1 + x, 10 + y, 255, 0, 0);
		gfx.PutPixel(2 + x, 10 + y, 255, 0, 0);
		gfx.PutPixel(3 + x, 10 + y, 255, 0, 0);
		gfx.PutPixel(4 + x, 10 + y, 255, 0, 0);
		gfx.PutPixel(5 + x, 10 + y, 255, 0, 0);
		gfx.PutPixel(6 + x, 10 + y, 255, 0, 0);
		gfx.PutPixel(7 + x, 10 + y, 255, 0, 0);
		gfx.PutPixel(8 + x, 10 + y, 255, 0, 0);
		gfx.PutPixel(0 + x, 11 + y, 255, 0, 0);
		gfx.PutPixel(1 + x, 11 + y, 255, 0, 0);
		gfx.PutPixel(2 + x, 11 + y, 255, 0, 0);
		gfx.PutPixel(3 + x, 11 + y, 255, 0, 0);
		gfx.PutPixel(4 + x, 11 + y, 255, 0, 0);
		gfx.PutPixel(5 + x, 11 + y, 255, 0, 0);
		gfx.PutPixel(6 + x, 11 + y, 255, 0, 0);
		gfx.PutPixel(7 + x, 11 + y, 255, 0, 0);
		gfx.PutPixel(8 + x, 11 + y, 255, 0, 0);
		gfx.PutPixel(0 + x, 12 + y, 255, 0, 0);
		gfx.PutPixel(1 + x, 12 + y, 255, 0, 0);
		gfx.PutPixel(2 + x, 12 + y, 255, 0, 0);
		gfx.PutPixel(3 + x, 12 + y, 255, 0, 0);
		gfx.PutPixel(4 + x, 12 + y, 255, 0, 0);
		gfx.PutPixel(5 + x, 12 + y, 255, 0, 0);
		gfx.PutPixel(6 + x, 12 + y, 255, 0, 0);
		gfx.PutPixel(7 + x, 12 + y, 255, 0, 0);
		gfx.PutPixel(8 + x, 12 + y, 255, 0, 0);
		gfx.PutPixel(0 + x, 13 + y, 255, 0, 0);
		gfx.PutPixel(1 + x, 13 + y, 255, 0, 0);
		gfx.PutPixel(2 + x, 13 + y, 255, 0, 0);
		gfx.PutPixel(3 + x, 13 + y, 255, 0, 0);
		gfx.PutPixel(4 + x, 13 + y, 255, 0, 0);
		gfx.PutPixel(5 + x, 13 + y, 255, 0, 0);
		gfx.PutPixel(6 + x, 13 + y, 255, 0, 0);
		gfx.PutPixel(7 + x, 13 + y, 255, 0, 0);
		gfx.PutPixel(8 + x, 13 + y, 255, 0, 0);
		gfx.PutPixel(0 + x, 14 + y, 255, 0, 0);
		gfx.PutPixel(1 + x, 14 + y, 255, 0, 0);
		gfx.PutPixel(2 + x, 14 + y, 255, 0, 0);
		gfx.PutPixel(3 + x, 14 + y, 255, 0, 0);
		gfx.PutPixel(4 + x, 14 + y, 255, 0, 0);
		gfx.PutPixel(5 + x, 14 + y, 255, 0, 0);
		gfx.PutPixel(6 + x, 14 + y, 255, 0, 0);
		gfx.PutPixel(7 + x, 14 + y, 255, 0, 0);
		gfx.PutPixel(8 + x, 14 + y, 255, 0, 0);
		gfx.PutPixel(0 + x, 15 + y, 255, 0, 0);
		gfx.PutPixel(1 + x, 15 + y, 255, 0, 0);
		gfx.PutPixel(2 + x, 15 + y, 255, 0, 0);
		gfx.PutPixel(3 + x, 15 + y, 255, 0, 0);
		gfx.PutPixel(4 + x, 15 + y, 255, 0, 0);
		gfx.PutPixel(5 + x, 15 + y, 255, 0, 0);
		gfx.PutPixel(6 + x, 15 + y, 255, 0, 0);
		gfx.PutPixel(7 + x, 15 + y, 255, 0, 0);
		gfx.PutPixel(8 + x, 15 + y, 255, 0, 0);
		gfx.PutPixel(0 + x, 16 + y, 255, 0, 0);
		gfx.PutPixel(1 + x, 16 + y, 255, 0, 0);
		gfx.PutPixel(2 + x, 16 + y, 255, 0, 0);
		gfx.PutPixel(3 + x, 16 + y, 255, 0, 0);
		gfx.PutPixel(4 + x, 16 + y, 255, 0, 0);
		gfx.PutPixel(5 + x, 16 + y, 255, 0, 0);
		gfx.PutPixel(6 + x, 16 + y, 255, 0, 0);
		gfx.PutPixel(7 + x, 16 + y, 255, 0, 0);
		gfx.PutPixel(8 + x, 16 + y, 255, 0, 0);
		gfx.PutPixel(0 + x, 17 + y, 255, 0, 0);
		gfx.PutPixel(1 + x, 17 + y, 255, 0, 0);
		gfx.PutPixel(2 + x, 17 + y, 255, 0, 0);
		gfx.PutPixel(3 + x, 17 + y, 255, 0, 0);
		gfx.PutPixel(4 + x, 17 + y, 255, 0, 0);
		gfx.PutPixel(5 + x, 17 + y, 255, 0, 0);
		gfx.PutPixel(6 + x, 17 + y, 255, 0, 0);
		gfx.PutPixel(7 + x, 17 + y, 255, 0, 0);
		gfx.PutPixel(8 + x, 17 + y, 255, 0, 0);
		gfx.PutPixel(0 + x, 18 + y, 255, 0, 0);
		gfx.PutPixel(1 + x, 18 + y, 255, 0, 0);
		gfx.PutPixel(2 + x, 18 + y, 255, 0, 0);
		gfx.PutPixel(3 + x, 18 + y, 255, 0, 0);
		gfx.PutPixel(4 + x, 18 + y, 255, 0, 0);
		gfx.PutPixel(5 + x, 18 + y, 255, 0, 0);
		gfx.PutPixel(6 + x, 18 + y, 255, 0, 0);
		gfx.PutPixel(7 + x, 18 + y, 255, 0, 0);
		gfx.PutPixel(8 + x, 18 + y, 255, 0, 0);
		gfx.PutPixel(0 + x, 19 + y, 255, 0, 0);
		gfx.PutPixel(1 + x, 19 + y, 255, 0, 0);
		gfx.PutPixel(2 + x, 19 + y, 255, 0, 0);
		gfx.PutPixel(3 + x, 19 + y, 255, 0, 0);
		gfx.PutPixel(4 + x, 19 + y, 255, 0, 0);
		gfx.PutPixel(5 + x, 19 + y, 255, 0, 0);
		gfx.PutPixel(6 + x, 19 + y, 255, 0, 0);
		gfx.PutPixel(7 + x, 19 + y, 255, 0, 0);
		gfx.PutPixel(8 + x, 19 + y, 255, 0, 0);
		gfx.PutPixel(0 + x, 20 + y, 255, 0, 0);
		gfx.PutPixel(1 + x, 20 + y, 255, 0, 0);
		gfx.PutPixel(2 + x, 20 + y, 255, 0, 0);
		gfx.PutPixel(3 + x, 20 + y, 255, 0, 0);
		gfx.PutPixel(4 + x, 20 + y, 255, 0, 0);
		gfx.PutPixel(5 + x, 20 + y, 255, 0, 0);
		gfx.PutPixel(6 + x, 20 + y, 255, 0, 0);
		gfx.PutPixel(7 + x, 20 + y, 255, 0, 0);
		gfx.PutPixel(8 + x, 20 + y, 255, 0, 0);
		gfx.PutPixel(0 + x, 21 + y, 255, 0, 0);
		gfx.PutPixel(1 + x, 21 + y, 255, 0, 0);
		gfx.PutPixel(2 + x, 21 + y, 255, 0, 0);
		gfx.PutPixel(3 + x, 21 + y, 255, 0, 0);
		gfx.PutPixel(4 + x, 21 + y, 255, 0, 0);
		gfx.PutPixel(5 + x, 21 + y, 255, 0, 0);
		gfx.PutPixel(6 + x, 21 + y, 255, 0, 0);
		gfx.PutPixel(7 + x, 21 + y, 255, 0, 0);
		gfx.PutPixel(8 + x, 21 + y, 255, 0, 0);
		gfx.PutPixel(0 + x, 22 + y, 255, 0, 0);
		gfx.PutPixel(1 + x, 22 + y, 255, 0, 0);
		gfx.PutPixel(2 + x, 22 + y, 255, 0, 0);
		gfx.PutPixel(3 + x, 22 + y, 255, 0, 0);
		gfx.PutPixel(4 + x, 22 + y, 255, 0, 0);
		gfx.PutPixel(5 + x, 22 + y, 255, 0, 0);
		gfx.PutPixel(6 + x, 22 + y, 255, 0, 0);
		gfx.PutPixel(7 + x, 22 + y, 255, 0, 0);
		gfx.PutPixel(8 + x, 22 + y, 255, 0, 0);
		gfx.PutPixel(0 + x, 23 + y, 255, 0, 0);
		gfx.PutPixel(1 + x, 23 + y, 255, 0, 0);
		gfx.PutPixel(2 + x, 23 + y, 255, 0, 0);
		gfx.PutPixel(3 + x, 23 + y, 255, 0, 0);
		gfx.PutPixel(4 + x, 23 + y, 255, 0, 0);
		gfx.PutPixel(5 + x, 23 + y, 255, 0, 0);
		gfx.PutPixel(6 + x, 23 + y, 255, 0, 0);
		gfx.PutPixel(7 + x, 23 + y, 255, 0, 0);
		gfx.PutPixel(8 + x, 23 + y, 255, 0, 0);
		gfx.PutPixel(0 + x, 24 + y, 255, 0, 0);
		gfx.PutPixel(1 + x, 24 + y, 255, 0, 0);
		gfx.PutPixel(2 + x, 24 + y, 255, 0, 0);
		gfx.PutPixel(3 + x, 24 + y, 255, 0, 0);
		gfx.PutPixel(4 + x, 24 + y, 255, 0, 0);
		gfx.PutPixel(5 + x, 24 + y, 255, 0, 0);
		gfx.PutPixel(6 + x, 24 + y, 255, 0, 0);
		gfx.PutPixel(7 + x, 24 + y, 255, 0, 0);
		gfx.PutPixel(8 + x, 24 + y, 255, 0, 0);
		gfx.PutPixel(0 + x, 25 + y, 255, 0, 0);
		gfx.PutPixel(1 + x, 25 + y, 255, 0, 0);
		gfx.PutPixel(2 + x, 25 + y, 255, 0, 0);
		gfx.PutPixel(3 + x, 25 + y, 255, 0, 0);
		gfx.PutPixel(4 + x, 25 + y, 255, 0, 0);
		gfx.PutPixel(5 + x, 25 + y, 255, 0, 0);
		gfx.PutPixel(6 + x, 25 + y, 255, 0, 0);
		gfx.PutPixel(7 + x, 25 + y, 255, 0, 0);
		gfx.PutPixel(8 + x, 25 + y, 255, 0, 0);
		gfx.PutPixel(0 + x, 26 + y, 255, 0, 0);
		gfx.PutPixel(1 + x, 26 + y, 255, 0, 0);
		gfx.PutPixel(2 + x, 26 + y, 255, 0, 0);
		gfx.PutPixel(3 + x, 26 + y, 255, 0, 0);
		gfx.PutPixel(4 + x, 26 + y, 255, 0, 0);
		gfx.PutPixel(5 + x, 26 + y, 255, 0, 0);
		gfx.PutPixel(6 + x, 26 + y, 255, 0, 0);
		gfx.PutPixel(7 + x, 26 + y, 255, 0, 0);
		gfx.PutPixel(8 + x, 26 + y, 255, 0, 0);
		gfx.PutPixel(0 + x, 27 + y, 255, 0, 0);
		gfx.PutPixel(1 + x, 27 + y, 255, 0, 0);
		gfx.PutPixel(2 + x, 27 + y, 255, 0, 0);
		gfx.PutPixel(3 + x, 27 + y, 255, 0, 0);
		gfx.PutPixel(4 + x, 27 + y, 255, 0, 0);
		gfx.PutPixel(5 + x, 27 + y, 255, 0, 0);
		gfx.PutPixel(6 + x, 27 + y, 255, 0, 0);
		gfx.PutPixel(7 + x, 27 + y, 255, 0, 0);
		gfx.PutPixel(8 + x, 27 + y, 255, 0, 0);
		gfx.PutPixel(0 + x, 28 + y, 255, 0, 0);
		gfx.PutPixel(1 + x, 28 + y, 255, 0, 0);
		gfx.PutPixel(2 + x, 28 + y, 255, 0, 0);
		gfx.PutPixel(3 + x, 28 + y, 255, 0, 0);
		gfx.PutPixel(4 + x, 28 + y, 255, 0, 0);
		gfx.PutPixel(5 + x, 28 + y, 255, 0, 0);
		gfx.PutPixel(6 + x, 28 + y, 255, 0, 0);
		gfx.PutPixel(7 + x, 28 + y, 255, 0, 0);
		gfx.PutPixel(8 + x, 28 + y, 255, 0, 0);
		gfx.PutPixel(0 + x, 29 + y, 255, 0, 0);
		gfx.PutPixel(1 + x, 29 + y, 255, 0, 0);
		gfx.PutPixel(2 + x, 29 + y, 255, 0, 0);
		gfx.PutPixel(3 + x, 29 + y, 255, 0, 0);
		gfx.PutPixel(4 + x, 29 + y, 255, 0, 0);
		gfx.PutPixel(5 + x, 29 + y, 255, 0, 0);
		gfx.PutPixel(6 + x, 29 + y, 255, 0, 0);
		gfx.PutPixel(7 + x, 29 + y, 255, 0, 0);
		gfx.PutPixel(8 + x, 29 + y, 255, 0, 0);

	}
	else {
		gfx.PutPixel(0 + x, 0 + y, 0, 255, 0);
		gfx.PutPixel(1 + x, 0 + y, 0, 255, 0);
		gfx.PutPixel(2 + x, 0 + y, 0, 255, 0);
		gfx.PutPixel(3 + x, 0 + y, 0, 255, 0);
		gfx.PutPixel(4 + x, 0 + y, 0, 255, 0);
		gfx.PutPixel(5 + x, 0 + y, 0, 255, 0);
		gfx.PutPixel(6 + x, 0 + y, 0, 255, 0);
		gfx.PutPixel(7 + x, 0 + y, 0, 255, 0);
		gfx.PutPixel(8 + x, 0 + y, 0, 255, 0);
		gfx.PutPixel(0 + x, 1 + y, 0, 255, 0);
		gfx.PutPixel(1 + x, 1 + y, 0, 255, 0);
		gfx.PutPixel(2 + x, 1 + y, 0, 255, 0);
		gfx.PutPixel(3 + x, 1 + y, 0, 255, 0);
		gfx.PutPixel(4 + x, 1 + y, 0, 255, 0);
		gfx.PutPixel(5 + x, 1 + y, 0, 255, 0);
		gfx.PutPixel(6 + x, 1 + y, 0, 255, 0);
		gfx.PutPixel(7 + x, 1 + y, 0, 255, 0);
		gfx.PutPixel(8 + x, 1 + y, 0, 255, 0);
		gfx.PutPixel(0 + x, 2 + y, 0, 255, 0);
		gfx.PutPixel(1 + x, 2 + y, 0, 255, 0);
		gfx.PutPixel(2 + x, 2 + y, 0, 255, 0);
		gfx.PutPixel(3 + x, 2 + y, 0, 255, 0);
		gfx.PutPixel(4 + x, 2 + y, 0, 255, 0);
		gfx.PutPixel(5 + x, 2 + y, 0, 255, 0);
		gfx.PutPixel(6 + x, 2 + y, 0, 255, 0);
		gfx.PutPixel(7 + x, 2 + y, 0, 255, 0);
		gfx.PutPixel(8 + x, 2 + y, 0, 255, 0);
		gfx.PutPixel(0 + x, 3 + y, 0, 255, 0);
		gfx.PutPixel(1 + x, 3 + y, 0, 255, 0);
		gfx.PutPixel(2 + x, 3 + y, 0, 255, 0);
		gfx.PutPixel(3 + x, 3 + y, 0, 255, 0);
		gfx.PutPixel(4 + x, 3 + y, 0, 255, 0);
		gfx.PutPixel(5 + x, 3 + y, 0, 255, 0);
		gfx.PutPixel(6 + x, 3 + y, 0, 255, 0);
		gfx.PutPixel(7 + x, 3 + y, 0, 255, 0);
		gfx.PutPixel(8 + x, 3 + y, 0, 255, 0);
		gfx.PutPixel(0 + x, 4 + y, 0, 255, 0);
		gfx.PutPixel(1 + x, 4 + y, 0, 255, 0);
		gfx.PutPixel(2 + x, 4 + y, 0, 255, 0);
		gfx.PutPixel(3 + x, 4 + y, 0, 255, 0);
		gfx.PutPixel(4 + x, 4 + y, 0, 255, 0);
		gfx.PutPixel(5 + x, 4 + y, 0, 255, 0);
		gfx.PutPixel(6 + x, 4 + y, 0, 255, 0);
		gfx.PutPixel(7 + x, 4 + y, 0, 255, 0);
		gfx.PutPixel(8 + x, 4 + y, 0, 255, 0);
		gfx.PutPixel(0 + x, 5 + y, 0, 255, 0);
		gfx.PutPixel(1 + x, 5 + y, 0, 255, 0);
		gfx.PutPixel(2 + x, 5 + y, 0, 255, 0);
		gfx.PutPixel(3 + x, 5 + y, 0, 255, 0);
		gfx.PutPixel(4 + x, 5 + y, 0, 255, 0);
		gfx.PutPixel(5 + x, 5 + y, 0, 255, 0);
		gfx.PutPixel(6 + x, 5 + y, 0, 255, 0);
		gfx.PutPixel(7 + x, 5 + y, 0, 255, 0);
		gfx.PutPixel(8 + x, 5 + y, 0, 255, 0);
		gfx.PutPixel(0 + x, 6 + y, 0, 255, 0);
		gfx.PutPixel(1 + x, 6 + y, 0, 255, 0);
		gfx.PutPixel(2 + x, 6 + y, 0, 255, 0);
		gfx.PutPixel(3 + x, 6 + y, 0, 255, 0);
		gfx.PutPixel(4 + x, 6 + y, 0, 255, 0);
		gfx.PutPixel(5 + x, 6 + y, 0, 255, 0);
		gfx.PutPixel(6 + x, 6 + y, 0, 255, 0);
		gfx.PutPixel(7 + x, 6 + y, 0, 255, 0);
		gfx.PutPixel(8 + x, 6 + y, 0, 255, 0);
		gfx.PutPixel(0 + x, 7 + y, 0, 255, 0);
		gfx.PutPixel(1 + x, 7 + y, 0, 255, 0);
		gfx.PutPixel(2 + x, 7 + y, 0, 255, 0);
		gfx.PutPixel(3 + x, 7 + y, 0, 255, 0);
		gfx.PutPixel(4 + x, 7 + y, 0, 255, 0);
		gfx.PutPixel(5 + x, 7 + y, 0, 255, 0);
		gfx.PutPixel(6 + x, 7 + y, 0, 255, 0);
		gfx.PutPixel(7 + x, 7 + y, 0, 255, 0);
		gfx.PutPixel(8 + x, 7 + y, 0, 255, 0);
		gfx.PutPixel(0 + x, 8 + y, 0, 255, 0);
		gfx.PutPixel(1 + x, 8 + y, 0, 255, 0);
		gfx.PutPixel(2 + x, 8 + y, 0, 255, 0);
		gfx.PutPixel(3 + x, 8 + y, 0, 255, 0);
		gfx.PutPixel(4 + x, 8 + y, 0, 255, 0);
		gfx.PutPixel(5 + x, 8 + y, 0, 255, 0);
		gfx.PutPixel(6 + x, 8 + y, 0, 255, 0);
		gfx.PutPixel(7 + x, 8 + y, 0, 255, 0);
		gfx.PutPixel(8 + x, 8 + y, 0, 255, 0);
		gfx.PutPixel(0 + x, 9 + y, 0, 255, 0);
		gfx.PutPixel(1 + x, 9 + y, 0, 255, 0);
		gfx.PutPixel(2 + x, 9 + y, 0, 255, 0);
		gfx.PutPixel(3 + x, 9 + y, 0, 255, 0);
		gfx.PutPixel(4 + x, 9 + y, 0, 255, 0);
		gfx.PutPixel(5 + x, 9 + y, 0, 255, 0);
		gfx.PutPixel(6 + x, 9 + y, 0, 255, 0);
		gfx.PutPixel(7 + x, 9 + y, 0, 255, 0);
		gfx.PutPixel(8 + x, 9 + y, 0, 255, 0);
		gfx.PutPixel(0 + x, 10 + y, 0, 255, 0);
		gfx.PutPixel(1 + x, 10 + y, 0, 255, 0);
		gfx.PutPixel(2 + x, 10 + y, 0, 255, 0);
		gfx.PutPixel(3 + x, 10 + y, 0, 255, 0);
		gfx.PutPixel(4 + x, 10 + y, 0, 255, 0);
		gfx.PutPixel(5 + x, 10 + y, 0, 255, 0);
		gfx.PutPixel(6 + x, 10 + y, 0, 255, 0);
		gfx.PutPixel(7 + x, 10 + y, 0, 255, 0);
		gfx.PutPixel(8 + x, 10 + y, 0, 255, 0);
		gfx.PutPixel(0 + x, 11 + y, 0, 255, 0);
		gfx.PutPixel(1 + x, 11 + y, 0, 255, 0);
		gfx.PutPixel(2 + x, 11 + y, 0, 255, 0);
		gfx.PutPixel(3 + x, 11 + y, 0, 255, 0);
		gfx.PutPixel(4 + x, 11 + y, 0, 255, 0);
		gfx.PutPixel(5 + x, 11 + y, 0, 255, 0);
		gfx.PutPixel(6 + x, 11 + y, 0, 255, 0);
		gfx.PutPixel(7 + x, 11 + y, 0, 255, 0);
		gfx.PutPixel(8 + x, 11 + y, 0, 255, 0);
		gfx.PutPixel(0 + x, 12 + y, 0, 255, 0);
		gfx.PutPixel(1 + x, 12 + y, 0, 255, 0);
		gfx.PutPixel(2 + x, 12 + y, 0, 255, 0);
		gfx.PutPixel(3 + x, 12 + y, 0, 255, 0);
		gfx.PutPixel(4 + x, 12 + y, 0, 255, 0);
		gfx.PutPixel(5 + x, 12 + y, 0, 255, 0);
		gfx.PutPixel(6 + x, 12 + y, 0, 255, 0);
		gfx.PutPixel(7 + x, 12 + y, 0, 255, 0);
		gfx.PutPixel(8 + x, 12 + y, 0, 255, 0);
		gfx.PutPixel(0 + x, 13 + y, 0, 255, 0);
		gfx.PutPixel(1 + x, 13 + y, 0, 255, 0);
		gfx.PutPixel(2 + x, 13 + y, 0, 255, 0);
		gfx.PutPixel(3 + x, 13 + y, 0, 255, 0);
		gfx.PutPixel(4 + x, 13 + y, 0, 255, 0);
		gfx.PutPixel(5 + x, 13 + y, 0, 255, 0);
		gfx.PutPixel(6 + x, 13 + y, 0, 255, 0);
		gfx.PutPixel(7 + x, 13 + y, 0, 255, 0);
		gfx.PutPixel(8 + x, 13 + y, 0, 255, 0);
		gfx.PutPixel(0 + x, 14 + y, 0, 255, 0);
		gfx.PutPixel(1 + x, 14 + y, 0, 255, 0);
		gfx.PutPixel(2 + x, 14 + y, 0, 255, 0);
		gfx.PutPixel(3 + x, 14 + y, 0, 255, 0);
		gfx.PutPixel(4 + x, 14 + y, 0, 255, 0);
		gfx.PutPixel(5 + x, 14 + y, 0, 255, 0);
		gfx.PutPixel(6 + x, 14 + y, 0, 255, 0);
		gfx.PutPixel(7 + x, 14 + y, 0, 255, 0);
		gfx.PutPixel(8 + x, 14 + y, 0, 255, 0);
		gfx.PutPixel(0 + x, 15 + y, 0, 255, 0);
		gfx.PutPixel(1 + x, 15 + y, 0, 255, 0);
		gfx.PutPixel(2 + x, 15 + y, 0, 255, 0);
		gfx.PutPixel(3 + x, 15 + y, 0, 255, 0);
		gfx.PutPixel(4 + x, 15 + y, 0, 255, 0);
		gfx.PutPixel(5 + x, 15 + y, 0, 255, 0);
		gfx.PutPixel(6 + x, 15 + y, 0, 255, 0);
		gfx.PutPixel(7 + x, 15 + y, 0, 255, 0);
		gfx.PutPixel(8 + x, 15 + y, 0, 255, 0);
		gfx.PutPixel(0 + x, 16 + y, 0, 255, 0);
		gfx.PutPixel(1 + x, 16 + y, 0, 255, 0);
		gfx.PutPixel(2 + x, 16 + y, 0, 255, 0);
		gfx.PutPixel(3 + x, 16 + y, 0, 255, 0);
		gfx.PutPixel(4 + x, 16 + y, 0, 255, 0);
		gfx.PutPixel(5 + x, 16 + y, 0, 255, 0);
		gfx.PutPixel(6 + x, 16 + y, 0, 255, 0);
		gfx.PutPixel(7 + x, 16 + y, 0, 255, 0);
		gfx.PutPixel(8 + x, 16 + y, 0, 255, 0);
		gfx.PutPixel(0 + x, 17 + y, 0, 255, 0);
		gfx.PutPixel(1 + x, 17 + y, 0, 255, 0);
		gfx.PutPixel(2 + x, 17 + y, 0, 255, 0);
		gfx.PutPixel(3 + x, 17 + y, 0, 255, 0);
		gfx.PutPixel(4 + x, 17 + y, 0, 255, 0);
		gfx.PutPixel(5 + x, 17 + y, 0, 255, 0);
		gfx.PutPixel(6 + x, 17 + y, 0, 255, 0);
		gfx.PutPixel(7 + x, 17 + y, 0, 255, 0);
		gfx.PutPixel(8 + x, 17 + y, 0, 255, 0);
		gfx.PutPixel(0 + x, 18 + y, 0, 255, 0);
		gfx.PutPixel(1 + x, 18 + y, 0, 255, 0);
		gfx.PutPixel(2 + x, 18 + y, 0, 255, 0);
		gfx.PutPixel(3 + x, 18 + y, 0, 255, 0);
		gfx.PutPixel(4 + x, 18 + y, 0, 255, 0);
		gfx.PutPixel(5 + x, 18 + y, 0, 255, 0);
		gfx.PutPixel(6 + x, 18 + y, 0, 255, 0);
		gfx.PutPixel(7 + x, 18 + y, 0, 255, 0);
		gfx.PutPixel(8 + x, 18 + y, 0, 255, 0);
		gfx.PutPixel(0 + x, 19 + y, 0, 255, 0);
		gfx.PutPixel(1 + x, 19 + y, 0, 255, 0);
		gfx.PutPixel(2 + x, 19 + y, 0, 255, 0);
		gfx.PutPixel(3 + x, 19 + y, 0, 255, 0);
		gfx.PutPixel(4 + x, 19 + y, 0, 255, 0);
		gfx.PutPixel(5 + x, 19 + y, 0, 255, 0);
		gfx.PutPixel(6 + x, 19 + y, 0, 255, 0);
		gfx.PutPixel(7 + x, 19 + y, 0, 255, 0);
		gfx.PutPixel(8 + x, 19 + y, 0, 255, 0);
		gfx.PutPixel(0 + x, 20 + y, 0, 255, 0);
		gfx.PutPixel(1 + x, 20 + y, 0, 255, 0);
		gfx.PutPixel(2 + x, 20 + y, 0, 255, 0);
		gfx.PutPixel(3 + x, 20 + y, 0, 255, 0);
		gfx.PutPixel(4 + x, 20 + y, 0, 255, 0);
		gfx.PutPixel(5 + x, 20 + y, 0, 255, 0);
		gfx.PutPixel(6 + x, 20 + y, 0, 255, 0);
		gfx.PutPixel(7 + x, 20 + y, 0, 255, 0);
		gfx.PutPixel(8 + x, 20 + y, 0, 255, 0);
		gfx.PutPixel(0 + x, 21 + y, 0, 255, 0);
		gfx.PutPixel(1 + x, 21 + y, 0, 255, 0);
		gfx.PutPixel(2 + x, 21 + y, 0, 255, 0);
		gfx.PutPixel(3 + x, 21 + y, 0, 255, 0);
		gfx.PutPixel(4 + x, 21 + y, 0, 255, 0);
		gfx.PutPixel(5 + x, 21 + y, 0, 255, 0);
		gfx.PutPixel(6 + x, 21 + y, 0, 255, 0);
		gfx.PutPixel(7 + x, 21 + y, 0, 255, 0);
		gfx.PutPixel(8 + x, 21 + y, 0, 255, 0);
		gfx.PutPixel(0 + x, 22 + y, 0, 255, 0);
		gfx.PutPixel(1 + x, 22 + y, 0, 255, 0);
		gfx.PutPixel(2 + x, 22 + y, 0, 255, 0);
		gfx.PutPixel(3 + x, 22 + y, 0, 255, 0);
		gfx.PutPixel(4 + x, 22 + y, 0, 255, 0);
		gfx.PutPixel(5 + x, 22 + y, 0, 255, 0);
		gfx.PutPixel(6 + x, 22 + y, 0, 255, 0);
		gfx.PutPixel(7 + x, 22 + y, 0, 255, 0);
		gfx.PutPixel(8 + x, 22 + y, 0, 255, 0);
		gfx.PutPixel(0 + x, 23 + y, 0, 255, 0);
		gfx.PutPixel(1 + x, 23 + y, 0, 255, 0);
		gfx.PutPixel(2 + x, 23 + y, 0, 255, 0);
		gfx.PutPixel(3 + x, 23 + y, 0, 255, 0);
		gfx.PutPixel(4 + x, 23 + y, 0, 255, 0);
		gfx.PutPixel(5 + x, 23 + y, 0, 255, 0);
		gfx.PutPixel(6 + x, 23 + y, 0, 255, 0);
		gfx.PutPixel(7 + x, 23 + y, 0, 255, 0);
		gfx.PutPixel(8 + x, 23 + y, 0, 255, 0);
		gfx.PutPixel(0 + x, 24 + y, 0, 255, 0);
		gfx.PutPixel(1 + x, 24 + y, 0, 255, 0);
		gfx.PutPixel(2 + x, 24 + y, 0, 255, 0);
		gfx.PutPixel(3 + x, 24 + y, 0, 255, 0);
		gfx.PutPixel(4 + x, 24 + y, 0, 255, 0);
		gfx.PutPixel(5 + x, 24 + y, 0, 255, 0);
		gfx.PutPixel(6 + x, 24 + y, 0, 255, 0);
		gfx.PutPixel(7 + x, 24 + y, 0, 255, 0);
		gfx.PutPixel(8 + x, 24 + y, 0, 255, 0);
		gfx.PutPixel(0 + x, 25 + y, 0, 255, 0);
		gfx.PutPixel(1 + x, 25 + y, 0, 255, 0);
		gfx.PutPixel(2 + x, 25 + y, 0, 255, 0);
		gfx.PutPixel(3 + x, 25 + y, 0, 255, 0);
		gfx.PutPixel(4 + x, 25 + y, 0, 255, 0);
		gfx.PutPixel(5 + x, 25 + y, 0, 255, 0);
		gfx.PutPixel(6 + x, 25 + y, 0, 255, 0);
		gfx.PutPixel(7 + x, 25 + y, 0, 255, 0);
		gfx.PutPixel(8 + x, 25 + y, 0, 255, 0);
		gfx.PutPixel(0 + x, 26 + y, 0, 255, 0);
		gfx.PutPixel(1 + x, 26 + y, 0, 255, 0);
		gfx.PutPixel(2 + x, 26 + y, 0, 255, 0);
		gfx.PutPixel(3 + x, 26 + y, 0, 255, 0);
		gfx.PutPixel(4 + x, 26 + y, 0, 255, 0);
		gfx.PutPixel(5 + x, 26 + y, 0, 255, 0);
		gfx.PutPixel(6 + x, 26 + y, 0, 255, 0);
		gfx.PutPixel(7 + x, 26 + y, 0, 255, 0);
		gfx.PutPixel(8 + x, 26 + y, 0, 255, 0);
		gfx.PutPixel(0 + x, 27 + y, 0, 255, 0);
		gfx.PutPixel(1 + x, 27 + y, 0, 255, 0);
		gfx.PutPixel(2 + x, 27 + y, 0, 255, 0);
		gfx.PutPixel(3 + x, 27 + y, 0, 255, 0);
		gfx.PutPixel(4 + x, 27 + y, 0, 255, 0);
		gfx.PutPixel(5 + x, 27 + y, 0, 255, 0);
		gfx.PutPixel(6 + x, 27 + y, 0, 255, 0);
		gfx.PutPixel(7 + x, 27 + y, 0, 255, 0);
		gfx.PutPixel(8 + x, 27 + y, 0, 255, 0);
		gfx.PutPixel(0 + x, 28 + y, 0, 255, 0);
		gfx.PutPixel(1 + x, 28 + y, 0, 255, 0);
		gfx.PutPixel(2 + x, 28 + y, 0, 255, 0);
		gfx.PutPixel(3 + x, 28 + y, 0, 255, 0);
		gfx.PutPixel(4 + x, 28 + y, 0, 255, 0);
		gfx.PutPixel(5 + x, 28 + y, 0, 255, 0);
		gfx.PutPixel(6 + x, 28 + y, 0, 255, 0);
		gfx.PutPixel(7 + x, 28 + y, 0, 255, 0);
		gfx.PutPixel(8 + x, 28 + y, 0, 255, 0);
		gfx.PutPixel(0 + x, 29 + y, 0, 255, 0);
		gfx.PutPixel(1 + x, 29 + y, 0, 255, 0);
		gfx.PutPixel(2 + x, 29 + y, 0, 255, 0);
		gfx.PutPixel(3 + x, 29 + y, 0, 255, 0);
		gfx.PutPixel(4 + x, 29 + y, 0, 255, 0);
		gfx.PutPixel(5 + x, 29 + y, 0, 255, 0);
		gfx.PutPixel(6 + x, 29 + y, 0, 255, 0);
		gfx.PutPixel(7 + x, 29 + y, 0, 255, 0);
		gfx.PutPixel(8 + x, 29 + y, 0, 255, 0);

	}
}
void Game::drawball(int x, int y) {
	gfx.PutPixel(5 + x, 3 + y, 255, 255, 255);
	gfx.PutPixel(6 + x, 3 + y, 255, 255, 255);
	gfx.PutPixel(7 + x, 3 + y, 255, 255, 255);
	gfx.PutPixel(8 + x, 3 + y, 255, 255, 255);
	gfx.PutPixel(9 + x, 3 + y, 255, 255, 255);
	gfx.PutPixel(3 + x, 4 + y, 255, 255, 255);
	gfx.PutPixel(4 + x, 4 + y, 255, 255, 255);
	gfx.PutPixel(5 + x, 4 + y, 255, 255, 255);
	gfx.PutPixel(6 + x, 4 + y, 255, 255, 255);
	gfx.PutPixel(7 + x, 4 + y, 255, 255, 255);
	gfx.PutPixel(8 + x, 4 + y, 255, 255, 255);
	gfx.PutPixel(9 + x, 4 + y, 255, 255, 255);
	gfx.PutPixel(10 + x, 4 + y, 255, 255, 255);
	gfx.PutPixel(11 + x, 4 + y, 255, 255, 255);
	gfx.PutPixel(2 + x, 5 + y, 255, 255, 255);
	gfx.PutPixel(3 + x, 5 + y, 255, 255, 255);
	gfx.PutPixel(4 + x, 5 + y, 255, 255, 255);
	gfx.PutPixel(5 + x, 5 + y, 255, 255, 255);
	gfx.PutPixel(6 + x, 5 + y, 255, 255, 255);
	gfx.PutPixel(7 + x, 5 + y, 255, 255, 255);
	gfx.PutPixel(8 + x, 5 + y, 255, 255, 255);
	gfx.PutPixel(9 + x, 5 + y, 255, 255, 255);
	gfx.PutPixel(10 + x, 5 + y, 255, 255, 255);
	gfx.PutPixel(11 + x, 5 + y, 255, 255, 255);
	gfx.PutPixel(12 + x, 5 + y, 255, 255, 255);
	gfx.PutPixel(2 + x, 6 + y, 255, 255, 255);
	gfx.PutPixel(3 + x, 6 + y, 255, 255, 255);
	gfx.PutPixel(4 + x, 6 + y, 255, 255, 255);
	gfx.PutPixel(5 + x, 6 + y, 255, 255, 255);
	gfx.PutPixel(6 + x, 6 + y, 255, 255, 255);
	gfx.PutPixel(7 + x, 6 + y, 255, 255, 255);
	gfx.PutPixel(8 + x, 6 + y, 255, 255, 255);
	gfx.PutPixel(9 + x, 6 + y, 255, 255, 255);
	gfx.PutPixel(10 + x, 6 + y, 255, 255, 255);
	gfx.PutPixel(11 + x, 6 + y, 255, 255, 255);
	gfx.PutPixel(12 + x, 6 + y, 255, 255, 255);
	gfx.PutPixel(1 + x, 7 + y, 255, 255, 255);
	gfx.PutPixel(2 + x, 7 + y, 255, 255, 255);
	gfx.PutPixel(3 + x, 7 + y, 255, 255, 255);
	gfx.PutPixel(4 + x, 7 + y, 255, 255, 255);
	gfx.PutPixel(5 + x, 7 + y, 255, 255, 255);
	gfx.PutPixel(6 + x, 7 + y, 255, 255, 255);
	gfx.PutPixel(7 + x, 7 + y, 255, 255, 255);
	gfx.PutPixel(8 + x, 7 + y, 255, 255, 255);
	gfx.PutPixel(9 + x, 7 + y, 255, 255, 255);
	gfx.PutPixel(10 + x, 7 + y, 255, 255, 255);
	gfx.PutPixel(11 + x, 7 + y, 255, 255, 255);
	gfx.PutPixel(12 + x, 7 + y, 255, 255, 255);
	gfx.PutPixel(13 + x, 7 + y, 255, 255, 255);
	gfx.PutPixel(1 + x, 8 + y, 255, 255, 255);
	gfx.PutPixel(2 + x, 8 + y, 255, 255, 255);
	gfx.PutPixel(3 + x, 8 + y, 255, 255, 255);
	gfx.PutPixel(4 + x, 8 + y, 255, 255, 255);
	gfx.PutPixel(5 + x, 8 + y, 255, 255, 255);
	gfx.PutPixel(6 + x, 8 + y, 255, 255, 255);
	gfx.PutPixel(7 + x, 8 + y, 255, 255, 255);
	gfx.PutPixel(8 + x, 8 + y, 255, 255, 255);
	gfx.PutPixel(9 + x, 8 + y, 255, 255, 255);
	gfx.PutPixel(10 + x, 8 + y, 255, 255, 255);
	gfx.PutPixel(11 + x, 8 + y, 255, 255, 255);
	gfx.PutPixel(12 + x, 8 + y, 255, 255, 255);
	gfx.PutPixel(13 + x, 8 + y, 255, 255, 255);
	gfx.PutPixel(1 + x, 9 + y, 255, 255, 255);
	gfx.PutPixel(2 + x, 9 + y, 255, 255, 255);
	gfx.PutPixel(3 + x, 9 + y, 255, 255, 255);
	gfx.PutPixel(4 + x, 9 + y, 255, 255, 255);
	gfx.PutPixel(5 + x, 9 + y, 255, 255, 255);
	gfx.PutPixel(6 + x, 9 + y, 255, 255, 255);
	gfx.PutPixel(7 + x, 9 + y, 255, 255, 255);
	gfx.PutPixel(8 + x, 9 + y, 255, 255, 255);
	gfx.PutPixel(9 + x, 9 + y, 255, 255, 255);
	gfx.PutPixel(10 + x, 9 + y, 255, 255, 255);
	gfx.PutPixel(11 + x, 9 + y, 255, 255, 255);
	gfx.PutPixel(12 + x, 9 + y, 255, 255, 255);
	gfx.PutPixel(13 + x, 9 + y, 255, 255, 255);
	gfx.PutPixel(1 + x, 10 + y, 255, 255, 255);
	gfx.PutPixel(2 + x, 10 + y, 255, 255, 255);
	gfx.PutPixel(3 + x, 10 + y, 255, 255, 255);
	gfx.PutPixel(4 + x, 10 + y, 255, 255, 255);
	gfx.PutPixel(5 + x, 10 + y, 255, 255, 255);
	gfx.PutPixel(6 + x, 10 + y, 255, 255, 255);
	gfx.PutPixel(7 + x, 10 + y, 255, 255, 255);
	gfx.PutPixel(8 + x, 10 + y, 255, 255, 255);
	gfx.PutPixel(9 + x, 10 + y, 255, 255, 255);
	gfx.PutPixel(10 + x, 10 + y, 255, 255, 255);
	gfx.PutPixel(11 + x, 10 + y, 255, 255, 255);
	gfx.PutPixel(12 + x, 10 + y, 255, 255, 255);
	gfx.PutPixel(13 + x, 10 + y, 255, 255, 255);
	gfx.PutPixel(2 + x, 11 + y, 255, 255, 255);
	gfx.PutPixel(3 + x, 11 + y, 255, 255, 255);
	gfx.PutPixel(4 + x, 11 + y, 255, 255, 255);
	gfx.PutPixel(5 + x, 11 + y, 255, 255, 255);
	gfx.PutPixel(6 + x, 11 + y, 255, 255, 255);
	gfx.PutPixel(7 + x, 11 + y, 255, 255, 255);
	gfx.PutPixel(8 + x, 11 + y, 255, 255, 255);
	gfx.PutPixel(9 + x, 11 + y, 255, 255, 255);
	gfx.PutPixel(10 + x, 11 + y, 255, 255, 255);
	gfx.PutPixel(11 + x, 11 + y, 255, 255, 255);
	gfx.PutPixel(12 + x, 11 + y, 255, 255, 255);
	gfx.PutPixel(2 + x, 12 + y, 255, 255, 255);
	gfx.PutPixel(3 + x, 12 + y, 255, 255, 255);
	gfx.PutPixel(4 + x, 12 + y, 255, 255, 255);
	gfx.PutPixel(5 + x, 12 + y, 255, 255, 255);
	gfx.PutPixel(6 + x, 12 + y, 255, 255, 255);
	gfx.PutPixel(7 + x, 12 + y, 255, 255, 255);
	gfx.PutPixel(8 + x, 12 + y, 255, 255, 255);
	gfx.PutPixel(9 + x, 12 + y, 255, 255, 255);
	gfx.PutPixel(10 + x, 12 + y, 255, 255, 255);
	gfx.PutPixel(11 + x, 12 + y, 255, 255, 255);
	gfx.PutPixel(12 + x, 12 + y, 255, 255, 255);
	gfx.PutPixel(3 + x, 13 + y, 255, 255, 255);
	gfx.PutPixel(4 + x, 13 + y, 255, 255, 255);
	gfx.PutPixel(5 + x, 13 + y, 255, 255, 255);
	gfx.PutPixel(6 + x, 13 + y, 255, 255, 255);
	gfx.PutPixel(7 + x, 13 + y, 255, 255, 255);
	gfx.PutPixel(8 + x, 13 + y, 255, 255, 255);
	gfx.PutPixel(9 + x, 13 + y, 255, 255, 255);
	gfx.PutPixel(10 + x, 13 + y, 255, 255, 255);
	gfx.PutPixel(11 + x, 13 + y, 255, 255, 255);
	gfx.PutPixel(5 + x, 14 + y, 255, 255, 255);
	gfx.PutPixel(6 + x, 14 + y, 255, 255, 255);
	gfx.PutPixel(7 + x, 14 + y, 255, 255, 255);
	gfx.PutPixel(8 + x, 14 + y, 255, 255, 255);
	gfx.PutPixel(9 + x, 14 + y, 255, 255, 255);

}
void Game::drawlobby()
{
	/*-----------------Boundary Drawing------------------*/
	for (int a = 50; a <= 750; a++) {
		gfx.PutPixel(a, 50, 0, 0, 255);
	}
	for (int b = 50; b <= 750; b++) {
		gfx.PutPixel(b, 550, 0, 0, 255);
	}
	for (int c = 50; c <= 550; c++) {
		gfx.PutPixel(50, c, 0, 0, 255);
	}
	for (int d = 50; d <= 550; d++) {
		gfx.PutPixel(750, d, 0, 0, 255);
	}
	/*---------------------------------------------------*/
	for (int e = 50; e <= 550; e++) {
		gfx.PutPixel(400, e, 255, 255, 255);
	}
}


bool Game::isracket1Colliding(int x, int y, int width, int height, int x1, int y1, int width1, int height1, int &vx, int &vy)
{
		int right = x + width;
		int bottom = y + height;
		int right1 = x1 + width;
		int bottom1 = y1 + height;
		if ((x <= right1) && (x >= x1) && (bottom >= y1) && (y <= bottom1)) {

			const int oldx = x1;
			const int oldy = y1;
			x1 = checkboundary_x(x1, 16, x, 750);
			y1 = checkboundary_y(y1, 18, bottom, 550);
			if ((x1 != oldx) || (y1 != oldy)) {
				if (x1 != oldx) {
					vx *= -1;

				}
				if (y1 != oldy) {
				}

			}
			return true;
		}
		return false;
	}

bool Game::isracket2colliding(int x, int y, int width, int height, int x1, int y1, int width1, int height1, int & vx, int & vy)
{
	int right = x + width;
	int bottom = y + height;
	int right1 = x1 + width;
	int bottom1 = y1 + height;
	if (right >= x1 && x <= right1 && bottom >= y1 && y <= bottom1) {

		const int oldx = x1;
		const int oldy = y1;
		x1 = checkboundary_x(x1, 16, right, 750);
		y1 = checkboundary_y(y1, 18, bottom, 550);
		if ((x1 != oldx) || (y1 != oldy)) {
			if (x1 != oldx) {
				vx *= -1;

			}
			if (y1 != oldy) {
			}

		}
		return true;
	}
	return false;

}
int Game::checkboundary_x(int x, int width, int lb, int ub)
{
	const int right = x + width;
	if (x == racket2x) {
		if (right == lb) {
			return lb;
		}
		else { return x; }
	}
	if (x < lb) {
		return lb;
	}
	else if (right >= ub) {
		return ub - width;
	}
	else {
		return x;
	}
}
int Game::checkboundary_y(int y, int height, int lb, int ub)
{
		const int bottom = y + height;
	if (y < lb) {
		return lb;
	}
	else if (bottom >= ub) {
		return ub - height;
	}
	else {
		return y;
	}
}
void Game::ComposeFrame()
{
	drawlobby();
	drawracket(racket1x, racket1y, 1);
	drawracket(racket2x, racket2y, 2);
	drawball(ballx, bally);
}

