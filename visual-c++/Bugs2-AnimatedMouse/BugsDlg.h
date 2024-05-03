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
	int K;
	void Escalar(double escala=2);
	double T[15];
	double N(int i, int k, double tta);
	
	void Borrar();
	void Inicio();
	int anim;
	int densidad;
	void Caritura();
	CBugsDlg(CWnd* pParent = NULL);	// standard constructor
		
	double t[5];
	double angulo[2];
	double p[5][4];
	double pc[3][3];
	double c[3];
	double puntoaux[4];
	double punto[4][4];
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
	virtual void OnCancel();
	afx_msg void OnCurvacompletaMas();
	afx_msg void OnCurvabierta();
	afx_msg void OnCurvacompletamenos();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BUGSDLG_H__35CE8F68_2EA8_11D4_900E_C7B1E716E525__INCLUDED_)
