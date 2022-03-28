// FilterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Sniffer.h"
#include "FilterDlg.h"


// CFilterDlg dialog

IMPLEMENT_DYNAMIC(CFilterDlg, CDialog)

CFilterDlg::CFilterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFilterDlg::IDD, pParent)
	, HasNewFilter(FALSE)
	, LastSel(0)
{

}

CFilterDlg::~CFilterDlg()
{
}

void CFilterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_filterList);
	DDX_Control(pDX, IDC_EDIT1, m_filterName);
	DDX_Control(pDX, IDC_EDIT2, m_filterString);
}


BEGIN_MESSAGE_MAP(CFilterDlg, CDialog)
	//ON_LBN_SELCHANGE(IDC_LIST1, &CFilterDlg::OnLbnSelchangeList1)
	ON_LBN_SELCHANGE(IDC_LIST1, &CFilterDlg::OnLbnSelchangeList1)
	ON_BN_CLICKED(IDC_BUTTON4, &CFilterDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON3, &CFilterDlg::OnBnClickedButton3)
	ON_EN_CHANGE(IDC_EDIT2, &CFilterDlg::OnEnChangeEdit2)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON2, &CFilterDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CFilterDlg::OnBnClickedButton1)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CFilterDlg message handlers
void CFilterDlg::OnInitADOConn()
{
	::CoInitialize(NULL);
	try
	{
		m_pConnection.CreateInstance("ADODB.Connection");
		_bstr_t strConnect = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=filter.mdb";//Home.mdb放在工程目录下   
		m_pConnection->Open(strConnect, "", "", adModeUnknown);

	}
	catch (_com_error e)
	{
		AfxMessageBox(_T("数据库filter.mdb打开失败！"));
	}
}
void CFilterDlg::ExitConnect()
{
	if (m_pRecordset != NULL)
		m_pRecordset->Close();
	m_pConnection->Close();
	::CoUninitialize();
}
BOOL CFilterDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	HasNewFilter = FALSE;
	LastSel = -1;
	hbrush = CreateSolidBrush(RGB(255, 255, 255));
	this->OnInitADOConn();//连接access数据库
	this->ReadFilter();//读取数据库中的filter sample
	return TRUE;  // return TRUE unless you set the focus to a control

}

void CFilterDlg::ReadFilter(void)
{
	_variant_t vFilterName, vFilterString;
	m_pRecordset.CreateInstance("ADODB.Recordset");
	m_pRecordset->Open("SELECT * FROM Filter ORDER BY num", _variant_t((IDispatch*)m_pConnection, true), adOpenStatic, adLockOptimistic, adCmdText);
	m_pRecordset->MoveFirst();
	while (!m_pRecordset->adoEOF)
	{
		vFilterName = m_pRecordset->GetCollect(_variant_t((long)0));
		vFilterString = m_pRecordset->GetCollect(_variant_t((long)1));
		m_filterList.InsertString(m_filterList.GetCount(), (LPCTSTR)(_bstr_t)vFilterName);

		m_pRecordset->MoveNext();
	}
}