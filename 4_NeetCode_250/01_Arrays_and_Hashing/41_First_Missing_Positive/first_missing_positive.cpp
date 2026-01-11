/*
    ============
    === HARD ===
    ============

    ===========================
    41) First Missing Positive
    ===========================

    ============
    Description:
    ============

    Given an unsorted integer array "nums", return the smallest missing
    positive integer.

    You must implement an algorithm in O(N) time and uses constant extra space.

    ======================================================
    FUNCTION: int firstMissingPositive(vector<int>& nums);
    ======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  nums = [1, 2, 0]
    Output: 3

    --- Example 2 ---
    Input:  nums = [3, 4, -1, 1]
    Output: 2

    --- Example 3 ---
    Input:  nums = [7, 8, 9, 11, 12]
    Output: 1

    *** Constraints ***
    1 <= nums.length <= 10^5
    -2^31 <= nums[i] <= 2^31 - 1

*/

#include <cstdlib>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    ***********
    **** N ****
    ***********

    It's important to notice that the return value has to be from this set of
    values:
        {1, 2, ..., num.size(), N + 1}

    To convince you of that, consider the following example:
    1.a)
        nums = [7, 0, -15, 2]
        smallest = 1            // 1

    1.b)
        nums = [10, 11, 12]
        smallest = 1            // 1

    1.c)
        nums = [2, 3, 4]
        smallest = 1            // 1



    2)
        nums = [1, 2, 4]
        smallest = 3            // ...  | Between 1 and N+1



    3)
        nums = [1, 2, 3, 1417]
        smallest = 4            // N



    4)
        nums = [1, 2, 3]
        smallest = 4            // N + 1

        Notice how both 0 and -15 are ignored since we're told:
            "return the smallest missing positive integer"


    We don't have to sort the elements, we can take the input array nums and
    convert it to Hash Set.

    Why Hash Set? Well, because we could "brute-force" it iterating trough

        [1, 2, ..., N + 1]

    and we can check if 'i'(index in this set [1, ..., N + 1]) does exist in
    Hash Set.

    If it does, then i++ and check the next i, and so on.

    We stop once we've found that current 'i', current possible_values[i] does
    NOT exist in array nums and we return that.

    If, however, we do not find that, just return N + 1.
    That is the worst case scenario.

    So since each of this "check" takes O(1) time and we're doing it O(N) times
    that makes it: O(1 * N), however the Space Complexity is O(N) as well which
    isn't what is required by the Description of a problem.

    But we can use this to our advantage. We can devise a Solution where we
    don't need a Hash Set.

    How are we going to do that?
    We need some extra memory, right?

    True, but it turns out that we can use our array nums as the
    "extra memory", that is, we don't need extra memory really.
    That doesn't count.

    Using "Negative Marking" technique within our "nums" vector.

        nums = [3, -3, 6, 3]    // Hash Set (kind of)

    Again, remember that our Solution set is: [1, ..., N + 1]
    So for every value out of [1, ..., N] (NOT the N + 1) we have a
    corresponding index in our original array nums.

    1 will be mapped to       0th index
    2 will be mapped to       1st index
    3 will be mapped to       2nd index
    3 will be mapped to       3rd index
    ...
    N will be mapped to (N - 1)th index


    So, how are we going to use this original array as our Hash Set?

    We're going to do this:
        index = value - 1

    And we're going to check if nums[index] is a NEGATIVE value.

    Also, it's important to note that negative values at certain indices aren't
    telling us where are those values in the array. It ONLY tells us that they
    DO exist in the input array nums.

    But there is one problem - It turns out that this input array, at the
    beginning, already have negative values in it.

    So, how are we going to handle that?

    It turns out that negative numbers, once we iterate through the array
    trying to find the smallest, are USELESS to us. As well as 0's.

    If we were to take every negative value in the nums and crossed it, it
    would NOT matter.

    So, first thing we're going to do is go through the array and replace every
    negative number with 0.

    Why 0?

    Because 0 is also a USELESS number in nums.
    If we were to change every negaive number to 1s or 2s, then we'd possibly
    change the Output, making it incorrect.

    However, 0 is NEVER going to be a result, therefore we can change it.

    The new "problem" we have is the the negative elements we stumble upon are
    NOT negative, they're just marked by some previous value.

    Also we wish this "marking process" to be idempotent, meaning -- We do NOT
    want to multiply by -1 if that position is already negative(i.e. marked)
    because that would unmark it.
