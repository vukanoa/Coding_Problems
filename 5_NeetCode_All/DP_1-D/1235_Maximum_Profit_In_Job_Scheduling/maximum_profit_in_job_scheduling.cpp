#include <iostream>
#include <vector>
#include <algorithm>

/*
    ============
    === HARD ===
    ============

    ======================================
    1235) Maximum Profit In Job Scheduling
    ======================================

    ============
    Description:
    ============

    We have n jobs, where every job is scheduled to be done from startTime[i]
    to endTime[i], obtaining a profit of profit[i].

    You're given the startTime, endTime and profit arrays, return the maximum
    profit you can take such that there are no two jobs in the subset with
    overlapping time range.

    If you choose a job that ends at time X you will be able to start another
    job that starts at time X.

    ===============================================================================================
    FUNCTION: int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit);
    ===============================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: startTime = [1,2,3,3], endTime = [3,4,5,6], profit = [50,10,40,70]
    Output: 120
    Explanation: The subset chosen is the first and fourth job. 
    Time range [1-3]+[3-6] , we get profit of 120 = 50 + 70.

    --- Example 2 ---
    Input: startTime = [1,2,3,4,6], endTime = [3,5,10,6,9], profit = [20,20,100,70,60]
    Output: 150
    Explanation: The subset chosen is the first, fourth and fifth job. 
    Profit obtained 150 = 20 + 70 + 60.

    --- Example 3 ---
    Input: startTime = [1,1,1], endTime = [2,3,4], profit = [5,6,4]
    Output: 6


    *** Constraints ***
    1 <= startTime.length == endTime.length == profit.length <= 5 * 10^4
    1 <= startTime[i] < endTime[i] <= 10^9
    1 <= profit[i] <= 10^4

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 57.33% */
/* Space Beats: 23.40% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n)        */
class Solution {
public:
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit)
    {
        int n = startTime.size();

		vector<int> dp(n,-1);

		vector<vector<int>> job;
		for(int i = 0; i < n; i++) 
            job.push_back( {startTime[i], endTime[i], profit[i]} );  

		sort(job.begin(),job.end());
		sort(startTime.begin(),startTime.end());

		return find(0,job,startTime,n,dp);
    }

private:
   int find(int i, vector<vector<int>>& job, vector<int>&startTime, int n, vector<int>& dp)
   {
		if (i >= n)
            return 0;

		if (dp[i] != -1)
            return dp[i];

		int index = lower_bound(startTime.begin(),startTime.end(),job[i][1]) - startTime.begin();
		int pick = job[i][2] + find(index, job, startTime, n, dp);

		int notpick = find(i+1, job, startTime, n, dp);

		return dp[i] = max(pick, notpick);
	}
};
