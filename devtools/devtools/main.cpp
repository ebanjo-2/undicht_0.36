#include <iostream>
#include <dev_tools.h>

using namespace std;
using namespace undicht;

// this project can be used to develop new code for the undicht engine

int main() {


    DevTools::createCoreClass("test/", "FrameBuffer", "graphics");
    DevTools::createCoreImplClass("test/", "FrameBuffer", "graphics", "gl33");


    return 0;
}
