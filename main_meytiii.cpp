#include <iostream>
#include <vector>
#include <string>
#include <Date.h>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

class bank;

//menu
void menu(bank &);
void menu_man(bank &);
void menu_fman(bank &);
void menu_Employee(bank &,int);
void menu_cost(bank &,int);
//save to file
void write_employee(bank &b);
void read_employee(bank &b);
void write_customer(bank &b);
void read_customer(bank &b);
void write_account(bank &b);
void read_account(bank &b);

class Account
{
public:
    Account(){}
    Account(string n, string c, Date o, long long int bal){
        day_vam=0;
        Account_active=true;
        account_number=n;
        owner_codem=c;
        Balance=bal;
        Opening_date=o;
    }
    Account(string n, string c, Date o, long long int bal, bool active, int day){
        day_vam=day;
        Account_active=active;
        account_number=n;
        owner_codem=c;
        Balance=bal;
        Opening_date=o;
    }
    void Check_account_balance()
    {
        if(Balance>=1000000)
        {
            day_vam++;
        }
    }
    long long int Facilities()
    {
        return Balance*day_vam;
    }
    void Account_increase(long amount)
    {
        Balance+=amount;
    }
    void Account_reduction(long amount)
    {
        //if Balance<0
        Balance-=amount;
    }
    bool get_active(){return Account_active;}
    void active_account(){
        this->Account_active=true;
    }
    void deactive_account(){
        this->Account_active=false;
    }
    string get_account_number(){return account_number;}
    string get_codem(){return owner_codem;}
    Date get_opening_date(){return Opening_date;}
    long long int get_bal(){return Balance;}
    int get_dayvam(){return day_vam;}
    void show_baseinfo(){
        cout<<"Account number: "<<account_number<<", Balance: "<<Balance<<endl;
    }
    void show_all(){

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
    human(){}
    human(string n,string f,Date b,string u, string p){
        name=n;
        family=f;
        birthdate=b;
        username=u;
        password=p;
    }
    ~human(){}
    virtual void View_all_information()
       {
           cout<<"name :"<<name<<endl;
           cout<<"family :"<<family<<endl;
           cout<<"birthdate :"<<birthdate.get_year()<<"/"<<birthdate.get_month()<<"/"<<birthdate.get_day()<<endl;
           cout<<"username :"<<username<<endl;
           cout<<"password :"<<password<<endl;
       }
    string get_user (){return username;}
    string get_pass (){return password;}
    string get_name(){return name;}
    string get_fname(){return family;}
    Date get_bday(){return birthdate;}

private:
    string name;
    string family;
    Date birthdate;
    string username;
    string password;
};

class costomer:public human
{
public:
    costomer(){}
    costomer(string n,string f,Date b,string u, string p, string c):human(n,f,b,u,p){
        codeM=c;
    }
    ~costomer(){}
    virtual void View_all_information()
    {
        human::View_all_information();
        cout<<"codeM :"<<codeM<<endl;
    }
    void withdraw(){
        cout<<"Enter account number:\n";
    }
    void add_account(Account a){
        Accounts.push_back(a);
    }
    void del_account(int p){   //delete an account by position
        Accounts.erase(Accounts.begin()+p);
    }
    void active_account(int j){
        Accounts[j].active_account();
    }
    void deactive_account(int j){
        Accounts[j].deactive_account();
    }
    void deposit(long bal,int i){
        Accounts[i].Account_increase(bal);
    }
    void withdraw(long bal,int i){
        Accounts[i].Account_reduction(bal);
    }
    void set_account(vector<Account> a){
        Accounts=a;
    }
    vector <Account> get_Accounts(){return Accounts;}
    string get_codeM(){return codeM;}
private:
    string codeM;
    vector <Account> Accounts;
};
class Facilities
{
public:
    void amount_per_installment()
    {
        Amount_per_installment=( (Loan_amount*(loan_interest+100))/100 )/Total_number_of_installments;
    }
    void loan_payments()
    {
        Connected_account.Account_reduction(Amount_per_installment);
    }
private:
    string Connected_account_number;
    Account Connected_account;
    Date Date_received;
    int Loan_amount;
    int loan_interest;
    int Total_number_of_installments;
    int Amount_per_installment;
    int Number_of_installments_paid;
    int Number_of_overdue_installments;
    string Serial_number;
};
class Employee:public human
{
public:
    Employee(){
        Vacation_hours=0;
        Overtime_hours=0;
    }
    Employee(string n,string f,Date b,string u, string p, int id, long s):human(n,f,b,u,p){
        Vacation_hours=0;
        Overtime_hours=0;
        personnel_id=id;
        base_salary=s;
    }
    ~Employee(){}
    int get_Vacation_hours(){return  Vacation_hours;}
    int get_Overtime_hours(){return  Overtime_hours;}
    void Request_for_leave(int H)
    {
        Vacation_hours+=H;
    }
    void Request_for_overtime(int H){
        Overtime_hours+=H;
    }
    long get_salary(){return base_salary;}
    int get_id(){return personnel_id;}
    virtual void View_all_information()
    {
        human::View_all_information();
        cout<<"base_salary :"<<base_salary<<endl;
        cout<<"Vacation_hours :"<<Vacation_hours<<endl;
        cout<<"Overtime_hours :"<<Overtime_hours<<endl;
        cout<<"Personnel_ID :"<<personnel_id<<endl;
    }
private:
    int personnel_id;
    long base_salary;
    int Vacation_hours;
    int Overtime_hours;
};

class manager:public Employee{
    public:
    manager(){}
    manager(string n,string f,Date b,string u, string p, int id, long s)
        :Employee(n,f,b,u,p,id,s){}
    ~manager(){}

};

class facility_manager:public Employee{
    public:
    facility_manager(){}
    facility_manager(string n,string f,Date b,string u, string p, int id, long s)
        :Employee(n,f,b,u,p,id,s){}
    ~facility_manager(){}
};

class bank{
public:
    bank(){}
    bank(string b,string c,manager m, facility_manager fm){
        branch_name=b;
        branch_code=c;
        modir=m;
        facility_modir=fm;
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
    void add_vacation(int h,int i){   //i=-1 manager, i=-2 facility manager
        if(i==-1)
            modir.Request_for_leave(h);
        else if(i==-2)
            modir.Request_for_leave(h);
        else
            employee_list[i].Request_for_leave(h);
    }
    void add_overtime(int h,int i){    //i=-1 manager, i=-2 facility manager
        if(i==-1)
            modir.Request_for_overtime(h);
        else if(i==-2)
            modir.Request_for_overtime(h);
        else
            employee_list[i].Request_for_overtime(h);
    }
    void add_account(Account a,int i){
        customer_list[i].add_account(a);
    }

    //settings things

    void set_branchname(string n){
        branch_name=n;
    }
    void set_branchcode(string c){
        branch_code=c;
    }
    void set_modir(manager c)
    {
        modir=c;
    }
    void set_facility_manager(facility_manager c)
    {
       facility_modir=c;
    }
    void set_customers(vector<costomer> c){
        customer_list=c;
    }
    void set_employees(vector<Employee> e){
        employee_list=e;
    }

    //deleting things

    void delete_costomer(int i)
    {
        customer_list.erase(customer_list.begin()+i);
    }
    void delete_employee(int i)
    {
        employee_list.erase(employee_list.begin()+i);
    }
    void delete_account(int i,int j){
        customer_list[i].del_account(j);
    }
    void active_account(int i,int j){
        customer_list[i].active_account(j);
    }
    void deactive_account(int i,int j){
        customer_list[i].deactive_account(j);
    }
    void deposit(long m,int i){
        customer_list[i].deposit(m,i);
    }
    void withdraw(long m,int i){
        customer_list[i].withdraw(m,i);
    }

    //gettings things

    string get_branchname(){return branch_name;}
    string get_branchcode(){return branch_code;}
    vector<costomer> get_costomers(){return  customer_list;}
    vector<Employee> get_Employees(){return  employee_list;}
    manager get_man(){return  modir;}
    facility_manager get_fman(){return  facility_modir;}

    //lists

    vector<int> personnelid_list;
    vector<string> account_num_list;
    vector<string> codem_list;
    vector<Facilities> loan_list;

private:

    vector<Employee> employee_list;
    vector<costomer> customer_list;
    string branch_name;
    string branch_code;
    manager modir;
    facility_manager facility_modir;

};

int main()
{
    int day;
    string days;
    ifstream day_input("dayvam.txt");
    getline(day_input,days);
    day_input.close();
    day=stoi(days);
    day++;
    ofstream day_output("dayvam.txt");
    day_output<<day;
    day_output.close();
    ofstream logday("log.txt",ios::app);
    logday<<"~Day "<<day<<":";
    logday<<"\n";
    logday.close();

    Date bd1(22,5,1379);
    Date bd2(12,5,1390);
    Date bd3(7,5,1390);
    manager m("eisa","nikahd",bd1,"lms","lms",111,1000000);
    facility_manager fm("taha","zoli",bd2,"lms2","lms2",222,500000);
    costomer c("mehdi","khoram",bd3,"lms3","lms3","1234");
    Account a("123456","1234",bd1,50000);
    vector<Account> as;
    Employee e("mmd","taghi",bd3,"lms4","lms4",333,2000000);
    bank b("ShahidRajaee","44",m,fm);
    as.push_back(a);
    c.set_account(as);
    b.add_costomer(c);
    b.add_employee(e);
    b.personnelid_list.push_back(111);
    b.personnelid_list.push_back(222);
    b.personnelid_list.push_back(333);
    b.codem_list.push_back("1234");
    b.account_num_list.push_back("123456");
    system("pause");
    menu(b);
//    write_employee(b);
//    read_employee(b);
    write_customer(b);
//    read_customer(b);
    write_account(b);
    read_account(b);

    return 0;
}

void write_employee(bank &b){
    cout<<"WRITING EMPLOYEES"<<endl;
    vector<Employee> e=b.get_Employees();
    size_t size=e.size();
    ofstream w("employee-size.ros",ios::binary);
    w.write(reinterpret_cast<char *>(&size), sizeof(size_t));
    w.close();
    ofstream w2("employee.ros",ios::binary);
    w2.write(reinterpret_cast<char *>(&e[0]), sizeof(Employee) * e.size());
    w2.close();
}

void read_employee(bank &b){
    cout<<"READING EMPLOYEES"<<endl;
    size_t size;
    ifstream ifs("employee-size.ros",ios::binary);
    ifs.read( reinterpret_cast<char *>(&size), sizeof(size_t));
    ifs.close();
    vector<Employee> e(size);
    ifstream ifs2("employee.ros", ios::binary);
    ifs2.read( reinterpret_cast<char *>(&e[0]), sizeof(Employee) * e.size() );
    ifs2.close();
    for(int i=0;i<e.size();i++){
        cout<<"NAME:"<<e[i].get_name()<<" "<<e[i].get_name()<<endl;
    }
}

void write_customer(bank &b){
    cout<<"WRITING CUSTOMERS"<<endl;
    vector<costomer> c_list=b.get_costomers();
    size_t customer_size=c_list.size();
    ofstream w("customer-size.ros",ios::binary);
    w.write(reinterpret_cast<char *>(&customer_size), sizeof(customer_size));
    w.close();
    for(int i=0;i<customer_size;i++){
        string name=c_list[i].get_name();
        string fname=c_list[i].get_fname();
        string codemeli=c_list[i].get_codeM();
        string username=c_list[i].get_user();
        string password=c_list[i].get_pass();
        Date bday=c_list[i].get_bday();
        ofstream w("customer"+to_string(i)+".ros",ios::binary);
        //writing name
        size_t name_size=name.size();
        w.write(reinterpret_cast<char *>(&name_size), sizeof(size_t));
        w.write(name.c_str(),name_size);
        //writing national code
        size_t codemeli_size=codemeli.size();
        w.write(reinterpret_cast<char *>(&codemeli_size), sizeof(size_t));
        w.write(codemeli.c_str(),codemeli_size);
        //writing family name
        size_t fname_size=fname.size();
        w.write(reinterpret_cast<char *>(&fname_size), sizeof(size_t));
        w.write(fname.c_str(),fname_size);
        //writing username
        size_t username_size=username.size();
        w.write(reinterpret_cast<char *>(&username_size), sizeof(size_t));
        w.write(username.c_str(),username_size);
        //writing password
        size_t password_size=password.size();
        w.write(reinterpret_cast<char *>(&password_size), sizeof(size_t));
        w.write(password.c_str(),password_size);
        //writing birthday
        w.write(reinterpret_cast<char *>(&bday), sizeof(Date));
        w.flush();
        w.close();
    }
}

void read_customer(bank &b){
    cout<<"READING CUSTOMERS"<<endl;
    vector<costomer> c_list;
    size_t customer_size;
    ifstream r("customer-size.ros",ios::binary);
    r.read(reinterpret_cast<char *>(&customer_size), sizeof(customer_size));
    r.close();
    for(int i=0;i<customer_size;i++){
        char *buf;
        string codemeli;
        string fname;
        string name;
        string username;
        string password;
        Date bday;
        ifstream r("customer"+to_string(i)+".ros",ios::binary);
        //reading name
        size_t name_size=0;
        r.read(reinterpret_cast<char *>(&name_size), sizeof(size_t));
        buf=new char[name_size];
        r.read(buf,name_size);
        name="";
        name.append(buf,name_size);
        delete buf;
        //reading national code
        size_t codemeli_size=0;
        r.read(reinterpret_cast<char *>(&codemeli_size), sizeof(size_t));
        buf=new char[codemeli_size];
        r.read(buf,codemeli_size);
        codemeli="";
        codemeli.append(buf,codemeli_size);
        delete buf;
        //reading family name
        size_t fname_size=0;
        r.read(reinterpret_cast<char *>(&fname_size), sizeof(size_t));
        buf=new char[fname_size];
        r.read(buf,fname_size);
        fname="";
        fname.append(buf,fname_size);
        delete buf;
        //reading username
        size_t username_size=0;
        r.read(reinterpret_cast<char *>(&username_size), sizeof(size_t));
        buf=new char[username_size];
        r.read(buf,username_size);
        username="";
        username.append(buf,username_size);
        delete buf;
        //reading password
        size_t password_size=0;
        r.read(reinterpret_cast<char *>(&password_size), sizeof(size_t));
        buf=new char[password_size];
        r.read(buf,password_size);
        password="";
        password.append(buf,password_size);
        delete buf;
        //reading birthdate
        r.read(reinterpret_cast<char *>(&bday), sizeof(Date));
        r.close();
        cout<<"DETAILS:"<<endl;
        costomer c(name,fname,bday,username,password,codemeli);
//        c.set_account(a_list);
//        c_list.push_back(c);
        c.View_all_information();
    }
//    b.set_customers(c_list);
}

void write_account(bank &b){
    cout<<"WRITING ACCOUNTS"<<endl;
    vector<Account> a_list;
    size_t customer_size=b.get_costomers().size();
    for(int i=0;i<customer_size;i++){
        a_list=b.get_costomers()[i].get_Accounts();
        size_t size_a=a_list.size();
        ofstream w("account-size"+to_string(i)+".ros",ios::binary);
        w.write(reinterpret_cast<char *>(&size_a), sizeof(size_t));
        w.close();
        for(int j=0;j<a_list.size();j++){
            string num=a_list[j].get_account_number();
            string codem=a_list[j].get_codem();
            Date o=a_list[j].get_opening_date();
            long long int bal=a_list[j].get_bal();
            int day_vam=a_list[j].get_dayvam();
            bool active=a_list[j].get_active();
            ofstream w2("account"+to_string(i)+"."+to_string(j)+".ros",ios::binary);
            //writing account number
            size_t num_size=num.size();
            w2.write(reinterpret_cast<char *>(&num_size), sizeof(size_t));
            w2.write(num.c_str(),num_size);
            //writing owner's national code
            size_t codem_size=codem.size();
            w2.write(reinterpret_cast<char *>(&codem_size), sizeof(size_t));
            w2.write(codem.c_str(),codem_size);
            //writing opening date
            w2.write(reinterpret_cast<char *>(&o), sizeof(Date));
            //writing balance
            w2.write(reinterpret_cast<char *>(&bal), sizeof(long long int));
            //writing day vam
            w2.write(reinterpret_cast<char *>(&day_vam), sizeof(int));
            //writing account active
            w2.write(reinterpret_cast<char *>(&active), sizeof(bool));
            w2.flush();
            w2.close();
            a_list[j].show_baseinfo();
        }
    }
}

void read_account(bank &b){
    cout<<"READING ACCOUNTS"<<endl;
    vector<Account> a_list;
    size_t customer_size;
    ifstream r("customer-size.ros",ios::binary);
    r.read(reinterpret_cast<char *>(&customer_size), sizeof(size_t));
    r.close();
    for(int i=0;i<customer_size;i++){
        size_t account_size;
        ifstream r2("account-size"+to_string(i)+".ros",ios::binary);
        r2.read(reinterpret_cast<char *>(&account_size), sizeof(size_t));
        for(int j=0;j<account_size;j++){
            char *buf;
            string num;
            string codem;
            Date o;
            long long int bal;
            int day_vam;
            bool active;
            ifstream r3("account"+to_string(i)+"."+to_string(j)+".ros",ios::binary);
            //reading account number
            size_t num_size=0;
            r3.read(reinterpret_cast<char *>(&num_size), sizeof(size_t));
            buf=new char[num_size];
            r3.read(buf,num_size);
            num="";
            num.append(buf,num_size);
            delete buf;
            //reading national code
            size_t codem_size=0;
            r3.read(reinterpret_cast<char *>(&codem_size), sizeof(size_t));
            buf=new char[codem_size];
            r3.read(buf,codem_size);
            codem="";
            codem.append(buf,codem_size);
            delete buf;
            //reading date
            r3.read(reinterpret_cast<char *>(&o), sizeof(Date));
            //reading balance
            r3.read(reinterpret_cast<char *>(&bal), sizeof(long long int));
            //reading day vam
            r3.read(reinterpret_cast<char *>(&day_vam), sizeof(int));
            //reading account active
            r3.read(reinterpret_cast<char *>(&active), sizeof(bool));
            r3.close();
            //Account(string n, string c, Date o, long long int bal)
            Account a(num,codem,o,bal,active,day_vam);
            a.show_baseinfo();
        }
    }
}
//string account_number;
//string owner_codem;
//Date Opening_date;
//long long int Balance;
//int day_vam;
//bool Account_active;
void menu(bank &bank)
{
    while (true)
    {
        system("cls");
        cout<<"~~~~~welcome~~~~~\n";
        cout<<"1) Employee.\n";
        cout<<"2) Customer.\n";
        cout<<"3) Exit.\n";
        int opt;
        cin>>opt;
        if(opt==1)
        {
            system("cls");
            cout<<"enter username: ";
            string us;
            cin>>us;
            cout<<"enter password: ";
            string pass;
            cin>>pass;
            bool flagm=false;
            bool flagfm=false;
            bool flage=false;
            int i=0;
            if(bank.get_man().get_pass()==pass && bank.get_man().get_user()==us)
                flagm=true;
            else if(bank.get_fman().get_user()==us && bank.get_fman().get_pass()==pass)
                flagfm=true;
            else
            {
                for(i=0;i<bank.get_Employees().size();i++)
                {
                    if(bank.get_Employees()[i].get_user()==us &&
                            bank.get_Employees()[i].get_pass()==pass )
                    {
                        flage=true;
                        break;
                    }
                }
            }
          if(flagm)
          {
              cout<<"Successfully logged in as manager!\n";
              ofstream log("log.txt",ios::app);
              log<<"Manager ("<<bank.get_man().get_id()<<")"
                <<bank.get_man().get_name()<<" "<<
                   bank.get_man().get_fname()<<
                   " has logged in the system on : ";
              time_t my_time = time(NULL);
              log<<ctime(&my_time);
              log.close();
              system("pause");
              menu_man(bank);
          }
          else if(flagfm)
          {
              cout<<"Successfully logged in as facility manager!\n";
              ofstream log("log.txt",ios::app);
              log<<"Facility manager ("<<bank.get_fman().get_id()<<")"
                <<bank.get_fman().get_name()<<" "<<
                   bank.get_fman().get_fname()<<
                   " has logged in the system on : ";
              time_t my_time = time(NULL);
              log<<ctime(&my_time);
              log.close();
              system("pause");
              menu_fman(bank);
          }
          else if (flage)
          {
              cout<<"Successfully logged in as employee!\n";
              ofstream log("log.txt",ios::app);
              log<<"Employee ("<<bank.get_Employees()[i].get_id()<<")"
                <<bank.get_Employees()[i].get_name()<<" "<<
                   bank.get_Employees()[i].get_fname()<<
                   " has logged in the system on : ";
              time_t my_time = time(NULL);
              log<<ctime(&my_time);
              log.close();
              system("pause");
              menu_Employee(bank,i);
          }
          else
          {
              cout<<"username or password Invalid :(\n";
              system("pause");
          }
        }
        if(opt==2)
        {
            system("cls");
            cout<<"enter username: ";
            string us;
            cin>>us;
            cout<<"enter password: ";
            string pass;
            cin>>pass;
            bool flag=false;
            int i;
            for(i=0;i<bank.get_costomers().size();i++)
            {
                if(bank.get_costomers()[i].get_pass()==pass && bank.get_costomers()[i].get_user()==us)
                {
                    flag =true;
                    break;
                }
            }
            if(flag)
            {
                cout<<"Successfully logged in as customer!\n";
                ofstream log("log.txt",ios::app);
                log<<"Customer ("<<bank.get_costomers()[i].get_codeM()<<")"
                  <<bank.get_costomers()[i].get_name()<<" "<<
                     bank.get_costomers()[i].get_fname()<<
                     " has logged in the system on : ";
                time_t my_time = time(NULL);
                log<<ctime(&my_time);
                log.close();
                menu_cost(bank,i);
            }
            else
            {
                cout<<"username or password Invalid :(\n";
                system("pause");
            }

        }
        if(opt==3)
        {
            cout<<"Good bye!"<<endl;     //karaye file va save va rooz
            break;
        }
    }
}
void menu_man(bank &bank)
{
    while(true){
    system("cls");
    cout<<"~~~Welcome "<<bank.get_man().get_name()<<" "
       <<bank.get_man().get_fname()<<"~~~\n";
    cout<<"1-Request for leave.\n";
    cout<<"2-Request for overtime.\n";
    cout<<"3-Display personal information.\n";
    cout<<"4-View complete customer information using a national number.\n";
    cout<<"5-Create an account for a customer.\n";
    cout<<"6-Delete a customer's account.\n";
    cout<<"7-Show an employee's information.\n";
    cout<<"8-Hire a new employee.\n";
    cout<<"9-Fire an employee.\n";
    cout<<"10-Exit.\n";
    int opt;
    cin>>opt;
    if(opt==1)
    {
         system("cls");
         cout<<"Hours of vacation taken this month :"<<
               bank.get_man().get_Vacation_hours()<<endl;
         int max=bank.get_man().get_salary()/100000;
         int current=bank.get_man().get_Vacation_hours();
         max=15-current+max;
         while(true){
             cout<<"Maximum hours you can take this month: "<<max<<endl;
             cout<<"(Enter 0 to cancel the operation.)"<<endl;
             int hour;
             cin>>hour;
             if(hour==0)
                 break;
             if(hour>max || hour<0){
                 cout<<"Invalid hour!\n";
             }
             else{
                 bank.add_vacation(hour,-1);
                 cout<<"You got "<<hour<<" hours for vacation.Have fun!\n";
                 ofstream log("log.txt",ios::app);
                 log<<"Manager ("<<bank.get_man().get_id()<<")"
                   <<bank.get_man().get_name()<<" "<<
                      bank.get_man().get_fname()<<
                      " has taken "<<hour<<" hours vacation "<<"on : ";
                 time_t my_time = time(NULL);
                 log<<ctime(&my_time);
                 log.close();
                 system("pause");
                 break;
             }
         }
    }
    if(opt==2)
    {
        system("cls");
        cout<<"Overtime hours taken this month :"<<
              bank.get_man().get_Overtime_hours()<<endl;
        while(true){
            cout<<"Allowed hours for overtime :"<<12-bank.get_man().get_Overtime_hours()<<endl;
            cout<<"(Enter 0 to cancel the operation.)"<<endl;
            int hour;
            cin>>hour;
            if(hour==0)
                break;
            if(hour<0 || hour>(12-bank.get_man().get_Overtime_hours()))
            {
                cout<<"Invalid hour!\n";
            }
            else
            {
                bank.add_overtime(hour,-1);
                cout<<"You got "<<hour<<" hours for overtime.Have fun!\n";
                ofstream log("log.txt",ios::app);
                log<<"Manager ("<<bank.get_man().get_id()<<")"
                  <<bank.get_man().get_name()<<" "<<
                     bank.get_man().get_fname()<<
                     " has taken "<<hour<<" hours overtime "<<"on : ";
                time_t my_time = time(NULL);
                log<<ctime(&my_time);
                log.close();
                system("pause");
                break;
            }
        }
    }
    if(opt==3)
    {
        system("cls");
        cout<<"Bank manager:"<<endl;
        bank.get_man().View_all_information();
        system("pause");
    }
    if(opt==4)
    {
        system("cls");
        cout<<"Customer National Number :";
        string National_code;
        cin>>National_code;
        int i=0;
        bool flag=true;
        for(;i<bank.get_costomers().size();i++)
        {
            if(National_code==bank.get_costomers()[i].get_codeM())
            {
                flag=false;
                break;
            }
        }
        if(flag){
            cout<<"Not found!"<<endl;
            system("pause");
        }
        else{
            bank.get_costomers()[i].View_all_information();
            for(int j=0;j<bank.get_costomers()[i].get_Accounts().size();j++){
                if(bank.get_costomers()[i].get_Accounts()[j].get_active()==true){
                    cout<<j+1<<". (ACTIVE) ";
                    bank.get_costomers()[i].get_Accounts()[j].show_baseinfo();
                }
                else{
                    cout<<j+1<<". (DEACTIVE) ";
                    bank.get_costomers()[i].get_Accounts()[j].show_baseinfo();
                }

            }
            system("pause");
        }
    }
    if(opt==5)
    {
        system("cls");
        cout<<"Is it a person's first account ?\n"<<endl;
        cout<<"1)Yes\n";
        cout<<"2)NO\n";
        int x;
        cin>>x;
        if(x==1)
        {
            string name;
            string family;
            string codeM;
            Date birthdate;
            string username;
            string password;
            string bday;
            cout<<"~~~~ Create a new customer ~~~~~"<<endl;
            cout<<"name: ";cin>>name;
            cout<<"family name: ";cin>>family;
            while(true){
                cout<<"National code: ";cin>>codeM;
                bool flagcode=false;
                bool digit=false;
                if(codeM.size()!=11){
                    cout<<"National code must be 11 digits."<<endl;
                    digit=true;
                }
                for(int k=0;k<bank.codem_list.size();k++){
                    if(codeM==bank.codem_list[k]){
                        flagcode=true;
                        cout<<"This national code already exists."<<endl;
                    }
                }
                if(flagcode==false && digit==false){
                    break;
                }

            }

            cout<<"Birthday (d/m/y):";cin>>bday;
            cout<<"BDAY : "<<bday<<endl;
            birthdate=Date::str_to_date(bday);
            cout<<"username: ";cin>>username;
            cout<<"password: ";cin>>password;
            costomer new_c(name,family,birthdate,username,password,codeM);
            ofstream log("log.txt",ios::app);
            log<<"Customer "<<"("<<codeM<<")"<<name<<" "<<family<<" has been added by "<<
                 "("<<bank.get_man().get_id()<<")"<<
                  bank.get_man().get_name()<<" "<<bank.get_man().get_fname()<<" on : ";
            time_t my_time = time(NULL);
            log<<ctime(&my_time);
            log.close();
            cout<<"Enter amount of money(50,000 minimum): "<<endl;
            long long int m;
            cin>>m;
            while(true){
                if(m<50000){
                    cout<<"Not enough money, Enter another amount."<<endl;
                    cin>>m;
                }
                else
                    break;
            }
            string num;
            while(true){
                cout<<"Enter account number: (6 digits)"<<endl;
                bool rep=false;
                bool digit=false;
                cin>>num;         //bayad check shavad.
                if(num.size()!=6){
                    digit=true;
                    cout<<"Invalid number, it must be 6 digits and unique."<<endl;
                }
                for(int z=0;z<bank.account_num_list.size();z++){
                    if(num==bank.account_num_list[z]){
                        rep=true;
                        cout<<"This number already exists. Try again!"<<endl;
                    }
                }
                if(rep==false && digit==false){
                    cout<<"This number is fine."<<endl;
                    break;
                }
            }
            bank.account_num_list.push_back(num);
            cout<<"Enter today's date: "<<endl;
            string d;
            cin>>d;
            Date o;
            o.str_to_date(d);
            Account a(num,codeM,o,m);
            new_c.add_account(a);
            cout<<"Account has been created!"<<endl;
            ofstream log2("log.txt",ios::app);
            log2<<"Account "<<num<<" has been created by "<<"("<<bank.get_man().get_id()<<")"<<
                  bank.get_man().get_name()<<" "<<bank.get_man().get_fname()<<" on : ";
            log2<<ctime(&my_time);
            log2.close();
            a.show_baseinfo();
            bank.add_costomer(new_c);
            system("pause");
        }
        if(x==2)
        {
          cout<<"Customer's National Code :";
          string National_code;
          cin>>National_code;
          int i=0;
          bool flag=true;
          for(;i<bank.get_costomers().size();i++)
          {
              if(National_code==bank.get_costomers()[i].get_codeM())
              {
                  flag=false;
                  break;
              }
          }
          if(flag){
              cout<<"Not found!"<<endl;
              system("pause");
          }
          else{
              cout<<"Enter amount of money(50,000 minimum): "<<endl;
              long long int m;
              cin>>m;
              while(true){
                  if(m<50000){
                      cout<<"Not enough money, Enter another amount."<<endl;
                      cin>>m;
                  }
                  else
                      break;
              }
              string num;
              while(true){
                  cout<<"Enter account number: (6 digits)"<<endl;
                  bool rep=false;
                  bool digit=false;
                  cin>>num;         //bayad check shavad.
                  if(num.size()!=6){
                      digit=true;
                      cout<<"Invalid number, it must be 6 digits and unique."<<endl;
                  }
                  for(int z=0;z<bank.account_num_list.size();z++){
                      if(num==bank.account_num_list[z]){
                          rep=true;
                          cout<<"This number already exists. Try again!"<<endl;
                      }
                  }
                  if(rep==false && digit==false){
                      cout<<"This number is fine."<<endl;
                      break;
                  }
               }
              bank.account_num_list.push_back(num);
              cout<<"Enter today's date: "<<endl;
              string d;
              cin>>d;
              Date o;
              o.str_to_date(d);
              string codeM=bank.get_costomers()[i].get_codeM();
              Account a(num,codeM,o,m);
              bank.add_account(a,i);
              cout<<"Account has been created!"<<endl;
              ofstream log2("log.txt",ios::app);
              log2<<"Account "<<num<<" has been created by "<<"("<<bank.get_man().get_id()<<")"<<
                    bank.get_man().get_name()<<" "<<bank.get_man().get_fname()<<" on : ";
              time_t my_time = time(NULL);
              log2<<ctime(&my_time);
              log2.close();
              a.show_baseinfo();
              system("pause");
          }
        }
    }
    if(opt==6)
    {
       system("cls");
       cout<<"Customer National Code :";
       string National_code;
       cin>>National_code;
       int i=0;
       bool flag=true;
       for(;i<bank.get_costomers().size();i++)
       {
           if(National_code==bank.get_costomers()[i].get_codeM())
           {
               flag=false;
               break;
           }
       }
       if(flag){
           cout<<"Customer not found!"<<endl;
           system("pause");
       }
       else{
           cout<<"Enter the customer's account number :";
           string account_number;
           cin>>account_number;
           bool flag2=true;
           int j=0;
           for(j=0;j<bank.get_costomers()[i].get_Accounts().size();j++)
           {
               if(bank.get_costomers()[i].get_Accounts()[j].get_account_number()==account_number)
               {
                   flag2=false;
                   break;
               }
           }
           if(flag2){
               cout<<"Account not found!"<<endl;
               system("pause");
           }
           else{
               int k=0;
               for(k=0;k<bank.account_num_list.size();k++){
                   if(bank.account_num_list[k]==account_number){
                       break;
                   }
               }
               bank.account_num_list.erase(bank.account_num_list.begin()+k);
               bank.delete_account(i,j);
               cout<<"Account has been deleted!"<<endl;
               ofstream log2("log.txt",ios::app);
               log2<<"Account "<<account_number<<" has been deleted by "<<
                     "("<<bank.get_man().get_id()<<")"<<
                     bank.get_man().get_name()<<" "<<bank.get_man().get_fname()<<" on : ";
               time_t my_time = time(NULL);
               log2<<ctime(&my_time);
               log2.close();
               if(bank.get_costomers()[i].get_Accounts().size()==0){
                   cout<<"This customer has no accounts. Deleting the customer..."<<endl;
                   int k=0;
                   for(k=0;k<bank.codem_list.size();k++){  //baraye delete kardan code
                       if(National_code==bank.codem_list[k]){   //meli az list code meli ha
                           break;
                       }
                   }
                   ofstream log("log.txt",ios::app);
                   log<<"Customer "<<"("<<bank.get_costomers()[i].get_codeM()<<")"
                      <<bank.get_costomers()[i].get_name()<<" "<<
                     bank.get_costomers()[i].get_fname()<<" has been deleted by "<<
                         "("<<bank.get_man().get_id()<<")"<<
                         bank.get_man().get_name()<<" "<<bank.get_man().get_fname()<<" on : ";
                   time_t my_time = time(NULL);
                   log<<ctime(&my_time);
                   log.close();
                   bank.codem_list.erase(bank.codem_list.begin()+k);
                   bank.delete_costomer(i);
               }
               system("pause");
           }
       }
    }
    if(opt==7){
        system("cls");
        cout<<"Enter the employee's personnel ID:"<<endl;
        int id;
        cin>>id;
        int i=0;
        bool flag=true;
        bool flagfm=true;
        bool flagm=true;
        if(id==bank.get_man().get_id()){
            flagm=false;
        }
        else if(id==bank.get_fman().get_id()){
            flagfm=false;
        }
        else{
            for(i=0;i<bank.get_Employees().size();i++){
                if(bank.get_Employees()[i].get_id()==id){
                    flag=false;
                    break;
                }
            }
        }
        if(flag && flagm && flagfm){
            cout<<"Not found!"<<endl;
            system("pause");
        }
        else if(!flag){
            cout<<"Bank employee:"<<endl;
            bank.get_Employees()[i].View_all_information();
            system("pause");
        }
        else if(!flagfm){
            cout<<"Bank facility manager:"<<endl;
            bank.get_fman().View_all_information();
            system("pause");
        }
        else if(!flagm){
            cout<<"Bank manager:"<<endl;
            bank.get_man().View_all_information();
            system("pause");
        }
    }
    if(opt==8){
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
        cout<<"~~~~ Create a new employee ~~~~~"<<endl;
        cout<<"name: ";cin>>name;
        cout<<"family name: ";cin>>family;
        cout<<"Birthday (d/m/y):";cin>>bday;    //try catch
        birthdate.str_to_date(bday);
        cout<<"username: ";cin>>username;
        cout<<"password: ";cin>>password;
        cout<<"base salary: ";cin>>base_salary;
        bool rep=false;   //baraye check kardan tekrari budan id
        bool digit=false; //baraye check kardan 3 raghami budan
        while(true){
            cout<<"personnel ID(must be unique and 3 digits): ";cin>>id;
            rep=false;
            digit=false;
            if(id<100 || id>999){
                cout<<"ID must be 3 digits."<<endl;
                digit=true;
            }
            for(int i=0;i<bank.personnelid_list.size();i++){
                if(id==bank.personnelid_list[i]){
                    rep=true;
                    cout<<"This ID is not unique.Try again!"<<endl;
                }
            }
            if(rep==false && digit==false){
                cout<<"This ID is fine."<<endl;
                break;
            }
        }
        bank.personnelid_list.push_back(id);
        Employee e(name,family,birthdate,username,password,id,base_salary);
        bank.add_employee(e);
        cout<<"Employee "<<e.get_name()<<
              " "<<e.get_fname()<<" has been hired!"<<endl;
        ofstream log("log.txt",ios::app);
        log<<"Employee "<<"("<<id<<")"<<name<<" "<<family<<" has been hired by ("
          <<bank.get_man().get_id()<<")"
         <<bank.get_man().get_name()<<" "<<bank.get_man().get_fname()<<" on : ";
        time_t my_time = time(NULL);
        log<<ctime(&my_time);
        log.close();
        system("pause");
    }
    if(opt==9){
        system("cls");
        cout<<"Enter the employee's personnel ID:"<<endl;
        int id;
        cin>>id;
        int i=0;
        bool flag=true;
        for(i=0;i<bank.get_Employees().size();i++){
            if(bank.get_Employees()[i].get_id()==id){
                flag=false;
                break;
            }
        }
        if(flag){
            cout<<"Not found!"<<endl;
            system("pause");
        }
        else{
            for(int j=0;j<bank.personnelid_list.size();j++){  //baraye pak kardan id az list kole id ha
                if(id==bank.personnelid_list[j]){
                    bank.personnelid_list.erase(bank.personnelid_list.begin()+j);
                }
            }
            cout<<"Employee "<<bank.get_Employees()[i].get_name()<<
                  " "<<bank.get_Employees()[i].get_fname()<<
               " ("<<bank.get_Employees()[i].get_id()<<")"<<" has been fired!"<<endl;
            ofstream log("log.txt",ios::app);
            log<<"Employee "<<"("<<id<<")"<<bank.get_Employees()[i].get_name()
              <<" "<<bank.get_Employees()[i].get_fname()<<" has been fired by ("
              <<bank.get_man().get_id()<<")"
             <<bank.get_man().get_name()<<" "<<bank.get_man().get_fname()<<" on : ";
            time_t my_time = time(NULL);
            log<<ctime(&my_time);
            log.close();
            bank.delete_employee(i);
            system("pause");
        }
    }
    if(opt==10)
    {
        ofstream log("log.txt",ios::app);
        log<<"Manager ("<<bank.get_man().get_id()<<")"
          <<bank.get_man().get_name()<<" "<<
             bank.get_man().get_fname()<<
             " has logged out of the system on : ";
        time_t my_time = time(NULL);
        log<<ctime(&my_time);
        log.close();
        break;
    }
    }
}
void menu_fman(bank &bank)
{
    while(true){
    system("cls");
    cout<<"~~~Welcome "<<bank.get_fman().get_name()<<" "<<
          bank.get_fman().get_fname()<<"~~~\n";
    cout<<"1-Request for leave.\n";
    cout<<"2-Request for overtime.\n";
    cout<<"3-Display personal information.\n";
    cout<<"4-View complete customer information using a national number.\n";
    cout<<"5-Create an account for a customer.\n";
    cout<<"6-Delete a customer's account.\n";
    cout<<"7-Blocking a customer's account.\n";
    cout<<"8-View all loan requests.\n";
    cout<<"9-Review loan requests.\n";
    cout<<"10-View a loan details by its serial number.\n";
    cout<<"11-Exit.\n";
    int opt;
    cin>>opt;
    if(opt==1)
    {
         system("cls");
         cout<<"Hours of vacation taken this month :"<<
               bank.get_fman().get_Vacation_hours()<<endl;
         int max=bank.get_fman().get_salary()/100000;
         int current=bank.get_fman().get_Vacation_hours();
         max=15-current+max;
         while(true){
             cout<<"Maximum hours you can take this month: "<<max<<endl;
             cout<<"(Enter 0 to cancel the operation.)"<<endl;
             int hour;
             cin>>hour;
             if(hour==0)
                 break;
             if(hour>max || hour<0){
                 cout<<"Invalid hour!\n";
             }
             else{
                 bank.add_vacation(hour,-2);
                 cout<<"You got "<<hour<<" hours for vacation.Have fun!\n";
                 ofstream log("log.txt",ios::app);
                 log<<"Facility manager ("<<bank.get_fman().get_id()<<")"
                   <<bank.get_fman().get_name()<<" "<<
                      bank.get_fman().get_fname()<<
                      " has taken "<<hour<<" hours vacation "<<"on : ";
                 time_t my_time = time(NULL);
                 log<<ctime(&my_time);
                 log.close();
                 system("pause");
                 system("pause");
                 break;
             }
         }
    }
    if(opt==2)
    {
        system("cls");
        cout<<"Overtime hours taken this month :"<<
              bank.get_fman().get_Overtime_hours()<<endl;
        while(true){
            cout<<"Allowed hours for overtime :"<<12-bank.get_fman().get_Overtime_hours()<<endl;
            cout<<"(Enter 0 to cancel the operation.)"<<endl;
            int hour;
            cin>>hour;
            if(hour==0)
                break;
            if(hour<0 || hour>(12-bank.get_fman().get_Overtime_hours()))
            {
                cout<<"Invalid hour!\n";
            }
            else
            {
                bank.add_overtime(hour,-2);
                cout<<"You got "<<hour<<" hours for overtime.Have fun!\n";
                ofstream log("log.txt",ios::app);
                log<<"Facility manager ("<<bank.get_fman().get_id()<<")"
                  <<bank.get_fman().get_name()<<" "<<
                     bank.get_fman().get_fname()<<
                     " has taken "<<hour<<" hours overtime "<<"on : ";
                time_t my_time = time(NULL);
                log<<ctime(&my_time);
                log.close();
                system("pause");
                break;
            }
        }
    }
    if(opt==3)
    {
        system("cls");
        cout<<"Bank facility manager:"<<endl;
        bank.get_fman().View_all_information();
        system("pause");
    }
    if(opt==4)
    {
        system("cls");
        cout<<"Customer National Number :";
        string National_code;
        cin>>National_code;
        int i=0;
        bool flag=true;
        for(;i<bank.get_costomers().size();i++)
        {
            if(National_code==bank.get_costomers()[i].get_codeM())
            {
                flag=false;
                break;
            }
        }
        if(flag){
            cout<<"Not found!"<<endl;
            system("pause");
        }
        else{
            bank.get_costomers()[i].View_all_information();
            for(int j=0;j<bank.get_costomers()[i].get_Accounts().size();j++){
                if(bank.get_costomers()[i].get_Accounts()[j].get_active()==true){
                    cout<<j+1<<". (ACTIVE) ";
                    bank.get_costomers()[i].get_Accounts()[j].show_baseinfo();
                }
                else{
                    cout<<j+1<<". (DEACTIVE) ";
                    bank.get_costomers()[i].get_Accounts()[j].show_baseinfo();
                }

            }
            system("pause");
        }
    }
    if(opt==5)
    {
        system("cls");
        cout<<"Is it a person's first account ?\n"<<endl;
        cout<<"1)Yes\n";
        cout<<"2)NO\n";
        int x;
        cin>>x;
        if(x==1)
        {
            string name;
            string family;
            string codeM;
            Date birthdate;
            string username;
            string password;
            string bday;
            cout<<"~~~~ Create a new customer ~~~~~"<<endl;
            cout<<"name: ";cin>>name;
            cout<<"family name: ";cin>>family;
            while(true){
                cout<<"National code: ";cin>>codeM;
                bool flagcode=false;
                bool digit=false;
                if(codeM.size()!=11){
                    cout<<"National code must be 11 digits."<<endl;
                    digit=true;
                }
                for(int k=0;k<bank.codem_list.size();k++){
                    if(codeM==bank.codem_list[k]){
                        flagcode=true;
                        cout<<"This national code already exists."<<endl;
                    }
                }
                if(flagcode==false && digit==false){
                    break;
                }

            }

            cout<<"Birthday (d/m/y):";cin>>bday;
            birthdate=Date::str_to_date(bday);
            cout<<"username: ";cin>>username;
            cout<<"password: ";cin>>password;
            costomer new_c(name,family,birthdate,username,password,codeM);
            ofstream log("log.txt",ios::app);
            log<<"Customer "<<"("<<codeM<<")"<<name<<" "<<family<<" has been added by "<<
                 "("<<bank.get_fman().get_id()<<")"<<
                  bank.get_fman().get_name()<<" "<<bank.get_fman().get_fname()<<" on : ";
            time_t my_time = time(NULL);
            log<<ctime(&my_time);
            log.close();
            cout<<"Enter amount of money(50,000 minimum): "<<endl;
            long long int m;
            cin>>m;
            while(true){
                if(m<50000){
                    cout<<"Not enough money, Enter another amount."<<endl;
                    cin>>m;
                }
                else
                    break;
            }
            string num;
            while(true){
                cout<<"Enter account number: (6 digits)"<<endl;
                bool rep=false;
                bool digit=false;
                cin>>num;         //bayad check shavad.
                if(num.size()!=6){
                    digit=true;
                    cout<<"Invalid number, it must be 6 digits and unique."<<endl;
                }
                for(int z=0;z<bank.account_num_list.size();z++){
                    if(num==bank.account_num_list[z]){
                        rep=true;
                        cout<<"This number already exists. Try again!"<<endl;
                    }
                }
                if(rep==false && digit==false){
                    cout<<"This number is fine."<<endl;
                    break;
                }
            }
            bank.account_num_list.push_back(num);
            cout<<"Enter today's date: "<<endl;
            string d;
            cin>>d;
            Date o;
            o.str_to_date(d);
            Account a(num,codeM,o,m);
            new_c.add_account(a);
            cout<<"Account has been created!"<<endl;
            ofstream log2("log.txt",ios::app);
            log2<<"Account "<<num<<" has been created by "<<"("<<bank.get_fman().get_id()<<")"<<
                  bank.get_fman().get_name()<<" "<<bank.get_fman().get_fname()<<" on : ";
            log2<<ctime(&my_time);
            log2.close();
            a.show_baseinfo();
            bank.add_costomer(new_c);
            system("pause");
        }
        if(x==2)
        {
          cout<<"Customer's National Code :";
          string National_code;
          cin>>National_code;
          int i=0;
          bool flag=true;
          for(;i<bank.get_costomers().size();i++)
          {
              if(National_code==bank.get_costomers()[i].get_codeM())
              {
                  flag=false;
                  break;
              }
          }
          if(flag){
              cout<<"Not found!"<<endl;
              system("pause");
          }
          else{
              cout<<"Enter amount of money(50,000 minimum): "<<endl;
              long long int m;
              cin>>m;
              while(true){
                  if(m<50000){
                      cout<<"Not enough money, Enter another amount."<<endl;
                      cin>>m;
                  }
                  else
                      break;
              }
              string num;
              while(true){
                  cout<<"Enter account number: (6 digits)"<<endl;
                  bool rep=false;
                  bool digit=false;
                  cin>>num;         //bayad check shavad.
                  if(num.size()!=6){
                      digit=true;
                      cout<<"Invalid number, it must be 6 digits and unique."<<endl;
                  }
                  for(int z=0;z<bank.account_num_list.size();z++){
                      if(num==bank.account_num_list[z]){
                          rep=true;
                          cout<<"This number already exists. Try again!"<<endl;
                      }
                  }
                  if(rep==false && digit==false){
                      cout<<"This number is fine."<<endl;
                      break;
                  }
               }
              bank.account_num_list.push_back(num);
              cout<<"Enter today's date: "<<endl;
              string d;
              cin>>d;
              Date o;
              o.str_to_date(d);
              string codeM=bank.get_costomers()[i].get_codeM();
              Account a(num,codeM,o,m);
              bank.add_account(a,i);
              cout<<"Account has been created!"<<endl;
              ofstream log2("log.txt",ios::app);
              log2<<"Account "<<num<<" has been created by "<<"("<<bank.get_fman().get_id()<<")"<<
                    bank.get_fman().get_name()<<" "<<bank.get_fman().get_fname()<<" on : ";
              time_t my_time = time(NULL);
              log2<<ctime(&my_time);
              log2.close();
              a.show_baseinfo();
              system("pause");
          }
        }
    }
    if(opt==6)
    {
        system("cls");
        cout<<"Customer National Code :";
        string National_code;
        cin>>National_code;
        int i=0;
        bool flag=true;
        for(;i<bank.get_costomers().size();i++)
        {
            if(National_code==bank.get_costomers()[i].get_codeM())
            {
                flag=false;
                break;
            }
        }
        if(flag){
            cout<<"Customer not found!"<<endl;
            system("pause");
        }
        else{
            cout<<"Enter the customer's account number :";
            string account_number;
            cin>>account_number;
            bool flag2=true;
            int j=0;
            for(j=0;j<bank.get_costomers()[i].get_Accounts().size();j++)
            {
                if(bank.get_costomers()[i].get_Accounts()[j].get_account_number()==account_number)
                {
                    flag2=false;
                    break;
                }
            }
            if(flag2){
                cout<<"Account not found!"<<endl;
                system("pause");
            }
            else{
                int k=0;
                for(k=0;k<bank.account_num_list.size();k++){
                    if(bank.account_num_list[k]==account_number){
                        break;
                    }
                }
                bank.account_num_list.erase(bank.account_num_list.begin()+k);
                bank.delete_account(i,j);
                cout<<"Account has been deleted!"<<endl;
                ofstream log2("log.txt",ios::app);
                log2<<"Account "<<account_number<<" has been deleted by "<<
                      "("<<bank.get_fman().get_id()<<")"<<
                      bank.get_fman().get_name()<<" "<<bank.get_fman().get_fname()<<" on : ";
                time_t my_time = time(NULL);
                log2<<ctime(&my_time);
                log2.close();
                if(bank.get_costomers()[i].get_Accounts().size()==0){
                    cout<<"This customer has no accounts. Deleting the customer..."<<endl;
                    int k=0;
                    for(k=0;k<bank.codem_list.size();k++){  //baraye delete kardan code
                        if(National_code==bank.codem_list[k]){   //meli az list code meli ha
                            break;
                        }
                    }
                    ofstream log("log.txt",ios::app);
                    log<<"Customer "<<"("<<bank.get_costomers()[i].get_codeM()<<")"
                       <<bank.get_costomers()[i].get_name()<<" "<<
                      bank.get_costomers()[i].get_fname()<<" has been deleted by "<<
                          "("<<bank.get_fman().get_id()<<")"<<
                          bank.get_fman().get_name()<<" "<<bank.get_fman().get_fname()<<" on : ";
                    time_t my_time = time(NULL);
                    log<<ctime(&my_time);
                    log.close();
                    bank.codem_list.erase(bank.codem_list.begin()+k);
                    bank.delete_costomer(i);
                }
                system("pause");
            }
        }
    }
    if(opt==7){
        cout<<"Enter customer's national code:"<<endl;
        string codem;
        cin>>codem;
        int i=0;
        bool flag=true;
        for(;i<bank.get_costomers().size();i++)
        {
            if(codem==bank.get_costomers()[i].get_codeM())
            {
                flag=false;
                break;
            }
        }
        if(flag){
            cout<<"Not found!"<<endl;
            system("pause");
        }
        else{
            string name=bank.get_costomers()[i].get_name();
            string fname=bank.get_costomers()[i].get_fname();
            for(int z=0;z<bank.get_costomers()[i].get_Accounts().size();z++){
                bank.deactive_account(i,z);
            }
            cout<<"All of "<<name<<" "<<fname<<"'s accounts have been deactivated."<<endl;
            ofstream log("log.txt",ios::app);
            log<<"All of ("<<bank.get_costomers()[i].get_codeM()<<")"
              <<name<<" "<<fname<<"'s accounts have been deactivated by ("<<
              bank.get_fman().get_id()<<")"<<bank.get_fman().get_name()<<" "
              <<bank.get_fman().get_fname()<<" on : ";
            time_t my_time = time(NULL);
            log<<ctime(&my_time);
            log.close();
            system("pause");
        }
    }
    if(opt==11)
    {
        ofstream log("log.txt",ios::app);
        log<<"Facility manager ("<<bank.get_fman().get_id()<<")"
          <<bank.get_fman().get_name()<<" "<<
             bank.get_fman().get_fname()<<
             " has logged out of the system on : ";
        time_t my_time = time(NULL);
        log<<ctime(&my_time);
        log.close();
        break;
    }
    }
}
void menu_Employee(bank &bank,int index)
{
    while(true){
    system("cls");
    cout<<"~~~Welcome "<<bank.get_Employees()[index].get_name()<<" "<<
          bank.get_Employees()[index].get_fname()<<"~~~\n";
    cout<<"1-Request for leave.\n";
    cout<<"2-Request for overtime.\n";
    cout<<"3-Display personal information.\n";
    cout<<"4-View complete customer information using a national number.\n";
    cout<<"5-Create an account for a customer.\n";
    cout<<"6-Delete a customer's account.\n";
    cout<<"7-Exit.\n";
    int opt;
    cin>>opt;
    if(opt==1)
    {
         system("cls");
         cout<<"Hours of vacation taken this month :"<<
               bank.get_Employees()[index].get_Vacation_hours()<<endl;
         int max=bank.get_Employees()[index].get_salary()/100000;
         int current=bank.get_Employees()[index].get_Vacation_hours();
         max=15-current+max;
         while(true){
             cout<<"Maximum hours you can take this month: "<<max<<endl;
             cout<<"(Enter 0 to cancel the operation.)"<<endl;
             int hour;
             cin>>hour;
             if(hour==0)
                 break;
             if(hour>max || hour<0){
                 cout<<"Invalid hour!\n";
             }
             else{
                 bank.add_vacation(hour,index);
                 cout<<"You got "<<hour<<" hours for vacation.Have fun!\n";
                 ofstream log("log.txt",ios::app);
                 log<<"Employee ("<<bank.get_Employees()[index].get_id()<<")"
                   <<bank.get_Employees()[index].get_name()<<" "<<
                      bank.get_Employees()[index].get_fname()<<
                      " has taken "<<hour<<" hours vacation "<<"on : ";
                 time_t my_time = time(NULL);
                 log<<ctime(&my_time);
                 log.close();
                 system("pause");
                 break;
             }
         }
    }
    if(opt==2)
    {
        system("cls");
        cout<<"Overtime hours taken this month :"<<
              bank.get_Employees()[index].get_Overtime_hours()<<endl;
        while(true){
            cout<<"Allowed hours for overtime :"
               <<12-bank.get_Employees()[index].get_Overtime_hours()<<endl;
            cout<<"(Enter 0 to cancel the operation.)"<<endl;
            int hour;
            cin>>hour;
            if(hour==0)
                break;
            if(hour<0 || hour>(12-bank.get_Employees()[index].get_Overtime_hours()))
            {
                cout<<"Invalid hour!\n";
            }
            else
            {
                bank.add_overtime(hour,index);
                cout<<"You got "<<hour<<" hours for overtime.Have fun!\n";
                ofstream log("log.txt",ios::app);
                log<<"Employee ("<<bank.get_Employees()[index].get_id()<<")"
                  <<bank.get_Employees()[index].get_name()<<" "<<
                     bank.get_Employees()[index].get_fname()<<
                     " has taken "<<hour<<" hours overtime "<<"on : ";
                time_t my_time = time(NULL);
                log<<ctime(&my_time);
                log.close();
                system("pause");
                break;
            }
        }
    }
    if(opt==3)
    {
        system("cls");
        cout<<"Bank employee:"<<endl;
        bank.get_Employees()[index].View_all_information();
        system("pause");
    }
    if(opt==4)
    {
        system("cls");
        cout<<"Customer National Number :";
        string National_code;
        cin>>National_code;
        int i=0;
        bool flag=true;
        for(;i<bank.get_costomers().size();i++)
        {
            if(National_code==bank.get_costomers()[i].get_codeM())
            {
                flag=false;
                break;
            }
        }
        if(flag){
            cout<<"Not found!"<<endl;
            system("pause");
        }
        else{
            bank.get_costomers()[i].View_all_information();
            for(int j=0;j<bank.get_costomers()[i].get_Accounts().size();j++){
                cout<<j+1<<". ";
                bank.get_costomers()[i].get_Accounts()[j].show_baseinfo();
            }
            system("pause");
        }
    }
    if(opt==5)
    {
        system("cls");
        cout<<"Is it a person's first account ?\n"<<endl;
        cout<<"1)Yes\n";
        cout<<"2)NO\n";
        int x;
        cin>>x;
        if(x==1)
        {
            string name;
            string family;
            string codeM;
            Date birthdate;
            string username;
            string password;
            string bday;
            cout<<"~~~~ Create a new customer ~~~~~"<<endl;
            cout<<"name: ";cin>>name;
            cout<<"family name: ";cin>>family;
            while(true){
                cout<<"National code: ";cin>>codeM;
                bool flagcode=false;
                bool digit=false;
                if(codeM.size()!=11){
                    cout<<"National code must be 11 digits."<<endl;
                    digit=true;
                }
                for(int k=0;k<bank.codem_list.size();k++){
                    if(codeM==bank.codem_list[k]){
                        flagcode=true;
                        cout<<"This national code already exists."<<endl;
                    }
                }
                if(flagcode==false && digit==false){
                    break;
                }

            }
            cout<<"Birthday (d/m/y):";cin>>bday;
            birthdate=Date::str_to_date(bday);
            cout<<"username: ";cin>>username;
            cout<<"password: ";cin>>password;
            costomer new_c(name,family,birthdate,username,password,codeM);
            ofstream log("log.txt",ios::app);
            log<<"Customer "<<"("<<codeM<<")"<<name<<" "<<family<<" has been added by "<<
                 "("<<bank.get_Employees()[index].get_id()<<")"<<
                  bank.get_Employees()[index].get_name()<<" "
              <<bank.get_Employees()[index].get_fname()<<" on : ";
            time_t my_time = time(NULL);
            log<<ctime(&my_time);
            log.close();
            cout<<"Enter amount of money(50,000 minimum): "<<endl;
            long long int m;
            cin>>m;
            while(true){
                if(m<50000){
                    cout<<"Not enough money, Enter another amount."<<endl;
                    cin>>m;
                }
                else
                    break;
            }
            string num;
            while(true){
                cout<<"Enter account number: (6 digits)"<<endl;
                bool rep=false;
                bool digit=false;
                cin>>num;         //bayad check shavad.
                if(num.size()!=6){
                    digit=true;
                    cout<<"Invalid number, it must be 6 digits and unique."<<endl;
                }
                for(int z=0;z<bank.account_num_list.size();z++){
                    if(num==bank.account_num_list[z]){
                        rep=true;
                        cout<<"This number already exists. Try again!"<<endl;
                    }
                }
                if(rep==false && digit==false){
                    cout<<"This number is fine."<<endl;
                    break;
                }
            }
            bank.account_num_list.push_back(num);
            cout<<"Enter today's date: "<<endl;
            string d;
            cin>>d;
            Date o;
            o.str_to_date(d);
            Account a(num,codeM,o,m);
            new_c.add_account(a);
            cout<<"Account has been created!"<<endl;
            ofstream log2("log.txt",ios::app);
            log2<<"Account "<<num<<" has been created by "<<"("
               <<bank.get_Employees()[index].get_id()<<")"<<
                  bank.get_Employees()[index].get_name()
              <<" "<<bank.get_Employees()[index].get_fname()<<" on : ";
            log2<<ctime(&my_time);
            log2.close();
            a.show_baseinfo();
            bank.add_costomer(new_c);
            system("pause");
        }
        if(x==2)
        {
          cout<<"Customer's National Code :";
          string National_code;
          cin>>National_code;
          int i=0;
          bool flag=true;
          for(;i<bank.get_costomers().size();i++)
          {
              if(National_code==bank.get_costomers()[i].get_codeM())
              {
                  flag=false;
                  break;
              }
          }
          if(flag){
              cout<<"Not found!"<<endl;
              system("pause");
          }
          else{
              cout<<"Enter amount of money(50,000 minimum): "<<endl;
              long long int m;
              cin>>m;
              while(true){
                  if(m<50000){
                      cout<<"Not enough money, Enter another amount."<<endl;
                      cin>>m;
                  }
                  else
                      break;
              }
              string num;
              while(true){
                  cout<<"Enter account number: (6 digits)"<<endl;
                  bool rep=false;
                  bool digit=false;
                  cin>>num;         //bayad check shavad.
                  if(num.size()!=6){
                      digit=true;
                      cout<<"Invalid number, it must be 6 digits and unique."<<endl;
                  }
                  for(int z=0;z<bank.account_num_list.size();z++){
                      if(num==bank.account_num_list[z]){
                          rep=true;
                          cout<<"This number already exists. Try again!"<<endl;
                      }
                  }
                  if(rep==false && digit==false){
                      cout<<"This number is fine."<<endl;
                      break;
                  }
               }
              bank.account_num_list.push_back(num);
              cout<<"Enter today's date: "<<endl;
              string d;
              cin>>d;
              Date o;
              o.str_to_date(d);
              string codeM=bank.get_costomers()[i].get_codeM();
              Account a(num,codeM,o,m);
              bank.add_account(a,i);
              cout<<"Account has been created!"<<endl;
              ofstream log2("log.txt",ios::app);
              log2<<"Account "<<num<<" has been created by "<<"("
                 <<bank.get_Employees()[index].get_id()<<")"<<
                    bank.get_Employees()[index].get_name()<<
                   " "<<bank.get_Employees()[index].get_fname()<<" on : ";
              time_t my_time = time(NULL);
              log2<<ctime(&my_time);
              log2.close();
              a.show_baseinfo();
              system("pause");
          }
        }
    }
    if(opt==6)
    {
        system("cls");
        cout<<"Customer National Code :";
        string National_code;
        cin>>National_code;
        int i=0;
        bool flag=true;
        for(;i<bank.get_costomers().size();i++)
        {
            if(National_code==bank.get_costomers()[i].get_codeM())
            {
                flag=false;
                break;
            }
        }
        if(flag){
            cout<<"Customer not found!"<<endl;
            system("pause");
        }
        else{
            cout<<"Enter the customer's account number :";
            string account_number;
            cin>>account_number;
            bool flag2=true;
            int j=0;
            for(j=0;j<bank.get_costomers()[i].get_Accounts().size();j++)
            {
                if(bank.get_costomers()[i].get_Accounts()[j].get_account_number()==account_number)
                {
                    flag2=false;
                    break;
                }
            }
            if(flag2){
                cout<<"Account not found!"<<endl;
                system("pause");
            }
            else{
                int k=0;
                for(k=0;k<bank.account_num_list.size();k++){
                    if(bank.account_num_list[k]==account_number){
                        break;
                    }
                }
                bank.account_num_list.erase(bank.account_num_list.begin()+k);
                bank.delete_account(i,j);
                cout<<"Account has been deleted!"<<endl;
                ofstream log2("log.txt",ios::app);
                log2<<"Account "<<account_number<<" has been deleted by "<<
                      "("<<bank.get_Employees()[index].get_id()<<")"<<
                      bank.get_Employees()[index].get_name()
                   <<" "<<bank.get_Employees()[index].get_fname()<<" on : ";
                time_t my_time = time(NULL);
                log2<<ctime(&my_time);
                log2.close();
                if(bank.get_costomers()[i].get_Accounts().size()==0){
                    cout<<"This customer has no accounts. Deleting the customer..."<<endl;
                    int k=0;
                    for(k=0;k<bank.codem_list.size();k++){  //baraye delete kardan code
                        if(National_code==bank.codem_list[k]){   //meli az list code meli ha
                            break;
                        }
                    }
                    ofstream log("log.txt",ios::app);
                    log<<"Customer "<<"("<<bank.get_costomers()[i].get_codeM()<<")"
                       <<bank.get_costomers()[i].get_name()<<" "<<
                      bank.get_costomers()[i].get_fname()<<" has been deleted by "<<
                          "("<<bank.get_Employees()[index].get_id()<<")"<<
                          bank.get_Employees()[index].get_name()
                      <<" "<<bank.get_Employees()[index].get_fname()<<" on : ";
                    time_t my_time = time(NULL);
                    log<<ctime(&my_time);
                    log.close();
                    bank.codem_list.erase(bank.codem_list.begin()+k);
                    bank.delete_costomer(i);
                }
                system("pause");
            }
        }
    }
    if(opt==7)
    {
        ofstream log("log.txt",ios::app);
        log<<"Employee ("<<bank.get_Employees()[index].get_id()<<")"
          <<bank.get_Employees()[index].get_name()<<" "<<
             bank.get_Employees()[index].get_fname()<<
             " has logged out of the system on : ";
        time_t my_time = time(NULL);
        log<<ctime(&my_time);
        log.close();
        break;
    }
    }
}

void menu_cost(bank &bank,int index)
{
    while(true){
        system("cls");
        cout<<"~~~Welcome "<<bank.get_costomers()[index].get_name()<<" "<<
              bank.get_costomers()[index].get_fname()<<"~~~\n";
        cout<<"1-Deposit money.\n";
        cout<<"2-Withdraw money.\n";
        cout<<"3-Apply for a loan.\n";
        cout<<"4-Display personal information and then select.\n";
        cout<<"5-Exit.\n";
        int opt;
        cin>>opt;
        if(opt==1)
        {
            system("cls");
            cout<<"Enter account number :";
            string account_number;
            cin>>account_number;

            bool not_found=true;
            int i=0;
            for(i=0;i<bank.get_costomers()[index].get_Accounts().size();i++)
            {
                if(bank.get_costomers()[index].get_Accounts()[i].get_account_number()==
                        account_number)
                {
                    not_found=false;
                    break;
                }
            }
            if(not_found)
            {
                cout<<"Account not found";
                system("pause");
                //throw
            }
            else{
                long amount;
                while(true){
                    cout<<"Amount of money :";
                    cin>>amount;
                    if(amount<=0){
                        cout<<"Error! please enter a valid amount of money!"<<endl;
                    }
                    else{
                        break;
                    }
                }

                bank.deposit(amount,index);
                cout<<amount<<" has been deposited to the account with number : ";
                cout<<account_number<<endl;
                ofstream log("log.txt",ios::app);
                log<<"Customer ("<<bank.get_costomers()[index].get_codeM()<<")"
                  <<bank.get_costomers()[index].get_name()
                 <<" "<<bank.get_costomers()[index].get_fname()<<" has deposited "<<amount
                <<" into account ("<<account_number<<") on : ";
                time_t my_time = time(NULL);
                log<<ctime(&my_time);
                log.close();
                system("pause");
            }
        }
        if(opt==2)
        {
            system("cls");
            cout<<"Enter account number :";
            string account_number;
            cin>>account_number;
            bool not_found=true;
            int i=0;
            for(i=0;i<bank.get_costomers()[index].get_Accounts().size();i++)
            {
                if(bank.get_costomers()[index].get_Accounts()[i].get_account_number()==
                        account_number)
                {
                    not_found=false;
                    break;
                }
            }
            if(not_found)
            {
                cout<<"Account not found";
                system("pause");
            }
            else{
                long amount;
                while(true){
                    cout<<"Amount of money : (0 to abort the operation)";
                    cin>>amount;
                    bool valid=false;
                    bool bal=false;
                    if(amount==0)
                        break;
                    else if(amount<=0){
                        cout<<"Error! please enter a valid amount of money!"<<endl;
                        valid=true;
                    }
                    else if(amount>bank.get_costomers()[index].get_Accounts()[i].get_bal()){
                        cout<<"Not enough money in account."<<endl;
                        bal=true;
                    }
                    if(bal==false && valid==false)
                        break;
                }
                bank.withdraw(amount,index);
                cout<<amount<<" has been withdrawed from the account with number : ";
                cout<<account_number<<endl;
                ofstream log("log.txt",ios::app);
                log<<"Customer ("<<bank.get_costomers()[index].get_codeM()<<")"
                  <<bank.get_costomers()[index].get_name()
                 <<" "<<bank.get_costomers()[index].get_fname()<<" has withdrawed "<<amount
                <<" from account ("<<account_number<<") on : ";
                time_t my_time = time(NULL);
                log<<ctime(&my_time);
                log.close();
                system("pause");
            }
        }
        if(opt==3)
        {
            system("cls");
            cout<<"Enter account number:\n";
            string acc;
            cin>>acc;
            bool flag=true;
            int i=0;
            for(i=0;i<bank.get_costomers()[index].get_Accounts().size();i++)
            {
                if(bank.get_costomers()[index].get_Accounts()[i].get_account_number()==acc)
                {
                    flag=false;
                    break;
                }
            }
            if(flag)
            {
                cout<<"Account not found";
                system("pause");
                //throw
            }
            long long int bal=bank.get_costomers()[index].get_Accounts()[i].get_bal();
            int dayvam=bank.get_costomers()[index].get_Accounts()[i].get_dayvam();
            cout<<"Account balance : ";
            cout<<bal<<endl;
            cout<<"Maximum loan ("<<dayvam<<" days) : ";
            cout<<dayvam*bal;
            cout<<"Enter loan amount:\n";
            long long int loan;
            cin>>loan;
            cout<<"Which kind of loan do you want?\n";
            cout<<"1. 12 months (%4 interest)\n";
            cout<<"2. 24 months (%8 interest)\n";
            cout<<"3. 36 months (%12 interest)\n";
            int ans;
            cin>>ans;
        }
        if(opt==4)
        {
            system("cls");
            bank.get_costomers()[index].View_all_information();
            cout<<"\n1. Show all accounts."<<endl;
            cout<<"2. Show all loans."<<endl;
            int ans;
            cin>>ans;
            if(ans==1){
                for(int j=0;j<bank.get_costomers()[index].get_Accounts().size();j++){
                    if(bank.get_costomers()[index].get_Accounts()[j].get_active()==true){
                        cout<<j+1<<". (ACTIVE) ";
                        bank.get_costomers()[index].get_Accounts()[j].show_baseinfo();
                    }
                    else{
                        cout<<j+1<<". (DEACTIVE) ";
                        bank.get_costomers()[index].get_Accounts()[j].show_baseinfo();
                    }

                }
                system("pause");
            }
        }
        if(opt==5)
        {
            ofstream log("log.txt",ios::app);
            log<<"Customer ("<<bank.get_costomers()[index].get_codeM()<<")"
              <<bank.get_costomers()[index].get_name()<<" "<<
                 bank.get_costomers()[index].get_fname()<<
                 " has logged out of the system on : ";
            time_t my_time = time(NULL);
            log<<ctime(&my_time);
            log.close();
            break;
        }
    }
}

