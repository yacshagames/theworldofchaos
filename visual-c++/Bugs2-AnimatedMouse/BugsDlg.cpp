/******************************************************************************
:: BUGS2 - ANIMATED MOUSE :: BUGS2 - RATÓN ANIMADO ::

Another style of drawing Bugs:
Draws a mouse's face using Bezier curves, and then animates the mouse's face,
like a cartoon.

Spanish:
Otro estilo de dibujar a Bugs:
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

HISTORY....

  >> Version 2 - 03-V-2024
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
}

void CBugsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBugsDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBugsDlg, CDialog)
	//{{AFX_MSG_MAP(CBugsDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CURVACOMPLETAMAS, OnCurvacompletaMas)
	ON_BN_CLICKED(IDC_CURVABIERTA, OnCurvabierta)
	ON_BN_CLICKED(IDC_CURVACOMPLETAMENOS, OnCurvacompletamenos)
	//}}AFX_MSG_MAP
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
	/*
	T[0] = 0;	T[1] = 0;	T[2] = 0;	T[3] = 1;	T[4] = 1;
	T[5] = 1;	T[6] = 2;	T[7] = 2;	T[8] = 2;	T[9] = 3;
	T[10]=3;	T[11]=3;	T[12]=4;	T[13]=4;	T[14]=4;
	*/

	T[0] = 0;	T[1] = 1;	T[2] = 2;	T[3] = 3;	T[4] = 4;
	T[5] = 5;	T[6] = 6;	T[7] = 7;	T[8] = 8;	T[9] = 9;
	T[10] = 10;	T[11] = 11;	T[12] = 12;	T[13] = 13;	T[14] = 14;

	K = 3;

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
	Inicio();
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CBugsDlg::OnQueryDragIcon()
{
	return (HCURSOR)m_hIcon;
}



void CBugsDlg::Caritura()
{

	//Dibuja Curva de Newton

	//OnEje3D();
	CClientDC pDC(this);

	//Convertir P0 a Coordenadas de Monitor
	puntoaux[1] = p[0][1];
	puntoaux[2] = p[0][2];
	puntoaux[3] = p[0][3];
	pc[1][1] = c[1] + puntoaux[2] * cos(angulo[1]) - puntoaux[1] * cos(angulo[0]);
	pc[1][2] = c[2] - puntoaux[3] + puntoaux[2] * sin(angulo[1]) + puntoaux[1] * sin(angulo[0]);
	pDC.MoveTo(int(pc[1][1]) / 3, int(pc[1][2]) / 3);
	//Curva
	CPen LapizRojo(PS_SOLID, 2, RGB(255, 0, 0));
	pDC.SelectObject(&LapizRojo);

	int n = npuntos - 1;
	densidad = 10;
	int korden = 10;
	double tt;


	for (int ka = 0; ka <= densidad; ka++)
	{
		puntoaux[1] = 0;
		puntoaux[2] = 0;
		puntoaux[3] = 0;
		//puntoaux[4] = 0;

		if (ka == densidad)
		{
			tt = (((T[n + 1] - T[korden - 1])*(ka - 0.000000001)) / (densidad)) + T[korden - 1];
		}
		else
		{
			tt = (((T[n + 1] - T[korden - 1])*(ka)) / (densidad)) + T[korden - 1];
		}


		for (int i = 0; i <= n; i++)
		{
			double BAR;
			BAR = N(i, korden, tt);
			puntoaux[1] = (puntoaux[1] + (p[i][1] * N(i, korden, tt)));
			puntoaux[2] = (puntoaux[2] + (p[i][2] * N(i, korden, tt)));
			puntoaux[3] = (puntoaux[3] + (p[i][3] * N(i, korden, tt)));
		}

		pc[1][1] = c[1] + puntoaux[2] * cos(angulo[1]) - puntoaux[1] * cos(angulo[0]);
		pc[1][2] = c[2] - puntoaux[3] + puntoaux[2] * sin(angulo[1]) + puntoaux[1] * sin(angulo[0]);
		if (ka == 0)
		{
			pDC.MoveTo(int(pc[1][1]) / 3, int(pc[1][2]) / 3);
		}
		else
		{
			pDC.LineTo(int(pc[1][1]) / 3, int(pc[1][2]) / 3);
		}
	}


}



