#include <iostream>
#include <vector>
#include <algorithm>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    826) Most Profit Assigning Work
    ===========================

    ============
    Description:
    ============

    You have n jobs and m workers. You are given three arrays: difficulty,
    profit, and worker where:

        + difficulty[i] and profit[i] are the difficulty and the profit of the
        ith job, and worker[j] is the ability of jth worker (i.e., the jth

        + worker can only complete a job with difficulty at most worker[j]).

    Every worker can be assigned at most one job, but one job can be completed
    multiple times.

        + For example, if three workers attempt the same job that pays $1, then
        the total profit will be $3. If a worker cannot complete any job, their
        profit is $0.

    Return the maximum profit we can achieve after assigning the workers to the
    jobs.

    =====================================================================================================
    FUNCTION: int maxProfitAssignment(vector<int>& difficulty, vector<int>& profit, vector<int>& worker);
    =====================================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: difficulty = [2,4,6,8,10], profit = [10,20,30,40,50], worker = [4,5,6,7]
    Output: 100
    Explanation: Workers are assigned jobs of difficulty [4,4,6,6] and they get
    a profit of [20,20,30,30] separately.


    --- Example 2 ---
    Input: difficulty = [85,47,57], profit = [24,66,99], worker = [40,25,25]
    Output: 0


    *** Constraints ***
    n == difficulty.length
    n == profit.length
    m == worker.length
    1 <= n, m <= 10^4
    1 <= difficulty[i], profit[i], worker[i] <= 10^5

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 36.98% */
/* Space Beats: 47.29% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n) */
class Solution_Greedy {
public:
    int maxProfitAssignment(std::vector<int>& difficulty,
                            std::vector<int>& profit,
                            std::vector<int>& worker)
    {
        int result  = 0;
        int best = 0;
        int j = 0;

        std::vector<std::pair<int, int>> temp;
        for(int i = 0; i < worker.size(); ++i)
            temp.push_back({difficulty[i], profit[i]});

        std::sort(temp.begin(), temp.end());
        std::sort(worker.begin(), worker.end());

        for (const int& work : worker)
        {
            while (work >= temp[j].first && j < worker.size())
                best = std::max(best, temp[j++].second);

            result += best;
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 61.34% */
/* Space Beats: 89.18% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n) */
class Solution_Greedy_Plus_Binary_Search {
public:
    int maxProfitAssignment(std::vector<int>& difficulty,
                            std::vector<int>& profit,
                            std::vector<int>& worker)
    {
        std::vector<std::pair<int,int>> vec (difficulty.size());
        for(int i = 0; i < difficulty.size(); i++)
            vec[i] = { difficulty[i], profit[i] };

        /* Lambda */
        auto comp = [&](std::pair<int,int> a, std::pair<int,int> b){
            if (a.first < b.first)
                return true;

            return false;
        };

        std::sort(vec.begin(), vec.end(), comp);
        std::sort(worker.begin(), worker.end());

        int result = 0;
        int x = 0;
        int max_profit = 0;

        for(int i = 0; i < worker.size(); i++)
        {
            int mid  = binarySearch(vec, worker[i]);
            for(int i = x; i <= mid; i++)
                max_profit = std::max(max_profit, vec[i].second);

            x = std::max(0, mid);
            result += max_profit;
        }

        return result;
    }

private:
    int binarySearch(std::vector<std::pair<int,int>>& vec, int target)
    {
        int left  = 0;
        int right = vec.size()-1;

        int result = -1;
        while (left <= right)
        {
            int mid = left + (right - left) / 2;

            if(vec[mid].first <= target)
            {
                result = mid;
                left   = mid + 1;
            }
            else
                right  = mid - 1;
        }

        return result;
    }
};
