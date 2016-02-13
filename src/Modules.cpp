#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <ctime>

#include "GlobalVariables.h"
#include "Printer.h"
#include "Modules.h"
#include "Programs.h"

int Modules::getRow(int rowColumn, int rowType) { // get the pitch from current column in the row
    switch (rowType) {
        case 1: return row[rowColumn];
        case 2: return row2[rowColumn];
        case 3: return rowLarge[rowColumn];
        case 4: return tranTable[rowColumn];
        default: return rowPrime[rowColumn];
    }
}

void Modules::setRow(int rowColumn, int rowPitch, int rowType) { // set the pitch from current column in the row
    switch (rowType) {
        case 1: row[rowColumn] = rowPitch; break;
        case 2: row2[rowColumn] = rowPitch; break;
        case 3: rowLarge[rowColumn] = rowPitch; break;
        case 4: tranTable[rowColumn] = rowPitch; break;
        default: rowPrime[rowColumn] = rowPitch;
    }
}

int Modules::getMultiRow(int rowColumn, int rowRow) { // get the pitch from current column in the multirow
    return rowMulti[rowColumn][rowRow];
}

void Modules::setMultiRow(int rowColumn, int rowRow, int rowPitch) { // get the pitch from current column in the multirow
    rowMulti[rowColumn][rowRow] = rowPitch;
}

int Modules::getRowSize(int rowType) { // get the size of row
    if (rowType== 2)
        return rowSize2;
    return rowSize;
}

void Modules::setRowSize(int x, int rowType) { // set the size of the row
    if (rowType == 2)
        rowSize2 = x;
    else
        rowSize = x;
}

void Modules::programCalling(Printer p, Modules &mo, int m) { // execute sub-programs
    Programs program;
    bool valid;

    if (!cin)    // if cin is in fail state, no need to go through switch statement
        inputInvalid(valid);
    else {
        switch (m) { // choose from the menu and execute selected program
            case 0: break;
            case 1: program.randomRow(p, mo); break;
            case 2: program.normalize(p, mo); break;
            case 3: program.rowTable(p, mo); break;
            case 4: program.matrix(p, mo); break;
            case 5: program.matrixRotate(p, mo); break;
            case 6: program.multiTable(p, mo, 1, 1); break; // range = 1 cancels the effect of the rotation
            case 7: program.multiTable(p, mo, 1, 0); break;	// when range is 0, it lets the j + i take effect (rotation)
            case 8: program.multiTable(p, mo, -1, 1); break; // multiply by -1 to change sign of the table, thus making inversions
            case 9: program.multiTable(p, mo, -1, 0); break;
            case 10: program.primeSet(p, mo); break;
            case 11: program.primeTable(p); break;
            case 12: program.permuteTable(p, mo); break;
            case 13: program.subsetsTable(p, mo); break;
            default: inputInvalid(valid); // check if invalid, go back to menu
        }
    }
}

int Modules::mod(int num, int sizeRange) {	// make sure pitch classes are in the range of sizeRange (default: 12)
    while(num >= sizeRange)
        num -= sizeRange; // keep subtracting sizeRange from input until it is in range
    while(num < 0)
        num += sizeRange; // keep adding sizeRange to input until it is in range
    return num;
}
/*
// same as Modules::mod() above, use recursion instead of loop
// sometimes causes stack-overflow in multiTable()
int Modules::modRecur(int num, int sizeRange) {
    if (num >= sizeRange)
        return modRecur(num - sizeRange, sizeRange);
    else if (num < 0)
        return modRecur(num + sizeRange, sizeRange);
    else
        return num;
}
*/
void Modules::swap(int &a, int &b) {	// swap a and b
    int temp = a;
    a = b;
    b = temp;
}

void Modules::insertionSort() { // insertion sort of an array
    for (int i = 0; i < rowSize; i++) {
        int j = i;
        while (j > 0 && rowPrime[j] < rowPrime[j - 1]) {
            swap(rowPrime[j], rowPrime[j - 1]);
            j--;
        }
    }
}

void Modules::insertionSortMulti() {  // insertion sort of a 2-D array
    for (int k = 0; k < rowSize * 4; k++) { // insertion sort of all normal sets
        for (int i = 0; i < rowSize; i++) {
            int j = i;
            while (j > 0 && rowMulti[k][j] < rowMulti[k][j - 1]) {
                swap(rowMulti[k][j], rowMulti[k][j - 1]);
                j--;
            }
        }
    }
}

