// DlgStatusView.cpp : implementation file
//

#include "stdafx.h"
#include "TEST_LXSMWD12.h"
#include "DlgStatusView.h"
#include "process.h"	// for _beginthreadex

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include <time.h> 
#include<windows.h> // strtok(), atoi()를 위해서 인클루드 함 
#include<stdio.h> 
#include <ctime>
#include<iostream>
#include<fstream>
#include<string>
#include <thread>
using namespace std;
// 출처: https://blockdmask.tistory.com/322 [개발자 지망생]

// 20201204
string filename_1sBPM = "";
//string filename_PPI_Array = "";
int total_s = 0;
char buffer1[80];
/////////////////////////////////////////////////////////////////////////////

// CDlgStatusView dialog
CDlgStatusView::CDlgStatusView(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgStatusView::IDD, pParent)
	, m_cstUsbSerial(_T(""))
{
	//{{AFX_DATA_INIT(CDlgStatusView)
	m_Finger = _T("");
	m_Stability = _T("");
	m_AutoSet = _T("");
	m_HeartRate = 0;
	m_DiagStatus = _T("");
	m_DiagRTime = 0;
	m_DiagResult = _T("");
	m_HBQty = 0;
	m_PerfusionIndex = _T("");
	m_ANSActLevel = _T("");
	m_HRResult = 0;
	m_HRResultLevel = _T("");
	m_PIResultLevel = _T("");
	m_PSNSActLevel = _T("");
	m_PSNSBal = 0;
	m_SNSBal = 0;
	m_SNSActLevel = _T("");
	m_SNSBalLevel = _T("");
	m_SNSAct = _T("");
	m_PSNSAct = _T("");
	m_ANSAct = _T("");
	m_PIResult = _T("");
	m_LOWPI = _T("");
	m_NumFaultHBI = 0;
	m_AbnormalHBI = _T("");
	m_Active = _T("");
	m_StressChronic = _T("");
	m_StressAcute = _T("");
	m_PID = 33;
	//}}AFX_DATA_INIT
}


void CDlgStatusView::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgStatusView)
	DDX_Control(pDX, IDC_LIST_HBIRESULT, m_ListHbiResult);
	DDX_Control(pDX, IDC_LIST_HISTORESULT, m_ListHistoResult);
	DDX_Control(pDX, IDC_PROGRESS_StreamQRemain, m_Progress_StreamQRemain);
	DDX_Control(pDX, IDC_LIST_STATUS1, m_ListStatus1);
	DDX_Text(pDX, IDC_EDIT_Finger, m_Finger);
	DDX_Text(pDX, IDC_EDIT_Stability, m_Stability);
	DDX_Text(pDX, IDC_EDIT_AutoSet, m_AutoSet);
	DDX_Text(pDX, IDC_EDIT_HeartRate, m_HeartRate);
	DDX_Text(pDX, IDC_EDIT_DiagStatus, m_DiagStatus);
	DDX_Text(pDX, IDC_EDIT_DiagRTime, m_DiagRTime);
	DDX_Text(pDX, IDC_EDIT_DiagResult, m_DiagResult);
	DDX_Text(pDX, IDC_EDIT_HBQty, m_HBQty);
	DDX_Text(pDX, IDC_EDIT_PerfusionIndex, m_PerfusionIndex);
	DDX_Text(pDX, IDC_EDIT_ANSActLevel, m_ANSActLevel);
	DDX_Text(pDX, IDC_EDIT_HRResult, m_HRResult);
	DDX_Text(pDX, IDC_EDIT_HRResultLevel, m_HRResultLevel);
	DDX_Text(pDX, IDC_EDIT_PIResultLevel, m_PIResultLevel);
	DDX_Text(pDX, IDC_EDIT_PSNSActLevel, m_PSNSActLevel);
	DDX_Text(pDX, IDC_EDIT_PSNSBal, m_PSNSBal);
	DDX_Text(pDX, IDC_EDIT_SNSBal, m_SNSBal);
	DDX_Text(pDX, IDC_EDIT_SNSActLevel, m_SNSActLevel);
	DDX_Text(pDX, IDC_EDIT_SNSBalLevel, m_SNSBalLevel);
	DDX_Text(pDX, IDC_EDIT_SNSAct, m_SNSAct);
	DDX_Text(pDX, IDC_EDIT_PSNSAct, m_PSNSAct);
	DDX_Text(pDX, IDC_EDIT_ANSAct, m_ANSAct);
	DDX_Text(pDX, IDC_EDIT_PIResult, m_PIResult);
	DDX_Text(pDX, IDC_EDIT_LOWPI, m_LOWPI);
	DDX_Text(pDX, IDC_EDIT_FaultHBI, m_NumFaultHBI);
	DDX_Text(pDX, IDC_EDIT_AbnormalHBI, m_AbnormalHBI);
	DDX_Text(pDX, IDC_EDIT_Active, m_Active);
	DDX_Text(pDX, IDC_EDIT_StressChronic, m_StressChronic);
	DDX_Text(pDX, IDC_EDIT_StressAcute, m_StressAcute);
	DDX_Text(pDX, IDC_EDIT1, m_PID);
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_EDIT_USBSERIAL, m_cstUsbSerial);
	DDV_MaxChars(pDX, m_cstUsbSerial, 16);
}


