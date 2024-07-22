#include <iostream>
#include <string>

using namespace std;

const int MAX_TASKS = 100;

class ToDoListManager {
private:
    string tasks[MAX_TASKS];
    bool completed[MAX_TASKS];
    int taskCount;

public:
    ToDoListManager() : taskCount(0) {
        for (int i = 0; i < MAX_TASKS; ++i) {
            completed[i] = false;
        }
    }

    void addTask(const string& taskDescription) {
        if (taskCount < MAX_TASKS) {
            tasks[taskCount] = taskDescription;
            completed[taskCount] = false;
            taskCount++;
        } else {
            cout << "Task list is full." << endl;
        }
    }

    void viewTasks() const {
        if (taskCount == 0) {
            cout << "No tasks to display." << endl;
        } else {
            for (int i = 0; i < taskCount; ++i) {
                cout << i + 1 << ". " << tasks[i] 
                     << " - " << (completed[i] ? "Completed" : "Pending") 
                     << endl;
            }
        }
    }

    void markTaskCompleted(int taskNumber) {
        if (taskNumber > 0 && taskNumber <= taskCount) {
            completed[taskNumber - 1] = true;
        } else {
            cout << "Invalid task number." << endl;
        }
    }

    void removeTask(int taskNumber) {
        if (taskNumber > 0 && taskNumber <= taskCount) {
            for (int i = taskNumber - 1; i < taskCount - 1; ++i) {
                tasks[i] = tasks[i + 1];
                completed[i] = completed[i + 1];
            }
            taskCount--;
        } else {
            cout << "Invalid task number." << endl;
        }
    }

    void run() {
        int choice;
        string description;
        int taskNumber;

        while (true) {
            cout << "\nTo-Do List Manager" << endl;
            cout << "1. Add Task" << endl;
            cout << "2. View Tasks" << endl;
            cout << "3. Mark Task as Completed" << endl;
            cout << "4. Remove Task" << endl;
            cout << "5. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;
            cin.ignore(); // To ignore the leftover newline character

            switch (choice) {
                case 1:
                    cout << "Enter task description: ";
                    getline(cin, description);
                    addTask(description);
                    break;
                case 2:
                    viewTasks();
                    break;
                case 3:
                    cout << "Enter task number to mark as completed: ";
                    cin >> taskNumber;
                    markTaskCompleted(taskNumber);
                    break;
                case 4:
                    cout << "Enter task number to remove: ";
                    cin >> taskNumber;
                    removeTask(taskNumber);
                    break;
                case 5:
                    return;
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
        }
    }
};

int main() {
    ToDoListManager manager;
    manager.run();
    return 0;
}

