/*
    ==============
    === MEDIUM ===
    ==============

    ======================================================================
    3192) Minimum Operations to Make Binary Array Elements Equal to One II
    ======================================================================

    ============
    Description:
    ============

    You are given a binary-array nums.

    You can do the following operation on the array any number of times
    (possibly zero):

        + Choose any index i from the array and flip all the elements from
          index i to the end of the array.

    Flipping an element means changing its value from 0 to 1, and from 1 to 0.

    Return the minimum number of operations required to make all elements in
    nums equal to 1.

    ===============================================
    FUNCTION: int minOperations(vector<int>& nums);
    ===============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [0,1,1,0,1]
    Output: 4
    Explanation:
    We can do the following operations:
        Choose the index i = 1. The resulting array will be nums = [0,0,0,1,0].
        Choose the index i = 0. The resulting array will be nums = [1,1,1,0,1].
        Choose the index i = 4. The resulting array will be nums = [1,1,1,0,0].
        Choose the index i = 3. The resulting array will be nums = [1,1,1,1,1].


    --- Example 2 ---
    Input: nums = [1,0,0,0]
    Output: 1
    Explanation:
    We can do the following operation:
        Choose the index i = 1. The resulting array will be nums = [1,1,1,1].


    *** Constraints ***
    1 <= nums.length <= 10^5
    0 <= nums[i] <= 1

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Since we need to make all the 0's become 1's, and since we are obliged to
    flip all the bits from that index until the end of an array, it makes no
    sense to try and do it from the back.

    Why?
    Because if we turn 0's to 1's going backwards, then as soon as we get to
    some lefter 0, we're going to mess everything up.

    Therefore, we should go from left-to-right and as soon as we stumble upon
    0, we flip all the bits until the end.

    However, since physically flipping bits would be WAY to inefficien since it
    would require going to N elements and flipping them, what we can do is just
    remember which "state" we're in.

    What's a "state" in this context?

    A "state" is whether we're looking for a 0 or a 1.

    But why would we be looking at 1 ever?
    Good question!

    Since, once we find a 0, we do NOT want to go through all the remaining
    elements and flip them individually, what we can do instead is starting
    looking for the next 1 now and not zero.

    But why?
    Consider this example:

        nums = [0,1,1,0,1]
                0 1 2 3 4

    Once we flip the lefmost zero(index 0) to become 1 and we flip all the
    remining ones we are in this "state":

        nums = [1,0,0,1,0]
                0 1 2 3 4

    Therefore, we now see that we need to flip bit at index 1.
    However, since we'll NOT go through the elements to ACTUALLY flip them, we
    then need to remember in which "state" we are on.

        1) normal = true  // Search for next 0
        1) normal = false // Search for next 1

    Why?

        nums = [0,1,1,0,1]
                0 1 2 3 4

    Because once we flip 0 at index 0, now the 1 at index 1 would become 0.
    However since we are NOT ACTUALLY flipping it, it's still 1. Therefore we
    act as if all the 1s are 0s and all the 0s are ones when the "state" is:

        normal = false;

    That's it.

*/

/* Time  Beats: 35.53% */
/* Space Beats: 35.53% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int minOperations(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 0;

        bool normal = true; // normal == false <==> INVERTED
        for (int i = 0; i < N; i++)
        {
            if (normal)
            {
                if (nums[i] == 0)
                {
                    result++;
                    normal = !normal;
                }
            }
            else
            {
                if (nums[i] == 1)
                {
                    result++;
                    normal = !normal;
                }
            }
        }

        return result;
    }
};
