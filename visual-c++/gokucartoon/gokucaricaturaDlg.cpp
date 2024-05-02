// gokucaricaturaDlg.cpp : implementation file
//

#include "stdafx.h"
#include "gokucaricatura.h"
#include "gokucaricaturaDlg.h"

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
// CGokucaricaturaDlg dialog

CGokucaricaturaDlg::CGokucaricaturaDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGokucaricaturaDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGokucaricaturaDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGokucaricaturaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGokucaricaturaDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGokucaricaturaDlg, CDialog)
	//{{AFX_MSG_MAP(CGokucaricaturaDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDCANCEL, Salir)
	ON_BN_CLICKED(IDC_BUTTON1, DibujarCurva)
	ON_BN_CLICKED(IDC_BUTTON2, DibujarCurvaBspline)
	ON_BN_CLICKED(IDC_BUTTON3, Dibujar_Bspline2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGokucaricaturaDlg message handlers

BOOL CGokucaricaturaDlg::OnInitDialog()
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



	
    

	n=2;
	densidad = 1000;
	



	m_densidad = densidad;
	UpdateData(FALSE);
	UpdateData(TRUE);


///INICIALIZACIONES CON RESPECTO A B-SPLINE
	
	T[0] = 0;	T[1] = 1;	T[2] = 2;	T[3] = 3;	T[4] = 4;
  	T[5] = 5;	T[6] = 6;	T[7] = 7;	T[8] = 8;	T[9] = 9;
    T[10]=10;	T[11]=11;	T[12]=12;	T[13]=13;	T[14]=14;

	korden = 3;


	

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CGokucaricaturaDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CGokucaricaturaDlg::OnPaint() 
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
HCURSOR CGokucaricaturaDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CGokucaricaturaDlg::Salir() 
{
	// TODO: Add your control notification handler code here
	OnOK();
	
}



void CGokucaricaturaDlg::Dibujar_Bezier()
{   
	
	CClientDC pDC(this);
	
	
	//Convertir P0 a Coordenadas de Monitor
	PtoAux[1] = p3d[0][1];
	PtoAux[2] = p3d[0][2];
	
	PtoAuxM[1] = Cx + PtoAux[1] ;
	PtoAuxM[2] = Cy - PtoAux[2];
    pDC.MoveTo(PtoAuxM[1], PtoAuxM[2]);
	
	/*
	
	//Poligono
	CPen LapizVerde(PS_DOT, 1, RGB(0,0,255));
	pDC.SelectObject(&LapizVerde);
	for (int l=1; l<=n; l++)
	{
		PtoAuxM[1] = Cx + p3d[l][1];
		PtoAuxM[2] = Cy - p3d[l][2];
		pDC.LineTo(PtoAuxM[1], PtoAuxM[2]);
	}
	
	
	//Convertir P0 a Coordenadas de Monitor
	*/
	
	
	PtoAux[1] = p3d[0][1];
	PtoAux[2] = p3d[0][2];
	
	PtoAuxM[1] = Cx + PtoAux[1];
	PtoAuxM[2] = Cy - PtoAux[2];
    pDC.MoveTo(PtoAuxM[1], PtoAuxM[2]);
	//Curva
	
	
	CPen LapizNegro(PS_SOLID, 1, RGB(0,0,0));
	pDC.SelectObject(&LapizNegro);
	UpdateData(TRUE);
	densidad = m_densidad;
	for (int k=1; k<=densidad; k++)
	{
		PtoAux[1] = 0;
		PtoAux[2] = 0;
		
		double ka = k;					//Para divisiones es necesario que alguno
		double densidada = densidad;    //de los parámetros sea un numero real.
		tt = (ka)/(densidada);
		
		for (int i=0; i<=n; i++)
		{
		//	double BAR;
		//	BAR = B(i,tt);
			PtoAux[1] = (PtoAux[1] + (p3d[i][1] * B(i,tt)));
			PtoAux[2] = (PtoAux[2] + (p3d[i][2] * B(i,tt)));
		

			
		}

		PtoAuxM[1] = Cx + PtoAux[1];
		PtoAuxM[2] = Cy - PtoAux[2];
		pDC.LineTo(PtoAuxM[1], PtoAuxM[2]);
	}
	
}

double CGokucaricaturaDlg::rad(double angulo)
{
	return angulo*pi/180;
}

double CGokucaricaturaDlg::f(int valor)
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

double CGokucaricaturaDlg::B(int k, double tt)
{
	double Bo;

	Bo = (f(n) / (f(n-k) * f(k))) * pow(1-tt, n-k) * pow(tt, k);

	return Bo;
}












void CGokucaricaturaDlg::DibujarCurva() 
{
	// TODO: Add your control notification handler code here
	

		Cx=0;
		Cy=300; 	
	
		MatxPto1();
	

	
}



void CGokucaricaturaDlg::MatxPto1()
{




	p1[0][1] =  10; p1[0][2] =    45;
	p1[1][1] =  110; p1[1][2] =    70;
	p1[2][1] =  112; p1[2][2] =    122;
	

	for (int k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p1[k][1];
			p3d[k][2] = p1[k][2];
		
			
	}

	Dibujar_Bezier();


	p2[0][1] =  112; p2[0][2] =    122;
	p2[1][1] =  160; p2[1][2] =    20;
	p2[2][1] =  216; p2[2][2] =    122;
	

	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p2[k][1];
			p3d[k][2] = p2[k][2];
		
			
	}

	Dibujar_Bezier();


	
	
	p3[0][1] =  216; p3[0][2] =    122; 
	p3[1][1] =  231; p3[1][2] =    72; 
	p3[2][1] =  300; p3[2][2] =    55; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p3[k][1];
			p3d[k][2] = p3[k][2];
		
			
	}

	Dibujar_Bezier();





	p4[0][1] =  112; p4[0][2] =   122; 
	p4[1][1] =  89; p4[1][2] =   139; 
	p4[2][1] =  88; p4[2][2] =   151; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p4[k][1];
			p3d[k][2] = p4[k][2];
		
			
	}

	Dibujar_Bezier();




	p5[0][1] =  216; p5[0][2] =   122; 
	p5[1][1] =  217; p5[1][2] =   126; 
	p5[2][1] =  220; p5[2][2] =   130; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p5[k][1];
			p3d[k][2] = p5[k][2];
		
			
	}

	Dibujar_Bezier();



	p6[0][1] =  220; p6[0][2] =   130; 
	p6[1][1] =  235; p6[1][2] =   135; 
	p6[2][1] =  239; p6[2][2] =   142; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p6[k][1];
			p3d[k][2] = p6[k][2];
		
			
	}

	Dibujar_Bezier();




	p7[0][1] =  239; p7[0][2] =    142; 
	p7[1][1] =  272; p7[1][2] =    165;
	p7[2][1] =  288; p7[2][2] =    208;
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p7[k][1];
			p3d[k][2] = p7[k][2];
		
			
	}

	Dibujar_Bezier();

	
	

	
	p8[0][1] =  288; p8[0][2] =   208; 
	p8[1][1] =  271; p8[1][2] =   200; 
	p8[2][1] =  260; p8[2][2] =   185; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p8[k][1];
			p3d[k][2] = p8[k][2];
		
			
	}

	Dibujar_Bezier();





	p9[0][1] =  260; p9[0][2] =   185; 
	p9[1][1] =  255; p9[1][2] =   160; 
	p9[2][1] =  249; p9[2][2] =   158; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p9[k][1];
			p3d[k][2] = p9[k][2];
		
			
	}

	Dibujar_Bezier();



	p10[0][1] =  260; p10[0][2] =    185;
	p10[1][1] =  262; p10[1][2] =    203; 
	p10[2][1] =  258; p10[2][2] =    208; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p10[k][1];
			p3d[k][2] = p10[k][2];
		
			
	}

	Dibujar_Bezier();



	p11[0][1] =  249; p11[0][2] =    158; 
	p11[1][1] =   245; p11[1][2] =    160; 
	p11[2][1] =  245; p11[2][2] =    165; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p11[k][1];
			p3d[k][2] = p11[k][2];
		
			
	}

	Dibujar_Bezier();



    p12[0][1] =   245; p12[0][2] =   165; 
	p12[1][1] =   255; p12[1][2] =   180 ;
	p12[2][1] =   252; p12[2][2] =   198; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p12[k][1];
			p3d[k][2] = p12[k][2];
		
			
	}

	Dibujar_Bezier();


  
	p13[0][1] =   245; p13[0][2] =   165; 
	p13[1][1] =   243; p13[1][2] =   155; 
	p13[2][1] =   232; p13[2][2] =   150; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p13[k][1];
			p3d[k][2] = p13[k][2];
		
			
	}

	Dibujar_Bezier();





    p14[0][1] =   232; p14[0][2] =   150; 
	p14[1][1] =   228; p14[1][2] =   175; 
	p14[2][1] =   210; p14[2][2] =   190; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p14[k][1];
			p3d[k][2] = p14[k][2];
		
			
	}

	Dibujar_Bezier();






    p15[0][1] =  212; p15[0][2] =   218; 
	p15[1][1] =  221 ; p15[1][2] =  191; 
	p15[2][1] =  170; p15[2][2] =   139; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p15[k][1];
			p3d[k][2] = p15[k][2];
		
			
	}

	Dibujar_Bezier();




    p16[0][1] =  170; p16[0][2] =   139; 
	p16[1][1] =  182 ; p16[1][2] =   173;
	p16[2][1] =  171; p16[2][2] =    216; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p16[k][1];
			p3d[k][2] = p16[k][2];
		
			
	}

	Dibujar_Bezier();




    p17[0][1] =  171; p17[0][2] =   216; 
	p17[1][1] =  164; p17[1][2] =    185; 
	p17[2][1] =  138; p17[2][2] =    160; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p17[k][1];
			p3d[k][2] = p17[k][2];
		
			
	}

	Dibujar_Bezier();




    


    p18[0][1] =  155; p18[0][2] =    218; 
	p18[1][1] =  155; p18[1][2] =    174; 
	p18[2][1] =  125; p18[2][2] =    144; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p18[k][1];
			p3d[k][2] = p18[k][2];
		
			
	}

	Dibujar_Bezier();



    
	p19[0][1] =  125; p19[0][2] =   144; 
	p19[1][1] =  93; p19[1][2] =    195; 
	p19[2][1] =  119; p19[2][2] =    228; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p19[k][1];
			p3d[k][2] = p19[k][2];
		
			
	}

	Dibujar_Bezier();







    p20[0][1] =  110; p20[0][2] =   184; 
	p20[1][1] =  95; p20[1][2] =   168; 
	p20[2][1] =  82; p20[2][2] =   141; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p20[k][1];
			p3d[k][2] = p20[k][2];
		
			
	}

	Dibujar_Bezier();



     

  
	p21[0][1] =  82; p21[0][2] =    141; 
	p21[1][1] =  66; p21[1][2] =    172; 
	p21[2][1] =  70; p21[2][2] =    200; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p21[k][1];
			p3d[k][2] = p21[k][2];
		
			
	}

	Dibujar_Bezier();





  

    p22[0][1] =  76; p22[0][2] = 153  ; 
	p22[1][1] =  36; p22[1][2] =   171; 
	p22[2][1] =  31; p22[2][2] =   220; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p22[k][1];
			p3d[k][2] = p22[k][2];
		
			
	}

	Dibujar_Bezier();

  



    p23[0][1] =  44; p23[0][2] =   199; 
	p23[1][1] =  24; p23[1][2] =    226; 
	p23[2][1] =  28; p23[2][2] =    250; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p23[k][1];
			p3d[k][2] = p23[k][2];
		
			
	}

	Dibujar_Bezier();





    p24[0][1] =  34; p24[0][2] =   250; 
	p24[1][1] =  44; p24[1][2] =   224;
	p24[2][1] =  81; p24[2][2] =    215; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p24[k][1];
			p3d[k][2] = p24[k][2];
		
			
	}

	Dibujar_Bezier();





    p25[0][1] =  279; p25[0][2] =   202; 
	p25[1][1] =  294; p25[1][2] = 230   ; 
	p25[2][1] =  290; p25[2][2] =    250; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p25[k][1];
			p3d[k][2] = p25[k][2];
		
			
	}

	Dibujar_Bezier();




    p26[0][1] =  180; p26[0][2] =   97; 
	p26[1][1] =  165; p26[1][2] =   105; 
	p26[2][1] =  145; p26[2][2] =   97; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p26[k][1];
			p3d[k][2] = p26[k][2];
		
			
	}

	Dibujar_Bezier();





  


    p27[0][1] =  180; p27[0][2] =   97; 
	p27[1][1] =  165; p27[1][2] =  86; 
	p27[2][1] =  145; p27[2][2] =   97; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p27[k][1];
			p3d[k][2] = p27[k][2];
		
			
	}

	Dibujar_Bezier();







    p28[0][1] =  156; p28[0][2] =   130; 
	p28[1][1] =  158; p28[1][2] =   120; 
	p28[2][1] =  151; p28[2][2] =    112; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p28[k][1];
			p3d[k][2] = p28[k][2];
		
			
	}

	Dibujar_Bezier();




    p29[0][1] =  169; p29[0][2] =   130; 
	p29[1][1] =  168; p29[1][2] =    120; 
	p29[2][1] =  175; p29[2][2] =   112; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p29[k][1];
			p3d[k][2] = p29[k][2];
		
			
	}

	Dibujar_Bezier();






    p30[0][1] =  175; p30[0][2] =   112; 
	p30[1][1] =  165; p30[1][2] =   108 ; 
	p30[2][1] =  151; p30[2][2] =   112; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p30[k][1];
			p3d[k][2] = p30[k][2];
		
			
	}

	Dibujar_Bezier();








    p31[0][1] =  182; p31[0][2] =   151; 
	p31[1][1] =  200; p31[1][2] =   160 ; 
	p31[2][1] =  220; p31[2][2] =   168 ; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p31[k][1];
			p3d[k][2] = p31[k][2];
		
			
	}

	Dibujar_Bezier();








    p32[0][1] =  220; p32[0][2] =   168; 
	p32[1][1] =  225; p32[1][2] =   169; 
	p32[2][1] =  223; p32[2][2] =   165; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p32[k][1];
			p3d[k][2] = p32[k][2];
		
			
	}

	Dibujar_Bezier();








    p33[0][1] =  223; p33[0][2] =   165; 
	p33[1][1] =  200; p33[1][2] =   154; 
	p33[2][1] =  175; p33[2][2] =   143; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p33[k][1];
			p3d[k][2] = p33[k][2];
		
			
	}

	Dibujar_Bezier();







    p34[0][1] =  215; p34[0][2] =   160;
	p34[1][1] =  194; p34[1][2] =    136; 
	p34[2][1] =  172; p34[2][2] =    140; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p34[k][1];
			p3d[k][2] = p34[k][2];
		
			
	}

	Dibujar_Bezier();






    p35[0][1] =  180; p35[0][2] =   145; 
	p35[1][1] =  191; p35[1][2] =   138; 
	p35[2][1] =  194; p35[2][2] =   151; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p35[k][1];
			p3d[k][2] = p35[k][2];
		
			
	}

	Dibujar_Bezier();








    p36[0][1] =  116; p36[0][2] =   160; 
	p36[1][1] =  107; p36[1][2] =    165;
	p36[2][1] =  100; p36[2][2] =    167; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p36[k][1];
			p3d[k][2] = p36[k][2];
		
			
	}

	Dibujar_Bezier();









    p37[0][1] =  100; p37[0][2] =   167; 
	p37[1][1] =  99; p37[1][2] =    163; 
	p37[2][1] =  98; p37[2][2] =    160; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p37[k][1];
			p3d[k][2] = p37[k][2];
		
			
	}

	Dibujar_Bezier();




    p38[0][1] =  98; p38[0][2] =  160; 
	p38[1][1] =  110; p38[1][2] =    158; 
	p38[2][1] =  119; p38[2][2] =    155; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p38[k][1];
			p3d[k][2] = p38[k][2];
		
			
	}

	Dibujar_Bezier();


    p39[0][1] =  134; p39[0][2] =   152; 
	p39[1][1] =  148; p39[1][2] =   144; 
	p39[2][1] =  154; p39[2][2] =    142; 
	
	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p39[k][1];
			p3d[k][2] = p39[k][2];
		
			
	}

	Dibujar_Bezier();


    p40[0][1] =  131; p40[0][2] =   150; 
	p40[1][1] =  140; p40[1][2] =    146; 
	p40[2][1] =  153; p40[2][2] =    140; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p40[k][1];
			p3d[k][2] = p40[k][2];
		
			
	}

	Dibujar_Bezier();



    p41[0][1] =  154; p41[0][2] =  142; 
	p41[1][1] =  153; p41[1][2] =   141; 
	p41[2][1] =  153; p41[2][2] =   140; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p41[k][1];
			p3d[k][2] = p41[k][2];
		
			
	}

	Dibujar_Bezier();


    p42[0][1] =  153; p42[0][2] =   140; 
	p42[1][1] =  120; p42[1][2] =   139; 
	p42[2][1] =  105; p42[2][2] =   159 ; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p42[k][1];
			p3d[k][2] = p42[k][2];
		
			
	}

	Dibujar_Bezier();


    p43[0][1] =  129; p43[0][2] =   146; 
	p43[1][1] =  136; p43[1][2] =   140; 
	p43[2][1] =  140; p43[2][2] =    146; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p43[k][1];
			p3d[k][2] = p43[k][2];
		
			
	}

	Dibujar_Bezier();




}