*/

/* Time  Beats: 100.00% */
/* Space Beats:  60.72% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Negative_Marking {
public:
    int firstMissingPositive(std::vector<int>& nums)
    {
        const int N = nums.size();

        for (int i = 0; i < N; i++)
        {
            if (nums[i] < 0)
                nums[i] = 0; // Convert all the initial negatives to 0s
        }

        for (int i = 0; i < N; i++)
        {
            int value = abs(nums[i]);

            if (value < 1 || value > N)
                continue;

            if (nums[value - 1] > 0)
            {
                nums[value - 1] *= -1;
            }
            else if (nums[value - 1] == 0)
            {
                nums[value - 1] = -1 * (N + 1);
            }
        }

        for (int i = 1; i < N+1; i++)
        {
            if (nums[i - 1] >= 0)
                return i;
        }

        return N + 1;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Put each number in its right place.
    It's kind of like sorting, but not exactly. We're sure that we will swap at
    worst n times, while trying to "sort".

    Thus this makes it O(N) which is required.

    It's important to notice that the return value has to be from this set of
    values:
        {1, 2, ..., N, N+1}

    Once we see that, we can come up with this Solution, since we can see that
    we don't have to "sort" values that are greater than "N + 1".


    We have to put each value at [value - 1]th index in array nums, using the
    "swap" function.

    Example:
    We find number 4 in our array "nums" and we should swap it with nums[3]

    Once we have "sorted" the array, the first place where its number is not
    right, return position + 1;

    We iterate through an entire array and check if the number is greater
    than 0 and less or equals to n, since we only consider positive integers.
    And if we have all the positive integers from 1 to n in our array, then
    return n + 1.

    If the number is between 1 and n then if that number(nums[i]) is not in
    the right place, that is:
        nums[nums[i] - 1] != nums[i]

    then swap it to a place where its supposed to be. Then again, within the
    while loop do this again - Place the current number under nums[i] to its
    right place in the array. That is:
        nums[nums[i] - 1] = nums[i]

    If we are doing multiple swaps for a single value of 'i', and we are
    iterating through an entire array, you may ask - how is it possible that a
    complexity is still O(N)?

    We will have multiple swaps for i == 0(in our example below), but as we
    iterate we will have less and less swap. Sometimes 1, and most of the
    times 0.

    In the end the total amount of swaps in an entire for loop is <= n.

    Our example: (Before 1st Iteration)
    [7, 1, 4, 9, 2, 8, 3, 5]

    1st iteration (i == 0)
        [3, 1, 4, 9, 2, 8, 7, 5]
        [4, 1, 3, 9, 2, 8, 3, 5]
        [9, 1, 3, 4, 2, 8, 7, 5]

    2nd iteration (i == 1)
        [1, 9, 3, 4, 2, 8, 7, 5]

    3rd iteration (i == 2)
        // Nothing has changed

    4th iteration (i == 3)
        // Nothing has changed

    5th iteration (i == 4)
        [1, 2, 3, 4, 9, 8, 7, 5]

    6th iteration (i == 5)
        [1, 2, 3, 4, 9, 5, 7, 8]
        [1, 2, 3, 4, 5, 9, 7, 8]

    7th iteration (i == 6)
        // Nothing has changed

    8th iteration (i == 7)
        // Nothing has changed


    **************************
    *** Counting the swaps ***
    **************************
    1st iteration
        3 swaps

    2nd iteration
        1 swap

    3rd iteration
        0 swaps (nums[2] == 3) // It's a CORRECT_SLOT

    4th iteration
        0 swaps (nums[3] == 4) // It's a CORRECT_SLOT

    5th iteration
        2 swaps

    6th iteration
        1 swap

    7th iteration
        0 swaps (nums[6] == 7) // It's a CORRECT_SLOT

    8th iteration
        0 swaps (nums[7] == 8) // It's a CORRECT_SLOT


    Total number of swaps = 3 + 1 + 2 + 1 = 7 <= n

    Therefore - Time Complexity is O(N)

    Complexity explained:
    Consider nums[i] = i + 1 as a CORRECT_SLOT

        i) CORRECT_SLOT will never be changed; for CORRECT_SLOT,
        nums[nums[i] - 1] always equals to nums[i].

        ii) For each std::swap, the number of CORRECT_SLOT's increases by
        at least 1.
        Position: nums[nums[i] - 1] = nums[i] becomes CORRECT_SLOT after
        std::swap, and according to i) this MUST be a new CORRECT_SLOT

        iii) The maximum of CORRECT_SLOTs <= n

    Therefore, Time complexity is O(N)

    In other words:
    We visit each number once, and each number will be put in its right place
    at most once.
    So, the first part is O(N), and the iterating again through the array is
    also O(N), that makes it:
        O(N) + O(N) => O(2 * N) => O(N).
*/


