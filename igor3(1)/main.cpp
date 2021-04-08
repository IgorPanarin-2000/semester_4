#include <cassert>
#include <string>
#include <map>
#include <vector>
#include "Creator.h"
#include "AutoTest.h"

using namespace std;

int main() {
    AutoTest();
    ifstream in("input.txt");
    int n = 0;
    in >> n;
    vector<CString*> mas(n);
    map<std::string, Creator*> creator;
    creator["Hori"] = new CreatorString0();
    creator["Vert"] = new CreatorString1();
    std::string j;
    std::string s;
    std::string filename;
    for (auto i = mas.begin(); i != mas.end(); i++) {
        in >> j;
        in >> filename;
        getline(in,s);
        std::string news = s.substr(1, s.size() - 1);
        *i = creator[j]->create(news, filename);
    }
    for (auto i = mas.begin(); i != mas.end(); i++) {
        (*i)->output();
        delete *i;
    }
    for (auto& i : creator) {
        delete i.second;
    }
    mas.clear();
}