/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
///           TODO SOBRE EL TRAZO B-SPLINE      /////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////






double CGokucaricaturaDlg::N(int i, int k, double tta)
{
	double No;
	double li, ld;

	if ( k == 1 )
	{
		if ( tta >= T[i] )
		{
			if ( tta < T[i+1] )
			{
				No = 1;
			}
			else
			{
				No = 0;
			}
		}
		else

		{
			No = 0;
		}
	}
	else
	{
		if ( tta >= T[i] )
		{
			if ( tta < T[i+k] )
			{
				//Lado izquierdo del B-Spline
				if ( T[i+k-1] == T[i] )
				{
					li = 0;
				}
				else
				{
					li = ((tta-T[i])/(T[i+k-1]-T[i]));
				}
				//Lado derecho del B-Spline
				if ( T[i+k] == T[i+1] )
				{
					ld = 0;
				}
				else
				{
					ld = ((T[i+k]-tta)/(T[i+k]-T[i+1]));
				}
				//B-Spline
				No = ((li*N(i,k-1,tta)) + (ld*N(i+1,k-1,tta)));
			}
			else
			{
				No = 0;
			}
		}
		else
		{
			No = 0;
		}
	}

	return No;
}









void CGokucaricaturaDlg::Dibujar_BSpline()
{
	
	
	
	CClientDC pDC(this);
	
	
	//Convertir P0 a Coordenadas de Monitor

	
	PtoAux[1] = p3d[0][1];
	PtoAux[2] = p3d[0][2];
	
	PtoAuxM[1] = Cx + PtoAux[1] ;
	PtoAuxM[2] = Cy - PtoAux[2];
    pDC.MoveTo(PtoAuxM[1], PtoAuxM[2]);
	
		
	/*
	
	//Poligono
	CPen LapizVerde(PS_DOT, 1, RGB(0,0,255));
	pDC.SelectObject(&LapizVerde);
	for (int l=1; l<=n; l++)
	{
		PtoAuxM[1] = Cx + p3d[l][1];
		PtoAuxM[2] = Cy - p3d[l][2];
		pDC.LineTo(PtoAuxM[1], PtoAuxM[2]);
	}
	
	
	//Convertir P0 a Coordenadas de Monitor
	*/
	
	
	PtoAux[1] = p3d[0][1];
	PtoAux[2] = p3d[0][2];
	
	PtoAuxM[1] = Cx + PtoAux[1];
	PtoAuxM[2] = Cy - PtoAux[2];
    pDC.MoveTo(PtoAuxM[1], PtoAuxM[2]);
	
	
	
	//Curva
	
	
	CPen LapizNegro(PS_SOLID, 1, RGB(0,0,0));
	pDC.SelectObject(&LapizNegro);
	UpdateData(TRUE);
	densidad = m_densidad;
	for (int ka=0; ka<=densidad; ka++)
	{
		PtoAux[1] = 0;
		PtoAux[2] = 0;
		
		if (ka==densidad)
		{
			tt = (((T[n+1]-T[korden-1])*(ka-0.000000001))/(densidad)) + T[korden-1];
		}
		else
		{
			tt = (((T[n+1]-T[korden-1])*(ka))/(densidad)) + T[korden-1];
		}
		
		for (int i=0; i<=n; i++)
		{
			double BAR;
			BAR = N(i,korden,tt);
			PtoAux[1] = (PtoAux[1] + (p3d[i][1] * N(i,korden,tt)));
			PtoAux[2] = (PtoAux[2] + (p3d[i][2] * N(i,korden,tt)));
			
		}

		PtoAuxM[1] = Cx + PtoAux[1];
		PtoAuxM[2] = Cy - PtoAux[2];

		if (ka==0)
		{
			pDC.MoveTo(PtoAuxM[1], PtoAuxM[2]);
		}
		else
		{
			pDC.LineTo(PtoAuxM[1], PtoAuxM[2]);
		}
	}
	
}














