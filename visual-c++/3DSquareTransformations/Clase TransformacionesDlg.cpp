/******************************************************************************
:: 3D SQUARE 2 :: CUADRADO 3D 2 ::

Model 2: A 3D square is plotted that supports translation, rotation, scaling,
projection in the XY, XZ, YZ planes, and reflection with respect to X, Y, Z
and the origin O

Developed by:

	Original authors: Manuel Paredes
	Improvements added from version 2, thanks to:

	JOSE LUIS DE LA CRUZ LAZARO (Yacsha)
	contact@theworldofchaos.com

	YACSHA - Software & Desing, since 1999, Lima-Peru
	>> The World of Chaos - EL MUNDO DEL CAOS - Unlimited Programming
	www.theworldofchaos.com

LICENSE
	This file is released under the terms of the BSD 3-Clause License.
	Read LICENSE.txt file for more information.

HISTORY...

  >> Version 2 - 05-V-2024
	* Thanks to the collaboration of a follower of "the world of chaos",
	  we obtained the first version. From which we have made the
	  following changes:
	- Porting to VC++ 2017.
	- Add credits and version history
	- Translate GUI from spanish to english
	- Warnings due to lack of static_cast are corrected

  >> Version 1 - 10-IX-2000
	- First version developed by Manuel Paredes

Warning!!!: These formulas may contain some errors, if you find them, let me
know from the contact page of "The world of chaos", or suggest a
modification in the project's github repository
https://github.com/yacshagames/elmundodelcaos

******************************************************************************/

#include "stdafx.h"
#include "Clase Transformaciones.h"
#include "Clase TransformacionesDlg.h"

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
// CClaseTransformacionesDlg dialog

CClaseTransformacionesDlg::CClaseTransformacionesDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CClaseTransformacionesDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CClaseTransformacionesDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void CClaseTransformacionesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClaseTransformacionesDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CClaseTransformacionesDlg, CDialog)
	//{{AFX_MSG_MAP(CClaseTransformacionesDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, OnAceptar)
	ON_BN_CLICKED(IDC_BUTTON1, OnTrasXPos)
	ON_BN_DOUBLECLICKED(IDC_BUTTON2, OnTrasxN)
	ON_BN_CLICKED(IDC_BUTTON3, OnTrasYPos)
	ON_BN_CLICKED(IDC_BUTTON4, OnTrasyN)
	ON_BN_CLICKED(IDC_BUTTON5, OnTrasZPos)
	ON_BN_CLICKED(IDC_BUTTON6, OnTraszN)
	ON_BN_CLICKED(IDC_BUTTON7, OnEje3D)
	ON_BN_CLICKED(IDC_BUTTON8, OnRotXP)
	ON_BN_CLICKED(IDC_BUTTON9, OnRotXN)
	ON_BN_CLICKED(IDC_BUTTON10, OnRotYP)
	ON_BN_CLICKED(IDC_BUTTON11, OnRotYN)
	ON_BN_CLICKED(IDC_BUTTON12, OnRotZP)
	ON_BN_CLICKED(IDC_BUTTON13, OnRotZN)
	ON_BN_CLICKED(IDC_BUTTON14, OnEscP)
	ON_BN_CLICKED(IDC_BUTTON16, OnEscN)
	ON_BN_CLICKED(IDC_ReflexX, OnReflexX)
	ON_BN_CLICKED(IDC_ReflexY, OnReflexY)
	ON_BN_CLICKED(IDC_ReflexZ, OnReflexZ)
	ON_BN_CLICKED(IDC_ReflexXY, OnReflexXY)
	ON_BN_CLICKED(IDC_ReflexXZ, OnReflexXZ)
	ON_BN_CLICKED(IDC_ReflexYZ, OnReflexYZ)
	ON_BN_CLICKED(IDC_BUTTON2, OnTrasxN)
	ON_BN_CLICKED(IDC_ReflexO, OnReflexO)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClaseTransformacionesDlg message handlers

