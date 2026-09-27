// BANKING MANAGEMENT SYSTEM

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;

// Customer Class
class Customer
{
private:
    string customer_id;
    string customer_name;

public:
    Customer()
    {
        customer_id = "";
        customer_name = "";
    }

    Customer(string id, string name)
    {
        customer_id = id;
        customer_name = name;
    }

    void displayCustomer()
    {
        cout << "Customer ID: " << customer_id << endl;
        cout << "Customer Name: " << customer_name << endl;
    }
};

// Transaction Class
class Transaction
{
private:
    string type;
    double amount;

public:
    Transaction(string t, double a)
    {
        type = t;
        amount = a;
    }

    void displayTransaction()
    {
        cout << type << " : " << amount << endl;
    }
};

// Bank Account Class
class BankAccount
{
    private:
      string acc_number;
      string acc_holder_name;
      double balance;
      vector<Transaction> transactions;

    public:
    // constructor
    BankAccount(string n, string h, double b)
    {
        acc_number = n;
        acc_holder_name = h;
        balance = b;
    }

    // Default constructor
    BankAccount()
    {
        acc_number = "";
        acc_holder_name = "";
        balance = 0.0;
    }

    // Deposit Function
    void deposit(double amount)
    {
        if(amount>0)
        {
            balance += amount;
            cout<<"Amount Deposited: "<<amount<<endl;
            cout<<"New Balance: "<< balance<<endl;
            cout<<"Amount Deposited Successfully!"<<endl;
            transactions.push_back(Transaction("Deposit ", amount));
        }
        else
        {
            cout<<"Deposit Amount Must Be Positive. Try Again!";
        }
        cout<<endl;
    }

    // withdraw Function
    void withdraw(double amount)
    {
        if(amount>0 && amount<=balance)
        {
            balance -= amount;
            cout<<"Amount Withdraw: "<<amount<<endl;
            cout<<"New Balance: "<< balance<<endl;
            cout<<"Amount Withdraw Successfully!"<<endl;
            transactions.push_back(Transaction("Withdrawal ", amount));
        }
        else
        {
            cout<<"Invalid Amount!"<<endl;
        }
        cout<<endl;
    }

     // Fund Transfer Function
    void transfer(BankAccount &receiver, double amount)
    {
        if(amount > 0 && amount <= balance)
        {
            balance -= amount;
            receiver.balance += amount;

            transactions.push_back
            (
                Transaction("Transfer Sent", amount)
            );

            receiver.transactions.push_back
            (
                Transaction("Transfer Received", amount)
            );

            cout << "Amount Transferred: " << amount << endl;
            cout << "Transfer Successful!" << endl;
            cout << "New Balance: " << balance << endl;
        }
        else
        {
            cout << "Invalid Amount or Insufficient Balance!" << endl;
        }
        cout<<endl;
    }

    // Check Balance Function
    void checkbalance() const 
    {
        cout<<"Account Balance: "<< balance<<endl;
        cout<<endl;
    }

    // Display Account Information Function
    void displayAccount()
    {
        cout << endl;
        cout << "------ACCOUNT INFORMATION------" << endl;
        cout << "Account Number: " << acc_number << endl;
        cout << "Account Holder: " << acc_holder_name << endl;
        cout << "Balance: " << balance << endl;
        cout<<endl;
    }

    // Display Transaction History
    void showTransactions()
    {
        cout << endl;
        cout << "----- TRANSACTION HISTORY -----" << endl;

        if(transactions.empty())
        {
            cout << "No transactions found." << endl;
            return;
        }

        for(int i = 0; i < transactions.size(); i++)
        {
            cout << i + 1 << ". ";
            transactions[i].displayTransaction();
        }
        cout<<endl;
    }

    // Save Account Faunction
    void saveAccount()
    {
        ofstream file("account.txt");

        if(file.is_open())
        {
            file << acc_number << endl;
            file << acc_holder_name << endl;
            file << balance << endl;
            file.close();
            cout << "Account details saved successfully!" << endl;
        }
        else
        {
            cout << "Error! Unable to save account details." << endl;
        }
        cout<<endl;
    }
};

int main()
{
    cout<<"========Welcome to Bank Application========"<<endl;
    cout<<endl;
    string customer_id;
    string customer_name;
    string acc_num;

    cout 
    << "Enter Customer ID: ";
    cin >> customer_id;
    cout << "Enter Customer Name: ";
    cin >> customer_name;
    cout<<"Enter Account Number: ";
    cin>>acc_num;

    Customer customer(customer_id, customer_name);
    BankAccount account(acc_num, customer_name, 0.0);

    int choice;

    do
    {
        cout<< "----MENU----"<<endl;
        cout << "1. Deposit Amount" << endl;
        cout << "2. Withdraw Amount" << endl;
        cout << "3. Check Balance" << endl;
        cout << "4. Transfer Funds" << endl;
        cout << "5. View Account Information" << endl;
        cout << "6. View Transaction History" << endl;
        cout << "7. Save Account" << endl;
        cout << "8. Exit" << endl;
        cout << endl;

        cout<<"Enter your Choice: ";
        cin>> choice;

        switch(choice)
        {
            case 1:
            {
                double amount;
                cout<<"Enter Amount to Deposit: ";
                cin>> amount;
                account.deposit(amount);
            }
            break;
            case 2:
            {
                double amount;
                cout<<"Enter Amount to withdraw: ";
                cin>> amount;
                account.withdraw(amount);
            }
            break;
            case 3:
            {
                account.checkbalance();
            }
            break;
            case 4:
            {
                string receiver_num;
                double amount;

                cout << "Enter Receiver Account Number: ";
                cin >> receiver_num;

                cout << "Enter Amount to Transfer: ";
                cin >> amount;

                BankAccount receiver(receiver_num, "Receiver", 0.0);

                account.transfer(receiver, amount);
            }
            break;
            case 5:
            {
                customer.displayCustomer();
                account.displayAccount();
            }
            break;
            case 6:
            {
                account.showTransactions();
            }
            break;
            case 7:
            {
                account.saveAccount();    
            }
            break;
            case 8:
            {
                cout<<"Exiting...."<<endl;
                cout<<"Thank for using Bank Appication"<<endl;
            }
            break;
            default:
            cout<<"Invalid Option! Try Again!";
        }
    }while(choice != 8);

    cout<<endl;
    return 0;
}