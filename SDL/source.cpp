#include <SDL.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define BOMB 10
#define tableiSize 10
#define VIDE 15
#define FLAG 11

#define BLK   "\x1B[30m"
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define WHTB   "\x1B[47m"
#define RESET "\x1B[0m"




// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.


int index(int x, int y, int ligne)
{
	int pos = y * ligne + x;
	return pos;
}
void discover(int* playground, int* t, int ligne, int x, int y)
{
	int pos = index(x, y, ligne);
	if (playground[pos] == VIDE)
	{
		t[pos] = 0;
		playground[pos] = 0;
		//printf("%d,%d", x, y);
		//right
		if (x + 1 < ligne)
		{
			discover(playground, t, ligne, x + 1, y);
		}
		//left
		if (x - 1 >= 0)
		{
			discover(playground, t, ligne, x - 1, y);
		}
		//down
		if (y + 1 < ligne)
		{
			discover(playground, t, ligne, x, y + 1);
		}
		//up
		if (y - 1 >= 0)
		{
			discover(playground, t, ligne, x, y - 1);
		}
		//up right
		if (x + 1 < ligne and y - 1 >= 0)
		{
			discover(playground, t, ligne, x + 1, y - 1);
		}
		//down left
		if (x - 1 >= 0 and y + 1 < ligne)
		{
			discover(playground, t, ligne, x - 1, y + 1);
		}
		//down right
		if (x + 1 < ligne and y + 1 < ligne)
		{
			discover(playground, t, ligne, x + 1, y + 1);
		}
		//up left
		if (x - 1 >= 0 and y - 1 >= 0)
		{
			discover(playground, t, ligne, x - 1, y - 1);
		}
	}
	if (playground[pos] == 10) {
		t[pos] = t[pos];
	}
	else
	{
		t[pos] = playground[pos];
	}


}
bool play(int* playground, int* t, int ligne, int x, int y, int flag)
{
	if (x < 0) {
		printf("Vous essayer de jouer en dehors du tableau\n");
		play(playground, t, ligne, x, y, flag);
	}
	else if (x >= ligne) {
		printf("Vous essayer de jouer en dehors du tableau\n");
		play(playground, t, ligne, x, y, flag);
	}

	if (y < 0) {
		printf("Vous essayer de jouer en dehors du tableau\n");
		play(playground, t, ligne, x, y, flag);
	}
	else if (y >= ligne) {
		printf("Vous essayer de jouer en dehors du tableau\n");
		play(playground, t, ligne, x, y, flag);
	}
	if (flag != 0 && flag != 1) {
		printf("1 = placer un drapeau ,0 = creuser la case\n");
		play(playground, t, ligne, x, y, flag);
	}

	int pos = index(x, y, ligne);
	if (x >= 0 and x < ligne and y >= 0 and y < ligne) {
		if (flag == 1)
		{
			if (t[pos] == FLAG) {
				t[pos] = VIDE;
			}
			else {
				t[pos] = FLAG;
			}
			
		}
		if (flag == 0)
		{
			if (t[pos] == FLAG)
			{
				return false;
			}
			if (playground[pos] == BOMB)
			{
				t[pos] = playground[pos];
				return true;
			}
			
			else
			{
				discover(playground, t, ligne, x, y);
				return false;
			}
		}
	}
	return false;
}

bool winCondition(int* t, int* playground, int ligne, int bombNumber) {
	//win check
	int winCount = 0;
	for (int i = 0; i < ligne; ++i)
	{
		for (int m = 0; m < ligne; m++) {
			int pos2 = index(i, m, ligne);
			if (t[pos2] != VIDE and t[pos2] != BOMB and t[pos2] != FLAG) {
				++winCount;
			}
		}
	}


	if (winCount == (ligne * ligne) - bombNumber) {
		return true;
	}
	else {
		return false;
	}
}


