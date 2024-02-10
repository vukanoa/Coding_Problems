#include <iostream>
#include <vector>
#include <algorithm>

/*
    ==============
    === MEDIUM ===
    ==============

    ========================================================
    1968) Array With Elements Not Equal to Average Neighbors
    ========================================================

    ============
    Description:
    ============

    You are given a 0-indexed array nums of distinct integers. You want to
    rearrange the elements in the array such that every element in the
    rearranged array is not equal to the average of its neighbors.

    More formally, the rearranged array should have the property such that for
    every i in the range 1 <= i < nums.length - 1, (nums[i-1] + nums[i+1]) / 2
    is not equal to nums[i].

    Return any rearrangement of nums that meets the requirements.

    ========================================================
    FUNCTION: vector<int> rearrangeArray(vector<int>& nums);
    ========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,3,4,5]
    Output: [1,2,4,5,3]
    Explanation:
    When i=1, nums[i] = 2, and the average of its neighbors is (1+4) / 2 = 2.5.
    When i=2, nums[i] = 4, and the average of its neighbors is (2+5) / 2 = 3.5.
    When i=3, nums[i] = 5, and the average of its neighbors is (4+3) / 2 = 3.5.

    --- Example 2 ---
    Input: nums = [6,2,0,9,7]
    Output: [9,7,6,2,0]
    Explanation:
    When i=1, nums[i] = 7, and the average of its neighbors is (9+6) / 2 = 7.5.
    When i=2, nums[i] = 6, and the average of its neighbors is (7+2) / 2 = 4.5.
    When i=3, nums[i] = 2, and the average of its neighbors is (6+0) / 2 = 3.


    *** Constraints ***
    3 <= nums.length <= 105
    0 <= nums[i] <= 105

*/

/*
    ------------
    --- IDEA ---
    ------------

    The first thing that comes to mind is the naive approach which is: Find one
    permutation that fulfills all the conditions.

    However, that would take us O(n!) time, which is way too inefficient.

    Since we're realizing that the Brute Force is not something close to (n^2),
    but O(n!), that suggests that if we sort, nothing will happen. Meaning the
    Time Complexity wouldn't get worse.

    Is that going to help us?

    Well, we don't know, however it's certainly an option.
    Next question we can pose to ourselves is: How can we be sure that the
    average sum of "left" and "right" is not equal to the current element?

    Let's look at the basic example:

        nums = [1, 2, 3, 4, 5]

        _ 2 _ _ _
          ^
          |
          |
    If we put 2 here, how can we make sure that 2 isn't the average sum of
    elements left and right to it?

    One way that certain works is to make both left and right elements GREATER
    than 2. For example:

        4 2 5 _ _

    This way we are 100% certain that 2 cannot be the average sum of its left
    and right element.

    However, if we take the greatest element in our array "nums", element 5,
    how can we put its left and right elements to be greater than the 5 if
        1) All elements are distinct
        2) 5 is the greatest element in our array
    ?

    Well, the answer is we can't. However, making both left and right elements
    to be greater is not the only way to ensure that the current elements is
    NOT the average sum of its left and right element.

    Another way to ensure that would be to make both left and right elements
    SMALLER than the current element.

    For example:

        _ _ 2 5 3


    Okay, now we know 2 things:
        1) We are allowed to sort
        2) In order to ensure that the element is at the right spot we either
           have to make its left and right neighbor:
             a) Greater than him
             b) Lower   than him


    Therefore, we'll construct a new array of n empty slots and we'll put first
    n/2 elements and even positions.
    Then, we'll put the remaining elements at the odd positions.

    So, an example like:
        nums = [4, 2, 1, 5, 3]


    Is solved like this:
        1) Sort it
            nums = [1, 2, 3, 4, 5]

        2) Construct new array "results" with n empty slots
            std::vector<int> results(n);

        3) Put first n/2 elements from "nums" at even positions in "results"

        4) Put the remaining elements from "nums" at odd positions in "results"

*/

/* Time  Beats: 45.80% */
/* Space Beats: 77.10% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(1)        */ // Depending on the sort
class Solution {
public:
    std::vector<int> rearrangeArray(vector<int>& nums)
    {
        std::sort(nums.begin(), nums.end());

        int left_half = nums.size() / 2;
        left_half += nums.size() & 1 ? 1 : 0;

        std::vector<int> results(nums.size());

        int pos = 0;
        for(int i = 0; i < left_half; i++)
        {
            results[pos] = nums[i];
            pos += 2;
        }

        pos = 1;
        for (int i = left_half; i < nums.size(); i++)
        {
            results[pos] = nums[i];
            pos += 2;
        }

        return results;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same as above, implemented differently.

*/

/* Time  Beats: 69.89% */
/* Space Beats: 35.05% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(1)        */ // Depending on the sort
class Solution_2 {
public:
    std::vector<int> rearrangeArray(vector<int>& nums)
    {
        int n = nums.size();

        std::sort(nums.begin(), nums.end());
        std::vector<int> result(n);

        int left = 0;

        for (int i = 0; i < n; i+=2)
            result[i] = nums[left++];

        for (int i = 1; i < n; i+=2)
            result[i] = nums[left++];

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Read the "IDEA" of the first Solution in this file.

    Up to here:

    Okay, now we know 2 things:
        1) We are allowed to sort
        2) In order to ensure that the element is at the right spot we either
           have to make its left and right neighbor:
             a) Greater than him
             b) Lower   than him


    is the same.


    However, now, instead of putting first half of elements at even positions,
    we'll construct the "results" array by alternating smallest and largest
    elements and put them consecutively.

    Therefore:
        1) Sort it
            nums = [1, 2, 3, 4, 5]

        2) Construct new array "results" with n empty slots
            std::vector<int> results(n);

        3) Push the element at the "left" pointer to "results" and increment
           the "left" pointer.

        4) If (left <= right) Push the element at the "right" pointer to
           "results" and decrement the "right" pointer.

               The purpose of this conditional push of the "right" pointers is
               this:

                   nums    = [1, 2, 3, 4, 5, 6]
                                    L  R

                   results = [1, 6, 2, 5, 0, 0]


               We now push 'L' and the INCREMENT the 'L'.

                   nums    = [1, 2, 3, 4, 5, 6]
                                       L
                                       R

                   results = [1, 6, 2, 5, 3, 0]

                And now we want to push the element at 'R' as well. Therefore
                if (L <= R)
                    results.push_back(nums[R--]);

                We MUST put '<=' and not '<' because after we put 'L' we indeed
                INCREMENT. Therefore, before putting 'R', our 'L' is already
                INCREMENTED.


                Also, another reason we do it like this is if we have an odd
                number of elements in "nums":

                   nums    = [1, 2, 3, 4, 5]
                                    L
                                    R

                   results = [1, 5, 2, 4, 0]

                Now if we put element at 'L' and INCREMENT it, we'll be at this
                position:

                   nums    = [1, 2, 3, 4, 5]
                                    R  L

                   results = [1, 5, 2, 4, 3]

                Meaning, we DO NOT have any more elements to process, therefore
                just stop. Putting a 'R' element would be a mistake.

*/

/* Time  Beats: 27.45% */
/* Space Beats: 10.49% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(1)        */ // Depending on the sort
class Solution_3 {
public:
    std::vector<int> rearrangeArray(vector<int>& nums)
    {
        std::sort(nums.begin(), nums.end());

        int left  = 0;
        int right = nums.size() - 1;

        std::vector<int> results;
        while (results.size() != nums.size())
        {
            results.push_back(nums[left++]);

            if (left <= right)
                results.push_back(nums[right--]);
        }

        return results;
    }
};
