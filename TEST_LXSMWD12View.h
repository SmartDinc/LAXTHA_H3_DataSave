// TEST_LXSMWD12View.h : interface of the CTEST_LXSMWD12View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEST_LXSMWD12VIEW_H__8A36BA1B_AC51_4F5E_AA35_801F1D2EDA97__INCLUDED_)
#define AFX_TEST_LXSMWD12VIEW_H__8A36BA1B_AC51_4F5E_AA35_801F1D2EDA97__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#if (My64bit == 1) // 64비트용 라이브러리 import
#pragma comment(lib,"LIB_64bit\\LXSMWD12.lib")		// USB장치 통신 라이브러리 임포트.
#pragma comment(lib,"LIB_64bit\\ACQPLOT.lib")		// 챠트 표현하는  라이브러리 임포트. 
#elif (My32bit== 1)// 32비트용 라이브러리 import
#pragma comment(lib,"LIB_32bit\\LXSMWD12.lib")		// USB장치 통신 라이브러리 임포트.
#pragma comment(lib,"LIB_32bit\\ACQPLOT.lib")		// 챠트 표현하는  라이브러리 임포트. 
#endif

#define MAXNUM_CH 1	// 스트림의 최대 채널수.
#define NUM_SAMPLE 4 // 각 채널당 샘플링 수.

#include "DlgStatusView.h"				// 상태보기 대화상자  이것 속에서 LXSMWD12.H 도 include하고 있다.

#include "ACQPLOTDLL.h" // 챠트표현.

class CTEST_LXSMWD12View : public CView
{
protected: // create from serialization only
	CTEST_LXSMWD12View();
	DECLARE_DYNCREATE(CTEST_LXSMWD12View)

// Attributes
public:
	CTEST_LXSMWD12Doc* GetDocument();
	CString y_text[8];
// Operations
public:
	CDlgStatusView *pDlg; // Modeless 대화상자 . DLL 함수시험 , 상태보기 
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTEST_LXSMWD12View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTEST_LXSMWD12View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	unsigned int Count_SaveData,FLAG_SaveData; 
	float SaveData[4096];
	void Save_Data(float* stream);

// Generated message map functions
protected:
	//{{AFX_MSG(CTEST_LXSMWD12View)
	afx_msg void OnMenuViewdlgstatus();
	afx_msg void OnMenuSavedata();
	afx_msg void OnMenuSavestart();
	afx_msg void OnMenuSavestop();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

	afx_msg LRESULT OnStreamData(WPARAM wParam, LPARAM lParam);
};

#ifndef _DEBUG  // debug version in TEST_LXSMWD12View.cpp
inline CTEST_LXSMWD12Doc* CTEST_LXSMWD12View::GetDocument()
   { return (CTEST_LXSMWD12Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEST_LXSMWD12VIEW_H__8A36BA1B_AC51_4F5E_AA35_801F1D2EDA97__INCLUDED_)
