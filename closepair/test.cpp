#include <iostream>
#include <map>

using namespace std;

int main () {
    map<int, int> m;
    m.insert({1, 2});
    printf("%d\n", m[2]);
}