/*
    ==============
    === MEDIUM ===
    ==============

    ========================================
    2537) Count the Number of Good Subarrays
    ========================================

    ============
    Description:
    ============

    Given an integer array nums and an integer k, return the number of good
    subarrays of nums.

    A subarray arr is good if there are at least k pairs of indices (i, j) such
    that i < j and arr[i] == arr[j].

    A subarray is a contiguous non-empty sequence of elements within an array.

    ========================================================
    FUNCTION: long long countGood(vector<int>& nums, int k);
    ========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,1,1,1,1], k = 10
    Output: 1
    Explanation: The only good subarray is the array nums itself.


    --- Example 2 ---
    Input: nums = [3,1,4,3,2,2,4], k = 2
    Output: 4
    Explanation: There are 4 different good subarrays:
    - [3,1,4,3,2,2] that has 2 pairs.
    - [3,1,4,3,2,2,4] that has 3 pairs.
    - [1,4,3,2,2,4] that has 2 pairs.
    - [4,3,2,2,4] that has 2 pairs.


    *** Constraints ***
    1 <= nums.length <= 10^5
    1 <= nums[i], k <= 10^9

*/

#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Pretty standard "Sliding Window" approach.

    This line is the most important:
        same += freq[nums[right]];

    Because it always adds new "same numbers".

    If there was only one occurrence of 3, then by stumbling upon a new 3, we
    have ONE pair os SAME integers.

    Then we increment freq[3]++;

    Next time we stumble upon a 3, we'll add TWO MORE pairs:

        First new:
            3   3   3
            |___|

        Seceond new:
            3   3   3
            |_______|

    And so on.

    That is the main "trick" and "addition" to the standard Sliding Window
    problem.

*/

/* Time  Beats: 58.53% */
/* Space Beats: 36.26% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    long long countGood(vector<int>& nums, int k)
    {
        const int N = nums.size();
        long long result = 0;

        unordered_map<int, int> freq;

        long long same = 0;

        int left  = 0;
        int right = 0;

        while (right < N)
        {
            same += freq[nums[right]];
            freq[nums[right]]++;

            while (same >= k)
            {
                result += N - right; // All subarrays ending at >= right are ok

                freq[nums[left]]--;
                same -= freq[nums[left]];
                left++;
            }

            // Increment
            right++;
        }

        return result;
    }
};
