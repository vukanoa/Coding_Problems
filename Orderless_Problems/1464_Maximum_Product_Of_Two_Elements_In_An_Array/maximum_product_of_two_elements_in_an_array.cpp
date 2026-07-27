/*
    ============
    === EASY ===
    ============

    =================================================
    1464) Maximum Product of Two Elements in an Array
    =================================================

    ============
    Description:
    ============

    Given the array of integers nums, you will choose two different indices i
    and j of that array. Return the maximum value of (nums[i]-1)*(nums[j]-1). 

    ============================================
    FUNCTION: int maxProduct(vector<int>& nums);
    ============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [3,4,5,2]
    Output: 12 
    Explanation: If you choose the indices i=1 and j=2 (indexed from 0), you
                 will get the maximum value, that is, (nums[1]-1)*(nums[2]-1) =
                 (4-1)*(5-1) = 3*4 = 12. 

    --- Example 2 ---
    Input: nums = [1,5,4,5]
    Output: 16
    Explanation: Choosing the indices i=1 and j=3 (indexed from 0), you will
                 get the maximum value of (5-1)*(5-1) = 16.

    --- Example 3 ---
    Input: nums = [3,7]
    Output: 12


    *** Constraints ***
    2 <= nums.length <= 500
    1 <= nums[i] <= 10^3

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
/* Space Beats:  85.48% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int maxProduct(vector<int>& nums)
    {
        int one = 0;
        int two = 0;

        for (const int& num : nums)
        {
            if (num >= one)
            {
                two = one;
                one = num;
            }
            else if (num > two)
            {
                two = num;
            }
        }

        return (one - 1) * (two - 1);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    It's important to know these little techniques in C++.

    ########################################################################
    nth_element(nums.begin(), nums.begin() + 1, nums.end(), greater<int>());
    ########################################################################

    + Arrange nums so that nums[1] contains the 2nd largest element.

    + nums[0] is guaranteed to be GREATER THAN OR EQUAL to nums[1]. 

    + Every element AFTER nums[1] is guaranteed to be LESS THAN OR EQUAL TO
      nums[1].

    For example:
        nums = {5, 1, 8, 3, 7}


    After we apply:

    ########################################################################
    nth_element(nums.begin(), nums.begin() + 1, nums.end(), greater<int>());
    ########################################################################

    Possible results are:

        {8, 7, 5, 3, 1}
        {8, 7, 1, 5, 3}
        {8, 7, 3, 1, 5}

    After the function, guarantees are:
        + nums[1] == 7, i.e. the second-largest element
        + Elems that come BEFORE index 1 are GREATER THAN OR EQUAL TO nums[1]
        + Elems that come AFTER  index 1 are LESS    THAN OR EQUAL TO nums[1].

*/

/* Time  Beats: 100.00% */
/* Space Beats:  99.05% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_nth_element {
public:
    int maxProduct(vector<int>& nums)
    {
        nth_element(nums.begin(), nums.begin()+1, nums.end(), greater<int>());

        return (nums[0] - 1) * (nums[1] - 1);
    }
};
