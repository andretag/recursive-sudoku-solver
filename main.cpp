//
//  main.c
//  SudokuSolver
//
//  Created by Andrea Tagliabue on 24/08/15.
//  Copyright (c) 2015 Andrea Tagliabue. All rights reserved.
//

#include <stdio.h>
#include </Users/Andrea/Documents/Progetti/SudokuSolver/SudokuSolver/mieliste.h>
#define N 9
#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>
#include <list>

typedef ListaDiElem Sudoku[N][N];

std::chrono::high_resolution_clock::time_point t1;

///////////////////////// FUNCTIONS ////////////////////

void CopyMatrix(int from[N][N], int to[N][N]){
    int i, j;
    for(i=0; i<N; i++){
        for(j=0; j<N; j++)
            to[i][j] = from[i][j];
    }
    return;
}

void PrintMatrix(int a[N][N]){
    int i, j;
    for(i=0; i<N; i++){
        for(j=0; j<N; j++)
            printf("%d ", a[i][j]);
    printf("\n");
    }
    return;

}

void UserInput(int a[N][N]){
    printf("Manual input mode selected\n");
    printf("Please input values followed by space; insert 0 if the cell is empty\n");
    int i, j, flag=0;
    
    //acquiring the sudoku through user input
    for(i=0; i<N; i++){
        for(j=0; j<N; j++){
            
            flag=0;
            
            do{
                fflush(stdin);
                scanf("%d", &a[i][j]);
                if(a[i][j]>=0 && a[i][j]<=N)
                    flag=1;
                else
                    printf("\nValue not allowed; please type a new value for cell [%d][%d]\n", i, j);
            }while(flag==0);
            
        }
        printf("\nline %d: ", i+1);
        for(j=0; j<N; j++){
            printf("%d ", a[i][j]);
        }
        printf("\n");
        
    }
    return;
    
}

void Acquire(Sudoku s){
    //variables
    int a_ultrahard[N][N] = {
        8, 2, 0, 0, 0, 0, 0, 0, 5,
        0, 9, 0, 0, 0, 6, 1, 0, 0,
        0, 0, 5, 0, 0, 7, 0, 3, 0,
        0, 8, 7, 0, 1, 5, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 2, 0, 0, 4, 0, 8,
        9, 0, 0, 4, 0, 0, 0, 0, 0,
        0, 3, 0, 0, 0, 2, 0, 0, 0,
        6, 0, 0, 0, 0, 0, 5, 8, 2,
    };
    int a_hard[N][N] = {
        8, 0, 0, 4, 0, 6, 0, 0, 7,
        0, 0, 0, 0, 0, 0, 4, 0, 0,
        0, 1, 0, 0, 0, 0, 6, 5, 0,
        5, 0, 9, 0, 3, 0, 7, 8, 0,
        0, 0, 0, 0, 7, 0, 0, 0, 0,
        0, 4, 8, 0, 2, 0, 1, 0, 3,
        0, 5, 2, 0, 0, 0, 0, 9, 0,
        0, 0, 1, 0, 0, 0, 0, 0, 0,
        3, 0, 0, 9, 0, 2, 0, 0, 5
    };
    int a_easy[N][N]= {
        5, 0, 4, 6, 0, 9, 7, 0, 1,
        0, 3, 0, 4, 0, 7, 0, 5, 0,
        0, 0, 9, 5, 0, 3, 4, 0, 0,
        8, 2, 0, 0, 0, 0, 0, 4, 7,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        3, 9, 0, 0, 0, 0, 0, 6, 8,
        0, 0, 3, 8, 0, 5, 2, 0, 0,
        0, 1, 0, 7, 0, 2, 0, 8, 0,
        2, 0, 8, 1, 0, 6, 9, 0, 5
    };
    
    int a_world_hardest[N][N] = {
        0, 0, 5, 3, 0, 0, 0, 0, 0,
        8, 0, 0, 0, 0, 0, 0, 2, 0,
        0, 7, 0, 0, 1, 0, 0, 5, 0,
        4, 0, 0, 0, 0, 5, 3, 0, 0,
        0, 1, 0, 0, 7, 0, 0, 0, 6,
        0, 0, 3, 2, 0, 0, 0, 8, 0,
        0, 6, 0, 5, 0, 0, 0, 0, 9,
        0, 0, 4, 0, 0, 0, 0, 3, 0,
        0, 0, 0, 0, 0, 9, 7, 0, 0,
    };
    
    int a[N][N];
    
    int i, j;
    char cheat;
    
    //acquiring sudoku and memorizing it into an int matrix
    printf("Please press 'return' to activate the manual imput mode\n");
    
    scanf("%c", &cheat);
    
    switch(cheat){
        case 'e': CopyMatrix(a_easy, a); break;
        case 'h': CopyMatrix(a_hard, a); break;
        case 'u': CopyMatrix(a_ultrahard, a); break;
        case 'w': CopyMatrix(a_world_hardest, a); break;
        default : UserInput(a); break;
    }
    
    //printing the input values from the int matrix
    printf("\nThe input values are:\n\n");
    PrintMatrix(a);
    
    //initializing the sudoku matrix, with each cell having a pointer equals to NULL
    for(i=0; i<N; i++)
        for(j=0; j<N; j++)
            s[i][j] = Inizializza();
    
    //adding values to the list in each s cell if the equivalent a cell is not empty
    for(i=0; i<N; i++)
        for(j=0; j<N; j++){
            if(a[i][j]!=0)
                s[i][j] = InsInTesta(s[i][j], a[i][j]);
        }
    
}

