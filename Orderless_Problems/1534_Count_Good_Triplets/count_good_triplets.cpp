/*
    ============
    === EASY ===
    ============

    ===========================
    1534) Count Good Triplets
    ===========================

    ============
    Description:
    ============

    Given an array of integers arr, and three integers a, b and c. You need to
    find the number of good triplets.

    A triplet (arr[i], arr[j], arr[k]) is good if the following conditions are
    true:

        0 <= i < j < k < arr.length
        |arr[i] - arr[j]| <= a
        |arr[j] - arr[k]| <= b
        |arr[i] - arr[k]| <= c

    Where |x| denotes the absolute value of x.

    Return the number of good triplets.

    =======================================================================
    FUNCTION: int countGoodTriplets(vector<int>& arr, int a, int b, int c);
    =======================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: arr = [3,0,1,1,9,7], a = 7, b = 2, c = 3
    Output: 4
    Explanation: There are 4 good triplets: [(3,0,1), (3,0,1), (3,1,1), (0,1,1)]

    --- Example 2 ---
    Input: arr = [1,1,2,2,3], a = 0, b = 0, c = 1
    Output: 0
    Explanation: No triplet satisfies all conditions.


    *** Constraints ***
    3 <= arr.length <= 100
    0 <= arr[i] <= 1000
    0 <= a, b, c <= 1000

*/

#include <cstdlib>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Brute-Force.

*/

/* Time  Beats: 90.51% */
/* Space Beats: 71.62% */

/* Time  Complexity: O(N^3) */
/* Space Complexity: O(1)   */
class Solution {
public:
    int countGoodTriplets(vector<int>& arr, int a, int b, int c)
    {
        const int N = arr.size();
        int result = 0;

        for (int j = 1; j < N-1; j++)
        {
            for (int i = 0; i < j; i++)
            {
                for (int k = j+1; k < N; k++)
                {
                    if (abs(arr[i] - arr[j]) <= a &&
                        abs(arr[j] - arr[k]) <= b &&
                        abs(arr[i] - arr[k]) <= c)
                    {
                        result++;
                    }
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

    A little optimization.

*/

/* Time  Beats: 41.98% */
/* Space Beats:  5.91% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(M)   */
class Solution_2 {
public:
    int countGoodTriplets(vector<int>& arr, int a, int b, int c)
    {
        const int N = arr.size();

        int result = 0;
        vector<int> counter(1001, 0);

        for (int j = 0; j < N; ++j)
        {
            for (int k = j + 1; k < N; ++k)
            {
                if (abs(arr[j] - arr[k]) <= b)
                {
                    int min_valid_first = max(   0, max(arr[j] - a, arr[k] - c));
                    int max_valid_first = min(1000, min(arr[j] + a, arr[k] + c));

                    if (min_valid_first <= max_valid_first)
                    {
                        if (min_valid_first == 0)
                            result += counter[max_valid_first];
                        else
                            result += counter[max_valid_first] - counter[min_valid_first - 1];
                    }
                }
            }

            // Update prefix frequency sum with the current value at arr[j]
            for (int value = arr[j]; value <= 1000; value++)
            {
                counter[value]++;
            }
        }

        return result;
    }
};
