#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
using namespace std;

class Customer
{
protected:
  int id;
  string name;
  string address;
  string area;
  long phone_no;
  string membershipType;

public:
  Customer(int id, string name, string address, string area, long phone_no, string membershipType)
      : id(id), name(name), address(address), area(area), phone_no(phone_no), membershipType(membershipType) {}

  virtual void displayCustomer() const
  {
    cout << setw(10) << left << id
         << setw(15) << left << name
         << setw(15) << left << address
         << setw(15) << left << area
         << setw(10) << left << phone_no
         << setw(10) << left << membershipType;
  }

  int getId() const { return id; }
};



class Order : public Customer
{
protected:
  string item_name;
  double price;
  int quantity;
  string order_date;
  string deliveryDate;
  bool orderStatus;
  double discount;
  double totalAmount;

public:
  Order(int id, string name, string address, string area, long phone_no, string membershipType,
        string item_name, double price, int quantity, string order_date, string deliveryDate, double discount)
      : Customer(id, name, address, area, phone_no, membershipType), item_name(item_name), price(price), quantity(quantity),
        order_date(order_date), deliveryDate(deliveryDate), discount(discount), orderStatus(false)
  {
    totalAmount = (price * quantity) * (1 - discount);
  }

  void dispatchOrder()
  {
    orderStatus = true;
  }

  void displayCustomer() const override
  {
    Customer::displayCustomer();
    cout << setw(15) << left << item_name
         << setw(10) << left << price
         << setw(10) << left << quantity
         << setw(10) << left << order_date
         << setw(10) << left << deliveryDate
         << setw(10) << left << discount
         << setw(10) << left << totalAmount
         << setw(10) << left << (orderStatus ? "Yes" : "No") << endl;
  }

  bool isOrderStatus() const
  {
    return orderStatus;
  }
};




class WarehouseSystem
{
private:
  Order *orders[10];
  int orderCount;
  int totalDispatched;

public:
  WarehouseSystem() : orderCount(0), totalDispatched(0) {}

  void createOrder()
  {
    if (orderCount >= 10)
    {
      cout << "Cannot create more orders. Maximum limit reached." << endl;
      return;
    }

    int id, quantity;
    long phone_no;
    string name, address, area, membershipType, item_name, order_date, deliveryDate;
    double price, discount = 0.0;

    cout << "Enter Order Details:\n";

    // Customer ID validation
    while (true)
    {
      cout << "Customer ID (numeric only): ";
      cin >> id;
      if (cin.fail() || id <= 0)
      {
        cout << "Invalid ID! Please enter a positive integer ID.\n";
        cin.clear();
        cin.ignore(10000, '\n');
      }
      else
      {
        break;
      }
    }

    cout << "Customer Name: ";
    cin >> ws;
    getline(cin, name);
    cout << "Address: ";
    cin >> ws;
    getline(cin, address);
    cout << "Area: ";
    cin >> ws;
    getline(cin, area);

    // Phone number validation
    while (true)
    {
      cout << "Phone Number (10 digits): ";
      cin >> phone_no;
      if (cin.fail() || to_string(phone_no).length() != 10)
      {
        cout << "Invalid phone number! Please enter a 10-digit number.\n";
        cin.clear();
        cin.ignore(10000, '\n');
      }
      else
      {
        break;
      }
    }

    // Membership type validation with discount setting
    while (true)
    {
      cout << "Membership Type (golden, silver, platinum): ";
      cin >> membershipType;
      if (membershipType == "golden")
      {
        discount = 0.3;
        break;
      }
      else if (membershipType == "silver")
      {
        discount = 0.2;
        break;
      }
      else if (membershipType == "platinum")
      {
        discount = 0.4;
        break;
      }
      else
      {
        cout << "Invalid membership type! Please enter 'golden', 'silver', or 'platinum'.\n";
      }
    }

    cout << "Item Name: ";
    cin >> ws;
    getline(cin, item_name);
    cout << "Price: ";
    cin >> price;
    cout << "Quantity: ";
    cin >> quantity;

    while (true)
    {
      cout << "Order Date (YYYY-MM-DD): ";
      cin >> order_date;
      cout << "Delivery Date (YYYY-MM-DD): ";
      cin >> deliveryDate;

      int orderYear = stoi(order_date.substr(0, 4));
      int orderMonth = stoi(order_date.substr(5, 2));
      int orderDay = stoi(order_date.substr(8, 2));
      int deliveryYear = stoi(deliveryDate.substr(0, 4));
      int deliveryMonth = stoi(deliveryDate.substr(5, 2));
      int deliveryDay = stoi(deliveryDate.substr(8, 2));

      if (deliveryYear < orderYear ||
          (deliveryYear == orderYear && deliveryMonth < orderMonth) ||
          (deliveryYear == orderYear && deliveryMonth == orderMonth && deliveryDay <= orderDay))
      {
        cout << "Error: Delivery date must be after the order date!\n";
        continue;
      }

      int totalOrderDays = orderYear * 365 + orderMonth * 30 + orderDay;
      int totalDeliveryDays = deliveryYear * 365 + deliveryMonth * 30 + deliveryDay;

      if (totalDeliveryDays > totalOrderDays + 30)
      {
        cout << "Error: Delivery date cannot exceed 30 days from order date!\n";
        continue;
      }
      break;
    }

    orders[orderCount++] = new Order(id, name, address, area, phone_no, membershipType,
                                     item_name, price, quantity, order_date, deliveryDate, discount);
    cout << "Order created successfully!" << endl;
  }

  void displayOrders() const
  {
    cout << setw(10) << left << "ID"
         << setw(15) << left << "Name"
         << setw(15) << left << "Address"
         << setw(15) << left << "Area"
         << setw(10) << left << "Phone"
         << setw(10) << left << "Membership"
         << setw(15) << left << "Item Name"
         << setw(10) << left << "Price"
         << setw(10) << left << "Quantity"
         << setw(10) << left << "Order Date"
         << setw(10) << left << "Delivery Date"
         << setw(10) << left << "Discount"
         << setw(10) << left << "Total Amt"
         << setw(10) << left << "Dispatched" << endl;

    cout << "----------------------------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < orderCount; i++)
    {
      orders[i]->displayCustomer();
    }

    cout << "\nTotal Pending Orders: " << (orderCount - totalDispatched) << endl;
    cout << "Total Dispatched Orders: " << totalDispatched << endl;
  }

  void dispatchOrder()
  {
    int id;
    cout << "Enter Customer ID to dispatch: ";
    cin >> id;

    for (int i = 0; i < orderCount; i++)
    {
      if (orders[i]->getId() == id && !orders[i]->isOrderStatus())
      {
        orders[i]->dispatchOrder();
        cout << "Order dispatched successfully!" << endl;

        char received;
        cout << "Has the customer received the item? (y/n): ";
        cin >> received;

        if (received == 'y' || received == 'Y')
        {
          delete orders[i];
          for (int j = i; j < orderCount - 1; j++)
          {
            orders[j] = orders[j + 1];
          }
          orderCount--;
          cout << "Order removed from the system after customer received the item." << endl;
        }
        else
        {
          totalDispatched++;
        }
        return;
      }
    }
    cout << "Order not found or already dispatched!" << endl;
  }

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
    cout << "\n1. Create Order\n2. Display Orders\n3. Dispatch Order\n4. Exit\n";
    cout << "Select an option: ";
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
      cout << "Exiting program." << endl;
      return 0;
    default:
      cout << "Invalid choice! Please enter a valid option." << endl;
      break;
    }
  }
}