void CGokucaricaturaDlg::MatxPto2()
{




	p1[0][1] =  10; p1[0][2] =    45;
	p1[1][1] =  110; p1[1][2] =    70;
	p1[2][1] =  112; p1[2][2] =    122;
	

	for (int k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p1[k][1];
			p3d[k][2] = p1[k][2];
		
			
	}

	Dibujar_BSpline();


	p2[0][1] =  112; p2[0][2] =    122;
	p2[1][1] =  160; p2[1][2] =    20;
	p2[2][1] =  216; p2[2][2] =    122;
	

	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p2[k][1];
			p3d[k][2] = p2[k][2];
		
			
	}

	Dibujar_BSpline();


	
	
	p3[0][1] =  216; p3[0][2] =    122; 
	p3[1][1] =  231; p3[1][2] =    72; 
	p3[2][1] =  300; p3[2][2] =    55; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p3[k][1];
			p3d[k][2] = p3[k][2];
		
			
	}

	Dibujar_BSpline();





	p4[0][1] =  112; p4[0][2] =   122; 
	p4[1][1] =  89; p4[1][2] =   139; 
	p4[2][1] =  88; p4[2][2] =   151; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p4[k][1];
			p3d[k][2] = p4[k][2];
		
			
	}

	Dibujar_BSpline();




	p5[0][1] =  216; p5[0][2] =   122; 
	p5[1][1] =  217; p5[1][2] =   126; 
	p5[2][1] =  220; p5[2][2] =   130; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p5[k][1];
			p3d[k][2] = p5[k][2];
		
			
	}

	Dibujar_BSpline();



	p6[0][1] =  220; p6[0][2] =   130; 
	p6[1][1] =  235; p6[1][2] =   135; 
	p6[2][1] =  239; p6[2][2] =   142; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p6[k][1];
			p3d[k][2] = p6[k][2];
		
			
	}

	Dibujar_BSpline();




	p7[0][1] =  239; p7[0][2] =    142; 
	p7[1][1] =  272; p7[1][2] =    165;
	p7[2][1] =  288; p7[2][2] =    208;
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p7[k][1];
			p3d[k][2] = p7[k][2];
		
			
	}

	Dibujar_BSpline();

	
	

	
	p8[0][1] =  288; p8[0][2] =   208; 
	p8[1][1] =  271; p8[1][2] =   200; 
	p8[2][1] =  260; p8[2][2] =   185; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p8[k][1];
			p3d[k][2] = p8[k][2];
		
			
	}

	Dibujar_BSpline();





	p9[0][1] =  260; p9[0][2] =   185; 
	p9[1][1] =  255; p9[1][2] =   160; 
	p9[2][1] =  249; p9[2][2] =   158; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p9[k][1];
			p3d[k][2] = p9[k][2];
		
			
	}

	Dibujar_BSpline();



	p10[0][1] =  260; p10[0][2] =    185;
	p10[1][1] =  262; p10[1][2] =    203; 
	p10[2][1] =  258; p10[2][2] =    208; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p10[k][1];
			p3d[k][2] = p10[k][2];
		
			
	}

	Dibujar_BSpline();



	p11[0][1] =  249; p11[0][2] =    158; 
	p11[1][1] =   245; p11[1][2] =    160; 
	p11[2][1] =  245; p11[2][2] =    165; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p11[k][1];
			p3d[k][2] = p11[k][2];
		
			
	}

	Dibujar_BSpline();



    p12[0][1] =   245; p12[0][2] =   165; 
	p12[1][1] =   255; p12[1][2] =   180 ;
	p12[2][1] =   252; p12[2][2] =   198; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p12[k][1];
			p3d[k][2] = p12[k][2];
		
			
	}

	Dibujar_BSpline();


  
	p13[0][1] =   245; p13[0][2] =   165; 
	p13[1][1] =   243; p13[1][2] =   155; 
	p13[2][1] =   232; p13[2][2] =   150; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p13[k][1];
			p3d[k][2] = p13[k][2];
		
			
	}

	Dibujar_BSpline();





    p14[0][1] =   232; p14[0][2] =   150; 
	p14[1][1] =   228; p14[1][2] =   175; 
	p14[2][1] =   210; p14[2][2] =   190; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p14[k][1];
			p3d[k][2] = p14[k][2];
		
			
	}

	Dibujar_BSpline();






    p15[0][1] =  212; p15[0][2] =   218; 
	p15[1][1] =  221 ; p15[1][2] =  191; 
	p15[2][1] =  170; p15[2][2] =   139; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p15[k][1];
			p3d[k][2] = p15[k][2];
		
			
	}

	Dibujar_BSpline();




    p16[0][1] =  170; p16[0][2] =   139; 
	p16[1][1] =  182 ; p16[1][2] =   173;
	p16[2][1] =  171; p16[2][2] =    216; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p16[k][1];
			p3d[k][2] = p16[k][2];
		
			
	}

	Dibujar_BSpline();




    p17[0][1] =  171; p17[0][2] =   216; 
	p17[1][1] =  164; p17[1][2] =    185; 
	p17[2][1] =  138; p17[2][2] =    160; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p17[k][1];
			p3d[k][2] = p17[k][2];
		
			
	}

	Dibujar_BSpline();




    


    p18[0][1] =  155; p18[0][2] =    218; 
	p18[1][1] =  155; p18[1][2] =    174; 
	p18[2][1] =  125; p18[2][2] =    144; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p18[k][1];
			p3d[k][2] = p18[k][2];
		
			
	}

	Dibujar_BSpline();



    
	p19[0][1] =  125; p19[0][2] =   144; 
	p19[1][1] =  93; p19[1][2] =    195; 
	p19[2][1] =  119; p19[2][2] =    228; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p19[k][1];
			p3d[k][2] = p19[k][2];
		
			
	}

	Dibujar_BSpline();







    p20[0][1] =  110; p20[0][2] =   184; 
	p20[1][1] =  95; p20[1][2] =   168; 
	p20[2][1] =  82; p20[2][2] =   141; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p20[k][1];
			p3d[k][2] = p20[k][2];
		
			
	}

	Dibujar_BSpline();



     

  
	p21[0][1] =  82; p21[0][2] =    141; 
	p21[1][1] =  66; p21[1][2] =    172; 
	p21[2][1] =  70; p21[2][2] =    200; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p21[k][1];
			p3d[k][2] = p21[k][2];
		
			
	}

	Dibujar_BSpline();





  

    p22[0][1] =  76; p22[0][2] = 153  ; 
	p22[1][1] =  36; p22[1][2] =   171; 
	p22[2][1] =  31; p22[2][2] =   220; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p22[k][1];
			p3d[k][2] = p22[k][2];
		
			
	}

	Dibujar_BSpline();

  



    p23[0][1] =  44; p23[0][2] =   199; 
    p23[1][1] =  24; p23[1][2] =    226; 
	p23[2][1] =  28; p23[2][2] =    250; 
	
	
	  
		
		  
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p23[k][1];
			p3d[k][2] = p23[k][2];
		
			
	}

	Dibujar_BSpline();





    p24[0][1] =  34; p24[0][2] =   250; 
	p24[1][1] =  44; p24[1][2] =   224;
	p24[2][1] =  81; p24[2][2] =    215; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p24[k][1];
			p3d[k][2] = p24[k][2];
		
			
	}

	Dibujar_BSpline();





    p25[0][1] =  279; p25[0][2] =   202; 
	p25[1][1] =  294; p25[1][2] = 230   ; 
	p25[2][1] =  290; p25[2][2] =    250; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p25[k][1];
			p3d[k][2] = p25[k][2];
		
			
	}

	Dibujar_BSpline();




    p26[0][1] =  180; p26[0][2] =   97; 
	p26[1][1] =  165; p26[1][2] =   105; 
	p26[2][1] =  145; p26[2][2] =   97; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p26[k][1];
			p3d[k][2] = p26[k][2];
		
			
	}

	Dibujar_BSpline();





  


    p27[0][1] =  180; p27[0][2] =   97; 
	p27[1][1] =  165; p27[1][2] =  86; 
	p27[2][1] =  145; p27[2][2] =   97; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p27[k][1];
			p3d[k][2] = p27[k][2];
		
			
	}

	Dibujar_BSpline();







    p28[0][1] =  156; p28[0][2] =   130; 
	p28[1][1] =  158; p28[1][2] =   120; 
	p28[2][1] =  151; p28[2][2] =    112; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p28[k][1];
			p3d[k][2] = p28[k][2];
		
			
	}

	Dibujar_BSpline();




    p29[0][1] =  169; p29[0][2] =   130; 
	p29[1][1] =  168; p29[1][2] =    120; 
	p29[2][1] =  175; p29[2][2] =   112; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p29[k][1];
			p3d[k][2] = p29[k][2];
		
			
	}

	Dibujar_BSpline();






    p30[0][1] =  175; p30[0][2] =   112; 
	p30[1][1] =  165; p30[1][2] =   108 ; 
	p30[2][1] =  151; p30[2][2] =   112; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p30[k][1];
			p3d[k][2] = p30[k][2];
		
			
	}

	Dibujar_BSpline();








    p31[0][1] =  182; p31[0][2] =   151; 
	p31[1][1] =  200; p31[1][2] =   160 ; 
	p31[2][1] =  220; p31[2][2] =   168 ; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p31[k][1];
			p3d[k][2] = p31[k][2];
		
			
	}

	Dibujar_BSpline();








    p32[0][1] =  220; p32[0][2] =   168; 
	p32[1][1] =  225; p32[1][2] =   169; 
	p32[2][1] =  223; p32[2][2] =   165; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p32[k][1];
			p3d[k][2] = p32[k][2];
		
			
	}

	Dibujar_BSpline();








    p33[0][1] =  223; p33[0][2] =   165; 
	p33[1][1] =  200; p33[1][2] =   154; 
	p33[2][1] =  175; p33[2][2] =   143; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p33[k][1];
			p3d[k][2] = p33[k][2];
		
			
	}

	Dibujar_BSpline();







    p34[0][1] =  215; p34[0][2] =   160;
	p34[1][1] =  194; p34[1][2] =    136; 
	p34[2][1] =  172; p34[2][2] =    140; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p34[k][1];
			p3d[k][2] = p34[k][2];
		
			
	}

	Dibujar_BSpline();






    p35[0][1] =  180; p35[0][2] =   145; 
	p35[1][1] =  191; p35[1][2] =   138; 
	p35[2][1] =  194; p35[2][2] =   151; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p35[k][1];
			p3d[k][2] = p35[k][2];
		
			
	}

	Dibujar_BSpline();








    p36[0][1] =  116; p36[0][2] =   160; 
	p36[1][1] =  107; p36[1][2] =    165;
	p36[2][1] =  100; p36[2][2] =    167; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p36[k][1];
			p3d[k][2] = p36[k][2];
		
			
	}

	Dibujar_BSpline();









    p37[0][1] =  100; p37[0][2] =   167; 
	p37[1][1] =  99; p37[1][2] =    163; 
	p37[2][1] =  98; p37[2][2] =    160; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p37[k][1];
			p3d[k][2] = p37[k][2];
		
			
	}

	Dibujar_BSpline();




    p38[0][1] =  98; p38[0][2] =  160; 
	p38[1][1] =  110; p38[1][2] =    158; 
	p38[2][1] =  119; p38[2][2] =    155; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p38[k][1];
			p3d[k][2] = p38[k][2];
		
			
	}

	Dibujar_BSpline();


    p39[0][1] =  134; p39[0][2] =   152; 
	p39[1][1] =  148; p39[1][2] =   144; 
	p39[2][1] =  154; p39[2][2] =    142; 
	
	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p39[k][1];
			p3d[k][2] = p39[k][2];
		
			
	}

	Dibujar_BSpline();


    p40[0][1] =  131; p40[0][2] =   150; 
	p40[1][1] =  140; p40[1][2] =    146; 
	p40[2][1] =  153; p40[2][2] =    140; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p40[k][1];
			p3d[k][2] = p40[k][2];
		
			
	}

	Dibujar_BSpline();



    p41[0][1] =  154; p41[0][2] =  142; 
	p41[1][1] =  153; p41[1][2] =   141; 
	p41[2][1] =  153; p41[2][2] =   140; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p41[k][1];
			p3d[k][2] = p41[k][2];
		
			
	}

	Dibujar_BSpline();


    p42[0][1] =  153; p42[0][2] =   140; 
	p42[1][1] =  120; p42[1][2] =   139; 
	p42[2][1] =  105; p42[2][2] =   159 ; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p42[k][1];
			p3d[k][2] = p42[k][2];
		
			
	}

	Dibujar_BSpline();


    p43[0][1] =  129; p43[0][2] =   146; 
	p43[1][1] =  136; p43[1][2] =   140; 
	p43[2][1] =  140; p43[2][2] =    146; 
	

	
	for ( k=0; k<=n; k++)
	{
		
		
			p3d[k][1] = p43[k][1];
			p3d[k][2] = p43[k][2];
		
			
	}

	Dibujar_BSpline();




}

void CGokucaricaturaDlg::Dibujar_Bspline2() 
{
	// TODO: Add your control notification handler code here
		

	Cx=630;
    Cy=300; 

	T[0] = 0;	T[1] = 0;	T[2] = 0;	T[3] = 2;	T[4] = 2;
  	T[5] = 2;	/*T[6] = 6;	T[7] = 7;	T[8] =10;	T[9] =10;
  	T[10]=10;	T[11]=11;	T[12]=12;	T[13]=13;	T[14]=14;

/*/
	MatxPto2();

	
}



void CGokucaricaturaDlg::DibujarCurvaBspline() 
{
	// TODO: Add your control notification handler code here
	
	Cx=300;
    Cy=300; 

	MatxPto2();
	
}
