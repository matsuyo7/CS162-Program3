//Molina Nhoung CS162 2/15/2023
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
const int TIME {7};
const int DESC {100};
const int MAX {10};

//Structures
struct event
{
	char name[NAME];
	int day;
	char time[TIME];
	int length_event;
	char desc[DESC];
};



//Prototypes
void read_event(event & new_event);
bool repeat(char response);
void save_event(event event_list[], int num_events);


int main()
{
	//Variables
	event memory[MAX]; 	//All of the events in the file
	int num_events {0}; 	//Number of events added
	char response {' '}; 	//Does the user want to do this again
	//Read in new events from the user
	if (num_events < MAX)
	{
		do
		{
			read_event(memory[num_events]);
			++num_events;
		} while (num_events < MAX && repeat(response));

	}
	save_event(memory, num_events);
	
	
	
	
	
	
	return 0;
}

//Functions
//Prompt the user to input event information
void read_event(event & new_event)
{
	cout << "What is the name of the event, celebrety, or fan favorite: ";
	cin.get(new_event.name, NAME, '\n');
	cin.ignore(100, '\n');

	cout << "What day is the event (e.g. 13): ";
	cin >> new_event.day;
	cin.ignore(100, '\n');

	cout << "What time is the event (e.g. 2:30PM): ";
	cin >> new_event.time;
	cin.ignore(100, '\n');

	cout << "How long is the event (minutes): ";
	cin >> new_event.length_event;
	cin.ignore(100, '\n');

	cout << "What do you want to do when you attend the event: ";
	cin.get(new_event.desc, DESC, '\n');
	cin.ignore(100, '\n');
}

//Does the user want to do it again
bool repeat(char response)
{
	cout << "Do you want to enter another event?: y/n " << endl;
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
				 << event_list[i].day << "|"
				 << event_list[i].time << "|" 
				 << event_list[i].length_event << "|" 
				 << event_list[i].desc << "|" << endl;
		}
	}
}

