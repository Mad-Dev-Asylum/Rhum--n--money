#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include "menu.h"
#include "config.h"
#include "structs.h"
#include "widget.h"


int main(int argc, char * argv[]){
    initSDL();	// Starts the SDL
    menu();	// Load main menu
    SDL_Quit();	// After menu did its job, stops SDL

    return(EXIT_SUCCESS);
}


int initSDL(){
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) == -1){
	perror("! Failed to initialise SDL");
	exit(EXIT_FAILURE);
    }

    if ((screen = SDL_SetVideoMode(WIN_WIDTH, WIN_HEIGHT, 8, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL){
	perror("! Failed to initialise screen");
	SDL_Quit();
	exit(EXIT_FAILURE);
    }

    SDL_WM_SetCaption("Rhum 'n' Money", "Rhum 'n' Money");

    return(1);
}


int menu(){
    /* VARS */
    widget * background;
    widget * new_game;
    widget * load_game;
    widget * options;
    widget * scores;
    widget * credits;
    widget * quit;
    SDL_Event event;
    char cont = 1;

    /* LOAD */
    background = WLoadBMP("IMG/menu/background.bmp", 0, 0);
    new_game = WLoadBMP("IMG/menu/newgame.bmp", 10, 10);
    load_game = WLoadBMP("IMG/menu/loadgame.bmp", 10, 90);
    options = WLoadBMP("IMG/menu/options.bmp", 10, 170);
    scores = WLoadBMP("IMG/menu/scores.bmp", 10, 250);
    credits = WLoadBMP("IMG/menu/credits.bmp", 10, 330);
    quit = WLoadBMP("IMG/menu/quit.bmp", 10, 410);

    /* BLIT */
    WBlit(background);
    WBlit(new_game);
    WBlit(load_game);
    WBlit(options);
    WBlit(scores);
    WBlit(credits);
    WBlit(quit);

    SDL_Flip(screen);

    /* EVENTS */
    while(cont){
	SDL_WaitEvent(&event);
	switch (event.type){
	    case SDL_QUIT :
		cont = 0;
		break;
	    case SDL_MOUSEBUTTONDOWN :
		if (event.button.button == SDL_BUTTON_LEFT){
		    if (event.button.x >= new_game->pos.x && event.button.x < new_game->pos.x + WGetWidth(new_game) && event.button.y >= new_game->pos.y && event.button.y < new_game->pos.y + WGetHeight(new_game)){
			newGame();
		    }
		    else if (event.button.x >= load_game->pos.x && event.button.x < load_game->pos.x + WGetWidth(load_game) && event.button.y >= load_game->pos.y && event.button.y < load_game->pos.y + WGetHeight(load_game)){
			loadGame();
		    }
		    else if (event.button.x >= options->pos.x && event.button.x < options->pos.x + WGetWidth(options) && event.button.y >= options->pos.y && event.button.y < options->pos.y + WGetHeight(options)){
			showOptions();
		    }
		    else if (event.button.x >= scores->pos.x && event.button.x < scores->pos.x + WGetWidth(scores) && event.button.y >= scores->pos.y && event.button.y < scores->pos.y + WGetHeight(scores)){
			showScores();
		    }
		    else if (event.button.x >= credits->pos.x && event.button.x < credits->pos.x + WGetWidth(credits) && event.button.y >= credits->pos.y && event.button.y < credits->pos.y + WGetHeight(credits)){
			showCredits();
		    }
		    else if (event.button.x >= quit->pos.x && event.button.x < quit->pos.x + WGetWidth(quit) && event.button.y >= quit->pos.y && event.button.y < quit->pos.y + WGetHeight(quit)){
			cont = 0;
		    }
		}
		break;
	}
    }

    /* FREE */
    WFree(background);
    WFree(new_game);
    WFree(load_game);
    WFree(options);
    WFree(scores);
    WFree(credits);
    WFree(quit);

    return(1);
}


int newGame(){
    printf("¤ Launching new game...\n");
    return(1);
}


int loadGame(){
    printf("¤ Loading old save...\n");
    return(1);
}


void showOptions(){
    printf("¤ Showing options...\n");
}


void showScores(){
    printf("¤ Showing scores...\n");
}


void showCredits(){
    printf("¤ Showing credits...\n");
}
