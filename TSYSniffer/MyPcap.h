#pragma once
#include "pcap.h"
#include "Struct.h"






class CMyPcap
{
public:
	CMyPcap(void);
	~CMyPcap(void);
	//  ȡ�����е������豸
	pcap_if_t* GetAllAdapter(void);



};


