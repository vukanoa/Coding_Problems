/*
    ==============
    === MEDIUM ===
    ==============

    ===============================
    2364) Count Number of Bad Pairs
    ===============================

    ============
    Description:
    ============

    You are given a 0-indexed integer array nums. A pair of indices (i, j) is a
    bad pair if i < j and j - i != nums[j] - nums[i].

    Return the total number of bad pairs in nums.

    =====================================================
    FUNCTION: long long countBadPairs(vector<int>& nums);
    =====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [4,1,3,3]
    Output: 5
    Explanation: The pair (0, 1) is a bad pair since 1 - 0 != 1 - 4.
    The pair (0, 2) is a bad pair since 2 - 0 != 3 - 4, 2 != -1.
    The pair (0, 3) is a bad pair since 3 - 0 != 3 - 4, 3 != -1.
    The pair (1, 2) is a bad pair since 2 - 1 != 3 - 1, 1 != 2.
    The pair (2, 3) is a bad pair since 3 - 2 != 3 - 3, 1 != 0.
    There are a total of 5 bad pairs, so we return 5.


    --- Example 2 ---
    Input: nums = [1,2,3,4,5]
    Output: 0
    Explanation: There are no bad pairs.


    *** Constraints ***
    1 <= nums.length <= 10^5
    1 <= nums[i] <= 10^9

*/

#include <unordered_map>
#include <vector>
using namespace std;


/*
    ------------
    --- IDEA ---
    ------------

    Instead of actually trying to count the number of "bad pairs", we can try
    to count the "good pairs" and subtract it from "total_pairs".

    If we have some array of size N=5:

        array = [A, B, C, D, E]
                 0  1  2  3  4

    How many pairs are there?
    There are exactly: N * (N-1) / 2.

    This seem arbitrary if you don't know the math behind the formula, but it's
    just a sum of the first N natural numbers;

    Let's consider each index as a 'j'(right one in the pair) and count them
    manually.

    At index 0, we can form 0 pairs. //
    At index 1, we can form 1 pair.  // {0,1}
    At index 2, we can form 2 pairs. // {0,2}, {1,2}
    At index 3, we can form 3 pairs. // {0,3}, {1,3}, {2,3}
    At index 4, we can form 4 pairs. // {0,4}, {1,4}, {2,4}, {3,4}

    Also they told us that "i < j", which essentially means--Don't double count
    the pairs.


    But what do we do now?
    Two pointers?
    Sliding Window?

    None of those would work since we can't predict the future and there's
    nothing we can do to preprocess the Input array "nums".

    So, how do we do it then?

    Once you see the picture, it'll become obvious. But it was a tough one to
    crack definitely.

    Example 1:

        nums = [4, 1, 3, 3]
                0  1  2  3

            ^
          6 |
            |  ^      ^ ^
          5 | /      / /
            |/      / /
          4 X      / /
            |     / /
   (num)  3 |    X X
            |     /
          2 |    /
            |   /
          1 |  X
            | /
          0 0--1-2-3-4-5--------------------->

                    (index)

    If there are X elements on the same slope, then there are X-1 "GOOD pairs"

    Now read through the code and look at this drawing and you'll get it.
    The reason for this line:

            good_pairs += umap_counter.count(slope) ? umap_counter[slope] : 0;

    Is that is we find a NEW slop, i.e. umap_counter[slope] doesn't exist in
    the HashMap yet, therefore we add 0 to our "good_pairs" count and only
    after that do we increment the number of elements on that slope.

*/

/* Time  Beats: 33.74% */
/* Space Beats: 70.06% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    long long countBadPairs(vector<int>& nums)
    {
        const long long N = nums.size();
        long long result = 0;

        long long total_pairs = N * (N-1) / 2;
        long long good_pairs  = 0;

        unordered_map<int,int> umap_counter;
        for (int i = 0; i < N; i++)
        {
            int slope = nums[i] - i;

            good_pairs += umap_counter.count(slope) ? umap_counter[slope] : 0;
            umap_counter[slope]++;
        }

        return total_pairs - good_pairs;
    }
};
