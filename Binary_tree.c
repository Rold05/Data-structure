#include <stdio.h>

#define MAXSIZE 100

char treeNodes[MAXSIZE] = {
    'G', 
    'D', 
    'I', 
    'B', 
    'F', 
    'H',
    'J', 
    'A', 
    'C', 
    'E', 
    'K'  
};

int numElements = 11;

void showTree() {
    for (int i = 0; i < numElements; i++) {

        printf("\nNode [%d]: %c", i, treeNodes[i]);

        int li = 2 * i + 1;
        int ri = 2 * i + 2;

        if (li < numElements)
            printf("\n   Left  -> [%d]: %c", li, treeNodes[li]);
        else
            printf("\n   Left  -> (none)");

        if (ri < numElements)
            printf("\n   Right -> [%d]: %c", ri, treeNodes[ri]);
        else
            printf("\n   Right -> (none)");
    }

    printf("\n");
}

int main() {

    printf("numElements = %d\n", numElements);

    showTree();

    return 0;
}

