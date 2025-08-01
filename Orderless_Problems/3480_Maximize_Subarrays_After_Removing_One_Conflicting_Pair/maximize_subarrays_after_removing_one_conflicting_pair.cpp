/*
    ============
    === HARD ===
    ============

    ============================================================
    3480) Maximize Subarrays After Removing One Conflicting Pair
    ============================================================

    ============
    Description:
    ============

    You are given an integer n which represents an array nums containing the
    numbers from 1 to n in order. Additionally, you are given a 2D array
    conflictingPairs, where conflictingPairs[i] = [a, b] indicates that a and b
    form a conflicting pair.

    Remove exactly one element from conflictingPairs. Afterward, count the
    number of non-empty subarrays of nums which do not contain both a and b for
    any remaining conflicting pair [a, b].

    Return the maximum number of subarrays possible after removing exactly one
    conflicting pair.

    ================================================================================
    FUNCTION: long long maxSubarrays(int n, vector<vector<int>>& conflicting_pairs);
    ================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 4, conflictingPairs = [[2,3],[1,4]]
    Output: 9
    Explanation:
        Remove [2, 3] from conflictingPairs. Now, conflictingPairs = [[1, 4]].
        There are 9 subarrays in nums where [1, 4] do not appear together.
        They are [1], [2], [3], [4], [1, 2], [2, 3], [3, 4], [1, 2, 3] and [2, 3, 4].
        The maximum number of subarrays we can achieve after removing one element
        from conflictingPairs is 9.


    --- Example 2 ---
    Input: n = 5, conflictingPairs = [[1,2],[2,5],[3,5]]
    Output: 12
    Explanation:
        Remove [1, 2] from conflictingPairs. Now, conflictingPairs = [[2, 5], [3, 5]].
        There are 12 subarrays in nums where [2, 5] and [3, 5] do not appear together.
        The maximum number of subarrays we can achieve after removing one element
        from conflictingPairs is 12.


    *** Constraints ***
    2 <= n <= 10^5
    1 <= conflictingPairs.length <= 2 * n
    conflictingPairs[i].length == 2
    1 <= conflictingPairs[i][j] <= n
    conflictingPairs[i][0] != conflictingPairs[i][1]

*/

#include <algorithm>
#include <climits>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    The implementation looks weird with these ridiculously long names, however
    it is MUCH easier to read and grasp what's going on in some more
    challenging problem lke this one, if we use these kind of naming.

*/

/* Time  Beats: 80.81% */
/* Space Beats: 89.53% */

/* Time  Complexity: O(N + M) */ // Where M is the number of conflicting pairs
/* Space Complexity: O(N)     */
class Solution {
public:
    long long maxSubarrays(int n, vector<vector<int>>& conflicting_pairs)
    {
        vector<int> earliest_conflict_end       (n + 1, INT_MAX);
        vector<int> second_earliest_conflict_end(n + 1, INT_MAX);

        for (const auto& pair : conflicting_pairs)
        {
            int start_index = min(pair[0], pair[1]);
            int end_index   = max(pair[0], pair[1]);

            if (earliest_conflict_end[start_index] > end_index)
            {
                second_earliest_conflict_end[start_index] = earliest_conflict_end[start_index];
                earliest_conflict_end[start_index] = end_index;
            }
            else if (second_earliest_conflict_end[start_index] > end_index)
            {
                second_earliest_conflict_end[start_index] = end_index;
            }
        }

        long long total_valid_subarrays = 0;
        int idx_of_min_conflict_start = n;
        int curr_second_earliest_conflict_end = INT_MAX;

        vector<long long> deletable_subarray_counts(n + 1, 0);

        for (int curr_start = n; curr_start >= 1; curr_start--)
        {
            if (earliest_conflict_end[idx_of_min_conflict_start] > earliest_conflict_end[curr_start])
            {
                curr_second_earliest_conflict_end = min(curr_second_earliest_conflict_end, earliest_conflict_end[idx_of_min_conflict_start]);
                idx_of_min_conflict_start = curr_start;
            }
            else
            {
                curr_second_earliest_conflict_end = min(curr_second_earliest_conflict_end, earliest_conflict_end[curr_start]);
            }

            int first_conflict_pos = min(earliest_conflict_end[idx_of_min_conflict_start], n + 1);
            total_valid_subarrays += first_conflict_pos - curr_start;

            int second_conflict_pos = min(min(curr_second_earliest_conflict_end, second_earliest_conflict_end[idx_of_min_conflict_start]), n + 1);
            deletable_subarray_counts[idx_of_min_conflict_start] += second_conflict_pos - first_conflict_pos;
        }

        return total_valid_subarrays + *max_element(deletable_subarray_counts.begin(), deletable_subarray_counts.end());
    }
};
