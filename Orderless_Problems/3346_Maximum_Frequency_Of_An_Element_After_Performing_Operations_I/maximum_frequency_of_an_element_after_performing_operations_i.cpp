/*
    ==============
    === MEDIUM ===
    ==============

    ===================================================================
    3346) Maximum Frequency of an Element After Performing Operations I
    ===================================================================

    ============
    Description:
    ============

    You are given an integer array nums and two integers k and numOperations.

    You must perform an operation numOperations times on nums, where in each
    operation you:

        Select an index i that was not selected in any previous operations.
        Add an integer in the range [-k, k] to nums[i].

    Return the maximum possible frequency of any element in nums after
    performing the operations.

    ========================================================================
    FUNCTION: int maxFrequency(vector<int>& nums, int k, int numOperations);
    ========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,4,5], k = 1, numOperations = 2
    Output: 2
    Explanation:
    We can achieve a maximum frequency of two by:
    Adding 0 to nums[1]. nums becomes [1, 4, 5].
    Adding -1 to nums[2]. nums becomes [1, 4, 4].


    --- Example 2 ---
    Input: nums = [5,11,20,20], k = 5, numOperations = 1
    Output: 2
    Explanation:
    We can achieve a maximum frequency of two by:
    Adding 0 to nums[1].


    *** Constraints ***
    1 <= nums.length <= 10^5
    1 <= nums[i] <= 10^5
    0 <= k <= 10^5
    0 <= numOperations <= nums.length

*/

#include <algorithm>
#include <set>
#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 65.20% */
/* Space Beats: 58.21% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n)        */
class Solution {
public:
    int maxFrequency(vector<int>& nums, int k, int numOperations)
    {
        const int n = nums.size();
        int result = 0;

        int left  = 0;
        int right = 0;

        // Sort the array for sliding window approach
        sort(nums.begin(), nums.end());

        // HashMap to store frequency of each number
        unordered_map<int, int> count;
        for (int num : nums)
            count[num]++;

        // First pass: choose an existing number as the reference point
        for (int mid = 0; mid < n; mid++)
        {
            // Adjust left pointer to keep nums[mid] - nums[left] within `k`
            while (nums[mid] - nums[left] > k)
                left++;

            // Adjust right pointer to keep nums[right] - nums[mid] within `k`
            while (right < n-1 && nums[right + 1] - nums[mid] <= k)
                right++;

            int total = right - left + 1; // Calculate range size

            // Update result with maximum achievable frequency for nums[mid] as the target
            result = max(result, min(total - count[nums[mid]], numOperations) + count[nums[mid]]);
        }

        // Second pass: choose a non-existent number as reference point
        left = 0;
        for (right = 0; right < n; right++)
        {
            int mid = (nums[left] + nums[right]) / 2;  // Calculate hypothetical midpoint

            // Adjust left pointer to ensure midpoint is within `k` range from both ends
            while (mid - nums[left] > k || nums[right] - mid > k)
            {
                left++;
                mid = (nums[left] + nums[right]) / 2;
            }

            // Update result with maximum achievable frequency with the hypothetical midpoint
            result = max(result, min(right - left + 1, numOperations));
        }

        return result;
    }
};
class Solution_2 {
public:
    int maxFrequency(vector<int>& nums, int k, int numOperations)
    {
        const int N = nums.size();

        /* Sort */
        sort(nums.begin(), nums.end());

        int result = 0;
        unordered_map<int, int> num_count;

        int last_num_idx = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] != nums[last_num_idx])
            {
                num_count[nums[last_num_idx]] = i - last_num_idx;
                result = max(result, i - last_num_idx);
                last_num_idx = i;
            }
        }

        num_count[nums[last_num_idx]] = N - last_num_idx;
        result = max(result, N - last_num_idx);

        auto left_bound = [&](int value) {
            int left = 0, right = nums.size() - 1;
            while (left < right) {
                int mid = (left + right) / 2;
                if (nums[mid] < value) {
                    left = mid + 1;
                } else {
                    right = mid;
                }
            }
            return left;
        };

        auto right_bound = [&](int value) {
            int left = 0, right = nums.size() - 1;
            while (left < right) {
                int mid = (left + right + 1) / 2;
                if (nums[mid] > value) {
                    right = mid - 1;
                } else {
                    left = mid;
                }
            }
            return left;
        };

        for (int i = nums.front(); i <= nums.back(); i++)
        {
            int L = left_bound(i - k);
            int R = right_bound(i + k);

            int tmp_result;
            if (num_count.count(i))
                tmp_result = min(R - L + 1, num_count[i] + numOperations);
            else
                tmp_result = min(R - L + 1, numOperations);

            result = max(result, tmp_result);
        }

        return result;
    }
};



/*
    ------------
    --- IDEA ---
    ------------

    TODO
    (Sweep Line)

*/

/* Time  Beats:  9.94% */
/* Space Beats: 14.53% */

/* Time  Complexity: O(n + p * logp) */
/* Space Complexity: O(n + p) */
class Solution_Sweep_Line {
public:
    int maxFrequency(vector<int>& nums, int k, int numOperations)
    {
        int result = 1;

        unordered_map<int,int> counter;
        unordered_map<int,int> sweep;
        set<int> points;

        for(auto& num : nums)
        {
            counter[num]++;

            sweep[num - k]++;
            sweep[num + k + 1]--;

            points.insert(num);
            points.insert(num - k);
            points.insert(num + k + 1);
        }

        int sum = 0;
        for (auto& num : points)
        {
            sum += sweep[num];
            result = max(result, counter[num] + min(sum - counter[num], numOperations));
        }

        return result;
    }
};
