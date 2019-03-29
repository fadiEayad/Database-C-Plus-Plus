//Fadi Ayad
//Database

#include <iostream>
#include <fstream>
#include "ArgumentManager.h"

using namespace std;

int counter = 0;
int c;
bool printOriginal = false;
bool before = true;
int k = 0;

struct node {
	node *next;
	string id;
	string dob;
	string firstname;
	string lastname;
	int yearsWorked;
	int salary;
	string position;
};

class linkedList {
private:
	node *head;
	node *originalhead;
public:
	linkedList();	//constructor
	~linkedList();	//destructor
	void add(string id, string first, string last, string dob, int yearsWorked, int salary, string position);	//add info
	void del(int index);	//delete info from specific index
	void delid(string id);	//delete info of specific id
	void delin(int index1, int index2);	//delete info between two indices, inclusive
	void sort(string command);	//sort info based on command (id, dob, firstname, lastname, yearsworked, salary, position)

	void parse(ifstream &infile);	//parse info from input file
	void print(ofstream &file);	//print info to output file

	void parseline(string str, int index);	//parse line from input file
	void addline(int index, string id, string first, string last, string dob, int yearsWorked, int salary, string position); //add line
};

linkedList::linkedList() {
	head = NULL;
	originalhead = NULL;
}

linkedList::~linkedList() {
	node* curr = head;
	while (curr != 0) {
		node* next = curr->next;
		delete curr;
		curr = next;
	}
	head = 0;

	curr = originalhead;
	while (curr != 0) {
		node* next = curr->next;
		delete curr;
		curr = next;
	}
	originalhead = 0;
}

void linkedList::add(string id, string first, string last, string dob, int yearsWorked, int salary, string position) {
	node* curr = head;
	node *newNode = new node;
	newNode->id = id;
	for (int i = 0; i < counter; i++) {
		if (newNode->id == curr->id)
			return;
		curr = curr->next;
	}
	curr = head;
	newNode->firstname = first;
	newNode->lastname = last;
	newNode->dob = dob;
	newNode->yearsWorked = yearsWorked;
	newNode->salary = salary;
	newNode->position = position;
	newNode->next = NULL;

	if (curr == NULL) {
		head = newNode;
	}
	else {
		while (curr->next != NULL) {
			curr = curr->next;
		}
		curr->next = newNode;
	}
	c++;
	counter = c;
}

void linkedList::addline(int index, string id, string first, string last, string dob, int yearsWorked, int salary, string position) {
	node* curr = head;
	node *newNode = new node;
	newNode->id = id;
	for (int i = 0; i < counter; i++) {
		if (newNode->id == curr->id)
			return;
		curr = curr->next;
	}
	curr = head;
	newNode->firstname = first;
	newNode->lastname = last;
	newNode->dob = dob;
	newNode->yearsWorked = yearsWorked;
	newNode->salary = salary;
	newNode->position = position;

	if (before) {
		if (index == 0) {
			if (k > 0) {
				for (int j = 0; j < k - 1; j++) {
					curr = curr->next;
				}
				newNode->next = curr->next;
				curr->next = newNode;
			}
			else {
				newNode->next = curr;
				head = newNode;
			}
		}
		else {
			for (int i = 0; i < index - 1; i++) {
				curr = curr->next;
			}
			newNode->next = curr->next;
			curr->next = newNode;
		}
	}
	else {
		for (int i = 0; i < index + k; i++) {
			curr = curr->next;
		}
		newNode->next = curr->next;
		curr->next = newNode;
	}
	counter++;
}

void linkedList::del(int index) {
	node *curr = head;
	node *temp = new node;
	node *prev = new node;
	if (before) {
		if (index == 0) {
			head = head->next;
			delete curr;
		}
		else {
			for (int i = 0; i < index; i++) {
				curr = curr->next;
			}
			temp = curr->next;
			if (curr->next->next == NULL)
				curr->next = NULL;
			else
				curr->next = curr->next->next;
			delete temp;
		}
	}
	else {
		if (index == 0) {
			head = head->next;
			delete curr;
		}
		else {
			for (int i = 0; i < index; i++) {
				curr = curr->next;
			}
			temp = curr->next;
			if (curr->next != NULL)
				curr->next = curr->next->next;
			else
				curr->next = NULL;
			delete temp;
		}
	}
	counter--;
}

void linkedList::delid(string id) {
	node *curr = head;
	node *temp = new node;
	node *prev = new node;
	if (curr->id == id) {
		head = curr->next;
		delete curr;
	}
	else {
		while (curr->next->id != id) {
			if (curr->next->next == NULL)
				return;
			curr = curr->next;
		}

		temp = curr->next;
		if (curr->next != NULL)
			curr->next = curr->next->next;
		else
			curr->next = NULL;
		delete temp;
	}
	counter--;
}

