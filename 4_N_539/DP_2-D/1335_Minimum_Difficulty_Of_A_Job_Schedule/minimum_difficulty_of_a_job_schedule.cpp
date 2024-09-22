#include <iostream>
#include <vector>

/*
    ============
    === HARD ===
    ============

    ==========================================
    1335) Minimum Difficulty of a Job Schedule
    ==========================================

    ============
    Description:
    ============

    You want to schedule a list of jobs in d days. Jobs are dependent (i.e To
    work on the ith job, you have to finish all the jobs j where 0 <= j < i).

    You have to finish at least one task every day. The difficulty of a job
    schedule is the sum of difficulties of each day of the d days. The
    difficulty of a day is the maximum difficulty of a job done on that day.

    You are given an integer array jobDifficulty and an integer d. The
    difficulty of the ith job is jobDifficulty[i].

    Return the minimum difficulty of a job schedule. If you cannot find a
    schedule for the jobs return -1.


    ===============================================================
    FUNCTION: int minDifficulty(vector<int>& jobDifficulty, int d); 
    ===============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: jobDifficulty = [6,5,4,3,2,1], d = 2
    Output: 7
    Explanation: First day you can finish the first 5 jobs, total difficulty = 6.
    Second day you can finish the last job, total difficulty = 1.
    The difficulty of the schedule = 6 + 1 = 7 

    --- Example 2 ---
    Input: jobDifficulty = [9,9,9], d = 4
    Output: -1
    Explanation: If you finish a job per day you will still have a free day.
                 you cannot find a schedule for the given jobs.

    --- Example 3 ---
    Input: jobDifficulty = [1,1,1], d = 3
    Output: 3
    Explanation: The schedule is one job per day. total difficulty will be 3.


    *** Constraints ***
    1 <= jobDifficulty.length <= 300
    0 <= jobDifficulty[i] <= 1000
    1 <= d <= 10

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 98.31% */
/* Space Beats: 80.57% */

/* Time  Complexity: O(days * num_jobs) */
/* Space Complexity: O(num_jobs) */
class Solution {
public:
    int minDifficulty(std::vector<int>& jobDifficulty, int days)
    {
        const int num_jobs = static_cast<int>(jobDifficulty.size());

        if (num_jobs < days)
            return -1;
        else if (num_jobs == days)
            return std::accumulate(jobDifficulty.begin(), jobDifficulty.end(), 0);

        std::vector<int> dp(num_jobs);
        dp[0] = jobDifficulty[0];

        for (int i = 1; i < num_jobs; ++i)
            dp[i] = std::max(jobDifficulty[i], dp[i - 1]);

        // Step 4: Monotonic Stack Optimization
        std::vector<int> dp_prev(num_jobs);
        std::vector<int> stack_index;
        stack_index.reserve(num_jobs);
        int last_job_index;

        for (int currentDay = 1; currentDay < days; ++currentDay)
        {
            dp.swap(dp_prev);
            stack_index.clear();

            // Step 4 (continued): Monotonic Stack Optimization
            for (int jobIndex = currentDay; jobIndex < num_jobs; ++jobIndex)
            {
                dp[jobIndex] = jobDifficulty[jobIndex] + dp_prev[jobIndex - 1];

                while ( ! stack_index.empty() && jobDifficulty[stack_index.back()] <= jobDifficulty[jobIndex])
                {
                    last_job_index = stack_index.back();
                    stack_index.pop_back();
                    dp[jobIndex] = std::min(dp[jobIndex], dp[last_job_index] + jobDifficulty[jobIndex] - jobDifficulty[last_job_index]);
                }

                if ( ! stack_index.empty())
                {
                    last_job_index = stack_index.back();
                    dp[jobIndex] = std::min(dp[jobIndex], dp[last_job_index]);
                }

                stack_index.emplace_back(jobIndex);
            }
        }

        return dp.back();
    }
};
