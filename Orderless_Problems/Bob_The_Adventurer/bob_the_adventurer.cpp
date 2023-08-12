#include <iostream>
#include <vector>

struct Point2D{
	int x;
	int y;
};

int solution(std::vector<Point2D> &A);

int
main()
{
	struct Point2D one   {.x=-1, .y=-2};
	struct Point2D two   {.x= 1, .y= 2};
	struct Point2D three {.x= 2, .y= 4};
	struct Point2D four  {.x=-3, .y= 2};
	struct Point2D five  {.x= 2, .y=-2};
	struct Point2D six   {.x= 3, .y= 3};   // 3rd point in II  quadrant (2 Rays)
	struct Point2D seven {.x= 3, .y= 6};   // 4th point in II  quadrant (Still 2 Rays)
	struct Point2D eight {.x= -3, .y= -6}; // 2nd point in III quadrant (Still only 1 Ray)
	struct Point2D nine  {.x= -3, .y= -1}; // 3rd point in III quadrant (2 Rays)

	std::vector<Point2D> A = {one, two, three, four, five, six, seven, eight, nine};
	std::cout << "\n\t======================\n";
	std::cout << "\t=== NUMBER OF RAYS ===\n";
	std::cout << "\t======================\n";

	std::cout << "\n\tPoints: \n";
	for (auto p : A)
	{
		std::cout << "\t\t(" << p.x << ", " << p.y << ")";
		if (p.x < 0 && p.y > 0)
			std::cout << "\t\tI Quadrant\n";
		else if (p.x > 0 && p.y > 0)
			std::cout << "\t\t\tII Quadrant\n";
		else if (p.x < 0 && p.y < 0)
			std::cout << "\t\t\tIII Quadrant\n"; // Why is this formatted this way?
		else
			std::cout << "\t\t\t\t\tIV Quadrant\n";
	}

	int sol = solution(A);
	std::cout << "\n\tSolution: " << sol << "\n\n";

	return 0;
}

bool check_ray_passing(int x1, int y1, int x2, int y2)
{
   return (x1 * (y2 - y1) == y1 * (x2 - x1));
}


