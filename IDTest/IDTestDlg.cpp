
// IDTestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "IDTest.h"
#include "IDTestDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CIDTestDlg 对话框



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


// CIDTestDlg 消息处理程序

BOOL CIDTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CIDTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CIDTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CIDTestDlg::OnBnClickedOpenPort()
{

	if (!reader.Init("COM3")) {
		AfxMessageBox("打开端口失败");
		return;
	}
	AfxMessageBox("打开端口成功");

	/*
	hComm = CreateFile("com3", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, 0);
	if (hComm == INVALID_HANDLE_VALUE)
	{
	AfxMessageBox("打开串口失败");
	return;
	}

	SetupComm(hComm, 4096, 4096);

	DCB dcb;
	GetCommState(hComm, &dcb);

	dcb.DCBlength = sizeof(dcb);
	dcb.BaudRate = CBR_115200;
	dcb.StopBits = ONESTOPBIT;
	SetCommState(hComm, &dcb);

	PurgeComm(hComm, PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR | PURGE_TXABORT);//清空缓存

	COMMTIMEOUTS ct;
	ct.ReadIntervalTimeout = 0;
	ct.ReadTotalTimeoutConstant = 5000;
	ct.ReadTotalTimeoutMultiplier = 500;
	ct.WriteTotalTimeoutConstant = 5000;
	ct.WriteTotalTimeoutMultiplier = 500;


	SetCommTimeouts(hComm, &ct);//设置超时

	AfxMessageBox("打开串口成功");
	*/

}



void CIDTestDlg::OnBnClickedReadId()
{

	char data[50] = { 0 };
	int data_len = 0;

	if (!reader.ReadIDNo(data, &data_len))
	{
		AfxMessageBox("读身份证号码失败");
		return;
	}

	int len = WideCharToMultiByte(CP_ACP, 0, (LPCWCH)data, -1, NULL, 0, NULL, NULL);
	char * buf = new char[len];
	WideCharToMultiByte(CP_ACP, 0, (LPCWCH)data, -1, buf, len, NULL, NULL);

	CString msg;
	msg.Format("读身份证号码成功 %s", buf);
	AfxMessageBox(msg);


	/*

	DWORD dwToWrite = 8;
	DWORD dwWritten = 0;



	if (WriteFile(hComm, buf, dwToWrite, &dwWritten, NULL))
	{
	TRACE("写成功...\n");

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
	TRACE("读成功...\n");
	}
	else
	{
	TRACE("读失败...\n");
	}
	}
	else
	{
	TRACE("写失败...\n");
	}
	*/
}


void CIDTestDlg::OnBnClickedReadIdcard()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CIDTestDlg::OnBnClickedClosePort()
{
	// TODO: 在此添加控件通知处理程序代码
}

