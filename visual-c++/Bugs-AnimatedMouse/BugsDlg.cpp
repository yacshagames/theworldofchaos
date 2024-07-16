/******************************************************************************
:: BUGS - ANIMATED MOUSE :: BUGS - RATÓN ANIMADO ::

Draws a mouse's face using Bezier curves, and then animates the mouse's face,
like a cartoon.

Spanish:
Dibuja la cara de un raton usando curvas de Bezier, y luego se anima
la cara del ratón, como un dibujo animado.

Developed by:

	Original authors: Amelia
	Improvements added from version 2, thanks to:

	JOSE LUIS DE LA CRUZ LAZARO
	contact@theworldofchaos.com

	YACSHA - Software & Desing, since 1999, Lima-Peru
	>> The World of Chaos - EL MUNDO DEL CAOS - Unlimited Programming
	www.theworldofchaos.com

LICENSE
	This file is released under the terms of the BSD 3-Clause License.
	Read LICENSE.txt file for more information.

HISTORY...

  >> Version 2 - 02-V-2024
	* Thanks to the collaboration of a follower of "the world of chaos",
	  we obtained the first version. From which we have made the
	  following changes:
	- Update visual-c++\Bugs-MouseAnimated - Porting to VC++ 2017.
	- Added mouse face icon
	- Update format code
	- Various bugs are corrected, which do not allow correct mouse animation.
	- A frame with a white background is added, to better show the animation,
	  and to eliminate the bug that caused the buttons to disappear when
	  starting the animation

  >> Version 1 - 02-VI-2000
	- First version developed by Amelia

Warning!!!: These formulas may contain some errors, if you find them, let me
know from the contact page of "The world of chaos", or suggest a
modification in the project's github repository
https://github.com/yacshagames/elmundodelcaos

******************************************************************************/

#include "stdafx.h"
#include "Bugs.h"
#include "BugsDlg.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	// Dialog Data
		//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBugsDlg dialog

CBugsDlg::CBugsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBugsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBugsDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_Detener = false;
}

void CBugsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBugsDlg)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_CUADRO, m_Cuadro);
}

BEGIN_MESSAGE_MAP(CBugsDlg, CDialog)
	//{{AFX_MSG_MAP(CBugsDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(ID_ANIMATE_BUTTON, &CBugsDlg::OnBnClickedAnimateButton)
	ON_BN_CLICKED(ID_STOP_BUTTON, &CBugsDlg::OnBnClickedStopButton)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBugsDlg message handlers

BOOL CBugsDlg::OnInitDialog()
{
	anim = 0;
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	T[0] = 0;	T[1] = 1;	T[2] = 2;	T[3] = 3;	T[4] = 4;
	T[5] = 5;	T[6] = 6;	T[7] = 7;	T[8] = 8;	T[9] = 9;
	T[10] = 10;	T[11] = 11;	T[12] = 12;	T[13] = 13;	T[14] = 14;



	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CBugsDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CBugsDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM)dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
	//Animar();
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CBugsDlg::OnQueryDragIcon()
{
	return (HCURSOR)m_hIcon;
}



