#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
class Student {
private:
    string full_name;
    int credit_book_number;
    double averageScore;
    bool is_budget;
    bool has_scholarship;
    static int last_id;
    int student_id;

public:
    
    Student() : full_name(""), credit_book_number(0), averageScore(0.0), is_budget(false), has_scholarship(false), student_id(0) {}
    Student(string name, int book_number, double gpa, bool is_budget, bool has_scholarship)
        : full_name(name), credit_book_number(book_number), averageScore(gpa), is_budget(is_budget), has_scholarship(has_scholarship) {
        student_id = generateID();
    }
    Student(string name, int book_number, double gpa)
        : full_name(name), credit_book_number(book_number), averageScore(gpa), is_budget(false), has_scholarship(false) {
        student_id = generateID();
    }

    ~Student() {}

   

    bool operator==(const Student& student) const {
        return full_name == student.full_name;
    }

    bool operator>(const Student& student) const {
        return full_name > student.full_name;
    }

    bool operator<(const Student& student) const {
        return full_name < student.full_name;
    }
    bool CompareAverageScore(const Student& student) const {
        return averageScore < student.averageScore;
    }
    int GetStudentID()
    {
        return student_id;
    }
    double GetAverageScore()
    {
        return averageScore;
    }
    bool GetIsBudget()
    {
		return is_budget;
	}
    bool GetHasScholarship()
    {
        return has_scholarship;
    }
    string GetFullName()
    {
		return full_name;
	}
    int GetCreditBookNumber()
    {
		return credit_book_number;
	}


    Student& operator=(const Student& student) {
        if (this != &student) {
            full_name = student.full_name;
            credit_book_number = student.credit_book_number;
            averageScore = student.averageScore;
            is_budget = student.is_budget;
            has_scholarship = student.has_scholarship;
            student_id = student.student_id;
        }
        return *this;
    }

    void display() {
        cout << "Student ID: " << student_id << endl;
        cout << "Full Name: " << full_name << endl;
        cout << "Credit Book Number: " << credit_book_number << endl;
        cout << "Average score: " << averageScore << endl;
        cout << "Budget Student: " << (is_budget ? "Yes" : "No") << endl;
        cout << "Scholarship: " << (has_scholarship ? "Yes" : "No") << endl;
    }

    friend std::ostream& operator<<(std::ostream& os, const Student& student) {
        os << "Student ID: " << student.student_id << endl;
        os << "Full Name: " << student.full_name << endl;
        os << "Credit Book Number: " << student.credit_book_number << endl;
        os << "Average score: " << student.averageScore << endl;
        os << "Budget Student: " << (student.is_budget ? "Yes" : "No") << endl;
        os << "Scholarship: " << (student.has_scholarship ? "Yes" : "No") << endl;
        return os;
    }

    int generateID() {
        return ++last_id;
    }
};

int Student::last_id = 0;

class Archive {
private:
    vector<Student> students;
    string archive_name;

public:
    Archive(string name) : archive_name(name) {}

    ~Archive() {}

    void addStudent(const Student& student) {
        students.push_back(student);
    }

    Student* findStudentById(int id) {
        for (auto& student : students) {
            if (student.GetStudentID() == id) {
                return &student;
            }
        }
        return nullptr; 
    }

    bool deleteStudentById(int id) {
        auto it = remove_if(students.begin(), students.end(), [id](Student& student) {
            return student.GetStudentID() == id;
        });
        if (it != students.end()) {
            students.erase(it, students.end());
            return true;
        }
        return false; 
    }
    vector<Student> sortStudentsByName() {
		vector<Student> sortedStudents = students;
		sort(sortedStudents.begin(), sortedStudents.end());
		return sortedStudents;
	}
    void displayTable() {
        vector<Student> sortedStudents = sortStudentsByName();
        cout << "Archive (sorted by name): " << archive_name << endl;
        cout << "--------------------------------------------------------------------------" << endl;
        cout << "Student ID  |  Full Name          |  Average score  |  Budget  |  Scholarship" << endl;
        cout << "--------------------------------------------------------------------------" << endl;
        for (auto& student : sortedStudents) {
            cout << student.GetStudentID() << "          |  " << student.GetFullName() << "          |  " << student.GetAverageScore()
                << "  |  " << (student.GetIsBudget() ? "Yes" : "No") << "  |  "
                << (student.GetHasScholarship() ? "Yes" : "No") << endl;
        }
    }
    vector<Student> sortStudentsByAverageScore() {
		vector<Student> sortedStudents = students;
        sort(sortedStudents.begin(), sortedStudents.end(), [](Student& a, Student& b) {
			return a.CompareAverageScore(b);
		});
		return sortedStudents;
	}
    void displaySortedByAverageScore() {
        vector<Student> sortedStudents = sortStudentsByAverageScore();
        sort(sortedStudents.begin(), sortedStudents.end());
        cout << "Archive: " << archive_name << " (Sorted by average score)" << endl;
        cout << "--------------------------------------------------------------------------" << endl;
        cout << "Student ID  |  Full Name          |  Average score  |  Budget  |  Scholarship" << endl;
        cout << "--------------------------------------------------------------------------" << endl;
        for (auto& student : sortedStudents) {
            cout << student.GetStudentID() << "          |  " << student.GetFullName() << "          |  " << student.GetAverageScore()
                << "  |  " << (student.GetIsBudget() ? "Yes" : "No") << "  |  "
                << (student.GetHasScholarship() ? "Yes" : "No") << endl;
        }
    }
};

int main() {
    Archive studentArchive("Student Archive");

    studentArchive.addStudent(Student("John Smith", 12345678, 3.7, true, true));
    studentArchive.addStudent(Student("Alice Johnson", 87654321, 3.9, true, false));
    studentArchive.addStudent(Student("Bob Brown", 23456789, 3.5, false, true));

    studentArchive.displayTable();

    studentArchive.displaySortedByAverageScore();

    Student* foundStudent = studentArchive.findStudentById(2);
    if (foundStudent) {
        cout << "Found Student:" << endl;
        foundStudent->display();
    }
    else {
        cout << "Student not found." << endl;
    }

    bool deleted = studentArchive.deleteStudentById(1);
    if (deleted) {
        cout << "Student deleted." << endl;
    }
    else {
        cout << "Student not found." << endl;
    }

    studentArchive.displayTable();

    return 0;
}
