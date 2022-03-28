// SnifferDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Sniffer.h"
#include "SnifferDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CSnifferDlg 对话框

CSnifferDlg::CSnifferDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSnifferDlg::IDD, pParent)

{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSnifferDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_devComboBox);
	DDX_Control(pDX, IDC_LIST2, m_List);
	DDX_Control(pDX, IDC_BUTTON3, m_saveBtn);
	DDX_Control(pDX, IDC_EDIT1, m_packetData);
	DDX_Control(pDX, IDC_TREE1, m_InfoTree);
}

BEGIN_MESSAGE_MAP(CSnifferDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON1, &CSnifferDlg::OnBnClickedButton1)

	ON_BN_CLICKED(IDC_BUTTON2, &CSnifferDlg::OnBnClickedButton2)
	ON_WM_CLOSE()

	ON_NOTIFY(NM_CLICK, IDC_LIST2, &CSnifferDlg::OnNMClickList2)
	ON_COMMAND(ID_CAPTURE_START, &CSnifferDlg::OnCaptureStart)
	ON_COMMAND(ID_CAPTURE_STOP, &CSnifferDlg::OnCaptureStop)
	ON_COMMAND(ID_CAPTURE_INTERFACE, &CSnifferDlg::OnCaptureInterface)
	ON_BN_CLICKED(IDC_BUTTON5, &CSnifferDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON4, &CSnifferDlg::OnBnClickedButton4)

	ON_BN_CLICKED(IDC_BUTTON3, &CSnifferDlg::OnBnClickedButton3)
	//ON_BN_CLICKED(IDC_BUTTON6, &CSnifferDlg::OnBnClickedButton6)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST2, &CSnifferDlg::OnLvnItemchangedList2)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CSnifferDlg::OnCbnSelchangeCombo2)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CSnifferDlg::OnCbnSelchangeCombo1)
	ON_EN_CHANGE(IDC_EDIT1, &CSnifferDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDOK, &CSnifferDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CSnifferDlg 消息处理程序

BOOL CSnifferDlg::OnInitDialog()
{
	CDialog::OnInitDialog();


	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动执行此操作

	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	GetDlgItem(IDC_BUTTON2)->EnableWindow(FALSE);//按钮属性

	//设置ListCtrl
	m_List.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP);
	m_List.InsertColumn(0, _T("Num"), LVCFMT_LEFT, 50);
	m_List.InsertColumn(1, _T("Time"), LVCFMT_LEFT, 90);
	m_List.InsertColumn(2, _T("Source"), LVCFMT_LEFT, 120);
	m_List.InsertColumn(3, _T("Destination"), LVCFMT_LEFT, 120);
	m_List.InsertColumn(4, _T("Protocol"), LVCFMT_LEFT, 80);
	m_List.InsertColumn(5, _T("Length"), LVCFMT_LEFT, 90);

	// 获得所有网卡设备
	alldevs = myPcap.GetAllAdapter();
	for (d = alldevs; d; d = d->next)
	{

		m_devComboBox.InsertString(m_devComboBox.GetCount(), CString(d->description));
	}
	pcap_freealldevs(d);
	//InitializeCriticalSection(&CapThreadCS);//no use

	capStatus = FALSE;

	m_Font.CreateFont(15, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_SWISS | DEFAULT_PITCH, _T("DejaVu Sans Mono"));
	m_packetData.SetFont(&m_Font);
	m_InfoTree.SetFont(&m_Font);
	m_List.SetFont(&m_Font);
	return TRUE;
}

void CSnifferDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}



void CSnifferDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。

HCURSOR CSnifferDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSnifferDlg::OnSize(UINT nType, int cx, int cy)
{

	CDialog::OnSize(nType, cx, cy);


}

//控件1
void CSnifferDlg::OnBnClickedButton1()
{

	GetModuleFileName(0, FilePath, 255);
	CapFilePath = FilePath;
	CapFilePath = CapFilePath.Left(CapFilePath.ReverseFind('\\'));
	CapFilePath += "\\tmpData.CAP";//文档存储设置 
	int devnum = m_devComboBox.GetCurSel();
	if (CB_ERR == devnum)
	{
		AfxMessageBox(_T("Please select an adapter!"));
		return;
	}
	int i;
	//定位网络设备
	for (d = alldevs, i = 0; i < devnum; d = d->next, i++);
	m_List.DeleteAllItems();
	m_InfoTree.DeleteAllItems();
	this->SetDlgItemText(IDC_EDIT1, CString(""));
	GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON5)->EnableWindow(FALSE);
	capStatus = TRUE;
	hCapThread = AfxBeginThread(CapThread, (LPVOID)d);

}



