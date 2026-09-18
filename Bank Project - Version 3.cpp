
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <conio.h>
#include <fstream>

using namespace std;
#include <limits>

//My Bank System ... 


struct stClient {

	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance = 0;

};
const string ClientsFileName = "BankSystemProject1";

struct stUser {

	string name;
	string password;
	int Permissions;
};
const string UsersFileName = "Users";

//Base Functions
vector <string > splitString(string statment, string seperator = "/##/") {

	int pos;
	string word = "";
	vector <string> v;

	while ((pos = statment.find(seperator)) != string::npos) {


		word = statment.substr(0, pos);

		if (word != "") {
			v.push_back(word);
		}

		statment.erase(0, pos + seperator.length());


	}


	if (statment != "") {
		v.push_back(statment);
	}



	return v;
}
string convertClientRecordToLine(stClient client, string seperator = "/##/") {

	string Line = "";

	Line = Line + client.AccountNumber + seperator;
	Line = Line + client.PinCode + seperator;
	Line = Line + client.Name + seperator;
	Line = Line + client.Phone + seperator;
	Line = Line + to_string(client.AccountBalance);

	return Line;

}
string convertUserRecordToLine(stUser user, string seperator = "/##/") {

	string Line = "";

	Line = Line + user.name + seperator;
	Line = Line + user.password + seperator;
	Line = Line + to_string(user.Permissions);
	return Line;

}
stClient convertLineToClientRecord(string Line, string seperator = "/##/") {

	stClient client;
	vector <string> v = splitString(Line, seperator);

	client.AccountNumber = v[0];
	client.PinCode = v[1];
	client.Name = v[2];
	client.Phone = v[3];
	client.AccountBalance = stod(v[4]);

	return client;

}
stUser convertLineToUserRecord(string Line, string seperator = "/##/") {

	stUser user;
	vector <string> v = splitString(Line, seperator);

	user.name = v[0];
	user.password = v[1];
	user.Permissions = stoi(v[2]);

	return user;

}



// File
vector <stClient> getClientsDataFromFile() {

	string Line;
	stClient client;
	vector <stClient> v;
	fstream MyFile;

	MyFile.open(ClientsFileName, ios::in);

	while (getline(MyFile, Line)) {

		client = convertLineToClientRecord(Line);
		v.push_back(client);


	}

	MyFile.close();

	return v;

}
vector <stUser> getUsersDataFromFile() {

	string Line;
	stUser user;
	vector <stUser> v;
	fstream MyFile;

	MyFile.open(UsersFileName, ios::in);

	while (getline(MyFile, Line)) {

		user = convertLineToUserRecord(Line);
		v.push_back(user);


	}

	MyFile.close();

	return v;

}


// Client Function
void readClientData(stClient& client) {



	cout << "Enter Pin Code : ";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, client.PinCode);


	cout << "Enter Name : ";

	getline(cin, client.Name);


	cout << "Enter Phone : ";

	getline(cin, client.Phone);

	cout << "Enter Account Balance : ";
	cin >> client.AccountBalance;

}
void readUserData(stUser& user, bool nameExist = false) {

	if (nameExist == false) {
		cout << "Enter User Name : ";
		cin >> user.name;
	}

	cout << "Enter Password : ";
	cin >> user.password;
}

bool isClientThere(string AccountNumber) {

	vector<stClient> v = getClientsDataFromFile();
	for (stClient& client : v) {

		if (client.AccountNumber == AccountNumber) {
			return true;
		}

	}

	return false;
}

bool isUserThere(string name) {



	vector<stUser> v = getUsersDataFromFile();

	for (stUser& user : v) {

		if (user.name == name) {
			return true;
		}

	}

	return false;


}
bool isPasswordRight(string name, string password) {

	vector<stUser> v = getUsersDataFromFile();

	for (stUser& user : v) {

		if (user.name == name) {

			if (user.password == password) {
				return true;
			}
			else {
				return false;
			}
		}

	}

	return false;

}
void printClientDetails(stClient Client) {

	cout << "The Following Are Client Details :         " << endl;
	cout << "-------------------------------------------" << endl;
	cout << Client.AccountNumber << endl;
	cout << Client.PinCode << endl;
	cout << Client.Name << endl;
	cout << Client.Phone << endl;
	cout << Client.AccountBalance << endl;
	cout << "-------------------------------------------" << endl;

}
void printUserDetails(stUser user) {


	cout << "The Following Are User Details :         " << endl;
	cout << "-------------------------------------------" << endl;
	cout << user.name << endl;
	cout << user.password << endl;
	cout << user.Permissions << endl;
	cout << "-------------------------------------------" << endl;

}



