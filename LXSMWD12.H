// 구조체 타입정의.

struct st_DiagResult
{
	unsigned char Type;				// 결과타입. 1:저혈류, 2:비정상심박(부정맥이 대표적인 원인.), 3: HRV검사결과.

	unsigned char SNSBal;			// 교감신경비율 단위 : % (100*교감활성/(교감활성+부교감활성) %)값. 교감:부교감 = SNS_Balance : 100-SNS_Balance.
	unsigned char SNSBal_Level;		// 교감신경비율 크기 판정값.
	
	unsigned char PSNSBal;			// 부교감신경비율, 단위 : % 
	unsigned char PSNSBal_Level;	// 부교감신경비율 크기 판정값.

	float SNSAct;					// 교감신경활성.
	unsigned char SNSAct_Level;     // 교감신경활성 크기판정값.

	float PSNSAct;					// 부교감신경활성.
	unsigned char PSNSAct_Level;	// 부교감신경활성 크기판정값. 

	float ANSAct;					// 자율신경활성
	unsigned char ANSAct_Level;		// 자율신경활성 크기판정값. 
	
	unsigned char HR;				// 분당심박수. 
	unsigned char HR_Level;			// 분당심박수 크기판정값. 

	float PI;						// 혈류지수. 단위 : %.
	unsigned char PI_Level;			// 혈류지수 크기판정값. 

	float HRVIndex;					// 심박변이도 
	unsigned char HRVIndex_Level;	// 심박변이도 크기 판정값. 


	unsigned char Active_Level;		// 활력-무기력을 의미힌다. 0:무기력(대),1:무기력(중), 2: 무기력(소), 3: 중립, 4: 활력(소). 5: 활력(중), 6:활력(대)

	// !!!!! 자율신경검사법의 스트레스 적용상의 주의점. 
	// 자율신경에 영향을 미치는 인자는 피검자의 질환이나, 체질, 스트레스 등이 있다. 
	// 피검자에게서 다른 질병, 특이체질의 등이 관찰되지 않고, 자율신경에 영향을 미치는 인자 스트레스가 주요한 원인인 경우에만
	// 피검자의 스트레스상태를 자율신경검사 결과로 유추하여 사용됨에 특히 주의할것.
	unsigned char StressAcute_Level;	// 급성스트레스 레벨. 총 5단계. 0(스트레스 아님.) 1,2,3,4(최악의 급성 스트레스 상태.)
	unsigned char StressChronic_Level;  // 만성스트레스 레벨. 총 5단계. 0(만성 아님.), 1,2,3,4(최악의 만성스트레스 상태.)

	unsigned int HBI[255];		// 측정된 심박시간격열. 
	unsigned int NUM_HBI;		// HBI에 저장된 심박수량.
	unsigned int NUM_FaultHBI;	// 심박시간격 중 비정상심박수량.
	unsigned char Histogram[225]; // 225개까지 데이터가 온다.
};

 

// 외부노출함수.
extern "C" __declspec(dllimport) short Set_ConfigMsg(int msgtype_idx, HWND hwnd_msgtarget,int msgid, unsigned char on_off);	
extern "C" __declspec(dllimport) short Open_Device(int pid);									// 장치열기.
extern "C" __declspec(dllimport) short Close_Device();											// 장치 닫기.
extern "C" __declspec(dllimport) short Get_DiagResult(st_DiagResult *diagresult);	
extern "C" __declspec(dllimport) short Get_QBufferSize();										// DLL내의 통신데이터 버퍼의 크기 반환.
extern "C" __declspec(dllimport) short Diag_ManualStart();										// 검사시작.
extern "C" __declspec(dllimport) short Diag_ManualStop();										// 검사 중지.
extern "C" __declspec(dllimport) short Get_UsbSerial(unsigned int product_id, char * serial);	// Get Usb Serial 2018.09.05 Added. 
extern "C" __declspec(dllimport) short Open_Device_UsbSerial(unsigned int product_id, char * serial);	// Open by USB serial 2020.01.27 Added. 




