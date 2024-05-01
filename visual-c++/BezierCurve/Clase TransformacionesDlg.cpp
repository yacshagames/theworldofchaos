// Clase TransformacionesDlg.cpp : implementation file
//

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
	m_Cex = 0.0;
	m_Cey = 0.0;
	m_Cez = 0.0;
	m_Nox = 0.0;
	m_Noy = 0.0;
	m_Noz = 0.0;
	m_Rox = 0.0;
	m_Roy = 0.0;
	m_Roz = 0.0;
	m_densidad = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClaseTransformacionesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClaseTransformacionesDlg)
	DDX_Text(pDX, IDC_Cex, m_Cex);
	DDX_Text(pDX, IDC_Cey, m_Cey);
	DDX_Text(pDX, IDC_Cez, m_Cez);
	DDX_Text(pDX, IDC_Nox, m_Nox);
	DDX_Text(pDX, IDC_Noy, m_Noy);
	DDX_Text(pDX, IDC_Noz, m_Noz);
	DDX_Text(pDX, IDC_Rox, m_Rox);
	DDX_Text(pDX, IDC_Roy, m_Roy);
	DDX_Text(pDX, IDC_Roz, m_Roz);
	DDX_Text(pDX, IDC_DENSIDAD, m_densidad);
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
	ON_BN_CLICKED(IDC_Dibujo, OnDibujo)
	ON_BN_CLICKED(IDC_Valinit, OnValinit)
	ON_BN_CLICKED(IDC_BUTTON2, OnTrasxN)
	ON_BN_CLICKED(IDC_Proyeccion, OnProyeccion)
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
	pi=3.1415926535897932384626433832795;

	anga=15;
    angb=30;

    Cx=320; 
    Cy=240; 

	n=7;
	densidad = 100;
	
	mt[1][1] = 1; mt[1][2] = 0; mt[1][3] = 0; mt[1][4] = 0;
	mt[2][1] = 0; mt[2][2] = 1; mt[2][3] = 0; mt[2][4] = 0;
	mt[3][1] = 0; mt[3][2] = 0; mt[3][3] = 1; mt[3][4] = 0;
	mt[4][1] = 0; mt[4][2] = 0; mt[4][3] = 0; mt[4][4] = 1;
	
	p[0][1] =   0; p[0][2] =   0; p[0][3] =   0; p[0][4] = 1;
	p[1][1] = 100; p[1][2] =   0; p[1][3] =   0; p[1][4] = 1;
	p[2][1] = 100; p[2][2] = 100; p[2][3] =   0; p[2][4] = 1;
	p[3][1] =   0; p[3][2] = 100; p[3][3] =   0; p[3][4] = 1;
	p[4][1] =   0; p[4][2] =   0; p[4][3] = 100; p[4][4] = 1;
	p[5][1] = 100; p[5][2] =   0; p[5][3] = 100; p[5][4] = 1;
	p[6][1] = 100; p[6][2] = 100; p[6][3] = 100; p[6][4] = 1;
	p[7][1] =   0; p[7][2] = 100; p[7][3] = 100; p[7][4] = 1;

	e3d[0][1] = 200; e3d[0][2] =   0; e3d[0][3] =   0; e3d[0][4] = 1;
	e3d[1][1] =   0; e3d[1][2] = 200; e3d[1][3] =   0; e3d[1][4] = 1;
	e3d[2][1] =   0; e3d[2][2] =   0; e3d[2][3] = 200; e3d[2][4] = 1;
	e3d[3][1] =   0; e3d[3][2] =   0; e3d[3][3] =   0; e3d[3][4] = 1;


	//Proyecciones

	normal[1] =  m_Nox = 1; normal[2] =   m_Noy = 0; normal[3] =   m_Noz = 0;      //Proyeccion Plano XY
	ro[1]     =  m_Rox = 0; ro[2]     =   m_Roy = 0; ro[3]     =   m_Roz = 0;
	centro[1] =  m_Cex = 0; centro[2] =   m_Cey = 0; centro[3] =   m_Cez = 0;
	
	m_densidad = densidad;
	UpdateData(FALSE);
	UpdateData(TRUE);


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

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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
	return (HCURSOR) m_hIcon;
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

  for (int i=0; i<=n; i++)
  {   
	  pm[i][1] = Cx + p3d[i][2] * cos(rad(auxb)) - p3d[i][1] * cos(rad(auxa));
	  pm[i][2] = Cy - p3d[i][3] + p3d[i][2] * sin(rad(auxb)) + p3d[i][1] * sin(rad(auxa));
  }

}

