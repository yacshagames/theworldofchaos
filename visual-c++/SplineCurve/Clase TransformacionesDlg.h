// Clase TransformacionesDlg.h : header file
//

#if !defined(AFX_CLASETRANSFORMACIONESDLG_H__D94C0027_088B_11D4_B69F_0000214974A3__INCLUDED_)
#define AFX_CLASETRANSFORMACIONESDLG_H__D94C0027_088B_11D4_B69F_0000214974A3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CClaseTransformacionesDlg dialog

class CClaseTransformacionesDlg : public CDialog
{
// Construction
public:
	CClaseTransformacionesDlg(CWnd* pParent = NULL);	// standard constructor
// Variables, Lista de Arreglos y Procedimientos


	double mt[5][5];                //Matriz de Trnasformacion
	double mm[5][5];                //Matriz de datos de transformacion
    
	double p[8][5];                 //Valores de los puntos en 3d
	double p3d[8][5];               //Puntos transformados en 3d
	double p2d[8][5];               //Puntos transformados en 2d
	double PtoAux[8];               //Vector Punto Auxiliar
	double pm[8][5];                //Puntos - Monitor 2d
	double PtoAuxM[8];              //Vector Puntos Monitor 2d

	double Q[8][8][5];				//Arreglo Qs
	double A[8][5];					//Vector As
	double T[15];					//Vector Ts
	double tt;						//t
	int korden;                     //Orden k del B-Spline
	int densidad;					//densidad
    
	double e3d[4][5];               //Valores de los ejes en 3d
	double em[4][4];                //Puntos - Monitor 2d

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
    double f(int valor);									   //Factorial
	double B(int k, double tt);                                //Bernstein
	double N(int i, int k, double tt);                         //B-Spline
    void MatxMat();                                            //Matriz x Matriz
	void MatxPto();                                            //Matriz x Punto
	double W(int i, double tt);
	void Obtener_An();										   //Obtener An
	void Trasladar(double Tx, double Ty, double Tz);           //Trasladar
	void Escalar(double Ex, double Ey, double Ez);             //Escalar
	void Rotar(int Eje, double ang);                           //Rotar
	void Proyectar();                                          //Proyectar
	void Dibujar_Cuadrado();                                   //Dibujar Cuadrado
	void DibujaEje();

    

// Dialog Data
	//{{AFX_DATA(CClaseTransformacionesDlg)
	enum { IDD = IDD_CLASETRANSFORMACIONES_DIALOG };
	double	m_Cex;
	double	m_Cey;
	double	m_Cez;
	double	m_Nox;
	double	m_Noy;
	double	m_Noz;
	double	m_Rox;
	double	m_Roy;
	double	m_Roz;
	int		m_densidad;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClaseTransformacionesDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CClaseTransformacionesDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnAceptar();
	afx_msg void OnTrasXPos();
	afx_msg void OnTrasxN();
	afx_msg void OnTrasYPos();
	afx_msg void OnTrasyN();
	afx_msg void OnTrasZPos();
	afx_msg void OnTraszN();
	afx_msg void OnEje3D();
	afx_msg void OnRotXP();
	afx_msg void OnRotXN();
	afx_msg void OnRotYP();
	afx_msg void OnRotYN();
	afx_msg void OnRotZP();
	afx_msg void OnRotZN();
	afx_msg void OnEscP();
	afx_msg void OnEscN();
	afx_msg void OnDibujo();
	afx_msg void OnValinit();
	afx_msg void OnProyeccion();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLASETRANSFORMACIONESDLG_H__D94C0027_088B_11D4_B69F_0000214974A3__INCLUDED_)
