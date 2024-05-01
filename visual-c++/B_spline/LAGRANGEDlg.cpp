// LAGRANGEDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "LAGRANGE.h"
#include "LAGRANGEDlg.h"
#include "afxdialogex.h"

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
// CLAGRANGEDlg dialog

CLAGRANGEDlg::CLAGRANGEDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLAGRANGEDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLAGRANGEDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLAGRANGEDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLAGRANGEDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CLAGRANGEDlg, CDialog)
	//{{AFX_MSG_MAP(CLAGRANGEDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_WM_LBUTTONDBLCLK()
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	ON_BN_CLICKED(IDC_BUTTON6, OnButton6)
	ON_BN_CLICKED(IDC_BUTTON7, OnButton7)
	ON_BN_CLICKED(IDC_BUTTON8, OnButton8)
	ON_BN_CLICKED(IDC_BUTTON9, OnButton9)
	ON_BN_CLICKED(IDC_BUTTON10, OnButton10)
	ON_BN_CLICKED(IDC_BUTTON11, OnButton11)
	ON_BN_CLICKED(IDC_BUTTON12, OnButton12)
	ON_BN_CLICKED(IDC_BUTTON13, OnButton13)
	ON_BN_CLICKED(IDC_BUTTON14, OnButton14)
	ON_BN_CLICKED(IDC_BUTTON15, OnButton15)
	ON_BN_CLICKED(IDC_BUTTON16, OnButton16)
	ON_BN_CLICKED(IDC_BUTTON18, OnButton18)
	ON_BN_CLICKED(IDC_BUTTON17, OnButton17)
	ON_BN_CLICKED(IDC_BUTTON21, OnButton21)
	ON_BN_CLICKED(IDC_BUTTON20, OnButton20)
	ON_BN_CLICKED(IDC_BUTTON19, OnButton19)
	ON_BN_CLICKED(IDC_BUTTON23, OnButton23)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLAGRANGEDlg message handlers

BOOL CLAGRANGEDlg::OnInitDialog()
{
	eje[0][1] = 0;	eje[0][2] = 0;    eje[0][3] = 0;
	eje[1][1] = 200;	eje[1][2] = 0;    eje[1][3] = 0;
	eje[2][1] = 0;	eje[2][2] = 200;    eje[2][3] = 0;
	eje[3][1] = 0;	eje[3][2] = 0;    eje[3][3] = 200;

	// Valores de los puntos
	p[0][1] = 25;	p[0][2] = 200;    p[0][3] = 125;
	p[1][1] = 60;	p[1][2] = 40;    p[1][3] = 0;
	p[2][1] = 0;	p[2][2] = 0;    p[2][3] = 0;

	t[0] = 0;	t[1] = 1;    t[2] = 2; t[3] = 3;	t[4] = 4;    t[5] = 5;
	angulo[0] = 0.26179;                             // 15/180*PI
	angulo[1] = 0.52358;                             // 30/180*PI

	c[1] = 420;
	c[2] = 410;

	k = 3; nodos = 6;
	npuntos = 2;
	//********************


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

void CLAGRANGEDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CLAGRANGEDlg::OnPaint()
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
HCURSOR CLAGRANGEDlg::OnQueryDragIcon()
{
	return (HCURSOR)m_hIcon;
}

void CLAGRANGEDlg::OnOK()
{
	// TODO: Add extra validation here

	CDialog::OnOK();
}

void CLAGRANGEDlg::OnButton1()
{
	OnInitDialog();

	Invalidate();
}

void CLAGRANGEDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	//Dibuja();
	CDialog::OnLButtonDblClk(nFlags, point);

}
void CLAGRANGEDlg::OnButton2()
{
	// trasladar en X
	Trasladar(20, 0, 0);

	Invalidate();
}

void CLAGRANGEDlg::OnButton3()
{
	// Trasladar en Y
	Trasladar(0, 20, 0);

	Invalidate();
}

void CLAGRANGEDlg::OnButton4()
{
	// Trasladar en Z
	Trasladar(0, 0, 20);

	Invalidate();
}

void CLAGRANGEDlg::OnButton5()
{
	// Trasladar en -X	
	Trasladar(-20, 0, 0);

	Invalidate();

}

void CLAGRANGEDlg::OnButton6()
{
	// Trasladar en -Y	
	Trasladar(0, -20, 0);

	Invalidate();
}

void CLAGRANGEDlg::OnButton7()
{
	// Trasladar en -Z	
	Trasladar(0, 0, -20);

	Invalidate();
}

void CLAGRANGEDlg::OnButton8()
{
	// Escalamiento (Aumentar)
	Escalamiento(2, 2, 2);

	Invalidate();
}

void CLAGRANGEDlg::OnButton9()
{
	// Escalamiento(Disminuir)
	Escalamiento(0.5, 0.5, 0.5);

	Invalidate();
}

