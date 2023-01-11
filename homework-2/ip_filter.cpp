#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "lib.h"

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
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
    try
    {
//      std::vector<std::vector<std::string> > ip_pool;
        std::vector<uint32_t> ip_pool;       // the pool of ip addresses
        uint32_t              tAddr;         // ipv4 address as uint32_t
        

        for(std::string line; std::getline(std::cin, line);)    // get addresses from standard input
        {
            std::vector<std::string> v = split(line, '\t');
            if (v.size() != 3)
            {
                throw std::runtime_error {"Wrong file format"};
            }
            if ( inet_pton4 (v.at(0), tAddr))   // get ipv4 address
                ip_pool.push_back(tAddr);       // put it into pool
        }

        // sort pool reverse lexicographically
        std::sort (ip_pool.begin(), ip_pool.end(), std::greater<uint32_t>());

        for (auto ip : ip_pool)
        {
            print_ip (ip);
            std::cout << std::endl;
        }

        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // filter by first byte and output
        // ip = filter(1)
        for (auto ip : ip_pool)
        {
            if (filter (ip, 1 ))
            {
                print_ip (ip);
                std::cout << std::endl;
            }
        }

        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

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

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

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

        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
