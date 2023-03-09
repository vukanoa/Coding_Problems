#include <iostream>
#include <unordered_map>
#include <vector>

/*
	==============
	=== MEDIUM ===
	==============

	===========================
	763) Partition Labels
	===========================

	============
	Description:
	============

	You are given a string s. We want to partition the string into as many
	parts as possible so that each letter appears in at most one part.

	Note that the partition is done so that after concatenating all the parts
	in order, the resultant string should be s.

	Return a list of integers representing the size of these parts.

	================================================
	FUNCTION: vector<int> partitionLabels(string s);
	================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  s = "ababcbacadefegdehijkhklij"
	Output: [9, 7, 8]
	Explanation:
	The partition is "ababcbaca", "defegde", "hijhklij".
	This is a partition so that each letter appears in at most one part.
	A partition like "ababcbacadefegde", "hijhklij" is incorrect, because it
	splits s into less parts.

	--- Example 2 ---
	Input:  s = "eccbbbbdec"
	Output: [10]

	*** Constraints ***
	1 <= s.length <= 500
	s consists of lowercase English letters.

*/


/*
	------------
	--- IDEA ---
	------------

*/


/*
	------------
	--- IDEA ---
	------------

	It's my very messy idea, but it works at the end.

	We make a Hash Map:
		{ Key :   Value   }
		|  a  : [beg,end] |
		|  b  : [beg,end] |
		|  c  : [beg,end] |
		|  d  : [beg,end] |
		|  e  : [beg,end] |
		|  f  : [beg,end] |
		|  g  : [beg,end] |
		|  h  : [beg,end] |
		|  i  : [beg,end] |
		|  j  : [beg,end] |
		|  k  : [beg,end] |
		|  l  : [beg,end] |
		|  m  : [beg,end] |
		|  n  : [beg,end] |
		|  o  : [beg,end] |
		|  p  : [beg,end] |
		|  q  : [beg,end] |
		|  r  : [beg,end] |
		|  s  : [beg,end] |
		|  t  : [beg,end] |
		|  u  : [beg,end] |
		|  v  : [beg,end] |
		|  w  : [beg,end] |
		|  x  : [beg,end] |
		|  y  : [beg,end] |
		|  z  : [beg,end] |

	beg - Index of the place where that character first appeared in string s
	      (-1 if it doesn't appear at all)
		  Default: -1

	end - Index of the place where that character last appeared in string s
	      (-1 if it doesn't appear more than once)
		  Default: -1

	That's done in O(n).

	Now we iterate through an entire string s once again. Again, only once so
	that's also O(n).

*/



/*	Time  Beats: 29.16% */
/*  Space Beats:  5.51% */
/*	Time  Complexity: O(n) */
/*
	Space Complexity: O(1)
	Tehnically it's O(1) since we are told that s is consisted of only
	lowercase english letters. So making a Hash Map of size 26 will always be
	of size 26 no matter the length of string s.
*/
class Solution{
public:
	std::vector<int> partitionLabels(std::string s)
	{
		std::unordered_map<char, std::vector<int>> umap
		{
			{'a', std::vector(2, -1)},
			{'b', std::vector(2, -1)},
			{'c', std::vector(2, -1)},
			{'d', std::vector(2, -1)},
			{'e', std::vector(2, -1)},
			{'f', std::vector(2, -1)},
			{'g', std::vector(2, -1)},
			{'h', std::vector(2, -1)},
			{'i', std::vector(2, -1)},
			{'j', std::vector(2, -1)},
			{'k', std::vector(2, -1)},
			{'l', std::vector(2, -1)},
			{'m', std::vector(2, -1)},
			{'n', std::vector(2, -1)},
			{'o', std::vector(2, -1)},
			{'p', std::vector(2, -1)},
			{'q', std::vector(2, -1)},
			{'r', std::vector(2, -1)},
			{'s', std::vector(2, -1)},
			{'t', std::vector(2, -1)},
			{'u', std::vector(2, -1)},
			{'v', std::vector(2, -1)},
			{'w', std::vector(2, -1)},
			{'x', std::vector(2, -1)},
			{'y', std::vector(2, -1)},
			{'z', std::vector(2, -1)}
		};

		// O(n)
		for (int i = 0; i < s.length(); i++)
		{
			if (umap[s[i]][0] == -1)
				umap[s[i]][0] = i;
			else
				umap[s[i]][1] = i;
		}


		std::vector<int> ret;
		int prev_wall = 0;
		int wall = -1;
		int flag = 0;

		for (int i = 0; i < s.length(); i++)
		{
			if (umap[s[i]][1] == -1)
			{
				if (umap[s[i]][0] > wall || wall == -1)
				{
					if (wall != -1 && umap[s[i - 1]][1] != -1)
					{
						ret.push_back(wall - prev_wall + 1);

						prev_wall = wall + 1;
						wall = umap[s[i]][1];
					}
					ret.push_back(1);

                    prev_wall = ((i - 1) >= 0) ? (i - 1) : 0;
					wall = i;
					flag = 1;
				}
			}
			else if (umap[s[i]][0] > wall)
			{
				// Only for the very first element
				if (wall == -1)
				{
					prev_wall = umap[s[i]][0]; // Equivalent to prev_wall = i;
					wall      = umap[s[i]][1];
				}
				else
				{
					if (flag == 0)
						ret.push_back(wall - prev_wall + 1);

					prev_wall = wall + 1;
					wall = umap[s[i]][1];

					flag = 0;
				}
			}
			else if (umap[s[i]][1] > wall)
				wall = umap[s[i]][1];
		}

		if (umap[s[s.length() - 1]][1] != - 1)
			ret.push_back(wall - prev_wall + 1);

		return ret;
	}
};


int
main()
{
	Solution sol;

	/* Example 1 */
	// std::string s = "ababcbacadefegdehijhklij";

	/* Example 2 */
	// std::string s = "eccbbbbdec";

	/* Example 3 */
	// std::string s = "caedbdedda";

	/* Example 4 */
	std::string s = "eaaaabaaec";

	/* Example 5 */
	// std::string s = "vhaagbqkaq";

	/* Example 6 */
	// std::string s = "jybmxfgseq";

	std::cout << "\n\t========================";
	std::cout << "\n\t=== PARTITION LABELS ===";
	std::cout << "\n\t========================\n";

	/* Write Input */
	std::cout << "\n\t" << s << "\n";

	/* Solution */
	std::vector<int> ret = sol.partitionLabels(s);

	/* Write Output */
	bool first = true;
	std::cout << "\n\tOutput: [";
	for (auto x: ret)
	{
		if (!first)
			std::cout << ", ";

		std::cout << x;
		first = false;
	}
	std::cout << "]\n\n";


	return 0;
}
