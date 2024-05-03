// SuperficieLagrangeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SuperficieLagrange.h"
#include "SuperficieLagrangeDlg.h"

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
// CSuperficieLagrangeDlg dialog

CSuperficieLagrangeDlg::CSuperficieLagrangeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSuperficieLagrangeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSuperficieLagrangeDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSuperficieLagrangeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSuperficieLagrangeDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSuperficieLagrangeDlg, CDialog)
	//{{AFX_MSG_MAP(CSuperficieLagrangeDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_GRAFICAR, OnGraficar)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSuperficieLagrangeDlg message handlers

BOOL CSuperficieLagrangeDlg::OnInitDialog()
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

	ox=250; //coordenada x
	oy=250; //coordenada y
	
	//coordenadas de los vectores unitarios i,j,k
	//en el plano 2D de la pantalla
	//se considera que 1 unidad = 1 pixel
	ix=-0.9659258; //ix=-cos(15)
	iy=0.2588190;  //iy=sin(15)
	jx=0.8660254;  //jx=cos(30)
	jy=0.5;		  //jy=sin(30)
	//zx=0;       //no es nesesario declararlo
	zy=-1;		  //zy=-1
	Xn=10;
	Yn=10;

	t[0] =0;	t[1] =2;    t[2] =6;  
	graficalista=0;
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSuperficieLagrangeDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSuperficieLagrangeDlg::OnPaint() 
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

	DibujarEjes();
	
	if( graficalista )
	 OnGraficar();


}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSuperficieLagrangeDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void CSuperficieLagrangeDlg::DibujarEjes()
{

  CClientDC dibujo(this);
  
  
  CPen NewPen(PS_SOLID, 2, RGB(0,200,0) );   
	dibujo.SelectObject(&NewPen);
	
  CPoint O,X,Y,Z;
  //longitud de los ejes = 110 unidades
  O=CPoint(ox,oy);
  X=CPoint((int)(110*ix),(int)(110*iy));
  Y=CPoint((int)(110*jx),(int)(110*jy));
  Z=CPoint(0,(int)(110*zy));

   dibujo.MoveTo(O);  
   dibujo.LineTo(O+X);
   dibujo.MoveTo(O);
   dibujo.LineTo(O+Y);
   dibujo.MoveTo(O);
   dibujo.LineTo(O+Z);

}

void CSuperficieLagrangeDlg::ConstruirSuperficie(double p[3][3],int eje)
{
	
CClientDC dibujo(this);

 int i,j,k;
 double tt,x,y,z;

 for (j=0;j<Yn;j++)
{

  for (i=0;i<Xn;i++)
  {
	tt=t[0]+((t[2]-t[0])*i)/Xn; 
	
	x=y=z=0;

   for (k=0;k<3;k++)
   {
    x+=p[k][0]*Lagrange(tt,k,2);
    y+=p[k][1]*Lagrange(tt,k,2);
    z+=p[k][2]*Lagrange(tt,k,2);

   }
   
   if(i==0)
   dibujo.MoveTo(int(ox+x*ix+y*jx),int(oy+x*iy+y*jy+z*zy));  
   else
   dibujo.LineTo(int(ox+x*ix+y*jx),int(oy+x*iy+y*jy+z*zy));  
  }

  //se traslada la curva para obtener otra linea de la Superficie en malla
  for (k=0;k<3;k++)
    p[k][eje]-=20;  
   
 }

}


double CSuperficieLagrangeDlg::Lagrange(double tt,int k,int n)
{double aux;
  aux=Produc(tt,k,n);
  return aux;
}

double CSuperficieLagrangeDlg::Produc(double tt,int k,int n)
{double aux;
 int j;
 	aux=1;
 for (j=0;j<=n;j++)
 {
   if (k!=j)
      aux=aux*((tt-t[j])/(t[k]-t[j]));
 }
return aux;
}


void CSuperficieLagrangeDlg::OnGraficar() 
{
	// TODO: Add your control notification handler code here
	graficalista=1;
	InicializarPuntos();
	ConstruirSuperficie(p,0);
	ConstruirSuperficie(p1,1);	
}

void CSuperficieLagrangeDlg::InicializarPuntos()
{

	p[0][0] =100 ;	p[0][1] =-110;    p[0][2] =0;  
	p[1][0] = 90;	p[1][1] =0;    p[1][2] =120;  
	p[2][0] = 120;	p[2][1] =100;    p[2][2] =0; 

	p1[0][0] =120 ;	p1[0][1] =100;    p1[0][2] =0;  
	p1[1][0] = 0;	p1[1][1] =90;    p1[1][2] =120;  
	p1[2][0] = -110;	p1[2][1] =120;    p1[2][2] =0; 
}

