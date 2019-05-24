//Pascale Vacher - March 17
//OOP Assignment Task 1c - Semester 2
//Group Number: 21
//Team: (Software Engineers - Hakim Elgabi(b5015647), Hamud Ibrahim(b5011597), Atiq Rafiq(b5009186), Shahid Ghafoor(b5012414))

#include "CashPoint.h"

//---------------------------------------------------------------------------
//CashPoint: class implementation
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//public member functions
//---------------------------------------------------------------------------

//____constructors & destructors

CashPoint::CashPoint()
	: p_theActiveAccount_(nullptr), p_theCashCard_(nullptr), theUI_(UserInterface::getInstance())
{ }

CashPoint::~CashPoint()
{
	assert(p_theActiveAccount_ == nullptr);
	assert(p_theCashCard_ == nullptr);
}

//____other public member functions

void CashPoint::activateCashPoint() {
	int command;
	theUI_->showWelcomeScreen();
    command = theUI_->readInCardIdentificationCommand();
	while (command != QUIT_COMMAND)
    {
		performCardCommand(command);
	    theUI_->showByeScreen();
		command = theUI_->readInCardIdentificationCommand();
	}

}

//---------------------------------------------------------------------------
//private support member functions
//---------------------------------------------------------------------------

void CashPoint::performCardCommand(int option) {
	switch (option)
	{
		case 1:
		{
			//read in card number and check that it is valid
			string cashCardNum;
			string cashCardFilename(theUI_->readInCardToBeProcessed(cashCardNum));	//read in card name & produce cashcard filename
			int validCardCode(validateCard(cashCardFilename));		//check valid card
			theUI_->showValidateCardOnScreen(validCardCode, cashCardNum);
			if (validCardCode == VALID_CARD) //valid card
			{
				//dynamically create a cash card and store card data
				activateCashCard(cashCardFilename);
				//display card data with available accounts
				string s_card(p_theCashCard_->toFormattedString());
				theUI_->showCardOnScreen(s_card);
				//process all request for current card (& bank accounts)
				processOneCustomerRequests();
				//free memory space used by cash card
				releaseCashCard();
			}
			break;
		}
		default:theUI_->showErrorInvalidCommand();
	}
}

int CashPoint::validateCard(const string& filename) const {
	//check that the card exists (valid)
	if (!canOpenFile(filename))   //invalid card
        return UNKNOWN_CARD;
    else    
		//card empty (exist but no bank account listed on card)
		if (!linkedCard(filename))
			return EMPTY_CARD;
		else
			//card valid (exists and linked to at least one bank account)
			return VALID_CARD;
}

int CashPoint::validateAccount(const string& filename) const {
//check that the account is valid 
//NOTE: MORE WORK NEEDED here in case of transfer
	string accountNum = (filename.substr(13, 3).c_str());
	string sortCode = (filename.substr(17, 5).c_str());
	if (!canOpenFile(filename))
		//account does not exist
		return UNKNOWN_ACCOUNT;
	else
		//unaccessible account (exist but not listed on card)
		if (!p_theCashCard_->onCard(filename))
			return UNACCESSIBLE_ACCOUNT;
		else
			if (p_theActiveAccount_ != NULL)
			{
				if ((p_theActiveAccount_->getAccountNumber() == accountNum) && (p_theActiveAccount_->getSortCode() == sortCode))
				{
					return SAME_ACCOUNT;
				}
				else
					return VALID_ACCOUNT;
			}
		else
			//account valid (exists and accessible)
			return VALID_ACCOUNT;
}

