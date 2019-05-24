//Pascale Vacher - March 17
//OOP Assignment Task 1c - Semester 2
//Group Number: 21
//Team: (Software Engineers - Hakim Elgabi(b5015647), Hamud Ibrahim(b5011597), Atiq Rafiq(b5009186), Shahid Ghafoor(b5012414))

#include "BankAccount.h"

//---------------------------------------------------------------------------
//BankAccount: class implementation
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//public member functions
//---------------------------------------------------------------------------

//____constructors & destructors

BankAccount::BankAccount()
    : balance_(0.0)
{}
BankAccount::BankAccount(const string& typ, const string& acctNum, const string& sCode,
                         const Date& cD, double b,
                         const TransactionList& trList)
    : accountType_(typ),
	  accountNumber_(acctNum), sortCode_(sCode),
      creationDate_(cD),
      balance_(b),
      transactions_(trList)
{}
BankAccount::~BankAccount()
{}

//____other public member functions

const string BankAccount::getAccountType() const {
    return accountType_;
}
const string BankAccount::getAccountNumber() const {
    return accountNumber_;
}
const string BankAccount::getSortCode() const {
    return sortCode_;
}
const Date BankAccount::getCreationDate() const {
    return creationDate_;
}
double BankAccount::getBalance() const {
    return balance_;
}
const TransactionList BankAccount::getTransactions() const {
    return transactions_;
}
bool BankAccount::isEmptyTransactionList() const {
	return transactions_.size() == 0;
}

void BankAccount::recordDeposit(double amountToDeposit) {
    //create a deposit transaction
	Transaction aTransaction("deposit_to_ATM", amountToDeposit);
    //update active bankaccount
    transactions_.addNewTransaction(aTransaction);		//update transactions_
    updateBalance(amountToDeposit);			//increase balance_
}

double BankAccount::maxWithdrawalAllowed() const {
//return borrowable amount
    return balance_;
}

bool BankAccount::canDeposit(double amountToDeposit) const {
	//check if enough money in account
	return true;
}

bool BankAccount::canWithdraw(double amountToWithdraw ) const {
//check if enough money in account
	return amountToWithdraw <= maxWithdrawalAllowed();
}


bool BankAccount::canTransferOut(double amount) const {
	//check if can transfer money out of account
	return amount<= maxWithdrawalAllowed();
}

bool BankAccount::canTranferIn(double amount) const {
	//check if can transfer money into account
	return true;
}

void BankAccount::recordWithdrawal(double amountToWithdraw) {
	//create a withdrawal transaction
    Transaction aTransaction("withdrawal_from_ATM", -amountToWithdraw);
    //update active bankaccount
    transactions_.addNewTransaction(aTransaction);		//update transactions_
    updateBalance(-amountToWithdraw);			//decrease balance_
}

const string BankAccount::prepareFormattedStatement() const {
	ostringstream os;
	//account details
	os << prepareFormattedAccountDetails();
	//list of transactions (or message if empty)
	os << prepareFormattedTransactionList();
	return os.str();
}

const string BankAccount::prepareFormattedMiniAccountDetails() const{
	ostringstream os;
	//account details
	os << prepareFormattedMAD();
	return os.str();
}

void BankAccount::readInBankAccountFromFile(const string& fileName) {
	ifstream fromFile;
	fromFile.open(fileName.c_str(), ios::in); 	//open file in read mode
	if (fromFile.fail())
		cout << "\nAN ERROR HAS OCCURED WHEN OPENING THE FILE.";
	else
        fromFile >> (*this);  	//read  all info from bank account file
    fromFile.close();			//close file: optional here
}

void BankAccount::storeBankAccountInFile(const string& fileName) const {
	ofstream toFile;
	toFile.open(fileName.c_str(), ios::out);	//open copy file in write mode
	if (toFile.fail())
		cout << "\nAN ERROR HAS OCCURED WHEN OPENING THE FILE.";
	else
        toFile << (*this);	//store all info to bank account file
	toFile.close();			//close file: optional here
}
ostream& BankAccount::putDataInStream(ostream& os) const {
//put (unformatted) BankAccount details in stream
	putAccountDetailsInStream(os);			//put bank account core information in stream
	if (transactions_.size() != 0)
		os << transactions_;				//put all transactions, one per line
	return os;
}
ostream& BankAccount::putAccountDetailsInStream(ostream& os) const {
	//put (unformatted) BankAccount details in stream
	os << accountType_ << "\n";				//put account type
	os << accountNumber_ << "\n";			//put account number
	os << sortCode_ << "\n";				//put sort code
	os << creationDate_ << "\n";			//put creation date
	os << balance_ << "\n";					//put balance
	return os;
}
istream& BankAccount::getDataFromStream(istream& is) {
//get BankAccount details from stream
	getAccountDataFromStream(is);			//get bank account ore information from stream
	is >> transactions_;					//get all transactions (if any)
	return is;
}
istream& BankAccount::getAccountDataFromStream(istream& is) {
	//get BankAccount details from stream
	is >> accountType_;						//get account type
	is >> accountNumber_;					//get account number
	is >> sortCode_;						//get sort code
	is >> creationDate_;					//get creation date
	is >> balance_;							//get balance
	return is;
}