UINT CapThread(LPVOID lpParameter)
{
	pcap_t *adhandle;
	pcap_if_t* devnow = (pcap_if_t*)lpParameter;
	char errbuf[PCAP_ERRBUF_SIZE + 1];
	int res;
	struct pcap_pkthdr *header;
	const u_char *pkt_data;
	int num = 0;
	CString errstring;
	u_int netmask;
	struct bpf_program fcode;

	if ((adhandle = pcap_open(devnow->name,          // 设备名
		65536,            // 65536保证能捕获到不同数据链路层上的每个数据包的全部内容
		PCAP_OPENFLAG_PROMISCUOUS,    // 混杂模式
		1000,             // 读取超时时间
		NULL,             // 远程机器验证
		errbuf            // 错误缓冲池
	)) == NULL)
	{
		errstring.Format(_T("Unable to open the adapter. %s is not supported by WinPcap"), CString(devnow->name));
		AfxMessageBox(errstring);
		pcap_freealldevs(devnow);
		return -1;
	}

	if (devnow->addresses != NULL)
		/* 获取接口第一个地址的掩码 */
		netmask = ((struct sockaddr_in *)(devnow->addresses->netmask))->sin_addr.S_un.S_addr;

	else
		/* 如果这个接口没有地址，那么我们假设这个接口在C类网络中 */
		netmask = 0xffffff;

	if (pcap_compile(adhandle, &fcode, CStringA(filterstr.GetBuffer()), 1, netmask) < 0)
	{
		errstring = CString("Unable to compile the packet filter. Check the syntax.");
		AfxMessageBox(errstring);
		/* 释放设备列表 */
		pcap_freealldevs(devnow);
		return -1;
	}

	if (pcap_setfilter(adhandle, &fcode) < 0)
	{
		errstring = CString("Unable to set the filter.Please ensure the expression is correct");
		AfxMessageBox(errstring);
		pcap_freealldevs(devnow);
		return -1;
	}

	pcap_dumper_t* dumpfile;
	dumpfile = pcap_dump_open(adhandle, CStringA(CapFilePath.GetBuffer()));
	if (NULL == dumpfile)
	{
		AfxMessageBox(_T("Can't open the dump file!"));
		return -1;
	}
	while ((res = pcap_next_ex(adhandle, &header, &pkt_data)) >= 0)
	{
		if (res == 0)
			/* 超时时间到 */
			continue;

		++num;
		time_t local_tv_sec;
		struct tm *ltime;
		char timestr[16];

		/* 将时间戳转换成可识别的格式 */
		local_tv_sec = header->ts.tv_sec;
		ltime = localtime(&local_tv_sec);
		strftime(timestr, sizeof timestr, "%H:%M:%S", ltime);
		char temp[50];
		_itoa(num, temp, 10);
		/*处理以太网首部*/
		ethernet_header *ethheader = (ethernet_header*)pkt_data;
		char protocaltype[10];
		CSnifferDlg::GetEthernetType(ethheader, protocaltype);

		TCHAR srcAddr[18];
		TCHAR desAddr[18];
		/*处理IPv4协议的类型*/
		if (CString(protocaltype) == CString("IPv4"))
		{
			/* 处理IP首部*/
			ip_header *ipheader = (ip_header *)(pkt_data + 14);
			swprintf_s(srcAddr, 16, _T("%d.%d.%d.%d"), ipheader->saddr.byte1, ipheader->saddr.byte2, ipheader->saddr.byte3, ipheader->saddr.byte4);
			swprintf_s(desAddr, 16, _T("%d.%d.%d.%d"), ipheader->daddr.byte1, ipheader->daddr.byte2, ipheader->daddr.byte3, ipheader->daddr.byte4);
			CSnifferDlg::GetIPv4Type(ipheader, protocaltype);
		}
		if (CString(protocaltype) == CString("ARP"))
		{
			u_char* tmpSrc = ethheader->srcmac;
			u_char* tmpDst = ethheader->dstmac;
			swprintf_s(srcAddr, 18, _T("%02X:%02X:%02X:%02X:%02X:%02X"), tmpSrc[0], tmpSrc[1], tmpSrc[2], tmpSrc[3], tmpSrc[4], tmpSrc[5]);
			swprintf_s(desAddr, 18, _T("%02X:%02X:%02X:%02X:%02X:%02X"), tmpDst[0], tmpDst[1], tmpDst[2], tmpDst[3], tmpDst[4], tmpDst[5]);
		}

		/*处理包长度*/
		char lenstr[10];
		_itoa(header->len, lenstr, 10);
		CSnifferDlg* 	mDlg = ((CSnifferDlg*)(AfxGetApp()->GetMainWnd()));
		int i = mDlg->m_List.InsertItem(mDlg->m_List.GetItemCount(), CString(temp));


		mDlg->m_List.SetTextBkColor(0xFFE070);
		mDlg->m_List.SetItemText(i, 0, CString(temp));
		mDlg->m_List.SetItemText(i, 1, CString(timestr));
		mDlg->m_List.SetItemText(i, 2, CString(srcAddr));
		mDlg->m_List.SetItemText(i, 3, CString(desAddr));
		mDlg->m_List.SetItemText(i, 4, CString(protocaltype));
		mDlg->m_List.SetItemText(i, 5, CString(lenstr));
		//EnterCriticalSection(&CapThreadCS);


		//LeaveCriticalSection(&CapThreadCS);
		CMyPcap::SavePacket(header, pkt_data, dumpfile);
	}

	if (res == -1) {
		CString errstr;
		errstr.Format(_T("Error reading the packets: %s\n"), CString(pcap_geterr(adhandle)));
		AfxMessageBox(errstr);
		return -1;
	}

	return 0;
}

