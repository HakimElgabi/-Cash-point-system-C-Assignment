//Pascale Vacher - March 17
//OOP Assignment Task 1c - Semester 2
//Group Number: 21
//Team: (Software Engineers - Hakim Elgabi(b5015647), Hamud Ibrahim(b5011597), Atiq Rafiq(b5009186), Shahid Ghafoor(b5012414))

#include "UserInterface.h"

//---------------------------------------------------------------------------
//UserInterface: class implementation
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//public member functions
//---------------------------------------------------------------------------

void UserInterface::wait() const {
	char ch;
	cout << "\n\nPress RETURN to go back to menu\n";
	cin.get(ch);
	cin.get(ch);
//	flushall();
}
int UserInterface::readInCardIdentificationCommand() const {
    showCardIdentificationMenu();
    return (readInCommand());
}
void UserInterface::showCardIdentificationMenu() const {
	cout << "\n\n\n      ________________________________________";
	cout << "\n      _______CARD IDENTIFICATION MENU________";
	cout << "\n      ________________________________________";
	cout << "\n       0           Quit CashPoint application";
	cout << "\n       1              Enter your card details";
	cout << "\n      ________________________________________";
}
int UserInterface::readInAccountProcessingCommand() const{
    showAccountProcessingMenu();
    return (readInCommand());
}
void UserInterface::showAccountProcessingMenu() const {
	cout << "\n\n\n      ________________________________________";
	cout << "\n      ________ACCOUNT PROCESSING MENU________";
	cout << "\n      ________________________________________";
	cout << "\n       0 End account processing & remove card";
	cout << "\n       1                      Display balance";
	cout << "\n       2                Withdraw from account";
	cout << "\n       3                 Deposit into account";
	cout << "\n       4                       Show statement";
	cout << "\n       5                    Show all deposits";
	cout << "\n       6                  Show mini statement";
	cout << "\n       7                  Search Transactions  //TO BE CLEANED UP FOR Task 1c";
	cout << "\n       8    Clear all transactions up to date";
	cout << "\n       9                 Show Funds Available";
	cout << "\n       10         Transfer to Another Account  //TO BE CLEANED UP FOR Task 1c";
	cout << "\n         ________________________________________";
}

const string UserInterface::readInCardToBeProcessed(string& cardNumber) const {
	cout << "\n SELECT THE CARD ...\n";
	cout << "   CARD NUMBER:  ";         //ask for card number
    cin >> cardNumber;
    cout << "\n=========================================";
    //create card file name
    return(FILEPATH + "card_" + cardNumber + ".txt");
}

void UserInterface::showValidateCardOnScreen(int validCode, const string& cardNumber) const {
    switch(validCode)
    {
    	case VALID_CARD:		//card valid: it exists, is accessible with that card (and not already open: TO BE IMPLEMENTED)
			cout << "\nTHE CARD (NUMBER: " << cardNumber << ") EXIST!";
            break;
    	case UNKNOWN_CARD:		//card does not exist
			cout << "\nERROR: INVALID CARD\n"
				<< "\nTHE CARD (NUMBER: " << cardNumber << ") DOES NOT EXIST!";
            break;
    	case EMPTY_CARD:		//account exists but is not accessible with that card
        	cout << "\nERROR: EMPTY CARD"
				<< "\nTHE CARD (NUMBER: " << cardNumber << ") DOES NOT LINK TO ANY ACCOUNT!";
             break;
    }
}

void UserInterface::showCardOnScreen(const string& cardDetails) const {
    cout << "\n=========================================";
    cout << "\n________ CARD DETAILS ___________________";
	cout << cardDetails;
    cout << "\n________ END CARD DETAILS _______________";
    cout << "\n=========================================";
}

const string UserInterface::readInAccountToBeProcessed(string& accountNumber, string& sortCode) const {
    cout << "\n SELECT THE ACCOUNT ...\n";
	cout << "   ACCOUNT NUMBER:  ";	//ask for account number
	cin >> accountNumber;
	cout << "   SORT CODE:       ";	//ask for sort code
	cin >> sortCode;
    cout << "\n=========================================";
    //create account file name
	return(FILEPATH + "account_" + accountNumber + "_" + sortCode + ".txt");
}

