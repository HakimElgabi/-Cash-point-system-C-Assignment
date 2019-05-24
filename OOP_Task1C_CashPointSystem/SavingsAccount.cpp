//Pascale Vacher - March 17
//OOP Assignment Task 1c - Semester 2
//Group Number: 21
//Team: (Software Engineers - Hakim Elgabi(b5015647), Hamud Ibrahim(b5011597), Atiq Rafiq(b5009186), Shahid Ghafoor(b5012414))

#include "SavingsAccount.h"

SavingsAccount::SavingsAccount() : minimumBalance_(0.0)
{}

SavingsAccount::SavingsAccount(const string& typ, const string& acctNum, const string& sCode,
	const Date& cD, double b,
	const TransactionList& trList,
	double minBalance) : minimumBalance_(minBalance),
	BankAccount(typ, acctNum, sCode, cD, b, trList)
{}

SavingsAccount:: ~SavingsAccount()
{}

double SavingsAccount::getMinimumBalance() const
{
	return minimumBalance_;
}

const string SavingsAccount::prepareFormattedStatement() const {
	ostringstream os;
	//display inherited BankAccount attributes
	os << BankAccount::prepareFormattedStatement();
	//display minimum balance limit
	os << fixed << setprecision(2);
	os << "\nMINIMUM BALANCE: " << (char)156 << minimumBalance_;
	return (os.str());
}

istream& SavingsAccount::getAccountDataFromStream(istream& is) {
	//get BankAccount details from stream
	BankAccount::getAccountDataFromStream(is);					//get balance
	is >> minimumBalance_;
	return is;
}
ostream& SavingsAccount::putAccountDetailsInStream(ostream& os) const {
	//put (unformatted) BankAccount details in stream
	BankAccount::putAccountDetailsInStream(os);
	os << minimumBalance_ << "\n";					//put overdraft limit
	return os;
}
bool SavingsAccount::canWithdraw(double amountToWithdraw) const {
	//check if there's enough money in account
	return ((getBalance() - amountToWithdraw) >= minimumBalance_);
}
bool SavingsAccount::canTransferOut(double amount) const {
	//check if can transfer money out of account
	return ((getBalance() - amount) >= minimumBalance_);
}