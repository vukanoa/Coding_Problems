/*
    ==============
    === MEDIUM ===
    ==============

    ==========================================================
    3228) Maximum Number of Operations to Move Ones to the End
    ==========================================================

    ============
    Description:
    ============

    You are given a binary stirng s.

    You can perform the following operation on the string any number of times:

        + Choose any index i from the string where i + 1 < s.length such that
          s[i] == '1' and s[i + 1] == '0'.

        + Move the character s[i] to the right until it reaches the end of the
          string or another '1'. For example, for s = "010010", if we choose
          i = 1, the resulting string will be s = "000110".

    Return the maximum number of operations that you can perform.

    ======================================
    FUNCTION: int maxOperations(string s);
    ======================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "1001101"
    Output: 4
    Explanation:
    We can perform the following operations:
        Choose index i = 0. The resulting string is s = "0011101".
        Choose index i = 4. The resulting string is s = "0011011".
        Choose index i = 3. The resulting string is s = "0010111".
        Choose index i = 2. The resulting string is s = "0001111".


    --- Example 2 ---
    Input: s = "00111"
    Output: 0


    *** Constraints ***
    1 <= s.length <= 10^5
    s[i] is either '0' or '1'.

*/

#include <string>
using namespace std;


/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory. Just read the code and go through one example and you'll
    get it.

*/

/* Time  Beats: 14.14% */
/* Space Beats: 58.22% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int maxOperations(string s)
    {
        const int N = s.length();
        int result = 0;

        if (N == 1)
            return 0;

        int ones = 0;

        bool ignore = true;
        for (int i = 0; i < N-1; i++)
        {
            if (s[i] == '0' && ignore)
                continue;

            ignore = false;

            if (s[i] == '1')
                ones++;
            else
            {
                result += ones;
                ignore = true;
            }
        }

        if (s[N-1] == '0' && s[N-2] != '0')
            result += ones;

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Just another way to implement it. More concise.

*/

/* Time  Beats: 83.22% */
/* Space Beats: 58.22% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_2 {
public:
    int maxOperations(string s)
    {
        const int N = s.length();
        int result = 0;

        for (int i = 0, cnt = 0; i < N; i++, cnt++)
        {
            if (s[i] == '0')
            {
                result += cnt;

                while (i < N && s[i] != '1')
                    i++;
            }
        }

        return result;
    }
};
