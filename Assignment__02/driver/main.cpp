#include <iostream>
#include <string>
#include <vector>
#include <ctime>

extern "C" {
#include "../../Assignment__01/src/graph.h"
#include "../../Assignment__01/src/csr.h"
}

#include "../src/betweenness.hpp"
#include "../src/connectedComponents.hpp"
#include "../src/triangleCounting.hpp"

using namespace std;

int main()
{
    while (true)
    {
        cout << "\n==============================\n";
        cout << "      ASSIGNMENT 2 - GRAPH\n";
        cout << "==============================\n";
        cout << "1. Betweenness Centrality\n";
        cout << "2. Connected Components\n";
        cout << "3. Triangle Counting\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";

        int choice;
        cin >> choice;

        if (choice == 4)
            break;

        if (choice < 1 || choice > 3)
        {
            cout << "Invalid choice.\n";
            continue;
        }

        string file;
        cout << "Enter input file path: ";
        cin >> file;
        cout <<"\n";

        // Read graph
        adjacency_list graph =
            read_unweighted_graph(file.c_str());

        if (graph.V <= 0)
        {
            cout << "Failed to load graph.\n";
            continue;
        }

        // CSR conversion - not timed
        csr_graph csr =
            adjacency_list_to_csr(&graph);

        clock_t start = clock();

        switch (choice)
        {
            case 1:
            {
                vector<double> bc =
                    betweenness_centrality(&csr);

                clock_t end = clock();

                cout << "\nAlgorithm: Betweenness Centrality\n";
                cout << "Vertex Centrality\n";

                for (int i = 0; i < graph.V; i++)
                    printf("%d %.2f\n", i, bc[i]);

                printf("Execution time: %.3f ms\n",
                       1000.0 * (end - start) /
                       CLOCKS_PER_SEC);

                break;
            }

            case 2:
            {
                int components;

                vector<int> id =
                    connected_components(
                        &csr,
                        components);

                clock_t end = clock();

                cout << "\nAlgorithm: Connected Components\n";
                cout << "Number of components: "
                     << components << "\n";

                cout << "Vertex Component\n";

                for (int i = 0; i < graph.V; i++)
                    cout << i << " " << id[i] << "\n";

                printf("Execution time: %.3f ms\n",
                       1000.0 * (end - start) /
                       CLOCKS_PER_SEC);

                break;
            }

            case 3:
            {
                bool collect = (graph.V <= 100);

                triangleCount result =
                    triangle_counting(
                        &csr,
                        collect);

                clock_t end = clock();

                cout << "\nAlgorithm: Triangle Counting\n";
                cout << "Total triangles: "
                     << result.total << "\n";

                if (collect)
                {
                    cout << "Triangles found:\n";

                    for (auto &t : result.triangles)
                        cout << "(" << t[0] << ", "
                             << t[1] << ", "
                             << t[2] << ")\n";
                }

                printf("Execution time: %.3f ms\n",
                       1000.0 * (end - start) /
                       CLOCKS_PER_SEC);

                break;
            }
        }

        free_csr_graph(&csr);
        free_adjacency_list(&graph);
    }

    cout << "Exiting...\n";
    return 0;
}