/*
    ============
    === EASY ===
    ============

    ======================================
    3875) Construct Uniform Parity Array I
    ======================================

    ============
    Description:
    ============

    You are given an array nums1 of n distinct integers.

    You want to construct another array nums2 of length n such that the
    elements in nums2 are either all odd or all even.

    For each index i, you must choose exactly one of the following (in any
    order):

        + nums2[i] = nums1[i]
        + nums2[i] = nums1[i] - nums1[j], for an index j != i

    Return true if it is possible to construct such an array, otherwise, return
    false.

    ================================================
    FUNCTION: bool uniformArray(vector<int>& nums1);
    ================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums1 = [2,3]
    Output: true
    Explanation:
        Choose nums2[0] = nums1[0] - nums1[1] = 2 - 3 = -1.
        Choose nums2[1] = nums1[1] = 3.
        nums2 = [-1, 3], and both elements are odd. Thus, the answer is
        true.

    --- Example 2 ---
    Input: nums1 = [4,6]
    Output: true
    Explanation:
        Choose nums2[0] = nums1[0] = 4.
        Choose nums2[1] = nums1[1] = 6.
        nums2 = [4, 6], and all elements are even. Thus, the answer is true.


    *** Constraints ***
    1 <= n == nums1.length <= 100
    1 <= nums1[i] <= 100
    nums1 consists of distinct integers.

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    If ALL elements of nums1 are EVEN, then we can take those same elements in
    the exact same order for nums2 and thus return true.

    If ALL elements of nums1 are ODD,  then we can take those same elements in
    the exact same order for nums2 and thus return true.

    If there is a mixture of EVEN and ODD elements, then we certainly can
    always make either odd or even entire nums2.

    How?

    Because:
        ODD_number  - EVEN_number = ODD_number  (5 - 2 = 3)
        ODD_number  - ODD_number  = EVEN_number (5 - 3 = 2)
        EVEN_number - ODD_number  = ODD_number  (6 - 3 = 3)
        EVEN_number - EVEN_number = EVEN_number (6 - 2 = 4)

    Therefore, there's always a combination to obtain an EVEN or ODD number if
    the elements in nums1 are mixed.

    Therefore, we ALWAYS return "true".

*/

class Solution {
public:
    bool uniformArray(vector<int>& nums1)
    {
        return true;
    }
};
