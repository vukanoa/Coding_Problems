/*
    ============
    === EASY ===
    ============

    ================================================
    2605) Form Smallest Number From Two Digit Arrays
    ================================================

    ============
    Description:
    ============

    Given two arrays of unique digits nums1 and nums2, return the smallest
    number that contains at least one digit from each array.

    ================================================================
    FUNCTION: int minNumber(vector<int>& nums1, vector<int>& nums2);
    ================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums1 = [4,1,3], nums2 = [5,7]
    Output: 15
    Explanation: The number 15 contains the digit 1 from nums1 and the digit 5
                 from nums2. It can be proven that 15 is the smallest number we
                 can have.

    --- Example 2 ---
    Input: nums1 = [3,5,2,6], nums2 = [3,1,7]
    Output: 3
    Explanation: The number 3 contains the digit 3 which exists in both arrays.


    *** Constraints ***
    1 <= nums1.length, nums2.length <= 9
    1 <= nums1[i], nums2[i] <= 9
    All digits in each array are unique.

*/

#include <algorithm>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  52.82% */

/* Time  Complexity: O(N + M) */
/* Space Complexity: O(1)     */
class Solution {
public:
    int minNumber(vector<int>& nums1, vector<int>& nums2)
    {
        const int N = nums1.size();
        const int M = nums2.size();

        vector<int> freq(10, 0);

        for (int i = 0; i < N; i++)
            freq[nums1[i]]++;

        for (int i = 0; i < M; i++)
            freq[nums2[i]]++;

        /* Min Elements */
        int min1 = *min_element(nums1.begin(), nums1.end());
        int min2 = *min_element(nums2.begin(), nums2.end());

        for (int num = 1; num < 10; num++)
        {
            if (freq[num] == 2) // It CANNOT be more than 2, since they're uniq
                return num;
        }

        if (min2 < min1)
            swap(min1, min2);

        return min1 * 10 + min2;
    }
};
