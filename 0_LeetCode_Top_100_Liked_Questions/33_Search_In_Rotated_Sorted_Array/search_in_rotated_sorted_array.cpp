/*
    ==============
    === MEDIUM ===
    ==============

    ==================================
    33) Search in Rotated Sorted Array
    ==================================

    ============
    Description:
    ============

    There is an integer array "nums" sorted in ascending order(with distinct
    values).

    Prior to being passed to your function, "nums" is *possibly rotated* at an
    unknown pivot index k (1 <= k < nums.length) such that the resulting array
    is:
    [nums[k], nums[k + 1], ..., nums[n - 1], nums[0], nums[1], ..., nums[k - 1]]
    (0-indexed).

    For example, [0, 1, 2, 4, 5, 6, 7] might be rotated at pivot index 3 and
    become [4, 5, 6, 7, 0, 1, 2].

    Given the array "nums" after the possible rotation and an integer target,
    return the index of target if it is in "nums", or -1 if it is not in "nums".

    =====
    Node: You must write an algorithm with O(log n) runtime complexity.
    =====

    =========================================================
    FUNCTION: int search(std::vector<int>& nums, int target);
    =========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  nums = [4, 5, 6, 7, 0, 1, 2], target = 0
    Output: 4

    --- Example 2 ---
    Input:  nums = [4, 5, 6, 7, 0, 1, 2], target = 3
    Output: -1

    --- Example 3 ---
    Input: nums = [1], target = 0
    Output: -1

    *** Constraints ***
    1 <= nums.length <= 5000
    -10^4 <= nums[i] <= 10^4
    All values of "nums" are unique
    "nums" is an ascending array that is possibly rotated
    -10^4 <= target <= 10^4

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Consider this example:
        [4, 5, 6, 7, 0, 1, 2]

    Given that the original Array was sorted, we can represent that as a graph:

        Original Array:
        [0, 1, 2, 4, 5, 6, 7]

        This line might not necessarily be linear, but it will always be
        increasing. (Note that this is the best way I can "draw" it using ASCII
        characters)

        ^         .   ^
        |         .  /
        |         . /
        |         ./
        |         /
        |        /.
        |       / .
        |      /  .
        |     /   .
        |    /    .
        |   /     .
        |  /      .
        | /       .
        |/        .
        --------------------------------->

        Now we swap these two portions.


        ^          ^
        |         /.
        |        / .
        |       /  .
        |      /   .
        |     /    .
        |    /     .
        |   /      .
        |  /       .
        | /        .
        |          .           ^
        |          .          /
        |          .         /
        |          .        /
        |          .       /
        |          .      /
        |          .     /
        |          .    /
        |          .   /
        |          .  /
        --------------------------------->



        Maybe this one represents it more accurate. It's hard to draw in ASCII.

        ^    ^
        |   /.
        |  / .
        | /  .
        |/   .
        |    .                ^
        |    .               /
        |    .              /
        |    .             /
        |    .            /
        |    .           /
        |    .          /
        |    .         /
        |    .        /
        |    .       /
        |    .      /
        |    .     /
        |    .    /
        |    .   /
        |    .  /
        --------------------------->

    In problem like this, we have to break it down to discrete cases and then
    use those cases to form a Solution.

    So, the most obvious thing is that there are two portions of the array
    that are sorted. The left portion and the right portion. Both independently
    are sorted.

    Now, we know that in order to have O(logn) we almost certainly have to use
    a Binary search.
    In a binary search we have:
        - Left  pointer
        - Mid   pointer
        - Right pointer

    The left is always going to be <= right, since we can have a single element
    in the entire array and thus this will cover that case too.

    So in our given example:
        [4, 5, 6, 7, 0, 1, 2]
               m

    Let's say that our mid value, at some point, is 6(the index 2).

    This means that we're in the Left sorted portion of the array. Can we use
    that to our advantage?

    Let's say that our target was greater than 6.

    In that case, we know for sure that, since we're in the Left sorted portion
    of the array, none of these values are greater than six: {4, 5, 6};

    So we can basically say that these values are eliminated and thus let's run
    binary search on the remaining part:
        [4, 5, 6, 7, 0, 1, 2]
               m  ~~~~~~~~~~

    So that's easy - If we know that we're in the Left sorted portion of the
    array and that our target is greater than the nums[mid], that's what we
    can do.

    Now, what if our target is less than the mid value? What if our target
    was less than 6?
    In our example:
        [4, 5, 6, 7, 0, 1, 2]
         ~~~~        ~~~~~~~
           ^            ^
these two _|            |
                        |
    and                 |
                        |
these three ____________|

    values are less than 6. So, how do we know which way to go?
    Do we go left or do we go right? We can't go both directions in a Binary
    Search.

    ***
    The key is to see that in our Left sorted portion, the smallest value is at
    nums[0]. In this case where we see that target is less than nums[mid].

    Or looking at our graph:

It's here:
    |
    |
    |
    |
    |
    |   ^    ^
    |   |   /.
    |   |  / .
    |   | /  .
    --> |/   .
        |    .                ^
        |    .               /
        |    .              /
        |    .             /
        |    .            /
        |    .           /
        |    .          /
        |    .         /
        |    .        /
        |    .       /
        |    .      /
        |    .     /
        |    .    /
        |    .   /
        |    .  /
        --------------------------->


    So if our target is even smaller than this left value 4 at nums[0], then in
    that case we know that we don't have to search: {4, 5, 6}.
    We can run Binary search on these:
        [4, 5, 6, 7, 0, 1, 2]
                  ~~~~~~~~~~

    However, if our target was greater or equal to 4(nums[0]) then that means
    that we're gonna have to run Binary Search on these two values:
        [4, 5, 6, 7, 0, 1, 2]
         ~~~~

    Because it's less than 6, but it's greater than or equal to 4.
    So we're removing all of these from consideration: {6, 7, 0, 1, 2}

    So all of that is when we were in the Left sorted portion of the array.

    Now, what happens if we're in the Right sorted portion of the array?
    Let's say that at some point, our mid was at value 1:
        [4, 5, 6, 7, 0, 1, 2]
                        m

    And let's say that somehow we knew that we're in the Right sorted portion
    of the array.

    What if our target was less than 1?
    Well then we know we have to search the only left value that is less than
    1, which is 0.

    So we're going to search the Left portion of this array:
        [4, 5, 6, 7, 0, 1, 2]
         ~~~~~~~~~~~~~~

    We're not going to look at: {1, 2}.
    We don't even necessarily have to know where is the pivot, we only have to
    know that we have to go left.

    But what if our target is greater than 1?

    Then our solution could possibly be: 2 or any of these: {4, 5, 6, 7}
        [4, 5, 6, 7, 0, 1, 2]
         ~~~~~~~~~~        ~~

    So where do we go?
    Again, we can use this right most value, or the edge basically of our
    array, to our advantage.

    So if our target is greater than 1 and it's also greater than 2, then that
    means that we have to search this Left portion.
        [4, 5, 6, 7, 0, 1, 2]
         ~~~~~~~~~~~~~

    But what if the opposite is true? What if our target is greater than 1, but
    it's less than or equal to 2?

    In that case we only have to run Binary Search on the right portion:
        [4, 5, 6, 7, 0, 1, 2]
                           ~~
    Every value to the right of one. Meaning we can remove all these elements
    from consideration: {4, 5, 6, 7, 0, 1}


    So this is a lot of discrete cases, it'll be a bit easier once you look at
    the code.

*/