int CountUnique(Sudoku s){
    //variables
    int i, j, uniq=0;
    
    //counting the unique values
    for(i=0; i<N; i++)
        for(j=0; j<N; j++)
            if(Dimensione(s[i][j])==1)
                uniq++;
    //returning the int value
    return uniq;
}

int IsCompatibleRow(Sudoku s, int row, int n){
    int count=0, j;
    
    //fisso la riga row, valuto nelle varie colonne j
    //la compatibilità di un valore con una riga è data tenedo solo conto dei valori già fissati
    //(rappresentati da liste di lunghezza unitaria)
    for(j=0; j<N; j++)
        if(Dimensione(s[row][j])==1)
            count += VerificaPresenza(s[row][j], n);
    
    return !count;
    
}

int IsCompatibleColumn(Sudoku s, int col, int n){
    int count=0, i;
    
    //fisso la colonna col, valuto nelle varie righe i
    //la compatibilità di un valore con una colonna è data tenedo solo conto dei valori già fissati
    //(rappresentati da liste di lunghezza unitaria)
    for(i=0; i<N; i++)
        if(Dimensione(s[i][col])==1)
            count += VerificaPresenza(s[i][col], n);
    
    return !count;
}

int IsCompatibleSquare(Sudoku s, int row, int col, int val){
    int from_i, to_i, from_j = 0, to_j = 0;
    int count=0, i, j;
    
    //definig the row values that must be considered
    if(row < (N/3)){
        from_i = 0;
        to_i = (N/3)-1;
    } else if(row>((N/3)-1) && row<(2*N/3)){
        from_i = N/3;
        to_i = (2*N/3)-1;
    }else if(row>(2*N/3)-1){
        from_i = 2*N/3;
        to_i = N-1;
    }
    
    //defining the column values that must be considered
    if(col < 3){
        from_j = 0;
        to_j = 2;
    } else if(col>2 && col<6){
        from_j = 3;
        to_j = 5;
    }else if(col>5){
        from_j = 6;
        to_j = 8;
    }
    
    //verifying if the given value val belongs to the submatrix defined
    for(i=from_i; i<=to_i; i++){
        for(j=from_j; j<=to_j; j++){
            if(Dimensione(s[i][j])==1)
                count += VerificaPresenza(s[i][j], val);
        }
    }
    return !count;
}

int Update(Sudoku s){
    //variables
    int i, j, val;
    int compatible_raw, compatible_column, compatible_square;
    
    //for each cell
    for(i=0; i<N; i++){
        for(j=0; j<N; j++){
            
            //verifying that the cell has not a definitive value
            if(Dimensione(s[i][j])!=1){
                
                //Rimuovo gli elementi che non sono più compatibili
                s[i][j] = DistruggiLista(s[i][j]);
                
                //evaluating compatible values from 1 to 9
                for(val=1; val<(N+1); val++){
                    
                    compatible_raw    = IsCompatibleRow(s, i, val);
                    compatible_column = IsCompatibleColumn(s, j, val);
                    compatible_square = IsCompatibleSquare(s, i, j, val);
                    
                    if(compatible_raw && compatible_column && compatible_square)
                        if(VerificaPresenza(s[i][j], val)==0)
                            s[i][j] = InsInOrdRic(s[i][j], val);
                    
                }
                
                //if no compatible value is found, return error
                if(s[i][j]==NULL)
                    return 0;
            }
        }
    }
    return 1;
}

