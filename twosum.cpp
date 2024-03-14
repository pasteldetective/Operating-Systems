//Jackie Yee
// Dr. D'Alotto
// CSCI 451
// twosum.cpp
/*
Program reads a file of num and adds each number until the nested loop is finished.
add the num in the following manner: (1st + 2nd), (1st + 3rd), ...,(1st + nth),...,(2nd + 3rd ), 
...,(2nd + 4th),...,(2nd + nth),...,(3rd + 4th),...,(n-1)th + nth)
Afterwards it provides the total cpu runtime.
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>


int ack(int x, int y) 
{
    if (x == 0) 
    {
        return y + 1;
    } 
    else if (y == 0) 
    {
        return ack(x - 1, 1);
    } 
    else 
    {
        return ack(x - 1, ack(x, y - 1));
    }
}

int main() 
{
    std::ifstream inputFile("numList.txt"); // ifstream object inputFile reads from file selected numList.txt
    if (!inputFile) 
    {
        std::cerr << "Error, file does not exist or cannot be opened." << std::endl;
        return 1;
    }    

    /*
    instantiated variables
    */
    std::vector<int> num;
    int tempNum;
    
    /*
    reads num from inputFile and sets to tempNum
    adds to vector num
    */
    while (inputFile >> tempNum) 
    {
        num.push_back(tempNum);
    }
    
    /*
    set n to size of vector nums, for nested loop iteration
    */
    int n = num.size();

    /*
    set clock
    */
    double x,y,runtime;
    x = clock();// clock x 

    /*
    nested loop for iteration that adds num until loop ends
   (1st + 2nd), (1st + 3rd), ...,(1st + nth),...,(2nd + 3rd ), 
    ...,(2nd + 4th),...,(2nd + nth),...,(3rd + 4th),...,(n-1)th + nth) 
    */
    for (int i = 0; i < n; i++) 
    {
        for (int j = i + 1; j < n; j++) 
        {
            std::cout << num[i] << " + " << num[j] << " = " << num[i] + num[j] << std::endl;
        }
        std::cout << i << " " << "iteration" << std::endl; //might add runtime to CPU 
    }

    y =clock(); //clock y later
    runtime = (y - x)/CLOCKS_PER_SEC; //estimated runtime for CPU

    printf("\n\n\tThe execution time was: %.10lf", runtime); //measures CPU time by program
    printf("\n\n");

    inputFile.close();

    return 0;
}
