#include <stdio.h>

int main() {  
  
    int n, m, i, j, k;  
    n = 5;                         // Number of processes  
    m = 3;                         // Number of resources

    int alloc[5][3] = {{0, 1, 0},  // Allocation Matrix  
                       {2, 0, 0},    
                       {3, 0, 2},    
                       {2, 1, 1},   
                       {0, 0, 2}};   
  
    int max[5][3] = {{7, 5, 3},  // MAX Matrix  
                     {3, 2, 2},    
                     {9, 0, 2},    
                     {2, 2, 2},    
                     {4, 3, 3}};   
  
    int avail[3] = {3, 3, 2}; // Available Resources  
  
    // array to store whether process has been checked
    int f[n]; 
    for (k = 0; k < n; k++) {  
        f[k] = 0;  
    }  

    // Need Matrix
    int need[n][m];  
    for (i = 0; i < n; i++) {  
        for (j = 0; j < m; j++)  
            need[i][j] = max[i][j] - alloc[i][j];  
    }  
  
    int ans[n], ind = 0;
    for (k = 0; k < 5; k++) {  
        for (i = 0; i < n; i++) {  
            if (f[i] == 0) {  
                int flag = 0;  
                for (j = 0; j < m; j++) {  
                    // if the process needs more than what's available, gets flagged
                    if (need[i][j] > avail[j]) {  
                        flag = 1;  
                        break;  
                    }  
                }

                // if not, gets added to sequence and updates Available Matrix
                if (flag == 0) {  
                    ans[ind++] = i;  
                    for (int y = 0; y < m; y++)  
                        avail[y] += alloc[i][y];  
                    f[i] = 1;  
                }  
            }  
        }  
    } 

    int flag = 1;  
    for (int i = 0; i < n; i++) {  
        // No safe sequence found
        if (f[i] == 0) {  
            flag = 0;  
            printf("This system is not safe from deadlock");  
            break;  
        }  
    }  

    if (flag == 1) {  
        printf("The following sequence is safe from deadlock:\n");  
        for (i = 0; i < n - 1; i++)  
            printf(" P%d ->", ans[i]);  
        printf(" P%d", ans[n - 1]); 
        printf("\n"); 
    }  
    
    return (0);  
}