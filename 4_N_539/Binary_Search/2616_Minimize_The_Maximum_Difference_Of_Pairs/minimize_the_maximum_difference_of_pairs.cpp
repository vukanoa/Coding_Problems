#include <iostream>
#include <vector>
#include <algorithm>

/*
    ==============
    === MEDIUM ===
    ==============

    ==============================================
    2616) Minimize the Maximum Difference of Pairs
    ==============================================

    ============
    Description:
    ============

    You are given a 0-indexed integer array nums and an integer p. Find p pairs
    of indices of nums such that the maximum difference amongst all the pairs
    is minimized. Also, ensure no index appears more than once amongst the p
    pairs.

    Note that for a pair of elements at the index i and j, the difference of
    this pair is |nums[i] - nums[j]|, where |x| represents the absolute value
    of x.

    Return the minimum maximum difference among all p pairs. We define the
    maximum of an empty set to be zero.

    ====================================================
    FUNCTION: int minimizeMax(vector<int>& nums, int p);
    ====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [10,1,2,7,1,3], p = 2
    Output: 1
    Explanation: The first pair is formed from the indices 1 and 4, and the
                 second pair is formed from the indices 2 and 5.  The maximum
                 difference is max(|nums[1] - nums[4]|, |nums[2] - nums[5]|) =
                 max(0, 1) = 1. Therefore, we return 1.


    --- Example 2 ---
    Input: nums = [4,2,1,2], p = 1
    Output: 0
    Explanation: Let the indices 1 and 3 form a pair. The difference of that
                 pair is |2 - 2| = 0, which is the minimum we can attain.


    *** Constraints ***
    1 <= nums.length <= 10^5
    0 <= nums[i] <= 10^9
    0 <= p <= (nums.length)/2

*/

/*
    ------------
    --- IDEA ---
    ------------

    LOOK AT THE CONSTRAINTS!!!

    In this problem it would be very difficult to come up with a Binary Search
    if you didn't read the "Constraints".

        1 <= nums.length <= 105     // N
        0 <= nums[i] <= 109         // M
        0 <= p <= (nums.length)/2


    Which means that O(N * logX) is much much better than O(N^2)

    Since we want to find p pairs with a certain difference:
        1. Sort the array
        2. Take "mid" from range 1 - M
        3. Try to find p pairs with that "mid" difference

            nums = [4, 5, 7, 9, 17]

        Always check the very next one to the one you're currently on
        because if they are sorted it means that the next one will make the
        LEAST absolute difference.

        If you're on index 0(element 4), with which number will element 4
        make the smallest ABSOLUTE difference out of the remaining ones?

        Well, it's certainly not going to be the last element in this SORTED
        array since that would MAXIMIZE the difference.

        Similarly, to MINIMIZE we just want to take the very next element
        and try to see if it makes a difference less than or equal to mid.

        If we get to find 'p' of such pairs, then update "result" and
        move "right" pointer to point to the left so that we can try some
        other "difference" from range 1 - 10^9, using Binary Search of course.

*/

/* Time  Beats: 87.06% */
/* Space Beats: 14.77% */

/*
    Time  Complexity: O(N * logM)

    N is the length of "nums", whereas M is the upper bound of nums[i].

    As stated in the constraints:
        1 <= nums.length <= 10^5
        0 <= nums[i] <= 10^9

    One way to solve this problem is to do it in O(N^2) by doing nested loops.
    However, which one is more efficient?

        O(N^2) or (N * logM)?

        N = 100000       // sqrt(N) = 316
        M = 1000000000   // log(M)  = 9

    In other words - "log" grows MUCH MUCH slower than "sqrt" function.
    Therefore, in this problem(at least for these values), we can say with
    confidence that O(N * logM) is faster than O(N^2)

*/
/*
    Space Complexity: O(1)

    Depending on the sort
*/
class Solution_Readable {
public:
    int minimizeMax(std::vector<int>& nums, int p)
    {
        std::sort(nums.begin(), nums.end());

        int left  = 0;
        int right = std::pow(10, 9);

        int result = 0;

        while (left <= right)
        {
            int mid = left + (right - left) / 2;

            if (able_to_make_p_pairs_with_difference(mid, nums, p))
            {
                result = mid;
                right = mid - 1;
            }
            else
                left  = mid + 1;
        }

        return result;
    }

private:
    bool able_to_make_p_pairs_with_difference(int& mid, std::vector<int>&nums, int& p)
    {
        int count = 0;
        int i = 0;

        while (i+1 < nums.size())
        {
            if (std::abs(nums[i] - nums[i+1]) <= mid)
            {
                count++;
                i += 2;
            }
            else
                i++;

            if (count == p)
                return true;
        }

        return false;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    It's the exact same idea, however it's much more efficient since we are
    not going from 10^9 as the right bound, but the maximum value in our sorted
    array "nums" which on average tends to be much less than 10^9 which is the
    upper bound in the contraints sections for nums[i] values.

*/

/* Time  Beats: 87.78% */
/* Space Beats: 31.40% */

/*
    Time  Complexity: O(N * logM)

    N is the length of "nums", whereas M is the upper bound of nums[i].

    As stated in the constraints:
        1 <= nums.length <= 10^5
        0 <= nums[i] <= 10^9

    One way to solve this problem is to do it in O(N^2) by doing nested loops.
    However, which one is more efficient?

        O(N^2) or (N * logM)?

        N = 100000       // sqrt(N) = 316
        M = 1000000000   // log(M)  = 9

    In other words - "log" grows MUCH MUCH slower than "sqrt" function.
    Therefore, in this problem(at least for these values), we can say with
    confidence that O(N * logM) is faster than O(N^2)

*/
/*
    Space Complexity: O(1)

    Depending on the sort
*/
class Solution_Efficient_Implementation {
public:
    int minimizeMax(std::vector<int>& nums, int p)
    {
        std::sort(nums.begin(), nums.end());

        int n = nums.size();
        int result = nums[n-1] - nums[0];

        int left  = 0;
        int right = result;

        while(left <= right)
        {
            int mid = (left + right) / 2;
            int count = 0;
            int k = 0;

            while(k < n-1)
            {
                if(nums[k+1] - nums[k] <= mid)
                {
                    count++;
                    k += 2;
                }
                else
                    k++;
            }

            if(count >= p)
            {
                result = mid;
                right = mid - 1;
            }
            else
                left  = mid + 1;
        }

        return result;
    }
};
