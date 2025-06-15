/*
    ==============
    === MEDIUM ===
    ==============

    =================================================================
    3584) Maximum Product of First and Last Elements of a Subsequence
    =================================================================

    ============
    Description:
    ============

    You are given an integer array nums and an integer m.

    Return the maximum product of the first and last elements of any
    subsequence of nums of size m.

    =============================================================
    FUNCTION: long long maximumProduct(vector<int>& nums, int m);
    =============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [-1,-9,2,3,-2,-3,1], m = 1
    Output: 81
    Explanation: The subsequence [-9] has the largest product of the first and
                 last elements: -9 * -9 = 81. Therefore, the answer is 81.

    --- Example 2 ---
    Input: nums = [1,3,-5,5,6,-4], m = 3
    Output: 20
    Explanation: The subsequence [-5, 6, -4] has the largest product of the
                 first and last elements.

    --- Example 3 ---
    Input: nums = [2,-1,2,-6,5,2,-5,7], m = 2
    Output: 35
    Explanation: The subsequence [5, 7] has the largest product of the first
                 and last elements.


    *** Constraints ***
    1 <= nums.length <= 10^5
    -10^5 <= nums[i] <= 10^5
    1 <= m <= nums.length

*/

#include <climits>
#include <map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    The only important thing here is to realize that you do NOT care about
    elements WITHIN the subsequence itself, only the first and the last one.

    So if m=3, and you start the leftmost at idx=2, then the last element of a
    subsequence starting at idx=2 can be either at: 4,5,6,7, ... N-1

        m = 3
        
        _ _ X _ _ _ _ _ _ _
        0 1 2 3 4 5 6 7 8 9

    If you start at idx=3 then the last element can be at: 5, 6, 7, ... N-1

    So you ONLY care about the elements from (idx + m - 1) until the end.

    However, since there are negative elements, it can be the case that the
    current negative and some negative towards the end give the maximum result.

    That's why we have to keep two Red-Black Trees, i.e. "map" in C++.

    One that will keep the MAXIMUM number from point Y until the end, and
    one that will keep the MINIMUM number from point Y until the end.

    Also, if m == N, we can immediately return nums[0] * nums.back() since that
    is the only option.

    Otherwise, fill both Maps from index m-1, until N-1(inclusive).

    Then simply start from i=0 and continue until i is <= (N - m).
    We CANNOT start our subsequence at idx (N - m + 1) since we would NOT be
    able to close it.

    Example:

        m = 3       // N = 10

        (N - m + 1) <==> 10 - 3 + 1 = 8
        
        _ _   _ _ _ _ _ X _
        0 1 2 3 4 5 6 7 8 9
                        ^
                        |
                        |
                        ------- If we start it here and m=3 we CANNOT have
                                the last element of a subsequence. It's simply
                                impossible.

*/

/* Time  Beats: 5.07% */
/* Space Beats:   -% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution {
public:
    long long maximumProduct(vector<int>& nums, int m)
    {
        const int N = nums.size();
        long long result = LLONG_MIN;

        if (m == N)
            return 1LL * nums[0] * nums.back();

        map<int, int> max_map;
        map<int, int, greater<int>> min_map;

        for (int i = m-1; i < N; i++)
        {
            max_map[nums[i]]++;
            min_map[nums[i]]++;
        }

        for (int i = 0; i <= N - m; i++)
        {
            long long tmp1 = 1LL * nums[i] * max_map.rbegin()->first;
            long long tmp2 = 1LL * nums[i] * min_map.rbegin()->first;
            result = max(result, tmp1);
            result = max(result, tmp2);

            max_map[nums[i + m - 1]]--;
            if (max_map[nums[i + m - 1]] == 0)
                max_map.erase(nums[i + m - 1]);

            min_map[nums[i + m - 1]]--;
            if (min_map[nums[i + m - 1]] == 0)
                min_map.erase(nums[i + m - 1]);
        }

        return result;
    }
};
