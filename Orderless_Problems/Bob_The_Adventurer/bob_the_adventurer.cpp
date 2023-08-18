#include <iostream>
#include <vector>
#include <unordered_set>

#include <iomanip>


struct Point2D{
	int x;
	int y;
};

class Solution{
public:
	int solution(std::vector<Point2D>& A)
	{
		std::vector<Point2D> I;
		std::vector<Point2D> II;
		std::vector<Point2D> III;
		std::vector<Point2D> IV;
		
		for (const auto& point : A)
		{
			if (point.x <= 0 && point.y >= 0)
				I.push_back(point);
			else if (point.x >= 0 && point.y >= 0)
				II.push_back(point);
			else if (point.x >= 0 && point.y <= 0)
				III.push_back(point);
			else if (point.x <= 0 && point.y <= 0)
				IV.push_back(point);
		}

		int rays = 0;
		std::unordered_set<double> slopes;

		// O(n)
		for (int i = 0; i < I.size(); i++)
			check_slope(I[i], slopes, rays);

		slopes.clear();

		// O(n)
		for (int i = 0; i < II.size(); i++)
			check_slope(II[i], slopes, rays);

		slopes.clear();

		// O(n)
		for (int i = 0; i < III.size(); i++)
			check_slope(III[i], slopes, rays);

		slopes.clear();

		// O(n)
		for (int i = 0; i < IV.size(); i++)
			check_slope(IV[i], slopes, rays);

		return rays;
	}

private:
	void check_slope(const Point2D &point, std::unordered_set<double>& slopes, int& rays)
	{
		int x_diff = point.x - 0;
		int y_diff = point.y - 0;

		double curr_slope = y_diff / x_diff;

		if (slopes.find(curr_slope) == slopes.end())
		{
			slopes.insert(curr_slope);
			rays++;
		}
	}
};


int main()
{
	Solution sol;
	std::vector<Point2D> A;

	/* Example 1 */
	// Point2D p1 {.x= -1, .y= -2};
	// Point2D p2 {.x=  1, .y=  2};
	// Point2D p3 {.x=  2, .y=  4};
	// Point2D p4 {.x= -3, .y=  2};
	// Point2D p5 {.x=  2, .y= -2};

	// A = {p1, p2, p3, p4, p5};



	/* Example 2 */
	// Point2D p1 {.x= -1, .y= -2};
	// Point2D p2 {.x=  2, .y=  2}; // Change to x = 2, y = 2
	// Point2D p3 {.x=  2, .y=  4};
	// Point2D p4 {.x= -3, .y=  2};
	// Point2D p5 {.x=  2, .y= -2};

	// A = {p1, p2, p3, p4, p5};



	/* Example 2 */
	Point2D p1 {.x= -1, .y= -2};
	Point2D p2 {.x=  1, .y=  2};
	Point2D p3 {.x=  2, .y=  4};
	Point2D p4 {.x= -3, .y=  2};
	Point2D p5 {.x=  2, .y= -2};
	Point2D p6 {.x=  3, .y=  3};  
	Point2D p7 {.x=  3, .y=  6};  
	Point2D p8 {.x= -3, .y= -6};
	Point2D p9 {.x= -3, .y= -1};

	A = {p1, p2, p3, p4, p5, p6, p7, p8, p9};



	std::cout << "\n\t========================";
	std::cout << "\n\t== BOB THE ADVENTURER ==";
	std::cout << "\n\t========================\n";


	/* Write Input */
	std::cout << "\n\tPoints:";
	for (const auto& p : A)
		std::cout << "\n\t\t(" << std::setw(2) << p.x << ", " << std::setw(2) << p.y << ")";

	/* Solution */
	int rays = sol.solution(A);

	/* Write Output */
	std::cout << "\n\n\tRays: " << rays << "\n\n";

	return 0;
}

