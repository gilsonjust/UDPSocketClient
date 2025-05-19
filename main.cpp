#include <time.h>
#include "SocketClientUDP.hpp"
#include "IPv4Address.hpp"
#include "Port.hpp";

int main()
{
	/* Destination IPv4 address and port */
	IPv4Address ip("10.1.1.100"); 
	Port port(9095);

	/* Create a UDP socket client handler */
	SocketClientUDP udpSocket(ip, port);

	/* Send some data over the network */
	for (int i = 0; i < 3; i++)
	{
		Sleep(500);
		udpSocket.send("test UDP port: " + std::to_string(i));
	}
		
	/* Close socket */
	udpSocket.closeSocket();

	return EXIT_SUCCESS;
}
