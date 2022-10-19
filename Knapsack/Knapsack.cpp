#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <math.h>
using namespace std; 

//the problem now is that the capacity is too large 
//the vector couldn't take number like that 104,723,596
//maybe we should split it in half
void knapSack(int W, vector<int> wt1, vector<int> val1, int n, string filename) {
    int i, w;
    vector<int> prev_b1(W + 1);
    vector<int> curr_b1(W + 1);

    vector<int> temp(n + 1);
    map<int, vector<int> ()> prev_t2;
   
    // we create a taken table for both the veectors
    vector<vector<bool>> prev_t1(W + 1, vector<bool>(n + 1));
    vector<vector<bool>> curr_t1(W + 1, vector<bool>(n + 1));
    // Build table K[][] in bottom up manner
    for (int i = 0; i <= n; i++)
    {
        for (w = 0; w <= W ; w+= 25)
        {
            if (i == 0 || w == 0) {
                curr_b1[w] = 0;
            }
            else if (wt1[i-1] <= w) {
                int temp = val1[i-1] + 
                    prev_b1[w-wt1[i-1]];
                if (temp > prev_b1[w]) {
                    curr_b1[w] = temp;
                    curr_t1[w] = prev_t1[w - wt1[i - 1]];
                    curr_t1[w][i] = true;
                }
                else {
                    curr_b1[w] = prev_b1[w];
                    curr_t1[w] = prev_t1[w];
                }
            }
            else {
                curr_b1[w] = prev_b1[w];
                curr_t1[w] = prev_t1[w];
            }
        }
        if (i != n) {
            prev_b1 = curr_b1;
            prev_t1 = curr_t1;
        }
    }
    ofstream output(filename + "_output");
    output << curr_b1[W] << endl;
    for (int i = 1; i <= n; i++) {
        output << curr_t1[W][i] << " ";
    }
    output.close();
}

int main()
{
    //Reading the input file
    string filename;
    cout << "Please Enter the File Name: "; 
    cin >> filename;
    ifstream infile;
    infile.open(filename);
    if (!infile.is_open()) {
        cout << "Can't open this file!" << endl << endl;
        return 1;
    }
    //Save the values that we need from the input file
    //First line is numbers of item and weight capacity
    int cap, weight, i;
    if (infile >> i) {
        cap = i;
        infile >> i;
        weight = i;
    }
    //now read the items and weights in the file
    vector<int> objects1;
    vector<int> weights1;
    while (infile >> i) {
            objects1.push_back(i);
            infile >> i;
            weights1.push_back(i);
       
    }
    infile.close();
    //We now have all of the inputs correctly;
    //gonna try the dynamic programming algorithmn for this problem
    //this algorithmn requires a 2d vector that stores 
    //where DP[i][j]
    //i = number of the item
    //w = weights till capacity
    knapSack(weight, weights1, objects1, cap, filename);
    
}

