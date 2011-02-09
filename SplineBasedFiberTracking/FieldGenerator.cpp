#include <iostream>
#include <fstream>

#include "FieldGenerator.h"

void FieldGenerator::generateFieldFile() {
    std::ofstream outputFile("inputField.txt");
    int x_axis = 10;
    int y_axis = 10;
    int z_axis = 10;
    outputFile << x_axis*y_axis*z_axis;

    for(int i = 0; i < y_axis; i++){
        for(int j = 0; j < x_axis; j++){
            for(int k = 0; k < z_axis; k++){
                outputFile << j << " " << i << " " << k;
                outputFile << " 1 0 0\n";
            }
        }
    }
    outputFile.close();
}