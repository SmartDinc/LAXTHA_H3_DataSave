// TEST_LXSMWD12View.cpp : implementation of the CTEST_LXSMWD12View class
//

#include "stdafx.h"
#include "TEST_LXSMWD12.h"

#include "TEST_LXSMWD12Doc.h"
#include "TEST_LXSMWD12View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif




/////////////////////////////////////////////////////////////////////////////
// CTEST_LXSMWD12View

IMPLEMENT_DYNCREATE(CTEST_LXSMWD12View, CView)

BEGIN_MESSAGE_MAP(CTEST_LXSMWD12View, CView)
	//{{AFX_MSG_MAP(CTEST_LXSMWD12View)
	ON_COMMAND(ID_MENU_VIEWDLGSTATUS, OnMenuViewdlgstatus)
	//}}AFX_MSG_MAP

//	ON_MESSAGE( WM_USER+1,OnStreamData )    // DLL에서 발생하는 실시간 데이터 전송 메시지 처리를 위하여 직접 기입한다.

ON_MESSAGE(WM_USER + 1, &CTEST_LXSMWD12View::OnStreamData)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTEST_LXSMWD12View construction/destruction

CTEST_LXSMWD12View::CTEST_LXSMWD12View()
{
	/// Modeless 대화상자 생성한다. DLL의 함수 시험을 위한 별도의 대화상자.
	pDlg = new CDlgStatusView;
	pDlg->Create(IDD_DLG_STATUSVIEW,this);

	// 챠트의 Y축 text 초기화. 
	char buf[50];

	for(int i=0;i<MAXNUM_CH;i++)
	{
		sprintf(buf,"Ch%d",i+1);
		y_text[i] = buf;		
	}

	Count_SaveData = 0;
	FLAG_SaveData = 0;
}

CTEST_LXSMWD12View::~CTEST_LXSMWD12View()
{
}

BOOL CTEST_LXSMWD12View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTEST_LXSMWD12View drawing

void CTEST_LXSMWD12View::OnDraw(CDC* pDC)
{
	CTEST_LXSMWD12Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here

	/// for waveform display. 파형디스플레이를 위한 코드부
	CRect client_Rect;
	GetClientRect(client_Rect);
	ACQPLOT_DLL_Window_Size_Changed_Or_Data_Set_Changed(this->m_hWnd,client_Rect,NUM_SAMPLE/*plot_unitbitmap_width*/,MAXNUM_CH/*pDoc->m_Number_Channel*/,NUM_SAMPLE/*pDoc->m_Number_Data_Unit*/,100.0f/*pDoc->Max_Amplitude*/,FALSE,TRUE,TRUE,4,0.5/*unit_intv_time*/,1/*Time_Plot_Mode*/);
	ACQPLOT_DLL_Array_Draw_Box_Axis(pDC,TRUE,TRUE,TRUE);
	ACQPLOT_DLL_Draw_Axis_Y_Text(pDC,y_text, "system");
}

/////////////////////////////////////////////////////////////////////////////
// CTEST_LXSMWD12View diagnostics

#ifdef _DEBUG
void CTEST_LXSMWD12View::AssertValid() const
{
	CView::AssertValid();
}

void CTEST_LXSMWD12View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTEST_LXSMWD12Doc* CTEST_LXSMWD12View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTEST_LXSMWD12Doc)));
	return (CTEST_LXSMWD12Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTEST_LXSMWD12View message handlers

void CTEST_LXSMWD12View::OnMenuViewdlgstatus() 
{
	pDlg->ShowWindow(SW_SHOW);
	pDlg->hWnd_StreamMsgTarget = this->m_hWnd;	// 대화상자로부터 스트림데이터 메시지를 받기 위하여, 대화상자에 본 view의 윈도우 핸들을 넘겼다.

}



afx_msg LRESULT CTEST_LXSMWD12View::OnStreamData(WPARAM wParam, LPARAM lParam)
{
	
	// DLL에서 AD변환된 float형 데이터를 저장하고 있는 데이터의 포인터가 메시지로 전달되며, 메시지 파라메타 중 lParam 이 그것이다. 
	// 따라서 데이터를 이용하기 위하여 본 포인터를 활용하여야 한다.
	// 아래의 사용예는 파형디스플레이를 위한 모듈형 함수에 (float *)(lParam) 이라는 형식으로 포인터 변수를 인자로 넘기고 있다.  
	ACQPLOT_DLL_Array_Datain_Strip((float *)(lParam), MAXNUM_CH, NUM_SAMPLE);


	// 대화상자의 progress bar 위치표현.
	pDlg->m_Progress_StreamQRemain.SetPos((unsigned int)wParam);


		/*
			/// 메시지 인자중 wParam으로 unsigned long타입의 추가정보가 전송된다. 데이터의 내용.
			/// (unsigned long)wParam 의 하위 1바이트는 전송시 카운트 값이 들어있고, 그 위 1바이트에는 현재의 스트림큐버퍼의 남아있는 (즉, 본 프로그램에서 읽어와야 할 ) 데이터 수량이 기록되어있다.
			/// 아래 코드는 잔여량을 대화상자의 progress bar로 전송하여 실시간으로 잔여량을 모니터링 하고 있는 예제이다.
			/// 큐버퍼가 오버플로우 하지 않도록 본 스트림데이터 메시지 수신처리부를 만들어야 함.
			/// 오버 플로우 발생하는 이유 : 본 처리부에서 과부하 걸릴 처리를 수행하는 경우가 대표적.


			// 대화상자의 progress bar 위치표현.
			pDlg ->m_Progress_StreamQRemain.SetPos(Get_StreamQRemain());
			// 대화상자의 숫자표현.
			char buf[10];
			sprintf(buf,"%d",Get_StreamQRemain());
			pDlg->SetDlgItemText(IDC_STATIC_StreamQRemain,buf);

			/// 카운트값 표현.
			pDlg ->m_Progress_StreamCount.SetPos((unsigned char)wParam);
			sprintf(buf,"%d",(unsigned char)wParam); // 하위 1바이트만 골랐다.
			pDlg->SetDlgItemText(IDC_STATIC_StreamCount,buf);
		*/

	return 0;
}
