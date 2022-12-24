#include <iostream>
#include <vector>

void print_matrix(std::vector<std::vector<int>>& matrix);


/*
	============
	=== HARD ===
	============

	===========================
	72) Edit Distance
	===========================

	============
	Description:
	============

	Given two strings "word1" and "word2", return the minimum number of
	operations required to convert word1 to word2.

	You have the following three operations permitted on a word:
		- Insert a character
		- Delete a character
		- Insert a character

	=======================================================
	FUNCTION: int mindDistance(string word1, string word2);
	=======================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  word1 = "horse", word2 = "ros"
	Output: 3

	--- Example 2 ---
	Input:  word1 = "intention", word2 = "execution"
	Output: 5

	*** Constraints ***
	0 <= word1.length, word2.length <= 500
	word1 and word2 consist of lowercase English letters

*/


/*
	------------
	--- IDEA ---
	------------

	Levensthein distance

	We can either:
		1. Replace
		2. Insert
		3. Delete
	a character.

	Word_1 = "horse"
	Word_2 = "ros"

	1) horse -> rorse (replace 'h' with 'r') [Replace]
	2) rorse -> rose  (delete 'r')           [Delete]
	3) rose  -> ros   (delete 'e')           [Delete]

	Consider another example:

	Word_1 = "benyam"

	(-1, 0) ""          // Base case. Substring from -1 to 0 is ""(empty)
	( 0, 0) "b"         // Substring from 0 to 0 => "b"
	( 0, 1) "be"        // Substring from 0 to 1 => "be"
	( 0, 2) "ben"       // Substring from 0 to 2 => "ben"
	( 0, 3) "beny"      // Substring from 0 to 3 => "beny"
	( 0, 4) "benya"     // Substring form 0 to 4 => "benya"
	( 0, 5) "benyam"    // Substring from 0 to 5 => "benyam"


	There are 4 possible situations in which we could find ourselves in.

	Word_1 = "benyam"
	          012345

	Word_2 = "ephrem"
	          012345

	So when we're doing character comparisons what we're going to do is check
	the transformation distance for every cross-section of substrings between
	the two strings.

	It will be clear when we draw our dp(dynamic programming) table, but for
	now let's see each situtation:

	---------------------------------------------------------------------------
	Situation 1: [Do nothing] // Characters DO match

	Word_1[0, 5] -> Word_2[0, 5]
	"benyam"        "ephrem"
          ^               ^

	Imagine that we're trying to transform a substring "benyam" into "ephrem".

	Notice: We care about LAST character of each sequence because that is what
	        we want to check whether we're going to: replace, insert, delete

	Since 'm' is shared between our two sequences of characters, that means
	that substring transformation from:
		Word_1[0, 5] -> Word_2[0, 5]

	IS GOING TO HAVE THE SAME EDIT DISTANCE AS SUBSTRING:
		Word_1[0, 4] -> Word_2[0, 4]

	Why?
	The 'm' characeters are the SAME. They will NOT contribute to our edit
	distance because they are the same thing.

	Therefore we do NOT have to take an action.
	No operations happens, no comparison happens. We do NOTHING.

	Answer to this problem:
		Word_1[0, 5] -> Word_2[0, 5]
	is the answer to this:
		Word_1[0, 4] -> Word_2[0, 4]

	subproblem.

	---------------------------------------------------------------------------

	Situation 2: [Replace] // Characters do NOT match

	Word_1[0, 3] -> Word_2[0, 2]
	"beny"           "eph"
	    ^               ^

	We're interestedin the LAST character. In this case 'y' does NOT match 'h'.
	We have 3 options:
		1. Replace
		2. Insert
		3. Delete

	Let's look it from this perspective.
	We can transform:
		Word_1[0, 2] -> Word_2[0, 1]
	    "ben"           "ep"

	We're taking one off of each of the substrings. Just look at the
	subproblem:
		Turning "ben" into "ep".

	After we turn "ben" into "ep", we add 'h' to "ep" so that now we have what
	we wanted at the beginning.

	This is the "Replace" operation.
		1. Ignore the character that don't match
		2. Transform "ben" to "ep"
		3. And the last character we replace. Replace 'y' with 'h'.

	So again, this is the Replacement operation. We transform everything before
	the mismatch and then at the mismatch we perform a Replace operation.

	---------------------------------------------------------------------------

	Situation 3: [Insert] // Characters do NOT match

	Let's look at the same transformation. We could've inserted instead.

	Word_1[0, 3] -> Word_2[0, 2]
	"beny"           "eph"
		^               ^

	But now what we do is - We subtract one from Word_2 and then transform:
		Word_1[0, 3] -> Word_2[0, 1]
		"beny"           "ep"

	So what we do is - We transform whole original string(subtring), into the
	substring of the previous string(substring), which is "ep" and then after
	that transformation I perform an insertion.

	We insert 'h' at the end of the transformation result "ep" and then we have
	what we wanted.

	Remember we want the minimum cost of these 3 options.

	---------------------------------------------------------------------------

	Situation 4: [Delete] // Characters do NOT match

	Same transformation:

	Word_1[0, 3] -> Word_2[0, 2]
	"beny"           "eph"
		^               ^

	Let's try deletion. Let's tranform:
		Word_1[0, 2] -> Word_2[0, 2]
		"ben"           "eph"

	We have effectively deleted the 'y'. We don't care about the 'y' anymore.

	---------------------------------------------------------------------------

	Dynamic Programming table:

           ""  "e" "p" "h" "r" "e" "m"
            0   1   2   3   4   5   6
          +---+---+---+---+---+---+---+
    ""  0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
          +---+---+---+---+---+---+---+
    "b" 1 | 0 | 0 | X | 0 | 0 | 0 | 0 |
          +---+---+---+---+---+---+---+
    "e" 2 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
          +---+---+---+---+---+---+---+
    "n" 3 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
          +---+---+---+---+---+---+---+
    "y" 4 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
          +---+---+---+---+---+---+---+
    "a" 5 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
          +---+---+---+---+---+---+---+
    "m" 6 | 0 | 0 | 0 | 0 | 0 | 0 | F |


	Word_1: benyam
	Word_2: ephrem

	Dynamic programming is not about remembering numbers, not about remembering
	patterns and how you fill the table. It's about - Knowing what is happening
	and why we do it this way.

	What are the subproblems? How are we building a globally optimal solution
	from the subproblems we're breaking down.

	So let's see this example(We're at 'X'):

           ""  "e" "p" "h" "r" "e" "m"
            0   1   2   3   4   5   6
          +---+---+---+---+---+---+---+
    ""  0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
          +---+---+---+---+---+---+---+
    "b" 1 | 0 | 0 | X | 0 | 0 | 0 | 0 |
          +---+---+---+---+---+---+---+
    "e" 2 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
          +---+---+---+---+---+---+---+
    "n" 3 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
          +---+---+---+---+---+---+---+
    "y" 4 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
          +---+---+---+---+---+---+---+
    "a" 5 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
          +---+---+---+---+---+---+---+
    "m" 6 | 0 | 0 | 0 | 0 | 0 | 0 | F |


	What does that mean to be in that position?
	It is a suproblem. Each of the cells are subproblems.

	The original question we asked is at 'F'(for Finish) in the table.
		dp[m][n]

	So the edit distance between two original strings is that field.
	But we answer every subproblem leading to that so that we get globally
	optimal answer.

	So, let's go back to 'X'.

	What does it mean to be at position 'X'. It means that we're trying to
	transform:
		"b" -> "ep"

	Index 'i' is the substring we take from the original string Word_1.
	Index 'j' is the substring we take from the orignal string Word_2.

	So each of the cells represents us with cross-sections of substring,
	finding the end distance for them and building up for our final answer at
	'F' (dp[m][n]).


	So first of all - If we need to transform an empty string into a any one of
	Word_2 substring or the Word_2 itself

	If I need to transform an empty string to "e"
	If I need to transform an empty string to "ep"
	If I need to transform an empty string to "eph"
	...

	We will always have to perform as many Insertions as it takes to turn an
	empty string into this new string with characters.

	So now the DP Table looks like this:

           ""  "e" "p" "h" "r" "e" "m"
            0   1   2   3   4   5   6
          +---+---+---+---+---+---+---+
    ""  0 | 0 | 1 | 2 | 3 | 4 | 5 | 6 |
          +---+---+---+---+---+---+---+
    "b" 1 | 0 | 0 | X | 0 | 0 | 0 | 0 |
          +---+---+---+---+---+---+---+
    "e" 2 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
          +---+---+---+---+---+---+---+
    "n" 3 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
          +---+---+---+---+---+---+---+
    "y" 4 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
          +---+---+---+---+---+---+---+
    "a" 5 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
          +---+---+---+---+---+---+---+
    "m" 6 | 0 | 0 | 0 | 0 | 0 | 0 | F |

	Looking at this table, it's obvious now that the edit distance between
	the empty string and a string "ep"(right above the X) is 2. That means
	we have to do 2 Insertions. 'e' and a 'p'. That is the answer to our
	subproblem.

	Each of these 'boxes' is a subproblem.


	Let's got the other way.
	If we just have the character 'b', and we're transforming it into an empty
	string, that means we just need 1 Deletion.

	If we have "be" and we're transforming it into an empty string, then we
	need 2 Deletions.

	And so on.
	Now we have a DP Table that looks like this:

           ""  "e" "p" "h" "r" "e" "m"
            0   1   2   3   4   5   6
          +---+---+---+---+---+---+---+
    ""  0 | 0 | 1 | 2 | 3 | 4 | 5 | 6 |
          +---+---+---+---+---+---+---+
    "b" 1 | 1 | 0 | 0 | 0 | 0 | 0 | 0 |
          +---+---+---+---+---+---+---+
    "e" 2 | 2 | 0 | 0 | 0 | 0 | 0 | 0 |
          +---+---+---+---+---+---+---+
    "n" 3 | 3 | 0 | 0 | 0 | 0 | 0 | 0 |
          +---+---+---+---+---+---+---+
    "y" 4 | 4 | 0 | 0 | 0 | 0 | 0 | 0 |
          +---+---+---+---+---+---+---+
    "a" 5 | 5 | 0 | 0 | 0 | 0 | 0 | 0 |
          +---+---+---+---+---+---+---+
    "m" 6 | 6 | 0 | 0 | 0 | 0 | 0 | F |


	Note: This is the bottom-up iterative solution.
	      Top-down recursive is also a possibility.

	We just need to understand what these subproblems mean and then we can
	implement it in any way that we like.

	So now let's get to work:
	Look at a position 'X' in each step:

           ""  "e" "p" "h" "r" "e" "m"
            0   1   2   3   4   5   6
          +---+---+---+---+---+---+---+
    ""  0 | 0 | 1 | 2 | 3 | 4 | 5 | 6 |
          +---+---+---+---+---+---+---+
    "b" 1 | 1 | X | 0 | 0 | 0 | 0 | 0 |
          +---+---+---+---+---+---+---+
    "e" 2 | 2 | 0 | 0 | 0 | 0 | 0 | 0 |
          +---+---+---+---+---+---+---+
    "n" 3 | 3 | 0 | 0 | 0 | 0 | 0 | 0 |
          +---+---+---+---+---+---+---+
    "y" 4 | 4 | 0 | 0 | 0 | 0 | 0 | 0 |
          +---+---+---+---+---+---+---+
    "a" 5 | 5 | 0 | 0 | 0 | 0 | 0 | 0 |
          +---+---+---+---+---+---+---+
    "m" 6 | 6 | 0 | 0 | 0 | 0 | 0 | F |

	does 'b' == 'e'? No!
	So we're going to have to perform an operation.

	What are our operations(this is our DP table zoomed in):
		Replace | Insert
		--------+-------------
		Delete  | (We're here)

	At position X, we have:
		   0    |    1
		--------+-------------
		   1    | (We're here)

	Which is the minimum of these? It's 0. In this case it's a Replacement.
	We're choosing to replace a 'b' to 'e'.
	And now since we performed an action we add 1 to the minimum of these 3
	options.
	Which in our case is:
		0 + 1 = 1

	Now at position X, we have:
		   0    |    1
		--------+-------------
		   1    |    1


	Let's look at some other situation: (Again look at position X):

	Note: We're not going "in order" here. This is just for explanation.
	In our code, we go from left to right for each row.

           ""  "e" "p" "h" "r" "e" "m"
            0   1   2   3   4   5   6
          +---+---+---+---+---+---+---+
    ""  0 | 0 | 1 | 2 | 3 | 4 | 5 | 6 |
          +---+---+---+---+---+---+---+
    "b" 1 | 1 | 1 | 0 | 0 | 0 | 0 | 0 |
          +---+---+---+---+---+---+---+
    "e" 2 | 2 | X | 0 | 0 | 0 | 0 | 0 |
          +---+---+---+---+---+---+---+
    "n" 3 | 3 | 0 | 0 | 0 | 0 | 0 | 0 |
          +---+---+---+---+---+---+---+
    "y" 4 | 4 | 0 | 0 | 0 | 0 | 0 | 0 |
          +---+---+---+---+---+---+---+
    "a" 5 | 5 | 0 | 0 | 0 | 0 | 0 | 0 |
          +---+---+---+---+---+---+---+
    "m" 6 | 6 | 0 | 0 | 0 | 0 | 0 | F |


	At position X these are the SAME characters.
	If we have an "e" and an "e", the distance is 0.
	It has the same distance as an "" string and an "" string.

	Matching characters mean we do NOTHING. (Situation 1)

	So the answer to our subproblem is these two string WITHOUT THAT MATCHING
	CHARACTER.

	So what we do for this position X (at 2, 1), we take it from (1, 0).
	We don't just magically take it from that sell for no reason. It's not just
	a random pattern.

	We're taking it because we do not need to factor this character in. It is
	NOT going to add to our Edit Distance.

	So our answer that goes into the cell is going to be the Edit Distanc
	without this character. Which is exactly like transforming:
		"b" -> ""
	That's why we're taking the diagonal value. It's the minimum number of
	operations that transform:
		"b" -> ""

	And since:
		"b" -> ""
	Edit Distance is going to be the same as:
		"be" -> "e"

	we just take the minimum number of operations of the substring(strings
	without this matching character 'e')

	And now we notice a pattern.
	Now we can just fill it, but it's not a random pattern. Now we understand
	why this pattern is the way it is.


           ""  "e" "p" "h" "r" "e" "m"
            0   1   2   3   4   5   6
          +---+---+---+---+---+---+---+
    ""  0 | 0 | 1 | 2 | 3 | 4 | 5 | 6 |
          +---+---+---+---+---+---+---+
    "b" 1 | 1 | 1 | 2 | 3 | 4 | 5 | 6 |
          +---+---+---+---+---+---+---+
    "e" 2 | 2 | 1 | 2 | 3 | 4 | 4 | 5 |
          +---+---+---+---+---+---+---+
    "n" 3 | 3 | 2 | 2 | 3 | 4 | 5 | 5 |
          +---+---+---+---+---+---+---+
    "y" 4 | 4 | 3 | 3 | 3 | 4 | 5 | 6 |
          +---+---+---+---+---+---+---+
    "a" 5 | 5 | 4 | 4 | 4 | 4 | 5 | 6 |
          +---+---+---+---+---+---+---+
    "m" 6 | 6 | 5 | 5 | 5 | 5 | 5 | 5 |

	For our final dp[m][n] since Word_1[6] == Word_2[6] (Characters 'm' match)
	The Edit Distance to transforming:
		"benyam" -> "ephrem"

	is the SAME as the subproblem:
		"benya" -> "ephre"

	That's why we take the value at dp[5][5] and don't add 1 to it.


	Note: Each time when we update dp[i][j] we only need:
		1. dp[i - 1][j - 1]
		2. dp[i - 1][  j  ]
		3. dp[  i  ][j - 1]

	We could optimize our space Complexity to two vectors.
	Code:
===============================================================================

	std::vector<int> previous(n + 1, 0);
	std::vector<int> current (n + 1, 0);

	for (int j = 0; j <= n; j++)
		previous[j] = j;

	for (int i = 1; i <= m; i++)
	{
		current[0] = i;

		for (int j = 1; j <= n; j++)
		{
			if (word1[i - 1] == word2[j - 1])
				current[j] = previous[j - 1];
			else
				current[j] = std::min(previous[j - 1], std::min(current[j - 1], previous[j])) + 1;
		}

		std::fill(previous.begin(), previous.end(), 0);
		std::swap(previous, current);
	}

	return previous[n];
===============================================================================



	We could also use only one vector:
	Code:
===============================================================================

	int previous;
	std::vector<int> current (n + 1, 0);

	for (int j = 0; j <= n; j++)
		current[j] = j;

	for (int i = 1; i <= m; i++)
	{
		previous = current[0];
		current[0] = i;

		for (int j = 1; j <= n; j++)
		{
			int tmp = current[j];

			if (word1[i - 1] == word2[j - 1])
				current[j] = previous;
			else
				current[j] = std::min(previous, std::min(current[j - 1], current[j])) + 1;

			previous = tmp;
		}
	}

	return current[n];
===============================================================================

*/


