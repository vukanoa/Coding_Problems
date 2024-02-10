#include <iostream>
#include <vector>
#include <algorithm>

/*
    ==============
    === MEDIUM ===
    ==============

    =================================================================
    1498) Number of Subsequences That Satisfy the Given Sum Condition
    =================================================================

    ============
    Description:
    ============

    You are given an array of integers nums and an integer target.

    Return the number of non-empty subsequences of nums such that the sum of
    the minimum and maximum element on it is less or equal to target. Since the
    answer may be too large, return it modulo 109 + 7.

    =======================================================
    FUNCTION: int numSubseq(vector<int>& nums, int target);
    =======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [3,5,6,7], target = 9
    Output: 4
    Explanation: There are 4 subsequences that satisfy the condition.
    [3] -> Min value + max value <= target (3 + 3 <= 9)
    [3,5] -> (3 + 5 <= 9)
    [3,5,6] -> (3 + 6 <= 9)
    [3,6] -> (3 + 6 <= 9)


    --- Example 2 ---
    Input: nums = [3,3,6,8], target = 10
    Output: 6
    Explanation: There are 6 subsequences that satisfy the condition. (nums can
    have repeated numbers).
    [3] , [3] , [3,3], [3,6] , [3,6] , [3,3,6]


    --- Example 3 ---
    Input: nums = [2,3,3,4,6,7], target = 12
    Output: 61
    Explanation: There are 63 non-empty subsequences, two of them do not
    satisfy the condition ([6,7], [7]).
    Number of valid subsequences (63 - 2 = 61).


    *** Constraints ***
    1 <= nums.length <= 10^5
    1 <= nums[i] <= 10^6
    1 <= target <= 10^6

*/

/*
    ------------
    --- IDEA ---
    ------------

    This one does NOT work for C++ because of the type-boundary. This would
    work for something like Python.

    However the Explanation for this Solution is by far the best. Once you
    understand this one, you'll easily understand the other 2 Solutions down
    below(besides this one).

    First, the subsequences must be NON-Empty!


    Let's consider this example:

        nums = [3, 3, 6, 8], target = 10

    The most Brute Force way to do this would be Backtracking. Check every
    single combination.

    In the first case we want to know if we include that number or not:


        nums = [3, 3, 6, 8], target = 10


                                  []
                        _________/  \__________
                       /                       \
                      3                         []
                 ____/ \____                ____/  \____
                /           \              /            \
             [3,3]          [3]          [3]             []
            /    \         /   \        /   \           /  \
        [3,3,6]  [3,3]  [3,6]  [3]   [3,6]  [3]       [6]   []
        ...
        ...
        ...

    At the end you would count every leaf node that has the sum of the lowest
    and the greatest in that array to be less than or equal to the target.

    The Time Complexity of such approach would be O(2^n).

    So, can we do better? Or is there some information that we can extract to
    be able to be "greedy" in some type of way?

    Hint hint - There is.

    ---------------------------------------------------------------------------
    The very first thing we should ask ourselves is - Is Sorting going to help
    us?
    We must ask that because we see that the Brute Force's Time Complexity is
    huge, therefore we notice that Sorting won't worsen the Time Complexity, it
    can only help us, possibly, solve it more efficiently.

    The second thing we have to ask ourselves is - Are we allowed to sort?

    Since we're not asked to have "increasing" or "decreasing" subsequence or
    something like that, we can notice that the order of elements would NOT
    change the end result.

    Since we're told to count how many subsequences where sum of the minimum
    and maximum elements are less than or equal to the "target", we can notice
    that the order is completely irrelevant.

        Subsequence:
            [5, 3, 12, 9] // min=3 + max=12

        is equivalent to subsequence:
            [3, 5, 9, 12] // min=3 + max=12

    Now that this is out of the way, we can talk about the optimal Solution.
    ---------------------------------------------------------------------------


    In this problem, the "target" is always going to be positive and the values
    in our Input array are also always going to be positive.

    So the limiting factor is really - How big is the maximum?

    The way we can count the subsequences is to say:"Okay, for each minimum how
    many other values can we add to it so that the sum of that number and the
    greatest one we add is less than 'target'?"

                0  1  2  3
        nums = [3, 3, 6, 8], target = 10
                ^
                |
             current minimum we're considering

        If we include another 3(the one at index 1), the sum is 6. That's good.
        If we include 6(at index 2), the sum is 9. That's good as well.
        If we include 8(at index 3), the sum is 11 which is NOT good. That
        means we cannot include the 8.

        We can only include these three numbers:
                0  1  2  3
        nums = [3, 3, 6, 8], target = 10
                ^^^^^^^


        Or the better way of thinking about it(and how we're actually going to
        compute it) is:

            "If we are definitely including the 3(at index 0) as the minimum
             value in our subsequence, how many other values can we add?"
    _________________________
    |                       |
    |                       v
    |   In this case, it's two more values. Element 3(index 1) and 6(index 2).
    |   So, how many subsequences, that definitely contain 3(at index 0) can we
    |   get?
    |
    |_____________________________________
                         |               |
                         |               |
        The answer is 2^(2), where the exponent is the number of values that
        when summed with the current minimum in our subsequence(3 at index 0 in
        this case) give a value that is less than or equal to "target".

        Let me emphasize - It is NOT 2^(3), even though we are considering a
        total of 3 elements.

        It's 2^(2) because the first one, the current minimum in our
        subsequence, is FIXED.

        If the first one, the element we're currently on, summed by itself is
        less than or equal to "target", then we are considering it as the
        minimum element in our subsequence and therefore it ISN'T optional,
        thus we don't include it in our exponent.

        ---
        Why are we summing with itself? Because once we're on some element,
        it's as if we only have that element in our subsequence, therefore it
        serves as both minimum and maximum.

        That is the purpose of sorting as well.

        If 6, in our example, can't be in a subsequency by itself, then 8
        cannot either since it's bigger than 6
        ---

        However, it the current element, that we're trying to include as the
        minimum for our subsequence, ISN'T less than or equal to the "target"
        when summed with itself, then just stop. (Because next elements are
        surely not going to be minimums in their subseuqnces because the
        elements are sorted)

    Now, we'll have 2^(2) be added to our result and then we're going to
    consider some other value as the minimum in subsequence.

                0  1  2  3
        nums = [3, 3, 6, 8], target = 10
                   ^
                   |
                current minimum we're considering

        When summed with itself, 3 + 3, is it less than or equal to 10? Yes.
        Okay, then let's see how many subsequent elements can come into play.

        3 + 6 = 9 <= 10. That's good.
        3 + 8 = 11 > 10. That's NOT good. Stop.

        So it's only one additional value(apart from the currently fixed
        minimum element)

        Therefore we'll add 2^(1) to our result.

    We'll continue this until the current element we're considering, when
    summed with itself, ISN'T less than or equals to the "target".


    Once again it is IMPORTANT to emphasize that sorting WILL NOT mess the
    subsequences for THIS PROBLEM(for others ordering in subsequences is
    usually important) and only because of that are we allowed to sort!

*/

