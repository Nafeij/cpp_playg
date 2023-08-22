#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
using std::vector;

template<typename T>
vector<T> getRandPerm(vector<T> names)
{
    vector<T> prefs = names;
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(prefs.begin(), prefs.end(), g);
    return prefs;
}