int Modules::pitchToNum(string pitch) {   // convert pitch numbers/numbers from string to integer (0-11)
    if (pitch == "0" || pitch == "C" || pitch == "c" || pitch == "B#" || pitch == "b#")
        return 0;
    else if (pitch == "1" || pitch == "C#" || pitch == "c#" || pitch == "Db" || pitch == "db")
        return 1;
    else if (pitch == "2" || pitch == "D" || pitch == "d")
        return 2;
    else if (pitch == "3" || pitch == "D#" || pitch == "d#" || pitch == "Eb" || pitch == "eb")
        return 3;
    else if (pitch == "4" || pitch == "E" || pitch == "e" || pitch == "Fb" || pitch == "fb")
        return 4;
    else if (pitch == "5" || pitch == "E#" || pitch == "e#" || pitch == "F" || pitch == "f")
        return 5;
    else if (pitch == "6" || pitch == "F#" || pitch == "f#" || pitch == "Gb" || pitch == "gb")
        return 6;
    else if (pitch == "7" || pitch == "G" || pitch == "g")
        return 7;
    else if (pitch == "8" || pitch == "G#" || pitch == "g#" || pitch == "Ab" || pitch == "ab")
        return 8;
    else if (pitch == "9" || pitch == "A" || pitch == "a")
        return 9;
    else if (pitch == "10" || pitch == "A#" || pitch == "a#" || pitch == "Bb" || pitch == "bb")
        return 10;
    else if (pitch == "11" || pitch == "B" || pitch == "b" || pitch == "Cb" || pitch == "cb")
        return 11;
    else
        return -1;
}

int Modules::charToNum(char pitch) {   // convert a char to a pitch number: A is 10, B is 11
    switch (pitch) {
        case '0': return 0;
        case '1': return 1;
        case '2': return 2;
        case '3': return 3;
        case '4': return 4;
        case '5': return 5;
        case '6': return 6;
        case '7': return 7;
        case '8': return 8;
        case '9': return 9;
        case 'A': return 10;
        default: return 11;
    }
}

string Modules::intToString(int num) {   // convert an integer (0 - 11) to a string: 10 is A, 11 is B
    switch (num) {
        case 0: return "0";
        case 1: return "1";
        case 2: return "2";
        case 3: return "3";
        case 4: return "4";
        case 5: return "5";
        case 6: return "6";
        case 7: return "7";
        case 8: return "8";
        case 9: return "9";
        case 10: return "A";
        default: return "B";
    }
}

void Modules::permute(string soFar, string rest, int arrSize, char out, ofstream &outFile) {	// print out a permutation table of a given set
    if (rest == "") {	// convert char symbols from the sub-strings of soFar to pitches, then print out
        for (int i = 0; i < arrSize; i++) {
            cout << TABLE[charToNum(soFar[i])];
            if (out == 'y')
                outFile << TABLE[charToNum(soFar[i])];
        }
        cout << endl;
        if (out == 'y')
            outFile << endl;
    } else {
        for (int i = 0; i < static_cast<int>(rest.length()); i++) {
            string next = soFar + rest[i];
            string remaining = rest.substr(0, i) + rest.substr(i + 1);
            permute(next, remaining, arrSize, out, outFile);
        }
    }
}

void Modules::subsets(string soFar, string rest, char out, ofstream &outFile) {	// print out all subsets of a given set
    if (rest == "") {	// convert char symbols from the sub-strings of soFar to pitches, then print out
        for (int i = 0; i < static_cast<int>(soFar.length()); i++) {
            cout << TABLE[charToNum(soFar[i])];
            if (out == 'y')
                outFile << TABLE[charToNum(soFar[i])];
        }
        cout << endl;
        if (out == 'y')
            outFile << endl;
    } else {
        // add to subset, remove from rest, recursion
        subsets(soFar + rest[0], rest.substr(1), out, outFile);
        // don't add to subset, remove from rest, recursion
        subsets(soFar, rest.substr(1), out, outFile);
    }
}

void Modules::inputInvalid(bool &check) { // input invalid warning
    check = false;
    cin.clear();    // clear input stream
    cin.ignore(MAXINT, '\n'); // ignore the max integer from input until '\n'
    cout << "INPUT INVALID--please try again..." << endl;
}

