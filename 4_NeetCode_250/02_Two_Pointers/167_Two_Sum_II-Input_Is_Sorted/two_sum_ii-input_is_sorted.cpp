/*
    ==============
    === MEDIUM ===
    ==============

    =================================
    167) Two Sum II - Input Is Sorted
    =================================

    ============
    Description:
    ============

    Given a 1-indexed array of integers numbers that is already sorted in
    non-decreasing order, find two numbers such that they add up to a specific
    target number. Let these two numbers be numbers[index1] and numbers[index2]
    where 1 <= index1 < index2 < numbers.length.

    Return the indices of the two numbers, index1 and index2, added by one as
    an integer array [index1, index2] of length 2.

    The tests are generated such that there is exactly one solution. You may
    not use the same element twice.

    Your solution must use only constant extra space.

    ===============================================================
    FUNCTION: vector<int> twoSum(vector<int>& numbers, int target);
    ===============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: numbers = [2,7,11,15], target = 9
    Output: [1,2]
    Explanation: The sum of 2 and 7 is 9. Therefore, index1 = 1, index2 = 2. We
                 return [1, 2].


    --- Example 2 ---
    Input: numbers = [2,3,4], target = 6
    Output: [1,3]
    Explanation: The sum of 2 and 4 is 6. Therefore index1 = 1, index2 = 3. We
                 return [1, 3].


    --- Example 3 ---
    Input: numbers = [-1,0], target = -1
    Output: [1,2]
    Explanation: The sum of -1 and 0 is -1. Therefore index1 = 1, index2 = 2. We return [1, 2].


    *** Constraints ***
    2 <= numbers.length <= 3 * 10^4
    -1000 <= numbers[i] <= 1000
    numbers is sorted in non-decreasing order.
    -1000 <= target <= 1000
    The tests are generated such that there is exactly one solution.

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Since the Input is sorted everytime check:
        if (nums[left] + nums[right] == target)
            return {left+1, right+1};

    Otherwise, check if the sum is greater or lower than the current sum.

    If it's greater, then:
        right--; // Since that will decrease the sum since it's non-decreasing
                 // order of the Input "numbers"
    else
        left++; // This will increase the sum in next iteration since the Input
                // is sorted in non-decreasing order
*/

/* Time  Beats: 100.00% */
/* Space Beats:  31.04% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target)
    {
        int left  = 0;
        int right = numbers.size() - 1;

        while (left < right)
        {
            int sum = numbers[left] + numbers[right];

            if (sum == target)
                break;

            if (sum > target)
                right--;
            else
                left++;
        }

        return {left+1, right+1}; // Because indexing starts with 1
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This one is less common and less concise and less elegant Implementation,
    however, each time we have NOT found a correct answer, why would we move
    our 'L' or 'R' pointer by just one forward or backward, respectively?

    If there are multiple consecutive EQUAL values that CERTAINLY will NOT be
    our answer, why don't we just semantically designate "jumping over" all of
    those CONSECUTIVE INVALID values in a "single" iteration?

    That's what we're doing here.

    Instead of requiring multiple outer-loop iterations to "jump over" the
    consecutive elements that will NOT be a result, we simply do that in a
    single semantic step within the inner while-loop.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  63.19% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Semantic_Step {
public:
    vector<int> twoSum(vector<int>& numbers, int target)
    {
        const int N = numbers.size();

        int L = 0;
        int R = N-1;

        // O(N) (entire block)
        while (L < R)
        {
            int sum = numbers[L] + numbers[R];

            if (sum == target)
                break;

            if (sum < target)
            {
                // Single Semantic Step
                L++;
                while (L < R && numbers[L-1] == numbers[L])
                    L++;
            }
            else
            {
                // Single Semantic Step
                R--;
                while (L < R && numbers[R] == numbers[R+1])
                    R--;
            }
        }

        return {L+1, R+1};
    }
};