int countVerif(int x, int y, int ligne, int* playground)
{
	int count = 0;
	int pos = index(x, y, ligne);
	//up
	if (playground[pos] == BOMB)
		return 0;

	if (y - 1 >= 0)
	{
		int up = index(x, y - 1, ligne);
		if (playground[up] == BOMB)
		{
			++count;
		}
	}
	//printf(" %d ", up);
	//down
	if (y + 1 < ligne)
	{
		int down = index(x, y + 1, ligne);
		if (playground[down] == BOMB)
		{
			++count;
		}
	}
	//printf(" %d ", down);
	//right
	if (x + 1 < ligne)
	{
		int right = index(x + 1, y, ligne);
		if (playground[right] == BOMB)
		{
			++count;
		}
	}
	//printf(" %d ", right);
	//left
	if (x - 1 >= 0)
	{
		int left = index(x - 1, y, ligne);
		if (playground[left] == BOMB)
		{
			++count;
		}
	}
	//printf(" %d ", left);
	//up right
	if (x + 1 < ligne and y - 1 >= 0)
	{
		int ur = index(x + 1, y - 1, ligne);
		if (playground[ur] == BOMB)
		{
			++count;
		}
	}
	//printf(" %d ", ur);
	//up left
	if (x - 1 >= 0 and y - 1 >= 0)
	{
		int ul = index(x - 1, y - 1, ligne);
		if (playground[ul] == BOMB)
		{
			++count;
		}
	}
	//printf(" %d ", ul);
	//down right
	if (x + 1 < ligne and y + 1 < ligne)
	{
		int dr = index(x + 1, y + 1, ligne);
		if (playground[dr] == BOMB)
		{
			++count;
		}
	}
	//printf(" %d ", dr);
	//down left
	if (x - 1 >= 0 and y + 1 < ligne)
	{
		int dl = index(x - 1, y + 1, ligne);
		if (playground[dl] == BOMB)
		{
			++count;
		}
	}
	//printf(" %d ", dl);
	if (count == 0)
	{
		playground[pos] = playground[pos];
	}
	else
	{
		playground[pos] = count;
	}
	return count;

}

void bombPlacement(int* playground, int bombNumber, int ligne) {
	srand(time(NULL));
	for (int l = 0; l < bombNumber; ++l) {
		int rBombs = rand() % (ligne * ligne) + 1;
		playground[rBombs] = 10;
	}
}
void countgrid(int* playground, int ligne)
{
	for (int o = 0; o < ligne; ++o)
	{
		for (int p = 0; p < ligne; ++p)
		{
			countVerif(p, o, ligne, playground);
		}
	}
}


void visualRender(int* t, int p, int ligne)
{
	printf("   ");
	for (int m = 0; m < ligne; ++m)
	{
		if (m < 9) {
			printf("  %d", m);
		}
		if (m == 9) {
			printf("  %d ", m);
		}
		if (m >= 10) {
			printf(" %d", m);
		}
	}
	for (int i = 0; i < ligne; ++i) {
		printf("\n");
		if (i < 10) {
			printf(" %d  ", i);
		}
		if (i >= 10) {
			printf(" %d ", i);
		}
		for (int n = 0; n < ligne; ++n) {
			if (t[p] == 0) {
				printf("[" WHTB " " RESET "]");
			}
			else if (t[p] == 1) {
				printf("[" BLU "1" RESET "]");
			}
			else if (t[p] == 2) {
				printf("[" GRN "2" RESET "]");
			}
			else if (t[p] == 3) {
				printf("[" RED "3" RESET "]");
			}
			else if (t[p] == 4) {
				printf("[" MAG "4" RESET "]");
			}
			else if (t[p] == 5) {
				printf("[" YEL "5" RESET "]");
			}
			else if (t[p] == 6) {
				printf("[" CYN "6" RESET "]");
			}
			else if (t[p] == 7) {
				printf("[" WHT "7" RESET "]");
			}
			else if (t[p] == 8) {
				printf("[" WHT "8" RESET "]");
			}
			else if (t[p] == BOMB) {
				printf("[@]");
			}
			else if (t[p] == FLAG) {
				printf("[" RED "P" RESET "]");
			}
			else if (t[p] == VIDE) {
				printf("[ ]");
			}
			++p;
		}
		printf("\n");
	}
}




