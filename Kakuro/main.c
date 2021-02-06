#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <windows.h>  

#define LEN 7
const int SUM[] = { 0,1,3,6,10,15,21,28,36,45 };

typedef struct Opcell
{
	int x, y;
	int Options[10];
	struct Opcell* Dnext;
	struct Opcell* Dprev;
	struct Opcell* Rnext;
	struct Opcell* Rprev;
	struct Kcell* kDown;
	struct Kcell* kRight;
}Opcell;
typedef struct OpcellList
{
	struct Opcell* opHead;
	struct Opcell* opTail;
}OpcellList;

typedef struct KcellList
{
	struct Kcell* kHead;
	struct Kcell* kTail;
}KcellList;
typedef struct Kcell
{
	int x, y;
	int D, R;
	int Dcells, Rcells;
	struct Kcell* Knext;
	OpcellList DList, RList;
}Kcell;

typedef struct Cell
{
	char what;
	struct Opcell* oCell;
	struct Kcell* kCell;
}Cell;
typedef struct pos
{
	int x, y;
}pos;

pos** print();
void gotoxy(int x, int y);
char** initBoard(pos** p);
COORD GetConsoleCursorPosition(HANDLE hConsoleOutput);
Cell** Organize2(char** Board);
Opcell* createOpCell();
Kcell* createKCell(int d, int r);
unsigned long factorial(unsigned int n);
void printC(Cell Mat[LEN][LEN]);
void print1(char** board);
KcellList ConnectMat(Cell** Mat);
void connectD(Cell** Mat, int i, int j);
void connectR(Cell** Mat, int i, int j);
void CleanSize(KcellList* Klist);
void deleteOp(Opcell* o, int from, int to);
void print2(Cell** board);
void solve(Kcell* k);
char isWon(KcellList klist);

void main()
{
	//int numH = 0, numV = 0;
	system("cls");
	Cell** Mat;
	KcellList Klist;
	pos** p = print();
	char ** getBoard= initBoard(p);
	print1(getBoard);
	Mat = Organize2(getBoard);
	Klist = ConnectMat(Mat);
	CleanSize(&Klist);
	print2(Mat);
	Kcell* k;
	Opcell* o;
	int i = 0;
	/*while (!isWon(Klist)) {
		printf("/////////////////////////////////\n");
		k = Klist.kHead;
		while (k != NULL)
		{
			printf("%d %d\n", k->D, k->R);
			o = k->DList.opHead;
			if (k->Dcells == 2 && !k->D % 2 && o->Options[k->D / 2] != 0)
			{
				while (o != NULL)
				{
					o->Options[k->D / 2] = 0;
					o = o->Dnext;
				}
			}
			o = k->RList.opHead;
			if (k->Rcells == 2 && !k->R % 2 && o->Options[k->R / 2] != 0)
			{
				while (o != NULL)
				{
					o->Options[k->R / 2] = 0;
					o = o->Rnext;
				}
			}
			o = k->DList.opHead;
			while (o != NULL)
			{
				printf("1D: ");
				for (i = 0; i < 10; i++)
					printf("%d,", o->Options[i]);
				printf("\n");
				o = o->Dnext;
			}
			o = k->RList.opHead;
			while (o != NULL)
			{
				printf("1R: ");
				for (i = 0; i < 10; i++)
					printf("%d,", o->Options[i]);
				printf("\n");
				o = o->Rnext;
			}
			///////////////////////
			solve(k);
			//////////////////////
			o = k->DList.opHead;
			while (o != NULL)
			{
				printf("2D: ");
				for (i = 0; i < 10; i++)
					printf("%d,", o->Options[i]);
				printf("\n");
				o = o->Dnext;
			}
			o = k->RList.opHead;
			while (o != NULL)
			{
				printf("2R: ");
				for (i = 0; i < 10; i++)
					printf("%d,", o->Options[i]);
				printf("\n");
				o = o->Rnext;
			}
			k = k->Knext;
		}
		printf("\n");
	}*/
}

