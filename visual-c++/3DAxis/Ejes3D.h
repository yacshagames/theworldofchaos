// Ejes3D.h : main header file for the EJES3D application
//

#if !defined(AFX_EJES3D_H__6D8E2504_E555_11D4_B224_CC053BD7D972__INCLUDED_)
#define AFX_EJES3D_H__6D8E2504_E555_11D4_B224_CC053BD7D972__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CEjes3DApp:
// See Ejes3D.cpp for the implementation of this class
//

class CEjes3DApp : public CWinApp
{
public:
	CEjes3DApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEjes3DApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEjes3DApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EJES3D_H__6D8E2504_E555_11D4_B224_CC053BD7D972__INCLUDED_)