void BankAccount::produceAllDepositTransactions(string& str, double& total) const{
	//2.1: trl : = getAllDepositTransactions() : TransactionList
	TransactionList trl(transactions_.getAllDepositTransactions());
	//2.2 : total : = getTotalTransactions() : double
	total = trl.getTotalTransactions();
	//2.3 : str : = toFormattedString() : string
	str = trl.toFormattedString();
}
void BankAccount::produceNMostRecentTransactions(string& str, int& numOfTransactions, double& total) const{
	//3.1: trl: = getMostRecentTransactions(integer) :TransactionList
	TransactionList trl(transactions_.getMostRecentTransactions(numOfTransactions));
	//3.2: total:= getTotalTransactions(): double
	total = trl.getTotalTransactions();
	//3.3: str:= toFormattedString(): string
	str = trl.toFormattedString();
}


//void BankAccount::produceTransactionsForAmount(double&a, int& n, string&str) const
//{
//	//2.1: trl : = getTransactionsForAmount (double) TransactionList
//	TransactionList trl(transactions_.getTransactionsForAmount(a));
//	//2.2: n:= size(): integer
//	n = trl.size();
//	//2.3: str:= toFormattedString(): string
//	str = trl.toFormattedString();
//}
//
//void BankAccount::produceTransactionsForTitle(string Title, int& n, string& str) const
//{
//	TransactionList trl(transactions_.getTransactionsForTitle(Title));
//	//2.2: n:= size(): integer
//	n = trl.size();
//	//2.3: str:= toFormattedString(): string
//	str = trl.toFormattedString();
//}
//
//void BankAccount::produceTransactionsForDate(Date& dateoftrans, int& n, string& str) const {
//	TransactionList trl(transactions_.getTransactionsForDate(dateoftrans));
//	//2.2: n:= size(): integer
//	n = trl.size();
//	//2.3: str:= toFormattedString(): string
//	str = trl.toFormattedString();
//}
void BankAccount::produceTransactionsUpToDate(Date& d, string& str, int& n) const{
	//4.1: trl:= getTransactionsUpToDate(d): TransactionList
	TransactionList trl(transactions_.getTransactionsUpToDate(d));
	//4.2: n:= size(): integer
	n = trl.size();
	//4.3: str:= toFormattedString(): string
	str = trl.toFormattedString();
}
void BankAccount::recordDeletionOfTransactionUpToDate(Date& d) {
	//7.1: deleteTransactionsUpToDate(d)
	transactions_.deleteTransactionsUpToDate(d);
}
void BankAccount::recordTransferIn(double& transferAmount, const string& aAN, const string& aSC){
	//1: createTransaction (string, double) : Transaction
	Transaction inTransaction = Transaction("TRANSFER_IN_" + aAN + "_" + aSC, transferAmount);
	//2: addNewTransaction(Transaction)
	transactions_.addNewTransaction(inTransaction);
	//3: updateBalance(double)
	updateBalance(transferAmount);
}
void BankAccount::recordTransferOut(double& transferAmount, const string& tAN, const string& tSC){
	//1: createTransaction (string, double) : Transaction
	Transaction outTransaction = Transaction("TRANSFER_OUT_" + tAN + "_" + tSC, -transferAmount);
	//2: addNewTransaction(Transaction)
	transactions_.addNewTransaction(outTransaction);
	//3: updateBalance(double)
	updateBalance(-transferAmount);
}
//---------------------------------------------------------------------------
//private support member functions
//---------------------------------------------------------------------------
void BankAccount::updateBalance(double amount) {
    balance_ += amount;   //add/take amount to/from balance_
}
const string BankAccount::prepareFormattedAccountDetails() const {
	//collect account details in string
	ostringstream os;
	//account details
	os << "\nACCOUNT TYPE:    " << accountType_ << " ACCOUNT";						//display account type
	os << "\nACCOUNT NUMBER:  " << accountNumber_;									//display account number
	os << "\nSORT CODE:       " << sortCode_;										//display sort code
	os << "\nCREATION DATE:   " << creationDate_.toFormattedString();				//display creation date
	os << fixed << setprecision(2) << setfill(' ');
	os << "\nBALANCE:         \234" << setw(10) << balance_;	//display balance
	return os.str();
}
const string BankAccount::prepareFormattedMAD() const {
	//collect account details in string
	ostringstream os;
	//account details
	os << "\nACCOUNT NUMBER:  " << accountNumber_;									//display account number
	os << "\nSORT CODE:       " << sortCode_;										//display sort code
	os << fixed << setprecision(2) << setfill(' ');
	os << "\nBALANCE:         \234" << setw(10) << balance_<< "\n";	//display balance
	return os.str();
}
const string BankAccount::prepareFormattedTransactionList() const {
	ostringstream os;
	//list of transactions (or message if empty)
	if (! transactions_.size() == 0)
		os << "\n\nLIST OF TRANSACTIONS \n"	<< transactions_.toFormattedString();	//one per line
	else
		os << "\n\nNO TRANSACTIONS IN BANK ACCOUNT!\n";
	return os.str();
}


//---------------------------------------------------------------------------
//non-member operator functions
//---------------------------------------------------------------------------

ostream& operator<<(ostream& os, const BankAccount& aBankAccount) {
//put (unformatted) BankAccount details in stream
    return aBankAccount.putDataInStream(os);
}
istream& operator>>(istream& is, BankAccount& aBankAccount) {
//get BankAccount details from stream
	return aBankAccount.getDataFromStream(is);
}