void CashPoint::processOneCustomerRequests() {
//process from one account
    string anAccountNumber, anAccountSortCode;
    //select active account and check that it is valid
	string bankAccountFilename(theUI_->readInAccountToBeProcessed(anAccountNumber, anAccountSortCode));
	int validAccountCode(validateAccount(bankAccountFilename));  //check valid account
	theUI_->showValidateAccountOnScreen(validAccountCode, anAccountNumber, anAccountSortCode);
    if (validAccountCode == VALID_ACCOUNT) //valid account: exists, accessible with card & not already open
    {
       	//dynamically create a bank account to store data from file
        p_theActiveAccount_ = activateBankAccount(bankAccountFilename);
		//process all request for current card (& bank accounts)
    	processOneAccountRequests();
		//store new state of bank account in file & free bank account memory space
        p_theActiveAccount_ = releaseBankAccount(p_theActiveAccount_, bankAccountFilename);
    }
}

void CashPoint::processOneAccountRequests() {
    int option;
	//select option from account processing menu
	option = theUI_->readInAccountProcessingCommand();
	while (option != QUIT_COMMAND)
	{
		performAccountProcessingCommand(option);   //process command for selected option

		theUI_->wait();
		option = theUI_->readInAccountProcessingCommand();   //select another option
	}
}

void CashPoint::performAccountProcessingCommand(int option) {
	switch (option)
	{
		case 1:	m1_produceBalance();
				break;
		case 2: m2_withdrawFromBankAccount();
 				break;
		case 3:	m3_depositToBankAccount();
				break;
		case 4:	m4_produceStatement();
				break;
		case 5: m5_showAllDepositsTransactions();
				break;
		case 6: m6_showMiniStatement();
				break;
		case 7: m7_searchForTransactions();
				break;
		case 8: m8_clearTransactionsUpToDate();
				break;
		case 9: m9_showFundsAvailableOnAllAccounts();
				break;
		case 10: m10_transferCashToAnotherAccount();
				break;
		default:theUI_->showErrorInvalidCommand();
	}
}
//------ menu options
//---option 1
void CashPoint::m1_produceBalance() const 
{	//option to show balance
	assert(p_theActiveAccount_ != nullptr);
	double balance(p_theActiveAccount_->getBalance());
	theUI_->showProduceBalanceOnScreen(balance);
}

