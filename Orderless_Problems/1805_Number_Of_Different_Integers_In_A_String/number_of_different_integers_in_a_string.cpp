/*
    ============
    === EASY ===
    ============

    ==============================================
    1805) Number of different integers in a String
    ==============================================

    ============
    Description:
    ============

    You are given a string word that consists of digits and lowercase English
    letters.

    You will replace every non-digit character with a space. For example,
    "a123bc34d8ef34" will become " 123  34 8  34". Notice that you are left
    with some integers that are separated by at least one space: "123", "34",
    "8", and "34".

    Return the number of different integers after performing the replacement
    operations on word.

    Two integers are considered different if their decimal representations
    without any leading zeros are different.

    ================================================
    FUNCTION: int numDifferentIntegers(string word);
    ================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: word = "a123bc34d8ef34"
    Output: 3
    Explanation: The three different integers are "123", "34", and "8". Notice
                 that "34" is only counted once.

    --- Example 2 ---
    Input: word = "leet1234code234"
    Output: 2

    --- Example 3 ---
    Input: word = "a1b01c001"
    Output: 1
    Explanation: The three integers "1", "01", and "001" all represent the same
                 integer because the leading zeros are ignored when comparing
                 their decimal values.

    *** Constraints ***
    1 <= word.length <= 1000
    word consists of digits and lowercase English letters.

*/

#include <string>
#include <unordered_set>
using namespace std;
#include <sstream>

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 13.13% */
/* Space Beats: 46.46% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    int numDifferentIntegers(string word)
    {
        const int N = word.size();
        unordered_set<string> uset_numbers;

        for (char& chr : word)
        {
            if ( ! isdigit(chr))
                chr = ' '; // Convert to <Space>
        }

        istringstream iss(word);
        string str_number;

        while (iss >> str_number)
        {
            int start = 0;

            while (start < str_number.length() && static_cast<unsigned char>(str_number[start]) == '0')
                start++;


            uset_numbers.insert(str_number.substr(start));
        }

        return uset_numbers.size();
    }
};
