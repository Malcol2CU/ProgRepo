#ifndef GRID_H
#define GRID_H
#include <iostream>

class Grid{
public:
	Grid();
	~Grid();
	Grid(int, int);
	Grid(const Grid&);

	void setDimension(int, int);
	void place(int, int);
	std::ostream& operator<<(std::ostream&);
	std::ostream& operator=(const Grid& grid);

private:
	char **board;
	int rows, columns;
};
#endif