void PrintSudoku(Sudoku s){
    int i, j;
    for(i=0; i<N; i++){
        for(j=0; j<N; j++){
            if(s[i][j] == NULL || Dimensione(s[i][j]) > 1)
                printf("0 ");
            else
                printf("%d ", s[i][j]->info);
        }
        printf("\n");
    }
}

void PrintSudokuDebug(Sudoku s){
    int i, j;
    
    for(i=0; i<N; i++)
        for(j=0; j<N; j++){
            printf("\ns[%d][%d]:", i, j);
            Stampa(s[i][j]);
        }
    
    return;
}

void BaseSolver(Sudoku s);

void CopySudoku(Sudoku from, Sudoku to){
    int i, j;
    for(i=0; i<N; i++){
        for(j=0; j<N; j++){
            to[i][j] = Copia(from[i][j]);
        }
    }
}

void DestroySudoku(Sudoku s){
    int i, j;
    for(i=0; i<N; i++){
        for(j=0; j<N; j++){
            s[i][j] = DistruggiLista(s[i][j]);
        }
    }
}

void BackTracking(Sudoku s){
    
    //variables
    int i, j, flag=0;
    ListaDiElem aux = NULL;
    Sudoku sCopy;
    
    PrintSudokuDebug(s);
    
    //creating a copy of s called sCopy. It will be use to restore the sudoku each time that backtracking function has called the BaseSolver function.
    CopySudoku(s, sCopy);
    
    //looking for the first cell of s with multiple elements ("Dimensione > 1")
    for(i=0; i<N && flag==0; i++){
        for(j=0; j<N && flag==0; j++){
    
            if(Dimensione(s[i][j])>1){
                flag = 1;
                
                
                //Now, the new sCopy will be used to created a modified version of s with an increased UniqueValue
                
                    
                //Evaluting the existance of a solution calling the BaseSolver with different values attached to sCopy[i][j]
                aux = s[i][j];
                while(aux != NULL){
                    
                    //emptying the content of sCopy[i][j]
                    sCopy[i][j] = DistruggiLista(sCopy[i][j]);
                    
                    printf("\nBackTracking: trying to solve choosing the value %d for the cell [%d][%d]", aux->info, i, j);
                    sCopy[i][j] = InsInTesta(sCopy[i][j], aux->info);
                    
                    //Stampa(sCopy[i][j]);
                    //PrintSudokuDebug(sCopy);
                    
                    //Calling BaseSolver
                    BaseSolver(sCopy);
                    
                    DestroySudoku(sCopy);
                    
                    CopySudoku(s, sCopy);
                    aux = aux->prox;
                    
                }
                
            }
        }
    }
    
    return;
}

void BaseSolver(Sudoku s){
    
    int prev, curr;
    int SuccessfullyUpdated = 0;
    
    printf("\n\nCalling \"BaseSolver\" function");
    
    prev = CountUnique(s);
    printf("\nUnique Values: %d", prev);
    if(prev == 0){
        printf("\nERR1 - CountUnique = 0 - suodku is empty");
        return;
    }

    SuccessfullyUpdated = Update(s);
    printf("\nUpdating Sudoku\n");
    if (SuccessfullyUpdated==0){
        printf("ERR2 - not successfully updated - a solution cannot be found\n");
        return;
    }
 
    curr = CountUnique(s);
    printf("New Unique Values: %d\n", curr);
    PrintSudoku(s);
    
    if(curr == N*N){
        printf("\n\nA solution has been found\n");
        PrintSudoku(s);
        
        std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
        
        std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
        
        std::cout << "It took me " << time_span.count() << " seconds.";
        std::cout << std::endl;
        exit(-1);
        return;
    }
    if(curr > prev)
        return BaseSolver(s);
    if(curr == prev){
        printf("\n\nCalling \"BackTracking\" function");
        return BackTracking(s);
    }
    
    else{
        printf("ERR3 - curr < prev");
        return;
    }
}





int main(int argc, const char * argv[]) {
    
    std::list<int>andrea;
    
    using namespace std::chrono;
    
    Sudoku s;
    
    Acquire(s);
    
    t1 = std::chrono::high_resolution_clock::now();
    
    BaseSolver(s);
    
    return 0;
}
