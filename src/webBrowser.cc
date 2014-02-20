#define BUILDING_NODE_EXTENSION
#include <node.h>
#include "awesomium.h"

using namespace v8;

void InitAll(Handle<Object> exports) {
      MyObject::Init(exports);
}

NODE_MODULE(awesomium, InitAll)
