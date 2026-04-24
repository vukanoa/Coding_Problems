/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    2615) Sum of Distances
    ===========================

    ============
    Description:
    ============

    You are given a 0-indexed integer array nums. There exists an array arr of
    length nums.length, where arr[i] is the sum of |i - j| over all j such that
    nums[j] == nums[i] and j != i. If there is no such j, set arr[i] to be 0.

    Return the array arr.

    ========================================================
    FUNCTION: vector<long long> distance(vector<int>& nums);
    ========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,3,1,1,2]
    Output: [5,0,3,4,0]
    Explanation: 
    When i = 0, nums[0] == nums[2] and nums[0] == nums[3]. Therefore, arr[0] = |0 - 2| + |0 - 3| = 5. 
    When i = 1, arr[1] = 0 because there is no other index with value 3.
    When i = 2, nums[2] == nums[0] and nums[2] == nums[3]. Therefore, arr[2] = |2 - 0| + |2 - 3| = 3. 
    When i = 3, nums[3] == nums[0] and nums[3] == nums[2]. Therefore, arr[3] = |3 - 0| + |3 - 2| = 4. 
    When i = 4, arr[4] = 0 because there is no other index with value 2. 

    --- Example 2 ---
    Input: nums = [0,5,3]
    Output: [0,0,0]
    Explanation: Since each element in nums is distinct, arr[i] = 0 for all i.


    *** Constraints ***
    1 <= nums.length <= 10^5
    0 <= nums[i] <= 10^9

*/

#include <cstdlib>
#include <numeric>
#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 7.25% */
/* Space Beats: 5.00% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution_Prefix_Suffix_and_Binary_Search {
public:
    vector<long long> distance(vector<int>& nums)
    {
        const int N = nums.size();
        vector<long long> arr(N, 0LL);

        unordered_map<int, vector<long long>> num__to__indices;
        for (int i = 0; i < N; i++) // O(N)
            num__to__indices[nums[i]].push_back(i);

        unordered_map<int, vector<long long>> prefix;
        unordered_map<int, vector<long long>> suffix;

        // O(N) (entire block)
        for (const auto& [number, indices] : num__to__indices)
        {
            prefix[number] = num__to__indices[number];
            suffix[number] = num__to__indices[number];

            partial_sum(prefix[number].begin(),  prefix[number].end(),  prefix[number].begin());
            partial_sum(suffix[number].rbegin(), suffix[number].rend(), suffix[number].rbegin());
        }

        // O(N * logN) (entire block)
        for (int i = 0; i < N; i++) // O(N)
        {
            const int SIZE = num__to__indices[nums[i]].size();

            auto iter       = lower_bound(num__to__indices[nums[i]].begin(), num__to__indices[nums[i]].end(), i); // O(logN)
            long long  idx  = iter - num__to__indices[nums[i]].begin();

            long long L = idx == 0      ? 0 : abs(prefix[nums[i]][idx-1] - idx            * i);
            long long R = idx == SIZE-1 ? 0 : abs(suffix[nums[i]][idx+1] - (SIZE-1 - idx) * i);

            arr[i] = L + R;
        }

        return arr;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Linear Solution.

    This shows the general idea that you don't need to calculate both prefix
    and suffix, instead you can use calculate "suffix" while iterating through
    the prefix.

    This also makes the Soltion Linear, as we don't have a need to lower_bound
    (i.e. Binary Serach) as in the above Solution.

*/

/* Time  Beats: 91.75% */
/* Space Beats: 72.25% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solutionwer {
public:
    vector<long long> distance(vector<int>& nums)
    {
        const int N = nums.size();
        vector<long long> arr(N, 0LL);

        unordered_map<int, vector<long long>> num__to__indices;
        for (int i = 0; i < N; i++) // O(N)
            num__to__indices[nums[i]].push_back(i);

        // O(N) (entire block)
        for (auto& [num, indices] : num__to__indices)
        {
            const int SIZE = indices.size();

            if (SIZE == 1)
                continue;

            // prefix_sum[x] is the sum of all values BEFORE 'x' NON-inclusive
            vector<long long> prefix_sum(SIZE + 1, 0LL);

            for (int i = 0; i < SIZE; i++)
                prefix_sum[i+1] = prefix_sum[i] + indices[i];

            // O(SIZE) per group ---> overall O(N)
            for (int i = 0; i < SIZE; i++)
            {
                long long prefix = prefix_sum[i];
                long long suffix = prefix_sum[SIZE] - prefix_sum[i];

                long long L = abs(prefix - indices[i] * i         );
                long long R = abs(suffix - indices[i] * (SIZE - i));

                arr[indices[i]] = L + R;
            }
        }

        return arr;
    }
};
