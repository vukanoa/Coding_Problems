/*
    ==============
    === MEDIUM === (Previously was under HARD)
    ==============

    =================================
    128) Longest Consecutive Sequence
    =================================

    ============
    Description:
    ============

    Given an unsorted array of integers "nums", return the length of the
    longest consecutive elements sequence.

    =====
    Node: You must write an algorithm that runs in O(n) time.
    =====

    =========================================================
    FUNCTION: int longestConsecutive(std::vector<int>& nums);
    =========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  nums = [100, 4, 200, 1, 3, 2]
    Output: 4

    --- Example 2 ---
    Input:  nums = [0, 3, 7, 2, 5, 8, 4, 6, 0, 1]
    Output: 9

    *** Constraints ***
    0 <= nums.length <= 10^5
    -10^9 <= nums[i] <= 10^9

*/

#include <vector>
#include <unordered_set>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Let's consider the first Example:
    Input:  nums = [100, 4, 200, 1, 3, 2]

    The crux of this Solution is realizing that you do NOT need to start
    counting the length of a sequence unless it is the START of a sequence.

    That's the absolute crux.
    But how do we know if an element is a START of a sequence?

    The answer is - Starting element is the smallest in the sequence.
    This sounds obvious at first, but this is exactly what solves us this
    problem.


    If ONE less than the current element does NOT exist in the array, then
    we're sure it is a beginning of a sequence.

    Is there a way to efficiently check this?
    Yes there is. We can simply use a HashSet. Initially we push all of the
    elements of "nums" in a Hashset and then each time we want to check if the
    current element is the start of a sequence, we simply check:

        if (uset.count(curr_num - 1))
            ...

                            number in vector "nums"
                              |
                              |
                              v
    99  does NOT    exist so 100 is INDEED a starting element
    3   does INDEED exist so 4   is NOT    a starting element
    199 does NOT    exist so 200 is INDEED a starting element
    0   does NOT    exist so 1   is INDEED a starting element
    2   does INDEED exist so 3   is NOT    a starting element
    1   does INDEED exist so 2   is NOT    a starting element

    We only loop the while loop for starting elements, which in this example,
    are:
        100, 200 and 1.

    Thus we keep Time Complexity to O(n).

    If we represent the give Input visually, it becomes painfully obvious:
    (That's why you should always try to draw while you're solving!)

        1 2 3 4       100     200

    You can clearly observe that to know that a single element is a starting
    one, it must NOT have a left neighbor, i.e. its immediate previous value.

          1 doesn't have its left neighbor present int "nums", i.e. 0
        100 doesn't have its left neighbor present int "nums", i.e. 99
        200 doesn't have its left neighbor present int "nums", i.e. 199

    Therefore, each element will be processed exactly twice. Once when creating
    a HashSet at the beginning and once when iterating through sequence from
    each STARTING element, thus makking this Solution O(N) as necessary.

*/

/* Time  Beats: 42.27% */
/* Space Beats: 41.21% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    int longestConsecutive(vector<int>& nums)
    {
        int result = 0;
        unordered_set<int> uset(nums.begin(), nums.end()); // O(N)

        // O(N) (entire block)
        for (const int& num : uset)
        {
            int curr_num = num;

            // Amortized O(1)
            if (uset.count(curr_num - 1)) // Then it's NOT a start of a seq.
                continue;

            int sequence_length = 0;
            while (uset.count(curr_num)) // Once per consecutive sequence
            {
                sequence_length++;
                curr_num++;
            }

            result = max(result, sequence_length); // O(1)
        }

        return result;
    }
};
