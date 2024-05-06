/******************************************************************************
:: 3D SQUARE :: CUADRADO 3D ::

A 3D square is plotted that supports translation, rotation, projection in
the XY, XZ, YZ planes, and reflection with respect to the origin O

Spanish:
Se plotea un cuadrado 3D que soporta traslaci�n, rotaci�n, proyecci�n en los
planos XY, XZ, YZ, y reflexi�n con respecto al origen O

Developed by:

	JOSE LUIS DE LA CRUZ LAZARO
	ramondc@hotmail.com

	UNIVERSIDAD NACIONAL DE INGENIERIA
	Faculty of Electrical and Electronic Engineering
	Lima-Peru

	YACSHA - Software & Desing
	>> The World of chaos - EL MUNDO DEL CAOS - Unlimited Programming

HISTORY...

  >> Version 2 - 05-V-2024
	* Thanks to the collaboration of a follower of "the world of chaos",
	  we obtained the first version. From which we have made the
	  following changes:
	- Porting to VC++ 2017.
	- Add credits and version history
	- Translate GUI from spanish to english
	- Warnings due to lack of static_cast are corrected

  >> Version 1 - 14-IV-2000
	- First version developed by Yacsha for VC++ 6.0

Warning!!!: These formulas may contain some errors, if you find them, let me
know from the contact page of "The world of chaos", or suggest a
modification in the project's github repository
https://github.com/yacshagames/elmundodelcaos

******************************************************************************/
#include "stdafx.h"
#include "Cuadrado3D.h"
#include "Cuadrado3DDlg.h"
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
// CCuadrado3DDlg dialog

CCuadrado3DDlg::CCuadrado3DDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCuadrado3DDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCuadrado3DDlg)
	m_Sentido = FALSE;
	m_Direccion = FALSE;
	m_Pivote = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCuadrado3DDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCuadrado3DDlg)
	DDX_Check(pDX, IDC_SENTIDO, m_Sentido);
	DDX_Check(pDX, IDC_DIRECCION, m_Direccion);
	DDX_Radio(pDX, IDC_PIVOTE, m_Pivote);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCuadrado3DDlg, CDialog)
	//{{AFX_MSG_MAP(CCuadrado3DDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ROTARX, OnRotarx)
	ON_BN_CLICKED(IDC_ROTARY, OnRotary)
	ON_BN_CLICKED(IDC_ROTARZ, OnRotarz)
	ON_BN_CLICKED(IDC_TRASLADARX, OnTrasladarx)
	ON_BN_CLICKED(IDC_TRASLADARY, OnTrasladary)
	ON_BN_CLICKED(IDC_TRASLADARZ, OnTrasladarz)
	ON_BN_CLICKED(IDC_REFLEJARXY, OnReflejarxy)
	ON_BN_CLICKED(IDC_REFLEJARXZ, OnReflejarxz)
	ON_BN_CLICKED(IDC_REFLEJARYZ, OnReflejaryz)
	ON_BN_CLICKED(IDC_REINICIAR, OnReiniciar)
	ON_BN_CLICKED(IDC_LIMPIARREFLEXION, OnLimpiarreflexion)
	ON_BN_CLICKED(IDC_REFLEJARORIGEN, OnReflejarOrigen)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCuadrado3DDlg message handlers

BOOL CCuadrado3DDlg::OnInitDialog()
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
	SetIcon(m_hIcon, TRUE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	//coordenadas del origen de coordenadas
	//en el plano 2D de la pantalla
	ox=300; //coordenada x
	oy=300; //coordenada y
	
	//coordenadas de los vectores unitarios i,j,k
	//en el plano 2D de la pantalla
	//se considera que 1 unidad = 1 pixel
	ix=-0.9659258; //ix=-cos(15)
	iy=0.2588190;  //iy=sin(15)
	jx=0.8660254;  //jx=cos(30)
	jy=0.5;		  //jy=sin(30)
	//zx=0;       //no es nesesario declararlo
	zy=-1;		  //zy=-1

	InicializarPuntos();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCuadrado3DDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCuadrado3DDlg::OnPaint() 
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

   //dibuja los ejes x y z
   DibujarEjes();
   //Dibuja el cuadrado en cualquier posici�n 
   Dibujar();

}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCuadrado3DDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CCuadrado3DDlg::Dibujar()
{
  CClientDC dibujo(this);

  //se selecciona el color y el grosor de la pluma
  CPen NewPen(PS_SOLID, 2, RGB(32,32,255) );     
  dibujo.SelectObject(&NewPen);

  int i,j;

  for(j=1,i=0;i<4;i++,j++)
   {
   	if( j==4 ) j=0;

	dibujo.MoveTo(	static_cast<int>(ox + Punto[i][0] * ix + Punto[i][1] * jx),
					static_cast<int>(oy + Punto[i][0] * iy + Punto[i][1] * jy + Punto[i][2] * zy));

	dibujo.LineTo(	static_cast<int>(ox + Punto[j][0] * ix + Punto[j][1] * jx),
					static_cast<int>(oy + Punto[j][0] * iy + Punto[j][1] * jy + Punto[j][2] * zy));
   }
 
}

