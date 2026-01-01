#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    1834) Single-Threaded CPU
    ===========================

    ============
    Description:
    ============

    You are given n tasks labeled from 0 to n - 1 represented by a 2D integer
    array tasks, where tasks[i] = [enqueueTimei, processingTimei] means that
    the ith task will be available to process at enqueueTimei and will take
    processingTimei to finish processing.

    You have a single-threaded CPU that can process at most one task at a time
    and will act in the following way:

        If the CPU is idle and there are no available tasks to process, the CPU
        remains idle.  If the CPU is idle and there are available tasks, the
        CPU will choose the one with the shortest processing time. If multiple
        tasks have the same shortest processing time, it will choose the task
        with the smallest index.  Once a task is started, the CPU will process
        the entire task without stopping.  The CPU can finish a task then start
        a new one instantly.

    Return the order in which the CPU will process the tasks.

    ===========================================================
    FUNCTION: vector<int> getOrder(vector<vector<int>>& tasks);
    ===========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: tasks = [[1,2],[2,4],[3,2],[4,1]]
    Output: [0,2,3,1]
    Explanation: The events go as follows:
    - At time = 1, task 0 is available to process. Available tasks = {0}.
    - Also at time = 1, the idle CPU starts processing task 0. Available tasks
      = {}.
    - At time = 2, task 1 is available to process. Available tasks = {1}.
    - At time = 3, task 2 is available to process. Available tasks = {1, 2}.
    - Also at time = 3, the CPU finishes task 0 and starts processing task 2 as
      it is the shortest. Available tasks = {1}.
    - At time = 4, task 3 is available to process. Available tasks = {1, 3}.
    - At time = 5, the CPU finishes task 2 and starts processing task 3 as it
      is the shortest. Available tasks = {1}.
    - At time = 6, the CPU finishes task 3 and starts processing task 1.
      Available tasks = {}.
    - At time = 10, the CPU finishes task 1 and becomes idle.


    --- Example 2 ---
    Input: tasks = [[7,10],[7,12],[7,5],[7,4],[7,2]]
    Output: [4,3,2,0,1]
    Explanation: The events go as follows:
    - At time = 7, all the tasks become available. Available tasks =
      {0,1,2,3,4}.
    - Also at time = 7, the idle CPU starts processing task 4. Available tasks
      = {0,1,2,3}.
    - At time = 9, the CPU finishes task 4 and starts processing task 3.
      Available tasks = {0,1,2}.
    - At time = 13, the CPU finishes task 3 and starts processing task 2.
      Available tasks = {0,1}.
    - At time = 18, the CPU finishes task 2 and starts processing task 0.
      Available tasks = {1}.
    - At time = 28, the CPU finishes task 0 and starts processing task 1.
      Available tasks = {}.
    - At time = 40, the CPU finishes task 1 and becomes idle.


    *** Constraints ***
    tasks.length == n
    1 <= n <= 10^5
    1 <= enqueueTimei, processingTimei <= 10^9

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

    (All 3 implementations are of the same IDEA. I just wanted to have all 3
    ways of implementing because C++ is cumbersome for this Problem).

*/

/* Time  Beats: 34.11% */
/* Space Beats: 13.62% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n) */
class Solution_1 {
public:
    std::vector<int> getOrder(std::vector<std::vector<int>>& tasks)
    {
        std::vector<int> results;

        std::priority_queue<std::pair<int, int>,
                            std::vector<std::pair<int, int>>,
                            std::greater<std::pair<int, int>>> available_tasks;

        // So that after the sort we have correct original indices available
        std::vector<std::pair<std::vector<int>, int>> tasks_idx;
        for (int i = 0; i < tasks.size(); i++)
            tasks_idx.push_back( {{tasks[i][0], tasks[i][1]}, i} );

        std::stable_sort(tasks_idx.begin(), tasks_idx.end(), [](const std::pair<std::vector<int>, int>& a,
                                                                const std::pair<std::vector<int>, int>& b)
                                                                {
                                                                    return a.first[0] < b.first[0];
                                                                });

        int curr_time = tasks_idx[0].first[0];
        int i = 0;

        while (i < tasks_idx.size())
        {
            if (available_tasks.empty() && curr_time < tasks_idx[i].first[0])
                curr_time = tasks_idx[i].first[0];

            while (i < tasks_idx.size() && curr_time == tasks_idx[i].first[0])
                available_tasks.push( {tasks_idx[i].first[1], tasks_idx[i++].second} );

            results.push_back(available_tasks.top().second); // Index
            curr_time += available_tasks.top().first;
            available_tasks.pop();

            while (i < tasks_idx.size() && tasks_idx[i].first[0] <= curr_time)
                available_tasks.push( {tasks_idx[i].first[1], tasks_idx[i++].second} );
        }

        while (!available_tasks.empty())
        {
            results.push_back(available_tasks.top().second);
            available_tasks.pop();
        }

        return results;
    }
};




/* Time  Beats: 34.11% */
/* Space Beats: 47.24% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n) */
class Solution_2 {
public:
    std::vector<int> getOrder(std::vector<std::vector<int>>& tasks)
    {
        std::vector<int> results;

        std::priority_queue<std::pair<int, int>,
                            std::vector<std::pair<int, int>>,
                            std::greater<std::pair<int, int>>> available_tasks;

        // So that after the sort we have correct original indices available
        for (int i = 0; i < tasks.size(); i++)
            tasks[i].push_back(i);

        std::stable_sort(tasks.begin(), tasks.end(), [](const std::vector<int>& a,
                                                        const std::vector<int>& b)
                                                        {
                                                            return a[0] < b[0];
                                                        });

        int curr_time = tasks[0][0];
        int i = 0;

        while (i < tasks.size())
        {
            if (available_tasks.empty() && curr_time < tasks[i][0])
                curr_time = tasks[i][0];

            while (i < tasks.size() && curr_time == tasks[i][0])
                available_tasks.push( {tasks[i][1], tasks[i++][2]} );

            results.push_back(available_tasks.top().second); // Index
            curr_time += available_tasks.top().first;
            available_tasks.pop();

            while (i < tasks.size() && tasks[i][0] <= curr_time)
                available_tasks.push( {tasks[i][1], tasks[i++][2]} );
        }

        while (!available_tasks.empty())
        {
            results.push_back(available_tasks.top().second);
            available_tasks.pop();
        }

        return results;
    }
};




/* Time  Beats: 35.83% */
/* Space Beats: 47.24% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n) */
class Solution_Neat {
public:
    std::vector<int> getOrder(std::vector<std::vector<int>>& tasks)
    {
        // So that after the sort we have correct original indices available
        for (int i = 0; i < tasks.size(); i++)
            tasks[i].push_back(i);

        std::stable_sort(tasks.begin(), tasks.end(), [](const std::vector<int>& a,
                                                        const std::vector<int>& b)
                                                        {
                                                            return a[0] < b[0];
                                                        });
        std::vector<int> results;

        std::priority_queue<std::pair<int, int>,
                            std::vector<std::pair<int, int>>,
                            std::greater<std::pair<int, int>>> available_tasks;


        unsigned long long curr_time = tasks[0][0];
        int i = 0;

        while (!available_tasks.empty() || i < tasks.size())
        {
            while (i < tasks.size() && tasks[i][0] <= curr_time)
                available_tasks.push( {tasks[i][1], tasks[i++][2]} );

            if (available_tasks.empty())
                curr_time = tasks[i][0];
            else
            {
                std::pair<int, int> task = available_tasks.top();
                available_tasks.pop();

                curr_time += task.first;
                results.push_back(task.second);
            }
        }

        return results;
    }
};
