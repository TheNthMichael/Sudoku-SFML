#include "SudokuGame.h"


/****************************************PRIVATE*******************************************/


/*	bool SudokuGame::validMove(int row, int col)
		check if a board's move was valid
*/
bool SudokuGame::validMove(int r, int c)
{
	std::set<std::string> row;
	std::set<std::string> col;

	if (board.size() != board[0].size()) {
		std::cout << "well here is the issue\n";
		return false;
	}

	if (r < 0 || r >= board.size()) {
		std::cout << "Invalid row...\n";
		return false;
	}
	if (c < 0 || c >= board.size()) {
		std::cout << "Invalid col...\n";
		return false;
	}


	for (int i = 0; i < board.size(); i++) {
		// look for duplicate in row
		std::cout << "boardrow = " << board[r][i]->getText() << "\n";
		std::cout << "boardcol = " << board[i][c]->getText() << "\n";
		if (!board[r][i]->getText().empty()) {
			if (row.find(board[r][i]->getText()) != row.end())
				return false;
			row.insert(board[r][i]->getText());
		}
		// look for duplicate in col
		if (!board[i][c]->getText().empty()) {
			if (col.find(board[i][c]->getText()) != col.end())
				return false;
			col.insert(board[i][c]->getText());
		}
	}


	// check if the submatrix of the new move is valid
	return validSubmatrix(r - r % 3, c - c % 3);
}


/*	bool SudokuGame::validSubmatrix(int startRow, int startCol)

*/
bool SudokuGame::validSubmatrix(int startRow, int startCol)
{
	std::set<std::string> subMatrix;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (!board[startRow + i][startCol + j]->getText().empty()) {
				if (subMatrix.find(board[startRow + i][startCol + j]->getText()) != subMatrix.end())
					return false;
				subMatrix.insert(board[startRow + i][startCol + j]->getText());
			}
		}
	}
	return true;
}

bool SudokuGame::validMove(std::vector<std::vector<std::string>> tmpBoard, int r, int c)
{
	std::set<std::string> row;
	std::set<std::string> col;

	if (tmpBoard.size() != tmpBoard[0].size()) {
		std::cout << "well here is the issue\n";
		return false;
	}

	if (r < 0 || r >= tmpBoard.size()) {
		std::cout << "Invalid row...\n";
		return false;
	}
	if (c < 0 || c >= tmpBoard.size()) {
		std::cout << "Invalid col...\n";
		return false;
	}


	for (int i = 0; i < tmpBoard.size(); i++) {
		// look for duplicate in row
		if (!tmpBoard[r][i].empty()) {
			if (row.find(tmpBoard[r][i]) != row.end())
				return false;
			row.insert(tmpBoard[r][i]);
		}
		// look for duplicate in col
		if (!tmpBoard[i][c].empty()) {
			if (col.find(tmpBoard[i][c]) != col.end())
				return false;
			col.insert(tmpBoard[i][c]);
		}
	}


	// check if the submatrix of the new move is valid
	return validSubmatrix(tmpBoard, r - r % 3, c - c % 3);
}

bool SudokuGame::validSubmatrix(std::vector<std::vector<std::string>> tmpBoard, int r, int c)
{
	std::set<std::string> subMatrix;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (!tmpBoard[r + i][c + j].empty()) {
				if (subMatrix.find(tmpBoard[r + i][c + j]) != subMatrix.end())
					return false;
				subMatrix.insert(tmpBoard[r + i][c + j]);
			}
		}
	}
	return true;
}

void SudokuGame::createSet(std::vector<std::vector<std::string>> tmpBoard, int r, int c, std::set<std::string>& elements)
{
	std::set<std::string> numbers;
	std::string why = "";
	for (int i = 1; i < 10; i++) {
		why += '0' + i;
		elements.insert(why);
		why.clear();
	}

	for (int i = 0; i < tmpBoard.size(); i++) {
		// generate row set
		if (!tmpBoard[r][i].empty()) {
			numbers.insert(tmpBoard[r][i]);
		}
		// generate col set
		if (!tmpBoard[i][c].empty()) {
			numbers.insert(tmpBoard[i][c]);
		}
	}

	r = r - r % 3;
	c = c - c % 3;

	// generate submatrix set
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (!tmpBoard[r + i][c + j].empty()) {
				numbers.insert(tmpBoard[r + i][c + j]);
			}
		}
	}


	// set test - intersection(test, elements) => difference
	for (auto& e : numbers) {
		if (elements.find(e) != elements.end())
			elements.erase(e);
	}

}


/*	std::string SudokuGame::getRandomElement(std::set<std::string> elements)
		returns a random element from a set
*/
std::string SudokuGame::getRandomElement(std::set<std::string> elements)
{
	int random = rand() % elements.size();
	auto iter = elements.begin();
	for (int i = 0; i < random; i++) {
		iter++;
	}
	return *iter;
}


