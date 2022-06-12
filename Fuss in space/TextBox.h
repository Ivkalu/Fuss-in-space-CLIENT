#pragma once
#include "Sprite.h"
#include "Game.h"
#include "Defines.h"
#include "Button.h"
#include <vector>
#include "FontManager.h"
#include <string>

class TextBox : public Button
{

public:

	TextBox(SDL_Rect* _dstrect, int maxLength = 10);

	void handleEvents() override;
	void render() override;

	std::string getContent()
	{
		return content;
	}

	void setContent(std::string content)
	{
		this->content = content;
	}

private:

	std::string content;
	int maxLength;

};
