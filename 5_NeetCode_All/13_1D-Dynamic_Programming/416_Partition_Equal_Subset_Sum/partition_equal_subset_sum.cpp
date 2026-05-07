/*
    ==============
    === MEDIUM ===
    ==============

    ===============================
    416) Partition Equal Subset Sum
    ===============================

    ============
    Description:
    ============

    Given an integer array "nums", return true if you can partition the array
    into two subsets such that the sum of the elements in both subsets is equal
    or false otherwise.

    ===============================================
    FUNCTION: bool canPartition(vector<int>& nums);
    ===============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  nums = [1, 5, 11, 5]
    Output: true
    Explanation: The array can be partitioned as [1, 5, 5] and [11].

    --- Example 2 ---
    Input:  nums = [1, 2, 3, 5]
    Output: false
    Explanation: The array cannot be partitioned into equal sum subsets.

    *** Constraints ***
    1 <= nums.length <= 200
    1 <= nums[i] <= 100

*/

#include <cstring>
#include <unordered_set>
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    By-the-book Memoization Problem.

    Constraits like these:

        1 <= N <= 200
        1 <= nums[i] <= 100

    scream:"Memoization!". As 2^N would be to inefficient, whereas the "total
    number of states" would be the Time Complexity of O(200 * 20000).

    How did I get these numbers?
    We'll have "memo" that will be declared like this:

        int memo[201][20001];

    But why these numbers specifically?

    201 is obvious. It's the total number of elements of "nums". That is always
    a part of "memo" in any Memoization Problem, we need to represent each
    index.

    However, 20001 seems to come from nowhere. Actually it's just the worst
    case scenario pertaining to our "sum" part.

    We need to be able to represent ANY sum, therefore the biggest possible sum
    is to sum all of the elements (all 200 of them) with the biggest value at
    each index.

    Imagine that each element is 100(which is the maximum according to our
    constraints).

    Now imagine that N=200, i.e. number of elements in total is 200.

    Therefore in the worst case, at the last element we will have a state that
    represents the sum of ALL the elements.

    If we have 200 elements and each one is 100, then the total sum is 20000.
    And that needs to be able to be represented, therefore 20001(because it's
    0-indexed).


    First, let's explore the Brute Force solution.
    We iterate through an entire array and we always have 2 choices:
        1) Include nums[i] in our sum, or
        2) Do not include nums[i] in our sum

    Consider the First given example:
        [1, 5, 11, 5]

    I) 1
        a) Indeed Include it -> sum = 1
        b) Do not include it -> sum = 0

    II) 5
        a) Indeed Include it -> sum = 6 or sum = 5
        b) Do not include it -> sum = 1 or sum = 1

    etc.

    Below is the tree of all possible cases.

    Left  means: Do INDEED include current nums[i]
    Right means: Do NOT    include current nums[i]

                                               0
                       1                                               0
           6                       1                       5                       0
     17          6           12          1           16          5           11          0
  22    17    11    6     17    12    6     1     21    16    10    5     16    11    5     0


    Once we find out target(11 in this case) we return true.
    Otherwise if we got to the end and did not find out target---return false.

    What is the height of this "decision tree"?
    It's N.

    So out Time complexity is 2^N

    So let's see how we can optimize this, by saving the COMPUTED work. This is
    done using "MEMOIZATION" technique.

    Let's see if there is any repetead work that we can cut down on.
    Initially index i is at position 0 at the beginning.

    [1, 5, 11, 5]
     i

    We have 2 choices:
        1) We could've chosen  1
            If we have chosen it - We have a new subproblem:

            Target = 10
            idx    = 2 // Since we had already processed 1 at position 0 and
                       // now we are only trying elements from the subbaray
                       // next to the current element(1 in this case)


        2) We could've skipped 1
            If we have not chosen it - We have a similar problem:
            Target = 11
            Idx    = 2 // Since we have already considered this element and
                       // have decided not to include it


        We would do the same thing in respective subproblems until we either
        find a soultion or hit the last element.


    So the dimensions of our "memo" are these two elements:
        1) idx    = 1  // Some index of nums
        2) target = 11 // Target we're trying to sum up to, starting at idx


    So the UNIQUE STATE is: memo[curr_idx][curr_target]

*/

/* Time  Beats: 15.45% */
/* Space Beats: 46.27% */

