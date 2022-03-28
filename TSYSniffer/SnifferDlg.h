// SnifferDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "MyPcap.h"
#include "FilterDlg.h"




static UINT CapThread(LPVOID lpParameter);
static UINT ReadDumpThread(LPVOID lpParameter);
static UINT LoadThread(LPVOID lpParameter);



static wchar_t FilePath[256];//��������·��
static CString CapFilePath;//��ʱץ���ļ�·��
static CString filterstr;


class CSnifferDlg : public CDialog
{
	// ����
public:
	CSnifferDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SNIFFER_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_devComboBox;
	pcap_if_t *alldevs;
	pcap_if_t *d;
	CListCtrl m_List;
	afx_msg void OnSize(UINT nType, int cx, int cy);//no use

	CButton m_saveBtn;
	afx_msg void OnBnClickedButton1();
	CWinThread *hCapThread;
	CMyPcap myPcap;
	afx_msg void OnBnClickedButton2();
	BOOL capStatus;
	afx_msg void OnClose();
	void ShowPacketOnList(packet* p);//packet info on listctrl
	static void GetEthernetType(ethernet_header * e, char *typestr);//�����̫������
	static void GetIPv4Type(ip_header* ih, char* pt);//IP����



};


