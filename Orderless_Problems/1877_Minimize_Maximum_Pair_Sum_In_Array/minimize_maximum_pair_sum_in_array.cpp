/*
    ==============
    === MEDIUM ===
    ==============

    =========================================
    1877) Minimize Maximize Pair Sum in Array
    =========================================

    ============
    Description:
    ============

    The pair sum of a pair (a,b) is equal to a + b. The maximum pair sum is the
    largest pair sum in a list of pairs.

        + For example, if we have pairs (1,5), (2,3), and (4,4), the maximum
          pair

        + sum would be max(1+5, 2+3, 4+4) = max(6, 5, 8) = 8.

    Given an array nums of even length n, pair up the elements of nums into
    n / 2 pairs such that:

        + Each element of nums is in exactly one pair, and

        + The maximum pair sum is minimized.

    Return the minimized maximum pair sum after optimally pairing up the
    elements.

    ============================================
    FUNCTION: int minPairSum(vector<int>& nums);
    ============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [3,5,2,3]
    Output: 7
    Explanation: The elements can be paired up into pairs (3,3) and (5,2).
    The maximum pair sum is max(3+3, 5+2) = max(6, 7) = 7.

    --- Example 2 ---
    Input: nums = [3,5,4,2,4,6]
    Output: 8
    Explanation: The elements can be paired up into pairs (3,5), (4,4), and
                 (6,2). The maximum pair sum is max(3+5, 4+4, 6+2) =
                 max(8, 8, 8) = 8.


    *** Constraints ***
    n == nums.length
    2 <= n <= 10^5
    n is even.
    1 <= nums[i] <= 10^5

*/

#include <algorithm>
#include <climits>
#include <cstring>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 34.42% */
/* Space Beats: 60.30% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(logN)     */ // Because that's Space Comp. of C++'s Sort
class Solution {
public:
    int minPairSum(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 0;

        /* Sort */
        sort(nums.begin(), nums.end());

        int L = 0;
        int R = N-1;
        while (L < R)
        {
            result = max(result, nums[L] + nums[R]);

            // Increment, Decrement
            L++;
            R--;
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Instead of sorting and making our BigO be O(N * logN), we can use a
    "Counting Sort" since the range is not large and thus reduce the Time
    Complexity by an order of O(logN), which makes it: O(N + K).

    Since N & K are similar values in the Constraints, it's essentially
    Linear:

        O(N + K) ~= O(N + N) ~= O(2 * N) ~= O(N)

*/

/* Time  Beats: 97.50% */
/* Space Beats:  7.43% */

/* Time  Complexity: O(N + K) */
/* Space Complexity: O(K)     */ // K is the range of nums[i]
class Solution_Linear {
private:
    static constexpr int MAX_SIZE = 1e5 + 1;
    int frequency_table[MAX_SIZE];

public:
    int minPairSum(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 0;

        /* Memset */
        memset(frequency_table, 0x00, sizeof(frequency_table)); // O(K)

        int min_elem = INT_MAX;
        int max_elem = INT_MIN;

        // O(N) (entire block)
        for (const int& num : nums)
        {
            frequency_table[num]++;

            min_elem = min(min_elem, num); // O(1)
            max_elem = max(max_elem, num); // O(1)
        }

        int L_val = min_elem;
        int R_val = max_elem;

        int pairs_remaining = N / 2;

        // O(N + K) (entire block)
        while (pairs_remaining > 0) // O(N / 2) --> O(N)
        {
            while (frequency_table[L_val] == 0) // O(K)
                L_val++;

            while (frequency_table[R_val] == 0) // O(K)
                R_val--;

            result = max(result, L_val + R_val);

            frequency_table[L_val]--;
            frequency_table[R_val]--;
            pairs_remaining--;
        }

        return result;
    }
};
