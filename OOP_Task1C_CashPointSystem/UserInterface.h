//Pascale Vacher - March 17
//OOP Assignment Task 1c - Semester 2
//Group Number: 21
//Team: (Software Engineers - Hakim Elgabi(b5015647), Hamud Ibrahim(b5011597), Atiq Rafiq(b5009186), Shahid Ghafoor(b5012414))


#ifndef UserInterfaceH 
#define UserInterfaceH

//---------------------------------------------------------------------------
//UserInterface: class declaration
//---------------------------------------------------------------------------

#include "constants.h"
#include "Time.h"
#include "Date.h"

#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

class UserInterface {
public:
	/*singleton pattern (doesn't work yet)*/
	static UserInterface* getInstance()
	{
		static UserInterface instance;
		return &instance;
	}

    void	showWelcomeScreen() const;
    void	showByeScreen() const;

	int		readInCardIdentificationCommand() const;
	int		readInAccountProcessingCommand() const;

	void	showErrorInvalidCommand() const;
    void	wait() const;
	const string	readInCardToBeProcessed(string& cardNum) const;
    void	showValidateCardOnScreen(int validCode, const string& cardNum) const;
	void	showCardOnScreen(const string& cardSt) const;
	const string  readInAccountToBeProcessed(string& aNum, string& sCod) const;
	void	showValidateAccountOnScreen(int valid, const string& aNum, const string& sCod) const;

    double	readInWithdrawalAmount() const;
    double	readInDepositAmount() const;

    void	showProduceBalanceOnScreen(double bal) const;
    void	showDepositOnScreen(bool auth, double deposit) const;
    void	showWithdrawalOnScreen(bool auth, double withdrawal) const;
    void	showStatementOnScreen(const string&) const;

	void	showAllDepositsOnScreen(bool noTransaction, const string& str, double total) const;
	int 	readInNumberOfTransactions() const;
	void	showMiniStatementOnScreen(bool noTransaction, const string& mad, double total) const;
	void	showSearchMenu()const;
	int		readInSearchCommand() const;
	double	readInAmount() const;
	void	showMatchingTransactionsOnScreen(double a, int n, const string& str) const;
	const string	readInTitle() const;
	void	showMatchingTransactionsOnScreenTitle(const string& title, int n, const string& str) const;
	Date	readInDate() const;
	void	showMatchingTransactionsOnScreenDate(const Date& dateOfTrans, int& n, const string& str) const;
	Date	readInValidDate(Date& cd) const;
	void	showTransactionsUpToDateOnScreen(bool noTransaction, const Date& d, int&n, const string& str) const;
	bool	readInConfirmDeletion() const;
	void	showDeletionOfTransactionsUpToDateOnScreen(int& n, const Date& d, bool& deletionConfirmed) const;
	void	showFundsAvailableOnScreen(bool& accts, const string& mad, double& m) const;
	void	UserInterface::showTransferOnScreen(bool& trOutOK, bool& trInOK, double& transferAmount) const;
	double	readInTransferAmount() const;
	void	showNoTransactionsOnScreen() const;
private:
	//singleton pattern (doesn't work yet)
	UserInterface() {};
	UserInterface(UserInterface const& copy);
	UserInterface& operator=(UserInterface const& copy);
	//support functions
    //support functions
	void	showCardIdentificationMenu() const;
	void	showAccountProcessingMenu() const;
    int		readInCommand() const;
    double	readInPositiveAmount() const;
	int		readInPositiveNumber() const;
	
};

#endif
