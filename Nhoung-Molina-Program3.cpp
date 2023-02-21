//Molina Nhoung CS162 2/18/2023
//Program 3
//
//This program will keep track of events added to this program by the user.
//A menu will appear for the user to choose from entering a new event,
//finding and displaying a matched event, displaying all the events thus far,
//saving all events to the external data file, and loading any existing
//events from the external data file. The user can choose to quit after.



#include <iostream>
#include <fstream>
#include <cctype>
#include <cstring>
using namespace std;

//Constants
const int NAME {50};
const int DATE {9};
const int TIME {7};
const int DESC {100};
const int MAX {10};

//Structures
struct event
{
	char name[NAME];
	char date[DATE];
	char time[TIME];
	int length_event;
	char desc[DESC];
};



//Prototypes
int menu(int pick);
void read_event(event & to_read);
bool repeat(char response);
void save_event(event event_list[], int num_events);
void display_event(event & to_display);
int load_event(event event_list[]);

int main()
{
	//Variables
	event memory[MAX]; 	//All of the events in the file
	int num_events {0}; 	//Number of events added
	char response {' '}; 	//Does the user want to do this again
	int i {0}; 		//Jump through array
	int pick{0}; 		//User choose from menu
	int option {0}; 	//Catch the pick from menu function


	do
	{	
		//Menu that user can choose from
		option = menu(pick);
		//Read in new events from the user
		if (option == 1)
		{
			if (num_events < MAX)
			{
				do
				{
					read_event(memory[num_events]);
					++num_events;
				} while (num_events < MAX && repeat(response));

			}
		}
		//Display all the events
		else if (option == 3)
		{
			for (i = 0; i < num_events; ++i)
			{
				display_event(memory[i]);
			}
		}
		//Save all events too external data file
		else if (option == 4)
		{
			save_event(memory, num_events);
		}
		//Load from external data file
		else if (option == 5)
		{
			//Load in events from external file
			num_events = load_event(memory);
			cout << "Events: " << num_events << endl;
		}
	} while(option != 6);
	
	cout << "***ENDING PROGRAM***" << endl;
	
	
	return 0;
}

//Functions
//Menu to choose item
int menu(int pick)
{
	cout << "*** MENU ***" << endl
		<< "1. Enter a new event celebrity, fan favorite " << endl
		<< "2. Find and display a match of a particulr event, celebrity, fan favorite " << endl
		<< "3. Display all events " << endl
		<< "4. Save all events into an external data file " << endl
		<< "5. Load from an external data file " << endl
		<< "6. Quit \n" << endl;
	do
	{
		cout << "Pick an option (1-6): ";
		cin >> pick;
		cin.ignore(100, '\n');

		if (pick < 1 && pick > 6)
			cout << "Invalid input, try again\n" << endl;
	} while (pick < 1 && pick > 6);
	return pick;
}

//Prompt the user to input event information
void read_event(event & to_read)
{
	cout << "What is the name of the event, celebrety, or fan favorite: ";
	cin.get(to_read.name, NAME, '\n');
	cin.ignore(100, '\n');

	cout << "What day is the event (e.g. 2/13/23): ";
	cin.get(to_read.date, DATE, '\n');
	cin.ignore(100, '\n');

	cout << "What time is the event (e.g. 2:30PM): ";
	cin >> to_read.time;
	cin.ignore(100, '\n');

	cout << "How long is the event (minutes): ";
	cin >> to_read.length_event;
	cin.ignore(100, '\n');

	cout << "What do you want to do when you attend the event: ";
	cin.get(to_read.desc, DESC, '\n');
	cin.ignore(100, '\n');
}

//Does the user want to do it again
bool repeat(char response)
{
	cout << "Do you want to enter another event (y/n)?: ";
	cin >> response;
	cin.ignore(100, '\n');
	if (toupper(response) == 'Y')
		return true;
	return false;
}

//Save the events to the external data file
void save_event(event event_list[], int num_event)
{
	ofstream file_out;
	file_out.open("comic_con.txt");
	
	if (file_out)
	{
		for (int i = 0; i < num_event; ++i)
		{
			file_out << event_list[i].name << "|"
				 << event_list[i].date << "|"
				 << event_list[i].time << "|" 
				 << event_list[i].length_event << "|" 
				 << event_list[i].desc << endl;
		}
		file_out.close();
		file_out.clear();
	}
}

//Display all events
void display_event(event & to_display)
{
	cout << "Event: " << to_display.name << endl
		<< "Date: " << to_display.date << endl
		<< "Time: " << to_display.time << endl
		<< "Event length: " << to_display.length_event << " minutes" << endl
		<< "What are you doing?: " << to_display.desc << endl << endl;
}

//Load events from the external list
int load_event(event event_list[])
{
	int i {0};
	ifstream file_in;
	file_in.open("comic_con.txt");
	if (!file_in)
		return 0;

	file_in.get(event_list[i].name, NAME, '|');
	file_in.ignore(100, '|');
	while (file_in && !file_in.eof())
	{
		file_in.get(event_list[i].date, DATE, '|');
		file_in.ignore(100, '|');
		file_in >> event_list[i].time;
		file_in.ignore(100, '|');
		file_in >> event_list[i].length_event;
		file_in.ignore(100, '|');
		file_in.get(event_list[i].desc, DESC, '|');
		file_in.ignore(100, '|');
		++i;

		file_in.get(event_list[i].name, NAME, '|');
		file_in.ignore(100, '|');
	}
	return i;
}
		
