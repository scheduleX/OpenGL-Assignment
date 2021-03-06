#pragma once
//Colour object to be used in shapes construction
class Colour
{
public:
	//Preset colours
	static const Colour BLACK;
	static const Colour RED;
	static const Colour GREEN;
	static const Colour BLUE;
	static const Colour YELLOW;
	//RGB values for a colour
	float Red = 0;
	float Green = 0;
	float Blue = 0;

	static Colour Random();
	static Colour RandomAny();
	void FadetoWhite();
	std::string ToString();

	Colour();
	Colour(float red, float green, float blue);
	~Colour();
};

