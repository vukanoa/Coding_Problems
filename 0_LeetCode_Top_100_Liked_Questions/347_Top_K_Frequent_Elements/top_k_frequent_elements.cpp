/*
    ==============
    === MEDIUM ===
    ==============

    ============================
    347) Top K Frequent Elements
    ============================

    ============
    Description:
    ============

    Given an integer array "nums" and an integer 'k', return the k most
    frequent elements. You may return the answer in any order.

    Follow up: Your algorithm's time complexity must be better than O(n * logn)
    (where n is the array's size)

    =============================================================
    FUNCTION: vector<int> topKFrequent(vector<int>& nums, int k);
    =============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  nums = [1, 1, 1, 2, 2, 3], k = 2
    Output: [1, 2]

    --- Example 2 ---
    Input:  nums = [1], k = 1
    Output: [1]

    *** Constraints ***
    1 <= nums.length <= 10^5
    -10^4 <= nums[i] <= 10^4
    k is in the range [1, the number of unique elements in the array]
    It is guaranteed that the answer is unique.

*/

#include <algorithm>
#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Example:
        [8, 8, 8, 8, 8]

    It is absolutely impossible to have more than N occurences. Also we can
    observe that we can have two elements occur the same amount of time.
    (Though there will always be K distinct unique elements. Meaning we will
    always have a result, we don't have to check these cases)

    The solution is to have an array of size N(maximum possible number of
    occurences) and that for each slot, we maintain a vector of elements that
    have that number of occurences in the vector "nums".

    This is a simple Bucket Sort Solution:

    Example:
    [5, 6, 2, 3, 4, 9, 9, 9, 6, 6, 6, 7, 7]

    freq:
        5: 1
        6: 4
        2: 1
        3: 1
        4: 1
        9: 3
        7: 2

    vector of vectors "bucket" is of size N

        bucket:
    5: /
    4: [6]
    3: [9]
    2: [7]
    1: [5, 2, 3, 4]
    0: /

    Since the result is guaranteed to be unique, simply start pushing elements
    from the back, until we push exactly k.

    That way we're guaranteed to have pushed MOST FREQUENT k elements.

*/

/* Time  Beats: 63.15% */
/* Space Beats: 32.61% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k)
    {
        const int N = nums.size();
        vector<int> result;

        int max_freq = 0;

        // O(N) (entire block)
        unordered_map<int, int> freq;
        for (const int& num : nums) // O(N)
            max_freq = max(max_freq, ++freq[num]);

        // O(N) (entire block)
        vector<vector<int>> bucket(max_freq + 1, vector<int>()); // O(N)
        for (const auto& [number, frequency] : freq) // O(N)
            bucket[frequency].push_back(number); // O(1)

        // O(N) (entire block)
        while (k > 0)
        {
            while (k > 0 &&  ! bucket.back().empty())
            {
                result.push_back(bucket.back().back()); // O(1)
                bucket.back().pop_back(); // O(1)
                k--;
            }

            bucket.pop_back(); // O(1)
        }

        return result;
    }
};
