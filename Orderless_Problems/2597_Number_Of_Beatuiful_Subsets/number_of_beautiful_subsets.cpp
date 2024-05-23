#include <iostream>
#include <vector>
#include <unordered_map>

/*
    ==============
    === MEDIUM ===
    ==============

    =================================
    2697) Number of Beautiful Subsets
    =================================

    ============
    Description:
    ============

    You are given an array nums of positive integers and a positive integer k.

    A subset of nums is beautiful if it does not contain two integers with an
    absolute difference equal to k.

    Return the number of non-empty beautiful subsets of the array nums.

    A subset of nums is an array that can be obtained by deleting some
    (possibly none) elements from nums. Two subsets are different if and only
    if the chosen indices to delete are different.

    =========================================================
    FUNCTION: int beautifulSubsets(vector<int>& nums, int k);
    =========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [2,4,6], k = 2
    Output: 4
    Explanation: The beautiful subsets of the array nums are: [2], [4], [6],
                 [2, 6].  It can be proved that there are only 4 beautiful
                 subsets in the array [2,4,6].


    --- Example 2 ---
    Input: nums = [1], k = 1
    Output: 1
    Explanation: The beautiful subset of the array nums is [1].
    It can be proved that there is only 1 beautiful subset in the array [1].


    *** Constraints ***
    1 <= nums.length <= 20
    1 <= nums[i], k <= 1000

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 5.17% */
/* Space Beats: 5.17% */

/* Time  Complexity: O(2^n) */
/* Space Complexity: O(n)   */
class Solution {
public:
    int beautifulSubsets(std::vector<int>& nums, int k)
    {
        int count;
        std::unordered_map<int, int> umap_visited;

        backtracking(nums, k, 0, umap_visited, count);

        return count - 1; // Subtract 1 to exclude the empty subset
    }

private:
    void backtracking(vector<int>& nums,
                      int& k,
                      int  curr_idx,
                      std::unordered_map<int, int>& umap_visited,
                      int& count)
    {
        if (curr_idx == nums.size())
        {
            count++;
            return;
        }

        int num = nums[curr_idx];

        if (umap_visited.find(num - k) == umap_visited.end() &&
            umap_visited.find(num + k) == umap_visited.end())
        {
            umap_visited[num]++; // Increment

            backtracking(nums, k, curr_idx+1, umap_visited, count);

            umap_visited[num]--; // Decrement
            if (umap_visited[num] == 0)
                umap_visited.erase(num);
        }

        backtracking(nums, k, curr_idx+1, umap_visited, count);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Intuition & Approach

    1.  The problem asks us to find the number of beautiful subsets of the
        given array nums, where a subset is beautiful if the absolute
        difference between any two elements in the subset is exactly k .

    2.  The intuition behind the algorithm is to use dynamic programming to
        count the number of beautiful subsets that end with each element of the
        array.

    3.  We can then sum up these counts to get the total number of beautiful
        subsets. To implement this approach, we first count the frequency of
        each element in the array using a HashMap .

    4.  We then define a recursive function dp(num) that takes an element num
        and returns a pair of values (dp0, dp1) , where dp0 is the number of
        beautiful subsets that end with num and do not include any element that
        is k units away from nums, and dp1 is the number of beautiful subsets
        that end with nums and include at least one element that is k units
        away from num. To compute dp(num),

    5.  We check if there is an element num - k in the count map. If there is,
        we recursively call dp(num - k) to get the values (dp0', dp1') for the
        element num - k .

    6.  We can then compute dp0 and dp1 as follows: dp0 = dp0' + dp1' : We can
        append num to any beautiful subset that ends with num-k and does not
        include any element that is k units away from num.
            dp1 = dp0' * (2^count[a] - 1) :

    7.  We can append num to any beautiful subset that ends with num-k and
        includes at least one element that is k units away from num.

    8.  There are dp0' such subsets, and for each subset, we can choose any
        subset of the count[num] elements that are k units away from nums
        except for the empty subset. If there is no element num-k in the
        umap_count, we set dp0 = 1 and dp1 = 2^count[num] - 1, since the only
        beautiful subset that ends with a is the singleton set (num}. To avoid
        redundant calculations, we use memoization to store the values of
        dp(num) in a HashMap called memo.

    9.  Finally, we sum up the values of dp0 and dp1 for all elements a in the
        count map that do not have an element num+k in the count map, and
        multiply them together to get the total number of beautiful subsets.

    10. We subtract 1 from the result to exclude the empty subset. The time
        complexity of this algorithm is O(n log n), where n is the length of
        the input array, since we need to sort the array and perform O(log n)
        recursive calls for each element.
        + The space complexity is also O(n), since we need to store the count
          map and the memo map.

*/

/* Time  Beats: 75.62% */
/* Space Beats: 71.49% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n)        */
class Solution_Efficient {
public:
    int beautifulSubsets(vector<int>& nums, int k)
    {
        std::unordered_map<int, int> umap_count;
        for (const int& num : nums)
            umap_count[num]++;

        /* Lambda */
        std::function<std::pair<int, int>(int)> dp = [&](int num)
        {
            if (umap_count.count(num - k))
            {
                auto [dp0, dp1] = dp(num - k);

                return std::make_pair(dp0 + dp1, dp0 * ((1 << umap_count[num]) - 1));
            }
            else
                return std::make_pair(1, (1 << umap_count[num]) - 1);
        };

        int result = 1;
        for (const auto& [num, freq] : umap_count)
        {
            if (!umap_count.count(num + k))
            {
                auto [dp0, dp1] = dp(num);

                result *= dp0 + dp1;
            }
        }

        return result - 1;
    }
};