class Solution_Does_NOT_work_CPP {
public:
    int numSubseq(std::vector<int>& nums, int target)
    {
        unsigned long long result = 0;
        int mod_value = std::pow(10, 9) + 7;

        std::sort(nums.begin(), nums.end());

        int right = nums.size() - 1;
        for (int left = 0; left < nums.size(); left++)
        {
            while (left <= right && (nums[left] + nums[right]) > target)
                right--;

            if (left <= right)
            {
                result += (1 << (right - left));
                result %= mod_value;
            }
        }

        return static_cast<int>(result);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    The idea is essentially the same as above, however since we cannot have
    such big numbers, what we can do instead is:
        1) Sort (This is done anyway)
        2) For every current element(nums[i] in this code) subtract it from
           the "target" and try to find the std::upper_bound.

           What will that do?

           Think of std::upper_bound as:"If you had an array in sorted order,
           return the first element that is greater than 'val' or std::end
           iterator if there is no greater element than 'val' in the entire
           array"

           If the element that is greater than 'val' exists, the iterator will
           be returned to that element.

           We'll call the iterator "bigger_val".

           If we want to get the index of that element we have to options:
               1) idx = std::distance(nums.begin(), bigger_val);
               2) idx = bigger_val - nums.begin();


    As I've said the IDEA is essentially the same as above, though it is
    implemented differently because of the limits of C++'s type-boundary.

    Therefore, we'll consider each nums[i] as the minimum for the current
    subsequence and we'll try to find:

        val = target - nums[i]

    Since:
        val + nums[i] should be <= target

    We are seeking for val, which by simple algebra, is going to be:
        val should be <= target - nums[i]

    However, since that SHOULD BE the case, we want to find a first element
    that is BIGGER than val(that is NOT going to fulfill the requirement).

    Once we have an index of the element that summed with the current
    considered minimum does NOT fulfill the requirement, we can calculate the
    distance between those two elements and add 2^(that distance) to our
    result.

    Since we want first one that is BIGGER than val, we'll use:
        std::upper_bound

*/

/* Time  Beats: 24.01% */
/* Space Beats: 39.74% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n) */
class Solution_Inefficient {
public:
    int numSubseq(std::vector<int>& nums, int target)
    {
        std::sort(nums.begin(), nums.end());
        int result = 0;
        int mod_value = 1e9 + 7;

        for(int i = 0; i < nums.size(); ++i)
        {
            int val = target - nums[i];

            // First Greater than "val"
            auto bigger_val = std::upper_bound(nums.begin(), nums.end(), val);

            int idx = std::distance(nums.begin(), bigger_val);
            idx--;

            if(idx >= i)
                result = (result + power(2, idx-i, mod_value)) % mod_value;
        }

        return result % mod_value;
    }

private:
    int power(unsigned long long x, unsigned long long y, unsigned long long p)
    {
        int res = 1;
        x = x % p;

        if (x == 0)
            return 0;

        while (y > 0)
        {
            if (y & 1)
                res = (res * x) % p;

            y = y >> 1;
            x = (x * x) % p;
        }

        return res;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This one is the same as the first Solutions in this file, however it
    bypasses the C++'s type-boundary problem by precalculating the powers we're
    going to be using.

*/

/* Time  Beats: 96.76% */
/* Space Beats: 54.46% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n) */
class Solution_Efficient {
public:
    int numSubseq(std::vector<int>& nums, int target)
    {
        int n = nums.size();
        int MOD = 1e9 + 7;

        /* Sort */
        std::sort(nums.begin(), nums.end());

        int result = 0;

        int left  = 0;
        int right = n-1;

        std::vector<int> pow(n, 1);
        for(int i = 1; i < n; i++)
            pow[i] = (pow[i-1] * 2) % MOD;

        while(left <= right)
        {
            if(nums[left] + nums[right] <= target)
                result = (result + pow[right - left++]) % MOD;
            else
                right--;
        }

        return result;
    }
};
