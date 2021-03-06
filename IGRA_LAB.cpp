/*============================//
	Name:		Chen Yu			
	Admin ID:	p1626063
	Assignment:	IGRA CA1
	Year:		AY 2017/2018	
//============================*/

// IGRA_LAB.cpp : Defines the entry point for the application.
#include "stdafx.h"
#include "IGRA_LAB.h"
//For IGRA - OPENGL
#include <gl\GL.h>
#include <gl\GLU.h>
//STD Dependencies
#include <stdio.h>
#include <vector>
#include <time.h> //For time to seed the rng

#pragma region Menu Controls

vector<int> shapeMenuList = { ID_SHAPE_SQURE, ID_SHAPE_TRIANGLE , ID_SHAPE_CIRCLE , ID_SHAPE_DIAMOND, ID_SHAPE_RANDOM, ID_SHAPE_RANDOMANY };
vector<int> colourMenuList = { ID_COLOUR_BLACK, ID_COLOUR_BLUE, ID_COLOUR_GREEN, ID_COLOUR_RANDOM, ID_COLOUR_RANDOMANY, ID_COLOUR_RED, ID_COLOUR_YELLOW};
vector<int> fillMenuList = { ID_FILL_FILLED, ID_FILL_WIREFRAME, ID_FILL_RANDOM };
vector<int> sizeMenuList = { ID_SIZE_LARGE, ID_SIZE_MEDIUM, ID_SIZE_RANDOM, ID_SIZE_RANDOMANY, ID_SIZE_SMALL};
vector<int> controlMenuList = { ID_CONTROL_CLICK, ID_CONTROL_HOLD};

void UnCheckMenuList(vector<int> menulist)
{
	for (size_t i = 0; i < menulist.size(); i++)
	{
		CheckMenuItem(GetMenu(hWnd), menulist[i], MF_UNCHECKED);
	}
}

void InitMenu()
{//Set the default menu selections
	CheckMenuItem(GetMenu(hWnd), ID_SHAPE_SQURE, MF_CHECKED);
	CheckMenuItem(GetMenu(hWnd), ID_COLOUR_BLACK, MF_CHECKED);
	CheckMenuItem(GetMenu(hWnd), ID_FILL_FILLED, MF_CHECKED);
	CheckMenuItem(GetMenu(hWnd), ID_SIZE_SMALL, MF_CHECKED);
	CheckMenuItem(GetMenu(hWnd), ID_CONTROL_CLICK, MF_CHECKED);
	CheckMenuItem(GetMenu(hWnd), ID_CONTROL_ALLOWFADE, MF_CHECKED);
	//Initiate rng with time seed
	srand(time(NULL));
}