int
solution(std::vector<Point2D> &A)
{
	int quadrant = -1;
	int count = 0;
	int ret_count = 0;

	while (quadrant < 3)
	{
		quadrant++;
		switch(quadrant)
		{
			case 0:
				for (auto point: A)
					if (point.x < 0 && point.y > 0)
						count++;

				if (count == 0)
					break;
				else if (count == 1)
					ret_count++;
				else if (count == 2)
				{
					struct Point2D one {.x=0, .y =0};
					struct Point2D two {.x=0, .y =0};

					for (auto point: A)
					{
						if (point.x < 0 && point.y > 0)
						{
							if (one.x == 0 && one.y == 0)
							{
								one.x = point.x;
								one.y = point.y;
							}
							else
							{
								two.x = point.x;
								two.y = point.y;
							}
						}
					}

					if(check_ray_passing(one.x, one.y, two.x, two.y))
						ret_count += 1;
					else
						ret_count += 2;
				}
				else // More than two points
				{
					std::vector<Point2D> points_this_quadrant;
					/* 
						It would be O(n*logn) if I was to implement  unordered_set<Point2D> 
						Inefficient because of using of another vector
						O(n^2) if every point was in a single quadrant
					 */
					std::vector<Point2D> set;

					// O(n)
					for (auto point: A)
					{
						if (point.x < 0 && point.y > 0)
							points_this_quadrant.push_back(point);
					}

					auto first_point = points_this_quadrant.begin();
					// set.push_back(first_point);

					ret_count++; // It certainly has at least one Ray if we have 3 points in this quadrant
					int flag = 0; // New Ray

					for (auto pnt : points_this_quadrant)
					{
						// If it's not the very first point in this quadrant
						if (pnt.x != first_point->x || pnt.y != first_point->y)
						{
							for (auto already: set)
							{
								if (check_ray_passing(already.x, already.y, pnt.x, pnt.y))
								{
									flag = 1; // Ray already exists
									break;
								}
							}

							if (flag == 0)
							{
								set.push_back(pnt); // Insert new ray in this quadrant
								ret_count++;
							}
							flag = 0; // Reset flag for the next point

						}
						else
							set.push_back(pnt); // Push the very first point
					}
				}
				count = 0;

				break;

			case 1:
				for (auto point: A)
					if (point.x > 0 && point.y > 0)
						count++;

				if (count == 0)
					break;
				else if (count == 1)
					ret_count++;
				else if (count == 2)
				{
					struct Point2D one {.x=0, .y =0};
					struct Point2D two {.x=0, .y =0};

					for (auto point: A)
					{
						if (point.x > 0 && point.y > 0)
						{
							if (one.x == 0 && one.y == 0)
							{
								one.x = point.x;
								one.y = point.y;
							}
							else
							{
								two.x = point.x;
								two.y = point.y;
							}
						}
					}

					if(check_ray_passing(one.x, one.y, two.x, two.y))
						ret_count += 1;
					else
						ret_count += 2;
				}
				else // More than two points
				{
					std::vector<Point2D> points_this_quadrant;
					/* 
						It would be O(n*logn) if I was to implement  unordered_set<Point2D> 
						Inefficient because of using of another vector
						O(n^2) if every point was in a single quadrant
					 */
					std::vector<Point2D> set;

					// O(n)
					for (auto point: A)
					{
						if (point.x > 0 && point.y > 0)
							points_this_quadrant.push_back(point);
					}

					auto first_point = points_this_quadrant.begin();
					// set.push_back(first_point);

					ret_count++; // It certainly has at least one Ray if we have 3 points in this quadrant
					int flag = 0; // New Ray

					for (auto pnt : points_this_quadrant)
					{
						// If it's not the very first point in this quadrant
						if (pnt.x != first_point->x || pnt.y != first_point->y)
						{
							for (auto already: set)
							{
								if (check_ray_passing(already.x, already.y, pnt.x, pnt.y))
								{
									flag = 1; // Ray already exists
									break;
								}
							}

							if (flag == 0)
							{
								set.push_back(pnt); // Insert new ray in this quadrant
								ret_count++;
							}
							flag = 0; // Reset flag for the next point

						}
						else
							set.push_back(pnt); // Push the very first point
					}
				}
				count = 0;

				break;



			case 2:
				for (auto point: A)
					if (point.x < 0 && point.y < 0)
						count++;

				if (count == 0)
					break;
				else if (count == 1)
					ret_count++;
				else if (count == 2)
				{
					struct Point2D one {.x=0, .y =0};
					struct Point2D two {.x=0, .y =0};

					for (auto point: A)
					{
						if (point.x < 0 && point.y < 0)
						{
							if (one.x == 0 && one.y == 0)
							{
								one.x = point.x;
								one.y = point.y;
							}
							else
							{
								two.x = point.x;
								two.y = point.y;
							}
						}
					}

					if(check_ray_passing(one.x, one.y, two.x, two.y))
						ret_count += 1;
					else
						ret_count += 2;
				}
				else // More than two points
				{
					std::vector<Point2D> points_this_quadrant;
					/* 
						It would be O(n*logn) if I was to implement  unordered_set<Point2D> 
						Inefficient because of using of another vector
						O(n^2) if every point was in a single quadrant
					 */
					std::vector<Point2D> set;

					// O(n)
					for (auto point: A)
					{
						if (point.x < 0 && point.y < 0)
							points_this_quadrant.push_back(point);
					}

					auto first_point = points_this_quadrant.begin();
					// set.push_back(first_point);

					ret_count++; // It certainly has at least one Ray if we have 3 points in this quadrant
					int flag = 0; // New Ray

					for (auto pnt : points_this_quadrant)
					{
						// If it's not the very first point in this quadrant
						if (pnt.x != first_point->x || pnt.y != first_point->y)
						{
							for (auto already: set)
							{
								if (check_ray_passing(already.x, already.y, pnt.x, pnt.y))
								{
									flag = 1; // Ray already exists
									break;
								}
							}

							if (flag == 0)
							{
								set.push_back(pnt); // Insert new ray in this quadrant
								ret_count++;
							}
							flag = 0; // Reset flag for the next point

						}
						else
							set.push_back(pnt); // Push the very first point
					}
				}
				count = 0;

				break;

			case 3:
				for (auto point: A)
					if (point.x > 0 && point.y < 0)
						count++;

				if (count == 0)
					break;
				else if (count == 1)
					ret_count++;
				else if (count == 2)
				{
					struct Point2D one {.x=0, .y =0};
					struct Point2D two {.x=0, .y =0};

					for (auto point: A)
					{
						if (point.x > 0 && point.y < 0)
						{
							if (one.x == 0 && one.y == 0)
							{
								one.x = point.x;
								one.y = point.y;
							}
							else
							{
								two.x = point.x;
								two.y = point.y;
							}
						}
					}

					if(check_ray_passing(one.x, one.y, two.x, two.y))
						ret_count += 1;
					else
						ret_count += 2;
				}
				else // More than two points
				{
					std::vector<Point2D> points_this_quadrant;
					/* 
						It would be O(n*logn) if I was to implement  unordered_set<Point2D> 
						Inefficient because of using of another vector
						O(n^2) if every point was in a single quadrant
					 */
					std::vector<Point2D> set;

					// O(n)
					for (auto point: A)
					{
						if (point.x > 0 && point.y < 0)
							points_this_quadrant.push_back(point);
					}

					auto first_point = points_this_quadrant.begin();
					// set.push_back(first_point);

					ret_count++; // It certainly has at least one Ray if we have 3 points in this quadrant
					int flag = 0; // New Ray

					for (auto pnt : points_this_quadrant)
					{
						// If it's not the very first point in this quadrant
						if (pnt.x != first_point->x || pnt.y != first_point->y)
						{
							for (auto already: set)
							{
								if (check_ray_passing(already.x, already.y, pnt.x, pnt.y))
								{
									flag = 1; // Ray already exists
									break;
								}
							}

							if (flag == 0)
							{
								set.push_back(pnt); // Insert new ray in this quadrant
								ret_count++;
							}
							flag = 0; // Reset flag for the next point

						}
						else
							set.push_back(pnt); // Push the very first point
					}
				}
				count = 0;

				break;
		}
	}

	return ret_count;
}
