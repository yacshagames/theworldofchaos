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

	/*
	cont = 0;
	cont1 = 0;
	
		// El c¢digo que sigue a continuaci¢n pasa el contenido del array "Paleta"
		//a la paleta de la VGA
		for (cont=0;cont<256;cont++)
		{
			outportb (0x03c8,cont);
			for (cont1=0;cont1<3;cont1++)
				outportb (0x03c9,Paleta[cont][cont1]);
				//cout<<Paleta
		}
		*/
}

// Converts a palette index (cColor) to an RGB color, using the palette loaded from the image
int getRGBFromPalette(unsigned char cColor)
{
	int rgb = Paleta[cColor * 3 + 2];			// blue
	rgb = (rgb << 8) + Paleta[cColor * 3 + 1];	// green
	rgb = (rgb << 8) + Paleta[cColor * 3 + 0];	// red

	return rgb;
}


double ARR = 1.0, ABA = -1.0;
/*
void potenciales(CRegionXY &campo, float x, float y, float radio,
	float arr, float der, float aba, float izq)
{
	// 01 ----------- arr ------------- 02
	// |               |               |	
	// |               |               |
	//  ------ 05 ---- 10 ---- 06 -----
	// |               |               |
	// |               |               |
	//izq ---- 09 ---- 00 ---- 11 ---- der
	// |               |               |
	// |               |               |
	//  ------ 08 ---- 12 ---- 07 -----
	// |               |               |	
	// |               |               |
	// 04 ----------- aba ------------ 03



	float potencial[13][3];

	potencial[0][0] = (izq + der + aba + arr) / 4;
	potencial[1][0] = (izq + arr) / 2;
	potencial[2][0] = (arr + der) / 2;
	potencial[3][0] = (der + aba) / 2;
	potencial[4][0] = (aba + izq) / 2;
	potencial[5][0] = (potencial[1][0] + arr + potencial[0][0] + izq) / 4;
	potencial[6][0] = (arr + potencial[2][0] + der + potencial[0][0]) / 4;
	potencial[7][0] = (potencial[0][0] + der + potencial[3][0] + aba) / 4;
	potencial[8][0] = (izq + potencial[0][0] + aba + potencial[4][0]) / 4;
	potencial[9][0] = (potencial[5][0] + potencial[0][0] + potencial[8][0] + izq) / 4;
	potencial[10][0] = (arr + potencial[6][0] + potencial[0][0] + potencial[5][0]) / 4;
	potencial[11][0] = (potencial[6][0] + der + potencial[7][0] + potencial[0][0]) / 4;
	//potencial[12][0] = (potencial[0][0] + potencial[7][0] + aba + potencial[9][0]) / 4;
	potencial[12][0] = (potencial[0][0] + potencial[7][0] + aba + potencial[8][0]) / 4;

	float R = radio / 4;

	potencial[0][1] = x + 2 * R;
	potencial[0][2] = y + 2 * R;

	potencial[1][1] = x;
	potencial[1][2] = y + radio;
	potencial[2][1] = x + radio;
	potencial[2][2] = y + radio;
	potencial[3][1] = x + radio;
	potencial[3][2] = y;
	potencial[4][1] = x;
	potencial[4][2] = y;

	potencial[5][1] = x + R;
	potencial[5][2] = y + 3 * R;
	potencial[6][1] = x + 3 * R;
	potencial[6][2] = y + 3 * R;
	potencial[7][1] = x + 3 * R;
	potencial[7][2] = y + R;
	potencial[8][1] = x + R;
	potencial[8][2] = y + R;

	potencial[9][1] = x + R;
	potencial[9][2] = y + 2 * R;
	potencial[10][1] = x + 2 * R;
	potencial[10][2] = y + 3 * R;
	potencial[11][1] = x + 3 * R;
	potencial[11][2] = y + 2 * R;
	potencial[12][1] = x + 2 * R;
	potencial[12][2] = y + R;

	

	for (int i = 0; i < 13; i++) {
		//campo.punto(potencial[i][1], potencial[i][2], getRGBFromPalette((int)(100.0 * potencial[i][0])%256));
		int color = (potencial[i][0] - ARR) * 256 / (ABA - ARR);
		campo.punto(potencial[i][1], potencial[i][2], getRGBFromPalette(color));
	}

	if (radio > 0.03)
	{
		R = radio / 2;
		potenciales(campo, x, y + R, R, arr, potencial[10][0], potencial[9][0], izq);
		potenciales(campo, x + R, y + R, R, arr, der, potencial[11][0], potencial[10][0]);
		potenciales(campo, x + R, y, R, potencial[11][0], der, aba, potencial[12][0]);
		potenciales(campo, x, y, R, potencial[9][0], potencial[12][0], aba, izq);
	}


}
*/


class CElectricPotential {
public:
	struct Potential {
		double x; // x coordinate
		double y; // y coordinate
		double V; // Potential in volts
		bool isDetermined = false;
	};

	CElectricPotential(const CRegionXY& Campo);
	~CElectricPotential();

	bool getPotential(const double &x, const double &y, double& potential);

	void calculatePotentials(double x, double y, double radio, double V1, double V2, double V4, double V5);


	const CRegionXY campo;

	double Rx;
	double Ry;

};

CElectricPotential::CElectricPotential(const CRegionXY& Campo)
	: campo(Campo)
{

	Rx = (campo.xmax() - campo.xmin())/4;
	Ry = (campo.ymax() - campo.ymin()) / 4;
}

CElectricPotential::~CElectricPotential()
{
}

bool CElectricPotential::getPotential(const double &x, const double &y, double& potential)
{

	double delta = 0.05;

	if (campo.xmin()-delta < x && x < campo.xmax()+delta){
		if (fabs(y- campo.ymin()) < delta) {
			potential = -1;
			return true;
		}
		else if (fabs(campo.ymax() - y) < delta) {
			potential = 1;
			return true;
		}
	}
	potential = 0.0;
	return false;
}

void CElectricPotential::calculatePotentials(double x, double y, double radio, double V1, double V2, double V4, double V5)
{

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
	
	for (auto& potential : vPotentials) 		
		potential.isDetermined = getPotential(potential.x, potential.y, potential.V);

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
//#ifdef __XX
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
//#endif
	int i;
	for (i = 0; i < 21; i++) {
		//if (vPotentials[i].V == 0)
		//	break;
		//campo.punto(potencial[i][1], potencial[i][2], getRGBFromPalette((int)(100.0 * potencial[i][0])%256));
		int color = (vPotentials[i].V - ARR) * 255 / (ABA - ARR);
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

	CElectricPotential e(campo);
	e.calculatePotentials(0, 0, 10, -1, 0, 0, 1);
	//potenciales(campo, 0, 0, 10, 1, 0, -1, 0);

	campo.draw();

	getch();
	closegraph();

}

