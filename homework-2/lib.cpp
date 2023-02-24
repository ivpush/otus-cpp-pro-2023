// 
// some functions 
//

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

//
// convert ipv4 address from string to uint32_t
// inet_pton4 (src, dst)
//    src - input  - string to convert from
//    dst - output - uint32_t to convert to
// returns
//    true - successful conversion
//    false - otherwise
//
bool inet_pton4 (
    const std::string& src
  , uint32_t&          dst
)
{
    int nOctets;
    int octet;
	std::stringstream	ss (src);
	std::string	item;

    dst = 0;        // initially 0

    for (nOctets = 0; nOctets < 4; ++nOctets)  // read octets
    {	
	getline (ss, item, '.');
	if (item.empty())	// no octet
            return false;
	try
	{
            octet = stoi (item);
	}
	catch (const std::exception& e)
	{
	    std::cerr << "Wrong ipv4 address format: " << src << '\n';
	    return false;
	}
        if (octet < 0 || octet > 255)   // invalid value
	{
	    std::cerr << "Wrong octet value " << octet << " in ipv4 address: " << src << '\n';
            return false;
	}
        dst <<= 8; 
	dst += octet; 
    }

    return true;
}

// print out ipv4 address in form of "xx.xx.xx.xx"
//
void print_ip (uint32_t ipAddr)
{
    std::cout << ((ipAddr >> 24) & 0x0ff) << "." << ((ipAddr >> 16) & 0x0ff)  << "." << ((ipAddr >> 8) & 0x0ff) << "." << (ipAddr & 0x0ff);
}

// filters

bool filter (uint32_t ip, uint32_t octet1)
{
    return  (((ip >> 24) & 255) == octet1);
}

bool filter (uint32_t ip, uint32_t octet1, uint32_t octet2)
{
    return (((ip >> 24) & 255) == octet1
         && ((ip >> 16) & 255) == octet2);
}

bool filter (uint32_t ip, uint32_t octet1, uint32_t octet2, uint32_t octet3)
{
    return (((ip >> 24) & 255) == octet1
         && ((ip >> 16) & 255) == octet2
         && ((ip >>  8) & 255) == octet3);
}

bool filter_any (uint32_t ip, uint32_t octet)
{
    return (((ip >> 24) & 255) == octet
         || ((ip >> 16) & 255) == octet
         || ((ip >>  8) & 255) == octet
         || ( ip        & 255) == octet);
}
