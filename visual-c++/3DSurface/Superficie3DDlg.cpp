// Superficie3DDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Superficie3D.h"
#include "Superficie3DDlg.h"
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
// CSuperficie3DDlg dialog

CSuperficie3DDlg::CSuperficie3DDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSuperficie3DDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSuperficie3DDlg)
	m_escala = 100;
	m_CoordenadaMax = 1;
	m_CoordenadaMin = -1;
	m_Velocidad = 100;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSuperficie3DDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSuperficie3DDlg)
	DDX_Control(pDX, IDC_CUADRO, m_Cuadro);
	DDX_Text(pDX, IDC_ESCALA, m_escala);
	DDX_Text(pDX, IDC_CMAX, m_CoordenadaMax);
	DDX_Text(pDX, IDC_CMIN, m_CoordenadaMin);
	DDX_Text(pDX, IDC_VELOCIDAD, m_Velocidad);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSuperficie3DDlg, CDialog)
	//{{AFX_MSG_MAP(CSuperficie3DDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDB_ANIMAR, OnAnimar)
	ON_BN_CLICKED(IDC_DETENER, OnDetener)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSuperficie3DDlg message handlers

BOOL CSuperficie3DDlg::OnInitDialog()
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

void CSuperficie3DDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSuperficie3DDlg::OnPaint() 
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
HCURSOR CSuperficie3DDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSuperficie3DDlg::Animar()
{

 //Recoje datos de las cajas de texto
 UpdateData(true);	
	
 //coordenadas del origen de coordenadas ( en pixels )
 //en el plano 2D de la pantalla
 ox=250; //coordenada x
 oy=200; //coordenada y
 //coordenadas de los vectores unitarios i,j,k
 //en el plano 2D de la pantalla
 //se considera que 1 unidad = p pixels
 double p=m_escala;
 //vectores unitarios i,j,k
 ix=-0.9659258*p; //ix=-cos(15)
 iy=0.2588190*p;  //iy=sin(15)
 jx=0.8660254*p;  //jx=cos(30)
 jy=0.5*p;       //jy=sin(30)
 //kx=0;       //no es nesesario declararlo
 ky=-1*p;		  //ky=-1

 double x,y,z;
 
// DibujarEjes();

 const Xn=25,Yn=25; //ancho y alto de cuadricula ( Malla )

 int Malla[Xn][Yn][2]; //Malla 2D de proyeccion de la superficie en la pantalla
 double Superficie[Xn][Yn][3]; //Malla 3D de puntos originales
 int i,j;

 //x pertenece al intervalo [a,b]
 //y pertenece al intervalo [a,b]
 double a=m_CoordenadaMin,b=m_CoordenadaMax;

 //construccion de la Malla 3D a partir de una ecuacion
 //de superficie z=f(x,y)
 for( i=0;i<Xn;i++ )
 {
  x=a+((b-a)/Xn)*i; //particion del eje X
  for( j=0;j<Yn;j++ )
  {
   y=a+((b-a)/Yn)*j; //particion del eje Y

   //Ejemplos de ecuaciones de superficie
   z=-sin(3*(x*x+y*y)); //El Sombrero de Bufon
   //z=x*x-y*y; //La silla de Montar
     //z=5*sqrt(fabs(1-x*x/25-y*y/16)); //Una elipse
   //z=sqrt(1-x*x+y*y);
   //if(z>0)z=4*sqrt(z);else z=0;//-sqrt(z);
   //z=cos(x*x+y*y)-3*cos(x*y)+2*sin(x)+sin(y);

   //Obteniendo Matriz de Superficie 3D
   Superficie[i][j][0]=x;
   Superficie[i][j][1]=y;
   Superficie[i][j][2]=z;
  }
 }

int k,ejerot=0;

CDC *dibujo=m_Cuadro.GetDC();

CPen NewPen(PS_SOLID, 1, RGB(0,0,230) );   
	dibujo->SelectObject(&NewPen);

 //Aceleradores de calculos trigonometricos
 //esto se hace para no emplear las funciones sin() y cos() 
 //que vuelven lento el proceso de animacion y hace que la imagen
 //parpadee mucho
 //La rotacion sera de 0.1 radianes
	double tsen=0.099833, //sin(0.1)
           tcos=0.995004; //cos(0.1)

//Muestra la superficie 3D rotando alrededor de los 3 ejes
//La animacion consiste de 300 cuadros
for( k=0;k<300;k++)
{
	
  //Se cambia el eje de rotacion cada 30 cuadros
  if( !(k%30) ) {ejerot++; ejerot%=3;}

  //rotacion de la Malla 3D
  for( i=0;i<Xn;i++ )
 {

  for( j=0;j<Yn;j++ )
  {

   x=Superficie[i][j][0];
   y=Superficie[i][j][1];
   z=Superficie[i][j][2];

   switch(ejerot)
   {
   case 0: //rotacion alrededor del eje X
    Superficie[i][j][1]=y*tcos-z*tsen;
    Superficie[i][j][2]=y*tsen+z*tcos;
    break;
   case 1: //rotacion alrededor del eje Y
    Superficie[i][j][0]=x*tcos+z*tsen;
    Superficie[i][j][2]=-x*tsen+z*tcos;
    break;
   case 2: //rotacion alrededor del eje Z
    Superficie[i][j][0]=x*tcos-y*tsen;
    Superficie[i][j][1]=x*tsen+y*tcos;
   }

   //Se Proyecta los puntos 3D al plano 2D de la pantalla
   Malla[i][j][0]=(int)(ox+Superficie[i][j][0]*ix+Superficie[i][j][1]*jx);
   Malla[i][j][1]=(int)(oy+Superficie[i][j][0]*iy+Superficie[i][j][1]*jy+Superficie[i][j][2]*ky);
  }
 }


 int n,m;

 //Borra la pantalla
 CRect rect;
 m_Cuadro.GetClientRect(rect);
 dibujo->Rectangle(rect);

 //Muestra la ecuacion de superficie
 dibujo->TextOut(10,10,_T("z = -sin( 3 * (x^2+y^2) )"));

 int alto=rect.Height(), ancho=rect.Width();

 //Muestra la Malla 2D ( Proyeccion de la superficie sobre la pantalla)
 for( i=0;i<Xn;i++ )
  for( j=0;j<Yn;j++ )   
  {

   if( Malla[i][j][0] >0 && Malla[i][j][0] < ancho &&
       Malla[i][j][1] >0 && Malla[i][j][1] < alto)	
   {
    dibujo->MoveTo(Malla[i][j][0],Malla[i][j][1]);
    n=i+1;
    if(n<Xn &&
	   Malla[n][j][0] >0 && Malla[n][j][0] < ancho &&
	   Malla[n][j][1] >0 && Malla[n][j][1] < alto  )
     dibujo->LineTo(Malla[n][j][0],Malla[n][j][1]);

    dibujo->MoveTo(Malla[i][j][0],Malla[i][j][1]);
    m=j+1;
    if(m<Yn &&
	   Malla[i][m][0] >0 && Malla[i][m][0] < ancho &&
	   Malla[i][m][1] >0 && Malla[i][m][1] < alto  )
     dibujo->LineTo(Malla[i][m][0],Malla[i][m][1]);

   }
  }
 //Pone una pausa de "m_Velocidad" milisegundos entre cada cuadro
 //si se presiona el boton Detener se sale del bucle
  if( Pausa(m_Velocidad) )break;
}
 
}

void CSuperficie3DDlg::OnAnimar() 
{
	// TODO: Add your control notification handler code here
	m_Detener= false;
	Animar();
}

//Pone una pausa durante "TiempoPausa" milisengundos
BOOL CSuperficie3DDlg::Pausa(time_t TiempoPausa)
{
	MSG msg;
	clock_t goal; 
	goal = TiempoPausa + clock();
   while( goal > clock() )
	   while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) { 
                // If it's a quit message, we're out of here.
                if (msg.message == WM_QUIT || m_Detener ) 
					 return 1; 
                // Otherwise, dispatch the message.
                DispatchMessage(&msg); 
            } // End of PeekMessage while loop.

   return false;
}

void CSuperficie3DDlg::OnDetener() 
{
	// TODO: Add your control notification handler code here
	m_Detener = true;
}
