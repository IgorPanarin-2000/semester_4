#include <cassert>
#include "CString1.h"
#include "CString0.h"
#include "AutoTest.h"

using namespace std;

int main() {
    AutoTest();
    ifstream in("input.txt");
    int n = 0;
    in >> n;
    CString** arr = new CString * [n];
    int j = 0;
    std::string s;
    std::string filename;
    for (int i = 0; i < n; i++) {
        in >> j;
        in >> filename;
        getline(in,s);
        CString* a;
        if (j == 0) {
            a = new CString0(s.c_str(),filename.c_str());
        }
        else {
            a = new CString1(s.c_str(),filename.c_str());
        }
        arr[i] = a;
    }
    for (int i = 0; i < n; i++) {
        arr[i]->output();
    }
    for (int i = 0; i < n; i++) {
        delete arr[i];
    }
    delete[] arr;
}
