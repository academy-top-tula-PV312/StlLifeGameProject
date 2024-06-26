#pragma once
#include <algorithm>
#include "Cell.h"

enum LifeState
{
	Ok,
	Empty,
	Still
};

class LifeGame
{
	std::vector<Cell*> colony;

public:
	std::vector<Cell*>& Colony() { return colony; }

	LifeState NextColony()
	{
		int currentSize = colony.size();

		int deads{};

		for (int i{}; i < currentSize; i++)
		{
			colony[i]->Neighbors() = 0;
			for (auto offset : Offsets)
				if (IsColony(colony[i]->Point() + offset))
					colony[i]->Neighbors()++;
			if (colony[i]->Neighbors() < 2 || colony[i]->Neighbors() > 3)
			{
				colony[i]->State() = CellState::Dead;
				deads++;
			}
		}

		int borns{};

		for (int i{}; i < currentSize; i++)
		{
			for (auto offset : Offsets)
			{
				Cell* cellNew = new Cell(colony[i]->Point() + offset);
				if (!IsColony(cellNew->Point()))
				{
					for (auto offsetNew : Offsets)
					{
						auto cellTemp = IterColony(cellNew->Point() + offsetNew);
						if (cellTemp != colony.end()
								&& (*cellTemp)->State() != CellState::Born)
							cellNew->Neighbors()++;
					}
					if (cellNew->Neighbors() == 3)
					{
						colony.push_back(cellNew);
						borns++;
					}
					else
						delete cellNew;
						
				}
			}
		}

		if (!colony.size())
			return LifeState::Empty;

		if (!deads && !borns)
			return LifeState::Still;

		for (int i{}; i < colony.size();)
		{
			if (colony[i]->State() == CellState::Dead)
				colony.erase(colony.begin() + i);
			else
				colony[i++]->State() = CellState::Alive;
		}

		return LifeState::Ok;
	}
	
	std::vector<Cell*>::iterator IterColony(Point point)
	{
		auto find = std::find_if(colony.begin(), colony.end(),
			[&point](Cell* item)
			{
				return item->Point() == point;
			});
		return find;
	}

	bool IsColony(Point point)
	{
		return IterColony(point) != colony.end();
	}

};

