#pragma once
#include <vector>

struct Point
{
	int Row;
	int Column;
public:
	Point(int row, int column)
		: Row{ row }, Column{ column } {}

	friend bool operator==(const Point& point1, const Point& point2)
	{
		return point1.Row == point2.Row && point1.Column == point2.Column;
	}

	friend Point operator+(const Point& point1, const Point& point2)
	{
		return Point(point1.Row + point2.Row, point1.Column + point2.Column);
	}
};

enum CellState
{
	Alive,
	Born,
	Dead
};

class Cell
{
	Point point;
	CellState state;
	int neighbors;
public:
	Cell(Point point,
		CellState state = CellState::Born)
		: point{ point },
		  state{ state },
		  neighbors{} {}

	int& Row();
	int& Column();
	Point& Point();

	CellState& State();
	int& Neighbors();
};

std::vector<Point> Offsets({ {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1} });

int& Cell::Row()
{
	return point.Row;
}

int& Cell::Column()
{
	return point.Column;
}

Point& Cell::Point()
{
	return point;
}

CellState& Cell::State()
{
	return state;
}

int& Cell::Neighbors()
{
	return neighbors;
}