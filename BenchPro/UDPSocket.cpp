// UDPSocket.cpp : implementation file
//

#include "pch.h"
#include "BenchPro.h"
#include "UDPSocket.h"


// UDPSocket

UDPSocket::UDPSocket()
{
    m_pDlg=NULL;
}

UDPSocket::~UDPSocket()
{
}


// UDPSocket member functions


void UDPSocket::OnReceive(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
    char buff[4096];
    int nRead;
    nRead = Receive(buff, 4096);

    switch (nRead)
    {
    case 0:
        Close();
        break;
    case SOCKET_ERROR:
        if (GetLastError() != WSAEWOULDBLOCK)
        {
            Close();
            AfxMessageBox(_T("Error occurred"));
            //bool bret=m_Event.SetEvent();
        }
        break;
    default:
        buff[nRead] = _T('\0'); //terminate the string
        CString szTemp(buff);
        /*
        m_strRecv += szTemp; // m_strRecv is a CString declared
                             // in CMyAsyncSocket
        if (szTemp.CompareNoCase(_T("bye")) == 0)
        {
            ShutDown();
            s_eventDone.SetEvent();
        }
        */
    }

	CSocket::OnReceive(nErrorCode);
}
