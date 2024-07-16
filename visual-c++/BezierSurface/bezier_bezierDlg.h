/*************************************************************************

LICENSE

	This file is released under the terms of the BSD 3-Clause License.
	Read LICENSE.txt file for more information.

*************************************************************************/

// bezier_bezierDlg.h : header file
//

#if !defined(AFX_BEZIER_BEZIERDLG_H__F828F2A7_E176_11D3_95FB_BF869007106C__INCLUDED_)
#define AFX_BEZIER_BEZIERDLG_H__F828F2A7_E176_11D3_95FB_BF869007106C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CBezier_bezierDlg dialog

class CBezier_bezierDlg : public CDialog
{
// Construction
public:
	CBezier_bezierDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CBezier_bezierDlg)
	enum { IDD = IDD_BEZIER_BEZIER_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBezier_bezierDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CBezier_bezierDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg
		void DrawBezierSurface();
	void OncmdRotarZ();
	afx_msg void OncmdRotarX();
	afx_msg void OncmdRotarY();
	afx_msg void OnSuperficie();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BEZIER_BEZIERDLG_H__F828F2A7_E176_11D3_95FB_BF869007106C__INCLUDED_)
