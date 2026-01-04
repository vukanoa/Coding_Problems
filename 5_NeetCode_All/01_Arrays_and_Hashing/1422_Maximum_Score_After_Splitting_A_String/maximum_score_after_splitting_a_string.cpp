/*
    ============
    === EASY ===
    ============

    ============================================
    1422) Maximum Score After Splitting A String
    ============================================

    ============
    Description:
    ============

    Given a string s of zeros and ones, return the maximum score after
    splitting the string into two non-empty substrings (i.e. left substring and
    right substring).

    The score after splitting a string is the number of zeros in the left
    substring plus the number of ones in the right substring.

    =================================
    FUNCTION: int maxScore(string s);
    =================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "011101"
    Output: 5
    Explanation:
    All possible ways of splitting s into two non-empty substrings are:
    left = "0" and right = "11101", score = 1 + 4 = 5
    left = "01" and right = "1101", score = 1 + 3 = 4
    left = "011" and right = "101", score = 1 + 2 = 3
    left = "0111" and right = "01", score = 1 + 1 = 2
    left = "01110" and right = "1", score = 2 + 1 = 3

    --- Example 2 ---
    Input: s = "00111"
    Output: 5
    Explanation: When left = "00" and right = "111", we get the maximum
                 score = 2 + 3 = 5

    --- Example 3 ---
    Input: s = "1111"
    Output: 3


    *** Constraints ***
    2 <= s.length <= 500
    The string s consists of characters '0' and '1' only.

*/

#include <climits>
#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    The only important thing here is to "notice" that you need to "add":

        left_zeroes[i] and right_ones[i+1]

    that is--Index of right_ones has to be larger by 1. If you are going to
    split it on index i, then you're not allow to count both 0s to the left
    from that index and number of 1s to the right, therefore, number of 1s is
    counted from the next elementi, i.e. i+1.

    Other than that, it's obvious that we have to precalculate number of 0s to
    the left and number of 1s to the right.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  15.33% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    int maxScore(string s)
    {
        const int N = s.length();
        int result = INT_MIN;

        vector<int> left_zeroes(N, 0);
        vector<int> right_ones(N, 0);

        left_zeroes[0] = s[0] == '0' ? 1 : 0;
        for (int i = 1; i < N; i++)
        {
            left_zeroes[i] = left_zeroes[i-1];

            if (s[i] == '0')
                left_zeroes[i]++;
        }

        right_ones[N-1] = s[N-1] == '1' ? 1 : 0;
        for (int i = N-2; i >= 0; i--)
        {
            right_ones[i] = right_ones[i+1];

            if (s[i] == '1')
                right_ones[i]++;
        }

        for (int i = 0; i < N-1; i++)
            result = max(result, left_zeroes[i] + right_ones[i+1]);

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Here, we can see that we don't actually need to allocate an entire vector,
    instead we can simply use one variable per character(i.e. one for 0s and
    one for 1s).

    We count the total number of 1s and then--In another loop--we begin from 0
    and iterate up until N-1 for the same reason as above.

    However, because we do NOT have a vector now, we must use our variables to
    have a correct idea how many 0s is from this index to the left and how many
    is from the index right to this, to the right.

    We check if current number of left_zeroes and current number of right_ones,
    AFTER the addition/subtraction is the maximum.

    That's it.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  38.48% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Optimized {
public:
    int maxScore(string s)
    {
        int result = INT_MIN;

        int left_zeroes = 0;
        int right_ones  = 0;

        for (const char& chr : s)
        {
            if (chr == '1')
                right_ones++;
        }

        for (int i = 0; i < s.length() - 1; i++)
        {
            if (s[i] == '0')
                left_zeroes++;
            else
                right_ones--;

            result = max(result, left_zeroes + right_ones);
        }

        return result;
    }
};
