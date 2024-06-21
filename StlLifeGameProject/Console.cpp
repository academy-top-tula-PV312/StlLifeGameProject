#include "Console.h"

int BorderSingle[]{ 0x250C, 0x252C, 0x2510, 0x251C, 0x253C, 0x2524, 0x2514, 0x2534, 0x2518, 0x2500, 0x2502 };
int BorderDouble[]{ 0x2554, 0x2566, 0x2557, 0x2560, 0x256C, 0x2563, 0x255A, 0x2569, 0x255D, 0x2550, 0x2551 };


Console::Console() : Console(120, 30) {}

Console::Console(int width, int height)  
{
	descriptor = GetStdHandle(STD_OUTPUT_HANDLE);

	SMALL_RECT rect;
	rect.Top = 0;
	rect.Left = 0;
	rect.Right = width - 1;
	rect.Bottom = height - 1;

	SetConsoleWindowInfo(descriptor, true, &rect);
}

HANDLE& Console::Descriptor()
{
	return descriptor;
}

void Console::SetCursor(int row, int column)
{
	coordinate.X = column;
	coordinate.Y = row;
	SetConsoleCursorPosition(descriptor, coordinate);
}

void Console::Write(char symbol)
{
	std::cout << symbol;
}

void Console::Write(const char* cstr)
{
	std::cout << cstr;
}

void Console::Write(std::string str)
{
	std::cout << str;
}

void Console::Foreground(Color color)
{
	GetConsoleScreenBufferInfo(descriptor, &info);
	byte colorBack = info.wAttributes & (0b1111 << 4);
	byte colorFore = (byte)color;
	SetConsoleTextAttribute(descriptor, colorBack | colorFore);
}

void Console::Background(Color color)
{
	GetConsoleScreenBufferInfo(descriptor, &info);
	byte colorFore = info.wAttributes & 0b1111;
	byte colorBack = (byte)color << 4;
	SetConsoleTextAttribute(descriptor, colorBack | colorFore);
}

void Console::Clear()
{
	std::system("cls");
}

int Console::GetChar()
{
	int key = _getch();

	if (key == 0 || key == 0xE0)
		key = _getch();

	return key;
}

int Console::KeyPressed()
{
	return _kbhit();
}






WindowConsole::WindowConsole(Console* console) 
	: WindowConsole(console, 0, 0, 80, 30) {}

WindowConsole::WindowConsole(Console* console, 
							int row, int column, 
							int width, int height)
	: console { console },
	row{ row }, column { column },
	width{ width }, height { height }
{
	isBorder = true;
	borderStyle = BorderStyle::Single;
	colorBack = Color::Blue;
	colorFore = Color::White;

	isVisible = false;

	bufferSave = new CHAR_INFO[width * height];
	bufferWin = new CHAR_INFO[width * height];
}

void WindowConsole::SetTitle(std::string title)
{
	this->title = title;
}

void WindowConsole::Show()
{
	if (isVisible) return;

	COORD bufferSize{ width, height };
	COORD bufferPosition{ 0, 0 };
	SMALL_RECT rect{ column, row, column + width, row + height };
	
	bool isSuccess = ReadConsoleOutput(console->Descriptor(),
										bufferSave,
										bufferSize,
										bufferPosition,
										&rect);

	WORD attribute = colorFore | (colorBack << 4);

	int* border = (borderStyle == BorderStyle::Single) ? BorderSingle : BorderDouble;

	int index{};

	for (int r = 0; r < height; r++)
		for (int c = 0; c < width; c++)
		{
			bufferWin[index].Char.UnicodeChar = ' ';
			bufferWin[index++].Attributes = attribute;
		}

	if (isBorder)
	{
		bufferWin[0].Char.UnicodeChar = border[Border::TopLeft];
		for(index = 1; index < width - 1; index++)
			bufferWin[index].Char.UnicodeChar = border[Border::Horizontal];
		bufferWin[index++].Char.UnicodeChar = border[Border::TopRight];

		for (int row = 1; row < height - 1; row++)
		{
			bufferWin[index].Char.UnicodeChar = border[Border::Vertical];
			index += width - 1;
			bufferWin[index++].Char.UnicodeChar = border[Border::Vertical];
		}

		bufferWin[index++].Char.UnicodeChar = border[Border::BottomLeft];
		
		int lwidth{ index + width - 2 };
		for (index; index < lwidth; index++)
			bufferWin[index].Char.UnicodeChar = border[Border::Horizontal];

		bufferWin[index].Char.UnicodeChar = border[Border::BottomRight];
	}

	if (title.length() > 0)
	{
		bufferWin[1].Char.UnicodeChar = ' ';
		index = 2;
		std::for_each(std::begin(title), std::end(title),
			[&](char ch)
			{
				bufferWin[index++].Char.UnicodeChar = ch;
			});
		bufferWin[index].Char.UnicodeChar = ' ';
	}
	


	isSuccess = WriteConsoleOutput(console->Descriptor(),
									bufferWin,
									bufferSize,
									bufferPosition,
									&rect);

	isVisible = true;
}

void WindowConsole::Hide()
{
	if (!isVisible) return;

	COORD bufferSize{ width, height };
	COORD bufferPosition{ 0, 0 };
	SMALL_RECT rect{ column, row, column + width, row + height };

	bool isSuccess = WriteConsoleOutput(console->Descriptor(),
											bufferSave,
											bufferSize,
											bufferPosition,
											&rect);

	isVisible = false;
}



