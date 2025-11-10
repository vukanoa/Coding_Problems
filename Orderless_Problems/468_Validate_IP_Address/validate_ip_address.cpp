/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    468) Validate IP Address
    ===========================

    ============
    Description:
    ============

    Given a string queryIP, return "IPv4" if IP is a valid IPv4 address, "IPv6"
    if IP is a valid IPv6 address or "Neither" if IP is not a correct IP of any
    type.

    A valid IPv4 address is an IP in the form "x1.x2.x3.x4" where
    0 <= xi <= 255 and xi cannot contain leading zeros. For example,
    "192.168.1.1" and "192.168.1.0" are valid IPv4 addresses while
    "192.168.01.1", "192.168.1.00", and "192.168@1.1" are invalid IPv4
    addresses.

    A valid IPv6 address is an IP in the form "x1:x2:x3:x4:x5:x6:x7:x8" where:

        + 1 <= xi.length <= 4

        + xi is a hexadecimal string which may contain digits, lowercase
          English letter ('a' to 'f') and upper-case English letters
          ('A' to 'F').

        + Leading zeros are allowed in xi.

    For example, "2001:0db8:85a3:0000:0000:8a2e:0370:7334" and
    "2001:db8:85a3:0:0:8A2E:0370:7334" are valid IPv6 addresses, while
    "2001:0db8:85a3::8A2E:037j:7334" and
    "02001:0db8:85a3:0000:0000:8a2e:0370:7334" are invalid IPv6 addresses.

    ================================================
    FUNCTION: string validIPAddress(string queryIP);
    ================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: queryIP = "172.16.254.1"
    Output: "IPv4"
    Explanation: This is a valid IPv4 address, return "IPv4".

    --- Example 2 ---
    Input: queryIP = "2001:0db8:85a3:0:0:8A2E:0370:7334"
    Output: "IPv6"
    Explanation: This is a valid IPv6 address, return "IPv6".

    --- Example 3 ---
    Input: queryIP = "256.256.256.256"
    Output: "Neither"
    Explanation: This is neither a IPv4 address nor a IPv6 address.

    *** Constraints ***
    queryIP consists only of English letters, digits and the characters '.' and ':'.


*/

#include <algorithm>
#include <string>
#include <vector>
#include <sstream>
#include <cctype>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  27.53% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    string validIPAddress(string IP)
    {
        vector<string> ipv4 = split(IP, '.');
        vector<string> ipv6 = split(IP, ':');

        if (count(IP.begin(), IP.end(), '.') == 3)
        {
            for (auto& octet : ipv4)
            {
                if (is_IPv4_compatible(octet))
                    continue;
                else
                    return "Neither";
            }

            return "IPv4";
        }

        if (count(IP.begin(), IP.end(), ':') == 7)
        {
            for (auto& hextet : ipv6)
            {
                if (is_IPv6_compatible(hextet))
                    continue;
                else
                    return "Neither";
            }

            return "IPv6";
        }

        return "Neither";
    }

private:
    vector<string> split(const string& s, char delim)
    {
        vector<string> parts;
        string token;
        stringstream ss(s);

        while (getline(ss, token, delim))
            parts.push_back(token);

        // Handle trailing delimiter
        if ( ! s.empty() && s.back() == delim)
            parts.push_back(""); 

        return parts;
    }

    bool is_IPv4_compatible(const string& s)
    {
        if (s.empty() || s.size() > 3)
            return false;

        for (const char& chr : s)
        {
            if ( ! isdigit(chr))
                return false;
        }

        int val = stoi(s);
        if (to_string(val) != s)
            return false; // leading zeros check

        return val >= 0 && val <= 255;
    }

    bool is_IPv6_compatible(const string& s)
    {
        if (s.empty() || s.size() > 4)
            return false;

        for (const char& chr : s)
        {
            if ( ! isxdigit(chr))
                return false;
        }

        return true;
    }
};
