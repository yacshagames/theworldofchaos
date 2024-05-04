// CurvasDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Curvas.h"
#include "CurvasDlg.h"

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
// CCurvasDlg dialog

CCurvasDlg::CCurvasDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCurvasDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCurvasDlg)
	m_P1X = 0.0;
	m_P1Y = 0.0;
	m_P1Z = 0.0;
	m_P3X = 0.0;
	m_P3Y = 0.0;
	m_P3Z = 0.0;
	m_P5X = 0.0;
	m_P5Y = 0.0;
	m_P5Z = 0.0;
	m_P6X = 0.0;
	m_P6Y = 0.0;
	m_P6Z = 0.0;
	m_P4X = 0.0;
	m_P4Y = 0.0;
	m_P4Z = 0.0;
	m_P2X = 0.0;
	m_P2Y = 0.0;
	m_P2Z = 0.0;
	m_EjeRotacion = 0;
	m_EjeTraslacion = 0;
	m_ActivaNewton = FALSE;
	m_ActivaLagrange = FALSE;
	m_ActivaBezier = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCurvasDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCurvasDlg)
	DDX_Control(pDX, IDC_FONDO, m_Fondo);
	DDX_Text(pDX, IDC_P1X, m_P1X);
	DDX_Text(pDX, IDC_P1Y, m_P1Y);
	DDX_Text(pDX, IDC_P1Z, m_P1Z);
	DDX_Text(pDX, IDC_P3X, m_P3X);
	DDX_Text(pDX, IDC_P3Y, m_P3Y);
	DDX_Text(pDX, IDC_P3Z, m_P3Z);
	DDX_Text(pDX, IDC_P5X, m_P5X);
	DDX_Text(pDX, IDC_P5Y, m_P5Y);
	DDX_Text(pDX, IDC_P5Z, m_P5Z);
	DDX_Text(pDX, IDC_P6X, m_P6X);
	DDX_Text(pDX, IDC_P6Y, m_P6Y);
	DDX_Text(pDX, IDC_P6Z, m_P6Z);
	DDX_Text(pDX, IDC_P4X, m_P4X);
	DDX_Text(pDX, IDC_P4Y, m_P4Y);
	DDX_Text(pDX, IDC_P4Z, m_P4Z);
	DDX_Text(pDX, IDC_P2X, m_P2X);
	DDX_Text(pDX, IDC_P2Y, m_P2Y);
	DDX_Text(pDX, IDC_P2Z, m_P2Z);
	DDX_Radio(pDX, IDC_RADIO_ROTARX, m_EjeRotacion);
	DDX_Radio(pDX, IDC_RADIO_TRASX, m_EjeTraslacion);
	DDX_Check(pDX, IDC_CURVANEWTON, m_ActivaNewton);
	DDX_Check(pDX, IDC_CURVALAGRANGE, m_ActivaLagrange);
	DDX_Check(pDX, IDC_CURVABEZIER, m_ActivaBezier);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCurvasDlg, CDialog)
	//{{AFX_MSG_MAP(CCurvasDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_TRASLADARMAS, OnTrasladarmas)
	ON_BN_CLICKED(IDC_TRASLADARMENOS, OnTrasladarmenos)
	ON_BN_CLICKED(IDC_ROTARMAS, OnRotarmas)
	ON_BN_CLICKED(IDC_ROTARMENOS, OnRotarmenos)
	ON_BN_CLICKED(IDC_ACTUALIZARPOLIGONAL, OnActualizarpoligonal)
	ON_BN_CLICKED(IDC_REINICIARDIBUJO, OnReiniciardibujo)
	ON_BN_CLICKED(IDC_CURVANEWTON, OnCurvanewton)
	ON_BN_CLICKED(IDC_CURVALAGRANGE, OnCurvalagrange)
	ON_BN_CLICKED(IDC_CURVABEZIER, OnCurvabezier)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCurvasDlg message handlers

