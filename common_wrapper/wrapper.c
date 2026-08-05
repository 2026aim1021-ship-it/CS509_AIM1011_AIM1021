#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int action;

    system("mkdir -p ../Assignment__01/outputs");

    while (1)
    {
        printf("........ CS509 Graph Algorithms Wrapper ........\n");
        printf("1. Compile\n");
        printf("2. Run BFS test\n");
        printf("3. Run DFS test\n");
        printf("4. Run SSSP test\n");
        printf("5. Run all tests\n");
        printf("0. Exit\n");
        printf("Select an option: ");
        scanf("%d", &action);

        if (action == 0)
        {
            return 0;
        }
        else if (action == 1)
        {
            system("gcc -Wall -Wextra -o ../Assignment__01/driver/main "
                   "../Assignment__01/driver/main.c "
                   "../Assignment__01/src/csr.c "
                   "../Assignment__01/src/bfs.c "
                   "../Assignment__01/src/dfs.c "
                   "../Assignment__01/src/sssp.c "
                   "../Assignment__01/src/graph.c");
        }
        else if (action == 2)
        {
            system("../Assignment__01/driver/main 1 ../Assignment__01/tests/bfs.txt | tee ../Assignment__01/outputs/bfs.out");
            system("../Assignment__01/driver/main 1 ../Assignment__01/tests/bfs2.txt | tee ../Assignment__01/outputs/bfs2.out");
        }
        else if (action == 3)
        {
            system("../Assignment__01/driver/main 2 ../Assignment__01/tests/dfs.txt | tee ../Assignment__01/outputs/dfs.out");
            system("../Assignment__01/driver/main 2 ../Assignment__01/tests/dfs2.txt | tee ../Assignment__01/outputs/dfs2.out");
        }
        else if (action == 4)
        {
            system("../Assignment__01/driver/main 3 ../Assignment__01/tests/sssp.txt | tee ../Assignment__01/outputs/sssp.out");
            system("../Assignment__01/driver/main 3 ../Assignment__01/tests/sssp2.txt | tee ../Assignment__01/outputs/sssp2.out");
        }
        else if (action == 5)
        {
            system("../Assignment__01/driver/main 1 ../Assignment__01/tests/bfs.txt | tee ../Assignment__01/outputs/bfs.out");
            system("../Assignment__01/driver/main 1 ../Assignment__01/tests/bfs2.txt | tee ../Assignment__01/outputs/bfs2.out");
            system("../Assignment__01/driver/main 2 ../Assignment__01/tests/dfs.txt | tee ../Assignment__01/outputs/dfs.out");
            system("../Assignment__01/driver/main 2 ../Assignment__01/tests/dfs2.txt | tee ../Assignment__01/outputs/dfs2.out");
            system("../Assignment__01/driver/main 3 ../Assignment__01/tests/sssp.txt | tee ../Assignment__01/outputs/sssp.out");
            system("../Assignment__01/driver/main 3 ../Assignment__01/tests/sssp2.txt | tee ../Assignment__01/outputs/sssp2.out");
        }
        else
        {
            printf("Invalid action\n");
        }
    }

    return 0;
}
