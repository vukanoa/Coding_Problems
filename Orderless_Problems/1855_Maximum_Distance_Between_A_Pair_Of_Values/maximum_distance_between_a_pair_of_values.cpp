/*
    ==============
    === MEDIUM ===
    ==============

    ===============================================
    1855) Maximum Distance Between a Pair of Values
    ===============================================

    ============
    Description:
    ============

    You are given two non-increasing 0-indexed integer arrays nums1 and nums2.

    A pair of indices (i, j), where:
        0 <= i < nums1.length
            and
        0 <= j < nums2.length,

    is valid if both i <= j and nums1[i] <= nums2[j]. The distance of the pair
    is j - i.

    Return the maximum distance of any valid pair (i, j). If there are no valid
    pairs, return 0.

    An array arr is non-increasing if arr[i-1] >= arr[i] for every 1 <= i <
    arr.length.

    ==================================================================
    FUNCTION: int maxDistance(vector<int>& nums1, vector<int>& nums2);
    ==================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums1 = [55,30,5,4,2], nums2 = [100,20,10,10,5]
    Output: 2
    Explanation: The valid pairs are (0,0), (2,2), (2,3), (2,4), (3,3), (3,4), and (4,4).
    The maximum distance is 2 with pair (2,4).

    --- Example 2 ---
    Input: nums1 = [2,2,2], nums2 = [10,10,1]
    Output: 1
    Explanation: The valid pairs are (0,0), (0,1), and (1,1).
    The maximum distance is 1 with pair (0,1).

    --- Example 3 ---
    Input: nums1 = [30,29,19,5], nums2 = [25,25,25,25,25]
    Output: 2
    Explanation: The valid pairs are (2,2), (2,3), (2,4), (3,3), and (3,4).
    The maximum distance is 2 with pair (2,4).


    *** Constraints ***
    1 <= nums1.length, nums2.length <= 10^5
    1 <= nums1[i], nums2[j] <= 10^5
    Both nums1 and nums2 are non-increasing.

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO
    Lower-bound in reverse. It's a bit tricky, you REALLY need to be good with
    Binary Search before attempting to solve it like this.

*/

/* Time  Beats: 12.14% */
/* Space Beats: 47.28% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(1)        */
class Solution_Binary_Search {
public:
    int maxDistance(vector<int>& nums1, vector<int>& nums2)
    {
        const int N = nums1.size();
        const int M = nums2.size();
        int result = 0;

        for (int i = 0; i < N; i++)
        {
            int& target = nums1[i];

            auto iter = lower_bound(nums2.rbegin(), nums2.rend() - (i+1), target);
            int j = nums2.rend() - iter - 1;

            if (i <= j && target <= *iter)
                result = max(result, j - i);
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Linear. Use the sorted property of BOTH vectors. Previously we've only used
    the sortedness from the SECOND vector, but not from the first one as well.

    Here we take advantage of both.

*/

/* Time  Beats: 49.20% */
/* Space Beats: 47.28% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Linear_1 {
public:
    int maxDistance(vector<int>& nums1, vector<int>& nums2)
    {
        const int N = nums1.size();
        const int M = nums2.size();
        int result = 0;

        int j = M-1;
        for (int i = N-1; i >= 0; i--)
        {
            while (j >= 0 && nums1[i] > nums2[j])
                j--;

            result = max(result, j - i);
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO
    Same as above, written in a different way. It's always beneficial to be
    aware of more than one implementation as sometimes this can be the only
    way to implement.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  74.44% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Linear_2 {
public:
    int maxDistance(vector<int>& nums1, vector<int>& nums2)
    {
        const int N = nums1.size();
        const int M = nums2.size();

        int i = 0;
        int j = 0;

        while (i < N && j < M)
        {
            i += nums1[i] > nums2[j]; // ? 1 : 0;

            // Increment
            j++;
        }

        return max(0, j - i - 1);
    }
};
