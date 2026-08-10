#include <cstdio>
#include <cstdlib>

// Single entry point covering both assignments: pick Assignment 1 or
// Assignment 2 first, then that assignment's own submenu (same actions
// as wrapper.c / wrapper2.cpp) runs in a loop until you back out to this
// top-level menu again.

static void assignment1_menu()
{
    int action;
    system("mkdir -p ../Assignment__01/outputs");

    while (1)
    {
        printf("\n---- Assignment 1: BFS / DFS / SSSP ----\n");
        printf("1. Compile\n");
        printf("2. Run BFS test\n");
        printf("3. Run DFS test\n");
        printf("4. Run SSSP test\n");
        printf("5. Run all tests\n");
        printf("0. Back\n");
        printf("Select an option: ");
        if (scanf("%d", &action) != 1) return;

        if (action == 0)
        {
            return;
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
}

static void assignment2_menu()
{
    int action;
    system("mkdir -p ../Assignment__02/outputs");

    while (1)
    {
        printf("\n---- Assignment 2: Triangle Counting ----\n");
        printf("1. Compile\n");
        printf("2. Run Triangle Counting tests\n");
        printf("0. Back\n");
        printf("Select an option: ");
        if (scanf("%d", &action) != 1) return;

        if (action == 0)
        {
            return;
        }
        else if (action == 1)
        {
            system("g++ -std=c++17 -O2 -o ../Assignment__02/driver/main "
                   "../Assignment__02/driver/main.cpp "
                   "../Assignment__02/src/csr_weighted.cpp "
                   "../Assignment__02/src/triangleCounting.cpp");
        }
        else if (action == 2)
        {
            system("../Assignment__02/driver/main ../Assignment__02/tests/tc_10.txt     | tee ../Assignment__02/outputs/tc_10.out");
            system("../Assignment__02/driver/main ../Assignment__02/tests/tc_100.txt    | tee ../Assignment__02/outputs/tc_100.out");
            system("../Assignment__02/driver/main ../Assignment__02/tests/tc_10000.txt  | tee ../Assignment__02/outputs/tc_10000.out");
            system("../Assignment__02/driver/main ../Assignment__02/tests/tc_50000.txt  | tee ../Assignment__02/outputs/tc_50000.out");
            system("../Assignment__02/driver/main ../Assignment__02/tests/tc_100000.txt | tee ../Assignment__02/outputs/tc_100000.out");
        }
        else
        {
            printf("Invalid action\n");
        }
    }
}

int main(void)
{
    int choice;

    while (1)
    {
        printf("\n========== CS509 Common Wrapper ==========\n");
        printf("1. Assignment 1\n");
        printf("2. Assignment 2\n");
        printf("0. Exit\n");
        printf("Select an option: ");
        if (scanf("%d", &choice) != 1) return 0;

        if (choice == 0)
        {
            return 0;
        }
        else if (choice == 1)
        {
            assignment1_menu();
        }
        else if (choice == 2)
        {
            assignment2_menu();
        }
        else
        {
            printf("Invalid option\n");
        }
    }

    return 0;
}
