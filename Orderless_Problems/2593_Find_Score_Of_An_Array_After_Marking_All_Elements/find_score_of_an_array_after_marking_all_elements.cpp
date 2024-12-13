#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    =======================================================
    2593) Find Score of an Array After Marking All Elements
    =======================================================

    ============
    Description:
    ============

    You are given an array nums consisting of positive integers.

    Starting with score = 0, apply the following algorithm:

        + Choose the smallest integer of the array that is not marked. If there
          is a tie, choose the one with the smallest index.

        + Add the value of the chosen integer to score.

        + Mark the chosen element and its two adjacent elements if they exist.

        + Repeat until all the array elements are marked.

    Return the score you get after applying the above algorithm.

    =================================================
    FUNCTION: long long findScore(vector<int>& nums);
    =================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [2,1,3,4,5,2]
    Output: 7
    Explanation: We mark the elements as follows:
    - 1 is the smallest unmarked element, so we mark it and its two adjacent elements: [2,1,3,4,5,2].
    - 2 is the smallest unmarked element, so we mark it and its left adjacent element: [2,1,3,4,5,2].
    - 4 is the only remaining unmarked element, so we mark it: [2,1,3,4,5,2].
    Our score is 1 + 2 + 4 = 7.


    --- Example 2 ---
    Input: nums = [2,3,5,1,3,2]
    Output: 5
    Explanation: We mark the elements as follows:
    - 1 is the smallest unmarked element, so we mark it and its two adjacent elements: [2,3,5,1,3,2].
    - 2 is the smallest unmarked element, since there are two of them, we choose the left-most one, so we mark the one at index 0 and its right adjacent element: [2,3,5,1,3,2].
    - 2 is the only remaining unmarked element, so we mark it: [2,3,5,1,3,2].
    Our score is 1 + 2 + 2 = 5.


    *** Constraints ***
    1 <= nums.length <= 10^5
    1 <= nums[i] <= 10^6

*/

using namespace std;


/*
    ------------
    --- IDEA ---
    ------------

    Create a new vector 'vec" that will has pairs of {value, index} from the
    original vector "nums" and then sort it.

    Create an additional vector "marked" of bool type that will be used as a
    HashMap to check whether some element has already been marked or not.

    That's about it.

*/

/* Time  Beats: 86.28% */
/* Space Beats: 57.19% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n)        */
class Solution {
public:
    long long findScore(vector<int>& nums)
    {
        const int n = nums.size();
        long long score = 0;

        vector<pair<int,int>> vec;
        for (int i = 0; i < n; i++)
            vec.push_back( {nums[i], i} );

        /* Sort */
        sort(vec.begin(), vec.end());

        vector<bool> marked(n, false);
        for (int i = 0; i < n; i++)
        {
            if (marked[vec[i].second])
                continue;

            score += vec[i].first;
            marked[vec[i].second] = true;

            if (vec[i].second > 0)
                marked[vec[i].second - 1] = true;

            if (vec[i].second < n-1)
                marked[vec[i].second + 1] = true;
        }

        return score;
    }
};
