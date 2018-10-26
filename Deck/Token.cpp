// implementation file for Token.h


#include "Token.h"
#include <iostream>
#include <string>

string names[5] = { "NONE", "Web", "Jinx", "Souvenir", "Carapace" };	// string representation of token types

// default constructor
Token::Token() {
	type = NONE;
}

// set constructor, creating a tile with type name
Token::Token(Names name) {
	type = name;
}

Token::~Token() {
	// destructor
}

/*** SETTER ***/
void Token::setName(Names name) {
	type = name;
}

/*** GETTER ***/
Names Token::getName() const {
	return type;
}

// prints information about a token
void Token::Print() {
	cout << "Token: " << names[type] << endl;
}

