#include <iostream>

/*
    ============
    === EASY ===
    ============

    ===========================
    278) First Bad Version
    ===========================

    ============
    Description:
    ============

    You are a product manager and currently leading a team to develop a new
    product. Unfortunately, the latest version of your product fails the
    quality check. Since each version is developed based on the previous
    version, all the versions after a bad version are also bad.

    Suppose you have n versions [1, 2, ..., n] and you want to find out the
    first bad one, which causes all the following ones to be bad.

    You are given an API bool isBadVersion(version) which returns whether
    version is bad. Implement a function to find the first bad version. You
    should minimize the number of calls to the API.

    =====================================
    FUNCTION: int firstBadVersion(int n);
    =====================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 5, bad = 4
    Output: 4
    Explanation:
    call isBadVersion(3) -> false
    call isBadVersion(5) -> true
    call isBadVersion(4) -> true
    Then 4 is the first bad version.

    --- Example 2 ---
    Input: n = 1, bad = 1
    Output: 1


    *** Constraints ***
    1 <= bad <= n <= 2^31 - 1

*/

// The API isBadVersion is defined for you.
// bool isBadVersion(int version);

/*
    ------------
    --- IDEA ---
    ------------

    Basic Binary Search. Since we're told that if there is one bad version that
    all the following are also bad, that means we must find "leftmost bad" or
    "the earliest bad version" from given n version.

    Since we're told that we should minimize that number of API calls, that
    highly indicates we shall use BinarySearch.
*/

/* Time  Beats: 100.00% */
/* Space Beats:  58.01% */

/* Time  Complexity: O(logn) */
/* Space Complexity: O(1) */
class Solution {
public:
    int firstBadVersion(int n)
    {
        int first_bad = INT_MAX;

        int left  = 1;
        int right = n;

        while (left <= right)
        {
            int mid = left + (right - left) / 2;

            if (isBadVersion(mid))
            {
                first_bad = mid;
                right = mid - 1;
            }
            else
                left = mid + 1;
        }

        return first_bad;
    }
};
