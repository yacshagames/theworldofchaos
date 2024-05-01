/******************************************************************************
3D CUBE
Rotate and translate a cube around the X, Y and Z axes

Original author: This project was sent by a follower of the "The world of chaos" website

Warning!!!: These formulas may contain some errors, if you find them, let me
know from the contact page of "The world of chaos", or suggest a
modification in the project's github repository
https://github.com/yacshagames/elmundodelcaos

******************************************************************************/

#include "stdafx.h"
#include "3DCube.h"
#include "3DCubeDlg.h"

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
// CPracticaDlg dialog

C3DCubeDlg::C3DCubeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(C3DCubeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPracticaDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C3DCubeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPracticaDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(C3DCubeDlg, CDialog)
	//{{AFX_MSG_MAP(CPracticaDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_CANCELMODE()
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_WM_CAPTURECHANGED()
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON5, &C3DCubeDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &C3DCubeDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &C3DCubeDlg::OnBnClickedButton7)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPracticaDlg message handlers

BOOL C3DCubeDlg::OnInitDialog()
{
	eje[0][1] = 0;	eje[0][2] = 0;    eje[0][3] = 0;
	eje[1][1] = 300;	eje[1][2] = 0;    eje[1][3] = 0;
	eje[2][1] = 0;	eje[2][2] = 300;    eje[2][3] = 0;
	eje[3][1] = 0;	eje[3][2] = 0;    eje[3][3] = 300;

	// Valores de los puntos
	punto[0][1] = -50;	punto[0][2] = -50;    punto[0][3] = -50;
	punto[1][1] = 50;	punto[1][2] = -50;    punto[1][3] = -50;
	punto[2][1] = 50;	punto[2][2] = 50;    punto[2][3] = -50;
	punto[3][1] = -50;	punto[3][2] = 50;    punto[3][3] = -50;
	punto[4][1] = -50;	punto[4][2] = -50;    punto[4][3] = -50;

	punto[5][1] = -50;	punto[5][2] = -50;    punto[5][3] = 50;
	punto[6][1] = 50;	punto[6][2] = -50;    punto[6][3] = 50;
	punto[7][1] = 50;	punto[7][2] = 50;    punto[7][3] = 50;
	punto[8][1] = -50;	punto[8][2] = 50;    punto[8][3] = 50;
	punto[9][1] = -50;	punto[9][2] = -50;    punto[9][3] = 50;
	/*
	punto[0][1] = 0;	punto[0][2] = 0;    punto[0][3] = 0;
	punto[1][1] = 100;	punto[1][2] = 0;    punto[1][3] = 0;
	punto[2][1] = 100;	punto[2][2] = 100;    punto[2][3] = 0;
	punto[3][1] = 0;	punto[3][2] = 100;    punto[3][3] = 0;
	punto[4][1] = 0;	punto[4][2] = 0;    punto[4][3] = 0;

	punto[5][1] = 0; punto[5][2] = 0; punto[5][3] = 100;
	punto[6][1] = 100; punto[6][2] = 0; punto[6][3] = 100;
	punto[7][1] = 100; punto[7][2] = 100; punto[7][3] = 100;
	punto[8][1] = 0; punto[8][2] = 100; punto[8][3] = 100;
	punto[9][1] = 0; punto[9][2] = 0; punto[9][3] = 100;
	*/


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

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void C3DCubeDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void C3DCubeDlg::OnPaint()
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

	Dibuja();
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR C3DCubeDlg::OnQueryDragIcon()
{
	return (HCURSOR)m_hIcon;
}

void C3DCubeDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	//Dibuja();
	CDialog::OnLButtonDblClk(nFlags, point);
}
void C3DCubeDlg::OnButton4()
{
	OnInitDialog();
	Invalidate();
}
void C3DCubeDlg::OnButton1()
{
	RotaX(0.1745329251994);
	//RotaY(0.01745329251994);
	//RotaX(0.1745329251994);
	//RotaY(-0.01745329251994);
	//RotaZ(0.01745329251994);

	Invalidate();
}
void C3DCubeDlg::OnButton2()
{
	Trasladar(0, 10, 0);

	Invalidate();
}
void C3DCubeDlg::OnButton3()
{
	Trasladar(10, 0, 0);

	Invalidate();
}


