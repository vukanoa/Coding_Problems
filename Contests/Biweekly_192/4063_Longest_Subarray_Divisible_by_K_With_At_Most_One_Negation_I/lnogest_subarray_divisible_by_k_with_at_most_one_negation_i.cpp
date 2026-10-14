/*
    ==============
    === MEDIUM ===
    ==============

    =================================================================
    4063) Longest Subarray Divisible by K with At Most One Negation I
    =================================================================

    ============
    Description:
    ============

    You are given an integer array nums and an integer k.

    A subarray is valid if its sum is divisible by k, or can become divisible
    by k by negating one element within that subarray.

    Negating an element means replacing its value x with -x.

    Return the length of the longest valid subarray. If no valid subarray
    exists, return 0.

    ========================================================
    FUNCTION: int longestSubarray(vector<int>& nums, int k);
    ========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [4,1,2], k = 3
    Output: 3
    Explanation:
        + The sum of the entire array is 7, and 7 % 3 = 1, so it is not
          divisible by k = 3.

        + Negating nums[2] = 2 changes the sum to 4 + 1 − 2 = 3, which is
          divisible by k.

        + Therefore, the entire array is a valid subarray, giving a length of 3


    --- Example 2 ---
    Input: nums = [5,3,4], k = 7
    Output: 2
    Explanation:
        + The sum of the entire array is 12, and negating any one of its
          elements does not make its sum divisible by 7.

        + However, the subarray [3, 4] has a sum of 7, which is divisible by k
          = 7 without any negation.

        + Therefore, the longest valid subarray has a length of 2.


    --- Example 3 ---
    Input: nums = [2,2,5], k = 6
    Output: 2
    Explanation:
        + The sum of the entire array is 9, and negating any one of its
          elements does not make its sum divisible by 6.

        + The subarray [2, 2] has a sum of 4. Negating either element changes
          it to [-2, 2] or [2, -2], both of which have a sum of 0.

        + Therefore, the longest valid subarray has a length of 2.



    *** Constraints ***
    1 <= nums.length <= 1000
    -10^5 <= nums[i] <= 10^5
    1 <= k <= 10^5

*/

#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

class Solution_qqq {
public:
    int longestSubarray(vector<int>& nums, int k)
    {
        const int N = nums.size();
        int result = 0;

        for (int left = 0; left < N; left++)
        {
            long long sum = 0LL;

            unordered_map<int, int> freq;
            for (int right = left; right < N; right++)
            {
                sum += nums[right];

                int mod_2num  = ((2 * nums[right]) % k + k) % k;
                int right_mod = ((sum % k) + k ) % k;
                ++freq[mod_2num];

                bool is_valid = false;
                if (right_mod == 0)
                    is_valid = true;
                else if (freq.count(right_mod))
                    is_valid = true;

                if (is_valid)
                    result = max(result, right - left + 1);
            }
        }

        

        return result;
    }
};

/*
    ------------
    --- IDEA ---
    ------------

    case 1 = sum      % k == 0
    case 2 = (sum-2x) % k == 0 =====> sum % k = 2x % k

    We need the LONGEST subarray which can be made divisible by k.

    For any subarray, let its sum be 'S'.
    There are exactly 2 possibilities.

    Case 1: We don't negate anything

        If (S % k == 0)
            the subarray is already valid.


    Case 2: We negate one element

        Suppose we choose an element x.

        Before negating:

            ... + x + ...


        After negating:

            ... - x + ...


        The sum decreases by:

            x - (-x) = 2x

        Therefore the new sum is:

            S - 2x



        We want it divisible by k:

            (S - 2x) % k == 0


        Rearranging:

            S % k == (2x) % k



    This is the main observation.
    So instead of actually negating every element, we only need to ask:

        Does this subarray contain an element x whose (2*x) % k equals the
        current sum's remainder?




    Why unordered_set?

    For every current subarray [i...j], we store:

        (2 * nums[x]) % k

    for every element x inside that subarray.


    Then for the current sum:

        sum = S % k

    we simply check:

        Does sum exist in the set?


    If yes, then some element CAN be negated and make the sum divisible by k.

    We don't care which element gives the required remainder.
    We only care whether at least one such element exists.

    That's exactly what unordered_set is useful for.

    Why not store the actual elements?
    Because the condition is not:

        x == something

    It is:

        (2*x) % k == S % k

    So we store the remainder that matters.

*/

/* Time  Beats: 24.23% */
/* Space Beats: 62.35% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(k)   */
class Solution {
public:
    int longestSubarray(vector<int>& nums, int k) {
        
        const int N = nums.size();
        int result = 0;

        for (int i = 0; i < N; i++)
        {
            unordered_set<int> seen;
            long long prefix_sum = 0LL;

            for (int j = i; j < N; j++)
            {
                prefix_sum += nums[j];

                long long remove = ((2LL * nums[j]) % k + k) % k;
                seen.insert(remove);

                long long sum = ((prefix_sum % k) + k) % k;

                if (sum == 0 || seen.find(sum) != seen.end())
                    result = max(result , j - i + 1);

            }
        }

        return result;

    }
};