void CBugsDlg::Caritura()
{

	//CClientDC dibu(this);

	CDC& dibu = *GetDC();

	int i, k;
	double tt;

	pc[0][0] = c[0] + (-p[0][0] * cos(angulo[0]) + p[0][1] * cos(angulo[1]));
	pc[0][1] = c[1] + (p[0][0] * sin(angulo[0]) + p[0][1] * sin(angulo[1]) - p[0][2]);


	dibu.MoveTo(int(pc[0][0]), int(pc[0][1]));

	for (i = 0; i <= densidad; i++)
	{
		tt = t[0] + (t[npuntos - 1] - t[0])*i / densidad;

		puntoaux[0] = 0;
		puntoaux[1] = 0;
		puntoaux[2] = 0;

		for (k = 0; k <= npuntos - 1; k++)
		{
			puntoaux[0] = puntoaux[0] + p[k][0] * Bezier(tt, k, npuntos - 1);
			puntoaux[1] = puntoaux[1] + p[k][1] * Bezier(tt, k, npuntos - 1);
			puntoaux[2] = puntoaux[2] + p[k][2] * Bezier(tt, k, npuntos - 1);
		}

		CPen NewPen2(PS_SOLID,
			2,
			RGB(0, 0, 255));

		dibu.SelectObject(&NewPen2);

		pc[0][0] = c[0] + (-puntoaux[0] * cos(angulo[0]) + puntoaux[1] * cos(angulo[1]));
		pc[0][1] = c[1] + (puntoaux[0] * sin(angulo[0]) + puntoaux[1] * sin(angulo[1]) - puntoaux[2]);

		dibu.LineTo(int(pc[0][0]), int(pc[0][1]));
	}

	/*

		//Dibuja Curva de Newton
		double auxa = 15;
		double auxb = 30;

		//OnEje3D();
		CClientDC pDC(this);

		/*
		//Convertir P0 a Coordenadas de Monitor
		puntoaux[1] = p[0][1];
		puntoaux[2] = p[0][2];
		puntoaux[3] = p[0][3];
		pc[1][1] = c[1] + puntoaux[2] * cos(angulo[1]) - puntoaux[1] * cos(angulo[0]);
		pc[1][2] = c[2] - puntoaux[3] + puntoaux[2] * sin(angulo[1]) + puntoaux[1] * sin(angulo[0]);
		pDC.MoveTo(pc[1][1], pc[1][2]);
		//Poligono
		CPen LapizVerde(PS_DOT, 1, RGB(0,0,255));
		pDC.SelectObject(&LapizVerde);
		for (int l=0; l<npuntos; l++)
		{
			pc[1][1] = c[1] + p[l][2] * cos(angulo[1]) - p[l][1] * cos(angulo[0]);
			pc[1][2] = c[2] - p[l][3] + p[l][2] * sin(angulo[1]) + p[l][1] * sin(angulo[0]);
			pDC.LineTo(pc[1][1], pc[1][2]);
		}


		//Convertir P0 a Coordenadas de Monitor
		puntoaux[1] = p[0][1];
		puntoaux[2] = p[0][2];
		puntoaux[3] = p[0][3];
		pc[1][1] = c[1] + puntoaux[2] * cos(angulo[1]) - puntoaux[1] * cos(angulo[0]);
		pc[1][2] = c[2] - puntoaux[3] + puntoaux[2] * sin(angulo[1]) + puntoaux[1] * sin(angulo[0]);
		pDC.MoveTo(pc[1][1], pc[1][2]);
		//Curva
		CPen LapizRojo(PS_SOLID, 1, RGB(255,0,0));
		pDC.SelectObject(&LapizRojo);
		//UpdateData(TRUE);
		densidad = 100;//m_densidad;
		int n=7;
		//densidad = 100;
		int korden = 3;
		double tt;

		for (int ka=0; ka<=densidad; ka++)
		{
			puntoaux[1] = 0;
			puntoaux[2] = 0;
			puntoaux[3] = 0;
			puntoaux[4] = 0;

			if (ka==densidad)
			{
				tt = (((T[n+1]-T[korden-1])*(ka-0.000000001))/(densidad)) + T[korden-1];
			}
			else
			{
				tt = (((T[n+1]-T[korden-1])*(ka))/(densidad)) + T[korden-1];
			}

			for (int i=0; i<=n; i++)
			{
				double BAR;
				BAR = N(i,korden,tt);
				puntoaux[1] = (puntoaux[1] + (p[i][1] * N(i,korden,tt)));
				puntoaux[2] = (puntoaux[2] + (p[i][2] * N(i,korden,tt)));
				puntoaux[3] = (puntoaux[3] + (p[i][3] * N(i,korden,tt)));
			}

			pc[1][1] = c[1] + puntoaux[2] * cos(angulo[1]) - puntoaux[1] * cos(angulo[0]);
			pc[1][2] = c[2] - puntoaux[3] + puntoaux[2] * sin(angulo[1]) + puntoaux[1] * sin(angulo[0]);
			if (ka==0)
			{
				pDC.MoveTo(pc[1][1], pc[1][2]);
			}
			else
			{
				pDC.LineTo(pc[1][1], pc[1][2]);
			}
		}
	*/
}




