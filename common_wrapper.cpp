#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

int run_command(const string& cmd)
{
    return system(cmd.c_str());
}

int main(){
    while (true)
    {
        cout << "\n========================================\n";
        cout << "        GRAPH ASSIGNMENT WRAPPER\n";
        cout << "========================================\n";
        cout << "1. Evaluate Assignment 1\n";
        cout << "2. Evaluate Assignment 2\n";
        cout << "3. Evaluate Assignment 3\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";

        int assignment;
        cin >> assignment;

        if (!cin)
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input.\n";
            continue;
        }

        if (assignment == 4)
            break;

        if (assignment == 1)
        {
            cout << "\n--- Assignment 1 ---\n";
            cout << "1. BFS\n";
            cout << "2. DFS\n";
            cout << "3. SSSP\n";
            cout << "Enter algorithm: ";

            int algorithm;
            cin >> algorithm;

            if (algorithm < 1 || algorithm > 3)
            {
                cout << "Invalid algorithm.\n";
                continue;
            }

            string input;
            cout << "Enter input file path: ";
            cin >> input;

            // Compile Assignment 1.
            string compile =
                "gcc "
                "Assignment__01/driver/main.c "
                "Assignment__01/src/graph.c "
                "Assignment__01/src/csr.c "
                "Assignment__01/src/bfs.c "
                "Assignment__01/src/dfs.c "
                "Assignment__01/src/sssp.c "
                "-o Assignment__01/driver/main";

            if (run_command(compile) != 0)
            {
                cout << "\nAssignment 1 compilation failed.\n";
                continue;
            }

            string run =
                "Assignment__01/driver/main " +
                to_string(algorithm) + " \"" + input + "\"";

            run_command(run);
        }
        else if (assignment == 2)
        {
            cout << "\n--- Assignment 2 ---\n";

            // Compile Assignment 1 C sources as object files.
            string compile_c =
                "gcc -I Assignment__01/src -c "
                "Assignment__01/src/graph.c "
                "Assignment__01/src/csr.c "
                "Assignment__01/src/bfs.c "
                "Assignment__01/src/dfs.c "
                "-o /tmp/assignment1_graph.o";

            // The command above cannot create multiple .o files with one -o,
            // so use individual commands instead.
            string c1 =
                "gcc -I Assignment__01/src -c "
                "Assignment__01/src/graph.c "
                "-o /tmp/a1_graph.o";

            string c2 =
                "gcc -I Assignment__01/src -c "
                "Assignment__01/src/csr.c "
                "-o /tmp/a1_csr.o";

            string c3 =
                "gcc -I Assignment__01/src -c "
                "Assignment__01/src/bfs.c "
                "-o /tmp/a1_bfs.o";

            string c4 =
                "gcc -I Assignment__01/src -c "
                "Assignment__01/src/dfs.c "
                "-o /tmp/a1_dfs.o";

            if (run_command(c1) != 0 ||
                run_command(c2) != 0 ||
                run_command(c3) != 0 ||
                run_command(c4) != 0)
            {
                cout << "\nAssignment 1 dependency compilation failed.\n";
                continue;
            }

            // Assignment 2 driver + algorithms.
            string compile_cpp =
                "g++ -std=c++17 -I Assignment__01/src "
                "Assignment__02/driver/main.cpp "
                "Assignment__02/src/betweenness.cpp "
                "Assignment__02/src/connectedComponents.cpp "
                "Assignment__02/src/triangleCounting.cpp "
                "/tmp/a1_graph.o "
                "/tmp/a1_csr.o "
                "/tmp/a1_bfs.o "
                "/tmp/a1_dfs.o "
                "-o Assignment__02/driver/main";

            if (run_command(compile_cpp) != 0)
            {
                cout << "\nAssignment 2 compilation failed.\n";
                continue;
            }

            // Assignment 2 has its own interactive driver.
            run_command("Assignment__02/driver/main");
        }
        else if (assignment == 3){
            cout << "\n--- Assignment 3 ---\n";

            // Compile Assignment 1 C dependencies first.
            string c1 =
                "gcc -I Assignment__01/src -c "
                "Assignment__01/src/graph.c "
                "-o /tmp/a3_graph.o";

            string c2 =
                "gcc -I Assignment__01/src -c "
                "Assignment__01/src/csr.c "
                "-o /tmp/a3_csr.o";

            if (run_command(c1) != 0 ||
                run_command(c2) != 0)
            {
                cout << "\nAssignment 1 dependency compilation failed.\n";
                continue;
            }

            // Compile Assignment 3 driver + both buddy-task algorithms.
            string compile_a3 =
                "g++ -std=c++17 -I Assignment__01/src "
                "Assignment__03/driver/main.cpp "
                "Assignment__03/src/gradientDescent.cpp "
                "Assignment__03/src/maxflowMincut.cpp "
                "/tmp/a3_graph.o "
                "/tmp/a3_csr.o "
                "-o Assignment__03/driver/main";

            if (run_command(compile_a3) != 0)
            {
                cout << "\nAssignment 3 compilation failed.\n";
                continue;
            }

            run_command("Assignment__03/driver/main");
        }
        else
        {
            cout << "Invalid assignment choice.\n";
        }
    }

    cout << "\nWrapper exited.\n";
    return 0;
}