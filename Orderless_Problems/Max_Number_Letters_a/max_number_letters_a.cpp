#include <iostream>

class Solution{
public:
	int solution(std::string& s)
	{
		int left = 0;

		// Find leftmost non-a letter
		while (left < s.length())
		{
			if (left == 3)
				return -1;

			if (s[left] != 'a')
				break;

			left++;
		}

		int count = 0;

		if (left == s.length()) // We haven't found non-a letter
		{
			if (left == 3)
				return -1;
			else if (left == 2)
				return 0;
			else
				return 1;
		}
		else if (left < 2) // left: 1 => "ab.." -> add 1   |  left: 0 => "b.." -> add 2
			count += 2 - left; // Takes care of the front

		int right = left + 1;

		// Sliding Window
		while (right < s.length())
		{
			if (right - left > 3)
				return -1; // substring "aaa"

			if (s[right] == 'a')
				right++;
			else
			{
				// 2 -> max permissible nubmer of consecuive a's
				count += 2 - (right - left - 1);

				left  = right;
				right = right + 1;
			}
		}

		// Takes care of the ending
		count += 2 - (right - left - 1);

		return count;
	}
};


int
main()
{
	Solution sol;

	/* Example 1 */
	std::string s = "aabab";

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

	std::cout << "\n\t=============================";
	std::cout << "\n\t=== MAX NUMBERS LETTERS A ===";
	std::cout << "\n\t=============================\n\n";


	/* Write Input */
	std::cout << "\n\tInput: " << s << "\n";

	/* Solution */
	int count = sol.solution(s);

	/* Write Output */
	std::cout << "\n\tOut: " << count << "\n\n";

	return 0;
}

