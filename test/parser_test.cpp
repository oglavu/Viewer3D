#include "Parser.hpp"
#include "Object.hpp"

void parser_test() {


	ObjectPtr obj = Parser::parseFile("./resources/untitled.obj");

	std::cout << *obj.get();

}