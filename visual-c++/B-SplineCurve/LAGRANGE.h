/*************************************************************************

LICENSE

	This file is released under the terms of the BSD 3-Clause License.
	Read LICENSE.txt file for more information.

*************************************************************************/

// LAGRANGE.h : main header file for the LAGRANGE application
//

#if !defined(AFX_LAGRANGE_H__3117C714_CDDE_11D3_8730_00C04F145A50__INCLUDED_)
#define AFX_LAGRANGE_H__3117C714_CDDE_11D3_8730_00C04F145A50__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "math.h"
/////////////////////////////////////////////////////////////////////////////
// CLAGRANGEApp:
// See LAGRANGE.cpp for the implementation of this class
//

class CLAGRANGEApp : public CWinApp
{
public:
	CLAGRANGEApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLAGRANGEApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CLAGRANGEApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LAGRANGE_H__3117C714_CDDE_11D3_8730_00C04F145A50__INCLUDED_)
