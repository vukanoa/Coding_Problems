/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    90) Subsets II
    ===========================

    ============
    Description:
    ============

    Given an integer array nums that may contain duplicates, return all
    possible subsets (the power set).

    The solution set must not contain duplicate subsets. Return the solution in
    any order.

    ==============================================================
    FUNCTION: vector<vector<int> subsetWithDup(vector<int>& nums);
    ==============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,2]
    Output: [[],[1],[1,2],[1,2,2],[2],[2,2]]

    --- Example 2 ---
    Input: nums = [0]
    Output: [[],[0]]

    *** Constraints ***
    1 <= nums.length <= 10
    -10 <= nums[i] <= 10


    nums  = [1, 2, 3]
    Out: [[], [1], [1, 2], [1, 2, 3], [1, 3], [2], [2, 3], [3]]

*/

#include <algorithm>
#include <set>
#include <unordered_set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Brute Force. It's beneficial to see this before optimizing.

*/

/* Time  Beats: 6.58% */
/* Space Beats: 5.40% */

/* Time  Complexity: O(N * 2^N * log(2^N)) */
/* Space Complexity: O(N * 2^N)            */
class Solution_Bruteforce {
private:
    set<vector<int>> result;

public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums)
    {
        /* Sort */
        sort(nums.begin(), nums.end());

        backtrack(0, {}, nums);

        return vector<vector<int>>(result.begin(), result.end());
    }

    void backtrack(int i, vector<int> subset, vector<int>& nums)
    {
        const int N = nums.size();

        if (i == N)
        {
            result.insert(subset);
            return;
        }

        subset.push_back(nums[i]);
        backtrack(i + 1, subset, nums);
        subset.pop_back();

        backtrack(i + 1, subset, nums);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  65.72% */

/* Time  Complexity: O(n * 2^n) */
/* Space Complexity: O(n * 2^n) */
class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums)
    {
        vector<vector<int>> results; // Don't add initial '{}'
        sort(nums.begin(), nums.end());

        vector<int> subset;
        backtracking(nums, 0, subset, results);

        return results;
    }

private:
    void backtracking(vector<int>& nums,
                      int i,
                      vector<int>& subset,
                      vector<vector<int>>& results)
    {
        if (i == nums.size())
        {
            results.push_back(subset);
            return;
        }

        // All subsets that do INDEED include nums[i]
        subset.push_back(nums[i]);
        backtracking(nums, i+1, subset, results);
        subset.pop_back();

        // All subsets that do NOT include nums[i]
        while (i+1 < nums.size() && nums[i] == nums[i+1])
            i++;

        backtracking(nums, i+1, subset, results);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 40.31% */
/* Space Beats: 30.78% */

/* Time  Complexity: O(N * 2^N) */
/* Space Complexity: O(N * 2^N) */
class Solution_Iterative {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums)
    {
        const int N = nums.size();

        // Total number of subsets is up to 2^N, each subset up to size N
        // Space: O(N * 2^N)
        vector<vector<int>> result = {{}};

        sort(nums.begin(), nums.end()); // O(N log N)

        int latest_subsets = 0;

        for (int i = 0; i < N; i++) // Contributes to overall O(N * 2^N)
        {
            vector<vector<int>> new_subsets;

            if (i > 0 && nums[i-1] == nums[i])
            {
                // Only extend subsets created in previous step
                // Number of such subsets is at most 2^N in total across
                // execution
                for (int x = result.size() - latest_subsets; x < result.size(); x++)
                {
                    vector<int> subset = result[x]; // O(N)

                    subset.push_back(nums[i]); // O(1)

                    new_subsets.push_back(subset); // O(N)
                }
            }
            else
            {
                // Iterate over all existing subsets (up to 2^N total)
                for (vector<int> subset : result)
                {
                    subset.push_back(nums[i]); // O(N) (copying subset)

                    new_subsets.push_back(subset); // O(N)
                }
            }

            latest_subsets = new_subsets.size();

            // O(N)
            result.insert(result.end(), new_subsets.begin(), new_subsets.end());
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  21.35% */

/* Time  Complexity: O(N * 2^N) */
/* Space Complexity: O(N * 2^N) */
struct VectorHash
{
    size_t operator()(const vector<int>& arr) const
    {
        size_t h = 0;
        hash<int> hasher;

        for (const int& num : arr)
            h ^= hasher(num) + 0x9e3779b9 + (h << 6) + (h >> 2);

        return h;
    }
};

class Solution_Rolling_Hash {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums)
    {
        const int N = nums.size();
        vector<vector<int>> result = {{}};

        /* Sort */
        sort(nums.begin(), nums.end());

        VectorHash hasher;

        unordered_set<size_t> uset_hashes;
        for (int i = 0; i < N; i++)
        {
            vector<vector<int>> new_subsets;
            for (vector<int> subset : result)
            {
                subset.push_back(nums[i]);
                size_t hash = hasher(subset);

                if ( ! uset_hashes.count(hash))
                {
                    new_subsets.push_back(subset);
                    uset_hashes.insert(hash);
                }
            }

            result.insert(result.end(), new_subsets.begin(), new_subsets.end());
        }

        return result;
    }
};
