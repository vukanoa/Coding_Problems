/*
    ==============
    === MEDIUM ===
    ==============

    ========================================
    2182) Construct String With Repeat Limit
    ========================================

    ============
    Description:
    ============

    You are given a string s and an integer repeatLimit. Construct a new string
    repeatLimitedString using the characters of s such that no letter appears
    more than repeatLimit times in a row. You do not have to use all characters
    from s.

    Return the lexicographically largest repeatLimitedString possible.

    A string a is lexicographically larger than a string b if in the first
    position where a and b differ, string a has a letter that appears later in
    the alphabet than the corresponding letter in b. If the first
    min(a.length,b.length) characters do not differ, then the longer string is
    the lexicographically larger one.

    ================================================================
    FUNCTION: string repeatLimitedString(string s, int repeatLimit);
    ================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "cczazcc", repeatLimit = 3
    Output: "zzcccac"
    Explanation: We use all of the characters from s to construct the repeatLimitedString "zzcccac".
    The letter 'a' appears at most 1 time in a row.
    The letter 'c' appears at most 3 times in a row.
    The letter 'z' appears at most 2 times in a row.
    Hence, no letter appears more than repeatLimit times in a row and the string is a valid repeatLimitedString.
    The string is the lexicographically largest repeatLimitedString possible so we return "zzcccac".
    Note that the string "zzcccca" is lexicographically larger but the letter 'c' appears more than 3 times in a row, so it is not a valid repeatLimitedString.


    --- Example 2 ---
    Input: s = "aababab", repeatLimit = 2
    Output: "bbabaa"
    Explanation: We use only some of the characters from s to construct the repeatLimitedString "bbabaa". 
    The letter 'a' appears at most 2 times in a row.
    The letter 'b' appears at most 2 times in a row.
    Hence, no letter appears more than repeatLimit times in a row and the string is a valid repeatLimitedString.
    The string is the lexicographically largest repeatLimitedString possible so we return "bbabaa".
    Note that the string "bbabaaa" is lexicographically larger but the letter 'a' appears more than 2 times in a row, so it is not a valid repeatLimitedString.


    *** Constraints ***
    1 <= repeatLimit <= s.length <= 10^5
    s consists of lowercase English letters.

*/

#include <string>
#include <vector>
#include <sstream>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    This problem should be solved in a natural, intuitive way. It's greedy.
    You start with 'z' and append as many as possible, then you move to the
    next one, but if 'z' is not 0, then only append 1 of that new character and
    get back to 'z'. Then do as much 'z' as possible and get to the next one.
    Again, if you are NOT done with 'z', only append one current character and
    get back to 'z'.

    Once you're finished with 'z', you're allowed to append as much as possible
    of the next character. And so on.

    There are, kind of, a lot of edge cases, so you do have to be careful. But
    the idea is not very difficult. If you read the code below, I'm sure it'll
    make sense.

*/

/* Time  Beats: 85.82% */
/* Space Beats:  7.11% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    string repeatLimitedString(string s, int repeatLimit)
    {
        ostringstream out;

        vector<int> freq(26, 0);
        
        for (const char& chr : s)
            freq[chr - 'a']++;

        int L = 25;
        int R = 25;

        while (L >= 0 && R >= 0)
        {
            if (freq[L] == 0)
            {
                if (R < L-1)
                    L = R;
                else
                    L--;

                continue;
            }

            if (L != R && freq[R] > 0)
            {
                out << (char)(L + 'a');
                freq[L]--;
                L = R;
                continue;
            }


            int times = min(repeatLimit, freq[L]);
            for (int i = 0; i < times; i++)
            {
                out << (char)(L + 'a');
                freq[L]--;
            }

            while (R >= 0 && freq[R] == 0)
                R--;

            L--;
        }
        
        return out.str();
    }
};
