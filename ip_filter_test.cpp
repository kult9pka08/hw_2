#include "ip_utils.h"

#include <algorithm>
#include <gtest/gtest.h>

namespace ip_utils_test {
    class IpFilterTest: public ::testing::Test {
      protected:
        std::vector<std::vector<std::string>> ip_pool = {
            {"192", "168", "1", "1"},
            { "10",   "0", "0", "1"},
            { "10",  "10", "0", "1"},
            {"172",  "16", "0", "1"},
            { "46",  "70", "0", "1"},
            {  "1",   "1", "1", "1"},
            {  "1",   "1", "1", "1"},
            {  "1",   "0", "0", "1"},
            {  "1",   "0", "1", "1"},
        };
    };

    TEST_F(IpFilterTest, SortingTest) {
        std::vector<std::vector<std::string>> expected_ip_pool = {
            {"192", "168", "1", "1"},
            {"172",  "16", "0", "1"},
            { "46",  "70", "0", "1"},
            { "10",  "10", "0", "1"},
            { "10",   "0", "0", "1"},
            {  "1",   "1", "1", "1"},
            {  "1",   "1", "1", "1"},
            {  "1",   "0", "1", "1"},
            {  "1",   "0", "0", "1"},
        };
        auto sort_ip_pool = [&]() {
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
        EXPECT_EQ(sort_ip_pool(), expected_ip_pool);
    }

    TEST_F(IpFilterTest, FilterFirstByteTest) {
        std::vector<std::vector<std::string>> expected_ip_pool = {
            {"1", "1", "1", "1"},
            {"1", "1", "1", "1"},
            {"1", "0", "0", "1"},
            {"1", "0", "1", "1"},
        };
        std::vector<std::vector<std::string>> expected_ip_pool_2 = {
            {"10",  "0", "0", "1"},
            {"10", "10", "0", "1"},
        };

        auto filter = [&](int first_byte, int second_byte = -1) {
            std::vector<std::vector<std::string>> result;
            std::copy_if(ip_pool.cbegin(), ip_pool.cend(), std::back_inserter(result), [first_byte, second_byte](const auto &ip) {
                if (second_byte != -1) {
                    return std::stoi(ip[0]) == first_byte && std::stoi(ip[1]) == second_byte;
                }
                return std::stoi(ip[0]) == first_byte;
            });
            return result;
        };

        EXPECT_EQ(filter(1), expected_ip_pool);
        EXPECT_EQ(filter(10), expected_ip_pool_2);
    }

    TEST_F(IpFilterTest, FilterFirstAndSecondByteTest) {
        std::vector<std::vector<std::string>> expected_ip_pool = {
            {"1", "1", "1", "1"},
            {"1", "1", "1", "1"},
        };
        std::vector<std::vector<std::string>> expected_ip_pool_2 = {
            {"10", "10", "0", "1"},
        };

        auto filter = [&](int first_byte, int second_byte = -1) {
            std::vector<std::vector<std::string>> result;
            std::copy_if(ip_pool.cbegin(), ip_pool.cend(), std::back_inserter(result), [first_byte, second_byte](const auto &ip) {
                if (second_byte != -1) {
                    return std::stoi(ip[0]) == first_byte && std::stoi(ip[1]) == second_byte;
                }
                return std::stoi(ip[0]) == first_byte;
            });
            return result;
        };

        EXPECT_EQ(filter(1, 1), expected_ip_pool);
        EXPECT_EQ(filter(10, 10), expected_ip_pool_2);
    }

    TEST_F(IpFilterTest, FilterAnyByteTest) {
        std::vector<std::vector<std::string>> expected_ip_pool = {
            {"10",  "0", "0", "1"},
            {"10", "10", "0", "1"},
        };
        std::vector<std::vector<std::string>> expected_ip_pool_2 = {
            { "10",  "0", "0", "1"},
            { "10", "10", "0", "1"},
            {"172", "16", "0", "1"},
            { "46", "70", "0", "1"},
            {  "1",  "0", "0", "1"},
            {  "1",  "0", "1", "1"},
        };
        auto filter_any = [&](int byte) {
            std::vector<std::vector<std::string>> result;
            std::copy_if(ip_pool.cbegin(), ip_pool.cend(), std::back_inserter(result), [byte](const auto &ip) {
                return std::any_of(ip.cbegin(), ip.cend(), [byte](const auto &ip_part) { return std::stoi(ip_part) == byte; });
            });
            return result;
        };

        EXPECT_EQ(filter_any(10), expected_ip_pool);
		EXPECT_EQ(filter_any(0), expected_ip_pool_2);
    }
}   // namespace ip_utils_test
