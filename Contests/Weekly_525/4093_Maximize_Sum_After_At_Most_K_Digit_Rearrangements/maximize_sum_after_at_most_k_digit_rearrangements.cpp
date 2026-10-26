/*
    ==============
    === MEDIUM ===
    ==============

    =======================================================
    4093) Maximize Sum After At Most K Digit Rearrangements
    =======================================================

    ============
    Description:
    ============

    You are given an integer array nums of length n and an integer k.

    In one operation, you may choose any element of nums and rearrange its
    decimal digits in any order to form a new integer.

    Return the maximum possible sum of the array after performing at most k
    operations.

    ==========================================================
    FUNCTION: long long maximizeSum(vector<int>& nums, int k);
    ==========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [123,45], k = 1
    Output: 366
    Explanation:
        We choose nums[0] = 123 and rearrange its digits to form 321.
        The array becomes [321, 45]. Thus, the total sum is 321 + 45 = 366.

    --- Example 2 ---
    Input: nums = [102,90,14], k = 2
    Output: 341
    Explanation:
        We choose nums[0] = 102 and rearrange its digits to form 210.
        We choose nums[2] = 14 and rearrange its digits to form 41.
        The array becomes [210, 90, 41]. Thus, the total sum is 210 + 90 + 41 =
        341.


    *** Constraints ***
    1 <= n == nums.length <= 10^5
    1 <= nums[i] <= 10^9
    1 <= k <= n

*/

#include <queue>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats:  8.33% */
/* Space Beats: 16.67% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution {
public:
    long long maximizeSum(vector<int>& nums, int k)
    {
        const int N = nums.size();
        long long result = 0LL;


        priority_queue<vector<long long>> max_heap; // {non-negative DIFF, best_decimal, orig_decimal}

        // O(N * logN) (entire block)
        for (int i = 0; i < N; i++)
        {
            int number = nums[i];
            
            // TC: O(log(max(nums)))
            int freq[10] = {}; // frequencies of each DIGIT in number
            while (number > 0)
            {
                int digit = number % 10;
                ++freq[digit];

                number /= 10;
            }

            // TC: O(10) --> O(1)
            // Re-construct the best_decimal greedily, largest digits first
            long long best_decimal = 0LL;
            for (int digit = 9; digit >= 0; digit--)
            {
                if (freq[digit] == 0)
                    continue;

                while (freq[digit] > 0)
                {
                    best_decimal = (best_decimal * 10LL) + digit;
                    
                    // Decrement
                    --freq[digit];
                }
            }

            // TC: O(logN)
            max_heap.push( {best_decimal - nums[i], best_decimal, 1LL * nums[i]} );
        }

        // O(N * logN) (entire block)
        while ( ! max_heap.empty())
        {
            vector<long long> top = max_heap.top();
            max_heap.pop(); // TC: O(logN) because of the "heapify"

            const long long& diff         = top[0];
            const long long& best_decimal = top[1];
            const long long& orig_decimal = top[2];

            if (k > 0)
                result += best_decimal;
            else
                result += orig_decimal;

            if (k > 0)
                --k;
        }
        
        return result;
    }
};