void C3DCubeDlg::OnBnClickedButton5()
{
	RotaY(0.1745329251994);

	Invalidate();
}


void C3DCubeDlg::OnBnClickedButton6()
{
	RotaZ(0.1745329251994);

	Invalidate();
}

void C3DCubeDlg::OnBnClickedButton7()
{
	Trasladar(0, 0, 10);

	Invalidate();
}



void C3DCubeDlg::OnCancelMode()
{
	CDialog::OnCancelMode();

	// TODO: Add your message handler code here

}

void C3DCubeDlg::Trasladar(double TrasX, double TrasY, double TrasZ)
{
	punto[0][1] = punto[0][1] + TrasX; punto[0][2] = punto[0][2] + TrasY; punto[0][3] = punto[0][3] + TrasZ;
	punto[1][1] = punto[1][1] + TrasX; punto[1][2] = punto[1][2] + TrasY; punto[1][3] = punto[1][3] + TrasZ;
	punto[2][1] = punto[2][1] + TrasX; punto[2][2] = punto[2][2] + TrasY; punto[2][3] = punto[2][3] + TrasZ;
	punto[3][1] = punto[3][1] + TrasX; punto[3][2] = punto[3][2] + TrasY; punto[3][3] = punto[3][3] + TrasZ;
	punto[4][1] = punto[4][1] + TrasX; punto[4][2] = punto[4][2] + TrasY; punto[4][3] = punto[4][3] + TrasZ;

	punto[5][1] = punto[5][1] + TrasX; punto[5][2] = punto[5][2] + TrasY; punto[5][3] = punto[5][3] + TrasZ;
	punto[6][1] = punto[6][1] + TrasX; punto[6][2] = punto[6][2] + TrasY; punto[6][3] = punto[6][3] + TrasZ;
	punto[7][1] = punto[7][1] + TrasX; punto[7][2] = punto[7][2] + TrasY; punto[7][3] = punto[7][3] + TrasZ;
	punto[8][1] = punto[8][1] + TrasX; punto[8][2] = punto[8][2] + TrasY; punto[8][3] = punto[8][3] + TrasZ;
	punto[9][1] = punto[9][1] + TrasX; punto[9][2] = punto[9][2] + TrasY; punto[9][3] = punto[9][3] + TrasZ;
	//Dibuja();
}

void C3DCubeDlg::RotaX(double angulo)
{
	
	//for (int i = 0; i < 1; i++)
	//{
		punto[0][1] = punto[0][1];
		punto[0][2] = punto[0][2] * cos(angulo) - punto[0][3] * sin(angulo);
		punto[0][3] = punto[0][2] * sin(angulo) + punto[0][3] * cos(angulo);


		punto[1][1] = punto[1][1];
		punto[1][2] = punto[1][2] * cos(angulo) - punto[1][3] * sin(angulo);
		punto[1][3] = punto[1][2] * sin(angulo) + punto[1][3] * cos(angulo);
		//punto p2
		punto[2][1] = punto[2][1];
		punto[2][2] = punto[2][2] * cos(angulo) - punto[2][3] * sin(angulo);
		punto[2][3] = punto[2][2] * sin(angulo) + punto[2][3] * cos(angulo);
		//punto p3
		punto[3][1] = punto[3][1];
		punto[3][2] = punto[3][2] * cos(angulo) - punto[3][3] * sin(angulo);
		punto[3][3] = punto[3][2] * sin(angulo) + punto[3][3] * cos(angulo);

		punto[4][1] = punto[4][1];
		punto[4][2] = punto[4][2] * cos(angulo) - punto[4][3] * sin(angulo);
		punto[4][3] = punto[4][2] * sin(angulo) + punto[4][3] * cos(angulo);

		punto[5][1] = punto[5][1];
		punto[5][2] = punto[5][2] * cos(angulo) - punto[5][3] * sin(angulo);
		punto[5][3] = punto[5][2] * sin(angulo) + punto[5][3] * cos(angulo);

		punto[6][1] = punto[6][1];
		punto[6][2] = punto[6][2] * cos(angulo) - punto[6][3] * sin(angulo);
		punto[6][3] = punto[6][2] * sin(angulo) + punto[6][3] * cos(angulo);

		//punto p7
		punto[7][1] = punto[7][1];
		punto[7][2] = punto[7][2] * cos(angulo) - punto[7][3] * sin(angulo);
		punto[7][3] = punto[7][2] * sin(angulo) + punto[7][3] * cos(angulo);
		//punto p8
		punto[8][1] = punto[8][1];
		punto[8][2] = punto[8][2] * cos(angulo) - punto[8][3] * sin(angulo);
		punto[8][3] = punto[8][2] * sin(angulo) + punto[8][3] * cos(angulo);

		//punto p9
		punto[9][1] = punto[9][1];
		punto[9][2] = punto[9][2] * cos(angulo) - punto[9][3] * sin(angulo);
		punto[9][3] = punto[9][2] * sin(angulo) + punto[9][3] * cos(angulo);

	//}
}


