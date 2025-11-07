/*
    ============
    === EASY ===
    ============

    =============================================================
    1491) Average Salary Excluding the Minimum and Maximum Salary
    =============================================================

    ============
    Description:
    ============

    You are given an array of unique integers salary where salary[i] is the
    salary of the ith employee.

    Return the average salary of employees excluding the minimum and maximum
    salary. Answers within 10-5 of the actual answer will be accepted.

    ==============================================
    FUNCTION: double average(vector<int>& salary);
    ==============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: salary = [4000,3000,1000,2000]
    Output: 2500.00000
    Explanation: Minimum salary and maximum salary are 1000 and 4000 respectively.
    Average salary excluding minimum and maximum salary is (2000+3000) / 2 = 2500

    --- Example 2 ---
    Input: salary = [1000,2000,3000]
    Output: 2000.00000
    Explanation: Minimum salary and maximum salary are 1000 and 3000 respectively.
    Average salary excluding minimum and maximum salary is (2000) / 1 = 2000


    *** Constraints ***
    3 <= salary.length <= 100
    1000 <= salary[i] <= 10^6
    All the integers of salary are unique.

*/

#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  44.49% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    double average(vector<int>& salary)
    {
        const int N = salary.size();

        int min_salary = *min_element(salary.begin(), salary.end());
        int max_salary = *max_element(salary.begin(), salary.end());

        long long total_sum = accumulate(salary.begin(), salary.end(), 0LL);

        return 1.0 * (total_sum - min_salary - max_salary) / (N - 2);
    }
};
