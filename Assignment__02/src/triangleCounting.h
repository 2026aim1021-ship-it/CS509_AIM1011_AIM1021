#ifndef TRIANGLE_COUNTING_H
#define TRIANGLE_COUNTING_H

#include "csr_weighted.h"
#include <vector>
#include <array>

using namespace std;

struct triangleCount{
    long long total = 0;
    vector<array<int,3>> triangles; // only populated when asked for
};

triangleCount triangle_counting(csr_graph *graph, bool collect_triangles);

#endif