// Main
void showMenuScreen() {
	cout << "---------------------------------------------" << endl;
	cout << "                   Main Menu Screen          " << endl;
	cout << "---------------------------------------------" << endl;
	cout << "            [1] Show Client List             " << endl;
	cout << "            [2] Add New Client              " << endl;
	cout << "            [3] Delete Client               " << endl;
	cout << "            [4] Update Client Info              " << endl;
	cout << "            [5] Find Client               " << endl;
	cout << "            [6] Transactions             " << endl;
	cout << "            [7] Manage Users          " << endl;
	cout << "            [8] Logout            " << endl;
	cout << "---------------------------------------------" << endl;

}
void showTransactionsScreen() {

	cout << "---------------------------------------------" << endl;
	cout << "           Transactions Menu Screen          " << endl;
	cout << "---------------------------------------------" << endl;
	cout << "            [1] Deposit            " << endl;
	cout << "            [2] Withdraw              " << endl;
	cout << "            [3] Total Balances           " << endl;
	cout << "            [4] Main Menu             " << endl;
	cout << "---------------------------------------------" << endl;

}
void showManageUsersScreen() {

	cout << "---------------------------------------------" << endl;
	cout << "                   Manage Users Menu Screen          " << endl;
	cout << "---------------------------------------------" << endl;
	cout << "            [1] List Users          " << endl;
	cout << "            [2] Add New User             " << endl;
	cout << "            [3] Delete User              " << endl;
	cout << "            [4] Update User Info              " << endl;
	cout << "            [5] Find User              " << endl;
	cout << "            [6] Main Menu             " << endl;
	cout << "---------------------------------------------" << endl;


}
int  readUserChoice(string where) {

	int choice;

	if (where == "Main") {

		do {

			cout << "Choose what do you want to do ? [ 1 to 8 ] ?  ";
			cin >> choice;

		} while (choice <= 0 || choice >= 9);

	}
	else if (where == "Trans") {

		do {

			cout << "Choose what do you want to do ? [ 1 to 4 ] ?  ";
			cin >> choice;

		} while (choice <= 0 || choice >= 5);
	}
	else {


		do {

			cout << "Choose what do you want to do ? [ 1 to 6 ] ?  ";
			cin >> choice;

		} while (choice <= 0 || choice >= 7);


	}

	return choice;
}
void BackToMenu() {

	cout << "Press any key to go back to main menu ....";
	_getch();
}
void PrintClientRecord(stClient Client) {
	cout << "| " << left << setw(15) << Client.AccountNumber
		<< "| " << left << setw(15) << Client.PinCode
		<< "| " << left << setw(30) << Client.Name
		<< "| " << left << setw(15) << Client.Phone
		<< "| " << right << setw(15) << Client.AccountBalance
		<< " |" << endl;
}
void PrintUserRecord(stUser user) {
	cout << "| " << left << setw(15) << user.name
		<< "| " << left << setw(15) << user.password
		<< "| " << left << setw(30) << user.Permissions
		<< " |" << endl;
}
void showClientList(string word)
{

	system("cls");
	vector<stClient> v = getClientsDataFromFile();
	cout << "\n\t\t\t " << word << " List (" << v.size() << ") Client(s)." << endl;
	cout << "------------------------------------------------------------------------------------------" << endl;

	cout << "| " << left << setw(15) << "Account Number"
		<< "| " << left << setw(15) << "PIN Code"
		<< "| " << left << setw(30) << "Client Name"
		<< "| " << left << setw(15) << "Phone"
		<< "| " << right << setw(15) << "Balance"
		<< " |" << endl;

	cout << "------------------------------------------------------------------------------------------" << endl;

	for (stClient& Client : v)
	{
		PrintClientRecord(Client);
	}

	cout << "------------------------------------------------------------------------------------------" << endl;
}
void showUserList(string word) {

	system("cls");
	vector<stUser> v = getUsersDataFromFile();
	cout << "\n\t\t\t " << word << " List (" << v.size() << ") User(s)." << endl;
	cout << "------------------------------------------------------------------------------------------" << endl;

	cout << "| " << left << setw(15) << "User Name"
		<< "| " << left << setw(15) << "Password"
		<< "| " << left << setw(30) << "Permissions"
		<< " |" << endl;

	cout << "------------------------------------------------------------------------------------------" << endl;

	for (stUser& user : v)
	{
		PrintUserRecord(user);
	}

	cout << "------------------------------------------------------------------------------------------" << endl;
}

