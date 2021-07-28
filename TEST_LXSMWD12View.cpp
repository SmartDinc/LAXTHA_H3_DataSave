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

//	ON_MESSAGE( WM_USER+1,OnStreamData )    // DLL���� �߻��ϴ� �ǽð� ������ ���� �޽��� ó���� ���Ͽ� ���� �����Ѵ�.

ON_MESSAGE(WM_USER + 1, &CTEST_LXSMWD12View::OnStreamData)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTEST_LXSMWD12View construction/destruction

CTEST_LXSMWD12View::CTEST_LXSMWD12View()
{
	/// Modeless ��ȭ���� �����Ѵ�. DLL�� �Լ� ������ ���� ������ ��ȭ����.
	pDlg = new CDlgStatusView;
	pDlg->Create(IDD_DLG_STATUSVIEW,this);

	// íƮ�� Y�� text �ʱ�ȭ. 
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

	/// for waveform display. �������÷��̸� ���� �ڵ��
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
	pDlg->hWnd_StreamMsgTarget = this->m_hWnd;	// ��ȭ���ڷκ��� ��Ʈ�������� �޽����� �ޱ� ���Ͽ�, ��ȭ���ڿ� �� view�� ������ �ڵ��� �Ѱ��.

}



afx_msg LRESULT CTEST_LXSMWD12View::OnStreamData(WPARAM wParam, LPARAM lParam)
{
	
	// DLL���� AD��ȯ�� float�� �����͸� �����ϰ� �ִ� �������� �����Ͱ� �޽����� ���޵Ǹ�, �޽��� �Ķ��Ÿ �� lParam �� �װ��̴�. 
	// ���� �����͸� �̿��ϱ� ���Ͽ� �� �����͸� Ȱ���Ͽ��� �Ѵ�.
	// �Ʒ��� ��뿹�� �������÷��̸� ���� ����� �Լ��� (float *)(lParam) �̶�� �������� ������ ������ ���ڷ� �ѱ�� �ִ�.  
	ACQPLOT_DLL_Array_Datain_Strip((float *)(lParam), MAXNUM_CH, NUM_SAMPLE);


	// ��ȭ������ progress bar ��ġǥ��.
	pDlg->m_Progress_StreamQRemain.SetPos((unsigned int)wParam);


		/*
			/// �޽��� ������ wParam���� unsigned longŸ���� �߰������� ���۵ȴ�. �������� ����.
			/// (unsigned long)wParam �� ���� 1����Ʈ�� ���۽� ī��Ʈ ���� ����ְ�, �� �� 1����Ʈ���� ������ ��Ʈ��ť������ �����ִ� (��, �� ���α׷����� �о�;� �� ) ������ ������ ��ϵǾ��ִ�.
			/// �Ʒ� �ڵ�� �ܿ����� ��ȭ������ progress bar�� �����Ͽ� �ǽð����� �ܿ����� ����͸� �ϰ� �ִ� �����̴�.
			/// ť���۰� �����÷ο� ���� �ʵ��� �� ��Ʈ�������� �޽��� ����ó���θ� ������ ��.
			/// ���� �÷ο� �߻��ϴ� ���� : �� ó���ο��� ������ �ɸ� ó���� �����ϴ� ��찡 ��ǥ��.


			// ��ȭ������ progress bar ��ġǥ��.
			pDlg ->m_Progress_StreamQRemain.SetPos(Get_StreamQRemain());
			// ��ȭ������ ����ǥ��.
			char buf[10];
			sprintf(buf,"%d",Get_StreamQRemain());
			pDlg->SetDlgItemText(IDC_STATIC_StreamQRemain,buf);

			/// ī��Ʈ�� ǥ��.
			pDlg ->m_Progress_StreamCount.SetPos((unsigned char)wParam);
			sprintf(buf,"%d",(unsigned char)wParam); // ���� 1����Ʈ�� �����.
			pDlg->SetDlgItemText(IDC_STATIC_StreamCount,buf);
		*/

	return 0;
}
