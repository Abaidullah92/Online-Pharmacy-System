///////////////////////////////////////////////////PROJECT//////////////////////////////////////////////////////////////////////////
// Project Name: Online Pharmacy System



#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
#include<sstream>
using namespace std;
int totalitems = 0;
const int MAX = 50;
string names[MAX];
string formula[MAX];
float price[MAX];
string dosage[MAX];
string mfgDate[MAX];
string expDate[MAX];
int quantity[MAX];
const int Cartsize = 10;
string cart_name[Cartsize];
string cart_dosage[Cartsize];
int cart_qty[Cartsize];
float cart_price[Cartsize];
const int MAX_CUSTOMERS = 30;
int totalOrders[MAX_CUSTOMERS] = { 0 };

void ReadSystemItems() {
	ifstream file;
	file.open("d:\\Pharmacy.txt");
	if (file.is_open()) {
		string line;
		while (getline(file, line)) {
				stringstream ss(line);
				file >> names[totalitems] >> formula[totalitems] >> dosage[totalitems] >> mfgDate[totalitems] >> expDate[totalitems] >> quantity[totalitems] >> price[totalitems];
				totalitems++;

			
		}
		file.close();
	}
}

// Step 1: To Print Pharmacy items
void PrintPharmacyItems() {
	for (int i = 1; i < totalitems; i++) {
		cout << names[i] << "     " << formula[i] << "\t\t" << dosage[i] << "\t\t" <<mfgDate[i] << "\t" << expDate[i] << "\t" << quantity[i] << "\t\t" << price[i] << endl;

	}
	totalitems++;
}


// Step 2: To Search pharamacy Items in the Repository
void SearchItems() {
	string name;
	int a = 0;
	cout << "Enter the name of Mdicine." << endl;
	cout<<'\n';
	cin >> name;
	for (int i = 1; i < totalitems; i++) {
		if (names[i] == name) {
			cout << "\n";
			cout << name << " PRICE is: " << price[i] << " || FORMULA is: " << formula[i] << " || DOSAGE is: " << dosage[i] << " || MFG DATE is: " << mfgDate[i] << "  || EXP DATE is : " << expDate[i] << endl;
			cout << "\n";
			cout << "|| AVALABLE QUANTITY is: " << quantity[i];
			a++;
			break;
		}
	}
	if (a == 0) {
		cout << "The Name of this Medicine is not found." << endl;
	}
}


// Step 3: To Insert an item add to the cart
void addtocart(string name,int qty) {
	for (int i = 0; i < Cartsize; i++) {
		if (cart_name[i] == name) {
			cout << "Medicine is already in the cart." << endl;
			return;
		}
	}
	for (int i = 0; i < totalitems; i++) {
		if (name == names[i]) {
			for (int j = 0; j < Cartsize; j++) {
				if (cart_name[j]=="") {
					cart_name[j] = names[i];
					cart_dosage[j] = dosage[i];
					cart_qty[j] = qty;
					cart_price[j] = price[i];
					cout << "Medicine add to the cart." << endl;
					 // Update the total number of orders
					totalOrders[0] += qty;
					return;
				}
			}
			cout << "Cart is full. Cannot add more than";
			return;
		}
	}
	cout << "invalid Medicine name.Item not add to the cart" << endl;
}


// Step 4: To Delete Items
void deletefromcart(string name) {
	for (int i = 0; i < Cartsize; i++) {
		if (cart_name[i] == name) {
			cart_name[i] = "";  
			cart_qty[i] = 0;   
			cart_dosage[i] = "";
			cart_price[i] = 0.0; 
			cout << "Item removed from cart." << endl;
			return;
		}
	}
	cout << "Medicine name not found in the cart." << endl;
}

// Step 5: to Update Quantity
void updatequantity(string name, int qty) {
	for (int i = 0; i < Cartsize; i++) {
		if (cart_name[i] == name) {
			cart_qty[i] += qty;
			cout << endl;
			return;
		}
	}

	for (int i = 0; i < totalitems; i++) {
		if (name == names[i]) {
			for (int j = 0; j < Cartsize; j++) {
				if (cart_name[j] == "") {
					
					cart_name[j] = names[i];
					cart_qty[j] = qty;
					cart_price[j] = price[i];
					return;
				}
			}
			cout << "Cart is full. Cannot add more items." << endl;
			return;
		}
	}

	
	cout << "Invalid Medicine name. Item not added to the cart" << endl;
}

// Step 6: To display  the Cart
void displayCart() {
	cout << "Cart Items" << endl;
	cout << "\n";
	cout << "\nNAME\t\tDOSAGE\t\tQUANTITY\tPRICE" << endl;
	cout << "\n";
	for (int i = 0; i < Cartsize; i++) {
		if (cart_name[i] != "") {
			cout << cart_name[i] << "\t\t"<<cart_dosage[i]<<"\t\t" << cart_qty[i] << "\t\t" << cart_price[i] << endl;
		}
	}
}

// Step 7 : To get user Detailes
string name;
string address;
string contactNo;
void userDetails() {
	cout << "Enter the Name of Customer" << endl;
	cin >> name;
	cout << "Enter the Address od Customer" << endl;
	cin >> address;
	cout << "Enter the Contact Number of Customer" << endl;
	cin >> contactNo;
	cout << "\n";
	cout << "Coustomer Details Successfully Added" << endl;
}

