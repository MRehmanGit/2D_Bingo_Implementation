#include "bingo.h"
Bingo::Bingo() {
    initObjBingo();
}

Bingo::Bingo(int rows, int columns, int min, int max) {

    if (rows < 2 || columns != 5 || (max - min + 1) % 5 != 0 || rows > 15) {
        initObjBingo();
    }
    else {
        m_numRows = rows;
        m_numCols = columns;
        m_minBallVal = min;
        m_maxBallVal = max;
        m_trackRows = new int[m_numCols];
        m_trackCols = new int[m_numRows];
        m_card = new Cell * [m_numRows];
        for (int i = 0; i < m_numRows; i++) {
            m_card[i] = new Cell[m_numCols];
        }
        m_helperSize = m_numRows * m_numCols;
        m_helper = new Cell[m_helperSize];
    }

}

bool Bingo::reCreateCard(int rows, int columns, int min, int max) {
   
    //The return value of this function indicates the success or failure of the operations. 

    //checking if the requirments of the paramenters are meet 
    if (rows < 2 || columns != 5 || (max - min + 1) % 5 != 0 || rows > 15) {
        //if it meets one of the requirements above then it means that it failed to meet the init requirments, thus
        //it would create an empty object
        initObjBingo(); 
    }
    else {  
        //if it doesnt meet the requirments above, then it means that it successfully meets the init requirments.
        //it would initializes a new card 
        //editing the size of rows and columns
        m_numRows = rows; //rows being doubled when reinit the bingo card 
        m_numCols = columns;
        m_minBallVal = min;
        m_maxBallVal = max;
        m_trackRows = new int[m_numCols];
        m_trackCols = new int[m_numRows];
        m_card = new Cell * [m_numRows];
        for (int i = 0; i < m_numRows; i++) {
            m_card[i] = new Cell[m_numCols];
        }
        
        m_helperSize = (m_numRows * m_numCols); //in the helperSize, the row would become multiplied by 2
        m_helper = new Cell[m_helperSize];
    }
    //creating a formula of range between min and max
    int formula = m_maxBallVal - m_minBallVal + 1;
    if (m_card == nullptr || formula % 5 != 0) {
        return false;
    }

    int jump = formula / 5;

    int start = m_minBallVal;
    int end = start + jump - 1;
    int counter = 0;
    int testCount = 0;
    cout <<"The number of rows are: " << m_numRows << endl;

    //implementing this as a regular 2D array 
    for (int r = 0; r < 5; r++) {  //replaced the condition from m_rows to 5
  
        cout << "Randomization is starting from :" << start << endl;
        cout << "Randomization is ending from :" << end << endl;
        Random randomValue(start, end, UNIFORMINT); //creating an object of type uniformant with required paramneters

        for (int c = 0; c < 10;) {  //replaced the condition from m_cols to 5

            int random = randomValue.getRandNum(); //storing the random object in the random variable

            cout << "created Random number:  " << random << "  ";
            
            if (!reInitDuplicates(c,r,random)) {      //checking if there are any duplicates 
                Cell tempCell(r, c, random); //if not then creating a cell which would store the random number
                    m_card[c][r] = tempCell;
                    m_helper[counter] = random;  //storing the random number into the array helper for backup
                    counter++;
                    c++;
            }
        }
        start = end + 1;   //updating the start 
        end = start + jump - 1; //updating the end 
    }
    cout << "total of not same values are " << testCount << endl;
    return true;

}

Bingo::~Bingo() {
    destroyObj();
}

void Bingo::clear() {
    destroyObj();
    initObjBingo();
    
}

