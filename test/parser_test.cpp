#include "Parser.hpp"
#include "Object.hpp"

void parser_test() {


	Object* obj = Parser::parseFile("./untitled.obj");

	std::cout << *obj;

}