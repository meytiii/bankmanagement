#include <iostream>
#include <vector>
#include <string>
#include "Date.h"
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

class bank;

//menu
void menu(bank&);
void menu_man(bank&);
void menu_fman(bank&);
void menu_Employee(bank&, int);
void menu_cost(bank&, int);
//save to file
void updt(bank &b);
void read(bank &b);
void day_vam_inc(bank &b);
//utilities
string serial_generator(bank &bank);
void loan_payments(bank &bank);
void end_of_month(bank &bank);

class Account
{
public:
    Account() {}
    Account(string n, string c, Date o, long long int bal, int v = 0, bool f = true) {
        day_vam = v;
        Account_active = f;
        account_number = n;
        owner_codem = c;
        Balance = bal;
        Opening_date = o;
    }
    void Check_account_balance()
    {
        if (Balance >= 1000000)
        {
            day_vam++;
        }
    }
    long long int Facilities()
    {
        return Balance * day_vam;
    }
    void Account_increase(long long int amount)
    {
        Balance += amount;
    }
    void Account_reduction(long long int amount)
    {
        //if Balance<0
        Balance -= amount;
    }
    bool get_active() { return Account_active; }
    void active_account() {
        this->Account_active = true;
    }
    void deactive_account() {
        this->Account_active = false;
    }
    string get_account_number() { return account_number; }
    string get_codem() { return owner_codem; }
    Date get_date() { return Opening_date; }
    long long int get_bal() { return Balance; }
    int get_dayvam() { return day_vam; }
    void show_baseinfo() {
        cout << "Account number: " << account_number << ", Balance: " << Balance << endl;
        cout<<"Days over 1M="<<day_vam<<endl;
    }
    void show_all() {

    }
private:
    string account_number;
    string owner_codem;
    Date Opening_date;
    long long int Balance;
    int day_vam;
    bool Account_active;
};

class human
{
public:
    human() {}
    human(string n, string f, Date b, string u, string p) {
        name = n;
        family = f;
        birthdate = b;
        username = u;
        password = p;
    }
    ~human() {}
    virtual void View_all_information()
    {
        cout << "name :" << name << endl;
        cout << "family :" << family << endl;
        cout << "birthdate :" << birthdate.get_year() << "/" << birthdate.get_month() << "/" << birthdate.get_day() << endl;
        cout << "username :" << username << endl;
        cout << "password :" << password << endl;
    }
    string get_user() { return username; }
    string get_pass() { return password; }
    string get_name() { return name; }
    string get_fname() { return family; }
    Date get_date() { return birthdate; }

private:
    string name;
    string family;
    Date birthdate;
    string username;
    string password;
};

class costomer :public human
{
public:
    costomer() {}
    costomer(string n, string f, Date b, string u, string p, string c) :human(n, f, b, u, p) {
        codeM = c;
    }
    ~costomer() {}
    virtual void View_all_information()
    {
        human::View_all_information();
        cout << "codeM :" << codeM << endl;
    }
    void withdraw() {
        cout << "Enter account number:\n";
    }
    void add_account(Account a) {
        Accounts.push_back(a);
    }
    void del_account(int p) {   //delete an account by position
        Accounts.erase(Accounts.begin() + p);
    }
    void active_account(int j) {
        Accounts[j].active_account();
    }
    void deactive_account(int j) {
        Accounts[j].deactive_account();
    }
    void deposit(long long int bal, int i) {
        Accounts[i].Account_increase(bal);

    }
    void withdraw(long long int bal, int i) {
        Accounts[i].Account_reduction(bal);
    }
    void set_account(vector<Account> a) {
        Accounts = a;
    }
    vector <Account> get_Accounts() { return Accounts; }
    string get_codeM() { return codeM; }
private:
    string codeM;
    vector <Account> Accounts;
};
class Facilities
{
public:
    Facilities(string c,Date r, long long int amount, int interest,
               int installment,
               string serial_num,int paid=0, int overdue=0 ){
        Connected_account_number=c;
        Date_received=r;
        Loan_amount=amount;
        loan_interest=interest;
        Total_number_of_installments=installment;
        Amount_per_installment=amount_per_installment();
        Serial_number=serial_num;
        Number_of_installments_paid=paid;
        Number_of_overdue_installments=overdue;
    }
    long long int amount_per_installment()
    {
        long long int Amount = ((Loan_amount * (loan_interest + 100))
                                  / 100) / Total_number_of_installments;
        return Amount;
    }
    //adder
    void add_Number_of_installments_paid(){Number_of_installments_paid++;}
    void add_Number_of_overdue_installments(){Number_of_overdue_installments++;}
    //getter
    long long int get_Amount_per_installment(){return  Amount_per_installment;}
    string get_account_num() { return Connected_account_number; }
    Date get_date_rec() { return Date_received; }
    long long int get_amount() { return Loan_amount; }
    int get_loan_intrest() { return loan_interest; }
    int get_total_instal(){return Total_number_of_installments;}
    int get_num_instal() { return Number_of_installments_paid; }
    int get_num_over() { return Number_of_overdue_installments; }
    string get_serial() { return Serial_number; }
    //utilities
    void display_info(){
        cout<<"Account number:"<<Connected_account_number<<", Amount:"<<Loan_amount<<
              ", Interest:"<<loan_interest<<", Number of installments:"
           <<Total_number_of_installments<<endl;
        cout<<"Amount per installment:"<<Amount_per_installment<<", paid:"
           <<Number_of_installments_paid<<endl;
        cout<<"Number of overdue installments:"<<Number_of_overdue_installments
           <<", Serial:"<<Serial_number<<", Date:";
        Date_received.print_date();
        cout<<endl;

    }
int get_Number_of_overdue_installments(){return Number_of_overdue_installments;}
void pay(){Number_of_overdue_installments=0;}
private:
    string Connected_account_number;
    Date Date_received;
    long long int Loan_amount;
    int loan_interest;
    int Total_number_of_installments;
    long long int Amount_per_installment;
    int Number_of_installments_paid;  //default 0
    int Number_of_overdue_installments;    //default 0
    string Serial_number;
};
class Employee :public human
{
public:
    Employee() {
        Vacation_hours = 0;
        Overtime_hours = 0;
    }
    Employee(string n, string f, Date b, string u, string p, int id, long s,int v=0,int o=0) :human(n, f, b, u, p) {
        Vacation_hours = v;
        Overtime_hours = o;
        personnel_id = id;
        base_salary = s;
    }
    ~Employee() {}
    int get_Vacation_hours() { return  Vacation_hours; }
    int get_Overtime_hours() { return  Overtime_hours; }
    void Request_for_leave(int H)
    {
        Vacation_hours += H;
    }
    void Request_for_overtime(int H) {
        Overtime_hours += H;
    }
    void set_vacation(int vac){
        Vacation_hours=vac;
    }
    void set_overtime(int overtime){
        Overtime_hours=overtime;
    }
    void set_salary(long long int sal){
        base_salary=sal;
    }
    long get_salary() { return base_salary; }
    int get_id() { return personnel_id; }
    virtual void View_all_information()
    {
        human::View_all_information();
        cout << "base_salary :" << base_salary << endl;
        cout << "Vacation_hours :" << Vacation_hours << endl;
        cout << "Overtime_hours :" << Overtime_hours << endl;
        cout << "Personnel_ID :" << personnel_id << endl;
    }
private:
    int personnel_id;
    long long int base_salary;
    int Vacation_hours;
    int Overtime_hours;
};

class manager :public Employee {
public:
    manager() {}
    manager(string n, string f, Date b, string u, string p, int id, long s, int v = 0, int o = 0)
        :Employee(n, f, b, u, p, id, s, v, o) {}
    ~manager() {}

};

class facility_manager :public Employee {
public:
    facility_manager() {}
    facility_manager(string n, string f, Date b, string u, string p, int id, long s, int v = 0, int o = 0)
        :Employee(n, f, b, u, p, id, s, v, o) {}
    ~facility_manager() {}
};

class bank {
public:
    bank() {}
    bank(string b, string c, manager m, facility_manager fm) {
        branch_name = b;
        branch_code = c;
        modir = m;
        facility_modir = fm;
    }
    //add things
    void add_costomer(costomer c)
    {
        customer_list.push_back(c);
    }
    void add_employee(Employee c)
    {
        employee_list.push_back(c);
    }
    void add_vacation(int h, int i) {   //i=-1 manager, i=-2 facility manager
        if (i == -1)
            modir.Request_for_leave(h);
        else if (i == -2)
            facility_modir.Request_for_leave(h);
        else
            employee_list[i].Request_for_leave(h);
    }
    void add_overtime(int h, int i) {    //i=-1 manager, i=-2 facility manager
        if (i == -1)
            modir.Request_for_overtime(h);
        else if (i == -2)
            facility_modir.Request_for_overtime(h);
        else
            employee_list[i].Request_for_overtime(h);
    }
    void add_account(Account a, int i) {
        customer_list[i].add_account(a);
    }
    //settings things
    void set_vacation(int vac,int i){   //i=-1 manager, i=-2 facility manager
        if (i == -1)
            modir.set_vacation(vac);
        else if (i == -2)
            facility_modir.set_vacation(vac);
        else
            employee_list[i].set_vacation(vac);
    }
    void set_overtime(int overtime,int i){    //i=-1 manager, i=-2 facility manager
        if (i == -1)
            modir.set_overtime(overtime);
        else if (i == -2)
            facility_modir.set_overtime(overtime);
        else
            employee_list[i].set_overtime(overtime);
    }
    void set_branchname(string n) {
        branch_name = n;
    }
    void set_branchcode(string c) {
        branch_code = c;
    }
    void set_modir(manager c)
    {
        modir = c;
    }
    void set_facility_manager(facility_manager c)
    {
        facility_modir = c;
    }
    void set_customers(vector<costomer> c) {
        customer_list = c;
    }
    void set_employees(vector<Employee> e) {
        employee_list = e;
    }
    void set_salary(long long int sal,int i){
        employee_list[i].set_salary(sal);
    }
    //deleting things
    void delete_costomer(int i)
    {
        customer_list.erase(customer_list.begin() + i);
    }
    void delete_employee(int i)
    {
        employee_list.erase(employee_list.begin() + i);
    }
    void delete_account(int i, int j){
        customer_list[i].del_account(j);
    }
    void active_account(int i, int j){
        customer_list[i].active_account(j);
    }
    void deactive_account(int i, int j){
        customer_list[i].deactive_account(j);
    }
    void deposit(long long int m, int i,int j){
        customer_list[i].deposit(m, j);
    }
    void withdraw(long long int m, int i,int j){
        customer_list[i].withdraw(m, j);
    }
    //gettings things
    bool get_daily_request(){return daily_request;}
    string get_branchname() { return branch_name; }
    string get_branchcode() { return branch_code; }
    vector<costomer> get_costomers() { return  customer_list; }
    vector<Employee> get_Employees() { return  employee_list; }
    manager get_man() { return  modir; }
    facility_manager get_fman() { return  facility_modir; }
    //lists
    vector<int> personnelid_list;
    vector<string> account_num_list;
    vector<string> codem_list;
    vector<Facilities> loan_requests;
    vector<Facilities> loan_list;
    //static
    static int loan_serial;
    //utilities
    bool daily_request=true;
private:
    vector<Employee> employee_list;
    vector<costomer> customer_list;
    string branch_name;
    string branch_code;
    manager modir;
    facility_manager facility_modir;
};

int bank::loan_serial=10000;