bool Bingo::initCard() {
    
    int formula = m_maxBallVal - m_minBallVal + 1;

    if (m_card == nullptr || formula % 5 != 0) {
        return false;
    }

    int jump = formula / 5; 
    
    int start = m_minBallVal;
    int end = start + jump - 1;
    int counter = 0;
    //implementing this as a regular 2D array 
    for (int r = 0; r < m_numRows; r++) {
        Random randomValue(start, end, UNIFORMINT); //creating an object of type uniformant with required paramneters
        for (int c = 0; c < m_numCols;) {
            int random = randomValue.getRandNum(); //storing the random object in the random variable 
            if (!same(c,r,random)) {      //checking if there are any duplicates 
                Cell tempCell(r, c, random); //if not then creating a cell which would store the random number 
                m_card[c][r] = tempCell;    
                m_helper[counter] = random;  //storing the random number into the array helper for backup
                counter++;
                c++;
            }
            
        }
        start = end + 1;   //updating the start 
        end = start + jump - 1; //updating the end 
        }
        return true;

    }
   
vector<int> Bingo::drawBalls() {
    //This function generates and returns a list containing randomly distributed ball numbers.
     
    // There is no duplicate numbers in the list. 
    
    // One may use the RANDOM type SHUFFLE from the Random class for generating the list. 
    
    // The ball numbers are within the range of m_minBallVal and m_maxBallVal

    vector<int> temp;
    int totalsize = m_numRows * m_numCols;
    int index = 0;
   /* cout<<"the size of vector is "<< temp.size() << endl;
    cout << "the size of 2D bingo card is " << totalsize << endl;*/
    int* arr = new int[totalsize];
  
        for (int i = m_minBallVal; i < m_maxBallVal && index < totalsize; i++) {
                arr[index] = i;
                index++;
            
        }

        //cout << "shuffled values below " << endl;
        for (int s = 0; s < totalsize; s++) {
            Random obj(m_minBallVal, m_maxBallVal, SHUFFLE);
            obj.getShuffle(&arr[s]);
           // cout << "In the index of the arr[" << s << "] the value: " << arr[s] << " is stored!" << endl;
            temp.push_back(arr[s]);
        }
       
    delete[]arr;
    return temp;
     
}

int Bingo::play(int numDraws, vector<int> rndBalls) {

    if (rndBalls.empty()) {
        return -1;
    }
    int count = 0;

    for (int i = 0; i < rndBalls.size(); i++) { //starting the check from rndBalls[0] index 
        for (int r = 0; r < m_numRows; r++) {  //making the card to check for comparision 
            for (int c = 0; c < m_numCols; c++) {
                if (same(c, r, rndBalls[i])) {  //if the value in the vector is same in the card 
                    Cell temp(r, c, EMPTYCELL); //then creating a cell which would store the value EMPTYCELL
                    m_card[c][r] = temp;   //inserting the Cell into the location
                    count++;  //counting the number of replacements
                    if (isEnd()) {
                        return count;
                   }
                }
            }
        }
    }
    
    try {
        if (numDraws > m_maxBallVal || rndBalls.size() > m_maxBallVal) { //a statement which would cause the error
            throw "there must have been an sizing error with the rndBalls vector or numDraws exceeded the max value";
        }
    }catch (const char *error) { //and printing the error statement below
        cout << error << endl;
        }

    return -1;
}

const Bingo& Bingo::operator=(const Bingo& rhs) {
  
    if (this != &rhs) {
     
        m_maxBallVal = rhs.m_maxBallVal;
        m_minBallVal = rhs.m_minBallVal;
        m_numCols = rhs.m_numCols;
        m_numRows = rhs.m_numRows;
        m_helperSize = rhs.m_helperSize;
        //creating columns track
        m_trackCols = new int[m_numRows];
        //copying columns track 
        for (int i = 0; i < m_numRows; i++) {
            m_trackCols[i] = rhs.m_trackCols[i];
        }
        //creating rows track
        m_trackRows = new int[m_numCols];
        //copuing rows track
        for (int i = 0; i < m_numCols; i++) {
            m_trackRows[i] = rhs.m_trackRows[i];
        }
        //creating a new 2D array
        m_card = new Cell *[m_numRows];
        for (int i = 0; i < m_numRows; i++) {
            m_card[i] = new Cell[m_numCols];
        }
        //now, copying the 2d array from rhs
        for (int r = 0; r < m_numRows; r++) {
            for (int c = 0; c < m_numCols; c++) {
                m_card[r][c] = rhs.m_card[r][c];
            }
        }
        //creating new m_helper array
        m_helper = new Cell[m_helperSize];
        //copy the m_helper array from rhs
        for (int i = 0; i < m_helperSize; i++) {
            m_helper[i] = rhs.m_helper[i];
        }

    }
    return *this;
}

