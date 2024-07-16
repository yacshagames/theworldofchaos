/*************************************************************************

LICENSE

	This file is released under the terms of the BSD 3-Clause License.
	Read LICENSE.txt file for more information.

*************************************************************************/

// Clase Transformaciones.h : main header file for the CLASE TRANSFORMACIONES application
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
// CClaseTransformacionesApp:
// See Clase Transformaciones.cpp for the implementation of this class
//

class CClaseTransformacionesApp : public CWinApp
{
public:
	CClaseTransformacionesApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClaseTransformacionesApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CClaseTransformacionesApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLASETRANSFORMACIONES_H__D94C0025_088B_11D4_B69F_0000214974A3__INCLUDED_)
