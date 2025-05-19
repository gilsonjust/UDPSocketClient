#pragma once

#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include "IPv4Address.hpp"
#include "Port.hpp";

#pragma comment(lib, "ws2_32.lib")

#define CRLF '\n'

#ifndef SOCKET_ERROR
#define SOCKET_ERROR -1
#endif 

#ifndef SOCKET_SUCCESS
#define SOCKET_SUCCESS 1
#endif

class SocketClientUDP
{
public:
    SocketClientUDP(IPv4Address ip, Port port)
    {
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
            std::cerr << "Error to initialize winSock!" << std::endl;

        if (!ip.isValid() || !port.isValid())
            return;

        udpSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

        if (udpSocket == INVALID_SOCKET || !ip.isValid() || !port.isValid())
        {
            std::cerr << "Failed to create socket: " << WSAGetLastError() << std::endl;
            m_initialized = false;
            WSACleanup();
        }

        m_initialized = true;
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(port.getValue());
        inet_pton(AF_INET, ip.getIpAddrStr().c_str(), &serverAddr.sin_addr);
    }

    ~SocketClientUDP()
    {
        if (udpSocket != INVALID_SOCKET)
            closesocket(udpSocket);
        
        if (m_initialized)
            WSACleanup();
    }

    void closeSocket() const
    {
        closesocket(udpSocket);
        WSACleanup();
    }

    int send(std::string msg) const
    {
        if (udpSocket == INVALID_SOCKET || msg.empty())
            return SOCKET_ERROR;

        std::string msgToSend = msg;

        if (msgToSend.back() != CRLF)
            msgToSend += CRLF;

        if (sendto(udpSocket, msgToSend.c_str(), msgToSend.size(), 0, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
        {
            std::cerr << "Failed to send UDP message - Error code: " << WSAGetLastError() << std::endl;
            closeSocket();
            return SOCKET_ERROR;
        }

        return SOCKET_SUCCESS;
    }
private:
    SOCKET udpSocket = INVALID_SOCKET;
    sockaddr_in serverAddr{};
    WSADATA wsaData{};
    bool m_initialized = false;
};

