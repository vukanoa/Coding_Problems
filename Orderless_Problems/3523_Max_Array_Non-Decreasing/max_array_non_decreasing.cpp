/*
    ==============
    === MEDIUM ===
    ==============

    ==============================
    3523) Max Array Non-Decreasing
    ==============================

    ============
    Description:
    ============

    You are given an integer array nums. In one operation, you can select a
    subarray and replace it with a single element equal to its maximum value.

    Return the maximum possible size of the array after performing zero or more
    operations such that the resulting array is non-decreasing.

    =====================================================
    FUNCTION: int maximumPossibleSize(vector<int>& nums);
    =====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [4,2,5,3,5]
    Output: 3
    Explanation:
    One way to achieve the maximum size is:
        Replace subarray nums[1..2] = [2, 5] with 5 → [4, 5, 3, 5].
        Replace subarray nums[2..3] = [3, 5] with 5 → [4, 5, 5].
    The final array [4, 5, 5] is non-decreasing with size 3.

    --- Example 2 ---
    Input: nums = [1,2,3]
    Output: 3
    Explanation:
    No operation is needed as the array [1,2,3] is already non-decreasing.


    *** Constraints ***
    1 <= nums.length <= 2 * 10^5
    1 <= nums[i] <= 2 * 10^5

*/

#include <climits>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Once we hit the element that is LESS than the previous, we need to find
    the next EQUAL OR GREATER than that previous.

    Once we find it, count the distance between previous greater and this one
    that is EQUAL OR GREATER and that is "the number of removed" elements.

    At the end we return N - removed.

*/

/* Time  Beats: 59.95% */
/* Space Beats: 56.46% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int maximumPossibleSize(vector<int>& nums)
    {
        const int N = nums.size();
        int removed = 0;

        int i = 1;
        while (i < N)
        {
            if (nums[i-1] > nums[i])
            {
                int idx = i;
                int val = nums[i-1];

                while (i < N && val > nums[i])
                    i++;

                if (i == N)
                {
                    removed += N - idx;
                    break;
                }

                removed += i - idx;
                i--;
            }

            i++;
        }

        return N - removed;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Here we do NOT count the number of removals, instead we count how many
    elements do NOT require to be compressed.

    And that is our answer;

*/

/* Time  Beats: 69.86% */
/* Space Beats: 76.93% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_simple {
public:
    int maximumPossibleSize(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 0;

        int curr = INT_MIN;

        for (const int& num : nums)
        {
            if (num >= curr)
            {
                curr = num;
                result++;
            }
        }

        return result;
    }
};