BOOL CCurvasDlg::OnInitDialog()
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
	//SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
		pi=3.1415926535897932384626433832795;

	anga=15;
    angb=30;
    
	//coordenadas del origen de coordenadas
	//en el plano 2D de la pantalla
	CRect rect;
	m_Fondo.GetClientRect(&rect);

	Cx = (rect.right-rect.left)/2; //coordenada x
    Cy = (rect.bottom-rect.top)/2; //coordenada y

	n=5;
	densidad = 100;
	
    Inicializar_Puntos();

	e3d[0][1] = 200; e3d[0][2] =   0; e3d[0][3] =   0; e3d[0][4] = 1;
	e3d[1][1] =   0; e3d[1][2] = 200; e3d[1][3] =   0; e3d[1][4] = 1;
	e3d[2][1] =   0; e3d[2][2] =   0; e3d[2][3] = 200; e3d[2][4] = 1;
	e3d[3][1] =   0; e3d[3][2] =   0; e3d[3][3] =   0; e3d[3][4] = 1;

//	T[0] = 0;	T[1] = 1;	T[2] = 2;	T[3] = 3;	T[4] = 4;	T[5] = 5;
//	T[6] = 6;	T[7] = 7;
//	T[0] = 0;	T[1] = 2;	T[2] = 4;	T[3] = 6;	T[4] = 12;	T[5] = 15;
//	T[6] = 18;	T[7] = 21;

	T[0] = 0;	T[1] = 1;	T[2] = 3;	T[3] = 6;	T[4] = 10;	T[5] = 15;
	T[6] = 21;	T[7] = 28;
	

	//Proyecciones
/*
	normal[1] =  m_Nox = 1; normal[2] =   m_Noy = 0; normal[3] =   m_Noz = 0;      //Proyeccion Plano XY
	ro[1]     =  m_Rox = 0; ro[2]     =   m_Roy = 0; ro[3]     =   m_Roz = 0;
	centro[1] =  m_Cex = 0; centro[2] =   m_Cey = 0; centro[3] =   m_Cez = 0;
	
	m_densidad = densidad;
	UpdateData(FALSE);
	UpdateData(TRUE);
*/	

	//Inicializando coordenadas de la poligonal
	m_P1X = p[0][1]; m_P1Y = p[0][2]; m_P1Z = p[0][3];
	m_P2X = p[1][1]; m_P2Y = p[1][2]; m_P2Z = p[1][3];
	m_P3X = p[2][1]; m_P3Y = p[2][2]; m_P3Z = p[2][3];
	m_P4X = p[3][1]; m_P4Y = p[3][2]; m_P4Z = p[3][3];
	m_P5X = p[4][1]; m_P5Y = p[4][2]; m_P5Z = p[4][3];
	m_P6X = p[5][1]; m_P6Y = p[5][2]; m_P6Z = p[5][3];

	UpdateData(false);

	
    //Limita la región de dibujo a solo el area cliente de m_Fondo

	CRgn RegionDeDibujo;

 	RegionDeDibujo.CreateRectRgn(rect.left,rect.top,rect.right,rect.bottom);

	pDC = m_Fondo.GetDC(); //se obtiene el DC de m_Fondo
	
	pDC->SelectClipRgn(&RegionDeDibujo); 
		
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCurvasDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCurvasDlg::OnPaint() 
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

	Dibujar_Sistema();
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCurvasDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CCurvasDlg::Transformar_puntos3d()
{
  double auxa = anga;
  double auxb = angb;

  for (int i=0; i<=n; i++)
  {   
	  pm[i][1] = Cx + p3d[i][2] * cos(rad(auxb)) - p3d[i][1] * cos(rad(auxa));
	  pm[i][2] = Cy - p3d[i][3] + p3d[i][2] * sin(rad(auxb)) + p3d[i][1] * sin(rad(auxa));
  }

}

void CCurvasDlg::Transformar_eje3d()
{
  double auxa = anga;
  double auxb = angb;

  for (int i=0; i<=3; i++)
  {
	  em[i][1] = Cx + e3d[i][2] * cos(rad(auxb)) - e3d[i][1] * cos(rad(auxa));
	  em[i][2] = Cy - e3d[i][3] + e3d[i][2] * sin(rad(auxb)) + e3d[i][1] * sin(rad(auxa));
  }

}

void CCurvasDlg::DibujaEje() 
{

	CPen Lapiz(PS_SOLID, 2, RGB(108,182,255));
	pDC->SelectObject(&Lapiz);

	pDC->MoveTo(em[3][1],em[3][2]);
	pDC->LineTo(em[0][1],em[0][2]);
	pDC->MoveTo(em[3][1],em[3][2]);
	pDC->LineTo(em[1][1],em[1][2]);
	pDC->MoveTo(em[3][1],em[3][2]);
	pDC->LineTo(em[2][1],em[2][2]);
}