stClient getClientInformationByAccountNumber(string AccountNumber) {

	vector<stClient> v = getClientsDataFromFile();
	for (stClient& client : v) {

		if (AccountNumber == client.AccountNumber) {

			return client;

		}

	}
}
stUser getUserInformationByName(string name) {

	vector<stUser> u = getUsersDataFromFile();
	for (stUser& user : u) {

		if (name == user.name) {

			return user;

		}

	}
}

stClient getExistingClient() {

	string AccountNumber;
	cout << "Please enter the Account Number : ";
	cin >> AccountNumber;

	do {

		if (!isClientThere(AccountNumber)) {

			cout << endl;
			cout << endl;
			cout << "Client with [" << AccountNumber << "] is not exist , Enter Another Account Number : ";
			cin >> AccountNumber;

		}


	} while (!isClientThere(AccountNumber));


	return getClientInformationByAccountNumber(AccountNumber);

}
stUser   getExistingUser() {


	string name;
	cout << "Please enter the User Name : ";
	cin >> name;

	do {

		if (!isUserThere(name)) {

			cout << endl;
			cout << endl;
			cout << "Client with [" << name << "] is not exist , Enter Another Account Number : ";
			cin >> name;

		}


	} while (!isUserThere(name));


	return getUserInformationByName(name);

}

//Add 
void addClientToFile(stClient client) {

	string Line = convertClientRecordToLine(client);
	fstream MyFile;

	MyFile.open(ClientsFileName, ios::out | ios::app);
	if (MyFile.is_open()) {

		MyFile << Line << endl;

	}

	MyFile.close();

}
void addNewClients() {

	system("cls");
	cout << "---------------------------------------------" << endl;
	cout << "          Add New Clients Screen            " << endl;
	cout << "---------------------------------------------" << endl;

	string AccountNumber;
	stClient Client;
	char Again = 'f';
	bool notFirst = false;

	do {

		if (notFirst == true) {
			system("cls");
			cout << "---------------------------------------------" << endl;
			cout << "          Add New Clients Screen            " << endl;
			cout << "---------------------------------------------" << endl;
		}
		cout << "Enter Account Number : ";
		cin >> AccountNumber;

		do {

			if (isClientThere(AccountNumber)) {

				cout << endl;
				cout << endl;
				cout << "Client with [" << AccountNumber << "] already exists , Enter Another Account Number : ";
				cin >> AccountNumber;

			}


		} while (isClientThere(AccountNumber));


		Client.AccountNumber = AccountNumber;
		readClientData(Client);
		addClientToFile(Client);
		cout << endl;
		cout << "Client Added Succesefully ... Do you want to add more clients ? (Y / N) ? ";
		cin >> Again;
		notFirst = true;

	} while (toupper(Again) == 'Y');

}

