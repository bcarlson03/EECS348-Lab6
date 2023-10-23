#include <iostream>
#include <fstream>
#include <iomanip>

//Sets the maximum size of the matrix to a constant of 100 as stated in the assignment.
const int maxSize = 100;

//Function prototypes:
void addMatrices(int matrix1[maxSize][maxSize], int matrix2[maxSize][maxSize], int result[maxSize][maxSize], int size);
void subtractMatrices(int matrix1[maxSize][maxSize], int matrix2[maxSize][maxSize], int result[maxSize][maxSize], int size);
void multiplyMatrices(int matrix1[maxSize][maxSize], int matrix2[maxSize][maxSize], int result[maxSize][maxSize], int size);
void readMatrixFromFile(int matrix1[maxSize][maxSize], int matrix2[maxSize][maxSize], int &size, const std::string &filename);
void printMatrix(int matrix1[maxSize][maxSize], int size);

int main()
{
    //Initializes the matrices and sets size as 0 by default.
    int matrix1[maxSize][maxSize];
    int matrix2[maxSize][maxSize];
    int result[maxSize][maxSize];
    int size = 0;

    //Prints my name and the Lab number formatted like the sample output.
    std::cout << "Blake Carlson" << std::endl;
    std::cout << "Lab #6 Matrix manipulation" << std::endl;

    //Skips a line before printing the matrix A information.
    std::cout << " " << std::endl;

    //Reads the matrix data from the file using the readMatrixFromFile function. 
    readMatrixFromFile(matrix1, matrix2, size, "matrix_input.txt");

    //Prints the header for matrix A, then matrix A itself by using the printMatrix function. Then skips a line before printing the info for matrix B
    std::cout << "Matrix A:" << std::endl;
    printMatrix(matrix1, size);
    std::cout << " " << std::endl;

    //Prints the header for matrix B, then matrix B itself by using the printMatrix function. Then skips a line before printing the sum info for formatting.
    std::cout << "Matrix B:" << std::endl;
    printMatrix(matrix2, size);
    std::cout << " " << std::endl;

    // Call matrix operations as needed.
    addMatrices(matrix1, matrix2, result, size);

    //Prints the header for the sum of matrix A and matrix B.
    std::cout << "Matrix Sum (A+B):" << std::endl;
    printMatrix(result, size);
    std::cout << " " << std::endl;

    //Multiplies matrix A and matrix B.
    multiplyMatrices(matrix1, matrix2, result, size);

    //Prints the header for the product of matrix A and matrix B, then the product, and skips a line for formatting.
    std::cout << "Matrix Product (A*B):" << std::endl;
    printMatrix(result, size);
    std::cout << " " << std::endl;

    //Subtracts matrix B from matrix A.
    subtractMatrices(matrix1, matrix2, result, size);
    
    //Prints the header for the difference of matrix A and matrix B, then the difference, and skips a line for formatting.
    std::cout << "Matrix Difference (A-B):" << std::endl;
    printMatrix(result, size);
    std::cout << " " << std::endl;

    return 0;
}

//The function that takes two matrices and changes the result matrix to A + B.
void addMatrices(int matrix1[maxSize][maxSize], int matrix2[maxSize][maxSize], int result[maxSize][maxSize], int size)
{
    //A nested for loop goes through each i, j position in the matrix and adds the corresponding numbers in the same position from matrix A and B.
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }
}

//Function that takes two matrices and sets the result matrix to the result of matrix A - B.
void subtractMatrices(int matrix1[maxSize][maxSize], int matrix2[maxSize][maxSize], int result[maxSize][maxSize], int size)
{
    //A nested for loop takes the i, j values in A and B, subtracts the B value from the A value, and sets it to the corresponding i,j position in the result matrix.
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result[i][j] = matrix1[i][j] - matrix2[i][j];
        }
    }
}

//The function that takes matrix A and B. It sets the result matrix to the result of matrix A * matrix B.
void multiplyMatrices(int matrix1[maxSize][maxSize], int matrix2[maxSize][maxSize], int result[maxSize][maxSize], int size)
{
    //A nested for loop goes through all the i,j combinations and performs the matrix multiplication.
    for (int i = 0; i < size; i++) 
    {
        for (int j = 0; j < size; j++) 
        {
            //Another for loop and variable k helps get the right numbers to perform the muliplication.
            //This is because as the numbers going left to right across matrix A need to be multiplied by the numbers going down the columns in matrix B.
            result[i][j] = 0;
            for (int k = 0; k < size; k++) 
            {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
}

void readMatrixFromFile(int matrix1[maxSize][maxSize], int matrix2[maxSize][maxSize], int &size, const std::string &filename)
{
    //Opens the .txt file. 
    std::ifstream MyFile(filename);
    //Prints an error if there is an error opening the file. 
    if (!MyFile) 
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        exit(1);
    }

    // Gets the size of the matrices from the first line of the file.
    MyFile >> size;

    // Creates the two matrices based on the data from the file.
    //A nested for loop traverses through the matrices in the text file and stores the numbers according to how they are in the text file.

    //Matrix1 is made first representing matrix A.
    for (int i = 0; i < size; i++) 
    {
        for (int j = 0; j < size; j++)
        {
            MyFile >> matrix1[i][j];
        }
    }

    //Matrix2 is made second representing matrix B.
    for (int i = 0; i < size; i++) 
    {
        for (int j = 0; j < size; j++) 
        {
            MyFile >> matrix2[i][j];
        }
    }
    //Closes the file after reading all the necessary information from it.
    MyFile.close();
}

//The printMatrix function which prints the matrix used as a parameter.
void printMatrix(int matrix1[maxSize][maxSize], int size)
{
    //Value to be used by the setw to make the formatting of the printed numbers consistent.
    //I chose 6 arbitrarily, as I wanted everything to be close enough together to look nice but something large enough where multiple digit numbers do not get messed up.
    //However, this means the formatting will be slightly off for numbers printed that are more than 6 digits.
    int width = 6;

    //This for loop traverses through each column in the matrix
    for(int i = 0; i < size; i++)
    {
        //This for loop traverses through each entry in a given row in a matrix
        for (int j = 0; j < size; j++)
        {
            //This prints the entry in the [i][j] position in the matrix and then adds a space before printing the next number in that row.
            //The setw(width) part makes the formatting consistent.
            std::cout << std::setw(width) << matrix1[i][j] << " ";
        }

        //Once all the numbers in the row has been printed, it skips a line before printng all the values in the next row.
        std::cout << " " << std::endl;
    }
}