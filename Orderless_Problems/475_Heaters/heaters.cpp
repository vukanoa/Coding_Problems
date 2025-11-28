/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    475) Heaters
    ===========================

    ============
    Description:
    ============

    Winter is coming! During the contest, your first job is to design a
    standard heater with a fixed warm radius to warm all the houses.

    Every house can be warmed, as long as the house is within the heater's warm
    radius range. 

    Given the positions of houses and heaters on a horizontal line, return the
    minimum radius standard of heaters so that those heaters could cover all
    houses.

    Notice that all the heaters follow your radius standard, and the warm
    radius will be the same.

    ====================================================================
    FUNCTION: int findRadius(vector<int>& houses, vector<int>& heaters);
    ====================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: houses = [1,2,3], heaters = [2]
    Output: 1
    Explanation: The only heater was placed in the position 2, and if we use
                 the radius 1 standard, then all the houses can be warmed.

    --- Example 2 ---
    Input: houses = [1,2,3,4], heaters = [1,4]
    Output: 1
    Explanation: The two heaters were placed at positions 1 and 4. We need to
                 use a radius 1 standard, then all the houses can be warmed.

    --- Example 3 ---
    Input: houses = [1,5], heaters = [2]
    Output: 3


    *** Constraints ***
    1 <= houses.length, heaters.length <= 3 * 10^4
    1 <= houses[i], heaters[i] <= 10^9

*/

#include <algorithm>
#include <climits>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 60.22% */
/* Space Beats:  7.75% */

/* Time  Complexity: O(N * logN + M * logM) */
/* Space Complexity: O(N)                   */
class Solution {
public:
    int findRadius(vector<int>& houses, vector<int>& heaters)
    {
        const int N = houses.size();
        const int M = heaters.size();

        /* Sort */
        sort(houses.begin(), houses.end());
        sort(heaters.begin(), heaters.end());

        vector<int> result(N, INT_MAX); 
        
        // For each house, calculate distance to nearest RHS heater
        // [Forward]
        int house_idx   = 0;
        int heater_idx = 0;
        while (house_idx < N && heater_idx < M)
        {
            if (houses[house_idx] <= heaters[heater_idx])
            {
                result[house_idx] = heaters[heater_idx] - houses[house_idx];
                house_idx++;
            }
            else
            {
                heater_idx++;
            }
        }
        
        // For each house, calculate distance to nearest LHS heater
        // [Backward]
        house_idx  = N-1;
        heater_idx = M-1;
        while (house_idx >= 0 && heater_idx >= 0)
        {
            if (houses[house_idx] >= heaters[heater_idx])
            {
                result[house_idx] = min(result[house_idx], houses[house_idx] - heaters[heater_idx]);
                house_idx--;
            }
            else
            {
                heater_idx--;
            }
        }
       
        return *max_element(result.begin(), result.end());
    }
};
