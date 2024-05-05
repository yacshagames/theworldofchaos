// Ejes3DDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Ejes3D.h"
#include "Ejes3DDlg.h"

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
// CEjes3DDlg dialog

CEjes3DDlg::CEjes3DDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEjes3DDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEjes3DDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEjes3DDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEjes3DDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEjes3DDlg, CDialog)
	//{{AFX_MSG_MAP(CEjes3DDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_EJES2D, OnEjes2d)
	ON_BN_CLICKED(IDC_EJES3D, OnEjes3d)
	ON_BN_CLICKED(IDC_LIMPIAR, OnLimpiar)
	ON_BN_CLICKED(IDC_PUNTOREAL2D, OnPuntoreal2d)
	ON_BN_CLICKED(IDC_PUNTOREAL3D, OnPuntoreal3d)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEjes3DDlg message handlers

BOOL CEjes3DDlg::OnInitDialog()
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
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CEjes3DDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CEjes3DDlg::OnPaint() 
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
HCURSOR CEjes3DDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CEjes3DDlg::OnEjes2d() 
{
	// TODO: Add your control notification handler code here

  RedrawWindow();
	
  CRect rect;
  GetClientRect( rect );

  int Ox = (rect.right-rect.left)/2;
  int Oy = (rect.bottom-rect.top)/2;
	
  int P1x = Ox+100;
  int P1y = rect.bottom-Oy;

  int P2x = Ox;
  int P2y = rect.bottom-(Oy+100);

  
  CClientDC dibujo(this);
    
  CPen NewPen(PS_SOLID, 2, RGB(0,0,200) );   
	dibujo.SelectObject(&NewPen);
	
   dibujo.MoveTo(P1x,P1y);  
   dibujo.LineTo(Ox,Oy);
   dibujo.LineTo(P2x,P2y);
    
}

void CEjes3DDlg::OnEjes3d() 
{
	// TODO: Add your control notification handler code here

    RedrawWindow();
		
	double ix,iy,jx,jy,kx,ky;

	double grados = 3.1415926/180; //factor de conversión de grados a radianes
	//coordenadas de los vectores unitarios i,j,k
	//en el plano 2D de la pantalla
	//se considera que 1 unidad = 1 pixel
	ix=-cos(15*grados); //ix=-cos(15)
	iy=sin(15*grados);  //iy=sin(15)
	jx=cos(30*grados);  //jx=cos(30)
	jy=sin(30*grados);  //jy=sin(30)
	kx=0;        // kx=0;
	ky=-1;		 //zy=-1

  CRect rect;
  GetClientRect( rect );

  int Ox = (rect.right-rect.left)/2;
  int Oy = (rect.bottom-rect.top)/2;
	
  int P1x = Ox+100*ix;
  int P1y = Oy+100*iy;

  int P2x = Ox+100*jx;
  int P2y = Oy+100*jy;

  int P3x = Ox+100*kx;
  int P3y = Oy+100*ky;


  CClientDC dibujo(this);
  
  
  CPen NewPen(PS_SOLID, 2, RGB(0,0,0) );   
	dibujo.SelectObject(&NewPen);

   dibujo.MoveTo(Ox,Oy);
   dibujo.LineTo(P1x,P1y);
   dibujo.MoveTo(Ox,Oy);
   dibujo.LineTo(P2x,P2y);
   dibujo.MoveTo(Ox,Oy);
   dibujo.LineTo(P3x,P3y);
}

void CEjes3DDlg::OnLimpiar() 
{
	// TODO: Add your control notification handler code here
	Invalidate();
}

void CEjes3DDlg::OnPuntoreal2d() 
{
	// TODO: Add your control notification handler code here
  CRect rect;
  GetClientRect( rect );
	
  int Ox = (rect.right-rect.left)/2;
  int Oy = (rect.bottom-rect.top)/2;

  CString msg;
  
  msg.Format("Centro con coordenandas reales de la pantalla es:\n(X = %i, Y= %i)", Ox, Oy);

  MessageBox(msg);
}

void CEjes3DDlg::OnPuntoreal3d() 
{
	// TODO: Add your control notification handler code here
  CRect rect;
  GetClientRect( rect );
	
  int Ox = (rect.right-rect.left)/2;
  int Oy = (rect.bottom-rect.top)/2;

  CString msg;
  
  msg.Format("Centro con coordenandas reales de la pantalla es:\n(X = %i, Y= %i)", Ox, Oy);

  MessageBox(msg);
}
