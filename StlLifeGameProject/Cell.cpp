#include "Cell.h"

int Cell::Row()
{
	return point.Row;
}

int Cell::Column()
{
	return point.Column;
}

Point Cell::Point()
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