void C3DCubeDlg::RotaY(double anguloRY)
{
	//for (int i = 0; i < 40; i++)
	//{
		//punto p0
		punto[0][1] = punto[0][1] * cos(anguloRY) + punto[0][3] * sin(anguloRY);
		punto[0][2] = punto[0][2];
		punto[0][3] = -punto[0][1] * sin(anguloRY) + punto[0][3] * cos(anguloRY);
		//punto p1
		punto[1][1] = punto[1][1] * cos(anguloRY) + punto[1][3] * sin(anguloRY);
		punto[1][2] = punto[1][2];
		punto[1][3] = -punto[1][1] * sin(anguloRY) + punto[1][3] * cos(anguloRY);
		//punto p2
		punto[2][1] = punto[2][1] * cos(anguloRY) + punto[2][3] * sin(anguloRY);
		punto[2][2] = punto[2][2];
		punto[2][3] = -punto[2][1] * sin(anguloRY) + punto[2][3] * cos(anguloRY);
		//punto p3
		punto[3][1] = punto[3][1] * cos(anguloRY) + punto[3][3] * sin(anguloRY);
		punto[3][2] = punto[3][2];
		punto[3][3] = -punto[3][1] * sin(anguloRY) + punto[3][3] * cos(anguloRY);
		//punto p4
		punto[4][1] = punto[4][1] * cos(anguloRY) + punto[4][3] * sin(anguloRY);
		punto[4][2] = punto[4][2];
		punto[4][3] = -punto[4][1] * sin(anguloRY) + punto[4][3] * cos(anguloRY);

		punto[5][1] = punto[5][1] * cos(anguloRY) + punto[5][3] * sin(anguloRY);
		punto[5][2] = punto[5][2];
		punto[5][3] = -punto[5][1] * sin(anguloRY) + punto[5][3] * cos(anguloRY);

		punto[6][1] = punto[6][1] * cos(anguloRY) + punto[6][3] * sin(anguloRY);
		punto[6][2] = punto[6][2];
		punto[6][3] = -punto[6][1] * sin(anguloRY) + punto[6][3] * cos(anguloRY);

		punto[7][1] = punto[7][1] * cos(anguloRY) + punto[7][3] * sin(anguloRY);
		punto[7][2] = punto[7][2];
		punto[7][3] = -punto[7][1] * sin(anguloRY) + punto[7][3] * cos(anguloRY);

		punto[8][1] = punto[8][1] * cos(anguloRY) + punto[8][3] * sin(anguloRY);
		punto[8][2] = punto[8][2];
		punto[8][3] = -punto[8][1] * sin(anguloRY) + punto[8][3] * cos(anguloRY);

		punto[9][1] = punto[9][1] * cos(anguloRY) + punto[9][3] * sin(anguloRY);
		punto[9][2] = punto[9][2];
		punto[9][3] = -punto[9][1] * sin(anguloRY) + punto[9][3] * cos(anguloRY);

	//}
}

