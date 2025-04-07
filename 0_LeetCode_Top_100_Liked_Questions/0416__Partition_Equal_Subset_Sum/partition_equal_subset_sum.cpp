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
#include <vector>
#include <set>
#include <numeric>
#include <algorithm>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    The very first thing we must notice is that for subset sums to be equal
    they have to be each sum of the entire array divided by 2.

    That also means that if the total sum of the array is an odd number then
    that means it is impossible to find a 2 equal subset sums.

    So out target always becomes:
        target = sum(array) / 2

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
    Left means: Include current nums[i]
    Right means: Do not include current nums[i]

                                               0
                       1                                               0
           6                       1                       5                       0
     17          6           12          1           16          5           11          0
  22    17    11    6     17    12    6     1     21    16    10    5     16    11    5     0

    Once we find out target(11 in this case) we return true.
    Otherwise if we got to the end and did not find out target - return false.

    What is the height of this "decision tree"?
    It's n.

    So out Time complexity is 2^n

    So let's see how we can optimize this.
    Let's see if there is any repetead work that we can cut down on.
    Initially index i is at position 0 at the beginning.

    [1, 5, 11, 5]
     i

    We have 2 choices:
        1) We could've chosen  1
            If we have chosen it - We have a new subproblem:
                Target: 10
                i = 2 // Since we had already processed 1 at position 0
                      // and now we are only trying elements from the subbaray
                      // next to the current element(1 in this case)

        2) We could've skipped 1
            If we have not chosen it - We have a similar problem:
                Target is the same: 11
                i = 2 // Since we have already considered this element and have
                      // decided not to include it

        We would do the same thing in respective subproblems until we either
        find a soultion or hit the last element.

    So the dimensions of our "cache" are these two elements:
        1) target = 11 // Sum of the entire array(subarray) divided by 2
        2) i = 1 // This can be any value in the input Array so => n

    So the Big O is going to be:
        O(n * (sum(nums) / 2))
    and since constants usually don't matter in time complexity, then:

        O(n * sum(nums))

    This is technically better than 2^n because they give us a pretty good
    limitation:
        1 <= nums.length <= 200

    If it was:
        1 <= nums.length <= 1000000 // million

    Then this wouldn't be so efficient

    So if we did a DFS with a "cache". A Backracking solution with a "cache"
    then this:
        O(n * sum(nums))
    would be both time and space complexity.

    However it is possible to improve space complexity by using:
        Dynammic Programming

    So we start from the back and construct the Bottom-Up solution using DP.

    I)
    [1, 5, 11, 5]
               i

    We either take it or we don't so:
        dp = {0, 5}

    I)
    [1, 5, 11, 5]
           i

    We either take it or we don't so:
        dp = {0, 5, 11, 16}

    etc.

    The important thing is that we construct out dp as a set. That way we don't
    store duplicates.

    If at any point we find out target => return true

    All the unique sums of this example(if we were not to stop immediately once
    we encountered "target" value) would be:
        dp {0, 5, 11, 16, 10, 21, 1, 6, 12, 17, 22}

*/

/* Time  Beats:  5.00% */
/* Space Beats:  5.23% */

