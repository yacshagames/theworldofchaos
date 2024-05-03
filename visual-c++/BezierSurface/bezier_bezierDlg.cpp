/******************************************************************************
:: BEZIER SURFACE :: SUPERFICIE BEZIER ::

Draw a bezier surface

Developed by:

Original authors: Amelia
Improvements added from version 2, thanks to Yacsha.

HISTORY...

  >> Version 2 - 03-V-2024
	* Thanks to the collaboration of a follower of "the world of chaos",
	  we obtained the first version. From which we have made the
	  following changes:
	- Update visual-c++\BezierSurface - Porting to VC++ 2017.
	- Various bugs are corrected, which do not allow correct mouse animation.
	- Added a new icon to the project
	- Add credits and version history
	- Translate GUI from spanish to english

  >> Version 1 - 18-II-2002
	- First version developed by Amelia

Warning!!!: These formulas may contain some errors, if you find them, let me
know from the contact page of "The world of chaos", or suggest a
modification in the project's github repository
https://github.com/yacshagames/elmundodelcaos

******************************************************************************/
#include "stdafx.h"
#include "bezier_bezier.h"
#include "bezier_bezierDlg.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

//MIS VARIABLES
long double P1[5][3];
long double QR[5][5][3];
long double EJES[4][2];
long double alfa, beta, rot;
long double P[10][10][3];
long double Q[2];
int cx, cy, i, j, n, m, a, b;
long double u, v;
long double PI = 3.1415926535897932384626433832795;
int nPuntos, densidad;
long double ptoaux[3];
long double S[200][200][3];

CPen colorrojo(PS_SOLID, 1, RGB(0, 0, 255));
CPen colorgris(PS_SOLID, 1, RGB(192, 192, 192));
CPen colorazul(PS_SOLID, 1, RGB(0, 0, 0));

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
// CBezier_bezierDlg dialog

CBezier_bezierDlg::CBezier_bezierDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBezier_bezierDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBezier_bezierDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBezier_bezierDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBezier_bezierDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBezier_bezierDlg, CDialog)
	//{{AFX_MSG_MAP(CBezier_bezierDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_KILLFOCUS()
	ON_BN_CLICKED(cmdRotarZ, OncmdRotarZ)
	ON_BN_CLICKED(cmdRotarX, OncmdRotarX)
	ON_BN_CLICKED(cmdRotarY, OncmdRotarY)
	ON_BN_CLICKED(IDC_Superficie, OnSuperficie)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBezier_bezierDlg message handlers

BOOL CBezier_bezierDlg::OnInitDialog()
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

	OnSuperficie();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CBezier_bezierDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CBezier_bezierDlg::OnPaint()
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
	alfa = 15;
	beta = 30;
	rot = 10;
	alfa = alfa * PI / 180;
	beta = beta * PI / 180;
	rot = rot * PI / 180;
	cx = 350;
	cy = 330;
	P1[0][0] = 0; P1[1][0] = 300; P1[2][0] = 0;  P1[3][0] = 0;
	P1[0][1] = 0; P1[1][1] = 0;  P1[2][1] = 300; P1[3][1] = 0;
	P1[0][2] = 0; P1[1][2] = 0;  P1[2][2] = 0;  P1[3][2] = 300;
	densidad = 10;

	///////////////////DIBUJA EJES/////////////////////////////////

	CClientDC area(this);

	for (i = 0; i <= 3; ++i)
	{
		EJES[i][0] = cx - P1[i][0] * cos(alfa) + P1[i][1] * cos(beta);
		EJES[i][1] = cy + P1[i][0] * sin(alfa) + P1[i][1] * sin(beta) - P1[i][2];
	}

	CPen colorazul(PS_SOLID, 1, RGB(0, 0, 153));

	area.SelectObject(&colorazul);
	area.MoveTo(EJES[0][0], EJES[0][1]);
	area.LineTo(EJES[1][0], EJES[1][1]);
	area.MoveTo(EJES[0][0], EJES[0][1]);
	area.LineTo(EJES[2][0], EJES[2][1]);
	area.MoveTo(EJES[0][0], EJES[0][1]);
	area.LineTo(EJES[3][0], EJES[3][1]);

	////////////////////////////////////////////////////////////////


	DrawBezierSurface();

}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CBezier_bezierDlg::OnQueryDragIcon()
{
	return (HCURSOR)m_hIcon;
}

void CBezier_bezierDlg::OnKillFocus(CWnd* pNewWnd)
{
	CDialog::OnKillFocus(pNewWnd);

	// TODO: Add your message handler code here

}

long int Factorial(int NumPuntos)
{
	if (NumPuntos == 0)
	{
		NumPuntos = 1;
	}
	else
	{
		NumPuntos = NumPuntos * Factorial(NumPuntos - 1);
	}
	return NumPuntos;
}

long double Bernstein(int h, int k, long double t)
{
	long double B;
	B = Factorial(h) / (Factorial(h - k)*Factorial(k))*pow(1 - t, h - k)*pow(t, k);
	return B;
}