void CClaseTransformacionesDlg::Transformar_eje3d()
{
  double auxa = anga;
  double auxb = angb;

  for (int i=0; i<=3; i++)
  {
	  em[i][1] = Cx + e3d[i][2] * cos(rad(auxb)) - e3d[i][1] * cos(rad(auxa));
	  em[i][2] = Cy - e3d[i][3] + e3d[i][2] * sin(rad(auxb)) + e3d[i][1] * sin(rad(auxa));
  }

}

double CClaseTransformacionesDlg::rad(double angulo)
{
	return angulo*pi/180;
}

double CClaseTransformacionesDlg::f(int valor)
{
	int fo;
	if (valor==0)
	{
		fo = 1;
	}
	if (valor>0)
	{
		fo = valor * f(valor - 1);
	}

	return fo;
}

double CClaseTransformacionesDlg::B(int k, double tt)
{
	double Bo;

	Bo = (f(n) / (f(n-k) * f(k))) * pow(1-tt, n-k) * pow(tt, k);

	return Bo;
}

void CClaseTransformacionesDlg::MatxMat()
{
	for (int l=1; l<=4; l++)
		for (int m=1; m<=4; m++)
		{
			mataux[l][m] = mt[l][m];
		}

	for (int j=1; j<=4; j++)
	{
		for (int i=1; i<=4; i++)
		{
			mt[i][j] = 0;
			for (int k=1; k<=4; k++)
			{
				mt[i][j] = mt[i][j] + mm[i][k] * mataux[k][j];
			}
		}
	}
}

void CClaseTransformacionesDlg::MatxPto()
{

	for (int k=0; k<=n; k++)
	{
		b[1] = p[k][1];
		b[2] = p[k][2];
		b[3] = p[k][3];
		b[4] = p[k][4];

		for (int i=1; i<=4; i++)
		{
			c[i] = 0;
			for (int j=1; j<=4; j++)
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
			mm[1][1] = 1; mm[1][2] =             0; mm[1][3] =              0; mm[1][4] = 0;
			mm[2][1] = 0; mm[2][2] = cos(rad(ang)); mm[2][3] = -sin(rad(ang)); mm[2][4] = 0;
			mm[3][1] = 0; mm[3][2] = sin(rad(ang)); mm[3][3] =  cos(rad(ang)); mm[3][4] = 0;
			mm[4][1] = 0; mm[4][2] =             0; mm[4][3] =              0; mm[4][4] = 1;
			break;
		}
	case 2:
		{
			mm[1][1] =  cos(rad(ang)); mm[1][2] = 0; mm[1][3] = sin(rad(ang)); mm[1][4] = 0;
			mm[2][1] =              0; mm[2][2] = 1; mm[2][3] =             0; mm[2][4] = 0;
			mm[3][1] = -sin(rad(ang)); mm[3][2] = 0; mm[3][3] = cos(rad(ang)); mm[3][4] = 0;
			mm[4][1] =              0; mm[4][2] = 0; mm[4][3] =             0; mm[4][4] = 1;
			break;
		}
	case 3:
		{
			mm[1][1] =  cos(rad(ang)); mm[1][2] = sin(rad(ang)); mm[1][3] = 0; mm[1][4] = 0;
			mm[2][1] = -sin(rad(ang)); mm[2][2] = cos(rad(ang)); mm[2][3] = 0; mm[2][4] = 0;
			mm[3][1] =              0; mm[3][2] =             0; mm[3][3] = 1; mm[3][4] = 0;
			mm[4][1] =              0; mm[4][2] =             0; mm[4][3] = 0; mm[4][4] = 1;
			break;
		}
	}
	MatxMat();
}

