/*
    ==============
    === MEDIUM ===
    ==============

    ===================================================
    1238) Circular Permutation in Binary Representation
    ===================================================

    ============
    Description:
    ============


    Given 2 integers n and start. Your task is return any permutation p of
    (0,1,2.....,2^n -1) such that :

        + p[0] = start

        + p[i] and p[i+1] differ by only one bit in their binary
          representation.

        + p[0] and p[2^n -1] must also differ by only one bit in their binary
          representation.

    ============================================================
    FUNCTION: vector<int> circularPermutation(int n, int start);
    ============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 2, start = 3
    Output: [3,2,0,1]
    Explanation: The binary representation of the permutation is (11,10,00,01).
    All the adjacent element differ by one bit. Another valid permutation is
    [3,1,0,2]

    --- Example 2 ---
    Input: n = 3, start = 2
    Output: [2,6,7,5,4,0,1,3]
    Explanation: The binary representation of the permutation is
    (010,110,111,101,100,000,001,011).


    *** Constraints ***
    1 <= n <= 16
    0 <= start < 2 ^ n

*/

#include <vector>
using namespace std;

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 58.33% */
/* Space Beats: 47.44% */

/* Time  Complexity: O(2^N) */
/* Space Complexity: O(2^N) */
class Solution {
public:
    vector<int> circularPermutation(int n, int start)
    {
        int size = 1 << n;  // 2^n

        vector<int> gray(size);
        int start_idx = 0;

        // Generate Gray-code and find start position
        for (int i = 0; i < size; i++)
        {
            gray[i] = i ^ (i >> 1);

            if (gray[i] == start)
                start_idx = i;
        }

        // Rotate: Start from start_idx
        vector<int> result;
        result.reserve(size);

        for (int i = 0; i < size; ++i)
            result.push_back(gray[(start_idx + i) % size]);

        return result;
    }
};
