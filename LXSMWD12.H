// ����ü Ÿ������.

struct st_DiagResult
{
	unsigned char Type;				// ���Ÿ��. 1:������, 2:������ɹ�(�������� ��ǥ���� ����.), 3: HRV�˻���.

	unsigned char SNSBal;			// �����Ű���� ���� : % (100*����Ȱ��/(����Ȱ��+�α���Ȱ��) %)��. ����:�α��� = SNS_Balance : 100-SNS_Balance.
	unsigned char SNSBal_Level;		// �����Ű���� ũ�� ������.
	
	unsigned char PSNSBal;			// �α����Ű����, ���� : % 
	unsigned char PSNSBal_Level;	// �α����Ű���� ũ�� ������.

	float SNSAct;					// �����Ű�Ȱ��.
	unsigned char SNSAct_Level;     // �����Ű�Ȱ�� ũ��������.

	float PSNSAct;					// �α����Ű�Ȱ��.
	unsigned char PSNSAct_Level;	// �α����Ű�Ȱ�� ũ��������. 

	float ANSAct;					// �����Ű�Ȱ��
	unsigned char ANSAct_Level;		// �����Ű�Ȱ�� ũ��������. 
	
	unsigned char HR;				// �д�ɹڼ�. 
	unsigned char HR_Level;			// �д�ɹڼ� ũ��������. 

	float PI;						// ��������. ���� : %.
	unsigned char PI_Level;			// �������� ũ��������. 

	float HRVIndex;					// �ɹں��̵� 
	unsigned char HRVIndex_Level;	// �ɹں��̵� ũ�� ������. 


	unsigned char Active_Level;		// Ȱ��-������� �ǹ�����. 0:�����(��),1:�����(��), 2: �����(��), 3: �߸�, 4: Ȱ��(��). 5: Ȱ��(��), 6:Ȱ��(��)

	// !!!!! �����Ű�˻���� ��Ʈ���� ������� ������. 
	// �����Ű濡 ������ ��ġ�� ���ڴ� �ǰ����� ��ȯ�̳�, ü��, ��Ʈ���� ���� �ִ�. 
	// �ǰ��ڿ��Լ� �ٸ� ����, Ư��ü���� ���� �������� �ʰ�, �����Ű濡 ������ ��ġ�� ���� ��Ʈ������ �ֿ��� ������ ��쿡��
	// �ǰ����� ��Ʈ�������¸� �����Ű�˻� ����� �����Ͽ� ���ʿ� Ư�� �����Ұ�.
	unsigned char StressAcute_Level;	// �޼���Ʈ���� ����. �� 5�ܰ�. 0(��Ʈ���� �ƴ�.) 1,2,3,4(�־��� �޼� ��Ʈ���� ����.)
	unsigned char StressChronic_Level;  // ������Ʈ���� ����. �� 5�ܰ�. 0(���� �ƴ�.), 1,2,3,4(�־��� ������Ʈ���� ����.)

	unsigned int HBI[255];		// ������ �ɹڽð��ݿ�. 
	unsigned int NUM_HBI;		// HBI�� ����� �ɹڼ���.
	unsigned int NUM_FaultHBI;	// �ɹڽð��� �� ������ɹڼ���.
	unsigned char Histogram[225]; // 225������ �����Ͱ� �´�.
};

 

// �ܺγ����Լ�.
extern "C" __declspec(dllimport) short Set_ConfigMsg(int msgtype_idx, HWND hwnd_msgtarget,int msgid, unsigned char on_off);	
extern "C" __declspec(dllimport) short Open_Device(int pid);									// ��ġ����.
extern "C" __declspec(dllimport) short Close_Device();											// ��ġ �ݱ�.
extern "C" __declspec(dllimport) short Get_DiagResult(st_DiagResult *diagresult);	
extern "C" __declspec(dllimport) short Get_QBufferSize();										// DLL���� ��ŵ����� ������ ũ�� ��ȯ.
extern "C" __declspec(dllimport) short Diag_ManualStart();										// �˻����.
extern "C" __declspec(dllimport) short Diag_ManualStop();										// �˻� ����.
extern "C" __declspec(dllimport) short Get_UsbSerial(unsigned int product_id, char * serial);	// Get Usb Serial 2018.09.05 Added. 
extern "C" __declspec(dllimport) short Open_Device_UsbSerial(unsigned int product_id, char * serial);	// Open by USB serial 2020.01.27 Added. 



