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
#include<windows.h> // strtok(), atoi()�� ���ؼ� ��Ŭ��� �� 
#include<stdio.h> 
#include <ctime>
#include<iostream>
#include<fstream>
#include<string>
#include <thread>
using namespace std;
// ��ó: https://blockdmask.tistory.com/322 [������ ������]

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


/// Ŭ���� ������� �߰��� �Լ�.
BOOL CDlgStatusView::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	/// ��ȭ���ڸ� �ֻ��� �������. 
	::SetWindowPos(this->m_hWnd, HWND_TOPMOST, 0, 0, 0, 0, 
                                          SWP_NOMOVE|SWP_NOSIZE);//|SWP_SHOWWINDOW);	

	/// ���α׷��� �� �ʱ� ������ ���⼭ �ϰ� �ִ�..

	m_Progress_StreamQRemain.SetRange(0,Get_QBufferSize()-1);	
	m_Progress_StreamQRemain.SetStep(1);
	
	Display_Status1("At first, click ths button Set_ConfigMsg."); 

	startSetCount();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/// ����Ʈ �ڽ�1�� ���� ����ϴ� �Լ�.
void CDlgStatusView::Display_Status1(CString str)
{
	m_ListStatus1.SetSel(m_ListStatus1.GetCount());
	m_ListStatus1.AddString(str);
	m_ListStatus1.SetTopIndex(	m_ListStatus1.GetCount()-1	);
}


// DLL���� �߻��� �޽����� ���� ���� �� �����Ѵ�.
void CDlgStatusView::OnBTNSetConfigMsg() 
{

	Set_ConfigMsg(0, hWnd_StreamMsgTarget,WM_USER+1, 1);	// �ǽð� ������ ���ſ�.�޽��� ������ �� ��ȭ������ �θ�� ������. �޽��� ���̵� WM_USER+1�μ�����.
	Set_ConfigMsg(1, this->m_hWnd ,WM_USER+2, 1);			// �ɹڹ߻��̺�Ʈ �� �д�ɹڼ� �޽��� ���ſ� �����ߴ�.
	Set_ConfigMsg(2, this->m_hWnd ,WM_USER+3, 1);			// ��ġ�� �������� �޽��� ���ſ� �����ߴ�. �հ��� Ż��, ��������, �ڵ����û������� ���ŵȴ�.

	Display_Status1("Message Receiving set completed");
	Display_Status1("Write a PID , click Open_Device");
	Display_Status1("PID examples : H3->33, G3->58, OEM1->56");
}

void CDlgStatusView::OnBTNOpenDevice() 
{

	short retv;
	CString str;

	UpdateData(TRUE); // ��ȭ���ڿ� ��ϵ� ���� �� ������ �о���� ó��.

	retv = Open_Device(m_PID); // ��ǰ�� PID�� :  OEM1 -> 56, H3 -> 33, G3 -> 58

	
	if(retv == -1)  str.Format(_T("USB PID=%d Open_Device fail : no device"),m_PID);
	if(retv == -2)  str.Format(_T("USB PID=%d Open_Device fail : duplicated call"),m_PID);
	if(retv ==  1)  str.Format(_T("USB PID=%d Open_Device OK   : USB device found, connected to device"),m_PID);

	Display_Status1(str);
	
}

void CDlgStatusView::OnBUTTON1IDCBTNCloseDevice() 
{
	short retv;
	CString str;
	
	retv = Close_Device(); // �� �̻� ��ġ�� ������� �ʴ� ��� �ݵ�� ȣ���Ұ�. 

	if(retv == -1)	str = _T("Close_Device fail : click Close_Device after Open_device");
	if(retv ==  1)	str = _T("Close_Device OK   : USB device released.");

	Display_Status1(str);
	
}

// �ɹ��� �Ҹ����� ������.
UINT WINAPI Thread_HeartSound(LPVOID pParam)
{
	// Beep(500,80);

	return 0;
}

