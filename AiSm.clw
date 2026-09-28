; CLW ファイルは MFC ClassWizard の情報を含んでいます。

[General Info]
Version=1
LastClass=CAiSmDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "AiSm.h"

ClassCount=3
Class1=CAiSmApp
Class2=CAiSmDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_AISM_DIALOG

[CLS:CAiSmApp]
Type=0
HeaderFile=AiSm.h
ImplementationFile=AiSm.cpp
Filter=N

[CLS:CAiSmDlg]
Type=0
HeaderFile=AiSmDlg.h
ImplementationFile=AiSmDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_LIST_CLEAR

[CLS:CAboutDlg]
Type=0
HeaderFile=AiSmDlg.h
ImplementationFile=AiSmDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_AISM_DIALOG]
Type=1
Class=CAiSmDlg
ControlCount=5
Control1=IDOK,button,1073807361
Control2=IDCANCEL,button,1342242816
Control3=IDC_MERGE,button,1342242816
Control4=IDC_LIST_FILES,listbox,1352728833
Control5=IDC_LIST_CLEAR,button,1342242816

