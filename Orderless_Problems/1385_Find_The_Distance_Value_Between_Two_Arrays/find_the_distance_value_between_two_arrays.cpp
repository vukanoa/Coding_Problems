/*
    ============
    === EASY ===
    ============

    ================================================
    1385) Find the Distance Value Between Two Arrays
    ================================================

    ============
    Description:
    ============

    Given two integer arrays arr1 and arr2, and the integer d, return the
    distance value between the two arrays.

    The distance value is defined as the number of elements arr1[i] such that
    there is not any element arr2[j] where |arr1[i]-arr2[j]| <= d.

    ================================================================================
    FUNCTION: int findTheDistanceValue(vector<int>& arr1, vector<int>& arr2, int d);
    ================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: arr1 = [4,5,8], arr2 = [10,9,1,8], d = 2
    Output: 2
    Explanation: 
    For arr1[0]=4 we have: 
    |4-10|=6 > d=2 
    |4-9|=5 > d=2 
    |4-1|=3 > d=2 
    |4-8|=4 > d=2 
    For arr1[1]=5 we have: 
    |5-10|=5 > d=2 
    |5-9|=4 > d=2 
    |5-1|=4 > d=2 
    |5-8|=3 > d=2
    For arr1[2]=8 we have:
    |8-10|=2 <= d=2
    |8-9|=1 <= d=2
    |8-1|=7 > d=2
    |8-8|=0 <= d=2

    --- Example 2 ---
    Input: arr1 = [1,4,2,3], arr2 = [-4,-3,6,10,20,30], d = 3
    Output: 2

    --- Example 3 ---
    Input: arr1 = [2,1,100,3], arr2 = [-5,-2,10,-3,7], d = 6
    Output: 1


    *** Constraints ***
    1 <= arr1.length, arr2.length <= 500
    -1000 <= arr1[i], arr2[j] <= 1000
    0 <= d <= 100

*/

#include <algorithm>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 41.27% */
/* Space Beats: 86.07% */

/* Time  Complexity: O(M * logN) */
/* Space Complexity: O(1)        */
class Solution {
public:
    int findTheDistanceValue(vector<int>& arr1, vector<int>& arr2, int d)
    {
        int M = arr1.size();
        int N = arr2.size();

        /* Sort in ASCENDING order */
        sort(arr2.begin(), arr2.end());

        int result = 0;
        for (int i = 0; i < M; i++)
        {
            int low  = 0;
            int high = N-1;

            int smaller_bound = arr1[i] - d;
            int greater_bound = arr1[i] + d;
            
            while (low <= high)
            {
                int mid = low + (high - low) / 2;

                if (arr2[mid] < smaller_bound)
                {
                    low  = mid + 1;
                } 
                else if (arr2[mid] > greater_bound)
                {
                    high = mid - 1;
                } 
                else
                {
                    result++;
                    break;
                }
            }
        }

        return M - result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  86.07% */

/* Time  Complexity: O(M * logN) */
/* Space Complexity: O(1)        */
class Solution_2 {
public:
    int findTheDistanceValue(vector<int>& arr1, vector<int>& arr2, int d)
    {
        int result = 0;

        /* Sort in ASCENDING */
        sort(arr2.begin(), arr2.end());
        
        int smaller_bound;
        int greater_bound;

        for (auto num : arr1)
        {
            smaller_bound = num - d;
            greater_bound = num + d;
            
            auto iter_low  = lower_bound(arr2.begin(), arr2.end(), smaller_bound);
            auto iter_high = lower_bound(arr2.begin(), arr2.end(), greater_bound);
            
            if (iter_low == iter_high && (*iter_low != smaller_bound && *iter_low != greater_bound))
                result++;
        }
        
        return result;
    }
};
