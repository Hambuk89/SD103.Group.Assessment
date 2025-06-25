// =======================
// TalentHub Project developed by Matthew, Laila, Han
// =======================

#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <array>
#include <vector>
#include <cctype>
#include <algorithm>

using namespace std;

string get_valid_password();

struct Student {
    string username;
	string password;
    string fullName;
    string age;
    string email;
    string phone;
    string currentAddress;
    string studentType; // "Domestic" or "International"
};

struct Admin {
    string username;
    string password;
    string fullName;
    string email;
};

struct Course {
	string courseName;
	vector<string> studentsEnrolled; // List of student usernames enrolled in the course
};

vector<Student> students;
vector<Admin> admins;
vector<Course> courses = {
	{"Introduction to Information Technology", {}},
	{"Foundations of Management", {}},
	{"Project Management Essentials", {}},
	{"English for Academic Purposes", {}},
	{"Business Communication", {}},
	{"Conversational Languages", {}},
	{"CISCO", {}},
	{"Microsoft Certification", {}}
};     

void registerStudent() { // function to register a new student

	//string password;

    Student s; // s variable to store student details
    cout << "*************** Please fill in the details to get started!!! ***************\n";
    cout << "Username: "; getline(cin, s.username);
    //cout << "Password: "; getline(cin,s.password); 
	s.password = get_valid_password();
    cout << "Full Name: "; getline(cin, s.fullName);;
	cout << "Email: "; getline(cin, s.email);
    cout << "Age: "; getline(cin, s.age);
    cout << "Phone: "; getline(cin, s.phone);
	cout << "Current Address: "; getline(cin, s.currentAddress);
    cout << "Student Type (Domestic/International): "; getline(cin, s.studentType);
    students.push_back(s); // Add the new student to the students vector

	ofstream file("students.txt", ios::app); // Append mode to add new students with registered details
	file << "student\n"
		<< s.username << "\n"
		<< s.password << "\n"
		<< s.fullName << "\n"
        << s.age << "\n"
        << s.email << "\n"
        << s.phone << "\n"
		<< s.currentAddress << "\n"
        << s.studentType << endl;
	file.close();
    cout << "Registration successful!\n";
}

void registerAdmin() { // function to register a new admin
	Admin a; // a variable to store admin details
	cout << "*************** Admin Register ***************\n";
	cout << "Username: "; getline(cin, a.username);
	cout << "Password: "; getline(cin, a.password);
	cout << "Full Name: "; getline(cin, a.fullName);
	cout << "Email: "; getline(cin, a.email);
	admins.push_back(a); // Add the new admin to the admins vector

	ofstream file("admins.txt", ios::app); // Append mode to add new admins with registered details.
	file << "admin\n"
		<< a.username << "\n"
		<< a.password << "\n"
		<< a.fullName << "\n"
		<< a.email << endl;
	file.close();
    cout << "Admin registration successful!\n";
}

bool login() { // function to login a student
    string username, password;
    cout << "*************** Login ***************\n";
    cout << "Username: ";
	getline(cin, username);
    cout << "Password: ";
	getline(cin, password);
    for (const auto& s : students) { // loop to check if the username and password match with the registered students
        if (s.username == username && s.password == password) {
            cout << "Login successful! Welcome, " << s.fullName << ".\n";
			ofstream file("students.txt", ios::app); // append mode to log the login activity
			file << "Student logged in: " << s.fullName << "\n";
			file.close();
            return true;
        }
    }
    cout << "Invalid username or password.\n";
    return false;
}

bool Adminlogin() { // function to login an admin
	string username, password;
	cout << "*************** Admin Login ***************\n";
	cout << "Username: "; getline(cin, username);
	cout << "Password: "; getline(cin, password);
	for (const auto& a : admins) { // loop to check if the username and password match with the registered admins
		if (a.username == username && a.password == password) {
			cout << "Admin login successful! Welcome, " << a.fullName << ".\n";
			ofstream file("admins.txt", ios::app); // append mode to log the login activity
			file << "Admin logged in: " << a.fullName << "\n";
			file.close();
			return true;
		}
	}
	cout << "Invalid admin username or password.\n";
	return false;
}