void UserInterface::showValidateAccountOnScreen(int validCode, const string& accNum, const string& sortCode) const {
    switch(validCode)
    {
    	case VALID_ACCOUNT:		//account valid: it exists, is accessible with that card (and not already open: TO BE IMPLEMENTED)
        	cout << "\nTHE ACCOUNT (NUMBER: " << accNum
             	 << " CODE: " << sortCode << ") IS NOW OPEN!";
            break;
    	case UNKNOWN_ACCOUNT:		//account does not exist
        	cout << "\nERROR: INVALID ACCOUNT"
                 << "\nTHE ACCOUNT (NUMBER: " << accNum
                 << " CODE: " << sortCode << ") DOES NOT EXIST!";
            break;
    	case UNACCESSIBLE_ACCOUNT:		//account exists but is not accessible with that card
        	cout << "\nERROR: INVALID ACCOUNT"
             	 << "\nTHE ACCOUNT (NUMBER: " << accNum
             	 << " CODE: " << sortCode << ") IS NOT ACCESSIBLE WITH THIS CARD!";
            break;
		case SAME_ACCOUNT:		//account valid: it exists, is accessible with that card (and not already open: TO BE IMPLEMENTED)
			cout << "\nTHE ACCOUNT (NUMBER: " << accNum
				<< " CODE: " << sortCode << ") IS ALLREADY OPEN!";
			break;
    }
}

//input functions

double UserInterface::readInWithdrawalAmount() const {
    //ask for the amount to withdraw
    cout << "\nAMOUNT TO WITHDRAW: \234" ;
	return (readInPositiveAmount());
}
double UserInterface::readInDepositAmount() const {
    //ask for the amount to deposit
    cout << "\nAMOUNT TO DEPOSIT: \234" ;
	return (readInPositiveAmount());
}
//output functions

void UserInterface::showProduceBalanceOnScreen(double balance) const {
	cout << fixed << setprecision(2) << setfill(' ');
    cout << "\nTHE CURRENT BALANCE IS: \234" << setw(12) << balance;	//display balance
}
void UserInterface::showWithdrawalOnScreen(bool trAuthorised, double withdrawnAmount) const {
    if (trAuthorised)
    	cout << "\nTRANSACTION AUTHORISED!: \n\234"
			 << setw(0) << withdrawnAmount
             << " WITHDRAWN FROM ACCOUNT";
    else //not enough money
		cout << "\nTRANSACTION IMPOSSIBLE!";
}
void UserInterface::showDepositOnScreen(bool trAuthorised, double depositAmount) const {
    if (trAuthorised)
    	cout << "\nTRANSACTION AUTHORISED!:\n\234"
			 << setw(0) << depositAmount
             << " DEPOSITED INTO ACCOUNT";
    else //too much to deposit
		cout << "\nTRANSACTION IMPOSSIBLE!";
}
void UserInterface::showStatementOnScreen(const string& statement) const {
    cout << "\nPREPARING STATEMENT...\n";
    cout << "\n________ ACCOUNT STATEMENT _____\n";
	cout << statement;
    cout << "\n\n________ END ACCOUNT STATEMENT _____";
}
void UserInterface::showAllDepositsOnScreen(bool noTransaction, const string& str, double total) const{

	cout << "\nALL DEPOSIT TRANSACTIONS REQUESTED AT " << Time::currentTime().toFormattedString() << " ON " << Date::currentDate().toFormattedString();

	if (noTransaction)
		cout << "\nNO TRANSACTIONS IN BANK ACCOUNT"; // needs formatting****************************************
	else
	{
		cout << "\n" << str;
		cout << fixed << setprecision(2) << setfill(' ');
		cout << "\nTHE CURRENT BALANCE IS: \234" << setw(12);
		cout << "\nCalulated Amount: " << total;
	}
}

int UserInterface::readInNumberOfTransactions() const{
	cout << "\n HOW MANY RECENT TRANSACTIONS YOU WANT TO SEE ";
	return(readInPositiveNumber());
}

void UserInterface::showMiniStatementOnScreen(bool noTransaction, const string& mad, double total) const{
	
	cout << "\nALL TRANSACTIONS REQUESTED AT " << Time::currentTime().toFormattedString() << " ON " << Date::currentDate().toFormattedString();
	if (noTransaction)
		cout << "\nNO TRANSACTIONS IN BANK ACCOUNT";
	else
	{
		cout << "\n" << mad;
		cout << "\nCumulated Amount: " << total;
	}
}

