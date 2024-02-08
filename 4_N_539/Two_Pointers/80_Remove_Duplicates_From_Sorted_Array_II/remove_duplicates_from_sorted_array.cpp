#include <iostream>

/*
    ==============
    === MEDIUM ===
    ==============

    ==========================================
    80) Remove Duplicates from Sorted Array II
    ==========================================

    ============
    Description:
    ============

    Given an integer array nums sorted in non-decreasing order, remove some
    duplicates in-place such that each unique element appears at most twice.
    The relative order of the elements should be kept the same.

    Since it is impossible to change the length of the array in some languages,
    you must instead have the result be placed in the first part of the array
    nums. More formally, if there are k elements after removing the duplicates,
    then the first k elements of nums should hold the final result. It does not
    matter what you leave beyond the first k elements.

    Return k after placing the final result in the first k slots of nums.

    Do not allocate extra space for another array. You must do this by
    modifying the input array in-place with O(1) extra memory.

    Custom Judge:

    The judge will test your solution with the following code:

    int[] nums = [...]; // Input array int[] expectedNums = [...]; // The
    expected answer with correct length

    int k = removeDuplicates(nums); // Calls your implementation

    assert k == expectedNums.length; for (int i = 0; i < k; i++) { assert
    nums[i] == expectedNums[i]; }

    If all assertions pass, then your solution will be accepted.

    ==================================================
    FUNCTION: int removeDuplicates(vector<int>& nums);
    ==================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,1,1,2,2,3]
    Output: 5, nums = [1,1,2,2,3,_]
    Explanation: Your function should return k = 5, with the first five
                 elements of nums being 1, 1, 2, 2 and 3 respectively.  It does
                 not matter what you leave beyond the returned k (hence they
                 are underscores).


    --- Example 2 ---
    Input: nums = [0,0,1,1,1,1,2,3,3]
    Output: 7, nums = [0,0,1,1,2,3,3,_,_]
    Explanation: Your function should return k = 7, with the first seven
                 elements of nums being 0, 0, 1, 1, 2, 3 and 3 respectively.
                 It does not matter what you leave beyond the returned k (hence
                 they are underscores).


    *** Constraints ***
    1 <= nums.length <= 3 * 10^4
    -10^4 <= nums[i] <= 10^4
    nums is sorted in non-decreasing order.

*/

/*
    ------------
    --- IDEA ---
    ------------

    I wanted to check if a Solution that uses HashMap will even work. It turns
    out that it does.

    So here is it.

*/

/* Time  Beats: 78.52% */
/* Space Beats: 13.73% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_HashMap {
public:
    int removeDuplicates(vector<int>& nums)
    {
        int left  = 0;
        int right = 0;

        std::unordered_map<int, int> umap;

        while (right < nums.size())
        {
            if (umap[nums[right]] < 2)
            {
                nums[left++] = nums[right];
                umap[nums[right]]++;
            }

            right++;
        }

        return left;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This one is what they actually want. It's O(1) Space Complexity.

    We are starting at index 2 and everytime we only check if element at
    curr_index is different than element at curr_index - 2.

    If it is, then we can place nums[right](i.e. curren element) at nums[left]
    and increment the left.

    Being different or not, we always increment "right" pointer.

*/

/* Time  Beats: 100% */
/* Space Beats: 13.88% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Space_O1 {
public:
    int removeDuplicates(vector<int>& nums)
    {
        if (nums.size() <= 2)
            return nums.size();

        int left  = 2;
        int right = 2;

        while (right < nums.size())
        {
            if (nums[left - 2] != nums[right])
                nums[left++] = nums[right];

            right++;
        }

        return left;
    }
};