double CBugsDlg::Bezier(double tt, int k, int n)
{
	int i;
	double aux;
	aux = Factorial(n) / (Factorial(n - k)*Factorial(k));
	for (i = 1; i <= n - k; i++)
		aux = aux * (1 - tt);
	for (i = 1; i <= k; i++)
		aux = aux * tt;
	return aux;
}

int CBugsDlg::Factorial(int num)
{
	int i, fact;
	if (num = 0)
		return 1;
	else
	{
		fact = 1;
		for (i = num; i >= 1; i--)
		{
			fact = fact * i;
		}
		return fact;
	}
}

void CBugsDlg::Animar()
{
	angulo[0] = 0.26179;                             // 15/180*PI
	angulo[1] = 0.52358;                             // 30/180*PI
	t[0] = 0; t[1] = 1; t[2] = 1; t[3] = 1; t[4] = 1;

	c[0] = 200;
	c[1] = 200;
	densidad = 10;

	anim = 0;
	int Velocidad = 100;

	while (m_Detener == false) {	

		//Borra la pantalla
		CRect rect;
		m_Cuadro.GetClientRect(rect);
		CDC& dibu = *m_Cuadro.GetDC();
		dibu.Rectangle(rect);

		if (anim == 0)
		{/*
			//boca-21
			npuntos = 3;
			p[0][0] = 100;	p[0][1] = 50 + p[0][0] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[0][2] = -55;
			p[1][0] = 20;	p[1][1] = 180 + p[1][0] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[1][2] = -50;
			p[2][0] = 20;	p[2][1] = 50 + p[3][0] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[2][2] = -30;
			*/
			//Borrar();
			//Invalidate();			
			
			//boca-10
			npuntos = 4;
			p[0][0] = 100;	p[0][1] = 50 + p[0][0] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[0][2] = -55;
			p[1][0] = 20;	p[1][1] = 180 + p[1][0] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[1][2] = -50;
			p[2][0] = 70;	p[2][1] = 400 + p[2][0] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[2][2] = -50;
			p[3][0] = 100;	p[3][1] = 50 + p[3][0] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[3][2] = -55;			

			Caritura();

		}
		else
		{/*
			//boca-10
			npuntos = 4;
			p[0][0] = 100;	p[0][1] = 50 + p[0][0] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[0][2] = -55;
			p[1][0] = 20;	p[1][1] = 180 + p[1][0] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[1][2] = -50;
			p[2][0] = 70;	p[2][1] = 400 + p[2][0] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[2][2] = -50;
			p[3][0] = 100;	p[3][1] = 50 + p[3][0] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[3][2] = -55;
			*/
			//Borrar();
			//Invalidate();
			
			//boca-21			
			npuntos = 4;
			p[0][0] = 100;	p[0][1] = 50+p[0][0] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[0][2] = -55;
			p[1][0] = 20;	p[1][1] = 180+p[1][0] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[1][2] = -340;
			p[2][0] = 20;	p[2][1] = 50-p[2][0] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[2][2] = -150;
			p[3][0] = 100;	p[3][1] = 50+p[3][0] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[3][2] = -55;

			Caritura();
		}
		
		// Se resetea anim
		if (++anim == 2)
			anim = 0;

		//orejaI-1
		npuntos = 5;
		p[0][0] = 20;	p[0][1] = -p[0][0] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[0][2] = 0;
		p[1][0] = 20;	p[1][1] = -p[1][0] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[1][2] = 500;
		p[2][0] = 520;	p[2][1] = -p[2][0] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[2][2] = 500;
		p[3][0] = 520;	p[3][1] = -p[3][0] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[3][2] = 0;
		p[4][0] = 20;	p[4][1] = -p[4][0] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[4][2] = 0;

		Caritura();

		//orejaIch-2
		npuntos = 4;
		p[0][0] = 20;	p[0][1] = -p[0][0] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[0][2] = 0;
		p[1][0] = 100;	p[1][1] = -p[1][0] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[1][2] = 300;
		p[2][0] = 300;	p[2][1] = -p[2][0] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[2][2] = 100;
		p[3][0] = 20;	p[3][1] = -p[4][0] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[3][2] = 0;

		Caritura();


		//orejaD-3
		npuntos = 5;
		p[0][0] = -20;	p[0][1] = -p[0][0] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[0][2] = 0;
		p[1][0] = -20;	p[1][1] = -p[1][0] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[1][2] = 500;
		p[2][0] = -520;	p[2][1] = -p[2][0] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[2][2] = 500;
		p[3][0] = -520;	p[3][1] = -p[3][0] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[3][2] = 0;
		p[4][0] = -20;	p[4][1] = -p[4][0] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[4][2] = 0;

		Caritura();

		//orejaDch-4
		npuntos = 4;
		p[0][0] = -20;	p[0][1] = -p[0][0] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[0][2] = 0;
		p[1][0] = -100;	p[1][1] = -p[1][0] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[1][2] = 300;
		p[2][0] = -300;	p[2][1] = -p[2][0] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[2][2] = 100;
		p[3][0] = -20;	p[3][1] = -p[4][0] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[3][2] = 0;

		Caritura();
		//cabeza-5
		npuntos = 3;
		p[0][0] = -20;	p[0][1] = -p[0][0] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[0][2] = 0;
		p[1][0] = 0;	p[1][1] = -p[1][0] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[1][2] = 50;
		p[2][0] = 20;	p[2][1] = -p[2][0] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[2][2] = 0;

		Caritura();

		//cara-6
		npuntos = 5;
		p[0][0] = 20;	p[0][1] = -p[0][0] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[0][2] = 0;
		p[1][0] = 600;	p[1][1] = -p[1][0] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[1][2] = -300;
		p[2][0] = 0;	p[2][1] = -p[2][0] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[2][2] = -1500;
		p[3][0] = -600;	p[3][1] = -p[3][0] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[3][2] = -300;
		p[4][0] = -20;	p[4][1] = -p[4][0] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[4][2] = 0;

		Caritura();

		//ojoI-7
		npuntos = 5;
		p[0][0] = 20;	p[0][1] = 10;    p[0][2] = 0;
		p[1][0] = 220;	p[1][1] = 10;    p[1][2] = 0;
		p[2][0] = 220;	p[2][1] = 10;    p[2][2] = -300;
		p[3][0] = 20;	p[3][1] = 10;    p[3][2] = -300;
		p[4][0] = 20;	p[4][1] = 10;    p[4][2] = 0;

		Caritura();

		//ojoD-8
		npuntos = 5;
		p[0][0] = 10;	p[0][1] = 30;    p[0][2] = 10;
		p[1][0] = 10;	p[1][1] = 30 + 580 * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[1][2] = 10;
		p[2][0] = 10;	p[2][1] = p[1][1];    p[2][2] = -280;
		p[3][0] = 10;	p[3][1] = 30;    p[3][2] = -280;
		p[4][0] = 10;	p[4][1] = 30;    p[4][2] = 10;

		Caritura();

		//nariz-9
		npuntos = 4;
		p[0][0] = 0;	p[0][1] = p[0][0] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[0][2] = -90;
		p[1][0] = 200;	p[1][1] = p[1][0] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[1][2] = -140;
		p[2][0] = -50;	p[2][1] = -p[2][0] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[2][2] = -140;
		p[3][0] = 0;	p[3][1] = p[3][0] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[3][2] = -90;

		Caritura();


		//ojoIch-11
		npuntos = 5;
		p[0][0] = 20;	p[0][1] = 10;    p[0][2] = -20;
		p[1][0] = 220;	p[1][1] = 10;    p[1][2] = 0;
		p[2][0] = 220;	p[2][1] = 10;    p[2][2] = -300;
		p[3][0] = 20;	p[3][1] = 10;    p[3][2] = -300;
		p[4][0] = 20;	p[4][1] = 10;    p[4][2] = -20;

		Caritura();

		//ojoD-12
		npuntos = 5;
		p[0][0] = 10;	p[0][1] = 30;    p[0][2] = -10;
		p[1][0] = 10;	p[1][1] = 30 + 580 * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[1][2] = 10;
		p[2][0] = 10;	p[2][1] = p[1][1];    p[2][2] = -280;
		p[3][0] = 10;	p[3][1] = 30;    p[3][2] = -280;
		p[4][0] = 10;	p[4][1] = 30;    p[4][2] = -10;

		Caritura();

		//bigoteI1-13
		npuntos = 3;
		p[0][0] = 80;	p[0][1] = 30 + p[0][0] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[0][2] = -30;
		p[1][0] = 120;	p[1][1] = p[1][0] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[1][2] = -50;
		p[2][0] = 180;   p[2][1] = p[2][0] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[2][2] = -20;

		Caritura();

		//bigoteI1-14
		npuntos = 3;
		p[0][0] = 80;	p[0][1] = 30 + p[0][0] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[0][2] = -25;
		p[1][0] = 120;	p[1][1] = p[1][0] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[1][2] = -45;
		p[2][0] = 180;   p[2][1] = p[2][0] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[2][2] = -15;

		Caritura();

		//bigoteI1-15
		npuntos = 3;
		p[0][0] = 80;	p[0][1] = 30 + p[0][0] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[0][2] = -20;
		p[1][0] = 120;	p[1][1] = p[1][0] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[1][2] = -40;
		p[2][0] = 180;   p[2][1] = p[2][0] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[2][2] = -10;

		Caritura();

		//bigoteI1-16
		npuntos = 3;
		p[0][0] = 80;	p[0][1] = 30 + p[0][0] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[0][2] = -35;
		p[1][0] = 120;	p[1][1] = p[1][0] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[1][2] = -55;
		p[2][0] = 180;   p[2][1] = p[2][0] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[2][2] = -25;

		Caritura();

		//bigoteD2-17
		npuntos = 3;
		p[0][0] = 40;	p[0][1] = 50 + p[0][0] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[0][2] = -35;
		p[1][0] = 20;	p[1][1] = 20 + p[1][0] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[1][2] = -100;
		p[2][0] = -60;   p[2][1] = 100 + p[2][0] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[2][2] = -35;

		Caritura();

		//bigoteD2-18
		npuntos = 3;
		p[0][0] = 40;	p[0][1] = 50 + p[0][0] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[0][2] = -30;
		p[1][0] = 20;	p[1][1] = 20 + p[1][0] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[1][2] = -95;
		p[2][0] = -60;   p[2][1] = 100 + p[2][0] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[2][2] = -30;

		Caritura();

		//bigoteD2-19
		npuntos = 3;
		p[0][0] = 40;	p[0][1] = 50 + p[0][0] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[0][2] = -40;
		p[1][0] = 20;	p[1][1] = 20 + p[1][0] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[1][2] = -105;
		p[2][0] = -60;   p[2][1] = 100 + p[2][0] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[2][2] = -40;

		Caritura();

		//bigoteD2-20
		npuntos = 3;
		p[0][0] = 40;	p[0][1] = 50 + p[0][0] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[0][2] = -45;
		p[1][0] = 20;	p[1][1] = 20 + p[1][0] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[1][2] = -110;
		p[2][0] = -60;   p[2][1] = 100 + p[2][0] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[2][2] = -45;

		Caritura();

		//Pone una pausa de "m_Velocidad" milisegundos entre cada cuadro
		//si se presiona el boton Detener se sale del bucle
		if (Pausa(Velocidad))
			break;
	}
}