void UserInterface::showSearchMenu() const{

	cout << "\n\n\n      ________________________________________";
	cout << "\n     ________ACCOUNT SEARCH MENU________";
	cout << "\n     ________________________________________";
	cout << "\n       0				Exit";
	cout << "\n       1				Amount Search";
	cout << "\n       2				Title Search";
	cout << "\n       3				Date Search";
	cout << "\n		________________________________________";
}
void UserInterface::showMatchingTransactionsOnScreen(double a, int n, const string& str) const {
	if (n == 0)
	{
		cout << "\nNO TRANSACTION IN BANK ACCOUNT MATCH THE SEARCH CRITERION GIVEN";
	}
	else
	{
		cout << "\nALL TRANSACTIONS REQUESTED AT " << Time::currentTime().toFormattedString() << " ON " << Date::currentDate().toFormattedString();
		cout << "\n" << str;
		cout << "\nCumulated Amount: " << n;
	}
	
}

void UserInterface::showMatchingTransactionsOnScreenTitle(const string& title, int n, const string& str) const {
	if (n == 0)
	{
		cout << "\nNO TRANSACTION IN BANK ACCOUNT MATCH THE SEARCH CRITERION GIVEN";
	}
	else
	{
		cout << "\nALL TRANSACTIONS REQUESTED AT " << Time::currentTime().toFormattedString() << " ON " << Date::currentDate().toFormattedString();
		cout << "\n" << str;
		cout << "\nCumulated Amount: " << n;
	}
}

void UserInterface::showMatchingTransactionsOnScreenDate(const Date& dateOfTrans, int& n, const string& str) const {
	if (n == 0)
	{
		cout << "\nNO TRANSACTION IN BANK ACCOUNT MATCH THE SEARCH CRITERION GIVEN";
	}
	else
	{
	cout << "\nALL TRANSACTIONS REQUESTED AT " << Time::currentTime().toFormattedString() << " ON " << Date::currentDate().toFormattedString();
	cout << "\n" << str;
	cout << "\nCumulated Amount: " << n;
	}
	
}
void UserInterface::showTransactionsUpToDateOnScreen(bool noTransaction, const Date& d, int&n, const string& str) const {
	if (noTransaction)
	cout << "\n\nNO TRANSACTIONS IN BANK ACCOUNT";
	else
	{
		cout << "AMOUNT OF TRANSATIONS FOUND: " << n;
		cout << "\nALL TRANSACTIONS REQUESTED AT " << Time::currentTime().toFormattedString() << " ON " << Date::currentDate().toFormattedString();
		cout << "\n" << str;
	}
}
void UserInterface::showDeletionOfTransactionsUpToDateOnScreen(int& n, const Date& d, bool& deletionConfirmed) const {
	if (deletionConfirmed)
	{
		cout << "\nDELETION COMPLETE";
		cout << "\nTHE "<< n << " TRANSACTIONS IN THE BANK ACCOUNT UP TO THE DATE " << d << " HAVE BEEN DELETED" ;
	}
	else
		cout << "\nDELETION CANCELLED";
}

void UserInterface::showFundsAvailableOnScreen(bool& empty, const string& mad, double& m) const{
	if (empty)
		cout << "\nNO ACCOUNT ACCESSIBLE WITH THIS CARD!"; // needs formatting****************************************
	else
	{
		cout << "\nBANK ACCOUNT(S)";
		cout << "\n" << mad;
		cout << fixed << setprecision(2) << setfill(' ');
		cout << "\nTOTAL AMOUNT AVAILABLE: \234" << setw(12) << m;
	}
}
void UserInterface::showTransferOnScreen(bool& trOutOK, bool& trInOK, double& transferAmount) const{
	cout << "\n _*_ATTEMPTING TRANSFER_*_";
	if (trOutOK && trInOK)
		cout << "\n TOTAL TRANSFER: \234" << setw(12) << transferAmount;
	else
	if (!trInOK)
		cout << "\n CANNOT TRANSER IN TO THIS ACCOUNT";
	else
	if (!trOutOK)
		cout << "\n INSUFFICANT FUNDS TO TRANSFER OUT";
}

void UserInterface::showNoTransactionsOnScreen() const
{
	cout << "\n NO TRANSACTIONS IN BANK ACCOUNT";
}
//---------------------------------------------------------------------------
//private support member functions
//---------------------------------------------------------------------------

