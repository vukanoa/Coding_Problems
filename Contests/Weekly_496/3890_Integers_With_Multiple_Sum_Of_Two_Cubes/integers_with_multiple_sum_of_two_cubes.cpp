/*
    ==============
    === MEDIUM ===
    ==============

    =============================================
    3890) Integers With Multiple Sum of Two Cubes
    =============================================

    ============
    Description:
    ============

    You are given an integer n.

    An integer x is considered good if there exist at least two distinct pairs
    (a, b) such that:

        a and b are positive integers.
        a <= b
        x = a3 + b3

    Return an array containing all good integers less than or equal to n,
    sorted in ascending order.

    ==============================================
    FUNCTION: vector<int> findGoodIntegers(int n);
    ==============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 4104
    Output: [1729,4104]
    Explanation:
    Among integers less than or equal to 4104, the good integers are:
        1729: 13 + 123 = 1729 and 93 + 103 = 1729.
        4104: 23 + 163 = 4104 and 93 + 153 = 4104.
    Thus, the answer is [1729, 4104].

    --- Example 2 ---
    Input: n = 578
    Output: []
    Explanation: There are no good integers less than or equal to 578, so the
                 answer is an empty array.


    *** Constraints ***
    1 <= n <= 10^9

*/

#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 74.60% */
/* Space Beats: 78.61% */

/* Time  Complexity: O(N^(2/3)) */
/* Space Complexity: O(N^(2/3)) */
class Solution {
public:
    vector<int> findGoodIntegers(int n)
    {
        unordered_map<int, int> umap;
        vector<int> result;

        int limit = cbrt(n); // cbrt <==> "Cube Root"

        for (long long i = 1; i <= limit; i++)
        {
            long long i3 = i * i * i;

            for (long long j = i; j <= limit; j++)
            {
                long long sum = i3 + j * j * j;

                if (sum > n)
                    break;

                ++umap[sum];
            }
        }

        for (const auto& [sum, pair_count] : umap)
        {
            if (pair_count >= 2)
                result.push_back(sum);
        }

        /* Sort */
        sort(result.begin(), result.end());

        return result;
    }
};