void CCuadrado3DDlg::DibujarEjes()
{

  CClientDC dibujo(this);
  
  
  CPen NewPen(PS_SOLID, 2, RGB(0,200,0) );   
	dibujo.SelectObject(&NewPen);
	
  CPoint O,X,Y,Z;
  //longitud de los ejes = 110 unidades
  O = CPoint(static_cast<int>(ox), static_cast<int>(oy));
  X = CPoint(static_cast<int>(110.0*ix), static_cast<int>(110.0*iy));
  Y = CPoint(static_cast<int>(110.0*jx), static_cast<int>(110.0*jy));
  Z = CPoint(0, static_cast<int>(110.0*zy));

   dibujo.MoveTo(O);  
   dibujo.LineTo(O+X);
   dibujo.MoveTo(O);
   dibujo.LineTo(O+Y);
   dibujo.MoveTo(O);
   dibujo.LineTo(O+Z);

}

//rota el cuadrado alrededor del eje x
void CCuadrado3DDlg::RotarX(double angulo)
{

	double Y,Z;

	for(int i=0;i<4;i++)
	{
	 Y=Punto[i][1]-Pivote[1];
	 Z=Punto[i][2]-Pivote[2];	

	 Punto[i][1]= Pivote[1]+Y*cos(angulo)+Z*sin(angulo);
	 Punto[i][2]= Pivote[2]-Y*sin(angulo)+Z*cos(angulo);
	}
}

//rota el cuadrado alrededor del eje y
void CCuadrado3DDlg::RotarY(double angulo)
{
   double X,Z;

	for(int i=0;i<4;i++)
	{
	 X=Punto[i][0]-Pivote[0];
	 Z=Punto[i][2]-Pivote[2];	

	 Punto[i][0]= Pivote[0]+X*cos(angulo)-Z*sin(angulo);
	 Punto[i][2]= Pivote[2]+X*sin(angulo)+Z*cos(angulo);
	}
}

//rota el cuadrado alrededor del eje z
void CCuadrado3DDlg::RotarZ(double angulo)
{
   double X,Y;

	for(int i=0;i<4;i++)
	{
	 X=Punto[i][0]-Pivote[0];
	 Y=Punto[i][1]-Pivote[1];	

	 Punto[i][0]= Pivote[0]+X*cos(angulo)+Y*sin(angulo);
	 Punto[i][1]= Pivote[1]-X*sin(angulo)+Y*cos(angulo);
	}
}

//traslada el cuadrado paralelo al eje x
void CCuadrado3DDlg::TrasladarX( int desplazamiento )
{
 	for(int i=0;i<5;i++)
	 Punto[i][0]+=desplazamiento;
}

//traslada el cuadrado paralelo al eje y
void CCuadrado3DDlg::TrasladarY( int desplazamiento )
{
  for(int i=0;i<5;i++)
	 Punto[i][1]+=desplazamiento;
}

//traslada el cuadrado paralelo al eje z
void CCuadrado3DDlg::TrasladarZ( int desplazamiento )
{
  for(int i=0;i<5;i++)
	 Punto[i][2]+=desplazamiento;
}


void CCuadrado3DDlg::OnRotarx() 
{
	// TODO: Add your control notification handler code here
	
	//El angulo de rotaci�n ser� 5� = 0.087266 radianes	
    UpdateData(true);
	int s;
    if( m_Sentido ) s=1; else s=-1;

	if( m_Pivote )
	{
		Pivote[0]=0; Pivote[1]=0; Pivote[2]=0; //Pivote es el origen
	}
	else
	{
		Pivote[0]=Punto[4][0]; Pivote[1]=Punto[4][1]; Pivote[2]=Punto[4][2]; //Pivote es el centro
	}

	RotarX(0.087266*s);
	Invalidate();
}



void CCuadrado3DDlg::OnRotary() 
{
	// TODO: Add your control notification handler code here
	
	//El angulo de rotaci�n ser� 5� = 0.087266 radianes	
	UpdateData(true);
	int s;
    if( m_Sentido ) s=1; else s=-1;
	
	if( m_Pivote )
	{
		Pivote[0]=0; Pivote[1]=0; Pivote[2]=0; //Pivote es el origen
	}
	else
	{
		Pivote[0]=Punto[4][0]; Pivote[1]=Punto[4][1]; Pivote[2]=Punto[4][2]; //Pivote es el centro
	}

	RotarY(0.087266*s);
	Invalidate();	
}


