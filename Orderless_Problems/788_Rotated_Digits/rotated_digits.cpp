/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    788) Rotated Digits
    ===========================

    ============
    Description:
    ============

    An integer x is a good if after rotating each digit individually by 180
    degrees, we get a valid number that is different from x. Each digit must be
    rotated - we cannot choose to leave it alone.

    A number is valid if each digit remains a digit after rotation. For example:

        + 0, 1, and 8 rotate to themselves,

        + 2 and 5 rotate to each other (in this case they are rotated in a
          different direction, in other words, 2 or 5 gets mirrored),

        + 6 and 9 rotate to each other, and

        + the rest of the numbers do not rotate to any other number and become
          invalid.

    Given an integer n, return the number of good integers in the range [1, n].

    ===================================
    FUNCTION: int rotatedDigits(int n);
    ===================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 10
    Output: 4
    Explanation: There are four good numbers in the range [1, 10] : 2, 5, 6, 9.
    Note that 1 and 10 are not good numbers, since they remain unchanged after
    rotating.

    --- Example 2 ---
    Input: n = 1
    Output: 0

    --- Example 3 ---
    Input: n = 2
    Output: 1


    *** Constraints ***
    1 <= n <= 10^4

*/

#include <cstring>
#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Brute-Force, but completely valid Solution given the Constrints of the
    problem.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  83.68% */

