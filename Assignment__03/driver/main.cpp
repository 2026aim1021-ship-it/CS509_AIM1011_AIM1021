#include <iostream>
#include <string>
#include <ctime>

extern "C" {
#include "../../Assignment__01/src/csr.h"
}

#include "../src/maxflowMincut.hpp"

#include <vector>
#include <iomanip>

bool read_gd_input(const std::string &path,
                   int &degree,
                   std::vector<double> &coefficients,
                   double &initial_x,
                   double &learning_rate,
                   double &tolerance,
                   int &max_iterations,
                   std::string &error);

void gradient_descent(const std::vector<double> &coefficients,
                      double initial_x,
                      double learning_rate,
                      double tolerance,
                      int max_iterations,
                      double &final_x,
                      double &final_f,
                      int &iterations,
                      bool &converged);

using namespace std;

static void run_gradient_descent(const string &file)
{
    int degree;
    vector<double> coefficients;
    double initial_x;
    double learning_rate;
    double tolerance;
    int max_iterations;
    string error;

    if (!read_gd_input(
            file,
            degree,
            coefficients,
            initial_x,
            learning_rate,
            tolerance,
            max_iterations,
            error))
    {
        cout << "Invalid Gradient Descent input: "
             << error << "\n";
        return;
    }

    double final_x;
    double final_f;
    int iterations;
    bool converged;

    clock_t start = clock();

    gradient_descent(
        coefficients,
        initial_x,
        learning_rate,
        tolerance,
        max_iterations,
        final_x,
        final_f,
        iterations,
        converged);

    clock_t end = clock();

    cout << "\nAlgorithm: Gradient Descent\n";
    cout << "Degree: " << degree << "\n";

    cout << fixed << setprecision(10);

    cout << "Final x: " << final_x << "\n";
    cout << "Final f(x): " << final_f << "\n";
    cout << "Iterations: " << iterations << "\n";
    cout << "Converged: "
         << (converged ? "true" : "false") << "\n";

    printf("Execution time: %.3f ms\n",
           1000.0 * (end - start) / CLOCKS_PER_SEC);
}

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

        if (choice == 1){
            string file;

            cout << "Enter input file path: ";
            cin >> file;
            cout << "\n";

            run_gradient_descent(file);
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