void Modules::generateTwelve(int rType) {    // populate an array with a random twelve-tone row
    bool repeated;
    int generatedPitch;
    int counter = 0;

    srand(unsigned(time(NULL)));

    while (counter < 12) {
        repeated = false;	// control if the counter increments
        generatedPitch = rand() % 12;	// generate a random number between 0-11

        for (int i = 0; i < counter; i++) {  // check all items before the current position
            if (generatedPitch == getRow(i, 1))  // if a pitch is repeated, repeated = true, do not advance counter
                repeated = true;		   // otherwise, repeated remains false
        }

        if (repeated == false) {  // if there's no repeat before the current position, assign the pitch
            setRow(counter, generatedPitch, rType);
            counter++;  // continue to the next item in array
        }
    }
}

void Modules::inputRowLength(int rType, int lim, string num) {  // user input: how many pitches?
    bool valid;	// input valid check
    int input;	// size of row

    do {
        valid = true;
        cout << "How many pitches would you like in your " << num << "row (1-" << lim << ")? ";
        cin >> input;
        if (input < 1 || input > lim || !cin) {
            inputInvalid(valid);
            continue;
        }
        setRowSize(input, rType);
    } while (valid == false);
}

void Modules::inputRow(int rType, string num) { // user input: what pitches?
    bool valid;	// input valid check
    string input;

    for (int i = 0; i < getRowSize(rType); i++) {
        cout << "Enter your " << num << "row in pitches or numbers (" << i + 1 << "): ";
        do {
            valid = true;
            cin >> input;
            if (pitchToNum(input) == -1) {
                inputInvalid(valid);
                continue;
            }
            setRow(i, pitchToNum(input), rType);
        } while (valid == false);
    }
}

void Modules::inputRowNor() {  // input for normalize()
    bool valid;	// input valid check
    int input;

    for (int i = 0; i < getRowSize(1); i++) {
        cout << "Enter your row in any integers between -" << MAXINT
            << " and " << MAXINT << " (" << i + 1 << "): ";
        do {
            valid = true;
            cin >> input;
            if (getRow(i, 1) < -MAXINT || getRow(i, 1) > MAXINT || !cin) {
                inputInvalid(valid);
                continue;
            }
            setRow(i, input, 1);
        } while (valid == false);
    }
}

void Modules::transposition(int rType) {	// make a transposition table
    setRow(0, 0, 4); // no transposition for the first pitch
    for (int i = 1; i < getRowSize(1); i++)
        // initialize a transposition table to find the distance between each pitch in the row
        setRow(i, getRow(i, rType) - getRow(i - 1, rType), 4); // start with subtracting the 1st pitch from the 2nd pitch
}

void Modules::populateRow(bool fixed, int rType, string prompt) {	// populate an array
    char answer;
    bool valid; //input valid check

    do {
        valid = true;
        cout << endl << "Would you like to use a randomly-generated twelve-tone row? (y/n): ";
        cin >> answer;
        if (!cin)
            inputInvalid(valid);
        else {
            switch (answer) {
                case 'y':
                    setRowSize(12, rType);
                    generateTwelve(rType);
                    break;
                case 'n':
                    cout << endl << prompt << endl;
                    if(fixed == false)	// if the array size is not fixed, prompt user to input size
                        inputRowLength(rType);
                    inputRow(rType);
                    break;
                default:
                    inputInvalid(valid);
            }
        }
    } while (valid == false);
}

int Modules::rotationDirection() {    // determine the direction of rotation (default to right)
    char direction;
    bool valid;

    do {
        valid = true;
        cout << endl << "Would you like to rotate to the left instead of to the right? (y/n): ";
        cin >> direction;
        if (!cin)
            inputInvalid(valid);	// back to loop if input is invalid
        else {
            switch (direction) {
                case 'y': return -1;    // rotate to left
                case 'n': return 1; // rotate to right
                default: inputInvalid(valid);
            }
        }
    } while (valid == false);
    return 1;
}

void Modules::outputting(char &f, ofstream &outFile) {  // output to a text file
    string fName;
    bool valid;

    do {
        valid = true;
        cout << "Would you like to write to a file? (y/n): ";
        cin >> f;
        if (!cin)
            inputInvalid(valid);
        else {
            switch (f) {
                case 'y':
                    cout << "Enter a file name (to append, enter the name of an existing file): ";
                    cin >> fName;
                    outFile.open(fName.c_str(), ios::app);
                    break;
                case 'n':
                    break;
                default:
                    inputInvalid(valid);
            }
        }
    } while (valid == false);
}