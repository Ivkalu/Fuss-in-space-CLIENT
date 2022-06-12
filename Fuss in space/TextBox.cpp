#include "TextBox.h"
#include "InputHandler.h"

TextBox::TextBox(SDL_Rect* _dstrect, int maxLength)
	:Button("assets/Buttons/DefaultButton.png", nullptr, _dstrect, nullptr),
	maxLength(maxLength)
{}


void TextBox::handleEvents()
{
	Button::handleEvents();

	if (Game::event.type == SDL_KEYDOWN && pressed) {
		if (FontManager::hasKey(Game::event.key.keysym.sym) && content.length() != maxLength)
		{
			if ((Game::event.key.keysym.sym <= 'z' && Game::event.key.keysym.sym >= 'a') && (inputHandler->CAPS_LOCK || inputHandler->SHIFT)) {
				content += Game::event.key.keysym.sym - 32;
			}
			else {
				content += Game::event.key.keysym.sym;
			}
		}
		if (Game::event.key.keysym.sym == SDLK_BACKSPACE && content.length() > 0) content.pop_back();
		else if (Game::event.key.keysym.sym == SDLK_ESCAPE) pressed = false;

	}

}

void TextBox::render()
{
	Button::render();
	FontManager::Draw(content.c_str(), (int)content.length(), dstR->x + 5 * 5 + 2, dstR->y + 4 * 5, 5);
}