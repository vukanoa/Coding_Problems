#include <iostream>
#include <vector>
#include <algorithm> // std::reverse()

/*
    ============
    === EASY ===
    ============

    ==============================
    977) Squares of a Sorted Array
    ==============================

    ============
    Description:
    ============

    Given an integer array nums sorted in non-decreasing order, return an array
    of the squares of each number sorted in non-decreasing order.


    Follow up: Squaring each element and sorting the new array is very trivial,
               could you find an O(n) solution using a different approach?


    =======================================================
    FUNCTION: vector<int> sortedSquares(vector<int>& nums);
    =======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [-4,-1,0,3,10]
    Output: [0,1,9,16,100]
    Explanation: After squaring, the array becomes [16,1,0,9,100].
    After sorting, it becomes [0,1,9,16,100].


    --- Example 2 ---
    Input: nums = [-7,-3,2,3,11]
    Output: [4,9,9,49,121]



    *** Constraints ***
    1 <= nums.length <= 10^4
    -104 <= nums[i] <= 10^4
    nums is sorted in non-decreasing order.

*/

/*
    ------------
    --- IDEA ---
    ------------

    This is the Naive approach, kind of.

    (Not really since the real Naive approach is to square each element first
    and then sort the entire array in O(n * logn), which is way too ineffcient
    and it would be trivial to imeplement).

    It's efficient, but we DON'T have to start "filling" our
    result vector from the front. That's where the naiveness lies.

    The first one below demonstrates what it has to be done if we want to push
    to the front.

    And the other Solution down below, the bottom one, shows how clean and easy
    it is if we start from the back and start "filling" with largest values
    first.


    Also, it's important to note that we MUST first push greatest squared
    elements, since we can determine in O(1) which of the two elements is going
    to have a greater square. That's why we use "Two Pointers" technique".

    Consider this:

        nums =  [-7, -3,  2,  3, 11]
                  0   1   2   3   4

        This is the Output:
        Output: [ 4,  9,  9, 49, 121]
                  0   1   2   3   4

    At first, you may think you want to build the Output from the bottom-up,
    meaning you first want to put 4, then 9, etc.

    However, you'll quickly realize you can't do that efficiently. Think about
    it - Which number in our Input "nums" is going to have the lowest squred
    value?

    Well, it's going to be 2, which is somewhere in the middle. Were it even
    bigger example, we would've had an even bigger problem, therefore we must
    begin by searching for elements that will have the GREATEST squared values.

    How can we "find" those?
    They are either on the left edge or on the right edge of our SORTED array
    "nums".

    Since squaring a number "doesn't care" if it's a positive or negative since
    after the square it's always going to be positive, then we only care about
    the absolute value of a number.

            abs
        -7 ------> 7
        11 ------> 11

    Which of the two will give us a bigger squared value?
    11, because its absolute value is greater than the absolute value of -7
    which is 7.

    Therefore, we'll just take either the leftmost or the rightmost element
    based on their absolute values and we'll square the greater absolute value
    and put it "on the back" of our vector "results".

    The Bottom one(2nd Solution) doesn't put squared number "on the back", but
    puts them in their right order immediately, which remove the need for
    reversing the "result" vector afterwards.

*/

/* Time  Beats: 97.65% */
/* Space Beats: 15.61% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */ // We shan't count "result" as additional memory
class Solution {
public:
    std::vector<int> sortedSquares(std::vector<int>& nums)
    {
        int left  = 0;
        int right = nums.size() - 1;

        std::vector<int> result;

        while (left <= right)
        {
            if (std::abs(nums[left]) <= std::abs(nums[right]))
                result.push_back(nums[right] * nums[right--]);
            else
                result.push_back(nums[left]  * nums[left++]);
        }

        std::reverse(result.begin(), result.end());

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same idea, however, we don't need to reverse the "result" afterwards, since
    we've put every element in its place once we were squaring it.

*/

/* Time  Beats: 99.64% */
/* Space Beats: 38.25% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_2 {
public:
    std::vector<int> sortedSquares(std::vector<int>& nums)
    {
        int n = nums.size();

        std::vector<int> result(n);

        int left  = 0;
        int right = n-1;

        int idx = n-1;
        while (left <= right)
        {
            if (std::abs(nums[left]) <= std::abs(nums[right]))
                result[idx--] = nums[right] * nums[right--];
            else
                result[idx--] = nums[left]  * nums[left++];
        }

        return result;
    }
};