void CBezier_bezierDlg::DrawBezierSurface() {

	CClientDC area(this);

	//////////Dibuja superficie bezier-bezier
	area.SelectObject(&colorrojo);
	//Curvas horizontales
	for (v = 0; v <= 1; v = v + 1. / densidad)
	{
		//Mueve a S[0][v]
		u = 0;
		b = v * densidad;
		S[0][b][0] = 0; S[0][b][1] = 0; S[0][b][2] = 0;
		for (j = 0; j <= m; ++j)
		{
			ptoaux[0] = 0; ptoaux[1] = 0; ptoaux[2] = 0;
			for (i = 0; i <= n; ++i)
			{
				ptoaux[0] = ptoaux[0] + Bernstein(n, i, u)*P[i][j][0];
				ptoaux[1] = ptoaux[1] + Bernstein(n, i, u)*P[i][j][1];
				ptoaux[2] = ptoaux[2] + Bernstein(n, i, u)*P[i][j][2];
			}
			b = v * densidad;
			S[0][b][0] = S[0][b][0] + ptoaux[0] * Bernstein(m, j, v);
			S[0][b][1] = S[0][b][1] + ptoaux[1] * Bernstein(m, j, v);
			S[0][b][2] = S[0][b][2] + ptoaux[2] * Bernstein(m, j, v);
		}
		b = v * densidad;
		Q[0] = cx - S[0][b][0] * cos(alfa) + S[0][b][1] * cos(beta);
		Q[1] = cy + S[0][b][0] * sin(alfa) + S[0][b][1] * sin(beta) - S[0][b][2];
		area.MoveTo(Q[0], Q[1]);
		///////
		for (u = 0; u <= 1; u = u + 1. / densidad)
		{
			a = u * densidad; b = v * densidad;
			S[a][b][0] = 0; S[a][b][1] = 0; S[a][b][2] = 0;
			for (j = 0; j <= m; ++j)
			{
				ptoaux[0] = 0; ptoaux[1] = 0; ptoaux[2] = 0;
				for (i = 0; i <= n; ++i)
				{
					ptoaux[0] = ptoaux[0] + Bernstein(n, i, u)*P[i][j][0];
					ptoaux[1] = ptoaux[1] + Bernstein(n, i, u)*P[i][j][1];
					ptoaux[2] = ptoaux[2] + Bernstein(n, i, u)*P[i][j][2];
				}
				a = u * densidad; b = v * densidad;
				S[a][b][0] = S[a][b][0] + ptoaux[0] * Bernstein(m, j, v);
				S[a][b][1] = S[a][b][1] + ptoaux[1] * Bernstein(m, j, v);
				S[a][b][2] = S[a][b][2] + ptoaux[2] * Bernstein(m, j, v);
			}
			a = u * densidad; b = v * densidad;
			Q[0] = cx - S[a][b][0] * cos(alfa) + S[a][b][1] * cos(beta);
			Q[1] = cy + S[a][b][0] * sin(alfa) + S[a][b][1] * sin(beta) - S[a][b][2];
			area.LineTo(Q[0], Q[1]);
		}
	}

	//Curvas verticales
	for (u = 0; u <= 1; u = u + 1. / densidad)
	{
		//Mueve a S[u][0]
		v = 0;
		a = u * densidad;
		S[a][0][0] = 0; S[a][0][1] = 0; S[a][0][2] = 0;
		for (i = 0; i <= n; ++i)
		{
			ptoaux[0] = 0; ptoaux[1] = 0; ptoaux[2] = 0;
			for (j = 0; j <= m; ++j)
			{
				ptoaux[0] = ptoaux[0] + Bernstein(m, j, v)*P[i][j][0];
				ptoaux[1] = ptoaux[1] + Bernstein(m, j, v)*P[i][j][1];
				ptoaux[2] = ptoaux[2] + Bernstein(m, j, v)*P[i][j][2];
			}
			a = u * densidad;
			S[a][0][0] = S[a][0][0] + ptoaux[0] * Bernstein(n, i, u);
			S[a][0][1] = S[a][0][1] + ptoaux[1] * Bernstein(n, i, u);
			S[a][0][2] = S[a][0][2] + ptoaux[2] * Bernstein(n, i, u);
		}
		a = u * densidad;
		Q[0] = cx - S[a][0][0] * cos(alfa) + S[a][0][1] * cos(beta);
		Q[1] = cy + S[a][0][0] * sin(alfa) + S[a][0][1] * sin(beta) - S[a][0][2];
		area.MoveTo(Q[0], Q[1]);
		///////
		for (v = 0; v <= 1; v = v + 1. / densidad)
		{
			a = u * densidad; b = v * densidad;
			S[a][b][0] = 0; S[a][b][1] = 0; S[a][b][2] = 0;
			for (i = 0; i <= n; ++i)
			{
				ptoaux[0] = 0; ptoaux[1] = 0; ptoaux[2] = 0;
				for (j = 0; j <= m; ++j)
				{
					ptoaux[0] = ptoaux[0] + Bernstein(m, j, v)*P[i][j][0];
					ptoaux[1] = ptoaux[1] + Bernstein(m, j, v)*P[i][j][1];
					ptoaux[2] = ptoaux[2] + Bernstein(m, j, v)*P[i][j][2];
				}
				a = u * densidad; b = v * densidad;
				S[a][b][0] = S[a][b][0] + ptoaux[0] * Bernstein(n, i, u);
				S[a][b][1] = S[a][b][1] + ptoaux[1] * Bernstein(n, i, u);
				S[a][b][2] = S[a][b][2] + ptoaux[2] * Bernstein(n, i, u);
			}
			a = u * densidad; b = v * densidad;
			Q[0] = cx - S[a][b][0] * cos(alfa) + S[a][b][1] * cos(beta);
			Q[1] = cy + S[a][b][0] * sin(alfa) + S[a][b][1] * sin(beta) - S[a][b][2];
			area.LineTo(Q[0], Q[1]);
		}
	}
	///////////////////////////////////////Fin superficie bezier-bezier///////////

}

