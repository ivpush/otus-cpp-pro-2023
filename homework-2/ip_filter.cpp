#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "lib.h"

std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

int main (int argc, char const *argv[])
{
    (void)argc;
    (void)argv;

    try
    {
        std::vector<uint32_t> ip_pool;       // the pool of ip addresses
        uint32_t              tAddr;         // ipv4 address as uint32_t

        for(std::string line; std::getline(std::cin, line);)    // get addresses from standard input
        {
            std::vector<std::string> v = split(line, '\t');
            if (v.size() != 3)
            {
                throw std::runtime_error {"Wrong file format - wrong number of line sections"};
            }
            if ( inet_pton4 (v.at(0), tAddr))   // get ipv4 address
                ip_pool.push_back(tAddr);       // put it into pool
	    else
	    {
		throw std::runtime_error {"Stop processing because of wrong ipv4 address"};
            }
	}

        // sort pool reverse lexicographically
        std::sort (ip_pool.begin(), ip_pool.end(), std::greater<uint32_t>());

        for (auto ip : ip_pool)
        {
            print_ip (ip);
            std::cout << std::endl;
        }

        // filter by first byte and output
        // ip = filter(1)
        for (auto ip : ip_pool)
        {
            if (filter (ip, 1))
            {
                print_ip (ip);
                std::cout << std::endl;
            }
        }

        // filter by first and second bytes and output
        // ip = filter(46, 70)
        for (auto ip : ip_pool)
        {
            if (filter (ip, 46, 70))
            {
                print_ip (ip);
                std::cout << std::endl;
            }
        }

        // filter by any byte and output
        // ip = filter_any(46)
        for (auto ip : ip_pool)
        {
            if (filter_any (ip, 46))
            {
                print_ip (ip);
                std::cout << std::endl;
            }
        }
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
