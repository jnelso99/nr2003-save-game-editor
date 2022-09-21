// SaveGameEditor.h : main header file for the SAVEGAMEEDITOR application
//

#if !defined(AFX_SAVEGAMEEDITOR_H__E4375014_A07E_4920_92AC_233A9445A776__INCLUDED_)
#define AFX_SAVEGAMEEDITOR_H__E4375014_A07E_4920_92AC_233A9445A776__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSaveGameEditorApp:
// See SaveGameEditor.cpp for the implementation of this class
//

class CSaveGameEditorApp : public CWinApp
{
public:
	CSaveGameEditorApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSaveGameEditorApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSaveGameEditorApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAVEGAMEEDITOR_H__E4375014_A07E_4920_92AC_233A9445A776__INCLUDED_)
