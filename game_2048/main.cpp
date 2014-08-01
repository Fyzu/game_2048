#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <time.h>
#include <string.h>

#define SIZE 4
#define WAIT_ANY_KEY getchar()

/*!
* ---------------------- ��������� ----------------------------
*/
bool printEndScreen(int matrix[SIZE][SIZE], char name_player[9], int score, int max);
bool printScreen(int matrix[SIZE][SIZE], int, char name_player[9]);
bool shiftElementsUp(int matrix[SIZE][SIZE], int *score);
bool turnElementsRight(int matrix[SIZE][SIZE], int);
bool addRandomElement(int matrix[SIZE][SIZE]);
bool verificationEndGame(int matrix[SIZE][SIZE]);
char * gameNumber(int, char num�[5]);
int maxNumber(int matrix[SIZE][SIZE]);
int gen_random(int, int);

/*!
* ------------------- ���� �������� ������� -------------------
*/
int main() {

Start:

	bool processing=true;				// ��������� ������
	bool result;						//��������� ���������� ��������
	bool no_char;						//���� ��������� ��������
	char name_player[9];				//������ � ������ ������
	char ch[2];							//������ ��������� �����
	char c;								//������ ������� �������
	int max;							//������������ ��������
	int score=0;						//���� ������

	int matrix[SIZE][SIZE]={			//������� ����
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0}
	};

	system("cls");										//�������� ���� �������
	srand((unsigned int)time(NULL));					//������ �� �������

	//��������� ����� ������
	printf("Enter your name: ");
	scanf("%5s", &name_player);

	//���������� ������� ����
	addRandomElement(matrix);
	addRandomElement(matrix);
	addRandomElement(matrix);
	printScreen(matrix, score, name_player);

	//��������
	do {
		//����� ����������� ����� ������ �����
		result=false;
		no_char=false;

		//��������� ������� �������
		c=_getch();
		
		//����������� �������� �� �������� ������
		switch (c) {

			//��� ������ �����
			case 'W': case 'w':
				result=shiftElementsUp(matrix, &score);
				break;

			//��� ������ ����
			case 'S': case 's':
				turnElementsRight(matrix, 2);
				result=shiftElementsUp(matrix, &score);
				turnElementsRight(matrix, 2);
				break;

			//��� ������ �����
			case 'A': case 'a':
				turnElementsRight(matrix, 1);
				result=shiftElementsUp(matrix, &score);
				turnElementsRight(matrix, 3);
				break;

			//��� ������ ������
			case 'D': case 'd':
				turnElementsRight(matrix, 3);
				result=shiftElementsUp(matrix, &score);
				turnElementsRight(matrix, 1);
				break;

			//��� ������� ������
			case 'B': case 'b':
				result=false;
				processing=false;
				break;

			//���� �� ���������� ������� ��������
			default:
				no_char=true;
		}

		//�������� ����� ����
		max=maxNumber(matrix);												//��������� ������������� ��������
		if (max == 11)
			processing=false;												//��� ���������� ������������� ��������
		else if (result && !no_char) {										//��� ������� ���������� �������� � ���� �������� ������ ���������
			addRandomElement(matrix);										//��������� ����� ������� �������� ��� ������� �� ����
			printScreen(matrix, score, name_player);						//�������� ����� ����� ������� ��������
		} else if (!result) if (!verificationEndGame(matrix))				//�������� ����� ����
			processing=false;

	} while (processing);

	//����� ����
	printEndScreen(matrix, name_player, score, max);
	scanf("%1s", &ch);
	if (ch[0] == 'Y' || ch[0] == 'y') goto Start;

	//TODO
	WAIT_ANY_KEY;
	return 0;
}

/*!
* -------------------- ���. ������� ----------------------------
*/

/*! ���������� �� ���� ��������� ������� � ��������� ������ ������
* \param[out] matrix - ������� ����
* \return ���������� ����������
*/
bool addRandomElement(int matrix[SIZE][SIZE]) {

	bool success=false;					//���������� ���������� ��������
	bool processing=false;				//������� ����������
	int X, Y;							//���������� ������������ ��������

	//���������� � ������� ���� ������� ���� �� ����������
	if (!matrix) return false;

	//�������� ����������� �������� �������
	for (int i=0; i < SIZE; i++)
		for (int j=0; j < SIZE; j++)
			if (matrix[i][j] == 0) processing=true;

	//���������� ���������� ��������
	while (processing && !success) {					//���� �� ����� �������� �������
		//��������� ��������� ���������
		X=gen_random(0, 3);
		Y=gen_random(0, 3);
		//�������� ��� � ������ ����������� ����� ���� ��������� ����
		if (matrix[Y][X] == 0) {
			matrix[Y][X]=gen_random(1, 2);				//���������� ��������� ������
			success=true;
		}
	}

	return success;
}

/*! ��������� ���������� ����� � ���������
* \param[in] range_min - ����������� �����
* \param[in] range_max - ������������ �����
* \return ��������� ����� �� ���������
*/
int gen_random(int range_min, int range_max) {

	return range_min + rand() % (range_max - range_min + 1);

}

