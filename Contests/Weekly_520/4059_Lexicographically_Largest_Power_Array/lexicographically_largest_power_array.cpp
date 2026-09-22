/*
    ============
    === HARD ===
    ============

    ===========================================
    4059) Lexicographically Largest Power Array
    ===========================================

    ============
    Description:
    ============

    You are given an integer array nums of length n. You may rearrange its
    elements to form any permutation "perm".

    Define an array power of length 15. For each 0 <= i < 15, power[i] is the
    largest integer j, where 0 <= j <= n, such that the first j elements of
    perm all have the (14 - i)th bit set.

    Bit positions are indexed from right to left, starting with the 0th bit.

    Return the lexicograpihcally largest possible power array.

    ======================================================
    FUNCTION: vector<int> largestPower(vector<int>& nums);
    ======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [7,5]
    Output: [0,0,0,0,0,0,0,0,0,0,0,0,2,1,2]
    Explanation:
    Choose perm = [7, 5].
        Both elements have bit 2 set, so power[12] = 2.
        The first element has bit 1 set, but the second does not, so power[13] = 1.
        Both elements have bit 0 set, so power[14] = 2.
    All higher bits are unset in the first element, so the remaining entries are 0.


    --- Example 2 ---
    Input: nums = [3,1,7]
    Output: [0,0,0,0,0,0,0,0,0,0,0,0,1,2,3]
    Explanation:
    Choose perm = [7, 3, 1].
        The first element has bit 2 set, but the second does not, so power[12] = 1.
        The first two elements have bit 1 set, but the third does not, so power[13] = 2.
        All three elements have bit 0 set, so power[14] = 3.
    All higher bits are unset in the first element, so the remaining entries are 0.


    *** Constraints ***
    1 <= nums.length <= 5 * 10^4
    0 <= nums[i] < 2^15

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 68.56% */
/* Space Beats: 65.72% */

/* Time  Complexity: O(15 * N) */
/* Space Complexity: O(15 * N) */
class Solution_Recursive {
private:
    const int MAX_BITS = 15;

    vector<int> result;
    vector<bool> is_done;

public:
    vector<int> largestPower(vector<int>& nums)
    {
        result.assign(MAX_BITS, 0);
        is_done.assign(MAX_BITS, false);

        maximize_power(nums, 0);

        return result;
    }


    void maximize_power(const vector<int>& nums, int ith_bit)
    {
        if (ith_bit == 15)
            return;

        if (is_done[ith_bit])
        {
            maximize_power(nums, ith_bit + 1);
            return;
        }

        vector<int> L;
        vector<int> R;

        for (const int& num : nums)
        {
            if (num & (1 << (14 - ith_bit)))
                L.push_back(num);
            else
                R.push_back(num);
        }


        if ( ! L.empty())
        {
            result[ith_bit] += L.size();
            maximize_power(L, ith_bit + 1);
        }

        if ( ! R.empty())
        {
            is_done[ith_bit] = true;
            maximize_power(R, ith_bit + 1);
        }
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 49.66% */
/* Space Beats:  7.29% */

/* Time  Complexity: O(15 * N) */
/* Space Complexity: O(15 * N) */
class Solution_Iterative {
private:
    const int MAX_BITS = 15;

    vector<int> result;
    vector<bool> is_done;

public:
    vector<int> largestPower(vector<int>& nums)
    {
        const int N = nums.size();

        result.assign(MAX_BITS, 0);
        is_done.assign(MAX_BITS, false);

        vector<vector<int>> groups = { nums };

        for (int ith_bit = 0; ith_bit < MAX_BITS; ith_bit++)
        {
            vector<vector<int>> next_groups;

            for (const auto& group : groups)
            {
                if (is_done[ith_bit])
                {
                    next_groups.push_back(group);
                    continue;
                }

                vector<int> set_bit_group;
                vector<int> unset_bit_group;

                for (const int& num : group)
                {
                    if (num & (1 << (14 - ith_bit)))
                        set_bit_group.push_back(num);
                    else
                        unset_bit_group.push_back(num);
                }

                if ( ! set_bit_group.empty())
                {
                    result[ith_bit] += set_bit_group.size();
                    next_groups.push_back(set_bit_group);
                }

                if ( ! unset_bit_group.empty())
                {
                    is_done[ith_bit] = true;
                    next_groups.push_back(unset_bit_group);
                }
            }

            groups = next_groups;
        }

        return result;
    }
};
