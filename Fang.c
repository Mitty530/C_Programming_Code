#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <string.h>
#include <stdlib.h>

void Admin();
void Staff();
void Customer();
void create();
void modify();
void delt();
void print(int);
int read();
void write();
void _scanf(char*, int);
int search();

struct CustomerStruct {
	int id;
	char name_f[50];
	char name_l[50];
	char billing_addr[100];
	char mob_no[20];
	float amountPaid;
	float amountDue;
	int paymentDate_m;
	int paymentDate_d;
	int paymentDate_y;
} customer;

struct CustomerStruct customers[100];
int totalCustomers;

int main()
{
	int choice;
	totalCustomers = read();

	while (1)
	{
		printf("1: Admin\n");
		printf("2: Staff\n");
		printf("3: Customer\n");
		printf("4: Exit\n");
		printf("Do you want to access as Admin or Staff or as a Customer: ");
		scanf_s("%d", &choice);

		if (choice == 1)
			Admin();
		else if (choice == 2)
			Staff();
		else if (choice == 3)
			Customer();
		else
			break;
	}

	return 0;
}

void Admin()
{
	int admin_activities;
	int id;
	char adminID[20];
	char password[10];

	printf("Enter username: ");
	scanf_s("%s", adminID, 20);

	printf("Enter password: ");
	scanf_s("%s", password, 10);

	if (strcmp(adminID, "Admin") == 0 && strcmp(password, "pass") == 0) {
		printf("Access granted\n\nChoose one of the options below:\n\n");
		printf("1. Create new customer profile\n2. Modify existing customer's record\n3. Delete customer's profile\n4. Search customers profile\n\nChoice number: ");
		scanf_s("%d", &admin_activities);

		switch (admin_activities) {
		case 1:
			create();
			break;
		case 2:
			modify();
			break;
		case 3:
			Delete();
			break;
		case 4:
			id = search();
			print(id);
			break;
		default:
			printf("invalid input");
			break;
		}
	}
	else printf("(Access denied)\n");

	_getch();
	printf("\n\n");
}

void Staff() {
	int staff_activities;
	char staff[20];
	char password[10];

	printf("Enter username: ");
	scanf_s("%s", staff, 20);
	printf("Enter password: ");
	scanf_s("%s", password, 10);

	if (strcmp(staff, "Staff") == 0 && strcmp(password, "pass") == 0) {
		printf("Access granted\n");
		printf("Welcome To MoonBucks Billing System %s\n\nChoose one of the options below:\n\n", staff);
		printf("1. Create new customer profile\n2. Search customer's profile\n\nChoice number: ");
		scanf_s("%d", &staff_activities);
		switch (staff_activities) {
		case 1:
			create();
			break;
		case 2:
			search();
			break;
		default:
			printf("Invalid input");
			break;
		}
	}
	else {
		printf("Wrong password\n\n");
	}
}

void Customer() {
	int id = search();

	if (id == totalCustomers)
	{
		printf("This customer does not exist.\n");
		return;
	}

	printf("-------------Welcome to our Moon Bucks Billing System--------------\n");
	printf("Following is your information:\n");
	print(id);
}

void create()
{
	struct CustomerStruct _new;
	char input[50];

	_new.id = totalCustomers;
	printf("First Name: ");
	scanf_s("%s", _new.name_f, 50);
	printf("Last Name: ");
	scanf_s("%s", _new.name_l, 50);
	printf("Billing address: ");
	_scanf(_new.billing_addr, 100);
	printf("Mobile number: ");
	scanf_s("%s", _new.mob_no, 20);
	printf("Amount paid: ");
	scanf_s("%f", &_new.amountPaid);
	printf("Amount due: ");
	scanf_s("%f", &_new.amountDue);
	printf("Month of due date: ");
	scanf_s("%d", &_new.paymentDate_m);
	printf("Day of due date: ");
	scanf_s("%d", &_new.paymentDate_d);
	printf("Year of due date: ");
	scanf_s("%d", &_new.paymentDate_y);

	customers[totalCustomers++] = _new;

	printf("New Customer added with Customer number: %d\n", _new.id);
	write();
}