void CClaseTransformacionesDlg::Proyectar()
{
	dividendo = (centro[1] * normal[1]) + (centro[2] * normal[2]) + (centro[3] * normal[3]);
	divisor = (ro[1] - centro[1]) * normal[1] + (ro[2] - centro[2]) * normal[2] + (ro[3] - centro[3]) * normal[3];

	mm[1][1] = 1 + (centro[1] * normal[1] / divisor);  mm[1][2] =     (centro[1] * normal[2] / divisor);  mm[1][3] =     (centro[1] * normal[3] / divisor);  mm[1][4] = 0 - centro[1] - (dividendo / divisor * centro[1]);
	mm[2][1] =     (centro[2] * normal[1] / divisor);  mm[2][2] = 1 + (centro[2] * normal[2] / divisor);  mm[2][3] =     (centro[2] * normal[3] / divisor);  mm[2][4] = 0 - centro[2] - (dividendo / divisor * centro[2]);
	mm[3][1] =     (centro[3] * normal[1] / divisor);  mm[3][2] =     (centro[3] * normal[2] / divisor);  mm[3][3] = 1 + (centro[3] * normal[3] / divisor);  mm[3][4] = 0 - centro[3] - (dividendo / divisor * centro[3]);
	mm[4][1] =                 (normal[1] / divisor);  mm[4][2] =                 (normal[2] / divisor);  mm[4][3] =                 (normal[3] / divisor);  mm[4][4] =                         0 - (dividendo / divisor);

	MatxMat();
}


void CClaseTransformacionesDlg::Dibujar_Cuadrado()
{   
	//Dibuja Curva de Newton
    double auxa = anga;
    double auxb = angb;

	OnEje3D();
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
	for (int k=1; k<=densidad; k++)
	{
		PtoAux[1] = 0;
		PtoAux[2] = 0;
		PtoAux[3] = 0;
		PtoAux[4] = 0;

		double ka = k;					//Para divisiones es necesario que alguno
		double densidada = densidad;    //de los parámetros sea un numero real.
		tt = (ka)/(densidada);
		
		for (int i=0; i<=n; i++)
		{
			double BAR;
			BAR = B(i,tt);
			PtoAux[1] = (PtoAux[1] + (p3d[i][1] * B(i,tt)));
			PtoAux[2] = (PtoAux[2] + (p3d[i][2] * B(i,tt)));
			PtoAux[3] = (PtoAux[3] + (p3d[i][3] * B(i,tt)));

			
		}

		PtoAuxM[1] = Cx + PtoAux[2] * cos(rad(auxb)) - PtoAux[1] * cos(rad(auxa));
		PtoAuxM[2] = Cy - PtoAux[3] + PtoAux[2] * sin(rad(auxb)) + PtoAux[1] * sin(rad(auxa));
		pDC.LineTo(PtoAuxM[1], PtoAuxM[2]);
	}
	
}

double CClaseTransformacionesDlg::W(int i, double tt)
{
	double Wo;

	if (i==0)
	{
		Wo = 1 ;
	}
	if (i>0)
	{
		Wo = (tt - T[i-1]) * W(i-1, tt);
	}

	return Wo;
}

void CClaseTransformacionesDlg::Obtener_An() 
{
	for (int z=0; z<=n; z++)		//Q[i][0] = P[i]
	{
		Q[z][0][1] = p3d[z][1];
		Q[z][0][2] = p3d[z][2];
		Q[z][0][3] = p3d[z][3];
		Q[z][0][4] = p3d[z][4];
	}

	for (int j=1; j<=n; j++)		//Q[i][j]
	{
		for (int i=j; i<=n; i++)
		{
			Q[i][j][1] = (Q[i][j-1][1] - Q[i-1][j-1][1]) / (T[i] - T[i-j]);
			Q[i][j][2] = (Q[i][j-1][2] - Q[i-1][j-1][2]) / (T[i] - T[i-j]);
			Q[i][j][3] = (Q[i][j-1][3] - Q[i-1][j-1][3]) / (T[i] - T[i-j]);
			Q[i][j][4] = (Q[i][j-1][4] - Q[i-1][j-1][4]) / (T[i] - T[i-j]);
		}
	}

	for (int y=0; y<=n; y++)		//A[i]
	{
		A[y][1] = Q[y][y][1];
		A[y][2] = Q[y][y][2];
		A[y][3] = Q[y][y][3];
		A[y][4] = 1;
	}
}

void CClaseTransformacionesDlg::OnTrasXPos() 
{
	// TODO: Add your control notification handler code here
	Trasladar(5,0,0);                     
	MatxPto();                            
	Dibujar_Cuadrado();
}

void CClaseTransformacionesDlg::OnTrasxN() 
{
	// TODO: Add your control notification handler code here
	Trasladar(-5,0,0);                     
	MatxPto();                            
	Dibujar_Cuadrado();
	
}

