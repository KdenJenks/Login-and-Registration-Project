#include <iostream>
#include <ostream>
#include <fstream>
#include <string>
#include <set>
using namespace std;
bool active = true;
bool loginstatus = false;
ifstream ipass;
ifstream iuser;
ofstream opass;
ofstream ouser;
string usercheck;
//Login Function
string loginfunc() {
	int passvariable = 0;
	int uindexpos = 0;
	int pindexpos = 0;
	int totalusernames = 0;
	string passcheck;
	string userline;
	string passline;
	string misc;
	iuser.open("username.txt");
	ipass.open("password.txt");
	while (!iuser.eof()) {
		getline(iuser, misc, '\n');
		totalusernames++;
		iuser.close();
	}
	cout << "Enter your username: ";
	cin >> usercheck;
	iuser.open("username.txt");
	while (!iuser.eof()) {
		uindexpos++;
		getline(iuser, userline, '\n');
		if (usercheck == userline) {
			cout << "Username match" << endl;
			cout << "Enter your password: ";
			cin >> passcheck;
			while (!ipass.eof()) {
				pindexpos++;
				getline(ipass, passline, '\n');
				if (passcheck == passline) {
					cout << "Password match" << endl;
					if (uindexpos == pindexpos) {
						iuser.close();
						ipass.close();
						active = false;
						loginstatus = true;
						return usercheck;
					}
				}
				if (pindexpos >= uindexpos and passcheck != passline) {
					int trycount = 3;
					cout << "Incorrect password, try again. " << trycount << " attempts remaining. " << endl;
					if (trycount < 1) {
						iuser.close();
						ipass.close();
						return usercheck;
					}
				}
			}
		}
		else if (uindexpos >= totalusernames and usercheck != userline) {
			cout << "No username is registered" << endl;
			iuser.close();
			ipass.close();
			return usercheck;
		}
	}
	return usercheck;
}
int main() {
	//Pre-User-Login algorithm
	while (active == true) {
		string command;
		cout << "Welcome; enter a command (help for help): ";
		cin >> command;
		if (command == "help") {
			cout << "Case sensitive: " << endl << "help: Presents a list of commands" << endl << "quit: Ends the program" << endl << "register: Allows you to register your account" << endl << "login: Allows you to login to your account" << endl << "printlog: Prints a list of all usernames and their corresponding passwords" << endl;
		}
		if (command == "quit") {
			active = false;
		}
		if (command == "register") {
			string reguser;
			string regpass;
			int userindex = 0;
			int passindex = 0;
			ouser.open("username.txt", ofstream::app);
			opass.open("password.txt", ofstream::app);
			cout << "Enter a username: ";
			cin >> reguser;
			cout << "Enter a password: ";
			cin >> regpass;
			opass << regpass << endl;
			ouser << reguser << endl;
			ouser.close();
			opass.close();
		}
		if (command == "login") {
			loginfunc();
		}
		if (command == "printlog") {
			iuser.open("username.txt");
			ipass.open("password.txt");
			int index = 0;
			string line1;
			while (!iuser.eof()) {
				getline(iuser, line1, '\n');
				cout << "Username " << index++ << ": " << line1 << endl;
			}
			index = 0;
			string line2;
			while (!ipass.eof()) {
				getline(ipass, line2, '\n');
				cout << "Password " << index++ << ": " << line2 << endl;	
			}
			iuser.close();
			ipass.close();
		}
	}
	//Post/Logged in algorithm
	while (loginstatus == true) {
		string command;
		cout << "Welcome " << usercheck << "." << endl;
		cin >> command;
	}
}