/* Time  Complexity: O(n * sum(nums)) */
/* Space Complexity: O(n * sum(nums)) */
class Solution{
public:
    bool canPartition(vector<int>& nums)
    {
        int sum = 0;
        for (const auto& n : nums)
            sum += n;

        if (sum & 1) // Odd number
            return false;

        set<int> dp_set;
        dp_set.insert(0);

        int target = sum / 2;
        int n = nums.size();

        for (int i = n - 1; i >= 0; i--)
        {
            set<int> tmp_set;
            for (const auto& elem : dp_set)
            {
                if ((elem + nums[i]) == target)
                    return true;

                tmp_set.insert(elem + nums[i]);
                tmp_set.insert(elem);
            }

            dp_set.insert(tmp_set.begin(), tmp_set.end());
        }

        if (dp_set.find(target) != dp_set.end())
            return true;

        return false;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same IDEA as the above Solution, just optimized code.

*/

/* Time  Beats: 10.31% */
/* Space Beats: 73.30% */

/* Time  Complexity: O(n * sum(nums)) */
/* Space Complexity: O(n * sum(nums)) */
class Solution_Optimized_1{
public:
    bool canPartition(vector<int>& nums)
    {
        int n = nums.size();
        int sum = accumulate(nums.begin(), nums.end(), 0);

        if (sum % 2 != 0)
            return false;

        int target = sum / 2;
        vector<vector<bool>> dp(n, vector<bool>(target + 1, false));

        // Populate the first column
        dp[0][0] = true;

        // Populate the first row
        if (nums[0] <= target)
            dp[0][nums[0]] = true;

        for (int i = 1; i < n; i++)
        {
            for (int j = 0; j <= target; j++)
            {
                dp[i][j] = dp[i - 1][j];

                if (j >= nums[i])
                    dp[i][j] = dp[i][j] || dp[i - 1][j - nums[i]];
            }
        }

        return dp[n - 1][target];
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same IDEA as the above two Solutions, just optimized even more.

*/

/* Time  Beats: 59.85% */
/* Space Beats: 99.50% */

/* Time  Complexity: O(n * sum(nums)) */
/* Space Complexity: O(n * sum(nums)) */
class Solution_Optimized_2_Efficient{
public:
    bool canPartition(vector<int>& nums)
    {
        int n = nums.size();
        int sum = accumulate(nums.begin(), nums.end(), 0);

        // These two sorts are effectively EQUIVALENT(sort in DESCENDING order)
        sort(nums.rbegin(), nums.rend());
        // sort(nums.begin(), nums.end(), greater<int>());

        if (sum % 2 != 0)
            return false;

        int target = sum / 2;
        vector<bool> dp(target + 1, false);
        dp[0] = true;

        for (int i = 0; i < n; i++)
        {
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

    By-the-book Memoization Problem.

    Constraits of:

        1 <= N <= 200
        1 <= nums[i] <= 100

    scream:"Memoization!" as 2^N would be to inefficient, whereas the "total
    number of states" would be the Time Complexity of O(200 * 20000).

    How did I get these numbers?
    We'll have "memo" that will be declared like this:

        int memo[201][20001];

    But why these numbers specifically?

    201 is obvious. It's the total number of elements of "nums". That is always
    a part of "memo" in any Memoization Problem.

    However, 20001 seems to come from nowhere. Actually it's just the worst
    case scenario pertaining to our "sum" part.

    We need to be able to represent ANY sum, therefore the biggest possible sum
    is to sum all of the elements.

    But imagine that each element is 100(which is the maximum according to our
    Constrints).

    Now imagine that N=200, i.e. number of elements in total is 200.

    Therefore in the worst case, at the last element we will have a state that
    represents the sum of ALL the elements.

    If we have 200 elements and each one is 100, then the total sum is 20000.
    And that needs to be able to be represented, therefore 20001(because it's
    0-indexed).

*/

/* Time  Beats: 11.10% */
/* Space Beats: 51.86% */

/* Time  Complexity: O(N * sum / 2) ---> O(N * sum) */
/* Space Complexity: O(N * sum / 2) ---> O(N * sum) */
class Solution_Memoization {
private:
    int memo[201][20001]; // 200 * 100 = 20000
public:
    bool canPartition(vector<int>& nums)
    {
        memset(memo, -1, sizeof(memo)); // It MUST be -1, and not "false"!!!

        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum & 1)
            return false;

        return memoization(nums, 0, sum / 2);
    }

private:
    bool memoization(vector<int>& nums, int idx, int sum)
    {
        if (sum == 0)
            return true;
        else if (static_cast<unsigned>(idx) == nums.size() || sum < 0)
            return false;

        if (memo[idx][sum] != -1)
            return memo[idx][sum];

        bool take = memoization(nums, idx+1, sum - nums[idx]);
        bool skip = memoization(nums, idx+1, sum            );

        return memo[idx][sum] = take || skip;
    }
};
