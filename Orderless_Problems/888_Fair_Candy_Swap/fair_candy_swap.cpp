#include <iostream>
#include <vector>
#include <unordered_map>
#include <numeric>

/*
    ============
    === EASY ===
    ============

    ===========================
    888) Fair Candy Swap
    ===========================

    ============
    Description:
    ============

    Alice and Bob have a different total number of candies. You are given two
    integer arrays aliceSizes and bobSizes where aliceSizes[i] is the number of
    candies of the ith box of candy that Alice has and bobSizes[j] is the
    number of candies of the jth box of candy that Bob has.

    Since they are friends, they would like to exchange one candy box each so
    that after the exchange, they both have the same total amount of candy. The
    total amount of candy a person has is the sum of the number of candies in
    each box they have.

    Return an integer array answer where answer[0] is the number of candies in
    the box that Alice must exchange, and answer[1] is the number of candies in
    the box that Bob must exchange. If there are multiple answers, you may
    return any one of them. It is guaranteed that at least one answer exists.

    ====================================================================================
    FUNCTION: vector<int> fairCandySwap(vector<int>& aliceSizes, vector<int>& bobSizes);
    ====================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: aliceSizes = [1,1], bobSizes = [2,2]
    Output: [1,2]

    --- Example 2 ---
    Input: aliceSizes = [1,2], bobSizes = [2,3]
    Output: [1,2]

    --- Example 3 ---
    Input: aliceSizes = [2], bobSizes = [1,3]
    Output: [2,3]

    *** Constraints ***
    1 <= aliceSizes.length, bobSizes.length <= 10^4
    1 <= aliceSizes[i], bobSizes[j] <= 10^5
    Alice and Bob have a different total number of candies.
    There will be at least one valid answer for the given input.

*/

/*
    ------------
    --- IDEA ---
    ------------

    It's important to read CAREFULLY. It is said that they will exchange ONE
    CANDY BOX.

    Once you internalize that, it essentially becomes very similar to the most
    famous LeetCode problem - "Two Sum"(LeetCode's 1st problem)

*/

/* Time  Beats: 56.17% */
/* Space Beats: 18.16% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    vector<int> fairCandySwap(vector<int> A, vector<int> B)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates

        int total_Alice = accumulate(A.begin(), A.end(), 0);
        int total_Bob   = accumulate(B.begin(), B.end(), 0);

        int diff = (total_Alice - total_Bob) / 2;

        unordered_set<int> uset(A.begin(), A.end());
        for (int b : B)
        {
            if (uset.count(b + diff))
                return {b + diff, b};
        }

        return {};
    }
};
