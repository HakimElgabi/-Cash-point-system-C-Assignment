//Pascale Vacher - March 17
//OOP Assignment Task 1c - Semester 2
//Group Number: 21
//Team: (Software Engineers - Hakim Elgabi(b5015647), Hamud Ibrahim(b5011597), Atiq Rafiq(b5009186), Shahid Ghafoor(b5012414))

#if !defined(ISAAccountH)
#define ISAAccountH

#include "SavingsAccount.h"

class ISAAccount : public SavingsAccount {
public:
	ISAAccount();
	ISAAccount(const string& typ, const string& acctNum, const string& sCode, const Date& cD, double b, const TransactionList& trList, double minBalance);
	~ISAAccount();
	double getMaximumYearlyDeposit() const;
	double getCurrentYearlyDeposit() const;
	void updateCurrentYearlyDeposit(double a); 
	Date endDepositPeriod() const;
	virtual const string prepareFormattedStatement() const;
	virtual istream& getAccountDataFromStream(istream& is);
	virtual  bool canDeposit(double amount) const;
	virtual void recordDeposit(double amount);
	virtual ostream& putAccountDetailsInStream(ostream& os) const;
	virtual bool canTranferIn(double amount) const;
private:
	double maximumYearlyDeposit_;
	double currentYearlyDeposit_;
	Date endDepositPeriod_;

};
#endif