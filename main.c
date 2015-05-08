#include <stdio.h>
#include <stdlib.h>

#define _CRT_SECURE_NO_WARNINGS
#pragma warning (disable:4996)

#define BOARD_SIZE 10
#define MINE_COUNT 10
#define SIZEOF_ARRAY(arr) (sizeof(arr) / sizeof(0[arr]))

typedef struct
{
	int Zone[140];
	int elementCount;
}TsafeZone;


void askInput(int* num1, char* prompt);
int Belongs(int a, int b[], int len);

int is_Safe(int guess);
void addZone(int guess, int flag);
void extendEdge(int guess);
void extendEdge_UpDown(int guess);

void printBoard(int guess, int flag);

int checkPosition(int guess);
int checkSurrondMines(int guess);

void initialize();
int rand_range(int min_n, int max_n);
void randomMine();
void printMines();
int checkWin();



//golbal variable
TsafeZone safe;
TsafeZone edge;
TsafeZone flags;
int mineList[MINE_COUNT] = {0};  //10 mines in total, for testing they are fixed, later make it random
int board[BOARD_SIZE][BOARD_SIZE]; // 00-99


int main(){
	int guess = -1;
	int flag = -1;
	int option = 0;

	initialize();

	/**/
	int temp = checkSurrondMines(0);
	printf("temp is %d\n", temp);

	/*
	printBoard(guess, 0);


	while (1){

		if (checkWin()){
			printf("\nYou win! \n");
			printMines();
			break;
		}

		askInput(&option, "Type 1 for guessing\nType 2 for flaging\n: ");

		if (option == 1){
			askInput(&guess, "Guess: \n");

			if (Belongs(guess, safe.Zone, safe.elementCount) ||
				Belongs(guess, edge.Zone, edge.elementCount) ||
				Belongs(guess, flags.Zone, flags.elementCount)){
				printf("It s already safe...Input another guess.\n");
				continue;
			}

			if (Belongs(guess, mineList, SIZEOF_ARRAY(mineList))){
				system("clear");
				printf("\nYou lose! Hit the mine! :)\n\n");
				printBoard(guess, 1);
				break;
			}
			else{
				system("clear");
				if (is_Safe(guess)){
					printBoard(guess, 0);
				}

			}
		}
		else if (option == 2){
			askInput(&flag, "Flag: \n");

			if (Belongs(flag, safe.Zone, safe.elementCount) ||
				Belongs(flag, edge.Zone, edge.elementCount) ||
				Belongs(flag, flags.Zone, flags.elementCount)){
				printf("It s already safe...Input another guess.\n");
				continue;
			}
			else{
				if (flags.elementCount<MINE_COUNT){
					system("clear");
					flags.Zone[flags.elementCount] = flag;
					flags.elementCount++;
					printBoard(flag, 0);
				}
				else{
					printf("No more flags! \n");
				}

			}

		}

	}
	*/

	return 0;
}

void printBoard(int guess, int flag_loss){
	/*
	printf("\nEdges are: \n");
	for (int i = 0; i<edge.elementCount; i++){
		printf("%d\n", edge.Zone[i]);
	}
	*/

	int i, j;

	printf("    ");
	for (i = 0; i<10; i++){
		printf("%d  ", i);
	}
	printf("\n\n");


	for (i = 0; i<BOARD_SIZE; i++){
		printf("%d  ", i);
		for (j = 0; j<BOARD_SIZE; j++){

			if (flag_loss == 1)
			{
				if (Belongs(board[i][j], mineList, MINE_COUNT)){
					printf(" * ");
				}
				else if (Belongs(board[i][j], flags.Zone, flags.elementCount)){
					printf(" # ");
				}
				else if (Belongs(board[i][j], edge.Zone, edge.elementCount)){
					printf(" %d ", checkSurrondMines(board[i][j]));
				}
				else if (Belongs(board[i][j], safe.Zone, safe.elementCount)){
					printf(" + ");
				}
				else{
					printf(" ? ");
				}
			}
			else
			{
				if (Belongs(board[i][j], flags.Zone, flags.elementCount)){
					printf(" # ");
				}
				else if (Belongs(board[i][j], edge.Zone, edge.elementCount)){
					printf(" %d ", checkSurrondMines(board[i][j]));
				}
				else if (Belongs(board[i][j], safe.Zone, safe.elementCount)){
					printf(" + ");
				}
				else{
					printf(" ? ");
				}
			}


		}
		printf("\n");
	}

}

