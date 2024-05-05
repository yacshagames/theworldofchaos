// Cuadrado3DDlg.h : header file
//

#if !defined(AFX_CUADRADO3DDLG_H__7B35699A_1179_11D4_B222_B9D199A2ED22__INCLUDED_)
#define AFX_CUADRADO3DDLG_H__7B35699A_1179_11D4_B222_B9D199A2ED22__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCuadrado3DDlg dialog

class CCuadrado3DDlg : public CDialog
{
// Construction
public:
	void Escalamiento( double escala );
	void DibujarTodo();
	void InicializarPuntos();
	void ReflejarYZ();
	void ReflejarXZ();
	void ReflejarXY();
	void TrasladarZ( int desplazamiento );
	void TrasladarY( int desplazamiento );
	void TrasladarX( int desplazamiento );
	void RotarZ( double angulo);
	void RotarY( double angulo );	
	void RotarX( double angulo );
	void DibujarEjes();	
	double ox,oy,ix,iy,jx,jy,ky;
	double Punto[5][3];

	void Dibujar();
	CCuadrado3DDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCuadrado3DDlg)
	enum { IDD = IDD_CUADRADO3D_DIALOG };
	CStatic	m_Fondo;
	BOOL	m_Sentido;
	BOOL	m_Direccion;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCuadrado3DDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCuadrado3DDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnRotarx();
	afx_msg void OnRotary();
	afx_msg void OnRotarz();
	afx_msg void OnTrasladarx();
	afx_msg void OnTrasladary();
	afx_msg void OnTrasladarz();
	afx_msg void OnReflejarxy();
	afx_msg void OnReflejarxz();
	afx_msg void OnReflejaryz();
	afx_msg void OnReiniciar();
	afx_msg void OnReflejarOrigen();
	afx_msg void OnReflejarx();
	afx_msg void OnReflejary();
	afx_msg void OnReflejarz();
	afx_msg void OnMas();
	afx_msg void OnMenos();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUADRADO3DDLG_H__7B35699A_1179_11D4_B222_B9D199A2ED22__INCLUDED_)
