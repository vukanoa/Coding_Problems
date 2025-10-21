/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    811) Subdomain Visit Count
    ===========================

    ============
    Description:
    ============

    A website domain "discuss.leetcode.com" consists of various subdomains.
    At the top level, we have "com", at the next level, we have "leetcode.com"
    and at the lowest level, "discuss.leetcode.com". When we visit a domain
    like "discuss.leetcode.com", we will also visit the parent domains
    "leetcode.com" and "com" implicitly.

    A count-paired domain is a domain that has one of the two formats
    "rep d1.d2.d3" or "rep d1.d2" where rep is the number of visits to the
    domain and d1.d2.d3 is the domain itself.

        + For example, "9001 discuss.leetcode.com" is a count-paired domain
          that indicates that discuss.leetcode.com was visited 9001 times.

    Given an array of count-paired domains cpdomains, return an array of the
    count-paired domains of each subdomain in the input. You may return the
    answer in any order.

    ====================================================================
    FUNCTION: vector<string> subdomainVisits(vector<string>& cpdomains);
    ====================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: cpdomains = ["9001 discuss.leetcode.com"]
    Output: ["9001 leetcode.com","9001 discuss.leetcode.com","9001 com"]
    Explanation: We only have one website domain: "discuss.leetcode.com".
    As discussed above, the subdomain "leetcode.com" and "com" will also be
    visited. So they will all be visited 9001 times.

    --- Example 2 ---
    Input: cpdomains = ["900 google.mail.com", "50 yahoo.com", "1 intel.mail.com", "5 wiki.org"]
    Output: ["901 mail.com","50 yahoo.com","900 google.mail.com","5 wiki.org","5 org","1 intel.mail.com","951 com"]
    Explanation: We will visit "google.mail.com" 900 times, "yahoo.com" 50 times, "intel.mail.com" once and "wiki.org" 5 times.
    For the subdomains, we will visit "mail.com" 900 + 1 = 901 times, "com" 900 + 50 + 1 = 951 times, and "org" 5 times.


    *** Constraints ***
    1 <= cpdomain.length <= 100
    1 <= cpdomain[i].length <= 100
    cpdomain[i] follows either the "repi d1i.d2i.d3i" format or the "repi d1i.d2i" format.
    repi is an integer in the range [1, 104].
    d1i, d2i, and d3i consist of lowercase English letters.

*/

#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO
    Almost a "Simulation problem".

*/

/* Time  Beats: 39.31% */
/* Space Beats: 53.62% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    vector<string> subdomainVisits(vector<string>& cpdomains)
    {
        const int N = cpdomains.size();
        unordered_map<string, int> counter;

        for (const auto& str : cpdomains)
        {
            int idx_whitespace = str.find(' ');
            int repeat = stoi(str.substr(0, idx_whitespace));

            int idx_first_dot = str.find('.');
            string full_domain = str.substr(idx_whitespace + 1); // Until the end
            const int SIZE = full_domain.size();

            for (int i = 0; i < SIZE; i++) // Taking care of SUBDOMAINS
            {
                if (full_domain[i] == '.')
                    counter[full_domain.substr(i + 1)] += repeat;
            }
            counter[full_domain] += repeat; // Taking care of full_domain itself
        }

        vector<string> result;
        for (const auto& entry : counter)
        {
            const string& domain_str = entry.first;
            const int&    frequency  = entry.second;

            string correct_format = to_string(frequency) + " " + domain_str;
            result.push_back(correct_format);
        }

        return result;
    }
};
