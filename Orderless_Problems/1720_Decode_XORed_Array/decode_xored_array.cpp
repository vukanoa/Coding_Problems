/*
    ============
    === EASY ===
    ============

    ===========================
    1720) Decode XORed Array
    ===========================

    ============
    Description:
    ============

    There is a hidden integer array arr that consists of n non-negative
    integers.

    It was encoded into another integer array encoded of length n - 1, such
    that encoded[i] = arr[i] XOR arr[i + 1]. For example, if arr = [1,0,2,1],
    then encoded = [1,2,3].

    You are given the encoded array. You are also given an integer first, that
    is the first element of arr, i.e. arr[0].

    Return the original array arr. It can be proved that the answer exists and
    is unique.

    ==============================================================
    FUNCTION: vector<int> decode(vector<int>& encoded, int first);
    ==============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: encoded = [1,2,3], first = 1
    Output: [1,0,2,1]
    Explanation: If arr = [1,0,2,1], then first = 1 and encoded = [1 XOR 0, 0
                 XOR 2, 2 XOR 1] = [1,2,3]

    --- Example 2 ---
    Input: encoded = [6,2,7,3], first = 4
    Output: [4,2,0,7,4]


    *** Constraints ***
    2 <= n <= 10^4
    encoded.length == n - 1
    0 <= encoded[i] <= 10^5
    0 <= first <= 10^5

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
/* Space Beats:  89.85% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    vector<int> decode(vector<int>& encoded, int first)
    {
        const int N = encoded.size();

        vector<int> result(N+1, 0);
        result[0] = first;

        for (int i = 0; i < N; i++)
            result[i+1] = result[i] ^ encoded[i];

        return result;
    }
};
