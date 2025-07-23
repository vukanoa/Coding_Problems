/*
    ==============
    === MEDIUM ===
    ==============

    =====================================================
    2829) Determine the Minimum Sum of a K-avoiding Array
    =====================================================

    ============
    Description:
    ============

    You are given two integers, n and k.

    An array of distinct positive integers is called a k-avoiding array if
    there does not exist any pair of distinct elements that sum to k.

    Return the minimum possible sum of a k-avoiding array of length n.

    =======================================
    FUNCTION: int minimumSum(int n, int k);
    =======================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 5, k = 4
    Output: 18
    Explanation: Consider the k-avoiding array [1,2,4,5,6], which has a sum of 18.
    It can be proven that there is no k-avoiding array with a sum less than 18.

    --- Example 2 ---
    Input: n = 2, k = 6
    Output: 3
    Explanation: We can construct the array [1,2], which has a sum of 3.
    It can be proven that there is no k-avoiding array with a sum less than 3.


    *** Constraints ***
    1 <= n, k <= 50

*/



#include <algorithm>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Code is self-explanatory. Variable names are precisely named to alleviate
    the reading and comprehension of the problem.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  93.13% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int minimumSum(int n, int k)
    {
        int total_sum  = 0;
        int lowest_available_num = max(n+1, k);

        for (int curr_num = 1; curr_num <= n; curr_num++)
        {
            total_sum += curr_num;

            /*
               If we pick "curr_num", then by the description of the problem,
               we're NOT allowed to pick:

                   (k - curr_num)

                because these two would be equal to k, which is NOT allowed.

                That's why we call this variable "forbidden_pair_of_curr_num".
            */
            int forbidden_pair_of_curr_num = k - curr_num;

            /*
                If the forbiden_pair of "curr_num" is between [curr_num + 1, n]
                then that means we're NOT allowed to include both:

                    pair: (curr_num, forbidden_pair_of_curr_num)

                Therefore, in order to include forbidden_pair_of_curr_num, we
                need to take "replacement_num" instead of the "curr_num".

                The "replacement_num" is lowest_available_num.

                After we include it, we must increment it since duplicates are
                NOT allowed.
            */
            if (curr_num < forbidden_pair_of_curr_num && forbidden_pair_of_curr_num <= n)
            {
                int replacement_num = lowest_available_num; // Instead of curr_num
                lowest_available_num++; // Increment

                total_sum += replacement_num - forbidden_pair_of_curr_num;
            }
        }

        return total_sum;
    }
};
