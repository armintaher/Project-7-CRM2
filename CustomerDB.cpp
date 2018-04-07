/*
 * Name:
 * EID:
 * Project 7, CRM part 2
 * EE 312, Spring 2017
 */
#include <iostream>
#include <cassert>
#include "String.h"
#include "CustomerDB.h"

using namespace std;

const int default_capacity = 1;

Customer::Customer(String name) { // done, please do not edit
	this->bottles = 0;
	this->rattles = 0;
	this->diapers = 0;
	this->name = name;
}

CustomerDB::CustomerDB(void) { // done, please do not edit
	this->capacity = default_capacity;
	this->data = new Customer[this->capacity];
	this->length = 0;
}

int CustomerDB::size(void) {
	return this->length;
}

CustomerDB::~CustomerDB(void) { // done, please do not edit
	delete[] this->data;
}

void CustomerDB::clear(void) { // done, please do not edit
	delete[] this->data;
	this->capacity = default_capacity;
	this->data = new Customer[this->capacity];
	this->length = 0;
}

Customer& CustomerDB::operator[](int k) { // done, please do not edit
	assert(k >= 0 && k < this->length);
	return this->data[k];
}

Customer& CustomerDB::operator[](String name) {
	for (int i =0; i< size(); i++) {
		if (name == this->data[i].name) {
			return this->data[i];
		}
	}
	if (this->capacity == size()) {
		this->capacity *= 2;
		Customer *New_Data = new Customer[this->capacity];
		for (int i = 0; i < size(); i++) {
			New_Data[i] = this->data[i];
		}
		this->~CustomerDB();
		this->data = New_Data;
	}
	Customer Customer1 = Customer(name);
	this->data[this->length] = Customer1;
	return ((this->data[(this->length)++]));

}



bool CustomerDB::isMember(String name) { // not done, your effort goes here
	int i =0;
	for (; i< size(); i++){
		if (name == this->data[i].name){
			return true;
		}
	}
	return false;
}