void addUserToFile(stUser user) {

	string Line = convertUserRecordToLine(user);
	fstream MyFile;

	MyFile.open(UsersFileName, ios::out | ios::app);
	if (MyFile.is_open()) {

		MyFile << Line << endl;

	}

	MyFile.close();

}
void AddNewUser() {

	system("cls");
	cout << "---------------------------------------------" << endl;
	cout << "          Add New User Screen            " << endl;
	cout << "---------------------------------------------" << endl;
	cout << "Adding New User : " << endl << endl;
	stUser user;

	string name;
	char Again = 'f';
	bool notFirst = false;


	do {
		int per = 0;
		if (notFirst == true) {
			system("cls");
			cout << "---------------------------------------------" << endl;
			cout << "          Add New User Screen            " << endl;
			cout << "---------------------------------------------" << endl;
		}
		cout << "Enter User Name : ";
		cin >> name;

		do {

			if (isUserThere(name)) {

				cout << endl;
				cout << endl;
				cout << "User with [" << name << "] already exists , Enter Another Name : ";
				cin >> name;

			}


		} while (isUserThere(name));


		user.name = name;
		readUserData(user, true);

		char choice;
		char perChoice;

		cout << "Do you want to give full access ? Y/N ? ";
		cin >> choice;

		if (toupper(choice) == 'Y') {

			user.Permissions = -1;
			addUserToFile(user);
			cout << endl;
			cout << "User Added Succesefully ... Do you want to add more users ? (Y / N) ? ";
			cin >> Again;
			notFirst = true;

		}
		else {

			cout << "Do you want to give access to : " << endl;
			cout << "show Client List ? Y/N ? " << endl << endl;
			cin >> perChoice;

			if (toupper(perChoice) == 'Y') {
				per = 1;
			}

			cout << "Add New Client ? Y/N ? " << endl;
			cin >> perChoice;

			if (toupper(perChoice) == 'Y') {
				per = per + 2;
			}

			cout << "Delete Client ? Y/N ? " << endl;
			cin >> perChoice;

			if (toupper(perChoice) == 'Y') {
				per = per + 4;
			}


			cout << "Update Client ? Y/N ? " << endl;
			cin >> perChoice;

			if (toupper(perChoice) == 'Y') {
				per = per + 8;
			}


			cout << "Find Client ? Y/N ? " << endl;
			cin >> perChoice;

			if (toupper(perChoice) == 'Y') {
				per = per + 16;
			}


			cout << "Transactions ? Y/N ? " << endl;
			cin >> perChoice;

			if (toupper(perChoice) == 'Y') {
				per = per + 32;
			}

			cout << "ManageUsers ? Y/N ? " << endl;
			cin >> perChoice;

			if (toupper(perChoice) == 'Y') {
				per = per + 64;
			}

			user.Permissions = per;
			addUserToFile(user);
			cout << endl;
			cout << "User Added Succesefully ... Do you want to add more users ? (Y / N) ? ";
			cin >> Again;
			notFirst = true;

		}



	} while (toupper(Again) == 'Y');




}

//Find

void findClient() {

	system("cls");

	cout << "---------------------------------------------" << endl;
	cout << "          Find Clients Screen            " << endl;
	cout << "---------------------------------------------" << endl;




	stClient client;
	client = getExistingClient();
	cout << endl;
	printClientDetails(client);
	cout << endl;









}
void FindUser() {

	system("cls");

	cout << "---------------------------------------------" << endl;
	cout << "          Find User Screen            " << endl;
	cout << "---------------------------------------------" << endl;




	stUser user;
	user = getExistingUser();
	cout << endl;
	printUserDetails(user);
	cout << endl;




}

//Delete
void deleteClientByAccountNumber(string AccountNumber) {

	vector <stClient> v = getClientsDataFromFile();
	fstream MyFile;
	MyFile.open(ClientsFileName, ios::out);

	for (stClient& client : v) {


		string Line = convertClientRecordToLine(client);



		if (MyFile.is_open()) {

			if (AccountNumber != client.AccountNumber) {
				MyFile << Line << endl;
			}


		}



	}

	MyFile.close();
}
void deleteClient() {

	system("cls");


	cout << "---------------------------------------------" << endl;
	cout << "           Delete Client Screen            " << endl;
	cout << "---------------------------------------------" << endl;


	stClient client;
	char sure = 'f';

	client = getExistingClient();
	printClientDetails(client);
	cout << endl;

	cout << "Are you sure you want to delete this client ? (Y / N) ? ";
	cin >> sure;

	if (toupper(sure) == 'Y') {
		deleteClientByAccountNumber(client.AccountNumber);
		cout << "Client Deleted Succsessfully" << endl;
	}



}

