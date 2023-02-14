#include "Game.h"



int FPS = 30;

Game* game = nullptr;

int main(int argc, char* argv[])
{
	int opt = 1;
	while (opt < argc)
	{
		if (argv[opt][0] == '-' && strlen(argv[opt]) == 2) {
			switch (argv[opt][1])
			{
			case 'h':
				printf("Usage: \"Fuss in space.exe\" [-a adresa] [-p port] [-f fps]\n");
				return 0;
			case 'a':
				if (++opt >= argc)
				{
					printf("Usage: \"Fuss in space.exe\" [-a adresa] [-p port] [-f fps]\n");
					return 1;
				}
				DEFAULT_ADDRESS = argv[opt];
				break;
			case 'p':
				break;
			case 'f':
				if (++opt >= argc)
				{
					printf("Usage: \"Fuss in space.exe\" [-a adresa] [-p port] [-f fps]\n");
					return 1;
				}
				FPS = atoi(argv[opt]);
				break;
			default:
				break;
			}
			opt++;
		}
	}
	
	const int HANDLEEVENTSPS = 1000;
	const int frameDelay = 1000 / FPS;
	
	Uint32 frameStart;
	int frameTime;
	
	
	game = new Game();
	game->init();

	int frame = 0;
	while (game->running())
	{
		
		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}

	}

	game->clean();
	return 0;
}