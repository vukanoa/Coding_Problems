/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    870) Advantage Shuffle
    ===========================

    ============
    Description:
    ============

    You are given two integer arrays nums1 and nums2 both of the same length.
    The advantage of nums1 with respect to nums2 is the number of indices i for
    which nums1[i] > nums2[i].

    Return any permutation of nums1 that maximizes its advantage with respect
    to nums2.

    =============================================================================
    FUNCTION: vector<int> advantageCount(vector<int>& nums1, vector<int>& nums2);
    =============================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums1 = [2,7,11,15], nums2 = [1,10,4,11]
    Output: [2,11,7,15]

    --- Example 2 ---
    Input: nums1 = [12,24,8,32], nums2 = [13,25,32,11]
    Output: [24,32,8,12]



    *** Constraints ***
    1 <= nums1.length <= 10^5
    nums2.length == nums1.length
    0 <= nums1[i], nums2[i] <= 10^9

*/

#include <set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 27.75% */
/* Space Beats: 28.11% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution {
public:
    vector<int> advantageCount(vector<int>& nums1, vector<int>& nums2)
    {
        const int N = nums1.size(); // nums1.size() <==> nums2.size()

        // Sorted in ASCENDING order by the nature of the DataStructure.
        multiset<int> multiset(nums1.begin(), nums1.end());

        for (auto i = 0; i < N; ++i)
        {
            auto iter = multiset.upper_bound(nums2[i]);

            if (iter == multiset.end())
                iter = multiset.begin();

            nums1[i] = *iter;
            multiset.erase(iter);
        }

        return nums1;
    }
};
