#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class Customer
{
protected:
  int id;
  string name;
  string address;
  string area;
  int phone_no;
  string membershipType;

public:
  Customer(int id, string name, string address, string area, int phone_no, string membershipType)
      : id(id), name(name), address(address), area(area), phone_no(phone_no), membershipType(membershipType) {}

  void displayCustomer() const
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
  Order(int id, string name, string address, string area, int phone_no, string membershipType,
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

  bool isDeliveryOnTime() const
  {
    if (orderStatus && deliveryDate >= order_date)
    {
      return true;
    }
    return false;
  }

  void displayOrder() const
  {
    displayCustomer();
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

    int id, phone_no, quantity;
    string name, address, area, membershipType, item_name, order_date, deliveryDate;
    double price, discount;

    cout << "Enter Order Details:\n";
    cout << "Customer ID: ";
    cin >> id;
    cout << "Customer Name: ";
    cin >> name;
    cout << "Address: ";
    cin >> address;
    cout << "Area: ";
    cin >> area;
    cout << "Phone Number: ";
    cin >> phone_no;
    cout << "Membership Type: ";
    cin >> membershipType;
    cout << "Item Name: ";
    cin >> item_name;
    cout << "Price: ";
    cin >> price;
    cout << "Quantity: ";
    cin >> quantity;
    cout << "Order Date: ";
    cin >> order_date;
    cout << "Delivery Date: ";
    cin >> deliveryDate;
    cout << "Discount (e.g., 0.1 for 10%): ";
    cin >> discount;

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
      orders[i]->displayOrder();
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
    default:
      cout << "Invalid choice, please try again." << endl;
    }
  }

  return 0;
}
