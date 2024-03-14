//Jackie Yee
// Dr. D'Alotto
// CSCI 451
// one.cpp
/*
Program reads a file of num and adds each number until the nested loop is finished
add the num in the following manner: (1st + 2nd), (1st + 3rd), ...,(1st + nth),...,(2nd + 3rd ), 
...,(2nd + 4th),...,(2nd + nth),...,(3rd + 4th),...,(n-1)th + nth) as a child process.
Then it runs the ackerman function as the parent process.
Afterwards it provides the total cpu runtime for both the child and parent process.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <unistd.h>

/*
ackerman function is a recursive function that grows fast
*/
unsigned long long int ackerman(unsigned long long int  x, unsigned long long int y) 
{
    if (x < 0 || y < 0) //error check when x or y is less than 0
    {
        std::cerr << "Bad input value" << std::endl; 
        return -1;
    }
    else if (x == 0) 
    {
        return y + 1;
    } 
    else if ((x > 0) && (y == 0)) 
    {
        return ackerman(x - 1, 1);
    } 
    else if ((x > 0) && (y > 0)) //recursive until x is equal to 0
    {
        return ackerman(x - 1, ackerman(x, y - 1));
    }
    else //do nothing
    {

    }
}

int main() 
{
    std::ifstream inputFile("num1.txt"); // ifstream object inputFile reads from file selected numList.txt
    if (!inputFile) 
    {
        std::cerr << "Error, file does not exist or cannot be opened." << std::endl;
        return 1;
    }

    //Fork a child process
    pid_t child_process = fork(); 

    if (child_process == -1) //does not fork
    {
        std::cerr << "Does not fork." << std::endl;
        return -1;
    }
    else if (child_process == 0) //will fork
    {

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

        printf("\n\n\tThe execution time for child process was: %.10lf", runtime); //measures CPU time by program
        printf("\n\n");
        inputFile.close(); 
        exit(0);  // exit child process

    }
    else 
    {

        // Parent process
        double parent_start = clock();

        int x2, y2; // values for ackerman
        std::cout << "Give an input for x2: " << std::endl; //user input
        std::cin >> x2;
        std::cout << "Give an input for y2: " << std::endl;
        std::cin >> y2;
        int result2 = ackerman(x2,y2);
        std::cout << result2 << std::endl;
        
        double parent_end = clock(); // clock the end
        double parent_runtime = (parent_end - parent_start)/CLOCKS_PER_SEC;
        
        printf("\n\n\tThe execution time for parent process was: %.10lf", parent_runtime); //measures CPU time by program
        printf("\n\n");
    }
    
    return 0;
}