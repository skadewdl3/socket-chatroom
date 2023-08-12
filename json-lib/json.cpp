#include <iostream>
#include <utility>
#include "json.hpp"

using namespace json;
using namespace std;

typedef enum {
    Boolean, Integer, Float, String, Null, Object, Array
} TokenType;

// Constructors
json::Parser::Parser(char* json_string) {
    cout << "Creating parser with char*" << endl;
    json::Parser::json_string = string(json_string);
}

json::Parser::Parser(string json_string) {
    cout << "Creating parser with string" << endl;
    json::Parser::json_string = std::move(json_string);
}

json::Parser::~Parser () {
    cout << "Destroying parser" << endl;
}

void json::Parser::parse() {
    cout << "Parsing" << endl;
}

void json::Parser::parse(long start, long end) {
    cout << "Parsing from " << start << " to " << end << endl;
}

void json::Parser::get_value() {
    cout << "Getting value" << endl;
}

