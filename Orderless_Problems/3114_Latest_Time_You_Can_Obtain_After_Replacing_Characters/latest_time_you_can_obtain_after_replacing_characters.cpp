/*
    ============
    === EASY ===
    ============

    ===========================================================
    3114) Latest Time You Can Obtain After Replacing Characters
    ===========================================================

    ============
    Description:
    ============

    You are given a string s representing a 12-hour format time where some of
    the digits (possibly none) are replaced with a "?".

    12-hour times are formatted as "HH:MM", where HH is between 00 and 11, and
    MM is between 00 and 59. The earliest 12-hour time is 00:00, and the latest
    is 11:59.

    You have to replace all the "?" characters in s with digits such that the
    time we obtain by the resulting string is a valid 12-hour format time and
    is the latest possible.

    Return the resulting string.

    ==========================================
    FUNCTION: string findLatestTime(string s);
    ==========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "1?:?4"
    Output: "11:54"
    Explanation: The latest 12-hour format time we can achieve by replacing "?"
    characters is "11:54".

    --- Example 2 ---
    Input: s = "0?:5?"
    Output: "09:59"
    Explanation: The latest 12-hour format time we can achieve by replacing "?"
    characters is "09:59".


    *** Constraints ***
    s.length == 5
    s[2] is equal to the character ":".
    All characters except s[2] are digits or "?" characters.
    The input is generated such that there is at least one time between "00:00"
    and "11:59" that you can obtain after replacing the "?" characters.

*/

#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Brute-Force.

*/

/* Time  Beats: 29.34% */
/* Space Beats: 49.70% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    string findLatestTime(string s)
    {
        const int N = s.length();

        for (int i = 0; i < N; i++)
        {
            if (s[i] == ':' || s[i] != '?')
                continue;

            switch (i)
            {
                case 0:
                    if (s[i+1] == '?')
                        s[i] = '1';
                    else if (s[i+1] >= '2')
                        s[i] = '0';
                    else
                        s[i] = '1';
                    break;

                case 1:
                    if (s[i-1] == '0')
                        s[i] = '9';
                    else
                        s[i] = '1';
                    break;

                case 3:
                    s[i] = '5';
                    break;

                case 4:
                    s[i] = '9';
                    break;
            }
        }

        return s;
    }
};
