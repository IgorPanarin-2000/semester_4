#pragma once
#include <ctime>
#include <chrono>

int AutoTest(){
    CString0 a("abc");
    CString1 b("def");
    CString1 c = a + b;
    CString0 d = std::string("hello world");
    assert(strcmp(d,"hello world") == 0);
    assert(d.getSize() == 11);
    d = std::string("world hello there");
    assert(strcmp(d,"world hello there") == 0);
    assert(d.getSize() == 17);
    assert(strcmp(c,"abcdef") == 0);
    assert(c.getSize() == 6);
    assert(strcmp(a,"abc") == 0);
    assert(a.getSize() == 3);
    assert(strcmp(b,"def") == 0);
    assert(b.getSize() == 3);

    CString0 k;

    std::string str;

    srand(uint8_t(time(NULL)));

    for (int i = 0; i < 1e8; i++) {
        str.push_back(rand() % 256);
    }

    std::cout << str.size() << std::endl;

    k = str;

    std::cout << "Started" << std::endl;

    std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
    k += k;
    std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
    int elapsed_ms = static_cast<int>(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());
    std::cout << "Addition operator runtime is " << elapsed_ms << " ms\n";
    return 0;
}
