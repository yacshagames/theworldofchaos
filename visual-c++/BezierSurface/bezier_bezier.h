/*************************************************************************

LICENSE

	This file is released under the terms of the BSD 3-Clause License.
	Read LICENSE.txt file for more information.

*************************************************************************/

// bezier_bezier.h : main header file for the BEZIER_BEZIER application
//

#if !defined(AFX_BEZIER_BEZIER_H__F828F2A5_E176_11D3_95FB_BF869007106C__INCLUDED_)
#define AFX_BEZIER_BEZIER_H__F828F2A5_E176_11D3_95FB_BF869007106C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CBezier_bezierApp:
// See bezier_bezier.cpp for the implementation of this class
//

class CBezier_bezierApp : public CWinApp
{
public:
	CBezier_bezierApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBezier_bezierApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CBezier_bezierApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BEZIER_BEZIER_H__F828F2A5_E176_11D3_95FB_BF869007106C__INCLUDED_)
