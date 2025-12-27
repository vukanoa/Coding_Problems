/*
    ==============
    === MEDIUM ===
    ==============

    ==============================
    823) Binary Trees with Factors
    ==============================

    ============
    Description:
    ============

    Given an array of unique integers, arr, where each integer arr[i] is
    strictly greater than 1.

    We make a binary tree using these integers, and each number may be used for
    any number of times. Each non-leaf node's value should be equal to the
    product of the values of its children.

    Return the number of binary trees we can make. The answer may be too large
    so return the answer modulo 109 + 7.

    =======================================================
    FUNCTION: int numFactoredBinaryTrees(vector<int>& arr);
    =======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: arr = [2,4]
    Output: 3
    Explanation: We can make these trees: [2], [4], [4, 2, 2]

    --- Example 2 ---
    Input: arr = [2,4,5,10]
    Output: 7
    Explanation: We can make these trees: [2], [4], [5], [10], [4, 2, 2], [10,
                 2, 5], [10, 5, 2].


    *** Constraints ***
    1 <= arr.length <= 1000
    2 <= arr[i] <= 10^9
    All the values of arr are unique.

*/

#include <algorithm>
#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 79.22% */
/* Space Beats: 34.85% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(N)   */
class Solution {
public:
    const int MOD = 1e9 + 7;

    int numFactoredBinaryTrees(vector<int>& arr)
    {
        const int N = arr.size();

        /* Sort */
        sort(arr.begin(), arr.end());

        unordered_map <int, long> root_with_count;
        root_with_count[arr[0]] = 1;

        for (int i = 1; i < N; i++)
        {
            long count = 1;

            for (const auto& entry : root_with_count)
            {
                int root_elem = entry.first;

                if (arr[i] % root_elem == 0 &&
                    root_with_count.find(arr[i] / root_elem) != root_with_count.end())
                {
                    count += root_with_count[root_elem] * root_with_count[arr[i] / root_elem];
                }
            }
            root_with_count[arr[i]] = count;
        }

        int number_of_trees = 0;
        for (const auto& entry : root_with_count)
        {
            number_of_trees = (number_of_trees + entry.second) % MOD;
        }
        return number_of_trees;
    }
};