BEGIN_MESSAGE_MAP(CDlgStatusView, CDialog)
	//{{AFX_MSG_MAP(CDlgStatusView)
	ON_BN_CLICKED(IDC_BTN_OpenDevice, OnBTNOpenDevice)
	ON_BN_CLICKED(IDC_BUTTON1IDC_BTN_CloseDevice, OnBUTTON1IDCBTNCloseDevice)
	ON_BN_CLICKED(IDC_BTN_SetConfigMsg, OnBTNSetConfigMsg)
	ON_BN_CLICKED(IDC_BTN_DiagStart, OnBTNDiagStart)
	ON_BN_CLICKED(IDC_BTN_DIAGSTOP, OnBtnDiagstop)
	ON_BN_CLICKED(IDC_BTN_GETUSBSERIAL, OnBtnGetUsbSerial)
	//}}AFX_MSG_MAP

	ON_MESSAGE(WM_USER+2, &CDlgStatusView::OnHeartBeat)
	ON_MESSAGE(WM_USER+3, &CDlgStatusView::OnDeviceStatus)

	ON_BN_CLICKED(IDC_BTN_OpenDeviceUsbSerial, &CDlgStatusView::OnBnClickedBtnOpendeviceusbserial)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgStatusView message handlers


/// 클래스 위저드로 추가한 함수.
BOOL CDlgStatusView::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	/// 대화상자를 최상위 윈도우로. 
	::SetWindowPos(this->m_hWnd, HWND_TOPMOST, 0, 0, 0, 0, 
                                          SWP_NOMOVE|SWP_NOSIZE);//|SWP_SHOWWINDOW);	

	/// 프로그래스 바 초기 설정을 여기서 하고 있다..

	m_Progress_StreamQRemain.SetRange(0,Get_QBufferSize()-1);	
	m_Progress_StreamQRemain.SetStep(1);
	
	Display_Status1("At first, click ths button Set_ConfigMsg."); 

	startSetCount();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/// 리스트 박스1에 글자 기록하는 함수.
void CDlgStatusView::Display_Status1(CString str)
{
	m_ListStatus1.SetSel(m_ListStatus1.GetCount());
	m_ListStatus1.AddString(str);
	m_ListStatus1.SetTopIndex(	m_ListStatus1.GetCount()-1	);
}


// DLL에서 발생한 메시지를 어디로 받을 지 설정한다.
void CDlgStatusView::OnBTNSetConfigMsg() 
{

	Set_ConfigMsg(0, hWnd_StreamMsgTarget,WM_USER+1, 1);	// 실시간 데이터 수신용.메시지 전송은 본 대화상자의 부모로 보낸다. 메시지 아이디를 WM_USER+1로설정함.
	Set_ConfigMsg(1, this->m_hWnd ,WM_USER+2, 1);			// 심박발생이벤트 및 분당심박수 메시지 수신용 설정했다.
	Set_ConfigMsg(2, this->m_hWnd ,WM_USER+3, 1);			// 장치의 상태정보 메시지 수신용 설정했다. 손가락 탈착, 측정안정, 자동셋팅상태정보 수신된다.

	Display_Status1("Message Receiving set completed");
	Display_Status1("Write a PID , click Open_Device");
	Display_Status1("PID examples : H3->33, G3->58, OEM1->56");
}

