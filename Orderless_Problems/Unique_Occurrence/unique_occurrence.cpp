#include <iostream>
#include <vector>
#include <deque>
#include <unordered_map>

class Solution{
public:
	int solution(std::vector<int>& A)
	{
		std::unordered_map<int, int> umap_num;
		std::unordered_map<int, int> umap_freq;

		for(const int& num : A)
			umap_num[num]++;

		for (const auto& entry : umap_num)
			umap_freq[entry.second]++;

		umap_freq[0] = 0;
		int deletions = 0;

		for (const auto& entry : umap_num)
		{
			int freq = entry.second;

			if(umap_freq[freq] > 1)
			{                        
				for(int j = freq-1; j >= 0; j--)
				{
					if(j == 0)
						deletions += freq;
					else if(umap_freq.count(j) == 0)
					{
						umap_freq[j] = 1;
						deletions += freq - j;

						break;
					} 
				}

				umap_freq[freq]--;
			}   
		} 

		return deletions;
	}
};


int
main()
{
	Solution sol;

	/* Example 1 */
	std::vector<int> A = {1, 1, 1, 2, 2, 2};

	/* Example 2 */
	// std::vector<int> A = {5, 3, 3, 2, 5, 2, 3, 2};

	/* Example 3 */
	// std::vector<int> A = {127, 15, 3, 8, 10};

	/* Example 4 */
	// std::vector<int> A = {1000000, 1000000, 5, 5, 5, 2, 2, 2, 0, 0};

	std::cout << "\n\t=========================";
	std::cout << "\n\t=== UNIQUE OCCURRENCE ===";
	std::cout << "\n\t=========================\n";


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
	int deletions = sol.solution(A);


	/* Write Output */
	std::cout << "\n\tSolution:";
	std::cout << "\n\t\tResult: " << deletions << "\n\n";

	return 0;
}
