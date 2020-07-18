#include <stdio.h>
#include <algorithms.hpp>
#include <vector>
#include<bits/stdc++.h> 

vector<vector<int>> solution_final;
int contador = 1;

vector<vector<int>> algorithms::generar(int row1, int col1, vector<vector<int>> solution) const{
    for(unsigned int i=0; i<row1; i++){
        vector<int> v1; 
        for(unsigned int j=0; j<col1; j++){
            v1.push_back(0);
        }
        solution_final.push_back(v1);
        solution.push_back(v1); 
    }
    return solution;
}

//function to print the solution matrix
std::string algorithms::ruta_backtracking() const{
    vector<vector<int>> ordenar_backtracking;
    int a = int(solution_final.size());
    int b = int(solution_final[0].size());
    for(unsigned int i=0; i<a; i++){ 
        for(unsigned int j=0; j<b; j++){
            if(solution_final[i][j]!=0){
                vector<int> v1;
                v1.push_back(solution_final[i][j]);
                v1.push_back(i);
                v1.push_back(j);
                ordenar_backtracking.push_back(v1);
            }
        }
    }
    sort(ordenar_backtracking.begin(), ordenar_backtracking.end());

    std::string ruta_a_seguir = "";

    for(unsigned int i=0; i<ordenar_backtracking.size(); i++){
        for(unsigned int j=1; j<ordenar_backtracking[0].size(); j++){
            if (j==1){
                ruta_a_seguir += to_string(ordenar_backtracking[i][j]); 
                ruta_a_seguir += ","; 
            }else{
                ruta_a_seguir += to_string(ordenar_backtracking[i][j]); 
            } 
        }
        ruta_a_seguir += "-"; 
    }

    return ruta_a_seguir;
}

//function to solve the maze
//using backtracking
int algorithms::algoritmo_backtracking(int r, int c, int x_end, int y_end, vector<vector<int>> mapa, vector<vector<int>> solution) const{

    if (solution.size()==0){ 
        solution = generar(int(mapa.size()), int(mapa[0].size()), solution);
    }
    //if destination is reached, maze is solved
    //destination is the last cell(maze[SIZE-1][SIZE-1])
    if((r==y_end) && (c==x_end))
    {
        solution[r][c] = 1;
        solution_final[r][c] = contador;
        contador +=1;
        return 1;
    }
    //checking if we can visit in this cell or not
    //the indices of the cell must be in (0,SIZE-1)
    //and solution[r][c] == 0 is making sure that the cell is not already visited
    //maze[r][c] == 0 is making sure that the cell is not blocked
    if(r>=0 && c>=0 && r<mapa.size() && c<mapa[0].size() && solution[r][c] == 0 && mapa[r][c] == 0)
    {
        //if safe to visit then visit the cell
        solution[r][c] = 1;
        solution_final[r][c] = contador;
        contador +=1;
        //going down
        if(algoritmo_backtracking(r+1, c, x_end, y_end, mapa, solution))
            return 1;
        //going right
        if(algoritmo_backtracking(r, c+1, x_end, y_end, mapa, solution))
            return 1;
        //going up
        if(algoritmo_backtracking(r-1, c, x_end, y_end, mapa, solution))
            return 1;
        //going left
        if(algoritmo_backtracking(r, c-1, x_end, y_end, mapa, solution))
            return 1;
        //backtracking
        solution[r][c] = 0;
        solution_final[r][c] = 0;
        contador -=1;
        return 0;
    }
    return 0;

}