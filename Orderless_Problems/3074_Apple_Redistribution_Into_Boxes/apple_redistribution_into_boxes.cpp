/*
    ============
    === EASY ===
    ============

    =====================================
    3074) Apple Redistribution into Boxes
    =====================================

    ============
    Description:
    ============

    You are given an array apple of size n and an array capacity of size m.

    There are n packs where the ith pack contains apple[i] apples. There are m
    boxes as well, and the ith box has a capacity of capacity[i] apples.

    Return the minimum number of boxes you need to select to redistribute these
    n packs of apples into boxes.

    =====
    Note: that, apples from the same pack can be distributed into different
          boxes.
    =====

    ======================================================================
    FUNCTION: int minimumBoxes(vector<int>& apple, vector<int>& capacity);
    ======================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: apple = [1,3,2], capacity = [4,3,1,5,2]
    Output: 2
    Explanation: We will use boxes with capacities 4 and 5.
    It is possible to distribute the apples as the total capacity is greater
    than or equal to the total number of apples.

    --- Example 2 ---
    Input: apple = [5,5,5], capacity = [2,4,2,7]
    Output: 4
    Explanation: We will need to use all the boxes.

    *** Constraints ***
    1 <= n == apple.length <= 50
    1 <= m == capacity.length <= 50
    1 <= apple[i], capacity[i] <= 50
    The input is generated such that it's possible to redistribute packs of
    apples into boxes.

*/

#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  71.29% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(logN)     */ // Log because Introsort's TC
class Solution {
public:
    int minimumBoxes(vector<int>& apple, vector<int>& capacity)
    {
        const int N = apple.size();
        const int M = capacity.size();

        int result = 0;

        /* Sort */
        sort(capacity.begin(), capacity.end(), greater<int>());

        int apples = accumulate(apple.begin(), apple.end(), 0);
        int cap = 0;

        if (cap >= apples)
            return result;

        for (int i = 0; i < M; i++)
        {
            cap += capacity[i];
            result++;

            if (cap >= apples)
                return result;
        }

        return -1;
    }
};
