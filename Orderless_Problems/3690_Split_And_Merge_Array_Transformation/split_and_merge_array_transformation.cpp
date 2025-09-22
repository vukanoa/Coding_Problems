/*
    ==============
    === MEDIUM ===
    ==============

    ==========================================
    3690) Split and Merge Array Transformation
    ==========================================

    ============
    Description:
    ============

    You are given two integer arrays nums1 and nums2, each of length n.
    You may perform the following split-and-merge operation on nums1 any number
    of times:

        + Choose a subarray nums1[L..R].

        + Remove that subarray, leaving the prefix nums1[0..L-1]
          (empty if L = 0) and the suffix nums1[R+1..n-1] (empty if R = n - 1).

        + Re-insert the removed subarray (in its original order) at any
          position in the remaining array (i.e., between any two elements, at
          the very start, or at the very end).

    Return the minimum number of split-and-merge operations needed to transform
    nums1 into nums2.

    ====================================================================
    FUNCTION: int minSplitMerge(vector<int>& nums1, vector<int>& nums2);
    ====================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums1 = [3,1,2], nums2 = [1,2,3]
    Output: 1
    Explanation:
        Split out the subarray [3] (L = 0, R = 0); the remaining array is [1,2].
        Insert [3] at the end; the array becomes [1,2,3].

    --- Example 2 ---
    Input: nums1 = [1,1,2,3,4,5], nums2 = [5,4,3,2,1,1]
    Output: 3
    Explanation:
        Remove [1,1,2] at indices 0 - 2; remaining is [3,4,5]; insert [1,1,2] at position 2, resulting in [3,4,1,1,2,5].
        Remove [4,1,1] at indices 1 - 3; remaining is [3,2,5]; insert [4,1,1] at position 3, resulting in [3,2,5,4,1,1].
        Remove [3,2] at indices 0 - 1; remaining is [5,4,1,1]; insert [3,2] at position 2, resulting in [5,4,3,2,1,1].

    *** Constraints ***
    2 <= n == nums1.length == nums2.length <= 6
    -10^5 <= nums1[i], nums2[i] <= 10^5
    nums2 is a permutation of nums1.

*/

#include <queue>
#include <set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Given the "astronomically small" Constraints, we SHOULD(and this is the
    ONLY Solution that works) implement it the Brute Force way.

    Please note that even with BruteForce allowed and being the only valid
    Solution -- It is difficult to implement.

    But not that difficult, you should try it yourself.

*/

/* Time  Beats: 100.00% */
/* Space Beats: 100.00% */

/* Time  Complexity: O(N! * N^3) */
/* Space Complexity: O(N!)       */
class Solution {
public:
    int minSplitMerge(vector<int>& nums1, vector<int>& nums2)
    {
        if (nums1 == nums2)
            return 0;

        int N = nums1.size();
        int result = 0;

        set<vector<int>> visited; // Visited permutations
        visited.insert(nums1);

        queue<pair<vector<int>, int>> queue;
        queue.push( {nums1, 0} ); // {permutation, step}

        while ( ! queue.empty())
        {
            vector<int> curr_permutation = queue.front().first;
            int curr_step                = queue.front().second;
            queue.pop();

            for (int start_idx = 0; start_idx < N; start_idx++)
            {
                for (int end_idx = start_idx; end_idx < N; end_idx++)
                {
                    vector<int> extracted_subarray(curr_permutation.begin() + start_idx,
                                                   curr_permutation.begin() + end_idx + 1);

                    vector<int> remaining_elements;
                    for (int prefix_idx = 0; prefix_idx < start_idx; prefix_idx++)
                        remaining_elements.push_back(curr_permutation[prefix_idx]);

                    for (int suffix_idx = end_idx + 1; suffix_idx < N; suffix_idx++)
                        remaining_elements.push_back(curr_permutation[suffix_idx]);

                    for (int reinsertion_idx = 0; reinsertion_idx <= remaining_elements.size(); reinsertion_idx++)
                    {
                        if (reinsertion_idx == start_idx)
                            continue; // Reinserting at the same place, would change anything

                        vector<int> new_permutation;

                        for (int prefix_idx = 0; prefix_idx < reinsertion_idx; prefix_idx++)
                            new_permutation.push_back(remaining_elements[prefix_idx]);

                        // Insert extracted_subarray at reinsertion_idx
                        for (int subarray_idx = 0; subarray_idx < extracted_subarray.size(); subarray_idx++)
                            new_permutation.push_back(extracted_subarray[subarray_idx]);

                        for (int suffix_idx = reinsertion_idx; suffix_idx < remaining_elements.size(); suffix_idx++)
                            new_permutation.push_back(remaining_elements[suffix_idx]);

                        if (visited.count(new_permutation))
                            continue;

                        if (new_permutation == nums2)
                        {
                            result = curr_step + 1;
                            return result;
                        }

                        visited.insert(new_permutation);
                        queue.push( {new_permutation, curr_step + 1} );
                    }
                }
            }
        }

        return result;
    }
};
