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
        string result = "";

        // Sort lexicographically
        std::sort(strs.begin(), strs.end());

        std::string first = strs[0];
        std::string last  = strs[n-1];

        // What if ["flower", "hat", "something", "zebra"]
        // What if ["flower", "flp", "flq", "flzzz"]
        for(int i = 0; i < std::min(first.size(), last.size()); i++)
        {
            if(first[i] != last[i])
                return result;

            result += first[i];
        }

        return result;
    }
};


int
main()
{
    Solution   sol;
    Solution_2 sol_2;

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

    /* Write Output */
    std::cout << "\n\tLongest Common Prefix is: \"" << prefix << "\"\n\n";

    return 0;
}
