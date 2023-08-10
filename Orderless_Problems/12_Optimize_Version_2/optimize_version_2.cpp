#include <algorithm>
#include <iostream>
#include <unordered_map>

int original(vector<int> &A)
{
	int N = A.size();
	int result = 0;

	for (int i = 0; i < N; i++)
		for (int j = i; j < N; j++)
			if (A[i] == A[j]) // Now when they are the SAME!
				result = max(result, j - i);
	
	return result;
}

/* ====================== */
/* === FIRST SOLUTION === */
/* ====================== */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
int solution_1(std::vector<int>& A)
{
	int N = A.size();
	int result = 0;

	std::unordered_map<int, std::pair<int, int>> umap;

	// O(N)
	for (int i = 0; i < N; i++)
	{
		if (umap.find(A[i]) == umap.end())
			umap[A[i]] = {i, i};
		else
		{
			std::pair<int, int> &ref_pair = umap[A[i]];
			ref_pair.second = i;
		}
	}

	// O(N)
	for (auto& row : umap)
	{
		// Take the value(pair)
		std::pair<int, int> tmp_pair = row.second;

		std::max(result, tmp_pair.second - tmp_pair.first);
	}

	return result;
}

/* ======================= */
/* === SECOND SOLUTION === */
/* ======================= */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
int solution_2(std::vector<int>& A)
{
	int N = A.size();
	int result = 0;

	std::unordered_map<int, int> umap_first_appearance;

	for (int i = 0; i < N; i++)
	{
		if (umap_first_appearance.find(A[i]) != umap_first_appearance.end())
			result = std::max(result, i - umap_first_appearance[A[i]]);
		else
			umap_first_appearance[A[i]] = i;
	}

	return result;
}