//---option 2
void CashPoint::m2_withdrawFromBankAccount() 
{	//option to withdraw money from bank account
	assert(p_theActiveAccount_ != nullptr);
	double amountToWithdraw(theUI_->readInWithdrawalAmount());
    bool transactionAuthorised(p_theActiveAccount_->canWithdraw(amountToWithdraw));
    if (transactionAuthorised)
    {   //transaction is accepted: money can be withdrawn from account
        p_theActiveAccount_->recordWithdrawal(amountToWithdraw);
    }   //else do nothing
	theUI_->showWithdrawalOnScreen(transactionAuthorised, amountToWithdraw);
}
//---option 3
void CashPoint::m3_depositToBankAccount() 
{	//option to deposit money into bank account
	assert(p_theActiveAccount_ != nullptr);
	double amountToDeposit(theUI_->readInDepositAmount());
	bool transactionAuthorised(p_theActiveAccount_->canDeposit(amountToDeposit));
	if (transactionAuthorised)
	{   //transaction is accepted: money can be withdrawn from account
		p_theActiveAccount_->recordDeposit(amountToDeposit);
	}   //else do nothing
	theUI_->showDepositOnScreen(transactionAuthorised, amountToDeposit);
}
//---option 4
void CashPoint::m4_produceStatement() const 
{	//provides a statement of the bank account
	assert(p_theActiveAccount_ != nullptr);
	theUI_->showStatementOnScreen(p_theActiveAccount_->prepareFormattedStatement());
}
//---option 5
void CashPoint::m5_showAllDepositsTransactions() const 
{	//shows all deposit transactions made
	assert(p_theActiveAccount_ != nullptr);
	//1: noTransaction:= isEmptyTransactionList(): boolean
	bool noTransaction(p_theActiveAccount_->isEmptyTransactionList());
	string str;
	double total(0.0);
	if (!noTransaction){
		//2: [~noTransaction] produceAllDepositTransactions():
		p_theActiveAccount_->produceAllDepositTransactions(str, total);
	}
	theUI_->showAllDepositsOnScreen(noTransaction, str, total);

	//3: showAllDepositsOnScreen (noTransaction, str, total)

}
//---option 6
void CashPoint::m6_showMiniStatement() const 
{	//show a mini-statement
	assert(p_theActiveAccount_ != nullptr);
	// 1. noTransaction:= isEmptyTransactionList(): boolean
	bool noTransaction(p_theActiveAccount_->isEmptyTransactionList());
	string str;
	double total(0.0);
	if (!noTransaction){
		//2:[~noTransaction] readInNumberOfTransactions() : integer
		int theNumberOfTransactions(theUI_->readInNumberOfTransactions());
		//3.[~noTransaction] produceNMostRecentTransactions(integer) :string x double
		p_theActiveAccount_->produceNMostRecentTransactions(str, theNumberOfTransactions, total);
	}
	//4. mad:= prepareFormattedMiniAccountDetails(): string
	string mad = p_theActiveAccount_->prepareFormattedMiniAccountDetails();
	//5: showMiniStatementOnScreen	(noTransaction, total, mad + str)
	theUI_->showMiniStatementOnScreen(noTransaction, mad + str, total);
}
//---option 7
void CashPoint::m7_searchForTransactions() const 
{	//search for transactions through either amount, title or date
	assert(p_theActiveAccount_ != nullptr);
	bool noTransaction(p_theActiveAccount_->isEmptyTransactionList());
	//2:[noTransaction] showNoTransactionsOnScreen()
	if (noTransaction)
	{
		//theUI_.showNoTransactionsOnScreen();
		theUI_->showNoTransactionsOnScreen();
	}
	//3:[~noTransaction] searchTransactions()
	if (!noTransaction)
	{
		//3.1 showSearchMenu()
		theUI_->showSearchMenu();
		//3.2. opt:= readInSearchCommand(): int
		int opt = theUI_->readInSearchCommand();

		switch (opt)
		{
			//3.3 [opt = 1] m7a_showTransactionsForAmount()
		case 1:	m7a_showTransactionsForAmount();
			break;
			//3.3 [opt = 2] m7b_showTransactionsForTitle()
		case 2: m7b_showTransactionsForTitle();
			break;
			//3.3 [opt = 3] m7c_showTransactionsForDate()
		case 3:	m7c_showTransactionsForDate();
			break;
		}
	}
}
////Templates Work Not Quite done have a issue with produceTransations
//template <typename T>
//void CashPoint::m7_showTransactions() const
//{	//shows transactions for amount provided
//	//1: a : = readInAmount() : double
//	int n = 0;
//	double a = theUI_->readInAmount();
//	string str;
//	//2. produceTransactionsForAmount(a): string x integer
//	p_theActiveAccount_->produceTransactionsForAmount(a, n, str);
//	//3: showMatchingTransactionsOnScreen(a, n, str)
//	theUI_->showMatchingTransactionsOnScreen(a, n, str);
//}

//option 7.1
void CashPoint::m7a_showTransactionsForAmount() const
{	//shows transactions for a amount  provided
		//1: a : = readInAmount() : double
		int n = 0;
		double a = theUI_->readInAmount();
		string str;
		//2. produceTransactionsForAmount(a): string x integer
		p_theActiveAccount_->produce(a, n, str);
		//3: showMatchingTransactionsOnScreen(a, n, str)
		theUI_->showMatchingTransactionsOnScreen(a, n, str);
}

