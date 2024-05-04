// Curvas.h : main header file for the CURVAS application
//

#if !defined(AFX_CLASETRANSFORMACIONES_H__D94C0025_088B_11D4_B69F_0000214974A3__INCLUDED_)
#define AFX_CLASETRANSFORMACIONES_H__D94C0025_088B_11D4_B69F_0000214974A3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "math.h"	    	// math functions


/////////////////////////////////////////////////////////////////////////////
// CCurvasApp:
// See Curvass.cpp for the implementation of this class
//

class CCurvasApp : public CWinApp
{
public:
	CCurvasApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCurvasApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCurvasApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLASETRANSFORMACIONES_H__D94C0025_088B_11D4_B69F_0000214974A3__INCLUDED_)
