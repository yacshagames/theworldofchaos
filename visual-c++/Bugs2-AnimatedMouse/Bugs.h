// Bugs.h : main header file for the BUGS application
//

#if !defined(AFX_BUGS_H__35CE8F66_2EA8_11D4_900E_C7B1E716E525__INCLUDED_)
#define AFX_BUGS_H__35CE8F66_2EA8_11D4_900E_C7B1E716E525__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CBugsApp:
// See Bugs.cpp for the implementation of this class
//

class CBugsApp : public CWinApp
{
public:
	CBugsApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBugsApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CBugsApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BUGS_H__35CE8F66_2EA8_11D4_900E_C7B1E716E525__INCLUDED_)
