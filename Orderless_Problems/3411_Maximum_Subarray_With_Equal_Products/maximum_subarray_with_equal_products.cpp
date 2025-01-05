/*
    ============
    === EASY ===
    ============

    ==========================================
    3411) Maximum Subarray With Equal Products
    ==========================================

    ============
    Description:
    ============

    You are given an array of positive integers nums.

    An array arr is called product equivalent if prod(arr) == lcm(arr) *
    gcd(arr), where:

        prod(arr) is the product of all elements of arr.

        gcd(arr) is the GCD of all elements of arr.

        lcm(arr) is the LCM of all elements of arr.

    Return the length of the longest product equivalent subarray of nums.

    A subarray is a contiguous non-empty sequence of elements within an array.

    The term gcd(a, b) denotes the greatest common divisor of a and b.

    The term lcm(a, b) denotes the least common multiple of a and b.

    ===========================================
    FUNCTION: int maxLength(vector<int>& nums);
    ===========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,1,2,1,1,1]
    Output: 5
    Explanation: The longest product equivalent subarray is [1, 2, 1, 1, 1],
                 where prod([1, 2, 1, 1, 1]) = 2, gcd([1, 2, 1, 1, 1]) = 1,
                 and lcm([1, 2, 1, 1, 1]) = 2.

    --- Example 2 ---
    Input: nums = [2,3,4,5,6]
    Output: 3
    Explanation: The longest product equivalent subarray is [3, 4, 5].


    --- Example 3 ---
    Input: nums = [1,2,3,1,4,5,1]
    Output: 5


    *** Constraints ***
    2 <= nums.length <= 100
    1 <= nums[i] <= 10

*/

#include <numeric>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    There is not better than than a simple Brute-Force here.

*/

/* Time  Beats: 30.77% */
/* Space Beats: 46.15% */

/* Time  Complexity: O(n^2) */
/* Space Complexity: O(n)   */
class Solution {
public:
    int maxLength(vector<int>& nums) 
    {
        const int N = nums.size();

        int max_len = 0;
        for (int i = 0; i < N; ++i) 
        {
            int curr_GCD = nums[i];
            int curr_LCM = nums[i];

            double reciprocal = 1.0 / nums[i];
            
            for (int j = i; j < N; ++j) 
            {
                if (i < j) 
                {
                    curr_GCD = gcd(curr_GCD, nums[j]);
                    curr_LCM = lcm(curr_LCM, nums[j]); 

                    reciprocal /= nums[j];
                }

                if (curr_GCD * curr_LCM * reciprocal > 0.99999999) 
                    max_len = max(max_len, j - i + 1);
            }
        }

        return max_len;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    There is not better than than a simple Brute-Force here. This is just
    another way to impement it.

*/

/* Time  Beats: 61.54% */
/* Space Beats: 30.77% */

/* Time  Complexity: O(n^2) */
/* Space Complexity: O(n)   */
class Solution_2 {
public:
    int maxLength(vector<int>& nums)
    {
        const int N = nums.size();

        int result = 0;
        for (int i = 0; i < N; i++)
        {
             int product = 1;
             int curr_GCD = nums[i];
             int curr_LCM = nums[i];

             int max_LCM = 1e9;

             for (int j = i; j < N; j++)
             {
                product *= static_cast<long long>(nums[j]);

                if (product > max_LCM)
                    break;

                curr_GCD = gcd(curr_GCD, nums[j]);
                curr_LCM = lcm(curr_LCM, nums[j]);

                if (product == curr_GCD * curr_LCM)
                    result = max(result, j-i+1);
             }
        }

        return result;
    }
};