double CCurvasDlg::rad(double angulo)
{
	return angulo*pi/180;
}

void CCurvasDlg::MatxMat()
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

void CCurvasDlg::MatxPto()
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

void CCurvasDlg::Trasladar(double Tx, double Ty, double Tz)
{
	mm[1][1] = 1;  mm[1][2] = 0;  mm[1][3] = 0;  mm[1][4] = Tx;
	mm[2][1] = 0;  mm[2][2] = 1;  mm[2][3] = 0;  mm[2][4] = Ty;
	mm[3][1] = 0;  mm[3][2] = 0;  mm[3][3] = 1;  mm[3][4] = Tz;
	mm[4][1] = 0;  mm[4][2] = 0;  mm[4][3] = 0;  mm[4][4] = 1;

	MatxMat();
}

void CCurvasDlg::Escalar(double Ex, double Ey, double Ez)
{
	mm[1][1] = Ex; mm[1][2] = 0;  mm[1][3] = 0;  mm[1][4] = 0;
	mm[2][1] = 0;  mm[2][2] = Ey; mm[2][3] = 0;  mm[2][4] = 0;
	mm[3][1] = 0;  mm[3][2] = 0;  mm[3][3] = Ez; mm[3][4] = 0;
	mm[4][1] = 0;  mm[4][2] = 0;  mm[4][3] = 0;  mm[4][4] = 1;

	MatxMat();
}

void CCurvasDlg::Rotar(int Eje, double ang)
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

void CCurvasDlg::Proyectar()
{
	dividendo = (centro[1] * normal[1]) + (centro[2] * normal[2]) + (centro[3] * normal[3]);
	divisor = (ro[1] - centro[1]) * normal[1] + (ro[2] - centro[2]) * normal[2] + (ro[3] - centro[3]) * normal[3];

	mm[1][1] = 1 + (centro[1] * normal[1] / divisor);  mm[1][2] =     (centro[1] * normal[2] / divisor);  mm[1][3] =     (centro[1] * normal[3] / divisor);  mm[1][4] = 0 - centro[1] - (dividendo / divisor * centro[1]);
	mm[2][1] =     (centro[2] * normal[1] / divisor);  mm[2][2] = 1 + (centro[2] * normal[2] / divisor);  mm[2][3] =     (centro[2] * normal[3] / divisor);  mm[2][4] = 0 - centro[2] - (dividendo / divisor * centro[2]);
	mm[3][1] =     (centro[3] * normal[1] / divisor);  mm[3][2] =     (centro[3] * normal[2] / divisor);  mm[3][3] = 1 + (centro[3] * normal[3] / divisor);  mm[3][4] = 0 - centro[3] - (dividendo / divisor * centro[3]);
	mm[4][1] =                 (normal[1] / divisor);  mm[4][2] =                 (normal[2] / divisor);  mm[4][3] =                 (normal[3] / divisor);  mm[4][4] =                         0 - (dividendo / divisor);

	MatxMat();
}




//CURVA NEWTON

double CCurvasDlg::W(int i, double tt)
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

void CCurvasDlg::Obtener_An() 
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


