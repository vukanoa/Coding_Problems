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
	Input:  s = "ababcbacadefegdehijhklij"
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

	// TO DO

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




/*
	------------
	--- IDEA ---
	------------

	Let's look at the very first example:

	Input:  s = "ababcbacadefegdehijkhklij"
	Output: [9, 7, 8]

	"ababcbacadefegdehijkhklij"
	 #

	Immediately, we know that we cannot partition this string as:
	"a" | "babcbacadefegdehijkhklij"

	if there are additional "a" characters somewhere else in the string.
	And not only that, we can have multiple "a" characters, and we do.
	We care about the last "a" character the most. Once we stop here:

        "ababcbaca" | "defegdehijkhklij"
         #       ^
      first     last

	We are sure that all of the "a" characters are in this first portion of
	the string.

	So that's what we're trying to do, to create a partition where all "a"
	characters, in this case, are in a single partition and not anywhere
	else in the string.

	So, wouldn't it be convenient for us that everytime we see a character
	we could automatically know the index at which it occurs for the last
	time in string s?

	Maybe that character itself is the last occurence of it. (It appears
	only once in string s).

	We can do exactly that, thus we will make a Hash Map:
	We put a character in Hash Map only if we stumble upon it while iterating
	over string s.

         char   last_index
		{ Key : Value }
		|  a  :  end  |
		|  b  :  end  |
		|  c  :  end  |
		|  d  :  end  |
		|  e  :  end  |
		|  f  :  end  |
		|  g  :  end  |
		|  h  :  end  |
		|  i  :  end  |
		|  j  :  end  |
		|  k  :  end  |
		|  l  :  end  |
		|  m  :  end  |
		|  n  :  end  |
		|  o  :  end  |
		|  p  :  end  |
		|  q  :  end  |
		|  r  :  end  |
		|  s  :  end  |
		|  t  :  end  |
		|  u  :  end  |
		|  v  :  end  |
		|  w  :  end  |
		|  x  :  end  |
		|  y  :  end  |
		|  z  :  end  |

	We take every single unique character in the input string and we map it to
	the last index it occurs at.

	 0 ...               ... 23
	"ababcbacadefegdehijkhklij"

	We will iterate through an entire string s, and this is what our Hash Map
	will look like after the iteration:

         char   last_index
		{ Key : Value }
		|  a  :   8   |
		|  b  :   5   |
		|  c  :   7   |
		|  d  :  14   |
		|  e  :  15   |
		|  f  :  11   |
		|  g  :  13   |
		|  h  :  18   |
		|  i  :  22   |
		|  j  :  23   |
		|  k  :  20   |
		|  l  :  21   |

	It would be helpful for us, us we're iterating through this the 2nd time
	(after we've created a Hash Map) if we maintain the size of the current
	partition ourselves:
		int size = 0; // At the beginning

	and as we iterate through this, we for example character "a" at index 0,
	but the last occurence of "a" is at index 8. So we can keep track of
	another variable:
		int wall = 0;

	which is going to tell us what's the end of our partition as far as we know
	so far.

	So far we're assuming that our partitition ends at index 8, but that
	doesn't have to be the case.

	Let's say that our initial example looked just a bit different:

	instead of: "ababcbacadefegdehijkhklij"
	we have   : "ababcbacabdefegdehijkhklij"

	So in that case, for i = 0, we will say that so far out partition is:
		from 0 to 8 (inclusive)

	However, the very next character, "b" in this case, woudl "extend" our wall
	variable value. The wall, or the current partition, won't end at index 8,
	but on index 9, since that is where "b" ends and "b" is between the first
	and last occurence of "a" so we have to put them in one partition, thus
	we just extend the wall even further, to the last occurrence of "b".

	|----------|
	0          8
	  |-----------|
	  1           9


	So we take:

	|-------------|
	0             9


	So let's Do a Simulation of this Algorithm:

	"ababcbacadefegdehijkhklij"
	size = 0;
	wall = 0;


	1) "ababcbacadefegdehijkhklij"
	    #

		size = 1
		wall = 8
		ret = []




	2) "ababcbacadefegdehijkhklij"
	     #

		size = 2
		last_index[b] <= wall so we don't have to update our wall.
		ret = []




	3) "ababcbacadefegdehijkhklij"
	      #

		size = 3
		wall = 8
		ret = []




	4) "ababcbacadefegdehijkhklij"
	       #

		size = 4
		last_index[b] <= wall so we don't have to update our wall.
		ret = []




	5) "ababcbacadefegdehijkhklij"
	        #

		size = 5
		last_index[c] <= wall so we don't have to update our wall.
		ret = []




	6) "ababcbacadefegdehijkhklij"
	         #

		size = 6
		last_index[b] <= wall so we don't have to update our wall.
		ret = []




	7) "ababcbacadefegdehijkhklij"
	          #

		size = 7
		wall = 8
		ret = []




	8) "ababcbacadefegdehijkhklij"
	           #

		size = 8
		last_index[c] <= wall so we don't have to update our wall.
		ret = []




	9) "ababcbacadefegdehijkhklij"
	            #

		size = 9
		i == wall so we put size in vector "ret" and reset size.
		ret = [9]
		size = 0;




	10) "ababcbacadefegdehijkhklij"
	              #

		size = 1
		last_index[h] > wall:
			wall = 14
		ret = [9]




	11) "ababcbacadefegdehijkhklij"
	               #

		size = 2
		last_index[e] > wall so we update our wall:
			wall = 15
		ret = [9]




	21) "ababcbacadefegdehijkhklij"
	                #

		size = 3
		last_index[f] <= wall so we don't have to update our wall.
		ret = [9]




	22) "ababcbacadefegdehijkhklij"
	                #

		size = 4
		last_index[e] <= wall so we don't have to update our wall
		ret = [9]
		size = 0;




	23) "ababcbacadefegdehijkhklij"
	                  #

		size = 5
		last_index[g] <= wall so we don't have to update our wall
		ret = [9]




	24) "ababcbacadefegdehijkhklij"
	                   #

		size = 6
		last_index[d] <= wall so we don't have to update our wall
		ret = [9]




	25) "ababcbacadefegdehijkhklij"
	                    #

		size = 7
		i == wall
		ret = [9]
		size = 0;




	23) "ababcbacadefegdehijkhklij"
	                  #

		size = 5
		last_index[g] <= wall so we don't have to update our wall
		ret = [9]




	24) "ababcbacadefegdehijkhklij"
	                   #

		size = 6
		last_index[d] <= wall so we don't have to update our wall
		ret = [9]




	25) "ababcbacadefegdehijkhklij"
	                    #

		size = 7
		i == wall so we put size in vector "ret" and reset size.
		ret = [9, 7]
		size = 0;




	26) "ababcbacadefegdehijkhklij"
	                     #

		size = 1
		last_index[h] > wall:
			wall = 19
		ret = [9, 7]




	27) "ababcbacadefegdehijkhklij"
	                      #

		size = 2
		last_index[i] > wall:
			wall = 22
		ret = [9, 7]




	28) "ababcbacadefegdehijkhklij"
	                       #

		size = 3
		last_index[j] > wall:
			wall = 23
		ret = [9, 7]




	29) "ababcbacadefegdehijkhklij"
	                         #

		size = 4
		last_index[h] <= wall so we don't have to update our wall
		ret = [9, 7]




	30) "ababcbacadefegdehijkhklij"
	                          #

		size = 5
		last_index[k] <= wall so we don't have to update our wall
		ret = [9, 7]




	31) "ababcbacadefegdehijkhklij"
	                           #

		size = 6
		last_index[l] <= wall so we don't have to update our wall
		ret = [9, 7]




	32) "ababcbacadefegdehijkhklij"
	                            #

		size = 7
		last_index[i] <= wall so we don't have to update our wall
		ret = [9, 7]




	33) "ababcbacadefegdehijkhklij"
	                             #

		size = 8
		i == wall so we put size in vector "ret" and reset size.
		ret = [9, 7, 8]
		size = 0




	We iterated through an entire string s.
	Return vector ret.

*/


