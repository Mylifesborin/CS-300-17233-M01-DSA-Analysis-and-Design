//============================================================================
// Name        : ProjectTwo.cpp
// Author      : Yakuba Conde
// Version     :
// Description : CS-300-17233-M01 DSA: Analysis and Design Project
//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

// Struct to store information about a course
struct Course {
    string courseNumber; // Example: CSCI100
    string title;        // Course title like "Intro to Programming"
    vector<string> prerequisites; // List of prerequisite courses
};

// Function prototypes
void loadCourses(const string& filename, map<string, Course>& courses);
void printCourseList(const map<string, Course>& courses);
void printCourseDetails(const map<string, Course>& courses, const string& courseNumber);
bool isValidInput(); // To validate user input
string toUpper(const string& str); // Converts string to uppercase

int main() {
    map<string, Course> courses; // Map to store course data
    int choice; // User's menu selection
    string filename = "CS 300 ABCU_Advising_Program_Input.csv"; // Default CSV file name

    cout << "Welcome to the course planner." << endl; // Initial program message

    do {
        // Display the menu options
        cout << "\n1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "9. Exit" << endl;
        cout << "What would you like to do? ";

        // Check if the input is a valid number
        if (!isValidInput()) {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
            continue;
        }

        cin >> choice; // Read the user's choice

        // Handle the menu options
        switch (choice) {
            case 1: {
                cout << "Loading courses from default file: " << filename << endl;
                loadCourses(filename, courses); // Call function to load courses from file
                break;
            }
            case 2:
                printCourseList(courses); // Print the list of all courses
                break;
            case 3: {
                string courseNumber;
                cout << "What course do you want to know about? ";
                cin >> courseNumber; // Get course number from user
                printCourseDetails(courses, toUpper(courseNumber)); // Display course details
                break;
            }
            case 9:
                cout << "Thank you for using the course planner!" << endl; // Exit message
                break;
            default:
                cout << choice << " is not a valid option." << endl; // For invalid menu options
        }
    } while (choice != 9); // Loop until the user chooses to exit

    return 0;
}

// Converts a string to uppercase for consistency in lookups
string toUpper(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

// Loads courses from the given CSV file into the courses map
void loadCourses(const string& filename, map<string, Course>& courses) {
    ifstream file(filename); // Open the file
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl; // File open error message
        return;
    }

    string line;
    while (getline(file, line)) { // Read each line from the file
        stringstream ss(line); // Use stringstream to parse the line
        string courseNumber, title, prereq;
        getline(ss, courseNumber, ','); // Get course number
        getline(ss, title, ',');       // Get course title

        if (courseNumber.empty() || title.empty()) {
            cerr << "Error: Malformed line in CSV file." << endl; // Handle bad data
            continue;
        }

        Course course; // Create a new Course object
        course.courseNumber = courseNumber;
        course.title = title;

        // Read all prerequisites
        while (getline(ss, prereq, ',')) {
            if (!prereq.empty()) {
                course.prerequisites.push_back(prereq); // Add prereq to the course
            }
        }

        courses[courseNumber] = course; // Add the course to the map
    }

    file.close(); // Close the file
    cout << "Courses loaded successfully." << endl; // Success message
}

// Prints a sorted list of all courses available in the map
void printCourseList(const map<string, Course>& courses) {
    if (courses.empty()) { // Check if the map is empty
        cout << "No courses available. Please load the courses first." << endl;
        return;
    }

    cout << "\nHere is a sample schedule:" << endl;
    for (const auto& [courseNumber, course] : courses) { // Loop through the map
        cout << courseNumber << ", " << course.title << endl; // Print course details
    }
}

// Prints details of a specific course, including its prerequisites
void printCourseDetails(const map<string, Course>& courses, const string& courseNumber) {
    auto it = courses.find(courseNumber); // Search for the course in the map
    if (it == courses.end()) { // If course not found
        cout << "Course not found." << endl;
        return;
    }

    const Course& course = it->second; // Get the course object
    cout << "\n" << course.courseNumber << ", " << course.title << endl; // Print course info

    if (!course.prerequisites.empty()) { // Check if the course has prerequisites
        cout << "Prerequisites: ";
        for (size_t i = 0; i < course.prerequisites.size(); ++i) {
            cout << course.prerequisites[i]; // Print each prerequisite
            if (i < course.prerequisites.size() - 1) {
                cout << ", "; // Add comma between prerequisites
            }
        }
        cout << endl;
    } else {
        cout << "Prerequisites: None" << endl; // No prerequisites
    }
}

// Validates that user input is an integer
bool isValidInput() {
    return cin.peek() >= '0' && cin.peek() <= '9'; // Check if input is a number
}
