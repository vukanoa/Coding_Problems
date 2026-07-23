/*
    ==============
    === MEDIUM ===
    ==============

    =====================================
    3513) Number of Unique XOR Triplets I
    =====================================

    ============
    Description:
    ============

    You are given an integer array nums of length n, where nums is a
    permutation of the numbers in the range [1, n].

    A XOR triplet is defined as the XOR of three elements nums[i] XOR nums[j]
    XOR nums[k] where i <= j <= k.

    Return the number of unique XOR triplet values from all possible triplets
    (i, j, k).

    A permutation is a rearrangement of all the elements of a set.

    ===================================================
    FUNCTION: int uniqueXorTriplets(vector<int>& nums);
    ===================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2]
    Output: 2
    Explanation:
    The possible XOR triplet values are:
        (0, 0, 0) → 1 XOR 1 XOR 1 = 1
        (0, 0, 1) → 1 XOR 1 XOR 2 = 2
        (0, 1, 1) → 1 XOR 2 XOR 2 = 1
        (1, 1, 1) → 2 XOR 2 XOR 2 = 2

    The unique XOR values are {1, 2}, so the output is 2.


    --- Example 2 ---
    Input: nums = [3,1,2]
    Output: 4
    Explanation:
    The possible XOR triplet values include:
        (0, 0, 0) → 3 XOR 3 XOR 3 = 3
        (0, 0, 1) → 3 XOR 3 XOR 1 = 1
        (0, 0, 2) → 3 XOR 3 XOR 2 = 2
        (0, 1, 2) → 3 XOR 1 XOR 2 = 0

    The unique XOR values are {0, 1, 2, 3}, so the output is 4.


    *** Constraints ***
    1 <= n == nums.length <= 10^5
    1 <= nums[i] <= n
    nums is a permutation of integers from 1 to n.

*/

#include <vector>
using namespace std;


/*
    ------------
    --- IDEA ---
    ------------

    Any group of XOR triplets will produce a binary value. Now, we only need to
    see how many UNIQUE binary values are possible.

    We're told that "nums" is a PERMUTATION of integers from 1 to N.

    Therefore, ALL of the elements in "nums" are bounded by N, i.e. the values
    that can be represented use AT MOST X bits, where 'X' is the number of bits
    of in N.


    For example, N = 5, therefore we have a permutation of 1 to 5 in "nums".
    N=5 in binary is written using X=3 bits.

        N = 5    --->   101   --->   X = 3 bits

    Since X = 3 bits, that means that MAXIMUM BINARY VALUE is 7(all 3 bits SET)


    Binary Combinations
    (Unique XOR values = 8)

      0       1       2       3       4       5       6       7
     000     001     010     011     100     101     110     111
    1^2^3   1^1^1   1^1^2   1^1^3   1^1^4   1^1^5   1^1^6   1^1^7
    1^4^5   1^2^2   2^2^2   2^2^3   2^2^4   2^2^5   1^3^4   1^3^5
            1^3^3   2^3^3   2^4^5   2^3^5   2^3^4
            ...     ...     ...     ...     ...


    So, if ever number from 1 to N uses AT MOST X bits, then their CUMULATIVE
    XOR also uses AT MOST X bits.

    Therefore, every XOR triplet value is a X-bit number, ranging from:

        0 up to (2^X - 1)

    Therefore the TOTAL number of UNIQUE XOR triplets is: (2^X - 1)

*/

/* Time  Beats: 100.00% */
/* Space Beats: 100.00% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums)
    {
        const int N = nums.size();

        return next_power_of_two(N);
    }

private:
    int next_power_of_two(const int& N)
    {
        if (N <= 2)
            return N;

        return 1 << (32 - __builtin_clz(N));
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This a Bit-Smearing technique. It is an alternative way of computing a
    "next_power_of_two".

    It can be handy, so it's a good technique to add to your toolset.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  85.00% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution_Smearing {
public:
    int uniqueXorTriplets(vector<int>& nums)
    {
        const int N = nums.size();

        int bit_mask = N;
        
        /* Bit SMEARING technique <==> next_power_of_two(N) */
        bit_mask |= bit_mask >> 1;
        bit_mask |= bit_mask >> 2;
        bit_mask |= bit_mask >> 4;
        bit_mask |= bit_mask >> 8;
        bit_mask |= bit_mask >> 16;

        int next_power_of_two = bit_mask + 1;

        if (N <= 2)
            return next_power_of_two >> 1;

        return next_power_of_two;
    }
};
