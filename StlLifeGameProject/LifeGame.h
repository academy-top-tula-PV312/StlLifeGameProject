#pragma once
#include <algorithm>
#include "Cell.h"


class LifeGame
{
	std::vector<Cell> colony;

protected:
	bool isColony(Cell cell)
	{
		auto find = std::find_if(colony.begin(), colony.end(),
			[&cell](Cell item)
			{
				return item.Point() == cell.Point();
			});
		return find != colony.end();
	}

public:
	std::vector<Cell>& Colony() { return colony; }

	void NextColony()
	{
		auto colony_begin = colony.begin(); //std::begin(colony);
		auto colony_end = colony.end();

		int currentSize = colony.size();

		for (int i{}; i < currentSize; i++)
		{
			Cell* cell = &colony[i];

			cell->Neighbors() = 0;

			for (auto offset : Offsets)
			{
				Cell newCell = Cell(cell->Point() + offset);

				if (isColony(newCell))
				{
					if(newCell.State() != CellState::Born)
						cell->Neighbors()++;
					continue;
				}
	
				for (auto newOffset : Offsets)
				{
					Cell cellTemp(newCell.Point() + newOffset);
					if (isColony(cellTemp) && cellTemp.State() != CellState::Born)
						newCell.Neighbors()++;
				}
					
				if (newCell.Neighbors() == 3)
				{
					newCell.State() = CellState::Born;
					colony.push_back(newCell);
				}
			}
			
			if (cell->Neighbors() < 2 || cell->Neighbors() > 3)
				cell->State() = CellState::Dead;
		}

		for (int i{}; i < colony.size();)
		{
			if (colony[i].State() == CellState::Dead)
				colony.erase(colony.begin() + i);
			else
			{
				colony[i].State() = CellState::Alive;
				i++;
			}
			if (colony.size() == 0) break;
		}
	}
	
	std::vector<Cell>::iterator ItColony(Cell cell)
	{
		auto find = std::find_if(colony.begin(), colony.end(),
			[&cell](Cell item)
			{
				return item.Point() == cell.Point();
			});
		return find;
	}
};