//option 7.2
void CashPoint::m7b_showTransactionsForTitle() const 
{	//shows transactions for a title provided
	int n = 0;
	string title = theUI_->readInTitle();
	string str;
	p_theActiveAccount_->produce(title, n, str);
	theUI_->showMatchingTransactionsOnScreenTitle(title, n, str);
}
//option 7.3
void CashPoint::m7c_showTransactionsForDate() const 
{	//shows transactions up to a given date
	int n = 0;
	Date dateOfTrans = theUI_->readInDate();
	string str;
	p_theActiveAccount_->produce(dateOfTrans, n, str);
	theUI_->showMatchingTransactionsOnScreenDate(dateOfTrans, n, str);

}
//option 8
void CashPoint::m8_clearTransactionsUpToDate() const 
{	//clears transactions up to certain date
	assert(p_theActiveAccount_ != nullptr);
	//1. noTransaction:= isEmptyTransactionList(): boolean
	bool noTransaction(p_theActiveAccount_->isEmptyTransactionList());
	string str;
	int n = 0;
	if (!noTransaction)
	{
		//2. [~noTransaction] cd:= getCreationDate(): Date	
		Date cd = p_theActiveAccount_->getCreationDate();
		//3. [~noTransaction]d : = readInValidDate(cd) : Date
		Date d = theUI_->readInValidDate(cd);
		//4. [~noTransaction] produceTransactionsUpToDate(d): string x integer
		p_theActiveAccount_->produceTransactionsUpToDate(d, str, n);
		//5: showTransactionsUpToDateOnScreen (noTransaction, d, n, str)
		theUI_->showTransactionsUpToDateOnScreen(noTransaction, d, n, str);
		if (!noTransaction && !str.empty())
		{
			//6: [~noTransaction and str ≠empty] deletionConfirmed := readInConfirmDeletion() : boolean
			bool deletionConfirmed = theUI_->readInConfirmDeletion();
			if ((!noTransaction) && (!str.empty()) && (deletionConfirmed))
			{
				//7. [~noTransaction and str ≠ empty and deletionConfirmed] recordDeletionOfTransactionUpToDate(d)
				p_theActiveAccount_->recordDeletionOfTransactionUpToDate(d);
			}
			//8: [~noTransaction and str ≠empty] showDeletionOfTransactionsUpToDateOnScreen (n, d, deletionConfirmed)
			theUI_->showDeletionOfTransactionsUpToDateOnScreen(n, d, deletionConfirmed);
		}
	}
}

