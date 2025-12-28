#include <iostream>
#include <raylib.h>
#include <stack>
#include <queue>
#define ROWS 25
#define COLS 25
using namespace std;

// DEAD_END means from that cell there's no unexplored neighbour left

const int SIZE = 25, BOT = 1, END = 9, WALL = 8, VISITED = 2, DEAD_END = 3, BOT_SIZE = 5;
int no_paths = 0, crt_val = 0;

Vector2 getBotPixel(int grid_x, int grid_y, int cell_w, int cell_h)
{
	return { grid_y * cell_w + cell_w / 2.0f, grid_x * cell_h + cell_h / 2.0f };
}
void Draw_Maze(int cell_width, int cell_height, bool& maze_solved, int& bot_pos_x, int& bot_pos_y, int(*maze)[SIZE])
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (maze[i][j] == WALL)
			{
				DrawRectangle(j * cell_width, i * cell_height, cell_width, cell_height, BLUE);
			}
			if (maze[i][j] == END)
			{
				DrawRectangle(j * cell_width, i * cell_height, cell_width, cell_height, PINK);
			}
			if (maze[i][j] == VISITED && maze[i][j] != END)
			{
				DrawRectangle(j * cell_width, i * cell_height, cell_width, cell_height, GREEN);
			}
			if (maze[i][j] == DEAD_END && maze[i][j] != END)
			{
				DrawRectangle(j * cell_width, i * cell_height, cell_width, cell_height, RED);
			}
			DrawRectangleLines(j * cell_width, i * cell_height, cell_width, cell_height, BLACK);
		}
	};
	Vector2 bot_pix = getBotPixel(bot_pos_x, bot_pos_y, cell_width, cell_height);
	DrawCircleV(bot_pix, BOT_SIZE, GRAY);
}
bool is_valid(int x, int y, int(*maze)[SIZE])
{
	return x >= 0 && x < COLS && y >= 0 && y < ROWS && maze[x][y] != WALL;
}
bool solved(int x, int y, int end_x, int end_y)
{
	return (x == end_x && y == end_y);
}
void back_track(int& x, int& y, int& end_x, int& end_y, bool& end_reached, stack<Vector2>& memory, int(*maze)[SIZE])
{
	if (memory.empty()) return;
	maze[x][y] = DEAD_END;
	auto prev_ele = memory.top();
	memory.pop();
	x = (int)prev_ele.x; y = (int)prev_ele.y;
}
void solve(int& x, int& y, int& end_x, int& end_y, bool& end_reached, stack<Vector2>& memory, int(*maze)[SIZE])
{
	int dx[4] = { 1,-1,0,0 };
	int dy[4] = { 0,0,1,-1 };
	int nx = x; int ny = y;
	for (int d = 0; d < 4; d++)
	{
		nx = x + dx[d];
		ny = y + dy[d];
		if (is_valid(nx, ny, maze) && maze[nx][ny] != VISITED && maze[nx][ny] != DEAD_END)
		{
			Vector2 pre_pos = { x,y };
			memory.push(pre_pos);
			maze[x][y] = VISITED;
			x = nx; y = ny;
			return;
		}
	}
	back_track(x, y, end_x, end_y, end_reached, memory, maze);

}
void find_path(int end_x, int end_y, int(*Emaze)[SIZE])
{
	Emaze[end_x][end_y] = crt_val;
	queue<pair<int, int>> q;
	int dx[4] = { 1,-1,0,0 };
	int dy[4] = { 0,0,1,-1 };
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (Emaze[i][j] == 0)
			{
				q.push({i,j});
			}
			else if (Emaze[i][j] > 0)
			{
				Emaze[i][j] = INT_MAX;
			}
		}
	}

	while (!q.empty())
	{
		auto x = q.front().first; auto y = q.front().second;
		q.pop();

		for (int d = 0; d < 4; d++)
		{
			int nx = x + dx[d];
			int ny = y + dy[d];

			if (nx < 0 || nx >= SIZE || ny < 0 || ny >= SIZE)
			{
				continue;
			}
			if (Emaze[nx][ny] < 0)
			{
				continue;
			}
			if (Emaze[nx][ny] == INT_MAX)
			{
				Emaze[nx][ny] = Emaze[x][y] + 1;
				q.push({ nx,ny });
			}
		}
	}
}
void DrawEmaze(int cell_width, int cell_height, bool& maze_solved, int& bot_pos_x, int& bot_pos_y, int(*Emaze)[SIZE])
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (Emaze[i][j] == -1)
			{
				DrawRectangle(j * cell_width, i * cell_height, cell_width, cell_height, BLUE);
			}
			else if (Emaze[i][j] == 0)
			{
				DrawRectangle(j * cell_width, i * cell_height, cell_width, cell_height, RED);
			}
			else
			{
				DrawRectangle(j * cell_width, i * cell_height, cell_width, cell_height, RAYWHITE);
			}
			DrawRectangleLines(j * cell_width, i * cell_height, cell_width, cell_height, BLACK);
		}
		
	};
	Vector2 bot_pix = getBotPixel(bot_pos_x, bot_pos_y, cell_width, cell_height);
	DrawCircleV(bot_pix, BOT_SIZE, GRAY);
}
void MoveBot(int& x, int& y, int& end_x, int& end_y, bool& end_reached, int(*Emaze)[SIZE], stack<Vector2>& path_mem)
{
	if (solved(x, y, end_x, end_y))
	{
		end_reached = true;
		return;
	}
	int dx[4] = { 1,-1,0,0 };
	int dy[4] = { 0,0,1,-1 };
	int nx = x; int ny = y;
	for (int d = 0; d < 4; d++)
	{
		nx = x + dx[d];
		ny = y + dy[d];
		if (nx < 0 || nx >= SIZE || ny < 0 || ny >= SIZE)
		{
			continue;
		}
		if (Emaze[nx][ny] != -1 && Emaze[nx][ny] < Emaze[x][y] && Emaze[nx][ny] >= 0)
		{
			Vector2 p = { x,y };
			path_mem.push(p);
			x = nx; y = ny;
			return;
		}
	}
}
void DrawGoldenPath(stack<Vector2> path_mem, int cell_width, int cell_height)
{
	while (!path_mem.empty())
	{
		Vector2 p = path_mem.top();
		path_mem.pop();
		DrawRectangle(p.y * cell_width, p.x * cell_height, cell_width, cell_height, GOLD);
	}
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			DrawRectangleLines(j * cell_width, i * cell_height, cell_width, cell_height, BLACK);
		}
	}
	
}

