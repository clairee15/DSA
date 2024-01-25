// DSA.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>;

using namespace std;
#include "List.h";
#include "Dictionary.h";
#include "Queue.h";
#include "custList.h";
#include "BST.h";


//advance features implemented
//searching and browsing food by categories and location

//program data to be saved in csv file


//calls function (below main program)
void displayLogin();
void displayUserMenu();
void displayAdminMenu();
void displaySearchMenu();
void displayFood();
void displayOrderListFormat();
void categoriseFood();
void insertFood();

// BST Tree
BST foodTree;

//dictionaries
Dictionary(foodCat);
Dictionary(foodLoc);
Dictionary(ratingBook);


//List || Queue
custList customerList;
List foodselections;
Queue(orderList);


int main()
{
    insertFood();
    int x;
    do
    {
        displayLogin();
        cout << "Please select an option: ";
        cin >> x;
        switch (x)
        {
            //register customer account
        case 1:
        {
            //access csv file
            fstream fout;
            fout.open("custAccount.csv", ios::out | ios::app);

            string address;
            string firstName;
            string lastName;
            string hpNum;
            ItemType id;
            string password;
            string confirmpassword;

            cout << "           Register a new account        " << endl;
            cout << "---------------------------------------------" << endl;
            do
            {
                cout << "Please enter your first name: ";
                cin >> firstName;
                cout << "Please enter your last name: ";
                cin >> lastName;
                cout << "Please enter your phone number: ";
                cin >> hpNum;
                cout << "Please enter your address: ";
                cin >> address;
                cout << "Please enter your username: ";
                cin >> id;
                cout << "Please enter your password: ";
                cin >> password;
                cout << "Please enter your password again: ";
                cin >> confirmpassword;

                //checks if passwords entered are the same

                if (password != confirmpassword)
                {
                    cout << "Passwords do not match!" << endl;
                }
                else
                {
                    // Insert the data to file
                    fout << id << ","
                        << password << ","
                        << firstName << ", "
                        << lastName << ", "
                        << hpNum << ", "
                        << address
                        << "\n";

                    //inserts record into csv file
                    //customerList.add(id, password, firstName, lastName, hpNum, address);
                    cout << "Account created successfully." << endl;
                }

            } while (password != confirmpassword);
            fout.close();
            break;
        }

        //login to customer account
        case 2:
        {
            fstream fin;
            fin.open("custAccount.csv", ios::in);
            ItemType custid;
            string custpassword;
            bool found = false;

            do {
                cout << "Please enter your username: ";
                cin >> custid;
                cout << "Please enter your password: ";
                cin >> custpassword;

                // Read the Data from the file as String Vector
                vector<vector<string>> content;
                vector<string> row;
                string line, word;

                if (fin.is_open())
                {
                    getline(fin, line);                   //ignore first column - headers 
                    while (getline(fin, line))
                    {
                        row.clear();                      //empty row buffer 
                        stringstream str(line);           //convert each line into a string 
                        while (getline(str, word, ','))   //split line by ','s and append to row buffer 
                            row.push_back(word);
                        content.push_back(row);           //append row to content buffer 
                    }
                }

                // content buffer is a 2d array, where each row is a customer entry 
                for (int i = 0;i < content.size();i++)
                {
                    // index according to the fields 
                    ItemType userid = content[i][0];
                    string pw = content[i][1];
                    string firstName = content[i][2];
                    string lastName = content[i][3];
                    string hpNum = content[i][4];
                    string address = content[i][5];
                    //adds record into customerlist
                    customerList.add(userid, pw, firstName, lastName, hpNum, address);
                }

                //checks if password linked with user id is te same as the password user typed in
                if (customerList.getPassword(custid) == custpassword)
                {
                    break;
                }
                else
                {
                    cout << "Invalid credentials!" << endl;
                }
            } while (true);

            fin.close();

            int y;
            do
            {
                displayUserMenu();
                cout << "Please select an option: ";
                cin >> y;
                switch (y)
                {
                    //searching of food
                case 1:
                {
                    //inputting diff foods into foodtree BST
                    categoriseFood();

                    int option;
                    displaySearchMenu();
                    cout << "What would you like to search? ";
                    cin >> option;
                    switch (option) {
                        //search by cuisine
                    case 1:
                    {
                        int z;
                        cout << "\nWhich category would you like to view? " << endl;
                        cout << "[1] Italian" << endl;
                        cout << "[2] Chinese" << endl;
                        cout << "[3] Japanese" << endl;
                        cout << "[4] Fast Food" << endl;
                        cout << "\nOption: ";
                        cin >> z;

                        // array for category names
                        string categories[] = { "Italian", "Chinese", "Japanese", "Fast Food" };

                        if (z >= 1 && z <= sizeof(categories) / sizeof(categories[0]))
                        {
                            string cat = categories[z - 1];
                            BinaryNode* byCategory = foodTree.searchbycat(cat);

                            if (byCategory != NULL) {
                                cout << "Food items under the '" << cat << "' category:" << endl;
                                foodTree.inorder(byCategory, cat);
                            }
                            else {
                                cout << "No food items found under the '" << cat << "' category." << endl;
                            }
                        }
                        else {
                            cout << "Invalid option." << endl;
                        }

                        break;
                    }

                    //search for restaurant location
                    case 2:
                    {
                        int z;
                        cout << "\nWhich restaurant would you like to view? " << endl;
                        cout << "[1] Restaurant A" << endl;
                        cout << "[2] Restaurant B" << endl;
                        cout << "[3] Restaurant C" << endl;
                        cout << "[4] Restaurant D" << endl;
                        cout << "\nOption: ";
                        cin >> z;

                        // array for restaurant names
                        string location[] = { "Restaurant A", "Restaurant B", "Restaurant C", "Restaurant D" };

                        if (z >= 1 && z <= sizeof(location) / sizeof(location[0]))
                        {
                            string loc = location[z - 1];
                            BinaryNode* byLoc = foodTree.searchbyloc(loc);

                            if (byLoc != NULL) {
                                cout << "Food items under " << loc << ":" << endl;
                                foodTree.inorder(byLoc, loc);
                            }
                            else {
                                cout << "No food items found under " << loc << "." << endl;
                            }
                        }
                        else {
                            cout << "Invalid option." << endl;
                        }
                        break;
                    }

                    //browse all food 
                    case 3:
                    {
                        if (!foodTree.isEmpty())
                        {
                            cout << "--------------------All Food Items-------------------" << endl;
                            foodTree.inorder(); // This will display all food items by alphabetical order.
                        }
                        else
                        {
                            cout << "No food items available." << endl;
                        }
                        break;
                    }
                    default:
                    {
                        cout << "Please choose a valid option." << endl;
                    }

                    }
                    break;
                }

                //create new order
                case 2:
                {
                    string z;
                    //display food options
                    displayFood();

                    do {
                        int x;
                        int y;
                        cout << "Please select your food: ";
                        cin >> x;

                        //checks if input is out of range
                        if (x >= 0 && x <= foodselections.getLength())
                        {
                            cout << "Please select your quantity: ";
                            cin >> y;
                            //adds to orderlist
                            orderList.addOrder((orderList.getlength()) + 1, custid, foodselections.get(x - 1), y, "Pending");
                            cout << "Order is placed!" << endl;

                            //allows customer to continue ordering
                            cout << "Would you still like to place an order [Y|N]? ";
                            cin >> z;
                        }
                        else
                        {
                            cout << "Food option is invalid. Please try again." << endl;
                        }

                    } while (z == "Y" || z == "y");

                    break;
                }

                //cancel order
                case 3:
                {

                    cout << "OrderID      Dish         Quantity        Status" << endl;
                    cout << "----------------------------------------------" << endl;
                    orderList.displayOrderDetails(custid);

                    if (orderList.isEmpty() != true)
                    {
                        int x;
                        cout << "Which option would you like to cancel?: ";
                        cin >> x;

                        //checks if input is out of range
                        if (x >= 0 && x <= orderList.getlength())
                        {
                            //check for order's status
                            if (orderList.getStatus(x) == "Pending")
                            {
                                //cancels order if it's not prepared
                                orderList.removeOrder(x);
                                cout << "Food order " << x << " cancelled successfully." << endl;

                            }
                            else if (orderList.getStatus(x) == "Preparing Order")
                            {
                                cout << "Kitchen is preparing order, no cancellation allowed." << endl;
                            }

                            else if (orderList.getStatus(x) == "Order Completed")
                            {
                                cout << "Food ready for pickup, no cancellation allowed." << endl;
                            }
                        }
                        else
                        {
                            cout << "Order does not exist" << endl;
                        }
                    }
                    else
                    {
                        cout << "No orders to display!" << endl;
                    }
                    break;
                }

                //view order history
                case 4:
                {

                    cout << "OrderID      Dish         Quantity        Status" << endl;
                    cout << "-------------------------------------------------------------" << endl;
                    //checks and only display food order that are from the logged in customer only
                    orderList.displayOrderDetails(custid);

                    break;
                }

                //give rating
                case 5:
                {
                    //access csv file
                    fstream fout;
                    fout.open("rating.csv", ios::out | ios::app);
                    int i;
                    int s;

                    //display orders that are completed
                    orderList.displayCompleted();
                    cout << "Which order would you like to give a rating for? ";
                    cin >> i;
                    cout << "Give a rating out of 5: ";
                    cin >> s;

                    //insert into csv
                    fout << i << ", "
                        << s << ", "
                        << "\n";

                    //add rating
                    //ratingBook.giveRating(foodselections.get(i-1), to_string(s));  
                    cout << "Rating given, thank you!" << endl;

                    //dequeue once rating made, cannot make duplicate ratings for the same order
                    orderList.removeOrder(i);
                    break;
                }


                case 0:
                    cout << "Have a great day, thank you!" << endl;
                    break;

                default:
                    cout << "Invalid option. Please try again." << endl;
                }
            } while (y != 0);
            break;
        }

        //login to admin account
        case 3:
        {
            string id;
            string password;
            do
            {
                //to implement checking of userid
                cout << "\nPlease enter your username: ";
                cin >> id;
                cout << "Please enter your password: ";
                cin >> password;

                //check if password match database password
                if (password != "password" || id != "admin")
                    cout << "Invalid credentials! Please try again." << endl;

            } while (password != "password" || id != "admin");  //loop till password is right

            int y;
            do
            {
                displayAdminMenu();
                cout << "Please select an option: ";
                cin >> y;
                switch (y)
                {
                    // view incoming orders
                case 1:
                {
                    if (orderList.isEmpty() != true)
                    {
                        displayOrderListFormat();
                        for (int i = 0; i < orderList.getlength(); i++)
                        {
                            if (orderList.getStatus(i) == "Pending")
                            {
                                orderList.displayItems(i);
                            }
                        }
                    }
                    else
                    {
                        cout << "No orders to display." << endl;
                        break;
                    }
                    break;
                }

                // update status of orders
                case 2:
                {
                    if (orderList.isEmpty() != true)
                    {
                        displayOrderListFormat();
                        for (int i = 0; i < orderList.getlength(); i++)
                        {
                            /*if (orderList.getStatus(i) != "Order Completed")
                            {
                                orderList.displayItems(i);
                            }*/
                            orderList.displayItems(i);
                        }
                        int i;
                        cout << "\nPlease enter the order number to update: ";
                        cin >> i;
                        if (i > 0 && i <= orderList.getlength())
                        {
                            string newstatus;
                            int ordernum;

                            do
                            {
                                cout << "\nPlease choose the status you would like to update to: " << endl;
                                cout << "[1] Preparing Order \t[2]Order Completed \t[3]Exit" << endl;
                                cout << "\nOption: ";
                                cin >> ordernum;
                                if (ordernum == 1)
                                {
                                    newstatus = "Preparing Order";

                                    orderList.updateStatus(i, newstatus);
                                    cout << "Order status updated successfully." << endl;
                                }
                                else if (ordernum == 2)
                                {
                                    newstatus = "Order Completed";

                                    orderList.updateStatus(i, newstatus);
                                    cout << "Order status updated successfully." << endl;
                                }
                                else if (ordernum == 3)
                                {
                                    cout << "No change to order status." << endl;
                                    break;
                                }
                                else
                                {
                                    cout << "Invalid option. Please choose again." << endl;
                                }

                            } while (ordernum != 1 && ordernum != 2);
                        }
                        else
                        {
                            cout << "Invalid order number." << endl;
                        }
                    }
                    else
                    {
                        cout << "No orders to display." << endl;
                        break;
                    }
                    break;
                }

                // view customer info for an order
                case 3:
                {
                    if (orderList.isEmpty() != true)
                    {
                        displayOrderListFormat();
                        for (int i = 0; i < orderList.getlength(); i++)
                        {
                            orderList.displayItems(i);
                        }

                        int i;
                        cout << "\nEnter an order number which you would like to view customer information on: ";
                        cin >> i;

                        if (i <= orderList.getlength() && i > 0)
                        {
                            i = i - 1;
                            string id = orderList.getID(i);
                            customerList.displayCustDetails(id);
                        }
                        else
                        {
                            cout << "Invalid Order Number." << endl;
                        }
                    }
                    else
                    {
                        cout << "No orders to display." << endl;
                        break;
                    }
                    break;
                }

                //view rating
                case 4:
                {
                    fstream fin;
                    fin.open("rating.csv", ios::in);

                    double total1 = 0;
                    double total2 = 0;
                    double total3 = 0;
                    double total4 = 0;
                    double total5 = 0;
                    double total6 = 0;
                    double total7 = 0;
                    double total8 = 0;
                    double total9 = 0;
                    double total10 = 0;
                    double total11 = 0;

                    double n1 = 0;
                    double n2 = 0;
                    double n3 = 0;
                    double n4 = 0;
                    double n5 = 0;
                    double n6 = 0;
                    double n7 = 0;
                    double n8 = 0;
                    double n9 = 0;
                    double n10 = 0;
                    double n11 = 0;

                    //Read data from the file as string vector
                    vector<vector<string>> content;
                    vector<string>row;
                    string line, word;

                    if (fin.is_open())
                    {
                        getline(fin, line);
                        while (getline(fin, line))
                        {
                            row.clear();
                            stringstream str(line);
                            while (getline(str, word, ','))
                                row.push_back(word);
                            content.push_back(row);
                        }
                    }
                    cout << "Food                    Rating" << endl;
                    cout << "--------------------------------" << endl;
                    for (int i = 0; i < content.size();i++)
                    {
                        string item = content[i][0];
                        string r = content[i][1];

                        //add csv records into dictionary
                        ratingBook.giveRating(foodselections.get(stoi(item)), r);
                        if (item == "1")
                        {
                            n1 += 1;
                            total1 += (stoi(r));
                        }
                        else if (item == "2")
                        {
                            n2 += 1;
                            total2 += (stoi(r));
                        }
                        else if (item == "3")
                        {
                            n3 += 1;
                            total3 += (stoi(r));
                        }
                        else if (item == "4")
                        {
                            n4 += 1;
                            total4 += (stoi(r));
                        }
                        else if (item == "5")
                        {
                            n5 += 1;
                            total5 += (stoi(r));
                        }
                        else if (item == "6")
                        {
                            n6 += 1;
                            total6 += (stoi(r));
                        }
                        else if (item == "7")
                        {
                            n7 += 1;
                            total7 += (stoi(r));
                        }
                        else if (item == "8")
                        {
                            n8 += 1;
                            total8 += (stoi(r));
                        }
                        else if (item == "9")
                        {
                            n9 += 1;
                            total4 += (stoi(r));
                        }
                        else if (item == "10")
                        {
                            n10 += 1;
                            total10 += (stoi(r));
                        }
                        else
                        {
                            n11 += 1;
                            total11 += (stoi(r));
                        }

                    }
                    double avg1 = total1 / n1;
                    double avg2 = total2 / n2;
                    double avg3 = total3 / n3;
                    double avg4 = total4 / n4;
                    double avg5 = total5 / n5;
                    double avg6 = total6 / n6;
                    double avg7 = total7 / n7;
                    double avg8 = total8 / n8;
                    double avg9 = total9 / n9;
                    double avg10 = total10 / n10;
                    double avg11 = total11 / n11;

                    cout << foodselections.get(0) << setw(15) << avg1 << endl;
                    cout << foodselections.get(1) << setw(15) << avg2 << endl;
                    cout << foodselections.get(2) << setw(15) << avg3 << endl;
                    cout << foodselections.get(3) << setw(15) << avg4 << endl;
                    cout << foodselections.get(4) << setw(15) << avg5 << endl;
                    cout << foodselections.get(5) << setw(15) << avg6 << endl;
                    cout << foodselections.get(6) << setw(15) << avg7 << endl;
                    cout << foodselections.get(7) << setw(15) << avg8 << endl;
                    cout << foodselections.get(8) << setw(15) << avg9 << endl;
                    cout << foodselections.get(9) << setw(15) << avg10 << endl;
                    cout << foodselections.get(10) << setw(15) << avg11 << endl;

                    break;
                }

                case 0:
                {
                    cout << "Have a great day, thank you!" << endl;
                    break;
                }
                default:
                {
                    cout << "Please choose a valid option!" << endl;
                    break;
                }

                }
            } while (y != 0);
            break;
        }


        // admin log out
        case 0:
        {
            cout << "Have a great day, thank you!" << endl;
            break;
        }

        // invalid option chosen
        default:
        {
            cout << "Please choose a valid option!" << endl;
            break;
        }
        break;
        }
    } while (x != 0);
}


