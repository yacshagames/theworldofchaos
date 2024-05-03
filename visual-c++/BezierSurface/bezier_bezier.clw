; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CBezier_bezierDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "bezier_bezier.h"

ClassCount=4
Class1=CBezier_bezierApp
Class2=CBezier_bezierDlg
Class3=CAboutDlg

ResourceCount=5
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_BEZIER_BEZIER_DIALOG
Resource4=IDD_ABOUTBOX (Spanish (Modern))
Resource5=IDD_BEZIER_BEZIER_DIALOG (Spanish (Modern))

[CLS:CBezier_bezierApp]
Type=0
HeaderFile=bezier_bezier.h
ImplementationFile=bezier_bezier.cpp
Filter=N

[CLS:CBezier_bezierDlg]
Type=0
HeaderFile=bezier_bezierDlg.h
ImplementationFile=bezier_bezierDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=bezier_bezierDlg.h
ImplementationFile=bezier_bezierDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=CAboutDlg


[DLG:IDD_BEZIER_BEZIER_DIALOG]
Type=1
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Class=CBezier_bezierDlg

[DLG:IDD_BEZIER_BEZIER_DIALOG (Spanish (Modern))]
Type=1
Class=?
ControlCount=6
Control1=IDOK,button,1342242817
Control2=cmdRotarZ,button,1342242816
Control3=cmdRotarX,button,1342242816
Control4=cmdRotarY,button,1342242816
Control5=IDC_Superficie,button,1342242817
Control6=IDC_STATIC,button,1342177287

[DLG:IDD_ABOUTBOX (Spanish (Modern))]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

