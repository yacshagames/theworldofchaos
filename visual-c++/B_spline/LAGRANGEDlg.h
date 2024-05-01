// LAGRANGEDlg.h : header file
//

#if !defined(AFX_LAGRANGEDLG_H__3117C716_CDDE_11D3_8730_00C04F145A50__INCLUDED_)
#define AFX_LAGRANGEDLG_H__3117C716_CDDE_11D3_8730_00C04F145A50__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CLAGRANGEDlg dialog

class CLAGRANGEDlg : public CDialog
{
// Construction
public:

	CLAGRANGEDlg(CWnd* pParent = NULL);	// standard constructor
	double t[6];
	double angulo[2];
	double p[3][3];
	double pc[2][2];
	double c[2];
	double puntoaux[3];
	double punto[3][3];
	double ppunto[3][3];
	int npuntos;
	int nodos;
	int densidad;
	double tt;
	int k;
    double vector[3];
	double eje[4][3];
	double ejec[3][3];
	/*****/
	double cvista[1][3];
	double Ro[1][3];
	double N[1][3];
    double pp[1][3];
	double ppc[1][2];
	/*****/
	// Declaracion de Rutinas
    void Dibuja();
	double Produc(double,int,int);
	
	void Curva(double,double);
	void LimpiaCurva(double,double);
	void Trasladar(double,double,double);
	void Escalamiento(double,double,double);
	void RotaX(double anguloRX);
	void RotaY(double anguloRY);
	void RotaZ(double anguloRZ);
	void Reflexion(double, double, double);
	
// Dialog Data
	//{{AFX_DATA(CLAGRANGEDlg)
	enum { IDD = IDD_LAGRANGE_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLAGRANGEDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CLAGRANGEDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnButton1();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	afx_msg void OnButton5();
	afx_msg void OnButton6();
	afx_msg void OnButton7();
	afx_msg void OnButton8();
	afx_msg void OnButton9();
	afx_msg void OnButton10();
	afx_msg void OnButton11();
	afx_msg void OnButton12();
	afx_msg void OnButton13();
	afx_msg void OnButton14();
	afx_msg void OnButton15();
	afx_msg void OnButton16();
	afx_msg void OnButton18();
	afx_msg void OnButton17();
	afx_msg void OnButton21();
	afx_msg void OnButton20();
	afx_msg void OnButton19();
	afx_msg void OnButton22();
	afx_msg void OnButton23();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LAGRANGEDLG_H__3117C716_CDDE_11D3_8730_00C04F145A50__INCLUDED_)