/*! ��������� ������� ����� �����
* \param[out] score - ���� ������
* \param[out] matrix - ������� �������� ����
* \return ���������� ��������
*/
bool shiftElementsUp(int matrix[SIZE][SIZE], int *score) {

	bool success=false;															//���������� ���������

	//���������� � ������� ���� ������� ���� �� ����������
	if (!matrix) return false;

	// -------- ����� ����� ����� ����������� -------- 
	//�������� ������ ����� � �����
	for (int i=0; i < SIZE; i++)														//������� �����
		for (int j=0; j < SIZE - 1; j++)												//�������� ����

			if (matrix[j][i] == 0)												//���� ������ ������ �������
				for (int k=j + 1; k < SIZE; k++) if (matrix[k][i] != 0)			//����� �� ������� �� ������ ������ 
				{	//����� ����� ��������� ����������� ������
					matrix[j][i]=matrix[k][i];
					matrix[k][i]=0;
					success=true;
					break;
				}
	// -------- ���������� -------- 
	//�������� ���������� ������ ���������
	for (int i=0; i < SIZE; i++)
		for (int j=0; j < SIZE - 1; j++)
			//������� ������� ��������
			if (matrix[j][i] == matrix[j + 1][i] && matrix[j][i] != NULL) {				//���� �� ������ ���� ��������� ����� �� ������� � ���� ���� ������� �� 0.
				*score+=matrix[j][i] * 10;												//���������� �����
				matrix[j][i]++;
				matrix[j + 1][i]=0;
				success=true;
			}

	// -------- ��������� �����, ����� ���������� -------- 
	//�������� ������ ����� � �����
	for (int i=0; i < SIZE; i++)														//������� �����
		for (int j=0; j < SIZE - 1; j++)												//�������� ����

			if (matrix[j][i] == 0)														//���� ������ ������ �������
				for (int k=j + 1; k < SIZE; k++) if (matrix[k][i] != 0)					//����� �� ������� �� ������ ������ 
				{	//����� ����� ��������� ����������� ������
					matrix[j][i]=matrix[k][i];
					matrix[k][i]=0;
					success=true;
					break;
				}

	return success;

}

/*! ������� ������� n ���
* \param[in] count - ���-�� ��������� �� 90 ��������.
* \param[out] matrix - ������� �������� ����
* \return ���������� ��������
*/
bool turnElementsRight(int matrix[SIZE][SIZE], int count) {

	bool success=false;											//���������� ����������
	int buffer;													//����� ��������

	//���������� � ������� ���� ������� ���� �� ����������
	if (!matrix) return false;

	// -------- ������� ������� �� COUNT ���, �� ������� ������� --------
	for (int k=0; k < count; k++)								//������� ���������
		//�������� �������� ������� �� ������� ������� �� 90 ��������
		for (int i=0; i<SIZE / 2 && matrix != NULL; i++)		//������� ���������...
			for (int j=i; j<SIZE - 1 - i; j++)					//...�������
			{
				buffer=matrix[i][j];
				matrix[i][j]=matrix[SIZE - j - 1][i];
				matrix[SIZE - j - 1][i]=matrix[SIZE - i - 1][SIZE - j - 1];
				matrix[SIZE - i - 1][SIZE - j - 1]=matrix[j][SIZE - i - 1];
				matrix[j][SIZE - i - 1]=buffer;
				success=true;
			}

	return success;

}

/*! ����� ������������� �������� �������� ����
* \param[in] matrix - ������� �������� ����
* \return ������������ �������� �������� ����
*/
int maxNumber(int matrix[SIZE][SIZE]) {

	//���������� � ������� ���� ������� ���� �� ����������.
	if (!matrix) return false;

	int maxNumber=0;

	for (int i=0; i < SIZE; i++)
		for (int j=0; j < SIZE; j++)
			if (maxNumber < matrix[i][j]) maxNumber=matrix[i][j];

	return maxNumber;
}

