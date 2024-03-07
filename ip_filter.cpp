#include "ip_utils.h"

#include <algorithm>
#include <cassert>
#include <cstdlib>

int main(int, char **) {
    try {
        std::vector<std::vector<std::string>> ip_pool;

        for (std::string line; std::getline(std::cin, line);) {
            auto v = ip_utils::split(line, '\t');
            ip_pool.push_back(ip_utils::split(v.at(0), '.'));
        }

        auto sort_ip_pool = [&ip_pool]() {
            std::sort(ip_pool.begin(), ip_pool.end(), [](const auto &lhs, const auto &rhs) {
                for (std::size_t i = 0; i < std::min(lhs.size(), rhs.size()); ++i) {
                    if (std::stoi(lhs[i]) == std::stoi(rhs[i])) {
                        continue;
                    }
                    return std::stoi(lhs[i]) > std::stoi(rhs[i]);
                }
                return false;
            });
            return ip_pool;
        };

        ip_pool = sort_ip_pool();

        ip_utils::print(ip_pool, std::cout);

        auto filter = [&ip_pool](int first_byte, int second_byte = -1) {
            std::vector<std::vector<std::string>> result;
            std::copy_if(ip_pool.cbegin(), ip_pool.cend(), std::back_inserter(result), [first_byte, second_byte](const auto &ip) {
                if (second_byte != -1) {
                    return std::stoi(ip[0]) == first_byte && std::stoi(ip[1]) == second_byte;
                }
                return std::stoi(ip[0]) == first_byte;
            });
            return result;
        };

        auto filter_any = [&ip_pool](int byte) {
            std::vector<std::vector<std::string>> result;
            std::copy_if(ip_pool.cbegin(), ip_pool.cend(), std::back_inserter(result), [byte](const auto &ip) {
                return std::any_of(ip.cbegin(), ip.cend(), [byte](const auto &ip_part) { return std::stoi(ip_part) == byte; });
            });
            return result;
        };

        std::vector<std::vector<std::string>> ip;
        ip = filter(1);
        ip_utils::print(ip, std::cout);

        ip = filter(46, 70);
        ip_utils::print(ip, std::cout);

        ip = filter_any(46);
        ip_utils::print(ip, std::cout);

    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