int Belongs(int a, int b[], int len){
	int i = 0;

	for (i = 0; i<len; i++){
		if (b[i] == a){
			return 1;
		}
	}

	return 0;
}

int is_Safe(int guess){

	if (guess>99 || guess<0){
		printf("Exceed the range!\n");
		return 0;
	}

	int count_safe = safe.elementCount;
	int count_edge = edge.elementCount;

	if ((checkSurrondMines(guess) != 0 && checkSurrondMines(guess) != 9) ){
		addZone(guess, 2);
	}

	else{
		addZone(guess, 1);
		extendEdge(guess);
	}

	printf("element_safe Count is %d \n", safe.elementCount);
	printf("element_edge Count is %d \n", edge.elementCount);
	return 1;

}

void extendEdge(int guess){

	int flag_edge = 0;
	int temp = guess;
	int position = checkPosition(guess);
	//extend rightward;

	while (checkSurrondMines(temp) == 0)
	{
		addZone(temp, 1);

		extendEdge_UpDown(temp);

		temp++;
		if (position == 5 || position == 7 || position == 9){ //means it cannot extend to the right
			flag_edge = 1;
			break;
		}
		position = checkPosition(temp);
	}

	if (flag_edge == 0)
	{
		addZone(temp, 2);
	}

	//extend leftward
	temp = guess;
	position = checkPosition(guess);
	flag_edge = 0;
	while (checkSurrondMines(temp) == 0)
	{
		addZone(temp, 1);

		extendEdge_UpDown(temp);

		temp--;
		if (position == 4 || position == 6 || position == 8){
			flag_edge = 1;
			break;
		}
		position = checkPosition(temp);
	}
	if (flag_edge == 0)
	{
		addZone(temp, 2);
	}


}

void extendEdge_UpDown(int guess){


	//extend upward
	int temp = guess;
	int position = checkPosition(guess);
	int flag_edge = 0;
	while (checkSurrondMines(temp) == 0)
	{
		addZone(temp, 1);
		temp -= 10;
		if (position == 2 || position == 6 || position == 7){
			flag_edge = 1;
			break;
		}
		position = checkPosition(temp);
	}
	if (flag_edge == 0)
	{
		addZone(temp, 2);
	}

	//extend downward
	temp = guess;
	position = checkPosition(guess);
	flag_edge = 0;
	while (checkSurrondMines(temp) == 0)
	{
		addZone(temp, 1);
		temp += 10;
		if (position == 3 || position == 8 || position == 9){
			flag_edge = 1;
			break;
		}
		position = checkPosition(temp);
	}
	if (flag_edge == 0)
	{
		addZone(temp, 2);
	}
	flag_edge = 0;

}

void addZone(int guess, int flag){
	switch (flag)
	{
		case 1:
			if (!(Belongs(guess, safe.Zone, safe.elementCount))){
				safe.Zone[safe.elementCount] = guess;
				safe.elementCount++;
			}
			break;
		case 2:
			if (!(Belongs(guess, edge.Zone, edge.elementCount))){
				edge.Zone[edge.elementCount] = guess;
				edge.elementCount++;
			}
			break;
		default:
			break;
	}

}

int checkWin(){
	/*=========================
	When user put all the flags on all the mine positions then win
	===========================*/

	int i = 0;
	int count = 0;

	for (i = 0; i<MINE_COUNT; i++){
		if (Belongs(mineList[i], flags.Zone, flags.elementCount)){
			count++;
		}
	}

	if (count == MINE_COUNT){
		return 1;
	}
	else{
		return 0;
	}
}

void initialize(){
	int i, j, k = 0;

	safe.elementCount = 0;
	edge.elementCount = 0;
	flags.elementCount = 0;

	for (i = 0; i<100; i++){
		safe.Zone[i] = -1;
	}

	for (i = 0; i<100; i++){
		edge.Zone[i] = -1;
	}

	for (i = 0; i<MINE_COUNT; i++){ //ten flags that user can input
		flags.Zone[i] = -1;
	}


	for (i = 0; i<BOARD_SIZE; i++){
		for (j = 0; j<BOARD_SIZE; j++){
			board[i][j] = k;
			k++;
		}
	}

	randomMine();
	printMines();
}

