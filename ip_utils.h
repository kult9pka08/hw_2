#pragma once
#include <iostream>
#include <string>
#include <vector>

namespace ip_utils {
	// ("",  '.') -> [""]
	// ("11", '.') -> ["11"]
	// ("..", '.') -> ["", "", ""]
	// ("11.", '.') -> ["11", ""]
	// (".11", '.') -> ["", "11"]
	// ("11.22", '.') -> ["11", "22"]
	std::vector<std::string> split(const std::string &str, char d);
	void					 print(std::vector<std::vector<std::string>> &ip_pool, std::ostream &out);
}	// namespace ip_utils
