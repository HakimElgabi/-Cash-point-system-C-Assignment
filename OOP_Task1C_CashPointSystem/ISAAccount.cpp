//Pascale Vacher - March 17
//OOP Assignment Task 1c - Semester 2
//Group Number: 21
//Team: (Software Engineers - Hakim Elgabi(b5015647), Hamud Ibrahim(b5011597), Atiq Rafiq(b5009186), Shahid Ghafoor(b5012414))

#include "ISAAccount.h"
ISAAccount::ISAAccount()
: maximumYearlyDeposit_(0.0),
currentYearlyDeposit_(0.0), endDepositPeriod_()
{}
ISAAccount::ISAAccount(const string& typ, const string& acctNum, const string& sCode,
	const Date& cD, double b,
	const TransactionList& trList, double minBalance) : 
	SavingsAccount(typ, acctNum, sCode, cD, b, trList, minBalance)
{}

ISAAccount:: ~ISAAccount()
{}

double ISAAccount::getMaximumYearlyDeposit() const	
{	//retrieves maximum yearly deposit
	return maximumYearlyDeposit_;
}

double ISAAccount::getCurrentYearlyDeposit() const
{	//retrieves current yearly deposit
	return currentYearlyDeposit_;
}

void ISAAccount::updateCurrentYearlyDeposit(double a)
{	//updates current yearly deposit
	currentYearlyDeposit_ += a;
}
Date  ISAAccount::endDepositPeriod() const
{	//retrieves end deposit period
	return endDepositPeriod_;
}

const string ISAAccount::prepareFormattedStatement() const {
	ostringstream os;
	//display inherited BankAccount attributes
	os << SavingsAccount::prepareFormattedStatement();
	//display overdraft limit
	os << fixed << setprecision(2);
	os << "\nMAXIMUM YEARLY DEPOSIT LIMIT: " << (char)156 << maximumYearlyDeposit_;
	os << "\nCURRENT YEARLY DEPOSIT LIMIT: " << (char)156 << currentYearlyDeposit_;
	os << "\nEND DEPOSIT PERIOD: " << endDepositPeriod_;
	return (os.str());
}

istream& ISAAccount::getAccountDataFromStream(istream& is) 
{	//get SavingsAccount details from stream
	SavingsAccount::getAccountDataFromStream(is);					//get balance
	is >> maximumYearlyDeposit_;
	is >> currentYearlyDeposit_;
	is >> endDepositPeriod_;
	return is;
}

bool ISAAccount::canDeposit(double amountToDeposit) const 
{	//check if enough money in account
	return ((amountToDeposit + currentYearlyDeposit_) <= maximumYearlyDeposit_) && (Date::currentDate() < endDepositPeriod_);
}
void ISAAccount::recordDeposit(double amountToDeposit) 
{	//records the amount to deposit and updates current yearly deposit
	BankAccount::recordDeposit(amountToDeposit);
	updateCurrentYearlyDeposit(amountToDeposit);
}

ostream& ISAAccount::putAccountDetailsInStream(ostream& os) const 
{	//put (unformatted) SavingsAccount details in stream
	SavingsAccount::putAccountDetailsInStream(os);
	os << maximumYearlyDeposit_ << "\n";					//put maximum yearly
	os << currentYearlyDeposit_ << "\n";					//put current yearly
	os << endDepositPeriod_ << "\n";						//put desposit date
	return os;
}

bool ISAAccount::canTranferIn(double amount) const {
	//check if can transfer money into account
	return ((amount + currentYearlyDeposit_) <= maximumYearlyDeposit_) && (Date::currentDate() < endDepositPeriod_);
}