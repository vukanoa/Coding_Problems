/*
    ============
    === HARD ===
    ============

    ===========================
    2551) Put Marbles in Bags
    ===========================

    ============
    Description:
    ============

    You have k bags. You are given a 0-indexed integer array weights where
    weights[i] is the weight of the ith marble. You are also given the integer
    k.

    Divide the marbles into the k bags according to the following rules:

        + No bag is empty.

        + If the ith marble and jth marble are in a bag, then all marbles with
          an index between the ith and jth indices should also be in that same
          bag.

        + If a bag consists of all the marbles with an index from i to j
          inclusively, then the cost of the bag is weights[i] + weights[j].

    The score after distributing the marbles is the sum of the costs of all the
    k bags.

    Return the difference between the maximum and minimum scores among marble
    distributions.

    ============================================================
    FUNCTION: long long putMarbles(vector<int>& weights, int k);
    ============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: weights = [1,3,5,1], k = 2
    Output: 4
    Explanation:
    The distribution [1],[3,5,1] results in the minimal score of (1+1) + (3+1) = 6.
    The distribution [1,3],[5,1], results in the maximal score of (1+3) + (5+1) = 10.
    Thus, we return their difference 10 - 6 = 4.

    --- Example 2 ---
    Input: weights = [1, 3], k = 2
    Output: 0
    Explanation: The only distribution possible is [1],[3].
    Since both the maximal and minimal score are the same, we return 0.


    *** Constraints ***
    1 <= k <= weights.length <= 10^5
    1 <= weights[i] <= 10^9

*/

#include <algorithm>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Let's start with a brute-force approach.

    Since we are looking for the maximum score and the minimum score, we shall
    try iterating over all possible splits. Splitting n marbles into k
    consecutive groups is a typical sticks-and-stones problem that has as many
    as:

        (n)
        ( ) =  N! / k! * (n - k)!
        (k)

    solutions, thus it is impractical to iterate over all possibilities.

    We might also think of using dynamic programming to solve the subproblem
    (x, y): splitting previous x marbles into y bags, then moving on to the
    next larger subproblem (x + 1, y) or (x, y + 1), until we reach the best
    solution of the entire problem (n, k). However, given the size of the input
    array and the maximum value of k, dynamic programming brings at most O(n2)
    time thus it won't pass the time limit.

    Let's shift our thinking a bit.

    Instead of focusing on how to partition the array of marbles, let's now
    focus on the boundary of each subarray, the splitting point and try to find
    the relation between the score and these splitting points.

    Since the score of a subarray only matters with its two ends, we can tell
    that the total score equals the sum of the first element, the last element,
    and the sum of every pair (two adjacent ends at each split).

    In general, if we partition the array into k groups, we always make k - 1
    splitting points regardless of how the array is partitioned.

    Now we know how to find the maximum score, by finding the sum of the
    largest k - 1 pairs. Similarly, we can get the minimum score by finding the
    sum of the smallest k - 1 pairs. This can be done by collecting every pair
    sum in an array pairWeights and sorting them.

    // pair_weights sorted in non-decreasing order
    max_score = weights[0] + weights[N - 1] + sum(i=N-k to N-1)pair_weights[i]
    min_score = weights[0] + weights[N - 1] + sum(i=0 to k-2)pair_weights[i]

    Then we have the difference between them as:

    result =               max_score          -            min_score
           = sum(i=N-k to N-1)pair_weights[i] - sum(i=0 to k-2)pair_weights[i]

*/

/* Time  Beats: 93.67% */
/* Space Beats: 76.79% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution {
public:
    long long putMarbles(vector<int>& weights, int k)
    {
        const int N = weights.size();
        long long result = 0;

        // We collect and sort the value of all n - 1 pairs.
        vector<int> pair_weights(N - 1, 0);

        for (int i = 0; i < N - 1; ++i)
            pair_weights[i] += weights[i] + weights[i + 1];

        sort(pair_weights.begin(), pair_weights.end());

        // Get the difference between:
        //     1. Largest  k-1 values, and
        //     2. Smallest k-1 values
        for (int i = 0; i < k - 1; ++i)
            result += pair_weights[N - 2 - i] - pair_weights[i];

        return result;
    }
};
