#include <iostream>
#include <stdio.h>
#include <string.h>

#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

int main()
{

    //container initialization
    std::vector<int> numbers;
    std::string line;
    int lineNumbers = 0;
    int linesCount = 0;
    ifstream inputFile("IslandMap");

    if (inputFile.good()) {

        int current_number = 0;

        //read the file
        while(std::getline(inputFile, line))
        //while(inputFile >> current_number)
        {
            std::stringstream linestream(line);
            lineNumbers = 0;

            while(linestream >> current_number) {

                //container fill in
                numbers.push_back(current_number);
                lineNumbers++;
            }

            linesCount++;
        }
        inputFile.close();

        //print the file contents
        cout << endl;
        cout << "Lines in file: " << linesCount << endl;
        cout << endl;
        cout << "Numbers per line in file: " << lineNumbers << endl;

        for (int count = 0; count < numbers.size(); count++) {

            if (count % lineNumbers != 0) {

                cout << numbers[count] << " ";

            } else {

                cout << endl;
                cout << numbers[count] << " ";
            }

        }

        cout << endl;
        cout << endl;

        //calc islands
        int islandCount = 0;
        int currentLine = 0;
        int previousLine = 0;

        for (int count = 0; count < numbers.size(); count++) {

            if (count % lineNumbers == 0) {

                currentLine++;

            }

            if (numbers[count] == 1) {

                //cout << count << " " << currentLine << " " << previousLine << " s ";

                if ((count > 0) && (numbers[count - 1] == 0) && (currentLine == previousLine)) {

                    if (count > lineNumbers) {

                        if (numbers[count - lineNumbers] == 0) {

                            if ((count + lineNumbers) < numbers.size()) {

                                if (numbers[count + lineNumbers] == 0) {

                                    //cout << " islandCount increase on: " << count << " i ";
                                    islandCount++;

                                }

                            } else {

                                //cout << " islandCount increase on: " << count << " i ";
                                islandCount++;

                            }
                        }

                    } else {

                        if ((count + lineNumbers) < numbers.size()) {

                            if (numbers[count + lineNumbers] == 0) {

                                //cout << " islandCount increase on: " << count << " i ";
                                islandCount++;

                            }

                        } else {

                            //cout << " islandCount increase on: " << count << " i ";
                            islandCount++;

                        }

                    }

                } else if ((count > 0) && (currentLine != previousLine)) {


                    if (count > lineNumbers) {

                        if (numbers[count - lineNumbers] == 0) {

                            if ((count + lineNumbers) < numbers.size()) {

                                if (numbers[count + lineNumbers] == 0) {

                                    //cout << " islandCount increase on: " << count << " i ";
                                    islandCount++;

                                }

                            }

                        } else {

                            //cout << " islandCount increase on: " << count << " i ";
                            islandCount++;

                        }

                    } else {

                        //cout << " islandCount increase on: " << count << " i ";
                        islandCount++;
                    }

                } else {

                    if (count == 0) {

                        //cout << " islandCount increase on: " << count << " i ";
                        islandCount++;

                    }

                }

            }

            if (count % lineNumbers == 0) {

                previousLine++;

            }

        }

        cout << "Number of islands: " << islandCount << endl;
        cout << endl;


    } else {

        cout << "Error!";

    }

    return 0;
}