// The dump function renders the card in the terminal
// This function is provided to facilitate debugging
// Using this function as a test case will not be accepted
void Bingo::dumpCard() {
    cout << "  ";
    cout << "\033[1;35m B   I   N   G   O\033[0m";
    cout << endl;
    for (int i = 1; i <= m_numRows; i++) {
        if ((i < 10))
            cout << "\033[1;35m" << "0" << i << " \033[0m";
        else
            cout << "\033[1;35m" << i << " \033[0m";
        for (int j = 1; j <= m_numCols; j++) {
            if (m_card[i - 1][j - 1].getVal() == EMPTYCELL)
                cout << "\033[1;31m" << m_card[i - 1][j - 1].getVal() << "\033[0m" << "  ";
            else
                cout << m_card[i - 1][j - 1].getVal() << "  ";
        }
        cout << endl;
    }
    cout << endl;
}

// the overloaded equality operator for the Cell object
bool operator==(const Cell& lhs, const Cell& rhs) {
    return ((lhs.m_col == rhs.m_col) &&
        (lhs.m_row == rhs.m_row) &&
        (lhs.m_value == rhs.m_value));
}




void Bingo::initObjBingo() {
    m_maxBallVal = 0;
    m_minBallVal = 0;
    m_numCols = 0;
    m_numRows = 0;
    m_card = nullptr;
    m_helperSize = 0;
    m_helper = nullptr;
    m_trackRows = nullptr;
    m_trackCols = nullptr;
}

void Bingo:: destroyObj(){
    if (m_card != nullptr) {

        for (int i = 0; i < m_numRows; i++) {

            delete[] m_card[i];
        }
        delete[] m_card;
        m_card = nullptr;

    }
    if (m_trackRows != nullptr) {
        delete[] m_trackRows;
        m_trackRows = nullptr;
    }
    if (m_trackCols != nullptr) {
        delete[] m_trackCols;
        m_trackCols = nullptr;
    }
    if (m_helper != nullptr) {
        delete[] m_helper;
        m_helper = nullptr;
    }


}




bool Bingo::isPresent(int column, int v) {

    for (int i = 0; i < m_numRows; i++) {

        if(m_card[column][i].getVal() == v) {
            return true;
        }
    }
    return false;
}



bool Bingo::same(int row, int column, int variable) {

    for (int r = 0; r < row; r++) {
        for (int c = 0; c < column; c++) {
            if (m_card[r][c].getVal() == variable) {
                return true;
            }
        }
    }

    return false;

}

bool Bingo::reInitDuplicates(int row, int column, int variable) {

    for (int r = 0; r < 5; r++) {
        for (int c = 0; c < 10; c++) {
            if (m_card[r][c].getVal() == variable) {
                return true;
            }
        }
    }

    return false;

}


bool Bingo::isEnd() {
    int cColumn = 0;
    int cRows = 0;


    for (int r = 0; r < m_numRows; r++) {
        cColumn = 0;
        cRows = 0;
        for (int c = 0; c < m_numCols; c++) {
            if (m_card[r][c].getVal() == 99) { //checking for regular 2D array 
                cRows++;
            }

            if (m_card[c][r].getVal() == 99) {  //checking for transposed 2D array 
                cColumn++;
            }

        }
        if (cColumn == m_numCols || cRows == m_numRows) {
            return true;
        }

    }
    return false;
}