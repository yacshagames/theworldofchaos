// CuadradoTrasDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CuadradoTras.h"
#include "CuadradoTrasDlg.h"

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
// CCuadradoTrasDlg dialog

CCuadradoTrasDlg::CCuadradoTrasDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCuadradoTrasDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCuadradoTrasDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCuadradoTrasDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCuadradoTrasDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCuadradoTrasDlg, CDialog)
	//{{AFX_MSG_MAP(CCuadradoTrasDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_XPOSITIVO, OnXpositivo)
	ON_BN_CLICKED(IDC_YPOSITIVO, OnYpositivo)
	ON_BN_CLICKED(IDC_ZPOSITIVO, OnZpositivo)
	ON_BN_CLICKED(IDC_XNEGATIVO, OnXnegativo)
	ON_BN_CLICKED(IDC_YNEGATIVO, OnYnegativo)
	ON_BN_CLICKED(IDC_ZNEGATIVO, OnZnegativo)
	ON_BN_CLICKED(IDC_REINICIAR, OnReiniciar)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCuadradoTrasDlg message handlers

BOOL CCuadradoTrasDlg::OnInitDialog()
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
	ox=250; //coordenada x
	oy=200; //coordenada y
	
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

void CCuadradoTrasDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCuadradoTrasDlg::OnPaint() 
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
   //Dibuja el cuadrado en cualquier posición 
   Dibujar();
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCuadradoTrasDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CCuadradoTrasDlg::InicializarPuntos()
{
    double Punto1[4][3] = { 10, 10, 0,
							110,10,0,
							110,110,0,
							10,110,0};
	int i,j;
	for( i=0;i<4;i++)
		for(j=0;j<3;j++)
			Punto[i][j]=Punto1[i][j];
}


void CCuadradoTrasDlg::Dibujar()
{
  CClientDC dibujo(this);

  //se selecciona el color y el grosor de la pluma
  CPen NewPen(PS_SOLID, 2, RGB(32,32,255) );     
  dibujo.SelectObject(&NewPen);

  int i,j;

  for(j=1,i=0;i<4;i++,j++)
   {
   	if( j==4 ) j=0;

    dibujo.MoveTo(ox+Punto[i][0]*ix+Punto[i][1]*jx,
	              oy+Punto[i][0]*iy+Punto[i][1]*jy+Punto[i][2]*zy);  
   
    dibujo.LineTo(ox+Punto[j][0]*ix+Punto[j][1]*jx,
	              oy+Punto[j][0]*iy+Punto[j][1]*jy+Punto[j][2]*zy);
   }
 
}

void CCuadradoTrasDlg::DibujarEjes()
{

  CClientDC dibujo(this);
  
  
  CPen NewPen(PS_SOLID, 2, RGB(0,200,0) );   
	dibujo.SelectObject(&NewPen);
	
  CPoint O,X,Y,Z;
  //longitud de los ejes = 110 unidades
  O=CPoint(ox,oy);
  X=CPoint(110*ix,110*iy);
  Y=CPoint(110*jx,110*jy);
  Z=CPoint(0,110*zy);

   dibujo.MoveTo(O);  
   dibujo.LineTo(O+X);
   dibujo.MoveTo(O);
   dibujo.LineTo(O+Y);
   dibujo.MoveTo(O);
   dibujo.LineTo(O+Z);

}

//traslada el cuadrado paralelo al eje x
void CCuadradoTrasDlg::TrasladarX( int desplazamiento )
{
 	for(int i=0;i<4;i++)
	 Punto[i][0]+=desplazamiento;
}

//traslada el cuadrado paralelo al eje y
void CCuadradoTrasDlg::TrasladarY( int desplazamiento )
{
  for(int i=0;i<4;i++)
	 Punto[i][1]+=desplazamiento;
}

//traslada el cuadrado paralelo al eje z
void CCuadradoTrasDlg::TrasladarZ( int desplazamiento )
{
  for(int i=0;i<4;i++)
	 Punto[i][2]+=desplazamiento;
}


void CCuadradoTrasDlg::OnXpositivo() 
{
	// TODO: Add your control notification handler code here
	TrasladarX(5);
	Invalidate();
}

void CCuadradoTrasDlg::OnYpositivo() 
{
	// TODO: Add your control notification handler code here
	TrasladarY(5);
	Invalidate();
}

void CCuadradoTrasDlg::OnZpositivo() 
{
	// TODO: Add your control notification handler code here
	TrasladarZ(5);
	Invalidate();
}

void CCuadradoTrasDlg::OnXnegativo() 
{
	// TODO: Add your control notification handler code here
	TrasladarX(-5);
	Invalidate();
}

void CCuadradoTrasDlg::OnYnegativo() 
{
	// TODO: Add your control notification handler code here
	TrasladarY(-5);
	Invalidate();
}

void CCuadradoTrasDlg::OnZnegativo() 
{
	// TODO: Add your control notification handler code here
	TrasladarZ(-5);
	Invalidate();
}

void CCuadradoTrasDlg::OnReiniciar() 
{
	// TODO: Add your control notification handler code here
   InicializarPuntos();
   Invalidate();
}
