#include <iostream>
#include <string>
#include <ctime>

extern "C" {
#include "../../Assignment__01/src/csr.h"
}

#include "../src/maxflowMincut.hpp"

// NOTE: Gradient Descent (the other half of this buddy task) is being
// implemented separately. Once "../src/gradientDescent.hpp" exists with
// read_gd_input() / gradient_descent(), #include it above, add a
// run_gradient_descent() helper (same shape as run_maxflow_mincut()
// below), and swap it in for the "not wired in yet" branch under
// choice == 1 in main(). Menu numbering (1 = Gradient Descent,
// 2 = Maxflow-Mincut) is already reserved so nothing else needs to move.

using namespace std;

static void run_maxflow_mincut(const string &file)
{
    mf_input input = read_maxflow_input(file);

    if (!input.valid)
    {
        cout << "Invalid Maxflow-Mincut input: " << input.error << "\n";
        return;
    }

    // CSR conversion - not timed. Reuses Assignment 1's helper directly
    // (no copy of the conversion code lives in this assignment).
    csr_graph csr = adjacency_list_to_csr(&input.graph);

    clock_t start = clock();
    mf_result result = maxflow_mincut(&csr, input.source, input.sink);
    clock_t end = clock();

    cout << "\nAlgorithm: Maxflow-Mincut\n";
    cout << "Source: " << input.source << "\n";
    cout << "Sink: " << input.sink << "\n";
    cout << "Maximum flow: " << result.max_flow << "\n";
    cout << "Minimum cut capacity: " << result.min_cut_capacity << "\n";

    cout << "Source side:";
    for (int v : result.source_side)
        cout << " " << v;
    cout << "\n";

    cout << "Sink side:";
    for (int v : result.sink_side)
        cout << " " << v;
    cout << "\n";

    cout << "Cut edges:\n";
    for (auto &e : result.cut_edges)
        cout << e.from << " " << e.to << " " << e.capacity << "\n";

    printf("Execution time: %.3f ms\n",
           1000.0 * (end - start) / CLOCKS_PER_SEC);

    free_csr_graph(&csr);
    free_adjacency_list(&input.graph);
}

int main()
{
    while (true)
    {
        cout << "\n==============================\n";
        cout << "   ASSIGNMENT 3 - BUDDY TASK\n";
        cout << "==============================\n";
        cout << "1. Gradient Descent\n";
        cout << "2. Maxflow-Mincut\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";

        int choice;
        cin >> choice;

        if (!cin)
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input.\n";
            continue;
        }

        if (choice == 3)
            break;

        if (choice == 1)
        {
            cout << "Gradient Descent is not wired in yet "
                    "(pending the other half of the pair's files).\n";
            continue;
        }

        if (choice != 2)
        {
            cout << "Invalid choice.\n";
            continue;
        }

        string file;
        cout << "Enter input file path: ";
        cin >> file;
        cout << "\n";

        run_maxflow_mincut(file);
    }

    cout << "Exiting...\n";
    return 0;
}
