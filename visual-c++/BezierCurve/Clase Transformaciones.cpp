/******************************************************************************
:: BEZIER CURVE :: CURVA SPLINE ::

Draw a Spline Curve

Developed by:

	Original authors: Manuel Paredes
	Improvements added from version 2, thanks to:

	JOSE LUIS DE LA CRUZ LAZARO
	contact@theworldofchaos.com

	YACSHA - Software & Desing, since 1999, Lima-Peru
	>> The World of Chaos - EL MUNDO DEL CAOS - Unlimited Programming
	www.theworldofchaos.com

LICENSE
	This file is released under the terms of the BSD 3-Clause License.
	Read LICENSE.txt file for more information.

HISTORY...

  >> Version 2 - 06-V-2024
	* Thanks to the collaboration of a follower of "the world of chaos",
	  we obtained the first version. From which we have made the
	  following changes:
	- Porting to VC++ 2017.
	- Added a new icon to the project
	- Add credits and version history
	- Translate GUI from spanish to english
	- Warnings due to lack of static_cast are corrected

  >> Version 1 - 03-V-2000
	- First version developed by Manuel Paredes

Warning!!!: These formulas may contain some errors, if you find them, let me
know from the contact page of "The world of chaos", or suggest a
modification in the project's github repository
https://github.com/yacshagames/elmundodelcaos

******************************************************************************/

#include "stdafx.h"
#include "Clase Transformaciones.h"
#include "Clase TransformacionesDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClaseTransformacionesApp

BEGIN_MESSAGE_MAP(CClaseTransformacionesApp, CWinApp)
	//{{AFX_MSG_MAP(CClaseTransformacionesApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClaseTransformacionesApp construction

CClaseTransformacionesApp::CClaseTransformacionesApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CClaseTransformacionesApp object

CClaseTransformacionesApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CClaseTransformacionesApp initialization

BOOL CClaseTransformacionesApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.
/*
#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
*/
	CClaseTransformacionesDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
