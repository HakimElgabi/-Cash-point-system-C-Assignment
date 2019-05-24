//Pascale Vacher - March 17
//OOP Assignment Task 1c - Semester 2
//Group Number: 21
//Team: (Software Engineers - Hakim Elgabi(b5015647), Hamud Ibrahim(b5011597), Atiq Rafiq(b5009186), Shahid Ghafoor(b5012414))

#ifndef TransactionListH
#define TransactionListH

//---------------------------------------------------------------------------
//TransactionList: class declaration
//---------------------------------------------------------------------------

#include "ListT.h"
#include "Transaction.h"

#include <algorithm>
#include <list>
#include <numeric>
#include <cassert> 	// for assert()
#include <sstream>

class TransactionList {
public:
	void  addNewTransaction(const Transaction&);
    const Transaction newestTransaction() const;
    const  TransactionList olderTransactions() const;
    void   deleteFirstTransaction();
    void   deleteGivenTransaction(const Transaction&);
	int    size() const;

	const string toFormattedString() const;		//return transactionlist as a (formatted) string
	ostream& putDataInStream(ostream& os) const;	//send TransactionList info into an output stream
	istream& getDataFromStream(istream& is);	//receive TransactionList info from an input stream

	const TransactionList getAllDepositTransactions() const;
	double getTotalTransactions() const;
	const TransactionList getMostRecentTransactions(int numOfTransactions) const;
	const TransactionList getTransactionsForAmount(double a) const;
	const TransactionList getTransactionsForTitle(string Title) const;
	const TransactionList getTransactionsForDate(Date& dateoftrans) const;
	/*const TransactionList getTransactionsUpToDate(Date& d) const;*/
	
	//recursion
	const TransactionList getTransactionsUpToDate(const Date& d) const;
	const TransactionList getTransactionsUpToDateRec(const Date& d, TransactionList& tempTrList, TransactionList& ret) const;
	//indirect recursion for delete dates
	void deleteTransactionsUpToDate(Date& d);
	void deleteTransactionsUpToDateRec(Date& d, TransactionList& tempTrList, List<Transaction>& listOfTransactions_2);
	
	private:
		//list<Transaction> listOfTransactions_;	//list of transactions
		List<Transaction> listOfTransactions_;	//list of transactions
};

//---------------------------------------------------------------------------
//non-member operator functions
//---------------------------------------------------------------------------

ostream& operator<<(ostream&, const TransactionList&);	//insertion operator
istream& operator>>(istream& is, TransactionList& trl); //extraction operator

#endif

