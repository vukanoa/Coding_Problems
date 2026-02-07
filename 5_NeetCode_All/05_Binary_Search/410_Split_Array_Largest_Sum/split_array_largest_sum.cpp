/*
    ============
    === HARD ===
    ============

    ============================
    410) Split Array Largest Sum
    ============================

    ============
    Description:
    ============

    Given an integer array nums and an integer k, split nums into k non-empty
    subarrays such that the largest sum of any subarray is minimized.

    Return the minimized largest sum of the split.

    A subarray is a contiguous part of the array.

    ===================================================
    FUNCTION: int splitArray(vector<int>& nums, int k);
    ===================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [7,2,5,10,8], k = 2
    Output: 18
    Explanation: There are four ways to split nums into two subarrays.
    The best way is to split it into [7,2,5] and [10,8], where the largest sum
    among the two subarrays is only 18.


    --- Example 2 ---
    Input: nums = [1,2,3,4,5], k = 2
    Output: 9
    Explanation: There are four ways to split nums into two subarrays.
    The best way is to split it into [1,2,3] and [4,5], where the largest sum
    among the two subarrays is only 9.


    *** Constraints ***
    1 <= nums.length <= 1000
    0 <= nums[i] <= 10^6
    1 <= k <= min(50, nums.length)

*/

#include <algorithm>
#include <climits>
#include <cstring>
#include <numeric>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Since we're asked to minimize the LARGEST sum, let's ask ourselves:

        What is the LARGEST SUM possible in this entire vector for ANY k?

    Of course, it's the total sum of the entire vector. It CANNOT possibly be
    any larger.

    Especially since 'k' CAN be 1. In that case, the answer it the sum of the
    entire vector and that is the only answer.

    Okay, that is the LARGEST possible sum. What about the SMALLEST possible
    sum?

    Consider this example:

        N = nums.size() = 6
        nums = [7, 5, 3, 9, 2, 6], k = 6
                0  1  2  3  4  5

    Since k == N == 6, meaning each subarray is going to have EXACTLY ONE
    element--what do you think is the SMALLEST POSSIBLE sum then?

    Of course it's the LARGEST element within an entire vector.
    Think about it.

    We can have groups of: 1, 2, 3, ... N elements per subarray.
    But the SMALLEST SIZE group is always 1. It's just the element itself.

    Therefore, each element can, in theory, be on its own, thus that is our
    SMALLEST possible sum that could exist even in theory.

    Okay, now we know what is the SMALLEST possible sum and what is the LARGEST
    possible sum.

        Smallest <==> Maximum_element_in_entire_vector
        Largest  <==> Total_sum_of_the_entire_vector


    That seems as a.... RANGE.

    Since that is a RANGE, we are ABSOLUTELY CERTAIN that the final answer is
    going to be from that RANGE, i.e.:

        [Maximum_element_in_entire_vector, Total_sum_of_the_entire_vector]
                    ^                                     ^
                    |                                     |
                    |                                     |
              SMALLEST possible sum                 LARGEST possible sum

    inclusivelly.


    So a Brute-Force Solution would be to simply start with the smallest one
    and then try to see if you can group them in such a way as to have that
    sum as its smallest.

    The first successful attempt is the answer.

    But how are we going to do that? How can we know if max_sum=<some_number>
    can be indeed the largest sum within 'k' groups?

    One way we'll certainly know is the simply try to be greedy. We try to
    combine consecutve elements until the consecutive_sum is <= max_sum.

    Every time consecutive_sum EXCEEDS "max_sum", we know we need to close the
    current group, increment needed_groups and reset our "consecutive_sum".

    At the end we only need to check if the "needed_groups" is <= 'k'.

    If that's the case, then that means we've made it. It means that we grouped
    elements in 'k' OR EVEN LESS GROUPS THAN 'k' and have a maximum sum of
    "max_sum".

    If we're able to to it with k OR LESS groups, then we're CERTAINLY able to
    do it in 'k' groups.

    This sounds confusing.

    Consider this:

        nums = [7, 3, 1, 6, 2], k = 3
                0  1  2  3  4 
        
    Let's say out max_sum = 13.
    How many groups do we need?

        nums = [7, 3, 1, 6, 2], k = 3
                0  1  2  3  4 
                ~~~~~~~  ~~~~
                  ^        ^
                  |        |
                  |        |
                One       Two

    We needed TWO groups in order to have the largest sum NOT exceed max_sum.
    Therefore, if we CAN do it in TWO groups, we CERTAINLY can do it in k=3
    groups.

    We'll just make one group SMALLER by adding another group. Therefore, if
    we can do it with even less than 'k' groups, then we CERTAINLY can do it
    with 'k' groups, therefore max_sum = 13 is one possible answer.

    But can we do better?
    What about max_sum = 12?


    But... Why would we try each possible answer individually, linearly?
    This would make it a total of: O(N * M), which usually isn't acceptable.
        
    Is there ANYTHING we can optimize?
    Of course there is!

    Instead of trying each max_sum linearly, until we find an answer, why don't
    we do a Binary Search on a RANGE we know that answer is from?

    For a RANGE:

        [Maximum_element_in_entire_vector, Total_sum_of_the_entire_vector]
                    ^                                     ^
                    |                                     |
                    |                                     |
              SMALLEST possible sum                 LARGEST possible sum
        
    Instead of doing:
        1. max_sum = 0 + Maximum_element_in_entire_vector
        2. max_sum = 1 + Maximum_element_in_entire_vector
        3. max_sum = 2 + Maximum_element_in_entire_vector
        ...

    Why won't we do a BINARY SEARCH on this range?
    That way we'll optimize this portion from O(M) to O(logM) where 'M' is the
    difference bettwee the largest element and the total sum of entire vector.


    Simply make:

        low  = Maximum_element_in_entire_vector
        high = Total_sum_of_the_entire_vector

    We're going to do "Left-leaning" mid, a lower_bound kind of Binary Search.
    That means once the while-loop breaks, we're left with both "low" and 
    high" pointing at the same value, i.e. the final result we got to return.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  57.82% */

