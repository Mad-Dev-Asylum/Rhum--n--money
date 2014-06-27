#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include "menu.h"
#include "config.h"
#include "structs.h"
#include "widget.h"
#include "cursor.h"


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

    SDL_ShowCursor(SDL_DISABLE);

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
    widget * w_curs;
    cursor * curs;
    widget * tmp;
    SDL_Event event;
    char cont = 1;
    char select = 1;

    /* LOAD */
    background = WLoadBMP("IMG/menu/background.bmp", 0, 0);
    new_game = WLoadBMP("IMG/menu/newgame.bmp", 10, 10);
    load_game = WLoadBMP("IMG/menu/loadgame.bmp", 10, 90);
    options = WLoadBMP("IMG/menu/options.bmp", 10, 170);
    scores = WLoadBMP("IMG/menu/scores.bmp", 10, 250);
    credits = WLoadBMP("IMG/menu/credits.bmp", 10, 330);
    quit = WLoadBMP("IMG/menu/quit.bmp", 10, 410);
    w_curs = WLoadIMG("IMG/menu/cursor.gif", 0, 0);

    /* ADD CONTENT TO BACKGROUND */
    WAddContent(background, new_game);
    WAddContent(background, load_game);
    WAddContent(background, options);
    WAddContent(background, scores);
    WAddContent(background, credits);
    WAddContent(background, quit);
    WAddContent(background, w_curs);

    /* CREATE THE CURSOR */
    curs = WCreateCursor(w_curs, RIGHT);

    WBlit(background);

    SDL_Flip(screen);

    /* EVENTS */
    while(cont){
	SDL_WaitEvent(&event);
	switch(event.type){
	    /* Left click */
	    case SDL_MOUSEBUTTONDOWN :
		if (event.button.button = SDL_BUTTON_LEFT){
		    tmp = WArea(background, event.button.x, event.button.y);
		    if (tmp == new_game){
			newGame();
		    }
		    if (tmp == load_game){
			loadGame();
		    }
		    if (tmp == options){
			showOptions();
		    }
		    if (tmp == scores){
			showScores();
		    }
		    if (tmp == credits){
			showCredits();
		    }
		    if (tmp == quit){
			cont = 0;
		    }
		}
		break;
	    case SDL_QUIT :
		cont = 0;
		break;
	    /* Keyboard event */
	    case SDL_KEYDOWN :
		switch (event.key.keysym.sym){
		    case SDLK_DOWN : 
			if (select < 6){
			    select ++;
			}
			break;
		    case SDLK_UP :
			if (select > 1){
			    select --;
			}
			break;
		    case SDLK_RETURN :
			switch (select){
			    case 1 :
				newGame();
				break;
			    case 2 :
				loadGame();
				break;
			    case 3 :
				showOptions();
				break;
			    case 4 :
				showScores();
				break;
			    case 5 :
				showCredits();
				break;
			    case 6 :
				cont = 0;
				break;
			}
			break;
		}
		break;
	    /* If the mouse moves... */
	    case SDL_MOUSEMOTION :
		WMoveCursor(curs, event.button.x, event.button.y);
		WBlit(background);
		SDL_Flip(screen);
		break;
	}
    }

    /* FREE */
    WFreeCursor(curs);
    WFree(background);

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
