// TEST_LXSMWD12.h : main header file for the TEST_LXSMWD12 application
//

#if !defined(AFX_TEST_LXSMWD12_H__E71D41F5_CD2E_4C00_BB8C_E4C9FD9A5F6E__INCLUDED_)
#define AFX_TEST_LXSMWD12_H__E71D41F5_CD2E_4C00_BB8C_E4C9FD9A5F6E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTEST_LXSMWD12App:
// See TEST_LXSMWD12.cpp for the implementation of this class
//

class CTEST_LXSMWD12App : public CWinApp
{
public:
	CTEST_LXSMWD12App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTEST_LXSMWD12App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CTEST_LXSMWD12App)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEST_LXSMWD12_H__E71D41F5_CD2E_4C00_BB8C_E4C9FD9A5F6E__INCLUDED_)
