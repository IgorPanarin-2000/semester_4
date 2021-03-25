#pragma once

int AutoTest(){
    CString0 a("abc",nullptr);
    CString1 b("def",nullptr);
    CString1 c = a + b;
    CString0 d("hello world",nullptr);
    assert(strcmp(d,"hello world") == 0);
    assert(d.getSize() == 11);
    d = "world hello there";
    assert(strcmp(d,"world hello there") == 0);
    assert(d.getSize() == 17);
    assert(strcmp(c,"abcdef") == 0);
    assert(c.getSize() == 6);
    assert(strcmp(a,"abc") == 0);
    assert(a.getSize() == 3);
    assert(strcmp(b,"def") == 0);
    assert(b.getSize() == 3);
    return 0;
}