void CCurvasDlg::Dibujar_Curva_Newton()
{   
	T[0] = 0;	T[1] = 1;	T[2] = 3;	T[3] = 6;	T[4] = 10;	T[5] = 15;
	T[6] = 21;	T[7] = 28;
	
	//Dibuja Curva de Newton
    double auxa = anga;
    double auxb = angb;


	//Proceso de An
	Obtener_An();

	//Convertir P0 a Coordenadas de Monitor
	PtoAux[1] = p3d[0][1];
	PtoAux[2] = p3d[0][2];
	PtoAux[3] = p3d[0][3];
	PtoAuxM[1] = Cx + PtoAux[2] * cos(rad(auxb)) - PtoAux[1] * cos(rad(auxa));
	PtoAuxM[2] = Cy - PtoAux[3] + PtoAux[2] * sin(rad(auxb)) + PtoAux[1] * sin(rad(auxa));
    pDC->MoveTo(PtoAuxM[1], PtoAuxM[2]);
	//Curva
	CPen LapizVerde(PS_SOLID, 1, RGB(0,255,0));
	pDC->SelectObject(&LapizVerde);
	UpdateData(TRUE);
	densidad = 100;//m_densidad;
	for (int k=1; k<=densidad; k++)
	{
		PtoAux[1] = 0;
		PtoAux[2] = 0;
		PtoAux[3] = 0;
		PtoAux[4] = 0;
		tt= (T[0] + (((T[n] - T[0]) / densidad) * k));
		
		for (int i=0; i<=n; i++)
		{
			double w1;
			w1 = W(i,tt);
			PtoAux[1] = (PtoAux[1] + (A[i][1] * W(i,tt)));
			PtoAux[2] = (PtoAux[2] + (A[i][2] * W(i,tt)));
			PtoAux[3] = (PtoAux[3] + (A[i][3] * W(i,tt)));
		}

		PtoAuxM[1] = Cx + PtoAux[2] * cos(rad(auxb)) - PtoAux[1] * cos(rad(auxa));
		PtoAuxM[2] = Cy - PtoAux[3] + PtoAux[2] * sin(rad(auxb)) + PtoAux[1] * sin(rad(auxa));

        pDC->LineTo(PtoAuxM[1], PtoAuxM[2]);
	}
	
}


//CURVA LAGRANGE
double CCurvasDlg::Ln(int k, double tt)
{
	double Lo;
	Lo = 1;
	for (int j=0; j<=n; j++)
	{
		if (j==k)
		{

		}
		else
		{
			Lo = Lo * (tt - T[j]) / (T[k] - T[j]);
		}
	}

	return Lo;
}


void CCurvasDlg::Dibujar_Curva_Lagrange()
{   
   T[0] = 0;	T[1] = 2;	T[2] = 4;	T[3] = 6;	T[4] = 10;	T[5] = 15;
   T[6] = 21;	T[7] = 28;


	//Dibuja Curva de Lagrange
    double auxa = anga;
    double auxb = angb;


	//Convertir P0 a Coordenadas de Monitor
	PtoAux[1] = p3d[0][1];
	PtoAux[2] = p3d[0][2];
	PtoAux[3] = p3d[0][3];
	PtoAuxM[1] = Cx + PtoAux[2] * cos(rad(auxb)) - PtoAux[1] * cos(rad(auxa));
	PtoAuxM[2] = Cy - PtoAux[3] + PtoAux[2] * sin(rad(auxb)) + PtoAux[1] * sin(rad(auxa));
    pDC->MoveTo(PtoAuxM[1], PtoAuxM[2]);

	//Curva
	CPen LapizAzul(PS_SOLID, 1, RGB(255,183,111));
	pDC->SelectObject(&LapizAzul);
	UpdateData(TRUE);
	densidad = 100;//m_densidad;
	for (int k=1; k<=densidad; k++)
	{
		PtoAux[1] = 0;
		PtoAux[2] = 0;
		PtoAux[3] = 0;
		PtoAux[4] = 0;
		tt= (T[0] + (((T[n] - T[0]) / densidad) * k));
		
		for (int i=0; i<=n; i++)
		{
			PtoAux[1] = (PtoAux[1] + (p3d[i][1] * Ln(i,tt)));
			PtoAux[2] = (PtoAux[2] + (p3d[i][2] * Ln(i,tt)));
			PtoAux[3] = (PtoAux[3] + (p3d[i][3] * Ln(i,tt)));
		}

		PtoAuxM[1] = Cx + PtoAux[2] * cos(rad(auxb)) - PtoAux[1] * cos(rad(auxa));
		PtoAuxM[2] = Cy - PtoAux[3] + PtoAux[2] * sin(rad(auxb)) + PtoAux[1] * sin(rad(auxa));
		pDC->LineTo(PtoAuxM[1], PtoAuxM[2]);
	}
	
}

//CURVA BEZIER

double CCurvasDlg::f(int valor)
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

double CCurvasDlg::B(int k, double tt)
{
	double Bo;

	Bo = (f(n) / (f(n-k) * f(k))) * pow(1-tt, n-k) * pow(tt, k);

	return Bo;
}

