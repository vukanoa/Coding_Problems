#include <iostream>
#include <vector>
#include <algorithm>

/*
    ==============
    === MEDIUM ===
    ==============

    ====================================
    2563) Count the Number of Fair Pairs
    ====================================

    ============
    Description:
    ============


    Given a 0-indexed integer array nums of size n and two integers lower and
    upper, return the number of fair pairs.

    A pair (i, j) is fair if:

        0 <= i < j < n, and

        lower <= nums[i] + nums[j] <= upper

    ============================================================================
    FUNCTION: long long countFairPairs(vector<int>& nums, int lower, int upper);
    ============================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [0,1,7,4,4,5], lower = 3, upper = 6
    Output: 6
    Explanation: There are 6 fair pairs: (0,3), (0,4), (0,5), (1,3), (1,4), and
                 (1,5).

    --- Example 2 ---
    Input: nums = [1,7,9,2,5], lower = 11, upper = 11
    Output: 1
    Explanation: There is a single fair pair: (2,3).


    *** Constraints ***
    1 <= nums.length <= 10^5
    nums.length == n
    -10^9 <= nums[i] <= 10^9
    -10^9 <= lower <= upper <= 10^9

*/

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    This part is VERY important:

        A pair (i, j) is fair if:       0 <= i < j < n


    What this means is NOT that we CANNOT sort the input, but rather that the
    same exact pair must NOT be counted more than once.

    Example:
        Input: nums = [0,1,7,4,4,5], lower = 3, upper = 6

        At this point we ONLY care about "nums".

            nums = 0, 1, 7, 4, 4, 5

        What they mean with when they say: 0 <= i < j < n
        is that we CANNOT count the same pair twice:

        Consider this:

                   0  1  2  3  4  5
            nums = 0, 1, 7, 4, 4, 5         // This is ONE pair: (1, 3)
                      i     j


                   0  1  2  3  4  5
            nums = 0, 1, 7, 4, 4, 5         // This is THE SAME pair: (3, 1)
                      j     i

        So, to prevent counting the same pair more than once, they say:
            0 <= i < j < n

        However, that DOESN'T mean that we cannot sort it. It ONLY means that
        we should somehow prevent counting one pair more than once.
        (I know I'm repeating myself, but this is CRUCIAL to understand)


    Knowing this, it kind of becomes obvious, but it's still difficult.
    Let's sort our Input:

                   0  1  2  3  4  5
            nums = 0, 1, 4, 4, 5, 7

    Now, instead of doing a Brute-Force way where for every idx that is < n-1
    we consider all the remaining elements to the right side of idx. And since
    we must do that for every idx < n-1, it would be a O(n^2) Solution.

    However, since we've realized we actually are allowed to sort the Input,
    there must be a way to do this in a more efficient way than doing a plain
    and naive Brute-Force for a MEDIUM problem.

    What are, generally speaking, our options when the Input is sorted?
    What comes to mind first?

    Yes, a Binary Search. (Two Pointers also comes to mind)

    We are going to, kind of, use both BinarySearch and TwoPointers.

    "Two Pointers" is usually the way if we are searching for a certain target.
    Like in the famous, basic, example:

        "LeetCode 167: Two Sum II - Input is sorted".

    However, "target" is not what we are looking for in this sorted input.
    Instead we are looking a range between which the sum of two elements could
    reside in.

    First we need to find:

        X + nums[j] <= upper

        where "X" is the current number for which we'll perform a Binary Search
        and "nums[j]" is the number that "X" can be added to without going
        ABOVE the upper bound of "upper".

    But, there is a nice little trick we can use here. It's not too intuitive,
    but it's not too bad either.

    Usually when we are writing a Binary Search, it's MUCH easier to find the
    bound if we have "<" instead of "<=".

    So, how can we get rid of it here:

        X + nums[j] <= upper

    We can simply do this:

        X + nums[j] < upper + 1

    That is EQUIVALENT, but it greatly facilitates the implementation of Binary
    Search function that we need.

    Since we're doing it for the "X" currently, we are essentially doing this:

        nums[j] < upper + 1 - X

    Index 'j' is actually going to be the right bound "R". (See below)


    However, if we have indeed found the last index that suits our needs, we're
    not done.

    We would be in this position:

               0  1  2  3  4  5
        nums = 0, 1, 4, 4, 5, 7          lower = 3, upper = 6
               X           R


        R - The largest element that is LESS THAN or EQUALS to "upper".


        nums[j] < upper + 1 - X
        nums[j] <   6   + 1 - 0
        nums[j] <   7

        So, the largest element that is STRICTLY LESS THAN 7 is element 5 at
        index 4.

        j == R == 4

    Now, we also must find "L", which is the smallest element that is EQUAL to
    or GREATER than "lower" - X, which in this case is:

        lower - X <==> 3 - 0 <==> 3

        Imagine that we had a similar example:

                   0  1  2, 3, 4  5  6  7
            nums = 0, 1, 3, 3, 4, 4, 5, 7          lower = 3, upper = 6
                   X     L           R

        In this example, what we did is we found ALL the elements that CAN BE
        added to element X(0 in this case) and be within the inclusive range
        of [3, 6].

        That is what we are doing.

    Since we are looking for "L", that means we are looking for the SMALLEST
    number that is EQUAL to or GREATER than:

        lower - X, i.e. 3-0, i.e. 3

    in this case.


    It's as if we are FIXED on X(0 in this case) and we are searching for all
    the elemenst from the remaining elements to the right of this element that
    are going to be within the range [lower, upper] when added to X.

    (Read his again. It's confusing not because of the words I've used, but
     becaues it is difficult and it takes time to "click")

    This is a straight-up optimization of the Brute-Force Solution.

    Remember, what was the Brute-Force?

        Fix the first element and consider all the elements to the right. To
        determine which one will suit, you have to scan linearly through the
        array to find that.

        Now, instead of scanning linearly, we are doing a Binary Search.

        Linear scan for EVERY element(except the very last one) takes: O(n^2)
        Bin_Search  for EVERY element(except the very last one) takes: O(n*logn)

    That's why and how this is an Optimization.

    Once we are fixed on X, we are searching for two things:
        1. Largest  number that can be added to X and falls <= "upper"
        2. Smallest number that can be added to X and falls >= "lower"

    Do that for every element(except the very last one because the last one
    cannot be paired since we are always pairing with elements TO THE RIGHT)
    and that will take O(n * logn).

        1. Largest  number that can be added to X and falls <= "upper"

            nums[j] < upper + 1 - X

        2. Smallest number that can be added to X and falls >= "lower"
            nums[j] >= lower - X
                or
            nums[j] <  lower - X    // So that we don't have to write two
                                    // different Binary Search functions and so
                                    // that we can simply subtract two indices.

    Because we've used "+1" for the 1st Binary Search and because we've used
            nums[j] <  lower - X
    we can simply subtract these two numbers and we got the amount of pairs for
    X that fall within the range of [lower, upper].

                   0  1  2, 3, 4  5  6  7
            nums = 0, 1, 3, 3, 4, 4, 5, 7          lower = 3, upper = 6
                   X  L              R

    This means that for element X(0 in this case. It's ELEMENT, not INDEX) we
    have 6-1 pairs, i.e. 5 pairs that are within the inclusive range [3, 6]:

        (0, 2), (0, 3), (0, 4), (0, 5), (0, 6)
         0+3      0+3     0+4    0+4     0+5

    That's the entire idea.

*/

/* Time  Beats: 72.02% */
/* Space Beats: 61.66% */

/* Time  Complexity: O(n * logn)  */
/* Space Complexity: O(1) or O(n) */ // Depending on the Sort
class Solution {
public:
    long long countFairPairs(vector<int>& nums, int lower, int upper)
    {
        const int n = nums.size();
        long long result = 0;

        /* Sort */
        sort(nums.begin(), nums.end());

        for (int i = 0; i < nums.size(); i++)
        {
            int low = lower - nums[i];
            int up  = upper - nums[i];

            result += (bin_search(nums, i+1, n-1, up+1) - bin_search(nums, i+1, n-1, low));
        }

        return result;
    }

private:
    int bin_search(vector<int>& nums, int left, int right, int target)
    {
        while (left <= right)
        {
            int mid = left + (right - left) / 2;

            if (nums[mid] >= target)
                right = mid - 1;
            else
                left  = mid + 1;
        }

        return right; // It MUST be index "right"
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Almost equivalent approach, but using STL's functions:
        1. upper_bound, and
        2. lower_bound

    In this one, we are NOT trying to get right of "<=" with "upper + 1",
    because std::upper_bound gets rid of that problem for us.

    And std::lower_bound is EXACTLY what we needed up there.


    Now, instead of this:


               0  1  2  3  4  5
        nums = 0, 1, 4, 4, 5, 7          lower = 3, upper = 6
               X  L        R


    We'll have it like this:


               0  1  2  3  4  5
        nums = 0, 1, 4, 4, 5, 7          lower = 3, upper = 6
               X     L        R

    
    That's why both work, but here we are using STL's functions so the indices
    will be like this.

*/

/* Time  Beats: 63.10% */
/* Space Beats: 61.66% */

/* Time  Complexity: O(n * logn)  */
/* Space Complexity: O(1) or O(n) */ // Depending on the Sort
class Solution_STL {
public:
    long long countFairPairs(vector<int>& nums, int lower, int upper)
    {
        const int n = nums.size();
        long long result = 0;

        /* Sort */
        sort(nums.begin(), nums.end());

        for (int i = 0; i < n-1; i++)
        {
            auto up  = std::upper_bound(nums.begin() + i + 1, nums.end(), upper - nums[i]);
            auto low = std::lower_bound(nums.begin() + i + 1, nums.end(), lower - nums[i]);

            result += (up - low);
        }

        return result;
    }
};