void linkedList::delin(int index1, int index2) {
	node *curr = head;
	node *temp = new node;
	node *prev = new node;
	if (index1 != 0) {
		for (int j = 0; j < index1 - 1; j++) {
			if (curr->next != NULL)
				curr = curr->next;
		}
	}
	for (int j = index1; j <= index2; j++) {
		if (index1 == 0) {
			head = head->next;
			temp = curr;
			curr = head;
			delete temp;
		}
		else {
			temp = curr->next;
			if (curr->next != NULL)
				curr->next = curr->next->next;
			else
				curr->next = NULL;
			delete temp;
		}
		counter--;
	}
}

void linkedList::parseline(string str, int index) {
	string arr[9] = {};
	int s = 0;
	for (unsigned int i = 0; i < str.size(); i++) {
		if (str[i] == ' ' || str[i] == '\0') {
			s++;
			continue;
		}
		arr[s] += str[i];
	}

	string id = arr[0];
	string first = arr[1];
	string last = arr[2];
	string dob = arr[3] + ' ' + arr[4] + ' ' + arr[5];
	int yw = stoi(arr[6]);
	int salary = stoi(arr[7]);
	string position = arr[8];

	addline(index, id, first, last, dob, yw, salary, position);
}

////////////////////////////////////////////////////////////////////////sorting section is from stackoverflow.com
void linkedList::sort(string command) {
	node *start = head;
	node *curr = NULL;
	node *trail = NULL;
	node *temp = NULL;
	string cu = "";
	string cunext = "";
	int c = 0;
	int cnext = 0;

	for (int i = 0; i < counter; i++) { //for every element in the list

		curr = trail = head; //set curr and trail at the start node

		while (curr->next != NULL) { //for the rest of the elements in the list
			if (command == "sort id") {
				cu = curr->id;
				cunext = curr->next->id;
			}
			else if (command == "sort first name") {	//if sorting by first name
				cu = curr->firstname;
				cunext = curr->next->firstname;
			}
			else if (command == "sort last name") {	//if sorting by last name
				cu = curr->lastname;
				cunext = curr->next->lastname;
			}
			else if (command == "sort DOB") {	//if sorting by date of birth
				cu = "";
				cunext = "";
				for (int x = 0; x < 4; x++) {
					cu += curr->dob[x + 6];
					cunext += curr->next->dob[x + 6];
				}
				for (int x = 0; x < 2; x++) {
					cu += curr->dob[x];
					cunext += curr->next->dob[x];
				}
				for (int x = 0; x < 2; x++) {
					cu += curr->dob[x + 3];
					cunext += curr->next->dob[x + 3];
				}
			}
			else if (command == "sort years worked") {	//if sorting by years worked
				c = curr->yearsWorked;
				cnext = curr->next->yearsWorked;
			}
			else if (command == "sort salary") {	//if sorting by salary
				c = curr->salary;
				cnext = curr->next->salary;
			}
			else if (command == "sort position") {	//if sorting by position
				cu = curr->position;
				cunext = curr->next->position;
			}

			if (cu > cunext || c > cnext) { //compare curr and curr->next

				temp = curr->next; //swap pointers for curr and curr->next
				curr->next = curr->next->next;
				temp->next = curr;

				//now we need to setup pointers for trail and possibly head
				if (curr == head) //this is the case of the first element swapping to preserve the head pointer
					head = trail = temp;
				else //setup trail correctly
					trail->next = temp;
				curr = temp; //update curr to be temp since the positions changed
			}
			//advance pointers
			trail = curr;
			curr = curr->next;
		}
	}
}
////////////////////////////////////////////////////////////////////////sorting section is from stackoverflow.com

void linkedList::parse(ifstream &infile) {
	string str = "";
	while (getline(infile, str)) {
		string arr[9] = {};
		int s = 0;
		if (str.empty())
			continue;
		for (unsigned int i = 0; i < str.size(); i++) {
			if (str[i] == ' ' || str[i] == '\0') {
				s++;
				continue;
			}
			arr[s] += str[i];
		}

		string id = arr[0];
		string first = arr[1];
		string last = arr[2];
		string dob = arr[3] + ' ' + arr[4] + ' ' + arr[5];
		int yw = stoi(arr[6]);
		int salary = stoi(arr[7]);
		string position = arr[8];

		add(id, first, last, dob, yw, salary, position);
	}

	node *curr = head;
	node *ocurr = new node;
	for (int i = 0; i < counter; i++) {
		if (i == 0) {
			originalhead = new node;
			originalhead->id = curr->id;
			originalhead->firstname = curr->firstname;
			originalhead->lastname = curr->lastname;
			originalhead->dob = curr->dob;
			originalhead->yearsWorked = curr->yearsWorked;
			originalhead->salary = curr->salary;
			originalhead->position = curr->position;
			originalhead->next = NULL;
			ocurr = originalhead;
		}
		else {
			ocurr->next = new node;
			ocurr = ocurr->next;
			ocurr->id = curr->id;
			ocurr->firstname = curr->firstname;
			ocurr->lastname = curr->lastname;
			ocurr->dob = curr->dob;
			ocurr->yearsWorked = curr->yearsWorked;
			ocurr->salary = curr->salary;
			ocurr->position = curr->position;
			ocurr->next = NULL;
		}
		curr = curr->next;
	}
}

