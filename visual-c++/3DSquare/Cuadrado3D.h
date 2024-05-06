// Cuadrado3D.h : main header file for the CUADRADO3D application
//

#if !defined(AFX_CUADRADO3D_H__7B356998_1179_11D4_B222_B9D199A2ED22__INCLUDED_)
#define AFX_CUADRADO3D_H__7B356998_1179_11D4_B222_B9D199A2ED22__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCuadrado3DApp:
// See Cuadrado3D.cpp for the implementation of this class
//

class CCuadrado3DApp : public CWinApp
{
public:
	CCuadrado3DApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCuadrado3DApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCuadrado3DApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUADRADO3D_H__7B356998_1179_11D4_B222_B9D199A2ED22__INCLUDED_)
