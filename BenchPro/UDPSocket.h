#pragma once

// UDPSocket command target

class UDPSocket : public CSocket
{
public:
	UDPSocket();
	virtual ~UDPSocket();
	virtual void OnReceive(int nErrorCode);
	CDialog* m_pDlg;
	//CEvent m_Event;
};