BOOL CClaseTransformacionesDlg::OnInitDialog()
{
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
	pi = 3.1415926535897932384626433832795;

	anga = 15;
	angb = 30;

	Cx = 320;
	Cy = 240;

	n = 3;

	mt[1][1] = 1; mt[1][2] = 0; mt[1][3] = 0; mt[1][4] = 0;
	mt[2][1] = 0; mt[2][2] = 1; mt[2][3] = 0; mt[2][4] = 0;
	mt[3][1] = 0; mt[3][2] = 0; mt[3][3] = 1; mt[3][4] = 0;
	mt[4][1] = 0; mt[4][2] = 0; mt[4][3] = 0; mt[4][4] = 1;

	p[0][1] = 10; p[0][2] = 10; p[0][3] = 0; p[0][4] = 1;
	p[1][1] = 110; p[1][2] = 10; p[1][3] = 0; p[1][4] = 1;
	p[2][1] = 110; p[2][2] = 110; p[2][3] = 0; p[2][4] = 1;
	p[3][1] = 10; p[3][2] = 110; p[3][3] = 0; p[3][4] = 1;

	e3d[0][1] = 200; e3d[0][2] = 0; e3d[0][3] = 0; e3d[0][4] = 1;
	e3d[1][1] = 0; e3d[1][2] = 200; e3d[1][3] = 0; e3d[1][4] = 1;
	e3d[2][1] = 0; e3d[2][2] = 0; e3d[2][3] = 200; e3d[2][4] = 1;
	e3d[3][1] = 0; e3d[3][2] = 0; e3d[3][3] = 0; e3d[3][4] = 1;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CClaseTransformacionesDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CClaseTransformacionesDlg::OnPaint()
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
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CClaseTransformacionesDlg::OnQueryDragIcon()
{
	return (HCURSOR)m_hIcon;
}

void CClaseTransformacionesDlg::OnAceptar()
{
	// TODO: Add your control notification handler code here

	OnOK();

}

void CClaseTransformacionesDlg::Transformar_puntos3d()
{
	double auxa = anga;
	double auxb = angb;

	for (int i = 0; i <= n; i++)
	{
		pm[i][1] = static_cast<int>(Cx + p3d[i][2] * cos(rad(auxb)) - p3d[i][1] * cos(rad(auxa)));
		pm[i][2] = static_cast<int>(Cy - p3d[i][3] + p3d[i][2] * sin(rad(auxb)) + p3d[i][1] * sin(rad(auxa)));
	}

}

void CClaseTransformacionesDlg::Transformar_eje3d()
{
	double auxa = anga;
	double auxb = angb;

	for (int i = 0; i <= 3; i++)
	{
		em[i][1] = static_cast<int>(Cx + e3d[i][2] * cos(rad(auxb)) - e3d[i][1] * cos(rad(auxa)));
		em[i][2] = static_cast<int>(Cy - e3d[i][3] + e3d[i][2] * sin(rad(auxb)) + e3d[i][1] * sin(rad(auxa)));
	}

}

double CClaseTransformacionesDlg::rad(double angulo)
{
	return angulo * pi / 180;
}

void CClaseTransformacionesDlg::MatxMat()
{
	for (int l = 1; l <= 4; l++)
		for (int m = 1; m <= 4; m++)
		{
			mataux[l][m] = mt[l][m];
		}

	for (int j = 1; j <= 4; j++)
	{
		for (int i = 1; i <= 4; i++)
		{
			mt[i][j] = 0;
			for (int k = 1; k <= 4; k++)
			{
				mt[i][j] = mt[i][j] + mm[i][k] * mataux[k][j];
			}
		}
	}
}

void CClaseTransformacionesDlg::MatxPto()
{

	for (int k = 0; k <= n; k++)
	{
		b[1] = p[k][1];
		b[2] = p[k][2];
		b[3] = p[k][3];
		b[4] = p[k][4];

		for (int i = 1; i <= 4; i++)
		{
			c[i] = 0;
			for (int j = 1; j <= 4; j++)
			{
				c[i] = c[i] + (mt[i][j] * b[j]);
			}
		}

		p3d[k][1] = c[1];
		p3d[k][2] = c[2];
		p3d[k][3] = c[3];
		p3d[k][4] = c[4];

	}
}

void CClaseTransformacionesDlg::Trasladar(double Tx, double Ty, double Tz)
{
	mm[1][1] = 1;  mm[1][2] = 0;  mm[1][3] = 0;  mm[1][4] = Tx;
	mm[2][1] = 0;  mm[2][2] = 1;  mm[2][3] = 0;  mm[2][4] = Ty;
	mm[3][1] = 0;  mm[3][2] = 0;  mm[3][3] = 1;  mm[3][4] = Tz;
	mm[4][1] = 0;  mm[4][2] = 0;  mm[4][3] = 0;  mm[4][4] = 1;

	MatxMat();
}

void CClaseTransformacionesDlg::Escalar(double Ex, double Ey, double Ez)
{
	mm[1][1] = Ex; mm[1][2] = 0;  mm[1][3] = 0;  mm[1][4] = 0;
	mm[2][1] = 0;  mm[2][2] = Ey; mm[2][3] = 0;  mm[2][4] = 0;
	mm[3][1] = 0;  mm[3][2] = 0;  mm[3][3] = Ez; mm[3][4] = 0;
	mm[4][1] = 0;  mm[4][2] = 0;  mm[4][3] = 0;  mm[4][4] = 1;

	MatxMat();
}

void CClaseTransformacionesDlg::Rotar(int Eje, double ang)
{
	switch (Eje)
	{
	case 1:
	{
		mm[1][1] = 1; mm[1][2] = 0; mm[1][3] = 0; mm[1][4] = 0;
		mm[2][1] = 0; mm[2][2] = cos(rad(ang)); mm[2][3] = -sin(rad(ang)); mm[2][4] = 0;
		mm[3][1] = 0; mm[3][2] = sin(rad(ang)); mm[3][3] = cos(rad(ang)); mm[3][4] = 0;
		mm[4][1] = 0; mm[4][2] = 0; mm[4][3] = 0; mm[4][4] = 1;
		break;
	}
	case 2:
	{
		mm[1][1] = cos(rad(ang)); mm[1][2] = 0; mm[1][3] = sin(rad(ang)); mm[1][4] = 0;
		mm[2][1] = 0; mm[2][2] = 1; mm[2][3] = 0; mm[2][4] = 0;
		mm[3][1] = -sin(rad(ang)); mm[3][2] = 0; mm[3][3] = cos(rad(ang)); mm[3][4] = 0;
		mm[4][1] = 0; mm[4][2] = 0; mm[4][3] = 0; mm[4][4] = 1;
		break;
	}
	case 3:
	{
		mm[1][1] = cos(rad(ang)); mm[1][2] = sin(rad(ang)); mm[1][3] = 0; mm[1][4] = 0;
		mm[2][1] = -sin(rad(ang)); mm[2][2] = cos(rad(ang)); mm[2][3] = 0; mm[2][4] = 0;
		mm[3][1] = 0; mm[3][2] = 0; mm[3][3] = 1; mm[3][4] = 0;
		mm[4][1] = 0; mm[4][2] = 0; mm[4][3] = 0; mm[4][4] = 1;
		break;
	}
	}
	MatxMat();
}

void CClaseTransformacionesDlg::Dibujar_Cuadrado()
{
	OnEje3D();
	CClientDC pDC(this);
	CPen LapizRojo(PS_SOLID, 1, RGB(255, 0, 0));
	pDC.SelectObject(&LapizRojo);
	pDC.MoveTo(pm[0][1], pm[0][2]);
	pDC.LineTo(pm[1][1], pm[1][2]);
	pDC.LineTo(pm[2][1], pm[2][2]);
	pDC.LineTo(pm[3][1], pm[3][2]);
	pDC.LineTo(pm[0][1], pm[0][2]);
}

void CClaseTransformacionesDlg::OnTrasXPos()
{
	// TODO: Add your control notification handler code here
	Trasladar(5, 0, 0);
	MatxPto();
	Transformar_puntos3d();
	Dibujar_Cuadrado();
}

void CClaseTransformacionesDlg::OnTrasxN()
{
	// TODO: Add your control notification handler code here
	Trasladar(-5, 0, 0);
	MatxPto();
	Transformar_puntos3d();
	Dibujar_Cuadrado();

}

void CClaseTransformacionesDlg::OnTrasYPos()
{
	// TODO: Add your control notification handler code here
	Trasladar(0, 5, 0);
	MatxPto();
	Transformar_puntos3d();
	Dibujar_Cuadrado();

}

void CClaseTransformacionesDlg::OnTrasyN()
{
	// TODO: Add your control notification handler code here
	Trasladar(0, -5, 0);
	MatxPto();
	Transformar_puntos3d();
	Dibujar_Cuadrado();

}

void CClaseTransformacionesDlg::OnTrasZPos()
{
	// TODO: Add your control notification handler code here
	Trasladar(0, 0, 5);
	MatxPto();
	Transformar_puntos3d();
	Dibujar_Cuadrado();

}

void CClaseTransformacionesDlg::OnTraszN()
{
	// TODO: Add your control notification handler code here
	Trasladar(0, 0, -5);
	MatxPto();
	Transformar_puntos3d();
	Dibujar_Cuadrado();

}

void CClaseTransformacionesDlg::DibujaEje()
{
	CClientDC pDC(this);

	pDC.Rectangle(5, 5, 630, 470);
	pDC.MoveTo(em[3][1], em[3][2]);
	pDC.LineTo(em[0][1], em[0][2]);
	pDC.MoveTo(em[3][1], em[3][2]);
	pDC.LineTo(em[1][1], em[1][2]);
	pDC.MoveTo(em[3][1], em[3][2]);
	pDC.LineTo(em[2][1], em[2][2]);
}

void CClaseTransformacionesDlg::OnEje3D()
{
	// TODO: Add your control notification handler code here
	Transformar_eje3d();
	DibujaEje();

}

void CClaseTransformacionesDlg::OnRotXP()
{
	// TODO: Add your control notification handler code here
	Rotar(1, 5);
	MatxPto();
	Transformar_puntos3d();
	Dibujar_Cuadrado();

}

void CClaseTransformacionesDlg::OnRotXN()
{
	// TODO: Add your control notification handler code here
	Rotar(1, -5);
	MatxPto();
	Transformar_puntos3d();
	Dibujar_Cuadrado();

}

void CClaseTransformacionesDlg::OnRotYP()
{
	// TODO: Add your control notification handler code here
	Rotar(2, 5);
	MatxPto();
	Transformar_puntos3d();
	Dibujar_Cuadrado();

}

void CClaseTransformacionesDlg::OnRotYN()
{
	// TODO: Add your control notification handler code here
	Rotar(2, -5);
	MatxPto();
	Transformar_puntos3d();
	Dibujar_Cuadrado();

}

void CClaseTransformacionesDlg::OnRotZP()
{
	// TODO: Add your control notification handler code here
	Rotar(3, 5);
	MatxPto();
	Transformar_puntos3d();
	Dibujar_Cuadrado();

}

void CClaseTransformacionesDlg::OnRotZN()
{
	// TODO: Add your control notification handler code here
	Rotar(3, -5);
	MatxPto();
	Transformar_puntos3d();
	Dibujar_Cuadrado();

}


void CClaseTransformacionesDlg::OnEscP()
{
	// TODO: Add your control notification handler code here
	Escalar(1.25, 1.25, 1.25);
	MatxPto();
	Transformar_puntos3d();
	Dibujar_Cuadrado();
}

void CClaseTransformacionesDlg::OnEscN()
{
	// TODO: Add your control notification handler code here
	Escalar(.75, .75, .75);
	MatxPto();
	Transformar_puntos3d();
	Dibujar_Cuadrado();
}


void CClaseTransformacionesDlg::OnReflexX()
{
	// TODO: Add your control notification handler code here
	mm[1][1] = 1;	mm[1][2] = 0;	mm[1][3] = 0;	mm[1][4] = 0;
	mm[2][1] = 0;	mm[2][2] = -1;	mm[2][3] = 0;	mm[2][4] = 0;
	mm[3][1] = 0;	mm[3][2] = 0;	mm[3][3] = -1;	mm[3][4] = 0;
	mm[4][1] = 0;	mm[4][2] = 0;	mm[4][3] = 0;	mm[4][4] = 1;
	MatxMat();
	MatxPto();
	Transformar_puntos3d();
	Dibujar_Cuadrado();
}

void CClaseTransformacionesDlg::OnReflexY()
{
	// TODO: Add your control notification handler code here
	mm[1][1] = -1;	mm[1][2] = 0;	mm[1][3] = 0;	mm[1][4] = 0;
	mm[2][1] = 0;	mm[2][2] = 1;	mm[2][3] = 0;	mm[2][4] = 0;
	mm[3][1] = 0;	mm[3][2] = 0;	mm[3][3] = -1;	mm[3][4] = 0;
	mm[4][1] = 0;	mm[4][2] = 0;	mm[4][3] = 0;	mm[4][4] = 1;
	MatxMat();
	MatxPto();
	Transformar_puntos3d();
	Dibujar_Cuadrado();
}

void CClaseTransformacionesDlg::OnReflexZ()
{
	// TODO: Add your control notification handler code here
	mm[1][1] = -1;	mm[1][2] = 0;	mm[1][3] = 0;	mm[1][4] = 0;
	mm[2][1] = 0;	mm[2][2] = -1;	mm[2][3] = 0;	mm[2][4] = 0;
	mm[3][1] = 0;	mm[3][2] = 0;	mm[3][3] = 1;	mm[3][4] = 0;
	mm[4][1] = 0;	mm[4][2] = 0;	mm[4][3] = 0;	mm[4][4] = 1;
	MatxMat();
	MatxPto();
	Transformar_puntos3d();
	Dibujar_Cuadrado();
}

void CClaseTransformacionesDlg::OnReflexXY()
{
	mm[1][1] = 1;	mm[1][2] = 0;	mm[1][3] = 0;	mm[1][4] = 0;
	mm[2][1] = 0;	mm[2][2] = 1;	mm[2][3] = 0;	mm[2][4] = 0;
	mm[3][1] = 0;	mm[3][2] = 0;	mm[3][3] = -1;	mm[3][4] = 0;
	mm[4][1] = 0;	mm[4][2] = 0;	mm[4][3] = 0;	mm[4][4] = 1;
	MatxMat();
	MatxPto();
	Transformar_puntos3d();
	Dibujar_Cuadrado();
}

void CClaseTransformacionesDlg::OnReflexXZ()
{
	// TODO: Add your control notification handler code here
	mm[1][1] = 1;	mm[1][2] = 0;	mm[1][3] = 0;	mm[1][4] = 0;
	mm[2][1] = 0;	mm[2][2] = -1;	mm[2][3] = 0;	mm[2][4] = 0;
	mm[3][1] = 0;	mm[3][2] = 0;	mm[3][3] = 1;	mm[3][4] = 0;
	mm[4][1] = 0;	mm[4][2] = 0;	mm[4][3] = 0;	mm[4][4] = 1;
	MatxMat();
	MatxPto();
	Transformar_puntos3d();
	Dibujar_Cuadrado();
}

void CClaseTransformacionesDlg::OnReflexYZ()
{
	// TODO: Add your control notification handler code here
	mm[1][1] = -1;	mm[1][2] = 0;	mm[1][3] = 0;	mm[1][4] = 0;
	mm[2][1] = 0;	mm[2][2] = 1;	mm[2][3] = 0;	mm[2][4] = 0;
	mm[3][1] = 0;	mm[3][2] = 0;	mm[3][3] = 1;	mm[3][4] = 0;
	mm[4][1] = 0;	mm[4][2] = 0;	mm[4][3] = 0;	mm[4][4] = 1;
	MatxMat();
	MatxPto();
	Transformar_puntos3d();
	Dibujar_Cuadrado();
}

void CClaseTransformacionesDlg::OnReflexO()
{
	// TODO: Add your control notification handler code here
	mm[1][1] = -1;	mm[1][2] = 0;	mm[1][3] = 0;	mm[1][4] = 0;
	mm[2][1] = 0;	mm[2][2] = -1;	mm[2][3] = 0;	mm[2][4] = 0;
	mm[3][1] = 0;	mm[3][2] = 0;	mm[3][3] = -1;	mm[3][4] = 0;
	mm[4][1] = 0;	mm[4][2] = 0;	mm[4][3] = 0;	mm[4][4] = 1;
	MatxMat();
	MatxPto();
	Transformar_puntos3d();
	Dibujar_Cuadrado();
}
