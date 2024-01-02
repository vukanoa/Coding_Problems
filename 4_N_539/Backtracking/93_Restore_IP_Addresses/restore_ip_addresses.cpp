#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    93) Restore IP Addresses
    ===========================

    ============
    Description:
    ============

    A valid IP address consists of exactly four integers separated by single
    dots. Each integer is between 0 and 255 (inclusive) and cannot have leading
    zeros.

        For example, "0.1.2.201" and "192.168.1.1" are valid IP addresses, but
        "0.011.255.245", "192.168.1.312" and "192.168@1.1" are invalid IP
        addresses.

    Given a string s containing only digits, return all possible valid IP
    addresses that can be formed by inserting dots into s. You are not allowed
    to reorder or remove any digits in s. You may return the valid IP addresses
    in any order.

    ======================================================
    FUNCTION: vector<string> restoreIpAddresses(string s);
    ======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "25525511135"
    Output: ["255.255.11.135","255.255.111.35"]

    --- Example 2 ---
    Input: s = "0000"
    Output: ["0.0.0.0"]

    --- Example 3 ---
    Input: s = "101023"
    Output: ["1.0.10.23","1.0.102.3","10.1.0.23","10.10.2.3","101.0.2.3"]

    *** Constraints ***
    1 <= s.length <= 20
    s consists of digits only.

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  93.56% */

/* Time  Complexity: O(2^n) */
/* Space Complexity: O(n)   */
class Solution {
public:
    std::vector<std::string> restoreIpAddresses(std::string s)
    {
        std::vector<std::string> result;
        backtrack(s, result, "", 0, 0);

        return result;
    }

    void backtrack(string& s,
                   std::vector<string>& result,
                   std::string path,
                   int index,
                   int count)
    {
        if (count > 4)
            return;

        if (count == 4 && index >= s.length())
        {
            path.pop_back();
            result.push_back(path);
            return;
        }

        for (int i = 1; i <= 3 && index + i <= s.length(); i++)
        {
            std::string num = s.substr(index, i);

            if (num[0] == '0' && i != 1)
                break;
            else if (std::stol(num) <= 255)
                backtrack(s, result, path + s.substr(index, i) + ".", index + i,count + 1);
        }
    }
};
