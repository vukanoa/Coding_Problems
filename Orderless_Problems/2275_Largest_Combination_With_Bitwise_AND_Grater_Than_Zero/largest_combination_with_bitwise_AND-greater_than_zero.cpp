#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ============================================================
    2275) Largest Combination With Bitwise AND Greater Than Zero
    ============================================================

    ============
    Description:
    ============

    The bitwise AND of an array nums is the bitwise AND of all integers in
    nums.

        + For example, for nums = [1, 5, 3] the bitwise AND is equal to:
            1 & 5 & 3 = 1.

        Also, for nums = [7], the bitwise AND is 7.

    You are given an array of positive integers candidates. Evaluate the
    bitwise AND of every combination of numbers of candidates. Each number in
    candidates may only be used once in each combination.

    Return the size of the largest combination of candidates with a bitwise AND
    greater than 0.

    ==========================================================
    FUNCTION: int largestCombination(vector<int>& candidates);
    ==========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: candidates = [16,17,71,62,12,24,14]
    Output: 4
    Explanation: The combination [16,17,62,24] has a bitwise AND of 16 & 17 &
    62 & 24 = 16 > 0.
    The size of the combination is 4.
    It can be shown that no combination with a size greater than 4 has a
    bitwise AND greater than 0.
    Note that more than one combination may have the largest size.
    For example, the combination [62,12,24,14] has a bitwise AND of 62 & 12 &
    24 & 14 = 8 > 0.


    --- Example 2 ---
    Input: candidates = [8,8]
    Output: 2
    Explanation: The largest combination [8,8] has a bitwise AND of 8 & 8 = 8 >
                 0. The size of the combination is 2, so we return 2.


    *** Constraints ***
    1 <= candidates.length <= 10^5
    1 <= candidates[i] <= 10^7

*/

/*
    ------------
    --- IDEA ---
    ------------

    You have to read the Description of this problem VERY VERY carefully to
    be able to come up with this idea.

    Read this:" Return the size of the largest combination of candidates with a
    bitwise AND greater than 0.'

    Size of the largest combination which bitwise_AND is greater than 0.

    Going through all of the combinations would result in TLE(Time Limit
    Exceeded), however we don't need to do that. We are not asked to return the
    largest number of some combination after bitwise_AND, instead we're only
    asked to return the SIZE of the combination that has bitwise_AND greater
    than 0.

    You have to read and ruminate on this sentence. To "chew the cud" of this
    sentence.

    After a while it maybe pops into your head. Here is the Solution - Since
    we do not care about the exact number of any combinations and since we only
    do care about the SIZE of the combination IF it has bitwise_AND greater
    than 0, what we can do is the following:

    Since the vector is filled with candidates of type "int" we know that on
    most 64-bit platforms, "int" is 4 bytes long, meaning 32bits.

    We can do a bitwise_AND operation for each candidate but only for one of
    the 32 bits at a time.

    Why? This seems strange!

    Let's say we only do a bitwise_AND on the 0th bit(LSB - Lowest Significant
    Bit) of all candidates. For every candidate that we found the 0th bit is
    Set, i.e. 1, we increment our "count".

    After we're done with ALL of the candidates for this 0th bit, our "count"
    variable will the SIZE of some combination that CERTAINLY has the
    bitwise_AND greater than 0.

    How do we know that?
    Well, if all of those candidates have the 0th bit set to 1, then if we do
    a bitwise_AND on all of those, the result would be 1, which is greater than
    0.

    We do NOT care about the combinations that have both, say, 0th and 4th bit
    set. We ONLY care about the SIZE of the comabinations that when
    bitwise_AND'd, the result is greater than 0.

    That's why we can and should do(for the most efficient solution)
    bitwise_AND on all candidates for that specific bit. Count all of those
    which has that bit set and see if that SIZE is the biggest so far.

    At the end return the biggest size.

    It's not intuitive, if you don't get it - Please read this once again with
    more attention.

    It is NOT difficult but it is unintuitive before you learn about it.

*/

/* Time  Beats: 73.13% */
/* Space Beats: 14.16% */

/* Time  Complexity: O(n * 32) --> O(n) */
/* Space Complexity: O(1)               */
class Solution {
public:
    int largestCombination(vector<int>& candidates)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates

        const int n = candidates.size();
        int result = 0;

        for (int i = 0; i < 32; i++)
        {
            int count = 0;
            for (auto candidate : candidates)
            {
                if (candidate & (1 << i))
                    count++;
            }
            result = max(result, count);
        }

        return result;
    }
};
