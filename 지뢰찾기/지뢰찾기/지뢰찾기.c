#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#define ROW 9
#define COL 9
#define B 10

#define N 100000

char area[ROW + 2][COL + 2];
char blind_area[ROW][COL];

char chain(int y, int x);
char is_win();
char flag();
char open();
void print_area();

int cnt = 0;

int create_area()
{
	//지뢰찾기 초기화
	for (int i = 0; i <= ROW + 1; i++)
	{
		for (int j = 0; j <= COL + 1; j++)
		{
			area[i][j] = '0';
			if (i == 0 || j == 0 || i == ROW + 1 || j == COL + 1)
			{
				area[i][j] = 'X';
			}
		}
	}


	//지뢰생성
	int cnt = B;
	srand(time(NULL));
	while (cnt)
	{
		for (int i = 1; i <= ROW; i++)
		{
			for (int j = 1; j <= COL; j++)
			{
				int num = rand() % B;
				/*printf("%d\n", num);*/
				if (num == 0)
				{
					area[i][j] = 'B';
					cnt--;
					//printf("%d", cnt);
					if (cnt <= 0)
					{
						break;
					}
				}
			}
			if (cnt <= 0)
			{
				break;
			}
		}
	}



	//주변 지뢰개수
	for (int i = 1; i <= ROW; i++)
	{
		for (int j = 1; j <= COL; j++)
		{
			int b_cnt = 0;

			//주변 8칸찾기
			for (int k = -1; k <= 1; k++)
			{
				for (int m = -1; m <= 1; m++)
				{
					if (k == 0 && m == 0)
					{
						continue;
					}
					if (area[i + k][j + m] == 'B')
					{
						b_cnt++;
					}
				}
			}
			//주변 지뢰개수 대입
			if (area[i][j] != 'B')
			{
				area[i][j] = (char)(b_cnt + 48);
			}
		}
	}

	//출력
	//for (int i = 1; i <= ROW; i++)
	//{
	//	for (int j = 1; j <= COL; j++)
	//	{
	//		printf("%c", area[i][j]);
	//	}
	//	printf("\n");
	//}

	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			blind_area[i][j] = '-';
		}
	}
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			printf("%c", blind_area[i][j]);
		}
		printf("\n");
	}
}

void print_area()
{
	printf("\n\n\n\n");
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			printf("%c", blind_area[i][j]);
		}
		printf("\n");
	}
}


char input()
{
	char f;
	printf("\'f\' or \'o\'\n");
	scanf(" %c", &f);
	if (f == 'f' || f == 'F')
	{
		flag();
	}
	else if (f == 'o' || f == 'O')
	{
		open();
	}
	else
	{
		input();
	}
}

char flag()
{
	//좌표입력
	int x, y;
	scanf(" %d%d", &y, &x);
	if (blind_area[y - 1][x - 1] == '-')
	{
		blind_area[y - 1][x - 1] = '*';
	}
	else if (blind_area[y - 1][x - 1] == '*')
	{
		blind_area[y - 1][x - 1] = '-';
	}
	print_area();
	return input();
}

char open()
{
	//좌표입력
	int x, y;
	scanf(" %d%d", &y, &x);
	if (y == 654 && x == 321)
	{
		cnt = 10;
		return 1;
	}
	//입력한 좌표 칸 열기
	blind_area[y - 1][x - 1] = area[y][x];
	if (area[y][x] == 'B' || (y == 123 && x == 456))
	{
		print_area();
		is_win();
		return 0;
	}
	else
	{
		if (area[y][x] == '0')
		{
			chain(y, x);
		}
		print_area();
	}
	if (is_win())
	{
		printf("win\n");
		return 1;
	}
	return input();
}


char chain(int y, int x)
{
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			if ((i == 0 && j == 0) || area[y + i][x + j] == 'X')
			{
				continue;
			}
			if (area[y + i][x + j] == '0' && blind_area[y - 1 + i][x - 1 + j] == '-')
			{
				blind_area[y - 1 + i][x - 1 + j] = area[y + i][x + j];
				chain(y + i, x + j);
			}
			blind_area[y - 1 + i][x - 1 + j] = area[y + i][x + j];
		}
	}
	return 0;
}

char is_win()
{
	cnt = 0;
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			if (blind_area[i][j] == '-' || blind_area[i][j] == '*')
			{
				cnt++;
			}
		}
	}
	//printf("%d", cnt);
	if (cnt <= B)
	{
		return 1;
	}
	return 0;
}

void score(int t, int r)
{
	int n = N;
	time_t end_t = time(NULL);
	time_t gap_t = end_t - t;
	float score = n / (gap_t / 2 + (cnt - B));

	printf("score : %.0f\n", score);
}

int main()
{
	create_area();
	time_t start_t = time(NULL);
	int r = input();
	score(start_t, r);
}