//控件2
void CSnifferDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	if (TerminateThread(hCapThread->m_hThread, 2) == FALSE)
	{
		AfxMessageBox(_T("Stop CapThread Fail,perhaps it has stopped yet!"));
	}
	GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON5)->EnableWindow(TRUE);

	capStatus = FALSE;
}

void CSnifferDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	if (capStatus)
	{
		AfxMessageBox(_T("Please stop capture first!"));
		return;
	}
	//DeleteCriticalSection(&CapThreadCS);
	pcap_freealldevs(alldevs);
	CDialog::OnClose();
}



void CSnifferDlg::GetEthernetType(ethernet_header * e, char *typestr)
{
	u_short etype = ntohs(e->eth_type);
	switch (etype)
	{
	case XNS_IDP:
		strcpy_s(typestr, 10, ("XNS IDP"));
		break;
	case DLOG:
		strcpy_s(typestr, 10, ("DLOG"));
		break;
	case IP:
		strcpy_s(typestr, 10, ("IPv4"));
		break;
	case X75:
		strcpy_s(typestr, 10, ("X.75"));
		break;
	case NBS:
		strcpy_s(typestr, 10, ("NBS"));
		break;
	case ECMA:
		strcpy_s(typestr, 10, ("ECMA"));
		break;
	case Chaosnet:
		strcpy_s(typestr, 10, ("Chaosnet"));
		break;
	case X25L3:
		strcpy_s(typestr, 10, ("X25 L3"));
		break;
	case ARP:
		strcpy_s(typestr, 10, ("ARP"));
		break;
	case FARP:
		strcpy_s(typestr, 10, ("FARP"));
		break;
	case RFR:
		strcpy_s(typestr, 10, ("RFR"));
		break;
	case RARP:
		strcpy_s(typestr, 10, ("RARP"));
		break;
	case NNIPX:
		strcpy_s(typestr, 10, ("NNIPX"));
		break;
	case EtherTalk:
		strcpy_s(typestr, 10, ("EtherTalk"));
		break;
	case ISSE:
		strcpy_s(typestr, 10, ("ISSE"));
		break;
	case AARP:
		strcpy_s(typestr, 10, ("AAPR"));
		break;
	case EAPS:
		strcpy_s(typestr, 10, ("EAPS"));
		break;
	case IPX:
		strcpy_s(typestr, 10, ("IPX"));
		break;
	case SNMP:
		strcpy_s(typestr, 10, ("SNMP"));
		break;
	case IPv6:
		strcpy_s(typestr, 10, ("IPv6"));
		break;
	case OAM:
		strcpy_s(typestr, 10, ("OAM"));
		break;
	case PPP:
		strcpy_s(typestr, 10, ("PPP"));
		break;
	case GSMP:
		strcpy_s(typestr, 10, ("GSMP"));
		break;
	case MPLSu:
		strcpy_s(typestr, 10, ("MPLS"));
		break;
	case MPLSm:
		strcpy_s(typestr, 10, ("MPLS"));
		break;
	case PPPoEds:
		strcpy_s(typestr, 10, ("PPPoE"));
		break;
	case PPPoEss:
		strcpy_s(typestr, 10, ("PPPoE"));
		break;
	case LWAPP:
		strcpy_s(typestr, 10, ("LWAPP"));
		break;
	case LLDP:
		strcpy_s(typestr, 10, ("LLDP"));
		break;
	case EAP:
		strcpy_s(typestr, 10, ("EAP"));
		break;
	case LOOPBACK:
		strcpy_s(typestr, 10, ("LOOPBACK"));
		break;
	case VLAN:
		strcpy_s(typestr, 10, ("VLAN"));
		break;
	default:
		strcpy_s(typestr, 10, ("UNKNOW"));
		break;
	}
}

void CSnifferDlg::GetIPv4Type(ip_header* ih, char* pt)
{
	u_short iptype = ih->proto;
	switch (iptype)
	{
	case ICMP:
		strcpy_s(pt, 10, "ICMP");
		break;
	case IGMP:
		strcpy_s(pt, 10, "IGMP");
		break;
	case TCP:
		strcpy_s(pt, 10, "TCP");
		break;
	case UDP:
		strcpy_s(pt, 10, "UDP");
		break;
	case OSPF:
		strcpy_s(pt, 10, "OSPF");
		break;
	default:
		strcpy_s(pt, 10, "UNKNOW IP");
	}
}
