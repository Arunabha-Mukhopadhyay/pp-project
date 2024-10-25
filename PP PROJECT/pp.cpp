#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// Base class for Customer
class Customer
{
protected:
  int id;
  string name;
  string area;
  string phone;

public:
  Customer(int customerId, const string &customerName, const string &customerArea, const string &customerPhone)
      : id(customerId), name(customerName), area(customerArea), phone(customerPhone) {}

  void displayCustomer() const
  {
    cout << setw(10) << left << id
         << setw(15) << left << name
         << setw(15) << left << area
         << setw(15) << left << phone;
  }

  int getId() const { return id; } 
};



class Order : public Customer
{
private:
  string itemName;
  double price;
  bool dispatched;

public:
  Order(int customerId, const string &customerName, const string &customerArea, const string &customerPhone,
        const string &item, double itemPrice)
      : Customer(customerId, customerName, customerArea, customerPhone), itemName(item), price(itemPrice), dispatched(false) {}

  void dispatchOrder()
  {
    dispatched = true;
  }


  void displayOrder() const
  {
    displayCustomer();
    cout << setw(15) << left << itemName
         << setw(10) << left << price
         << setw(10) << left << (dispatched ? "Yes" : "No") << endl;
  }
};

// Warehouse Management System
class WarehouseSystem
{
private:
  Order *orders[10]; 
  int orderCount;    

public:
  WarehouseSystem() : orderCount(0) {}

  void createOrder()
  {
    if (orderCount >= 10)
    {
      cout << "Cannot create more orders. Maximum limit reached." << endl;
      return;
    }

    int id;
    string name, area, phone, itemName;
    double price;

    cout << "Enter Customer ID: ";
    cin >> id;
    cout << "Enter Customer Name: ";
    cin >> name;
    cout << "Enter Area: ";
    cin >> area;
    cout << "Enter Phone Number: ";
    cin >> phone;
    cout << "Enter Item Name: ";
    cin >> itemName;
    cout << "Enter Item Price: ";
    cin >> price;

    orders[orderCount++] = new Order(id, name, area, phone, itemName, price);
    cout << "Order created successfully!" << endl;
  }

  void displayOrders() const
  {
    cout << setw(10) << left << "ID"
         << setw(15) << left << "Name"
         << setw(15) << left << "Area"
         << setw(15) << left << "Phone"
         << setw(15) << left << "Item Name"
         << setw(10) << left << "Price"
         << setw(10) << left << "Dispatched" << endl;

    cout << "---------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < orderCount; i++)
    {
      orders[i]->displayOrder(); 
    }
  }

  void dispatchOrder()
  {
    int id;
    cout << "Enter Customer ID to dispatch: ";
    cin >> id;

    for (int i = 0; i < orderCount; i++)
    {
      if (orders[i]->getId() == id)
      {
        orders[i]->dispatchOrder();
        cout << "Order dispatched successfully!" << endl;
        return;
      }
    }
    cout << "Order not found!" << endl;
  }


  // Destructor to clean up dynamically allocated orders
  ~WarehouseSystem()
  {
    for (int i = 0; i < orderCount; i++)
    {
      delete orders[i];
    }
  }
};




int main()
{
  WarehouseSystem system;

  while (true)
  {
    cout << "\n1. Create Order\n2. Display Orders\n3. Dispatch Order\n4. Exit\nChoose an option: ";
    int choice;
    cin >> choice;

    switch (choice)
    {
    case 1:
      system.createOrder();
      break;
    case 2:
      system.displayOrders();
      break;
    case 3:
      system.dispatchOrder();
      break;
    case 4:
      return 0;
    default:
      cout << "Invalid choice, please try again." << endl;
    }
  }

  return 0;
}
