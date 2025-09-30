/*
    ============
    === EASY ===
    ============

    ================================
    551) Student Attendance Record I
    ================================

    ============
    Description:
    ============

    You are given a string s representing an attendance record for a student
    where each character signifies whether the student was absent, late, or
    present on that day. The record only contains the following three
    characters:

        'A': Absent.
        'L': Late.
        'P': Present.

    The student is eligible for an attendance award if they meet both of the
    following criteria:

        + The student was absent ('A') for strictly fewer than 2 days total.
        + The student was never late ('L') for 3 or more consecutive days.

    Return true if the student is eligible for an attendance award, or false
    otherwise.

    =====================================
    FUNCTION: bool checkRecord(string s);
    =====================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "PPALLP"
    Output: true
    Explanation: The student has fewer than 2 absences and was never late 3 or
                 more consecutive days.

    --- Example 2 ---
    Input: s = "PPALLL"
    Output: false
    Explanation: The student was late 3 consecutive days in the last 3 days,
                 so is not eligible for the award.


    *** Constraints ***
    1 <= s.length <= 1000
    s[i] is either 'A', 'L', or 'P'.

*/

#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  97.05% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    bool checkRecord(string s)
    {
        const int N = s.length();

        int absent = 0;
        int consecutively_late = 0;

        int idx = 0;
        while (idx < N)
        {
            if (s[idx] == 'A')
            {
                absent++;
                consecutively_late = 0;
            }
            else if (s[idx] == 'L')
            {
                consecutively_late++;

                if (consecutively_late == 3)
                    return false;

            }
            else // 'P'
            {
                consecutively_late = 0;
            }

            // Increment
            idx++;
        }

        return absent < 2;
    }
};
