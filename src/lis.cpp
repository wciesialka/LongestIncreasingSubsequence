/**
 * @file lis.cpp
 * @brief Solve the Longest-Increasing-Subsequence problem.
 * 
 * @author Willow Ciesialka
 * @date 2023-11-28
*/

#include <iostream>
#include <fstream>
#include <string>
#include <limits.h>

#define MAX_ARRAY_SIZE 256

int read_input(int* input){
    /**
     * @brief Get input and store it in input vector.
     * 
     * @param[in] input Vector to store inpiut values.
     * @return Size of the array. -1 if file could not be read.
    */
    std::ifstream in;
    // Your program should read input from a text file 
    // (one value per line; name the text file incseq.txt)
    in.open("incseq.txt");
    int size = 0;

    if(in.is_open()){
        std::string line;

        while(getline(in, line)){
            int value = std::stoi(line);
            input[size] = value;
            size++;
            if(size > MAX_ARRAY_SIZE){
                return -1;
            }
        }

        in.close();
        return size;
    }
    return -1;
}

int main(){
    int* input = new int[MAX_ARRAY_SIZE];
    int size = read_input(input);

    // Exit with -1 if file can't be read
    if(size == -1){
        std::cerr << "File could not be read, or was invalid." << std::endl;
        delete[] input;
        return 1; // EXIT_FAILURE
    } else if(size == 0){
        std::cerr << "File was not a list of integers." << std::endl;
        delete[] input;
        return 1;
    }

    // Print sequence for clarity.
    std::cout << "Sequence:" << std::endl;
    for(int i = 0; i < size; i++){
        std::cout << input[i] << " ";
    }
    std::cout << std::endl << std::endl;

    int* L = new int[size];
    L[0] = 1;
    
    // Generate L-table
    for(int i = 1; i < size; i++){
        // Find max predecessor
        int max_predecessor = 0;
        for(int j = i-1; j >= 0; j--){
            // First, check that it's a predecessor.
            if(input[j] < input[i]){
                // Then, check to see if it has a larger L-value
                if(L[j] > max_predecessor){
                    max_predecessor = L[j];
                }
            }
        }
        L[i] = max_predecessor + 1;
    }

    // Print the table and find the largest L-value
    std::cout << "L Table:" << std::endl;

    int longest_subsequence_length = 0;
    for(int i = 0; i < size; i++){
        std::cout << L[i] << " ";
        if(L[i] > longest_subsequence_length){
            longest_subsequence_length = L[i];
        }
    }
    std::cout << std::endl;
    std::cout << "Longest Increasing Subsequence Length: " << longest_subsequence_length << std::endl;

    delete[] input;
    delete[] L;
    return 0;
}

#undef MAX_ARRAY_SIZE