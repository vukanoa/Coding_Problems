/*
    ==============
    === MEDIUM ===
    ==============

    =====================================
    3644) Maximum K To Sort a Permutation
    =====================================

    ============
    Description:
    ============

    You are given an integer array nums of length n, where nums is a permutation
    of the numbers in the range [0..n - 1].

    You may swap elements at indices i and j only if nums[i] AND nums[j] == k,
    where AND denotes the bitwise AND operation and k is a non-negative integer

    Return the maximum value of k such that the array can be sorted in
    non-decreasing order using any number of such swaps. If nums is already
    sorted, return 0.

    =================================================
    FUNCTION: int sortPermutation(vector<int>& nums);
    =================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [0,3,2,1]
    Output: 1
    Explanation: Choose k = 1. Swapping nums[1] = 3 and nums[3] = 1 is allowed
                 since nums[1] AND nums[3] == 1, resulting in a sorted
                 permutation: [0, 1, 2, 3].

    --- Example 2 ---
    Input: nums = [0,1,3,2]
    Output: 2
    Explanation: Choose k = 2. Swapping nums[2] = 3 and nums[3] = 2 is allowed
                 since nums[2] AND nums[3] == 2, resulting in a sorted
                 permutation: [0, 1, 2, 3].

    --- Example 3 ---
    Input: nums = [3,2,1,0]
    Output: 0
    Explanation: Only k = 0 allows sorting since no greater k allows the
                 required swaps where nums[i] AND nums[j] == k.


    *** Constraints ***
    1 <= n == nums.length <= 10^5
    0 <= nums[i] <= n - 1
    nums is a permutation of integers from 0 to n - 1.

*/

#include <algorithm>
#include <vector>
using namespace std;


/*
    ------------
    --- IDEA ---
    ------------

    This one seems easy at first, then it seems really trick, then once you
    figure it out, it looks easy once again.


    First, it's important to understand what we're being asked to do here.

    They are essentially asking:
        If you find element nums[i] that is NOT in its position, try to swap it
        with some other nums[j] elements ONLY if (nums[i] & nums[j] == k),
        where k is a non-negative number.


    It's important to bring to your attention the fact that we're working with
    elements [0, n-1].

    There are NO negative numbers.

    Also, it's important to realize that when you do "bitwise AND" operation
    on ANY TWO NON-NEGATIVE numbers, the result will always be >= 0.

    It seems trivial, but this is very important.

    What this suggests is that, if we proclaim 'k' to be 0, then we're allowed
    to swap any two elements in the "nums" vector.

    In other words -- We're able to sort "nums", which means that for k=0, it's
    ALWAYS possible.


    Now, consider other thing: If some number is NOT where it SHOULD be, then
    then we need to swap it with a number that SHULD INDEED be at this index.

    First time, we do it without any problems. However, what if the next number
    has different "bitiwse AND" than the previous swap?

    Example:

                    i
            nums = [7, 9, 3, 5] // Original
            nums = [3, 5, 7, 9] // What it SHOULD be


        When i=0, we realize that 7 is NOT where it should. At i=0 there should
        be the lowest element, i.e. 3.

        Then we need to check if we CAN swap 7 and 3.
        Since their "bitiwse AND" gives 3, and since this is a FIRST swap, we
        can swap ANY two numbers.

            7 & 3 = 3

        Now we're in this position:

                       i
            nums = [3, 9, 7, 5] // Original
            nums = [3, 5, 7, 9] // What it SHOULD be

        Here, 9 is also NOT where it should. At i=1 there should be 5.

        But can we swap 9 with 4?

            9 & 5 = 1

        But our PREVIOUS swap value was 3. We're NOT allowed to CHANGE the
        value of 'k'.

        We need to check what is the MAXIMUM VALUE of k such that we can swap
        elements to its place.


        So what should we do?

        Should we say that this is NOT possible to sort at all?
        Or just say k=0 and return that?

        Or is there maybe some other variation in which we can swap elements?

        Maybe we can swap 9 with some other element and then that new element
        with the desired 5. But that would get too complicated very quickly,
        wouldn't it?


        Also, if:
                X & Y = Z,

        but you need X & Y to be equal M, then no matter what you do with Y,
        you will NOT be albe to find an element which Y can give M that also
        gives M when you AND it with X.

        That's just not possible.
        You're free to try and find the counter-example. (Hint hint: you won't)


        However, order of swapping DOES matter.
        When we're able to swap 7 and 3, but NOT 9 and 5, we shouldn't just
        say "it's not possible to sort this array", instead we should check 
        what is the result if we AND all of the misplaced elements.


        Consider this example:

            nums = [0, 1, 2, 3, 7, 6, 4, 5] // Original
            nums = [0, 1, 2, 3, 7, 6, 4, 5] // What it SHOULD be
                    0  1  2  3  4  5  6  7


        If we try to swap 7 with 4, our 'k' will be 4.
        If we try to swap 6 with 5, our 'k' will be 4.

        But now,
        if we try to swap 7 with 6, our 'k' will be 6 which is ILLEGAL.
        Does that mean we're NOT able to swap elements when k=4?


        NO!


        If we "bitwise AND" all misplaced elements, i.e.: 7, 6, 4, 5

            7 AND 6 AND 4 AND 5 = 4


    Essentially, this Solution is:

        Collect ALL of the MISPLACED elements and do a "bitwise AND" of them.
        The number you get is the highest 'k' for which we can SORT the array.

*/

/* Time  Beats: 22.63% */
/* Space Beats: 31.09% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N) */
class Solution {
public:
    int sortPermutation(vector<int>& nums)
    {
        const int N = nums.size();

        vector<int> sorted = nums;
        sort(sorted.begin(), sorted.end());

        if (nums == sorted)
            return 0;

        int k = -1;
        for (int i = 0; i < N; i++)
        {
            if (nums[i] != sorted[i])
            {
                if (k == -1)
                    k = nums[i];
                else
                    k &= nums[i];
            }
        }

        return k == -1 ? 0 : k;
    }
};
