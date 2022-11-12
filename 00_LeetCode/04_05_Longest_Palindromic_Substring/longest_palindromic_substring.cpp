#include <iostream>
#include <cstring>

/*
	==============
	=== MEDIUM ===
	==============

	================================
	5) Longest Palindromic Substring
	================================

	Given a string s, return the longest palindromic substring in s

	--- Example 1 ---
	Input: s = "babad"
	Output: "bab"
	Explanation: "aba" is also a valid answer

	--- Example 2 ---
	Input: s = "cbbd"
	Output: "bb"

	*** Constraints ***
	1 <= s.length <= 1000
	s consists of only digits and English letters

	TODO: Implement Manacher's Algorithm

*/


using namespace std;

/*
	Possible Time Complexities Solutions:
	O(n^3) -> O(n^2 * logn) -> O(n^2) -> O(n)

	O(n) -> Manacher's Algorithm
*/

/* ------------------------------------------------------------------------- */

/*
	==============
	=== O(n^3) ===
	==============
*/

bool is_palindrome(string s) // bool is_palindrome(const string& s)
{
	string reversed = string(s.rbegin(), s.rend()); // O(n)
	
	return s == reversed;
}

class Solution_n3 {
public:
	string longestPalindrome(string s)
	{
		int n = s.length();
		int longest = 0;
		string longest_substr = "";

		for (int L = 0; L < n; L++)
		{
			for (int R = L; R < n; R++)
			{
				int length = R - L + 1;
				string substr = s.substr(L, length);

				/*
					C++ has lazy if statements so it's faster to check for the
					lenght first
				*/
				if (length > longest && is_palindrome(substr))
				{
					longest = length;
					longest_substr = substr; // O(n); Improved version looks like:
					// longest_substr = s.substr(L, R);
					// longest_start = L;
					// longest_end   = R;
				}
			}
		}
		// Improved:
		// return s.substr(longest_start, longest_end);
		// Now the "copying" still has to go through an entire string
		// but now it happens only once. At the very end. So it's constant.

		return longest_substr;
	}
	
};

/* ------------------------------------------------------------------------- */

/*
	=====================
	=== O(n^2 * logn) ===
	=====================
*/

/*
bool is_palindrome(string s) // bool is_palindrome(const string& s)
{
	string reversed = string(s.rbegin(), s.rend()); // O(n)
	
	return s == reversed;
}
*/


// Palindrome substring exist of length x
int palindrome_substring_exist(int x, string s)
{
	int n = s.length();
	for (int L = 0; L + x <= n; L++)
	{
		if (is_palindrome(s.substr(L, x)))
			return L;
	}

	return -1;
}

class Solution_nlogn {
public:
	string longestPalindrome(string s)
	{
		int longest = 0;
		string longest_substr = "";
		int n = s.length();

		for (int parity: {0, 1})
		{
			int low  = 1;
			int high = n;

			if (low % 2 != parity)
				low++;

			if (high % 2 != parity)
				high--;

			while (low <= high)
			{
				int mid = (low + high) / 2;

				if (mid % 2 != parity)
					mid++;

				if (mid > high)
					break;

				int found = palindrome_substring_exist(mid, s);
				if (found != -1)
				{
					if (mid > longest)
					{
						longest = mid;
						longest_substr = s.substr(found, mid);
					}
					low = mid + 2;
				}
				else
					high = mid - 2;
			}
		}

		return longest_substr;
	}
};

/* ------------------------------------------------------------------------- */

/*
	==============
	=== O(n^2) ===
	==============
*/

class Solution_n2 {
public:
	string longestPalindrome(string s)
	{
		int longest = 0;
		string longest_substr = "";
		int n = s.length();

		for (int mid = 0; mid < n; mid++)
		{
			for (int x = 0; mid - x >= 0 && mid + x < n; x++)
			{
				if (s[mid - x] != s[mid + x])
					break;

				int length = 2 * x + 1;
				if (length > longest)
				{
					longest = length;
					longest_substr = s.substr(mid - x, length);
				}
			}
		}
		
		for (int mid = 0; mid < n - 1; mid++)
		{
			for (int x = 1; mid - x + 1 >= 0 && mid + x < n; x++)
			{
				if (s[mid - x + 1] != s[mid + x])
					break;

				int length = 2 * x;
				if (length > longest)
				{
					longest = length;
					longest_substr = s.substr(mid - x + 1, length);
				}
			}
		}

		return longest_substr;
	}
};

/* ------------------------------------------------------------------------- */

/*
	==============
	=== O(n^2) ===
	==============
*/

class Solution_n2_table{
public:
	string longestPalindrome(string s)
	{
		int n = s.length();
		int longest = 1;
		int start = 0;

		bool dp[n][n];
		memset(dp, 0, sizeof(dp));

		// Fill the diagonal
		for (int i = 0; i < n; ++i)
			dp[i][i] = true;

		// Fill with substrings of length 2
		for (int i = 0; i < n - 1; ++i)
		{
			if (s[i] == s[i + 1])
			{
				dp[i][i + 1] = true;
				start = i;
				longest = 2;
			}
		}

		// Find all substrings of length >= 3 and <= n
		for (int k = 3; k <= n; ++k)
		{
			for (int i = 0; i < n - k + 1; ++i)
			{
				int j = i + k - 1;

				if (dp[i + 1][j - 1] && s[i] == s[j]) // Reverse operations?
				{
					dp[i][j] = true;

					if (k > longest)
					{
						start = i;
						longest = k;
					}
				}
			}
		}

		string longest_substr = s.substr(start, longest);

		return longest_substr;
	}

};

/* ------------------------------------------------------------------------- */

int
main()
{
	// Solution_n3 sol_n3;          // O(n^3)
	// Solution_nlogn sol_nlogn;    // O(n^2 * logn)
	// Solution_n2 sol_n2;          // O(n^2)
	Solution_n2_table sol_n2_table; // O(n^2)

	/* Example 1 */
	// string s = "babad";

	/* Example 2 */
	// string s = "cbbd";

	/* Example 3 */
	// string s = "abaxabaxabb";

	/* Example 4 */
	string s = "abaxabaxabybaxabyb";


	cout << "\n\tString:\n\t\t\"" << s << "\"";

	// cout << "\n\n\n\tLongest palindrome substring is:\n\t\t" << "\"" << sol_n3.longestPalindrome(s) << "\"";    // O(n^3)
	// cout << "\n\n\n\tLongest palindrome substring is:\n\t\t" << "\"" << sol_nlogn.longestPalindrome(s) << "\""; // O(n^2 * logn)
	// cout << "\n\n\n\tLongest palindrome substring is:\n\t\t" << "\"" << sol_n2.longestPalindrome(s) << "\"";    // O(n^2)
	cout << "\n\n\n\tLongest palindrome substring is:\n\t\t" << "\"" << sol_n2_table.longestPalindrome(s) << "\""; // O(n^2)

	cout << "\n\n\n";

	return 0;
}
