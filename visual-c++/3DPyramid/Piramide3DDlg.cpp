// Piramide3DDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Piramide3D.h"
#include "Piramide3DDlg.h"
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
// CPiramide3DDlg dialog

CPiramide3DDlg::CPiramide3DDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPiramide3DDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPiramide3DDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPiramide3DDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPiramide3DDlg)
	DDX_Control(pDX, IDC_FONDO, m_Fondo);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPiramide3DDlg, CDialog)
	//{{AFX_MSG_MAP(CPiramide3DDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ROTAR90, OnRotar90)
	ON_BN_CLICKED(IDC_REINICIAR, OnReiniciar)
	ON_BN_CLICKED(IDC_TRASX, OnTrasx)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPiramide3DDlg message handlers

BOOL CPiramide3DDlg::OnInitDialog()
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
	
	//coordenadas del origen de coordenadas
	//en el plano 2D de la pantalla
	CRect rect;
	m_Fondo.GetClientRect(&rect);

	ox = (rect.right-rect.left)/2; //coordenada x
    oy = (rect.bottom-rect.top)/2; //coordenada y

	//coordenadas de los vectores unitarios i,j,k
	//en el plano 2D de la pantalla
	//se considera que 1 unidad = 1 pixel
	ix=-0.9659258; //ix=-cos(15)
	iy=0.2588190;  //iy=sin(15)
	jx=0.8660254;  //jx=cos(30)
	jy=0.5;		  //jy=sin(30)
	//zx=0;       //no es nesesario declararlo
	ky=-1;		  //zy=-1

	InicializarPuntos();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPiramide3DDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CPiramide3DDlg::OnPaint() 
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

	DibujarTodo();
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPiramide3DDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void CPiramide3DDlg::InicializarPuntos()
{
	double Punto1[5][3] = { 100,  20, 0,
							100, 100, 0,
							 20, 100, 0,
							 20,  20, 0,
							 60,  60, 100 };
	int i,j;
	for( i=0;i<5;i++)
		for(j=0;j<3;j++)
			Punto[i][j]=Punto1[i][j];
}


void CPiramide3DDlg::DibujarEjes()
{

  CDC *dibujo = m_Fondo.GetDC();
  
  
  CPen NewPen(PS_SOLID, 2, RGB(0,255,0) );   
	dibujo->SelectObject(&NewPen);
	
  CPoint O,X,Y,Z;
  //longitud de los ejes = 110 unidades
  O=CPoint(ox,oy);
  X=CPoint(110*ix,110*iy);
  Y=CPoint(110*jx,110*jy);
  Z=CPoint(0,110*ky);

   dibujo->MoveTo(O);  
   dibujo->LineTo(O+X);
   dibujo->MoveTo(O);
   dibujo->LineTo(O+Y);
   dibujo->MoveTo(O);
   dibujo->LineTo(O+Z);

}

void CPiramide3DDlg::Dibujar()
{
  CDC *dibujo = m_Fondo.GetDC();

  //se selecciona el color y el grosor de la pluma
  CPen NewPen(PS_SOLID, 2, RGB(255,255,255) );     
  dibujo->SelectObject(&NewPen);

  int i,j;

  //dibuja la Base
  for(j=1,i=0;i<4;i++,j++)
   {
   	if( j==4 ) j=0;

    dibujo->MoveTo(ox+Punto[i][0]*ix+Punto[i][1]*jx,
	              oy+Punto[i][0]*iy+Punto[i][1]*jy+Punto[i][2]*ky);  
   
    dibujo->LineTo(ox+Punto[j][0]*ix+Punto[j][1]*jx,
	              oy+Punto[j][0]*iy+Punto[j][1]*jy+Punto[j][2]*ky);
   }

  //Une la base con la punta
  for(i=0;i<4;i++)
  {
	  dibujo->MoveTo(ox+Punto[4][0]*ix+Punto[4][1]*jx,
	              oy+Punto[4][0]*iy+Punto[4][1]*jy+Punto[4][2]*ky);  

	  dibujo->LineTo(ox+Punto[i][0]*ix+Punto[i][1]*jx,
	              oy+Punto[i][0]*iy+Punto[i][1]*jy+Punto[i][2]*ky);  

  }
 
}

void CPiramide3DDlg::DibujarTodo()
{
  
   m_Fondo.RedrawWindow();
   //dibuja los ejes x y z
   DibujarEjes();
   //Dibuja el cuadrado en cualquier posici�n 
   Dibujar();
 
}

//rota el cuadrado alrededor del eje x
void CPiramide3DDlg::RotarX(double angulo)
{

	double Y,Z;

	for(int i=0;i<5;i++)
	{
	 Y=Punto[i][1];
	 Z=Punto[i][2];	

	 Punto[i][1]= Y*cos(angulo)+Z*sin(angulo);
	 Punto[i][2]= -Y*sin(angulo)+Z*cos(angulo);
	}
}

void CPiramide3DDlg::OnRotar90() 
{
	// TODO: Add your control notification handler code here
	RotarX( 3.141592/2 ); //rota 90 grados
	DibujarTodo();
}

void CPiramide3DDlg::OnReiniciar() 
{
	// TODO: Add your control notification handler code here
	InicializarPuntos();
	RedrawWindow();
}


void CPiramide3DDlg::OnTrasx() 
{
	// TODO: Add your control notification handler code here
	
	for(int i=0;i<5;i++)
	{
	 Punto[i][0]+=60;
	 Punto[i][1]+=60;
	 Punto[i][2]+=50;
	}

	DibujarTodo();
}