void C3DCubeDlg::RotaZ(double anguloRZ)
{
	// Apparently the rotation in Z has an error
	// if you find it, let me know from the contact page of the "the world of chaos" website
	// or suggest a modification in the project's github
	// repository	https://github.com/yacshagames/elmundodelcaos

	//for (int i = 0; i < 45; i++)
	//{//punto p0
		punto[0][1] = punto[0][1] * cos(anguloRZ) - punto[0][2] * sin(anguloRZ);
		punto[0][2] = punto[0][1] * sin(anguloRZ) + punto[0][2] * cos(anguloRZ);
		punto[0][3] = punto[0][3];
		//punto p1
		punto[1][1] = punto[1][1] * cos(anguloRZ) - punto[1][2] * sin(anguloRZ);
		punto[1][2] = punto[1][1] * sin(anguloRZ) + punto[1][2] * cos(anguloRZ);
		punto[1][3] = punto[1][3];
		//punto p2
		punto[2][1] = punto[2][1] * cos(anguloRZ) - punto[2][2] * sin(anguloRZ);
		punto[2][2] = punto[2][1] * sin(anguloRZ) + punto[2][2] * cos(anguloRZ);
		punto[2][3] = punto[2][3];
		//punto p3
		punto[3][1] = punto[3][1] * cos(anguloRZ) - punto[3][2] * sin(anguloRZ);
		punto[3][2] = punto[3][1] * sin(anguloRZ) + punto[3][2] * cos(anguloRZ);
		punto[3][3] = punto[3][3];
		//punto p4
		punto[4][1] = punto[4][1] * cos(anguloRZ) - punto[4][2] * sin(anguloRZ);
		punto[4][2] = punto[4][1] * sin(anguloRZ) + punto[4][2] * cos(anguloRZ);
		punto[4][3] = punto[4][3];

		punto[5][1] = punto[5][1] * cos(anguloRZ) - punto[5][2] * sin(anguloRZ);
		punto[5][2] = punto[5][1] * sin(anguloRZ) + punto[5][2] * cos(anguloRZ);
		punto[5][3] = punto[5][3];

		punto[6][1] = punto[6][1] * cos(anguloRZ) - punto[6][2] * sin(anguloRZ);
		punto[6][2] = punto[6][1] * sin(anguloRZ) + punto[6][2] * cos(anguloRZ);
		punto[6][3] = punto[6][3];

		punto[7][1] = punto[7][1] * cos(anguloRZ) - punto[7][2] * sin(anguloRZ);
		punto[7][2] = punto[7][1] * sin(anguloRZ) + punto[7][2] * cos(anguloRZ);
		punto[7][3] = punto[7][3];

		punto[8][1] = punto[8][1] * cos(anguloRZ) - punto[8][2] * sin(anguloRZ);
		punto[8][2] = punto[8][1] * sin(anguloRZ) + punto[8][2] * cos(anguloRZ);
		punto[8][3] = punto[8][3];

		punto[9][1] = punto[9][1] * cos(anguloRZ) - punto[9][2] * sin(anguloRZ);
		punto[9][2] = punto[9][1] * sin(anguloRZ) + punto[9][2] * cos(anguloRZ);
		punto[9][3] = punto[9][3];

	//}
}