void CLAGRANGEDlg::OnButton10()
{
	/*
	CClientDC di(this);
	// Rotar X
	di.TextOutW((c[1] - 42.5*cos(angulo[0]) + 120 * cos(angulo[1])), (c[2] + 42.5*sin(angulo[0]) + 120 * sin(angulo[1]) - 62.5), _T("p"));
	LimpiaCurva(c[1], c[2]);
	RotaX(0.872664646);
	LimpiaCurva(c[1], c[2]);
	Trasladar(42.5, 120, 62.5);*/

	// Rotar X
	RotaY(0.17453277777777777777777777777778);

	Invalidate();

}
void CLAGRANGEDlg::OnButton11()
{
	// Rotar Y
	RotaY(0.17453277777777777777777777777778);

	Invalidate();

}

void CLAGRANGEDlg::OnButton12()
{
	// Rotar Z
	RotaZ(0.17453277777777777777777777777778);

	Invalidate();

}

void CLAGRANGEDlg::OnButton13()
{
	// Rotar -X
	RotaX(-0.17453277777777777777777777777778);

	Invalidate();

}

void CLAGRANGEDlg::OnButton14()
{
	// Rotar -Y
	RotaY(-0.17453277777777777777777777777778);

	Invalidate();

}

void CLAGRANGEDlg::OnButton15()
{
	// Rotar -Z
	RotaZ(-0.17453277777777777777777777777778);

	Invalidate();

}

void CLAGRANGEDlg::OnButton16()
{
	// reflexion x
	Reflexion(1, -1, -1);

	Invalidate();

}

void CLAGRANGEDlg::OnButton18()
{
	// reflexion z
	Reflexion(-1, -1, 1);

	Invalidate();
}

void CLAGRANGEDlg::OnButton17()
{

	// reflexion y
	Reflexion(-1, 1, -1);

	Invalidate();

}

void CLAGRANGEDlg::OnButton21()
{
	//Reflexion XY	
	Reflexion(1, 1, -1);

	Invalidate();
}

void CLAGRANGEDlg::OnButton20()
{
	//Reflexion YZ	
	Reflexion(-1, 1, 1);

	Invalidate();

}

void CLAGRANGEDlg::OnButton19()
{
	//Reflexion XZ	
	Reflexion(1, -1, 1);

	Invalidate();
}

void CLAGRANGEDlg::OnButton23()
{
	//Reflexion ORIGEN	
	Reflexion(-1, -1, -1);

	Invalidate();

}




void CLAGRANGEDlg::RotaX(double anguloRX)
{

	//for (int i = 0; i < 1; i++)
//	{
		//LimpiaCurva(c[1], c[2]);
		//p0
		p[0][1] = p[0][1];
		p[0][2] = p[0][2] * cos(anguloRX) - p[0][3] * sin(anguloRX);
		p[0][3] = p[0][2] * sin(anguloRX) + p[0][3] * cos(anguloRX);
		//p1
		p[1][1] = p[1][1];
		p[1][2] = p[1][2] * cos(anguloRX) - p[1][3] * sin(anguloRX);
		p[1][3] = p[1][2] * sin(anguloRX) + p[1][3] * cos(anguloRX);
		//p2
		p[2][1] = p[2][1];
		p[2][2] = p[2][2] * cos(anguloRX) - p[2][3] * sin(anguloRX);
		p[2][3] = p[2][2] * sin(anguloRX) + p[2][3] * cos(anguloRX);

		//Curva(c[1], c[2]);
	//}
}

void CLAGRANGEDlg::RotaY(double anguloRY)
{

	//for (int i = 0; i < 1; i++)
	//{
		//punto p0
		p[0][1] = p[0][1] * cos(anguloRY) - p[0][3] * sin(anguloRY);
		p[0][2] = p[0][2];
		p[0][3] = p[0][1] * sin(anguloRY) + p[0][3] * cos(anguloRY);
		//punto p1
		p[1][1] = p[1][1] * cos(anguloRY) - p[1][3] * sin(anguloRY);
		p[1][2] = p[1][2];
		p[1][3] = p[1][1] * sin(anguloRY) + p[1][3] * cos(anguloRY);
		//punto p2
		p[2][1] = p[2][1] * cos(anguloRY) - p[2][3] * sin(anguloRY);
		p[2][2] = p[2][2];
		p[2][3] = p[2][1] * sin(anguloRY) + p[2][3] * cos(anguloRY);
		//Curva(c[1], c[2]);
	//}
}

