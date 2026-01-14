/*
    ============
    === EASY ===
    ============

    ===========================
    88) Merge Sorted Array
    ===========================

    ============
    Description:
    ============

    You are given two integer arrays nums1 and nums2, sorted in non-decreasing
    order, and two integers m and n, representing the number of elements in
    nums1 and nums2 respectively.

    Merge nums1 and nums2 into a single array sorted in non-decreasing order.

    The final sorted array should not be returned by the function, but instead
    be stored inside the array nums1. To accommodate this, nums1 has a length
    of m + n, where the first m elements denote the elements that should be
    merged, and the last n elements are set to 0 and should be ignored. nums2
    has a length of n.

    Follow up: Can you come up with an algorithm that runs in O(m + n) time?

    ===========================================================================
    FUNCTION: void merge(vector<int>& nums1, int m, vector<int>& nums2, int n);
    ===========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3
    Output: [1,2,2,3,5,6]

    --- Example 2 ---
    Input: nums1 = [1], m = 1, nums2 = [], n = 0
    Output: [1]

    --- Example 3 ---
    Input: nums1 = [0], m = 0, nums2 = [1], n = 1
    Output: [1]

    *** Constraints ***
    nums1.length == m + n
    nums2.length == n
    0 <= m, n <= 200
    1 <= m + n <= 200
    -109 <= nums1[i], nums2[j] <= 109

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    The "trick" here is to begin "populating" from the back. That's it.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  95.61% */

/* Time  Complexity: O(M + N) */
/* Space Complexity: O(1)     */
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n)
    {
        if (n == 0)
            return;

        int one = m-1;
        int two = n-1;

        // O(m + n) (entire block)
        for (int i = m+n-1; i >=0; i--) // i <==> last_unfilled_idx
        {
            if (one >= 0 && nums1[one] >= nums2[two])
                nums1[i] = nums1[one--];
            else
                nums1[i] = nums2[two--];
        }
    }
};