void forgotUsername() { // function to find the username with the email
    string email;
    cout << "*************** Find your Username with your Email ***************\n";
    cout << "Enter your email: "; getline(cin, email);
    for (const auto& s : students) { // loop to check if the email matches with the registered students
        if (s.email == email) {
            cout << "Your username is: " << s.username << "\n";
			ofstream file("students.txt", ios::app); // append mode to log the activity
			file << "Username found for email: " << email << "\n";
			file.close();
            return;
        }
    }
    cout << "Email not found.\n";
}

void forgotPassword() { // function to find the password with the username and email
    string username, email;
    cout << "*************** Find your Password with your Username and Email ***************\n";
    cout << "Enter your username: "; getline(cin, username);
    cout << "Enter your email: "; getline(cin, email);
    for (const auto& s : students) { // loop to check if the username and email match with the registered students
        if (s.username == username && s.email == email) {
            cout << "Your password is: " << s.password << "\n";
			ofstream file("students.txt", ios::app); // append mode to log the activity
			file << "Password found for username: " << username << " and email: " << email << "\n";
			file.close();
            return;
        }
    }
    cout << "Username and email do not match.\n";
}

void viewStudentProfiles() { // function to view student profiles
	vector<Student> sortedStudents = students;
	sort(sortedStudents.begin(), sortedStudents.end(), [](const Student& a, const Student& b) { // Sort by full name alphabetically
		return a.fullName < b.fullName;
		});
	cout << "*************** Student Profiles (Alphabetically) ***************\n";
	for (const auto& s : sortedStudents) { // loop to print the student profiles
		cout << s.fullName << " (" << s.username << ")\n";
		ofstream file("students.txt", ios::app); // append mode to log the student profiles
		file << "Student Profile: " << s.fullName << " (" << s.username << ")\n" << endl;
		file.close();
	}
}

void viewStudentByTypes() { // function to view students by type (Domestic or International)
	cout << "*************** View Students by Type ***************\n";
	cout << "1. Domestic Students\n";
	cout << "2. International Students\n";
	cout << "Select an option: ";
	string choice;
	getline(cin, choice);

	if (choice == "1") {
		cout << "Domestic Students:\n";
		for (const auto& s : students) {
			if (s.studentType == "Domestic") {
				cout << s.fullName << " (" << s.username << ")\n";
				ofstream file("students.txt", ios::app);
				file << "Domestic Student: " << s.fullName << " (" << s.username << ")\n";
				file.close();
			}
		}
	}
	else if (choice == "2") {
		cout << "International Students:\n";
		for (const auto& s : students) {
			if (s.studentType == "International") {
				cout << s.fullName << " (" << s.username << ")\n";
				ofstream file("students.txt", ios::app);
				file << "International Student: " << s.fullName << " (" << s.username << ")\n";
				file.close();
			}
		}
	}
	else {
		cout << "Invalid option. Please try again.\n";
	}
}

void viewCourseDetails() { // function to view course details and enrolled students
	for (const auto& c : courses) {
		cout << "Course: " << c.courseName << "\n";
		cout << "Enrolled Students:\n";
		for (const auto& student : c.studentsEnrolled) {
			auto it = find_if(students.begin(), students.end(), [&](const Student& s) { return s.username == student; }); // find the student by username in the students vector
			if (it != students.end()) cout << " - " << it->fullName << " (" << student << ")\n";
			ofstream file("students.txt", ios::app);
			file << "Course: " << c.courseName << "\n";
			file << "Enrolled Students:\n";
			file << " - " << student << "\n";
			file.close();
		}
		cout << endl;
	}
}

void searchStudentByName() { // function to search for a student by full name
	cout << "*************** Search Student by Username ***************\n";
	string fullName;
	cout << "Enter the student's full name: "; getline(cin, fullName);
	bool found = false;
	for (const auto& s : students) { // loop to check if the full name matches with the registered students
		if (s.fullName == fullName) {
			ofstream file("students.txt", ios::app);
			cout << "Student found: " << s.fullName << " (" << s.username << ")\n";
			found = true;
			break;
		}
	}
	if (!found) {
		cout << "No student found with the input name.\n";
	}
}

