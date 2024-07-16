/***********************************************************************
 ::: PING PONG :::

 Classic Ping Pong game with scores and increased ball speed.
 The game is given to FT5 (the player who first reaches 5 points wins)

Developed by:

	JOSE LUIS DE LA CRUZ LAZARO
	contact@theworldofchaos.com

	YACSHA - Software & Desing, since 1999, Lima-Peru
	>> The World of chaos - EL MUNDO DEL CAOS - Unlimited Programming
	www.theworldofchaos.com

LICENSE
	This file is released under the terms of the BSD 3-Clause License.
	Read LICENSE.txt file for more information.

HISTORY...

 >> Version 2 - 27-III-2024
	- Update graphics/ping-pong - Porting to VC++ 2017 using winbgi
	- Changes the routines for detecting pressed keys, which were
	  previously in the old DOS. Now the WinAPI Keyboard is used (fast
	  routines) when running the program on Windows and the classic
	  WinBGI getch routines are used on other operating systems
	  (slow routines).
	- Add player scores. The game is given to FT5 
	  (the player who first reaches 5 points wins)
	- Add a increased ball speed. To increase the difficulty of the game

>> Version 1 - 8-11-III-2001
	- First version for Borland C++ 3.1 and Turbo C 3.0  

***********************************************************************/

#include "graphics.h"
#include "conio.h"
#include <string>
#include <vector>

const unsigned int maxx = 1024, maxy = 768;
const unsigned int hitRacketsToChangeVelocity = 10;

enum class BOARD {
	NONE,
	PLAYER1,
	PLAYER2,
	HITRACKED,
	// Maximum score with which a player wins the game
	MAXIMUN_SCORE = 5
};

class Ball {	
public:

	Ball();
	BOARD bounce(int j1y, int j2y);
	void move();
	void position();
	void resetposition(); // reset position
	void resetvelocity(); // reset velocity
	void incrementvelocity();// increment velocity

private:
	int dirx, diry;
	int x, y;
	int vel;

	static const int diam;	
};

const int Ball::diam = 6 ;

Ball::Ball() {	
	randomize();	
	resetposition();	
	resetvelocity();
};

// return the winner player or NONE
BOARD Ball::bounce(int j1y, int j2y) {
	BOARD ret = BOARD::NONE;
	if (x > maxx - 10 - (diam))
		if (y > j2y && (y + diam) < j2y + 80)
		{
			dirx = 0;
			// vel++;
			return BOARD::HITRACKED;
		}
	if (x < 10 + (diam))
		if (y > j1y && (y + diam) < j1y + 80)
		{
			dirx = 1;
			//vel++;
			return BOARD::HITRACKED;
		}
	if (x < diam)
		ret = BOARD::PLAYER2;
	if (x > maxx + diam)
		ret = BOARD::PLAYER1;
	if (y > maxy - (diam))
		diry = 0;
	if (y < 2)
		diry = 1;
	return ret;
};

void Ball::move() {
	if (dirx == 1)
		x += vel;
	else
		x -= vel;
	if (diry == 1)
		y += vel;
	else
		y -= vel;
};

void Ball::position() {
	circle(x, y, diam);
}
void Ball::resetposition(){
	x = maxx / 2;
	y = maxy / 2;	
	dirx = random(2) + 1;
	diry = random(2) + 1;	
}

void Ball::resetvelocity()
{
	vel = 3;
}

void Ball::incrementvelocity()
{
	vel++;
}


class Player {
public:
	
	Player(int j);
	void move(int dir);
	void draw();
	void resetposition();
	void resetpoints();
	void incrementvelocity();

	int x, y, xa, ya;

	unsigned int xScoreBoard; // Coordinate x of scoreboard
	unsigned int Points; // Points of player

private:
	static unsigned int mov;
};

unsigned int Player::mov = 6;

Player::Player(int j) {

	if (j == 1) {
		x = 1;

		xScoreBoard = (unsigned int)(0.3*double(maxx));
	}
	else {
		x = maxx - 11;		
		xScoreBoard = (unsigned int)(0.7*double(maxx));
	}
	xa = 10;
	ya = 80;

	resetposition();
	resetpoints();
};

void Player::move(int dir) {
	
	if (dir == 1)
		y = y - mov;
	else
		y = y + mov;

	if (y <= 0)
		y = 0;
	if (y + ya > maxy)
		y = maxy - ya;
};

