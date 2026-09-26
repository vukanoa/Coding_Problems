/*
    ============
    === HARD ===
    ============

    ===============================================
    3864) Minimum Cost to Partition a Binary String
    ===============================================

    ============
    Description:
    ============

    You are given a binary string s and two integers encCost and flatCost.

    For each index i, s[i] = '1' indicates that the ith element is sensitive,
    and s[i] = '0' indicates that it is not.

    The string must be partitioned into segments. Initially, the entire string
    forms a single segment.

    For a segment of length L containing X sensitive elements:

        + If X = 0, the cost is flatCost.
        + If X > 0, the cost is L * X * encCost.

    If a segment has even length, you may split it into two contiguous segments
    of equal length and the cost of this split is the sum of costs of the
    resulting segments.

    Return an integer denoting the minimum possible total cost over all valid
    partitions.

    =================================================================
    FUNCTION: long long minCost(string s, int encCost, int flatCost);
    =================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "1010", encCost = 2, flatCost = 1
    Output: 6
    Explanation:
        + The entire string s = "1010" has length 4 and contains 2 sensitive
          elements, giving a cost of 4 * 2 * 2 = 16.

        + Since the length is even, it can be split into "10" and "10". Each
          segment has length 2 and contains 1 sensitive element, so each costs
          2 * 1 * 2 = 4, giving a total of 8.

        + Splitting both segments into four single-character segments yields
          the segments "1", "0", "1", and "0". A segment containing "1" has
          length 1 and exactly one sensitive element, giving a cost of 1 * 1 *
          2 = 2, while a segment containing "0" has no sensitive elements and
          therefore costs flatCost = 1.

        + The total cost is thus 2 + 1 + 2 + 1 = 6, which is the minimum
          possible total cost.


    --- Example 2 ---
    Input: s = "1010", encCost = 3, flatCost = 10
    Output: 12
    Explanation:
        + The entire string s = "1010" has length 4 and contains 2 sensitive
          elements, giving a cost of 4 * 2 * 3 = 24.

        + Since the length is even, it can be split into two segments "10" and
          "10".

        + Each segment has length 2 and contains one sensitive element, so each
          costs 2 * 1 * 3 = 6, giving a total of 12, which is the minimum
          possible total cost.


    --- Example 3 ---
    Input: s = "00", encCost = 1, flatCost = 2
    Output: 2
    Explanation:
    + The string s = "00" has length 2 and contains no sensitive elements, so
      storing it as a single segment costs flatCost = 2, which is the minimum
      possible total cost.



    *** Constraints ***
    1 <= s.length <= 10^5
    s consists only of '0' and '1'.
    1 <= encCost, flatCost <= 10^5

*/

#include <cstdint>
#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats:  98.65% */
/* Space Beats: 100.00% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
private:
    long long encCost;
    long long flatCost;
    long long min_cost_for_two_elements;

public:
    static constexpr int MAX_N = 1e5;
    uint32_t prefix_sum[MAX_N + 1];

    long long minCost(const string& s, long long encCost, long long flatCost)
    {
        int N = s.size();

        this->encCost  = encCost;
        this->flatCost = flatCost;
        min_cost_for_two_elements = min(2 * encCost, flatCost + encCost);

        prefix_sum[0] = 0;
        for (int i = 0; i < N; i++)
            prefix_sum[i + 1] = prefix_sum[i] + (s[i] & 1);


        return min_cost_for_segment(0, N);
    }

private:
    long long min_cost_for_segment(long long start, long long end)
    {
        long long ones_count  = prefix_sum[end] - prefix_sum[start];
        long long segment_len = end - start;

        if (ones_count == 0)
            return flatCost;

        if (ones_count == segment_len)
            return (segment_len * segment_len * encCost) / (segment_len & -segment_len);

        if (segment_len == 2)
            return min_cost_for_two_elements;

        long long cost = ones_count * segment_len * encCost;

        if (segment_len & 1) // Odd length
            return cost;

        int mid = start + segment_len / 2;

        return min(cost, min_cost_for_segment(start, mid) +
                         min_cost_for_segment(mid  , end));
    }
};