/*! ���������� ����� ����
* \param[in] matrix - ������� �������� ����
* \param[in] score - ���� ������
* \param[in] name_player - ��� ������
* \return ���������� ���������
*/
bool printScreen(int matrix[SIZE][SIZE], int score, char name_player[9]) {

	char num[16][5];													//���������� ��� ����������� ����� ������
	system("cls");														//�������� ���� �������

	//���������� � ������� ���� ������� ���� �� ����������
	if (!matrix) return false;

	// ---------- ��������� ������ ----------
	//����� ����������
	printf("_____________________________________\n");
	printf("|             GAME 2048             |\n");
	printf("|    Name: %5s   Score: %7d   |\n", name_player, score);
	printf("|___________________________________|\n");
	printf("|        |        |        |        |\n");
	//1-� ������ �������� ����
	printf("|  %4s  |  %4s  |  %4s  |  %4s  |\n",
		gameNumber(matrix[0][0], num[0]), gameNumber(matrix[0][1], num[1]),
		gameNumber(matrix[0][2], num[2]), gameNumber(matrix[0][3], num[3]));
	//2-� ������ �������� ����
	printf("|        |        |        |        |\n");
	printf("|________|________|________|________|\n");
	printf("|        |        |        |        |\n");
	printf("|  %4s  |  %4s  |  %4s  |  %4s  |\n",
		gameNumber(matrix[1][0], num[4]), gameNumber(matrix[1][1], num[5]),
		gameNumber(matrix[1][2], num[6]), gameNumber(matrix[1][3], num[7]));
	//3-� ������ �������� ����
	printf("|        |        |        |        |\n");
	printf("|________|________|________|________|\n");
	printf("|        |        |        |        |\n");
	printf("|  %4s  |  %4s  |  %4s  |  %4s  |\n",
		gameNumber(matrix[2][0], num[8]), gameNumber(matrix[2][1], num[9]),
		gameNumber(matrix[2][2], num[10]), gameNumber(matrix[2][3], num[11]));
	//4-� ������ �������� ����
	printf("|        |        |        |        |\n");
	printf("|________|________|________|________|\n");
	printf("|        |        |        |        |\n");
	printf("|  %4s  |  %4s  |  %4s  |  %4s  |\n",
		gameNumber(matrix[3][0], num[12]), gameNumber(matrix[3][1], num[13]),
		gameNumber(matrix[3][2], num[14]), gameNumber(matrix[3][3], num[15]));
	//������������� ����
	printf("|        |        |        |        |\n");
	printf("|________|________|________|________|\n");
	printf("#===================================#\n");
	printf("#    W,A,S,D - Move; B - Exit       #\n");
	printf("#       Powered by PDV, 2014        #\n");
	printf("#___________________________________#\n");

	return true;

}

/*! ������� ������ num ��� �������� ����
* \param[in] n - �����
* \param[out] num - ������ � �������
* \return ��������� �� num
*/
char * gameNumber(int n, char num[5]) {

	//������� � ������
	if (n == 0) {							//��� 0 �������
		num[0]=' ';
		num[1]='\0';
	} else {
		int buff=(int)pow(2.0, n);			//��������� 2 ������������ � ������� ����� n
		_itoa(buff, num, 10);				//������� � �	�����
	}

	return num;
}

/*! �������� ����� ����
* \param[out] matrix - ������� ����
* \return ���������� �������� ����� ����, ��� ��������� ����� - true, ��� ������� - false
*/
bool verificationEndGame(int matrix[SIZE][SIZE]) {

	bool success=false;															//���������� ��������

	//���������� � ������� ���� ������� ���� �� ����������
	if (!matrix) return false;

	//�������� ������
	for (int k=0; k < 4; k++) {														//�������� ������ �������

		//�������� �������� �����, �������� ��������
		for (int i=0; i < SIZE && !success; i++)									//������� �����
			for (int j=0; j < SIZE - 1 && !success; j++)							//�������� ����

				if (matrix[j][i] == 0)												//���� ������ ������ �������
					for (int k=j + 1; k < SIZE; k++) if (matrix[k][i] != 0)			//����� �� ������� �� ������ ������ 
					{	//����� ����� ��������� ����������� ������
						success=true;
						break;
					}

		//�������� �������� �����, �������� ����������
		for (int i=0; i < SIZE && k < 3 && !success; i++)
			for (int j=0; j < SIZE - 1 && !success; j++)
				//������� ������� ��������
				if (matrix[j][i] == matrix[j + 1][i] && matrix[j][i] != NULL) success=true;

		//������� �������
		turnElementsRight(matrix, 1);
	}

	return success;
}

/*! ���������� ����� ���������� ����
* \param[in] matrix - ������� �������� ����
* \param[in] score - ���� ������
* \param[in] name_player - ��� ������
* \param[in] max - ������������ ��������
* \return ���������� ���������
*/
bool printEndScreen(int matrix[SIZE][SIZE], char name_player[9], int score, int max) {

	system("cls");														//�������� ���� �������

	//���������� � ������� ���� ������� ���� �� ����������
	if (!matrix) return false;

	// ------------------- ��������� ������ ---------------
	printf("_____________________________________\n");
	printf("|             GAME 2048             |\n");
	printf("|    Name: %5s   Score: %7d   |\n", name_player, score);
	printf("|___________________________________|\n");
	printf("|                                   |\n");
	printf("|                                   |\n");
	printf("|                                   |\n");
	printf("|                                   |\n");
	printf("|                                   |\n");
	printf("|            %9s              |\n", (max == 11) ? "YOU  WIN!" : "GAME OVER");
	printf("|                                   |\n");
	printf("|                                   |\n");
	printf("|      You want play new game?      |\n");
	printf("|                                   |\n");
	printf("|            Press Y\\N.             |\n");
	printf("|                                   |\n");
	printf("|                                   |\n");
	printf("|                                   |\n");
	printf("|                                   |\n");
	printf("|___________________________________|\n");
	printf("#===================================#\n");
	printf("#                                   #\n");
	printf("#       Powered by PDV, 2014        #\n");
	printf("#___________________________________#\n");

	return true;

}