void Player::draw() {
	bar(x, y, x + xa, y + ya);
	outtextxy(xScoreBoard, 20, std::to_string(Points).c_str());
}
void Player::resetposition(){

	// Init position Y
	y = (maxy - 80) / 2;
}

void Player::resetpoints()
{
	// Init at zero points
	Points = 0;
}

void Player::incrementvelocity(){
	Player::mov++;
}


int main() {

	initwindow(maxx+10, maxy+10, "The world of chaos in C++ - Unlimited Programming");

	std::vector<std::string> winText = {	"Player 1 wins the game",
											"Brilliant game player 2" };
	unsigned int playerWin = 0;

	unsigned int hitRackets = random(1);	

	Ball ball;
	Player j1(1), j2(2);

#ifdef _WIN32

	while ( !(GetKeyState(VK_ESCAPE) & 0x8000) ) // while key pressed is different from the ESC key 
	{
#else

	char keyPressed = 0;

	while (keyPressed != 27) // while keypressed is different from the ESC key 
	{

#endif

#ifdef _WIN32

		// This routine is very fast at detecting pressed keys.But it only works on Windows

		if (GetKeyState('A') & 0x8000/*Check if high-order bit is set (1 << 15)*/){
			// Key A
			j1.move(1);
		}else if (GetKeyState('Z') & 0x8000){
			// Key Z
			j1.move(2);
		}else if (GetKeyState(VK_UP) & 0x8000){
			// Key Up
			j2.move(1);
		}else if (GetKeyState(VK_DOWN) & 0x8000) {
			// Key Down
			j2.move(2);
		}
#else	
		// Keyboard movements are detected slowly.This is because getch is a slow routine.
		// But the advantage is that this routine works on all operating systems that support WinBGI
		
		// Detect key pressed
		if (kbhit()) {
			keyPressed = toupper(getch());
		}

		// Execute the movements of the players
		switch (keyPressed) {
		case 'A':
			j1.move(1);
			break;
		case 'Z':
			j1.move(2);
			break;
		case 'O':
			j2.move(1);
			break;
		case 'L':
			j2.move(2);			
		}

		if (keyPressed > 0) {
			keyPressed = 0;
		}

#endif	
		
		delay(10);
		cleardevice();

		// Calculate points
		BOARD eWinner = ball.bounce(j1.y, j2.y);
		switch (eWinner) {
		case BOARD::PLAYER1:
			j1.Points++; break;
		case BOARD::PLAYER2:
			j2.Points++;
		}

		if (j1.Points == (int)BOARD::MAXIMUN_SCORE)
			playerWin = 1;
		else if( j2.Points == (int)BOARD::MAXIMUN_SCORE )
			playerWin = 2;
			
		if (playerWin > 0) {
			outtextxy(maxx / 2-80, maxy / 2, winText[playerWin - 1].c_str());
			
			// Pauses for 3 seconds to show the winner
			delay(3000);

			// Clear all remaining keys pressed after finishing the game
			while (kbhit()) {
				getch();
			}
			// Show message to continue
			outtextxy(maxx / 2 - 80, maxy / 2+20, "Press any key to continue ....");

			ball.resetposition(); // Reset ball position
			ball.resetvelocity();

			// Reset points to players
			j1.resetpoints();
			j2.resetpoints();

			// Reset positions to players
			j1.resetposition();
			j2.resetposition();		
			
			// Reset playerWin
			playerWin = 0;

			getch(); // pause
		}

		// If any player WIN
		if (eWinner == BOARD::PLAYER1 || eWinner == BOARD::PLAYER2) {
			
			ball.resetposition(); // Reset ball position

			hitRackets = 0; // reset hitRackets

			// Reset positions to players
			j1.resetposition();
			j2.resetposition();

		}
		else if (eWinner == BOARD::HITRACKED) {
			
			// Speed is increased each hitRacketsToChangeVelocity hitRackets
			if ( hitRackets++ == hitRacketsToChangeVelocity) {
				ball.incrementvelocity();
				j1.incrementvelocity();
				j2.incrementvelocity();
				// The next increase in ball speed will be given
				// randomly when player 1 or player 2 hitsRacket.
				hitRackets = random(1);
			}
		}

		ball.move();
		ball.position();
		
		//settextstyle(10, HORIZ_DIR, 10);
		j1.draw();
		j2.draw();
		//settextstyle(10, HORIZ_DIR, 1);
	}

	closegraph();

	return 1;
}