/* Time  Beats: 72.30% */
/* Space Beats: 50.54% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Cycle_Sort_From_Index_0 {
public:
    int firstMissingPositive(vector<int>& nums)
    {
        const int N = nums.size();

        // O(N) (entire block)
        for (int i = 0; i < N; i++)
        {
            int curr_elem = nums[i];

            /*
                // Check if curr_elem is in range[1, n]
                curr_elem >= 1 && curr_elem <= n

                // Check if curr_elem is ALREADY at i+1(where it should be)
                curr_elem-1 != i

                // Check if at curr_elem-1 there is ALREADY the CORRECT element
                nums[curr_elem - 1] != curr_elem
            */
            while (curr_elem >= 1 && curr_elem <= N && curr_elem-1 != i && nums[curr_elem-1] != curr_elem)
            {
                swap(nums[curr_elem-1], nums[i]);
                curr_elem = nums[i];
            }
        }

        // O(N) (entire block)
        for (int i = 0; i < N; i++)
        {
            if (nums[i] != i+1)
                return i+1;
        }

        return N+1;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This implementation is different.

    Instead of trying to place each element at its value-1 index, we actually
    place it at index==value.

    Why?
    First, becase it's MUCH easier to write. We don't have the annoying
    overhead od thinking about +1 or -1 indices.

    Second, the only thing that is different, then, is that once we're done
    and we have our final "index" as a result, we must check if at index 0
    there is our current result.

    If that's the case, then our result actually ought to be index+1.
    Otherwise, it's "index".

    That's the whole difference, but this is MUCH easier to write.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  31.31% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Cycle_Sort_From_Index_1 {
public:
    int firstMissingPositive(vector<int>& nums)
    {
        const int N = nums.size();

        // O(N) (entire block)
        for (int i = 0; i < N; i++)
        {
            /*
               For the ease of reading:
               
               // If nums[i] is NOT at 'i'(where it ought to be):
               nums[i] != i

                 and

               // If nums[i] is within the bounds of nums(i.e. >= 0 && < N)
               nums[i] >= 0 && nums[i] < N

                 and

               // If nums[nums[i]] != nums[i] <==> nums[curr_value] != curr_val
               nums[nums[i]] != nums[i]

               This last thing prevents INFINITE CYCLE.
               Consider this:

                   nums = [1, 1]
                           0  1

               So if the CORRECT element is ALREADY at the position where the
               current_element SHOULD be, then just get out of this while-loop,
               because we already have the CORRECT element at index "nums[i]",
               i.e. at index "current_element".

            */
            while (nums[i] != i && nums[i] >= 0 && nums[i] < N && nums[nums[i]] != nums[i])
                swap(nums[i], nums[nums[i]]);
        }

        // O(N) (entire block)
        int index = 1;
        while (index < N)
        {
            if (nums[index] != index)
                break;

            // Increment
            index++;
        }

        return nums[0] == index ? index+1 : index;
    }
};