void CCuadrado3DDlg::OnRotarz() 
{
	// TODO: Add your control notification handler code here
	
	//El angulo de rotaci�n ser� 5� = 0.087266 radianes	
	UpdateData(true);
	int s;
    if( m_Sentido ) s=1; else s=-1;
	
	if( m_Pivote )
	{
		Pivote[0]=0; Pivote[1]=0; Pivote[2]=0; //Pivote es el origen
	}
	else
	{
		Pivote[0]=Punto[4][0]; Pivote[1]=Punto[4][1]; Pivote[2]=Punto[4][2]; //Pivote es el centro
	}

	RotarZ(0.087266*s);
	Invalidate();	
}

void CCuadrado3DDlg::OnTrasladarx() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	int d;
    //se trasladara 5 unidades segun la direcci�n indicada
	if( m_Direccion ) d=-5; else d=5;

	TrasladarX(d);
	Invalidate();
}



void CCuadrado3DDlg::OnTrasladary() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	int d;
    //se trasladara 5 unidades segun la direcci�n indicada
	if( m_Direccion ) d=-5; else d=5;

	TrasladarY(d);
	Invalidate();
}

void CCuadrado3DDlg::OnTrasladarz() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	int d;
    //se trasladara 5 unidades segun la direcci�n indicada
	if( m_Direccion ) d=-5; else d=5;
	
	TrasladarZ(d);
	Invalidate();
}

//Refleja el cuadrado al plano XY
void CCuadrado3DDlg::ReflejarXY()
{
  
  for(int i=0;i<4;i++)
  {
   PuntoReflejado[i][0]=Punto[i][0];
   PuntoReflejado[i][1]=Punto[i][1];
   PuntoReflejado[i][2]=-Punto[i][2];
  }
  
}

//Refleja el cuadrado al plano XZ
void CCuadrado3DDlg::ReflejarXZ()
{

  for(int i=0;i<4;i++)
  {
   PuntoReflejado[i][0]=Punto[i][0];
   PuntoReflejado[i][1]=-Punto[i][1];
   PuntoReflejado[i][2]=Punto[i][2];
  }
}

//Refleja el cuadrado al plano YZ
void CCuadrado3DDlg::ReflejarYZ()
{

  for(int i=0;i<4;i++)
  {
   PuntoReflejado[i][0]=-Punto[i][0];
   PuntoReflejado[i][1]=Punto[i][1];
   PuntoReflejado[i][2]=Punto[i][2];
  }
}

void CCuadrado3DDlg::DibujarReflejo()
{

   CClientDC dibujo(this);

   CPen NewPen(PS_SOLID, 1, RGB(255,0,0) );   
   dibujo.SelectObject(&NewPen);

  int i,j;

  for(j=1,i=0;i<4;i++,j++)
   {   
	if( j==4 ) j=0;

	dibujo.MoveTo(	static_cast<int>(ox + PuntoReflejado[i][0] * ix + PuntoReflejado[i][1] * jx),
					static_cast<int>(oy + PuntoReflejado[i][0] * iy + PuntoReflejado[i][1] * jy + PuntoReflejado[i][2] * zy));

	dibujo.LineTo(	static_cast<int>(ox + PuntoReflejado[j][0] * ix + PuntoReflejado[j][1] * jx),
					static_cast<int>(oy + PuntoReflejado[j][0] * iy + PuntoReflejado[j][1] * jy + PuntoReflejado[j][2] * zy));
   }
}


void CCuadrado3DDlg::OnReflejarxy() 
{
	// TODO: Add your control notification handler code here
	ReflejarXY();	
 	DibujarReflejo();
}

void CCuadrado3DDlg::OnReflejarxz() 
{
	// TODO: Add your control notification handler code here
	ReflejarXZ();	
 	DibujarReflejo();
}

void CCuadrado3DDlg::OnReflejaryz() 
{
	// TODO: Add your control notification handler code here
	ReflejarYZ();	
 	DibujarReflejo();
}

void CCuadrado3DDlg::OnReiniciar() 
{
	// TODO: Add your control notification handler code here
   InicializarPuntos();
   Invalidate();
	
}

void CCuadrado3DDlg::InicializarPuntos()
{
	double Punto1[5][3] = { -50, -50, 0,
							 50, -50, 0,
							 50,  50, 0,
							-50,  50, 0,
							  0,   0, 0 };
	int i,j;
	for( i=0;i<5;i++)
		for(j=0;j<3;j++)
			Punto[i][j]=Punto1[i][j];
}

void CCuadrado3DDlg::OnLimpiarreflexion() 
{
	// TODO: Add your control notification handler code here
	Invalidate();
}

void CCuadrado3DDlg::OnReflejarOrigen() 
{
	// TODO: Add your control notification handler code here
	for(int i=0;i<4;i++)
  {
   PuntoReflejado[i][0]=-Punto[i][0];
   PuntoReflejado[i][1]=-Punto[i][1];
   PuntoReflejado[i][2]=-Punto[i][2];
  }
	
	DibujarReflejo();
}