void solve(Kcell* k)
{
	int i = 1;
	Opcell* o,*t;
	int count = 0;
	o = k->DList.opHead;
	while (o != NULL)
	{
		if (o->Options[0] == 0)
		{
			i = 1;
			while(i<10)
			{
				if (o->Options[i] != 0) {
					if (o->Options[0] == 0) {
						o->Options[0] = i;
						printf("if %d i:%d\n", o->Options[0],i);
					}
					else
					{
						printf("else %d i:%d\n", o->Options[0],i);
						o->Options[0] = 0;
						i = 10;
					}
				}
				i++;
			}
			printf("out\n");
			if (o->Options[0] != 0) {
				t = k->DList.opHead;
				while (t != NULL){
					t->Options[o->Options[0]] = 0;
					t = t->Dnext;
				}
				k->D -= o->Options[0];
				k->Dcells--;
				printf("Dout %d %d\n",k->D,k->Dcells);
				t = o->kRight->RList.opHead;
				while (t != NULL) {
					t->Options[o->Options[0]] = 0;
					t = t->Rnext;
				}
				o->kRight->R -= o->Options[0];
				k->Rcells--;
				printf("Rout %d %d\n", o->kRight->D, o->kRight->Dcells);
			}
		}
		o = o->Dnext;
	}
	o = k->RList.opHead;
	while (o != NULL)
	{
		if (o->Options[0] == 0)
		{
			i = 1;
			while (i < 10)
			{
				if (o->Options[i] != 0) {
					if (o->Options[0] == 0)
						o->Options[0] = i;
					else
					{
						o->Options[0] = 0;
						i = 10;
					}
				}
				i++;
			}
			if (o->Options[0] != 0) {
				t = k->RList.opHead;
				while (t != NULL) {
					t->Options[o->Options[0]] = 0;
					t = t->Rnext;
				}
				k->R -= o->Options[0];
				k->Rcells--;
				t = o->kDown->DList.opHead;
				while (t != NULL) {
					t->Options[o->Options[0]] = 0;
					t = t->Dnext;
				}
				o->kDown->D -= o->Options[0];
				k->Dcells--;
			}
		}
		o = o->Rnext;
	}
}
void solveRec(Opcell* o,int sum)
{
	Opcell* temp;
	if(sum == 0)
		
	for (int i = 1; i < 10; i++)
	{
		if (o->Options[i] != 0)
		{
			o->Options[0] = i;
			temp = o->Dnext;
			while (temp != NULL)
				temp->Options[i] = 0;
			solveRec(o->Dnext, sum - i);
		}
	}
}
char** initBoard(pos** p)
{
	char c;
	FILE* fp;
	fp = fopen("kakuros.txt", "r");
	char** Board;
	Board = (char**)calloc(LEN * 2, sizeof(char*));
	for (int i = 0; i < LEN * 2; i++)
	{
		Board[i] = (char*)calloc(LEN * 2, sizeof(char));
		for (int j = 0; j < LEN * 2; j++)
		{
			if (i % 2 != j % 2) {
				//gotoxy(p[i][j].x, p[i][j].y);
				//scanf("%d", &(Board[i][j]));
				//fprintf(fp, "%d", Board[i][j]);
				fscanf(fp, "%d", &(Board[i][j]));
				fseek(fp, sizeof(char), SEEK_CUR);
			}
			else
				Board[i][j] = 0;
		}
	}
	fclose(fp);
	return Board;
}

