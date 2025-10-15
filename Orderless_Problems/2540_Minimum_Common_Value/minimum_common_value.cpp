/*
    ============
    === EASY ===
    ============

    ===========================
    2540) Minimum Common Value
    ===========================

    ============
    Description:
    ============

    Given two integer arrays nums1 and nums2, sorted in non-decreasing order,
    return the minimum integer common to both arrays. If there is no common
    integer amongst nums1 and nums2, return -1.

    that an integer is said to be common to nums1 and nums2 if both arrays
    have at least one occurrence of that integer.

    ================================================================
    FUNCTION: int getCommon(vector<int>& nums1, vector<int>& nums2);
    ================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums1 = [1,2,3], nums2 = [2,4]
    Output: 2
    Explanation: The smallest element common to both arrays is 2, so we return
                 2.

    --- Example 2 ---
    Input: nums1 = [1,2,3,6], nums2 = [2,3,4,5]
    Output: 2
    Explanation: There are two common elements in the array 2 and 3 out of
                 which 2 is the smallest, so 2 is returned.


    *** Constraints ***
    1 <= nums1.length, nums2.length <= 10^5
    1 <= nums1[i], nums2[j] <= 10^9
    Both nums1 and nums2 are sorted in non-decreasing order.

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 29.18% */
/* Space Beats: 57.58% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(1)        */
class Solution_Binary_Search {
public:
    int getCommon(vector<int>& nums1, vector<int>& nums2)
    {
        const int N = nums1.size();
        const int M = nums2.size();
        int result = 0;

        for (int i = 0; i < N; i++)
        {
            int target = nums1[i];

            // O(N * logN)
            auto iter = lower_bound(nums2.begin(), nums2.end(), target);

            if (iter != nums2.end() && *iter == target)
                return target;
        }

        return -1;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  96.92% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Linear {
public:
    int getCommon(vector<int>& nums1, vector<int>& nums2)
    {
        const int N = nums1.size();
        const int M = nums2.size();
        int result = 0;

        int i = 0;
        int j = 0;
        while (i < N && j < M)
        {
            if (nums1[i] == nums2[j])
            {
                result = nums1[i];
                break;
            }

            if (nums1[i] < nums2[j])
                i++;
            else
                j++;
        }
        

        return result == 0 ? -1 : result;
    }
};