void updt(bank& b)
{
    ofstream out;
        out.open("info.txt");
        out << b.get_Employees().size() << endl;
        if (b.get_Employees().size() != 0)
        {
            for (int i = 0; i < b.get_Employees().size(); i++)
            {
                out << b.get_Employees()[i].get_name() << endl;
                out << b.get_Employees()[i].get_fname() << endl;
                out << b.get_Employees()[i].get_date().get_day() << "/" << b.get_Employees()[i].get_date().get_month() << "/" <<
                    b.get_Employees()[i].get_date().get_year() << endl;
                out << b.get_Employees()[i].get_user() << endl;
                out << b.get_Employees()[i].get_pass() << endl;
                out << b.get_Employees()[i].get_id() << endl;
                out << b.get_Employees()[i].get_salary() << endl;
                out << b.get_Employees()[i].get_Vacation_hours() << endl;
                out << b.get_Employees()[i].get_Overtime_hours() << endl;
            }
        }

        out << b.get_costomers().size() << endl;
        if (b.get_costomers().size() != 0)
        {
            for (int i = 0; i < b.get_costomers().size(); i++)
            {
                out << b.get_costomers()[i].get_name() << endl;
                out << b.get_costomers()[i].get_fname() << endl;
                out << b.get_costomers()[i].get_date().get_day() << "/" << b.get_costomers()[i].get_date().get_month() << "/"
                    << b.get_costomers()[i].get_date().get_year() << endl;
                out << b.get_costomers()[i].get_user() << endl;
                out << b.get_costomers()[i].get_pass() << endl;
                out << b.get_costomers()[i].get_codeM() << endl;
                out << b.get_costomers()[i].get_Accounts().size() << endl;
                if (b.get_costomers()[i].get_Accounts().size() != 0)
                {
                    for (int j = 0; j < b.get_costomers()[i].get_Accounts().size(); j++)
                    {
                        out << b.get_costomers()[i].get_Accounts()[j].get_account_number() << endl;
                        out << b.get_costomers()[i].get_Accounts()[j].get_codem() << endl;

                        out << b.get_costomers()[i].get_Accounts()[j].get_date().get_day() << "/" <<
                            b.get_costomers()[i].get_Accounts()[j].get_date().get_month() << "/" <<
                            b.get_costomers()[i].get_Accounts()[j].get_date().get_year() << endl;

                        out << b.get_costomers()[i].get_Accounts()[j].get_bal() << endl;
                        out << b.get_costomers()[i].get_Accounts()[j].get_dayvam() << endl;
                        out << b.get_costomers()[i].get_Accounts()[j].get_active() << endl;
                    }
                }

            }
        }
        out << b.get_branchname() << endl;
        out << b.get_branchcode() << endl;

        out << b.get_man().get_name() << endl;
        out << b.get_man().get_fname() << endl;

        out << b.get_man().get_date().get_day() << "/" << b.get_man().get_date().get_month() << "/" <<
            b.get_man().get_date().get_year() << endl;

        out << b.get_man().get_user() << endl;
        out << b.get_man().get_pass() << endl;
        out << b.get_man().get_id() << endl;
        out << b.get_man().get_salary() << endl;
        out << b.get_man().get_Vacation_hours() << endl;
        out << b.get_man().get_Overtime_hours() << endl;


        out << b.get_fman().get_name() << endl;
        out << b.get_fman().get_fname() << endl;

        out << b.get_fman().get_date().get_day() << "/" << b.get_fman().get_date().get_month() << "/" <<
            b.get_fman().get_date().get_year() << endl;

        out << b.get_fman().get_user() << endl;
        out << b.get_fman().get_pass() << endl;
        out << b.get_fman().get_id() << endl;
        out << b.get_fman().get_salary() << endl;
        out << b.get_fman().get_Vacation_hours() << endl;
        out << b.get_fman().get_Overtime_hours() << endl;

        /*vector<int> personnelid_list;
        vector<string> account_num_list;
        vector<string> codem_list;*/
        out << b.personnelid_list.size() << endl;
        if (b.personnelid_list.size() != 0)
        {
            for (int i = 0; i < b.personnelid_list.size(); i++)
            {
                out << b.personnelid_list[i] << endl;
            }
        }

        out << b.account_num_list.size() << endl;
        if (b.account_num_list.size() != 0)
        {
            for (int i = 0; i < b.account_num_list.size(); i++)
            {
                out << b.account_num_list[i] << endl;
            }
        }

        out << b.codem_list.size() << endl;
        if (b.codem_list.size() != 0)
        {
            for (int i = 0; i < b.codem_list.size(); i++)
            {
                out << b.codem_list[i] << endl;
            }
        }
        out << b.loan_serial << endl;
        out << b.loan_requests.size() << endl;
        if (b.loan_requests.size() != 0)
        {
            for (int i = 0; i < b.loan_requests.size(); i++)
            {
                out << b.loan_requests[i].get_account_num() << endl;
                out << b.loan_requests[i].get_date_rec().get_day() << "/" << b.loan_requests[i].get_date_rec().get_month() << "/"
                    << b.loan_requests[i].get_date_rec().get_year() << endl;
                out << b.loan_requests[i].get_amount() << endl;
                out << b.loan_requests[i].get_loan_intrest() << endl;
                out << b.loan_requests[i].get_total_instal() << endl;
                out << b.loan_requests[i].get_num_instal() << endl;
                out << b.loan_requests[i].get_num_over() << endl;
                out << b.loan_requests[i].get_serial() << endl;
            }
        }
//        Facilities(string c,Date r, long long int amount, int interest,
//                   int installment,
//                   string serial_num,int paid=0, int overdue=0 ){
        out << b.loan_list.size() << endl;
        if (b.loan_list.size() != 0)
        {
            for (int i = 0; i < b.loan_list.size(); i++)
            {
                out << b.loan_list[i].get_account_num() << endl;   //string
                out << b.loan_list[i].get_date_rec().get_day() << "/" << b.loan_list[i].get_date_rec().get_month() << "/"
                    << b.loan_list[i].get_date_rec().get_year() << endl;
                out << b.loan_list[i].get_amount() << endl;   //long long int
                out << b.loan_list[i].get_loan_intrest() << endl;  //int
                out << b.loan_list[i].get_total_instal() << endl;  //int
                out << b.loan_list[i].get_num_instal() << endl;  //int
                out << b.loan_list[i].get_num_over() << endl;  //int
                out << b.loan_list[i].get_serial() << endl;   //string
            }
        }
}

void read(bank& b)
{
    ifstream input("info.txt");
        string key;
        int val;
        Employee e;
        string s1, s2, s3, s4, s5, s6, s7, s8, s9;
        int a1, a2, a3;
        long long int l;

    //employee
        getline(input, key);
        if (key.size() != 0)
        {
            val = stoi(key);
            for (int i = 0; i < val; i++)
            {
                Date d;
                getline(input, key);
                s1 = key;
                getline(input, key);
                s2 = key;
                getline(input, key);
                s3 = key;
                d = d.str_to_date(s3);
                getline(input, key);
                s4 = key;
                getline(input, key);
                s5 = key;
                getline(input, key);
                a1 = stoi(key);
                input >> l;
                getline(input, key);
                getline(input, key);
                a2 = stoi(key);
                getline(input, key);
                a3 = stoi(key);
                Employee e(s1, s2, d, s4, s5, a1, l, a2, a3);
                b.add_employee(e);
            }
        }

    //costumer
        getline(input, key);
        if (key.size() != 0)
        {
            val = stoi(key);
            for (int i = 0; i < val; i++)
            {
                Date d, d1;
                getline(input, key);
                s1 = key;
                getline(input, key);
                s2 = key;
                getline(input, key);
                s3 = key;
                d = d.str_to_date(s3);
                getline(input, key);
                s4 = key;
                getline(input, key);
                s5 = key;
                getline(input, key);
                s6 = key;
                int val2;
                getline(input, key);
                val2 = stoi(key);
                costomer cost(s1, s2, d, s4, s5, s6);
                bool f;
                for (int j = 0; j < val2; j++)
                {
                    getline(input, key);
                    s7 = key;
                    getline(input, key);
                    s8 = key;
                    getline(input, key);
                    s9 = key;
                    d1 = d1.str_to_date(s9);
                    input >> l;
                    getline(input, key);
                    getline(input, key);
                    a1 = stoi(key);
                    getline(input, key);
                    f = stoi(key);
                    Account acc(s7, s8, d1, l, a1, f);
                    cost.add_account(acc);
                }
                b.add_costomer(cost);
            }
        }

    //branch_name
        getline(input, key);
        s1 = key;
        b.set_branchname(s1);

    //branch_code
        getline(input, key);
        s1 = key;
        b.set_branchcode(s1);

    //manager
        Date d, d1;
        getline(input, key);
        s1 = key;
        getline(input, key);
        s2 = key;
        getline(input, key);
        s3 = key;
        d = d.str_to_date(s3);
        getline(input, key);
        s4 = key;
        getline(input, key);
        s5 = key;
        getline(input, key);
        a1 = stoi(key);
        input >> l;
        getline(input, key);
        getline(input, key);
        a2 = stoi(key);
        getline(input, key);
        a3 = stoi(key);
        manager m(s1, s2, d, s4, s5, a1, l, a2, a3);
        b.set_modir(m);


    //f_manager
        getline(input, key);
        s1 = key;
        getline(input, key);
        s2 = key;
        getline(input, key);
        s3 = key;
        d1 = d1.str_to_date(s3);
        getline(input, key);
        s4 = key;
        getline(input, key);
        s5 = key;
        getline(input, key);
        a1 = stoi(key);
        input >> l;
        getline(input, key);
        getline(input, key);
        a2 = stoi(key);
        getline(input, key);
        a3 = stoi(key);
        facility_manager fm(s1, s2, d1, s4, s5, a1, l, a2, a3);
        b.set_facility_manager(fm);



        getline(input, key);
        if (key.size() != 0)
        {
            val = stoi(key);
            for (int i = 0; i < val; i++)
            {
                getline(input, key);
                a1 = stoi(key);
                b.personnelid_list.push_back(a1);
            }

            getline(input, key);
            val = stoi(key);
            for (int i = 0; i < val; i++)
            {
                getline(input, key);
                b.account_num_list.push_back(key);
            }

            getline(input, key);
            val = stoi(key);
            for (int i = 0; i < val; i++)
            {
                getline(input, key);
                b.codem_list.push_back(key);
            }
            getline(input, key);
            a1 = stoi(key);
            b.loan_serial = a1;
        }
    //loan_requests
        getline(input, key);
        if (key.size() != 0)
        {
            val = stoi(key);
            for (int i = 0; i < val; i++)
            {
                getline(input, key);
                s1 = key;

                getline(input, key);
                s2 = key;

                Date d;
                d = d.str_to_date(s2);

                input >> l;
                getline(input, key);

                getline(input, key);
                a1 = stoi(key);

                getline(input, key);
                a2 = stoi(key);

                getline(input, key);
                a3 = stoi(key);

                getline(input, key);
                int a4 = stoi(key);

                getline(input, key);
                s3 = key;

                Facilities f(s1, d, l, a1, a2, s3, a3, a4);
                b.loan_requests.push_back(f);
            }
        }
    //loan_list
        getline(input, key);
        if (key.size() != 0)
        {
            val = stoi(key);
            for (int i = 0; i < val; i++)
            {
                getline(input, key);
                s1 = key;

                getline(input, key);
                s2 = key;

                Date d;
                d = d.str_to_date(s2);

                input >> l;
                getline(input, key);

                getline(input, key);
                a1 = stoi(key);

                getline(input, key);
                a2 = stoi(key);

                getline(input, key);
                a3 = stoi(key);

                getline(input, key);
                int a4 = stoi(key);

                getline(input, key);
                s3 = key;

                Facilities f(s1, d, l, a1, a2, s3, a3, a4);
                b.loan_list.push_back(f);
            }
        }
}

