#include <iostream>
using namespace std;

float balance = 1000.0f; 

void Deposit(float amount) 
{
    balance += amount;
    cout << "Successfully deposited RM " << amount << endl;
    cout << "Current Balance: RM" << balance << "\n" << endl;
}

bool Withdraw(float amount) 
{
    if (amount <= 0) 
    {
        cout << "Withdrawal failed: Amount must be greater than zero." << endl;
        return false;
    }

    if (amount > balance) 
    {
        cout << "Withdrawal failed: Insufficient funds!" << endl;
        return false; 
    }
    
    balance -= amount;
    cout << "Successfully withdrew RM " << amount << endl;
    return true; 
}

int main() 
{
    float depositAmount;

    cout << "Initial Balance: RM" << balance << endl;
    do {

        cout << "Deposit amount: RM";
        cin >> depositAmount;
        if (depositAmount <= 0) 
        {
            cout << "Deposit failed: Amount must be greater than zero." << endl;
        } 
        
        else 
        {
            Deposit(depositAmount);
        }

    } while (depositAmount <= 0);
    
    bool success1 = Withdraw(50.00f);
    cout << "Withdrawal Success Status: " << (success1 ? "TRUE" : "FALSE") << endl;
    cout << "Current Balance: RM" << balance << "\n" << endl;

    bool success2 = Withdraw(2000.00f);
    cout << "Withdrawal Success Status: " << (success2 ? "TRUE" : "FALSE") << endl;
    cout << "Final Balance: RM" << balance << endl;

    return 0;
}