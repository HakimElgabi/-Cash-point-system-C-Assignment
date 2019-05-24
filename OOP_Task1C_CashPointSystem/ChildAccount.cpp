//Pascale Vacher - March 17
//OOP Assignment Task 1c - Semester 2
//Group Number: 21
//Team: (Software Engineers - Hakim Elgabi(b5015647), Hamud Ibrahim(b5011597), Atiq Rafiq(b5009186), Shahid Ghafoor(b5012414))

#include "ChildAccount.h"
ChildAccount::ChildAccount() 
: maximumPaidIn_(0.0), minimumPaidIn_(0.0)
{}

ChildAccount::ChildAccount(const string& typ, const string& acctNum, const string& sCode,
	const Date& cD, double b,
	const TransactionList& trList,
	double minBalance)  :  
	SavingsAccount(typ, acctNum, sCode, cD, b, trList, minBalance)
{}

ChildAccount:: ~ChildAccount()
{}

double ChildAccount::getMaximumPaidIn() const
{
	return maximumPaidIn_;
}

double ChildAccount::getMinimumPaidIn() const
{
	return minimumPaidIn_;
}

bool ChildAccount::canWithdraw(double amountToWithdraw) const {
	//check if there's enough money in account
	return false;
}

bool ChildAccount::canDeposit(double amountToDeposit) const {
	//check if there's enough money in account
	return ((amountToDeposit >= minimumPaidIn_) && (amountToDeposit <= maximumPaidIn_));
}

const string ChildAccount::prepareFormattedStatement() const {
	ostringstream os;
	//display inherited BankAccount attributes
	os << SavingsAccount::prepareFormattedStatement();
	//display overdraft limit
	os << fixed << setprecision(2);
	os << "\nMAXIMUM DEPOSIT LIMIT: " << (char)156 << maximumPaidIn_;
	os << "\nMINIMUM DEPOSIT LIMIT: " << (char)156 << minimumPaidIn_;
	return (os.str());
}

istream& ChildAccount::getAccountDataFromStream(istream& is) {
	//get SavingsAccount details from stream
	SavingsAccount::getAccountDataFromStream(is);					//gets balance
	is >> minimumPaidIn_;
	is >> maximumPaidIn_;
	return is;
}

ostream& ChildAccount::putAccountDetailsInStream(ostream& os) const {
	//put (unformatted) SavingsAccount details in stream
	SavingsAccount::putAccountDetailsInStream(os);
	os << minimumPaidIn_ << "\n";					//output minimum limit
	os << maximumPaidIn_ << "\n";					//output maximum limit
	return os;
}

bool ChildAccount::canTransferOut(double amount) const {
	//check if can transfer money out of account
	return false;
}

bool ChildAccount::canTranferIn(double amount) const {
	//check if can transfer money into account
	return ((amount >= minimumPaidIn_) && (amount <= maximumPaidIn_));;
}