void manageCourseEnrollment() { // function to manage course enrollment for a student
	cout << "*************** Manage Course Enrollment ***************\n";
	cout << "Enter student fullname:\n";
	string sName;
	getline(cin, sName);

	int studentIndex = -1; // intialize the variable studentIndex to -1 to indicate that the student is not found yet
	for (int i = 0; i < students.size(); ++i) { // loop to find the student by full name in the students vector
		if (students[i].fullName == sName) { // if the full name matches with the registered students
			studentIndex = i;
			break;
		}
	}
	if (studentIndex == -1) { // if the student is not found, print a message and return
		cout << "Student not found.\n";
		return;
	}
	cout << "1. Add student to a course\n";
	cout << "2. Remove student from a course\n";
	cout << "Select an option: ";
	string option;
	getline(cin, option);

	cout << "Available Courses:\n";
	for (int i = 0; i < courses.size(); ++i) { // loop to print the available courses
		cout << " " << (i + 1) << ".  " << courses[i].courseName << endl;
	}
	cout << "Enter course Number: ";
	string input;
	getline(cin, input);

	int courseIndex = -1;
	for (int i = 0; i < courses.size(); ++i) {
		string num = to_string(i + 1);
		if (input == num) {
			courseIndex = i;
			break;
		}
	}
	if (courseIndex == -1) {
		cout << "Invalid course number.\n";
		return;
	}

	
	vector<string>& enrolled = courses[courseIndex].studentsEnrolled; // get the vector of enrolled students for the selected course
	sName = students[studentIndex].fullName; // get the full name of the student from the students vector using the studentIndex
	
	if (option == "1") {
		bool alreadyEnrolled = false; // check if the student is already enrolled in the course by set variable called alreadyEnrolled to false
		for (int i = 0; i < enrolled.size(); ++i) {
			if (enrolled[i] == sName) alreadyEnrolled = true;
		}
		if (!alreadyEnrolled) {
			enrolled.push_back(sName); // if the student is not already enrolled, add the student to the course
			cout << "Student " << sName << " has been added to the course " << courses[courseIndex].courseName << ".\n";
		}
		else {
			cout << "Student " << sName << " is already enrolled in the course " << courses[courseIndex].courseName << ".\n";
		}
	}
	else if (option == "2") {
		bool enrolledStudent = false; // check if the student is found in the course by set variable called enrolledStudent to false
		for (int i = 0; i < enrolled.size(); ++i) {
			if (enrolled[i] == sName) {
				enrolled.erase(enrolled.begin() + i); // if the student is found in the course, remove the student from the course
				enrolledStudent = true;
				cout << "Student " << sName << " has been removed from the course " << courses[courseIndex].courseName << ".\n";
				break;
			}
		}
		if (!enrolledStudent) { // if the student is not found in the course, print a message
			cout << "Student " << sName << " is not enrolled in the course " << courses[courseIndex].courseName << ".\n";
		}
	}
	else {
		cout << "Invalid option. Please try again.\n";
		return;
	}

	ofstream file("students.txt", ios::app);
	file << "Student: " << sName << "\n";
	file << (option == "1" ? "Added to" : "Removed from") << " course: " << courses[courseIndex].courseName << "\n";
	file.close();
}
// =======================
// Students Menu
// =======================
// Coded by Han
// =======================
void studentsMenu(int studentIndex) { // function to display the student menu and handle student actions
	while (true) {
		cout << "\n*************** Student Page ***************\n";
		cout << "1. View Profile\n";
		cout << "2. View available courses\n";
		cout << "3. Enroll in a course\n";
		cout << "4. Drop a course\n";
		cout << "5. Log out to main page\n";
		cout << "Select an option: ";
		string choice; 
		getline(cin, choice);

		Student& currentStudent = students[studentIndex]; // Get the current student using the studentIndex passed to the function

		int enrolledCourseIndexes[8]; // array to store 8 enrolled course indexes
		int enrolledCount = 0; // count of enrolled courses
		for (int courseIndex = 0; courseIndex < courses.size(); ++courseIndex) { // loop through all courses to find the enrolled courses for the current student
			for (int studentInCourseIndex = 0; courses[courseIndex].studentsEnrolled.size(); ++studentInCourseIndex) { // loop through all students enrolled in the course
				if (courses[courseIndex].studentsEnrolled[studentInCourseIndex] == currentStudent.fullName) { // if the student is enrolled in the course
					enrolledCourseIndexes[enrolledCount++] = courseIndex; // store the course index in the enrolledCourseIndexes array and increment the count
					break;
				}
			}
		}
		if (choice == "1") {
			cout << "Full Name: " << currentStudent.fullName << "\n";
			cout << "Email: " << currentStudent.email << "\n";
			cout << "Age: " << currentStudent.age << "\n";
			cout << "Phone: " << currentStudent.phone << "\n";
			cout << "Current Address: " << currentStudent.currentAddress << "\n";
			cout << "Student Type: " << currentStudent.studentType << "\n";
			ofstream file("students.txt", ios::app);
			file << "Student Profile: " << currentStudent.username << "\n";
			if (enrolledCount == 0) {
				cout << "Please enrol in a course first\n";
				file << "No courses enrolled\n";
				cout << endl;
			}
			else {
				for (int enrolledIndex = 0; enrolledIndex < enrolledCount; ++enrolledIndex) { // loop through all enrolled courses and print the course name
					cout << " - " << courses[enrolledCourseIndexes[enrolledIndex]].courseName << endl;
					file << "Enrolled in course: " << courses[enrolledCourseIndexes[enrolledIndex]].courseName << "\n";
					cout << endl;
				}
			}
			file.close();
		}
		else if (choice == "2") {
			cout << "Available Courses:\n";
			ofstream file("students.txt", ios::app);
			file << "View Available Courses: " << currentStudent.fullName << "\n";
			for (int courseIndex = 0; courseIndex < courses.size(); ++courseIndex) { // loop through all courses and print the course name and enrolled students count
				cout << (courseIndex + 1) << ". " << courses[courseIndex].courseName << "\n"
				<< " (" << courses[courseIndex].studentsEnrolled.size() << " enrolled)\n";
				file << courses[courseIndex].courseName << " (" << courses[courseIndex].studentsEnrolled.size() << " enrolled)\n";
				cout << endl;
			}
			file.close();
		}
		else if (choice == "3") {
			cout << "Enter courses number to enrol: ";
			string enrolchoice;
			getline(cin, enrolchoice);
			int selectedCourseIndex = -1; // variable to store the selected course index
			for (int courseIndex = 0; courseIndex < courses.size(); ++courseIndex) { // loop through all courses to find the selected course by comparing the input with the course index
				if (enrolchoice == to_string(courseIndex + 1)) { // if the input matches the course index
					selectedCourseIndex = courseIndex; // set the selectedCourseIndex to the course index
					break;
					cout << endl;
				}
			}
			ofstream file("students.txt", ios::app);
			if (selectedCourseIndex == -1) { // if the selectedCourseIndex is -1, it means the course is not found
				cout << "Invalid class number.\n";
				file << "Failed enrollment attempt by " << currentStudent.username << "\n";
				cout << endl;
			}
			else {
				bool alreadyEnrolled = false; // variable to check if the student is already enrolled in the course
				for (int studentInCourseIndex = 0; studentInCourseIndex < courses[selectedCourseIndex].studentsEnrolled.size(); ++studentInCourseIndex) {
					if (courses[selectedCourseIndex].studentsEnrolled[studentInCourseIndex] == currentStudent.username) alreadyEnrolled = true;
				}
				if (alreadyEnrolled) {
					cout << "You are already enrolled in this course.\n";
					file << "Already enrolled in course: " << courses[selectedCourseIndex].courseName << "\n";
				}
				else {
					courses[selectedCourseIndex].studentsEnrolled.push_back(currentStudent.username);
					cout << "You have been enrolled in " << courses[selectedCourseIndex].courseName << ".\n";
					file << "Enrolled in course: " << courses[selectedCourseIndex].courseName << "\n";
				}
			}
			file.close();
		}
		else if (choice == "4") {
			if (enrolledCount == 0) { // if the enrolledCount is 0, it means the student is not enrolled in any course
				cout << "No classes to drop.\n";
				ofstream file("students.txt", ios::app);
				file << "No classes to drop for " << currentStudent.username << "\n";
				file.close();
				cout << endl;
			}
			else {
				for (int enrolledIndex = 0; enrolledIndex < enrolledCount; ++enrolledIndex) {
					cout << (enrolledIndex + 1) << ". " << courses[enrolledCourseIndexes[enrolledIndex]].courseName << "\n";
				}
				cout << "Enter course number to drop: ";
				string dropChoice;
				getline(cin, dropChoice);
				int dropCourseIndex = -1; // variable to store the course index to be dropped
				for (int courseIndex = 0; courseIndex < enrolledCount; ++courseIndex) {
					if (dropChoice == to_string(courseIndex + 1)) {
						dropCourseIndex = enrolledCourseIndexes[courseIndex];
						break;
					}
				}
				ofstream file("students.txt", ios::app);
				if (dropCourseIndex == -1) {
					cout << "Invalid course number.\n";
					file << "Failed drop attempt by " << currentStudent.username << "\n";
				}
				else {
					bool found = false;
					for (int studentInCourseIndex = 0; studentInCourseIndex < courses[dropCourseIndex].studentsEnrolled.size(); ++studentInCourseIndex) {
						if (courses[dropCourseIndex].studentsEnrolled[studentInCourseIndex] == currentStudent.username) {
							courses[dropCourseIndex].studentsEnrolled.erase(courses[dropCourseIndex].studentsEnrolled.begin() + studentInCourseIndex);
							found = true;
							cout << "You have been dropped from " << courses[dropCourseIndex].courseName << ".\n";
							file << "Dropped from course: " << courses[dropCourseIndex].courseName << "\n";
							break;
						}
					}
					if (!found) {
						cout << "You are not enrolled in this course.\n";
						file << "Not enrolled in course: " << courses[dropCourseIndex].courseName << "\n";
					}
				}file.close();
			}
		}
		else if (choice == "5") {
			cout << "Logging out to main page...\n";
			ofstream file("students.txt", ios::app);
			file << "Student logged out: " << currentStudent.username << "\n";
			file.close();
			break;
		}
		else {
			cout << "Invalid option. Please try again.\n";
			ofstream file("students.txt", ios::app);
			file << "Invalid option selected by " << currentStudent.username << "\n";
			file.close();
		}
	}
}
// =======================
// Admin Menu
// =======================
// Coded by Han
// =======================

