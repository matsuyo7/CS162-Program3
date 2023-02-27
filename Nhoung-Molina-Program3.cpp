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
const int TIME {8};
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
void welcome();
int menu(int pick);
void read_event(event & to_read);
bool repeat(char response);
bool save_event(event event_list[], int num_events);
void display_event(event & to_display);
int load_event(event event_list[]);
void one_display(event display_list[], char one_event[], int num_events);

int main()
{
	//Variables
	event memory[MAX]; 	//All of the events in the file
	int num_events {0}; 	//Number of events added
	char response {' '}; 	//Does the user want to do this again
	int i {0}; 		//Jump through array
	int pick{0}; 		//User choose from menu
	int option {0}; 	//Catch the pick from menu function
	char one_event[NAME]; 	//Find one event to match and display

	//Welcome the user
	welcome();

	//Loop until the user wants to quit
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
		//Display one event if it matches
		else if (option == 2)
		{
			one_display(memory, one_event, num_events);
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
			if (save_event(memory, num_events))
				cout << "\n-Your events have been saved-" << endl;
			else
				cout << "\nEvents could not save" << endl;
		}
		//Load from external data file
		else if (option == 5)
		{
			//Load in events from external file
			num_events = load_event(memory);
			cout << "Events: " << num_events << endl;
		}
	} while (option != 6);
	
	cout << "***ENDING PROGRAM***" << endl;
	
	
	return 0;
}

//Functions
//Welcome the user to the program and give them information
void welcome()
{
	cout << "\n*** ComicCon Events ***\n"
		<< "Keep track of events that you want to do\n"
		<< "You can store up to 10 events\n"
		<< "Each event stored will ask for: \n"
		<< "\t - Event name\n"
		<< "\t - Date\n"
		<< "\t - Time\n"
		<< "\t - Length of event\n"
		<< "\t - What you want to do\n"
	        << "You will be given options to enter new events, display all of them, display one, save, and load with the menu below" << endl;
}

//Menu to choose item
int menu(int pick)
{
	cout << "\n*** MENU ***" << endl
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
	cout << "\nWhat is the name of the event, celebrity, or fan favorite: ";
	cin.get(to_read.name, NAME, '\n');
	cin.ignore(100, '\n');

	cout << "What day is the event (e.g. 2/13/23): ";
	cin.get(to_read.date, DATE, '\n');
	cin.ignore(100, '\n');

	cout << "What time is the event (e.g. 2:30PM): ";
	cin.get(to_read.time, TIME, '\n');
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
bool save_event(event event_list[], int num_event)
{
	ofstream file_out;
	file_out.open("comic_con.txt");
	
	if (!file_out)
		return false;

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

	return true;
}

//Display all events
void display_event(event & to_display)
{
	cout << "\nEvent: " << to_display.name << endl
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

		file_in.get(event_list[i].time, TIME , '|');
		file_in.ignore(100, '|');

		file_in >> event_list[i].length_event;
		file_in.ignore(100, '|');

		file_in.get(event_list[i].desc, DESC, '\n');
		file_in.ignore(100, '\n');
		++i;


		file_in.get(event_list[i].name, NAME, '|');
		file_in.ignore(100, '|');
	}	
	file_in.close();
	file_in.clear();
	return i;
}
		
//Display one event
void one_display(event display_list[], char one_event[], int num_event)
{
	int j {0};
	cout << "\nWhat's the EXACT name of the event that you're looking for: ";
	cin.get(one_event, NAME, '\n');
	cin.ignore(100, '\n');

	for (int i {0}; i < num_event; ++i)
	{
		if (strcmp(one_event, display_list[i].name) == 0)
		{ 
			cout << "\nEvent: " << display_list[i].name << endl
				<< "Date: " << display_list[i].date << endl
				<< "Time: " << display_list[i].time << endl
				<< "Event length: " << display_list[i].length_event << " minutes" << endl
				<< "What are you doing?: " << display_list[i].desc << endl << endl;
			++j;
		}
	}

	if (j == 0)
	{
		cout << "\n-EVENT NOT FOUND-" << endl;
	}
}
