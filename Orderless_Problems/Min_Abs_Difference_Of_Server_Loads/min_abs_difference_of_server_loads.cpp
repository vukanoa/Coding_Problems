#include <iostream>
#include <vector>

#include <climits>
#include <numeric> // std::accumulate

/*
    Almost equivalent, in terms of Solutions to the:
    LeetCode 1049: Last Stone Weight II
*/

/*

    There are some processes that need to be executed. Amount of a load that
    process causes on a server that runs it, is being represented by a single
    integer. Total load caused on a server is the sum of the loads of all the
    processes that run on that server. You have at your disposal two servers,
    on which mentioned processes can be run. Your goal is to distribute given
    processes between those two servers in the way that, absolute difference of
    their loads will be minimized.

    Given an array of n integers, of which represents loads caused by
    successive processes, return the minimum absolute difference of server
    loads.

    Example 1:

    Input: [1, 2, 3, 4, 5]
    Output: 1
    Explanation:
    We can distribute the processes with loads [1, 2, 4] to the first server
    and [3, 5] to the second one, so that their total loads will be 7 and 8,
    respectively, and the difference of their loads will be equal to 1.

    Constraints:
    In reality <unknown>, however I assume:
    1) 1 <= processes.size() <= INT_MAX
    2) 1 <= sum(processes)   <= INT_MAX
    3) processes[i] is a positive number
    4) 1 <= i < processes.size();
*/










/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/


/* Time  Complexity: O(n * sum) */
/* Space Complexity: O(n * sum) */
class Solution {
public:
    int solution(std::vector<int>& processes)
    {
        const int N = processes.size();
        int min_difference = INT_MAX;

        int sum = std::accumulate(processes.begin(), processes.end(), 0);
        std::vector<std::vector<bool>> dp(N+1, std::vector(sum + 1, false));

        for (int i = 0; i < N+1; i++)
            dp[i][0] = true;

        for (int i = 1; i < N+1; i++)
        {
            for (int j = 1; j < sum+1; j++)
            {
                if (dp[i-1][j] || (j-processes[i-1] >= 0 &&  dp[i-1][j - processes[i-1]]) )
                    dp[i][j] = true;
            }
        }

        for (int j = 0; j < sum+1; j++)
            min_difference = std::min(min_difference, dp[N][j] ? std::abs(sum-2*j) : INT_MAX);

        return min_difference;       

    }
};


int
main()
{
    Solution sol;

    /* Example 1 */
    // std::vector<int> processes = {1, 2, 3};

    /* Example 2 */
    // std::vector<int> processes = {1, 2, 3, 4, 5};

    /* Example 3 */
    std::vector<int> processes = {7, 4, 5, 3, 2, 8};

    /* Example 4 */
    // std::vector<int> processes = {5};

    /* Example 5 */
    // std::vector<int> processes = {5, 8};

    /* Example 6 */
    // std::vector<int> processes = {5, 8, 2};

    /* Example 6 */
    // std::vector<int> processes = {5, 8, 2, 1};

    std::cout << "\n\t==========================================";
    std::cout << "\n\t=== MIN ABS DIFFERENCE OF SERVER LOADS ===";
    std::cout << "\n\t==========================================\n";


    /* Write Input */
    bool first = true;
    std::cout << "\n\tProcesses: [";
    for (auto x: processes)
    {
        if (!first)
            std::cout << ", ";

        std::cout << x;
        first = false;
    }
    std::cout << "]\n";


    /* Solution */
    int  result = sol.solution(processes);


    /* Write Output */
    std::cout << "\n\tResult: " << result;

    std::cout << "\n\n";
    return 0;
}
