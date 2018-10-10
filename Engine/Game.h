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
	void drawracket(int x, int y, int type);
	void drawball(int x, int y);
	bool isracket1Colliding(int x, int y, int width, int height,
		int x1, int y1, int width1, int height1,int &vx,int &vy);
	bool isracket2colliding(int x, int y, int width, int height,
		int x1, int y1, int width1, int height1, int &vx, int &vy);
	int checkboundary_x(int x, int width,int lb, int ub);
	int checkboundary_y(int y, int height,int lb, int ub);
	void drawlobby();
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
		/*------Racket-------*/
			int racket_width = 9;
			int racket_height = 30;
			/*------Racket1------*/
				int racket1x = 200;
				int racket1y= 300;
			/*-------------------*/
			/*-------Racket2-----*/
				int racket2x = 600;
				int racket2y = 300;
			/*-------------------*/
		/*-------------------*/
		/*------Ball---------*/
			int ballx = 300;
			int bally = 300;
			int ballvx = 2;
			int ballvy = 2;
			int ball_width = 16;
			int ball_height = 18;
		/*--------------------*/
		/*--------Other-------*/
			bool collided = false;
	/********************************/
};