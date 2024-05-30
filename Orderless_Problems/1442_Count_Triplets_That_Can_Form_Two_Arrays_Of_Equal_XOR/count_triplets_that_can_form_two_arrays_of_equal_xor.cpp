#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ==========================================================
    1442) Count Triplets That Can Form Two Arrays of Equal XOR
    ==========================================================

    ============
    Description:
    ============

    Given an array of integers arr.

    We want to select three indices i, j and k where (0 <= i < j <= k <
    arr.length).

    Let's define a and b as follows:

        a = arr[i] ^ arr[i + 1] ^ ... ^ arr[j - 1]
        b = arr[j] ^ arr[j + 1] ^ ... ^ arr[k]

    Note that ^ denotes the bitwise-xor operation.

    Return the number of triplets (i, j and k) Where a == b.

    ==============================================
    FUNCTION: int countTriplets(vector<int>& arr);
    ==============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: arr = [2,3,1,6,7]
    Output: 4
    Explanation: The triplets are (0,1,2), (0,2,2), (2,3,4) and (2,4,4)


    --- Example 2 ---
    Input: arr = [1,1,1,1,1]
    Output: 10


    *** Constraints ***
    1 <= arr.length <= 300
    1 <= arr[i] <= 10^8

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats:  100% */
/* Space Beats: 43.21% */

/* Time  Complexity: O(n^2) */
/* Space Complexity: O(n) */
class Solution {
public:
    int countTriplets(std::vector<int>& arr)
    {
        const int N = arr.size() + 1;

        std::vector<int> prefix_xor(N, 0);

        for (int i = 1; i < N; i++)
            prefix_xor[i] = prefix_xor[i - 1] ^ arr[i - 1];

        int result = 0;

        for (int start = 0; start < N; start++)
        {
            for (int end = start+1; end < N; end++)
            {
                if (prefix_xor[start] == prefix_xor[end])
                    result += end - start - 1;
            }
        }

        return result;
    }
};