void CDlgStatusView::OnBTNOpenDevice() 
{

	short retv;
	CString str;

	UpdateData(TRUE); // 대화상자에 기록된 값을 각 변수로 읽어오는 처리.

	retv = Open_Device(m_PID); // 제품별 PID값 :  OEM1 -> 56, H3 -> 33, G3 -> 58

	
	if(retv == -1)  str.Format(_T("USB PID=%d Open_Device fail : no device"),m_PID);
	if(retv == -2)  str.Format(_T("USB PID=%d Open_Device fail : duplicated call"),m_PID);
	if(retv ==  1)  str.Format(_T("USB PID=%d Open_Device OK   : USB device found, connected to device"),m_PID);

	Display_Status1(str);
	
}

void CDlgStatusView::OnBUTTON1IDCBTNCloseDevice() 
{
	short retv;
	CString str;
	
	retv = Close_Device(); // 더 이상 장치를 사용하지 않는 경우 반드시 호출할것. 

	if(retv == -1)	str = _T("Close_Device fail : click Close_Device after Open_device");
	if(retv ==  1)	str = _T("Close_Device OK   : USB device released.");

	Display_Status1(str);
	
}

// 심박음 소리내기 스레드.
UINT WINAPI Thread_HeartSound(LPVOID pParam)
{
	// Beep(500,80);

	return 0;
}

// 심박발생 이벤트 수신처리.
// 인자 lParam 으로 분당심박수가 전송되어온다. unsigned char 로 형변환하여 받아서 사용한다.
afx_msg LRESULT CDlgStatusView::OnHeartBeat(WPARAM wParam, LPARAM lParam)
{
	switch ((unsigned char)wParam) {
	case 0: // 심박 발생했고, 현재의 심박수가 lParam으로 전달된다.
	{
		m_HeartRate = (unsigned char)lParam;// 심박수 표현했다.		// 문예성

		/*
		// 20201208
		time_t curr_time;
		struct tm* curr_tm;
		curr_time = time(NULL);
		curr_tm = localtime(&curr_time);
		char buffer[80];
		std::strftime(buffer, 80, "%Y%m%d_%H%M%S\t", curr_tm);

		ofstream output(filename_1sBPM, ios::app);
		output << buffer << m_HeartRate << endl;
		output.close();
		*/
		

		
		SYSTEMTIME cur_time;
		GetLocalTime(&cur_time);

		CString strTime;
		strTime.Format("%02d:%02d:%02d.%03d\t", cur_time.wHour, cur_time.wMinute, cur_time.wSecond, cur_time.wMilliseconds);

		float var1 = m_HeartRate;
		float var2 = var1 / 1000;
		int var3 = (int)(60 / var2);

		ofstream output(filename_1sBPM, ios::app);
		output << strTime << m_HeartRate <<"\t"<< var3 << endl;
		output.close();
		

		// 출처: https://killsia.tistory.com/entry/현재-시간-millisecond밀리세컨드까지-가져오기 [One Day One Line]


	

		//Beep(400,80); // 소리내기. 이 자리에서 소리내기 하면서 일정 시간동안 홀딩하게 되면 파형 디스플레이에서 끊김 현상 발생하므로 스레드로 처리.
		_beginthreadex(NULL, 0, Thread_HeartSound, NULL, 0, &dw_Thread_HeartSound_ID);

		break;
	}
	case 1: // 혈류지수 정보수신이다. %단위에 100이 곱해진 값이 lParam으로 전송되어 오므로, 이를 100으로 나누기 해서float으로 사용한다.
	{
		float temp = ((float)((unsigned int)lParam)) / 100.f; // 수신된 값을 %단위로 변경했다.
		m_PerfusionIndex.Format("%.2f", temp); // 소수점 이하 2자리까지 표현.
		break;
	}
	}


	UpdateData(FALSE);

	return 0;

}