void CBugsDlg::Borrar()
{
	CClientDC dibu(this);
	int i, k;
	double tt;
	pc[1][1] = c[1] + (-p[0][1] * cos(angulo[0]) + p[0][2] * cos(angulo[1]));
	pc[1][2] = c[2] + (p[0][1] * sin(angulo[0]) + p[0][2] * sin(angulo[1]) - p[0][3]);
	dibu.MoveTo(int(pc[1][1]), int(pc[1][2]));
	for (i = 0; i <= densidad; i++)
	{
		tt = t[0] + (t[npuntos - 1] - t[0])*i / densidad;
		puntoaux[1] = 0; puntoaux[2] = 0; puntoaux[3] = 0;
		for (k = 0; k <= npuntos - 1; k++)
		{
			puntoaux[1] = puntoaux[1] + p[k][1] * Bezier(tt, k, npuntos - 1);
			puntoaux[2] = puntoaux[2] + p[k][2] * Bezier(tt, k, npuntos - 1);
			puntoaux[3] = puntoaux[3] + p[k][3] * Bezier(tt, k, npuntos - 1);
		}
		CPen NewPen2(PS_SOLID,
			40,
			RGB(190, 190, 190));
		dibu.SelectObject(&NewPen2);
		pc[1][1] = c[1] + (-puntoaux[1] * cos(angulo[0]) + puntoaux[2] * cos(angulo[1]));
		pc[1][2] = c[2] + (puntoaux[1] * sin(angulo[0]) + puntoaux[2] * sin(angulo[1]) - puntoaux[3]);

		dibu.LineTo(int(pc[1][1]), int(pc[1][2]));
	}
}