//functions
void displayLogin()
{
    cout << "\n------------- Main Menu -------------" << endl;
    cout << "[1] Register a customer account" << endl;
    cout << "[2] Login to customer account" << endl;
    cout << "[3] Login to admin account" << endl;
    cout << "[0] Exit" << endl;
    cout << "-------------------------------------" << endl;

}
void displayUserMenu()
{
    cout << "\n------------ Customer Menu -------------" << endl;
    cout << "[1] Browse all food selections offered" << endl;
    cout << "[2] Create new order" << endl;
    cout << "[3] Cancel order" << endl;
    cout << "[4] View order history" << endl;
    cout << "[5] Give rating" << endl;
    cout << "[0] Exit" << endl;
    cout << "---------------------------------------" << endl;
}
void displayAdminMenu()
{
    cout << "\n------------ Admin Menu -------------" << endl;
    cout << "[1] View incoming orders" << endl;
    cout << "[2] Update status of orders" << endl;
    cout << "[3] View customer information" << endl;
    cout << "[4] View rating" << endl;
    cout << "[0] Exit" << endl;
    cout << "-------------------------------------" << endl;

}

void displaySearchMenu()
{
    cout << "\n[1] Search cuisine" << endl;
    cout << "[2] Search location" << endl;
    cout << "[3] Display all food" << endl;
}

