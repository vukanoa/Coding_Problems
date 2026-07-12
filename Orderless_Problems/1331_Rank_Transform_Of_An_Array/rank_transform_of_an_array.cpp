/*
    ============
    === EASY ===
    ============

    ================================
    1331) Rank Transform of an Array
    ================================

    ============
    Description:
    ============

    Given an array of integers arr, replace each element with its rank.

    The rank represents how large the element is. The rank has the following
    rules:

        + Rank is an integer starting from 1.

        + The larger the element, the larger the rank. If two elements are
          equal, their rank must be the same.

        + Rank should be as small as possible.


    ===========================================================
    FUNCTION: vector<int> arrayRankTransform(vector<int>& arr);
    ===========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: arr = [40,10,20,30]
    Output: [4,1,2,3]
    Explanation: 40 is the largest element. 10 is the smallest. 20 is the
                 second smallest. 30 is the third smallest.


    --- Example 2 ---
    Input: arr = [100,100,100]
    Output: [1,1,1]
    Explanation: Same elements share the same rank.


    --- Example 3 ---
    Input: arr = [37,12,28,9,100,56,80,5,12]
    Output: [5,3,4,2,8,6,7,1,3]


    *** Constraints ***
    0 <= arr.length <= 10^5
    -10^9 <= arr[i] <= 10^9

*/

#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 70.09% */
/* Space Beats: 70.17% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution {
public:
    vector<int> arrayRankTransform(vector<int>& arr)
    {
        const int N = arr.size();

        unordered_map<int, int> rank_of_num;
        vector<int> sorted_uniq_nums = arr;

        /* Sort */
        sort(sorted_uniq_nums.begin(), sorted_uniq_nums.end());

        /* Remove Duplicates */
        sorted_uniq_nums.erase(unique(sorted_uniq_nums.begin(), sorted_uniq_nums.end()), sorted_uniq_nums.end());

        const int UNIQUE_NUMBERS = sorted_uniq_nums.size();

        // Assign ranks to sorted unique elements
        for (int i = 0; i < UNIQUE_NUMBERS; i++)
            rank_of_num[sorted_uniq_nums[i]] = i + 1;

        // Replace each element in the original array with its rank
        for (int i = 0; i < arr.size(); i++)
            arr[i] = rank_of_num[arr[i]];

        return arr;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 42.82% */
/* Space Beats: 42.78% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution_2 {
public:
    vector<int> arrayRankTransform(vector<int>& arr)
    {
        const int N = arr.size();
        vector<int> result(N, -1);

        vector<pair<int,int>> nums;
        nums.reserve(N);
        for (int i = 0; i < N; i++)
            nums.push_back( {arr[i], i} );  // {number, orig_idx}

        /* Sort */
        sort(nums.begin(), nums.end());

        unordered_map<int,int> rank_of_num;
        int smallest_unused_rank = 1;
        for (int i = 0; i < N; i++)
        {
            if (rank_of_num.find(nums[i].first) != rank_of_num.end())
                continue;

            rank_of_num[nums[i].first] = smallest_unused_rank;
            smallest_unused_rank++;
        }

        for (int i = 0; i < N; i++)
        {
            const int& number   = nums[i].first;
            const int& orig_idx = nums[i].second;

            result[orig_idx] = rank_of_num[number];
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Another way to solve it.

*/

/* Time  Beats: 96.01% */
/* Space Beats: 99.15% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution_Binary_Search {
public:
    vector<int> arrayRankTransform(vector<int>& arr)
    {
        const int N = arr.size();
        vector<int> nums = arr;

        /* Sort */
        sort(nums.begin(), nums.end());

        /* Remove Duplicates */
        nums.erase(unique(nums.begin(), nums.end()), nums.end());

        for (int i = 0; i < arr.size(); i++)
            arr[i] = lower_bound(nums.begin(), nums.end(), arr[i]) - nums.begin() + 1;

        return arr;
    }
};
