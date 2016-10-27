#include <node.h>
#include <map>
#include <string>
#include <iostream>

using namespace v8;

void Method(const FunctionCallbackInfo<Value>& args) {
  Local<Object> obj = args[0]->ToObject();
  Local<Array> property_names = obj->GetOwnPropertyNames();
  std::map<std::string, std::string> params;

  for (unsigned int i = 0; i < property_names->Length(); ++i) {
    Local<Value> key = property_names->Get(i);
    Local<Value> value = obj->Get(key);
    if (key->IsString() && value->IsString()) {
      String::Utf8Value utf8_key(key);
      String::Utf8Value utf8_value(value);
      params.insert(std::pair<std::string, std::string>(*utf8_key, *utf8_value));
    } else {
      // Throw an error or something
    }
  }
  std::cout << "Backup location: " << params["backupFile"] << "\n";
}

void init(Local<Object> exports) {
  NODE_SET_METHOD(exports, "launchSimulation", Method);
}

NODE_MODULE(algoGen, init)
