#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;

int main(void){
    string line;
    ifstream in("model.obj");
    double data[100000][3];
    int triangle[2000][3];
    if (!in.is_open()){
        cout << "Error opening file" << endl;
        exit(1); 
    }  
    int count = 0;
    int index = 0;
    while (getline(in, line))  
    {  
        count++;
        if (line.empty())
            continue;
        if (line[0] == 'v' && line[1] == ' '){
            double temp;
            string tempstr;
            line = line.substr(line.find(" ") + 1);
            for (int i = 0; i < 3; i++){
                tempstr = line.substr(0, line.find(" "));
                data[count][i] = atof(tempstr.c_str());
                line = line.substr(line.find(" ") + 1);
            }
        }
        if (line[0] == 'f'){
            double temp;
            string tempstr;
            line = line.substr(line.find(" ") + 1);
            for (int i = 0; i < 3; i++){
                
                tempstr = line.substr(0, line.find("/"));
                triangle[index][i] = atof(tempstr.c_str());
                line = line.substr(line.find(" ") + 1);
            } 
            index += 1;
        }  
    }
    return 0;
}
