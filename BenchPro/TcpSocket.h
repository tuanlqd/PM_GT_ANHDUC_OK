#pragma once
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <thread>

#include"MSG_Qeueu.h"
using namespace std;

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#define DEFAULT_BUFLEN 128
#define DEFAULT_PORT "81"
#define DEFAULT_PORT_PHI "1234"

#define IDThanh 1
#define IDPhi   2
// A callable object
class SocketTCP {
public:
    WSADATA wsaData;
    SOCKET ConnectSocket = INVALID_SOCKET;
    struct addrinfo* result = NULL,
        * ptr = NULL,
        hints;
    const char* sendbuf = "this is a test\n";
    const char* sendbufPhi = "aDuc\n";
    //const char* sendbuf = "admin\n";
    //const char* sendbuf = "user\n";
    //const char* sendbuf = "off\n";

    char recvbuf[DEFAULT_BUFLEN];
    int iResult;
    int recvbuflen = DEFAULT_BUFLEN;
    MSG_Queue* rec_mq = NULL;
    MSG_Queue* send_mq = NULL;

    int idUser = 0;   //=1 -> Thanh; =2->Phi
    
    int *pflagThConnected;
    int *pFlagPhConnected;

    //int* pkillThread;
public:
    SocketTCP(MSG_Queue* rec_mq, MSG_Queue* send_mq) {
        this->rec_mq = rec_mq;
        this->send_mq = send_mq;
    }
    //--------- to Thanh ---------------------
    int TCP_init() {
        iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
        if (iResult != 0) {
            printf("WSAStartup failed with error: %d\n", iResult);
            return 1;
        }
        idUser = 1;
        ZeroMemory(&hints, sizeof(hints));
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;

        // Resolve the server address and port
        //iResult = getaddrinfo(argv[1], DEFAULT_PORT, &hints, &result);
        iResult = getaddrinfo("localhost", DEFAULT_PORT, &hints, &result);
       // iResult = getaddrinfo("192.168.3.108", DEFAULT_PORT, &hints, &result);

        if (iResult != 0) {
            printf("getaddrinfo failed with error: %d\n", iResult);
            WSACleanup();
            return 1;
        }
        return 0;
    }
    //-----------------------------------------------
    int TCP_initPhi() {
        iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
        if (iResult != 0) {
            printf("WSAStartup failed with error: %d\n", iResult);
            return 1;
        }
        idUser = 2;
        ZeroMemory(&hints, sizeof(hints));
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;

        // Resolve the server address and port
       //iResult = getaddrinfo("192.168.3.104", DEFAULT_PORT_PHI, &hints, &result);
       iResult = getaddrinfo("localhost", DEFAULT_PORT_PHI, &hints, &result);
       //iResult = getaddrinfo("localhost", "81", &hints, &result);  // test my server
        if (iResult != 0) {
            printf("getaddrinfo failed with error: %d\n", iResult);
            WSACleanup();
            return 1;
        }
        return 0;
    }
    //-------------------------------------------
    int TCP_connect() {
        // Attempt to connect to an address until one succeeds
        for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {
            // Create a SOCKET for connecting to server
            ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
            if (ConnectSocket == INVALID_SOCKET) {
                printf("socket failed with error: %ld\n", WSAGetLastError());
                WSACleanup();
                return 1;
            }

            // Connect to server.
            iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
            if (iResult == SOCKET_ERROR) {
                closesocket(ConnectSocket);
                ConnectSocket = INVALID_SOCKET;
                continue;
            }
            break;
        }

        freeaddrinfo(result);
        if (ConnectSocket == INVALID_SOCKET) {
            printf("Unable to connect to server!\n");
            WSACleanup();
            return 1;
        }
        return 0;
    }

    int TCP_send(const char* msg) {
        // Send an initial buffer
        iResult = send(ConnectSocket, msg, (int)strlen(msg), 0);
        if (iResult == SOCKET_ERROR) {
            printf("send failed with error: %d\n", WSAGetLastError());
            closesocket(ConnectSocket);
            WSACleanup();
            return 1;
        }

        printf("Bytes Sent: %ld\n", iResult);
        return 0;
    }
    
    void TCP_send_message() {
        // Send an initial buffer
        while (true) {
            //if (*pkillThread == 1) return;
            if (!send_mq->isEmty()) {
                cout << "your send message begin" << endl;
                TCP_send(send_mq->readMsg());
                cout << "your send message end" << endl;
            }
        }
        //while (true) {
        //    Sleep(1000);
        //}
    }
    int TCP_shutdown() {
        // shutdown the connection since no more data will be sent
        iResult = shutdown(ConnectSocket, SD_SEND);
        if (iResult == SOCKET_ERROR) {
            printf("shutdown failed with error: %d\n", WSAGetLastError());
            closesocket(ConnectSocket);
            WSACleanup();
            return 1;
        }
        return 0;
    }
   
    void TCP_receive() {
        // Receive until the peer closes the connection   
        //AfxMessageBox(_T("TCP_receive"));
       
        do {
            iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
            if (iResult > 0) {
                //AfxMessageBox(_T("Phi nhan Mess"));
                if (idUser == IDThanh) 
                    *pflagThConnected = 1;
                if (idUser == IDPhi) 
                    *pFlagPhConnected = 1;
               //printf("Bytes received: %d\n", iResult);
                //cout << recvbuf << endl;
                rec_mq->addMsg(recvbuf);
                if (idUser == IDPhi) {
                    if (recvbuf[0] == 'h' && recvbuf[1] == 'e' && recvbuf[2] == 'l') TCP_send("aDuc\n");
                    //if (recvbuf[0] == 's' && recvbuf[1] == 't' && recvbuf[2] == 'a') TCP_send("status 1\n"); // get status hard connect
                }
            }

            else if (iResult == 0) {
                //printf("Connection closed\n");
                AfxMessageBox(_T("Connection closed"));
            }
            else {
                //AfxMessageBox(_T("Disconnect"));
                Sleep(1000);
                if (idUser == IDThanh) 
                    *pflagThConnected = 0;
                if (idUser == IDPhi) 
                    *pFlagPhConnected = 0;
                
                int nresult = WSAGetLastError();
                printf("recv failed with error: %d\n", WSAGetLastError());
                //WSACleanup();
            }

        } while  (iResult > 0);// (1);// (iResult > 0);
    }

    void TCP_send_receive() {

        // Receive until the peer closes the connection   
        thread t3(&SocketTCP::TCP_receive, this);
        TCP_send_message();
    }

    void closeConnection() {
        closesocket(ConnectSocket);
    }

    int createTCP() {
        TCP_init();
        TCP_connect();
        TCP_send(sendbuf);
        //thread t3(&SocketTCP::TCP_send1, SocketTCP(rec_mq,send_mq));
        //t3.join();
        //TCP_shutdown();        
        TCP_send_receive();
        closeConnection();
        WSACleanup();
        return 1;
    }

    int createTCPPhi() {
        TCP_initPhi();
        TCP_connect();
        TCP_send(sendbufPhi);
        //thread t3(&SocketTCP::TCP_send1, SocketTCP(rec_mq,send_mq));
        //t3.join();
        //TCP_shutdown();        
        // 
        TCP_send_receive();
        closeConnection();
        WSACleanup();
        return 1;
    }

};
// your application here