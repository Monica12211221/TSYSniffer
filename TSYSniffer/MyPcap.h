#pragma once
#include "pcap.h"
#include "Struct.h"






class CMyPcap
{
public:
	CMyPcap(void);
	~CMyPcap(void);
	//  取得所有的网卡设备
	pcap_if_t* GetAllAdapter(void);



};