void adminMenu() { // function to display the admin menu and handle admin actions
    while (true) {
		cout << "\n*************** Admin Page ***************\n";
        cout << "1. View Student Profile (Alphabetically)\n";
        cout << "2. View Domestic/International Students\n";
        cout << "3. View Courses\n";
		cout << "4. Search Student by Username\n";
		cout << "5. Add or remove students from classes\n";
		cout << "6. Sign out to main page\n";
		cout << "Select an option: ";
		string choice;
		getline(cin, choice);
        if (choice == "1") viewStudentProfiles();
        else if (choice == "2") viewStudentByTypes();
        else if (choice == "3") viewCourseDetails();
        else if (choice == "4") searchStudentByName();
        else if (choice == "5") manageCourseEnrollment();
        else if (choice == "6") break;
		else cout << "Invalid option. Please try again.\n";
    }
}
// =======================

// =======================
// Password Functions
// =======================
// Coded by Matthew
// =======================

template <typename Pred>
bool contains_if(const string& s, Pred p)
{
	return any_of(s.begin(), s.end(), p);
}

struct Result
{
	int score;
	vector<string>tips;
};

// function for evaluating the password and setting the criteria
Result evaluate_password(const string& pw)
{
	Result out{ 0, {} };

	bool long_enough = pw.length() >= 8;
	bool has_upper = contains_if(pw, isupper);
	bool has_lower = contains_if(pw, islower);
	bool has_digit = contains_if(pw, isdigit);
	bool has_special = contains_if(pw, ispunct);

	// each criteria met adds 1 point, they need all 5 to meet requirements
	out.score = static_cast<int>(long_enough)
		+ static_cast<int>(has_upper)
		+ static_cast<int>(has_lower)
		+ static_cast<int>(has_digit)
		+ static_cast<int>(has_special);

	// Tips for each section they'll be prompted if not meting any
	if (!long_enough) out.tips.emplace_back("Use at least 8 charcters.");
	if (!has_upper) out.tips.emplace_back("Add an uppercase letter (A-Z).");
	if (!has_lower) out.tips.emplace_back("Add a lowercase leter (a-z).");
	if (!has_digit) out.tips.emplace_back("Include a digit (0-9).");
	if (!has_special) out.tips.emplace_back("Include a special character, e.g (!,@,#,$,%).");

	return out;
}
// gives feedback based on how strong they make the password
string strength_label(int score)
{
	switch (score)
	{
	case 5: return "Very Strong"; // will use this one in a Do While loop for the condition to exit the loop
	case 4: return "Strong";
	case 3: return "Moderate";
	case 2: return "Weak";
	default: return "Very Weak";
	}
}
// =======================