Cell** Organize2(char** Board)
{
	Cell** Mat;
	Mat = (Cell**)calloc(LEN, sizeof(Cell*));

	for (int i = 0; i < LEN; i++)
	{
		Mat[i] = (Cell*)calloc(LEN, sizeof(Cell));
		for (int j = 0; j < LEN; j++)
		{
			if (!(Board[i * 2][j * 2 + 1]) && !(Board[i * 2 + 1][j * 2]))
			{
				Mat[i][j].what = 0;
				Mat[i][j].oCell = createOpCell(i,j);
				printf("%d, ", Mat[i][j].oCell->Options[0]);

			}
			else
			{
				if ((Board[i * 2][j * 2 + 1]) >= 0 || (Board[i * 2 + 1][j * 2]) >= 0) 
				{
					Mat[i][j].what = 1;
					Mat[i][j].kCell = createKCell(Board[i * 2 + 1][j * 2], Board[i * 2][j * 2 + 1],i,j);
					printf("D:%dR:%d, ", Mat[i][j].kCell->D,Mat[i][j].kCell->R);
				}
				else
					Mat[i][j].what = -1;
			}
			
		}
		printf("\n");
	}
	return Mat;
	//printC(Mat);
}
void CleanSize(KcellList* Klist)
{
	Kcell* k;
	Opcell* o;
	int maxN = 9,minN = 1;
	k = Klist->kHead;
	while (k != NULL)
	{
		//printf("%d  %d\n", k->D, SUM[k->Dcells - 1]);
		maxN = (2 * k->D - (k->Dcells * (k->Dcells - 1)))/2;
		if (maxN > 9)
			minN = maxN - 8;
		maxN = k->D - SUM[k->Dcells-1];
		o = k->DList.opHead;
		//printf("D\n");
		while (o != NULL)
		{
			//printf("D %d  %d  %d\ni: ", o->x, o->y, maxN);
			deleteOp(o, minN, maxN);
			if(k->D == 4 && k->Dcells == 2)
				o->Options[2] = 0;
			if (k->D == 7 && k->Dcells == 3)
				o->Options[2] = 0;
			o = o->Dnext;
		}
		maxN = (2 * k->R - (k->Rcells * (k->Rcells - 1))) / 2;
		if (maxN > 9)
			minN = maxN - 8;
		o = k->RList.opHead;
		//printf("\nR\n");
		while (o != NULL)
		{
			//printf("R %d  %d  %d\n", o->x, o->y, maxN);
			deleteOp(o, minN, maxN);
			if (k->R == 4 && k->Rcells == 2)
				o->Options[2] = 0;
			if (k->R == 7 && k->Rcells == 3)
				o->Options[2] = 0;
			o = o->Rnext;
		}
		k = k->Knext;
	}
}/*
char isValidD(Opcell* o,int n)
{
	int j = 1;
	if (n == 0)
		return 1;
	for (int i = 1; i < 10; i++)
	{
		if (o->Options[i] != 0)
			return isValidD(o->Dnext, n - o->Options[i]);
	}
	return 0;
}*/
char isWon(KcellList klist)
{
	int sum;
	Kcell* k = klist.kHead;
	Opcell* o;
	while (k != NULL)
	{
		sum = 0;
		o = k->DList.opHead;
		while (o != NULL)
		{
			sum += o->Options[0];
			printf("D %d %d  %d\n",k->D, o->Options[0], sum);
			o = o->Dnext;
		}
		if (sum != k->D && k->Dcells != 0)
			return 0;
		sum = 0;
		o = k->RList.opHead;
		while (o != NULL)
		{
			sum += o->Options[0];
			printf("R %d %d  %d\n", k->R, o->Options[0], sum);
			o = o->Rnext;
		}
		if (sum != k->R && k->Rcells != 0)
			return 0;
		k = k->Knext;
	}
	return 1;
}
void deleteOp(Opcell* o,int from ,int to)
{
	int i = to+1;
	while (i != from)
	{
		o->Options[i] = 0;
		i++; if (i > 9) i = 1;
	}
}
void AddOp(Opcell* o, int from, int to)
{
	for (int i = from; i < to + 1; i++) {
		o->Options[i] = i;
	}
}
KcellList ConnectMat(Cell** Mat)
{
	int i, j;
	Kcell* temp = NULL;
	KcellList klist;
	for (i = 0; i < LEN; i++)
	{
		for (j = 0; j < LEN; j++)
		{
			if (Mat[i][j].what == 1)
			{
				if (temp == NULL)
				{
					temp = Mat[i][j].kCell;
					klist.kHead = temp;
				}
				else
				{
					temp->Knext = Mat[i][j].kCell;
					temp = temp->Knext;
				}
				if (Mat[i][j].kCell->D > 0)
					connectD(Mat, i, j);
				else {
					Mat[i][j].kCell->Dcells = 0;
					Mat[i][j].kCell->DList.opHead = NULL; Mat[i][j].kCell->DList.opTail = NULL;
				}

				if (Mat[i][j].kCell->R > 0)
					connectR(Mat, i, j);
				else {
				Mat[i][j].kCell->Rcells = 0;
				Mat[i][j].kCell->RList.opHead = NULL; Mat[i][j].kCell->RList.opTail = NULL;
				}

			}
		}
	}
	klist.kTail = temp;
	temp->Knext = NULL;
	return klist;
}
void connectD(Cell** Mat,int i ,int j)
{
	int k;
	k = i + 1;
	Mat[i][j].kCell->DList.opHead = Mat[k][j].oCell;
	Mat[k][j].oCell->kDown = Mat[i][j].kCell;
	Mat[k][j].oCell->Dnext = Mat[k + 1][j].oCell;
	Mat[k + 1][j].oCell->Dprev = Mat[k][j].oCell;
	k++;
	while (k + 1 < LEN && Mat[k + 1][j].what == 0)
	{
		Mat[k][j].oCell->kDown = Mat[i][j].kCell;
		Mat[k][j].oCell->Dnext = Mat[k + 1][j].oCell;
		Mat[k + 1][j].oCell->Dprev = Mat[k][j].oCell;
		k++;
	}
	Mat[k][j].oCell->kDown = Mat[i][j].kCell;
	Mat[k][j].oCell->Dnext = NULL;
	Mat[i][j].kCell->Dcells = k - i;
	Mat[i][j].kCell->DList.opTail = Mat[k][j].oCell;
	
}

