#include <iostream>

/*
	-- Example 1 --
	aabab
	aabaabaa
	3

	-- Example 2 -- 
	dog
	aadaaoaagaa
	8
	
	-- Example 3 --
	aa
	0

	-- Example 4 --
	baaa
	-1
*/

using namespace std;

int
solution(string& S)
{
	if (S.size() > 200000)
		return -1; // Invalid number of characters N
	
	if (S.empty())
		return -1; // Invalid input. String must have at least 1 character

	int cnt = 0; // Count consecutive letters 'a'

	// Check if there's a substring 'aaa' in the string S
	for (auto x : S)
	{
		if (x == 'a')
		{
			cnt++;
			if (cnt >= 3)
				return -1; // Substring exists
		}
		else
			cnt = 0;
	}

	int ret_count = 0; // Total number of added letters 'a'
	unsigned i = 0; // Need to use it after the for loop
	cnt = 0; // Count letters 'a' before the current non 'a' character

	for (i = 0; i < S.size(); i++)
	{
		if (i == 0 && S[i] != 'a')
		{
			ret_count += 2;
			cnt = 0;
		}
		else if (S[i] != 'a')
		{
			if (cnt == 0)
				ret_count += 2;
			else if (cnt == 1)
				ret_count += 1;

			cnt = 0;
		}
		else
			cnt++;
	}

	if (S[i - 1] != 'a')
		ret_count += 2;
	else
	{
		if (cnt == 1)
			ret_count += 1;
	}

	return ret_count;
}


int
main()
{
	/* Examples */
	string S = "aabab";
	// string S = "dog";
	// string S = "aa";
	// string S = "baaa";
	// string S = "abrafa";
	// string S = "abraafa";
	// string S = "b";
	// string S = "a";

	std::cout << "\n\tSolution is: " << solution(S) << "\n\n";

	return 0;
}
