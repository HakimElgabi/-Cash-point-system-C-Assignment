//Pascale Vacher - March 17
//OOP Assignment Task 1c - Semester 2
//Group Number: 21
//Team: (Software Engineers - Hakim Elgabi(b5015647), Hamud Ibrahim(b5011597), Atiq Rafiq(b5009186), Shahid Ghafoor(b5012414))

#ifndef BankAccountH
#define BankAccountH

//---------------------------------------------------------------------------
//BankAccount: class declaration
//---------------------------------------------------------------------------

//#include "Date.h"
//#include "Transaction.h"
#include "TransactionList.h"

#include <fstream>
using namespace std;


class BankAccount {
public:
    //constructors & destructor
	BankAccount();
    BankAccount(const string& typ, const string& acctNum, const string& sCode,
                          const Date& cD, double b,
                          const TransactionList& trList);
    virtual ~BankAccount();

	//getter (assessor) functions
	const string getAccountType() const;
    const string getAccountNumber() const;
    const string getSortCode() const;
    const Date getCreationDate() const;
	double getBalance() const;
    const TransactionList getTransactions() const;
    bool isEmptyTransactionList() const;

	//other operations
	virtual const string prepareFormattedStatement() const;
	const string prepareFormattedMAD() const;

    virtual void recordDeposit(double amount);

	virtual double maxWithdrawalAllowed() const;
	virtual bool canWithdraw(double amount) const;
	virtual bool canDeposit(double amount) const;
	virtual bool canTransferOut(double amount) const;
	virtual bool canTranferIn(double amount) const;
    void recordWithdrawal(double amount);

	void readInBankAccountFromFile(const string& fileName);
	void storeBankAccountInFile(const string& fileName) const;
	//functions to put data into and get data from streams
	ostream& putDataInStream(ostream& os) const;
	virtual ostream& putAccountDetailsInStream(ostream& os) const;
	istream& getDataFromStream(istream& is);
	virtual istream& getAccountDataFromStream(istream& is);

	const string prepareFormattedAccountDetails() const;
	const string prepareFormattedTransactionList() const;
	const string prepareFormattedMiniAccountDetails() const;
	void produceAllDepositTransactions(string& str, double& total) const;
	void produceNMostRecentTransactions(string& str, int& numOfTransactions, double& total) const;
	void produceTransactionsForAmount(double&a, int& n, string&str) const;
	void produceTransactionsForTitle(string Title, int& n, string& str) const;
	void produceTransactionsForDate(Date& dateoftrans, int& n, string& str) const;
	void produceTransactionsUpToDate(Date& d, string& str, int& n) const;
	void recordDeletionOfTransactionUpToDate(Date& d);
	void recordTransferIn(double& transferAmount, const string& aAN, const string& aSC);
	void recordTransferOut(double& transferAmount, const string& tAN, const string& tSC);
	

	template <typename A>
	void produce(A& a, int& n, string& str) const
	{
		TransactionList trl(transactions_.getTransactionsForAmount(a));
		//2.2: n:= size(): integer
		n = trl.size();
		//2.3: str:= toFormattedString(): string
		str = trl.toFormattedString();
	}

	template<>
	void produce(string& a, int& n, string& str) const
	{
		TransactionList trl(transactions_.getTransactionsForTitle(a));
		//2.2: n:= size(): integer
		n = trl.size();
		//2.3: str:= toFormattedString(): string
		str = trl.toFormattedString();
	}

	template<>
	void produce(Date& a, int& n, string& str) const
	{
		TransactionList trl(transactions_.getTransactionsForDate(a));
		//2.2: n:= size(): integer
		n = trl.size();
		//2.3: str:= toFormattedString(): string
		str = trl.toFormattedString();
	}

private:
    //data items
    string accountType_;
    string accountNumber_;
    string sortCode_;
    Date   creationDate_;
	double balance_;
    TransactionList transactions_;
 
	//support functions
	void updateBalance(double amount);
};

//---------------------------------------------------------------------------
//non-member operator functions
//---------------------------------------------------------------------------

ostream& operator<<(ostream&, const BankAccount&);	//output operator
istream& operator>>(istream&, BankAccount&);	    //input operator

#endif