/* Time  Complexity: O(N * logM) */
/* Space Complexity: O(1)        */
class Solution {
public:
    int splitArray(vector<int>& nums, int k)
    {
        const int N = nums.size();

        int total_sum = accumulate(nums.begin(), nums.end(), 0); // O(N)
        int max_elem  = *max_element(nums.begin(), nums.end());  // O(N)

        // O(N * logM) (entire block)
        int low  = max_elem;
        int high = total_sum;
        while (low < high) // O(logM)
        {
            int mid = low + (high - low) / 2; // mid <==> max_sum

            int needed_groups = needed_groups_with_max_sum(mid, nums); // O(N)

            if (needed_groups > k)
                low  = mid + 1;
            else
                high = mid;
        }

        return low; // Or "high" it does NOT matter
    }

private:
    int needed_groups_with_max_sum(int& max_sum, vector<int>& nums)
    {
        const int N = nums.size();

        int needed_groups = 0;
        int consecutive_sum = 0;
        for (int i = 0; i < N; i++)
        {
            if (consecutive_sum + nums[i] > max_sum)
            {
                needed_groups++;
                consecutive_sum = 0; // Reset
            }

            consecutive_sum += nums[i];
        }
        needed_groups++; // Count the last one as well

        return needed_groups;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This one is WORSE, both asymptotically and in practice, than the one above.

    That begs the question--Why have I, then, included this one as well?

    Because it is REALLY beneficial to notice one thing: When you have a
    prefix-sum of non-negative elements, that array is ALWAYS SORTED in
    NON-DECREASING order.

    Since it's sorted in NON-DECREASING order(i.e. ASCENDING with duplicates)
    that means it's susceptible to Binary Searched.

    For this specific problem, this is NOT optimal, however it is beneficial
    to have this toolkit in your arsenal when you need it. Just know that you
    can do a Binary Search on a "Prefix Sum" as that can improve Time
    Complexity in some problems.

    Also, the Binary Search on "Prefix Sum" is implemented in a DIFFERENT way
    that the "outer" Binary Search that searched on the answer-space.

    The answer-space Binary Search is a classic "lower_bound Left-leaning"
    Binary Search, whereas the other one is "Right-leaning".

    Also, the second one has a different kind of logic because we're dealing
    with prefix sums.

    It is really beneficial to see and truly understand both Solutions.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  10.04% */

/* Time  Complexity: O(k * logN * logM) <==> O(N * logN * M) */
/* Space Complexity: O(N)                                    */
class Solution_Additional_Binary_Search_on_Prefix_Sum {
public:
    int splitArray(vector<int>& nums, int k)
    {
        const int N = nums.size();

        /* Prefix Sum */
        vector<int> prefix(N);
        prefix[0] = nums[0];

        for (int i = 1; i < N; ++i)
            prefix[i] = prefix[i-1] + nums[i];

        int low  = *max_element(nums.begin(), nums.end());
        int high = accumulate(nums.begin(), nums.end(), 0);

        // O(k * logN * logM) <==> O(N * logN * logM) (enire block)
        while (low < high) // O(logM)
        {
            int mid = low + (high - low) / 2;

            // O(k * logN) <==> O(N * logN)
            int needed_groups = needed_groups_with_max_sum(mid, nums, prefix);

            if (needed_groups > k)
                low  = mid + 1; // "mid" CERTAINLY is NOT a valid answer
            else
                high = mid;     // "mid" still CAN be a valid answer
        }

        return low; // Or "high" it does NOT matter
    }

private:
    int needed_groups_with_max_sum(int max_sum, vector<int>& nums, vector<int>& prefix)
    {
        const int N = nums.size();

        int needed_groups = 0;

        // O(k * logN), i.e. O(N * logN) (enire block)
        int start_idx_of_new_subarray = 0;
        while (start_idx_of_new_subarray < N) // O(k), i.e. O(N) in the worst
        {
            int low  = start_idx_of_new_subarray;
            int high = N-1;

            // O(logN) (entire block)
            while (low < high)
            {
                int mid = low + (high - low + 1) / 2; // Right-leaning "mid"

                int consecutive_sum = prefix[mid] - (start_idx_of_new_subarray == 0 ? 0 : prefix[start_idx_of_new_subarray - 1]);

                if (consecutive_sum > max_sum)
                    high = mid - 1; // "mid" CERTAINLY is NOT a valid answer
                else
                    low = mid;      // "mid" still CAN be a valid answer
            }
            needed_groups++;

            start_idx_of_new_subarray = high + 1;
        }

        return needed_groups;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This one is BY FAR the worst Solution of all three in this file, however
    this is one common template for doing "Memoization" Problems.

    It's good to get familiar with "Memoization" as soon as possible, so even
    if it's not the most optimal for some problems, I like to include it just
    for the same of practice.

*/

/* Time  Beats: 4.52% */
/* Space Beats: 6.81% */

/* Time  Complexity: O(k * N^2) */
/* Space Complexity: O(k * N)   */
class Solution_Memoization {
private:
    static constexpr int MAX_N = 1001;
    int memo[MAX_N][MAX_N];

public:
    int splitArray(vector<int>& nums, int k)
    {
        const int N = nums.size();

        /* Memset */
        memset(memo, 0xff, sizeof(memo)); // 0xff <==> -1 in "2's completent"


        return solve(0, nums, k);
    }

private:
    int solve(int idx, vector<int>& nums, int remaining_k)
    {
        const int N = nums.size();

        if (idx == N)
            return remaining_k == 0 ? 0 : INT_MAX;

        if (remaining_k == 0)
            return INT_MAX;

        if (memo[idx][remaining_k] != -1)
            return memo[idx][remaining_k];



        int result = INT_MAX; // Smallest worst_group_sum from here
        int left_group_sum = 0;

        for (int split_end = idx; split_end <= N - remaining_k; split_end++)
        {
            // Take current element as the end of the current subarray
            left_group_sum += nums[split_end];

            // Smallest max_sum from any subarray until the end
            int right_best = solve(split_end + 1, nums, remaining_k - 1);

            int worst_group_sum = max(left_group_sum, right_best);

            result = min(result, worst_group_sum);
        }

        return memo[idx][remaining_k] = result;
    }
};