void C3DCubeDlg::Dibuja()
{
	CClientDC dibujo(this);


	angulo[0] = 0.26179;
	angulo[1] = 0.52358;

	c[0] = 300;
	c[1] = 220;
	/*
	CPen NewPen3(PS_SOLID,
		3,
		RGB(192, 192, 192));
	dibujo.SelectObject(&NewPen3);


	dibujo.MoveTo(puntoc[0][1], puntoc[0][2]);
	dibujo.LineTo(puntoc[1][1], puntoc[1][2]);
	dibujo.LineTo(puntoc[2][1], puntoc[2][2]);
	dibujo.LineTo(puntoc[3][1], puntoc[3][2]);
	dibujo.LineTo(puntoc[4][1], puntoc[4][2]);

	dibujo.MoveTo(puntoc[5][1], puntoc[5][2]);
	dibujo.LineTo(puntoc[6][1], puntoc[6][2]);
	dibujo.LineTo(puntoc[7][1], puntoc[7][2]);
	dibujo.LineTo(puntoc[8][1], puntoc[8][2]);
	dibujo.LineTo(puntoc[9][1], puntoc[9][2]);

	dibujo.MoveTo(puntoc[0][1], puntoc[0][2]);
	dibujo.LineTo(puntoc[5][1], puntoc[5][2]);
	dibujo.MoveTo(puntoc[1][1], puntoc[1][2]);
	dibujo.LineTo(puntoc[6][1], puntoc[6][2]);
	dibujo.MoveTo(puntoc[2][1], puntoc[2][2]);
	dibujo.LineTo(puntoc[7][1], puntoc[7][2]);
	dibujo.MoveTo(puntoc[3][1], puntoc[3][2]);
	dibujo.LineTo(puntoc[8][1], puntoc[8][2]);
	*/
	// Convierte eje 3D a 2D
	ejec[0][1] = c[0] + eje[0][2] * cos(angulo[1]) - eje[0][1] * cos(angulo[0]);
	ejec[0][2] = c[1] - eje[0][3] + eje[0][1] * sin(angulo[0]) + eje[0][2] * sin(angulo[1]);
	ejec[1][1] = c[0] + eje[1][2] * cos(angulo[1]) - eje[1][1] * cos(angulo[0]);
	ejec[1][2] = c[1] - eje[1][3] + eje[1][1] * sin(angulo[0]) + eje[1][2] * sin(angulo[1]);
	ejec[2][1] = c[0] + eje[2][2] * cos(angulo[1]) - eje[2][1] * cos(angulo[0]);
	ejec[2][2] = c[1] - eje[2][3] + eje[2][1] * sin(angulo[0]) + eje[2][2] * sin(angulo[1]);
	ejec[3][1] = c[0] + eje[3][2] * cos(angulo[1]) - eje[3][1] * cos(angulo[0]);
	ejec[3][2] = c[1] - eje[3][3] + eje[3][1] * sin(angulo[0]) + eje[3][2] * sin(angulo[1]);

	// Convierte punto 3D a 2D

	puntoc[0][1] = c[0] + punto[0][2] * cos(angulo[1]) - punto[0][1] * cos(angulo[0]);
	puntoc[0][2] = c[1] - punto[0][3] + punto[0][1] * sin(angulo[0]) + punto[0][2] * sin(angulo[1]);
	puntoc[1][1] = c[0] + punto[1][2] * cos(angulo[1]) - punto[1][1] * cos(angulo[0]);
	puntoc[1][2] = c[1] - punto[1][3] + punto[1][1] * sin(angulo[0]) + punto[1][2] * sin(angulo[1]);
	puntoc[2][1] = c[0] + punto[2][2] * cos(angulo[1]) - punto[2][1] * cos(angulo[0]);
	puntoc[2][2] = c[1] - punto[2][3] + punto[2][1] * sin(angulo[0]) + punto[2][2] * sin(angulo[1]);
	puntoc[3][1] = c[0] + punto[3][2] * cos(angulo[1]) - punto[3][1] * cos(angulo[0]);
	puntoc[3][2] = c[1] - punto[3][3] + punto[3][1] * sin(angulo[0]) + punto[3][2] * sin(angulo[1]);
	puntoc[4][1] = c[0] + punto[4][2] * cos(angulo[1]) - punto[4][1] * cos(angulo[0]);
	puntoc[4][2] = c[1] - punto[4][3] + punto[4][1] * sin(angulo[0]) + punto[4][2] * sin(angulo[1]);

	puntoc[5][1] = c[0] + punto[5][2] * cos(angulo[1]) - punto[5][1] * cos(angulo[0]);
	puntoc[5][2] = c[1] - punto[5][3] + punto[0][1] * sin(angulo[0]) + punto[5][2] * sin(angulo[1]);
	puntoc[6][1] = c[0] + punto[6][2] * cos(angulo[1]) - punto[6][1] * cos(angulo[0]);
	puntoc[6][2] = c[1] - punto[6][3] + punto[1][1] * sin(angulo[0]) + punto[6][2] * sin(angulo[1]);
	puntoc[7][1] = c[0] + punto[7][2] * cos(angulo[1]) - punto[7][1] * cos(angulo[0]);
	puntoc[7][2] = c[1] - punto[7][3] + punto[2][1] * sin(angulo[0]) + punto[7][2] * sin(angulo[1]);
	puntoc[8][1] = c[0] + punto[8][2] * cos(angulo[1]) - punto[8][1] * cos(angulo[0]);
	puntoc[8][2] = c[1] - punto[8][3] + punto[3][1] * sin(angulo[0]) + punto[8][2] * sin(angulo[1]);
	puntoc[9][1] = c[0] + punto[9][2] * cos(angulo[1]) - punto[9][1] * cos(angulo[0]);
	puntoc[9][2] = c[1] - punto[9][3] + punto[4][1] * sin(angulo[0]) + punto[9][2] * sin(angulo[1]);


	// Crear pluma
	CPen NewPen1(PS_SOLID,
		1,
		RGB(0, 204, 33));
	dibujo.SelectObject(&NewPen1);

	// Dibuja Eje 3D
	dibujo.MoveTo(ejec[0][1], ejec[0][2]);
	dibujo.LineTo(ejec[1][1], ejec[1][2]);
	dibujo.MoveTo(ejec[0][1], ejec[0][2]);
	dibujo.LineTo(ejec[2][1], ejec[2][2]);
	dibujo.MoveTo(ejec[0][1], ejec[0][2]);
	dibujo.LineTo(ejec[3][1], ejec[3][2]);

	// Crea Pluma  
	CPen NewPen2(PS_SOLID,
		3,
		RGB(99, 204, 255));
	dibujo.SelectObject(&NewPen2);

	// Dibuja cubo
	dibujo.MoveTo(puntoc[0][1], puntoc[0][2]);
	dibujo.LineTo(puntoc[1][1], puntoc[1][2]);
	dibujo.LineTo(puntoc[2][1], puntoc[2][2]);
	dibujo.LineTo(puntoc[3][1], puntoc[3][2]);
	dibujo.LineTo(puntoc[4][1], puntoc[4][2]);

	dibujo.MoveTo(puntoc[5][1], puntoc[5][2]);
	dibujo.LineTo(puntoc[6][1], puntoc[6][2]);
	dibujo.LineTo(puntoc[7][1], puntoc[7][2]);
	dibujo.LineTo(puntoc[8][1], puntoc[8][2]);
	dibujo.LineTo(puntoc[9][1], puntoc[9][2]);

	dibujo.MoveTo(puntoc[0][1], puntoc[0][2]);
	dibujo.LineTo(puntoc[5][1], puntoc[5][2]);
	dibujo.MoveTo(puntoc[1][1], puntoc[1][2]);
	dibujo.LineTo(puntoc[6][1], puntoc[6][2]);
	dibujo.MoveTo(puntoc[2][1], puntoc[2][2]);
	dibujo.LineTo(puntoc[7][1], puntoc[7][2]);
	dibujo.MoveTo(puntoc[3][1], puntoc[3][2]);
	dibujo.LineTo(puntoc[8][1], puntoc[8][2]);
}





void C3DCubeDlg::OnCaptureChanged(CWnd *pWnd)
{
	// TODO: Add your message handler code here

	CDialog::OnCaptureChanged(pWnd);
}