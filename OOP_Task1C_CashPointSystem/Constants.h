//Pascale Vacher - March 17
//OOP Assignment Task 1c - Semester 2
//Group Number: 21
//Team: (Software Engineers - Hakim Elgabi(b5015647), Hamud Ibrahim(b5011597), Atiq Rafiq(b5009186), Shahid Ghafoor(b5012414))

#ifndef ConstantsH
#define ConstantsH

#include <string>
using namespace std;

//menu command
const int QUIT_COMMAND(0);

//account type
const int BANKACCOUNT_TYPE(0); 
const int CURRENTACCOUNT_TYPE(1);
const int SAVINGSACCOUNT_TYPE(2);
const int CHILDACCOUNT_TYPE(3);
const int ISAACCOUNT_TYPE(4);
//card state
const int VALID_CARD(0);
const int UNKNOWN_CARD(1);
const int EMPTY_CARD(2);

//account state
const int VALID_ACCOUNT(0);
const int UNKNOWN_ACCOUNT(1);
const int UNACCESSIBLE_ACCOUNT(2);
const int SAME_ACCOUNT(3);
//ressource path
const string FILEPATH("data\\");

#endif