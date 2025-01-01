/*
    ==============
    === MEDIUM ===
    ==============

    ================================
    3404) Count Special Subsequences
    ================================

    ============
    Description:
    ============

    You are given an array nums consisting of positive integers.

    A special subsequence is defined as a subsequence of length 4, represented
    by indices (p, q, r, s), where p < q < r < s. This subsequence must satisfy
    the following conditions:

        nums[p] * nums[r] == nums[q] * nums[s]

    There must be at least one element between each pair of indices. In other
    words, q - p > 1, r - q > 1 and s - r > 1.

    A subsequence is a sequence derived from the array by deleting zero or more
    elements without changing the order of the remaining elements.

    Return the number of different special subsequences in nums.

    ============================================================
    FUNCTION: long long numberOfSubsequences(vector<int>& nums);
    ============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,3,4,3,6,1]
    Output: 1
    Explanation:
    There is one special subsequence in nums.
        (p, q, r, s) = (0, 2, 4, 6):
            This corresponds to elements (1, 3, 3, 1).
            nums[p] * nums[r] = nums[0] * nums[4] = 1 * 3 = 3
            nums[q] * nums[s] = nums[2] * nums[6] = 3 * 1 = 3


    --- Example 2 ---
    Input: nums = [3,4,3,4,3,4,3,4]
    Output: 3
    Explanation:
    There are three special subsequences in nums.
        (p, q, r, s) = (0, 2, 4, 6):
            This corresponds to elements (3, 3, 3, 3).
            nums[p] * nums[r] = nums[0] * nums[4] = 3 * 3 = 9
            nums[q] * nums[s] = nums[2] * nums[6] = 3 * 3 = 9
        (p, q, r, s) = (1, 3, 5, 7):
            This corresponds to elements (4, 4, 4, 4).
            nums[p] * nums[r] = nums[1] * nums[5] = 4 * 4 = 16
            nums[q] * nums[s] = nums[3] * nums[7] = 4 * 4 = 16
        (p, q, r, s) = (0, 2, 5, 7):
            This corresponds to elements (3, 3, 4, 4).
            nums[p] * nums[r] = nums[0] * nums[5] = 3 * 4 = 12
            nums[q] * nums[s] = nums[2] * nums[7] = 3 * 4 = 12


    *** Constraints ***
    7 <= nums.length <= 1000
    1 <= nums[i] <= 1000

*/

#include <unordered_map>
#include <vector>
using namespace std;

class Solution_TLE {
public:
    long long numberOfSubsequences(vector<int>& nums)
    {
        const int N = nums.size();
        long long result = 0;


        vector<unordered_map<int,int>> dp(N, unordered_map<int,int>());
        dp[0][nums[0]]++;

        for (int i = 1; i < N; i++)
        {
            dp[i] = dp[i-1];
            dp[i][nums[i]]++;
        }

        for (int s = N-1; s-6 >= 0; s--)
        {
            for (int r = s-2; r-4 >= 0; r--)
            {
                for (int q = r-2; q-2 >= 0; q--)
                {
                    for (int p = q-2; p >= 0; p--)
                    {
                        if (nums[p] * nums[r] == nums[q] * nums[s])
                            result++;
                    }
                }
            }
        }

        return result;
    }
};




class Solution_Optimized_But_Still_TLE {
public:
    long long numberOfSubsequences(vector<int>& nums)
    {
        const int N = nums.size();
        long long result = 0;


        vector<unordered_map<int,int>> dp(N, unordered_map<int,int>());
        dp[0][nums[0]]++;

        for (int i = 1; i < N; i++)
        {
            dp[i] = dp[i-1];
            dp[i][nums[i]]++;
        }

        for (int s = N-1; s-6 >= 0; s--)
        {
            for (int r = s-2; r-4 >= 0; r--)
            {
                for (int q = r-2; q-2 >= 0; q--)
                {
                    if (dp[q-2].find(nums[q] * nums[s] / nums[r]) != dp[q-2].end())
                        result += dp[q-2][nums[q] * nums[s] / nums[r]];
                }
            }
        }

        return result;
    }
};

/*
    ------------
    --- IDEA ---
    ------------

    Looking at two attempts of Solution above you'll realize that O(n^4) is
    not efficient enough. But you'll always realize that O(n^3) is not
    efficient enough, so how can we do better?

    If you get the optimization from O(n^4) down to O(n^3), then this one
    shouldn't be any more difficult, it only requires a bit more "noticing".

    Keep in mind that this is what is required:

        nums[p] * nums[r] == nums[q] * nums[s]

        where: p < q < r < s

    In the above Solution, Optimized_But_Still_TLE we've tried to optimize it
    like this:

        nums[p] = nums[q] * nums[s] / nums[r]

    That way we didn't need to go through all 'p' indices.

    However, can you see that we can order it in another way?
    We can do this:

       nums[p] / nums[q] == nums[s] / nums[r]

    This way it seems as if we would still need to have O(N^4), but you would
    be mistaken.

    We can iterate with 'r' pointer, beginning at 3 and going up to N-2,
    non-inclusive, thorugh all of its possibilities.

    However, now we can FIX our 'q' pointer and then we can only iterate our
    'p' pointer on the left side, up until the 'q' index.

    And we can iterate our 's' pointer from current 'r' up until the end.

    This way it is O(n^2). however how are we making this work?

    The key is to notice that:

            nums[p] * nums[r] == nums[q] * nums[s]

        is the same as this:

           nums[p] / nums[q] == nums[s] / nums[r]

    It seems weird but bear with me. This way we can use a HashMap "counter" to
    count all of "nums[p] / nums[q]" as a double value.

    Now all we have to do, after we've done that, is try to see if there are
    any "nums[s] / nums[r]" is our Hashmap "counter".

    If there are, we just add how frequent this quiotient were.
    That's literally it.

    This way we can do it in O(n^2 instead of (n^3), or God forbid, O(n^4).

    It's not super intuitive, but it's not too bad. If you've succeded to write
    O(n^3), then given enough time you'd come up with this O(n^2) as well.

    If you've seen this "trick", then you'd come up with it pretty quickly.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  40.00% */

/* Time  Complexity: O(n^2) */
/* Space Complexity: O(n)   */
class Solution {
public:
    long long numberOfSubsequences(vector<int>& nums)
    {
        const int N = nums.size();
        const int LAST_ELEM = N-1;

        long long result = 0;
        unordered_map<double, int> counter;


        for (int r = 3; r < LAST_ELEM - 1; r++)
        {
            int q = r-2;

            for (int p = 0; p < q-1; p++)
                counter[1.0 * nums[p] / nums[q]]++;

            for (int s = r+2; s < N; s++)
                result += counter[1.0 * nums[s] / nums[r]];
        }

        return result;
    }
};
