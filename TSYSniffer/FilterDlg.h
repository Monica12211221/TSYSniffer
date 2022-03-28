#pragma once
#include "afxwin.h"
#include "MyPcap.h"


// CFilterDlg dialog


class CFilterDlg : public CDialog
{
	DECLARE_DYNAMIC(CFilterDlg)

public:
	CFilterDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CFilterDlg();

	// Dialog Data
	enum { IDD = IDD_FILTER_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	_ConnectionPtr   m_pConnection; // ���ݿ� 
	_RecordsetPtr    m_pRecordset; // ���� 
	_CommandPtr      m_pCommand; // ��¼
	void OnInitADOConn();//�������ݿ�
	void ExitConnect();
	virtual BOOL OnInitDialog();
	void ReadFilter(void);
	CListBox m_filterList;

};


