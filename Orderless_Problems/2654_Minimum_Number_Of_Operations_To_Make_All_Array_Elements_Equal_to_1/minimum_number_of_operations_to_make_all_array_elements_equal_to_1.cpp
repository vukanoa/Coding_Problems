/*
    ==============
    === MEDIUM ===
    ==============

    ========================================================================
    2654) Minimum Number of Operations to Make All Array Elements Equal to 1
    ========================================================================

    ============
    Description:
    ============

    You are given a 0-indexed array nums consisiting of positive integers. You
    can do the following operation on the array any number of times:

        + Select an index i such that 0 <= i < n - 1 and replace either of
          nums[i] or nums[i+1] with their gcd value.

    Return the minimum number of operations to make all elements of nums equal
    to 1. If it is impossible, return -1.

    The gcd of two integers is the greatest common divisor of the two integers.

    ===============================================
    FUNCTION: int minOperations(vector<int>& nums);
    ===============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [2,6,3,4]
    Output: 4
    Explanation: We can do the following operations:
    - Choose index i = 2 and replace nums[2] with gcd(3,4) = 1. Now we have nums = [2,6,1,4].
    - Choose index i = 1 and replace nums[1] with gcd(6,1) = 1. Now we have nums = [2,1,1,4].
    - Choose index i = 0 and replace nums[0] with gcd(2,1) = 1. Now we have nums = [1,1,1,4].
    - Choose index i = 2 and replace nums[3] with gcd(1,4) = 1. Now we have nums = [1,1,1,1].

    --- Example 2 ---
    Input: nums = [2,10,6,14]
    Output: -1
    Explanation: It can be shown that it is impossible to make all the elements
                 equal to 1.


    *** Constraints ***
    2 <= nums.length <= 50
    1 <= nums[i] <= 10^6

*/

#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    This requires a small explanation.

    First, my thoughts went in something like this:

        What if we just check the number of intial ones in "nums".
        That way we'll only need to convert the (N - ones) that are not 1s.

        But is it that easy?

        What if initial we did not have ANY 1, as in Example 1?

            Input: nums = [2,6,3,4]
            Output: 4

        Hmm, what if we go through first N-1 elements and try do GCD of
        nums[i] and nums[i+1] for all N-1 elements and then we count ones.

        In this example it would be:

                         0  1  2  3
            nums      = [2, 6, 3, 4]
            processed = [2, 3, 1]

        Then we can count the number of 1s in this new "processed" vector of
        N-1 elements.

        Then, we simply return (N - ones) again, however "ones" are made-up
        therefore we need to return he number of made-up 1s as well.

        In this case: 1 + (N - ones).


    Will that work?
    Not quite. Almost, but no.


    Consider this example:

        Input:  nums = [6, 10, 15]
        Output: 4

    Had we used my above approach, we'd return -1, because we're NOT able
    make-up any 1s.


    But is that correct?
    No!

    We would be able to create 1s in this example, but it would require
    more than 2 operations.

    We used to do this:
        nums      = [6, 10, 15]
        processed = [2,  5]

    And there are no 1s, however, had we done one more GCD, then we'd get:

        processed = [1, 5]

    And then we'd spread out that 1 to the rest, giving us the correct
    result of 4.

    Therefore, what we need to do instead is find the:

        "shortest subarray that has a gcd == 1"


    What I'm about to say is CRUCIAL! Listen to this:

    The number of operations needed to get a 1 from subarray is:

        (subarray_len - 1) operations


    Of course, assuming IF the GCD of ENTIRE SUBARRAY is equal to 1.


    Therefore, IF we find that subarray, then the total number of operations
    needed to convert the ENTIRE array to 1s is:

        (min_subarray_len - 1) + (N - 1)


    min_subarray_len is the MINIMUM LENGTH subarray that CAN INDEED be
    converted to 1s using gcd function.

    Why do we need to "minimum one", because we want to get the 1 with AS
    LITTLE operations as possible. Remember that the number of operations
    needed to convert to get 1 from a subarray is:

        (subarray_len - 1)

    Therefore, since the number of operations is dependent on the LENGTH of
    the subarray, we want to REDUCE its length as much as possible.

    However, once we have that one 1, we need to spread it to all the other
    elements.

    The remaining amount of elements that are NOT 1s, are (N-1).

    Therefore, the total number of operations needed is:

        (min_subarray_len - 1) + (N - 1).


    Also, if INITIALLY, we DO have at least one 1 in "nums", then all we have
    to do is count those 1s and return (N - ones).

    We don't have to grapple with min_subarray_len or anything else because we
    already have 1s initially.

    Also, if there is NO subarray in the entire "nums", including the subarray
    "nums" itself, then we must return -1 since there is no possible way to
    converting all the elements to 1s.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  34.03% */

/* Time  Complexity: O(N^2 * log(max(nums[i]))) */
/* Space Complexity: O(1)                       */
class Solution {
public:
    int minOperations(vector<int>& nums)
    {
        const int N = nums.size();

        // Step 1: If we already have 1's, then spread out that 1s to non-1s.
        int ones = count(nums.begin(), nums.end(), 1);
        if (ones > 0)
            return N - ones;

        // Step 2: Find shortest subarray with gcd == 1
        int min_subarray_len = N + 1;
        for (int i = 0; i < N; i++)
        {
            int curr_gcd = nums[i];
            for (int j = i+1; j < N; j++)
            {
                curr_gcd = gcd(curr_gcd, nums[j]);

                if (curr_gcd == 1)
                {
                    int curr_subarray_len = j - i + 1;
                    min_subarray_len = min(min_subarray_len, curr_subarray_len);
                    break;
                }
            }
        }

        // Step 3: If we have NOT found a subarray in entire nums with gcd == 1
        if (min_subarray_len == N + 1)
            return -1; // Then it's impossible

        // Step 4: Create 1, then spread it
        return (min_subarray_len - 1) + (N - 1);
    }

private:
    int gcd(int a, int b)
    {
        return b == 0 ? a : gcd(b, a % b);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same idea as above, however it's written in a much more compact way.
    Still, I'd prefer the above Solution.

    I feel it's easier to follow and grasp.

    This is more in a Competitive-Programming spirit.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  93.06% */

/* Time  Complexity: O(N^2 * log(max(nums[i]))) */
/* Space Complexity: O(1)                       */
class Solution_2 {
public:
    int minOperations(vector<int>& nums)
    {
        const int N = nums.size();

        int ones = count(nums.begin(), nums.end(), 1);
        if (ones > 0)
            return N - ones;

        for (int curr_subarray_len = 2; curr_subarray_len <= N; curr_subarray_len++)
        {
            for (int l = 0; l <= N - curr_subarray_len; l++)
            {
                int curr_gcd = nums[l] = gcd(nums[l], nums[l+1]);

                if (curr_gcd == 1)
                    return curr_subarray_len + N-2;
            }
        }

        return -1;
    }
};