/*
void CBugsDlg::Spline()
{

	//Dibuja Curva de Newton
	double auxa = anga;
	double auxb = angb;

	//OnEje3D();
	CClientDC pDC(this);


	//Convertir P0 a Coordenadas de Monitor
	PtoAux[1] = p3d[0][1];
	PtoAux[2] = p3d[0][2];
	PtoAux[3] = p3d[0][3];
	PtoAuxM[1] = Cx + PtoAux[2] * cos(rad(auxb)) - PtoAux[1] * cos(rad(auxa));
	PtoAuxM[2] = Cy - PtoAux[3] + PtoAux[2] * sin(rad(auxb)) + PtoAux[1] * sin(rad(auxa));
	pDC.MoveTo(PtoAuxM[1], PtoAuxM[2]);
	//Poligono
	CPen LapizVerde(PS_DOT, 1, RGB(0,0,255));
	pDC.SelectObject(&LapizVerde);
	for (int l=1; l<=n; l++)
	{
		PtoAuxM[1] = Cx + p3d[l][2] * cos(rad(auxb)) - p3d[l][1] * cos(rad(auxa));
		PtoAuxM[2] = Cy - p3d[l][3] + p3d[l][2] * sin(rad(auxb)) + p3d[l][1] * sin(rad(auxa));
		pDC.LineTo(PtoAuxM[1], PtoAuxM[2]);
	}


	//Convertir P0 a Coordenadas de Monitor
	PtoAux[1] = p3d[0][1];
	PtoAux[2] = p3d[0][2];
	PtoAux[3] = p3d[0][3];
	PtoAuxM[1] = Cx + PtoAux[2] * cos(rad(auxb)) - PtoAux[1] * cos(rad(auxa));
	PtoAuxM[2] = Cy - PtoAux[3] + PtoAux[2] * sin(rad(auxb)) + PtoAux[1] * sin(rad(auxa));
	pDC.MoveTo(PtoAuxM[1], PtoAuxM[2]);
	//Curva
	CPen LapizRojo(PS_SOLID, 1, RGB(255,0,0));
	pDC.SelectObject(&LapizRojo);
	UpdateData(TRUE);
	densidad = m_densidad;
	for (int ka=0; ka<=densidad; ka++)
	{
		PtoAux[1] = 0;
		PtoAux[2] = 0;
		PtoAux[3] = 0;
		PtoAux[4] = 0;

		if (ka==densidad)
		{
			tt = (((T[n+1]-T[korden-1])*(ka-0.000000001))/(densidad)) + T[korden-1];
		}
		else
		{
			tt = (((T[n+1]-T[korden-1])*(ka))/(densidad)) + T[korden-1];
		}

		for (int i=0; i<=n; i++)
		{
			double BAR;
			BAR = N(i,korden,tt);
			PtoAux[1] = (PtoAux[1] + (p3d[i][1] * N(i,korden,tt)));
			PtoAux[2] = (PtoAux[2] + (p3d[i][2] * N(i,korden,tt)));
			PtoAux[3] = (PtoAux[3] + (p3d[i][3] * N(i,korden,tt)));
		}

		PtoAuxM[1] = Cx + PtoAux[2] * cos(rad(auxb)) - PtoAux[1] * cos(rad(auxa));
		PtoAuxM[2] = Cy - PtoAux[3] + PtoAux[2] * sin(rad(auxb)) + PtoAux[1] * sin(rad(auxa));
		if (ka==0)
		{
			pDC.MoveTo(PtoAuxM[1], PtoAuxM[2]);
		}
		else
		{
			pDC.LineTo(PtoAuxM[1], PtoAuxM[2]);
		}
	}

}*/

