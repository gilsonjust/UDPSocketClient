#ifndef _IPV4_ADDRESS_H_
#define _IPV4_ADDRESS_H_

#include <string>
#include <vector>

#define MIN_OCTET 0
#define MAX_OCTET 255

class IPv4Address
{
public:
	IPv4Address(std::string ip)
	{
		m_isValidIP = validateIPv4(ip);
		m_ipAddr = m_isValidIP ? ip : "";
	}

	std::string getIpAddrStr() const
	{
		return m_ipAddr;
	}

	bool isValid() const
	{
		return m_isValidIP;
	}

	/* Basic IPv4 validation */
    bool validateIPv4(const std::string& ip) const
    {
		int counter = 0;
		int p1 = 0;
		int p2 = 0;
		std::vector<std::string> octets;

		for (int i = 0; i <= ip.size(); ++i)
		{
			if (ip[i] == '.' || i == ip.size())
			{
				p2 = i;
				std::string token = ip.substr(p1, p2 - p1);

				/* Empty 192..10.10 */
				if (token.empty()) 
					return false;

				counter++;
				octets.push_back(token);

				p1 = i + 1;
			}
		}

		/* Must have four octets */
		if (counter != 4) 
			return false;

		for (const std::string& part : octets)
		{
			/* Check if octet is numeric */
			for (char c : part)
			{
				if (!std::isdigit(c))
					return false;
			}

			if (part.length() > 1 && part[0] == '0') 
				return false;

			int value = std::stoi(part);
			
			/* Check basic range valus */
			if (value < MIN_OCTET || value > MAX_OCTET)
				return false;
		}

		/* Good IPv4 Address */
		return true;
	}

private:
	std::string m_ipAddr;
	bool m_isValidIP;
};

#endif