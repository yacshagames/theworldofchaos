/*************************************************************************

LICENSE

	This file is released under the terms of the BSD 3-Clause License.
	Read LICENSE.txt file for more information.

*************************************************************************/

// Ejes3DDlg.h : header file
//

#if !defined(AFX_EJES3DDLG_H__6D8E2506_E555_11D4_B224_CC053BD7D972__INCLUDED_)
#define AFX_EJES3DDLG_H__6D8E2506_E555_11D4_B224_CC053BD7D972__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CEjes3DDlg dialog

class CEjes3DDlg : public CDialog
{
// Construction
public:
	CEjes3DDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CEjes3DDlg)
	enum { IDD = IDD_EJES3D_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEjes3DDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CEjes3DDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnEjes2d();
	afx_msg void OnEjes3d();
	afx_msg void OnLimpiar();
	afx_msg void OnPuntoreal2d();
	afx_msg void OnPuntoreal3d();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EJES3DDLG_H__6D8E2506_E555_11D4_B224_CC053BD7D972__INCLUDED_)
