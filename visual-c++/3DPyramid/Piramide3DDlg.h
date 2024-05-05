// Piramide3DDlg.h : header file
//

#if !defined(AFX_PIRAMIDE3DDLG_H__09A268A6_EA0D_11D4_B224_9AFE6104988B__INCLUDED_)
#define AFX_PIRAMIDE3DDLG_H__09A268A6_EA0D_11D4_B224_9AFE6104988B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CPiramide3DDlg dialog

class CPiramide3DDlg : public CDialog
{
// Construction
public:
    int ox,oy;
	double ix,iy,jx,jy,ky;
	double Punto[5][3];
    void InicializarPuntos();
	void DibujarEjes();
	void DibujarTodo();
	void Dibujar();
	void RotarX(double angulo);
	void TrasladarX( int desplazamiento );

	CPiramide3DDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CPiramide3DDlg)
	enum { IDD = IDD_PIRAMIDE3D_DIALOG };
	CStatic	m_Fondo;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPiramide3DDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CPiramide3DDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnRotar90();
	afx_msg void OnReiniciar();
	afx_msg void OnTrasladarx();
	afx_msg void OnTrasx();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRotar90Neg();
	afx_msg void OnBnClickedTrasxNeg();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PIRAMIDE3DDLG_H__09A268A6_EA0D_11D4_B224_9AFE6104988B__INCLUDED_)