void connectR(Cell** Mat, int i, int j)
{
	int k;
	k = j + 1;
	Mat[i][j].kCell->RList.opHead = Mat[i][k].oCell;
	Mat[i][k].oCell->kRight = Mat[i][j].kCell;
	Mat[i][k].oCell->Rnext = Mat[i][k+1].oCell;
	Mat[i][k+1].oCell->Rprev = Mat[i][k].oCell;
	k++;
	while (k + 1 < LEN && Mat[i][k+1].what == 0)
	{
		Mat[i][k].oCell->kRight = Mat[i][j].kCell;
		Mat[i][k].oCell->Rnext = Mat[i][k + 1].oCell;
		Mat[i][k + 1].oCell->Rprev = Mat[i][k].oCell;
		k++;
	}
	Mat[i][k].oCell->kRight = Mat[i][j].kCell;
	Mat[i][k].oCell->Rnext = NULL;
	Mat[i][j].kCell->Rcells = k - j;
	Mat[i][j].kCell->RList.opTail = Mat[i][k].oCell;
}

void printC(Cell Mat [LEN][LEN])
{
	for (int i = 0; i <= LEN; i++)
	{
		for (int j = 2; j < LEN; j++)
			printf("---");
		printf("\n");
		if (i != LEN)
			for (int j = 0; j <= LEN; j++)
			{
				printf("|");
				if (j != LEN)
				{
					printf(" %d ", Mat[i][j].what);
				}
			}
		printf("\n");
	}

}

Opcell* createOpCell(int i,int j)
{
	Opcell* result;
	result = (Opcell*)malloc(sizeof(Opcell));
	for (int k = 0; k < 10; k++)
		result->Options[k] = k;
	result->x = i; result->y = j;
	return result;
}
Kcell* createKCell(int d, int r,int i,int j)
{
	Kcell* result;
	result = (Kcell*)malloc(sizeof(Kcell));
	result->D = d;result->R = r;
	result->x = i; result->y = j;
	return result;
}