void CClaseTransformacionesDlg::OnTrasYPos() 
{
	// TODO: Add your control notification handler code here
	Trasladar(0,5,0);                     
	MatxPto();                            
	Dibujar_Cuadrado();
	
}

void CClaseTransformacionesDlg::OnTrasyN() 
{
	// TODO: Add your control notification handler code here
	Trasladar(0,-5,0);                     
	MatxPto();                            
	Dibujar_Cuadrado();
	
}

void CClaseTransformacionesDlg::OnTrasZPos() 
{
	// TODO: Add your control notification handler code here
	Trasladar(0,0,5);                     
	MatxPto();                            
	Dibujar_Cuadrado();
	
}

void CClaseTransformacionesDlg::OnTraszN() 
{
	// TODO: Add your control notification handler code here
	Trasladar(0,0,-5);                     
	MatxPto();                            
	Dibujar_Cuadrado();
	
}

void CClaseTransformacionesDlg::DibujaEje() 
{
	CClientDC pDC(this);

    pDC.Rectangle(5,5,630,470);
	pDC.MoveTo(em[3][1],em[3][2]);
	pDC.LineTo(em[0][1],em[0][2]);
	pDC.MoveTo(em[3][1],em[3][2]);
	pDC.LineTo(em[1][1],em[1][2]);
	pDC.MoveTo(em[3][1],em[3][2]);
	pDC.LineTo(em[2][1],em[2][2]);
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
	Dibujar_Cuadrado();
		
}

void CClaseTransformacionesDlg::OnRotXN() 
{
	// TODO: Add your control notification handler code here
	Rotar(1, -5);                     
	MatxPto();                            
	Dibujar_Cuadrado();
		
}

void CClaseTransformacionesDlg::OnRotYP() 
{
	// TODO: Add your control notification handler code here
	Rotar(2, 5);                     
	MatxPto();                            
	Dibujar_Cuadrado();
		
}

void CClaseTransformacionesDlg::OnRotYN() 
{
	// TODO: Add your control notification handler code here
	Rotar(2, -5);                     
	MatxPto();                            
	Dibujar_Cuadrado();
		
}

void CClaseTransformacionesDlg::OnRotZP() 
{
	// TODO: Add your control notification handler code here
	Rotar(3, 5);                     
	MatxPto();                            
	Dibujar_Cuadrado();
		
}

void CClaseTransformacionesDlg::OnRotZN() 
{
	// TODO: Add your control notification handler code here
	Rotar(3, -5);                     
	MatxPto();                            
	Dibujar_Cuadrado();
		
}


void CClaseTransformacionesDlg::OnEscP() 
{
	// TODO: Add your control notification handler code here
	Escalar(1.25,1.25,1.25);                     
	MatxPto();                            
	Dibujar_Cuadrado();
}

void CClaseTransformacionesDlg::OnEscN() 
{
	// TODO: Add your control notification handler code here
	Escalar(.75,.75,.75);                     
	MatxPto();                            
	Dibujar_Cuadrado();
}

void CClaseTransformacionesDlg::OnDibujo() 
{
	// TODO: Add your control notification handler code here
	MatxPto();
	Dibujar_Cuadrado();
	
}

void CClaseTransformacionesDlg::OnValinit() 
{
	// TODO: Add your control notification handler code here
	mt[1][1] = 1; mt[1][2] = 0; mt[1][3] = 0; mt[1][4] = 0;
	mt[2][1] = 0; mt[2][2] = 1; mt[2][3] = 0; mt[2][4] = 0;
	mt[3][1] = 0; mt[3][2] = 0; mt[3][3] = 1; mt[3][4] = 0;
	mt[4][1] = 0; mt[4][2] = 0; mt[4][3] = 0; mt[4][4] = 1;

	MatxPto();
	Dibujar_Cuadrado();
}

void CClaseTransformacionesDlg::OnProyeccion() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	normal[1] =  m_Nox; normal[2] =   m_Noy; normal[3] =   m_Noz;      //Proyeccion Plano XY
	ro[1]     =  m_Rox; ro[2]     =   m_Roy; ro[3]     =   m_Roz;
	centro[1] =  m_Cex; centro[2] =   m_Cey; centro[3] =   m_Cez;

	Proyectar();
	MatxPto();
	Dibujar_Cuadrado();
}
