#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map> // TLE Solution

/*
    ==============
    === MEDIUM ===
    ==============

    ===================================
    300) Longest Increasing Subsequence
    ===================================

    ============
    Description:
    ============

    Given an integer array "nums", return the length of the longest strictly
    increasing subsequence.

    Follow Up: Can you come up with an algorithm that runs in O(n * logn) time
    complexity?

    =============================================
    FUNCTION: int lengthOfLIS(vector<int>& nums);
    =============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  nums = [10, 9, 2, 5, 3, 7, 101, 18]
    Output: 4
    Explanation: The longest increasing subsequence is [2, 3, 7, 101],
    therefore the length is 4.

    --- Example 2 ---
    Input:  nums = [0, 1, 0, 3, 2, 3]
    Output: 4

    --- Example 3 ---
    Input:  [7, 7, 7, 7, 7, 7, 7]
    Output: 1

    *** Constraints ***
    1 <= nums.length <= 2500
    -10^4 <= nums[i] <= 10^4

*/


class Solution_TLE {
public:
    int lengthOfLIS(std::vector<int>& nums)
    {
        int n = nums.size();
        std::unordered_map<int, std::vector<int>> umap;
        int max = 1;

        for (int i = 0; i <= n; i++)
            umap[i] = {};

        for (int i = 0; i < nums.size(); i++)
        {
            umap[1].push_back(nums[i]);

            for (int j = i; j > 0; j--)
            {
                if (umap[j].empty())
                    continue;

                bool exist = false;
                for (int k = 0; k < umap[j].size(); k++)
                {
                    if (umap[j][k] < nums[i])
                    {
                        umap[j + 1].push_back(nums[i]);

                        if (j + 1 > max)
                            exist = true;
                    }
                }

                if (exist)
                    max++;
            }
        }

        return max;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    At each index we can either choose it or skip it. Thus doing every possible
    combination would take O(2^n) Time.

    Can we do better?
    Let's draw a decision tree.

    Consider this example:
        nums = [1, 2, 4, 3]
                0  1  2  3
                                              START
                                             / | \ \________________
                                    ________/  |  \__________       \
                                  0/          1|           2|        \3
                                  /            |            |         \
                                 /             |            |         |
                                /              |            |         |
                               /               |            |         |
                            [1]               [2]          [4]       [3]
                       ___/  | \___          /   \          |         |
                     1/     2|     \3      2/     \3        X         X
                     /       |      \      |       |
                 [1,2]     [1,4]  [1,3]  [2,4]  [2,3]
             ___/   |        |      |      |      |
           2/      3|        X      X      X      X
           /        |
        [1,2,4]   [1,2,3]
           |         |
           X         X


    We can see, for example, that going all the way to the left, after we
    include 4(index 2) we aren't able to increase our subsequence any further.
    Thus, if we go any other route, if we choose 4(index 2), it's immediately
    terminated sinsce we've already calculated that we can't increase our
    subsequence from that point onwards.

    So in order to remove repeated calculations, we'll have a "cache", i.e. our
    LIS(Longest Increasing Subsequence) vector which represents our DP array
    where we store our calculated sequences.

    Since LIS[2] represents how many elements, or how big is going to be our
    subsequence if we include number at index 2, until the end of the array is
    increasing, we can see that we have to start from the back.

    In our Example:
        nums = [1, 2, 4, 3]
                0  1  2  3

    LIS[3] will always be 1, because 3 == n-1

    Then when we're calculating LIS[2] we can either have:
        1. 1 or
        2. 1 + LIS[3]   if (nums[2] < nums[3])

    However, we can only take the latter if nums[2] < nums[3].

    When we're calculating LIS[1], we can either have:
        1. 1 or
        2. 1 + LIS[2]  if(nums[1] < nums[2]) or
        3. 1 + LIS[3]  if(nums[1] < nums[3])

    You can see that we're iterating through the array for every element, thus
    it's a O(n^2) Time Complexity.
*/

/* Time  Beats: 62.94% */
/* Space Beats: 71.42% */
class Solution_DFS_with_Cache_DP {
public:
    int lengthOfLIS(std::vector<int>& nums)
    {
        int n = nums.size();
        std::vector<int> LIS (n, 1);

        for (int i = n-1; i >= 0; i--)
        {
            for (int j = i+1; j < n; j++)
            {
                if (nums[i] < nums[j])
                    LIS[i] = std::max(LIS[i], 1 + LIS[j]);
            }
        }

        return *std::max_element(LIS.begin(), LIS.end());
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same as above, however it's a bit faster if we find "result" while we are
    doing the problem. That way we don't have to go through the array once more
    to find the maximum element.

*/

/* Time  Beats: 61.69% */
/* Space Beats: 63.09% */

/* Time  Complexity: O(n^2) */
/* Space Complexity: O(n) */
class Solution_DP_2 {
public:
    int lengthOfLIS(vector<int>& nums)
    {
        const int n = nums.size();
        std::vector<int> LIS(n, 1);

        int result = 1;

        for (int i = n; i >= 0; i--)
        {
            for (int j = i+1; j < n; j++)
            {
                if (nums[i] < nums[j])
                {
                    LIS[i] = std::max(LIS[i], 1 + LIS[j]);
                    result = std::max(result, LIS[i]);
                }
            }
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This is a classic Dynamic Programming problem.

    Let dp[i] be the longest increase subsequence of nums[0..i] where nums[i]
    is the last element of the subsequence.

    It's pretty much self-explanatory. Just simulate one example by going
    through the code and it will be clear.

*/

/* Time  Beats: 64.76% */
/* Space Beats: 69.51% */

/* Time  Complexity: O(n^2) */
/* Space Complexity: O(n) */
class Solution_DP{
public:
    int lengthOfLIS(std::vector<int>& nums)
    {
        int n = nums.size();
        std::vector<int> dp(n, 1);

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < i; j++)
            {
                if (nums[i] > nums[j] && dp[i] < dp[j] + 1)
                    dp[i] = dp[j] + 1;
            }
        }

        return *std::max_element(dp.begin(), dp.end());
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Almost equivalent IDEA to the one above, but implemented in a way that's
    easier to undersand.

    This is a good example to simulate:

    nums = [3,  4, -1,  0,  6,  2,  3]
            0   1   2   3   4   5   6

    dp   = [1,  2,  1,  2,  3,  3,  4]
            0   1   2   3   4   5   6

*/

/* Time  Beats: 60.30% */
/* Space Beats: 39.14% */

/* Time  Complexity: O(n^2) */
/* Space Complexity: O(n) */
class Solution_Touche {
public:
    int lengthOfLIS(std::vector<int> &nums)
    {
        int n = nums.size();
        std::vector<int> dp(n, 1);

        int left  = 0;
        int right = 1;
        while (right < n)
        {
            if (left == right)
            {
                left = 0;
                right++;

                continue;
            }
            else if (nums[left] < nums[right])
                dp[right] = std::max(dp[right], dp[left] + 1);

            left++;
        }

        return *max_element(dp.begin(), dp.end());
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Greedy with Binary Search

    Let's construct the idea from following example.

        nums = [2, 6, 8, 3, 4, 5, 1],

    let's try to build the increasing subsequences starting with an empty one

        sub1 = [].

    1. Let pick the first element, sub1 = [2]


    2. 6 is greater than the previous number.

           sub1 = [2, 6]


    3. 8 is greater than previous number.

           sub1 = [2, 6, 8]


    4. 3 is less than previous number, therefore we can't extend the
       subsequence sub1, but we must keep 3 because in the future the longest
       subsequence may start with [2, 3]. Now we have:

        sub1 = [2, 6, 8],
        sub2 = [2, 3]


    5. With 4, we can't extend sub1, but we can extend sub2, so:

           sub1 = [2, 6, 8],
           sub2 = [2, 3, 4]

    6. With 5, we can't extend sub1, but we can extend sub2, so:

           sub1 = [2, 6, 8],
           sub2 = [2, 3, 4, 5]


    7. With 1, we can't extend neither sub1 nor sub2, but we need to keep 1,
       so:
           sub1 = [2, 6, 8],
           sub2 = [2, 3, 4, 5],
           sub3 = [1]


    8. Finally, length of the longest increase subsequence = len(sub2) = 4


    ~~~~~~~~~~~~
    ~~~ Note ~~~
    ~~~~~~~~~~~~
    Now this optimization is not intuitive to me AT ALL. If you find it hard
    to grasp, it's okay.

    In the above steps, we need to keep different "sub" arrays

        (sub1, sub2, sub3, ..., subk)

    which causes poor performance. But we are noticing that we can just keep
    one "sub" array, when new number 'x' is not greater than the last element
    of the subsequence "sub" we do a binary search to find the smallest
    element >= x in "sub", and replace with number x.


    Let's run that example again:

        nums = [2, 6, 8, 3, 4, 5, 1] again:

    1. Let's pick the first element,

           sub = [2]


    2. 6 is greater than the previous number,

           sub = [2, 6]


    3. 8 is greater than the previous number,

           sub = [2, 6, 8]


    4. 3 is less than the previous number, so we can't extend the subsequence
       sub. We need to find the smallest number that is >= 3 in "sub", it's 6.
       Then we overwrite it, now:

           sub = [2, 3, 8].


    5. 4 is less than previous number so we can't extend the subsequence sub.
       We overwrite 8 by 4, so:

           sub = [2, 3, 4]


    6. 5 is greater than the previous number:

           sub = [2, 3, 4, 5]


    7. 1 is less than previous number, so we can't extend the subsequence sub,
       We overwrite 2 by 1, so:

           sub = [1, 3, 4, 5].


    8. Finally, length of the longest increase subsequence = len(sub) = 4

*/

/* Time  Beats:   100% */
/* Space Beats: 87.72% */

/*    Time  Complexity: O(n * logn) */
/*
    Space Complexity: O(n)
    We can achieve O(1) in space by overwriting values of "sub" into original
    "nums" array. But in order to do that we'd have to be sure that is
    permitted.
*/
class Solution_Greedy_Binary {
public:
    int lengthOfLIS(std::vector<int> &nums)
    {
        std::vector<int> sub;
        sub.push_back(nums[0]);

        for (int i = 1; i < nums.size(); i++)
        {
            if (sub[sub.size() - 1] < nums[i])
            {
                sub.push_back(nums[i]);
            }
            else
            {
                // Search for first element e such that: nums[i] <= e
                auto it = std::lower_bound(sub.begin(), sub.end(), nums[i]);
                *it = nums[i];
            }
        }

        return sub.size();
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    The above and below Solutions are similar, however it's more difficult to
    grasp if you hear the right name of the approach - Patience Sort.

    That name comes from the playing card game called "Patience" in which the
    goal is to have the lesat amount of piles that are all in decreasing
    order.

    However, if you do that, top of each of those piles will form the longest
    increasing subsequences.

    Similar problem called: "Decreasing Subsequences" exists(not on LeetCode).
    The goal in that problem is the return the minimum number of piles needed,
    where every pile MUST be a decreasing subsequence.

*/

/* Time  Beats:   100% */
/* Space Beats: 80.57% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n) */
class Solution_Patience_Sort {
public:
    int lengthOfLIS(std::vector<int>& nums)
    {
        std::vector<int> piles;
        piles.push_back(nums[0]);

        for (int i = 1; i < nums.size(); i++)
        {
            if (piles[piles.size() - 1] < nums[i])
                piles.push_back(nums[i]);
            else
            {
                auto upper = std::lower_bound(piles.begin(), piles.end(), nums[i]);
                *upper = nums[i];
            }
        }

        return piles.size();
    }
};





/*
    ------------
    --- IDEA ---
    ------------

    It's absolutely equivalent to the Solution above(Solution_Greedy_Binary),
    however, this one uses my own Binary Search "lower_bound" function.

*/

/* Time  Beats:  100% */
/* Space Beats: 48.99% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n) */
class Solution_My_Binary {
public:
    int lengthOfLIS(std::vector<int> &nums)
    {
        if (nums.size() == 1)
            return 1;

        std::vector<int> subseq;
        subseq.push_back(nums[0]);

        for (int i = 1; i < nums.size(); i++)
        {
            if (subseq[subseq.size() - 1] < nums[i])
                subseq.push_back(nums[i]);
            else
                binary_search_emplace(subseq, nums[i]);
        }

        return subseq.size();
    }

private:
    void binary_search_emplace(std::vector<int>& subseq, int num)
    {
        // [1, 4, 7, 8, 10], num=3, num=9, num=4

        int left  = 0;
        int right = subseq.size() - 1;

        while (left < right)
        {
            int mid = left + (right - left) / 2;

            if (subseq[mid] >= num)
                right = mid;
            else // subseq[mid] < num
                left = mid + 1;
        }

        subseq[left] = num;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Binary Indexed Tree(Increase base of "nums" into one-basing indexing)

    - Let f[x] be the length of longest increase subsequence, where all number
    in the subsequence are <= x. This is the max element in indices [1..x] if
    we build the Binary Indexed Tree(BIT)

    - Since -10^4 <= nums[i] <= 10^4, we can convert nums into:
          1 <= nums[i] <= 2 * 10^4 + 1 by plus base=10001 to store into the BIT

    - We build Max BIT, which has 2 operators:
        - get(idx): Return the maximum value of indices in range [1..idx].
        - update(idx, val): Update a value "val" into BIT at index "idx".

    - Iterate numbers "i" in range [0..n-1]:
        - subLongest = bit.get(nums[i] - 1) // Get longest increasing
          // subsequence so far, which idx < nums[i], or idx <= nums[i] - 1
        - bit.update(nums[i], subLongest + 1) // Update latest longest to the
          BIT.

    - The answer is bit.get(20001) // Maximum of all elemenst in the BIT

*/

/* Time  Beats: 95.35% */
/* Space Beats: 29.4% */

/*
    Time  Complexity: O(n * logMAX)
    where MAX <= 20000 is the difference between minimum and maximum elements
    in nums, N <= 2500 is the number of elements in array nums.
*/
/*
    Space Complexity: O(MAX)
*/
class MaxBIT {
private:
    std::vector<int> bit;

public:
    MaxBIT(int size)
    {
        bit.resize(size + 1);
    }

    int get(int idx)
    {
        int ans = 0;
        for (; idx > 0; idx -= idx & -idx)
            ans = std::max(ans, bit[idx]);

        return ans;
    }

    void update(int idx, int val)
    {
        for(; idx < bit.size(); idx += idx & -idx)
            bit[idx] = std::max(bit[idx], val);
    }

};

class Solution_BIT {
public:
    int lengthOfLIS(std::vector<int>& nums)
    {
        int base = 10001;
        MaxBIT bit(20001);

        for (int x : nums)
        {
            int subLongest = bit.get(base + x - 1);
            bit.update(base + x, subLongest + 1);
        }

        return bit.get(20001);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Binary Indexed Tree(Compress nums into values [i..N])

    In previous solution(the one above this one), -10^4 <= nums[i] <= 10^4 is
    small enough, so we can store in our Binary Indexed Tree (BIT)

    Can we store when -10^9 <= nums[i] <= 10^9 is very big? In that case, we
    can compress our nums array while keeping the relative comparation order
    between numbers.

    How to compress?
        - In the nums array the length n, where n <= 2500, there are maximum n
          different numbers.

        - We can ge the unique values of numbers in nums, and sort those values
          in increasing order, let's name it uniqueSorted.

        - Then we traverse i in ragen [0..n-1], we get the compressed value of
          nums[i] by looking hte index in uniqueSorted.

        - As the result, elements in nums is compressed into values in range
          [1..N]

*/

// ##### This Solution uses the same Max BIT class as the Solution above #####

/* Time  Beats: 75.39% */
/* Space Beats: 37.24% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n) */
class Solution_BIT_Compress {
public:
    int lengthOfLIS(std::vector<int>& nums)
    {
        int nUnique = compress(nums);
        MaxBIT bit(nUnique);

        for(int x : nums)
        {
            int subLongest = bit.get(x - 1);
            bit.update(x, subLongest + 1);
        }

        return bit.get(nUnique);
    }

    int compress(std::vector<int>& arr)
    {
        std::vector<int> uniqueSorted(arr);
        std::sort(uniqueSorted.begin(), uniqueSorted.end());
        uniqueSorted.erase(unique(uniqueSorted.begin(), uniqueSorted.end()), uniqueSorted.end()); // Remove duplicated values

        for (int& x: arr)
            x = lower_bound(uniqueSorted.begin(), uniqueSorted.end(), x) - uniqueSorted.begin() + 1;

        return uniqueSorted.size();
    }
};

int
main()
{
    Solution_DFS_with_Cache_DP sol_dfs_cache_dp;
    Solution_DP                sol_dp;
    Solution_Greedy_Binary     sol_grd_bin; // Efficient!
    Solution_Patience_Sort     sol_patience; // Efficient!
    Solution_My_Binary         sol_my_bin;  // Efficient!
    Solution_BIT               sol_bit;
    Solution_BIT_Compress      sol_bit_com;
    Solution_Touche            sol_touche;


    /* Example 1 */
    std::vector<int> nums = {10, 9, 2, 5, 3, 7, 101, 18};

    /* Example 2 */
    // std::vector<int> nums = {0, 1, 0, 3, 2, 3};

    /* Example 3 */
    // std::vector<int> nums = {7, 7, 7, 7, 7, 7, 7};

    std::cout << "\n\t======================================";
    std::cout << "\n\t=== LONGEST INCREASING SUBSEQUENCE ===";
    std::cout << "\n\t======================================\n";


    /* Write Input */
    bool first = true;
    std::cout << "\n\tArray: [";
    for (auto x: nums)
    {
        if (!first)
            std::cout << ", ";

        std::cout << x;
        first = false;
    }
    std::cout << "]\n";


    /* Solution */
    // int longest = sol_dfs_cache_dp.lengthOfLIS(nums);
    // int longest = sol_dp.lengthOfLIS(nums);
    // int longest = sol_grd_bin.lengthOfLIS(nums);
    int longest = sol_patience.lengthOfLIS(nums);
    // int longest = sol_my_bin.lengthOfLIS(nums);
    // int longest = sol_bit.lengthOfLIS(nums);
    // int longest = sol_bit_com.lengthOfLIS(nums);
    // int longest = sol_touche.lengthOfLIS(nums);


    std::cout << "\n\tLongest Increasing Subsequence: " << longest << "\n\n";

    return 0;
}
