/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    932) Beautiful Array
    ===========================

    ============
    Description:
    ============

    An array nums of length n is beautiful if:

        + nums is a permutation of the integers in the range [1, n].

        + For every 0 <= i < j < n, there is no index k with i < k < j where
          2 * nums[k] == nums[i] + nums[j].

    Given the integer n, return any beautiful array nums of length n. There
    will be at least one valid answer for the given n.

    ============================================
    FUNCTION: vector<int> beautifulArray(int n);
    ============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 4
    Output: [2,1,4,3]

    --- Example 2 ---
    Input: n = 5
    Output: [3,1,2,5,4]


    *** Constraints ***
    1 <= n <= 1000

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  88.78% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    vector<int> beautifulArray(int N)
    {
        vector<int> result = {1};

        while (result.size() < N)
        {
            vector<int> tmp;

            for (int i : result)
            {
                if (i*2 - 1 <= N)
                    tmp.push_back(i*2 - 1);
            }

            for (int i : result)
            {
                if (i*2 <= N)
                    tmp.push_back(i*2);
            }

            result = tmp;
        }

        return result;
    }
};
