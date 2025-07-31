/*
    ============
    === HARD ===
    ============

    ====================================
    995) Number of Consectuive Bit Flips
    ====================================

    ============
    Description:
    ============

    You are given a binary array nums and an integer k.

    A k-bit flip is choosing a subarray of length k from nums and
    simultaneously changing every 0 in the subarray to 1, and every 1 in the
    subarray to 0.

    Return the minimum number of k-bit flips required so that there is no 0 in
    the array. If it is not possible, return -1.

    A subarray is a contiguous part of an array.

    =====================================================
    FUNCTION: int minKBitFlips(vector<int>& nums, int k);
    =====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [0,1,0], k = 1
    Output: 2
    Explanation: Flip nums[0], then flip nums[2].

    --- Example 2 ---
    Input: nums = [1,1,0], k = 2
    Output: -1
    Explanation: No matter how we flip subarrays of size 2, we cannot make the
    array become [1,1,1].

    --- Example 3 ---
    Input: nums = [0,0,0,1,0,1,1,0], k = 3
    Output: 3
    Explanation:
    Flip nums[0],nums[1],nums[2]: nums becomes [1,1,1,1,0,1,1,0]
    Flip nums[4],nums[5],nums[6]: nums becomes [1,1,1,1,1,0,0,0]
    Flip nums[5],nums[6],nums[7]: nums becomes [1,1,1,1,1,1,1,1]


    *** Constraints ***
    1 <= nums.length <= 10^5
    1 <= k <= nums.length

*/

#include <deque>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 96.31% */
/* Space Beats: 81.35% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Auxiliary_Array {
public:
    int minKBitFlips(vector<int>& nums, int k)
    {
        const int N = nums.size();

        vector<bool> flipped(N - k + 1, 0);
        int count  = 0;
        int flip_x = 0;

        for (int i = 0; i < N; i++)
        {
            if (i >= k)
                flip_x -= flipped[i - k];

            if ((flip_x & 1) == nums[i])
            {
                if (i + k > N)
                    return -1;

                flipped[i] = 1;

                flip_x++;
                count++;
            }
        }

        return count;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 11.19% */
/* Space Beats: 40.49% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    int minKBitFlips(vector<int>& nums, int k)
    {
        int N = nums.size();
        int result = 0;

        deque<int> flip_queue;
        int flipped = 0; // Initially false

        for (int i = 0; i < N; i++)
        {
            if (i >= k)
            {
                flipped ^= flip_queue.front();
                flip_queue.pop_front();
            }

            if (flipped == nums[i])
            {
                if (i + k > N)
                    return -1;

                flip_queue.push_back(1);

                flipped ^= 1;
                result += 1;
            }
            else
            {
                flip_queue.push_back(0);
            }
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

/* Time  Beats: 50.54% */
/* Space Beats: 89.38% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Space_Efficient {
public:
    int minKBitFlips(vector<int>& nums, int k)
    {
        const int N = nums.size();
        int result = 0;

        int curr_flips = 0;
        for (int i = 0; i < N; ++i)
        {
            if (i >= k && nums[i - k] == 2)
                curr_flips--;

            if ((curr_flips % 2) == nums[i])
            {
                if (i + k > N)
                    return -1;

                nums[i] = 2;
                curr_flips++;
                result++;
            }
        }

        return result;
    }
};