int checkSurrondMines(int guess){

	int Count = 0;
	int temp = checkPosition(guess);
	int col = guess % 10;
	int row = guess / (int)10;

	if (Belongs(board[row][col], mineList, MINE_COUNT))
	{
		return 9;
	}

	/*There are 9 different position for the guess number in the board*/

	if (temp == 1){
		// Check for mine down
		if (Belongs(board[row + 1][col], mineList, MINE_COUNT))
			Count++;
		// Check for mine to the up.
		if (Belongs(board[row - 1][col], mineList, MINE_COUNT))
			Count++;
		// Check for mine to the left.
		if (Belongs(board[row][col - 1], mineList, MINE_COUNT))
			Count++;
		// Check for mine to the right
		if (Belongs(board[row][col + 1], mineList, MINE_COUNT))
			Count++;
		// Check for mine diagonal-downright
		if (Belongs(board[row + 1][col + 1], mineList, MINE_COUNT))
			Count++;
		// Check for mine diagonal-downleft
		if (Belongs(board[row + 1][col - 1], mineList, MINE_COUNT))
			Count++;
		// Check for mine diagonal-upright
		if (Belongs(board[row - 1][col + 1], mineList, MINE_COUNT))
			Count++;
		// Check for mine diagonal-upleft
		if (Belongs(board[row - 1][col - 1], mineList, MINE_COUNT))
			Count++;
	}
	else if (temp == 2){
		//Check for mine to the down
		if (Belongs(board[row + 1][col], mineList, MINE_COUNT))
			Count++;
		// Check for mine to the left.
		if (Belongs(board[row][col - 1], mineList, MINE_COUNT))
			Count++;
		// Check for mine to the right
		if (Belongs(board[row][col + 1], mineList, MINE_COUNT))
			Count++;
		// Check for mine diagonal-downright
		if (Belongs(board[row + 1][col + 1], mineList, MINE_COUNT))
			Count++;
		// Check for mine diagonal-upleft
		if (Belongs(board[row + 1][col - 1], mineList, MINE_COUNT))
			Count++;
	}
	else if (temp == 3){
		// Check for mine up
		if (Belongs(board[row - 1][col], mineList, MINE_COUNT))
			Count++;
		// Check for mine to the left.
		if (Belongs(board[row][col - 1], mineList, MINE_COUNT))
			Count++;
		// Check for mine to the right
		if (Belongs(board[row][col + 1], mineList, MINE_COUNT))
			Count++;
		// Check for mine diagonal-upright
		if (Belongs(board[row - 1][col + 1], mineList, MINE_COUNT))
			Count++;
		// Check for mine diagonal-upright
		if (Belongs(board[row - 1][col - 1], mineList, MINE_COUNT))
			Count++;
	}
	else if (temp == 4){
		// Check for mine up
		if (Belongs(board[row + 1][col], mineList, MINE_COUNT))
			Count++;
		// Check for mine to the down.
		if (Belongs(board[row - 1][col], mineList, MINE_COUNT))
			Count++;
		// Check for mine to the right
		if (Belongs(board[row][col + 1], mineList, MINE_COUNT))
			Count++;
		// Check for mine diagonal-downright
		if (Belongs(board[row + 1][col + 1], mineList, MINE_COUNT))
			Count++;
		// Check for mine diagonal-upright
		if (Belongs(board[row - 1][col + 1], mineList, MINE_COUNT))
			Count++;
	}
	else if (temp == 5){
		// Check for mine up
		if (Belongs(board[row + 1][col], mineList, MINE_COUNT))
			Count++;
		// Check for mine to the down.
		if (Belongs(board[row - 1][col], mineList, MINE_COUNT))
			Count++;
		// Check for mine to the left.
		if (Belongs(board[row][col - 1], mineList, MINE_COUNT))
			Count++;
		// Check for mine diagonal-downleft
		if (Belongs(board[row + 1][col - 1], mineList, MINE_COUNT))
			Count++;
		// Check for mine diagonal-upleft
		if (Belongs(board[row - 1][col - 1], mineList, MINE_COUNT))
			Count++;
	}
	else if (temp == 6){
		// Check for mine to the down.
		if (Belongs(board[row + 1][col], mineList, MINE_COUNT))
			Count++;
		// Check for mine to the right
		if (Belongs(board[row][col + 1], mineList, MINE_COUNT))
			Count++;
		// Check for mine diagonal-downright
		if (Belongs(board[row + 1][col + 1], mineList, MINE_COUNT))
			Count++;
	}
	else if (temp == 7){
		// Check for mine down
		if (Belongs(board[row + 1][col], mineList, MINE_COUNT))
			Count++;
		// Check for mine to the left.
		if (Belongs(board[row][col - 1], mineList, MINE_COUNT))
			Count++;
		// Check for mine diagonal-downleft
		if (Belongs(board[row + 1][col - 1], mineList, MINE_COUNT))
			Count++;
	}
	else if (temp == 8){
		// Check for mine to the up.
		if (Belongs(board[row - 1][col], mineList, MINE_COUNT))
			Count++;
		// Check for mine to the right
		if (Belongs(board[row][col + 1], mineList, MINE_COUNT))
			Count++;
		// Check for mine diagonal-upright
		if (Belongs(board[row - 1][col + 1], mineList, MINE_COUNT))
			Count++;
	}
	else if (temp == 9){
		// Check for mine to the up.
		if (Belongs(board[row - 1][col], mineList, MINE_COUNT))
			Count++;
		// Check for mine to the left.
		if (Belongs(board[row][col - 1], mineList, MINE_COUNT))
			Count++;
		// Check for mine diagonal-upleft
		if (Belongs(board[row - 1][col - 1], mineList, MINE_COUNT))
			Count++;
	}

	return Count;
}