/* Time  Beats: % */
/* Space Beats: % */
/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Neat{
public:
	std::vector<int> partitionLabels(std::string s)
	{
		std::unordered_map<char, int> last_index;

		// O(n)
		for (int i = 0; i < s.length(); i++)
			last_index[s[i]] = i;


		std::vector<int> ret;
		int size = 0;
		int wall = 0;

		// O(n)
		for (int i = 0; i < s.length(); i++)
		{
			size++;
			wall = std::max(wall, last_index[s[i]]);

			if (i == wall)
			{
				ret.push_back(size);
				size = 0;
			}
		}

		return ret;
	}
};


int
main()
{
	Solution sol;
	Solution_Neat sol_neat;

	/* Example 1 */
	std::string s = "ababcbacadefegdehijhklij";

	/* Example 2 */
	// std::string s = "eccbbbbdec";

	/* Example 3 */
	// std::string s = "caedbdedda";

	/* Example 4 */
	// std::string s = "eaaaabaaec";

	/* Example 5 */
	// std::string s = "vhaagbqkaq";

	/* Example 6 */
	// std::string s = "jybmxfgseq";

	std::cout << "\n\t========================";
	std::cout << "\n\t=== PARTITION LABELS ===";
	std::cout << "\n\t========================\n";

	/* Write Input */
	std::cout << "\n\ts = \"" << s << "\"\n";

	/* Solution */
	// std::vector<int> ret = sol.partitionLabels(s);
	std::vector<int> ret = sol_neat.partitionLabels(s);

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
