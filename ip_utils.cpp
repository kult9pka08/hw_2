#include "ip_utils.h"

std::vector<std::string> ip_utils::split(const std::string &str, char d) {
	std::vector<std::string> r;
	std::size_t				 start = 0;
	std::size_t				 stop  = str.find_first_of(d);
	while (stop != std::string::npos) {
		r.push_back(str.substr(start, stop - start));

		start = stop + 1;
		stop  = str.find_first_of(d, start);
	}
	r.push_back(str.substr(start));
	return r;
}

void ip_utils::print(std::vector<std::vector<std::string>> &ip_pool, std::ostream &out) {
	for (auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip) {
		for (auto ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part) {
			if (ip_part != ip->cbegin()) {
				out << ".";
			}
			out << *ip_part;
		}
		out << std::endl;
	}
}