void CBugsDlg::Inicio()
{
	angulo[0] = 0.26179;                             // 15/180*PI
	angulo[1] = 0.52358;                             // 30/180*PI
	t[0] = 0; t[1] = 1; t[2] = 1; t[3] = 1; t[4] = 1;

	c[1] = 520;//200
	c[2] = 440;//200
	densidad = 10;

	if (anim == 0)
	{

		c[1] = 580;
		c[2] = 880;

		//boca-21


		//Borrar();
		//boca-10
		npuntos = 3;

		p[0][1] = 80;	p[0][2] = 30 + p[0][1] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[0][3] = -25;
		p[1][1] = 120;	p[1][2] = p[1][1] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[1][3] = -45;
		p[2][1] = 180;   p[2][2] = p[2][1] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[2][3] = -15;

		Caritura();

		c[1] = 520;
		c[2] = 440;


	}
	else
	{

		c[1] = 520;
		c[2] = 880;
		
		//boca-10

		npuntos = 4;
		p[0][1] = 100;	p[0][2] = 50 + p[0][1] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[0][3] = -55;
		p[1][1] = 20;	p[1][2] = 180 + p[1][1] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[1][3] = -50;
		p[2][1] = 70;	p[2][2] = 400 + p[2][1] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[2][3] = -50;
		p[3][1] = 100;	p[3][2] = 50 + p[3][1] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[3][3] = -55;

		//Borrar();
		//boca-21
		npuntos = 3;
		p[0][1] = 100;	p[0][2] = 50 + p[0][1] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[0][3] = -55;
		p[1][1] = 20;	p[1][2] = 180 + p[1][1] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[1][3] = -50;
		p[2][1] = 20;	p[2][2] = 50 + p[3][1] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[2][3] = -30;

		Escalar();
		Caritura();

		c[1] = 520;
		c[2] = 440;
	}

	//orejaI-1
	npuntos = 5;
	p[0][1] = 20;	p[0][2] = -p[0][1] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[0][3] = 0;
	p[1][1] = 20;	p[1][2] = -p[1][1] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[1][3] = 500;
	p[2][1] = 520;	p[2][2] = -p[2][1] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[2][3] = 500;
	p[3][1] = 520;	p[3][2] = -p[3][1] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[3][3] = 0;
	p[4][1] = 20;	p[4][2] = -p[4][1] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[4][3] = 0;

	Caritura();

	//orejaIch-2
	npuntos = 4;
	p[0][1] = 20;	p[0][2] = -p[0][1] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[0][3] = 0;
	p[1][1] = 100;	p[1][2] = -p[1][1] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[1][3] = 300;
	p[2][1] = 300;	p[2][2] = -p[2][1] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[2][3] = 100;
	p[3][1] = 20;	p[3][2] = -p[4][1] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[3][3] = 0;

	Caritura();


	//orejaD-3
	npuntos = 5;
	p[0][1] = -20;	p[0][2] = -p[0][1] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[0][3] = 0;
	p[1][1] = -20;	p[1][2] = -p[1][1] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[1][3] = 500;
	p[2][1] = -520;	p[2][2] = -p[2][1] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[2][3] = 500;
	p[3][1] = -520;	p[3][2] = -p[3][1] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[3][3] = 0;
	p[4][1] = -20;	p[4][2] = -p[4][1] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[4][3] = 0;

	Caritura();

	//orejaDch-4
	npuntos = 4;
	p[0][1] = -20;	p[0][2] = -p[0][1] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[0][3] = 0;
	p[1][1] = -100;	p[1][2] = -p[1][1] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[1][3] = 300;
	p[2][1] = -300;	p[2][2] = -p[2][1] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[2][3] = 100;
	p[3][1] = -20;	p[3][2] = -p[4][1] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[3][3] = 0;

	Caritura();
	//cabeza-5
	npuntos = 3;
	p[0][1] = -20;	p[0][2] = -p[0][1] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[0][3] = 0;
	p[1][1] = 0;	p[1][2] = -p[1][1] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[1][3] = 50;
	p[2][1] = 20;	p[2][2] = -p[2][1] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[2][3] = 0;

	c[1] = 440;
	c[2] = 680;
	Caritura();

	//cabeza-5a
	npuntos = 3;
	p[0][1] = -20;	p[0][2] = -p[0][1] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[0][3] = 0;
	p[1][1] = 0;	p[1][2] = -p[1][1] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[1][3] = 50;
	p[2][1] = 20;	p[2][2] = -p[2][1] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[2][3] = 0;

	c[1] = 660;
	c[2] = 680;
	Caritura();
	c[1] = 520;
	c[2] = 440;


	//cara-6
	npuntos = 5;
	p[0][1] = 20;	p[0][2] = -p[0][1] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[0][3] = 0;
	p[1][1] = 600;	p[1][2] = -p[1][1] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[1][3] = -300;
	p[2][1] = 0;	p[2][2] = -p[2][1] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[2][3] = -1500;
	p[3][1] = -600;	p[3][2] = -p[3][1] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[3][3] = -300;
	p[4][1] = -20;	p[4][2] = -p[4][1] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[4][3] = 0;

	Caritura();

	//ojoI-7
	npuntos = 5;
	p[0][1] = 20;	p[0][2] = 10;    p[0][3] = 0;
	p[1][1] = 220;	p[1][2] = 10;    p[1][3] = 0;
	p[2][1] = 220;	p[2][2] = 10;    p[2][3] = -300;
	p[3][1] = 20;	p[3][2] = 10;    p[3][3] = -300;
	p[4][1] = 20;	p[4][2] = 10;    p[4][3] = 0;

	Caritura();

	//ojoD-8
	npuntos = 5;
	p[0][1] = 10;	p[0][2] = 30;    p[0][3] = 10;
	p[1][1] = 10;	p[1][2] = 30 + 580 * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[1][3] = 10;
	p[2][1] = 10;	p[2][2] = p[1][2];    p[2][3] = -280;
	p[3][1] = 10;	p[3][2] = 30;    p[3][3] = -280;
	p[4][1] = 10;	p[4][2] = 30;    p[4][3] = 10;

	Caritura();

	//nariz-9
	npuntos = 4;
	p[0][1] = 0;	p[0][2] = p[0][1] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[0][3] = -90;
	p[1][1] = 200;	p[1][2] = p[1][1] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[1][3] = -140;
	p[2][1] = -50;	p[2][2] = -p[2][1] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[2][3] = -140;
	p[3][1] = 0;	p[3][2] = p[3][1] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[3][3] = -90;

	c[1] = 520;
	c[2] = 580;
	Caritura();
	c[1] = 520;
	c[2] = 440;

	//ojoIch-11
	npuntos = 5;
	p[0][1] = 20;	p[0][2] = 10;    p[0][3] = -20;
	p[1][1] = 220;	p[1][2] = 10;    p[1][3] = 0;
	p[2][1] = 220;	p[2][2] = 10;    p[2][3] = -300;
	p[3][1] = 20;	p[3][2] = 10;    p[3][3] = -300;
	p[4][1] = 20;	p[4][2] = 10;    p[4][3] = -20;

	Caritura();

	//ojoD-12
	npuntos = 5;
	p[0][1] = 10;	p[0][2] = 30;    p[0][3] = -10;
	p[1][1] = 10;	p[1][2] = 30 + 580 * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[1][3] = 10;
	p[2][1] = 10;	p[2][2] = p[1][2];    p[2][3] = -280;
	p[3][1] = 10;	p[3][2] = 30;    p[3][3] = -280;
	p[4][1] = 10;	p[4][2] = 30;    p[4][3] = -10;

	Caritura();

	//bigoteI1-13


	c[1] = 520;
	c[2] = 750;

	npuntos = 3;
	p[0][1] = 80;	p[0][2] = 30 + p[0][1] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[0][3] = -30;
	p[1][1] = 120;	p[1][2] = p[1][1] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[1][3] = -50;
	p[2][1] = 180;   p[2][2] = p[2][1] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[2][3] = -20;

	Escalar();
	Caritura();

	//bigoteI1-14
	//npuntos=3;
	p[0][1] = 80;	p[0][2] = 30 + p[0][1] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[0][3] = -25;
	p[1][1] = 120;	p[1][2] = p[1][1] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[1][3] = -45;
	p[2][1] = 180;   p[2][2] = p[2][1] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[2][3] = -15;

	Escalar();
	Caritura();

	//bigoteI1-15
	//npuntos=3;
	p[0][1] = 80;	p[0][2] = 30 + p[0][1] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[0][3] = -20;
	p[1][1] = 120;	p[1][2] = p[1][1] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[1][3] = -40;
	p[2][1] = 180;   p[2][2] = p[2][1] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[2][3] = -10;

	Escalar();
	Caritura();

	//bigoteI1-16
	//npuntos=3;
	p[0][1] = 80;	p[0][2] = 30 + p[0][1] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[0][3] = -35;
	p[1][1] = 120;	p[1][2] = p[1][1] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[1][3] = -55;
	p[2][1] = 180;   p[2][2] = p[2][1] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[2][3] = -25;

	Escalar();
	Caritura();

	//bigoteD2-17
	//npuntos=3;
	p[0][1] = 40;	p[0][2] = 50 + p[0][1] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[0][3] = -35;
	p[1][1] = 20;	p[1][2] = 20 + p[1][1] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[1][3] = -100;
	p[2][1] = -60;   p[2][2] = 100 + p[2][1] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[2][3] = -35;

	Escalar();
	Caritura();

	//bigoteD2-18
	//npuntos=3;
	p[0][1] = 40;	p[0][2] = 50 + p[0][1] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[0][3] = -30;
	p[1][1] = 20;	p[1][2] = 20 + p[1][1] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[1][3] = -95;
	p[2][1] = -60;   p[2][2] = 100 + p[2][1] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[2][3] = -30;

	Escalar();
	Caritura();

	//bigoteD2-19
	//npuntos=3;
	p[0][1] = 40;	p[0][2] = 50 + p[0][1] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[0][3] = -40;
	p[1][1] = 20;	p[1][2] = 20 + p[1][1] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[1][3] = -105;
	p[2][1] = -60;   p[2][2] = 100 + p[2][1] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[2][3] = -40;

	Escalar();
	Caritura();

	//bigoteD2-20
	//npuntos=3;
	p[0][1] = 40;	p[0][2] = 50 + p[0][1] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[0][3] = -45;
	p[1][1] = 20;	p[1][2] = 20 + p[1][1] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[1][3] = -110;
	p[2][1] = -60;   p[2][2] = 100 + p[2][1] * sin(angulo[0]) / (sin(angulo[0] + angulo[1])*cos(angulo[0]));    p[2][3] = -45;

	Escalar();
	Caritura();

	c[1] = 520;
	c[2] = 440;


}

