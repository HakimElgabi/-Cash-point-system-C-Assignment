//Pascale Vacher - March 17
//OOP Assignment Task 1c - Semester 2
//Group Number: 21
//Team: (Software Engineers - Hakim Elgabi(b5015647), Hamud Ibrahim(b5011597), Atiq Rafiq(b5009186), Shahid Ghafoor(b5012414))

#if !defined(CurrentAccountH)
#define CurrentAccountH

#include "BankAccount.h"

class CurrentAccount : public BankAccount {
public:
	CurrentAccount();
	CurrentAccount(const string& typ, const string& acctNum, const string& sCode, 
							const Date& cD, double b, 
							const TransactionList& trList);
	~CurrentAccount();
	double getOverdraftLimit() const;
	virtual double maxWithdrawalAllowed() const;
	virtual const string prepareFormattedStatement() const;
	virtual istream& getAccountDataFromStream(istream& is);
	virtual ostream& putAccountDetailsInStream(ostream& os) const;
	virtual bool canTransferOut(double amount) const;
private:
	double overdraftLimit_;

};
#endif