int main()
{
    int day;
    string days;
    ifstream day_input("dayvam.txt");
    getline(day_input, days);
    day_input.close();
    day = stoi(days);
    ofstream logday("log.txt", ios::app);
    logday << "--Day " << day << ":";
    logday << "\n";
    logday.close();

//    Date bd1(22, 5, 1379);
//    Date bd2(12, 5, 1390);
//    manager m("eisa", "nikahd", bd1, "lms", "lms", 111, 5000000);
//    facility_manager fm("taha", "zolghadri", bd2, "lms2", "lms2", 222, 3000000);
//    bank b("ShahidRajaee", "444", m, fm);
//    b.personnelid_list.push_back(111);
//    b.personnelid_list.push_back(222);
//    b.loan_serial=11111;

    bank b;
    read(b);
    menu(b);
    day_vam_inc(b);
    loan_payments(b);
    end_of_month(b);

    day++;
    ofstream day_output("dayvam.txt");
    day_output << day;
    day_output.close();

    updt(b);
    return 0;
}

void loan_payments(bank &bank)
{
        for(int i=0;i<bank.loan_list.size();i++)   //i=loan counter
        {
            string accnum=bank.loan_list[i].get_account_num();
            long long int amount=bank.loan_list[i].get_Amount_per_installment();
            int j=0;   //customer counter
            int k=0;   //account counter
            bool flag=true;
            for(j=0;j<bank.get_costomers().size() && flag;j++)
            {
                for(k=0;k<bank.get_costomers()[j].get_Accounts().size();k++)
                {
                    if(accnum==bank.get_costomers()[j].get_Accounts()[k].get_account_number())
                    {
                         if (amount > bank.get_costomers()[j].get_Accounts()[k].get_bal()) {

                                 bank.loan_list[i].add_Number_of_overdue_installments();
                                 if(bank.loan_list[i].get_Number_of_overdue_installments()==1)
                                 {
                                     cout<<"The warning was sent to "<<bank.get_costomers()[j].get_name()<<" "
                                        <<bank.get_costomers()[j].get_fname() <<
                                          " with national code "<<bank.get_costomers()[j].get_codeM()<<endl;
                                     system("pause");
                                 }
                                 else if(bank.loan_list[i].get_Number_of_overdue_installments()>=2)
                                 {
                                     for (int r = 0; r < bank.get_costomers()[j].get_Accounts().size(); r++) {
                                         bank.deactive_account(j, r);
                                     }
                                     ofstream log("log.txt", ios::app);
                                     log << "All of (" << bank.get_costomers()[j].get_codeM() << ")"
                                         << bank.get_costomers()[j].get_fname() << " " <<
                                            bank.get_costomers()[j].get_name() <<
                                            "'s accounts have been deactivated because "<<
                                            "of not paying installments on : ";
                                     time_t my_time = time(NULL);
                                     log << ctime(&my_time);
                                     log.close();
                                 }
                                 flag=false;
                                 break;
                            }
                         else
                         {
                             if(bank.loan_list[i].get_num_instal()<bank.loan_list[i].get_total_instal()){
                                 bank.withdraw(amount,j,k);
                                 bank.loan_list[i].add_Number_of_installments_paid();
                                 flag=false;
                                 break;
                             }
                             else{
                                 bank.loan_list.erase(bank.loan_list.begin()+i);
                                 flag=false;
                                 break;
                             }
                         }
                    }
                }
            }
        }
}

void end_of_month(bank &bank){
    int day;
    string days;
    ifstream day_input("dayvam.txt");
    getline(day_input, days);
    day_input.close();
    day = stoi(days);
    if(day%30==0){
        cout<<"End of month!"<<endl;
        //employees' salary
        for(int i=0;i<bank.get_Employees().size();i++){
            long long int salary=bank.get_Employees()[i].get_salary();
            int vac=bank.get_Employees()[i].get_Vacation_hours();
            int overtime=bank.get_Employees()[i].get_Overtime_hours();
            if(vac>15){
                vac=vac-15;
                salary=salary-(vac*100000);
            }
            salary+=overtime*120000;
            ofstream log("log.txt", ios::app);
            log << "Employee (" << bank.get_Employees()[i].get_id() << ")"
                << bank.get_Employees()[i].get_name() << " " <<
                bank.get_Employees()[i].get_fname() <<
                " has got paid "<<salary<<" as salary on : ";
            time_t my_time = time(NULL);
            log << ctime(&my_time);
            log.close();
            bank.set_vacation(0,i);
            bank.set_overtime(0,i);
        }
        //manager's salary
        long long int salary=bank.get_man().get_salary();
        int vac=bank.get_man().get_Vacation_hours();
        int overtime=bank.get_man().get_Overtime_hours();
        if(vac>15){
            vac=vac-15;
            salary=salary-(vac*100000);
        }
        salary+=overtime*120000;
        ofstream log("log.txt", ios::app);
        log << "Manager (" << bank.get_man().get_id() << ")"
            << bank.get_man().get_name() << " " <<
            bank.get_man().get_fname() <<
            " has got paid "<<salary<<" as salary on : ";
        time_t my_time = time(NULL);
        log << ctime(&my_time);
        log.close();
        bank.set_vacation(0,-1);
        bank.set_overtime(0,-1);
        //facility manager's salary
        salary=bank.get_fman().get_salary();
        vac=bank.get_fman().get_Vacation_hours();
        overtime=bank.get_fman().get_Overtime_hours();
        if(vac>15){
            vac=vac-15;
            salary=salary-(vac*100000);
        }
        salary+=overtime*120000;
        log.open("log.txt", ios::app);
        log << "Facility manager (" << bank.get_fman().get_id() << ")"
            << bank.get_fman().get_name() << " " <<
            bank.get_fman().get_fname() <<
            " has got paid "<<salary<<" as salary on : ";
        log << ctime(&my_time);
        log.close();
        bank.set_vacation(0,-2);
        bank.set_overtime(0,-2);
    }
}

string serial_generator(bank &bank){
    string serial=bank.get_branchcode();
    serial.append("-");
    serial.append(to_string(bank::loan_serial));
    bank::loan_serial++;
    return serial;
}

void day_vam_inc(bank &b){
    vector<costomer> c=b.get_costomers();
    for(int i=0;i<c.size();i++){
        vector<Account> a=c[i].get_Accounts();
        for(int j=0;j<a.size();j++){
            a[j].Check_account_balance();
        }
        c[i].set_account(a);
    }
    b.set_customers(c);
}