void CLAGRANGEDlg::RotaZ(double anguloRZ)
{

	//for (int i = 0; i < 1; i++)
	//{
		//PUNTO p1
		p[0][1] = p[0][1] * cos(anguloRZ) - p[0][2] * sin(anguloRZ);
		p[0][2] = p[0][1] * sin(anguloRZ) + p[0][2] * cos(anguloRZ);
		p[0][3] = p[0][3];
		//punto p2
		p[1][1] = p[1][1] * cos(anguloRZ) - p[1][2] * sin(anguloRZ);
		p[1][2] = p[1][1] * sin(anguloRZ) + p[1][2] * cos(anguloRZ);
		p[1][3] = p[1][3];
		//punto p3
		p[2][1] = p[2][1] * cos(anguloRZ) - p[2][2] * sin(anguloRZ);
		p[2][2] = p[2][1] * sin(anguloRZ) + p[2][2] * cos(anguloRZ);
		p[2][3] = p[2][3];
//		Curva(c[1], c[2]);
	//}
}
void CLAGRANGEDlg::Trasladar(double TrasX, double TrasY, double TrasZ)
{
	//puntos  
	p[0][1] = p[0][1] + TrasX;
	p[0][2] = p[0][2] + TrasY;
	p[0][3] = p[0][3] + TrasZ;
	p[1][1] = p[1][1] + TrasX;
	p[1][2] = p[1][2] + TrasY;
	p[1][3] = p[1][3] + TrasZ;
	p[2][1] = p[2][1] + TrasX;
	p[2][2] = p[2][2] + TrasY;
	p[2][3] = p[2][3] + TrasZ;
	//Curva(c[1], c[2]);
}
void CLAGRANGEDlg::Escalamiento(double ex, double ey, double ez)
{
	//puntos p1  
	p[0][1] = p[0][1] * ex;
	p[0][2] = p[0][2] * ey;
	p[0][3] = p[0][3] * ez;
	//puntos p2
	p[1][1] = p[1][1] * ex;
	p[1][2] = p[1][2] * ey;
	p[1][3] = p[1][3] * ez;
	//puntos p3
	p[2][1] = p[2][1] * ex;
	p[2][2] = p[2][2] * ey;
	p[2][3] = p[2][3] * ez;

	//Curva(c[1], c[2]);
}

void CLAGRANGEDlg::Reflexion(double signo1, double signo2, double signo3)
{

	p[0][1] = p[0][1] * signo1; p[0][2] = p[0][2] * signo2; p[0][3] = p[0][3] * signo3;
	p[1][1] = p[1][1] * signo1; p[1][2] = p[1][2] * signo2; p[1][3] = p[1][3] * signo3;
	p[2][1] = p[2][1] * signo1; p[2][2] = p[2][2] * signo2; p[2][3] = p[2][3] * signo3;
	//Curva(c[1], c[2]);
}

void CLAGRANGEDlg::Curva(double cx, double cy)
{
	CClientDC dibu(this);

	double n1;
	tt = t[2];
	puntoaux[1] = 0; puntoaux[2] = 0; puntoaux[3] = 0;

	for (int j = 0; j <= nodos; j++)
	{
		n1 = Produc(tt, j, k);
		puntoaux[1] = puntoaux[1] + p[j][1] * n1;
		puntoaux[2] = puntoaux[2] + p[j][2] * n1;
		puntoaux[3] = puntoaux[3] + p[j][3] * n1;
	}
	pc[1][1] = cx + (-puntoaux[1] * cos(angulo[0]) + puntoaux[2] * cos(angulo[1]));
	pc[1][2] = cy + (puntoaux[1] * sin(angulo[0]) + puntoaux[2] * sin(angulo[1]) - puntoaux[3]);
	dibu.MoveTo(pc[1][1], pc[1][2]);

	do
	{
		puntoaux[1] = 0; puntoaux[2] = 0; puntoaux[3] = 0;

		for (int i = 0; i <= nodos; i++)
		{
			n1 = Produc(tt, i, k);
			puntoaux[1] = puntoaux[1] + p[i][1] * n1;
			puntoaux[2] = puntoaux[2] + p[i][2] * n1;
			puntoaux[3] = puntoaux[3] + p[i][3] * n1;
		}

		CPen NewPen2(PS_SOLID,
			2,
			RGB(255, 0, 0));
		dibu.SelectObject(&NewPen2);
		pc[1][1] = cx + (-puntoaux[1] * cos(angulo[0]) + puntoaux[2] * cos(angulo[1]));
		pc[1][2] = cy + (puntoaux[1] * sin(angulo[0]) + puntoaux[2] * sin(angulo[1]) - puntoaux[3]);
		dibu.LineTo(pc[1][1], pc[1][2]);

		tt = tt + 0.05;
	} while (tt <= t[npuntos + k - 2]);

}