void deleteUserByName(string name) {

	vector <stUser> v = getUsersDataFromFile();
	fstream MyFile;
	MyFile.open(UsersFileName, ios::out);

	for (stUser& user : v) {


		string Line = convertUserRecordToLine(user);



		if (MyFile.is_open()) {

			if (name != user.name) {
				MyFile << Line << endl;
			}


		}



	}

	MyFile.close();

}
void DeleteUser() {

	system("cls");


	cout << "---------------------------------------------" << endl;
	cout << "           Delete User Screen            " << endl;
	cout << "---------------------------------------------" << endl;


	stUser user;
	char sure = 'f';

	user = getExistingUser();
	printUserDetails(user);
	cout << endl;

	cout << "Are you sure you want to delete this user ? (Y / N) ? ";
	cin >> sure;

	if (toupper(sure) == 'Y') {
		deleteUserByName(user.name);
		cout << "User Deleted Succsessfully" << endl;
	}



}

//Update
void updateClientByAccountNumber(string AccountNumber) {


	vector <stClient> v = getClientsDataFromFile();
	fstream MyFile;

	MyFile.open(ClientsFileName, ios::out);

	for (stClient& client : v) {


		string Line = convertClientRecordToLine(client);

		if (MyFile.is_open()) {

			if (AccountNumber == client.AccountNumber) {


				readClientData(client);
				Line = convertClientRecordToLine(client);
				MyFile << Line << endl;

			}
			else {


				MyFile << Line << endl;
			}

		}



	}
	MyFile.close();
}
void updateClient() {

	system("cls");


	cout << "---------------------------------------------" << endl;
	cout << "           Update Client Screen            " << endl;
	cout << "---------------------------------------------" << endl;
	char sure = 'f';
	stClient client;

	client = getExistingClient();
	printClientDetails(client);
	cout << endl;

	cout << "Are you sure you want to update this client ? (Y / N ) ? ";
	cin >> sure;

	if (toupper(sure) == 'Y') {
		updateClientByAccountNumber(client.AccountNumber);
		cout << "Client Updated Succsessfully" << endl;
	}


}

void updateUserByName(string name) {


	vector <stUser> v = getUsersDataFromFile();
	fstream MyFile;

	MyFile.open(UsersFileName, ios::out);

	for (stUser& user : v) {


		string Line = convertUserRecordToLine(user);

		if (MyFile.is_open()) {

			if (name == user.name) {


				readUserData(user, true);

				int per = 0;
				char choice;
				char perChoice;

				cout << "Do you want to give full access ? Y/N ? ";
				cin >> choice;

				if (toupper(choice) == 'Y') {

					user.Permissions = -1;
					cout << endl;



				}
				else {

					cout << "Do you want to give access to : " << endl;
					cout << "show Client List ? Y/N ? " << endl << endl;
					cin >> perChoice;

					if (toupper(perChoice) == 'Y') {
						per = 1;
					}

					cout << "Add New Client ? Y/N ? " << endl;
					cin >> perChoice;

					if (toupper(perChoice) == 'Y') {
						per = per + 2;
					}

					cout << "Delete Client ? Y/N ? " << endl;
					cin >> perChoice;

					if (toupper(perChoice) == 'Y') {
						per = per + 4;
					}


					cout << "Update Client ? Y/N ? " << endl;
					cin >> perChoice;

					if (toupper(perChoice) == 'Y') {
						per = per + 8;
					}


					cout << "Find Client ? Y/N ? " << endl;
					cin >> perChoice;

					if (toupper(perChoice) == 'Y') {
						per = per + 16;
					}


					cout << "Transactions ? Y/N ? " << endl;
					cin >> perChoice;

					if (toupper(perChoice) == 'Y') {
						per = per + 32;
					}

					cout << "ManageUsers ? Y/N ? " << endl;
					cin >> perChoice;

					if (toupper(perChoice) == 'Y') {
						per = per + 64;
					}

					user.Permissions = per;
					cout << endl;



				}

				Line = convertUserRecordToLine(user);
				MyFile << Line << endl;
			}
			else {


				MyFile << Line << endl;
			}

		}



	}
	MyFile.close();
	cout << "User Updated Succesefully ...  ";
}
void UpdateUser() {


	system("cls");


	cout << "---------------------------------------------" << endl;
	cout << "           Update User Screen            " << endl;
	cout << "---------------------------------------------" << endl;
	char sure = 'f';
	stUser user;

	user = getExistingUser();
	printUserDetails(user);
	cout << endl;

	cout << "Are you sure you want to update this User ? (Y / N ) ? ";
	cin >> sure;

	if (toupper(sure) == 'Y') {
		updateUserByName(user.name);
		cout << "User Updated Succsessfully" << endl;
	}
}

