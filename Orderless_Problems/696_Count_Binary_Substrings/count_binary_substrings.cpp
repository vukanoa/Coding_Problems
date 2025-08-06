/*
    ============
    === EASY ===
    ============

    ============================
    696) Count Binary Substrings
    ============================

    ============
    Description:
    ============

    Given a binary string s, return the number of non-empty substrings that
    have the same number of 0's and 1's, and all the 0's and all the 1's in
    these substrings are grouped consecutively.

    Substrings that occur multiple times are counted the number of times they
    occur.

    ==============================================
    FUNCTION: int countBinarySubstrings(string s);
    ==============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "00110011"
    Output: 6
    Explanation: There are 6 substrings that have equal number of consecutive
    1's and 0's: "0011", "01", "1100", "10", "0011", and "01".
    Notice that some of these substrings repeat and are counted the number of
    times they occur.
    Also, "00110011" is not a valid substring because all the 0's (and 1's) are
    not grouped together.


    --- Example 2 ---
    Input: s = "10101"
    Output: 4
    Explanation: There are 4 substrings: "10", "01", "10", "01" that have equal
                 number of consecutive 1's and 0's.


    *** Constraints ***
    1 <= s.length <= 10^5
    s[i] is either '0' or '1'.

*/

#include <bitset>
#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 11.52% */
/* Space Beats: 24.33% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    int countBinarySubstrings(string s)
    {
        const int N = s.length();
        int result = 0;

        string binary_string = bitset<32>(s).to_string();

        char curr_active_bit = s[0];
        int curr_size = 1;

        vector<int> block_size;

        for (int i = 1; i < N; i++)
        {
            if (s[i] != curr_active_bit)
            {
                block_size.push_back(curr_size);
                curr_size = 1;

                curr_active_bit = curr_active_bit == '0' ? '1' : '0';
            }
            else
                curr_size++;
        }
        block_size.push_back(curr_size);

        for (unsigned i = 0; i < block_size.size() - 1; i++)
            result += min(block_size[i], block_size[i+1]);

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  33.50% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Efficient {
public:
    int countBinarySubstrings(string s)
    {
        int result = 0;

        int curr = 1;
        int prev = 0;
        for (int i = 1; i < s.size(); i++)
        {
            if (s[i] == s[i - 1])
            {
                curr++;
            }
            else
            {
                result += min(curr, prev);
                prev = curr;
                curr = 1;
            }
        }

        return result + min(curr, prev);
    }
};
