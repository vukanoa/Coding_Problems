/*
    ==============
    === MEDIUM ===
    ==============

    =========================================
    2799) Count Complete Subarray in an Array
    =========================================

    ============
    Description:
    ============

    You are given an array nums consisting of positive integers.

    We call a subarray of an array complete if the following condition is
    satisfied:

        + The number of distinct elements in the subarray is equal to the
          number of distinct elements in the whole array.

    Return the number of complete subarrays.

    A subarray is a contiguous non-empty part of an array.

    ========================================================
    FUNCTION: int countCompleteSubarrays(vector<int>& nums);
    ========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,3,1,2,2]
    Output: 4
    Explanation: The complete subarrays are the following:
                 [1,3,1,2], [1,3,1,2,2], [3,1,2] and [3,1,2,2].

    --- Example 2 ---
    Input: nums = [5,5,5,5]
    Output: 10
    Explanation: The array consists only of the integer 5, so any subarray is
                 complete. The number of subarrays that we can choose is 10.


    *** Constraints ***
    1 <= nums.length <= 1000
    1 <= nums[i] <= 2000

*/

#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    By-the-book Sliding Window. One of the most basic examples.

*/

/* Time  Beats: 96.52% */
/* Space Beats: 59.44% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    int countCompleteSubarrays(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 0;

        unordered_set<int> unique(nums.begin(), nums.end());
        unordered_map<int,int> umap;

        int L = 0;
        int R = 0;
        while (R < N)
        {
            umap[nums[R]]++;

            while (L <= R && umap.size() == unique.size())
            {
                result += N - R;

                umap[nums[L]]--;
                if (umap[nums[L]] == 0)
                    umap.erase(nums[L]);

                L++;
            }

            // Increment
            R++;
        }

        return result;
    }
};
