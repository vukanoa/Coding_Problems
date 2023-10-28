#include <iostream>
#include <vector>

/*
    ============
    === EASY ===
    ============

    =======================================
    26) Remove Duplicates From Sorted Array
    =======================================

    ============
    Description:
    ============

    Given an integer array "nums" sorted in non-decreasing order, remove the
    duplicates in-place such that each unique element appears only once. The
    relative order of the elements should be kept the same. Then return the
    number of unique elements in nums.

    Consider the number of unique elements of nums to be k, to get accepted,
    you need to do the following things:

    - Change the array nums such that the first k elements of nums contain the
      unique elements in the order they were present in nums initially. The
      remaining elements of nums are not important as well as the size of nums.

    - Return k.


    Custom Judge:

    The judge will test your solution with the following code:

        int[] nums = [...]; // Input array
        int[] expectedNums = [...]; // The expected answer with correct length

        int k = removeDuplicates(nums); // Calls your implementation

        assert k == expectedNums.length;
        for (int i = 0; i < k; i++) {
            assert nums[i] == expectedNums[i];
        }

    If all assertions pass, then your solution will be accepted.


    ==================================================
    FUNCTION: int removeDuplicates(vector<int>& nums);
    ==================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================


    --- Example 1 ---
    Input: nums = [1,1,2]
    Output: 2, nums = [1,2,_]

    Explanation: Your function should return k = 2, with the first two elements
    of nums being 1 and 2 respectively. It does not matter what you leave
    beyond the returned k (hence they are underscores).



    --- Example 2 ---
    Input: nums = [0,0,1,1,1,2,2,3,3,4]
    Output: 5, nums = [0,1,2,3,4,_,_,_,_,_]

    Explanation: Your function should return k = 5, with the first five
    elements of nums being 0, 1, 2, 3, and 4 respectively. It does not matter
    what you leave beyond the returned k (hence they are underscores).



    *** Constraints ***
    1 <= nums.length <= 3 * 104
    -100 <= nums[i] <= 100
    nums is sorted in non-decreasing order.

*/


/*
    ------------
    --- IDEA ---
    ------------

    Self_Explanatory

*/

/* Time  Beats: 97.65% */
/* Space Beats: 34.27% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_1 {
public:
    int removeDuplicates(std::vector<int>& nums)
    {
        int i = 0;
        for (int j = 1; j < nums.size(); j++)
        {
            if (nums[i] != nums[j])
            {
                i++;
                nums[i] = nums[j];
            }
        }

        return i + 1;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Another way of implementing it.

*/

/* Time  Beats: 97.57% */
/* Space Beats: 40.23% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_2 {
public:
    int removeDuplicates(std::vector<int>& nums)
    {
        int left  = 0;
        int right = 0;

        while (right < nums.size())
        {
            nums[left++] = nums[right++];

            while (right < nums.size() && nums[right - 1] == nums[right])
                right++;
        }

        return left;
    }
};


int
main()
{
    Solution_1 sol_1;
    Solution_2 sol_2;



    /* Example 1 */
    // std::vector<int> nums = {1, 1, 2};

    /* Example 2 */
    std::vector<int> nums = {0, 0, 1, 1, 1, 2, 2, 3, 3, 4};

    /* Example 3 */
    // std::vector<int> nums = {1, 2, 3, 4, 5};

    std::cout << "\n\t===========================================";
    std::cout << "\n\t=== REMOVE DUPLICATES FROM SORTED ARRAY ===";
    std::cout << "\n\t===========================================\n";


    /* Write Input */
    bool first = true;
    std::cout << "\n\tNums: [";
    for (auto x: nums)
    {
        if (!first)
            std::cout << ", ";

        std::cout << x;
        first = false;
    }
    std::cout << "]\n\n";


    /* Solution */
    // int result = sol_1.removeDuplicates(nums);
    int result = sol_2.removeDuplicates(nums);


    /* Write Output */
    std::cout << "\n\tOutput: " << result;

    first = true;
    std::cout << "\n\tNums: [";
    for (int x = 0; x < nums.size(); x++)
    {
        if (!first)
            std::cout << ", ";

        if (x < result)
            std::cout << nums[x];
        else 
            std::cout << "_";

        first = false;
    }
    std::cout << "]\n\n";


    return 0;
}
