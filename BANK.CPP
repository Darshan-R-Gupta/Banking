/*____________________________________________________________________*/
/*		        Welcome to Avion Bank!                	      */
/*		  -----------------------------------		      */
/*                   USER SECURITY IS OUR DIGNITY                     */
/* We are thankful to our subscribers who made us reach to a position */
/* we never expected we would. Thanks to our developers that now we   */
/* can maintain your precious information securely in a user-friendly */
/* software. 	                                                      */
/* We provide the following feautres:                          	      */
/* 	1. Provides facility to change password 		      */
/*	2. Has facility to reset password if you forgot		      */
/*	3. Has user-friendly interface				      */
/*	4. We also provide Loans to not let your pocket run out of    */
/*         money!                                                     */
/*	5. Unlike other banks, you can start account with 0 balance   */
/* We promise your security while you are having a user-friendly      */
/*   experience with our software. 				      */
/* We even provide special offers to our existing users so that you   */
/* never feel ignored				                      */
/* Still don't like us? You can unsubscribe us anytime you want and   */
/* we won't make any excuses.                                         */
/*                                                                    */
/*                                                                    */
/*					Created and Maintained by:    */
/*						Darshan R Gupta       */
/*						C.E.O.                */
/*						Avion Bank 	      */
/*						7046393537            */
/*____________________________________________________________________*/
#include <iostream.h>
#include <math.h>
#include <ctype.h>
#include <conio.h>
#include <fstream.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <iomanip.h>
const int max_users = 50;
const int low_lim = 1000 ;
void update();//to update files;
void disp_home(); //To display home page;
void gen_format(char *nm);  //to convert strings into standard formats
char * gen_format(double d); //to convert money into standard formats
int show_dec(double a); //to show decimal places of standard formatted money
void disp_money(float amount); //to show money in standard formats
class user{
private:
	 float balance;
	 char pass[20];
	 int acc_no;
public:
	char gender;
	char aadhar[13];
	char name[50];
	void add_bal(float no){
		 balance += no;
	}
	int remove_bal(float no){
		if(no <= balance){   balance -= no;   return 1;   }
		else        	     return 0;

	}
	int get_acc_no(){
		return acc_no;
	}
	double get_bal(){
		return balance;
	}
	char * get_pass(){
		return pass;
	}
	int check_pass(char password[20]){
		 if(strcmp(pass,password) == 0){
			return 1;
		 }
		 else{
			return 0;
		 }
	}
	int change_password(char old[20], char new_pass[20]){
		if(strcmp(old,pass) == 0){
			strcpy(pass,new_pass);
			return 1;
		}
		else{
			return 0;
		};
	}
	user(){
		strcpy(name, "N/A");
		strcpy(pass, "N/A");
		strcpy(aadhar, "N/A");
		gender = 'N';
		acc_no = 0;
		balance = 0;
	}
	user(  int account_no,char nm[50],char gen,char aad_no[13],
	       char password[20], float bal = 0  )
	{
		strcpy(name, nm);
		strcpy(pass, password);
		strcpy(aadhar, aad_no);
		gender = gen;
		balance = bal;
		acc_no = account_no;
	}
};
void disp_user(user *u); //To display functions related to a particular user
class Bank{
public:
	user u[max_users];
	static int accounts;
	static void change_no_of_acc(int dx){
		accounts+= dx;
	}
	static int get_no_of_acc(){
		return accounts;
	}
	Bank();
	void login();
	void signin();
	void deposit(int dep_acc);
	void withdraw(int acc_no);
	void change_pass(int acc);
	void change_creden(int acc);
	void forgot_pass(char c);
	void review_acc(int acc);
	void remove_acc();
};
int Bank::accounts;
Bank b1;
void ini_acc(){
	fstream e;
	e.open("Avion\\Accounts.txt", ios::in);
	e>>Bank::accounts;
}
void main(){
	clrscr();
	ini_acc();
	disp_home();
	update();
}
void Bank::signin()
{
	char nm[50],pass[20];
	double balance;
	int acc_no;
	char gen;
	char aad_no[13];
	clrscr();
	cout<<"SIGN-IN"<<endl;
	cout<<"Enter your name: ";
	gets(nm);
	gen_format(nm); //for generalized format
	cout<<"Gender (M/F): ";
	gen:
	cin>>gen;
	gen = toupper(gen);
	if(gen != 'M' && gen != 'F')
	{
		 cout<<"Invalid Gender. Enter M/F: ";
		 goto gen;
	}
	cout<<"Enter your Aadhar card no.: ";
	aad:
	cin>>aad_no;
	for(int o = 0; o < 12; o++){
		if(aad_no[o] < '0' || aad_no[o] > '9' ){
			cout<<"Invalid Aadhar card no. Please type again: ";
			goto aad;
		}
	}
	//check if it already exists
	for(int j= 0; j < max_users; j++){
		 if(strcmp(aad_no,u[j].aadhar) == 0){
			cout<<"Account already exists!"<<endl;
			cout<<"Account no.: "<<u[j].get_acc_no()<<endl;
			cout<<"Name: ";
			puts(u[j].name);
			cout<<"Aadhar No.: ";
			cout<<u[j].aadhar;
			getch();
			disp_home();
			break;
		 }
	}
	cout<<"Enter your password: ";
	gets(pass);
	cout<<"Enter balance: ";
	cin>>balance;
	int i = 0;
	//create the account
	for(i =0; i < max_users; i++){
		 if(u[i].get_acc_no() == 0){
			 break;
		 }
	}
	u[i].user::user( (i+low_lim+1),nm,gen,aad_no,pass,balance);
	cout<<"Account successfully created!"<<endl;
	cout<<"Account no: "<<u[i].get_acc_no();
	cout<<"\nName: ";
	puts(u[i].name);
	cout<<"Gender: "<<u[i].gender<<endl;
	cout<<"Aadhar no.: "<<u[i].aadhar<<endl;
	cout<<"Current Balance: ";
	disp_money(u[i].get_bal());
	change_no_of_acc(+1);
	getch();
	disp_user(&u[i]);
}
void Bank::login(){
	char nm[50];
	int acc;
	char password[20];
	clrscr();
	cout<<"LOGIN: "<<endl;
	cout<<"Enter Account no: ";
	cin>>acc;
	cout<<"Enter your name: ";
	gets(nm);
	gen_format(nm); //for generalized format
	cout<<"Enter your password: ";
	cin>>password;
	int i =0;
	int matched = 0;
	for(i = 0; i < max_users; i++){
		 if( (acc == u[i].get_acc_no()) )
		 {
			if(strcmp(nm, u[i].name) == 0){
				if(u[i].check_pass(password) ==1){
				     matched = 1;
				     disp_user(&u[i]);
				 }
				 else{
					cout<<"Invalid Password! "<<endl;
					cout<<"Forgot? ";
					char choice;
					cin>>choice;
					matched = 1;
					if(choice == 'y' || choice == 'Y'){
						b1.forgot_pass('L');
					}
					else{
						disp_home();
					};

				 }
			}
		 }
	}
	if(matched != 1){
		 cout<<"Sorry! something went wrong, perhaps some typing mistake. Please try again!"<<endl;
		 getch();
		 disp_home();
	}
}
void Bank::review_acc(int acc){
	int matched = 0;
	for(int i = 0; i < max_users; i++){
		if(u[i].get_acc_no() == acc){
			cout<<"Account no.: "<<u[i].get_acc_no()<<endl;
			cout<<"Name: ";
			puts(u[i].name);
			cout<<"Aadhar no.: ";
			puts(u[i].aadhar);
			cout<<"Current Balance: ";
			disp_money(u[i].get_bal());
			matched = 1;
			break;
		}
	}
	if(!matched){
		cout<<"Sorry, we couldn't find you! "<<endl;
		getch();
		disp_home();
	}
	else{
		getch();
		disp_user(&u[i]);
	};

}
void Bank::deposit(int dep_acc = 0){
	int i;
	int acc;
	float money;
	int matched = 0;
	clrscr();
	cout<<"DEPOSIT: "<<endl;
	cout<<"Enter Account no of creditor: ";
	cin>>acc;
	cout<<"Enter Money to deposit: ";
	cin>>money;
	//to check whether given acc_no exists
	for(i = 0; i < max_users; i++) {
		if(u[i].get_acc_no() == acc){
			matched = 1;
			break;
		 }
	}
	if(dep_acc == 0){//If the depositor isn't a existing user
		char depositor[20];
		cout<<"Enter the name of depositor: ";
		gets(depositor);
		gen_format(depositor);
		u[i].add_bal(money);
		if(matched != 1){
			 cout<<"Invalid Account no. "<<endl;
			 getch();
			 disp_home();
		}
		else{
			cout<<"The money has been succesfully deposited to:\n";
			cout<<"Account No: "<<u[i].get_acc_no()<<endl;
			cout<<"Account Name: ";
			puts(u[i].name);
			cout<<"By: "<<depositor<<endl;
			getch();
			disp_home();
		};
	}
	else
	{
		//get depositors acc_no
		for(int k = 0; k < max_users; k++){
			if(u[k].get_acc_no() == dep_acc){
				break;
			}
		}
		if(matched != 1){ //if creditor's account is not found
			cout<<"The account no in which you are trying to deposit is incorrect. Please try again"<<endl;
			getch();
			disp_user(&u[k]);
		}
		if(u[i].get_acc_no() == u[k].get_acc_no()) {
		   //If you deposit to your own account
			u[k].add_bal(money);
			cout<<"The money has been succesfully deposited to:\n";
			cout<<"Account No: "<<u[i].get_acc_no()<<endl;
			cout<<"Name: ";
			puts(u[i].name);
			cout<<"By: "<<u[k].name<<endl;
			cout<<"Current Balance: ";
			disp_money(u[i].get_bal());
			getch();
			disp_user(&u[k]);
		}
		else{ //if you deposit to someone's account
			if(u[k].remove_bal(money) == 1){
				u[i].add_bal(money);
				cout<<"The money has been succesfully deposited to:\n";
				cout<<"Account No: "<<u[i].get_acc_no()<<endl;
				cout<<"Name: ";
				puts(u[i].name);
				cout<<"By: "<<u[k].name<<endl;
				cout<<"Balance Remaining: ";
				disp_money(u[k].get_bal());
				getch();
				disp_user(&u[k]);
			}
			else{
				cout<<"Insufficient balance! "<<endl;
				cout<<"Current Balance: ";
				disp_money(u[k].get_bal());
				getch();
				disp_user(&u[k]);
			};
		}

	};

}
void Bank::withdraw(int acc_no){
	clrscr();
	cout<<"WITHDRAW: "<<endl;
	for(int i = 0; i < max_users; i++){
		if(u[i].get_acc_no() == acc_no){
		     cout<<"Enter Amount of money: ";
		     float money = 0;
		     cin>>money;
		     if(u[i].remove_bal(money) == 0){
				cout<<"Insufficient balance! "<<endl;
				cout<<"Current Balance: ";
				disp_money(u[i].get_bal());
				getch();
				disp_user(&u[i]);
		     }
		     else{
			cout<<"Withdraw Successfull! "<<endl;
			cout<<"Balance Remaining: ";
			disp_money(u[i].get_bal());
			getch();
			disp_user(&u[i]);
		     };
		}
	}
}
void Bank::forgot_pass(char c){
	char last_pass[20];
	char nm[50];
	int acc_no;
	char aad_no[13];
	clrscr();
	cout<<"FORGOT PASSWORD: "<<endl;
	cout<<"Enter Account no.: ";
	cin>>acc_no;
	cout<<"Enter your name: ";
	gets(nm);
	gen_format(nm); // for generalized format
	cout<<"Enter the last password you remember: ";
	gets(last_pass);
	cout<<"Enter your Aadhar card no.: ";
	aad:
	cin>>aad_no;
	for(int o = 0; o < 12; o++){
		if(aad_no[o] < '0' || aad_no[o] > '9' ){
			cout<<"Invalid Aadhar card no. Please type again: ";
			goto aad;
		}
	}
	int matched = 0;
	for(int i = 0; i < max_users; i++){
		if(u[i].get_acc_no() == acc_no){
			if(strcmp(u[i].name,nm) == 0){
				if(strcmp(u[i].aadhar, aad_no) == 0){
					matched = 1;
					cout<<"Your password is: ";
					strcpy(last_pass, u[i].get_pass());
					puts(last_pass);
					getch();
					clrscr();
					if(c == 'L')	b1.login();
					else if(c == 'C')	b1.change_creden(acc_no);
					else if(c == 'R')	b1.remove_acc();
					else if(c == 'W')	b1.withdraw(u[i].get_acc_no());
					else{};
					break;
				}
			}
	       }

	}
	if(matched != 1){
		cout<<"Sorry! We didn't recognise its you. Please try again!"<<endl;
		getch();
		disp_home();
	}
}
void Bank::change_creden(int acc)
{
	int choice;
	clrscr();
	for(int i =0; i < max_users; i++){
		if(u[i].get_acc_no() == acc){
			break;
		}
	}
	cout<<"CHANGE YOUR CREDENTIALS: "<<endl;
	cout<<"Please press what you want to change: "<<endl;
	cout<<"1. Name"<<endl;
	cout<<"2. Password "<<endl;
	cout<<"3. To go back"<<endl;
	cin>>choice;
	switch(choice){
		case 1:
			char new_name[20];
			cout<<"Enter new name: ";
			gets(new_name);
			gen_format(new_name); //for generalized format
			strcpy(u[i].name, new_name);
			cout<<"Account Successfully renamed! "<<endl;
			cout<<"New name: ";
			puts(u[i].name);
			getch();
			disp_user(&u[i]);
			break;
		case 2:
			change_pass(acc);
			getch();
			disp_home();
			break;
		case 3:
			clrscr();
			disp_user(&u[i]);
			break;
		default:
			cout<<"Invalid choice! ";
			getch();
			//To go back
			disp_user(&u[i]);
	}

}
void Bank::change_pass(int acc){
	clrscr();
	for(int i = 0; i < max_users; i++){
		if(u[i].get_acc_no() == acc)
		{
			break;
		}
	}
	char old_pass[20];
	char new_pass[20];
	char aad_no[13];
	cout<<"CHANGE PASSWORD: "<<endl;
	cout<<"Enter old password: ";
	gets(old_pass);
	cout<<"Enter Your Aadhar no.: ";
	aad:
	cin>>aad_no;
	for(int o = 0; o < 12; o++){
		if(aad_no[o] < '0' || aad_no[o] > '9' ){
			cout<<"Invalid Aadhar card no. Please type again: ";
			goto aad;
		}
	}
	if(strcmp(u[i].aadhar, aad_no) == 0){
		cout<<"Enter New password: ";
		cin>>new_pass;
		if(u[i].change_password(old_pass,new_pass) == 1){
			cout<<"Password changed! "<<endl;
		}
		else{
			cout<<"Your old password is incorrect!"<<endl;
			cout<<"Forgot? ";
			char choice;
			cin>>choice;
			if(choice == 'Y' || choice == 'y'){
				b1.forgot_pass('C');
			}
			else{
				change_creden(acc);
			};
		};
	}
	else{
		cout<<"Aadhar no was incorrect! "<<endl;
		getch();
		change_creden(acc);
	};
}
Bank::Bank(){
	//To fetch data from Bank.dat and initialize users
	fstream f1;
	f1.open("Avion\\Bank.dat", ios::in);
	f1.read((char *) & b1, sizeof(b1));
}
void update(){
	//function to update files
	fstream f1;
	f1.open("Avion\\Bank.dat",ios::out);
	f1.write((char *) & b1, sizeof(b1));
	f1.close();
	f1.open("Avion\\Accounts.txt", ios::out);
	f1<<Bank::accounts;
	f1.close();
}
void Bank::remove_acc()
{
	char pass[20];
	int acc;
	clrscr();
	cout<<"REMOVE ACCOUNT: "<<endl;
	cout<<"Enter Account no.: ";
	cin>>acc;
	p:
	cout<<"Enter Password: ";
	cin>>pass;

	int i = 0;
	for(i = 0; i < max_users; i++){
		if(u[i].get_acc_no() == acc)
		{
			if(u[i].check_pass(pass) ==1){
				char temp;
				cout<<"(Y/N)Are you sure :( ";
				cin>>temp;
				if(temp  >= 97){
					temp -= 32;
				}
				if(temp == 'Y'){
					u[i].user::user();
					cout<<"Account Removed."<<endl;
					change_no_of_acc(-1);
					getch();
					disp_home();
				}
				else{
					disp_home();
				};
				break;
			}
			else{
				cout<<"Invalid password!"<<endl;
				cout<<"Forgot password? "<<endl;
				char choice;
				cin>>choice;
				if(choice == 'y' || choice == 'Y'){
					b1.forgot_pass('R');
				}
				else{
					goto p;
				};
			}
		}
	}
	cout<<"No such account exists! "<<endl;
	getch();
	disp_home();

}
void disp_home()
{
	start:
	clrscr();
	update();
	cout<<"";
	cout<<"\t\t\t   WELCOME TO AVION BANK "<<endl;
	cout<<"";
	cout<<"Press: \n";
	cout<<"1. Login "<<endl;
	cout<<"2. Sign-in "<<endl;
	cout<<"3. Deposit "<<endl;
	cout<<"4. Remove your account "<<endl;
	cout<<"5. Exit "<<endl;
	int choice;
	cin>>choice;
	switch(choice){
		case 1:
			b1.login();
			break;
		case 2:
			b1.signin();
			break;
		case 3:
			b1.deposit();
			break;
		case 4:
			clrscr();
			b1.remove_acc();
			break;
		case 5:
			return;
		default:
			cout<<"Invalid choice!"<<endl;
			getch();
			goto start;
	}

}
void disp_user(user *u){
	start:
	clrscr();
	cout<<"Welcome ";
	for(int b = 0; b < 50; b++){
		//only display user's firstname
		if(u->name[b] != ' ')		cout<<u->name[b];
		else				break;
	}
	     if(u->gender == 'M')
		cout<<" sir, How can I help you"<<endl;
	     else
		cout<<" Ma'am, How can I help you"<<endl;

	cout<<"Please press: "<<endl;
	cout<<"1. To change your credentials"<<endl;
	cout<<"2. To review your information"<<endl;
	cout<<"3. To withdraw money"<<endl;
	cout<<"4. To deposit to your/someone's account "<<endl;
	cout<<"5. To remove this account"<<endl;
	cout<<"6. To log out and go Back "<<endl;
	int choice;
	cin>>choice;
	switch(choice){
		case 1:
			b1.change_creden(u->get_acc_no());
			break;
		case 2:
			b1.review_acc(u->get_acc_no());
			break;
		case 3:
			b1.withdraw(u->get_acc_no());
			break;
		case 4:
			b1.deposit(u->get_acc_no());
			break;
		case 5:
			b1.remove_acc();
			break;
		case 6:
			disp_home();
			break;
		default:
			cout<<"Invalid choice!"<<endl;
			goto start;
	}
}
void gen_format(char *nm){
	strlwr(nm);
	nm[0] = toupper(nm[0]);
	for(int m = 1 ; m < strlen(nm);m++){
		if(nm[m] == ' '){
			nm[m+1] = toupper(nm[m+1]);
		}
	}
}
char *gen_format(double a)
{
	long b = a;
	int c[10];
	//to convert the given input to array of ints
	for(int i = 10, j = 9; (j >= 0 && i > 0); i--,j--){
		c[j] = b/pow(10,i-1);         //it does so by removing from the order
		b -= (c[j]*pow(10,i-1));      //of 1000s which why it reverses the number
	}
	char e[20];  //to store the converted string
	int tr_zero = 1;
	//add a '-1'(serving as '\0') at the end of significant digits
	for(int r = 0; r < 10; r++){
		//compare the given index with others following it
		for(int y = r+1; y < 10; y++){
			if(c[y] != 0){
				tr_zero = 0;   //it makes tr_zero 1 if it
				break;         //cannot find any digit following it
			}
			else
				tr_zero = 1;
		}
		if(y == 9){
			tr_zero = 1;
		}
		if(tr_zero != 0){
			break;
		}
	}
	c[r+1] = -1; //add '-1' terminator at the end
	//convert int array to char array including commas wherever necessary
	for(int k = 0,l = 0; k < 20; k++,l++){
		if(k != 0){
			if(k%3 == 0){
				e[k] = ',';
				k++;
			}
		}
		e[k] = (c[l] + 48);//actual conversion from char to int
		if(c[l] == -1){
			e[k] = '\0';
			break;
		}
		if(l == 9) {
			e[k+1] = '\0';
			break;
		}
	}
	strrev(e);
	return e;
}
int show_dec(double a){
	int re_val;
	int temp = a;
	double b;
	b = a- temp;
	re_val = (b*100);
	return re_val;
}
void disp_money(float amount){
	char *f = gen_format(amount);
	char d[20];
	if(f[0] == ','){
		for(int i = 1,j =0 ; i < 20; j++,i++){
			d[j] = f[i];
		}
	}
	else{
		for(int i = 0; i < 20; i++){
			d[i] = f[i];
		}
	};
	cout<<"Rs. "<<d<<".";
	int dec = show_dec(amount);
	if(dec == 0){
		cout<<"00"<<endl;
	}
	else{
		cout<<show_dec(amount)<<endl;
	};
}
