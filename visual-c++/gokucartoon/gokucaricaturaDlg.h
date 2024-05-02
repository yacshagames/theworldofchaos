// gokucaricaturaDlg.h : header file
//

#if !defined(AFX_GOKUCARICATURADLG_H__453F8D07_31C8_11D4_BB70_EA336ED40145__INCLUDED_)
#define AFX_GOKUCARICATURADLG_H__453F8D07_31C8_11D4_BB70_EA336ED40145__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CGokucaricaturaDlg dialog

class CGokucaricaturaDlg : public CDialog
{
// Construction
public:
	CGokucaricaturaDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CGokucaricaturaDlg)
	enum { IDD = IDD_GOKUCARICATURA_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGokucaricaturaDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation

	
    double mt[5][5];                //Matriz de Trnasformacion
	double mm[5][5];                //Matriz de datos de transformacion
    
	double p1[8][3];				
	double p2[8][3];
	double p3[8][3];
	double p4[8][3];
	double p5[8][3];
	double p6[8][3];
	double p7[8][3];
	double p8[8][3];

	double p9[8][3];				
	double p10[8][3];
	double p11[8][3];
	double p12[8][3];
	double p13[8][3];
	double p14[8][3];
	double p15[8][3];
	double p16[8][3];


	double p17[8][3];				
	double p18[8][3];
	double p19[8][3];
	double p20[8][3];
	double p21[8][3];
	double p22[8][3];
	double p23[8][3];
	double p24[8][3];

	double p25[8][3];				
	double p26[8][3];
	double p27[8][3];
	double p28[8][3];
	double p29[8][3];
	double p30[8][3];
	double p31[8][3];
	double p32[8][3];

	double p33[8][3];
	double p34[8][3];
	double p35[8][3];
	double p36[8][3];
	double p37[8][3];
	double p38[8][3];
	double p39[8][3];
    double p40[8][3];

	double p41[8][3];
	double p42[8][3];
	double p43[8][3];
	double p44[8][3];
    double p45[8][3];


	
	double p3d[8][3];               //Puntos transformados en 3d
	double p2d[8][5];               //Puntos transformados en 2d
	double PtoAux[8];               //Vector Punto Auxiliar
	double pm[8][5];                //Puntos - Monitor 2d
	double PtoAuxM[8];              //Vector Puntos Monitor 2d

	double Q[8][8][5];				//Arreglo Qs
	double A[8][5];					//Vector As
	double T[14];					//Vector Ts
	double tt;						//t
	int densidad;					//densidad
	int m_densidad;					//densidad
    
	double e3d[4][5];               //Valores de los ejes en 3d
	double em[4][4];                //Puntos - Monitor 2d

	double pi;                      //Valor de Pi

    double anga;                    //Angulo alpha
    double angb;                    //Angulo beta
    double Cx;                      //Centro X
    double Cy;                      //Centro Y
	int n;                          //Cantidad Puntos - 1

	

	double mataux[5][5];
	double b[5];
	double c[5];

                               
    double rad(double angulo);                                 //Conversion en radianes
    double f(int valor);									   //Factorial
	double B(int k, double tt);                                //Bernstein
    void MatxPto1();
	void Dibujar_Bezier();                                   //Dibujar Bezier
	void DibujaEje();


	
	double N(int i, int k, double tt);          
	void MatxPto2();
	void Dibujar_BSpline();
	int korden;


protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CGokucaricaturaDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void Salir();
	afx_msg void DibujarCurva();
	afx_msg void DibujarCurvaBspline();
	afx_msg void Dibujar_Bspline2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GOKUCARICATURADLG_H__453F8D07_31C8_11D4_BB70_EA336ED40145__INCLUDED_)
