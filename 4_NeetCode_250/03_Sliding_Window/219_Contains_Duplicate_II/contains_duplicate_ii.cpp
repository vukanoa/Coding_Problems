/*
    ============
    === EASY ===
    ============

    ===========================
    219) Contains Duplicate
    ===========================

    ============
    Description:
    ============

    Given an integer array nums and an integer k, return true if there are two
    distinct indices i and j in the array such that nums[i] == nums[j] and
    abs(i - j) <= k.

    =================================================================
    FUNCTION: bool containsNearbyDuplicate(vector<int>& nums, int k);
    =================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,3,1], k = 3
    Output: true

    --- Example 2 ---
    Input: nums = [1,0,1,1], k = 1
    Output: true

    --- Example 3 ---
    Input: nums = [1,2,3,1,2,3], k = 2
    Output: false


    *** Constraints ***
    1 <= nums.length <= 10^5
    -10^9 <= nums[i] <= 10^9
    0 <= k <= 10^5

*/

#include <vector>
#include <unordered_set>
#include <unordered_map>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory. However, the Solution with HashSET is better.

*/

/* Time  Beats: 64.92% */
/* Space Beats: 14.40% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_HashMap {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k)
    {
        const int N = nums.size();

        unordered_map<int, int> umap;
        for (int i = 0; i < N; i++)
        {
            if (umap.find(nums[i]) != umap.end() && (i - umap[nums[i]]) <= k)
                return true;

            umap[nums[i]] = i;
        }

        return false;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    In Description, it says:"... array such that ... and abs(i - j) <= k"

    Since "abs(i - j)" is a range(window), it is at least possible that this
    may, in fact, be the Sliding Windows problem. So let's check if we can
    indeed solve it in an efficient manner using this technique.

    What they are asking us to do is to find 2 DISTINCT elements, within the
    range(window) that are equal.

    The length of the window is designated by variable 'k', but that's not
    actually true. It's "k + 1" since the condition that must NOT be satisfied
    is (abs(i - j) > k), therefore, if, say, k = 2 then a window where:

        i = 5
        j = 7

    is considered valid, but you can clearly see that it is consisted not of 2,
    but of 3 elements, at indices: 5, 6 and 7.
    Therefore the length of the window is not 'k', but "k + 1".

    So, since we have to "move the window" in order to check all the elements,
    we only need to consider the elements that are currently within the window.

    Also, it's important to note that we don't necessarily have to check every
    single element in the array, as we may satisfy the given condition and
    return true before we reach the end.

    As we've said - We have to "move the window" and check if there are two of
    the same values within that range(window) and if there are we immediately
    stop by returning true.

    However, if we do not find two of the same values within the current window
    then we have to add the current element to the window.


    We'll have two pointers: 'L' and 'R', designating the range of our window.
    Once 'L' becomes STRICTLY LESS THAN (R - k), i.e. it's outside of the
    currently considered window, we pop it from the Hash Set.

    After popping the leftmost element, i.e. the one that is OUTSIDE of the
    current valid window, we check if nums[i] is present within this window.

    If it is--Simply return true.
    Othwerise, push this nums[i] to Hashset and continue.

*/

/* Time  Beats: 20.58% */
/* Space Beats: 81.82% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_HashSet {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k)
    {
        const int N = nums.size();

        unordered_set<int> uset;
        int L = 0;
        int R = 0;
        while (R < N)
        {
            if (L < R - k) // If "L" index is Out-of-Bounds
            {
                uset.erase(nums[L]);
                L++;
            }

            if (uset.count(nums[R]))
                return true;

            uset.insert(nums[R]); // Push current element

            // Increment
            R++;
        }

        return false;
    }
};
