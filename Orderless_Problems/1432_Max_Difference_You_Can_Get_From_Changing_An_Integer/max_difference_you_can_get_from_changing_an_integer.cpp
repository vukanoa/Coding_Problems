/*
    ==============
    === MEDIUM ===
    ==============

    =========================================================
    1432) Max Difference You Can Get From Changing an Integer
    =========================================================

    ============
    Description:
    ============

    You are given an integer num. You will apply the following steps to num two
    separate times:

        + Pick a digit x (0 <= x <= 9).

        + Pick another digit y (0 <= y <= 9). Note y can be equal to x.

        + Replace all the occurrences of x in the decimal representation of num
          by y.

    Let a and b be the two results from applying the operation to num
    independently.

    Return the max difference between a and b.

    =====
    Note: that neither a nor b may have any leading zeros, and must not be 0.
    =====

    ===============================
    FUNCTION: int maxDiff(int num);
    ===============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: num = 555
    Output: 888
    Explanation: The first time pick x = 5 and y = 9 and store the new integer
    in a.
    The second time pick x = 5 and y = 1 and store the new integer in b.
    We have now a = 999 and b = 111 and max difference = 888

    --- Example 2 ---
    Input: num = 9
    Output: 8
    Explanation: The first time pick x = 9 and y = 9 and store the new integer
    in a.
    The second time pick x = 9 and y = 1 and store the new integer in b.
    We have now a = 9 and b = 1 and max difference = 8


    *** Constraints ***
    1 <= num <= 10^8

*/

#include <algorithm>
#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  93.84% */

/* Time  Complexity: O(d) */ // Where 'd' is the number of digits in "num"
/* Space Complexity: O(d) */
class Solution {
public:
    int maxDiff(int num)
    {
        string max_num = to_string(num);
        string min_num = to_string(num);

        /* One */
        size_t idx = max_num.find_first_not_of('9');
        if (idx != string::npos)
        {
            char digit = max_num[idx];
            replace(max_num.begin(), max_num.end(), digit, '9');
        }

        /* Two */
        idx = min_num.find_first_not_of('1');
        if (idx != string::npos)
        {
            char digit = min_num[idx];

            if (digit == '0')
            {
                while (idx < min_num.size() && (min_num[idx] == '0' || min_num[idx] == '1'))
                    idx++;

                if (idx < min_num.size())
                    digit = min_num[idx];

                replace(min_num.begin(), min_num.end(), digit, '0');
            }
            else
            {
                if (idx == 0)
                    replace(min_num.begin(), min_num.end(), digit, '1');
                else
                    replace(min_num.begin(), min_num.end(), digit, '0');
            }
        }

        return stoi(max_num) - stoi(min_num);
    }
};
