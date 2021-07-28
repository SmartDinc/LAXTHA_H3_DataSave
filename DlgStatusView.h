#if !defined(AFX_DLGSTATUSVIEW_H__A9D5B6A5_726A_46EB_82EC_4FCBC7D0A6A1__INCLUDED_)
#define AFX_DLGSTATUSVIEW_H__A9D5B6A5_726A_46EB_82EC_4FCBC7D0A6A1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgStatusView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgStatusView dialog

#include "LXSMWD12.h"	// USB장치 통신 함수및 구조체 타입 정의 있음. 

class CDlgStatusView : public CDialog
{
// Construction
public:
	CDlgStatusView(CWnd* pParent = NULL);   // standard constructor
	HWND hWnd_StreamMsgTarget;
	void Display_Status1(CString str);
	void DisplayResult();
	void DisplayResult2();

	// 검사결과 받아둘 구조체 
	st_DiagResult stDiagResult;

	UINT dw_Thread_HeartSound_ID;
//	HANDLE h_Thread_HeartSound;
// Dialog Data
	//{{AFX_DATA(CDlgStatusView)
	enum { IDD = IDD_DLG_STATUSVIEW };
	CListBox	m_ListHbiResult;
	CListBox	m_ListHistoResult;
	CProgressCtrl	m_Progress_StreamQRemain;
	CListBox	m_ListStatus1;
	CString	m_Finger;
	CString	m_Stability;
	CString	m_AutoSet;
	UINT	m_HeartRate;
	CString	m_DiagStatus;
	UINT	m_DiagRTime;
	CString	m_DiagResult;
	UINT	m_HBQty;
	CString	m_PerfusionIndex;
	CString	m_ANSActLevel;
	UINT	m_HRResult;
	CString	m_HRResultLevel;
	CString	m_PIResultLevel;
	CString	m_PSNSActLevel;
	UINT	m_PSNSBal;
	UINT	m_SNSBal;
	CString	m_SNSActLevel;
	CString	m_SNSBalLevel;
	CString	m_SNSAct;
	CString	m_PSNSAct;
	CString	m_ANSAct;
	CString	m_PIResult;
	CString	m_LOWPI;
	UINT	m_NumFaultHBI;
	CString	m_AbnormalHBI;
	CString	m_Active;
	CString	m_StressChronic;
	CString	m_StressAcute;
	int		m_PID;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgStatusView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgStatusView)
	afx_msg void OnBTNOpenDevice();
	virtual BOOL OnInitDialog();
	afx_msg void OnBUTTON1IDCBTNCloseDevice();
	afx_msg void OnBTNSetConfigMsg();
	afx_msg void OnBTNDiagStart();
	afx_msg void OnBTNDiagStop();
	afx_msg void OnBTNReqDiagResult1();
	afx_msg void OnBTNReqDiagResult2();
	afx_msg void OnBTNReqDiagResult3();
	afx_msg void OnBtnDisableautoentry();
	afx_msg void OnBtnDiagstop();
	afx_msg void OnBTNOpenDeviceSync();
	afx_msg void OnBtnGetUsbSerial();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	afx_msg LRESULT OnHeartBeat(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDeviceStatus(WPARAM wParam, LPARAM lParam);

//	afx_msg void OnHeartBeat(WPARAM wParam,LPARAM lParam);
//	afx_msg void OnDeviceStatus(WPARAM wParam,LPARAM lParam);

public:
	afx_msg void OnBnClickedBtnOpendeviceusbserial();
	CString m_cstUsbSerial;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSTATUSVIEW_H__A9D5B6A5_726A_46EB_82EC_4FCBC7D0A6A1__INCLUDED_)