void linkedList::print(ofstream &file) {
	node *curr = new node;
	int x;
	if (printOriginal) {
		curr = originalhead;
		x = c;
	}
	else {
		curr = head;
		x = counter;
	}

	for (int i = 0; i < x; i++) {
		file << curr->id << ' ' << curr->firstname << ' ' << curr->lastname
			<< ' ' << curr->dob << ' ' << curr->yearsWorked << ' '
			<< curr->salary << ' ' << curr->position << endl;
		curr = curr->next;
	}
	printOriginal = false;
	x = counter;
}


int main() {

	ifstream infile;	// Creating instance
	ifstream commandfile;	// Creating instance
	ofstream outfile;	// Creating instance

	infile.open("input38.txt");
	commandfile.open("command38.txt");
	outfile.open("output38.txt");


	linkedList obj;
	string command = "";

	if (!infile.is_open())	//print out message if can't open input file
	{
		cout << "Couldn't open input file.";
		return 0;
	}
	if (!commandfile.is_open())	//print out message if can't open command file
	{
		cout << "Couldn't open sort file.";
		return 0;
	}

	obj.parse(infile);

	int i = 0;
	while (getline(commandfile, command)) {	//reading command file
		if (command.empty())
			continue;
		if (i > 0)
			outfile << endl;

		if (command[0] == 'a') {	//if adding
			if (command[4] == 'b') {	//if add before index
				before = true;
				int index = stoi(command.substr(11, -1));
				while (isdigit(commandfile.peek())) {
					getline(commandfile, command);
					obj.parseline(command, index);
					k++;
					if (commandfile.eof())
						break;
				}
				k = 0;
			}
			else if (command.substr(4, -1) == "at beginning") {		//if add at beginning
				before = true;
				int index = 0;
				while (isdigit(commandfile.peek())) {
					getline(commandfile, command);
					obj.parseline(command, index);
					k++;
					if (commandfile.eof())
						break;
				}
				k = 0;
			}
			else if (command.substr(4, -1) == "at end") {		//if add at end
				before = false;
				int index = counter - 1;
				while (isdigit(commandfile.peek())) {
					getline(commandfile, command);
					obj.parseline(command, index);
					k++;
					if (commandfile.eof())
						break;
				}
				k = 0;
			}
			else if (command[4] == 'a' && command[5] == 'f') {		//if add after index
				before = false;
				int index = stoi(command.substr(10, -1));
				while (isdigit(commandfile.peek())) {
					getline(commandfile, command);
					obj.parseline(command, index);
					k++;
					if (commandfile.eof())
						break;
				}
				k = 0;
			}
		}
		else if (command[0] == 'd') {	//if deleting
			if (command.substr(7, -1) == "at beginning") {		//if delete at beginning
				before = true;
				int index = 0;
				obj.del(index);
			}
			else if (command.substr(7, -1) == "at end") {		//if delete at end
				before = false;
				int index = counter - 1;
				obj.del(index);
			}
			else if (command[7] == 'b') {		//if delete before index
				before = true;
				int index = stoi(command.substr(14, -1));
				obj.del(index);
			}
			else if (command[7] == 'a' && command[8] == 'f') {		//if delete after index
				before = false;
				int index = stoi(command.substr(13, -1));
				obj.del(index);
			}
			else if (isdigit(command[7]) && isdigit(command[11]) && command[12] == '\0') {		//if delete id
				string id = command.substr(7, -1);
				obj.delid(id);
			}
			else {			//if delete from index to index
				int z = 0;
				string index1;
				string index2;
				while (isdigit(command[7 + z])) {
					index1 += command[7 + z];
					z++;
				}
				while (isdigit(command[7 + z + 4])) {
					index2 += command[7 + z + 4];
					z++;
				}
				obj.delin(stoi(index1), stoi(index2));
			}
		}
		else if (command == "output original") {	//if output original
			printOriginal = true;
			obj.print(outfile);
			continue;
		}
		else	//if sorting
			obj.sort(command);

		obj.print(outfile);

		i++;
	}


	infile.close();
	commandfile.close();
	outfile.close();
	return 0;
}
