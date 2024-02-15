#include <iostream>
#include <vector>
#include <sstream>

/*
    ============
    === EASY ===
    ============

    ===========================
    14) Longest Common Prefix
    ===========================

    ============
    Description:
    ============

    Write a function to find the longest common prefix string amongst
    an array of strings.

    If there is no common prefix, return an empty string "".

    ===========================================================
    FUNCTION: string longestCommonPrefix(vector<string>& strs);
    ===========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  strs = ["flower", "flow", "flight"]
    Output: "fl"

    --- Example 2 ---
    Input:  strs = ["dog", "racecar", "car"]
    Output: ""
    Explanation: There is no common prefix among the input stringsn.

    *** Constraints ***
    1 <= strs.length() <= 200
    0 <= strs[i].length() <= 200
    strs[i] consists of only lowercase English letters.
*/

/*
    ------------
    --- IDEA ---
    ------------

    The most logical approach.

    We MUST stop if the i-th character is out of bounds for the given word,
    therefore it doesn't matter up to which length are we going to iterate
    out 'i' variable.

    If we ever go out of bounds with the current value of i, then we must
    immediately return constructed string up to this point, not including this
    one.

    We're going to use a "String Builder" std::ostringstream in order to avoid
    constructing a new string each time we "append" a character.

    That's how strings work because of the string literals. Technically we are
    not able to "append" a character, instead we always create a new one in
    the pool of string literals and then point to that new one.

    To avoid this, we can use a "String Builder" class as affore mentioned and
    avoid this as previously mentioned.

    std::ostringstream is from <sstream> library, so make sure to include it.

*/

/* Time  Beats:   100% */
/* Space Beats: 24.98% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    std::string longestCommonPrefix(std::vector<std::string>& strs)
    {
        std::ostringstream result;

        for (int i = 0; i < strs[0].size(); i++)
        {
            for (auto& word : strs)
            {
                if (i == word.length() || word[i] != strs[0][i])
                    return result.str();
            }

            result << strs[0][i];
        }

        return result.str();
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    The big brained concept here seems to be this:

    If the array is sorted alphabetically then you can assume that the first
    element of the array and the last element of the array will have most
    different prefixes of all comparisons that could be made between strings in
    the array. If this is true, you only have to compare these two strings.

*/

/* Time  Beats:   100% */
/* Space Beats: 61.24% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(1)        */ // Depends on the sort
class Solution_2 {
public:
    std::string longestCommonPrefix(std::vector<std::string>& strs)
    {
        int n = strs.size();
        std::string result = "";

        // Sort lexicographically
        std::sort(strs.begin(), strs.end());

        std::string first = strs[0];
        std::string last  = strs[n-1];

        // Try these, it'll give you a better understanding of why this works
        // ["flower", "hat", "something", "zebra"] // Sorted
        // ["flower", "flp", "flq", "flzzz"]       // Sorted
        // ["fl", "flower", "flp", "flq", "flzzz"] // Sorted
        for(int i = 0; i < std::min(first.size(), last.size()); i++)
        {
            if(first[i] != last[i])
                return result;

            result += first[i];
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    We're going to have "chr_idx" variable which denotes number of characters
    that are the same among all strings in vectors of strings "strs".

    At the beginning it's 0 because we assume non of them are the same.

    At the beginning of the "while" loop we are checking:
        if (chr_idx == strs[0].size())

    and if it is true, then we return first chr_idx characters of strs[0]:
        return strs[0].substr(0, chr_idx);

    If that's not the case, then we need to check every two adjacent strings in
    vector of strings "strs".

    Since we've already checked if (chr_idx == strs[0].size()), we don't have
    to do it again, however, we must start out 'i' pointer from 0.

    However, now we have to keep checking, while iterating in "for" loop:
        if (chr_idx == strs[i+1].size())

    If at any point that condition is fulfilled, it's over, we must return the
    substring of any of the strings of size "chr_idx" starting from index 0.

    Or if (strs[i][chr_idx] != strs[i+1][chr_idx]) then we do the same since
    that means some two characters among the strings in vector of strings
    "strs" are NOT the same. In that case, we, also, return the substring of
    any of the stirngs of size "chr_idx" starting from index 0.

    However, if we check every two adjacent strings and no two string's chr_idx
    character differ, then we can increment "chr_idx" by one, denoting that we
    have one more common consecutive character among all of the strings.

    Note that we must return the substring at some point of our iteration in
    the "while" loop. We will never return an empty string outside the "while"
    loop. That's just so the compiler doesn't give us an error and/or warning.

*/

/* Time  Beats: 73.11% */
/* Space Beats: 35.95% */

/* Time  Complexity: O( min_len_str(strs) * n ) */
/* Space Complexity: O(1) */
class Solution_3 {
public:
    std::string longestCommonPrefix(std::vector<std::string>& strs)
    {
        int chr_idx = 0;

        while (1)
        {
            if (chr_idx == strs[0].size())
                return strs[0].substr(0, chr_idx);

            for (int i = 0; i < strs.size() - 1; i++)
            {
                if (chr_idx == strs[i+1].size() || strs[i][chr_idx] != strs[i+1][chr_idx])
                    return strs[0].substr(0, chr_idx);
            }

            chr_idx++;
        }

        return "";
    }
};


int
main()
{
    Solution   sol;
    Solution_2 sol_2;
    Solution_3 sol_3;

    /* Example 1 */
    std::vector<std::string> strs = {"flower", "flow", "flight"};

    /* Example 2 */
    // std::vector<std::string> strs = {"dog", "racecar", "car"};

    /* Example 3 */
    // std::vector<std::string> strs = {"",""};

    /* Example 4 */
    // std::vector<std::string> strs = {"c", "c"};

    /* Example 5 */
    // std::vector<std::string> strs = {"apple"};

    std::cout << "\n\t=============================";
    std::cout << "\n\t=== LONGEST COMMON PREFIX ===";
    std::cout << "\n\t=============================\n";

    /* Write Input */
    bool first = true;
    std::cout << "\n\tStrings: [";
    for (auto s: strs)
    {
        if (!first)
            std::cout << ", ";

        std::cout << "\"" << s << "\"";
        first = false;
    }
    std::cout << "]\n";

    /* Solution */
    // std::string prefix = sol.longestCommonPrefix(strs);
    std::string prefix = sol_2.longestCommonPrefix(strs);
    // std::string prefix = sol_3.longestCommonPrefix(strs);

    /* Write Output */
    std::cout << "\n\tLongest Common Prefix is: \"" << prefix << "\"\n\n";

    return 0;
}