void CCurvasDlg::Dibujar_Curva_Bezier()
{   
	//Dibuja Curva de Bezier
    double auxa = anga;
    double auxb = angb;


	//Convertir P0 a Coordenadas de Monitor
	PtoAux[1] = p3d[0][1];
	PtoAux[2] = p3d[0][2];
	PtoAux[3] = p3d[0][3];
	PtoAuxM[1] = Cx + PtoAux[2] * cos(rad(auxb)) - PtoAux[1] * cos(rad(auxa));
	PtoAuxM[2] = Cy - PtoAux[3] + PtoAux[2] * sin(rad(auxb)) + PtoAux[1] * sin(rad(auxa));
    pDC->MoveTo(PtoAuxM[1], PtoAuxM[2]);
	//Curva
	CPen LapizRojo(PS_SOLID, 1, RGB(255,255,0));
	pDC->SelectObject(&LapizRojo);
	UpdateData(TRUE);
	densidad = 100;//m_densidad;
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
		pDC->LineTo(PtoAuxM[1], PtoAuxM[2]);
	}
	
}

//IMPLEMENTACION DE FUNCIONES DE DIBUJO DEL SISTEMA POLIGONAL-CURVAS

void CCurvasDlg::Dibujar_Poligonal()
{
    double auxa = anga;
    double auxb = angb;
	
 	//Convertir P0 a Coordenadas de Monitor
	PtoAux[1] = p3d[0][1];
	PtoAux[2] = p3d[0][2];
	PtoAux[3] = p3d[0][3];
	PtoAuxM[1] = Cx + PtoAux[2] * cos(rad(auxb)) - PtoAux[1] * cos(rad(auxa));
	PtoAuxM[2] = Cy - PtoAux[3] + PtoAux[2] * sin(rad(auxb)) + PtoAux[1] * sin(rad(auxa));
    pDC->MoveTo(PtoAuxM[1], PtoAuxM[2]);
	//Poligono
	CPen LapizVerde(PS_DOT, 1, RGB(0,0,0));
	pDC->SelectObject(&LapizVerde);
	for (int l=1; l<=n; l++)
	{
		PtoAuxM[1] = Cx + p3d[l][2] * cos(rad(auxb)) - p3d[l][1] * cos(rad(auxa));
		PtoAuxM[2] = Cy - p3d[l][3] + p3d[l][2] * sin(rad(auxb)) + p3d[l][1] * sin(rad(auxa));
		pDC->LineTo(PtoAuxM[1], PtoAuxM[2]);
	}
}

void CCurvasDlg::Dibujar_Curvas()
{
  	//Dibuja solo las curvas activas
	UpdateData(true);

	if( m_ActivaNewton )
	 Dibujar_Curva_Newton();

	if( m_ActivaLagrange )
	 Dibujar_Curva_Lagrange();

	if( m_ActivaBezier )
	 Dibujar_Curva_Bezier();

}

void CCurvasDlg::Dibujar_Sistema()
{
	MatxPto();
    m_Fondo.RedrawWindow();
	Transformar_eje3d();
	DibujaEje();
	Dibujar_Poligonal();
	Dibujar_Curvas();
	Actualizar_puntos_en_caja_de_dialogo();

}

void CCurvasDlg::Inicializar_Puntos()
{
	
    mt[1][1] = 1; mt[1][2] = 0; mt[1][3] = 0; mt[1][4] = 0;
	mt[2][1] = 0; mt[2][2] = 1; mt[2][3] = 0; mt[2][4] = 0;
	mt[3][1] = 0; mt[3][2] = 0; mt[3][3] = 1; mt[3][4] = 0;
	mt[4][1] = 0; mt[4][2] = 0; mt[4][3] = 0; mt[4][4] = 1;

	
	p[0][1] =   0; p[0][2] =   0; p[0][3] = -100; p[0][4] = 1;
	p[1][1] = -50; p[1][2] =   50; p[1][3] =   0; p[1][4] = 1;
	p[2][1] = -50; p[2][2] = -50; p[2][3] =   0; p[2][4] = 1;
	p[3][1] =   50; p[3][2] = -50; p[3][3] =   0; p[3][4] = 1;
	p[4][1] =   50; p[4][2] =   50; p[4][3] = 0; p[4][4] = 1;
	p[5][1] =  0; p[5][2] =   0; p[5][3] = 100; p[5][4] = 1;
}

