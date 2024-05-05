// CurvasDlg.h : header file
//

#if !defined(AFX_CURVASDLG_H__31599F06_FA7D_11D4_B225_DAA9ABABF23C__INCLUDED_)
#define AFX_CURVASDLG_H__31599F06_FA7D_11D4_B225_DAA9ABABF23C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCurvasDlg dialog

class CCurvasDlg : public CDialog
{
// Construction
public:

	CDC *pDC;

	void Actualizar_puntos_en_caja_de_dialogo();
	void Inicializar_Puntos();
	void Dibujar_Sistema();
	void Dibujar_Poligonal();
	void Dibujar_Curvas();
    
  	double mt[5][5];                //Matriz de Trnasformacion
	double mm[5][5];                //Matriz de datos de transformacion
    
	double p[8][5];                 //Valores de los puntos en 3d
	double p3d[8][5];               //Puntos transformados en 3d
	double p2d[8][5];               //Puntos transformados en 2d
	double PtoAux[8];               //Vector Punto Auxiliar
	double pm[8][5];                //Puntos - Monitor 2d
	int PtoAuxM[8];              //Vector Puntos Monitor 2d

	double Q[8][8][5];				//Arreglo Qs
	double A[8][5];					//Vector As
	double T[8];					//Vector Ts
	double tt;						//t
	int densidad;					//densidad


	//LAGRANGE
    double Ln(int k, double tt);    //Función Lagrange

    
	double e3d[4][5];               //Valores de los ejes en 3d
	int em[4][4];                //Puntos - Monitor 2d

	double pi;                      //Valor de Pi

    double anga;                    //Angulo alpha
    double angb;                    //Angulo beta
    double Cx;                      //Centro X
    double Cy;                      //Centro Y
	int n;                          //Cantidad Puntos - 1

	double dividendo;               //Dividendo m de Proyecciones
	double divisor;                 //Divisor n de Proyecciones
	double centro[4];               //Centro de Proyeccion
	double ro[4];                   //Punto del Plano Proyeccion
	double normal[4];               //Normal del Plano Proyeccion

	double mataux[5][5];
	double b[5];
	double c[5];

	void Transformar_puntos3d();                               //Transforma los puntos a 2D
	void Transformar_eje3d();                                  //Transforma el eje a 2D
    double rad(double angulo);                                 //Conversion en radianes
    int f(int valor);									   //Factorial
	double B(int k, double tt);                                //Bernstein
    void MatxMat();                                            //Matriz x Matriz
	void MatxPto();                                            //Matriz x Punto
	double W(int i, double tt);
	void Obtener_An();										   //Obtener An
	void Trasladar(double Tx, double Ty, double Tz);           //Trasladar
	void Escalar(double Ex, double Ey, double Ez);             //Escalar
	void Rotar(int Eje, double ang);                           //Rotar
	void Proyectar();                                          //Proyectar
	void DibujaEje();
	void Dibujar_Curva_Newton();                                 
	void Dibujar_Curva_Lagrange();
	void Dibujar_Curva_Bezier();



	CCurvasDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCurvasDlg)
	enum { IDD = IDD_CURVAS_DIALOG };
	CStatic	m_Fondo;
	double	m_P1X;
	double	m_P1Y;
	double	m_P1Z;
	double	m_P3X;
	double	m_P3Y;
	double	m_P3Z;
	double	m_P5X;
	double	m_P5Y;
	double	m_P5Z;
	double	m_P6X;
	double	m_P6Y;
	double	m_P6Z;
	double	m_P4X;
	double	m_P4Y;
	double	m_P4Z;
	double	m_P2X;
	double	m_P2Y;
	double	m_P2Z;
	int		m_EjeRotacion;
	int		m_EjeTraslacion;
	BOOL	m_ActivaNewton;
	BOOL	m_ActivaLagrange;
	BOOL	m_ActivaBezier;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCurvasDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCurvasDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTrasladarmas();
	afx_msg void OnTrasladarmenos();
	afx_msg void OnRotarmas();
	afx_msg void OnRotarmenos();
	afx_msg void OnActualizarpoligonal();
	afx_msg void OnReiniciardibujo();
	afx_msg void OnCurvanewton();
	afx_msg void OnCurvalagrange();
	afx_msg void OnCurvabezier();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CURVASDLG_H__31599F06_FA7D_11D4_B225_DAA9ABABF23C__INCLUDED_)
