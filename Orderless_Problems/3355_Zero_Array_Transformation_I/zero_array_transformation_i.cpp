/*
    ==============
    === MEDIUM ===
    ==============

    =================================
    3355) Zero Array Transformation I
    =================================

    ============
    Description:
    ============

    You are given an integer array nums of length n and a 2D array queries,
    where queries[i] = [li, ri].

    For each queries[i]:

        + Select a subset of indices within the range [li, ri] in nums.

        + Decrement the values at the selected indices by 1.

    A Zero Array is an array where all elements are equal to 0.

    Return true if it is possible to transform nums into a Zero Array after
    processing all the queries sequentially, otherwise return false.

    ===============================
    FUNCTION:
    ===============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,0,1], queries = [[0,2]]
    Output: true
    Explanation:
        For i = 0:
            Select the subset of indices as [0, 2] and decrement the values at these indices by 1.
            The array will become [0, 0, 0], which is a Zero Array.


    --- Example 2 ---
    Input: nums = [4,3,2,1], queries = [[1,3],[0,2]]
    Output: false
    Explanation:
        For i = 0:
            Select the subset of indices as [1, 2, 3] and decrement the values at these indices by 1.
            The array will become [4, 2, 1, 0].
        For i = 1:
            Select the subset of indices as [0, 1, 2] and decrement the values at these indices by 1.
            The array will become [3, 1, 0, 0], which is not a Zero Array.


    *** Constraints ***
    1 <= nums.length <= 10^5
    0 <= nums[i] <= 10^5
    1 <= queries.length <= 10^5
    queries[i].length == 2
    0 <= li <= ri < nums.length

*/

#include <vector>
using namespace std;



/*
    ------------
    --- IDEA ---
    ------------

    This is a famous Algorithm called "Sweep Line".

    When you have a bunch of intervals, you can "merge them" and count each
    occurrence without going through every range manually.

    For example, if we had this:

        queries = [[0, N-1], [0, N-1], [0, N-1], [0, N-1], [0, N-1]]

        let's say that N == queries.size()

        That means in order to count how many "pieces" of each element in the
        range are, we would ne to go thorugh every piece in queries.size() and
        then we would need to increment "pieces" by going through the entire
        range of size N.

        That makes it O(N^2). It's waaaay to ineffcient.


    Solution?
    Sweepline.

    Go thorugh queries only ONCE and have a vector where you will increment a
    "piece" frequency if it's in the beginning and you will DECREMENT a "piece"
    frequency if it's a end+1.

    Let's draw some examples and you'll understand it quickly:

        queries = [[1,3],[0,2][3,6],[4,7],[6,10]]]

    If we draw this:


     0  1  2  3  4  5  6  7  8  9 10
        X--|--X
     X--|--X
              X--|--|--X
                 X--|--|--X
                       X--|--|--|--X



    If you "merge" them like this, you'd quickly know how many of each "piece"
    are there.

    For example, there are two 1s. From queries: [0,2] and [1,3]
    There are also two 2s from the same two queries.

    There are two 3s from queries: [1,3], [3,6]

    etc.

    So all we have to do is INCREMENT number of "pieces" for "beginning" of
    the range and DECREMENT one AFTER the end of the range.

    for [0,2]:
        INCREMENT 0
        DECREMENT 3

    for [1,3]
        INCREMENT 1
        DECREMENT 4

    and so on.

    At the end we'll have this:

        [+1, +1,  0,  0,  1,  0,  1, -1, -1,  0,  0,  -1]
          0   1   2   3   4   5   6   7   8   9  10   11

    Now all we have to do is go iterate through this array and increment curr
    element, i.e. "piece"

    This way we only have to check if there are enough of "pieces" for current
    element.

    That's it.

*/

/* Time  Beats: 28.28% */
/* Space Beats: 10.04% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    bool isZeroArray(vector<int>& nums, vector<vector<int>>& queries)
    {
        const int N = nums.size();

        vector<int>freq(N+1, 0);

        for(auto query : queries)
        {
            int begin_range = query[0]; // Inclusive
            int end_range   = query[1]; // Inclusive

            freq[begin_range]++;
            freq[end_range + 1]--;
        }

        int pieces = 0;
        for (int i = 0; i < N; i++)
        {
            pieces += freq[i];

            // If there AREN'T enough pieces of nums[i] in queries
            if (pieces < nums[i])
                return false;
        }

        return true;
    }
};