void CBugsDlg::OnCancel()
{
	// TODO: Add extra cleanup here

	CDialog::OnCancel();
}

void CBugsDlg::Borrar()
{
	CClientDC dibu(this);

	CPen NewPen2(PS_SOLID,
		1,
		RGB(190, 190, 190));
	dibu.SelectObject(&NewPen2);

	CBrush pincel;
	pincel.CreateSolidBrush(RGB(190, 190, 190));

	dibu.SelectObject(&pincel);
	dibu.Rectangle(160, 290, 230, 350);
}



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

void CBugsDlg::Escalar(double escala)
{
	int i, j;
	for (i = 0; i < 3; i++)
		for (j = 1; i < 4; i++)
			p[i][j] *= escala;
}


void CBugsDlg::OnCurvabierta()
{
	// TODO: Add your control notification handler code here
	if (anim == 0) anim = 1;
	else anim = 0;

	int i;
	for (i = 0; i < 15; i++)
		T[i] = i;


	Invalidate();
	//Inicio();
	K = 3;


}

void CBugsDlg::OnCurvacompletaMas()
{
	// TODO: Add your control notification handler code here
	if (K <= 15) K++;

	int N = 15 / K;

	int i, j;

	for (i = 0; i < N; i++)
		for (j = 0; j < K; j++)
			T[i + j] = j;


	Invalidate();
	//Inicio();



}

void CBugsDlg::OnCurvacompletamenos()
{
	// TODO: Add your control notification handler code here
	if (K > 3) K--;

	int N = 15 / K;

	int i, j;
	for (i = 0; i < N; i++)
		for (j = 0; j < K; j++)
			T[i + j] = j;

	Invalidate();
	//Inicio();

}