// =======================
// Main Menu
// =======================
// Coded by Han
// =======================
int main() { // main function to run the TalentHub Online application
    while (true) {
        cout << "\n*************** Welcome to the TalentHub Online ***************\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Forgot Username & password\n";
		cout << "4. Admin Page\n";
        cout << "5. Exit\n";
        cout << "Select an option: ";
        string choice;
        getline(cin, choice);

        if (choice == "1") {
            registerStudent();
        }
		else if (choice == "2") {
			string username, password;
			cout << "*************** Login ***************\n";
			cout << "Username: "; getline(cin, username);
			cout << "Password: "; password = get_valid_password();

			

			//getline(cin, password);

			int studentIndex = -1; // Initialize studentIndex to -1 to indicate that the student is not found yet
			for (int i = 0; i < students.size(); ++i) { // loop through all registered students to find the matching username and password
				if (students[i].username == username && students[i].password == password) {
					studentIndex = i;
					cout << "Login successful! Welcome, " << students[i].fullName << ".\n";
					ofstream file("students.txt", ios::app);
					file << "Student logged in: " << students[i].fullName << "\n";
					file.close();
					break;
				}
			}
			if (studentIndex != -1) {
				studentsMenu(studentIndex);
				ofstream file("students.txt", ios::app);
				file << "Student logged in successfully.\n";
				file.close();
			}
			else {
				cout << "Invalid username or password.\n";
			}
		}
        else if (choice == "3") {
			cout << "1. Forgot Username\n";
			cout << "2. Forgot Password\n";
			cout << "Select an option: ";
			string forgotChoice;
			getline(cin, forgotChoice);
			if (forgotChoice == "1") {
            forgotUsername();
        }
        else if (forgotChoice == "2") {
            forgotPassword();
			}
		else {
				cout << "Invalid option. Please try again.\n";
			}
		}   
		else if (choice == "4") {
			cout << "1. Admin Register\n";
			cout << "2. Admin Login\n";
			cout << "Select an option: ";
			string adminChoice;
			getline(cin, adminChoice);
			if (adminChoice == "1") {
				registerAdmin();
			}
			else if (adminChoice == "2") {
				if (Adminlogin()) {
					adminMenu();
					ofstream file("admins.txt", ios::app);
					file << "Admin logged in successfully.\n";
					file.close();
				}
			}
			else {
				cout << "Invalid option. Please try again.\n";
			}
		}
        else if (choice == "5") {
            cout << "Exiting application. Goodbye!\n";
            break;
        }
        else {
            cout << "Invalid option. Please try again.\n";
        }
    }
    return 0;
}
// =======================
// Password Functions
// =======================
// Coded by Matthew
// =======================
string get_valid_password()
{
	string password;
	Result res;

	do
	{
		// Tell the user the password conditions
		cout << "***** Password Conditions *****" << endl;
		cout << "Please use an Upper and lower case, A number. " << endl;
		cout << "A special character and be 8 characters long." << endl;
		cout << endl;
		cout << "Enter a Password: \n";
		//cin.ignore(numeric_limits<streamsize>::max(), '\n');
		getline(cin, password);

		res = evaluate_password(password); // Calling the function to evaluate the password after its been input

		cout << "\nPassword Strength: " << strength_label(res.score)
			<< " (" << res.score << "/5)\n"; // Gives a score out of 5

		if (!res.tips.empty()) // output the tips for the best practices they haven't followed yet.
		{
			cout << "\nSuggestions:\n";
			for (const string& tip : res.tips)
				cout << "  . " << tip << '\n' << endl;
		}

	} while (res.score < 5); // let the loop end once they have reached a perfect score (followed best practices).

	return password;
}
// =======================
