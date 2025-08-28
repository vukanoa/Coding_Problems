/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    2680) Maximum OR
    ===========================

    ============
    Description:
    ============

    You are given a 0-indexed integer array nums of length n and an integer k.
    In an operation, you can choose an element and multiply it by 2.

    Return the maximum possible value of nums[0] | nums[1] | ... | nums[n - 1]
    that can be obtained after applying the operation on nums at most k times.

    Note that a | b denotes the bitwise or between two integers a and b.

    ========================================================
    FUNCTION: long long maximumOr(vector<int>& nums, int k);
    ========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [12,9], k = 1
    Output: 30
    Explanation: If we apply the operation to index 1, our new array nums will
                 be equal to [12,18]. Thus, we return the bitwise or of 12 and
                 18, which is 30.

    --- Example 2 ---
    Input: nums = [8,1,2], k = 2
    Output: 35
    Explanation: If we apply the operation twice on index 0, we yield a new
                 array of [32,1,2]. Thus, we return 32|1|2 = 35.

    *** Constraints ***
    1 <= nums.length <= 10^5
    1 <= nums[i] <= 10^9
    1 <= k <= 15

*/

#include <vector>
using namespace std;


/*
    ------------
    --- IDEA ---
    ------------

    Multiplying by 2 means "left shift by 1".

    We can left-shift at most k times. We can do it in any order we want.
    We can shift by one each number or we can use all of our k-shifts on a
    single number.



    Now this may not sound intuitive at first, but bear with me.

    It's ALWAYS the best to use all k-shifts on a single number, than to use
    any other combiations of shifts on different numbers.


    Why? (This is unituitive at first)


    Let's consider this array:

         5 - 000000000101
         6 - 000000000110
         9 - 000000001001
        20 - 000000010100
        23 - 000000010111

    If we decide to use all of our k-shifts for number: 23, we'd end up like
    this:

         5 - 000000000101
         6 - 000000000110
         9 - 000000001001
       640 - 001010000100
        23 - 000000010111


    The Left-Most-Significant-Bit is: 2^9 <==> 512

    Bitwise-OR of array will be at least 2^9. It can be more depending on less
    significant bits.


    Now let's say we don't give all k moves to a single number.
    Since, we are not giving all k moves to single number, we will never be
    able to generate 29 set bit in any number. And even if somehow we generate
    all lower set bits such as: 2^8, 2^7, 2^6, ... by distributing k moves to
    different numbers, answer will still be less than 2^9.

        2^8 + 2^7 + 2^6 + ... + 2^0 <===> 2^9 − 1 < 2^9


    Therefore, giving all k moves to single element (that too having largest
    Leftmost-Significant-Bit) is the most optimal.


    Since it's costly to try and go through all (n-1) numbers in N for each
    number with the maximum Leftmost-Sifnicant-Bit, we can take use of:
    Preffix and Suffix.

    For each number that has the Leftmost-Signicant-Bit among all the elements
    in array, we shift that number k times and the use bitwise-OR of its
    preceding(prefix) and succeeding(suffix) elements.

    Among all of them, we return the maximum value we've obtained.

*/

/* Time  Beats: 53.49% */
/* Space Beats: 67.83% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    long long maximumOr(vector<int>& nums, int k)
    {
        const int N = nums.size();
        long long result = 0;

        vector<int> prefix(N + 1);
        vector<int> suffix(N + 1);

        for (int i = 1; i < N; i++)
        {
            prefix[i]         = prefix[i - 1] | nums[i - 1];
            suffix[N - i - 1] = suffix[N - i] | nums[N - i];
        }

        for (int i = 0; i < N; i++)
            result = max(result, prefix[i] | (static_cast<long long>(nums[i]) << k) | suffix[i]);

        return result;
    }
};
