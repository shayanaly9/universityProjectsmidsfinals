#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <limits> // For numeric_limits

using namespace std;

// Transaction structure to hold details of each transaction
struct Transaction {
    int id;
    double amount;
    string date;
    string type; // "income" or "expense"
    Transaction* next;

    // Default constructor
    Transaction() : id(0), amount(0.0), date(""), type(""), next(NULL) {}

    // Parameterized constructor without default value for next
    Transaction(int id, double amount, const string& date, const string& type, Transaction* next) {
        this->id = id;
        this->amount = amount;
        this->date = date;
        this->type = type;
        this->next = next;
    }
};

// Linked List for managing transactions
class TransactionList {
private:
    Transaction* head;

public:
    TransactionList() : head(NULL) {}

    // Add transaction
    void addTransaction(int id, double amount, const string& date, const string& type) {
        Transaction* newTransaction = new Transaction(id, amount, date, type, head);
        head = newTransaction;
    }

    // Display all transactions
    void displayTransactions() {
        Transaction* temp = head;
        cout << "Transaction History:\n";
        while (temp) {
            cout << "ID: " << temp->id << ", Amount: " << temp->amount
                 << ", Date: " << temp->date << ", Expenses: " << temp->type << endl;
            temp = temp->next;
        }
    }

    // Search transaction by amount (Linear Search)
    Transaction* searchByAmount(double amount) {
        Transaction* temp = head;
        while (temp) {
            if (temp->amount == amount) return temp;
            temp = temp->next;
        }
        return NULL; // Return NULL if not found
    }

    // Delete transaction by ID
    void deleteTransaction(int id) {
        Transaction* temp = head;
        Transaction* prev = NULL;

        while (temp && temp->id != id) {
            prev = temp;
            temp = temp->next;
        }
        
        if (temp) {
            if (prev) {
                prev->next = temp->next;
            } else {
                head = temp->next;
            }
            delete temp; // Deallocate memory for the transaction
            cout << "Transaction " << id << " deleted.\n";
        } else {
            cout << "Transaction not found.\n";
        }
    }
    
    // Get head node for cumulative calculations
    Transaction* getHead() {
        return head;
    }

    // Destructor to clean up memory
    ~TransactionList() {
        while (head) {
            Transaction* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Stack-based undo functionality
class UndoStack {
private:
    stack<int> undoStack;  // Store IDs of transactions

public:
    void pushUndo(int transactionId) {
        undoStack.push(transactionId);
    }

    void popUndo(TransactionList& transactionList) {
        if (!undoStack.empty()) {
            int lastTransactionId = undoStack.top();
            undoStack.pop();
            transactionList.deleteTransaction(lastTransactionId);
            cout << "Last transaction undone.\n";
        } else {
            cout << "No transactions to undo.\n";
        }
    }
};

// Queue for reminders (e.g., recurring payments)
class ReminderQueue {
private:
    queue<string> reminders;

public:
    void addReminder(const string& reminder) {
        reminders.push(reminder);
    }

    void processReminders() {
        cout << "Processing Reminders:\n";
        while (!reminders.empty()) {
            cout << reminders.front() << endl;
            reminders.pop();
        }
    }
};

// Recursive function for cumulative transaction calculation
double cumulativeTransaction(Transaction* transaction, double total = 0) {
    if (!transaction) return total;
    return cumulativeTransaction(transaction->next, total + transaction->amount);
}

// Main Application Class
class FinanceTracker {
private:
    TransactionList transactions;
    UndoStack undoStack;
    ReminderQueue reminders;
    int transactionCount = 0;

public:
    // Add transaction and save for undo
    void addTransaction(double amount, const string& date, const string& type) {
        transactions.addTransaction(++transactionCount, amount, date, type);
        undoStack.pushUndo(transactionCount);
        cout << "Transaction added.\n";
    }

    // Display transactions
    void displayTransactions() {
        transactions.displayTransactions();
    }

    // Delete a transaction by ID
    void deleteTransaction(int id) {
        transactions.deleteTransaction(id);
    }

    // Search transaction by amount
    void searchTransaction(double amount) {
        Transaction* result = transactions.searchByAmount(amount);
        if (result) {
            cout << "Transaction Found - ID: " << result->id << ", Amount: " << result->amount
                 << ", Date: " << result->date << ", Type: " << result->type << endl;
        } else {
            cout << "No transaction with amount " << amount << " found.\n";
        }
    }

    // Undo last transaction
    void undoLastTransaction() {
        undoStack.popUndo(transactions);
    }

    // Add a reminder
    void addReminder(const string& reminder) {
        reminders.addReminder(reminder);
    }

    // Process all reminders
    void processReminders() {
        reminders.processReminders();
    }

    // Calculate and display cumulative transactions
    void calculateCumulativeTransactions() {
        double total = cumulativeTransaction(transactions.getHead());
        cout << "Cumulative Transaction Amount: " << total << endl;
    }
};

// Main function
int main() {
    FinanceTracker tracker;
    int choice;
    double amount;
    string date, type;

    do {
        cout << "\nPersonal Finance Tracker:\n";
        cout << "1. Add Transaction\n";
        cout << "2. Display Transactions\n";
        cout << "3. Delete Transaction\n";
        cout << "4. Search Transaction by Amount\n";
        cout << "5. Undo Last Transaction\n";
        cout << "6. Add Reminder\n";
        cout << "7. Process Reminders\n";
        cout << "8. Calculate Cumulative Transactions\n";
        cout << "9. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear input buffer after integer input

        switch (choice) {
            case 1:
                cout << "Enter amount: ";
                cin >> amount;
                cin.ignore();
                cout << "Enter date (DD-MM-YYYY): ";
                getline(cin, date);
                cout << "Enter type (income/expense): ";
                getline(cin, type);
                tracker.addTransaction(amount, date, type);
                break;
            case 2:
                tracker.displayTransactions();
                break;
            case 3: {
                int id;
                cout << "Enter transaction ID to delete: ";
                cin >> id;
                cin.ignore();
                tracker.deleteTransaction(id);
                break;
            }
            case 4:
                cout << "Enter amount to search: ";
                cin >> amount;
                cin.ignore();
                tracker.searchTransaction(amount);
                break;
            case 5:
                tracker.undoLastTransaction();
                break;
            case 6:
                cout << "Enter reminder: ";
                getline(cin, type);
                tracker.addReminder(type);
                break;
            case 7:
                tracker.processReminders();
                break;
            case 8:
                tracker.calculateCumulativeTransactions();
                break;
            case 9:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 9);

    return 0;
}
