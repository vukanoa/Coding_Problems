/*
    ============
    === EASY ===
    ============

    ============================================
    2124) Check if All A's Appear Before All B's
    ============================================

    ============
    Description:
    ============

    Given a string s consisting of only the characters 'a' and 'b', return true
    if every 'a' appears before every 'b' in the string. Otherwise, return
    false.

    =====================================
    FUNCTION: bool checkString(string s);
    =====================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "aaabbb"
    Output: true
    Explanation:
    The 'a's are at indices 0, 1, and 2, while the 'b's are at indices 3, 4,
    and 5. Hence, every 'a' appears before every 'b' and we return true.

    --- Example 2 ---
    Input: s = "abab"
    Output: false
    Explanation:
    There is an 'a' at index 2 and a 'b' at index 1.
    Hence, not every 'a' appears before every 'b' and we return false.

    --- Example 3 ---
    Input: s = "bbb"
    Output: true
    Explanation:
    There are no 'a's, hence, every 'a' appears before every 'b' and we return
    true.


    *** Constraints ***
    1 <= s.length <= 100
    s[i] is either 'a' or 'b'.

*/

#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  96.90% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    bool checkString(string s)
    {
        const int N = s.size();

        int rightmost_a_idx = -1;
        int leftmost_b_idx = -1;

        for (int i = 0; i < N; i++)
        {
            if (s[i] == 'a')
                rightmost_a_idx = i;
            else if (leftmost_b_idx == -1)
                leftmost_b_idx = i;
        }

        if (rightmost_a_idx == -1 || leftmost_b_idx == -1)
            return true;

        return rightmost_a_idx < leftmost_b_idx;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Look at the example and it'll become painfully obvious:

    +-----------+-------------------+------------------+
    |   s       |  an a after a b?  |  contains "ba"?  |
    +-----------+-------------------+------------------+
    |   aaabbb  |  no               |  no              |
    +-----------+-------------------+------------------+
    |   aaa     |  no               |  no              |
    +-----------+-------------------+------------------+
    |   bbb     |  no               |  no              |
    +-----------+-------------------+------------------+
    |   abab    |  yes              |  yes   a[ba]b    |
    +-----------+-------------------+------------------+
    |   bbaa    |  yes              |  yes   b[ba]a    |
    +-----------+-------------------+------------------+
    |   abbaaa  |  yes              |  yes   ab[ba]aa  |
    +-----------+-------------------+------------------+

    So if substring "ba" does NOT exist, then it means all a's do appear before
    all the b's.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  96.90% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Simple {
public:
    bool checkString(string s)
    {
        return s.find("ba") == string::npos;
    }
};