void CBezier_bezierDlg::OncmdRotarZ()
{
	//rota Z+
	for (i = 0; i <= n; ++i)
	{
		for (j = 0; j <= m; ++j)
		{
			QR[i][j][0] = P[i][j][0] * cos(rot) - P[i][j][1] * sin(rot);
			QR[i][j][1] = P[i][j][0] * sin(rot) + P[i][j][1] * cos(rot);
			QR[i][j][2] = P[i][j][2];
		}
	}

	//EQUIVALENCIAS
	for (i = 0; i <= n; ++i)
	{
		for (j = 0; j <= m; ++j)
		{
			P[i][j][0] = QR[i][j][0];
			P[i][j][1] = QR[i][j][1];
			P[i][j][2] = QR[i][j][2];
		}
	}

	Invalidate();	

}

void CBezier_bezierDlg::OncmdRotarX()
{	
	//rota X+
	for (i = 0; i <= n; ++i)
	{
		for (j = 0; j <= m; ++j)
		{
			QR[i][j][0] = P[i][j][0];
			QR[i][j][1] = P[i][j][1] * cos(rot) - P[i][j][2] * sin(rot);
			QR[i][j][2] = P[i][j][1] * sin(rot) + P[i][j][2] * cos(rot);
		}
	}

	//EQUIVALENCIAS
	for (i = 0; i <= n; ++i)
	{
		for (j = 0; j <= m; ++j)
		{
			P[i][j][0] = QR[i][j][0];
			P[i][j][1] = QR[i][j][1];
			P[i][j][2] = QR[i][j][2];
		}
	}	

	Invalidate();

}

void CBezier_bezierDlg::OncmdRotarY()
{
	//rota Y+
	for (i = 0; i <= n; ++i)
	{
		for (j = 0; j <= m; ++j)
		{
			QR[i][j][0] = P[i][j][0] * cos(rot) - P[i][j][2] * sin(rot);
			QR[i][j][1] = P[i][j][1];
			QR[i][j][2] = P[i][j][0] * sin(rot) + P[i][j][2] * cos(rot);
		}
	}


	//EQUIVALENCIAS
	for (i = 0; i <= n; ++i)
	{
		for (j = 0; j <= m; ++j)
		{
			P[i][j][0] = QR[i][j][0];
			P[i][j][1] = QR[i][j][1];
			P[i][j][2] = QR[i][j][2];
		}
	}

	Invalidate();
}

void CBezier_bezierDlg::OnSuperficie()
{

	///////////////////////////////////////////////////////////////////////////////////////////
	/***********************************************************************************///////
	/////////////////Dibuja superficie bezier-bezier   ////////////////////////////////////////
	/***********************************************************************************///////
	///////////////////////////////////////////////////////////////////////////////////////////

	n = 2;
	m = 2;
	//area.SelectObject(&colorrojo);

	P[0][0][0] = 50; P[0][0][1] = 0;  P[0][0][2] = 0;   	//P00
	P[0][1][0] = 0; P[0][1][1] = 50;  P[0][1][2] = 250; 	//P01
	P[0][2][0] = 0; P[0][2][1] = 150;  P[0][2][2] = 0;  	//P02
	P[0][2][0] = 0; P[0][2][1] = 200;  P[0][2][2] = 50;

	P[1][0][0] = 50;   P[1][0][1] = 0;  P[1][0][2] = 150;	//P10
	P[1][1][0] = 50;  P[1][1][1] = 150; P[1][1][2] = 50;	//P11
	P[1][2][0] = 50; P[1][2][1] = 100; P[1][2][2] = 300;	//P12
	P[1][2][0] = 50; P[1][2][1] = 200; P[1][2][2] = 250;

	P[2][0][0] = 100;  P[2][0][1] = 0; P[2][0][2] = 50;  	//P20
	P[2][1][0] = 150; P[2][1][1] = 100; P[2][1][2] = 200;	//P21
	P[2][2][0] = 150; P[2][2][1] = 150; P[2][2][2] = 0;  	//P22
	P[2][2][0] = 100; P[2][2][1] = 200; P[2][2][2] = 50;

	Invalidate();
}