void CCurvasDlg::Actualizar_puntos_en_caja_de_dialogo()
{

	//Actualizando coordenadas de la poligonal
	m_P1X = p3d[0][1]; m_P1Y = p3d[0][2]; m_P1Z = p3d[0][3];
	m_P2X = p3d[1][1]; m_P2Y = p3d[1][2]; m_P2Z = p3d[1][3];
	m_P3X = p3d[2][1]; m_P3Y = p3d[2][2]; m_P3Z = p3d[2][3];
	m_P4X = p3d[3][1]; m_P4Y = p3d[3][2]; m_P4Z = p3d[3][3];
	m_P5X = p3d[4][1]; m_P5Y = p3d[4][2]; m_P5Z = p3d[4][3];
	m_P6X = p3d[5][1]; m_P6Y = p3d[5][2]; m_P6Z = p3d[5][3];


	UpdateData(false);

}


//IMPLEMENTACION DE LOS EVENTOS RECIBIDOS DESDE LA CAJA DE DIALOGO

void CCurvasDlg::OnReiniciardibujo() 
{
	// TODO: Add your control notification handler code here

	//Se desactiva todas las curvas
    m_ActivaNewton = m_ActivaLagrange = m_ActivaBezier = false;
	UpdateData(false );

	Inicializar_Puntos();

	Dibujar_Sistema();
}

void CCurvasDlg::OnTrasladarmas() 
{
	// TODO: Add your control notification handler code here
	UpdateData( true );

	switch( m_EjeTraslacion )
	{
	 case 0: Trasladar( 5, 0, 0 );
		     break;
	 case 1: Trasladar( 0, 5, 0 );
		     break;
	 case 2: Trasladar( 0, 0, 5 );
		     break;
	}

	Dibujar_Sistema();

}

void CCurvasDlg::OnTrasladarmenos() 
{
	// TODO: Add your control notification handler code here
	UpdateData( true );

   switch( m_EjeTraslacion )
	{
	 case 0: Trasladar( -5, 0, 0 );
		     break;
	 case 1: Trasladar( 0, -5, 0 );
		     break;
	 case 2: Trasladar( 0, 0, -5 );
		     break;
	}

	Dibujar_Sistema();
	
}


void CCurvasDlg::OnRotarmas() 
{
	// TODO: Add your control notification handler code here
	UpdateData ( true );
	
	Rotar( m_EjeRotacion+1, 5 );

	Dibujar_Sistema();	
}

void CCurvasDlg::OnRotarmenos() 
{
	// TODO: Add your control notification handler code here
	UpdateData( true );
	
	Rotar( m_EjeRotacion+1, -5 );
	
	Dibujar_Sistema();
}



void CCurvasDlg::OnActualizarpoligonal() 
{
	// TODO: Add your control notification handler code here
	UpdateData( true );

    mt[1][1] = 1; mt[1][2] = 0; mt[1][3] = 0; mt[1][4] = 0;
	mt[2][1] = 0; mt[2][2] = 1; mt[2][3] = 0; mt[2][4] = 0;
	mt[3][1] = 0; mt[3][2] = 0; mt[3][3] = 1; mt[3][4] = 0;
	mt[4][1] = 0; mt[4][2] = 0; mt[4][3] = 0; mt[4][4] = 1;

	
	p[0][1] = m_P1X; p[0][2] = m_P1Y; p[0][3] = m_P1Z;
	p[1][1] = m_P2X; p[1][2] = m_P2Y; p[1][3] = m_P2Z;
	p[2][1] = m_P3X; p[2][2] = m_P3Y; p[2][3] = m_P3Z;
	p[3][1] = m_P4X; p[3][2] = m_P4Y; p[3][3] = m_P4Z;
	p[4][1] = m_P5X; p[4][2] = m_P5Y; p[4][3] = m_P5Z;
	p[5][1] = m_P6X; p[5][2] = m_P6Y; p[5][3] = m_P6Z;

	Dibujar_Sistema();
}


void CCurvasDlg::OnCurvanewton() 
{
	// TODO: Add your control notification handler code here
	Dibujar_Sistema();
}

void CCurvasDlg::OnCurvalagrange() 
{
	// TODO: Add your control notification handler code here
	Dibujar_Sistema();
}

void CCurvasDlg::OnCurvabezier() 
{
	// TODO: Add your control notification handler code here
	Dibujar_Sistema();
}