int rand_range(int min_n, int max_n){
	//This will not give a uniform distribution (except for powers-of-two). But who cares
	return rand() % (max_n - min_n + 1) + min_n;
}

void randomMine(){
	int i = 0;
	int temp = 0;
	for (i = 0; i<MINE_COUNT; i++){
		while (1){
			temp = rand_range(0, 99);
			if (!Belongs(temp, mineList, MINE_COUNT)){
				break;
			}
		}
		mineList[i] = temp;
	}

}

int checkPosition(int guess){
	int col = guess % 10;
	int row = guess / (int)10;

	/*
	printf("int is %d\n", board[row][col]);
	printf("col: %d \nrow: %d \n", col, row);
	*/

	//check if the guess number with in the inner part (not the first or last row and col)
	if ((row>0 && row<BOARD_SIZE - 1) && (col>0 && col<BOARD_SIZE - 1)){
		return 1;
	}
	//check if the first row
	else if (row == 0 && (col>0 && col<BOARD_SIZE - 1)){
		return 2;
	}
	//check if the last row
	else if (row == BOARD_SIZE - 1 && (col>0 && col<BOARD_SIZE - 1)){
		return 3;
	}
	//check if the first col
	else if ((row>0 && row<BOARD_SIZE - 1) && (col == 0)){
		return 4;
	}
	//check if the last col
	else if ((row>0 && row<BOARD_SIZE - 1) && (col == BOARD_SIZE - 1)){
		return 5;
	}
	//check if (0,0)
	else if (row == 0 && col == 0){
		return 6;
	}
	//check if (0,9)
	else if (row == 0 && col == BOARD_SIZE - 1){
		return 7;
	}
	//check if (9,0)
	else if (row == BOARD_SIZE - 1 && col == 0){
		return 8;
	}
	//check if (9,9)
	else if (row == BOARD_SIZE - 1 && col == BOARD_SIZE - 1){
		return 9;
	}

	return 0;
}

void printMines(){
	int i=0;
	printf("\nMines position are: \n");
	for (i = 0; i<MINE_COUNT; i++){
		printf("%d\n", mineList[i]);
	}
}

void askInput(int* num1, char* prompt){
	int guess;

	printf("%s", prompt);
	scanf("%d", &guess);

	*num1 = guess;

}