//Transactions

void depositByAccountNum(string AccountNumber, double amount) {

	vector <stClient> v = getClientsDataFromFile();
	fstream MyFile;

	MyFile.open(ClientsFileName, ios::out);

	for (stClient& client : v) {


		string Line = convertClientRecordToLine(client);

		if (MyFile.is_open()) {

			if (AccountNumber == client.AccountNumber) {


				client.AccountBalance += amount;
				Line = convertClientRecordToLine(client);
				MyFile << Line << endl;

			}
			else {


				MyFile << Line << endl;
			}

		}



	}
	MyFile.close();

}
void Deposit() {

	system("cls");


	cout << "---------------------------------------------" << endl;
	cout << "				Deposit Screen            " << endl;
	cout << "---------------------------------------------" << endl;


	stClient client;
	char sure = 'f';

	client = getExistingClient();
	printClientDetails(client);
	cout << endl;

	double amount = 0;


	do {

		cout << endl;
		cout << "Please enter Deposit Amount : ";
		cin >> amount;



	} while (amount <= 0);

	cout << endl;
	cout << "Are you sure you want to Prefrom this transactions  ? (Y / N) ? ";
	cin >> sure;


	if (toupper(sure) == 'Y') {

		depositByAccountNum(client.AccountNumber, amount);
		cout << " Done Succsessfully" << endl;
	}



}

void withdrawByAccountNum(string AccountNumber, double amount) {

	vector <stClient> v = getClientsDataFromFile();
	fstream MyFile;

	MyFile.open(ClientsFileName, ios::out);

	for (stClient& client : v) {


		string Line = convertClientRecordToLine(client);

		if (MyFile.is_open()) {

			if (AccountNumber == client.AccountNumber) {


				client.AccountBalance -= amount;
				Line = convertClientRecordToLine(client);
				MyFile << Line << endl;

			}
			else {


				MyFile << Line << endl;
			}

		}



	}
	MyFile.close();

}
void Withdraw() {

	system("cls");


	cout << "---------------------------------------------" << endl;
	cout << "				withdraw Screen            " << endl;
	cout << "---------------------------------------------" << endl;


	stClient client;
	char sure = 'f';

	client = getExistingClient();
	printClientDetails(client);
	cout << endl;

	double amount = 0;
	bool first = true;

	do {

		if (first == true) {

			cout << endl;
			cout << "Please enter withdraw Amount : ";
			cin >> amount;

		}
		else {

			cout << endl;
			cout << "Amount Exceeds the balance or not true , you can withdraw up to :" << client.AccountBalance << endl;
			cout << "Please enter withdraw Amount : ";
			cin >> amount;

		}

		first = false;


	} while (amount > client.AccountBalance || amount <= 0);

	cout << endl;
	cout << "Are you sure you want to Prefrom this transactions  ? (Y / N) ? ";
	cin >> sure;


	if (toupper(sure) == 'Y') {

		withdrawByAccountNum(client.AccountNumber, amount);
		cout << " Done Succsessfully" << endl;
	}

}

double getTotalBalances() {


	string Line;
	stClient client;
	fstream MyFile;
	double total = 0;

	MyFile.open(ClientsFileName, ios::in);

	while (getline(MyFile, Line)) {

		client = convertLineToClientRecord(Line);
		total = total + client.AccountBalance;


	}

	MyFile.close();

	return total;

}
void TotalBalances() {

	showClientList("Balance");
	cout << endl << endl;
	cout << "\t\t\t\t Total Balances = ";
	cout << getTotalBalances() << endl << endl;

}


