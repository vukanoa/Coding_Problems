/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    3133) Minimum Array End
    ===========================

    ============
    Description:
    ============

    You are given two integers n and x. You have to construct an array of
    positive integers nums of size n where for every 0 <= i < n - 1, nums[i +
    1] is greater than nums[i], and the result of the bitwise AND operation
    between all elements of nums is x.

    Return the minimum possible value of nums[n - 1].

    =========================================
    FUNCTION: long long minEnd(int n, int x);
    =========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 3, x = 4
    Output: 6
    Explanation:
    nums can be [4,5,6] and its last element is 6.

    --- Example 2 ---
    Input: n = 2, x = 7
    Output: 15
    Explanation:
    nums can be [7,15] and its last element is 15.


    *** Constraints ***
    1 <= n, x <= 10^8

*/

/*
    ------------
    --- IDEA ---
    ------------

    Take pen and paper and go through one example. You'll get it by reading the
    code.

    The main takeaway is this: The result MUST begin at x and ALL of the
    subsequent numbers MUST HAVE all set-bits of x also set and more.

    Example 1:
        n = 4
        x = 8

        8  = 0 0 0 0 ... 1 0 0 0
        9  = 0 0 0 0 ... 1 0 0 1
        10 = 0 0 0 0 ... 1 0 1 0
        11 = 0 0 0 0 ... 1 0 1 1


        4th element starting at x=8 is 11.


    Example 2:
        n = 2
        x = 7

        7  = 0 0 0 0 ... 0 1 1 1 <---- 1st
        8  = 0 0 0 0 ... 1 0 0 0
        9  = 0 0 0 0 ... 1 0 0 1
        10 = 0 0 0 0 ... 1 0 1 0
        11 = 0 0 0 0 ... 1 0 1 1
        12 = 0 0 0 0 ... 1 1 0 0
        13 = 0 0 0 0 ... 1 0 1 1
        14 = 0 0 0 0 ... 1 1 1 0
        15 = 0 0 0 0 ... 1 1 1 1  <--- 2nd 


        2nd element starting at x=7 is 15.


    Any number must have ALL of the same set-bits as x. Initially 'n' is NOT
    a 0-indexed number, that's why we subtract 1.



    So just think about this:
        n = 4
        x = 8

        8  = 0 0 0 0 ... 1 0 0 0
        9  = 0 0 0 0 ... 1 0 0 1
        10 = 0 0 0 0 ... 1 0 1 0
        11 = 0 0 0 0 ... 1 0 1 1


        4th element starting at x=8 is 11.

    We need 4th number starting at x. Since x will takeaway one from n, we end
    up with 3.

    3 in binary is 0000....0011

    Now we go and put bits of this 3 in HOLES(i.e. 0 bits in x).

    And that's it.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  58.02% */

/* Time  Complexity: O(logN) */
/* Space Complexity: O(1)    */
class Solution {
public:
    long minEnd(int n, int x)
    {
        long result = x;

        int th_LSB_of_result = 0;

        int zero_indexed_n           = n-1;
        int th_LSB_of_zero_indexed_n = 0;


        while (th_LSB_of_result < 64)
        {
            if ((result & (1LL << th_LSB_of_result)) == 0)
            {
                if (zero_indexed_n & (1LL << th_LSB_of_zero_indexed_n))
                    result |= (1LL << th_LSB_of_result);

                th_LSB_of_zero_indexed_n++;
            }

            th_LSB_of_result++;
        }

        return result;
    }
};