/*	void SudokuGame::randomBoard()
		generates a random board, fills in this->board in place
*/
void SudokuGame::randomBoard()
{
	std::vector<std::vector<std::string>> tmpBoard;
	int count = 0;
	srand((int)time(0));
	tmpBoard = generateSimpleBoardCopy();
	if (!solve(tmpBoard, 0, 0)) {
		std::cout << "something went terribly wrong\n";
		exit(1);
	}

	for (auto& row : tmpBoard) {
		for (auto& tile : row) {
			std::cout << " " << tile << " ";
		}
		std::cout << std::endl;
	}

	for (int i = 0; i < tmpBoard.size(); i++) {
		for (int j = 0; j < tmpBoard[i].size(); j++) {
			if (rand() % 100 >= 65 && count < 18) {
				board[i][j]->setString(tmpBoard[i][j]);
				board[i][j]->setIsSelectable(false);
				count++;
			}
		}
	} 

}


/*	std::vector<std::vector<std::string>> SudokuGame::generateSimpleBoardCopy()
		from this->board, retrieves the strings inside tile objects and creates a dummy board to fill
*/
std::vector<std::vector<std::string>> SudokuGame::generateSimpleBoardCopy()
{
	std::vector<std::vector<std::string>> tmpBoard;

	for (int i = 0; i < boardSize; i++) {
		tmpBoard.push_back(std::vector<std::string>());
		for (int j = 0; j < boardSize; j++) {
			tmpBoard[i].push_back(board[i][j]->getText());
		}
	}

	return tmpBoard;
}


/*	bool SudokuGame::boardFull()
		checks if this->board is full
*/
bool SudokuGame::boardFull()
{
	for (auto& row : board) {
		for (auto& tile : row) {
			if (tile->getText().empty())
				return false;
		}
	}
	return true;
}


/*	void SudokuGame::solve(int r, int c)
		Uses the backtracking algorithm to solve a board/see if a solution exists
*/
bool SudokuGame::solve(int r, int c)
{
	/*
        if(state == unsolvable)
            return
        from state
            For each move
                recurse with that move
	*/
	// check if the board is full
	if (r == boardSize) {
		return true;
	}
	
	// check if we are moving to a new row
	int new_r = r;
	if (c + 1 == boardSize) {
		new_r++;
	}

	// don't check empty spots
	if (!board[r][c]->getText().empty()) {
		return solve(new_r, (r + 1) % boardSize);
	}

	// go through each possibility
	for (int i = 1; i < 10; i++) {
		board[r][c]->setValue('0' + i);
		if (this->validMove(r, c)) {
			if (solve(new_r, (c + 1) % boardSize))
				return true;
		}
	}
	// no valid move exists in this state
	board[r][c]->clearValue();
	return false;
}


/*	bool SudokuGame::solve(std::vector<std::vector<std::string>>& tmpBoard, int r, int c)
		solves tmpBoard in place using random elements from a set of given options
*/
bool SudokuGame::solve(std::vector<std::vector<std::string>>& tmpBoard, int r, int c)
{
	/*
		if(state == unsolvable)
			return
		from state
			For each move
				recurse with that move
	*/
	// check if the board is full
	if (r == tmpBoard.size()) {
		return true;
	}

	// check if we are moving to a new row
	int new_r = r;
	if (c + 1 == tmpBoard.size()) {
		new_r++;
	}

	// don't check empty spots
	if (!tmpBoard[r][c].empty()) {
		return solve(tmpBoard, new_r, (c + 1) % tmpBoard.size());
	}

	std::set<std::string> elements;
	this->createSet(tmpBoard, r, c, elements);
	/*for (auto& e : elements) {
		std::cout << "[:::] -> " << e << std::endl;
	}*/

	std::string chosen = "0";

	// go through each possibility
	
	while (elements.size() != 0) {
		//std::cout << "len = " << elements.size() << std::endl;

		chosen = getRandomElement(elements);
		tmpBoard[r][c] = chosen;
		elements.erase(chosen);

		// chosen from the only available options
		if (solve(tmpBoard, new_r, (c + 1) % tmpBoard.size()))
			return true;
	}
	
	// no valid move exists in this state
	tmpBoard[r][c].clear();
	return false;
}


/****************************************PUBLIC*******************************************/


// Create a default 9x9 board
SudokuGame::SudokuGame(sf::Font& font)
{
	// int charSize, sf::Font& font, sf::Vector2f size, sf::Color backgroundColor, sf::Color textColor, bool sel
	this->font = font;
	this->boardSize = 9;
	this->tileSize = 50;
	this->selected = nullptr;
	for (int i = 0; i < boardSize; i++) {
		this->board.push_back(std::vector<SudokuTile*>());
		for (int j = 0; j < boardSize; j++) {
			this->board[i].push_back(new SudokuTile(15, this->font, { static_cast<float>(tileSize),static_cast<float>(tileSize) }, sf::Color(175, 175, 175), sf::Color::Black, false, true));
			this->board[i][j]->setPosition({ i * (static_cast<float>(tileSize) + 5), j* (static_cast<float>(tileSize) + 5) });
		}
	}

	this->btn_solve = Button("Solve", 20, { 100, 50 }, sf::Color::Red, sf::Color::White);
	this->btn_solve.setFont(this->font);
	this->btn_solve.setPosition({100.0f, this->boardSize * this->tileSize + 50 * 1.0f});

	this->randomBoard();
}

