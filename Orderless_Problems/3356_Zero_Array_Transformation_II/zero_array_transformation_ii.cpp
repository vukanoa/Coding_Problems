/*
    ==============
    === MEDIUM ===
    ==============

    ==================================
    3356) Zero Array Transformation II
    ==================================

    ============
    Description:
    ============

    You are given an integer array nums of length n and a 2D array queries
    where queries[i] = [li, ri, vali].

    Each queries[i] represents the following action on nums:

        + Decrement the value at each index in the range [li, ri] in nums by at
          most vali.

        + The amount by which each value is decremented can be chosen
          independently for each index.

    A Zero Array is an array with all its elements equal to 0.

    Return the minimum possible non-negative value of k, such that after
    processing the first k queries in sequence, nums becomes a Zero Array.
    If no such k exists, return -1.

    ============================================================================
    FUNCTION: int minZeroArray(vector<int>& nums, vector<vector<int>>& queries);
    ============================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [2,0,2], queries = [[0,2,1],[0,2,1],[1,1,3]]
    Output: 2
    Explanation:
        For i = 0 (l = 0, r = 2, val = 1):
            Decrement values at indices [0, 1, 2] by [1, 0, 1] respectively.
            The array will become [1, 0, 1].
        For i = 1 (l = 0, r = 2, val = 1):
            Decrement values at indices [0, 1, 2] by [1, 0, 1] respectively.
            The array will become [0, 0, 0], which is a Zero Array. Therefore,
            the minimum value of k is 2.


    --- Example 2 ---
    Input: nums = [4,3,2,1], queries = [[1,3,2],[0,2,1]]
    Output: -1
    Explanation:
        For i = 0 (l = 1, r = 3, val = 2):
            Decrement values at indices [1, 2, 3] by [2, 2, 1] respectively.
            The array will become [4, 1, 0, 0].
        For i = 1 (l = 0, r = 2, val = 1):
            Decrement values at indices [0, 1, 2] by [1, 1, 0] respectively.
            The array will become [3, 0, 0, 0], which is not a Zero Array.


    *** Constraints ***
    1 <= nums.length <= 10^5
    0 <= nums[i] <= 5 * 10^5
    1 <= queries.length <= 10^5
    queries[i].length == 3
    0 <= li <= ri < nums.length
    1 <= vali <= 5

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    This is by-the-book Binary Search Solution.

    Whenever you're asked to check how many FROM SOME RANGE you need in order
    to accmoplish X, you can perform a Binary Search.

    Here we immediately try all of them, i.e. R = M.size(). If we're unable to
    accomplish what we're being asked to do even by using all of the queries
    then we ought to return -1.

    However, if we CAN do it by, at least, using all of them, we can try to see
    if we can accomplish the same thing by using less than all of them.

    But how are we going to do it? Are we going to try first querry and then
    if we are unable, then try with first 2, etc. until we find it?

    Well, no. That would be considered a Brute Force.

    Instead, we can try first mid, where mid is the middle query element
    between 0 and "mid"(i.e. queries.size()).

    Then, if we can indeed accomplish what we're being asked, then try with
    fewer queries, i.e. try to accomplish the same with lesser 'k' value.

    In that case we'd do:

        R = mid - 1

    Meaning, we're sliding our right edge before our current "mid" value.

    However, if we couldn't accmoplish what we're being asked with our "mid",
    then, instead, we do:

        L = mid + 1


    We're going to be repeating this until L <= R, it's important to be '<='
    and not '<', because we want to return 'L' as a final result.



    But now, how are we going to check if first "mid" queries CAN form a zero
    array?

    We're going to use a Technique called "Line Sweep".
    This is a fundamental technique when working with ranges.

    Let's say we have some ranges:

        ranges = [0,4,1], [2,7,3], [4,9,5], [1,6,2], [0,5,4], [3,7,4], [1,3,2]

    Instead of going through EACH element within EACH range and add the
    corresponding value, what we can do is denote a BEGINNING of some range by
    adding the value at that index and then once that same range is done, we
    SUBRACT the same value.

    It sounds unintuitive if this is your first time dealing with LineSweep,
    but take a look at ASCII drawing below and I'm sure you'll understand it.

          0   1     2    3    4    5    6    7    8    9   10   11
       +----+----+----+----+----+----+----+----+----+----+----+----+
       | +1 |    |    |    |    | -1 |    |    |    |    |    |    |
       +----+----+----+----+----+----+----+----+----+----+----+----+
       |    |    | +3 |    |    |    |    |    | -3 |    |    |    |
       +----+----+----+----+----+----+----+----+----+----+----+----+
       |    |    |    |    | +5 |    |    |    |    |    | -5 |    |
       +----+----+----+----+----+----+----+----+----+----+----+----+
       |    | +2 |    |    |    |    |    | -2 |    |    |    |    |
       +----+----+----+----+----+----+----+----+----+----+----+----+
       | +4 |    |    |    |    |    | -4 |    |    |    |    |    |
       +----+----+----+----+----+----+----+----+----+----+----+----+
       |    |    |    | +4 |    |    |    |    | -4 |    |    |    |
       +----+----+----+----+----+----+----+----+----+----+----+----+
       |    | +2 |    |    | -2 |    |    |    |    |    |    |    |
       +----+----+----+----+----+----+----+----+----+----+----+----+


    This is how we would do it "by-the-book", however, what really happens is
    that we are ONLY adding and subtracting elements at certain indices in our
    "line_sweep" array.

    In other words--This is NOT a 2D array, instead it is a 1D array called
    "line sweep".

    This equivalent array of the above drawing would be:

          0    1    2    3    4    5    6    7    8    9   10   11
       +----+----+----+----+----+----+----+----+----+----+----+----+
       | +5 | +4 | +3 | +4 | +3 | -1 | -4 | -2 | -7 |  0 | -5 |  0 |
       +----+----+----+----+----+----+----+----+----+----+----+----+


    Iterating through this array "line_sweep" would give us the maximum value
    AT EACH INDEX.

    It would look like this:

          0      1      2      3     4     5     6     7     8     9    10
          5  ->  9 ->  12 ->  16 -> 19 -> 18 -> 14 -> 12 ->  5 ->  5 ->  0

    That way, since we know the MAXIMUM POSSIBLE VALUE AT EACH INDEX, if we see
    that at any index along the way, nums[idx] is GREATER than the MAXIMUM
    POSSIBLE VALUE AT THAT INDEX, we return false.

    Why?
    Because we're certain that we CANNOT make a zero-array using these first k
    queries.

    That's the way we're going to check if we can make a zero-array using our
    first 'k'(i.e. "mid") queries.

    As we've already said, we if CAN, then:

            R = mid - 1;

    else

            L = mid + 1;


    Once we're done doing a Binary Search, we're going to return 'L' which is
    guaranteed to be our minimal 'k' number of queries we need to use in order
    to make our array zero-array.

*/

