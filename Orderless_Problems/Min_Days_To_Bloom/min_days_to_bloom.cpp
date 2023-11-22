#include <iostream>
#include <vector>
#include <algorithm>

#include <climits>

/*

    Given an array of roses. roses[i] means rose i will bloom on day roses[i].
    Also given an int k, which is the minimum number of adjacent bloom roses
    required for a bouquet, and an int n, which is the number of bouquets we
    need. Return the earliest day that we can get n bouquets of roses.

    Example: Input: roses = [1, 2, 4, 9, 3, 4, 1], k = 2, n = 2
    Output: 4
    Explanation: day 1: [b, n, n, n, n, n, b] The first and the last rose
    bloom.

    day 2: [b, b, n, n, n, n, b] The second rose blooms. Here the first two
    bloom roses make a bouquet.

    day 3: [b, b, n, n, b, n, b]

    day 4: [b, b, b, n, b, b, b] Here the last three bloom roses make a
    bouquet, meeting the required n = 2 bouquets of bloom roses. So return day
    4.

    int minDaysBloom(vector<int>& roses, int k, int n)
    {

    }


    Constraints:
    In reality <unknown>, however I assume that:
    1) 1 <= roses[idx] <= INT_MAX.
    2) 0 <= idx <= roses.size()-1
    3) 1 <= roses.size() <= INT_MAX
    4) n * k <= roses.size(); // we're always able to make n Bouquets of size k

*/








/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(1) */
class Solution_Binary_Search{
public:
    int solution(std::vector<int>& roses, int k, int n)
    {
        int result = INT_MAX;
        int max_day = *std::max_element(roses.begin(), roses.end());

        int low_day  = 1;
        int high_day = max_day;
        while (low_day <= high_day)
        {
            int curr_day = (low_day + high_day) / 2;

            int consecutive_roses = 0;
            int bouquets = 0;
            for (int i = 0; i < roses.size(); i++)
            {
                if (roses[i] <= curr_day)
                    consecutive_roses++;
                else
                    consecutive_roses = 0;

                if (consecutive_roses == k)
                {
                    bouquets++;
                    consecutive_roses = 0;
                }
            }

            if (bouquets >= n)
                result = std::min(result, curr_day);

            if (bouquets >= n)
                high_day = curr_day - 1;
            else
                low_day  = curr_day + 1;
        }

        return result;
    }
};


int
main()
{
    Solution_Binary_Search sol_bin_search;

    /* Example 1 */
    std::vector<int> roses = {1, 2, 4, 9, 3, 4, 1};
    int k = 2;
    int n = 2;

    /* Example 2 */
    // std::vector<int> roses = {1, 5, 6, 2};
    // int k = 1;
    // int n = 4;

    /* Example 3 */
    // std::vector<int> roses = {1, 1, 1, 1};
    // int k = 4;
    // int n = 1;

    /* Example 4 */
    // std::vector<int> roses = {9};
    // int k = 1;
    // int n = 1;


    std::cout << "\n\t==========================";
    std::cout << "\n\t=== MIN DAYS TO BLOOM  ===";
    std::cout << "\n\t==========================\n";


    /* Write Input */
    std::cout << "\n\tK: " << k;
    std::cout << "\n\tN: " << n;
    bool first = true;
    std::cout << "\n\tRoses: [";
    for (auto x: roses)
    {
        if (!first)
            std::cout << ", ";

        std::cout << x;
        first = false;
    }
    std::cout << "]\n";


    /* Solution */
    int  result = sol_bin_search.solution(roses, k, n);


    /* Write Output */
    std::cout << "\n\tResult: " << result;

    std::cout << "\n\n";
    return 0;
}