#pragma endregion

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_COMMAND:
		{// Parse the menu selections:
			int wmId = LOWORD(wParam);
			CheckMenuItem(GetMenu(hWnd), ID_CONTROL_ALLRANDOMANY, MF_UNCHECKED);
			switch (wmId)
				{
					{//Shape List
					case ID_SHAPE_SQURE:
						UnCheckMenuList(shapeMenuList);
						CheckMenuItem(GetMenu(hWnd), wmId, MF_CHECKED);
						shapeType = Shape::ShapeType::SQURE;
						break;

					case ID_SHAPE_TRIANGLE:
						UnCheckMenuList(shapeMenuList);
						CheckMenuItem(GetMenu(hWnd), wmId, MF_CHECKED);
						shapeType = Shape::ShapeType::TRIANGLE;
						break;

					case ID_SHAPE_CIRCLE:
						UnCheckMenuList(shapeMenuList);
						CheckMenuItem(GetMenu(hWnd), wmId, MF_CHECKED);
						shapeType = Shape::ShapeType::CIRCLE;
						break;

					case ID_SHAPE_DIAMOND:
						UnCheckMenuList(shapeMenuList);
						CheckMenuItem(GetMenu(hWnd), wmId, MF_CHECKED);
						shapeType = Shape::ShapeType::DIAMOND;
						break;

					case ID_SHAPE_RANDOM:
						UnCheckMenuList(shapeMenuList);
						CheckMenuItem(GetMenu(hWnd), wmId, MF_CHECKED);
						shapeType = Shape::ShapeType::RANDOM;
						break;

					case ID_SHAPE_RANDOMANY:
						UnCheckMenuList(shapeMenuList);
						CheckMenuItem(GetMenu(hWnd), wmId, MF_CHECKED);
						shapeType = Shape::ShapeType::RANDOMANY;
						break;
					}
					{//Colour List
					case ID_COLOUR_BLACK:
						UnCheckMenuList(colourMenuList);
						CheckMenuItem(GetMenu(hWnd), wmId, MF_CHECKED);
						shapeColour = Colour::BLACK;
						isRandomColourMode = false;
						isRandomAnyColourMode = false;
						break;

					case ID_COLOUR_RED:
						UnCheckMenuList(colourMenuList);
						CheckMenuItem(GetMenu(hWnd), wmId, MF_CHECKED);
						shapeColour = Colour::RED;
						isRandomColourMode = false;
						isRandomAnyColourMode = false;
						break;

					case ID_COLOUR_GREEN:
						UnCheckMenuList(colourMenuList);
						CheckMenuItem(GetMenu(hWnd), wmId, MF_CHECKED);
						shapeColour = Colour::GREEN;
						isRandomColourMode = false;
						isRandomAnyColourMode = false;
						break;

					case ID_COLOUR_BLUE:
						UnCheckMenuList(colourMenuList);
						CheckMenuItem(GetMenu(hWnd), wmId, MF_CHECKED);
						shapeColour = Colour::BLUE;
						isRandomColourMode = false;
						isRandomAnyColourMode = false;
						break;

					case ID_COLOUR_YELLOW:
						UnCheckMenuList(colourMenuList);
						CheckMenuItem(GetMenu(hWnd), wmId, MF_CHECKED);
						shapeColour = Colour::YELLOW;
						isRandomColourMode = false;
						isRandomAnyColourMode = false;
						break;

					case ID_COLOUR_RANDOM:
						UnCheckMenuList(colourMenuList);
						CheckMenuItem(GetMenu(hWnd), wmId, MF_CHECKED);
						shapeColour = Colour::Random();
						isRandomColourMode = true;
						isRandomAnyColourMode = false;
						break;

					case ID_COLOUR_RANDOMANY:
						UnCheckMenuList(colourMenuList);
						CheckMenuItem(GetMenu(hWnd), wmId, MF_CHECKED);
						shapeColour = Colour::RandomAny();
						isRandomColourMode = false;
						isRandomAnyColourMode = true;
						break;
					}
					{//Fill mode List
					case ID_FILL_FILLED:
						UnCheckMenuList(fillMenuList);
						CheckMenuItem(GetMenu(hWnd), wmId, MF_CHECKED);
						shapeFillMode = Shape::Fill::FILLED;
						break;

					case ID_FILL_WIREFRAME:
						UnCheckMenuList(fillMenuList);
						CheckMenuItem(GetMenu(hWnd), wmId, MF_CHECKED);
						shapeFillMode = Shape::Fill::WIREFRAME;
						break;

					case ID_FILL_RANDOM:
						UnCheckMenuList(fillMenuList);
						CheckMenuItem(GetMenu(hWnd), wmId, MF_CHECKED);
						shapeFillMode = Shape::Fill::RANDOM;
						break;
					}
					{//Size List
					case ID_SIZE_SMALL:
						UnCheckMenuList(sizeMenuList);
						CheckMenuItem(GetMenu(hWnd), wmId, MF_CHECKED);
						shapeSize = Shape::Size::SMALL;
						break;

					case ID_SIZE_MEDIUM:
						UnCheckMenuList(sizeMenuList);
						CheckMenuItem(GetMenu(hWnd), wmId, MF_CHECKED);
						shapeSize = Shape::Size::MEDIUM;
						break;

					case ID_SIZE_LARGE:
						UnCheckMenuList(sizeMenuList);
						CheckMenuItem(GetMenu(hWnd), wmId, MF_CHECKED);
						shapeSize = Shape::Size::LARGE;
						break;

					case ID_SIZE_RANDOM:
						UnCheckMenuList(sizeMenuList);
						CheckMenuItem(GetMenu(hWnd), wmId, MF_CHECKED);
						shapeSize = Shape::Size::RANDOM;
						break;

					case ID_SIZE_RANDOMANY:
						UnCheckMenuList(sizeMenuList);
						CheckMenuItem(GetMenu(hWnd), wmId, MF_CHECKED);
						shapeSize = Shape::Size::RANDOMANY;
						break;
					}
					{//Control List
					case ID_CONTROL_CLICK:
						UnCheckMenuList(controlMenuList);
						CheckMenuItem(GetMenu(hWnd), wmId, MF_CHECKED);
						holdMode = false;
						break;

					case ID_CONTROL_HOLD:
						UnCheckMenuList(controlMenuList);
						CheckMenuItem(GetMenu(hWnd), wmId, MF_CHECKED);
						holdMode = true;
						break;
					//Set all options to random
					case ID_CONTROL_ALLRANDOMANY:
						UnCheckMenuList(shapeMenuList);
						UnCheckMenuList(colourMenuList);
						UnCheckMenuList(fillMenuList);
						UnCheckMenuList(sizeMenuList);
						CheckMenuItem(GetMenu(hWnd), ID_SHAPE_RANDOMANY, MF_CHECKED);
						CheckMenuItem(GetMenu(hWnd), ID_COLOUR_RANDOMANY, MF_CHECKED);
						CheckMenuItem(GetMenu(hWnd), ID_FILL_RANDOM, MF_CHECKED);
						CheckMenuItem(GetMenu(hWnd), ID_SIZE_RANDOMANY, MF_CHECKED);
						CheckMenuItem(GetMenu(hWnd), ID_CONTROL_ALLRANDOMANY, MF_CHECKED);
						shapeType = Shape::ShapeType::RANDOMANY;
						shapeColour = Colour::RandomAny();
						isRandomAnyColourMode = true;
						isRandomColourMode = false;
						shapeFillMode = Shape::Fill::RANDOM;
						shapeSize = Shape::Size::RANDOMANY;
						allowFade = true;
						break;
					//Reset all options to default
					case ID_CONTROL_RESET:
						UnCheckMenuList(shapeMenuList);
						UnCheckMenuList(colourMenuList);
						UnCheckMenuList(fillMenuList);
						UnCheckMenuList(sizeMenuList);
						UnCheckMenuList(controlMenuList);
						InitMenu();
						shapeType = Shape::ShapeType::SQURE;
						shapeColour = Colour::BLACK;
						shapeFillMode = Shape::Fill::FILLED;
						shapeSize = Shape::Size::SMALL;
						holdMode = false;
						isRandomColourMode = false;
						isRandomAnyColourMode = false;
						break;
					//Allow the shapes to fade out and destroy or not
					case ID_CONTROL_ALLOWFADE:
						if (allowFade)
						{
							CheckMenuItem(GetMenu(hWnd), ID_CONTROL_ALLOWFADE, MF_UNCHECKED);
							allowFade = false;
						}
						else
						{
							CheckMenuItem(GetMenu(hWnd), ID_CONTROL_ALLOWFADE, MF_CHECKED);
							allowFade = true;
						}
					}

					default:
						return DefWindowProc(hWnd, message, wParam, lParam);
				}
			break;
		}
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			// TODO: Add any drawing code that uses hdc here...
			EndPaint(hWnd, &ps);
			break;
		}
		case WM_SIZE:
		{// Added for IGRA
			ReSizeGLScene(LOWORD(lParam), HIWORD(lParam));
			break;
		}
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}
		case WM_LBUTTONDOWN:
		{//Determine for start of mouse hold
			isLBottonHold = true;
			break;
		}
		case WM_LBUTTONUP:
		{//Get the left mouse press coordinates
			int mouseX = LOWORD(lParam);
			int mouseY = HIWORD(lParam);
			Vector2f::ConvertMouseCoordinates(mouseX, mouseY, width, height);
			//Call the constructor for all the shapes to construct a derived shape object based on parameters
			Shape shapetodraw = Shape(shapeType, shapeColour, shapeFillMode, shapeSize);
			//Regenerate a new random colour if a random colour mode is true
			if (isRandomColourMode)
			{
				shapeColour = Colour::Random();
			}
			if (isRandomAnyColourMode)
			{
				shapeColour = Colour::RandomAny();
			}
			//Fade out and destroy shapes if there are too many on screen
			if (allowFade)
			{
				for (size_t i = 0; i < Shape::List.size() / 3; i++)
				{
					Shape::List[i]->ShapeColour.FadetoWhite();
				}
				if (Shape::List.size() > 500)
				{
					Shape::List.erase(Shape::List.begin());
				}
			}
			//Determine for end of mouse hold
			isLBottonHold = false;
			break;
		}
		case WM_MOUSEMOVE:
		{//Construct shapes rapidly as mouse moves if the mouse is on hold and the hold mode is true
			if (isLBottonHold && holdMode)
			{
				int mouseX = LOWORD(lParam);
				int mouseY = HIWORD(lParam);
				Vector2f::ConvertMouseCoordinates(mouseX, mouseY, width, height);
				Shape shapetodraw = Shape(shapeType, shapeColour, shapeFillMode, shapeSize);

				if (isRandomColourMode)
				{
					shapeColour = Colour::Random();
				}
				if (isRandomAnyColourMode)
				{
					shapeColour = Colour::RandomAny();
				}

				if (allowFade)
				{
					for (size_t i = 0; i < Shape::List.size() / 3; i++)
					{
						Shape::List[i]->ShapeColour.FadetoWhite();
					}
					if (Shape::List.size() > 500)
					{
						Shape::List.erase(Shape::List.begin());
					}
				}
			}
			break;
		}

		case WM_RBUTTONUP:
		{//Right click to clear all the shapes on screen
			Shape::List.clear();
			break;
		}

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void DrawGLScene()
{//Draw the shapes based in the shape holder list
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1, 1, 1, 1);

	for (size_t i = 0; i < Shape::List.size(); i++)
	{//Draw all derived shape objects by pointer
		Shape::List[i]->Draw();
	}

	glLoadIdentity();
}