//option 9
void CashPoint::m9_showFundsAvailableOnAllAccounts() 
{	//shows funds available on all accounts
	assert(p_theActiveAccount_ != nullptr);
	//1: accts : = getAccountsList() : List<string>
	List<string> accts = p_theCashCard_->getAccountsList();
	//2: empty:= isEmpty(): boolean
	bool empty = accts.isEmpty();
	double m = 0.0;
	string mad;
	string account;
	while (!accts.isEmpty())
	{
	//3: first(): string
		account = accts.first();
	//4: pacct:= activateBankAccount(string): 	BankAccount*
		BankAccount* p_acct_ = activateBankAccount(FILEPATH + "account_" + account + ".txt");
	//5: m:= maxWithdrawalAllowed(): double
		m += p_acct_->maxWithdrawalAllowed();
	//6: mad:= prepareFormattedMiniAccountDetails():  string
		mad += p_acct_->prepareFormattedMiniAccountDetails();
	//7: releaseBankAccount(BankAccount*, string): BankAccount*
		releaseBankAccount(p_acct_, FILEPATH + "account_" + account + ".txt");
	//8:  deleteFirst()
		accts.deleteFirst();
	}
	//9: showFundsAvailableOnScreen(empty, string, double)
	theUI_->showFundsAvailableOnScreen(empty, mad, m);
}
//option 10
void CashPoint::m10_transferCashToAnotherAccount() 
{	//allows the transfer of cash from one account to another
	//1: toFormattedString(): string
	string card = p_theCashCard_->toFormattedString();
	//2: showCardOnScreen(string)
	theUI_->showCardOnScreen(card);
	//3: readInAccountToBeProcessed(): 	string x string x string
	string accountNumber;
	string sortCode;
	BankAccount* p_transferAccount(nullptr);
	theUI_->readInAccountToBeProcessed(accountNumber, sortCode);
	//4: validAccountCode:=validateAccount(string): integer
	int validAccountCode = validateAccount(FILEPATH + "account_" + accountNumber + "_" + sortCode + ".txt");
	//5: showValidateAccountOnScreen(validAccountCode, string, string)
	theUI_->showValidateAccountOnScreen(validAccountCode, accountNumber, sortCode);
	//6: [validAccountCode is 0] activateBankAccount(string):BankAccount*
	if (validAccountCode == VALID_ACCOUNT)
	{
		p_transferAccount = activateBankAccount(FILEPATH + "account_" + accountNumber + "_" + sortCode + ".txt");
		//6.1: checkAccountType(string): integer
		int type = checkAccountType(FILEPATH + "account_" + accountNumber + "_" + sortCode + ".txt");
		switch (type)
		{
		case BANKACCOUNT_TYPE:	//NOT NEEDED WITH ABSTRACT CLASSES
			//6.2: createBankAccount(string) : BankAccount*
			p_transferAccount = new BankAccount;
			break;
		case CURRENTACCOUNT_TYPE:	//NOT NEEDED WITH ABSTRACT CLASSES
			//6.2: createBankAccount(string) : currentaccount*
			p_transferAccount = new CurrentAccount;
			break;
		case SAVINGSACCOUNT_TYPE:
			//6.2: createBankAccount(string) : savingsaccount*
			p_transferAccount = new SavingsAccount;
			break;
		case CHILDACCOUNT_TYPE:
			//6.2: createBankAccount(string) : childaccount*
			p_transferAccount = new ChildAccount;
			break;
		case ISAACCOUNT_TYPE:
			//6.2: createBankAccount(string) : isaaccount*
			p_transferAccount = new ISAAccount;
			break;
		}
		//6.3: readBankAccountFromFile(string)
		p_transferAccount->readInBankAccountFromFile(FILEPATH + "account_" + accountNumber + "_" + sortCode + ".txt");
	}
	//7: [validAccountCode is 0] attemptTransfer(BankAccount*)
	if (validAccountCode == 0)
	{
		attemptTransfer(p_transferAccount);
	//8: [validAccountCode is 0] releaseBankAccount(BankAccount*, string) :BankAccount*
		releaseBankAccount(p_transferAccount, FILEPATH + "account_" + accountNumber + "_" + sortCode + ".txt");
	}
}
void CashPoint::attemptTransfer(BankAccount* p_transferAccount)	
{	//attempts to make transfer from one account to another and if successful, calls 'recordTransfer'
	//7.1: transferAmount:= readInTransferAmount():double
	double transferAmount = theUI_->readInTransferAmount();
	//7.2: trOutOK:= canTransferOut(transferAmount): boolean
	bool trOutOK = p_theActiveAccount_->canTransferOut(transferAmount);
	//7.3: trInOK := canTransferIn(transferAmount): boolean
	bool trInOK = p_transferAccount->canTranferIn(transferAmount);
	if (trOutOK && trInOK)
	{
		//7.4: [trOutOK and trInOK] recordTransfer(transferAmount, BankAccount*)
		recordTransfer(transferAmount, p_transferAccount);
	}
	//7.5: showTransferOnScreen(trOutOK, trInOK, transferAmount)
	theUI_->showTransferOnScreen(trOutOK, trInOK, transferAmount);
}

void CashPoint::recordTransfer(double transferAmount, BankAccount* p_transferAccount)	{
	//7.4.1: tAN:= getAccountNumber(): string
	string tAN = p_transferAccount->getAccountNumber();
	//7.4.2: tSC := getSortCode(): string
	string tSC = p_transferAccount->getSortCode();
	//7.4.3: recordTransferOut(transferAmount, tAN, tSC)
	p_theActiveAccount_->recordTransferOut(transferAmount, tAN, tSC);
	//7.4.4: aAN:= getAccountNumber(): string
	string aAN = p_theActiveAccount_->getAccountNumber();
	//7.4.5: aSC:= getSortCode(): string
	string aSC = p_theActiveAccount_->getSortCode();
	//7.4.6: recordTransferIn(transferAmount, aAN, aSC)
	p_transferAccount->recordTransferIn(transferAmount, aAN, aSC);
}
//------private file functions

