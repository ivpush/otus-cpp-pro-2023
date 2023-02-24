// helpers
//

bool inet_pton4 (const std::string& src, uint32_t& dst);

void print_ip (uint32_t ipAddr);

bool filter (uint32_t ip, uint32_t octet);
bool filter (uint32_t ip, uint32_t octet1, uint32_t octet2);
bool filter (uint32_t ip, uint32_t octet1, uint32_t octet2, uint32_t octet3);

bool filter_any (uint32_t ip, uint32_t octet);