// 장치의 상태정보가 수신된다. 
// wParam, lParam 값에 따라 아래와 같은 의미가 있다. 
// wPapam : 0  손가락 탈착 메시지이다. lParam : 0 = 손가락 빠진 시점. 1 = 손가락 들어온 시점. 
// wPapam : 1  측정의 안정상태. lParam : 0 = 불안정 상태, 1 = 안정상태.  
// wPapam : 2  자동셋팅 상태. lParam : 1 = 셋팅중 아님. 0 =  셋팅중임.   셋팅중에는 비정상 데이터 임.
//  활용 : 셋팅중이 아니고, 안정상태이면서 손가락이 들어와 있는 상태가 정상 측정 상태이므로 검사 진입 가능함.
afx_msg LRESULT CDlgStatusView::OnDeviceStatus(WPARAM wParam, LPARAM lParam)
{
	switch((unsigned char)wParam)
	{
	case 0: // 손가락 탈착 이벤트 

		if(((unsigned char)lParam) == 1) // 손가락 들어왔다.
		{
			m_Finger = _T("In");
			//Beep(800,150); // 소리내기. 삑.
			// 기타 초기화 할것들.
			m_LOWPI = _T(".");
			m_AbnormalHBI = _T(".");
			m_NumFaultHBI = 0;
			
		}
		else // 손가락 빠졌다.
		{
			m_Finger = _T("Out");
			//Beep(70,400); // 소리내기. 부욱.
		}

		break;

	case 1: // 안정 이벤트.

		if(((unsigned char)lParam) == 1) //   비안정 -> 안정.
		{
			m_Stability = _T("Stable");
		}
		else // 안정 -> 비안정. 
		{
			m_Stability = _T("Unstable");
		}

		break;

	case 2: // 오토셋 이벤트.

		if(((unsigned char)lParam) == 1) //   Normal  상태로 됨.
		{
			m_AutoSet = _T("Normal");
		}
		else // Normal 상태로 됨.
		{
			m_AutoSet = _T("AutoSet..."); // AutoSet 상태임.
		}

		break;

	case 3: // 검사 상태. 0: 비진행. 1: 진행. 2: 진행하다가 중지됨. - 사유 : 검사진행중 손가락 뺐음. 3: 진행하다가 중지됨 - 사유: 심한저혈류로 검사 중지됨.
		if(((unsigned char)lParam) == 0)
		{
			m_DiagStatus = _T("not going");
		}
		else if(((unsigned char)lParam) == 1)
		{
			m_DiagStatus = _T("going");
		}
		else if(((unsigned char)lParam) == 2)
		{
			m_DiagStatus = _T("stopped-finger out");
		}
		else if(((unsigned char)lParam) == 3)
		{
			m_DiagStatus = _T("stopped-low perfusion");
		}

		break;

	case 4: // 검사결과 보유여부. 검사결과 있는 경우1, 없는 경우 0.

		if(((unsigned char)lParam) == 0)
		{
			m_DiagResult = _T("no data");
		}
		else if(((unsigned char)lParam) == 1)
		{
			m_DiagResult = _T("yes data");
			
			Get_DiagResult(&stDiagResult); // 검사결과 stDiagResult 로 받아오기.
			
			if(stDiagResult.Type == 1)		// 검사결과타입1 - 저혈류. 
			{
				m_LOWPI = _T("Very Low Blood Perfusion");
			}
			else if(stDiagResult.Type == 2) // 검사결과 타입2 - 이상심박.
			{
				m_AbnormalHBI = _T("Abnoraml heartbeat");
				m_NumFaultHBI = stDiagResult.NUM_FaultHBI;
			}
			else if(stDiagResult.Type == 3) // 검사결과 타입3 - HRV검사결과. 
			{
				DisplayResult(); // HRV 결과 표현. 표현할 결과들이 많아 별도의 함수에서 처리함.
				DisplayResult2(); // 활력(무기력), 급성/만성 스트레스 표현. 
			}

		}
		
		break;

	case 5: // 검사 잔여시간. 초단위 60 부터 에서 다운카운팅됨.
	{
		/*
		m_DiagRTime = (unsigned char)lParam;

		CString buff;
		buff.Format(_T("%d"), m_DiagRTime);
		
		total_s++;
		if(0 == buff.Compare("1")){
			if (total_s < 300) {
				Diag_ManualStart();
			}
		}
		
		buff.Format(_T("%d"), total_s);
		Display_Status1(buff);

		*/


		break;
	}
	case 6: // 검사중 확보된 심박수량.
		
		m_HBQty = (unsigned int)lParam;

		break;
	}

	UpdateData(FALSE);

	return 0;
}