int main(int argc, char* argv[])
{
	int iSize,ligne, bombNumber;
	ligne = 0;
	iSize = ligne * ligne;
	bombNumber = 0;
	int winCount = 0;
	bool lose = false;
	bool win = false;
	int p = 0;
	int count = 0;



	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//																	//CONSOLE CONSOLE CONSOLE                                               ||
	//																																			||
	//																		  //MUR MARIA														||
	//																																			||
	//																	   //SDL SDL SDL SDL													||
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	//initialisations
	int inGame = 1;
	int start = -1;
	int windowSize = 720;
	int mainButtonW = 200;
	int mainButtonH = 100;
	int boxSize = 50;
	int statut = EXIT_FAILURE;
	int playing = 0;
	int gameOver = 0;
	int x, y;
	Uint32 boutons;

	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Event event;


	//vérif 1er temps


	//textures init
	SDL_Surface* bomb = NULL;
	SDL_Texture* bombTexture = NULL;

	SDL_Surface* detect1 = NULL;
	SDL_Texture* detect1Texture = NULL;

	SDL_Surface* detect2 = NULL;
	SDL_Texture* detect2Texture = NULL;

	SDL_Surface* detect3 = NULL;
	SDL_Texture* detect3Texture = NULL;

	SDL_Surface* detect4 = NULL;
	SDL_Texture* detect4Texture = NULL;

	SDL_Surface* detect5 = NULL;
	SDL_Texture* detect5Texture = NULL;

	SDL_Surface* detect6 = NULL;
	SDL_Texture* detect6Texture = NULL;

	SDL_Surface* detect7 = NULL;
	SDL_Texture* detect7Texture = NULL;

	SDL_Surface* detect8 = NULL;
	SDL_Texture* detect8Texture = NULL;

	SDL_Surface* discovery = NULL;
	SDL_Texture* discoveryTexture = NULL;

	SDL_Surface* flag = NULL;
	SDL_Texture* flagTexture = NULL;

	SDL_Surface* loseScreen = NULL;
	SDL_Texture* loseScreenTexture = NULL;

	SDL_Surface* winScreen = NULL;
	SDL_Texture* winScreenTexture = NULL;

	SDL_Surface* titleScreen = NULL;
	SDL_Texture* titleScreenTexture = NULL;

	SDL_Surface* titleScreen2 = NULL;
	SDL_Texture* titleScreenTexture2 = NULL;

	SDL_Surface* playButton = NULL;
	SDL_Texture* playButtonTexture = NULL;

	SDL_Surface* quitButton = NULL;
	SDL_Texture* quitButtonTexture = NULL;

	SDL_Surface* easyButton = NULL;
	SDL_Texture* easyButtonTexture = NULL;

	SDL_Surface* mediumButton = NULL;
	SDL_Texture* mediumButtonTexture = NULL;

	SDL_Surface* hardButton = NULL;
	SDL_Texture* hardButtonTexture = NULL;

	SDL_Surface* escapeButton = NULL;
	SDL_Texture* escapeButtonTexture = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		fprintf(stderr, "Erreur SDL_INIT_VIDEO : %s", SDL_GetError());
		goto Quit;
	}

	if (SDL_Init(SDL_INIT_AUDIO) != 0) {
		fprintf(stderr, "Erreur SDL_INIT_AUDIO : %s", SDL_GetError());
		goto Quit;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //Initialisation de l'API Mixer
	{
		printf("%s", Mix_GetError());
	}

	//paramètres

	SDL_RaiseWindow(window);

	//paramètres rendu/fenêtre

	window = SDL_CreateWindow("Démineur", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		windowSize, windowSize, SDL_WINDOW_SHOWN);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	//musique

	Mix_Music* musique; //Création du pointeur de type Mix_Music
	musique = Mix_LoadMUS("src/minesweeper.mp3"); //Chargement de la musique
	Mix_PlayMusic(musique, -1); //Jouer infiniment la musique
	Mix_VolumeMusic(MIX_MAX_VOLUME/8);
	//vérif 2ème temps

	if (NULL == window)
	{
		fprintf(stderr, "Erreur SDL_CreateWindow : %s", SDL_GetError());
		goto Quit;
	}

	if (NULL == renderer)
	{
		fprintf(stderr, "Erreur SDL_CreateRenderer : %s", SDL_GetError());
		goto Quit;
	}

	//textures loading


	bomb = SDL_LoadBMP("src/bomb.bmp");
	bombTexture = SDL_CreateTextureFromSurface(renderer, bomb);

	detect1 = SDL_LoadBMP("src/detector1.bmp");
	detect1Texture = SDL_CreateTextureFromSurface(renderer, detect1);

	detect2 = SDL_LoadBMP("src/detector2.bmp");
	detect2Texture = SDL_CreateTextureFromSurface(renderer, detect2);

	detect3 = SDL_LoadBMP("src/detector3.bmp");
	detect3Texture = SDL_CreateTextureFromSurface(renderer, detect3);

	detect4 = SDL_LoadBMP("src/detector4.bmp");
	detect4Texture = SDL_CreateTextureFromSurface(renderer, detect4);

	detect5 = SDL_LoadBMP("src/detector5.bmp");
	detect5Texture = SDL_CreateTextureFromSurface(renderer, detect5);

	detect6 = SDL_LoadBMP("src/detector6.bmp");
	detect6Texture = SDL_CreateTextureFromSurface(renderer, detect6);

	detect7 = SDL_LoadBMP("src/detector7.bmp");
	detect7Texture = SDL_CreateTextureFromSurface(renderer, detect7);

	detect8 = SDL_LoadBMP("src/detector8.bmp");
	detect8Texture = SDL_CreateTextureFromSurface(renderer, detect8);

	discovery = SDL_LoadBMP("src/discovered.bmp");
	discoveryTexture = SDL_CreateTextureFromSurface(renderer, discovery);

	flag = SDL_LoadBMP("src/flag.bmp");
	flagTexture = SDL_CreateTextureFromSurface(renderer, flag);

	loseScreen = SDL_LoadBMP("src/loseScreen.bmp");
	loseScreenTexture = SDL_CreateTextureFromSurface(renderer, loseScreen);

	winScreen = SDL_LoadBMP("src/winScreen.bmp");
	winScreenTexture = SDL_CreateTextureFromSurface(renderer, winScreen);

	titleScreen = SDL_LoadBMP("src/titleScreen.bmp");
	titleScreenTexture = SDL_CreateTextureFromSurface(renderer, titleScreen);

	titleScreen2 = SDL_LoadBMP("src/titleScreen2.bmp");
	titleScreenTexture2 = SDL_CreateTextureFromSurface(renderer, titleScreen2);

	playButton = SDL_LoadBMP("src/play.bmp");
	playButtonTexture = SDL_CreateTextureFromSurface(renderer, playButton);

	quitButton = SDL_LoadBMP("src/leave.bmp");
	quitButtonTexture = SDL_CreateTextureFromSurface(renderer, quitButton);

	easyButton = SDL_LoadBMP("src/easy.bmp");
	easyButtonTexture = SDL_CreateTextureFromSurface(renderer, easyButton);

	mediumButton = SDL_LoadBMP("src/medium.bmp");
	mediumButtonTexture = SDL_CreateTextureFromSurface(renderer, mediumButton);

	hardButton = SDL_LoadBMP("src/hard.bmp");
	hardButtonTexture = SDL_CreateTextureFromSurface(renderer, hardButton);

	escapeButton = SDL_LoadBMP("src/pressEscape.bmp");
	escapeButtonTexture = SDL_CreateTextureFromSurface(renderer, escapeButton);

	if (bomb == NULL) {
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		fprintf(stderr, "Impossible de charger l'image\n");
	}

	if (bombTexture == NULL) {
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		fprintf(stderr, "Impossible de charger la texture\n");
	}

	while (inGame == 1) {
		if (start == -1) {
			SDL_RenderClear(renderer);
			SDL_Rect playB;
			playB.x = 260;  //the x coordinate
			playB.y = 250; // the y coordinate
			playB.w = mainButtonW; //the width of the texture
			playB.h = mainButtonH; //the height of the texture
			SDL_Rect quitB;
			quitB.x = 260;  //the x coordinate
			quitB.y = 420; // the y coordinate
			quitB.w = mainButtonW; //the width of the texture
			quitB.h = mainButtonH; //the height of the texture
			while (SDL_PollEvent(&event)) {
				//bouton quit
				if (event.type == SDL_KEYDOWN) {
					if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
						inGame = 0;
					}
					else if (event.key.keysym.scancode == SDL_SCANCODE_1) {
						start = 0;
					}

				}
				else if (event.type == SDL_MOUSEBUTTONDOWN) {
					if (event.button.button == SDL_BUTTON_LEFT) {
						boutons = SDL_GetMouseState(&x, &y);
						if (x >= 260 && x <= 460 && y >= 250 && y <= 350) {
							start = 0;
						}
						else if (x >= 260 && x <= 460 && y >= 420 && y <= 520) {
							inGame = 0;
						}
					}

				}
			}
			SDL_RenderCopy(renderer, titleScreenTexture, NULL, NULL);
			SDL_RenderCopy(renderer, playButtonTexture, NULL, &playB);
			SDL_RenderCopy(renderer, quitButtonTexture, NULL, &quitB);
			SDL_RenderPresent(renderer);
		}
		if (start == 0) {
			SDL_Rect easy;
			easy.x = 260;  //the x coordinate
			easy.y = 150; // the y coordinate
			easy.w = mainButtonW; //the width of the texture
			easy.h = mainButtonH; //the height of the texture
			SDL_Rect medium;
			medium.x = 260;  //the x coordinate
			medium.y = 320; // the y coordinate
			medium.w = mainButtonW; //the width of the texture
			medium.h = mainButtonH; //the height of the texture
			SDL_Rect hard;
			hard.x = 260;  //the x coordinate
			hard.y = 490; // the y coordinate
			hard.w = mainButtonW; //the width of the texture
			hard.h = mainButtonH; //the height of the texture
			while (SDL_PollEvent(&event)) {
				//bouton quit
				if (event.type == SDL_KEYDOWN) {
					if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
						inGame = 0;
					}
				}
				else if (event.type == SDL_MOUSEBUTTONDOWN) {
					if (event.button.button == SDL_BUTTON_LEFT) {
						boutons = SDL_GetMouseState(&x, &y);
						if (x >= 260 && x <= 460 && y >= 150 && y <= 250) {
							ligne = 7;
							bombNumber = 8;
							iSize = ligne * ligne;
							playing = 1;
							start = 1;
						}
						else if (x >= 260 && x <= 460 && y >= 320 && y <= 420) {
							ligne = 10;
							bombNumber = 17;
							iSize = ligne * ligne;
							playing = 1;
							start = 1;
						}

						else if (x >= 260 && x <= 460 && y >= 490 && y <= 590) {
							ligne = 12;
							bombNumber = 28;
							iSize = ligne * ligne;
							playing = 1;
							start = 1;
						}
						
					}

				}
			}
			

			SDL_RenderCopy(renderer, titleScreenTexture2, NULL, NULL);
			SDL_RenderCopy(renderer, easyButtonTexture, NULL, &easy);
			SDL_RenderCopy(renderer, mediumButtonTexture, NULL, &medium);
			SDL_RenderCopy(renderer, hardButtonTexture, NULL, &hard);
			SDL_RenderPresent(renderer);
		}
		int gridSize = ligne;
		int center = (windowSize - (gridSize * boxSize)) / 2;
		int* tab = (int*)malloc(sizeof(int) * iSize);
		for (int a = 0; a < iSize; ++a) {
			*(tab + a) = VIDE;
		}


		int* playground = (int*)malloc(sizeof(int) * iSize);
		for (int b = 0; b < iSize; ++b) {
			*(playground + b) = VIDE;
		}
		bombPlacement(playground, bombNumber, ligne);
		countgrid(playground, ligne);
		if (start == 1) {
			SDL_RenderClear(renderer);
			while (playing == 1)
			{

				if (gameOver == 0) {
					SDL_Rect ez;
					ez.x = 0;  //the x coordinate
					ez.y = 0; // the y coordinate
					ez.w = boxSize; //the width of the texture
					ez.h = boxSize; //the height of the texture
					for (int i = 0; i < gridSize; ++i) {
						for (int o = 0; o < gridSize; ++o) {
							ez = { i * boxSize + center, o * boxSize + center, boxSize, boxSize };
							if (i % 2 == 0) {
								if (o % 2 == 0) {
									SDL_SetRenderDrawColor(renderer, 71, 71, 71, 255);
								}
								else {
									SDL_SetRenderDrawColor(renderer, 55, 55, 55, 255);

								}
							}
							else {
								if (o % 2 == 0) {
									SDL_SetRenderDrawColor(renderer, 55, 55, 55, 255);
								}
								else {
									SDL_SetRenderDrawColor(renderer, 71, 71, 71, 255);
								}
							}

							SDL_RenderFillRect(renderer, &ez);


						}


					}
					int c1 = -1;
					int l1 = -1;
					int c2 = -1;
					int l2 = -1;
					while (SDL_PollEvent(&event)) {
						if (event.type == SDL_MOUSEBUTTONDOWN)
						{
							if (event.button.button == SDL_BUTTON_RIGHT) {
								boutons = SDL_GetMouseState(&x, &y);
								//printf("Clic droit a la positions %d - %d\n", x, y);
								if (x >= center && x <= windowSize - center && y >= center && y <= windowSize - center) {
									for (int i = 0; i < gridSize; ++i) {

										if ((boxSize * (i)) + center <= x && x <= (boxSize * (i + 1)) + center)
										{
											//printf("Colonne %i \n", i);
											c1 = i;
										}

										if ((boxSize * (i)) + center <= y && y <= (boxSize * (i + 1)) + center)
										{
											l1 = i;
											//printf(" %d \n", l2);
										}
									}
									play(playground, tab, ligne, c1, l1, 1);
								}
								else {
									printf("Vous ne pouvez pas jouer ici. \n");
								}


							}
							else if (event.button.button == SDL_BUTTON_LEFT) {
								boutons = SDL_GetMouseState(&x, &y);
								//printf("Clic gauche a la positions %d - %d\n", x, y);
								//proto affichage
								if (x >= center && x <= windowSize - center && y >= center && y <= windowSize - center) {
									for (int i = 0; i < gridSize; ++i) {

										if ((boxSize * (i)) + center <= x && x <= (boxSize * (i + 1)) + center)
										{
											//printf("Colonne %i \n", i);
											c2 = i;
										}

										if ((boxSize * (i)) + center <= y && y <= (boxSize * (i + 1)) + center)
										{
											l2 = i;
											//printf(" %d \n", l2);
										}
									}
									play(playground, tab, ligne, c2, l2, 0);
								}
								else {
									printf("Vous ne pouvez pas jouer ici. \n");
								}




							}



						}
						//else if (event.type == SDL_KEYDOWN) {
							//if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
								//playing = 0;
							//}
						//}
					}

					//Listage de la comparaison avec la tablOOOO
					for (int a = 0; a < ligne; ++a) {
						for (int b = 0; b < ligne; ++b) {
							if (tab[(a)*ligne + (b)] == 0) {
								if (b >= NULL && a >= NULL) {
									ez = { ((b)*boxSize) + center,((a)*boxSize) + center,boxSize,boxSize };
									SDL_RenderCopy(renderer, discoveryTexture, NULL, &ez);
								}
							}
							if (tab[(a)*ligne + (b)] == 1) {
								if (a >= NULL && b >= NULL) {
									ez = { ((b)*boxSize) + center,((a)*boxSize) + center,boxSize,boxSize };
									SDL_RenderCopy(renderer, detect1Texture, NULL, &ez);
								}
							}
							if (tab[(a)*ligne + (b)] == 2) {
								if (a >= NULL && b >= NULL) {
									ez = { ((b)*boxSize) + center,((a)*boxSize) + center,boxSize,boxSize };
									SDL_RenderCopy(renderer, detect2Texture, NULL, &ez);
								}
							}
							if (tab[(a)*ligne + (b)] == 3) {
								if (b >= NULL && a >= NULL) {
									ez = { ((b)*boxSize) + center,((a)*boxSize) + center,boxSize,boxSize };
									SDL_RenderCopy(renderer, detect3Texture, NULL, &ez);
								}
							}
							if (tab[(a)*ligne + (b)] == 4) {
								if (a >= NULL && b >= NULL) {
									ez = { ((b)*boxSize) + center,((a)*boxSize) + center,boxSize,boxSize };
									SDL_RenderCopy(renderer, detect4Texture, NULL, &ez);
								}
							}
							if (tab[(a)*ligne + (b)] == 5) {
								if (a >= NULL && b >= NULL) {
									ez = { ((a)*boxSize) + center,((a)*boxSize) + center,boxSize,boxSize };
									SDL_RenderCopy(renderer, detect5Texture, NULL, &ez);
								}
							}
							if (tab[(a)*ligne + (b)] == 6) {
								if (a >= NULL && b >= NULL) {
									ez = { ((b)*boxSize) + center,((a)*boxSize) + center,boxSize,boxSize };
									SDL_RenderCopy(renderer, detect6Texture, NULL, &ez);
								}
							}
							if (tab[(a)*ligne + (b)] == 7) {
								if (a >= NULL && b >= NULL) {
									ez = { ((b)*boxSize) + center,((a)*boxSize) + center,boxSize,boxSize };
									SDL_RenderCopy(renderer, detect7Texture, NULL, &ez);
								}
							}
							if (tab[(a)*ligne + (b)] == 8) {
								if (a >= NULL && b >= NULL) {
									ez = { ((b)*boxSize) + center,((a)*boxSize) + center,boxSize,boxSize };
									SDL_RenderCopy(renderer, detect8Texture, NULL, &ez);
								}
							}
							if (tab[(a)*ligne + (b)] == BOMB) {
								if (a >= NULL && b >= NULL) {
									ez = { ((b)*boxSize) + center,((a)*boxSize) + center,boxSize,boxSize };
									SDL_RenderCopy(renderer, bombTexture, NULL, &ez);
									gameOver = 1;
								}

							}
							if (tab[(a)*ligne + (b)] == FLAG) {
								if (a >= NULL && b >= NULL) {
									ez = { ((b)*boxSize) + center,((a)*boxSize) + center,boxSize,boxSize };
									SDL_RenderCopy(renderer, flagTexture, NULL, &ez);
								}
							}
						}
					}
					if (winCondition(tab, playground, ligne, bombNumber) == true) {
						gameOver = 2;
					}
				}


				if (gameOver == 1) {
					SDL_Rect escape;
					escape.x = 260;  //the x coordinate
					escape.y = 500; // the y coordinate
					escape.w = mainButtonW; //the width of the texture
					escape.h = mainButtonH; //the height of the texture
					while (SDL_PollEvent(&event)) {
						if (event.type == SDL_KEYDOWN) {
							if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
								start = -1;
								gameOver = 0;
								playing = 0;
							}
						}
						else if (event.type == SDL_MOUSEBUTTONDOWN) {
							if (event.button.button == SDL_BUTTON_LEFT) {
								boutons = SDL_GetMouseState(&x, &y);
								if (x >= 260 && x <= 460 && y >= 500 && y <= 600) {
									start = -1;
									gameOver = 0;
									playing = 0;
								}
							}
						}
					}

					SDL_RenderCopy(renderer, loseScreenTexture, NULL, NULL);
					SDL_RenderCopy(renderer, escapeButtonTexture, NULL, &escape);
					SDL_RenderPresent(renderer);
				}

				if (gameOver == 2) {
					SDL_Rect escape;
					escape.x = 260;  //the x coordinate
					escape.y = 500; // the y coordinate
					escape.w = mainButtonW; //the width of the texture
					escape.h = mainButtonH; //the height of the texture
					while (SDL_PollEvent(&event)) {
						if (event.type == SDL_KEYDOWN) {
							if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
								start = -1;
								gameOver = 0;
								playing = 0;
							}
						}
						else if (event.type == SDL_MOUSEBUTTONDOWN) {
							if (event.button.button == SDL_BUTTON_LEFT) {
								boutons = SDL_GetMouseState(&x, &y);
								if (x >= 260 && x <= 460 && y >= 500 && y <= 600) {
									start = -1;
									gameOver = 0;
									playing = 0;
								}
							}
						}
					}
					SDL_RenderCopy(renderer, winScreenTexture, NULL, NULL);
					SDL_RenderCopy(renderer, escapeButtonTexture, NULL, &escape);
					SDL_RenderPresent(renderer);
				}



				//EVENT

				//UPDATE

				//RENDER

				SDL_SetRenderDrawColor(renderer, 22, 22, 23, 255);
				SDL_RenderPresent(renderer);
			}
		}

	}

	Mix_FreeMusic(musique); //Libération de la musique
	Mix_CloseAudio(); //Fermeture de l'API
	SDL_RenderClear(renderer);



	//dessin





	//def variable Quit

Quit:
	if (NULL != renderer)
		SDL_DestroyRenderer(renderer);
	if (NULL != window)
		SDL_DestroyWindow(window);
	SDL_Quit();
	return statut;


}