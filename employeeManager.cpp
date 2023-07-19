#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Employee {
private:
    std::string name;
    std::string position;
    double salary;

public:
    Employee() {}

    Employee(const std::string& n, const std::string& p, double s)
        : name(n), position(p), salary(s) {}

    void display() const {
        std::cout << "Name: " << name
                  << "\nPosition: " << position
                  << "\nSalary: $" << salary << "\n";
    }

    std::string getName() const {
        return name;
    }

    std::string getPosition() const {
        return position;
    }

    double getSalary() const {
        return salary;
    }

    // Assuming setter methods might be needed for the edit function
    void setName(const std::string& n) {
        name = n;
    }

    void setPosition(const std::string& p) {
        position = p;
    }

    void setSalary(double s) {
        salary = s;
    }
};

class EmployeeManager {
private:
    std::vector<Employee> employees;

public:
    void addEmployee(const Employee& e) {
        employees.push_back(e);
    }

    void listEmployees() const {
        for (const Employee& e : employees) {
            e.display();
        }
    }

    void searchEmployeeByName(const std::string& name) const {
        for (const Employee& e : employees) {
            if (e.getName() == name) {
                e.display();
            }
        }
    }

    void editEmployee(const std::string& name) {
        for (Employee& e : employees) {
            if (e.getName() == name) {
                std::string newName, newPosition;
                double newSalary;

                std::cout << "Enter new name (leave empty for no change): ";
                std::getline(std::cin, newName);
                if (!newName.empty()) e.setName(newName);

                std::cout << "Enter new position (leave empty for no change): ";
                std::getline(std::cin, newPosition);
                if (!newPosition.empty()) e.setPosition(newPosition);

                std::cout << "Enter new salary (negative for no change): ";
                std::cin >> newSalary;
                if (newSalary >= 0) e.setSalary(newSalary);

                break;  // Exit after editing the first matching employee
            }
        }
    }

    void saveToFile(const std::string& filename) const {
        std::ofstream outFile(filename.c_str());
        for (const Employee& e : employees) {
            outFile << e.getName() << "\n";
            outFile << e.getPosition() << "\n";
            outFile << e.getSalary() << "\n";
        }
        outFile.close();
    }

    void loadFromFile(const std::string& filename) {
        std::ifstream inFile(filename.c_str());
        std::string name, position;
        double salary;

        employees.clear();  // Assuming you want to replace the current list

        while (getline(inFile, name)) {
            getline(inFile, position);
            inFile >> salary;
            inFile.ignore();  // Ignore the newline after the salary
            employees.push_back(Employee(name, position, salary));
        }
        inFile.close();
    }
};

int main() {
    EmployeeManager manager;
    manager.addEmployee(Employee("John Doe", "Developer", 50000.00));
    manager.addEmployee(Employee("Jane Smith", "Designer", 55000.00));

    std::cout << "List of employees:\n";
    manager.listEmployees();

    std::cout << "\nSearching for Jane Smith:\n";
    manager.searchEmployeeByName("Jane Smith");

    std::cout << "\nEditing Jane Smith's details:\n";
    manager.editEmployee("Jane Smith");
    manager.listEmployees();

    manager.saveToFile("employees.txt");

    EmployeeManager newManager;
    newManager.loadFromFile("employees.txt");
    std::cout << "\nLoaded employees from file:\n";
    newManager.listEmployees();

    return 0;
}

