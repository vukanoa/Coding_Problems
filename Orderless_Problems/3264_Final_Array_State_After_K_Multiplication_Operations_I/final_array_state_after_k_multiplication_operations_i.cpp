/*
    ============
    === EASY ===
    ============

    ===========================================================
    3264) Final Array State After K Multiplication Operations I
    ===========================================================

    ============
    Description:
    ============

    You are given an integer array nums, an integer k, and an integer
    multiplier.

    You need to perform k operations on nums. In each operation:

        + Find the minimum value x in nums. If there are multiple occurrences
          of the minimum value, select the one that appears first.

        + Replace the selected minimum value x with x * multiplier.

    Return an integer array denoting the final state of nums after performing
    all k operations.

    ==============================================================================
    FUNCTION: vector<int> getFinalState(vector<int>& nums, int k, int multiplier); 
    ==============================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [2,1,3,5,6], k = 5, multiplier = 2
    Output: [8,4,6,5,6]
    Explanation:
    Operation          Result
    After operation 1  [2, 2, 3, 5, 6]
    After operation 2  [4, 2, 3, 5, 6]
    After operation 3  [4, 4, 3, 5, 6]
    After operation 4  [4, 4, 6, 5, 6]
    After operation 5  [8, 4, 6, 5, 6]


    --- Example 2 ---
    Input: nums = [1,2], k = 3, multiplier = 4
    Output: [16,8]
    Explanation:
    Operation          Result
    After operation 1  [4, 2]
    After operation 2  [4, 8]
    After operation 3  [16, 8]


    *** Constraints ***
    1 <= nums.length <= 100
    1 <= nums[i] <= 100
    1 <= k <= 10
    1 <= multiplier <= 5

*/

#include <queue>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Fundamental Heap problem. The only thing you have to "worry about" is that
    you must keep indices as the second value in pair because we need to return
    nums in order in which was given.

*/

/* Time  Beats: 20.56% */
/* Space Beats: 25.16% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n)        */
class Solution {
public:
    vector<int> getFinalState(vector<int>& nums, int k, int multiplier)
    {
        const int n = nums.size();

        std::priority_queue<std::pair<int, int>,
                            std::vector<std::pair<int, int>>,
                            std::greater<std::pair<int, int>>> min_heap;

        // Push to Heap
        for (int i = 0; i < n; i++)
            min_heap.push( {nums[i], i} );

        for (int i = 0; i < k; i++)
        {
            auto [top, idx] = min_heap.top();
            min_heap.pop();

            top *= multiplier;

            min_heap.push( {top, idx} );
        }

        while ( ! min_heap.empty())
        {
            auto [top, idx] = min_heap.top();
            min_heap.pop();

            nums[idx] = top;
        }

        return nums;
    }
};
