/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    2735) Collecting Chocolates
    ===========================

    ============
    Description:
    ============

    You are given a 0-indexed integer array nums of size n representing the
    cost of collecting different chocolates. The cost of collecting the
    chocolate at the index i is nums[i]. Each chocolate is of a different type,
    and initially, the chocolate at the index i is of ith type.

    In one operation, you can do the following with an incurred cost of x:

        Simultaneously change the chocolate of ith type to ((i + 1) mod n)th
        type for all chocolates.

    Return the minimum cost to collect chocolates of all types, given that you
    can perform as many operations as you would like.

    ======================================================
    FUNCTION: long long minCost(vector<int>& nums, int x);
    ======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [20,1,15], x = 5
    Output: 13
    Explanation: Initially, the chocolate types are [0,1,2]. We will buy the
    1st type of chocolate at a cost of 1.
    Now, we will perform the operation at a cost of 5, and the types of
    chocolates will become [1,2,0]. We will buy the 2nd type of chocolate at a
    cost of 1.
    Now, we will again perform the operation at a cost of 5, and the chocolate
    types will become [2,0,1]. We will buy the 0th type of chocolate at a cost
    of 1. 
    Thus, the total cost will become (1 + 5 + 1 + 5 + 1) = 13. We can prove
    that this is optimal.

    --- Example 2 ---
    Input: nums = [1,2,3], x = 4
    Output: 6
    Explanation: We will collect all three types of chocolates at their own
    price without performing any operations. Therefore, the total cost is:
    1 + 2 + 3 = 6.


    *** Constraints ***
    1 <= nums.length <= 1000
    1 <= nums[i] <= 10^9
    1 <= x <= 10^9

*/

#include <climits>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    This seems as a "Memoization problem", or maybe some other type of Dynamic
    Programming, or even "Greedy" problem.

    But it isn't. Even if these are the Constraints.

    It's MUCH more simple than you'd think. All we need to do is to determine
    in which "shift"(round) is the BEST buy chocolate of type 'i'.

    The only "tricky part" here is that you CANNOT do it the other way around.
    Meaning, you can't iterate through all of the "nums"(chocolates) and then
    go through each shift and determine when is the best time to buy.

    Why?

    Because it is possible that you may buy one type for the same UNIQUE price,
    in the SAME shift, which is impossible and forbidden according to the
    description of the problem.


    Consider this example:

        nums = [20, 90, 1], x = 3

    If you tried to buy each one in their own shift -- And you do NOT shift
    elements globally, all at once -- then you'd end up having a wrong result:

        type i=0: min(20, 90 + 1*3, 1  + 2*3) = 7
        type i=1: min(90,  1 + 1*3, 20 + 2*3) = 4
        type i=2: min( 1, 20 + 1*3, 90 + 2*3) = 1

        result = 12 // which is NOT correct.


    BECAUSE THE NUMBER OF SHIFTS MUST BE THE SAME FOR ALL CHOCOLATES!!!

    It is THAT simple. The description is not very well exaplined, but that's
    literally it.

*/

/* Time  Beats: 61.49% */
/* Space Beats: 44.59% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(N)   */
class Solution {
public:
    long long minCost(vector<int>& nums, int x)
    {
        const int N = nums.size();
        long long result = LLONG_MAX;

        // best[i] = best cost for type 'i' so far(while we're shifting)
        // Essentially: In which "shift" is it BEST to buy this chocolate
        vector<long long> best(nums.begin(), nums.end());

        for (int shifts = 0; shifts < N; shifts++)
        {
            long long curr_cost = 1LL * shifts * x;

            long long sum = 0;
            for (int i = 0; i < N; i++)
            {
                // After "shifts" shifts, chocolate type 'i' maps to:
                // nums[(i - shifts + n) % n]
                best[i] = min(best[i], static_cast<long long>(nums[(i - shifts + N) % N]));
                sum += best[i];
            }

            result = min(result, curr_cost + sum);
        }

        return result;
    }
};
