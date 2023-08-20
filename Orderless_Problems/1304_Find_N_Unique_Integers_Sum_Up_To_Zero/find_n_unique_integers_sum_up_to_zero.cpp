#include <iostream>

/*
	==============
	=== MEDIUM ===
	==============

	===========================================
	1304) Find N Unique Integers Sum Up To Zero
	===========================================

	============
	Description:
	============

	Given an integer n, return any array containing n unique integers such that
	they add up to 0.

	=====================================
	FUNCTION: vector<int> sumZero(int n);
	=====================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input: n = 5
	Output: [-7,-1,1,3,4]
	Explanation: These arrays also are accepted [-5,-1,1,2,3] , [-3,-1,2,-2,4].

	--- Example 2 ---
	Input: n = 3
	Output: [-1,0,1]

	--- Example 3 ---
	Input: n = 1
	Output: [0]

	*** Constraints ***
	1 <= n <= 1000

*/

/* Time  Beats: 100% */
/* Space Beats: 14.57% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution
{
public:
    vector<int> sumZero(int n)
    {
        std::vector<int> result;
        for (int i = 0; i < n/2; i++)
        {
            result.push_back(i + 1);
            result.push_back(-1 * (i + 1));
        }

        if (n & 1)
            result.push_back(0);
        
        return result;
    }
};
