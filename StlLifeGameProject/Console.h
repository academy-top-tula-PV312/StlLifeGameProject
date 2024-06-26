#pragma once
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <algorithm>

enum Color
{
	Black,
	DarkBlue,
	DarkGreen,
	DarkCyan,
	DarkRed,
	DarkMagenta,
	DarkYellow,
	Gray,
	DarkGray,
	Blue,
	Green,
	Cyan,
	Red,
	Magenta,
	Yellow,
	White
};

enum BorderStyle
{
	Single,
	Double
};

enum Border
{
	TopLeft,
	TopCenter,
	TopRight,
	MiddleLeft,
	MiddleCenter,
	MiddleRight,
	BottomLeft,
	BottomCenter,
	BottomRight,
	Horizontal,
	Vertical
};

enum KeyCode
{
	ArrowUp = 72,
	ArrowDown = 80,
	ArrowLeft = 75,
	ArrowRight = 77,

	Esc = 27,
	Space = 32,
	Enter = 13
};

class Console
{
	HANDLE descriptor;
	COORD coordinate;
	CONSOLE_SCREEN_BUFFER_INFO info;
public:
	Console();
	Console(int width, int height);

	HANDLE& Descriptor();

	void SetCursor(int row, int column);

	void Write(char symbol);
	void Write(const char* cstr);
	void Write(std::string str);

	void Foreground(Color color);
	void Background(Color color);

	void WritePosition(int row, int column, char symbol);
	void WritePosition(int row, int column, const char* cstr);
	void WritePosition(int row, int column, std::string str);

	void WritePositionWidth(int row, int column, int width, char symbol);
	void WritePositionWidth(int row, int column, int width, const char* cstr);
	void WritePositionWidth(int row, int column, int width, std::string str);

	void WriteColor(char symbol, Color back, Color fore);
	void WriteColor(const char* cstr, Color back, Color fore);
	void WriteColor(std::string str, Color back, Color fore);

	void Clear();
	int GetChar();
	int KeyPressed();

	void CursorView(bool visible)
	{
		CONSOLE_CURSOR_INFO CCI;
		CCI.bVisible = visible;
		CCI.dwSize = 1;
		SetConsoleCursorInfo(descriptor, &CCI);
	}
};

class WindowConsole
{
protected:
	Console* console;

	int row;
	int column;
	int width;
	int height;

	bool isBorder;
	BorderStyle borderStyle;

	std::string title;

	Color colorBack;
	Color colorFore;

	bool isVisible;

	CHAR_INFO* bufferSave;
	CHAR_INFO* bufferWin;

public:
	WindowConsole(Console* console);
	WindowConsole(Console* console, int row, int column, int width, int height);

	int Row() { return row; }
	int Column() { return column; }
	int Width() { return width; }
	int Height() { return height; }

	void SetPosition(int row, int column);
	void SetSize(int width, int height);

	bool& IsBorder() { return isBorder; }
	BorderStyle& Style() { return borderStyle; }

	std::string Title() { return title; }
	void SetTitle(std::string title);

	Color& ColorBack() { return colorBack; }
	Color& ColorFore() { return colorFore; }

	bool IsVisible() { return isVisible; }
	void SetVisible(bool isVisible);

	virtual void Show();
	virtual void Hide();

};