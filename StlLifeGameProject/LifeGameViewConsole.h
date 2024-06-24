#pragma once
#include "ILifeGameView.h"
#include "Console.h"
#include <thread>
#include <chrono>

class LifeGameViewConsole : public ILifeGameView
{
	Console* console;
	char box25 = 176;
	char box75 = 178;
public:
	LifeGameViewConsole()
		: console{ new Console() } {}

	void ShowColony()
	{
		for (auto cell : lifeGame->Colony())
			console->WritePosition(cell.Row(), cell.Column() * 2, std::string(2, box75));
	}

	bool Setup() override
	{
		int row{};
		int column{};

		console->SetCursor(row, column);

		KeyCode keyCode;

		std::vector<Cell>::iterator it;

		while (true)
		{
			if (console->KeyPressed())
			{
				keyCode = (KeyCode)console->GetChar();
				
				switch (keyCode)
				{
				case ArrowUp:
					if(row > 0) row--; break;

				case ArrowDown: 
					row++; break;

				case ArrowLeft:
					if (column > 0) column--; break;

				case ArrowRight:
					column++; break;

				case Esc:
					lifeGame->Colony().clear();
					return false;

				case Enter:
					if (lifeGame->Colony().size() > 0)
						return true;
					break;

				case Space:
					Cell cell(Point(row, column));
					it = lifeGame->ItColony(cell);

					if (it == lifeGame->Colony().end())
						lifeGame->Colony().push_back(cell);
					else
						lifeGame->Colony().erase(it);

					console->Clear();
					ShowColony();
					break;
				}
				console->SetCursor(row, column * 2);
			}
		}
	}

	void Play() override 
	{
		while (true)
		{
			if (console->KeyPressed() && (KeyCode)console->GetChar() == KeyCode::Esc)
				break;
			lifeGame->NextColony();
			console->Clear();
			ShowColony();
			

			std::chrono::microseconds duration(speed);
			std::this_thread::sleep_for(duration);
		}
	}
};

