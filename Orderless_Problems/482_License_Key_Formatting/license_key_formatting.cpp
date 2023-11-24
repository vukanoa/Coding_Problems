#include <iostream>

/*
    ============
    === EASY ===
    ============

    ===========================
    482) License Key Formatting
    ===========================

    ============
    Description:
    ============

    You are given a license key represented as a string s that consists of only
    alphanumeric characters and dashes. The string is separated into n + 1
    groups by n dashes. You are also given an integer k.

    We want to reformat the string s such that each group contains exactly k
    characters, except for the first group, which could be shorter than k but
    still must contain at least one character. Furthermore, there must be a
    dash inserted between two groups, and you should convert all lowercase
    letters to uppercase.

    Return the reformatted license key.

    ========================================================
    FUNCTION: string licenseKeyFormatting(string& s, int k);
    ========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "5F3Z-2e-9-w", k = 4
    Output: "5F3Z-2E9W"
    Explanation: The string s has been split into two parts, each part has 4
    characters.  Note that the two extra dashes are not needed and can be
    removed.


    --- Example 2 ---
    Input: s = "2-5g-3-J", k = 2
    Output: "2-5G-3J"
    Explanation: The string s has been split into three parts, each part has 2
    characters except the first part as it could be shorter as mentioned above.



    *** Constraints ***
    1 <= s.length <= 10^5
    s consists of English letters, digits, and dashes '-'.
    1 <= k <= 10^4

*/

/* Time  Beats: 10.26% */
/* Space Beats:  5.02% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    std::string licenseKeyFormatting(std::string& s, int k)
    {
        std::vector<std::deque<char>> groups;

        int N = s.length();
        std::deque<char> curr_group;
        for (int i = N-1; i >= 0; i--)
        {
            if (s[i] == '-')
                continue;

            if (curr_group.size() == k)
            {
                groups.push_back(curr_group);
                curr_group.clear();
            }

            curr_group.push_front(std::toupper(s[i]));
        }
        groups.push_back(curr_group);

        std::ostringstream formatted_license;
        for (int i = groups.size() - 1; i >= 0; i--)
        {
            for (int j = 0; j < groups[i].size(); j++)
            {
                formatted_license << groups[i][j];
            }

            if (i > 0)
                formatted_license << "-";
        }

        return formatted_license.str();
    }
};




/* Time  Beats: 98.80% */
/* Space Beats: 84.61% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */ // If we don't consider the resulting string as
                             // additional memory
class Solution {
public:
    std::string licenseKeyFormatting(std::string s, int k)
    {
        int N = s.size();
        std::string result = "";

        int elements = 0;
        for (int i = N-1; i >= 0; --i)
        {
            if (s[i] == '-')
                continue;

            if (elements > 0 && elements % k == 0)
                result.push_back('-');

            result.push_back(toupper(s[i]));
            elements++;
        }

        std::reverse(result.begin(), result.end());

        return result;
    }
};




/* Time  Beats: 85.48% */
/* Space Beats: 36.90% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */ // If we don't consider the resulting string as
                             // additional memory
class Solution_String_Builder {
public:
    std::string licenseKeyFormatting(std::string s, int k)
    {
        int N = s.size();

        int elements = 0;
        std::ostringstream out;
        for (int i = N-1; i >= 0; --i)
        {
            if (s[i] == '-')
                continue;

            if (elements > 0 && elements % k == 0)
                out << "-";

            char capital = std::toupper(s[i]);
            out << capital;
            elements++;
        }

        std::string result = out.str();
        std::reverse(result.begin(), result.end());

        return result;
    }
};
