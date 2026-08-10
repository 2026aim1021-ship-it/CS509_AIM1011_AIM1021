#ifndef CSR_WEIGHTED_H
#define CSR_WEIGHTED_H

#include <vector>
using namespace std;

struct csr_graph{
    int V;
    int E;
    vector<int> row_ptr;
    vector<int> col_idx;
};

csr_graph buildCSR(int V, const vector<vector<int>> &adj);

#endif
