#include <iostream>
#include <string>
#include <fstream>		// LIBRARY FOR FILE HANDLING
using namespace std;

fstream files("Filenames.txt");		// MAKING A FILE TO KEEP TRACK OF THE FILES CREATED

struct node
{
	string name;
	node* next;
};


void Clear();

class LinkedList
{
public:

	void Insert_end();
	void Insert_head();
	void Insert_Given();
	void Display();
	string Search();
	void Delete();
	void Filling();
	LinkedList(char* filename)
	{
		head = tail = NULL;
		counter = 0;	// To keep track of how many things have been stored ( Number of things	)
		this->filename = filename;						//	this->filename means the variable we will use inside class
									// we set it equal to the filename we provided in the int main() function
		fstream file(filename,ios::out|ios::app);	// Opening the file of that name
		tempi = "temp.txt";		// Name of the temporary file
		lineno = 0;				// To Keep track of which line we're at
	}

private:
	node* head,*tail;	// To keep track of heads and tails of list
	int counter,lineno;
	const char* filename, *tempi;		// If you want to store a filename, store it in this data type
	string search,line,linenums;
};

void LinkedList::Filling() // TO FILL THE LINKED LISTS IF A FILE ALREADY EXISTS
{
	
	node* n;
	fstream file(filename);
	while (getline(file,line))
	{
		if (head == NULL)
		{
			head = new node;
			head->name = line;
			head->next = NULL;
			tail = head;
			counter++;
		}
		else
		{
			n = new node;
			n->name = line;
			n->next = NULL;
			tail->next = n;
			tail = n;
			counter++;
		}
	}
}

void LinkedList::Insert_end()
{
	ofstream file(filename, ios::out | ios::app);	// Opeing file in append mode

	cin.ignore();
	if (head == NULL)
	{
		head = new node;
		cout << ">>\t";
		getline(cin,head->name);
		head->next = NULL;
		tail = head;
		file << ">>\t" << head->name << endl;	// APPENDING IN FILE
		counter++;
	}
	else
	{
		node* n = new node;
		cout << ">>\t";
		getline(cin,n->name);
		n->next = NULL;
		tail->next = n;
		tail = n;
		file << ">>\t" << n->name << endl;	// APPENDING IN FILE
		counter++;
	}
	file.close();	// MAKE SURE TO ALWAYS CLOSE THE FILE
}

void LinkedList::Insert_head()
{
	cin.ignore();
	if (head == NULL)	// IF NOTHING EXISTS THIS OPERATION WILL RUN
	{
		head = new node;
		cout << ">>\t";
		getline(cin,head->name);
		head->next = NULL;
		tail = head;

		fstream file(filename, ios::out);	// OPENING FILE	(	ios::out means that it is opened in overwrite mode	)
		
		file << ">>\t" << head->name << endl;
		
		counter++;
		file.close();
	}
	else
	{
		ofstream temp(tempi,ios::out);		// Opening a temporary file in overwrite mode so that any prev data if left in this file is deleted

		node* n = new node;
		cout << ">>\t";
		getline(cin, n->name);
		n->next = head;
		temp << ">>\t" << n->name << endl;	// Inserting in the start of the file
		
		ifstream file(filename);	// Opening the original file in READ mode
		while (!file.eof())		// Loop will run until the file ends		( .eof() means End Of File	)
		{
			getline(file, line);	//	Each line will be stored in variable 'line'
			temp << line << endl;	// It will then be written in temporary file
		}
		temp.close();	
		file.close();
		remove(filename);	// Original file is removed
		rename(tempi, filename);	// Renamed the temporary file to be the original file
		
		head = n;
		counter++;	// Whenever something is added in the list, counter will increase
	}
}
void LinkedList::Insert_Given() // INSERTING AT A GIVEN INDEX
{

	int index;
	bool invalid;
	do		// This loop will run until invalid is equal to false
			// It will be true if a valid Index is entered
	{
		cout << "Index:\t";
		
		cin >> index;
		if (index > counter || index < 0)		// Invalid Index
		{
			if (counter > 0)
			{
				cout << "Invalid Index\nChoose between 0-" << counter << endl;
				invalid = true;
			}
			else
			{
				cout << "\nVOID!\n";
				invalid = false;
			}
		}
		else if (index == 0)		// If index = 0, It will insert at head
		{
			Insert_head();
			invalid = false;
		}
		else if (index == counter)	// If index  is equal to the number of things, it will insert at end
		{
			Insert_end();
			invalid = false;
		}
		else		// If a valid Index is entered
		{
			node* temp = head;
			int count = 0;
			cin.ignore();
			fstream file(filename);
			ofstream tempo(tempi, ios::out);

			while (count++ != index)	// It will check from start of the file and increment count until index is reached.
			{							// count++ != index means that if when the condition count != index is executed, count is incremented 
				getline(file, line);
				tempo << line << endl;
				temp = temp->next;	
			}
			node* n = new node;
			cout << ">>\t";
			getline(cin, n->name);
			tempo << ">>\t" << n->name << endl;
			while (!file.eof())
			{
				getline(file, line);
				tempo << line << endl;
			}
			tempo.close();
			file.close();

			remove(filename);
			rename(tempi, filename);
			n->next = temp->next;
			temp->next = n;
			counter++;
			invalid = false;

		}
	} while (invalid);
}

