#ifndef TOKEN_H
#define TOKEN_H
using namespace std;

enum Names { NONE, Web, Jinx, Souvenir, Carapace };		// possible types of token

class Token {
	// class that represents a token
	private:
		Names type;					// type of token

	public:
		Token();					// default constructor
		Token(Names);				// set constructor
		~Token();					// destructor

		void setName(Names);		// set type of token

		Names getName() const;		// gets type of token

		void Print();				// prints information about token

};
#endif