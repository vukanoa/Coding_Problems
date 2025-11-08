/*
    ============
    === EASY ===
    ============

    =============================
    1854) Maximum Population Year
    =============================

    ============
    Description:
    ============

    You are given a 2D integer array logs where each logs[i] = [birthi, deathi]
    indicates the birth and death years of the ith person.

    The population of some year x is the number of people alive during that
    year. The ith person is counted in year x's population if x is in the
    inclusive range [birthi, deathi - 1]. Note that the person is not counted
    in the year that they die.

    Return the earliest year with the maximum population.

    ===========================================================
    FUNCTION: int maximumPopulation(vector<vector<int>>& logs);
    ===========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: logs = [[1993,1999],[2000,2010]]
    Output: 1993
    Explanation: The maximum population is 1, and 1993 is the earliest year
                 with this population.

    --- Example 2 ---
    Input: logs = [[1950,1961],[1960,1971],[1970,1981]]
    Output: 1960
    Explanation:
    The maximum population is 2, and it had happened in years 1960 and 1970.
    The earlier year between them is 1960.


    *** Constraints ***
    1 <= logs.length <= 100
    1950 <= birthi < deathi <= 2050

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Line Sweep 101.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  76.01% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */ // Because it's always 100 years
class Solution {
public:
    int maximumPopulation(vector<vector<int>>& logs)
    {
        const int N = logs.size();

        const int START_YEAR  = 1950;
        const int END_YEAR    = 2050;
        const int TOTAL_YEARS = END_YEAR - START_YEAR + 1;

        vector<int> line_sweep(TOTAL_YEARS, 0);

        for (int i = 0; i < N; i++)
        {
            line_sweep[logs[i][0] - START_YEAR]++;
            line_sweep[logs[i][1] - START_YEAR]--;
        }

        int max_population  = 0;
        int earliest_year_with_max_population = END_YEAR + 1;

        int curr_population = 0;
        for (unsigned i = 0; i < TOTAL_YEARS; i++)
        {
            curr_population += line_sweep[i];

            if (curr_population > max_population)
            {
                max_population = curr_population;
                earliest_year_with_max_population = START_YEAR + i;
            }
        }

        return earliest_year_with_max_population;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This one is much easier to read and grasp, however it uses unnecessary
    amount of space for the purposes of easier coding and reading.

*/

/* Time  Beats: 100.00% */
/* Space Beats:   6.52% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */ // Kind of O(1), but used much more than necessary
class Solution_Concise {
public:
    int maximumPopulation(vector<vector<int>>& logs)
    {
        int population[2051] = {}; // Line Sweep
        int year = 0;

        for (auto &l : logs)
        {
            population[l[0]]++;
            population[l[1]]--;
        }

        for (int i = 1950; i < 2050; i++)
        {
            population[i] += population[i - 1];

            if (population[i] > population[year])
                year = i;
        }

        return year;
    }
};
