/*
    ==============
    === MEDIUM ===
    ==============

    ====================================
    3468) Find the Number of Copy Arrays
    ====================================

    ============
    Description:
    ============

    You are given an array original of length n and a 2D array bounds of length
    n x 2, where bounds[i] = [ui, vi].

    You need to find the number of possible arrays copy of length n such that:

        + (copy[i] - copy[i - 1]) == (original[i] - original[i - 1])
          for 1 <= i <= n - 1.

        + ui <= copy[i] <= vi for 0 <= i <= n - 1.

    Return the number of such arrays.

    ==============================================================================
    FUNCTION: int countArrays(vector<int>& original, vector<vector<int>>& bounds);
    ==============================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: original = [1,2,3,4], bounds = [[1,2],[2,3],[3,4],[4,5]]
    Output: 2
    Explanation:
    The possible arrays are:
        [1, 2, 3, 4]
        [2, 3, 4, 5]

    --- Example 2 ---
    Input: original = [1,2,3,4], bounds = [[1,10],[2,9],[3,8],[4,7]]
    Output: 4
    Explanation:
    The possible arrays are:
        [1, 2, 3, 4]
        [2, 3, 4, 5]
        [3, 4, 5, 6]
        [4, 5, 6, 7]

    --- Example 3 ---
    Input: original = [1,2,1,2], bounds = [[1,1],[2,3],[3,3],[2,3]]
    Output: 0
    Explanation:
    No array is possible.


    *** Constraints ***
    2 <= n == original.length <= 10^5
    1 <= original[i] <= 10^9
    bounds.length == n
    bounds[i].length == 2
    1 <= bounds[i][0] <= bounds[i][1] <= 10^9

*/

#include <climits>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Consider this example:

    original = [1, 4, 2, 8]      bounds = [[1,6], [7,10], [2,11], [8,15]]
                0  1  2  3                   0      1       2       3


    1  2  3  4  5  6  7  8  9  10  11  12  13  14  15
    x---------------x                                   // bounds
              \     \
               \     \
                \     \
                 \     \      diff = 3
                  \     \
                   \     \
                    \     \
                     \     \
    1  2  3  4  5  6  7  8  9  10  11  12  13  14  15
                      x---------x                       // bounds
                     /     /
                    /     /
                   /     /      diff = -2
                  /     /
                 /     /
    1  2  3  4  5  6  7  8  9  10  11  12  13  14  15
       x---------------------------x                   // bounds
                \      \
                 \      \
                  \      \
                   \      \
                    \      \
                     \      \
                      \      \
                       \      \
                        \      \
                         \      \       diff = 6
                          \      \
                           \      \
                            \      \
                             \      \
                              \      \
                               \      \
                                \      \
                                 \      \
                                  \      \
                                   \      \
    1  2  3  4  5  6  7  8  9  10  11  12  13  14  15
                         x--------------------------x  // bounds




    In usual interval-like problems, you do something like SweepLine or
    something like that, however, we cannot do that here since ranges cannot
    be just overlapped, instead we need to go bounds-by-bounds and intersect
    "diff" value to the right or to the left.

    To the right if diff is positive.
    To the left  if diff is negative.

    If at any point we find out that 'L' is greater than 'R', we can
    immediately return 0, since we certainly can't have even a single possible
    array.


    If you still don't get it, consider this:

    nums = [1, 5, 4]    bounds = [[1,6], [8,17], [7,16]]
            0  1  2                 0      1       2

    Diff between 1st and 0th element is 4.
    Therefore, when we intersect 0th and 1st bound, we get this:

    1  2  3  4  5  6  7  8  9  10  11  12  13  14  15  16  17
    x--------------x
              \     \
               \     \
                \     \
                 \     \
                  \     \
                   \     \
                    \     \
                     \     \
                      \     \
                       \     \
                        \     \
    1  2  3  4  5  6  7  8  9  10  11  12  13  14  15  16  17
                         x----------------------------------x


    Maximal possible arrays if we ONLY had 0th and 1st element and its bounds
    would be of size 2.
    Why?

    Because we can start 0th element only at either 4 or 5 and then we can also
    start 1st element at either 8 or 9, respectively.

    So there are ONLY two possibilities.

    Diff between 1st and 0th element is -1.
    If we were to intersect 1st and 2nd element and its bounds, we'd have this:

    1  2  3  4  5  6  7  8  9  10  11  12  13  14  15  16  17
                         x----------------------------------x
                        /                                  /
                       /                                  /
                      /                                  /
    1  2  3  4  5  6  7  8  9  10  11  12  13  14  15  16  17
                      x---------------------------------x

    Even though, if we had only 1st and 2nd element and its bounds, we could've
    have 10 possible arrays. i.e. if we start 1st at 8, then 2nd at 9, etc.

    However we CANNOT really have 10 because we've already determined that
    the 1st element MUST start and can start only at: 8, 9 or 10 in order to
    intersect with 0th element properly.

    Therefore we don't really consider the entire bounds from 1st, instead we
    consider updated bounds that are interesected previous two bounds.

    Now read through the code and go through the first example in this IDEA and
    you'll understand it.

*/

/* Time  Beats: 100.00% */
/* Space Beats:   0.00% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int countArrays(vector<int>& original, vector<vector<int>>& bounds)
    {
        int L = bounds[0][0];
        int R = bounds[0][1];

        for (size_t i = 1; i < original.size(); ++i)
        {
            int diff = original[i] - original[i - 1];

            L = max(L + diff, bounds[i][0]);
            R = min(R + diff, bounds[i][1]);

            if (L > R)
                return 0;
        }

        return R - L + 1;
    }
};