/* Time  Beats: 66.78% */
/* Space Beats: 63.70% */

/* Time  Complexity: O(logM * (N + M)) */
/* Space Complexity: O(N)              */
class Solution_Bin_Search_plus_Line_Sweep {
public:
    int minZeroArray(vector<int>& nums, vector<vector<int>>& queries)
    {
        const int N = nums.size();
        const int M = queries.size();

        int L = 0;
        int R = M;

        // Zero array isn't formed after all queries are processed
        if ( ! can_form_zero_array(nums, queries, R))
            return -1;

        // Binary Search
        while (L <= R)
        {
            int mid = L + (R - L) / 2;

            if (can_form_zero_array(nums, queries, mid))
                R = mid - 1;
            else
                L = mid + 1;
        }

        // Return earliest query that zero array can be formed
        return L;
    }

private:
    bool can_form_zero_array(vector<int>& nums, vector<vector<int>>& queries, int k)
    {
        const int N = nums.size();
        int sum = 0;

        vector<int> line_sweep(N + 1);

        // Process query
        for (int query_idx = 0; query_idx < k; query_idx++)
        {
            int start = queries[query_idx][0];
            int end   = queries[query_idx][1];
            int val   = queries[query_idx][2];

            // Process start and end of range
            line_sweep[start]   += val;
            line_sweep[end + 1] -= val;
        }

        // Check if zero array can be formed
        for (int i = 0; i < N; i++)
        {
            sum += line_sweep[i];

            if (sum < nums[i])
                return false;
        }

        return true;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  74.49% */

/* Time  Complexity: O(N + M) */
/* Space Complexity: O(N)     */
class Solution_Line_Sweep_Only {
public:
    int minZeroArray(vector<int>& nums, vector<vector<int>>& queries)
    {
        const int N = nums.size();
        int sum = 0;
        int k = 0;

        vector<int> line_sweep(N + 1);

        for (int i = 0; i < N; i++)
        {
            // Iter through queries while current idx of nums cannot equal zero
            while (sum + line_sweep[i] < nums[i])
            {
                k++;

                // Zero array isn't formed after all queries are processed
                if (k > queries.size())
                    return -1;

                int L   = queries[k - 1][0];
                int R   = queries[k - 1][1];
                int val = queries[k - 1][2];

                // Process start and end of range
                if (R >= i)
                {
                    line_sweep[max(L, i)] += val;
                    line_sweep[R + 1]     -= val;
                }
            }

            // Update prefix sum at current index
            sum += line_sweep[i];
        }

        return k;
    }
};
