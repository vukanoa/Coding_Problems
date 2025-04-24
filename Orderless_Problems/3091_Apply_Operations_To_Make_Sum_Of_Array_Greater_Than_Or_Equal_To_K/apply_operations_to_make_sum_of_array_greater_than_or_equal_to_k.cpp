/*
    ==============
    === MEDIUM ===
    ==============

    ======================================================================
    3091) Apply Operations to Make Sum of Array Greater Than or Equal to K
    ======================================================================

    ============
    Description:
    ============

    You are given a positive integer k. Initially, you have an array nums = [1]

    You can perform any of the following operations on the array any number of
    times (possibly zero):

        + Choose any element in the array and increase its value by 1.

        + Duplicate any element in the array and add it to the end of the array

    Return the minimum number of operations required to make the sum of elements
    of the final array greater than or equal to k.

    ===================================
    FUNCTION: int minOperations(int k);
    ===================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: k = 11
    Output: 5
    Explanation:
    We can do the following operations on the array nums = [1]:
        Increase the element by 1 three times. The resulting array is nums = [4].
        Duplicate the element two times. The resulting array is nums = [4,4,4].
    The sum of the final array is 4 + 4 + 4 = 12 which is greater than or equal to k = 11.
    The total number of operations performed is 3 + 2 = 5.

    --- Example 2 ---
    Input: k = 1
    Output: 0
    Explanation:
    The sum of the original array is already greater than or equal to 1, so no
    operations are needed.


    *** Constraints ***
    1 <= k <= 10^5

*/

#include <cmath>
using namespace std;


/*
    ------------
    --- IDEA ---
    ------------

    For every i starting at 1, all he way up to k(inclusive), try to see how
    many duplicates of 'i' would you need to have sum >= k.

    Fro example:

    We're searching for minimum amount of operations needed to get sum k = 11.

    Let's move to i=4:

        i = 4;

    Now we have nums[4], for that happen we needed to increment 3 times.
    I.e. (i - 1) times.

    Now that we have:

        nums = [4]

    and since we're searching for k=11, but we already have 4, that means we
    need (11 - 4) more. Which is 7.

    How many times do we have to DUPLICATE our nums = [4] in order to get sum
    greater than 7?

    Twice.

    At the beginning we had: nums = [4], and we want total sum >= 11
    Since we already have sum of 4, we need (11 - 4) more.

    What is the MINIMUM amount of 4s we need to get sum >= 7?
    It's two 4s.

    In total that's:
        (i-1) // Which denotes the number of INCREMENT from
              // nums = [1] to nums = [4]

        ceil(7 / 4)


    Since these are mathematical operations that are done in O(1), we can try
    each and every one, starting at i=1 all the way up to k=11.

    Since Constraints of k are 10^5, that means we are indeed allowed to have
    Time Complexity of O(N).

*/

/* Time  Beats: 37.50% */
/* Space Beats: 40.22% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int minOperations(int k)
    {
        int result = k;

        for (int i = 1; i <= k; i++)
        {
            int operations = (i-1) + static_cast<int>(ceil(1.0 * (k - i) / i));

            result = min(result, operations);
        }

        return result;
    }
};
