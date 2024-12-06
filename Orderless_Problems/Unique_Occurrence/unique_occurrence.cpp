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



/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */ // Usually it's going to be much less than n
class Solution_2 {
public:
    int solution(vector<int>& A)
    {
        int result = 0;

        int highest_occurrence_times = 0;
        int lowest__occurrence_times = INT_MAX;

        // O(n)
        unordered_map<int, int> umap_occurrences;
        for (const int& num : A)
            umap_occurrences[num]++;

        // O(n)
        for (const auto& entry : umap_occurrences)
        {
            highest_occurrence_times = max(highest_occurrence_times, entry.second);
            lowest__occurrence_times = min(lowest__occurrence_times, entry.second);
        }

        // O(n)
        vector<vector<int>> occurrences(highest_occurrence_times+1);
        // occurrences[0] is NOT going to be used

        // O(n) at worst, but usually much smaller
        for (const auto& entry : umap_occurrences)
            occurrences[entry.second].push_back(entry.first);

        int curr_frequency  = highest_occurrence_times;
        int first_available = lowest__occurrence_times - 1;

        // O(n), even if there is a nested while-loop, we only go through n elements at most
        while (curr_frequency >= lowest__occurrence_times)
        {
            while (occurrences[curr_frequency].size() > 1)
            {
                if (first_available == 0)
                {
                    result += (occurrences[curr_frequency].size()-1) * (curr_frequency - 0);

                    occurrences[curr_frequency] = {occurrences[curr_frequency][0]};
                    break;
                }
                else
                {
                    result += curr_frequency - first_available;

                    occurrences[curr_frequency].pop_back();
                    first_available--;
                }
            }

            curr_frequency--;
        }

        return result;
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