void menu(bank& bank)
{
    while (true)
    {
        system("cls");
        cout << "~~~~~welcome~~~~~\n";
        cout << "1) Employee.\n";
        cout << "2) Customer.\n";
        cout << "3) Exit.\n";
        int opt;
        cin >> opt;
        if (opt == 1)
        {
            system("cls");
            cout << "enter username: ";
            string us;
            cin >> us;
            cout << "enter password: ";
            string pass;
            cin >> pass;
            bool flagm = false;
            bool flagfm = false;
            bool flage = false;
            int i = 0;
            if (bank.get_man().get_pass() == pass && bank.get_man().get_user() == us)
                flagm = true;
            else if (bank.get_fman().get_user() == us && bank.get_fman().get_pass() == pass)
                flagfm = true;
            else
            {
                for (i = 0; i < bank.get_Employees().size(); i++)
                {
                    if (bank.get_Employees()[i].get_user() == us &&
                        bank.get_Employees()[i].get_pass() == pass)
                    {
                        flage = true;
                        break;
                    }
                }
            }
            if (flagm)
            {
                cout << "Successfully logged in as manager!\n";
                ofstream log("log.txt", ios::app);
                log << "Manager (" << bank.get_man().get_id() << ")"
                    << bank.get_man().get_name() << " " <<
                    bank.get_man().get_fname() <<
                    " has logged in the system on : ";
                time_t my_time = time(NULL);
                log << ctime(&my_time);
                log.close();
                system("pause");
                menu_man(bank);
            }
            else if (flagfm)
            {
                cout << "Successfully logged in as facility manager!\n";
                ofstream log("log.txt", ios::app);
                log << "Facility manager (" << bank.get_fman().get_id() << ")"
                    << bank.get_fman().get_name() << " " <<
                    bank.get_fman().get_fname() <<
                    " has logged in the system on : ";
                time_t my_time = time(NULL);
                log << ctime(&my_time);
                log.close();
                system("pause");
                menu_fman(bank);
            }
            else if (flage)
            {
                cout << "Successfully logged in as employee!\n";
                ofstream log("log.txt", ios::app);
                log << "Employee (" << bank.get_Employees()[i].get_id() << ")"
                    << bank.get_Employees()[i].get_name() << " " <<
                    bank.get_Employees()[i].get_fname() <<
                    " has logged in the system on : ";
                time_t my_time = time(NULL);
                log << ctime(&my_time);
                log.close();
                system("pause");
                menu_Employee(bank, i);
            }
            else
            {
                cout << "username or password Invalid :(\n";
                system("pause");
            }
        }
        if (opt == 2)
        {
            system("cls");
            cout << "enter username: ";
            string us;
            cin >> us;
            cout << "enter password: ";
            string pass;
            cin >> pass;
            bool flag = false;
            int i;
            for (i = 0; i < bank.get_costomers().size(); i++)
            {
                if (bank.get_costomers()[i].get_pass() == pass && bank.get_costomers()[i].get_user() == us)
                {
                    flag = true;
                    break;
                }
            }
            if (flag)
            {
                cout << "Successfully logged in as customer!\n";
                ofstream log("log.txt", ios::app);
                log << "Customer (" << bank.get_costomers()[i].get_codeM() << ")"
                    << bank.get_costomers()[i].get_name() << " " <<
                    bank.get_costomers()[i].get_fname() <<
                    " has logged in the system on : ";
                time_t my_time = time(NULL);
                log << ctime(&my_time);
                log.close();
                system("pause");
                menu_cost(bank, i);
            }
            else
            {
                cout << "username or password Invalid :(\n";
                system("pause");
            }

        }
        if (opt == 3)
        {
            cout << "Good bye!" << endl;     //karaye file va save va rooz
            break;
        }
    }
}
void menu_man(bank& bank)
{
    while (true) {
        system("cls");
        cout << "~~~Welcome " << bank.get_man().get_name() << " "
            << bank.get_man().get_fname() << "~~~\n";
        cout << "1-Request for leave.\n";
        cout << "2-Request for overtime.\n";
        cout << "3-Display personal information.\n";
        cout << "4-View complete customer information using a national number.\n";
        cout << "5-Create an account for a customer.\n";
        cout << "6-Delete a customer's account.\n";
        cout << "7-Show an employee's information.\n";
        cout << "8-Hire a new employee.\n";
        cout << "9-Fire an employee.\n";
        cout << "10-Exit.\n";
        int opt;
        cin >> opt;
        if (opt == 1)
        {
            system("cls");
            cout << "Hours of vacation taken this month :" <<
                bank.get_man().get_Vacation_hours() << endl;
            int max = bank.get_man().get_salary() / 100000;
            int current = bank.get_man().get_Vacation_hours();
            max = 15 - current + max;
            while (true) {
                cout << "Maximum hours you can take this month: " << max << endl;
                cout << "(Enter 0 to cancel the operation.)" << endl;
                int hour;
                cin >> hour;
                if (hour == 0)
                    break;
                if (hour > max || hour < 0) {
                    cout << "Invalid hour!\n";
                }
                else {
                    bank.add_vacation(hour, -1);
                    cout << "You got " << hour << " hours for vacation.Have fun!\n";
                    ofstream log("log.txt", ios::app);
                    log << "Manager (" << bank.get_man().get_id() << ")"
                        << bank.get_man().get_name() << " " <<
                        bank.get_man().get_fname() <<
                        " has taken " << hour << " hours vacation " << "on : ";
                    time_t my_time = time(NULL);
                    log << ctime(&my_time);
                    log.close();
                    system("pause");
                    break;
                }
            }
        }
        if (opt == 2)
        {
            system("cls");
            cout << "Overtime hours taken this month :" <<
                bank.get_man().get_Overtime_hours() << endl;
            while (true) {
                cout << "Allowed hours for overtime :" << 12 - bank.get_man().get_Overtime_hours() << endl;
                cout << "(Enter 0 to cancel the operation.)" << endl;
                int hour;
                cin >> hour;
                if (hour == 0)
                    break;
                if (hour<0 || hour>(12 - bank.get_man().get_Overtime_hours()))
                {
                    cout << "Invalid hour!\n";
                }
                else
                {
                    bank.add_overtime(hour, -1);
                    cout << "You got " << hour << " hours for overtime.Have fun!\n";
                    ofstream log("log.txt", ios::app);
                    log << "Manager (" << bank.get_man().get_id() << ")"
                        << bank.get_man().get_name() << " " <<
                        bank.get_man().get_fname() <<
                        " has taken " << hour << " hours overtime " << "on : ";
                    time_t my_time = time(NULL);
                    log << ctime(&my_time);
                    log.close();
                    system("pause");
                    break;
                }
            }
        }
        if (opt == 3)
        {
            system("cls");
            cout << "Bank manager:" << endl;
            bank.get_man().View_all_information();
            system("pause");
        }
        if (opt == 4)
        {
            system("cls");
            cout << "Customer National Number :";
            string National_code;
            cin >> National_code;
            int i = 0;
            bool flag = true;
            for (; i < bank.get_costomers().size(); i++)
            {
                if (National_code == bank.get_costomers()[i].get_codeM())
                {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                cout << "Not found!" << endl;
                system("pause");
            }
            else {
                bank.get_costomers()[i].View_all_information();
                for (int j = 0; j < bank.get_costomers()[i].get_Accounts().size(); j++) {
                    if (bank.get_costomers()[i].get_Accounts()[j].get_active() == true) {
                        cout << j + 1 << ". (ACTIVE) ";
                        bank.get_costomers()[i].get_Accounts()[j].show_baseinfo();
                    }
                    else {
                        cout << j + 1 << ". (DEACTIVE) ";
                        bank.get_costomers()[i].get_Accounts()[j].show_baseinfo();
                    }

                }
                system("pause");
            }
        }
        if (opt == 5)
        {
            system("cls");
            cout << "Is it a person's first account ?\n" << endl;
            cout << "1)Yes\n";
            cout << "2)NO\n";
            int x;
            cin >> x;
            if (x == 1)
            {
                string name;
                string family;
                string codeM;
                Date birthdate;
                string username;
                string password;
                string bday;
                cout << "~~~~ Create a new customer ~~~~~" << endl;
                cout << "name: "; cin >> name;
                cout << "family name: "; cin >> family;
                while (true) {
                    cout << "National code: "; cin >> codeM;
                    bool flagcode = false;
                    bool digit = false;
                    if (codeM.size() != 11) {
                        cout << "National code must be 11 digits." << endl;
                        digit = true;
                    }
                    for (int k = 0; k < bank.codem_list.size(); k++) {
                        if (codeM == bank.codem_list[k]) {
                            flagcode = true;
                            cout << "This national code already exists." << endl;
                        }
                    }
                    if (flagcode == false && digit == false) {
                        break;
                    }

                }

                cout << "Birthday (d/m/y):"; cin >> bday;
                birthdate = Date::str_to_date(bday);
                cout << "username: "; cin >> username;
                cout << "password: "; cin >> password;
                costomer new_c(name, family, birthdate, username, password, codeM);
                ofstream log("log.txt", ios::app);
                log << "Customer " << "(" << codeM << ")" << name << " " << family << " has been added by " <<
                    "(" << bank.get_man().get_id() << ")" <<
                    bank.get_man().get_name() << " " << bank.get_man().get_fname() << " on : ";
                time_t my_time = time(NULL);
                log << ctime(&my_time);
                log.close();
                cout << "Enter amount of money(50,000 minimum): " << endl;
                long long int m;
                cin >> m;
                while (true) {
                    if (m < 50000) {
                        cout << "Not enough money, Enter another amount." << endl;
                        cin >> m;
                    }
                    else
                        break;
                }
                string num;
                while (true) {
                    cout << "Enter account number: (6 digits)" << endl;
                    bool rep = false;
                    bool digit = false;
                    cin >> num;         //bayad check shavad.
                    if (num.size() != 6) {
                        digit = true;
                        cout << "Invalid number, it must be 6 digits and unique." << endl;
                    }
                    for (int z = 0; z < bank.account_num_list.size(); z++) {
                        if (num == bank.account_num_list[z]) {
                            rep = true;
                            cout << "This number already exists. Try again!" << endl;
                        }
                    }
                    if (rep == false && digit == false) {
                        cout << "This number is fine." << endl;
                        break;
                    }
                }
                bank.account_num_list.push_back(num);
                cout << "Enter today's date: " << endl;
                string d;
                cin >> d;
                Date o;
                o.str_to_date(d);
                Account a(num, codeM, o, m);
                new_c.add_account(a);
                cout << "Account has been created!" << endl;
                ofstream log2("log.txt", ios::app);
                log2 << "Account " << num << " has been created by " << "(" << bank.get_man().get_id() << ")" <<
                    bank.get_man().get_name() << " " << bank.get_man().get_fname() << " on : ";
                log2 << ctime(&my_time);
                log2.close();
                a.show_baseinfo();
                bank.add_costomer(new_c);
                system("pause");
            }
            if (x == 2)
            {
                cout << "Customer's National Code :";
                string National_code;
                cin >> National_code;
                int i = 0;
                bool flag = true;
                for (; i < bank.get_costomers().size(); i++)
                {
                    if (National_code == bank.get_costomers()[i].get_codeM())
                    {
                        flag = false;
                        break;
                    }
                }
                if (flag) {
                    cout << "Not found!" << endl;
                    system("pause");
                }
                else {
                    cout << "Enter amount of money(50,000 minimum): " << endl;
                    long long int m;
                    cin >> m;
                    while (true) {
                        if (m < 50000) {
                            cout << "Not enough money, Enter another amount." << endl;
                            cin >> m;
                        }
                        else
                            break;
                    }
                    string num;
                    while (true) {
                        cout << "Enter account number: (6 digits)" << endl;
                        bool rep = false;
                        bool digit = false;
                        cin >> num;         //bayad check shavad.
                        if (num.size() != 6) {
                            digit = true;
                            cout << "Invalid number, it must be 6 digits and unique." << endl;
                        }
                        for (int z = 0; z < bank.account_num_list.size(); z++) {
                            if (num == bank.account_num_list[z]) {
                                rep = true;
                                cout << "This number already exists. Try again!" << endl;
                            }
                        }
                        if (rep == false && digit == false) {
                            cout << "This number is fine." << endl;
                            break;
                        }
                    }
                    bank.account_num_list.push_back(num);
                    cout << "Enter today's date: " << endl;
                    string d;
                    cin >> d;
                    Date o;
                    o.str_to_date(d);
                    string codeM = bank.get_costomers()[i].get_codeM();
                    Account a(num, codeM, o, m);
                    bank.add_account(a, i);
                    cout << "Account has been created!" << endl;
                    ofstream log2("log.txt", ios::app);
                    log2 << "Account " << num << " has been created by " << "(" << bank.get_man().get_id() << ")" <<
                        bank.get_man().get_name() << " " << bank.get_man().get_fname() << " on : ";
                    time_t my_time = time(NULL);
                    log2 << ctime(&my_time);
                    log2.close();
                    a.show_baseinfo();
                    system("pause");
                }
            }
        }
        if (opt == 6)
        {
            system("cls");
            cout << "Customer National Code :";
            string National_code;
            cin >> National_code;
            int i = 0;
            bool flag = true;
            for (; i < bank.get_costomers().size(); i++)
            {
                if (National_code == bank.get_costomers()[i].get_codeM())
                {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                cout << "Customer not found!" << endl;
                system("pause");
            }
            else {
                cout << "Enter the customer's account number :";
                string account_number;
                cin >> account_number;
                bool flag2 = true;
                int j = 0;
                for (j = 0; j < bank.get_costomers()[i].get_Accounts().size(); j++)
                {
                    if (bank.get_costomers()[i].get_Accounts()[j].get_account_number() == account_number)
                    {
                        flag2 = false;
                        break;
                    }
                }
                if (flag2) {
                    cout << "Account not found!" << endl;
                    system("pause");
                }
                else {
                    int k = 0;
                    for (k = 0; k < bank.account_num_list.size(); k++) {
                        if (bank.account_num_list[k] == account_number) {
                            break;
                        }
                    }
                    bank.account_num_list.erase(bank.account_num_list.begin() + k);
                    bank.delete_account(i, j);
                    cout << "Account has been deleted!" << endl;
                    ofstream log2("log.txt", ios::app);
                    log2 << "Account " << account_number << " has been deleted by " <<
                        "(" << bank.get_man().get_id() << ")" <<
                        bank.get_man().get_name() << " " << bank.get_man().get_fname() << " on : ";
                    time_t my_time = time(NULL);
                    log2 << ctime(&my_time);
                    log2.close();
                    if (bank.get_costomers()[i].get_Accounts().size() == 0) {
                        cout << "This customer has no accounts. Deleting the customer..." << endl;
                        int k = 0;
                        for (k = 0; k < bank.codem_list.size(); k++) {  //baraye delete kardan code
                            if (National_code == bank.codem_list[k]) {   //meli az list code meli ha
                                break;
                            }
                        }
                        ofstream log("log.txt", ios::app);
                        log << "Customer " << "(" << bank.get_costomers()[i].get_codeM() << ")"
                            << bank.get_costomers()[i].get_name() << " " <<
                            bank.get_costomers()[i].get_fname() << " has been deleted by " <<
                            "(" << bank.get_man().get_id() << ")" <<
                            bank.get_man().get_name() << " " << bank.get_man().get_fname() << " on : ";
                        time_t my_time = time(NULL);
                        log << ctime(&my_time);
                        log.close();
                        bank.codem_list.erase(bank.codem_list.begin() + k);
                        bank.delete_costomer(i);
                    }
                    system("pause");
                }
            }
        }
        if (opt == 7) {
            system("cls");
            cout << "Enter the employee's personnel ID:" << endl;
            int id;
            cin >> id;
            int i = 0;
            bool flag = true;
            bool flagfm = true;
            bool flagm = true;
            if (id == bank.get_man().get_id()) {
                flagm = false;
            }
            else if (id == bank.get_fman().get_id()) {
                flagfm = false;
            }
            else {
                for (i = 0; i < bank.get_Employees().size(); i++) {
                    if (bank.get_Employees()[i].get_id() == id) {
                        flag = false;
                        break;
                    }
                }
            }
            if (flag && flagm && flagfm) {
                cout << "Not found!" << endl;
                system("pause");
            }
            else if (!flag) {
                cout << "Bank employee:" << endl;
                bank.get_Employees()[i].View_all_information();
                system("pause");
            }
            else if (!flagfm) {
                cout << "Bank facility manager:" << endl;
                bank.get_fman().View_all_information();
                system("pause");
            }
            else if (!flagm) {
                cout << "Bank manager:" << endl;
                bank.get_man().View_all_information();
                system("pause");
            }
        }
        if (opt == 8) {
            system("cls");
            string name;
            string family;
            string codeM;
            Date birthdate;
            string username;
            string password;
            string bday;
            long base_salary;
            int id;
            cout << "~~~~ Create a new employee ~~~~~" << endl;
            cout << "name: "; cin >> name;
            cout << "family name: "; cin >> family;
            cout << "Birthday (d/m/y):"; cin >> bday;    //try catch
            birthdate.str_to_date(bday);
            cout << "username: "; cin >> username;
            cout << "password: "; cin >> password;
            cout << "base salary: "; cin >> base_salary;
            bool rep = false;   //baraye check kardan tekrari budan id
            bool digit = false; //baraye check kardan 3 raghami budan
            while (true) {
                cout << "personnel ID(must be unique and 3 digits): "; cin >> id;
                rep = false;
                digit = false;
                if (id < 100 || id>999) {
                    cout << "ID must be 3 digits." << endl;
                    digit = true;
                }
                for (int i = 0; i < bank.personnelid_list.size(); i++) {
                    if (id == bank.personnelid_list[i]) {
                        rep = true;
                        cout << "This ID is not unique.Try again!" << endl;
                    }
                }
                if (rep == false && digit == false) {
                    cout << "This ID is fine." << endl;
                    break;
                }
            }
            bank.personnelid_list.push_back(id);
            Employee e(name, family, birthdate, username, password, id, base_salary);
            bank.add_employee(e);
            cout << "Employee " << e.get_name() <<
                " " << e.get_fname() << " has been hired!" << endl;
            ofstream log("log.txt", ios::app);
            log << "Employee " << "(" << id << ")" << name << " " << family << " has been hired by ("
                << bank.get_man().get_id() << ")"
                << bank.get_man().get_name() << " " << bank.get_man().get_fname() << " on : ";
            time_t my_time = time(NULL);
            log << ctime(&my_time);
            log.close();
            system("pause");
        }
        if (opt == 9) {
            system("cls");
            cout << "Enter the employee's personnel ID:" << endl;
            int id;
            cin >> id;
            int i = 0;
            bool flag = true;
            for (i = 0; i < bank.get_Employees().size(); i++) {
                if (bank.get_Employees()[i].get_id() == id) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                cout << "Not found!" << endl;
                system("pause");
            }
            else {
                for (int j = 0; j < bank.personnelid_list.size(); j++) {  //baraye pak kardan id az list kole id ha
                    if (id == bank.personnelid_list[j]) {
                        bank.personnelid_list.erase(bank.personnelid_list.begin() + j);
                    }
                }
                cout << "Employee " << bank.get_Employees()[i].get_name() <<
                    " " << bank.get_Employees()[i].get_fname() <<
                    " (" << bank.get_Employees()[i].get_id() << ")" << " has been fired!" << endl;
                ofstream log("log.txt", ios::app);
                log << "Employee " << "(" << id << ")" << bank.get_Employees()[i].get_name()
                    << " " << bank.get_Employees()[i].get_fname() << " has been fired by ("
                    << bank.get_man().get_id() << ")"
                    << bank.get_man().get_name() << " " << bank.get_man().get_fname() << " on : ";
                time_t my_time = time(NULL);
                log << ctime(&my_time);
                log.close();
                bank.delete_employee(i);
                system("pause");
            }
        }
        if (opt == 10)
        {
            ofstream log("log.txt", ios::app);
            log << "Manager (" << bank.get_man().get_id() << ")"
                << bank.get_man().get_name() << " " <<
                bank.get_man().get_fname() <<
                " has logged out of the system on : ";
            time_t my_time = time(NULL);
            log << ctime(&my_time);
            log.close();
            break;
        }
    }
}
void menu_fman(bank& bank)
{
    while (true) {
        system("cls");
        cout << "~~~Welcome " << bank.get_fman().get_name() << " " <<
            bank.get_fman().get_fname() << "~~~\n";
        cout << "1-Request for leave.\n";
        cout << "2-Request for overtime.\n";
        cout << "3-Display personal information.\n";
        cout << "4-View complete customer information using a national number.\n";
        cout << "5-Create an account for a customer.\n";
        cout << "6-Delete a customer's account.\n";
        cout << "7-Blocking a customer's account.\n";
        cout << "8-View all loan requests.\n";
        cout << "9-Review loan requests.\n";
        cout << "10-View a loan details by its serial number.\n";
        cout<<"11-View all loans."<<endl;
        cout << "12-Exit.\n";
        int opt;
        cin >> opt;
        if (opt == 1)
        {
            system("cls");
            cout << "Hours of vacation taken this month :" <<
                bank.get_fman().get_Vacation_hours() << endl;
            int max = bank.get_fman().get_salary() / 100000;
            int current = bank.get_fman().get_Vacation_hours();
            max = 15 - current + max;
            while (true) {
                cout << "Maximum hours you can take this month: " << max << endl;
                cout << "(Enter 0 to cancel the operation.)" << endl;
                int hour;
                cin >> hour;
                if (hour == 0)
                    break;
                if (hour > max || hour < 0) {
                    cout << "Invalid hour!\n";
                }
                else {
                    bank.add_vacation(hour, -2);
                    cout << "You got " << hour << " hours for vacation.Have fun!\n";
                    ofstream log("log.txt", ios::app);
                    log << "Facility manager (" << bank.get_fman().get_id() << ")"
                        << bank.get_fman().get_name() << " " <<
                        bank.get_fman().get_fname() <<
                        " has taken " << hour << " hours vacation " << "on : ";
                    time_t my_time = time(NULL);
                    log << ctime(&my_time);
                    log.close();
                    system("pause");
                    system("pause");
                    break;
                }
            }
        }
        if (opt == 2)
        {
            system("cls");
            cout << "Overtime hours taken this month :" <<
                bank.get_fman().get_Overtime_hours() << endl;
            while (true) {
                cout << "Allowed hours for overtime :" << 12 - bank.get_fman().get_Overtime_hours() << endl;
                cout << "(Enter 0 to cancel the operation.)" << endl;
                int hour;
                cin >> hour;
                if (hour == 0)
                    break;
                if (hour<0 || hour>(12 - bank.get_fman().get_Overtime_hours()))
                {
                    cout << "Invalid hour!\n";
                }
                else
                {
                    bank.add_overtime(hour, -2);
                    cout << "You got " << hour << " hours for overtime.Have fun!\n";
                    ofstream log("log.txt", ios::app);
                    log << "Facility manager (" << bank.get_fman().get_id() << ")"
                        << bank.get_fman().get_name() << " " <<
                        bank.get_fman().get_fname() <<
                        " has taken " << hour << " hours overtime " << "on : ";
                    time_t my_time = time(NULL);
                    log << ctime(&my_time);
                    log.close();
                    system("pause");
                    break;
                }
            }
        }
        if (opt == 3)
        {
            system("cls");
            cout << "Bank facility manager:" << endl;
            bank.get_fman().View_all_information();
            system("pause");
        }
        if (opt == 4)
        {
            system("cls");
            cout << "Customer National Number :";
            string National_code;
            cin >> National_code;
            int i = 0;
            bool flag = true;
            for (; i < bank.get_costomers().size(); i++)
            {
                if (National_code == bank.get_costomers()[i].get_codeM())
                {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                cout << "Not found!" << endl;
                system("pause");
            }
            else {
                bank.get_costomers()[i].View_all_information();
                for (int j = 0; j < bank.get_costomers()[i].get_Accounts().size(); j++) {
                    if (bank.get_costomers()[i].get_Accounts()[j].get_active() == true) {
                        cout << j + 1 << ". (ACTIVE) ";
                        bank.get_costomers()[i].get_Accounts()[j].show_baseinfo();
                    }
                    else {
                        cout << j + 1 << ". (DEACTIVE) ";
                        bank.get_costomers()[i].get_Accounts()[j].show_baseinfo();
                    }

                }
                system("pause");
            }
        }
        if (opt == 5)
        {
            system("cls");
            cout << "Is it a person's first account ?\n" << endl;
            cout << "1)Yes\n";
            cout << "2)NO\n";
            int x;
            cin >> x;
            if (x == 1)
            {
                string name;
                string family;
                string codeM;
                Date birthdate;
                string username;
                string password;
                string bday;
                cout << "~~~~ Create a new customer ~~~~~" << endl;
                cout << "name: "; cin >> name;
                cout << "family name: "; cin >> family;
                while (true) {
                    cout << "National code: "; cin >> codeM;
                    bool flagcode = false;
                    bool digit = false;
                    if (codeM.size() != 11) {
                        cout << "National code must be 11 digits." << endl;
                        digit = true;
                    }
                    for (int k = 0; k < bank.codem_list.size(); k++) {
                        if (codeM == bank.codem_list[k]) {
                            flagcode = true;
                            cout << "This national code already exists." << endl;
                        }
                    }
                    if (flagcode == false && digit == false) {
                        break;
                    }

                }

                cout << "Birthday (d/m/y):"; cin >> bday;
                birthdate = Date::str_to_date(bday);
                cout << "username: "; cin >> username;
                cout << "password: "; cin >> password;
                costomer new_c(name, family, birthdate, username, password, codeM);
                ofstream log("log.txt", ios::app);
                log << "Customer " << "(" << codeM << ")" << name << " " << family << " has been added by " <<
                    "(" << bank.get_fman().get_id() << ")" <<
                    bank.get_fman().get_name() << " " << bank.get_fman().get_fname() << " on : ";
                time_t my_time = time(NULL);
                log << ctime(&my_time);
                log.close();
                cout << "Enter amount of money(50,000 minimum): " << endl;
                long long int m;
                cin >> m;
                while (true) {
                    if (m < 50000) {
                        cout << "Not enough money, Enter another amount." << endl;
                        cin >> m;
                    }
                    else
                        break;
                }
                string num;
                while (true) {
                    cout << "Enter account number: (6 digits)" << endl;
                    bool rep = false;
                    bool digit = false;
                    cin >> num;         //bayad check shavad.
                    if (num.size() != 6) {
                        digit = true;
                        cout << "Invalid number, it must be 6 digits and unique." << endl;
                    }
                    for (int z = 0; z < bank.account_num_list.size(); z++) {
                        if (num == bank.account_num_list[z]) {
                            rep = true;
                            cout << "This number already exists. Try again!" << endl;
                        }
                    }
                    if (rep == false && digit == false) {
                        cout << "This number is fine." << endl;
                        break;
                    }
                }
                bank.account_num_list.push_back(num);
                cout << "Enter today's date: " << endl;
                string d;
                cin >> d;
                Date o;
                o.str_to_date(d);
                Account a(num, codeM, o, m);
                new_c.add_account(a);
                cout << "Account has been created!" << endl;
                ofstream log2("log.txt", ios::app);
                log2 << "Account " << num << " has been created by " << "(" << bank.get_fman().get_id() << ")" <<
                    bank.get_fman().get_name() << " " << bank.get_fman().get_fname() << " on : ";
                log2 << ctime(&my_time);
                log2.close();
                a.show_baseinfo();
                bank.add_costomer(new_c);
                system("pause");
            }
            if (x == 2)
            {
                cout << "Customer's National Code :";
                string National_code;
                cin >> National_code;
                int i = 0;
                bool flag = true;
                for (; i < bank.get_costomers().size(); i++)
                {
                    if (National_code == bank.get_costomers()[i].get_codeM())
                    {
                        flag = false;
                        break;
                    }
                }
                if (flag) {
                    cout << "Not found!" << endl;
                    system("pause");
                }
                else {
                    cout << "Enter amount of money(50,000 minimum): " << endl;
                    long long int m;
                    cin >> m;
                    while (true) {
                        if (m < 50000) {
                            cout << "Not enough money, Enter another amount." << endl;
                            cin >> m;
                        }
                        else
                            break;
                    }
                    string num;
                    while (true) {
                        cout << "Enter account number: (6 digits)" << endl;
                        bool rep = false;
                        bool digit = false;
                        cin >> num;         //bayad check shavad.
                        if (num.size() != 6) {
                            digit = true;
                            cout << "Invalid number, it must be 6 digits and unique." << endl;
                        }
                        for (int z = 0; z < bank.account_num_list.size(); z++) {
                            if (num == bank.account_num_list[z]) {
                                rep = true;
                                cout << "This number already exists. Try again!" << endl;
                            }
                        }
                        if (rep == false && digit == false) {
                            cout << "This number is fine." << endl;
                            break;
                        }
                    }
                    bank.account_num_list.push_back(num);
                    cout << "Enter today's date: " << endl;
                    string d;
                    cin >> d;
                    Date o;
                    o.str_to_date(d);
                    string codeM = bank.get_costomers()[i].get_codeM();
                    Account a(num, codeM, o, m);
                    bank.add_account(a, i);
                    cout << "Account has been created!" << endl;
                    ofstream log2("log.txt", ios::app);
                    log2 << "Account " << num << " has been created by " << "(" << bank.get_fman().get_id() << ")" <<
                        bank.get_fman().get_name() << " " << bank.get_fman().get_fname() << " on : ";
                    time_t my_time = time(NULL);
                    log2 << ctime(&my_time);
                    log2.close();
                    a.show_baseinfo();
                    system("pause");
                }
            }
        }
        if (opt == 6)
        {
            system("cls");
            cout << "Customer National Code :";
            string National_code;
            cin >> National_code;
            int i = 0;
            bool flag = true;
            for (; i < bank.get_costomers().size(); i++)
            {
                if (National_code == bank.get_costomers()[i].get_codeM())
                {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                cout << "Customer not found!" << endl;
                system("pause");
            }
            else {
                cout << "Enter the customer's account number :";
                string account_number;
                cin >> account_number;
                bool flag2 = true;
                int j = 0;
                for (j = 0; j < bank.get_costomers()[i].get_Accounts().size(); j++)
                {
                    if (bank.get_costomers()[i].get_Accounts()[j].get_account_number() == account_number)
                    {
                        flag2 = false;
                        break;
                    }
                }
                if (flag2) {
                    cout << "Account not found!" << endl;
                    system("pause");
                }
                else {
                    int k = 0;
                    for (k = 0; k < bank.account_num_list.size(); k++) {
                        if (bank.account_num_list[k] == account_number) {
                            break;
                        }
                    }
                    bank.account_num_list.erase(bank.account_num_list.begin() + k);
                    bank.delete_account(i, j);
                    cout << "Account has been deleted!" << endl;
                    ofstream log2("log.txt", ios::app);
                    log2 << "Account " << account_number << " has been deleted by " <<
                        "(" << bank.get_fman().get_id() << ")" <<
                        bank.get_fman().get_name() << " " << bank.get_fman().get_fname() << " on : ";
                    time_t my_time = time(NULL);
                    log2 << ctime(&my_time);
                    log2.close();
                    if (bank.get_costomers()[i].get_Accounts().size() == 0) {
                        cout << "This customer has no accounts. Deleting the customer..." << endl;
                        int k = 0;
                        for (k = 0; k < bank.codem_list.size(); k++) {  //baraye delete kardan code
                            if (National_code == bank.codem_list[k]) {   //meli az list code meli ha
                                break;
                            }
                        }
                        ofstream log("log.txt", ios::app);
                        log << "Customer " << "(" << bank.get_costomers()[i].get_codeM() << ")"
                            << bank.get_costomers()[i].get_name() << " " <<
                            bank.get_costomers()[i].get_fname() << " has been deleted by " <<
                            "(" << bank.get_fman().get_id() << ")" <<
                            bank.get_fman().get_name() << " " << bank.get_fman().get_fname() << " on : ";
                        time_t my_time = time(NULL);
                        log << ctime(&my_time);
                        log.close();
                        bank.codem_list.erase(bank.codem_list.begin() + k);
                        bank.delete_costomer(i);
                    }
                    system("pause");
                }
            }
        }
        if (opt == 7) {
            system("cls");
            cout << "Enter customer's national code:" << endl;
            string codem;
            cin >> codem;
            int i = 0;
            bool flag = true;
            for (; i < bank.get_costomers().size(); i++)
            {
                if (codem == bank.get_costomers()[i].get_codeM())
                {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                cout << "Not found!" << endl;
                system("pause");
            }
            else {
                string name = bank.get_costomers()[i].get_name();
                string fname = bank.get_costomers()[i].get_fname();
                for (int z = 0; z < bank.get_costomers()[i].get_Accounts().size(); z++) {
                    bank.deactive_account(i, z);
                }
                cout << "All of " << name << " " << fname << "'s accounts have been deactivated." << endl;
                ofstream log("log.txt", ios::app);
                log << "All of (" << bank.get_costomers()[i].get_codeM() << ")"
                    << name << " " << fname << "'s accounts have been deactivated by (" <<
                    bank.get_fman().get_id() << ")" << bank.get_fman().get_name() << " "
                    << bank.get_fman().get_fname() << " on : ";
                time_t my_time = time(NULL);
                log << ctime(&my_time);
                log.close();
                system("pause");
            }
        }
        if(opt==8){
            system("cls");
            cout<<"All loan request."<<endl;
            size_t size=bank.loan_requests.size();
            for(int i=0;i<size;i++){
                bank.loan_requests[i].display_info();
            }
            system("pause");
        }
        if(opt==9){
            system("cls");
            if(bank.loan_requests.size()==0){
                cout<<"No requests!"<<endl;
                system("pause");
            }
            else{
                cout<<"Note: You can only accept one request per day!"<<endl;
                int ans;
                for(int i=0;i<bank.loan_requests.size();i++){
                    bank.loan_requests[i].display_info();
                    cout<<endl;
                    while(true){
                        cout<<"1.Accept."<<endl;
                        cout<<"2.Reject."<<endl;
                        cout<<"3.Next."<<endl;
                        cin>>ans;
                        if(ans==1 || ans==2 || ans==3){
                            break;
                        }
                    }
                    if(ans==1){
                        if(bank.daily_request==true){
                            bank.loan_list.push_back(bank.loan_requests[i]);
                            long long int loan=bank.loan_requests[i].get_amount();
                            string accnum=bank.loan_requests[i].get_account_num();
                            string ser;
                            int k=0,z=0;
                            bool found=false;
                            for(k=0;k<bank.get_costomers().size()&&found==false;k++){
                                for(z=0;z<bank.get_costomers()[k].get_Accounts().size()&&found==false;z++){
                                    if(accnum==bank.get_costomers()[k].
                                            get_Accounts()[z].get_account_number()){
                                        bank.deposit(loan,k,z);
                                        bank.daily_request=false;
                                        ser=bank.loan_requests[i].get_serial();
                                        bank.loan_requests.erase(bank.loan_requests.begin()+i);
                                        found=true;
                                        break;
                                    }
                                }
                            }
                            cout<<"Request has been accepted!"<<endl;
                            ofstream log("log.txt", ios::app);
                            log << "Facility manager (" << bank.get_fman().get_id() << ")"
                                << bank.get_fman().get_name() << " " <<
                                bank.get_fman().get_fname() <<
                                " has accepted loan("<<ser<<") on : ";
                            time_t my_time = time(NULL);
                            log << ctime(&my_time);
                            log.close();
                            system("pause");
                        }
                        else{
                            cout<<"You can't accept another request for today!"<<endl;
                            system("pause");
                        }
                    }
                    else if(ans==2){
                        bank.loan_requests.erase(bank.loan_requests.begin()+i);
                        string ser=bank.loan_requests[i].get_serial();
                        cout<<"Request has been rejected!"<<endl;
                        ofstream log("log.txt", ios::app);
                        log << "Facility manager (" << bank.get_fman().get_id() << ")"
                            << bank.get_fman().get_name() << " " <<
                            bank.get_fman().get_fname() <<
                            " has rejected loan("<<ser<<") on : ";
                        time_t my_time = time(NULL);
                        log << ctime(&my_time);
                        log.close();
                        system("pause");
                    }
                    else if(ans==3){
                        system("cls");
                        continue;
                    }

                }
            }

        }
        if(opt==10){
            system("cls");
            cout<<"Enter loan's serial number:"<<endl;
            string num;
            cin>>num;
            bool found=false;
            for(int i=0;i<bank.loan_list.size() && found==false;i++){
                if(bank.loan_list[i].get_serial()==num){
                    found=true;
                    bank.loan_list[i].display_info();
                    break;
                }
            }
            if(found==false){
                cout<<"Not found!"<<endl;
            }
            system("pause");
        }
        if(opt==11){
            system("cls");
            cout<<"All loans."<<endl;
            size_t size=bank.loan_list.size();
            for(int i=0;i<size;i++){
                bank.loan_list[i].display_info();
            }
            system("pause");
        }
        if (opt == 12)
        {
            ofstream log("log.txt", ios::app);
            log << "Facility manager (" << bank.get_fman().get_id() << ")"
                << bank.get_fman().get_name() << " " <<
                bank.get_fman().get_fname() <<
                " has logged out of the system on : ";
            time_t my_time = time(NULL);
            log << ctime(&my_time);
            log.close();
            break;
        }
    }
}
void menu_Employee(bank& bank, int index)
{
    while(true){
        system("cls");
        cout << "~~~Welcome " << bank.get_Employees()[index].get_name() << " " <<
            bank.get_Employees()[index].get_fname() << "~~~\n";
        cout << "1-Request for leave.\n";
        cout << "2-Request for overtime.\n";
        cout << "3-Display personal information.\n";
        cout << "4-View complete customer information using a national number.\n";
        cout << "5-Create an account for a customer.\n";
        cout << "6-Delete a customer's account.\n";
        cout << "7-Exit.\n";
        int opt;
        cin >> opt;
        if (opt == 1)
        {
            system("cls");
            cout << "Hours of vacation taken this month :" <<
                bank.get_Employees()[index].get_Vacation_hours() << endl;
            int max = bank.get_Employees()[index].get_salary() / 100000;
            int current = bank.get_Employees()[index].get_Vacation_hours();
            max = 15 - current + max;
            while (true) {
                cout << "Maximum hours you can take this month: " << max << endl;
                cout << "(Enter 0 to cancel the operation.)" << endl;
                int hour;
                cin >> hour;
                if (hour == 0)
                    break;
                if (hour > max || hour < 0) {
                    cout << "Invalid hour!\n";
                }
                else {
                    bank.add_vacation(hour, index);
                    cout << "You got " << hour << " hours for vacation.Have fun!\n";
                    ofstream log("log.txt", ios::app);
                    log << "Employee (" << bank.get_Employees()[index].get_id() << ")"
                        << bank.get_Employees()[index].get_name() << " " <<
                        bank.get_Employees()[index].get_fname() <<
                        " has taken " << hour << " hours vacation " << "on : ";
                    time_t my_time = time(NULL);
                    log << ctime(&my_time);
                    log.close();
                    system("pause");
                    break;
                }
            }
        }
        if (opt == 2)
        {
            system("cls");
            cout << "Overtime hours taken this month :" <<
                bank.get_Employees()[index].get_Overtime_hours() << endl;
            while (true) {
                cout << "Allowed hours for overtime :"
                    << 12 - bank.get_Employees()[index].get_Overtime_hours() << endl;
                cout << "(Enter 0 to cancel the operation.)" << endl;
                int hour;
                cin >> hour;
                if (hour == 0)
                    break;
                if (hour<0 || hour>(12 - bank.get_Employees()[index].get_Overtime_hours()))
                {
                    cout << "Invalid hour!\n";
                }
                else
                {
                    bank.add_overtime(hour, index);
                    cout << "You got " << hour << " hours for overtime.Have fun!\n";
                    ofstream log("log.txt", ios::app);
                    log << "Employee (" << bank.get_Employees()[index].get_id() << ")"
                        << bank.get_Employees()[index].get_name() << " " <<
                        bank.get_Employees()[index].get_fname() <<
                        " has taken " << hour << " hours overtime " << "on : ";
                    time_t my_time = time(NULL);
                    log << ctime(&my_time);
                    log.close();
                    system("pause");
                    break;
                }
            }
        }
        if (opt == 3)
        {
            system("cls");
            cout << "Bank employee:" << endl;
            bank.get_Employees()[index].View_all_information();
            system("pause");
        }
        if (opt == 4)
        {
            system("cls");
            cout << "Customer National Number :";
            string National_code;
            cin >> National_code;
            int i = 0;
            bool flag = true;
            for (; i < bank.get_costomers().size(); i++)
            {
                if (National_code == bank.get_costomers()[i].get_codeM())
                {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                cout << "Not found!" << endl;
                system("pause");
            }
            else {
                bank.get_costomers()[i].View_all_information();
                for (int j = 0; j < bank.get_costomers()[i].get_Accounts().size(); j++) {
                    cout << j + 1 << ". ";
                    bank.get_costomers()[i].get_Accounts()[j].show_baseinfo();
                }
                system("pause");
            }
        }
        if (opt == 5)
        {
            system("cls");
            cout << "Is it a person's first account ?\n" << endl;
            cout << "1)Yes\n";
            cout << "2)NO\n";
            int x;
            cin >> x;
            if (x == 1)
            {
                string name;
                string family;
                string codeM;
                Date birthdate;
                string username;
                string password;
                string bday;
                cout << "~~~~ Create a new customer ~~~~~" << endl;
                cout << "name: "; cin >> name;
                cout << "family name: "; cin >> family;
                while (true) {
                    cout << "National code: "; cin >> codeM;
                    bool flagcode = false;
                    bool digit = false;
                    if (codeM.size() != 11) {
                        cout << "National code must be 11 digits." << endl;
                        digit = true;
                    }
                    for (int k = 0; k < bank.codem_list.size(); k++) {
                        if (codeM == bank.codem_list[k]) {
                            flagcode = true;
                            cout << "This national code already exists." << endl;
                        }
                    }
                    if (flagcode == false && digit == false) {
                        break;
                    }

                }
                cout << "Birthday (d/m/y):"; cin >> bday;
                birthdate = Date::str_to_date(bday);
                cout << "username: "; cin >> username;
                cout << "password: "; cin >> password;
                costomer new_c(name, family, birthdate, username, password, codeM);
                ofstream log("log.txt", ios::app);
                log << "Customer " << "(" << codeM << ")" << name << " " << family << " has been added by " <<
                    "(" << bank.get_Employees()[index].get_id() << ")" <<
                    bank.get_Employees()[index].get_name() << " "
                    << bank.get_Employees()[index].get_fname() << " on : ";
                time_t my_time = time(NULL);
                log << ctime(&my_time);
                log.close();
                cout << "Enter amount of money(50,000 minimum): " << endl;
                long long int m;
                cin >> m;
                while (true) {
                    if (m < 50000) {
                        cout << "Not enough money, Enter another amount." << endl;
                        cin >> m;
                    }
                    else
                        break;
                }
                string num;
                while (true) {
                    cout << "Enter account number: (6 digits)" << endl;
                    bool rep = false;
                    bool digit = false;
                    cin >> num;         //bayad check shavad.
                    if (num.size() != 6) {
                        digit = true;
                        cout << "Invalid number, it must be 6 digits and unique." << endl;
                    }
                    for (int z = 0; z < bank.account_num_list.size(); z++) {
                        if (num == bank.account_num_list[z]) {
                            rep = true;
                            cout << "This number already exists. Try again!" << endl;
                        }
                    }
                    if (rep == false && digit == false) {
                        cout << "This number is fine." << endl;
                        break;
                    }
                }
                bank.account_num_list.push_back(num);
                cout << "Enter today's date: " << endl;
                string d;
                cin >> d;
                Date o;
                o.str_to_date(d);
                Account a(num, codeM, o, m);
                new_c.add_account(a);
                cout << "Account has been created!" << endl;
                ofstream log2("log.txt", ios::app);
                log2 << "Account " << num << " has been created by " << "("
                    << bank.get_Employees()[index].get_id() << ")" <<
                    bank.get_Employees()[index].get_name()
                    << " " << bank.get_Employees()[index].get_fname() << " on : ";
                log2 << ctime(&my_time);
                log2.close();
                a.show_baseinfo();
                bank.add_costomer(new_c);
                system("pause");
            }
            if (x == 2)
            {
                cout << "Customer's National Code :";
                string National_code;
                cin >> National_code;
                int i = 0;
                bool flag = true;
                for (; i < bank.get_costomers().size(); i++)
                {
                    if (National_code == bank.get_costomers()[i].get_codeM())
                    {
                        flag = false;
                        break;
                    }
                }
                if (flag) {
                    cout << "Not found!" << endl;
                    system("pause");
                }
                else {
                    cout << "Enter amount of money(50,000 minimum): " << endl;
                    long long int m;
                    cin >> m;
                    while (true) {
                        if (m < 50000) {
                            cout << "Not enough money, Enter another amount." << endl;
                            cin >> m;
                        }
                        else
                            break;
                    }
                    string num;
                    while (true) {
                        cout << "Enter account number: (6 digits)" << endl;
                        bool rep = false;
                        bool digit = false;
                        cin >> num;         //bayad check shavad.
                        if (num.size() != 6) {
                            digit = true;
                            cout << "Invalid number, it must be 6 digits and unique." << endl;
                        }
                        for (int z = 0; z < bank.account_num_list.size(); z++) {
                            if (num == bank.account_num_list[z]) {
                                rep = true;
                                cout << "This number already exists. Try again!" << endl;
                            }
                        }
                        if (rep == false && digit == false) {
                            cout << "This number is fine." << endl;
                            break;
                        }
                    }
                    bank.account_num_list.push_back(num);
                    cout << "Enter today's date: " << endl;
                    string d;
                    cin >> d;
                    Date o;
                    o.str_to_date(d);
                    string codeM = bank.get_costomers()[i].get_codeM();
                    Account a(num, codeM, o, m);
                    bank.add_account(a, i);
                    cout << "Account has been created!" << endl;
                    ofstream log2("log.txt", ios::app);
                    log2 << "Account " << num << " has been created by " << "("
                        << bank.get_Employees()[index].get_id() << ")" <<
                        bank.get_Employees()[index].get_name() <<
                        " " << bank.get_Employees()[index].get_fname() << " on : ";
                    time_t my_time = time(NULL);
                    log2 << ctime(&my_time);
                    log2.close();
                    a.show_baseinfo();
                    system("pause");
                }
            }
        }
        if (opt == 6)
        {
            system("cls");
            cout << "Customer National Code :";
            string National_code;
            cin >> National_code;
            int i = 0;
            bool flag = true;
            for (; i < bank.get_costomers().size(); i++)
            {
                if (National_code == bank.get_costomers()[i].get_codeM())
                {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                cout << "Customer not found!" << endl;
                system("pause");
            }
            else {
                cout << "Enter the customer's account number :";
                string account_number;
                cin >> account_number;
                bool flag2 = true;
                int j = 0;
                for (j = 0; j < bank.get_costomers()[i].get_Accounts().size(); j++)
                {
                    if (bank.get_costomers()[i].get_Accounts()[j].get_account_number() == account_number)
                    {
                        flag2 = false;
                        break;
                    }
                }
                if (flag2) {
                    cout << "Account not found!" << endl;
                    system("pause");
                }
                else {
                    int k = 0;
                    for (k = 0; k < bank.account_num_list.size(); k++) {
                        if (bank.account_num_list[k] == account_number) {
                            break;
                        }
                    }
                    bank.account_num_list.erase(bank.account_num_list.begin() + k);
                    bank.delete_account(i, j);
                    cout << "Account has been deleted!" << endl;
                    ofstream log2("log.txt", ios::app);
                    log2 << "Account " << account_number << " has been deleted by " <<
                        "(" << bank.get_Employees()[index].get_id() << ")" <<
                        bank.get_Employees()[index].get_name()
                        << " " << bank.get_Employees()[index].get_fname() << " on : ";
                    time_t my_time = time(NULL);
                    log2 << ctime(&my_time);
                    log2.close();
                    if (bank.get_costomers()[i].get_Accounts().size() == 0) {
                        cout << "This customer has no accounts. Deleting the customer..." << endl;
                        int k = 0;
                        for (k = 0; k < bank.codem_list.size(); k++) {  //baraye delete kardan code
                            if (National_code == bank.codem_list[k]) {   //meli az list code meli ha
                                break;
                            }
                        }
                        ofstream log("log.txt", ios::app);
                        log << "Customer " << "(" << bank.get_costomers()[i].get_codeM() << ")"
                            << bank.get_costomers()[i].get_name() << " " <<
                            bank.get_costomers()[i].get_fname() << " has been deleted by " <<
                            "(" << bank.get_Employees()[index].get_id() << ")" <<
                            bank.get_Employees()[index].get_name()
                            << " " << bank.get_Employees()[index].get_fname() << " on : ";
                        time_t my_time = time(NULL);
                        log << ctime(&my_time);
                        log.close();
                        bank.codem_list.erase(bank.codem_list.begin() + k);
                        bank.delete_costomer(i);
                    }
                    system("pause");
                }
            }
        }
        if (opt == 7)
        {
            ofstream log("log.txt", ios::app);
            log << "Employee (" << bank.get_Employees()[index].get_id() << ")"
                << bank.get_Employees()[index].get_name() << " " <<
                bank.get_Employees()[index].get_fname() <<
                " has logged out of the system on : ";
            time_t my_time = time(NULL);
            log << ctime(&my_time);
            log.close();
            break;
        }
    }
}
void menu_cost(bank& bank, int index)
{
    while (true) {
        system("cls");
        cout << "~~~Welcome " << bank.get_costomers()[index].get_name() << " " <<
            bank.get_costomers()[index].get_fname() << "~~~\n";
        cout << "1-Deposit money.\n";
        cout << "2-Withdraw money.\n";
        cout << "3-Apply for a loan.\n";
        cout << "4-Display personal information and then select.\n";
        cout << "5-Exit.\n";
        int opt;
        cin >> opt;
        if (opt == 1)
        {
            system("cls");
            cout << "Enter account number :";
            string account_number;
            cin >> account_number;
            bool not_found = true;
            int i = 0;
            for (i = 0; i < bank.get_costomers()[index].get_Accounts().size(); i++)
            {
                if (bank.get_costomers()[index].get_Accounts()[i].get_account_number() ==
                    account_number)
                {
                    not_found = false;
                    break;
                }
            }
            if (not_found)
            {
                cout << "Account not found"<<endl;
                system("pause");
                //throw
            }
            else {
                // chek kardan active bodan
                    long long int amount;
                    while (true) {
                        cout << "Amount of money :";
                        cin >> amount;
                        if (amount <= 0) {
                            cout << "Error! please enter a valid amount of money!" << endl;
                        }
                        else {
                            break;
                        }
                    }
                    bank.deposit(amount, index,i);
                    cout << amount << " has been deposited to the account with number : ";
                    cout << account_number << endl;
                    ofstream log("log.txt", ios::app);
                    log << "Customer (" << bank.get_costomers()[index].get_codeM() << ")"
                        << bank.get_costomers()[index].get_name()
                        << " " << bank.get_costomers()[index].get_fname() << " has deposited " << amount
                        << " into account (" << account_number << ") on : ";
                    time_t my_time = time(NULL);
                    log << ctime(&my_time);
                    log.close();
                    system("pause");
                    if(!bank.get_costomers()[index].get_Accounts()[i].get_active()){
                        long long int amount_not=0;
                        int s;
                        bool found_loan=false;
                        for(s=0;s<bank.loan_list.size();s++)
                        {
                            if(account_number==bank.loan_list[s].get_account_num())
                            {
                                amount_not= bank.loan_list[s].get_Number_of_overdue_installments()*
                                        bank.loan_list[s].get_Amount_per_installment();
                                found_loan=true;
                                break;
                            }
                        }
                        if(amount_not < bank.get_costomers()[index].get_Accounts()[i].get_bal() && found_loan)
                        {
                            bank.withdraw(amount_not,index,i);
                            for (int r = 0; r < bank.get_costomers()[index].get_Accounts().size(); r++)
                            {
                                bank.active_account(index, r);
                            }
                            ofstream log("log.txt", ios::app);
                            log << "Customer (" << bank.get_costomers()[index].get_codeM() << ")"
                                << bank.get_costomers()[index].get_name()
                                << " " << bank.get_costomers()[index].get_fname()
                                << " has withdrawed " << amount_not
                                << " from account (" << account_number << ") on : ";
                            time_t my_time = time(NULL);
                            log << ctime(&my_time);

                            bank.loan_list[s].pay();
                            log << "Customer (" << bank.get_costomers()[index].get_codeM() << ")"
                                << bank.get_costomers()[index].get_name()
                                << " " << bank.get_costomers()[index].get_fname() <<
                                   " has paid all their debts on : ";
                            log << ctime(&my_time);

                            log << "Customer (" << bank.get_costomers()[index].get_codeM() << ")"
                                << bank.get_costomers()[index].get_name()
                                << " " << bank.get_costomers()[index].get_fname()
                                << "'s accounts have been activated on : ";
                            log << ctime(&my_time);
                        }
                        else if(!found_loan){
                            for (int r = 0; r < bank.get_costomers()[index].get_Accounts().size(); r++)
                            {
                                bank.active_account(index, r);
                            }
                        }
                    }
            }
        }
        if (opt == 2)
        {
            system("cls");
            cout << "Enter account number :";
            string account_number;
            cin >> account_number;
            bool not_found = true;
            int i = 0;
            for (i = 0; i < bank.get_costomers()[index].get_Accounts().size(); i++)
            {
                if (bank.get_costomers()[index].get_Accounts()[i].get_account_number() ==
                    account_number)
                {
                    not_found = false;
                    break;
                }
            }
            if (not_found)
            {
                cout << "Account not found"<<endl;
                system("pause");
            }
            else
            {
                if(bank.get_costomers()[index].get_Accounts()[i].get_active()==true)
                {
                    long long int amount;
                    while (true) {
                        cout << "Amount of money : (0 to abort the operation)";
                        cin >> amount;
                        bool valid = false;
                        bool bal = false;
                        if (amount == 0)
                            break;
                        else if (amount <= 0) {
                            cout << "Error! please enter a valid amount of money!" << endl;
                            valid = true;
                        }
                        else if (amount > bank.get_costomers()[index].get_Accounts()[i].get_bal()) {
                            cout << "Not enough money in account." << endl;
                            bal = true;
                        }
                        if (bal == false && valid == false)
                            break;
                    }
                    bank.withdraw(amount, index,i);
                    cout << amount << " has been withdrawed from the account with number : ";
                    cout << account_number << endl;
                    ofstream log("log.txt", ios::app);
                    log << "Customer (" << bank.get_costomers()[index].get_codeM() << ")"
                        << bank.get_costomers()[index].get_name()
                        << " " << bank.get_costomers()[index].get_fname() << " has withdrawed " << amount
                        << " from account (" << account_number << ") on : ";
                    time_t my_time = time(NULL);
                    log << ctime(&my_time);
                    log.close();
                    system("pause");
                }
                else{
                    cout<<"Account is not active!"<<endl;
                    system("pause");
                }

            }
        }
        if (opt == 3)
        {
            system("cls");
            cout << "Enter account number:\n";
            string acc;
            cin >> acc;
            bool found = true;
            bool has_loan=false;
            bool has_request=false;
            bool is_active=false;
            int i = 0;
            for (i = 0; i < bank.get_costomers()[index].get_Accounts().size(); i++)
            {
                if (bank.get_costomers()[index].get_Accounts()[i].get_account_number() == acc)
                {
                    found = false;
                    break;
                }
            }
            if(bank.get_costomers()[index].get_Accounts()[i].get_active()==true)
                is_active=true;
            for(int j=0;j<bank.loan_list.size();j++){
                if(bank.loan_list[j].get_account_num()==acc){
                    has_loan=true;
                    break;
                }
            }
            for(int z=0;z<bank.loan_requests.size();z++){
                if(bank.loan_requests[z].get_account_num()==acc){
                    has_request=true;
                    break;
                }
            }
            if (found)
            {
                cout << "Account not found"<<endl;
                system("pause");
                //throw
            }
            else if(has_loan){
                cout<<"This account already has a loan!"<<endl;
                system("pause");
            }
            else if(has_request){
                cout<<"This account already did a request for loan"<<endl;
                system("pause");
            }
            else if(!is_active){
                cout<<"This account is not active!"<<endl;
                system("pause");
            }
            else if(bank.get_costomers()[index].get_Accounts()[i].get_dayvam()==0){
                cout<<"Your account doesn't meet the requirements for a loan."<<endl;
                cout<<"Note: to get a loan your account must have 1,000,000 balance for"<<endl;
                cout<<"at least a day."<<endl;
                system("pause");
            }
            else{
                long long int bal = bank.get_costomers()[index].get_Accounts()[i].get_bal();
                int dayvam = bank.get_costomers()[index].get_Accounts()[i].get_dayvam();
                cout << "Account balance : ";
                cout << bal << endl;
                cout << "Maximum loan (" << dayvam << " days) : ";
                long long int max=dayvam*bal;
                cout <<max<<endl;
                long long int loan;
                while(true){
                    cout << "Enter loan amount:\n";
                    cin >> loan;
                    if(loan>max){
                        cout<<"Please enter an amount lower than maximum amount."<<endl;
                    }
                    else{
                        break;
                    }
                }
                Date today;
                cout<<"Enter today's date:(d/m/y)"<<endl;
                string d;
                cin>>d;
                today=Date::str_to_date(d);
                while(true){
                    cout << "Which kind of loan do you want?\n";
                    cout << "1. 12 months (%4 interest)\n";
                    cout << "2. 24 months (%8 interest)\n";
                    cout << "3. 36 months (%12 interest)\n";
                    cout<<"4. Exit.\n";
                    int ans;
                    cin >> ans;
                    string account_number=bank.get_costomers()[index].
                            get_Accounts()[i].get_account_number();
                    if(ans==1){
                        string serial=serial_generator(bank);
                        Facilities f(account_number,today,loan,4,12,serial,0,0);
                        bank.loan_requests.push_back(f);
                        cout<<"Your loan request has been submitted."<<endl;
                        cout<<"You will get the loan after facility manager's approval."<<endl;
                        cout<<"Serial number:"<<serial<<endl;
                        system("pause");
                        ofstream log("log.txt", ios::app);
                        log << "Customer (" << bank.get_costomers()[index].get_codeM() << ")"
                            << bank.get_costomers()[index].get_name() << " " <<
                            bank.get_costomers()[index].get_fname() <<
                            " has requested a loan("<<serial<<") on : ";
                        time_t my_time = time(NULL);
                        log << ctime(&my_time);
                        log.close();
                        break;
                    }
                    else if(ans==2){
                        string serial=serial_generator(bank);
                        Facilities f(account_number,today,loan,8,24,serial,0,0);
                        bank.loan_requests.push_back(f);
                        cout<<"Your loan request has been submitted."<<endl;
                        cout<<"You will get the loan after facility manager's approval."<<endl;
                        cout<<"Serial number:"<<serial<<endl;
                        system("pause");
                        ofstream log("log.txt", ios::app);
                        log << "Customer (" << bank.get_costomers()[index].get_codeM() << ")"
                            << bank.get_costomers()[index].get_name() << " " <<
                            bank.get_costomers()[index].get_fname() <<
                            " has requested a loan("<<serial<<") on : ";
                        time_t my_time = time(NULL);
                        log << ctime(&my_time);
                        log.close();
                        break;
                    }
                    else if(ans==3){
                        string serial=serial_generator(bank);
                        Facilities f(account_number,today,loan,12,36,serial,0,0);
                        bank.loan_requests.push_back(f);
                        cout<<"Your loan request has been submitted."<<endl;
                        cout<<"You will get the loan after facility manager's approval."<<endl;
                        cout<<"Serial number:"<<serial<<endl;
                        system("pause");
                        ofstream log("log.txt", ios::app);
                        log << "Customer (" << bank.get_costomers()[index].get_codeM() << ")"
                            << bank.get_costomers()[index].get_name() << " " <<
                            bank.get_costomers()[index].get_fname() <<
                            " has requested a loan("<<serial<<") on : ";
                        time_t my_time = time(NULL);
                        log << ctime(&my_time);
                        log.close();
                        break;
                    }
                    else if(ans==4){
                        break;
                    }
                }
            }

        }
        if (opt == 4)
        {
            system("cls");
            bank.get_costomers()[index].View_all_information();
            cout << "\n1. Show all accounts." << endl;
            cout << "2. Show all loans." << endl;
            int ans;
            cin >> ans;
            if (ans == 1) {
                for (int j = 0; j < bank.get_costomers()[index].get_Accounts().size(); j++) {
                    if (bank.get_costomers()[index].get_Accounts()[j].get_active() == true) {
                        cout << j + 1 << ". (ACTIVE) ";
                        bank.get_costomers()[index].get_Accounts()[j].show_baseinfo();
                    }
                    else {
                        cout << j + 1 << ". (DEACTIVE) ";
                        bank.get_costomers()[index].get_Accounts()[j].show_baseinfo();
                    }

                }
                system("pause");
            }
            if(ans==2){
                cout<<"Enter account number:"<<endl;
                for(int i=0;i<bank.get_costomers()[index].get_Accounts().size();i++){
                    cout<<bank.get_costomers()[index].get_Accounts()[i].get_account_number()<<endl;
                }
                string accnum;
                cin>>accnum;
                bool found=false;
                for(int i=0;i<bank.get_costomers()[index].get_Accounts().size();i++){
                    if(accnum==bank.get_costomers()[index].get_Accounts()[i].get_account_number()){
                        found=true;
                        break;
                    }
                }
                if(found==true){
                    bool found1=false;
                    for(int i=0;i<bank.loan_list.size();i++){
                        if(bank.loan_list[i].get_account_num()==accnum){
                            bank.loan_list[i].display_info();
                            found1=true;
                            break;
                        }
                    }
                    if(!found1){
                        cout<<"No loans associated with this account was found!"<<endl;
                    }
                    system("pause");
                }
                else{
                    cout<<"Not found!"<<endl;
                    system("pause");
                }
            }
        }
        if (opt == 5)
        {
            ofstream log("log.txt", ios::app);
            log << "Customer (" << bank.get_costomers()[index].get_codeM() << ")"
                << bank.get_costomers()[index].get_name() << " " <<
                bank.get_costomers()[index].get_fname() <<
                " has logged out of the system on : ";
            time_t my_time = time(NULL);
            log << ctime(&my_time);
            log.close();
            break;
        }
    }
}

