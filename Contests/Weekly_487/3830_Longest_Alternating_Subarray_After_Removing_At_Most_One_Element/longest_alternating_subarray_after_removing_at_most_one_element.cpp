/*
    ============
    === HARD ===
    ============

    =====================================================================
    3830) Longest Alternating Subarray After Removing At Most One Element
    =====================================================================

    ============
    Description:
    ============

    You are given an integer array nums.

    A subarray nums[l..r] is alternating if one of the following holds:

        nums[l] < nums[l + 1] > nums[l + 2] < nums[l + 3] > ...
        nums[l] > nums[l + 1] < nums[l + 2] > nums[l + 3] < ...

    In other words, if we compare adjacent elements in the subarray, then the
    comparisons alternate between strictly greater and strictly smaller.

    You can remove at most one element from nums. Then, you select an
    alternating subarray from nums.

    Return an integer denoting the maximum length of the alternating subarray
    you can select.

    A subarray of length 1 is considered alternating.

    ====================================================
    FUNCTION: int longestAlternating(vector<int>& nums);
    ====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [2,1,3,2]
    Output: 4
    Explanation:
        Choose not to remove elements.
        Select the entire array [2, 1, 3, 2], which is alternating because 2 >
        1 < 3 > 2.


    --- Example 2 ---
    Input: nums = [3,2,1,2,3,2,1]
    Output: 4
    Explanation:
        Choose to remove nums[3] i.e., [3, 2, 1, 2, 3, 2, 1]. The array becomes
        [3, 2, 1, 3, 2, 1].
        Select the subarray [3, 2, 1, 3, 2, 1].


    --- Example 3 ---
    Input: nums = [100000,100000]
    Output: 1
    Explanation:
        Choose not to remove elements.
        Select the subarray [100000, 100000].


    *** Constraints ***
    2 <= nums.length <= 10^5
    1 <= nums[i] <= 10^5

*/

#include <algorithm>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 44.88% */
/* Space Beats: 35.43% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    int longestAlternating(vector<int>& nums)
    {
        const int N = nums.size();

        vector<int> a(N, 1); // WITHOUT removal: max alternating length without removal ending at i
        vector<int> b(N, 1); // WITH    removal: max alternating length with    removal ending at or around i
        
        vector<int> l1(N, 1); // ending with <
        vector<int> l2(N, 1); // ending with >
        vector<int> r1(N, 1); // starting with >
        vector<int> r2(N, 1); // starting with <

        int result = 1;

        // WITHOUT removal (Prefix)
        for (int i = 1; i < N; i++)
        {
            if (nums[i-1] < nums[i])
            {
                l1[i] = l2[i-1] + 1;
            }
            else if (nums[i-1] > nums[i])
            {
                l2[i] = l1[i-1] + 1;
            }

            a[i] = max(l1[i], l2[i]);
            result = max(result, a[i]);
        }

        // Suffix alternating arrays
        for (int i = N-2; i >= 0; i--)
        {
            if (nums[i+1] > nums[i])
            {
                r1[i] = r2[i+1] + 1;
            }
            else if (nums[i+1] < nums[i])
            {
                r2[i] = r1[i+1] + 1;
            }
        }

        // WITH removal: Try removing each element nums[i] to bridge left and
        //               right parts
        for (int i = 1; i < N-1; i++)
        {
            if (nums[i-1] < nums[i+1])
            {
                b[i] = l2[i-1] + r2[i+1];
            }
            else if (nums[i-1] > nums[i+1])
            {
                b[i] = l1[i-1] + r1[i+1];
            }
            else
            {
                b[i] = max(l2[i-1], r2[i+1]); // Fallback if equal
            }
            result = max(result, b[i]);
        }

        return result;
    }
};
