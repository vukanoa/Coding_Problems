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

#include <vector>
#include <algorithm>
using namespace std;

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


    TODO

*/

/* Time  Beats: 62.94% */
/* Space Beats: 71.42% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(N)   */
class Solution_Squared {
public:
    int lengthOfLIS(vector<int>& nums)
    {
        const int N = nums.size();

        vector<int> dp(N, 1);
        for (int i = N-2; i >= 0; i--)
        {
            for (int j = i+1; j < N; j++)
            {
                if (nums[i] < nums[j])
                    dp[i] = max(dp[i], 1 + dp[j]);
            }
        }

        return *max_element(dp.begin(), dp.end());
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This is also known as "Patience Sort" as it optimally solves the game of
    patience.

    That name comes from the playing card game called "Patience" in which the
    goal is to have the lesat amount of piles that are all in decreasing
    order.

    However, if you do that, top of each of those piles will form the longest
    increasing subsequences.

    Similar problem called: "Decreasing Subsequences" exists(not on LeetCode).
    The goal in that problem is the return the minimum number of piles needed,
    where every pile MUST be a decreasing subsequence.


    Vector "top_of_pile" is in singular as top_of_pile[i] represents the top
    card at pile 'i'.

    The LENGTH of "top_of_pile" is the NUMBER OF DIFFERENT PILES.
    Cards in EACH pile is sorted in DECREASING order, however we ONLY keep
    track of the SMALLEST card that is on the TOP of that pile[i].


    Let's construct the idea from following example.

        nums = [2, 6, 8, 3, 4, 5, 1]


    1. Let's pick the first element,

           top_of_pile = [2]


    2. 6 is greater than the previous number, create a NEW pile with 6 on top
       of that new pile.

           top_of_pile = [2, 6]


    3. 8 is greater than the previous number, create a NEW pile with 8 on top
       of that new pile.

           top_of_pile = [2, 6, 8]


    4. 3 is less than the previous number, so we can't extend the subsequence
       top_of_pile(which contains a bunch of piles, each sorted in DECREASING
       order, however we ONLY keep track of the smallest card in each pile that
       is at the very top).
       We need to find the smallest number that is >= 3 in "top_of_pile", and
       replace that pile's top with 3.

       In our example, it's 6, thus we overwrite 6 with our current card=3.

           top_of_pile = [2, 3, 8].


    5. 4 is smaller than 8, thus we replace 8 with 4.

           top_of_pile = [2, 3, 4]


    6. 5 is greater than the rightmost top card, thus we create a NEW pile with
       5 on top of that new pile.

           top_of_pile = [2, 3, 4, 5]


    7. For card=1, this smallest top_card is 2, thus we overwrite 2 by 1, so:

           top_of_pile = [1, 3, 4, 5].


    8. Finally, the total number of piles is = len(top_of_pile) = 4

*/

/* Time  Beats: 100.00% */
/* Space Beats:  67.15% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution_Patience_Sort {
public:
    int lengthOfLIS(vector<int>& nums)
    {
        const int N = nums.size();

        vector<int> top_of_pile;
        top_of_pile.reserve(N); // To prevent reallocations

        /* Initially only 1 pile exists with nums[0] at the top of that pile */
        top_of_pile.push_back(nums[0]);

        for (int i = 1; i < N; i++)
        {
            if (top_of_pile.back() < nums[i])
            {
                top_of_pile.push_back(nums[i]);
            }
            else
            {
                auto pile = lower_bound(top_of_pile.begin(), top_of_pile.end(), nums[i]);
                *pile = nums[i];
            }
        }

        return top_of_pile.size();
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    It's absolutely equivalent to the above Solution, however this one uses my
    own "lower bound" Binary Search implementation instead.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  67.08% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution_Patience_Sort_using_My_Binary_Search_Implementation {
public:
    int lengthOfLIS(vector<int>& nums)
    {
        const int N = nums.size();

        vector<int> top_of_pile;
        top_of_pile.reserve(N); // To prevent reallocations

        /* Initially only 1 pile exists with nums[0] at the top of that pile */
        top_of_pile.push_back(nums[0]);

        for (int i = 1; i < N; i++)
        {
            if (top_of_pile.back() < nums[i])
            {
                top_of_pile.push_back(nums[i]);
            }
            else
            {
                const int PILES = top_of_pile.size();
                int pile_idx = my_lower_bound(0, PILES-1, nums[i], top_of_pile);

                top_of_pile[pile_idx] = nums[i];
            }
        }

        return top_of_pile.size();
    }

private:
    int my_lower_bound(int low, int high, int target, vector<int>& top_of_pile)
    {
        while (low < high)
        {
            int mid = low + (high - low) / 2; // Low-leaning

            if (target > top_of_pile[mid])
                low = mid + 1;
            else
                high = mid;
        }

        return low; // or "high", it does NOT matter
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
    Time  Complexity: O(N * logMAX)
    where MAX <= 20000 is the difference between minimum and maximum elements
    in nums, N <= 2500 is the number of elements in array nums.
*/
/*
    Space Complexity: O(MAX)
*/
class MaxBIT {
private:
    vector<int> bit;

public:
    MaxBIT(int size)
    {
        bit.resize(size + 1);
    }

    int get(int idx)
    {
        int ans = 0;
        for (; idx > 0; idx -= idx & -idx)
            ans = max(ans, bit[idx]);

        return ans;
    }

    void update(int idx, int val)
    {
        for(; idx < bit.size(); idx += idx & -idx)
            bit[idx] = max(bit[idx], val);
    }

};

class Solution_BIT {
public:
    int lengthOfLIS(vector<int>& nums)
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

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution_BIT_Compress {
public:
    int lengthOfLIS(vector<int>& nums)
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

    int compress(vector<int>& nums)
    {
        vector<int> unique_sorted(nums);

        /* Sort */
        sort(unique_sorted.begin(), unique_sorted.end());

        unique_sorted.erase(unique(unique_sorted.begin(), unique_sorted.end()), unique_sorted.end()); // Remove duplicated values

        for (int& x : nums)
            x = lower_bound(unique_sorted.begin(), unique_sorted.end(), x) - unique_sorted.begin() + 1;

        return unique_sorted.size();
    }
};