/* Time  Complexity: O(N * log10(N)) */
/* Space Complexity: O(1)            */
class Solution {
public:
    int rotatedDigits(int n)
    {
        int result = 0;

        /* TYPES */
        const int SELF    = 0;
        const int INVALID = 1;
        const int MIRROR  = 2;

        int digit_type[10];
        digit_type[0] = SELF;
        digit_type[1] = SELF;
        digit_type[2] = MIRROR;
        digit_type[3] = INVALID;
        digit_type[4] = INVALID;
        digit_type[5] = MIRROR;
        digit_type[6] = MIRROR;
        digit_type[7] = INVALID;
        digit_type[8] = SELF;
        digit_type[9] = MIRROR;

        for (int i = 1; i <= n; i++)
        {
            int number = i;
            bool good = false;

            while (number > 0)
            {
                int digit = number % 10;

                if (digit_type[digit] == INVALID)
                {
                    good = false;
                    break;
                }

                if (digit_type[digit] == MIRROR)
                    good = true;

                // Divide
                number /= 10;
            }

            if (good)
                result++;
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This is a classic "DigitDP" problem. This one is pretty basic, but it still
    requires thinking about it.

    Prerequisites for this problem are:
        1. Be EXTREMELY good and comfortable with all sorts of Memoization
           problems.

        2. Have a basic unerstanding of "bitmasks"(though we could've
           implemented this without using bitmasks, however the code is easier
           to read this way I think)

        3. Be aware that "DigitDP" is the in the "opposite way" of usual
           Memoizaiton problems. In Memoization problems, we usually go until
           the very and and then we use "suffixes" to compute each step as we
           unravel the Recursion's call stack. However, in "DigitDP", it's the
           opposite. We are doing a kind of Memoization indeed, but we are
           utilizing "prefixes". It's difficult to understand by just reading
           the text, you'll have to grapple with it yourself and create your
           own understanding and analogy. There's no other way around this.

           Good thing is---This is usually not asked on Interview, however this
           does come up on LeetCode contests and in Competitive Programming.

           But I would suggest everybody to learn this as it improves you
           "Memoization" skills which almost certainly come up in Interviews
           nowadays.

           It really solidifies your Memoization skills and knowledge and
           builds a new thing on top of it.


    Here is a list of recommended "Digit DP" problems:
    (The key word is "rotated" and/or "digits")

        1.    788. Rotated Digits
        2.     48. Rotate Image
        3.     61. Rotate List
        4.    189. Rotate Array
        5.    396. Rotate Function
        6.    796. Rotate String
        7.   3819. Rotate Non Negative Elements
        8.   1861. Rotating the Box
        9.   1914. Cyclically Rotating a Grid
        10.    33. Search in Rotated Sorted Array
        11.   798. Smallest Rotation with Highest Score
        12.    81. Search in Rotated Sorted Array II
        13.   153. Find Minimum in Rotated Sorted Array
        14.  1007. Minimum Domino Rotations For Equal Row
        15.   154. Find Minimum in Rotated Sorted Array II
        16.  1210. Minimum Moves to Reach Target with Rotations
        17.  1752. Check if Array Is Sorted and Rotated
        18.  1886. Determine Whether Matrix Can Be Obtained By Rotation

*/

/* Time  Beats: 100.00% */
/* Space Beats:  83.60% */

/* Time  Complexity: O(logN) */
/* Space Complexity: O(logN) */
class Solution_Digit_DP {
private:
    const int MAX_DIGITS = 6; // 1e5 contains 6 digits
    int memo[7][2][2];

    const unsigned good    = (1 << 2) | (1 << 5) | (1 << 6) | (1 << 9);
    const unsigned invalid = (1 << 3) | (1 << 4) | (1 << 7);

public:
    int rotatedDigits(int n)
    {
        string str = to_string(n);
        str = string(MAX_DIGITS - str.size(), '0') + str;

        /* Memset */
        memset(memo, -1, sizeof(memo));

        return solve(0, false, true, str);
    }

private:
    int solve (int i, bool is_prefix_num_good, bool is_tight, string& str)
    {
        const int N = str.size();

        if (i == N)
            return is_prefix_num_good;

        if (memo[i][is_prefix_num_good][is_tight] != -1)
            return memo[i][is_prefix_num_good][is_tight];

        int result = 0;
        int limit = is_tight ? (str[i] - '0') : 9;

        for (int d = 0; d <= limit; d++)
        {
            if ((1 << d) & invalid) // Invalid digit, i.e. {3, 4, 7}
                continue;

            bool next_is_tight = is_tight & (d == limit);

            if ((1 << d) & good) // Good digit, i.e. {2, 5, 6, 9}
            {
                result += solve(i+1, true              , next_is_tight, str);
            }
            else // Neutral digit, i.e. {0, 1, 8}
            {
                result += solve(i+1, is_prefix_num_good, next_is_tight, str);
            }
        }

        return memo[i][is_prefix_num_good][is_tight] = result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same as above, however this one does NOT use Bitmasking. Maybe this one is
    a bit easier if you're just getting in to "Digit DP", but if you're trying
    to do "Digit DP" without knowing basic "Bitmasking", then I'd highly advise
    you first go and fill that gap and only then come back here.

    However, it's usually beneficial to see multiple variants.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  65.78% */

/* Time  Complexity: O(logN) */
/* Space Complexity: O(logN) */
class Solution_Digit_DP_without_Bitmasking {
private:
    const int MAX_DIGITS = 6; // 1e5 contains 6 digits
    int memo[7][2][2];

public:
    int rotatedDigits(int n)
    {
        string str = to_string(n);
        str = string(MAX_DIGITS - str.size(), '0') + str;

        /* Memset */
        memset(memo, -1, sizeof(memo));

        return solve(0, false, true, str);
    }

private:
    int solve (int i, bool is_prefix_num_good, bool is_tight, string& str)
    {
        const int N = str.size();

        if (i == N)
            return is_prefix_num_good;

        if (memo[i][is_prefix_num_good][is_tight] != -1)
            return memo[i][is_prefix_num_good][is_tight];

        int result = 0;
        int limit = is_tight ? (str[i] - '0') : 9;

        for (int d = 0; d <= limit; d++)
        {
            bool next_is_tight = is_tight & (d == limit);

            switch (d)
            {
                case 3: case 4: case 7:
                    continue;

                case 2: case 5: case 6: case 9:
                    result += solve(i + 1, true              , next_is_tight, str);
                    break;

                case 0: case 1: case 8:
                    result += solve(i + 1, is_prefix_num_good, next_is_tight, str);
                    break;
            }
        }

        return memo[i][is_prefix_num_good][is_tight] = result;
    }
};
