
// IDTestDlg.h : ͷ�ļ�
//

#pragma once

#include "IDReader.h"

// CIDTestDlg �Ի���
class CIDTestDlg : public CDialogEx
{
// ����
public:
	CIDTestDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IDTEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	

private:
	

	
	IDReader reader;
	

public:
	afx_msg void OnBnClickedLoadDll();
	afx_msg void OnBnClickedReadId();
	
	

	
};
