/*************************************************************************

LICENSE

	This file is released under the terms of the BSD 3-Clause License.
	Read LICENSE.txt file for more information.

*************************************************************************/

// SuperficieLagrangeDlg.h : header file
//

#if !defined(AFX_SUPERFICIELAGRANGEDLG_H__D4C82746_3EA5_11D4_B222_8F1FC929113A__INCLUDED_)
#define AFX_SUPERFICIELAGRANGEDLG_H__D4C82746_3EA5_11D4_B222_8F1FC929113A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSuperficieLagrangeDlg dialog

class CSuperficieLagrangeDlg : public CDialog
{
// Construction
public:
	int graficalista;
	void InicializarPuntos();
	void ConstruirSuperficie(double p[3][3],int eje);
	double Lagrange(double tt,int k,int n);
	double Produc(double tt,int k,int n);
	double t[3];
	double p[3][3],p1[3][3];
	void DibujarEjes();
	double ix,iy,jx,jy,zy;
	int Xn,Yn;//numero de puntos en la malla
	int ox,oy;
	CSuperficieLagrangeDlg(CWnd* pParent = NULL);	// standard constructor
	// Dialog Data
	//{{AFX_DATA(CSuperficieLagrangeDlg)
	enum { IDD = IDD_SUPERFICIELAGRANGE_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSuperficieLagrangeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSuperficieLagrangeDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnGraficar();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SUPERFICIELAGRANGEDLG_H__D4C82746_3EA5_11D4_B222_8F1FC929113A__INCLUDED_)
