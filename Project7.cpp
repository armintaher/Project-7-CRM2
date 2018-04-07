/*
 * Name:
 * EID:
 * Project 7, CRM part 2
 * EE 312, Spring 2017
 */

#include <stdio.h>
#include <iostream>
#include "String.h"
#include "Customer.h"
#include "CustomerDB.h"

using namespace std;

void readString(String&);
void readNum(int&);

CustomerDB database;

int num_bottles = 0;
int num_rattles = 0;
int num_diapers = 0;


/* clear the inventory and reset the customer database to empty */
void reset(void) {
	database.clear();
	num_bottles = 0;
	num_rattles = 0;
	num_diapers = 0;
}

/*
 * selectInventItem is a convenience function that allows you
 * to obtain a pointer to the inventory record using the item type name
 * word must be "Bottles", "Diapers" or "Rattles"
 * for example the expression *selectInventItem("Bottles") returns the
 * current global variable for the number of bottls in the inventory
 */
int* selectInventItem(String word) {
	if (word == "Bottles") {
		return &num_bottles;
	} else if (word == "Diapers") {
		return &num_diapers;
	} else if (word == "Rattles") {
		return &num_rattles;
	}

	/* NOT REACHED */
	return 0;
}

/*
 * this overload of selectInventItem is similar to selectInventItem above, however
 * this overload takes a Customer as a second argument and selects the data member
 * of that Customer that matches "word". The function returns a pointer to one of the three data
 * members from the specified customer.
 */
int* selectInventItem(String word, Customer& cust) {
	if (word == "Bottles") {
		return &cust.bottles;
	} else if (word == "Diapers") {
		return &cust.diapers;
	} else if (word == "Rattles") {
		return &cust.rattles;
	}

	/* NOT REACHED */
	return 0;
}


/*
 * findMax searches through the CustomerDB "database" and returns the Customer
 * who has purchased the most items of the specified type.
 * type must be one of "Bottles", "Rattles" or "Diapers".
 *
 * Note: if two or more Customers are tied for having purchased the most of that item type
 * then findMax returns the first Customer in the CustomerDB who has purchased that maximal
 * quantity.
 *
 * Note: in the special case (invalid case) where there are zero Customers in the
 * CustomerDB, fundMax returns a null pointer (0)
 */
Customer* findMax(String type) {
	Customer* result = 0;
	int max = 0;
	for (int k = 0; k < database.size(); k += 1) {
		Customer& cust = database[k];
		int *p = selectInventItem(type, cust);
		if (*p > max) {
			max = *p;
			result = &cust;
		}
	}

	return result;
}

void processPurchase() {
    String Customer_Name;
    String Item;
    int Item_Quantity =0;
    readString(Customer_Name);
    readString(Item);
    readNum(Item_Quantity);

    if (Item_Quantity != 0){
        if (Item_Quantity <= *(selectInventItem(Item))){
            Customer Customer1 = database.operator[](Customer_Name);
            *(selectInventItem(Item, Customer1)) += Item_Quantity;
            *(selectInventItem(Item)) -= Item_Quantity;
            database.operator[](Customer_Name) = Customer1;
        } else{
            cout << "Sorry" << Customer_Name.c_str() << ", we only have " << *(selectInventItem(Item)) << " " << Item.c_str() << endl;
        }

    }
}

void processSummarize() {
    String Bottles = "Bottles";
    String Diapers = "Diapers";
    String Rattles = "Rattles";
    cout << "There are " << num_bottles << " Bottles, " << num_diapers << " Diapers and " << num_rattles << " Rattles in inventory" << endl;
    cout << "we have had a total of " << database.size() << " different customers" << endl;

    if (findMax(Bottles) == nullptr) {
        cout << "no one has purchased any Bottles" << endl;
    }
    else {
        cout << findMax(Bottles)->name.c_str();
        cout << " has purchased the most Bottles " << "(" << findMax(Bottles)->bottles << ")" << endl;
        }
    if (findMax(Diapers) == nullptr) {
        cout << "no one has purchased any Diapers" << endl;
    }
    else {
        cout << findMax(Diapers)->name.c_str();
        cout << " has purchased the most Diapers " << "(" << findMax(Diapers)->diapers << ")" << endl;
    }
    if (findMax(Rattles) == nullptr) {
        cout << "no one has purchased any Rattles" << endl;
    }
    else {
        cout << findMax(Rattles)->name.c_str();
        cout << " has purchased the most Rattles " << "(" << findMax(Rattles)->rattles << ")" << endl;
    }

}

void processInventory() {
    String Item;    //make string type value for item's name
    int Item_Quantity =0;
    readString(Item);
    readNum(Item_Quantity);

    int* _Item = selectInventItem(Item);
    if (Item_Quantity >= 0){
        *_Item += Item_Quantity;
    }


}