// �ɹڹ߻� �̺�Ʈ ����ó��.
// ���� lParam ���� �д�ɹڼ��� ���۵Ǿ�´�. unsigned char �� ����ȯ�Ͽ� �޾Ƽ� ����Ѵ�.
afx_msg LRESULT CDlgStatusView::OnHeartBeat(WPARAM wParam, LPARAM lParam)
{
	switch ((unsigned char)wParam) {
	case 0: // �ɹ� �߻��߰�, ������ �ɹڼ��� lParam���� ���޵ȴ�.
	{
		m_HeartRate = (unsigned char)lParam;// �ɹڼ� ǥ���ߴ�.		// ������

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
		

		// ��ó: https://killsia.tistory.com/entry/����-�ð�-millisecond�и����������-�������� [One Day One Line]


	

		//Beep(400,80); // �Ҹ�����. �� �ڸ����� �Ҹ����� �ϸ鼭 ���� �ð����� Ȧ���ϰ� �Ǹ� ���� ���÷��̿��� ���� ���� �߻��ϹǷ� ������� ó��.
		_beginthreadex(NULL, 0, Thread_HeartSound, NULL, 0, &dw_Thread_HeartSound_ID);

		break;
	}
	case 1: // �������� ���������̴�. %������ 100�� ������ ���� lParam���� ���۵Ǿ� ���Ƿ�, �̸� 100���� ������ �ؼ�float���� ����Ѵ�.
	{
		float temp = ((float)((unsigned int)lParam)) / 100.f; // ���ŵ� ���� %������ �����ߴ�.
		m_PerfusionIndex.Format("%.2f", temp); // �Ҽ��� ���� 2�ڸ����� ǥ��.
		break;
	}
	}


	UpdateData(FALSE);

	return 0;

}

// ��ġ�� ���������� ���ŵȴ�. 
// wParam, lParam ���� ���� �Ʒ��� ���� �ǹ̰� �ִ�. 
// wPapam : 0  �հ��� Ż�� �޽����̴�. lParam : 0 = �հ��� ���� ����. 1 = �հ��� ���� ����. 
// wPapam : 1  ������ ��������. lParam : 0 = �Ҿ��� ����, 1 = ��������.  
// wPapam : 2  �ڵ����� ����. lParam : 1 = ������ �ƴ�. 0 =  ��������.   �����߿��� ������ ������ ��.
//  Ȱ�� : �������� �ƴϰ�, ���������̸鼭 �հ����� ���� �ִ� ���°� ���� ���� �����̹Ƿ� �˻� ���� ������.
afx_msg LRESULT CDlgStatusView::OnDeviceStatus(WPARAM wParam, LPARAM lParam)
{
	switch((unsigned char)wParam)
	{
	case 0: // �հ��� Ż�� �̺�Ʈ 

		if(((unsigned char)lParam) == 1) // �հ��� ���Դ�.
		{
			m_Finger = _T("In");
			//Beep(800,150); // �Ҹ�����. ��.
			// ��Ÿ �ʱ�ȭ �Ұ͵�.
			m_LOWPI = _T(".");
			m_AbnormalHBI = _T(".");
			m_NumFaultHBI = 0;
			
		}
		else // �հ��� ������.
		{
			m_Finger = _T("Out");
			//Beep(70,400); // �Ҹ�����. �ο�.
		}

		break;

	case 1: // ���� �̺�Ʈ.

		if(((unsigned char)lParam) == 1) //   ����� -> ����.
		{
			m_Stability = _T("Stable");
		}
		else // ���� -> �����. 
		{
			m_Stability = _T("Unstable");
		}

		break;

	case 2: // ����� �̺�Ʈ.

		if(((unsigned char)lParam) == 1) //   Normal  ���·� ��.
		{
			m_AutoSet = _T("Normal");
		}
		else // Normal ���·� ��.
		{
			m_AutoSet = _T("AutoSet..."); // AutoSet ������.
		}

		break;

	case 3: // �˻� ����. 0: ������. 1: ����. 2: �����ϴٰ� ������. - ���� : �˻������� �հ��� ����. 3: �����ϴٰ� ������ - ����: ������������ �˻� ������.
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

	case 4: // �˻��� ��������. �˻��� �ִ� ���1, ���� ��� 0.

		if(((unsigned char)lParam) == 0)
		{
			m_DiagResult = _T("no data");
		}
		else if(((unsigned char)lParam) == 1)
		{
			m_DiagResult = _T("yes data");
			
			Get_DiagResult(&stDiagResult); // �˻��� stDiagResult �� �޾ƿ���.
			
			if(stDiagResult.Type == 1)		// �˻���Ÿ��1 - ������. 
			{
				m_LOWPI = _T("Very Low Blood Perfusion");
			}
			else if(stDiagResult.Type == 2) // �˻��� Ÿ��2 - �̻�ɹ�.
			{
				m_AbnormalHBI = _T("Abnoraml heartbeat");
				m_NumFaultHBI = stDiagResult.NUM_FaultHBI;
			}
			else if(stDiagResult.Type == 3) // �˻��� Ÿ��3 - HRV�˻���. 
			{
				DisplayResult(); // HRV ��� ǥ��. ǥ���� ������� ���� ������ �Լ����� ó����.
				DisplayResult2(); // Ȱ��(�����), �޼�/���� ��Ʈ���� ǥ��. 
			}

		}
		
		break;

	case 5: // �˻� �ܿ��ð�. �ʴ��� 60 ���� ���� �ٿ�ī���õ�.
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
	case 6: // �˻��� Ȯ���� �ɹڼ���.
		
		m_HBQty = (unsigned int)lParam;

		break;
	}

	UpdateData(FALSE);

	return 0;
}

