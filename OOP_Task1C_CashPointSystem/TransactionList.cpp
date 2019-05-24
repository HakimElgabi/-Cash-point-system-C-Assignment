//Pascale Vacher - March 17
//OOP Assignment Task 1c - Semester 2
//Group Number: 21
//Team: (Software Engineers - Hakim Elgabi(b5015647), Hamud Ibrahim(b5011597), Atiq Rafiq(b5009186), Shahid Ghafoor(b5012414))

#include "TransactionList.h"
#include <list>
//---------------------------------------------------------------------------
//TransactionList: class implementation
//---------------------------------------------------------------------------

//____public member functions

//____constructors & destructors

//____other public member functions

void TransactionList::addNewTransaction(const Transaction& tr) {
    listOfTransactions_.addInFront(tr);
	//listOfTransactions_.push_front(tr);
}
const Transaction TransactionList::newestTransaction() const {
    return (listOfTransactions_.first());
	//return (listOfTransactions_.front());
}
const TransactionList TransactionList::olderTransactions() const {
	TransactionList trlist(*this);
    trlist.deleteFirstTransaction();
    return trlist;
}
void TransactionList::deleteFirstTransaction() {
    listOfTransactions_.deleteFirst();
	//listOfTransactions_.pop_front();
}
void TransactionList::deleteGivenTransaction(const Transaction& tr) {
    listOfTransactions_.deleteOne(tr);
	//listOfTransactions_.remove(tr);
}
int TransactionList::size() const {
    return (listOfTransactions_.length());
	//return (listOfTransactions_.size());
}

const string TransactionList::toFormattedString() const {
//return transaction list as a (formatted) string
	ostringstream os_transactionlist;
    TransactionList tempTrList(*this);
	while (! (tempTrList.size() == 0))
    {
		os_transactionlist << tempTrList.newestTransaction().toFormattedString() << endl;
        tempTrList.deleteFirstTransaction();
    }
	return (os_transactionlist.str());
}

const TransactionList TransactionList::getAllDepositTransactions() const{
	TransactionList tempTrList(*this);
	TransactionList ret;
	while (tempTrList.size() != 0)
	{
		if (tempTrList.newestTransaction().getAmount() > 0){
			ret.addNewTransaction(tempTrList.newestTransaction());
		}	
		tempTrList.deleteFirstTransaction();
	}
	return ret;
}

double TransactionList::getTotalTransactions() const{
	double totalAmount(0.0);
	TransactionList tempTrList(*this);
	while (tempTrList.size() != 0)
	{
			totalAmount += tempTrList.newestTransaction().getAmount();
			tempTrList.deleteFirstTransaction();
	}
	return totalAmount;
}
TransactionList const TransactionList::getMostRecentTransactions(int numOfTransactions) const{
	TransactionList tempTrList(*this);
	TransactionList ret;
	numOfTransactions = tempTrList.size() - numOfTransactions;
	while (tempTrList.size() != 0)
	{
		if (!(tempTrList.size() <= numOfTransactions)){
			ret.addNewTransaction(tempTrList.newestTransaction());	
		}
		tempTrList.deleteFirstTransaction();
	}
	return ret;
}
TransactionList const TransactionList::getTransactionsForAmount(double a) const{
	TransactionList tempTrList(*this);
	TransactionList ret;
	while (tempTrList.size() != 0)
	{
		if (tempTrList.newestTransaction().getAmount() == a)
		{
			ret.addNewTransaction(tempTrList.newestTransaction());
		}
		tempTrList.deleteFirstTransaction();
	}
	return ret;
}
TransactionList const TransactionList::getTransactionsForTitle(string Title) const{
	TransactionList tempTrList(*this);
	TransactionList ret;
	while (tempTrList.size() != 0)
	{
		if (Title == tempTrList.newestTransaction().getTitle())
		{
			ret.addNewTransaction(tempTrList.newestTransaction());
		}
		tempTrList.deleteFirstTransaction();
	}
	return ret;
}
TransactionList const TransactionList::getTransactionsForDate(Date& dateoftrans) const{
	TransactionList tempTrList(*this);
	TransactionList ret;
	while (tempTrList.size() != 0)
	{
		if (dateoftrans.toFormattedString() == (tempTrList.newestTransaction().getDate().toFormattedString()))
		{
			ret.addNewTransaction(tempTrList.newestTransaction());
		}
		tempTrList.deleteFirstTransaction();
	}
	return ret;
}
//TransactionList const TransactionList::getTransactionsUpToDate(Date& d) const{
//	TransactionList tempTrList(*this);
//	TransactionList ret;
//	while (tempTrList.size() != 0)
//	{
//		if (tempTrList.newestTransaction().getDate() < d)
//		{
//			ret.addNewTransaction(tempTrList.newestTransaction());
//		}
//		if (tempTrList.newestTransaction().getDate() == d)
//		{
//			ret.addNewTransaction(tempTrList.newestTransaction());
//		}
//		tempTrList.deleteFirstTransaction();
//	}
//	return ret;
//}

