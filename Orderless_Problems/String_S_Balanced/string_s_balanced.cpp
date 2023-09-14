/*
	Balanced:
	()
	()(())()
	()()()

	Not Balanced:
	(
	)()(
	))((

	My example:
	) (()) ))(
*/

#include <iostream>


class Solution{
public:
	int solution(std::string& S)
	{
		int add = 0;
		int indicator = 0;

		for (int i = 0; i < S.length(); i++)
		{
			if (S[i] == ')')
			{
				if (indicator > 0)
					indicator--;
				else
					add++;
			}
			else
				indicator++;
		}

		add += indicator;

		return add;
	}
};


int main()
{
	Solution sol;

	/* Example 1 */
	// std::string S = "()";

	/* Example 2 */
	// std::string S = "()(())()";

	/* Example 3 */
	// std::string S = "()()()";

	/* Example 4 */
	// std::string S = "(";

	/* Example 5 */
	// std::string S = ")()()(";

	/* Example 6 */
	std::string S = "))((";

	/* Example 7 */
	// std::string S = ")(())))()())";

	/* Example 8 */
	// std::string S = ")(())))(";

	/* Example 9 */
	// std::string S = ")()()";

	/* Example 10 */
	// std::string S = "";


	std::cout << "\n\t=========================";
	std::cout << "\n\t=== STRING S BALANCED ===";
	std::cout << "\n\t=========================\n";


	/* Write Input */
	std::cout << "\n\tInput: " << S << "\n";

	/* Solution */
	int add = sol.solution(S);

	/* Write Output */
	std::cout << "\n\tAdd: " << add << "\n\n";

	return 0;
}

