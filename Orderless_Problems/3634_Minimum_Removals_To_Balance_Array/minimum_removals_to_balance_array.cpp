/*
    ==============
    === MEDIUM ===
    ==============

    =======================================
    3634) Minimum Removals to Balance Array
    =======================================

    ============
    Description:
    ============

    You are given an integer array nums and an integer k.

    An array is considered balanced if the value of its maximum element is at
    most k times the minimum element.

    You may remove any number of elements from nums without making it empty.

    Return the minimum number of elements to remove so that the remaining array
    is balanced.

    =====
    Note: An array of size 1 is considered balanced as its maximum and minimum
          are equal, and the condition always holds true.
    =====

    ===================================================
    FUNCTION: int minRemoval(vector<int>& nums, int k);
    ===================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [2,1,5], k = 2
    Output: 1
    Explanation:
        Remove nums[2] = 5 to get nums = [2, 1].
        Now max = 2, min = 1 and max <= min * k as 2 <= 1 * 2. Thus, the answer is 1.


    --- Example 2 ---
    Input: nums = [1,6,2,9], k = 3
    Output: 2
    Explanation:
        Remove nums[0] = 1 and nums[3] = 9 to get nums = [6, 2].
        Now max = 6, min = 2 and max <= min * k as 6 <= 2 * 3. Thus, the answer is 2.


    --- Example 3 ---
    Input: nums = [4,6], k = 2
    Output: 0
    Explanation:
        Since nums is already balanced as 6 <= 4 * 2, no elements need to be removed.


    *** Constraints ***
    1 <= nums.length <= 10^5
    1 <= nums[i] <= 10^9
    1 <= k <= 10^5

*/

#include <algorithm>
#include <vector>
using namespace std;


/*
    ------------
    --- IDEA ---
    ------------

    First, we must sort, that is absolutely obvious and clear. Especially
    since the Constraints for N are: 10^5.

    Once we sort, we can try to consider EACH element as a starting element in
    a new VALID array.

    Meaning "if we begin our VALID array HERE(at this idx), what is the total
    number of elements we need to get rid of in order to obtain a valid array?"

    We do that by starting at EACH index(except the last since by strating at
    the very last idx, we're destined to to remove all the previous ones, so
    we don't need to calculate that) and checking how many need to be removed
    in order to have a VALID array.

    We're moving our "L"(i.e. "left" pointer) until we're left with a valid
    array.

    We want to take the minimum of all of the removals.

*/

/* Time  Beats: 79.65% */
/* Space Beats: 52.91% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(logN)     */ // Space Complexity of C++'s Intro-Sort
class Solution_Inner_Linear {
public:
    int minRemoval(vector<int>& nums, int k)
    {
        const int N = nums.size();
        int result = N;

        /* Sort in ASCENDING order */
        sort(nums.begin(), nums.end()); // O(N * logN)

        if (1LL * nums[N-1] <= 1LL * nums[0] * k)
            return 0;

        int L = 0;
        int R = 0;
        while (R < N)
        {
            while (L < R && ! is_balanced(nums[L], k, nums[R]))
                L++;

            int valid_window_len = R - L + 1;
            result = min(result, N - valid_window_len);

            // Increment
            R++;
        }

        return result;
    }

private:
    bool is_balanced(int& min, int&k, int& max)
    {
        return 1LL * max <= 1LL * min * k;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    First, we must sort, that is absolutely obvious and clear. Especially
    since the Constraints for N are: 10^5.

    Once we sort, we can try to consider EACH element as a starting element in
    a new VALID array.

    Meaning "if we begin our VALID array HERE(at this idx), what is the total
    number of elements we need to get rid of in order to obtain a valid array?"

    We do that by starting at EACH index(except the last since by strating at
    the very last idx, we're destined to to remove all the previous ones, so
    we don't need to calculate that) and checking how many need to be removed
    in order to have a VALID array.

    Since we've already sorted the array, we can use Binary Search to obtain
    this result more quickly.

*/

/* Time  Beats: 14.24% */
/* Space Beats: 86.83% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution_Binary_Search {
public:
    int minRemoval(vector<int>& nums, int k)
    {
        const int N = nums.size();
        int result = N-1;

        /* Sort in ASCENDING order */
        sort(nums.begin(), nums.end()); // O(N * logN)

        /* O(N * logN) */
        for (int L = 0; L < N-1; L++)
        {
            long long max_val = 1LL * nums[L] * k;
            auto iter = upper_bound(nums.begin() + L, nums.end(), max_val);

            int first_exceeding = distance(nums.begin(), iter);

            int needed_removals = (L - 0) + (N - first_exceeding);
            result = min(result, needed_removals);
        }

        return result;
    }
};
