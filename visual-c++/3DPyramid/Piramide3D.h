/*************************************************************************

LICENSE

	This file is released under the terms of the BSD 3-Clause License.
	Read LICENSE.txt file for more information.

*************************************************************************/

// Piramide3D.h : main header file for the PIRAMIDE3D application
//

#if !defined(AFX_PIRAMIDE3D_H__09A268A4_EA0D_11D4_B224_9AFE6104988B__INCLUDED_)
#define AFX_PIRAMIDE3D_H__09A268A4_EA0D_11D4_B224_9AFE6104988B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CPiramide3DApp:
// See Piramide3D.cpp for the implementation of this class
//

class CPiramide3DApp : public CWinApp
{
public:
	CPiramide3DApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPiramide3DApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CPiramide3DApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PIRAMIDE3D_H__09A268A4_EA0D_11D4_B224_9AFE6104988B__INCLUDED_)