/* Time  Beats: 80.49% */
/* Space Beats: 82.44% */

/* Time  Complexity: O(logn) */
/* Space Complexity: O(1) */
class Solution_Verbose {
public:
    int search(vector<int>& nums, int target)
    {
        const int N = nums.size();

        int low  = 0;
        int high = N-1;

        while (low <= high)
        {
            int mid = (low + high) / 2;

            if (target == nums[mid])
                return mid;

            // Left of "mid" is LOWER part of the rotation
            if (nums[low] <= nums[mid])
            {
                if (target > nums[mid] || target < nums[low])
                    low  = mid + 1;
                else
                    high = mid - 1;
            }
            else // Right of "mid" is UPPER part of the rotation
            {
                if (target < nums[mid] || target > nums[high])
                    high = mid - 1;
                else
                    low  = mid + 1;
            }
        }

        return -1;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This is much simpler.

    First use Binary Search to find pivot(First element BEFORE the rotation)
    Then  use Binary Search to find target.

*/

/* Time  Beats:   100% */
/* Space Beats: 58.46% */

/* Time  Complexity: O(logN) */
/* Space Complexity: O(1)    */
class Solution_Trick {
public:
    int search(vector<int>& nums, int target)
    {
        int n = nums.size();
        int left = find_pivot(nums);

        // Classical Binary Search
        if (target <= nums[n - 1])
            return binary_search(nums, left,  n-1  , target);

        return binary_search(nums,   0 , left-1, target);
    }

private:
    int find_pivot(const vector<int>& nums)
    {
        int left  = 0;
        int right = nums.size() - 1;

        while (left < right)
        {
            int mid = left + (right - left) / 2;

            if (nums[mid] > nums[right])
                left = mid + 1;
            else
                right = mid;
        }

        return left;
    }

    int binary_search(vector<int>& nums, int left, int right, int target)
    {
        while (left < right)
        {
            int mid = (left + right) / 2;

            if (nums[mid] == target)
                return mid;

            if (target < nums[mid])
                right = mid - 1;
            else
                left = mid + 1;
        }

        return nums[left] == target ? left : -1;
    }
};
