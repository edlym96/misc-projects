#include <iostream>
	using namespace std;
	
	enum Day {Sun, Mon, Tue, Wed, Thu, Fri, Sat};
	
	int closing_time(Day day_of_the_week);

        void print_day(Day day_of_the_week, ostream& out_stream);

	/* MAIN PROGRAM */
	int main()
	{
		int count;
	
                cout.setf(ios::left);
		/* Print table heading */
		cout.width(17);
		cout << "DAY";
		cout << "CLOSING TIME\n\n";
	
		/* Print table from Sunday to Saturday */
		for (count = static_cast<int>(Sun) ; count <= static_cast<int>(Sat) ; count++)
		{
			cout.width(19);
			/*switch (count)
			{
				case Sun: cout << "Sunday"; break;
				case Mon: cout << "Monday"; break;
				case Tue: cout << "Tuesday"; break;
				case Wed: cout << "Wednesday"; break;
				case Thu: cout << "Thursday"; break;
				case Fri: cout << "Friday"; break;
				case Sat: cout << "Saturday"; break;
				default:	cout << "ERROR!";
			}*/
			//cout << static_cast<Day>(count);
			print_day(static_cast<Day>(count), cout);
			cout << closing_time(static_cast<Day>(count)) << "pm\n";
		}
	
		return 0;
	}
	/* END OF MAIN PROGRAM */
	
	/* FUNCTION TO GENERATE SHOP CLOSING TIMES FROM DAY OF THE WEEK */
	int closing_time(Day day_of_the_week)
	{
		return 5;
	}
