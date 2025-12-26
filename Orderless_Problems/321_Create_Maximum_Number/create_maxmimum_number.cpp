/*
    ============
    === HARD ===
    ============

    ===========================
    321) Create Maximum Number
    ===========================

    ============
    Description:
    ============

    You are given two integer arrays nums1 and nums2 of lengths m and n
    respectively. nums1 and nums2 represent the digits of two numbers. You are
    also given an integer k.

    Create the maximum number of length k <= m + n from digits of the two
    numbers. The relative order of the digits from the same array must be
    preserved.

    Return an array of the k digits representing the answer.

    ===============================================================================
    FUNCTION: vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k);
    ===============================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums1 = [3,4,6,5], nums2 = [9,1,2,5,8,3], k = 5
    Output: [9,8,6,5,3]

    --- Example 2 ---
    Input: nums1 = [6,7], nums2 = [6,0,4], k = 5
    Output: [6,7,6,0,4]

    --- Example 3 ---
    Input: nums1 = [3,9], nums2 = [8,9], k = 3
    Output: [9,8,9]


    *** Constraints ***
    m == nums1.length
    n == nums2.length
    1 <= m, n <= 500
    0 <= nums1[i], nums2[i] <= 9
    1 <= k <= m + n
    nums1 and nums2 do not have leading zeros.

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 14.40% */
/* Space Beats:  7.48% */

/* Time  Complexity: O(K * (N + M + K)) */
/* Space Complexity: O(K)               */
class Solution {
private:
    vector<int> select_max_subsequence(vector<int>& values, int required_length)
    {
        vector<int> selected_indices;
        int total_length = values.size();

        for (int index = 0; index < total_length; index++)
        {
            while(! selected_indices.empty()
                  && values[index] > values[selected_indices.back()]
                  && static_cast<int>(selected_indices.size()) + (total_length - index) > required_length)
            {
                selected_indices.pop_back();
            }

            if (static_cast<int>(selected_indices.size()) < required_length)
                selected_indices.push_back(index);
        }

        // Convert indices to actual values
        for (int& idx : selected_indices)
            idx = values[idx];

        return selected_indices;
    }

public:
    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k)
    {
        vector<int> best_result(k, 0);

        int size_1 = nums1.size();
        int size_2 = nums2.size();

        for (int picked_from_1 = 0; picked_from_1 <= k; picked_from_1++)
        {
            int picked_from_2 = k - picked_from_1;

            if (picked_from_1 > size_1 || picked_from_2 > size_2)
                continue;

            vector<int> best_subsequence_1 = select_max_subsequence(nums1, picked_from_1);
            vector<int> best_subsequence_2 = select_max_subsequence(nums2, picked_from_2);

            vector<int> merged_sequence;
            int index_1 = 0;
            int index_2 = 0;

            while (index_1 < best_subsequence_1.size() &&
                   index_2 < best_subsequence_2.size())
            {
                if (best_subsequence_1[index_1] > best_subsequence_2[index_2])
                {
                    merged_sequence.push_back(best_subsequence_1[index_1++]);
                }
                else if(best_subsequence_1[index_1] < best_subsequence_2[index_2])
                {
                    merged_sequence.push_back(best_subsequence_2[index_2++]);
                }
                else
                {
                    vector<int> remaining_1(best_subsequence_1.begin() + index_1, best_subsequence_1.end());
                    vector<int> remaining_2(best_subsequence_2.begin() + index_2, best_subsequence_2.end());

                    if (remaining_1 > remaining_2)
                    {
                        merged_sequence.push_back(best_subsequence_1[index_1++]);
                    }
                    else
                    {
                        merged_sequence.push_back(best_subsequence_2[index_2++]);
                    }
                }
            }

            while (index_1 < best_subsequence_1.size())
            {
                merged_sequence.push_back(best_subsequence_1[index_1++]);
            }

            while (index_2 < best_subsequence_2.size())
            {
                merged_sequence.push_back(best_subsequence_2[index_2++]);
            }

            // Compare merged_sequence with best_result lexicographically
            bool should_update = true;
            for (int position = 0; position < k; position++)
            {
                if (merged_sequence[position] > best_result[position])
                {
                    should_update = true;
                    break;
                }
                else if (merged_sequence[position] < best_result[position])
                {
                    should_update = false;
                    break;
                }
            }

            if (should_update)
                best_result = merged_sequence;
        }

        return best_result;
    }
};
