#include <iostream>
#include <vector>
#include <algorithm>

/*
    ============
    === HARD ===
    ============

    ===========================
    354) Russian Doll Envelopes
    ===========================

    ============
    Description:
    ============

    You are given a 2D array of integers envelopes where envelopes[i] = [wi,
    hi] represents the width and the height of an envelope.

    One envelope can fit into another if and only if both the width and height
    of one envelope are greater than the other envelope's width and height.

    Return the maximum number of envelopes you can Russian doll (i.e., put one
    inside the other).

    =====
    Note: You cannot rotate an envelope.
    =====

    ===========================================================
    FUNCTION: int maxEnvelopes(vector<vector<int>>& envelopes);
    ===========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: envelopes = [[5,4],[6,4],[6,7],[2,3]]
    Output: 3
    Explanation: The maximum number of envelopes you can Russian doll is 3
                 ([2,3] => [5,4] => [6,7]).

    --- Example 2 ---
    Input: envelopes = [[1,1],[1,1],[1,1]]
    Output: 1


    *** Constraints ***
    1 <= envelopes.length <= 10^5
    envelopes[i].length == 2
    1 <= wi, hi <= 10^5

*/

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Usually, when we have 2D vector, or vector of pairs or vector of points,
    if you get stuck with idea and don't know where to begin - Try to sort it.

    Sorting will atleast give you a new perspective. Then you'll maybe come up
    with a Solution.

    Let's consider one Example:

        envelopes = [[7,13], [6,7], [3,5], [6,10], [8,4], [7,11]]
                       0       1      2      3       4      5

    After we sort it:

        envelopes = [[3,5], [6,7], [6,10], [7,11], [7,13], [8,4]]
                       0      1      2       3       4       5

    Let's display this in a more visual way:

        |  Key  :  Value |
        +----------------+
        |   3   :    5   |
        +----------------+
        |   6   :    7   |
        +----------------+
        |   6   :   10   |
        +----------------+
        |   7   :   11   |
        +----------------+
        |   7   :   13   |
        +----------------+
        |   8   :    4   |
        +----------------+

    Now we need to start with a lowest possible envelope and then try to fit
    with the first on on the right(downward in the drawing)

    Since it is primarily sorted on the width part, it can happen that the next
    envelope's width is indeed wider than the next evenlope's width, but the
    HEIGHT is NOT taller than the next one!
    (As is this case once we're on [7,13])

    Since it is sorted, generally speaking, we could try to use a Binary Search
    instead of going manually through all the remaining, wider, envelopes.

    If we were to do that, it would look something like this:

        |  Key  :  Value |
        +----------------+
        |                |
        |   3   :    5   |
        |                | ---------
        +----------------+         |
        |                | <--------
        |   6   :    7   |
        |                | ---------
        +----------------+         |
        |                | <--------
        |   6   :   10   |
        |                | ---------
        +----------------+         |
        |                | <--------
        |   7   :   11   |
        |                | ---------
        +----------------+         |
        |                | <--------
        |   7   :   13   |
        |                |
        +----------------+
        |                |
        |   8   :    4   |
        |                |
        +----------------+

    Here we can clearly see that we have counter envelopes with width: 6 and 7
    twice, even though we know that we wouldn't be able to fit one envelope
    with width 6 into another envelopes with width 6.

    So how can we over comes this?

    Simply by doing a different kind of Sort! Instead of sorting by width in
    INCREASING order and then height ALSO in INCREASING order, we can sort
    still sort by width in INCREASING order, but we can sort by HEIGHT in
    DECREASING order!!

    That way we can search only by height since at every width we get to be, we
    will be certain that current height is the MAXIMUM for that width.

    Therefore, if we find some height to the right(downwards) that is TALLER
    than then current height, we are 100% sure that its width is ALSO bigger,
    i.e. wider.

    Therefore, we know we can fit our current envelope into that one.

    As you can see, this looks awfully similar to "Longest Increasing
    Subsequence", and that is absolutely right. Once we sort by first element
    in INCREASING and then by 2nd element in DECREASING order, it becomes a
    LIS problem.

    Now we would have this situation:

        |  Key  :  Value |
        +----------------+
        |                |
        |   3   :    5   |
        |                | ---------
        +----------------+         |
        |                | <--------
        |   6   :   10   |
        |                | ---------
        +----------------+         |
        |                |         |
        |   6   :    7   |         |
        |                |         |
        +----------------+         |
        |                | <--------
        |   7   :   13   |
        |                |
        +----------------+
        |                |
        |   7   :   11   |
        |                |
        +----------------+
        |                |
        |   8   :    4   |
        |                |
        +----------------+


    Since we've made two steps, and since we've "visited" three different
    envelopes using this method, we conclude that the maximum envelopes that we
    can "Russian doll" one into another is 3.

*/

/* Time  Beats: 80.38% */
/* Space Beats: 45.15% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n)        */
class Solution {
public:
    static bool comp(vector<int>& a, vector<int>& b)
    {
        if (a[0] == b[0])
            return a[1] > b[1];

        return a[0] < b[0];
    }

    int maxEnvelopes(vector<vector<int>>& envelopes)
    {
        const int n = envelopes.size();

        /* Sort */
        sort(envelopes.begin(), envelopes.end(), comp);

        vector<int> LIS;
        for (int i = 0; i < n; i++)
        {
            auto it = lower_bound(LIS.begin(), LIS.end(), envelopes[i][1]);

            if (it == LIS.end())
                LIS.push_back(envelopes[i][1]);
            else
                *it = envelopes[i][1];
        }

        return LIS.size();
    }
};