string LinkedList::Search()
{
	int index;
	char op;
	bool invalid;
	if (search == "")		// If the variable search is already not filled, it will ask how we want to search the thing
	{
		cout << "\n1. Index\n";
		cout << "\n2. Name\n";
		cin >> op;
	}
	else
		op = '2';	// If the delele function is running, it will automatically choose option 2 to search by name and will not ask for
					// the search variable because it will already be given by the delete function

	switch (op)
	{
	case '1':
		do
		{
			cout << "Index:\t";

			cin >> index;
			if (index >= counter || index < 0)		// Invalid Index
			{
				if (counter > 0)
				{
					cout << "Invalid Index\nChoose between 0-" << counter - 1 << endl;
					invalid = true;
				}
				else
				{
					cout << "\nVOID!\n";
					invalid = false;
				}
			}
			else
			{
				int count;
				fstream file(filename);
				count = -1;
				
				while (count++ != index)
					getline(file, line);
				cout << line << endl;	//	Displaying the value at the index searched
										// this function will vary according to the information you are asking and the way you are setting your file
				file.close();
				invalid = false;
				file.close();
				return 0;	// Doing nothing. Just a formality of making int type function.
			}
		} while (invalid);
		break;
	case '2':
		linenums = "";
		if (search == "")		// If search function is chosen from the Menu
		{
			cin.ignore();
			cout << "Name:\t";
			getline(cin, search);
		}
		cout << "Seaching " << search << endl;
		int offset;
		lineno = 0;
		fstream file(filename);
		while (!file.eof())
		{
			lineno++;	// Line number will keep on increasing until the dedicated line is found
			offset = 0;
			getline(file, line);
			int i = line.find(search, 0);		// It will tell at which index on the line the thing we're searching for, say Kirmada is located
												// if the line is:-
												// My name is Kirmada
												// i = 11
			if (i != string::npos)	// string::npos always = -1. If Kirmada was not located in the line, i would also be equal to -1
									// So if the thing's first letter is found say K of Kirmada, this condition will be equal to true
				for (; i < line.length(); i++)		// Loop runs in the line from i to the end of line
													// It is to make sure that the thing matches the word we search
				{
					
					if (search.at(offset) == line.at(i))	// search.at(0)  means letter at 0 index of search variable
						offset++;		// This condition is making sure the all the letters match
										// If all the letters match, offset will be equal to the length of the word we searched for
										// otherwise the loop will run again and on the next line and offset will again be equal to zero
					else
						offset = 0;		// Even if one letter is not equal to the one we searched for, it will set offset = 0
					
					if (offset == search.length())
					{
								cout << "Match found!\n";
								cout << endl << line << endl;
								cout << "Line number: " << lineno << endl;
								linenums += lineno;		// If the thing we search for exists in the line, it will save its linenumber in linenums
								break;
					}
				}
		}
		
		search = "";	// We have to set it equal to this because if we search again, it asks for the name again
		file.close();
		return linenums;
		break;
	}
	search = "";
}

void LinkedList::Delete()
{
	bool invalid;
	int count;
	Display();
	cin.ignore();
	cout << "\n\nName you want to delete:\t";
	getline(cin, search);
	Search();
	do
	{
		cout << "Name at which line number do you wish to delete:\t";
		cin >> lineno;
		count = 0;
		for (; count < linenums.length(); count++)
		{
			if (lineno == linenums.at(count))
			{
				invalid = false;
				break;
			}
			else invalid = true;
		}
		if (invalid)
			cout << "Invalid Line Number\nType again\n";
	} while (invalid);
	count = 1;
	ofstream temp(tempi, ios::out);
	ifstream file(filename);
	cout << "\nDeleting\n";
	while (!file.eof())
	{
		getline(file, line);
		if (count++ != lineno)
			temp << line << endl;
		cout << ".\n";
	}
	cout << "Deleted\n";
	temp.close();
	file.close();
	remove(filename);
	rename(tempi, filename);
}

void LinkedList::Display()
{
	
	ifstream file(filename);
	string line = "asd";
	while (!file.eof() && line!= "")
	{
		getline(file, line);
		cout << line << endl;
	}
	file.close();
}
int main()
{
	char* filename = new char[50];
	cout << "Enter File Name:\t";
	cin >> filename; // TAKING FILE'S NAME
	string line;
	bool found = false;

	//	CHECKING IF IT ALREADY EXISTS


	while (!files.eof())
	{
		getline(files, line);
		if (line == filename)
		{
			cout << "File already Exists\n";
			cout << "Opening " << filename << endl;
			Clear();
			found = true;
			break;
		}
		
	}
	if (!found)
	{
		cout << "Creating New File\n";
		fstream files("Filenames.txt", ios::out | ios::app);
		files << filename << endl;
		Clear();
	}
			LinkedList l(filename);
			l.Filling();
		do
		{
			cout << "1. Insert at Beginning\n";
			cout << "\n2. Insert at End\n";
			cout << "\n3. Insert at Given Index\n";
			cout << "\n4. Display\n";
			cout << "\n5. Search\n";
			cout << "\n6. Delete\n";
			cout << "\nPress any key to exit\n";
			char  op;
			cin >> op;
			switch (op)
			{
			case '1':
				l.Insert_head();
				Clear();
				break;
			case '2':
				l.Insert_end();
				Clear();
				break;
			case '3':
				l.Insert_Given();
				Clear();
				break;
			case '4':
				l.Display();
				Clear();
				break;
			case '5':
				l.Search();
				Clear();
				break;
			case '6':
				l.Delete();
				Clear();
				break;
			default:
				cout << "Do you really want to exit the program?(y/n)\t";
				cin >> op;
				if (op == 'y')
					exit(1);
				else
					system("cls");
			}


		} while (true);
	
}
void Clear()
{
	system("pause");
	system("cls");

}