void insertFood()
{
    foodselections.add("Burger");
    foodselections.add("Cheese Fries");
    foodselections.add("Chicken Wing");
    foodselections.add("Spaghetti");
    foodselections.add("Pizza");
    foodselections.add("Sushi");
    foodselections.add("Ramen");
    foodselections.add("Takoyaki");
    foodselections.add("Mala");
    foodselections.add("Chicken Rice");
    foodselections.add("Yong Tau Foo");
}

void displayFood()
{
    foodselections.print();
}


void categoriseFood()
{
    // Insert food items into the BST
    foodTree.insert("Burger", "Restaurant A", "Fast Food");
    foodTree.insert("Cheese Fries", "Restaurant A", "Fast Food");
    foodTree.insert("Chicken Wings", "Restaurant A", "Fast Food");
    foodTree.insert("Spaghetti", "Restaurant B", "Italian");
    foodTree.insert("Pizza", "Restaurant B", "Italian");
    foodTree.insert("Sushi", "Restaurant C", "Japanese");
    foodTree.insert("Ramen", "Restaurant C", "Japanese");
    foodTree.insert("Takoyaki", "Restaurant C", "Japanese");
    foodTree.insert("Mala", "Restaurant D", "Chinese");
    foodTree.insert("Chicken Rice", "Restaurant D", "Chinese");
    foodTree.insert("Yong Tau Foo", "Restaurant D", "Chinese");
}

void displayOrderListFormat()
{
    cout << "\n-------------------------------------------------------------------------------------------------" << endl;
    cout << setw(15) << "Order Number" << setw(20) << "Customer Username";
    cout << setw(20) << "Dish" << setw(15) << "Quantity" << setw(20) << "Status" << endl;
    cout << "-------------------------------------------------------------------------------------------------" << endl;

}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
