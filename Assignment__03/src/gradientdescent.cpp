#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <cctype>
#include <cstdlib>

using namespace std;

namespace
{
    bool parse_double(const string &s, double &value)
    {
        if (s.empty())
            return false;

        char *end = nullptr;
        value = strtod(s.c_str(), &end);

        return end != s.c_str() && *end == '\0' && isfinite(value);
    }

    bool parse_int(const string &s, int &value)
    {
        if (s.empty())
            return false;

        char *end = nullptr;
        long long temp = strtoll(s.c_str(), &end, 10);

        if (end == s.c_str() || *end != '\0')
            return false;

        if (temp < 0 || temp > 1000000)
            return false;

        value = static_cast<int>(temp);
        return true;
    }

    bool read_key_value(ifstream &file, const string &expected_key,
                        string &value, string &error)
    {
        string line;
        if (!getline(file, line))
        {
            error = "Missing " + expected_key;
            return false;
        }

        string key;
        stringstream ss(line);
        ss >> key >> value;

        if (key != expected_key || value.empty())
        {
            error = "Invalid " + expected_key + " line";
            return false;
        }

        return true;
    }
}

bool read_gd_input(const string &path,
                   int &degree,
                   vector<double> &coefficients,
                   double &initial_x,
                   double &learning_rate,
                   double &tolerance,
                   int &max_iterations,
                   string &error)
{
    ifstream file(path);

    if (!file.is_open())
    {
        error = "Cannot open file " + path;
        return false;
    }

    string value;

    // DEGREE
    {
        string key;
        string line;
        if (!getline(file, line))
        {
            error = "Missing DEGREE";
            return false;
        }

        stringstream ss(line);
        ss >> key >> value;

        if (key != "DEGREE" || !parse_int(value, degree) || degree < 1)
        {
            error = "Invalid degree";
            return false;
        }
    }

    // COEFFICIENTS
    {
        string line;
        if (!getline(file, line))
        {
            error = "Missing COEFFICIENTS";
            return false;
        }

        string key;
        stringstream ss(line);
        ss >> key;

        if (key != "COEFFICIENTS")
        {
            error = "Invalid COEFFICIENTS line";
            return false;
        }

        coefficients.clear();
        string token;
        while (ss >> token)
        {
            double coefficient;
            if (!parse_double(token, coefficient))
            {
                error = "Invalid coefficient";
                return false;
            }
            coefficients.push_back(coefficient);
        }

        if (static_cast<int>(coefficients.size()) != degree + 1)
        {
            error = "Coefficient count must be d+1";
            return false;
        }
    }

    // INITIAL_X
    if (!read_key_value(file, "INITIAL_X", value, error) ||
        !parse_double(value, initial_x))
    {
        if (error.empty())
            error = "Invalid INITIAL_X";
        return false;
    }

    // LEARNING_RATE
    if (!read_key_value(file, "LEARNING_RATE", value, error) ||
        !parse_double(value, learning_rate) || learning_rate <= 0.0)
    {
        error = "Learning rate must be positive";
        return false;
    }

    // TOLERANCE
    if (!read_key_value(file, "TOLERANCE", value, error) ||
        !parse_double(value, tolerance) || tolerance <= 0.0)
    {
        error = "Tolerance must be positive";
        return false;
    }

    // MAX_ITERATIONS
    if (!read_key_value(file, "MAX_ITERATIONS", value, error) ||
        !parse_int(value, max_iterations) || max_iterations <= 0)
    {
        error = "MAX_ITERATIONS must be positive";
        return false;
    }

    return true;
}

// Evaluates f(x) = c0 + c1*x + ... + cd*x^d.
// Horner's rule avoids repeatedly calculating powers of x.
double evaluate_polynomial(const vector<double> &coefficients, double x)
{
    double result = 0.0;

    for (int i = static_cast<int>(coefficients.size()) - 1; i >= 0; --i)
        result = result * x + coefficients[i];

    return result;
}

// Evaluates f'(x) = c1 + 2*c2*x + ... + d*cd*x^(d-1).
// The derivative is evaluated using Horner's rule as well.
double evaluate_derivative(const vector<double> &coefficients, double x)
{
    int degree = static_cast<int>(coefficients.size()) - 1;

    if (degree == 0)
        return 0.0;

    double result = degree * coefficients[degree];

    for (int i = degree - 1; i >= 1; --i)
        result = result * x + i * coefficients[i];

    return result;
}

// Runs Gradient Descent. Only the algorithm itself should be timed by the
// driver, so input parsing and output are deliberately kept outside this
// function.
void gradient_descent(const vector<double> &coefficients,
                      double initial_x,
                      double learning_rate,
                      double tolerance,
                      int max_iterations,
                      double &final_x,
                      double &final_f,
                      int &iterations,
                      bool &converged)
{
    double x = initial_x;
    iterations = 0;
    converged = false;

    while (iterations < max_iterations)
    {
        double derivative = evaluate_derivative(coefficients, x);

        if (fabs(derivative) <= tolerance)
        {
            converged = true;
            break;
        }

        x -= learning_rate * derivative;
        ++iterations;

        // Guard against numerical overflow/non-finite values. This does not
        // change the required stopping rule; it simply prevents an invalid
        // floating-point state from continuing through all iterations.
        if (!isfinite(x))
            break;
    }

    final_x = x;
    final_f = evaluate_polynomial(coefficients, x);

    if (!converged && isfinite(x))
    {
        double derivative = evaluate_derivative(coefficients, x);
        if (fabs(derivative) <= tolerance)
            converged = true;
    }
}
