
// IDTestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "IDTest.h"
#include "IDTestDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CIDTestDlg �Ի���



CIDTestDlg::CIDTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_IDTEST_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CIDTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CIDTestDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OPEN_PORT, &CIDTestDlg::OnBnClickedOpenPort)
	ON_BN_CLICKED(IDC_READ_ID, &CIDTestDlg::OnBnClickedReadId)
	ON_BN_CLICKED(IDC_READ_IDCARD, &CIDTestDlg::OnBnClickedReadIdcard)
	ON_BN_CLICKED(IDC_CLOSE_PORT, &CIDTestDlg::OnBnClickedClosePort)

	
	
END_MESSAGE_MAP()


// CIDTestDlg ��Ϣ�������

BOOL CIDTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CIDTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CIDTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CIDTestDlg::OnBnClickedOpenPort()
{

	if (!reader.Init("COM3")) {
		AfxMessageBox("�򿪶˿�ʧ��");
		return;
	}
	AfxMessageBox("�򿪶˿ڳɹ�");

	/*
	hComm = CreateFile("com3", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, 0);
	if (hComm == INVALID_HANDLE_VALUE)
	{
	AfxMessageBox("�򿪴���ʧ��");
	return;
	}

	SetupComm(hComm, 4096, 4096);

	DCB dcb;
	GetCommState(hComm, &dcb);

	dcb.DCBlength = sizeof(dcb);
	dcb.BaudRate = CBR_115200;
	dcb.StopBits = ONESTOPBIT;
	SetCommState(hComm, &dcb);

	PurgeComm(hComm, PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR | PURGE_TXABORT);//��ջ���

	COMMTIMEOUTS ct;
	ct.ReadIntervalTimeout = 0;
	ct.ReadTotalTimeoutConstant = 5000;
	ct.ReadTotalTimeoutMultiplier = 500;
	ct.WriteTotalTimeoutConstant = 5000;
	ct.WriteTotalTimeoutMultiplier = 500;


	SetCommTimeouts(hComm, &ct);//���ó�ʱ

	AfxMessageBox("�򿪴��ڳɹ�");
	*/

}



void CIDTestDlg::OnBnClickedReadId()
{

	char data[50] = { 0 };
	int data_len = 0;

	if (!reader.ReadIDNo(data, &data_len))
	{
		AfxMessageBox("�����֤����ʧ��");
		return;
	}

	int len = WideCharToMultiByte(CP_ACP, 0, (LPCWCH)data, -1, NULL, 0, NULL, NULL);
	char * buf = new char[len];
	WideCharToMultiByte(CP_ACP, 0, (LPCWCH)data, -1, buf, len, NULL, NULL);

	CString msg;
	msg.Format("�����֤����ɹ� %s", buf);
	AfxMessageBox(msg);


	/*

	DWORD dwToWrite = 8;
	DWORD dwWritten = 0;



	if (WriteFile(hComm, buf, dwToWrite, &dwWritten, NULL))
	{
	TRACE("д�ɹ�...\n");

	DWORD dwRead;


	memset(buf, 0x00, sizeof(buf));
	DWORD dwNeedRead = 38 + 5;
	if (ReadFile(hComm, buf, 1, &dwRead, NULL))
	{

	DWORD dwError;
	COMSTAT cs = { 0 };

	ClearCommError(hComm, &dwError, &cs);
	int read_len = cs.cbInQue;

	ReadFile(hComm, buf + 1, dwNeedRead-1, &dwRead, NULL);
	TRACE("���ɹ�...\n");
	}
	else
	{
	TRACE("��ʧ��...\n");
	}
	}
	else
	{
	TRACE("дʧ��...\n");
	}
	*/
}


void CIDTestDlg::OnBnClickedReadIdcard()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CIDTestDlg::OnBnClickedClosePort()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

