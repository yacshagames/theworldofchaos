// Practica.h : main header file for the PRACTICA application
//

#if !defined(AFX_PRACTICA_H__1343CB64_C0B5_11D3_ACBB_A56FA291AF07__INCLUDED_)
#define AFX_PRACTICA_H__1343CB64_C0B5_11D3_ACBB_A56FA291AF07__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "math.h"
/////////////////////////////////////////////////////////////////////////////
// CPracticaApp:
// See Practica.cpp for the implementation of this class
//

class C3DCubeApp : public CWinApp
{
public:
	C3DCubeApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPracticaApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CPracticaApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRACTICA_H__1343CB64_C0B5_11D3_ACBB_A56FA291AF07__INCLUDED_)
