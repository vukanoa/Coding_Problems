#include <iostream>

/* Time  Complexity: O(1 * n) --> O(n) */ // Single pass
/* Space Complexity: O(1)              */
class Solution {
public:
    int solution(std::string& S)
    {
        // Check for the presence of "aaa" in the original string
        if (S.find("aaa") != string::npos)
            return -1;

        int max_insertions = 0;
        int n = S.length();
        int consecutive_A = 0;

        // Traverse the string
        for (int i = 0; i < n; ++i)
        {
            if (S[i] == 'a')
            {
                consecutive_A++;
            }
            else
            {
                // For non-'a' characters, calculate insertions for the gap
                max_insertions += max(0, 2 - consecutive_A);
                consecutive_A = 0;
            }
        }

        // Account for trailing 'a' sequence
        max_insertions += max(0, 2 - consecutive_A);

        return max_insertions;
    }
};

int
main()
{
	Solution sol;

	/* Example 1 */
	// std::string s = "aabab";

	/* Example 2 */
	// std::string s = "dog";

	/* Example 3 */
	// std::string s = "aa";

	/* Example 4 */
	// std::string s = "baaaa";

	/* Example 5 */
	// std::string s = "abaabacba";

	/* Example 6 */
	// std::string s = "doag";

	/* Example 7 */
	// std::string s = "a";

	/* Example 8 */
	// std::string s = "b";

	/* Example 9 */
	// std::string s = "bc";

	/* Example 10 */
	// std::string s = "aaa";

	/* Example 11 */
    // std::string s = "cac";

	/* Example 12 */
    std::string s = "acca";

	/* Example 13 */
    // std::string s = "aacca";

	/* Example 14 */
    // std::string s = "accaa";

	/* Example 15 */
    // std::string s = "aaccaa";

	/* Example 16 */
    // std::string s = "aacacaa";


	std::cout << "\n\t=============================";
	std::cout << "\n\t=== MAX NUMBERS LETTERS A ===";
	std::cout << "\n\t=============================\n\n";


	/* Write Input */
	std::cout << "\n\tInput: \"" << s << "\"\n";

	/* Solution */
	int count   = sol.solution(s);

	/* Write Output */
	std::cout << "\n\tOut: " << count << "\n\n";

	return 0;
}
