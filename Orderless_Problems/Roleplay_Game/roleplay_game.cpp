/*
	Examples:
	
	1. T = [0, 0, 1, 1],              A = [2],               return 3

	2. T = [0, 0, 0, 0, 2, 3, 3],     A = [2, 5, 6],         return 5

	3. T = [0, 0, 1, 2],              A = [1, 2],            return 3

	4. T = [0, 3, 0, 0, 5, 0, 5],     A = [4, 2, 6, 1, 0],   return 7

	N is an integer within the range [1..100000]
	M is an integer within the range [1..N]
	Each element of arrays T and A is an integer within the range [1..N]
	Skills form a tree rooted at 0
	The elements of A are all distinct

*/

#include <iostream>
#include <vector>
#include <unordered_set>

/* Similar to Course Schedule(Topological Sort) */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution{
public:
	int solution(std::vector<int>& T, std::vector<int>& A)
	{
		std::unordered_set<int> uset_learned;

		uset_learned.insert(0);
		int min_to_learn = 1; // 0 is learnt by default(N is at least 1)

		for (int i = 0; i < A.size(); i++)
			topological(T, uset_learned, min_to_learn, A[i]);

		return min_to_learn;
	}

private:
	void topological(std::vector<int>& T,
	                 std::unordered_set<int>& uset_learned,
	                 int& min_to_learn,
	                 int i)
	{
		if (i == 0) // It's added by default
			return;

		// Already learned
		if (uset_learned.find(T[i]) != uset_learned.end())
		{
			uset_learned.insert(i);
			min_to_learn++;

			return;
		}

		topological(T, uset_learned, min_to_learn, T[i]);

		uset_learned.insert(i);
		min_to_learn++;
	}
};


int
main()
{
	Solution sol;

	/* Example 1 */
	// std::vector<int> T = {0, 0, 1, 1};
	// std::vector<int> A = {2};

	/* Example 2 */
	// std::vector<int> T = {0, 0, 0, 0, 2, 3, 3};
	// std::vector<int> A = {2, 5, 6};

	/* Example 3 */
	// std::vector<int> T = {0, 0, 1, 2};
	// std::vector<int> A = {1, 2};

	/* Example 4 */
	std::vector<int> T = {0, 3, 0, 0, 5, 0, 5};
	std::vector<int> A = {4, 2, 6, 1, 0};

	/* Example 5 */
	// std::vector<int> T = {0, 0, 1, 1};
	// std::vector<int> A = {0, 2};


	std::cout << "\n\t=====================";
	std::cout << "\n\t=== ROLEPLAY GAME ===";
	std::cout << "\n\t=====================\n";


	/* Write Input */
	bool first = true;
	std::cout << "\n\tT: [";
	for (auto x: T)
	{
		if (!first)
			std::cout << ", ";

		std::cout << x;
		first = false;
	}
	std::cout << "]";

	first = true;
	std::cout << "\n\tA: [";
	for (auto x: A)
	{
		if (!first)
			std::cout << ", ";

		std::cout << x;
		first = false;
	}
	std::cout << "]\n";


	/* Solution */
	int min_to_learn = sol.solution(T, A);


	/* Write Output */
	std::cout << "\n\tMin to Learn: " << min_to_learn << "\n\n";


	return 0;
}
