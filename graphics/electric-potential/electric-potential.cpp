/*********************************************************************
ELECTRIC POTENTIAL

It plots the distribution of potentials between two parallel plates at
different potentials, like a capacitor. Using a recursive algorithm
instead of array-based algorithms

Programmed by:

	JOSE LUIS DE LA CRUZ LAZARO
	ramondc@hotmail.com

	UNIVERSIDAD NACIONAL DE INGENIERIA
	Faculty of Electrical and Electronic Engineering
	Lima-Peru

 HISTORY...

 >> Version 2 - 30-III-2024
	- The initially proposed algorithm is improved, correcting the
	  recursive calculation of potentials on the edges of the
	  recursive square.
	- Documentation is added to improve future work
	- The algorithm is coded using a CElectricPotential class, which
	  organizesand streamlines the coding.
	- The Grafxy class is improved to draw directly in memory, using
	  bitmaps and putimage, instead of using the putpixel function,
	  which is quite slow. Considerably increasing the program's
	  performance in time

>> Version 1 - 06-X-1999
	- First version for Borland C++ 3.1 and Turbo C 3.0

*********************************************************************/

#include "graphics.h"
#include "grafxy.h"
#include <vector>

unsigned char Paleta[256*3];

void DefinirPaleta(unsigned char r, unsigned char g, unsigned char b)
{
	unsigned char cont1;
	int cont;

	for (cont = 0; cont < 256; cont++)
	{
		Paleta[cont * 3 + 0] = r * (cont + 1);
		Paleta[cont * 3 + 1] = g * (cont + 1);
		Paleta[cont * 3 + 2] = b * (cont + 1);
	}
}

// Converts a palette index (cColor) to an RGB color, using the palette loaded from the image
int getRGBFromPalette(unsigned char cColor)
{
	int rgb = Paleta[cColor * 3 + 2];			// blue
	rgb = (rgb << 8) + Paleta[cColor * 3 + 1];	// green
	rgb = (rgb << 8) + Paleta[cColor * 3 + 0];	// red

	return rgb;
}

class CElectricPotential {
public:
	struct Potential {
		double x; // x coordinate
		double y; // y coordinate
		double V; // Potential in volts
		bool isDetermined = false;
	};

	CElectricPotential(const CRegionXY& Campo, double _potentialUP, double _potentialDOWN);
	~CElectricPotential();

	bool getPotential(const double &x, const double &y, double& potential);

	void calculatePotentials(double x, double y, double radio, double V1, double V2, double V4, double V5);


	const CRegionXY campo;

	const double potentialUP;
	const double potentialDOWN;
};

CElectricPotential::CElectricPotential(const CRegionXY& Campo, double _potentialUP, double _potentialDOWN)
	: campo(Campo), potentialUP(_potentialUP), potentialDOWN(_potentialDOWN)
{
}

CElectricPotential::~CElectricPotential()
{
}

bool CElectricPotential::getPotential(const double &x, const double &y, double& potential)
{

	double delta = 0.05;

	if (campo.xmin()-delta < x && x < campo.xmax()+delta){
		if (fabs(y- campo.ymin()) < delta) {
			potential = potentialDOWN;
			return true;
		}
		else if (fabs(campo.ymax() - y) < delta) {
			potential = potentialUP;
			return true;
		}
	}
	potential = 0.0;
	return false;
}

