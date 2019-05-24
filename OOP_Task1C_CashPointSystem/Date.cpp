//Pascale Vacher - March 17
//OOP Assignment Task 1c - Semester 2
//Group Number: 21
//Team: (Software Engineers - Hakim Elgabi(b5015647), Hamud Ibrahim(b5011597), Atiq Rafiq(b5009186), Shahid Ghafoor(b5012414))

#include "Date.h"

//---------------------------------------------------------------------------
//Date: class implementation
//---------------------------------------------------------------------------

//____public member functions

//____constructors & destructors
Date::Date() 						//default constructor
: day_(0), month_(0), year_(0)
{}
Date::Date(int d, int m, int y) 	//constructor
: day_(d), month_(m), year_(y)
{}

//____other public member functions
int Date::getDay() const {
	return day_;
}
int Date::getMonth() const {
	return month_;
}
int Date::getYear() const {
	return year_;
}
const Date Date::currentDate() {	//returns the current date
	time_t now(time(0));
	struct tm& t(*localtime(&now));
    return Date(t.tm_mday, t.tm_mon + 1,  t.tm_year + 1900);
}
void Date::setDate(int d, int m, int y) {
	day_ = d;
	month_ = m;
	year_ = y;
}

const bool Date::isValid(Date d)
{
	bool validation = false;
	if (d.year_ <= currentDate().year_)
	{
		if (d.month_ < 13 && d.month_ > 0)
		{
			if (d.day_ > 0 && d.day_ < 32)
			{
				if (d.month_ == 4 || d.month_ == 6 || d.month_ == 9 || d.month_ == 11)
				{
					if (d.day_ < 31)
					{
						validation = true;
					}
				}
				if (d.month_ == 1 || d.month_ == 3 || d.month_ == 5 || d.month_ == 7 || d.month_ == 8 || d.month_ == 10 || d.month_ == 12)
				{
					if (d.day_ < 32)
					{
						validation = true;
					}
				}
				if (d.month_ == 2)
				{
					if (d.day_ < 29)
					{
						validation = true;
					}
				}
			}
		}
		
	}
	return validation;
}
string Date::toFormattedString() const {
//return date formatted as string ("DD/MM/YYYY")
	ostringstream os;
	os << setfill('0');
	os << setw(2) << day_ << "/";
	os << setw(2) << month_ << "/";
	os << setw(4) << year_;
	return (os.str());
}

ostream& Date::putDataInStream(ostream& os) const {
//put (unformatted) date (D/M/Y) into an output stream
	os << day_ << "/";
	os << month_ << "/";
	os << year_;
	return os;
}
istream& Date::getDataFromStream(istream& is) {
//read in date from (semi-formatted) input stream (D/M/Y)
	char ch;			//(any) colon field delimiter
	is >> day_ >> ch >> month_ >> ch >> year_;
	return is;
}

//---------------------------------------------------------------------------
//overloaded operator functions
//---------------------------------------------------------------------------

bool Date::operator==(const Date& d) const { //comparison operator
	return
		((day_ == d.day_) &&
		 (month_ == d.month_) &&
		 (year_ == d.year_));
}
bool Date::operator!=(const Date& d) const {
	return (!(*this == d));
}
bool Date::operator<(const Date& d) const { //NEW
//true if (strictly) earlier than d (i.e., *this < d)
	return ((year_ < d.year_)
	     || ((year_ == d.year_) && (month_ < d.month_) )
	     || ((year_ == d.year_) && (month_ == d.month_) && (day_ < d.day_)));
}

//---------------------------------------------------------------------------
//non-member operator functions
//---------------------------------------------------------------------------

ostream& operator<<(ostream& os, const Date& aDate) {
    return (aDate.putDataInStream(os));
}
istream& operator>>(istream& is, Date& aDate) {
	return (aDate.getDataFromStream(is));
}
