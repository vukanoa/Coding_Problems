#include <iostream>

/* Time  Complexity: O(1 * n) --> O(n) */ // Single pass
/* Space Complexity: O(1)              */
class Solution {
public:
    int solution(std::string& S)
    {
        int N = S.length();
        if (N == 1) return S[0] == 'a' ? 1 : 4;

        int can_be_inserted = 0;
        for (int i = 0; i < N; i++)
        {
            int a = 0;
            while (i < S.length() && S[i] == 'a' && a < 3){
                a++;
                i++;
            }

            if      (a == 3) return -1;
            else if (i == N) break;

            if      (i-1 < 0 || S[i-1] != 'a') can_be_inserted += 2;
            else if (i-2 < 0 || S[i-2] != 'a') can_be_inserted += 1;
        }

        if      (S[N-1] != 'a') can_be_inserted += 2;
        else if (S[N-2] != 'a') can_be_inserted += 1;

        return can_be_inserted;
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