/* Time  Complexity: O(N * sum / 2) ---> O(N * sum) */
/* Space Complexity: O(N * sum / 2) ---> O(N * sum) */
class Solution_Memoization {
private:
    int memo[201][20001]; // 200 * 100 = 20000
public:
    bool canPartition(vector<int>& nums)
    {
        const int N = nums.size();

        /* Memset */
        memset(memo, -1, sizeof(memo));

        int total_sum = accumulate(nums.begin(), nums.end(), 0);
        if (total_sum & 1)
            return false;

        return memoization(nums, 0, total_sum / 2);
    }

private:
    bool memoization(vector<int>& nums, int idx, int target)
    {
        if (target == 0)
            return true;

        const int N = nums.size();
        if (idx >= N || target < 0)
            return false;

        if (memo[idx][target] != -1)
            return memo[idx][target];

        bool take = memoization(nums, idx+1, target - nums[idx]);
        bool skip = memoization(nums, idx+1, target            );

        return memo[idx][target] = take || skip;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same as above, implemented differently. It depends on how you think about
    the problem.

    It's always beneficial to see multiple implementations, especially if
    you're not "well versed" with Memoization.

*/

/* Time  Beats:  8.07% */
/* Space Beats: 45.69% */

/* Time  Complexity: O(N * sum / 2) ---> O(N * sum) */
/* Space Complexity: O(N * sum / 2) ---> O(N * sum) */
class Solution_Memoization_2 {
private:
    int memo[201][20001];

public:
    bool canPartition(vector<int>& nums)
    {
        const int N = nums.size();

        /* Memset */
        memset(memo, 0xff, sizeof(memo));

        int total_sum = accumulate(nums.begin(), nums.end(), 0);
        if (total_sum & 1) // total_sum is ODD
            return false;

        return solve(0, total_sum / 2, nums);
    }

private:
    bool solve(int idx, int target, vector<int>& nums)
    {
        if (target == 0)
            return true;

        const int N = nums.size();
        if (idx >= N)
            return false;

        if (memo[idx][target] != -1)
            return memo[idx][target];

        bool skip = solve(idx + 1, target, nums);
        bool take = false;

        /* Potential take */
        if (nums[idx] <= target)
            take = solve(idx + 1, target - nums[idx], nums);

        return memo[idx][target] = skip | take;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 10.31% */
/* Space Beats: 73.30% */

/* Time  Complexity: O(N * sum(nums)) */
/* Space Complexity: O(N * sum(nums)) */
class Solution_Bottom_Up__Tabulation_2D {
public:
    bool canPartition(vector<int>& nums)
    {
        const int N = nums.size();
        int total_sum = accumulate(nums.begin(), nums.end(), 0);

        if (total_sum & 1)
            return false;

        int target = total_sum / 2;
        vector<vector<bool>> dp(N, vector<bool>(target + 1, false));

        // Populate the first column
        dp[0][0] = true;

        // Populate the first row
        if (nums[0] <= target)
            dp[0][nums[0]] = true;

        for (int i = 1; i < N; i++)
        {
            
            // j <==> curr_target
            for (int j = 0; j <= target; j++)
            {
                dp[i][j] = dp[i - 1][j];

                if (j >= nums[i])
                    dp[i][j] = dp[i][j] || dp[i - 1][j - nums[i]];
            }
        }

        return dp[N - 1][target];
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same IDEA as above Solution, but instead of using a 2D vector, we can
    actually use only a 1D, thus optimizing the Space Complexity.

*/

/* Time  Beats: 59.85% */
/* Space Beats: 99.50% */

/* Time  Complexity: O(n * sum(nums)) */
/* Space Complexity: O(n * sum(nums)) */
class Solution_Bottom_Up__Tabulation_1D__Space_Optimized {
public:
    bool canPartition(vector<int>& nums)
    {
        const int N = nums.size();

        int total_sum = accumulate(nums.begin(), nums.end(), 0);

        if (total_sum & 1)
            return false;

        /* Sort in DESCENDING order */
        sort(nums.begin(), nums.end(), greater<int>());

        int target = total_sum / 2;
        vector<bool> dp(target + 1, false);
        dp[0] = true;

        for (int i = 0; i < N; i++)
        {

            // j <==> curr_target
            for (int j = target; j >= nums[i]; j--)
            {
                dp[j] = dp[j] || dp[j - nums[i]];
            }
        }

        return dp[target];
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    The very first thing we must notice is that for subset sums to be equal
    they have to be each (sum_of_the_entire_array  /  2).

    That also means that if the total sum of the array is an ODD number then
    that means it is IMPOSSIBLE to find 2 EQUAL subset sums.

    So our target always becomes:
        target = total_sum / 2

    So we start from the back and construct the Bottom-Up solution using
    uset_sums.

    I) [1, 5, 11, 5]
                  i

        We either take it or we don't so:
            uset_sums = {0, 5}


    II) [1, 5, 11, 5]
                i

        We either take it or we don't so:
            uset_sums = {0, 5, 11, 16}

    etc.

    The important thing is that we construct our uset_sums as a set.
    That way we don't store duplicates.

    If at any point we find out target---return true

    All the unique sums of this example would be:
    (if we were not to stop immediately once we encountered "target" value)

        uset_sums {0, 5, 11, 16, 10, 21, 1, 6, 12, 17, 22}

*/

/* Time  Beats:  5.00% */
/* Space Beats:  5.23% */

/* Time  Complexity: O(N * sum(nums)) */
/* Space Complexity: O(N * sum(nums)) */
class Solution_Hash_Set {
public:
    bool canPartition(vector<int>& nums)
    {
        const int N = nums.size();

        int total_sum = accumulate(nums.begin(), nums.end(), 0);

        if (total_sum & 1)
            return false;

        unordered_set<int> uset_sums;
        uset_sums.insert(0);

        for (int i = N-1; i >= 0; i--)
        {
            unordered_set<int> new_uset_sums;

            for (const int& sum : uset_sums)
            {
                new_uset_sums.insert(sum + nums[i]);
                new_uset_sums.insert(sum);
            }

            uset_sums = new_uset_sums;
        }

        return uset_sums.count(total_sum / 2);
    }
};
