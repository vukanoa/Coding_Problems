/*
    ============
    === EASY ===
    ============

    ============================================================
    1784) Check if Binary String Has at Most One Segment of Ones
    ============================================================

    ============
    Description:
    ============

    Given a binary string without leading zeros, return true if s contains at
    most one contiguous segment of ones. Otherwise, return false.

    ==========================================
    FUNCTION: bool checkOnesSegment(string s);
    ==========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "1001"
    Output: false
    Explanation: The ones do not form a contiguous segment.

    --- Example 2 ---
    Input: s = "110"
    Output: true


    *** Constraints ***
    1 <= s.length <= 100
    s[i] is either '0' or '1'.
    s[0] is '1'.

*/

#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    First iterate over any eventual TRAILING 0s.

    Then once we're at the rightmost block of 1s, iterate in through them in
    reverse.

    If we do NOT end up iterating over ALL the elements, i.e. i > -1, then we
    know this is NOT valid.


    How do we know that?

    They've told that the string s does NOT contain any LEADING 0s.

    That means that it's CERTAIN that s[0] == 1.

    Which means that if after the iteration of the rightmost block of 1s, we do
    NOT end up in -1, then that menas must've stopped on index i >= 2.

    Which means that there is a 0 at index 1, and we certainly know there is a
    '1' at s[0].

*/

/* Time  Beats: 100.00% */
/* Space Beats:  9.52% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    bool checkOnesSegment(string s)
    {
        const int N = s.size();
        bool result = false;


        int i = N-1;
        while (i >= 0 && s[i] == '0')
            i--;

        while (i >= 0 && s[i] == '1')
            i--;

        if (i == -1)
            return true;

        return false;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    A much more concise example. We really utilize the fact there are no
    LEADING 0s.

*/

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_One_Liner{
public:
    bool checkOnesSegment(string s)
    {
        return s.find("01") == string::npos;
    }
};
