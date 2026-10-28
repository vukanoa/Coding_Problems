/*
    ==============
    === MEDIUM ===
    ==============

    =======================================
    3876) Construct Uniform Parity Array II 
    =======================================

    ============
    Description:
    ============

    You are given an array nums1 of n distinct integers.

    You want to construct another array nums2 of length n such that the
    elements in nums2 are either all odd or all even.

    For each index i, you must choose exactly one of the following (in any
    order):

        + nums2[i] = nums1[i]
        + nums2[i] = nums1[i] - nums1[j], for an index j != i, such that nums1[i] - nums1[j] >= 1

    Return true if it is possible to construct such an array, otherwise return false.

    ================================================
    FUNCTION: bool uniformArray(vector<int>& nums1);
    ================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums1 = [1,4,7]
    Output: true
    Explanation:
        Set nums2[0] = nums1[0] = 1.
        Set nums2[1] = nums1[1] - nums1[0] = 4 - 1 = 3.
        Set nums2[2] = nums1[2] = 7.
        nums2 = [1, 3, 7], and all elements are odd. Thus, the answer is true.


    --- Example 2 ---
    Input: nums1 = [2,3]
    Output: false
    Explanation:
    It is not possible to construct nums2 such that all elements have the same
    parity. Thus, the answer is false.


    --- Example 3 ---
    Input: nums1 = [4,6]
    Output: true
    Explanation:
        Set nums2[0] = nums1[0] = 4.
        Set nums2[1] = nums1[1] = 6.
        nums2 = [4, 6], and all elements are even. Thus, the answer is true.


    *** Constraints ***
    1 <= n == nums1.length <= 10^5
    1 <= nums1[i] <= 10^9
    nums1 consists of distinct integers.

*/

#include <climits>
#include <cstdint>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 30.17% */
/* Space Beats: 20.89% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_1 {
public:
    bool uniformArray(vector<int>& nums1)
    {
        const int N = nums1.size();

        int even = 0;
        int odd  = 0;

        int smallest_element  = INT_MAX;
        for (const int& num : nums1)
        {
            if (num & 1)
                ++odd;
            else
                ++even;

            smallest_element = min(smallest_element, num);
        }

        if (odd == N || even == N)
            return true;

        return smallest_element & 1;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 65.72% */
/* Space Beats: 55.66% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_2 {
public:
    bool uniformArray(vector<int>& nums1)
    {
        int  smallest_element   = nums1[0];
        bool odd_exist_in_nums1 = false;

        for (const int& num : nums1)
        {
            smallest_element    = min(smallest_element, num);
            odd_exist_in_nums1 |= num & 1;
        }

        return (smallest_element & 1) == odd_exist_in_nums1;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  83.41% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_3 {
public:
    bool uniformArray(vector<int>& nums1)
    {
        uint32_t smallest[2] = {-1u, -1u}; // {even, odd}

        for (const uint32_t& num : nums1)
            smallest[num & 1] = min(smallest[num & 1], num);

        // TRUE IF: The min is odd || ALL of the elemnts are EVEN
        return smallest[1] < smallest[0] | smallest[1] == -1u;
    }
};
