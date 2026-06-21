/*
    ============
    === EASY ===
    ============

    ===========================
    338) Counting Bits
    ===========================

    ============
    Description:
    ============

    Given an integer n, return an array ans of length n + 1 such that for each
    i (0 <= i <= n), ans[i] is the number of 1's in the binary representation
    of i.

    ~~~ Follow Up ~~~
    It is very easy to come up with a solution with a runtime of O(n log n).

    Can you do it in linear time O(n) and possibly in a single pass?
    Can you do it without using any built-in function (i.e., like
    __builtin_popcount in C++)?


    =======================================
    FUNCTION: vector<int> countBits(int n);
    =======================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 2
    Output: [0,1,1]
    Explanation:
    0 --> 0
    1 --> 1
    2 --> 10


    --- Example 2 ---
    Input: n = 5
    Output: [0,1,1,2,1,2]
    Explanation:
    0 --> 0
    1 --> 1
    2 --> 10
    3 --> 11
    4 --> 100
    5 --> 101


    *** Constraints ***
    0 <= n <= 105
*/

#include <cstring>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    THe most basic Solution for this problem. However, for beginners even this
    is not so obivous, that's why I'm including it.

*/

/* Time  Beats:  9.55% */
/* Space Beats: 55.47% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Basic {
public:
    vector<int> countBits(int n) {
        vector<int> result(n + 1, 0);

        for (int num = 1; num <= n; num++)
        {
            for (int j = 0; j < 32; j++)
            {
                if (num & (1 << j))
                    result[num]++;
            }
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    If we do a "bitwise AND" with 0x1 on any number, we get to see if it's an
        1) Odd, or
        2) Even
    number.

    Odd numbers in binary representation have 1 at the very end.
    Examples:                                ~~~~~~~~~~~~~~~~~~
                                                   |
              _____________________________________|
              |
              v
        3: 0011
        5: 0101
        7: 0111
        9: 1001


    Even numbers, on the other hand, have 0 at the very end.
    Examples:                             ~~~~~~~~~~~~~~
                                                   |
              _____________________________________|
              |
              v
        2: 0010
        4: 0100
        6: 0110
        8: 1000


    Therefore, if we do a "bitwise AND" with 0x1:

        4: 0100
        1: 0001  AND
        ________
           0000 // 0 means 4 is an EVEN number
                // 1 would mean it is an ODD number

    Based on that we are checking each bit and after that we do a Logical Shift
    Right.

    That's it.

*/

/* Time  Beats: 22.61% */
/* Space Beats: 78.77% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Slower {
public:
    vector<int> countBits(int n)
    {
        vector<int> result(n+1, 0);

        for (int i = 0; i <= n; i++) // Inclding n
        {
            int count = 0;

            int num  = i;
            while (num > 0)
            {
                if (num & 1)
                    result[i]++;

                num >>= 1;
            }
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same as above, though this one will iterate exactly "number of bits" times
    for each number, which is faster even if the TC of this part is O(1) in
    both SOlutions.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  78.77% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Faster {
public:
    vector<int> countBits(int n)
    {
        vector<int> result(n + 1, 0);

        for (int i = 1; i <= n; i++)
        {
            int num = i;

            while (num > 0)
            {
                result[i]++;
                num &= (num - 1); // Cool little trick
            }
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Bottom-Up Dynamic Programming, aka "Tabulation".

*/

/* Time  Beats: 100.00% */
/* Space Beats:  97.09% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */ // But it's not AUXILIARY space since it's result
class Solution_Bottom_Up__Tabulation_1 {
public:
    vector<int> countBits(int n)
    {
        vector<int> result(n+1, 0);

        int pow_of_two = 1;
        for (int i = 1; i <= n; i++)
        {
            if (pow_of_two * 2 == i)
                pow_of_two = i;

            result[i] = 1 + result[i - pow_of_two];
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Effectively same as bove, but written in another, more elegant, way.

*/

/* Time  Beats: 95.87% */
/* Space Beats: 63.11% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Bottom_Up__Tabulation_2 {
public:
    vector<int> countBits(int n)
    {
        vector<int> result(n+1, 0);

        for (int i = 1; i <= n; i++)
            result[i] = result[i/2] + i%2;

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same as above, however instead of using:
    
        "i / 2", we used "i >> 1"

    and

        "i % 2", we used "i & 1".

*/

/* Time  Beats: 100.00% */
/* Space Beats:  55.47% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Bottom_Up__Tabulation_3 {
public:
    vector<int> countBits(int n)
    {
        vector<int> dp(n + 1, 0);

        for (int i = 1; i <= n; i++)
            dp[i] = dp[i >> 1] + (i & 1);

        return dp;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 95.87% */
/* Space Beats: 51.59% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Bottom_Up__Tabulation_4 {
public:
    vector<int> countBits(int num)
    {
        vector<int> result(num+1, 0);

        for (int i = 1; i <= num; ++i)
            result[i] = result[i & (i-1)] + 1;

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This is a Top-Down Dynamic Programming Solution, aka "Memoization", not
    "MemoRization"!

    It's really beneficial to learn Memoization properly, so whenever you're
    writing a Bottom-Up DP, make sure to write Top-Down as well. And vice-verca
    as sometimes one approach is MUCH more natural than the other, therefore it
    makes you really learn ins-and-outs of both approaches.

*/

/* Time  Beats:  6.11% */
/* Space Beats: 32.04% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Top_Down__Memoization {
private:
    int memo[100001];

public:
    int solve(int n)
    {
        if (n == 0) return 0;
        if (n == 1) return 1;

        if (memo[n] != 0)
            return memo[n];

        if (n & 1)
            memo[n] = 1;

        return memo[n] += solve(n / 2);
    }

    vector<int> countBits(int n)
    {
        vector<int> result(n + 1);

        /* Memset */
        memset(memo, 0x00, sizeof(memo));

        for (int i = 0; i <= n; i++)
            result[i] = solve(i);

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    __builtin_popcount and __builtin_popcountll are NOT a part of C++, this is
    GCC/Clang extension. Keep in mind that this is Compiler specific.

    MSVC does NOT provide __builtin_popcount or __builtin_popcountll. If you
    use a MSVC compiler then you'd need to use:

        __pocnt or __popcnt64

    In C++20 there is a std::popcount() function.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  55.47% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_CPP_Way {
public:
    vector<int> countBits(int n)
    {
        vector<int> result(n + 1, 0);

        for (int i = 0; i <= n; i++)
            result[i] = __builtin_popcount(i);

        return result;
    }
};