void CLAGRANGEDlg::LimpiaCurva(double cx, double cy)
{
	CClientDC dibu(this);

	double n1;
	tt = t[2];
	puntoaux[1] = 0; puntoaux[2] = 0; puntoaux[3] = 0;

	for (int j = 0; j <= nodos; j++)
	{
		n1 = Produc(tt, j, k);
		puntoaux[1] = puntoaux[1] + p[j][1] * n1;
		puntoaux[2] = puntoaux[2] + p[j][2] * n1;
		puntoaux[3] = puntoaux[3] + p[j][3] * n1;
	}
	pc[1][1] = cx + (-puntoaux[1] * cos(angulo[0]) + puntoaux[2] * cos(angulo[1]));
	pc[1][2] = cy + (puntoaux[1] * sin(angulo[0]) + puntoaux[2] * sin(angulo[1]) - puntoaux[3]);
	dibu.MoveTo(pc[1][1], pc[1][2]);

	do
	{
		puntoaux[1] = 0; puntoaux[2] = 0; puntoaux[3] = 0;

		for (int i = 0; i <= nodos; i++)
		{
			n1 = Produc(tt, i, k);
			puntoaux[1] = puntoaux[1] + p[i][1] * n1;
			puntoaux[2] = puntoaux[2] + p[i][2] * n1;
			puntoaux[3] = puntoaux[3] + p[i][3] * n1;
		}

		CPen NewPen3(PS_SOLID,
			2,
			RGB(192, 192, 192));
		dibu.SelectObject(&NewPen3);
		pc[1][1] = cx + (-puntoaux[1] * cos(angulo[0]) + puntoaux[2] * cos(angulo[1]));
		pc[1][2] = cy + (puntoaux[1] * sin(angulo[0]) + puntoaux[2] * sin(angulo[1]) - puntoaux[3]);
		dibu.LineTo(pc[1][1], pc[1][2]);

		tt = tt + 0.05;
	} while (tt <= t[npuntos + k - 2]);

}


double CLAGRANGEDlg::Produc(double t1, int I, int K)
{
	double N; double R; double aux1; double aux2; double aux11; double aux22;

	if (K == 1)
	{
		if ((t1 >= t[I]) && (t1 < t[I + 1]))
		{
			N = 1;
		}
		else
		{
			N = 0;
		}
	}
	else
	{
		aux1 = (t[I + K - 1] - t[I]);
		aux2 = (t[I + K] - t[I + 1]);
		if (aux1 == 0)
		{
			aux11 = 0;
		}
		else
		{
			aux11 = (t1 - t[I]) / (t[I + K - 1] - t[I]);
		}

		if (aux2 == 0)
		{
			aux22 = 0;
		}
		else
		{
			aux22 = (t[I + K] - tt) / (t[I + K] - t[I + 1]);
		}

		R = aux11 * Produc(t1, I, K - 1) + aux22 * Produc(t1, I + 1, K - 1);

		if ((t1 >= t[I]) && (t1 < t[I + K]))
		{
			N = R;
		}
		else
		{
			N = 0;
		}
	}

	return N;
}


void CLAGRANGEDlg::Dibuja()
{
	CClientDC dibujo(this);

	// Conversión del eje de 3D a 2D
	ejec[0][1] = c[1] + eje[0][2] * cos(angulo[1]) - eje[0][1] * cos(angulo[0]);
	ejec[0][2] = c[2] - eje[0][3] + eje[0][1] * sin(angulo[0]) + eje[0][2] * sin(angulo[1]);
	ejec[1][1] = c[1] + eje[1][2] * cos(angulo[1]) - eje[1][1] * cos(angulo[0]);
	ejec[1][2] = c[2] - eje[1][3] + eje[1][1] * sin(angulo[0]) + eje[1][2] * sin(angulo[1]);
	ejec[2][1] = c[1] + eje[2][2] * cos(angulo[1]) - eje[2][1] * cos(angulo[0]);
	ejec[2][2] = c[2] - eje[2][3] + eje[2][1] * sin(angulo[0]) + eje[2][2] * sin(angulo[1]);
	ejec[3][1] = c[1] + eje[3][2] * cos(angulo[1]) - eje[3][1] * cos(angulo[0]);
	ejec[3][2] = c[2] - eje[3][3] + eje[3][1] * sin(angulo[0]) + eje[3][2] * sin(angulo[1]);


	// Crear y Usar Pluma
	CPen NewPen1(PS_SOLID,
		2,
		RGB(0, 102, 255));
	dibujo.SelectObject(&NewPen1);

	// Dibujar Eje 3d en pantalla
	dibujo.MoveTo(ejec[0][1], ejec[0][2]);
	dibujo.LineTo(ejec[1][1], ejec[1][2]);
	dibujo.MoveTo(ejec[0][1], ejec[0][2]);
	dibujo.LineTo(ejec[2][1], ejec[2][2]);
	dibujo.MoveTo(ejec[0][1], ejec[0][2]);
	dibujo.LineTo(ejec[3][1], ejec[3][2]);

	Curva(c[1], c[2]);;


}