void CDlgStatusView::DisplayResult2() 
{
	// Ȱ�� ����� ǥ��.  7�ܰ�. 
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

	// �޼� ��Ʈ���� ǥ��. 5�ܰ�. 
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

	// ������Ʈ���� ǥ�� 5�ܰ�. 
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
		m_StressChronic = _T("4-level 4/4."); // �־��� ��Ȳ. 
	}


}

void CDlgStatusView::DisplayResult() 
{
	printf("DisplayResult");

	int idx=0;
	CString str;
//	float ftemp;

	/// ����
	m_SNSBal = stDiagResult.SNSBal; //  �����Ű� ������ ��������,
	m_PSNSBal = stDiagResult.PSNSBal; //  �����Ű� ������ �α�������,

	/// ���� ũ��������. 
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

	/// ����Ȱ��
	m_SNSAct.Format("%.1f",stDiagResult.SNSAct); // �Ҽ��� ���� 1�ڸ����� ǥ��.

	/// ����Ȱ�� ũ�� ������. 
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


	/// �α��� Ȱ��. 
	m_PSNSAct.Format("%.1f",stDiagResult.PSNSAct); // �Ҽ��� ���� 1�ڸ����� ǥ��.

	/// �α���Ȱ�� ũ�� ������. 
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

	/// �����Ű� Ȱ��. 
	m_ANSAct.Format("%.1f",stDiagResult.ANSAct); // �Ҽ��� ���� 1�ڸ����� ǥ��.

	/// �����Ű�Ȱ�� ũ�� ������. 
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


	/// �ɹڼ�.
	m_HRResult = stDiagResult.HR;			// ������

	/// �ɹڼ� ũ�� ������. 
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

	/// ��������. 
	m_PIResult.Format("%.2f",stDiagResult.PI); // �Ҽ��� ���� 2�ڸ����� ǥ��.

	/// ��������  ũ�� ������. 
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


	/// ������׷�.
	m_ListHistoResult.ResetContent();
	for(idx = 0;idx<225;idx++)
	{
		str.Format("%d : %d",idx, stDiagResult.Histogram[idx]);
		m_ListHistoResult.AddString(str);// ǥ��.
	}

	/// �ɹڽð��� ������.
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
		// 20201208 : ���� ����
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

	// https://dosnipe.tistory.com/39 [����� ���߳�Ʈ]
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

	UpdateData(TRUE); // ��ȭ���ڿ� ��ϵ� ���� �� ������ �о���� ó��.
		
	char * buf_serial; 

	buf_serial = m_cstUsbSerial.GetBuffer(0); m_cstUsbSerial.ReleaseBuffer(); 

	retv = Open_Device_UsbSerial(m_PID,buf_serial); // ��ǰ�� PID�� :  OEM1 -> 56, H3 -> 33, G3 -> 58


	if (retv == -1)  str.Format(_T("USB PID=%d, Serial=%s. Open_Device fail : no device"), m_PID, buf_serial);
	if (retv == -2)  str.Format(_T("USB PID=%d Open_Device fail : duplicated call"), m_PID);
	if (retv == 1)  str.Format(_T("USB PID=%d, Serial=%s. Open_Device OK   : USB device found, connected to device"), m_PID,buf_serial);

	Display_Status1(str);

}



void CDlgStatusView::startSetCount()
{

	CWinThread* p = NULL;
	p = AfxBeginThread(countThread, this);//aExelSaveThread �Լ����� �־��ְ�

	if (p == NULL)  //������������нÿ����޽���
		MessageBox("thread 1 Error");

	// CloseHandle(p); // Ŭ���� �ڵ�
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