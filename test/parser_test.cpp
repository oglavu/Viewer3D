#include "Parser.hpp"
#include "Object.hpp"

void parser_test() {


	ObjectPtr obj = Parser::parseFile("./untitled.obj");

	std::cout << *obj.get();

}