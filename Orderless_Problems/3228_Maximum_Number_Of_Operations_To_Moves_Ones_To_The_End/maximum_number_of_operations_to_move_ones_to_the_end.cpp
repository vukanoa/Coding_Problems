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




/*
    ------------
    --- IDEA ---
    ------------

    This is, at least to me, the solution that makes the most sense.
    Let's consider Example 1:


        Input: s = "1001101"
        Output: 4

        Explanation:
        We can perform the following operations:

            Choose index i = 0. The resulting string is s = "0011101".
            Choose index i = 4. The resulting string is s = "0011011".
            Choose index i = 3. The resulting string is s = "0010111".
            Choose index i = 2. The resulting string is s = "0001111".

    I'm not sure if you see the pattern, but let me clarify it.

    If we're going from left-to-right, we're going to need and move each
    consecutive 1s to next group of 1s that is separated by one or more 0s from
    this current group.

    Then, we'd need to move that new group of consecutive 1s to the next
    group of consecutive 1s that is separated by one or more 0s from this
    current group.

    And so on and so on.


    But let me be very precise:


        1 0 0 1 1 0 1
        0 1 2 3 4 5 6

    To move 1 from index 0 to join the next group at indices 3 and 4, we need
    to perform one operation.

    Now, once those 1s are join at indices 2,3,4, we need to move THOSE 1s to
    join the next group, etc.

    Do you see the pattern?

    Essentially every 1 in the binary string, in order to join the last group
    of consecutive 1s, it needs to jump over exactly X number of 0 segments.

        1 0 0 1 1 0 1
        0 1 2 3 4 5 6
          ^^^     ^
           |      |
       1st Seg   2nd Seg

    Therefore, 1 at index 2, need to jump over TWO segments of 0s and 1s at
    indices 3 and 4 need to jump only over ONE segment of 0s.

    Therefore, the result is: (1 * 2)                 + (2 * 1) = 4
                               ^   ^                     ^   ^           
                             __|   |__                 __|   |__         
                             |        |                |        |
                          cons 1s   0-segments      cons 1s   0-segments



    Now read the code and it'll make sense.


*/

/* Time  Beats: 86.23% */
/* Space Beats: 53.99% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_3 {
public:
    int maxOperations(string s)
    {
        const int N = s.length();
        int result = 0;

        int i = N-1;
        while (i >= 0 && s[i] == '1') // Skip over rightmost 1s at the end
            i--;

        if (i == -1)
            return 0;

        int zero_segments = 0;
        while (i >= 0)
        {
            while (i >= 0 && s[i] == '0') // Iterate over 0-segments
                i--;

            zero_segments++;

            int consecutive_ones = 0;
            while (i >= 0 && s[i] == '1') // Iterate and count consecutive 1s
            {
                consecutive_ones++;
                i--;
            }

            result += consecutive_ones * zero_segments;
        }

        return result;
    }
};
