/*
    ============
    === HARD ===
    ============

    ============================
    1095) Find In Mountain Array
    ============================

    ============
    Description:
    ============

    (This problem is an interactive problem.)

    You may recall that an array arr is a mountain array if and only if:

        arr.length >= 3
        There exists some i with 0 < i < arr.length - 1 such that:
            arr[0] < arr[1] < ... < arr[i - 1] < arr[i]
            arr[i] > arr[i + 1] > ... > arr[arr.length - 1]

    Given a mountain array mountainArr, return the minimum index such that
    mountainArr.get(index) == target. If such an index does not exist, return
    -1.

    You cannot access the mountain array directly. You may only access the
    array using a MountainArray interface:

        + MountainArray.get(k) returns the element of the array at index k
          (0-indexed).

        + MountainArray.length() returns the length of the array.

    Submissions making more than 100 calls to MountainArray.get will be judged
    Wrong Answer. Also, any solutions that attempt to circumvent the judge will
    result in disqualification.

    ==========================================================================
    FUNCTION: int findInMountainArray(int target, MountainArray &mountainArr);
    ==========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: array = [1,2,3,4,5,3,1], target = 3
    Output: 2
    Explanation: 3 exists in the array, at index=2 and index=5. Return the
                 minimum index, which is 2.

    --- Example 2 ---
    Input: array = [0,1,2,4,2,1], target = 3
    Output: -1
    Explanation: 3 does not exist in the array, so we return -1.


    *** Constraints ***
    3 <= mountain_arr.length() <= 10%4
    0 <= target <= 109
    0 <= mountain_arr.get(index) <= 10^9

*/

#include <climits>
using namespace std;

// This is the MountainArray's API interface.
// You should not implement it, or speculate about its implementation
class MountainArray {
  public:
    int get(int index);
    int length();
};

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 73.44% */
/* Space Beats: 39.15% */

/* Time  Complexity: O(logN) */
/* Space Complexity: O(1)    */
class Solution {
public:
    int findInMountainArray(int target, MountainArray &mountainArr)
    {
        const int N = mountainArr.length();

        /********************************/
        /* Find peak_idx in mountainArr */
        /********************************/
        int low  = 0;
        int high = N-1;
        while (low < high)
        {
            int mid = low + (high - low) / 2; // Left-leaning "mid"

            int prev = mid-1 < 0  ? INT_MIN : mountainArr.get(mid - 1);
            int curr = mountainArr.get(mid);
            int next = mid+1 == N ? INT_MAX : mountainArr.get(mid + 1);

            if (prev < curr && curr < next)
                low = mid + 1;
            else
                high = mid;
        }

        int peak_idx = low; // Or "high" it does NOT matter, since low == high

        /*
                               |
              peak_idx ------- |
                             | |
                             | |
                             v |
            [1, 2, 4, 7, 9, 14,|8, 6, 5, 4,  2]
             0  1  2  3  4   5 |6  7  8  9  10
             ~~~~~~~~~~~~~~~~~ |~~~~~~~~~~~~~~
                    ^          |        ^
                    |          |        |
                    |          |        |
                LEFT-HALF      |   RIGHT-HALF
           (including peak_idx)| (NOT including peak_idx)
                               |
                               |

        */

        /*****************************************************/
        /* Lower_bound on the LEFT-HALF (including peak_idx) */
        /*****************************************************/
        low  = 0;
        high = peak_idx;
        while (low < high)
        {
            int mid = low + (high - low) / 2; // Left-leaning "mid"

            if (target > mountainArr.get(mid))
                low = mid + 1;
            else
                high = mid;
        }

        if (target == mountainArr.get(low))
            return low; // Or "high" it does NOT matter

        /*******************************************************************/
        /* Lower_bound in RIGHT-HALF (EXCLUDING peak_idx) in REVERSE order */
        /*******************************************************************/
        /*
            peak_idx
                  |
                  |
                  v
           [.... 14,  8,  6,  5 , 4,  2]
                  5   6   7   8   9  10
                      ^               ^
                      |               |
                      |               |
                    high             low
             ("left" pointer)     ("right" pointer)
                 points to           points to
                  BIGGER              SMALLER
                  values              values


            This is precisely why we must "swap":

                standard lower_bound: while (low  < high)
                REVERSED lower_bound: while (high <  low)

                standard lower_bound: mid = low  + (high - low     ) / 2
                REVERSED lower_bound: mid = high + (low  - high + 1) / 2;

            Since we ALWAYS want to have "mid" lean towards "low", that's done
            in two different ways here, since "low" pointer is the "right
            pointer" here.

                standard lower_bound: mid = low  + (high - low     ) / 2
                REVERSED lower_bound: mid = high + (low  - high + 1) / 2;
                                                                  ^
                                                                  |
                                                                  |
                                                     This is the CRUX


            ALWAYS consider when you're left with only 2 elements and then
            check if your implementation is going to get stuck or not.

        */
        low  = N-1;          // "right pointer", but points to SMALLER values
        high = peak_idx + 1; // "left  pointer", but points to BIGGER  values
        while (high < low)
        {
            int mid = high + (low - high + 1) / 2; // "mid" leans toward "low"

            if (target > mountainArr.get(mid))
                low = mid - 1;
            else
                high = mid;
        }


        return target == mountainArr.get(low) ? low : -1;
    }
};
