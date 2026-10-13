/*
    ==============
    === MEDIUM ===
    ==============

    ================================
    3790) Smallest All-Ones Multiple
    ================================

    ============
    Description:
    ============

    You are given a positive integer k.

    Find the smallest integer n divisible by k that consists of only the digit
    1 in its decimal representation (e.g., 1, 11, 111, ...).

    Return an integer denoting the number of digits in the decimal
    representation of n. If no such n exists, return -1.

    =======================================
    FUNCTION: int minAllOneMultiple(int k);
    =======================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: k = 3
    Output: 3
    Explanation:
    n = 111 because 111 is divisible by 3, but 1 and 11 are not. The length of
    n = 111 is 3.

    --- Example 2 ---
    Input: k = 7
    Output: 6
    Explanation:
    n = 111111. The length of n = 111111 is 6.

    --- Example 3 ---
    Input: k = 2
    Output: -1
    Explanation:
    There does not exist a valid n that is a multiple of 2.


    *** Constraints ***
    2 <= k <= 10^5

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 64.88% */
/* Space Beats: 99.60% */

/* Time  Complexity: O(K) */
/* Space Complexity: O(1) */
class Solution {
public:
    int minAllOneMultiple(int k)
    {
        if (k % 2 == 0 || k % 5 == 0)
            return -1;
    
        int remainder = 0;
    
        for (int num_of_digits = 1; num_of_digits <= k; num_of_digits++)
        {
            remainder = (remainder * 10LL + 1) % k;
    
            if (remainder == 0)
                return num_of_digits;
        }
    
        return -1;       
    }
};
