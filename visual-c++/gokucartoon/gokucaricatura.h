/*************************************************************************

LICENSE

	This file is released under the terms of the BSD 3-Clause License.
	Read LICENSE.txt file for more information.

*************************************************************************/

// gokucaricatura.h : main header file for the GOKUCARICATURA application
//

#if !defined(AFX_GOKUCARICATURA_H__453F8D05_31C8_11D4_BB70_EA336ED40145__INCLUDED_)
#define AFX_GOKUCARICATURA_H__453F8D05_31C8_11D4_BB70_EA336ED40145__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CGokucaricaturaApp:
// See gokucaricatura.cpp for the implementation of this class
//

class CGokucaricaturaApp : public CWinApp
{
public:
	CGokucaricaturaApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGokucaricaturaApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CGokucaricaturaApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GOKUCARICATURA_H__453F8D05_31C8_11D4_BB70_EA336ED40145__INCLUDED_)
