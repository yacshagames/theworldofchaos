/*************************************************************************

LICENSE

	This file is released under the terms of the BSD 3-Clause License.
	Read LICENSE.txt file for more information.

*************************************************************************/

// Superficie3DDlg.h : header file
//

#if !defined(AFX_SUPERFICIE3DDLG_H__BF2F6FE6_488E_11D4_B222_B89F6DF6EB3A__INCLUDED_)
#define AFX_SUPERFICIE3DDLG_H__BF2F6FE6_488E_11D4_B222_B89F6DF6EB3A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSuperficie3DDlg dialog

class CSuperficie3DDlg : public CDialog
{
// Construction
public:
	BOOL m_Detener;
	BOOL Pausa( time_t TiempoPausa );
	void Animar();
	CSuperficie3DDlg(CWnd* pParent = NULL);	// standard constructor
	double ox,oy,ix,iy,jx,jy,ky;

// Dialog Data
	//{{AFX_DATA(CSuperficie3DDlg)
	enum { IDD = IDD_SUPERFICIE3D_DIALOG };
	CStatic	m_Cuadro;
	double	m_escala;
	double	m_CoordenadaMax;
	double	m_CoordenadaMin;
	int		m_Velocidad;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSuperficie3DDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSuperficie3DDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnAnimar();
	afx_msg void OnDetener();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	int surfaceType;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SUPERFICIE3DDLG_H__BF2F6FE6_488E_11D4_B222_B89F6DF6EB3A__INCLUDED_)
