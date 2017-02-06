#include "Grid.h"

Grid::Grid(): rows(0), columns(0){
	board = NULL;
}

Grid::Grid(int r, int c): rows(r), columns(c){
	board = new char*[rows];
	for(int i = 0; i < rows; i++)
    		board[i] = new char[columns]; 
}

Grid::Grid(const Grid& g){
	delete board;
	rows = g.rows;
	columns = g.columns;
}

Grid::~Grid(){
	for(int i = 0; i < rows; i++)
    		delete board[i];
	delete board;
}

void Grid::setDimension(int r, int c){
	rows = r; columns = c;
	if(board != NULL){
		for(int i = 0; i < rows; i++)
    			delete board[i];
		delete board;	
	}
	board = new char*[rows];
	for(int i = 0; i < rows; i++)
    		board[i] = new char[columns];
	
}
void print(){
	
}

int main(){
	Grid grid(5, 5);
}