//Exit
void Logout() {

	system("cls");
	cout << "---------------------------------------" << endl;
	cout << "           Program Ends :)             " << endl;
	cout << "---------------------------------------" << endl;
}
void DontHavePermissionsScreen() {

	system("cls");
	cout << "---------------------------------------" << endl;
	cout << "  Access Denied,                       " << endl;
	cout << "  You Dont Have the Permission to do that, " << endl;
	cout << "  Please Contact your Admin. " << endl;
	cout << "---------------------------------------" << endl << endl;

}
// Main
void RunManageUsers() {

	int choice = 0;

	do {

		system("cls");
		showManageUsersScreen();

		choice = readUserChoice("Other");

		switch (choice) {

		case 1: {

			showUserList("Users");
			BackToMenu();
			break;
		}

		case 2: {

			AddNewUser();
			BackToMenu();
			break;
		}

		case 3: {

			DeleteUser();
			BackToMenu();
			break;
		}

		case 4: {

			UpdateUser();
			BackToMenu();
			break;
		}

		case 5: {

			FindUser();
			BackToMenu();
			break;
		}

		case 6: {


			return;
		}

		}



	} while (true);
}
void RunTransactions() {




	int choice = 0;

	do {

		system("cls");
		showTransactionsScreen();
		choice = readUserChoice("Trans");

		switch (choice) {

		case 1: {

			Deposit();
			BackToMenu();
			break;
		}

		case 2: {

			Withdraw();
			BackToMenu();
			break;
		}

		case 3: {

			TotalBalances();
			BackToMenu();
			break;
		}

		case 4: {


			return;

		}



		}

	} while (true);




}
void runBankSystem(stUser user) {

	int choice = 0;
	int Full = -1;
	user = getUserInformationByName(user.name);

	do {

		system("cls");
		showMenuScreen();
		choice = readUserChoice("Main");


		switch (choice) {

		case 1: {

			if (((1 & user.Permissions) == (1)) || (user.Permissions == Full)) {
				showClientList("Clients");
				BackToMenu();
			}
			else {
				DontHavePermissionsScreen();
				BackToMenu();
			}

			break;
		}

		case 2: {

			if (((2 & user.Permissions) == (2)) || (user.Permissions == Full)) {
				addNewClients();
				BackToMenu();
			}
			else {
				DontHavePermissionsScreen();
				BackToMenu();
			}

			break;
		}

		case 3: {

			if (((4 & user.Permissions) == (4)) || (user.Permissions == Full)) {
				deleteClient();
				BackToMenu();
			}
			else {
				DontHavePermissionsScreen();
				BackToMenu();
			}


			break;
		}

		case 4: {

			if (((8 & user.Permissions) == (8)) || (user.Permissions == Full)) {
				updateClient();
				BackToMenu();
			}
			else {
				DontHavePermissionsScreen();
				BackToMenu();
			}


			break;
		}

		case 5: {

			if (((16 & user.Permissions) == (16)) || (user.Permissions == Full)) {
				findClient();
				BackToMenu();
			}
			else {
				DontHavePermissionsScreen();
				BackToMenu();
			}


			break;
		}

		case 6: {

			if (((32 & user.Permissions) == (32)) || (user.Permissions == Full)) {
				RunTransactions();
			}
			else {
				DontHavePermissionsScreen();
				BackToMenu();
			}


			break;
		}

		case 7: {


			if (((64 & user.Permissions) == (64)) || (user.Permissions == Full)) {
				RunManageUsers();
				BackToMenu();
			}
			else {
				DontHavePermissionsScreen();
				BackToMenu();
			}

			break;
		}

		case 8: {

			Logout();
			BackToMenu();
			return;
		}

		}



	} while (true);
}


void showLoginScreen() {


	cout << "---------------------------------------" << endl;
	cout << "           Login Screen                " << endl;
	cout << "---------------------------------------" << endl;

}
void Login() {


	stUser user;

	showLoginScreen();
	do {



		readUserData(user);
		if ((!isUserThere(user.name)) || (!isPasswordRight(user.name, user.password))) {
			system("cls");
			showLoginScreen();
			cout << "Invalid UserName/password!" << endl;

		}
		else {
			break;
		}



	} while (true);



	runBankSystem(user);


}



int main()
{

	Login();
 
}

