#include <stdbool.h>
#include <raylib.h>
#include <stdlib.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

#define SQUARE_SIZE 20
#define NR_SQUARES_X SCREEN_WIDTH/SQUARE_SIZE
#define NR_SQUARES_Y SCREEN_HEIGHT/SQUARE_SIZE

int get_living_neighbours(bool** grid,int x,int y){
	int alive_neighbours = 0;

	for(int dx=-1; dx<=1; dx++){
		for(int dy = -1; dy<=1; dy++){
			if(x+dx>=0 && x+dx < NR_SQUARES_X && y+dy >= 0 && y+dy < NR_SQUARES_Y){
				if(grid[x+dx][y+dy]){
					alive_neighbours++;
				}
			}
		}
	}

	if(grid[x][y])
		alive_neighbours--;

	return alive_neighbours;
}

void update_grid(bool** grid,bool** next_state){

	for(int y=0; y<NR_SQUARES_Y; y++){
		for(int x=0; x<NR_SQUARES_X; x++){
			int neighbours = get_living_neighbours(grid,x,y);

			if(grid[x][y]){
				if(neighbours<2 || neighbours>3)
					next_state[x][y] = false;
				else
					next_state[x][y] = true;
				
			}else{
				if(neighbours == 3)
					next_state[x][y]=true;
			}
		}
	}

	for(int x=0; x<NR_SQUARES_X; x++){
		for(int y=0; y<NR_SQUARES_Y; y++){
			grid[x][y]=next_state[x][y];
		}
	}
}

void init_matricies(bool** grid,bool** next_state){
	for(int i=0; i<NR_SQUARES_X; i++){
		grid[i] = (bool*)malloc(NR_SQUARES_Y*sizeof(bool*));
		next_state[i] = (bool*)malloc(NR_SQUARES_Y*sizeof(bool*));
		for(int j=0; j<NR_SQUARES_Y; j++){
			grid[i][j] = false;
			next_state[i][j] = false;
		}
	}
}

void free_memory(bool** grid,bool** next_state){
	for(int i=0; i<NR_SQUARES_X; i++){
		free(grid[i]);
		free(next_state[i]);
	}

	free(grid);
	free(next_state);
}

int main(int argc,char** argv){
	InitWindow(SCREEN_WIDTH,SCREEN_HEIGHT,"mandelbrot set");
	SetTargetFPS(60);

	bool **grid=(bool**)malloc(NR_SQUARES_X*sizeof(bool*));
	bool **next_state=(bool**)malloc(NR_SQUARES_X*sizeof(bool*));
	init_matricies(grid,next_state);

	bool start = false;

	while(!WindowShouldClose()){

		if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !start){
			Vector2 pos = GetMousePosition();
			grid[(int)pos.x/SQUARE_SIZE][(int)pos.y/SQUARE_SIZE]=true;
		}else if(start){
			update_grid(grid,next_state);
		}else if(IsKeyReleased(KEY_ENTER)){
			start=true;
		}

		BeginDrawing();

			ClearBackground(WHITE);

			for(int y=0; y<NR_SQUARES_Y; y++){
				for(int x=0; x<NR_SQUARES_X; x++){
					Rectangle cell = { (float)SQUARE_SIZE*x, (float)SQUARE_SIZE*y, SQUARE_SIZE,SQUARE_SIZE}; 
					if(grid[x][y]){
						DrawRectangleRec(cell,BLACK);
					}
				}
			}


			WaitTime(0.2);

		EndDrawing();
	}

	CloseWindow();

	free_memory(grid,next_state);	

	return 0;
}
