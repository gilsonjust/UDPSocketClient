#ifndef _PORT_HPP_
#define _PORT_HPP_

#define MAX_PORT 65535
#define MIN_PORT 0

class Port
{
public:
	Port(unsigned int port)
	{
		m_isValid = validatePort(port);
		m_port = port;
	}

	bool isValid() const
	{
		return m_isValid;
	}

	unsigned int getValue() const
	{
		return m_port;
	}

	bool validatePort(unsigned int port)
	{
		return (port > MIN_PORT && port <= MAX_PORT);
	}
private:
	unsigned int m_port;
	bool m_isValid;
};

#endif