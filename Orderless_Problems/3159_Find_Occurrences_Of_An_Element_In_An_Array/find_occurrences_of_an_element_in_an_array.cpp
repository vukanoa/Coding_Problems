/*
    ==============
    === MEDIUM ===
    ==============

    ================================================
    3159) Find Occurrences of an Element in an Array
    ================================================

    ============
    Description:
    ============

    You are given an integer array nums, an integer array queries, and an
    integer x.

    For each queries[i], you need to find the index of the queries[i]th
    occurrence of x in the nums array. If there are fewer than queries[i]
    occurrences of x, the answer should be -1 for that query.

    Return an integer array answer containing the answers to all queries.

    ===========================================================================================
    FUNCTION: vector<int> occurrencesOfElement(vector<int>& nums, vector<int>& queries, int x);
    ===========================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,3,1,7], queries = [1,3,2,4], x = 1
    Output: [0,-1,2,-1]
    Explanation:
        For the 1st query, the first occurrence of 1 is at index 0.
        For the 2nd query, there are only two occurrences of 1 in nums, so the answer is -1.
        For the 3rd query, the second occurrence of 1 is at index 2.
        For the 4th query, there are only two occurrences of 1 in nums, so the answer is -1.


    --- Example 2 ---
    Input: nums = [1,2,3], queries = [10], x = 5
    Output: [-1]
    Explanation:
        For the 1st query, 5 doesn't exist in nums, so the answer is -1.


    *** Constraints ***
    1 <= nums.length, queries.length <= 10^5
    1 <= queries[i] <= 10^5
    1 <= nums[i], x <= 10^4

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-Explanatory.

*/

/* Time  Beats: 70.17% */
/* Space Beats: 79.13% */

/* Time  Complexity: O(N + M) */
/* Space Complexity: O(N)     */
class Solution {
public:
    vector<int> occurrencesOfElement(vector<int>& nums, vector<int>& queries, int x)
    {
        const int N = nums.size();
        const int M = queries.size();

        vector<int> result(M, -1);

        vector<int> positions(N+1, -1);
        int order = 1;
        for (int i = 0; i < N; i++)
        {
            if (nums[i] == x)
                positions[order++] = i;
        }

        for (int j = 0; j < M; j++)
        {
            if (queries[j] <= N)
                result[j] = positions[queries[j]];
        }

        return result;
    }
};
