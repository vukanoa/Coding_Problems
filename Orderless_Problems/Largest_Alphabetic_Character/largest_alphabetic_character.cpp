#include <iostream>
#include <vector>

/*
	Input: str = “admeDCAB” 
	Output: "D" 
	Explanation: 
	Both the uppercase and lowercase characters for letter D is present in the
	string and it is also the largest alphabetical character, hence our output
	is D.

	Input: str = “dAeB” 
	Output: "-1"
	Explanation: 
	Although the largest character is d in the string but the uppercase version
	is not present hence the output is -1. 

*/

class Solution{
public:
	std::string largestCharacter(std::string str)
	{
		std::vector<int> lowercase(26, 0);
		std::vector<int> uppercase(26, 0);

		for (int i = 0; i < str.length(); i++)
		{
			if (str[i] >= 65 && str[i] <= 90)
				lowercase[str[i] - 65]++;
			else if (str[i] >= 97 && str[i] <= 122)
				uppercase[str[i] - 97]++;
		}

		for (int i = 25; i >= 0; i--)
		{
			if (lowercase[i] && uppercase[i])
			{
				std::string ret;
				ret.append(1,  "ABCDEFGHIJKLMNOPQRSTUVWXYZ"[i]);

				return ret;
			}
		}

		return "-1";
	}
};


int
main()
{
	Solution sol;

	/* Example 1 */
	// std::string str = "admeDCAB";

	/* Example 2 */
	// std::string str = "a";

	/* Example 3 */
	// std::string str = "";

	/* Example 4 */
	// std::string str = "admeCAB";

	/* Example 5 */
	std::string str = "aMceDMAB";

	/* Example 6 */
	//mstd::string str = "amceDMAB";

	std::cout << "\n\t=================================";
	std::cout << "\n\t=== LARGEST ALPHABETIC NUMBER ===";
	std::cout << "\n\t=================================\n";


	/* Write Input */
	std::cout << "\n\tInput:  " << "\"" << str << "\"\n";

	/* Solution */
	std::string result = sol.largestCharacter(str);

	/* Write Output */
	std::cout << "\n\tOutput: " << "\"" << result << "\"\n\n";

	return 0;
}
