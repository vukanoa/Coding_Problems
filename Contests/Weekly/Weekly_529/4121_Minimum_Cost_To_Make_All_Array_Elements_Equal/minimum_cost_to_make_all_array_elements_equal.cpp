/*
    ==============
    === MEDIUM ===
    ==============

    ===================================================
    4121) Minimum Cost to Make All Array Elements Equal
    ===================================================

    ============
    Description:
    ============

    You are given an integer array nums of length n.

    You may perform any of the following operations any number of times, in any
    order.

        + Prefix operation: Choose an index i such that 0 < i < n - 1, and set
          all elements from index 0 to i - 1 to nums[i]. The cost of this
          operation is i * nums[i].

        + Suffix operation: Choose an index i such that 0 < i < n - 1, and set
          all elements from index i + 1 to n - 1 to nums[i]. The cost of this
          operation is (n - i - 1) * nums[i].

    The cost is based on the current value of nums[i] and includes every
    element in the chosen prefix or suffix, even if it already equals nums[i].

    Return the minimum total cost required to make all elements of nums equal.

    ===============================================
    FUNCTION: long long minCost(vector<int>& nums);
    ===============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,3]
    Output: 4
    Explanation:
    One sequence of operations that achieves the minimum cost is as follows:
    nums         Operation    i    Modified nums    Cost
    [1, 2, 3]    Suffix       1    [1, 2, 2]        (3 - 1 - 1) * 2 = 2
    [1, 2, 2]    Prefix       1    [2, 2, 2]        1 * 2 = 2

    Hence, the total cost is 2 + 2 = 4.


    --- Example 2 ---
    Input: nums = [3,3,3,6,3,3]
    Output: 9
    Explanation:
    One sequence of operations that achieves the minimum cost is as follows:
    nums                 Operation    i    Modified nums         Cost
    [3, 3, 3, 6, 3, 3]    Suffix      2    [3, 3, 3, 3, 3, 3]    (6 - 2 - 1) * 3 = 9

    Hence, the total cost is 9.


    --- Example 3 ---
    Input: nums = [3,4,4,5,4,4,3]
    Output: 20
    Explanation:
    One sequence of operations that achieves the minimum cost is as follows:
    nums                    Operation    i    Modified nums    Cost
    [3, 4, 4, 5, 4, 4, 3]    Prefix      4    [4, 4, 4, 4, 4, 4, 3]    4 * 4 = 16
    [4, 4, 4, 4, 4, 4, 3]    Suffix      5    [4, 4, 4, 4, 4, 4, 4]    (7 - 5 - 1) * 4 = 4
    Hence, the total cost is 16 + 4 = 20.


    *** Constraints ***
    3 <= n == nums.length <= 10^5
    1 <= nums[i] <= 10^9

*/

#include <climits>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 15.60% */
/* Space Beats: 14.21% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    long long minCost(vector<int>& nums)
    {
        const int N = nums.size();
        long long result = LLONG_MAX;

        vector<int> prefix(N, 0); prefix[0]   = nums[0];
        vector<int> suffix(N, 0); suffix[N-1] = nums[N-1];

        for (int i = 1; i < N; i++)
        {
            if (prefix[i-1] == nums[i])
                prefix[i] = prefix[i-1];
        }
        
        for (int i = N-2; i >= 0; i--)
        {
            if (nums[i] == suffix[i+1])
                suffix[i] = suffix[i+1];
        }

        int i = 1;
        while (i < N-1)
        {
            int L = i;
            int R = i;

            while (R < N-1 && nums[L] == nums[R])
                ++R;

            long long left_cost  = (prefix[L-1] == nums[L]) ? 0 : 1LL * L       * nums[L];
            long long right_cost = (suffix[R]   == nums[L]) ? 0 : 1LL * (N - R) * nums[L];

            result = min(result, left_cost + right_cost);

            i = R;
        }
        
        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    We can actually do it in One-Pass and without any additional Space.

*/

/* Time  Beats: 71.60% */
/* Space Beats: 57.81% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Optimal {
public:
    long long minCost(vector<int>& nums)
    {
        const int N = nums.size();
        long long result = LLONG_MAX;

        int consecutive = 0;

        for (int i = 0; i < N; i++)
        {
            if (i > 0 && nums[i-1] == nums[i])
                ++consecutive;
            else
                consecutive = 1; // Reset

            if (consecutive > 1 || (0 < i && i < N-1))
                result = min(result, 1LL * (N - consecutive) * nums[i]);
        }

        return result;
    }
};