// Create a board of size numTiles x numTiles
SudokuGame::SudokuGame(sf::Font& font, int numTiles)
{
	this->font = font;
	this->boardSize = numTiles;
	this->tileSize = 50;
	this->selected = nullptr;
	for (int i = 0; i < boardSize; i++) {
		this->board.push_back(std::vector<SudokuTile*>());
		for (int j = 0; j < boardSize; j++) {
			this->board[i].push_back(new SudokuTile(15, this->font, { static_cast<float>(tileSize),static_cast<float>(tileSize) }, sf::Color(175, 175, 175), sf::Color::Black, false, true));
			this->board[i][j]->setPosition({ i * (static_cast<float>(tileSize) + 20), j * (static_cast<float>(tileSize) + 20) });
		}
	}
}


/* void SudokuGame::hover(sf::Event ev, sf::RenderWindow* window)
	Game handles the event of hovering,
		search through the list of SudokuTiles
		set the backColor of the hovered peice to a darker gray
		sets the backColor of all other peices to the original color
*/
void SudokuGame::hover(sf::Event ev, sf::RenderWindow* window)
{
	for (auto& v : board) {
		for (auto& t : v) {
			if (t != this->selected) {
				if (t->isMouseOver(window)) {
					t->setBackColor(sf::Color(100, 100, 100));	// gray
				}
				else {
					t->setBackColor(sf::Color(175, 175, 175));	// light-gray
				}
			}
		}
	}
}

Response SudokuGame::selecting(sf::Event ev, sf::RenderWindow* window)
{
	/*int i = 0, j = 0;
	for (auto& v : board) {
		for (auto& t : v) {
			if (t->isMouseOver(window)) {
				this->selected = t;
				t->setSelected(true);
				t->setBackColor(sf::Color(198, 237, 186));	// green-ish
				rowSel = i;
				colSel = j;
			}
			else {
				t->setSelected(false);
				t->setBackColor(sf::Color(175, 175, 175));	// light-gray
			}
			j++;
		}
		i++;
	}*/

	// solve for me
	if (btn_solve.isMouseOver(window)) {
		if (this->selected != nullptr) {
			this->selected->clearValue();
			this->selected->setSelected(false);
			this->selected->setBackColor(sf::Color(175, 175, 175));	// light-gray
			this->selected = nullptr;
		}
		std::cout << "Solving for you...\n";
		std::vector<std::vector<std::string>> tmpBoard = generateSimpleBoardCopy();
		PAIR p;
		while (!this->solve(tmpBoard, 0, 0) && this->moveList.size() != 0) {
			p = this->moveList[this->moveList.size() - 1];
			board[p.i][p.j]->clearValue();
			this->moveList.pop_back();
			std::cout << "Failed, removing [" << p.i << ", " << p.j << "]\n";
		}
		for (int i = 0; i < tmpBoard.size(); i++) {
			for (int j = 0; j < tmpBoard[i].size(); j++) {
				board[i][j]->setString(tmpBoard[i][j]);
			}
		}
		return NONE;
	}

	// test
	if (this->deselect() == false)
		return NONE;

	if (this->boardFull()) {
		return TO_MENU;
	}

	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[i].size(); j++) {
			if (board[i][j]->isMouseOver(window) && board[i][j]->getIsSelectable()) {
					this->selected = board[i][j];
					board[i][j]->setSelected(true);
					board[i][j]->setBackColor(sf::Color(198, 237, 186));	// green-ish
					rowSel = i;
					colSel = j;
			}
			else {
				board[i][j]->setSelected(false);
				board[i][j]->setBackColor(sf::Color(175, 175, 175));	// light-gray
			}
		}
	}

	return NONE;
}

bool SudokuGame::deselect()
{
	if (this->selected != nullptr) {
		//getchar();
		if (this->validMove(rowSel, colSel)) {
			if (!this->selected->getText().empty()) {
				// text isn't empty, a move was made
				this->moveList.push_back({ rowSel, colSel });
			}
			this->selected->setSelected(false);
			this->selected->setBackColor(sf::Color(175, 175, 175));	// light-gray
			this->selected = nullptr;
			return true;
		}
		else {
			this->selected->setSelected(true);
			this->selected->setBackColor(sf::Color(255, 0, 0));	// this is clearly not light-gray
			return false;
		}
	}
	return true;
}

Response SudokuGame::enteringText(sf::Event ev, sf::RenderWindow* window)
{
	if (this->selected == nullptr)
		return NONE;
	this->selected->typedOn(ev);
	return NONE;
}

void SudokuGame::drawTo(sf::RenderWindow* window)
{
	for (int i = 0; i < this->board.size(); i++) {
		for (int j = 0; j < this->board[i].size(); j++) {
			board[i][j]->drawTo(window);
		}
	}

	this->btn_solve.drawTo(window);
}