int main()
{
	const int screen_width = 500, screen_height = 500;
	const int cell_width = screen_width / ROWS;
	const int cell_height = screen_height / ROWS;
	bool maze_solved = false, path_initilized = false;

	int start_pos_x = 0, start_pos_y = 0, end_pos_x = 0, end_pos_y = 0, end_x = 0, end_y = 0, start_x = 0, start_y = 0;
	stack<Vector2>memory, path_mem;
	
	int explored_maze[SIZE][SIZE] = { 0 }, final_maze[SIZE][SIZE] = { 0 };
	int maze[SIZE][SIZE] =
	{
    {8,8,8,8,8,8,8,8,8,8,8,8,1,8,8,8,8,8,8,8,8,8,8,8,8},
	{8,0,0,0,8,0,0,0,0,0,8,0,0,0,8,0,0,0,0,0,0,0,8,0,8},
	{8,0,8,0,8,0,8,8,8,0,8,8,8,0,8,0,8,8,8,8,8,0,8,0,8},
	{8,0,8,0,0,0,8,0,0,0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,8},
	{8,0,8,8,8,8,8,0,8,8,8,8,8,0,8,8,8,0,8,8,8,8,8,8,8},
	{8,0,0,0,0,0,0,0,8,0,0,0,8,0,8,0,0,0,0,0,0,0,0,0,8},
	{8,8,8,0,8,8,8,8,8,0,8,0,8,0,8,0,8,8,8,0,8,8,8,0,8},
	{8,0,8,0,8,0,0,0,0,0,8,0,0,0,8,0,0,0,8,0,0,0,8,0,8},
	{8,0,8,0,8,0,8,8,8,8,8,8,8,8,8,8,8,0,8,0,8,8,8,0,8},
	{8,0,0,0,8,0,0,0,0,0,0,0,0,0,0,0,0,0,8,0,8,0,0,0,8},
	{8,0,8,8,8,8,8,0,8,8,8,8,8,0,8,8,8,8,8,0,8,0,8,8,8},
	{8,0,0,0,0,0,8,0,8,0,0,0,0,0,0,0,0,0,8,0,0,0,8,0,8},
	{8,8,8,8,8,0,8,0,8,0,8,8,8,8,8,8,8,0,8,0,8,8,8,0,8},
	{8,0,0,0,8,0,0,0,8,0,8,0,0,0,0,0,8,0,0,0,0,0,0,0,8},
	{8,0,8,0,8,8,8,8,8,0,8,0,8,8,8,0,8,8,8,0,8,8,8,8,8},
	{8,0,8,0,0,0,0,0,0,0,8,0,8,0,8,0,0,0,8,0,8,0,0,0,8},
	{8,0,8,8,8,8,8,0,8,8,8,0,8,0,8,8,8,0,8,0,8,0,8,0,8},
	{8,0,0,0,0,0,8,0,0,0,0,0,8,0,0,0,0,0,8,0,0,0,8,0,8},
	{8,8,8,0,8,0,8,8,8,8,8,8,8,8,8,0,8,8,8,8,8,8,8,0,8},
	{8,0,8,0,8,0,0,0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,0,0,8},
	{8,0,8,0,8,8,8,0,8,8,8,0,8,0,8,8,8,8,8,0,8,8,8,8,8},
	{8,0,0,0,0,0,8,0,8,0,0,0,8,0,0,0,0,0,8,0,8,0,0,0,8},
	{8,0,8,8,8,0,8,0,8,0,8,8,8,8,8,8,8,0,8,0,8,0,8,0,8},
	{8,0,8,0,0,0,0,0,8,0,0,0,0,0,0,0,0,0,0,0,8,0,8,0,8},
	{8,8,8,8,8,8,8,8,8,8,8,8,9,8,8,8,8,8,8,8,8,8,8,8,8}
	};


	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (maze[i][j] == BOT)
			{
				start_pos_x = i; start_pos_y = j;
				start_x = i; start_y = j;
			}
			if (maze[i][j] == END)
			{
				end_pos_x = i; end_pos_y = j;
				end_x = i; end_y = j;
			}
		}
	}
	Vector2 st_ = { start_pos_x,start_pos_y };
	memory.push(st_);
	InitWindow(screen_width, screen_height, "Tryna_Give_Visual_to_my_DFS");
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);
		if (memory.empty())
		{
			if (!path_initilized)
			{
				for (int i = 0; i < SIZE; i++)
				{
					for (int j = 0; j < SIZE; j++)
					{
						maze[end_x][end_y] = END;
						if (maze[end_x][end_y] == END)
						{
							explored_maze[end_x][end_y] = 0;
						}
						if (maze[i][j] == WALL)
						{
							explored_maze[i][j] = -1;
						}
						else
						{
							explored_maze[i][j] = 9999;
						}

					}
				}
			}
			path_initilized = true;

			find_path(end_x, end_y, explored_maze);
			DrawEmaze(cell_width, cell_height, maze_solved, start_x, start_y, explored_maze);
			MoveBot(start_x, start_y, end_x, end_y, maze_solved, explored_maze, path_mem);
		}
		if(!memory.empty())
		{
			Draw_Maze(cell_width, cell_height, maze_solved, start_pos_x, start_pos_y, maze);
			solve(start_pos_x, start_pos_y, end_pos_x, end_pos_y, maze_solved, memory, maze);
		}
		if (maze_solved)
		{
			DrawGoldenPath(path_mem,cell_width,cell_height);
		}

		EndDrawing();
	}
	CloseWindow();

}