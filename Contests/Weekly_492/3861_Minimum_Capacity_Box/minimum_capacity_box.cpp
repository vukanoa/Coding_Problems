/*
    ============
    === EASY ===
    ============

    ===========================
    3861) Minimum Capacity Box
    ===========================

    ============
    Description:
    ============

    You are given an integer array capacity, where capacity[i] represents the
    capacity of the ith box, and an integer itemSize representing the size of
    an item.

    The ith box can store the item if capacity[i] >= itemSize.

    Return an integer denoting the index of the box with the minimum capacity
    that can store the item. If multiple such boxes exist, return the smallest
    index.

    If no box can store the item, return -1.

    ================================================================
    FUNCTION: int minimumIndex(vector<int>& capacity, int itemSize);
    ================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: capacity = [1,5,3,7], itemSize = 3
    Output: 2
    Explanation:
    The box at index 2 has a capacity of 3, which is the minimum capacity that
    can store the item. Thus, the answer is 2.

    --- Example 2 ---
    Input: capacity = [3,5,4,3], itemSize = 2
    Output: 0
    Explanation:
    The minimum capacity that can store the item is 3, and it appears at
    indices 0 and 3. Thus, the answer is 0.

    --- Example 3 ---
    Input: capacity = [4], itemSize = 5
    Output: -1
    Explanation:
    No box has enough capacity to store the item, so the answer is -1.


    *** Constraints ***
    1 <= capacity.length <= 100
    1 <= capacity[i] <= 100
    1 <= itemSize <= 100

*/

#include <climits>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory.

*/

/* Time  Beats: 100.00% */
/* Space Beats: 100.00% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int minimumIndex(vector<int>& capacity, int itemSize)
    {
        const int N = capacity.size();
        int result_idx = INT_MAX;
        int result_cap = INT_MAX;

        for (int i = 0; i < N; i++)
        {
            if (capacity[i] < itemSize)
                continue;
                
            if (capacity[i] < result_cap)
            {
                result_cap = capacity[i];
                result_idx = i;
            }
        }

        return result_idx == INT_MAX ? -1 : result_idx;
    }
};
