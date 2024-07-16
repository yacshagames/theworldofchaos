/*************************************************************************

LICENSE

	This file is released under the terms of the BSD 3-Clause License.
	Read LICENSE.txt file for more information.

*************************************************************************/

// Superficie3D.h : main header file for the SUPERFICIE3D application
//

#if !defined(AFX_SUPERFICIE3D_H__BF2F6FE4_488E_11D4_B222_B89F6DF6EB3A__INCLUDED_)
#define AFX_SUPERFICIE3D_H__BF2F6FE4_488E_11D4_B222_B89F6DF6EB3A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSuperficie3DApp:
// See Superficie3D.cpp for the implementation of this class
//

class CSuperficie3DApp : public CWinApp
{
public:
	CSuperficie3DApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSuperficie3DApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSuperficie3DApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SUPERFICIE3D_H__BF2F6FE4_488E_11D4_B222_B89F6DF6EB3A__INCLUDED_)
