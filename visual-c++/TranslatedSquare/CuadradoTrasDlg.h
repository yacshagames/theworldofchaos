/*************************************************************************

LICENSE

	This file is released under the terms of the BSD 3-Clause License.
	Read LICENSE.txt file for more information.

*************************************************************************/

// CuadradoTrasDlg.h : header file
//

#if !defined(AFX_CUADRADOTRASDLG_H__648DEB86_11F1_11D4_B222_FCCA97D80C23__INCLUDED_)
#define AFX_CUADRADOTRASDLG_H__648DEB86_11F1_11D4_B222_FCCA97D80C23__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCuadradoTrasDlg dialog

class CCuadradoTrasDlg : public CDialog
{
// Construction
public:
	double ox,oy,ix,iy,jx,jy,zy;
	double Punto[4][3];
	void DibujarEjes();	
	void Dibujar();
	void TrasladarZ( int desplazamiento );
	void TrasladarY( int desplazamiento );
	void TrasladarX( int desplazamiento );
	void InicializarPuntos();
	CCuadradoTrasDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCuadradoTrasDlg)
	enum { IDD = IDD_CUADRADOTRAS_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCuadradoTrasDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCuadradoTrasDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnXpositivo();
	afx_msg void OnYpositivo();
	afx_msg void OnZpositivo();
	afx_msg void OnXnegativo();
	afx_msg void OnYnegativo();
	afx_msg void OnZnegativo();
	afx_msg void OnReiniciar();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUADRADOTRASDLG_H__648DEB86_11F1_11D4_B222_FCCA97D80C23__INCLUDED_)