void CDlgStatusView::DisplayResult2() 
{
	// 활력 무기력 표현.  7단계. 
	if(stDiagResult.Active_Level == 0)
	{
		m_Active = _T("0-Low(very)");
	}
	else if(stDiagResult.Active_Level == 1)
	{
		m_Active = _T("1-Low(somewhat)");
	}
	else if(stDiagResult.Active_Level == 2)
	{
		m_Active = _T("2-Low(a little)");
	}
	else if(stDiagResult.Active_Level == 3)
	{
		m_Active = _T("3-normal( neutral)");
	}
	else if(stDiagResult.Active_Level == 4)
	{
		m_Active = _T("4-High(a little)");
	}
	else if(stDiagResult.Active_Level == 5)
	{
		m_Active = _T("5-High(somewhat)");
	}
	else if(stDiagResult.Active_Level == 6)
	{
		m_Active = _T("6-High(very)");
	}

	// 급성 스트레스 표현. 5단계. 
	if(stDiagResult.StressAcute_Level == 0)
	{
		m_StressAcute = _T("0-No Stress");
	}
	else if(stDiagResult.StressAcute_Level == 1)
	{
		m_StressAcute = _T("1-stress 1/4.");
	}
	else if(stDiagResult.StressAcute_Level == 2)
	{
		m_StressAcute = _T("2-stress 2/4.");
	}
	else if(stDiagResult.StressAcute_Level == 3)
	{
		m_StressAcute = _T("3-stress 3/4.");
	}
	else if(stDiagResult.StressAcute_Level == 4)
	{
		m_StressAcute = _T("4-stress 4/4.");
	}

	// 만성스트레스 표현 5단계. 
	if(stDiagResult.StressChronic_Level == 0)
	{
		m_StressChronic = _T("0-No.");
	}
	else if(stDiagResult.StressChronic_Level == 1)
	{
		m_StressChronic = _T("1-level 1/4.");
	}
	else if(stDiagResult.StressChronic_Level == 2)
	{
		m_StressChronic = _T("2-level 2/4.");
	}
	else if(stDiagResult.StressChronic_Level == 3)
	{
		m_StressChronic = _T("3-level 3/4.");
	}
	else if(stDiagResult.StressChronic_Level == 4)
	{
		m_StressChronic = _T("4-level 4/4."); // 최악의 상황. 
	}


}