void modify()
{
	int id = search();
	char input[50];

	print(id);
	printf("\nEnter the new data or leave empty:\n");

	printf("Enter first name: ");
	scanf_s("%s", input, 50);
	if (strlen(input) > 1)
		strcpy_s(customers[id].name_f, sizeof(customers[id].name_f), input);

	printf("Enter last name: ");
	scanf_s("%s", input, 50);
	if (strlen(input) > 1)
		strcpy_s(customers[id].name_l, sizeof(customers[id].name_l), input);

	printf("Enter Billing address: ");
	_scanf(input, 50);
	if (strlen(input) > 1)
		strcpy_s(customers[id].billing_addr, sizeof(customers[id].billing_addr), input);

	printf("Enter mobile number: ");
	scanf_s("%s", input, 20);
	if (strlen(input) > 1)
		strcpy_s(customers[id].mob_no, sizeof(customers[id].mob_no), input);

	printf("Enter Amount paid: ");
	_scanf(input, 50);
	if (strlen(input) > 1)
		customers[id].amountPaid = atof(input);

	printf("Enter Amount due: ");
	_scanf(input, 50);
	if (strlen(input) > 1)
		customers[id].amountDue = atof(input);

	printf("Enter month of due date: ");
	_scanf(input, 50);
	if (strlen(input) > 1)
		customers[id].paymentDate_m = atoi(input);

	printf("Enter day of due date: ");
	_scanf(input, 50);
	if (strlen(input) > 1)
		customers[id].paymentDate_d = atoi(input);

	printf("Enter year of due date: ");
	_scanf(input, 50);
	if (strlen(input) > 1)
		customers[id].paymentDate_y = atoi(input);

	printf("\nAfter modifying record:");
	write();
	print(id);
}

void delt()
{
	int i, id = search();
	for (i = id; i < totalCustomers; i++)
		customers[i] = customers[i + 1];
	totalCustomers--;

	write();
}

int search()
{
	int i, id;
	char input[5];

	printf("\nEnter customer ID: ");
	scanf_s("%s", input, 5);
	id = atoi(input);

	for (i = 0; i < totalCustomers; i++)
	{
		if (customers[i].id == id)
			break;
	}

	return i;
}

void print(int i)
{
	if (i < 0 || i >= totalCustomers)
	{
		printf("User not found!");
		return;
	}

	printf("\nID: %d\n", customers[i].id);
	printf("Name: %s %s\n", customers[i].name_f, customers[i].name_l);
	printf("Billing Address: %s\n", customers[i].billing_addr);
	printf("Mobile Number: %s\n", customers[i].mob_no);
	printf("Amount paid: %.2f\n", customers[i].amountPaid);
	printf("Amount due: %.2f\n", customers[i].amountDue);
	printf("Payment date: %d/%d/%d\n", customers[i].paymentDate_m, customers[i].paymentDate_d, customers[i].paymentDate_y);
}

int read()
{
	int i, size, c_size;
	FILE *fp;

	fopen_s(&fp, "db.dat", "rb"); // open in reading mode as byte data

	if (!fp) // File not present
	{
		fopen_s(&fp, "db.dat", "a");
		fclose(fp);
		fopen_s(&fp, "db.dat", "rb");
	}

	fseek(fp, 0, SEEK_END); // go to end of file
	size = ftell(fp);
	c_size = sizeof(customer);

	i = 0;
	fseek(fp, 0, SEEK_SET); // go to start of file
	while (fread(&customers[i++], sizeof(customer), 1, fp));
	fclose(fp);

	return (int)size / c_size;
}

void write()
{
	FILE *fp;
	int i;
	fopen_s(&fp, "db.dat", "wb");  // open in writing mode as byte data
	for (i = 0; i < totalCustomers; i++)
		fwrite(&customers[i], sizeof(customer), 1, fp);
	fclose(fp);
}

void _scanf(char *input, int size) // To get user input with spaces
{
	scanf_s(" %[^\n]s", input, size);
}