bool CashPoint::canOpenFile(const string& filename) const {
//check if a file already exist
	ifstream inFile;
	inFile.open(filename.c_str(), ios::in); 	//open file
	//if does not exist fail, otherwise open file but do nothing to it
	bool exist;
    if (inFile.fail())
        exist = false;
    else
        exist = true;
    inFile.close();			//close file: optional here
    return exist;
}
bool CashPoint::linkedCard(string cashCardFileName) const {
//check that card is linked with account data
	ifstream inFile;
	inFile.open(cashCardFileName.c_str(), ios::in); 	//open file
 	bool linked(false);
	if (! inFile.fail()) //file should exist at this point 
	{	//check that it contain some info in addition to card number
		string temp;
		inFile >> temp; //read card number
		inFile >> temp;	//ready first account data or eof
		if (inFile.eof())
			linked = false;
		else
			linked = true;
		inFile.close();			//close file: optional here
	}
	return linked;
}

void CashPoint::activateCashCard(const string& filename) {
//dynamically create a cash card to store data from file
    //effectively create the cash card instance with the data
	p_theCashCard_ = new CashCard;
	assert(p_theCashCard_ != nullptr);
	p_theCashCard_->readInCardFromFile(filename);
}

void CashPoint::releaseCashCard() {
//release the memory allocated to the dynamic instance of a CashCard
	delete p_theCashCard_;
	p_theCashCard_ = nullptr;
}

int CashPoint::checkAccountType(const string& filename) const {
    //(simply) identify type/class of account from the account number
    //start with 0 for bank account, 1 for current account, 2 for saving account, etc.
	return(atoi(filename.substr(13, 1).c_str())); //13th char from the filename ("data/account_101_00-44.txt")
}

BankAccount* CashPoint::activateBankAccount(const string& filename) {
	//check the type of the account (already checked for validity)
	int accType(checkAccountType(filename));
    //effectively create the active bank account instance of the appropriate class
	//& store the appropriate data read from the file
	BankAccount* p_BA(nullptr);
	switch(accType)
    {
     	case BANKACCOUNT_TYPE:	//NOT NEEDED WITH ABSTRACT CLASSES
     		p_BA = new BankAccount;    //points to a BankAccount object
			assert(p_BA != nullptr);
			p_BA->readInBankAccountFromFile(filename); //read account details from file
			break;
		case CURRENTACCOUNT_TYPE:	//NOT NEEDED WITH ABSTRACT CLASSES
			p_BA = new CurrentAccount;
			assert(p_BA != nullptr);
			p_BA->readInBankAccountFromFile(filename); //read account details from file
			break;
		case SAVINGSACCOUNT_TYPE:
			p_BA = new SavingsAccount;
			assert(p_BA != nullptr);
			p_BA->readInBankAccountFromFile(filename); //read account details from file
			break;
		case CHILDACCOUNT_TYPE:
			p_BA = new ChildAccount;
			assert(p_BA != nullptr);
			p_BA->readInBankAccountFromFile(filename); //read account details from file
			break;
		case ISAACCOUNT_TYPE:
			p_BA = new ISAAccount;
			assert(p_BA != nullptr);
			p_BA->readInBankAccountFromFile(filename); //read account details from file
			break;
    }
	//use dynamic memory allocation: the bank account created will have to be released in releaseBankAccount
	return p_BA;
}

BankAccount* CashPoint::releaseBankAccount(BankAccount* p_BA, string filename) {
//store (possibly updated) data back in file
	assert(p_BA != nullptr);
	p_BA->storeBankAccountInFile(filename);
	//effectively destroy the bank account instance
	delete p_BA;
	return nullptr;
}