void CElectricPotential::calculatePotentials(double x, double y, double radio, double V1, double V2, double V4, double V5)
{
	// Division of the analysis region to apply the recursive algorithm
	//
	// 01 -----13----- V5 -----14----- 02
	// |               |               |	
	// |               |               |
	// 20----- 05 ---- 10 ---- 06 -----15
	// |               |               |
	// |               |               |
	// V2 ---- 09 ----  00 ---- 11 ---- V4
	// |               |               |
	// |               |               |
	// 19----- 08 ---- 12 ---- 07 -----16
	// |               |               |	
	// |               |               |
	// 04---- 18-----  V1 -----17------ 03


	double R = radio / 4;

	std::vector<Potential> vPotentials(21);

	// Calculate coordinates of the potentials
	vPotentials[0].x = x + 2 * R;
	vPotentials[0].y = y + 2 * R;

	vPotentials[1].x = x;
	vPotentials[1].y = y+radio;
	vPotentials[2].x = x + radio;
	vPotentials[2].y = y + radio;
	vPotentials[3].x = x + radio;
	vPotentials[3].y = y;
	vPotentials[4].x = x;
	vPotentials[4].y = y;

	vPotentials[5].x = x + R;
	vPotentials[5].y = y + 3 * R;
	vPotentials[6].x = x + 3 * R;
	vPotentials[6].y = y + 3*R;
	vPotentials[7].x = x + 3 * R;
	vPotentials[7].y = y + R;
	vPotentials[8].x = x + R;
	vPotentials[8].y = y + R;

	vPotentials[9].x = x + R;
	vPotentials[9].y = y + 2 * R;
	vPotentials[10].x = x + 2 * R;
	vPotentials[10].y = y + 3*R;
	vPotentials[11].x = x + 3 * R;
	vPotentials[11].y = y + 2 * R;
	vPotentials[12].x = x + 2 * R;
	vPotentials[12].y = y + R;

	vPotentials[13].x = x + R;
	vPotentials[13].y = y + radio;
	vPotentials[14].x = x + 3 * R;
	vPotentials[14].y = y + radio;
	vPotentials[15].x = x + radio;
	vPotentials[15].y = y + 3 * R;
	vPotentials[16].x = x + radio;
	vPotentials[16].y = y + R;

	vPotentials[17].x = x + 3*R;
	vPotentials[17].y = y;
	vPotentials[18].x = x + R;
	vPotentials[18].y = y;
	vPotentials[19].x = x;
	vPotentials[19].y = y + R;
	vPotentials[20].x = x;
	vPotentials[20].y = y + 2*R;
	
	// Calculate if any of the potentials already have a certain value
	for (auto& potential : vPotentials) 		
		potential.isDetermined = getPotential(potential.x, potential.y, potential.V);


	// Calculates the potentials of the quadrants, based on the potentials of the parent square

	vPotentials[0].V = (V1 + V2 + V4 + V5)/4;


	// 1rd Cuadrant
	if(vPotentials[1].isDetermined) 	
		vPotentials[5].V = (vPotentials[1].V + V5 + vPotentials[0].V + V2) / 4;
	else {
		vPotentials[5].V = vPotentials[1].V = (vPotentials[0].V + V2 + V5) / 3;
	}

	if (vPotentials[13].isDetermined == false)
		vPotentials[13].V = (vPotentials[1].V + V5)*0.5;

	if (vPotentials[10].isDetermined == false)
		vPotentials[10].V = (V5 + vPotentials[0].V)*0.5;

	if (vPotentials[9].isDetermined == false)
		vPotentials[9].V = (V2 + vPotentials[0].V)*0.5;

	if (vPotentials[20].isDetermined == false)
		vPotentials[20].V = (vPotentials[1].V+V2)*0.5;

	// 2nd Cuadrant
	if (vPotentials[2].isDetermined)
		vPotentials[6].V = (vPotentials[2].V + V4 + vPotentials[0].V + V5) / 4;
	else
		vPotentials[6].V = vPotentials[2].V = (vPotentials[0].V + V5 + V4) / 3;

	if (vPotentials[14].isDetermined == false)
		vPotentials[14].V = (V5+vPotentials[2].V)*0.5;

	if (vPotentials[15].isDetermined == false)
		vPotentials[15].V = (vPotentials[2].V+V4)*0.5;

	if (vPotentials[11].isDetermined == false)
		vPotentials[11].V = (vPotentials[0].V + V4)*0.5;

	if (vPotentials[10].isDetermined == false)
		vPotentials[10].V = (V5+vPotentials[0].V)*0.5;

	// 3rd Cuadrant
	if (vPotentials[3].isDetermined)
		vPotentials[7].V = (vPotentials[0].V + V4 + vPotentials[3].V + V1) / 4;
	else
		vPotentials[7].V = vPotentials[3].V = (vPotentials[0].V + V4 + V1) / 3;

	if (vPotentials[11].isDetermined == false)
		vPotentials[11].V = (vPotentials[0].V+V4)*0.5;

	if (vPotentials[16].isDetermined == false)
		vPotentials[16].V = (V4+vPotentials[3].V)*0.5;

	if (vPotentials[17].isDetermined == false)
		vPotentials[17].V = (V1+vPotentials[3].V)*0.5;

	if (vPotentials[12].isDetermined == false)
		vPotentials[12].V = (vPotentials[0].V+V1)*0.5;

	// 4rd Cuadrant
	if (vPotentials[4].isDetermined)
		vPotentials[8].V = (V2+vPotentials[0].V + V1 + vPotentials[4].V) / 4;
	else
		vPotentials[8].V = vPotentials[4].V = (V2+vPotentials[0].V + V1) / 3;

	if (vPotentials[18].isDetermined == false)
		vPotentials[18].V = (vPotentials[4].V + V1)*0.5;

	if (vPotentials[19].isDetermined == false)
		vPotentials[19].V = (V2 + vPotentials[4].V)*0.5;

	if (vPotentials[9].isDetermined == false)
		vPotentials[9].V = (V2 + vPotentials[0].V)*0.5;

	if (vPotentials[12].isDetermined == false)
		vPotentials[12].V = (vPotentials[0].V + V1)*0.5;
	
	int i;
	for (i = 0; i < 21; i++) {
		int color = (vPotentials[i].V - potentialUP) * 255 / (potentialDOWN - potentialUP);
		//campo.punto(vPotentials[i].x, vPotentials[i].y, getRGBFromPalette(color));		
		campo.punto(vPotentials[i].x, vPotentials[i].y, RGB(0, color, 255 - color));
		//outtextxy((vPotentials[i].x-campo.xmin())/(campo.xmax()- campo.xmin())*1024*0.8, (768-(vPotentials[i].y - campo.ymin()) / (campo.ymax() - campo.ymin()) * 768)*0.8, std::to_string(vPotentials[i].V).c_str());
	}
	
	if (radio > 0.01)
	{
		R = radio / 2;
		calculatePotentials(x, y + R, R, vPotentials[9].V, vPotentials[20].V, vPotentials[10].V, vPotentials[13].V);
		calculatePotentials(x + R, y + R, R, vPotentials[11].V, vPotentials[10].V, vPotentials[15].V, vPotentials[14].V);
		calculatePotentials(x + R, y, R, vPotentials[17].V, vPotentials[12].V, vPotentials[16].V, vPotentials[11].V);
		calculatePotentials(x, y, R, vPotentials[18].V, vPotentials[19].V, vPotentials[12].V, vPotentials[9].V);
	}
		
}

void main()
{
	// Init WinBGI window
	initwindow(1024, 768, "The world of chaos in C++ - Unlimited Programming");

	CRegionXY campo(0, 10, 0, 10);

	//DefinirPaleta(10, 5, 1);

	CElectricPotential ep(campo, 1, -1);
	
	// Calculates electrical potentials recursively and saves them in a bitmap that resides in memory
	ep.calculatePotentials(0, 0, 10, ep.potentialDOWN, 0, 0, ep.potentialUP);

	// Display the draw directly from the bitmap to the screen using putimage
	// You can comment out this line and enable WinBGI putpixel painting (in grafxy.h) to see recursive painting in slow motion	 
	campo.draw();

	getch();
	closegraph();

}