void CDlgStatusView::DisplayResult() 
{
	printf("DisplayResult");

	int idx=0;
	CString str;
//	float ftemp;

	/// 균형
	m_SNSBal = stDiagResult.SNSBal; //  자율신경 균형중 교감비율,
	m_PSNSBal = stDiagResult.PSNSBal; //  자율신경 균형중 부교감비율,

	/// 균형 크기판정값. 
	if(stDiagResult.SNSBal_Level == 0)
	{
		m_SNSBalLevel = _T("SNS << PSNS");
	}
	else if(stDiagResult.SNSBal_Level == 1)
	{
		m_SNSBalLevel = _T("SNS < PSNS");
	}
	else if(stDiagResult.SNSBal_Level == 2)
	{
		m_SNSBalLevel = _T("Good Balance");
	}
	else if(stDiagResult.SNSBal_Level == 3)
	{
		m_SNSBalLevel = _T("SNS > PSNS");
	}
	else if(stDiagResult.SNSBal_Level == 4)
	{
		m_SNSBalLevel = _T("SNS >> PSNS");
	}

	/// 교감활성
	m_SNSAct.Format("%.1f",stDiagResult.SNSAct); // 소수점 이하 1자리까지 표현.

	/// 교감활성 크기 판정값. 
	if(stDiagResult.SNSAct_Level == 0)
	{
		m_SNSActLevel = _T("Very Low");
	}
	else if(stDiagResult.SNSAct_Level == 1)
	{
		m_SNSActLevel = _T("Low");
	}
	else if(stDiagResult.SNSAct_Level == 2)
	{
		m_SNSActLevel = _T("Normal");
	}
	else if(stDiagResult.SNSAct_Level == 3)
	{
		m_SNSActLevel = _T("High");
	}
	else if(stDiagResult.SNSAct_Level == 4)
	{
		m_SNSActLevel = _T("Very High");
	}


	/// 부교감 활성. 
	m_PSNSAct.Format("%.1f",stDiagResult.PSNSAct); // 소수점 이하 1자리까지 표현.

	/// 부교감활성 크기 판정값. 
	if(stDiagResult.PSNSAct_Level == 0)
	{
		m_PSNSActLevel = _T("Very Low");
	}
	else if(stDiagResult.PSNSAct_Level == 1)
	{
		m_PSNSActLevel = _T("Low");
	}
	else if(stDiagResult.PSNSAct_Level == 2)
	{
		m_PSNSActLevel = _T("Normal");
	}
	else if(stDiagResult.PSNSAct_Level == 3)
	{
		m_PSNSActLevel = _T("High");
	}
	else if(stDiagResult.PSNSAct_Level == 4)
	{
		m_PSNSActLevel = _T("Very High");
	}

	/// 자율신경 활성. 
	m_ANSAct.Format("%.1f",stDiagResult.ANSAct); // 소수점 이하 1자리까지 표현.

	/// 자율신경활성 크기 판정값. 
	if(stDiagResult.ANSAct_Level == 0)
	{
		m_ANSActLevel = _T("Very Low");
	}
	else if(stDiagResult.ANSAct_Level == 1)
	{
		m_ANSActLevel = _T("Low");
	}
	else if(stDiagResult.ANSAct_Level == 2)
	{
		m_ANSActLevel = _T("Normal");
	}
	else if(stDiagResult.ANSAct_Level == 3)
	{
		m_ANSActLevel = _T("High");
	}
	else if(stDiagResult.ANSAct_Level == 4)
	{
		m_ANSActLevel = _T("Very High");
	}


	/// 심박수.
	m_HRResult = stDiagResult.HR;			// 문예성

	/// 심박수 크기 판정값. 
	if(stDiagResult.HR_Level == 0)
	{
		m_HRResultLevel = _T("Very Low");
	}
	else if(stDiagResult.HR_Level == 1)
	{
		m_HRResultLevel = _T("Low");
	}
	else if(stDiagResult.HR_Level == 2)
	{
		m_HRResultLevel = _T("Noraml");
	}
	else if(stDiagResult.HR_Level == 3)
	{
		m_HRResultLevel = _T("High");
	}
	else if(stDiagResult.HR_Level == 4)
	{
		m_HRResultLevel = _T("Very High");
	}

	/// 혈류지수. 
	m_PIResult.Format("%.2f",stDiagResult.PI); // 소수점 이하 2자리까지 표현.

	/// 혈류지수  크기 판정값. 
	if(stDiagResult.PI_Level == 0)
	{
		m_PIResultLevel = _T("Very Low");
	}
	else if(stDiagResult.PI_Level == 1)
	{
		m_PIResultLevel = _T("Low");
	}
	else if(stDiagResult.PI_Level == 2)
	{
		m_PIResultLevel = _T("Noraml");
	}
	else if(stDiagResult.PI_Level == 3)
	{
		m_PIResultLevel = _T("High");
	}
	else if(stDiagResult.PI_Level == 4)
	{
		m_PIResultLevel = _T("Very High");
	}


	/// 히스토그램.
	m_ListHistoResult.ResetContent();
	for(idx = 0;idx<225;idx++)
	{
		str.Format("%d : %d",idx, stDiagResult.Histogram[idx]);
		m_ListHistoResult.AddString(str);// 표현.
	}

	/// 심박시간격 데이터.
	m_ListHbiResult.ResetContent();
	
}

void CDlgStatusView::OnBTNDiagStart()
{
	short retv;
	CString str;
	retv = Diag_ManualStart();

	if (retv == -1)  str = _T("Diag_ManualStart fail : must execute after Open_Device.");
	if (retv == -2)  str = _T("Diag_ManualStart fail : finger out.");

	if (retv == 1) {
		str = _T("Diag_ManualStart OK   : Manual Started");
		// 20201208 : 파일 생성
		time_t curr_time;
		struct tm* curr_tm;
		curr_time = time(NULL);
		curr_tm = localtime(&curr_time);

		std::strftime(buffer1, 80, "./data/%Y%m%d_%H%M%S_data.txt", curr_tm);
		filename_1sBPM = buffer1;

		total_s = 0;

		CDlgStatusView::count = 0;
	}
	Display_Status1(str);

	// https://dosnipe.tistory.com/39 [참고용 개발노트]
	// https://www.ibm.com/support/knowledgecenter/ko/ssw_ibm_i_73/rtref/strfti.htm
	// https://dosnipe.tistory.com/39
}


