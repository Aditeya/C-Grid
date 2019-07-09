#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

#define WIDTH 600
#define HEIGHT 600
#define SPEED 5
#define POINTS 275

int W(int x);
int H(int y);

int main(void) {

	// init graphics and timer
	if( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
		printf("error initializing SDL: %s\n", SDL_GetError());
		return 1;
	}

	SDL_Window* win = SDL_CreateWindow("Graph Grid",
										SDL_WINDOWPOS_CENTERED,
										SDL_WINDOWPOS_CENTERED,
										WIDTH, HEIGHT, 0);

	if(!win) {
		printf("Error Creating window: %s\n", SDL_GetError());
		SDL_Quit();
		return 1;
	}

	Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);
	if(!rend) {
		printf("Error creating renderer: %s\n",SDL_GetError());
		SDL_DestroyWindow(win);
		SDL_Quit();
		return 1;
	}



	int up = 0,
		down = 0,
		left = 0, 
		right = 0;
	float xpos = W(100),
		  ypos = H(100),
		  x_vel = 0,
		  y_vel = 0;

	// make points for sinewave
	SDL_Point points[(POINTS * 2)+1];
	for(int i = -POINTS; i <= POINTS; i++) {
		points[i + POINTS].x = W(i);
		points[i + POINTS].y = H(50*sin(12.5*i)); //50 for height & 12.5 for period
	}

	int close_requested = 0;
	while(!close_requested) {
		SDL_Event event;
		while( SDL_PollEvent(&event) ) {
			switch( event.type) {
				case SDL_QUIT:
					close_requested = 1;
					break;
				case SDL_KEYDOWN:
					switch(event.key.keysym.scancode) {
						case SDL_SCANCODE_W:
            			case SDL_SCANCODE_UP:
            			    up = 1;
            			    break;
            			case SDL_SCANCODE_A:
            			case SDL_SCANCODE_LEFT:
            			    left = 1;
            			    break;
            			case SDL_SCANCODE_S:
            			case SDL_SCANCODE_DOWN:
            			    down = 1;
            			    break;
            			case SDL_SCANCODE_D:
            			case SDL_SCANCODE_RIGHT:
            			    right = 1;
            			    break;
						default:
							break;
					}
					break;
				case SDL_KEYUP:
					switch(event.key.keysym.scancode) {
               			case SDL_SCANCODE_W:
               			case SDL_SCANCODE_UP:
               			    up = 0;
               			    break;
               			case SDL_SCANCODE_A:
               			case SDL_SCANCODE_LEFT:
               			    left = 0;
               			    break;
               			case SDL_SCANCODE_S:
               			case SDL_SCANCODE_DOWN:
               			    down = 0;
               			    break;
               			case SDL_SCANCODE_D:
               			case SDL_SCANCODE_RIGHT:
               			    right = 0;
               			    break;
						default:
							break;
					}
					break;
				default:
					break;
			}
		}

		// Background Colour
		SDL_SetRenderDrawColor(rend, 60, 63, 128, 255);
		SDL_RenderClear(rend);

		// Grid Lines
		SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
		for(unsigned int i = 25; i <= 575; i += 25) {
			SDL_RenderDrawLine(rend, i, 25, i, 575);
			SDL_RenderDrawLine(rend, 25, i, 575, i);
		}

		// Thick Lines for x axis
		SDL_RenderDrawLine(rend, 25, 299, 575, 299);
		SDL_RenderDrawLine(rend, 25, 301, 575, 301);

		// Thick Lines for y axis
		SDL_RenderDrawLine(rend, 299, 25, 299, 575);
		SDL_RenderDrawLine(rend, 301, 25, 301, 575);

		// Render Sine Wave
		SDL_RenderDrawLines(rend, points, POINTS*2);

		// Line movement calculations
		x_vel = y_vel = 0;
		if(up && !down) y_vel = -SPEED;
		if(down && !up) y_vel = SPEED;
		if(left && !right) x_vel = -SPEED;
		if(right && !left) x_vel = SPEED;

		xpos += x_vel;
		ypos += y_vel;

		if(xpos <= 25) xpos = 25;
		if(ypos <= 25) ypos = 25;
		if(xpos >= 575) xpos = 575;
		if(ypos >= 575) ypos = 575;

		// Draw Line
		SDL_SetRenderDrawColor(rend, 255, 0, 0, 255);
		SDL_RenderDrawLine(rend, W(0), H(0), xpos, ypos);

		// Present Render
		SDL_RenderPresent(rend);
		SDL_Delay(1000/60);
	}


	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(win);
	SDL_Quit();

	return 0;
}

int W(int x) {
	return x + WIDTH/2;
}

int H(int y) {
	return -y + HEIGHT/2;
}
