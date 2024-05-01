// PracticaDlg.h : header file
//

#if !defined(AFX_PRACTICADLG_H__1343CB66_C0B5_11D3_ACBB_A56FA291AF07__INCLUDED_)
#define AFX_PRACTICADLG_H__1343CB66_C0B5_11D3_ACBB_A56FA291AF07__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CPracticaDlg dialog

class CPracticaDlg : public CDialog
{
// Construction
public:
	CPracticaDlg(CWnd* pParent = NULL);	// standard constructor
double eje[4][4];
	double ejec[4][3];
	double c[2];
	double angulo[2];
	double punto[10][4];
	double puntoc[10][4];
	double anguloR[1];
    // Declaracion de Rutinas
    void Dibuja(void);
	void RotaX(double);void RotaY(double); void RotaZ(double);
	
	void Trasladar(double, double, double);
// Dialog Data
	//{{AFX_DATA(CPracticaDlg)
	enum { IDD = IDD_PRACTICA_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPracticaDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CPracticaDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnCancelMode();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnCaptureChanged(CWnd *pWnd);
	afx_msg void OnButton4();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRACTICADLG_H__1343CB66_C0B5_11D3_ACBB_A56FA291AF07__INCLUDED_)
