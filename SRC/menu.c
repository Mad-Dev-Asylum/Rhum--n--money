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
    background = WLoadIMG(FIXED, 0, 0, 0, "IMG/menu/background.bmp", NULL);
    new_game = WLoadIMG(FIXED, 0, 10, 10, "IMG/menu/newgame.bmp", NULL);
    load_game = WLoadIMG(FIXED, 0, 10, 90, "IMG/menu/loadgame.bmp", NULL);
    options = WLoadIMG(FIXED, 0, 10, 170, "IMG/menu/options.bmp", NULL);
    scores = WLoadIMG(FIXED, 0, 10, 250, "IMG/menu/scores.bmp", NULL);
    credits = WLoadIMG(FIXED, 0, 10, 330, "IMG/menu/credits.bmp", NULL);
    quit = WLoadIMG(FIXED, 0, 10, 410, "IMG/menu/quit.bmp", NULL);
    w_curs = WLoadIMG(LOOP, 130, 0, 0, "IMG/cursor/cursor1.png", "IMG/cursor/cursor2.png", "IMG/cursor/cursor3.png", "IMG/cursor/cursor4.png", "IMG/cursor/cursor5.png", "IMG/cursor/cursor6.png", NULL);

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
	SDL_PollEvent(&event);
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
		break;
	}
	event.type = 0;

	/* Refresh */
	WFlip(background);
	WBlit(background);
	SDL_Flip(screen);
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
