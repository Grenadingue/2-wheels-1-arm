#include <node.h>
#include <map>
#include <string>
#include <iostream>
#include "MainController.hpp"

void nodeLaunchAlgorithm(const v8::FunctionCallbackInfo<v8::Value> &args)
{
  MainController &main = *(new MainController);
  v8::Local<v8::Object> obj = args[0]->ToObject();
  v8::Local<v8::Array> property_names = obj->GetOwnPropertyNames();
  std::map<std::string, std::string> *parameters = new std::map<std::string, std::string>;

  for (unsigned int i = 0; i != property_names->Length(); ++i)
    {
      v8::Local<v8::Value> key = property_names->Get(i);
      v8::Local<v8::Value> value = obj->Get(key);

      if (key->IsString() && value->IsString())
	{
	  v8::String::Utf8Value utf8_key(key);
	  v8::String::Utf8Value utf8_value(value);
	  parameters->insert(std::pair<std::string, std::string>(*utf8_key, *utf8_value));
	}
      else
	{
	  std::cerr << "Invalid parameter at index " << i << std::endl;
	}
    }

  main(parameters);
}

void init(v8::Local<v8::Object> exports) {
  NODE_SET_METHOD(exports, "launchSimulation", nodeLaunchAlgorithm);
}

NODE_MODULE(algoGen, init)
