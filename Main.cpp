#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

// Finding neighbours of an element of array
void getNeighbours(int** array, int x, int y, int* neighboursX, int* neighboursY, int value, int N, int& index) {

    if (x - 1 >= 0 && array[x - 1][y] == value) {
        bool flag = false;
        for (int i = 0; i < index; i++) {
            if (neighboursX[i] == x - 1 && neighboursY[i] == y) {
                flag = true;
                break;
            }
        }
        if (flag == false) {
            neighboursX[index] = x - 1;
            neighboursY[index] = y;
            index++;
            getNeighbours(array, x - 1, y, neighboursX, neighboursY, value, N, index);
        }
    }
    if (y + 1 < N && array[x][y + 1] == value) {
        bool flag = false;
        for (int i = 0; i < index; i++) {
            if (neighboursX[i] == x && neighboursY[i] == y + 1) {
                flag = true;
                break;
            }
        }
        if (flag == false) {
            neighboursX[index] = x;
            neighboursY[index] = y + 1;
            index++;
            getNeighbours(array, x, y + 1, neighboursX, neighboursY, value, N, index);
        }
    }
    if (x + 1 < N && array[x + 1][y] == value) {
        bool flag = false;
        for (int i = 0; i < index; i++) {
            if (neighboursX[i] == x + 1 && neighboursY[i] == y) {
                flag = true;
                break;
            }
        }
        if (flag == false) {
            neighboursX[index] = x + 1;
            neighboursY[index] = y;
            index++;
            getNeighbours(array, x + 1, y, neighboursX, neighboursY, value, N, index);
        }
    }
    if (y - 1 >= 0 && array[x][y - 1] == value) {
        bool flag = false;
        for (int i = 0; i < index; i++) {
            if (neighboursX[i] == x && neighboursY[i] == y - 1) {
                flag = true;
                break;
            }
        }
        if (flag == false) {
            neighboursX[index] = x;
            neighboursY[index] = y - 1;
            index++;
            getNeighbours(array, x, y - 1, neighboursX, neighboursY, value, N, index);
        }
    }

    return;
}

// PART 1 - Process function
void process(int** arr1, int* neighboursX, int* neighboursY, int index, int t, int N, int x, int y) {

    for (int i = 0; i < index; i++) {
        arr1[neighboursX[i]][neighboursY[i]] = 0;
    }
    arr1[neighboursX[0]][neighboursY[0]] = t + 1;
    index = 1;
    getNeighbours(arr1, x, y, neighboursX, neighboursY, t + 1, N, index);

    if (index >= 3) {
        process(arr1, neighboursX, neighboursY, index, t + 1, N, x, y);
    }
    else {
        return;
    }
}

// PART 2 - Process function
void processPart2(int** arr2, int part2X, int part2Y, int M, int& totalPoint) {

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            if (i == part2X && j == part2Y) continue;
            if (i == part2X && arr2[i][j] == arr2[part2X][part2Y]) {
                totalPoint += arr2[i][j];
                arr2[i][j] = 0;
            }
            else if (j == part2Y && arr2[i][j] == arr2[part2X][part2Y]) {
                totalPoint += arr2[i][j];
                arr2[i][j] = 0;
            }
            else if (part2X - i == part2Y - j && arr2[part2X][part2Y] == arr2[i][j]) {
                totalPoint += arr2[i][j];
                arr2[i][j] = 0;
            }
            else if (part2X + part2Y == i + j && arr2[part2X][part2Y] == arr2[i][j]) {
                totalPoint += arr2[i][j];
                arr2[i][j] = 0;
            }
        }
    }
}

int main(int argc, char** argv) {

    // Output File
    ofstream outputFile;
    outputFile.open(argv[3]);

    // For reading first input file
    ifstream inputFile1;
    inputFile1.open(argv[1]);
    string text1;

    // For declaring array size
    int N;
    getline(inputFile1, text1);
    N = stoi(text1);

    // Array declaration
    int** arr1;
    arr1 = new int* [N];

    for (int i = 0; i < N; i++) {
        arr1[i] = new int[N];
    }

    // For neighbours indexes
    int maxSize = N * N;
    int* neighboursX;
    neighboursX = new int[maxSize];
    int* neighboursY;
    neighboursY = new int[maxSize];
    int index = 1; // first line of file is array size

    // Filling array with 0
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            arr1[i][j] = 0;
        }
    }

    int value, xInd, yInd;
    vector<int> values;
    vector<int> xIndices;
    vector<int> yIndices;


    while (getline(inputFile1,text1)) {

        stringstream ss(text1);
        ss >> value >> xInd >> yInd;

        values.push_back(value);
        xIndices.push_back(xInd);
        yIndices.push_back(yInd);
       
        int t, x, y;      // t = value, x = row index, y = column index
        t = values[0];
        x = xIndices[0];
        y = yIndices[0];
        
        values.pop_back();
        xIndices.pop_back();
        yIndices.pop_back();

        arr1[x][y] = t;
        neighboursX[0] = x;
        neighboursY[0] = y;
        index = 1;
        getNeighbours(arr1, x, y, neighboursX, neighboursY, t, N, index);

        if (index >= 3) // if there are 3 or more identical elements next to each other
            process(arr1, neighboursX, neighboursY, index, t, N, x, y);

    }

    

    // PART 1 - output
    outputFile << "PART 1:" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N - 1; j++) {
            outputFile << arr1[i][j] << " ";
        }
        outputFile << arr1[i][N - 1];
        outputFile << endl;
    }
    outputFile << endl;

    inputFile1.close();

    // For reading second input file
    ifstream inputFile2;
    inputFile2.open(argv[2]);
    string text2;

    // For declaring array size
    int M;
    getline(inputFile2, text2);
    M = stoi(text2);

    // Array declaration
    int** arr2;
    arr2 = new int* [M];

    for (int i = 0; i < M; i++) {
        arr2[i] = new int[M];
    }

    int indexPart2 = 1; // first line of file is array size

    // Final point
    int totalPoint = 0;

    int valuePart2, xIndPart2, yIndPart2;
    vector<int> valuesPart2;
    vector<int> xIndicesPart2;
    vector<int> yIndicesPart2;

    while (getline(inputFile2, text2)) {

        stringstream ssPart2(text2);

        if (indexPart2 <= M) {

            for (int i = 0; i < M; i++) {
                ssPart2 >> valuePart2;
                valuesPart2.push_back(valuePart2);
                arr2[indexPart2 - 1][i] = valuesPart2[0];
                valuesPart2.pop_back();
            }
            indexPart2++;
        }
        else {
            
            ssPart2 >> xIndPart2 >> yIndPart2;

            xIndices.push_back(xIndPart2);
            yIndices.push_back(yIndPart2);

            int part2X, part2Y;
            part2X = xIndices[0];
            part2Y = yIndices[0];

            xIndices.pop_back();
            yIndices.pop_back();

            processPart2(arr2, part2X, part2Y, M, totalPoint);

            if (arr2[part2X][part2Y] != 0) {
                totalPoint += arr2[part2X][part2Y];
            }
            arr2[part2X][part2Y] = 0;
        }
    }

    // PART 2 - output
    outputFile << "PART 2:" << endl;

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M - 1; j++) {
            outputFile << arr2[i][j] << " ";
        }
        outputFile << arr2[i][M - 1];
        outputFile << endl;
    }

    outputFile << "Final Point: " << totalPoint << "p";

    inputFile2.close();
}