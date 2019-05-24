//Pascale Vacher - March 17
//OOP Assignment Task 1c - Semester 2
//Group Number: 21
//Team: (Software Engineers - Hakim Elgabi(b5015647), Hamud Ibrahim(b5011597), Atiq Rafiq(b5009186), Shahid Ghafoor(b5012414))

#include "CurrentAccount.h"
CurrentAccount::CurrentAccount()
: overdraftLimit_(0.0)
{}
CurrentAccount::CurrentAccount(const string& typ, const string& acctNum, const string& sCode, 
	const Date& cD, double b, 
	const TransactionList& trList) : 
	BankAccount( typ, acctNum, sCode,  cD, b,  trList)
{ }

CurrentAccount:: ~CurrentAccount()
{}

double CurrentAccount:: getOverdraftLimit() const
{
	return overdraftLimit_;
}

double CurrentAccount::maxWithdrawalAllowed() const 
{
	//returning the borrowable amount
	return  getBalance() + overdraftLimit_;
}

const string CurrentAccount::prepareFormattedStatement() const {
	ostringstream os;
	//displays inherited BankAccount attributes
	os << BankAccount::prepareFormattedStatement();
	//displays overdraft limit
	os << fixed << setprecision(2);
	os << "\nOVERDRAFT LIMIT: " << (char)156 << overdraftLimit_;
	return (os.str());
}
istream& CurrentAccount::getAccountDataFromStream(istream& is) {
	//gets BankAccount details from stream
	BankAccount::getAccountDataFromStream(is);					//get balance
	is >> overdraftLimit_;
	return is;
}

ostream& CurrentAccount::putAccountDetailsInStream(ostream& os) const {
	//this puts the (unformatted) BankAccount details in stream
	BankAccount::putAccountDetailsInStream(os);
	os << overdraftLimit_ << "\n";					//put overdraft limit
	return os;
}
bool CurrentAccount::canTransferOut(double amount) const {
	//check if can transfer money out of account
	return (amount <= (getBalance() + overdraftLimit_));
}