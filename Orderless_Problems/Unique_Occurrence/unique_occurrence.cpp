#include <iostream>
#include <vector>
#include <deque>
#include <unordered_map>

int solution(std::vector<int>& A)
{
	int n = A.size();
	std::unordered_map<int, int> umap;

	// O(n)
	// Count the occurrences of each number
	for (int i = 0; i < n; i++)
		umap[A[i]]++;

	std::vector<int> occur(n + 1, 0);

	// O(n)
	// Vector of occurrences
	for (const auto& entry : umap)
		occur[entry.second]++;


	std::deque<int> deque;
	bool flag = false;
	// O(n)
	// Push all occurences that don't happen in this array. But push only those
	// that are less than the largest occurrence in the array since we are
	// allower to delete only
	for (int i = n; i >= 0; i--)
	{
		if (flag == false && occur[i] != 0)
			flag = true;

		if (flag == true && occur[i] == 0)
			deque.push_back(i);
	}

	std::unordered_map<int, int> map_occur;

	// O(n)
	// Make a Hash Map of occurrences as a key
	for (const auto& entry : umap)
	{
		if (map_occur.find(entry.second) == map_occur.end())
			map_occur.insert({entry.second, 1});
		else
			map_occur[entry.second]++;
	}

	int deletions = 0;
	// O(n)
	for (auto& entry : map_occur)
	{
		while (entry.second > 1)
		{
			if (deque.empty())
				deletions += entry.first;
			else
			{
				deletions += entry.first - deque.front();
				deque.pop_front();
			}

			entry.second--;
		}
	}

	return deletions;
}


int
main()
{
	std::cout << "\n\t=========================";
	std::cout << "\n\t=== UNIQUE OCCURRENCE ===";
	std::cout << "\n\t=========================\n";

	/* Example 1 */
	// std::vector<int> A = {1, 1, 1, 2, 2, 2};

	/* Example 2 */
	// std::vector<int> A = {5, 3, 3, 2, 5, 2, 3, 2};

	/* Example 3 */
	// std::vector<int> A = {127, 15, 3, 8, 10};

	/* Example 4 */
	std::vector<int> A = {1000000, 1000000, 5, 5, 5, 2, 2, 2, 0, 0};

	/* Write Input */
	std::cout << "\n\tInput:";
	bool first = true;
	std::cout << "\n\t\tA: [";
	for (auto x: A)
	{
		if (!first)
			std::cout << ", ";

		std::cout << x;
		first = false;
	}
	std::cout << "]\n\n";


	/* Solution */
	int sol = solution(A);


	/* Write Output */
	std::cout << "\n\tSolution:";
	std::cout << "\n\t\tResult: " << solution(A);
	std::cout << "\n\n";

	return 0;
}
