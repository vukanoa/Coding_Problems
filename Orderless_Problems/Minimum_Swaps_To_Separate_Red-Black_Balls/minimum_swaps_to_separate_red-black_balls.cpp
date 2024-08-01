#include <iostream>

/*

    You're given a string s consisting only of 'R' or 'B' characters that are
    representing Red and Blacks balls respectively.

    The goal is to separate Red and Black balls on two sides, without them
    overlapping, by swapping the least amount of times.


    Constraints:
    0 <= s.length <= 10^4
    s[i] is either 'R' or 'B'

    --- Example 1 ---
    Input:  s = ""
    Output: 0

    --- Example 2 ---
    Input:  s = "RRRRR"
    Output: 0

    --- Example 3 ---
    Input:  s = "-----"
    Output: 0

    --- Example 4 ---
    Input:  s = "R-R-R-R"
    Output: 2

    --- Example 6 ---
    Input:  s = "RRR-R-R-R"
    Output: 2

    --- Example 8 ---
    Input:  s = "---R--RR---RRR-RRR-"
    Output: 3

*/

using namespace std;

class Solution {
public:
    int minimum_swaps(string s)
    {
        const int n = s.length();

        if (n == 0)
            return 0;

        int half = n / 2; // Floor

        char left_type  = 'R';
        char right_type = 'B';

        int count_red = 0;
        for (int i = 0; i < half; i++)
        {
            if (s[i] == 'R')
                count_red++;
        }

        if (count_red <= half/2)
            swap(left_type, right_type);

        int swaps = 0;

        int left_idx  = 0;
        int right_idx = n-1;

        while (left_idx < n && right_idx >= 0)
        {
            while (left_idx < n && s[left_idx] == left_type)
                left_idx++;

            while (right_idx >= 0 && s[right_idx] == right_type)
                right_idx--;

            if (left_idx >= right_idx)
                break;

            swaps++;

            left_idx++;
            right_idx--;
        }

        return swaps;
    }
};


int
main()
{
    Solution sol;

    /* Example 1 */
    // string s = "";

    /* Example 2 */
    // string s = "RRRRR";

    /* Example 3 */
    // string s = "BBBBB";

    /* Example 4 */
    // string s = "RBRBRBR";

    /* Example 5 */
    // string s = "RRRBRBRBR";

    /* Example 6 */
    string s = "BBBRBBRRBBBRRRBRRRB";

    cout << "\n\t===============================";
    cout << "\n\t=== MINIMUM NUMBER OF SWAPS ===";
    cout << "\n\t===============================\n";

    /* Solution */
    int result = sol.minimum_swaps(s);

    cout << "\n\ts = \"" << s << "\"\n";
    cout << "\n\tOutput: " << result;

    cout << "\n\n";

    return 0;
}
