#pragma once

#include "http_request.h"

#include <string_view>
#include <map>
#include <array>

using namespace std;

static const size_t COUNT_METHOD = 5;
static const size_t COUNT_URI= 6;

class Stats {
public:
	Stats();
	void AddMethod(string_view method);
	void AddUri(string_view uri);
	const map<string_view, int>& GetMethodStats() const;
	const map<string_view, int>& GetUriStats() const;

private:
	inline static const array<string, COUNT_METHOD> methods = {"UNKNOWN", "DELETE", "POST", "PUT", "GET"};
	inline static const array<string, COUNT_URI> uris = {"unknown", "/help", "/basket", "/product", "/order", "/"};
	map<string_view, int> data_method;
	map<string_view, int> data_uri;
};

HttpRequest ParseRequest(string_view line);