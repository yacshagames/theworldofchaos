/*************************************************************************

LICENSE

	This file is released under the terms of the BSD 3-Clause License.
	Read LICENSE.txt file for more information.

*************************************************************************/

// SuperficieLagrange.h : main header file for the SUPERFICIELAGRANGE application
//

#if !defined(AFX_SUPERFICIELAGRANGE_H__D4C82744_3EA5_11D4_B222_8F1FC929113A__INCLUDED_)
#define AFX_SUPERFICIELAGRANGE_H__D4C82744_3EA5_11D4_B222_8F1FC929113A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSuperficieLagrangeApp:
// See SuperficieLagrange.cpp for the implementation of this class
//

class CSuperficieLagrangeApp : public CWinApp
{
public:
	CSuperficieLagrangeApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSuperficieLagrangeApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSuperficieLagrangeApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SUPERFICIELAGRANGE_H__D4C82744_3EA5_11D4_B222_8F1FC929113A__INCLUDED_)
