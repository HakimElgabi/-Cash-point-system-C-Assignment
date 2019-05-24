//Pascale Vacher - March 17
//OOP Assignment Task 1c - Semester 2
//Group Number: 21
//Team: (Software Engineers - Hakim Elgabi(b5015647), Hamud Ibrahim(b5011597), Atiq Rafiq(b5009186), Shahid Ghafoor(b5012414))

#if !defined(ChildAccountH)
#define ChildAccountH

#include "SavingsAccount.h"

class ChildAccount : public SavingsAccount {
public:
	ChildAccount();
	ChildAccount(const string& typ, const string& acctNum, const string& sCode, const Date& cD, double b, const TransactionList& trList, double minBalance);
	~ChildAccount();
	double  getMaximumPaidIn() const;
	double  getMinimumPaidIn() const;
	virtual bool canWithdraw(double amount) const;
	virtual  bool canDeposit(double amount) const;
	virtual const string prepareFormattedStatement() const;
	virtual istream& getAccountDataFromStream(istream& is);
	virtual ostream& putAccountDetailsInStream(ostream& os) const;
	virtual bool canTransferOut(double amount) const;
	virtual bool canTranferIn(double amount) const;
private:
	double  maximumPaidIn_;
	double  minimumPaidIn_;
};
#endif