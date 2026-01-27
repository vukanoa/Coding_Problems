/*
    ============
    === EASY ===
    ============

    ===========================
    2032) Two out of Three
    ===========================

    ============
    Description:
    ============

    Given three integer arrays nums1, nums2, and nums3, return a distinct array
    containing all the values that are present in at least two out of the three
    arrays. You may return the values in any order. 

    ================================================================================================
    FUNCTION: vector<int> twoOutOfThree(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3);
    ================================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums1 = [1,1,3,2], nums2 = [2,3], nums3 = [3]
    Output: [3,2]
    Explanation: The values that are present in at least two arrays are:
    - 3, in all three arrays.
    - 2, in nums1 and nums2.

    --- Example 2 ---
    Input: nums1 = [3,1], nums2 = [2,3], nums3 = [1,2]
    Output: [2,3,1]
    Explanation: The values that are present in at least two arrays are:
    - 2, in nums2 and nums3.
    - 3, in nums1 and nums2.
    - 1, in nums1 and nums3.

    --- Example 3 ---
    Input: nums1 = [1,2,2], nums2 = [4,3,3], nums3 = [5]
    Output: []
    Explanation: No value is present in at least two arrays.

    *** Constraints ***
    1 <= nums1.length, nums2.length, nums3.length <= 100
    1 <= nums1[i], nums2[j], nums3[k] <= 100

*/

#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Simple use of bitmasks.

*/

/* Time  Beats: 40.19% */
/* Space Beats: 63.18% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    vector<int> twoOutOfThree(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3)
    {
        const int SIZE_1 = nums1.size();
        const int SIZE_2 = nums2.size();
        const int SIZE_3 = nums3.size();
        vector<int> result;

        unordered_map<int,int> umap;

        int i = 0;
        int j = 0;
        int k = 0;
        while (i < SIZE_1 || j < SIZE_2 || k < SIZE_3)
        {
            if (i < SIZE_1) umap[nums1[i++]] |= 1 << 2;
            if (j < SIZE_2) umap[nums2[j++]] |= 1 << 1;
            if (k < SIZE_3) umap[nums3[k++]] |= 1 << 0;
        }

        for (const auto& [number, bitmask] : umap)
        {
            if (bitmask == 0x03 ||
                bitmask == 0x05 ||
                bitmask == 0x06 ||
                bitmask == 0x07)
            {
                result.push_back(number);
            }
        }

        return result;
    }
};
