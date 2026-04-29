/*
    ==============
    === MEDIUM ===
    ==============

    =============================================
    3334) Find the Matximum Factor Score of Array
    =============================================

    ============
    Description:
    ============

    You are given an integer array nums.

    The factor score of an array is defined as the product of the LCM and GCD
    of all elements of that array.

    Return the maximum factor score of nums after removing at most one element
    from it.

    =====
    Note: that both the and of a single number are the number itself, and the
          factor score of an empty array is 0. 
    =====

    ===============================================
    FUNCTION: ong long maxScore(vector<int>& nums);
    ===============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [2,4,8,16]
    Output: 64
    Explanation: On removing 2, the GCD of the rest of the elements is 4 while
                 the LCM is 16, which gives a maximum factor score of 4 * 16 =
                 64.

    --- Example 2 ---
    Input: nums = [1,2,3,4,5]
    Output: 60
    Explanation: The maximum factor score of 60 can be obtained without
                 removing any elements.

    --- Example 3 ---
    Input: nums = [3]
    Output: 9


    *** Constraints ***
    1 <= nums.length <= 100
    1 <= nums[i] <= 30

*/

#include <numeric>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    This one does NOT pass because LCM overflows!
    It must be done in the other "Optimized" way as shown in the 2nd SOlution.

*/

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(N)   */
class Solution {
public:
    long long maxScore(vector<int>& nums)
    {
        const int N = nums.size();
        
        if (N == 0) return 0;
        if (N == 1) return 1LL * nums[0] * nums[0];
        
        long long result = 0;
        
        // Calculate score for the ENTIRE array
        long long total_gcd = nums[0];
        long long total_lcm = nums[0];

        for (int i = 1; i < N; i++)
        {
            total_gcd = my_gcd(total_gcd, nums[i]);
            total_lcm = my_lcm(total_lcm, nums[i]);
        }

        result = max(result, total_gcd * total_lcm);
        
        // Calculate score after removing each index i
        for (int i = 0; i < N; i++)
        {
            long long curr_gcd = -1;
            long long curr_lcm = -1;
            bool first = true;
            
            for (int j = 0; j < N; j++)
            {
                if (j == i) continue;
                
                if (first)
                {
                    curr_gcd = nums[j];
                    curr_lcm = nums[j];
                    first = false;
                }
                else
                {
                    curr_gcd = my_gcd(curr_gcd, nums[j]);
                    curr_lcm = my_lcm(curr_lcm, nums[j]);
                }
            }
            
            result = max(result, curr_gcd * curr_lcm);
        }

        return result;
    }

private:
    int my_gcd(int a, int b)
    {
        while (b != 0)
        {
            int tmp = b;
            b = a % b;
            a = tmp;
        }

        return a;
    }

    unsigned long long my_lcm(unsigned long long a, unsigned long long b)
    {
        return 1ULL * (a / my_gcd(a, b)) * b;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Classic "Prefix-Suffix" Trick.

*/

/* Time  Beats: 67.67% */
/* Space Beats: 31.58% */

/* Time  Complexity: O(N * logM) */ // where 'M' is the max_value(nums)
/* Space Complexity: O(N)        */
class Solution_Optimized {
public:
    long long maxScore(vector<int>& nums)
    {
        int N = nums.size();

        if (N == 0)
            return 0;

        if (N == 1)
            return nums[0] * nums[0];

        vector<int> prefix_gcd(N, 0);
        vector<int> suffix_gcd(N, 0);

        vector<long long> prefix_lcm(N, 0);
        vector<long long> suffix_lcm(N, 0);

        /* Prefix */
        prefix_gcd[0] = nums[0];
        prefix_lcm[0] = nums[0];
        for (int i = 1; i < N; i++)
        {
            prefix_gcd[i] = gcd(prefix_gcd[i-1], nums[i]);
            prefix_lcm[i] = lcm(prefix_lcm[i-1], nums[i]);
        }
        
        /* Suffix */
        suffix_gcd[N-1] = nums[N-1];
        suffix_lcm[N-1] = nums[N-1];
        for (int i = N-2; i >= 0; i--)
        { 
            suffix_gcd[i] = gcd(suffix_gcd[i+1], nums[i]);
            suffix_lcm[i] = lcm(suffix_lcm[i+1], nums[i]);
        }

        long long product1 = suffix_lcm[0]   * suffix_gcd[0];   // Without removing ANY element
        long long product2 = suffix_lcm[1]   * suffix_gcd[1];   // With removed element at index 0
        long long product3 = prefix_lcm[N-2] * prefix_gcd[N-2]; // With removed element at index N-1

        long long result = max( max(product1, product2), product3 );
        
        for (int i = 1; i < N-1; i++)
        {
            long long curr_lcm = lcm(prefix_lcm[i-1],
                                     suffix_lcm[i+1]);

            long long curr_gcd = gcd(prefix_gcd[i-1],
                                     suffix_gcd[i+1]);

            long long curr = curr_lcm * curr_gcd;

            result = max(curr, result);
        }

        return result;
    }
};
