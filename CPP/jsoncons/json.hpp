// Copyright 2013 Daniel Parker
// Distributed under Boost license

#ifndef JSONCONS_JSON_HPP
#define JSONCONS_JSON_HPP

//#define NOMINMAX  // prevent issues with max() colliding with jsoncons
#undef max

#include "jsoncons/json1.hpp"
#include "jsoncons/json2.hpp"

namespace jsoncons {

typedef basic_json<char> json;
typedef basic_json<wchar_t> wjson;

}

#endif