double CBugsDlg::N(int i, int k, double tta)
{
	double No;
	double li, ld;

	if (k == 1)
	{
		if (tta >= T[i])
		{
			if (tta < T[i + 1])
			{
				No = 1;
			}
			else
			{
				No = 0;
			}
		}
		else

		{
			No = 0;
		}
	}
	else
	{
		if (tta >= T[i])
		{
			if (tta < T[i + k])
			{
				//Lado izquierdo del B-Spline
				if (T[i + k - 1] == T[i])
				{
					li = 0;
				}
				else
				{
					li = ((tta - T[i]) / (T[i + k - 1] - T[i]));
				}
				//Lado derecho del B-Spline
				if (T[i + k] == T[i + 1])
				{
					ld = 0;
				}
				else
				{
					ld = ((T[i + k] - tta) / (T[i + k] - T[i + 1]));
				}
				//B-Spline
				No = ((li*N(i, k - 1, tta)) + (ld*N(i + 1, k - 1, tta)));
			}
			else
			{
				No = 0;
			}
		}
		else
		{
			No = 0;
		}
	}

	return No;
}


void CBugsDlg::OnBnClickedAnimateButton()
{
	m_Detener = false;
	/*
	if (anim == 0) 
		anim = 1;
	else 
		anim = 0;
	*/
	Animar();
	
}


void CBugsDlg::OnBnClickedStopButton()
{
	m_Detener = true;
}

//Pone una pausa durante "TiempoPausa" milisengundos
BOOL CBugsDlg::Pausa(time_t TiempoPausa)
{
	MSG msg;
	clock_t goal;
	goal = TiempoPausa + clock();
	while (goal > clock())
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			// If it's a quit message, we're out of here.
			if (msg.message == WM_QUIT || m_Detener)
				return 1;
			// Otherwise, dispatch the message.
			DispatchMessage(&msg);
		} // End of PeekMessage while loop.

	return false;
}


void CBugsDlg::OnClose()
{
	m_Detener = false;
	CDialog::OnClose();
}