pos** print()
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c;
	pos** p;
	p = (pos**)calloc(LEN * 2, sizeof(pos*));
	for (int i = 0; i <= LEN * 2; i++)
	{
		p[i] = (pos*)calloc(LEN * 2, sizeof(pos));
		if (!(i % 2))
		{
			for (int j = 4; j < LEN * 2; j++)
				printf("---");
			printf("\n");
		}
		if (i != LEN * 2)
			for (int j = 0; j <= LEN * 2; j++)
			{
				if (!(j % 2))
					printf("|");
				if (j != LEN * 2)
				{
					c = GetConsoleCursorPosition(hStdout);
					p[i][j].x = c.X;
					p[i][j].y = c.Y;
					if (j % 2 != i % 2)
					{
						printf("  ");
					}
					else
						printf("\\");
				}
			}
		printf("\n");
	}
	return p;
}
void print1(char** board)
{
	for (int i = 0; i <= LEN * 2; i++)
	{
		if (!(i % 2))
		{
			for (int j = 2; j < LEN * 2; j++)
				printf("---");
			printf("\n");
		}
		if (i != LEN * 2)
			for (int j = 0; j <= LEN * 2; j++)
			{
				if (!(j % 2))
					printf("|");
				if (j != LEN * 2)
				{
					

					if (j % 2 != i % 2)
					{
						if (board[i][j] == -1)
							printf("XX");
						else if (board[i][j] == 0)
							printf("  ");
						else
							printf("%2d", board[i][j]);
					}
					else
					{
						if ((!(i % 2) && !board[i + 1][j] && !board[i][j + 1] )|| ((i % 2) && !board[i - 1][j] && !board[i][j - 1])) {
								printf("  ");
						}
						else
						printf(" \\");
					}
				}
			}
		printf("\n");
	}
}
void print2(Cell** board)
{

	for (int i = 0; i <= LEN * 2; i++)
	{
		if (!(i % 2))
		{
			for (int j = 2; j < LEN * 2; j++)
				printf("---");
			printf("\n");
		}
		if (i != LEN * 2)
			for (int j = 0; j <= LEN * 2; j++)
			{
				if (!(j % 2))
					printf("|");
				if (j != LEN * 2)
				{
					if (j % 2 != i % 2)
					{
						if (board[i/2][j/2].what == -1)
						{
							printf("XX");
						}
						else if (board[i/2][j/2].what == 0)
						{
							if (board[i/2][j/2].oCell->Options[0] == 0)
								printf("  ");
							else
								printf(" %d", board[i/2][j/2].oCell->Options[0]);
						}

						else
							printf("%2d", board[i/2][j/2]);
					}
					else
					{
						if (board[i / 2][j / 2].what == 0) {
							printf("  ");
						}
						else
							printf(" \\");
					}
				}
			}
		printf("\n");
	}
}
/*
void print2(Cell** board)
{

	for (int i = 0; i <= LEN * 2; i++)
	{
		if (!(i % 2))
		{
			for (int j = 2; j < LEN * 2; j++)
				printf("---");
			printf("\n");
		}
		else if (i != LEN * 2)
			for (int j = 0; j <= LEN * 2; j++)
			{
				if (!(j % 2))
					printf("|");
				else if (j != LEN * 2)
				{
					
					if (board[i][j].what == -1)
					{
						printf("XX");
					}
						else if (board[i][j].what == 0)
						{
							if(board[i][j].oCell->Options[0] == 0)
								printf("  ");
							else
								printf(" %d", board[i][j].oCell->Options[0]);
						}

						else
							printf("%2d", board[i][j]);
					else
						printf(" \\");
				}
			}
		printf("\n");
	}
}
*/
unsigned long factorial(unsigned int n)
{
	unsigned long fact = 1;
	unsigned int i;

	for (i = 1; i <= n; ++i)
		fact *= i;

	return fact;
}
COORD GetConsoleCursorPosition(HANDLE hConsoleOutput)
{
	CONSOLE_SCREEN_BUFFER_INFO cbsi;
	if (GetConsoleScreenBufferInfo(hConsoleOutput, &cbsi))
	{
		return cbsi.dwCursorPosition;
	}
	else
	{
		// The function failed. Call GetLastError() for details.
		COORD invalid = { 0, 0 };
		return invalid;
	}
}
void gotoxy(int x, int y)
{
	COORD coordinate;
	coordinate.X = x;
	coordinate.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinate);
}