void UserInterface::showWelcomeScreen() const {
	cout << "\n\n\n             _____WELCOME TO THE ATM_____";
}
void UserInterface::showByeScreen() const {
    cout << "\n\n\n________________NEXT CUSTOMER...\n\n";
}
int UserInterface::readInCommand() const{
	int com;
	cout << "\n          ENTER YOUR COMMAND: ";
	cin >> com;
	return com;
}
void UserInterface::showErrorInvalidCommand() const {
	cout << "\nINVALID COMMAND CHOICE, TRY AGAIN";
}
double UserInterface::readInPositiveAmount() const {
    double amount;
	cin >> amount;
	while (amount <= 0.0)
    {
	    cout << "\nAMOUNT SHOULD BE A POSITIVE AMOUNT, TRY AGAIN: ";
		cin >> amount;
	}
    return amount;
}
int UserInterface::readInPositiveNumber() const {
	int transactions;
	cin >> transactions;
	while (transactions <= 0)
	{
		cout << "\nVALUE SHOULD BE A POSITIVE VALUE, TRY AGAIN: ";
		cin >> transactions;
	}
	return transactions;
}

int UserInterface::readInSearchCommand() const {
	int transSearch;
	cout << "\n          ENTER YOUR COMMAND: ";
	cin >> transSearch;
	
	while ((transSearch < 0) || (transSearch > 3))
	{
		cout << "\nVALUE SHOULD BE A CORRECT VALUE, TRY AGAIN: ";
		cin >> transSearch;
	}
	return transSearch;
}

double UserInterface::readInAmount() const {
	double amountSearch;
	cout << "\n          ENTER THE AMOUNT YOU WANT TO SEARCH: ";
	cin >> amountSearch;
	while (cin.fail()) {
		cin.clear();
		cin.ignore(256, '\n');
		cout << "MUST ENTER A VALID VALUE: ";
		cin >> amountSearch;
	}
	return amountSearch;
}
string const UserInterface::readInTitle() const {
	string title;
	cout << "\n          ENTER THE TITLE YOU WANT TO SEARCH: ";
	cin >> title;
	return title;
}
Date UserInterface::readInDate() const {
	Date amountSearch;
	cout << "\n          ENTER THE DATE YOU WANT TO SEARCH UP TO (e.g. 12/12/2016): ";
	cin >> amountSearch;
	bool isval = false;
	isval = Date::isValid(amountSearch);
	while (!isval)
	{
		cout << "\nINVALID DATE, TRY AGAIN: ";
		cin >> amountSearch;
		isval = Date::isValid(amountSearch);
	}
	return amountSearch;
}
Date UserInterface::readInValidDate(Date& cd) const{

	//3.1: isValid(Date) : boolean
	bool isval = false;
	Date dateOfDelete;	
	cout << "\n          ENTER THE DATE YOU WANT TO SEARCH (e.g. 12/12/2016): ";
	cin >> dateOfDelete;
	isval = Date::isValid(dateOfDelete);
	if (dateOfDelete < cd)
		isval = false;
	while (!isval)
	{
		cout << "\nINVALID DATE, TRY AGAIN: ";
		cin >> dateOfDelete;
		isval = Date::isValid(dateOfDelete);
		if (dateOfDelete < cd)
			isval = false;
	}
	return dateOfDelete;
}
bool UserInterface::readInConfirmDeletion() const{
	bool wantToDelete;
	char reply;
	cout << "\n          ARE YOU SURE YOU WANT TO DELETE THIS TRANSACTION?";
	cout << "\n          Enter 'y' FOR 'YES' AND 'n' FOR 'NO': ";
	cin >> reply;
	while ((reply != 'y') && (reply != 'n'))
	{
		cout << "\nINCORRECT INPUT: Enter 'y' FOR 'YES' AND 'n' FOR 'NO': ";
		cin >> reply;
	}
	if (reply == 'y')
	{
		wantToDelete = true;
	}
	else {
		wantToDelete = false;
	}
	return wantToDelete;
}

double	UserInterface::readInTransferAmount() const{
	int amount;
	cout << "\nPLEASE ENTER THE AMOUNT YOU WISH TO TRANSFER: ";
	cin >> amount;
	while (amount <= 0)
	{
		cout << "\nVALUE SHOULD BE A POSITIVE VALUE, TRY AGAIN: ";
		cin >> amount;
	}
	return amount;
}