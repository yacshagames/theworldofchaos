// CuadradoTras.h : main header file for the CUADRADOTRAS application
//

#if !defined(AFX_CUADRADOTRAS_H__648DEB84_11F1_11D4_B222_FCCA97D80C23__INCLUDED_)
#define AFX_CUADRADOTRAS_H__648DEB84_11F1_11D4_B222_FCCA97D80C23__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCuadradoTrasApp:
// See CuadradoTras.cpp for the implementation of this class
//

class CCuadradoTrasApp : public CWinApp
{
public:
	CCuadradoTrasApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCuadradoTrasApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCuadradoTrasApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUADRADOTRAS_H__648DEB84_11F1_11D4_B222_FCCA97D80C23__INCLUDED_)
