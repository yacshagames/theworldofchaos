/******************************************************************************
:: BUGS2 - ANIMATED MOUSE :: BUGS2 - RATÓN ANIMADO ::

Another style of drawing Bugs:
Draws a mouse's face using Bezier curves, and then animates the mouse's face,
like a cartoon.

Spanish:
Otro estilo de dibujar a Bugs:
Dibuja la cara de un raton usando curvas de Bezier, y luego se anima
la cara del ratón, como un dibujo animado.

Developed by:

Original authors: Amelia
Improvements added from version 2, thanks to Yacsha.

HISTORY...

  >> Version 2 - 03-V-2024
	* Thanks to the collaboration of a follower of "the world of chaos",
	  we obtained the first version. From which we have made the
	  following changes:
	- Update visual-c++\Bugs-MouseAnimated - Porting to VC++ 2017.
	- Added mouse face icon
	- Update format code
	- Various bugs are corrected, which do not allow correct mouse animation.
	- A frame with a white background is added, to better show the animation,
	  and to eliminate the bug that caused the buttons to disappear when
	  starting the animation

  >> Version 1 - 02-VI-2000
	- First version developed by Amelia

Warning!!!: These formulas may contain some errors, if you find them, let me
know from the contact page of "The world of chaos", or suggest a
modification in the project's github repository
https://github.com/yacshagames/elmundodelcaos

******************************************************************************/

#include "stdafx.h"
#include "Bugs.h"
#include "BugsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBugsApp

BEGIN_MESSAGE_MAP(CBugsApp, CWinApp)
	//{{AFX_MSG_MAP(CBugsApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBugsApp construction

CBugsApp::CBugsApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CBugsApp object

CBugsApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CBugsApp initialization

BOOL CBugsApp::InitInstance()
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
	CBugsDlg dlg;
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