void CDlgStatusView::OnBtnDiagstop() 
{
	short retv;
	CString str;
	retv = Diag_ManualStop();

	if(retv == -1)  str = _T("Diag_ManualStop fail : must execute after Open_Device.");
	if(retv == -2)  str = _T("Diag_ManualStop fail : finger out.");

	if (retv == 1) {
		str = _T("Diag_ManualStop OK   : Stopped.");
		CDlgStatusView::count = -1;
	}
		

	Display_Status1(str);

	
}

// 2018.09.05 Added. 
void CDlgStatusView::OnBtnGetUsbSerial() 
{
	short retv; 
	CString str;

	char buf_serial[20]; // array size must be more than 17. 

	UpdateData(TRUE); 

	retv = Get_UsbSerial(m_PID, buf_serial); // PID for each products :  OEM1 -> 56, H3 -> 33, G3 -> 58

	if(retv == 1)
	{
		str.Format(_T("The attached USB device's serial = %s"), buf_serial);
	}	
	else if(retv == -1)
	{
		str.Format(_T("USB PID=%d device not attached"),m_PID);
	}

	Display_Status1(str);
	
}

// 2020.01.27 added.
void CDlgStatusView::OnBnClickedBtnOpendeviceusbserial()
{
	short retv;
	CString str;

	UpdateData(TRUE); // 대화상자에 기록된 값을 각 변수로 읽어오는 처리.
		
	char * buf_serial; 

	buf_serial = m_cstUsbSerial.GetBuffer(0); m_cstUsbSerial.ReleaseBuffer(); 

	retv = Open_Device_UsbSerial(m_PID,buf_serial); // 제품별 PID값 :  OEM1 -> 56, H3 -> 33, G3 -> 58


	if (retv == -1)  str.Format(_T("USB PID=%d, Serial=%s. Open_Device fail : no device"), m_PID, buf_serial);
	if (retv == -2)  str.Format(_T("USB PID=%d Open_Device fail : duplicated call"), m_PID);
	if (retv == 1)  str.Format(_T("USB PID=%d, Serial=%s. Open_Device OK   : USB device found, connected to device"), m_PID,buf_serial);

	Display_Status1(str);

}



void CDlgStatusView::startSetCount()
{

	CWinThread* p = NULL;
	p = AfxBeginThread(countThread, this);//aExelSaveThread 함수명을 넣어주고

	if (p == NULL)  //쓰레드생성실패시에러메시지
		MessageBox("thread 1 Error");

	// CloseHandle(p); // 클로즈 핸들
}

UINT CDlgStatusView::countThread(LPVOID pParam)
{
	while (TRUE) {
		if (((CDlgStatusView*)pParam)->count >= 0) {
			SYSTEMTIME cur_time;
			GetLocalTime(&cur_time);

			CString strTime;
			strTime.Format("[%02d:%02d:%02d.%03d] %d(s)", cur_time.wHour, cur_time.wMinute, cur_time.wSecond, cur_time.wMilliseconds, ((CDlgStatusView*)pParam)->count);


			((CDlgStatusView*)pParam)->m_ListStatus1.SetSel(((CDlgStatusView*)pParam)->m_ListStatus1.GetCount());
			((CDlgStatusView*)pParam)->m_ListStatus1.AddString(strTime);
			((CDlgStatusView*)pParam)->m_ListStatus1.SetTopIndex(((CDlgStatusView*)pParam)->m_ListStatus1.GetCount() - 1);
			((CDlgStatusView*)pParam)->count++;
			if (((CDlgStatusView*)pParam)->count > 300) {
				((CDlgStatusView*)pParam)->OnBtnDiagstop();
			}
		}
		Sleep(1000);
	}
	

	return 0;
}