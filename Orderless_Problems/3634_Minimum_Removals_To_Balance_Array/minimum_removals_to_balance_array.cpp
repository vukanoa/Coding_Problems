/*
    ==============
    === MEDIUM ===
    ==============

    =======================================
    3634) Minimum Removals to Balance Array
    =======================================

    ============
    Description:
    ============

    You are given an integer array nums and an integer k.

    An array is considered balanced if the value of its maximum element is at
    most k times the minimum element.

    You may remove any number of elements from nums without making it empty.

    Return the minimum number of elements to remove so that the remaining array
    is balanced.

    =====
    Note: An array of size 1 is considered balanced as its maximum and minimum
          are equal, and the condition always holds true.
    =====

    ===================================================
    FUNCTION: int minRemoval(vector<int>& nums, int k);
    ===================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [2,1,5], k = 2
    Output: 1
    Explanation:
        Remove nums[2] = 5 to get nums = [2, 1].
        Now max = 2, min = 1 and max <= min * k as 2 <= 1 * 2. Thus, the answer is 1.


    --- Example 2 ---
    Input: nums = [1,6,2,9], k = 3
    Output: 2
    Explanation:
        Remove nums[0] = 1 and nums[3] = 9 to get nums = [6, 2].
        Now max = 6, min = 2 and max <= min * k as 6 <= 2 * 3. Thus, the answer is 2.


    --- Example 3 ---
    Input: nums = [4,6], k = 2
    Output: 0
    Explanation:
        Since nums is already balanced as 6 <= 4 * 2, no elements need to be removed.


    *** Constraints ***
    1 <= nums.length <= 10^5
    1 <= nums[i] <= 10^9
    1 <= k <= 10^5

*/

#include <algorithm>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    (Igore this "other" vector, since that is needed only in C++ due to
    overflow. We're given a vector of integers and k is an integer as well, but
    once they are multiplied it can overflow. Therefore we use this "other",
    but when reading assume it's "nums")

    Sort the Input and then check for each element how many elements would it
    entail to remove in order for it to be the MINIMUM value.

    That's literally it.

*/

/* Time  Beats: 11.11% */
/* Space Beats: 00.00% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution {
public:
    int minRemoval(vector<int>& nums, int k)
    {
        const int N = nums.size();
        int result = N-1;

        vector<long long> other; // O(N) Space
        for (const int& num : nums)
            other.push_back(1LL * num);

        /* Sort O(N * logN) */
        sort(other.begin(), other.end());

        /* O(N * logN) */
        for (int i = 0; i < N-1; i++)
        {
            long long target = 1LL * other[i] * k;
            auto iter = upper_bound(other.begin() + i, other.end(), target);


            int leftmost_okay_idx;
            if (iter == other.end())
                leftmost_okay_idx = N;
            else
                leftmost_okay_idx = distance(other.begin(), iter);

            result = min(result, i + (N - leftmost_okay_idx));
        }

        return result;
    }
};
