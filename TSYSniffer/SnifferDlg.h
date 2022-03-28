// SnifferDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "MyPcap.h"
#include "FilterDlg.h"




static UINT CapThread(LPVOID lpParameter);
static UINT ReadDumpThread(LPVOID lpParameter);
static UINT LoadThread(LPVOID lpParameter);



static wchar_t FilePath[256];//程序运行路径
static CString CapFilePath;//临时抓包文件路径
static CString filterstr;


class CSnifferDlg : public CDialog
{
	// 构造
public:
	CSnifferDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SNIFFER_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
	static void GetEthernetType(ethernet_header * e, char *typestr);//获得以太网类型
	static void GetIPv4Type(ip_header* ih, char* pt);//IP类型



};