//recursion (works but not sure if correct)
TransactionList const TransactionList::getTransactionsUpToDate(const Date& d) const{
	TransactionList tempTrList(*this);
	TransactionList ret;
	return getTransactionsUpToDateRec(d, tempTrList, ret);
}

TransactionList const TransactionList::getTransactionsUpToDateRec(const Date& d, TransactionList& tempTrList, TransactionList& ret) const{
	if (tempTrList.size() != 0)
	{
		if (tempTrList.newestTransaction().getDate() < d)
		{
			ret.addNewTransaction(tempTrList.newestTransaction());
		}
		if (tempTrList.newestTransaction().getDate() == d)
		{
			ret.addNewTransaction(tempTrList.newestTransaction());
		}
		tempTrList.deleteFirstTransaction();
		return getTransactionsUpToDateRec(d, tempTrList, ret);
	}
	else
	{
		return ret;
	}
}

void TransactionList::deleteTransactionsUpToDate(Date& d){
	TransactionList tempTrList(*this);
	TransactionList ret;
	List<Transaction> listOfTransactions_2;
	deleteTransactionsUpToDateRec(d, tempTrList, listOfTransactions_2);
	}

void TransactionList::deleteTransactionsUpToDateRec(Date& d, TransactionList& tempTrList, List<Transaction>& listOfTransactions_2) {
	if (tempTrList.size() != 0)
	{
		if (d < tempTrList.newestTransaction().getDate())
		{
			listOfTransactions_2.addInFront(tempTrList.newestTransaction());
		}
		tempTrList.deleteFirstTransaction();
		listOfTransactions_ = listOfTransactions_2;
		return deleteTransactionsUpToDateRec(d, tempTrList, listOfTransactions_2);
	}
}

//void TransactionList::deleteTransactionsUpToDate(Date& d) {
//	TransactionList tempTrList(*this);
//	List<Transaction> listOfTransactions_2;
//	while (tempTrList.size() != 0)
//	{
//		if (d < tempTrList.newestTransaction().getDate())
//		{
//			listOfTransactions_2.addInFront(tempTrList.newestTransaction());
//		}
//		tempTrList.deleteFirstTransaction();
//	}
//	listOfTransactions_ = listOfTransactions_2;
//}

ostream& TransactionList::putDataInStream(ostream& os) const {
//put (unformatted) transaction list into an output stream
    TransactionList tempTrList(*this);
	while (! (tempTrList.size() == 0))
    {
		os << tempTrList.newestTransaction() << endl;
        tempTrList.deleteFirstTransaction();
    }
	return os;
}
istream& TransactionList::getDataFromStream(istream& is) {
//read in (unformatted) transaction list from input stream
	Transaction aTransaction;
	is >> aTransaction;	//read first transaction
	while (is) 	//while not end of file
	{
		listOfTransactions_.addAtEnd(aTransaction);   //add transaction to list of transactions
		//listOfTransactions_.push_back(aTransaction);
		is >> aTransaction;	//read in next transaction
	}
	return is;
}


//---------------------------------------------------------------------------
//non-member operator functions
//---------------------------------------------------------------------------

ostream& operator<<(ostream& os, const TransactionList& aTransactionList) {
    return (aTransactionList.putDataInStream(os));
}
istream& operator>>(istream& is, TransactionList& aTransactionList) {
	return (aTransactionList.getDataFromStream(is));
}
