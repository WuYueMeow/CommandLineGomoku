#include<cstdio>
#include<vector>
#include<cstdlib>
#include<conio.h>
#include<iostream>
using namespace std;

#define BOARD_SIZE 41

enum Piece {
	EMPTY = 0,
	BLACK = 1,
	WHITE = 2
};

enum GameState {
	MENU,
	PLAYING,
	EXIT
};

class Gomoku {
private:
	vector< vector<Piece> > board;
	Piece currentPlayer;
	GameState state;
	bool gameOver;

public:
	Gomoku() :board(BOARD_SIZE, vector<Piece>(BOARD_SIZE, EMPTY)),
		currentPlayer(BLACK), state(MENU), gameOver(false) {
	}

	void clearScreen() {
		system("cls");
	}

	void showMenu() {
		clearScreen();
		for (int i = 1; i <= 60; i++) cout << "*";
		cout << endl;
		for (int i = 1; i <= 20; i++) cout << " ";
		cout << "雾月的五子棋小游戏";
		for (int i = 1; i <= 20; i++) cout << " ";
		cout << endl;
		for (int i = 1; i <= 60; i++) cout << "*";
		cout << endl;
		cout << "1.开始游戏\n" << "2.退出游戏\n";
	}

	void initBoard() {
		for (int i = 0; i < BOARD_SIZE; i++) {
			for (int j = 0; j < BOARD_SIZE; j++) {
				board[i][j] = EMPTY;
			}
		}currentPlayer = BLACK;
		gameOver = false;
	}

	void displayBoard() {
		clearScreen();
		cout << "   ";
		for (int i = 0; i < BOARD_SIZE; i++) {
			cout << i << " ";
		}cout << "\n";
		for (int i = 0; i < BOARD_SIZE; i++) {
			cout << i << (i < 10 ? " " : "") << " ";
			for (int j = 0; j < BOARD_SIZE; j++) {
				switch (board[i][j]) {
				case EMPTY:
					if (i == 0 && j == 0) cout << "+ ";
					else if (i == 0 && j == BOARD_SIZE - 1) cout << "+ ";
					else if (i == BOARD_SIZE - 1 && j == 0) cout << "+ ";
					else if (i == BOARD_SIZE - 1 && j == BOARD_SIZE - 1) cout << "+ ";
					else if (i == 0) cout << "- ";
					else if (i == BOARD_SIZE - 1) cout << "- ";
					else if (j == 0) cout << "| ";
					else if (j == BOARD_SIZE - 1) cout << "| ";
					else cout << "+ ";
					break;
				case BLACK:
					cout << "B ";
					break;
				case WHITE:
					cout << "W ";
					break;
				}
			}cout << "\n";
		}
		cout << "\n当前玩家:" << (currentPlayer == BLACK ? "黑棋(B)" : "白棋(W)") << "\n";
		cout << "请输入落子位置(行 列),例如:2 2 \n";
		cout << "输入-1 -1返回菜单\n";
		
	}

	bool checkWin(int row, int col) {
		Piece player = board[row][col];
		int directions[4][2] = { {1,0},{0,1},{1,1},{1,-1} };
		for (auto& dir : directions) {
			int count = 1;
			for (int i = 1; i <= 4; i++) {
				int r = row + dir[0] * i;
				int c = col + dir[1] * i;
				if (r >= 0 && r < BOARD_SIZE && c >= 0 && c < BOARD_SIZE && board[r][c] == player) {
					count++;
				}
				else break;
			}
			for (int i = 1; i <= 4; i++) {
				int r = row - dir[0] * i;
				int c = col - dir[1] * i;
				if (r >= 0 && r < BOARD_SIZE && c >= 0 && c < BOARD_SIZE && board[r][c] == player) {
					count++;
				}
				else break;
			}if (count >= 5) return true;
		}
		return false;
	}

	void processInput() {
		int row, col;
		cout << "请输入落子位置";
		cin >> row >> col;
		if (row == -1 && col == -1) {
			state = MENU;
			return;
		}
		if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) {
			cout << "落子超出棋盘范围！按任意键继续...";
			_getch();
			return;
		}
		if (board[row][col] != EMPTY) {
			cout << "该位置已有棋子！按任意键继续...";
			_getch();
			return;
		}
		board[row][col] = currentPlayer;
		if (checkWin(row, col)) {
			displayBoard();
			cout << "\n恭喜！" << (currentPlayer == BLACK ? "黑棋" : "白棋") << "获胜！\n";
			cout << "按任意键返回菜单...";
			_getch();
			state = MENU;
			return;
		}
		currentPlayer = (currentPlayer == BLACK) ? WHITE : BLACK;
	}
	void run() {
		while (state != EXIT) {
			switch (state) {
			case MENU:
				showMenu();
				int choice;
				cin >> choice;
				if (choice == 1) {
					initBoard();
					state = PLAYING;
				}
				else if (choice == 2) {
					state = EXIT;
				}break;
			case PLAYING:
				displayBoard();
				processInput();
				break;
			}
		}
		cout << "感谢使用！再见！\n";
	}
};

int main() {
	Gomoku game;
	game.run();
	return 0;
}