// Step 8: to generated the bill
void generateBill() {
	double totalCost;
	double tax;
	double total = 0.0;
	float deliveryCharges = 250; // Deilvery Charges fixed
	double discount;
	ofstream outFile("d:\\Bill.txt");

	if (!outFile.is_open()) {
		cout << "Error: Unable to open the output file." << endl;
		return;
	}
	else {
		cout << "Bill Generated Successfully" << endl;
	}
	// write the user details
	outFile << "Customer Name: " << setw(10) << name << endl;
	outFile << "Customer Address: " << setw(10) << address << endl;
	outFile << "Customer Contact Number: " << setw(10) << contactNo << endl;
	outFile << "\n";
	outFile << "--------------------------------------------------|Bill|-------------------------------------------------------" << endl;
	outFile << setw(20) << "Medicine Name" << setw(15) << "Dosage" << setw(15) << "Quantity" << setw(15) << "Price" << setw(15) << "Total" << endl;
	outFile << "---------------------------------------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < Cartsize; i++) {
		if (cart_name[i] != "") {
			double itemTotal = cart_qty[i] * cart_price[i];
			total = total + itemTotal;
			tax = total * 0.12; // 12% Tax rate
			totalCost = total + tax + deliveryCharges;
			outFile << setw(20) << cart_name[i] << setw(19) << cart_dosage[i] << setw(18) << cart_qty[i] << setw(18) << cart_price[i] << setw(19) << itemTotal << endl;
		}
	}
	cout << "-------------------------------------------------------------------------------------------------------------------" << endl;
	outFile << "\n";
	// Bonus Task:-
	//a. Offer a discount of 20% to loyal customers
	if (totalOrders[0] > 5) {
		double discount = total * 0.20;  // 20% discount
		totalCost -= discount;
		outFile << setw(60) << "Bulk Order Discount (20%): " << discount << endl;
	}
	// b. If the order exceeds 10000PKR, waive off delivery charges
	if (totalCost > 10000) {
		totalCost -= deliveryCharges;
		outFile << setw(60) << "Delivery Charges (Waived off for orders > 10000PKR)" << endl;
	}
	cout << "\n";
	outFile << "---------------------------------------------------------------------------------------------------------------" << endl;
	outFile << setw(60) << "Sub total : " << total << endl;
	outFile << setw(60) << "Tax(12%) :  " << tax << endl;
	outFile << setw(60) << "Delivery Charges : " << deliveryCharges << endl;
	outFile << setw(60) << "Total Cost : " << totalCost << endl;
	outFile << "---------------------------------------------------------------------------------------------------------------" << endl;

	// Close the file
	outFile.close();
}



int main() {
	string name;
	int qty;
	ReadSystemItems();
	cout << "----------------------------------------------------------------------------------" << endl;
	cout << "**********************************************************************************" << endl;
	cout << "***************|               APEX ONLINE PHARMACY                |**************" << endl;
	cout << "**********************************************************************************" << endl;
	cout << "----------------------------------------------------------------------------------" << endl;
	cout << "\n\tMENU";
	int MENU;
	for (MENU = 0; MENU < 10; MENU++) {
		cout << "\n\t**************************************" << endl;
		cout << "\n\t** 1.Print Pharmacy items           **" << endl;
		cout << "\n\t** 2.Search Pharamcy Items.         **" << endl;
		cout << "\n\t** 3.Insert  an Items to Cart.      **" << endl;
		cout << "\n\t** 4.Deleted Items from the Cart.   **" << endl;
		cout << "\n\t** 5.Update Quantity Items.         **" << endl;
		cout << "\n\t** 6.Display The shoping Cart       **" << endl;
		cout << "\n\t** 7.Get users Details              **" << endl;
		cout << "\n\t** 8.Bill Genetrated                **" << endl;
		cout << "\n\t**************************************" << endl;
		cout << "\n	     << Chose Options >>	" << endl;
		cin >> MENU;
		cout << "------------------------------------------------------" << endl;
		cout << endl;
		if (MENU) {
			if (MENU == 1) {
				PrintPharmacyItems();
			}
			else if (MENU == 2) {
				SearchItems();
			}
			else if (MENU == 3) {
				cout << "Enter the name of Medicine.add to the cart" << endl;
				cin >> name;
				cout << "Enter the quantity of medicine" << endl;
				cin >> qty;
				addtocart(name, qty);

			}
			else if (MENU == 4) {

				cout << "Enter the name of Medicne From Cart." << endl;
				cin >> name;
				deletefromcart(name);
			}
			else if (MENU == 5) {
				cout << "Enter the Name of medicine from cart" << endl;
				cin >> name;
				cout << "Enter the Quantity to Update the item Quantity." << endl;
				cin >> qty;
				cout << "\n";
				cout << " Medicine quantity is Updated Successfully to :  " << qty << endl;
				updatequantity(name, 3);
				//updatequantity(name, -1);
				//for (int i = 0; i < totalitems; i++) {
					//cout << names[i] << "\t\t" << quantity[i] << endl;
				//}
			}
			else if (MENU == 6) {
				displayCart();
			}
			else if (MENU == 7) {
				userDetails();
			}
			else if (MENU == 8) {
				generateBill();
				break;
			}
		}

	}
	system("Pause");
	return 0;
}