/* Time  Complexity: O(m * n) */
/* Space Complexity: O(n)
   But for purposes of readability and ease of understanding, I will leave
   the core with O(m * n) Space Complexity. Better Complexity is right above
   in the IDEA section
*/
class Solution {
public:
    int minDistance(std::string word1, std::string word2)
	{
        int m = word1.size();
		int n = word2.size();
        std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));

        for (int i = 1; i <= m; i++)
            dp[i][0] = i;

        for (int j = 1; j <= n; j++)
            dp[0][j] = j;

        for (int i = 1; i <= m; i++)
		{
            for (int j = 1; j <= n; j++)
			{
                if (word1[i - 1] == word2[j - 1])
                    dp[i][j] = dp[i - 1][j - 1];
                else
                    dp[i][j] = std::min(dp[i - 1][j - 1], std::min(dp[i][j - 1], dp[i - 1][j])) + 1;
            }
        }

		// print_matrix(dp);

        return dp[m][n];
    }
};


void
print_matrix(std::vector<std::vector<int>>& matrix)
{
	for (int i = 0; i < matrix.size(); i++)
	{
		std::cout << "\n\n\t\t";

		for (int j = 0; j < matrix[0].size(); j++)
			printf("%2d ", matrix[i][j]);
	}
	std::cout << "\n\n";
}

int
main()
{
	Solution sol;

	/* Example 1 */
	// std::string word1 = "horse";
	// std::string word2 = "ros";

	/* Example 2 */
	// std::string word1 = "intention";
	// std::string word2 = "execution";

	/* Example 3 */
	// std::string word1 = "book";
	// std::string word2 = "rookie";

	/* Example 4 */
	// std::string word1 = "linux";
	// std::string word2 = "unix";

	/* Example 5 */
	// std::string word1 = "stoicism";
	// std::string word2 = "seneca";

	/* Example 6 */
	// std::string word1 = "algorithm";
	// std::string word2 = "";

	/* Example 7 */
	// std::string word1 = "bicycle";
	// std::string word2 = "push-up";

	/* Example 8 */
	std::string word1 = "benyam";
	std::string word2 = "ephrem";


	std::cout << "\n\t=====================";
	std::cout << "\n\t=== EDIT DISTANCE ===";
	std::cout << "\n\t=====================\n";

	std::cout << "\n\tWord 1: \"" << word1 << "\"";
	std::cout << "\n\tWord 2: \"" << word2 << "\"\n";

	/* Solution */
	int result = sol.minDistance(word1, word2);

	std::cout << "\n\tOperations: " << result << "\n\n";

	return 0;
}
