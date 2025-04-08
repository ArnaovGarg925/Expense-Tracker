#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Login {
private:
    vector<string> usernames;
    vector<string> passwords;

public:
    void showLoginMenu() {
        cout << "Welcome to the Expense Tracker!" << endl;
        cout << "Please log in to continue." << endl;
        cout << "1. Log In" << endl;
        cout << "2. Register" << endl;
        cout << "3. Exit" << endl;
    }

    bool isUserRegistered(const string& username) {
        for (const auto& user : usernames) {
            if (user == username) {
                return true;
            }
        }
        return false;
    }

    bool registerUser(const string& username, const string& password) {
        if (username.length() < 5 || password.length() < 12) {
            cout << "Username must be at least 5 characters and password at least 12 characters long." << endl;
            return false;
        }
        if (isUserRegistered(username)) {
            cout << "Username already exists." << endl;
            return false;
        }
        usernames.push_back(username);
        passwords.push_back(password);
        return true;
    }

    bool authenticateUser(const string& username, const string& password) {
        for (size_t i = 0; i < usernames.size(); ++i) {
            if (usernames[i] == username && passwords[i] == password) {
                return true;
            }
        }
        return false;
    }
};

class ExpenseTracker {
private:
    double balance;
    double savingsGoal;
    double savings;
    vector<string> credit_descriptions;
    vector<string> debit_descriptions;
    vector<double> monthlyExpenses;
    vector<double> monthlyEarnings;

public:
    ExpenseTracker() {
        balance = 0.0;
        savingsGoal = 0.0;
        savings = 0.0;
    }

    void credit() {
        double amount;
        cout << "Enter amount to credit: ";
        cin >> amount;
        if (amount <= 0) {
            cout << "Invalid amount." << endl;
            return;
        }
        cout << "Enter description: ";
        string description;
        cin >> description;
        credit_descriptions.push_back(description);
        cout << "Credited: " << amount << endl;
        balance += amount;
        monthlyEarnings.push_back(amount);
    }

    void debit() {
        double amount;
        cout << "Enter amount to debit: ";
        cin >> amount;
        if (amount <= 0) {
            cout << "Invalid amount." << endl;
            return;
        }
        if (amount <= balance) {
            balance -= amount;
            monthlyExpenses.push_back(amount);
            cout << "Debited: " << amount << endl;
        } else {
            cout << "Insufficient balance." << endl;
        }
        cout << "Enter description: ";
        string description;
        cin >> description;
        debit_descriptions.push_back(description);
    }

    void showMonthlyExpenses() {
        cout << "Monthly Expenses:" << endl;
        for (size_t i = 0; i < monthlyExpenses.size(); ++i) {
            cout << "------------------------" << endl;
            cout << "Transaction " << i + 1 << endl;
            cout << "Expense " << i + 1 << ": " << monthlyExpenses[i] << endl;
            cout << "Description: " << debit_descriptions[i] << endl;
            cout << "------------------------" << endl;
        }
    }

    void setSavingsGoal() {
        cout << "Enter savings goal: ";
        double goal;
        cin >> goal;
        if (goal <= 0) {
            cout << "Invalid savings goal." << endl;
            return;
        }
        savingsGoal = goal;
        cout << "Savings goal set to: " << savingsGoal << endl;
    }

    void addToSavings() {
        cout << "Enter amount to add to savings: ";
        double amount;
        cin >> amount;
        if (amount <= 0) {
            cout << "Invalid amount." << endl;
            return;
        }
        if (amount <= balance) {
            balance -= amount;
            savings += amount;
            cout << "Added to savings: " << amount << endl;
        } else {
            cout << "Insufficient balance." << endl;
        }
    }

    void generateReport() {
        double totalSpent = 0;
        double totalEarned = 0;
        for (const auto& expense : monthlyExpenses) {
            totalSpent += expense;
        }
        for (const auto& earning : monthlyEarnings) {
            totalEarned += earning;
        }
        cout << "------------------------" << endl;
        cout << "Report:" << endl;
        cout << "Total Spent: " << totalSpent << endl;
        cout << "Total Earned: " << totalEarned << endl;
        cout << "Balance: " << balance << endl;
        cout << "Savings: " << savings << endl;
        cout << "Savings Percentage: " << (savings / balance) * 100 << "%" << endl;
        cout << "Savings Goal: " << savingsGoal << endl;
        cout << "------------------------" << endl;
    }
};

int main() {
    Login login;
    while (true) {
        login.showLoginMenu();
        int choice;
        string username, password;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: // Log In
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: ";
                cin >> password;

                if (login.authenticateUser(username, password)) {
                    cout << "Login successful!" << endl;
                    ExpenseTracker tracker;
                    int trackerChoice;
                    while (true) {
                        cout << "------------------------" << endl;
                        cout << "Expense Tracker Menu:" << endl;
                        cout << "------------------------" << endl;
                        cout << "1. Credit" << endl;
                        cout << "2. Debit" << endl;
                        cout << "3. Show Monthly Expenses" << endl;
                        cout << "4. Set Savings Goal" << endl;
                        cout << "5. Add to Savings" << endl;
                        cout << "6. Generate Report" << endl;
                        cout << "7. Logout" << endl;
                        cout << "Enter your choice: ";
                        cin >> trackerChoice;
                        cout << "------------------------" << endl;

                        switch (trackerChoice) {
                            case 1:
                                tracker.credit();
                                break;
                            case 2:
                                tracker.debit();
                                break;
                            case 3:
                                tracker.showMonthlyExpenses();
                                break;
                            case 4:
                                tracker.setSavingsGoal();
                                break;
                            case 5:
                                tracker.addToSavings();
                                break;
                            case 6:
                                tracker.generateReport();
                                break;
                            case 7:
                                cout << "Logging out..." << endl;
                                goto login_menu; // Break out of the tracker menu loop
                            default:
                                cout << "Invalid choice. Please try again." << endl;
                        }
                    }
                } else {
                    cout << "Invalid username or password." << endl;
                }
                break;

            case 2: // Register
                cout << "Enter new username: ";
                cin >> username;
                cout << "Enter new password: ";
                cin >> password;

                if (login.registerUser(username, password)) {
                    cout << "Registration successful!" << endl;
                }
                break;

            case 3: // Exit
                cout << "Exiting..." << endl;
                return 0;

            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    login_menu:; // Label to return to the login menu
    }
}
