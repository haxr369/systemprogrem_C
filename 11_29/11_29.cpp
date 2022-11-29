
//server
#undef UNICODE //유니코드 끄는 것

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")         //링크할 때 추가하는 라이브러리
// #pragma comment (lib, "Mswsock.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

int __cdecl main(void)
{
    WSADATA wsaData;
    int iResult;

    SOCKET ListenSocket = INVALID_SOCKET;       //소캣 초기화
    SOCKET ClientSocket = INVALID_SOCKET;       //소캣 초기화

    struct addrinfo* result = NULL; //ip주소 이름, 포트넘버 같은 것들이 들어간다
    struct addrinfo hints;

    int iSendResult;
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;

    // winsock을 사용하기 위해 맨처음 실행해야한다.
    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));    //다이나믹 메모리 할당받음. 주소정보 입력
    hints.ai_family = AF_INET;          //ip사용한다는 뜻
    hints.ai_socktype = SOCK_STREAM;    //TCP 사용한다는 뜻, connection-oriented  사용
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;        //서버용, 잠시후 bind사용할 예정!!

    // Resolve the server address and port
    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }


    //지금부터 시작!!!! 서버용 소캣 생성
    // Create a SOCKET for the server to listen for client connections.
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol); //소캣은 TCP/IP만 사용하므로 인수는 거이 고정이다!!!
    if (ListenSocket == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    //소켓에 기다리는 포트 번호 지정
    // Setup the TCP listening socket 특정 포트넘버에서 기다리는가?
    iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    freeaddrinfo(result);
    //최대 연결 수 지정
    iResult = listen(ListenSocket, SOMAXCONN);  //소캣 받을 준비
    if (iResult == SOCKET_ERROR) {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);//에러가 났을 때 꼭 해줘야해
        WSACleanup();             //에러가 났을 때 꼭 해줘야해
        return 1;
    }


    // Accept a client socket
    // 연결 요청이 오면 새로운 소켓을 생성하여 이 소캣(ClientSocket)으로 데이터 송수신 기존 것(ListenSocket)은 제거 
    ClientSocket = accept(ListenSocket, NULL, NULL); // 요청 받을 준비중
    if (ClientSocket == INVALID_SOCKET) {  //요청이 오면 새로운 소캣 핸들을 반환함. 이 소캣을 사용해서 데이터 왔다갔다
        printf("accept failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);      // 연결 계속하려면 닫으면 안된다.
        WSACleanup();
        return 1;
    }

    // No longer need server socket
    closesocket(ListenSocket);

    // Receive until the peer shuts down the connection 데이터 교환
    do {

        iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);//file handle을 써라!! readfile, writefile을 사용해서 바꿔보자
        if (iResult > 0) {
            printf("Bytes received: %d\n", iResult);

            // Echo the buffer back to the sender
            iSendResult = send(ClientSocket, recvbuf, iResult, 0);
            if (iSendResult == SOCKET_ERROR) {
                printf("send failed with error: %d\n", WSAGetLastError());
                closesocket(ClientSocket);
                WSACleanup();
                return 1;
            }
            printf("Bytes sent: %d\n", iSendResult);
        }
        else if (iResult == 0) //클라이언트에서 close request가 올 때,
            printf("Connection closing...\n");
        else {
            printf("recv failed with error: %d\n", WSAGetLastError());
            closesocket(ClientSocket);
            WSACleanup();
            return 1;
        }

    } while (iResult > 0);  

    // shutdown the connection since we're done
    iResult = shutdown(ClientSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(ClientSocket);
        WSACleanup();
        return 1;
    }

    // cleanup
    closesocket(ClientSocket);
    WSACleanup();

    return 0;
}