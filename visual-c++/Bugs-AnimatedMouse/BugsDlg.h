// BugsDlg.h : header file
//

#if !defined(AFX_BUGSDLG_H__35CE8F68_2EA8_11D4_900E_C7B1E716E525__INCLUDED_)
#define AFX_BUGSDLG_H__35CE8F68_2EA8_11D4_900E_C7B1E716E525__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CBugsDlg dialog

class CBugsDlg : public CDialog
{
// Construction
public:
	double T[15];
	double N(int i, int k, double tta);
	//void Spline();
	void Borrar();
	void Inicio();
	int anim;
	int Factorial(int num);
	double Bezier(double tt,int k,int n);
	int densidad;
	void Caritura();
	CBugsDlg(CWnd* pParent = NULL);	// standard constructor
	
	double t[5];
	double angulo[2];
	double p[5][3];
	double pc[2][2];
	double c[2];
	double puntoaux[3];
	double punto[3][3];
	int npuntos;
// Dialog Data
	//{{AFX_DATA(CBugsDlg)
	enum { IDD = IDD_BUGS_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBugsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CBugsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnCancel2();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BUGSDLG_H__35CE8F68_2EA8_11D4_900E_C7B1E716E525__INCLUDED_)
