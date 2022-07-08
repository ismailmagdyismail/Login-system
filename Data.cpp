#include "Data.h"
#include <fstream>
#include <vector>
#include <regex>


vector<string>IDs;
map<string,Data>stored;

//---------------------------------------------

ostream& operator<<(ostream& out,Data&data)
{
    cout<<">>>Full Name : "<<data.fullName<<'\n';
    cout<<">>>ID : "<<data.ID<<'\n';
    cout<<">>>Email : "<<data.email<<'\n';
    cout<<">>>Password : "<<data.password<<'\n';
    cout<<">>>PhoneNumber : "<<data.phoneNumber<<'\n';
    cout<<">>>Gender : "<<data.gender<<'\n';
    cout<<">>>Age : "<<data.age;
    return out;
}

//---------------------------------------------

void menu()
{
    //Displaying options Menu
    cout<<"\n";
    cout<<"Menu\n";
    cout<<"Choose From The Menu :\n";
    cout<<"1-Register\n";
    cout<<"2-Login\n";
    cout<<"3-ChangePassword\n";
    cout<<"4-Exit\n";
    cout<<">>>Choose your option : ";
}


//---------------------------------------------

void checkChoice()
{
    // getting user's choice
    string choice;
    cin>>choice;

    // validating choice
    while (!isdigit(choice[0])||choice[0]>'4'||choice[0]<'1'||choice.size()>1||choice.empty())
    {
        cout<<">>>Invalid Option ,Choose Again : ";
        cin>>choice;
    }
    if(choice[0]=='1')
    {
        registerUser();
    }
    else if(choice[0]=='2')
    {
        login();
    }
    else if(choice[0]=='3')
    {
        changePassword();
    }
    else
    {
        exit(0);
    }
}
//---------------------------------------------

void generateFile()
{
    // Make a File that stores the IDs if it wasn't created
    ifstream file;
    string name="Registered.txt";
    file.open(name,ios::app);
    file.close();
}

//---------------------------------------------

void fetchIDs()
{
    // Make a File that stores the IDs if it wasn't already created
    generateFile();

    // fetch all the Ids that has already been registered
    ifstream registered;
    registered.open("Registered.txt");
    char id[100];
    if(!registered)
    {
        return;
    }
    while (!registered.eof())
    {
        registered.getline(id,100);
        // avoiding special char at the end of the file
        if(strlen(id)>1)
        {
            IDs.push_back(id);
        }
    }
    registered.close();
}

//---------------------------------------------

void fetchData()
{
    // get data and store for each id Registered
    int number=IDs.size();
    for (int i = 0; i <number; ++i)
    {
        string id=IDs[i]+".txt";

        //to avoid special char at the end of the File
        if(id.size()<=4)
        {
            continue;
        }

        ifstream data;
        data.open(id);

        if(!data)
        {
            return;
        }
         int line =1;
         Data userData;
         char info[100];
        while (!data.eof())
        {
            data.getline(info,100);
            if(line==1)
            {
                userData.fullName=info;
            }
            else if(line==2)
            {
                userData.ID=info;
            }
            else if(line==3)
            {
                userData.email=info;
            }
            else if(line==4)
            {
                userData.password=info;
                userData.password= decryptPassword(userData.password);
            }
            else if(line==5)
            {
                userData.phoneNumber=info;
            }
            else if(line==6)
            {
                userData.gender=info;
            }
            else if(line==7)
            {
                userData.age=info;
            }
           line++;
        }
        data.close();
        stored.insert({IDs[i],userData});
    }
}

//---------------------------------------------

void registerUser()
{
    // creating a new object for each new user
    Data newUser;

    //getting user's full name
    string userFirstName = verifyFirstName();
    string userMiddleName = verifyMiddleName();
    string userLastName = verifyLastName();
    newUser.fullName = userFirstName+" "+userMiddleName+" "+userLastName;

    //getting new user's ID
    string ID=verifyID();
    newUser.ID = ID;

    //getting new user's Email
    newUser.email = verifyEmail();

    //getting new user's password
    newUser.password = verifyPassword();

    //getting new user's PhoneNumber
    newUser.phoneNumber = verifyPhoneNumber();

    //getting new user's Gender
    newUser.gender = verifyGender();

    //getting new user's Age
    newUser.age = verifyAge();

    storeUser(newUser);
    cout<<">>>You have been successfully stored in the system\n";
    menu();
    checkChoice();
}

//---------------------------------------------

string verifyFirstName()
{
    // validating that the First Name is valid
    cin.ignore();
    string name;
    bool isValid= false;
    cout<<"\n";
    cout<<"First Name\n";
    while (!isValid)
    {
        cout<<">>>Enter your FirstName consisting of letters [a-z] : ";
        getline(cin,name);
        isValid = true;
        for (const char& i : name)
        {
            if(!isalpha(i))
            {
                cout<<">>>Invalid FirstName ,Names should consist of characters only,please Enter another one\n";
                isValid = false;
                break;
            }
        }
    }
    return name;
}
//---------------------------------------------

string verifyMiddleName()
{
    // validating that the Middle Name is valid
    string name;
    bool isValid= false;
    cout<<"\n";
    cout<<"Middle Name\n";
    while (!isValid)
    {
        cout<<">>>Enter your MiddleName consisting of letters [a-z] : ";
        getline(cin,name);
        isValid = true;
        for (const char& i : name)
        {
            if(!isalpha(i))
            {
                cout<<">>>Invalid MiddleName,Names should consist of characters only,please Enter another one\n";
                isValid = false;
                break;
            }
        }
    }
    return name;
}

//---------------------------------------------

string verifyLastName()
{
    // validating that the last Name is valid
    string name;
    bool isValid= false;
    cout<<"\n";
    cout<<"Last Name\n";
    while (!isValid)
    {
        cout<<">>>Enter your LastName consisting of letters [a-z] : ";
        getline(cin,name);
        isValid = true;
        for (const char& i : name)
        {
            if(!isalpha(i))
            {
                cout<<">>>Invalid LastName ,Names should consist of characters only,please Enter another one\n";
                isValid = false;
                break;
            }
        }
    }
    return name;
}

//---------------------------------------------

string verifyID()
{
    //verifying ID
    string id;
    bool isValid = false;

    cout<<"\n";
    cout<<"ID\n";
    while (!isValid)
    {
        cout<<">>>Enter your ID consisting of digits only [0-9] and Not consisting of less than 5 Numbers : ";
        cin>>id;
        isValid = true;
        if(stored.find(id)!=stored.end())
        {
            cout<<">>>This ID is already taken,Choose a unique new one\n";
            isValid=false;
            continue;
        }
        else if(id.size()<5)
        {
            cout<<">>>This ID is too short,Choose another one\n";
            isValid = false;
            continue;
        }
        for (char i:id)
        {
            if(i>'9'||i<'0')
            {
                cout<<">>>Invalid ID,Enter another one\n";
                isValid = false;
                break;
            }
        }
    }
    return id;
}

//---------------------------------------------

string verifyEmail()
{
    // verifying Email
    string email;
    bool isValid = false;
    regex validEmail("[a-zA-Z]+[0-9]{0,10}@[a-zA-Z]+[.]com");
    cout<<"\n";
    cout<<"Email\n";
    while (!isValid)
    {
        isValid = true;
        cout<<">>>Enter your email in this form  \"Example@domain.com\" without any Special character : ";
        cin>>email;
        if(!regex_match(email,validEmail))
        {
            cout<<">>>This Email is in an Invalid Format ,please use a proper Email format\n";
            isValid = false;
            continue;
        }
        for (const auto& x:stored)
        {
            if(x.second.email == email)
            {
                cout<<">>>This Email is already Taken by another user,please use a new one\n";
                isValid = false;
                break;
            }
        }
    }
    return email;
}

//---------------------------------------------

string verifyPassword()
{
    string password;
    bool isValid = false;
    cout<<"Password\n>>>Password should be not less than 12 characters long and consisting of lower and upper case letters and at least one digit\n";

    while (!isValid)
    {
        isValid = true ;
        cout<<">>>Enter your Password : ";
        cin>>password;
        if(password.size()<12)
        {
            cout<<">>>Password is Too Short , must be at least 12 characters\n";
            isValid = false;
            continue;
        }
        else if(password.size()>=100)
        {
            cout<<">>>Password is Too long\n";
            isValid = false;
            continue;
        }
        int upperCounter=0;
        int lowerCounter=0;
        int digitCounter=0;
        for (const char& x :password)
        {
            if(!isalpha(x)&&!isdigit(x))
            {
                cout<<">>>Password Must have only digits and letters only\n";
                isValid = false;
                break;
            }
            else if(isalpha(x)&& isupper(x))
            {
                upperCounter++;
            }
            else if(isalpha(x)&& islower(x))
            {
                lowerCounter++;
            }
            else if(isdigit(x))
            {
                digitCounter++;
            }
        }
        if(upperCounter>0 &&lowerCounter>0 && digitCounter>0&&password.size()>=12)
        {
            cout<<">>>Password is Strong \n";
        }
        else
        {
            cout<<">>>Weak Password,please use another one\n";
            cout<<">>>Password should be consisting of lower and upper case letters and at least one digit\n";
            isValid = false;
            continue;
        }
    }
    string confirmation;
    cout<<"Confirmation\n";
    while (confirmation!=password)
    {
        cout<<">>>Confirm your Password : ";
        cin>>confirmation;
        if(confirmation!=password)
        {
            cout<<">>>Passwords don't match\n";
        }
        else
        {
            cout<<">>>Password Verified\n";
            cout<<">>>Password is Strong \n";
        }
    }
    return password;
}

//---------------------------------------------

string encryptPassword(string& userPassword)
{
    // Encrypting Passwords to be stored in the file
    // using Cesar cipher Encryption Method

    //shifting each character by 1 to the right
    for (char & i : userPassword)
    {
        int ASCII=i;
        ASCII++;
        i=ASCII;
    }
    return userPassword;
}

//---------------------------------------------

string decryptPassword(string& userPassword)
{
    // Decrypting Passwords to be stored in the file
    // using Cesar cipher Encryption Method

    //shifting each character by 1 to the left
    for (char & i : userPassword)
    {
        int ASCII=i;
        ASCII--;
        i=ASCII;
    }
    return userPassword;
}

//---------------------------------------------

string verifyPhoneNumber()
{
    //verifying phoneNumber
    string phoneNumber;
    bool isValid = false;
    cout<<"\n";
    cout<<"Phone Number\n";
    while (!isValid)
    {
        isValid = true;
        cout<<">>>Enter your phoneNumber consisting of Digits only (01**********) : ";
        cin >> phoneNumber;
        if(phoneNumber[0]!='0'||phoneNumber[1]!='1')
        {
            cout<<">>>Invalid PhoneNumber,Please Enter a correct PhoneNumber\n";
            isValid = false;
            continue;
        }
        else if(phoneNumber[2]!='0'&&phoneNumber[2]!='1'&&phoneNumber[2]!='2'&&phoneNumber[2]!='5')
        {
            cout<<">>>Invalid PhoneNumber,Please Enter a correct PhoneNumber\n";
            isValid = false;
            continue;
        }
        else if(phoneNumber.size()<11||phoneNumber.size()>11)
        {
            cout<<">>>Invalid PhoneNumber,Please Enter a correct PhoneNumber\n";
            isValid = false;
            continue;
        }
        for (const auto& x:stored)
        {
            if(x.second.phoneNumber==phoneNumber)
            {
                cout<<">>>This PhoneNumber is already used by Another user,please Enter a new one\n";
                isValid = false;
                break;
            }
        }
    }
    return phoneNumber;
}

//---------------------------------------------

string verifyGender()
{
    //verifying Gender
    cout<<"\n";
    cout<<"Gender\n";
    char choice;
    cout<<"choose your Gender : \n";
    cout<<"1-Male\n";
    cout<<"2-Female\n";
    cout<<">>>Your choice : ";
    cin>>choice;
    while (!isdigit(choice)||choice>'2'||choice<'1')
    {
        cout<<">>>Invalid choice\n";
        cout<<">>>Your choice : ";
        cin>>choice;
    }
    if(choice==1)
        return "Male";
    else
        return "Female";
}

//---------------------------------------------

string verifyAge()
{
    //verifying Age
    string age;
    bool isValid = false;
    cout<<"\n";
    cout<<"Age\n";
    while (!isValid)
    {
        cout<<">>>Enter your Age : ";
        cin>>age;
        isValid = true;
        if(age.size()>2||age[0]=='0')
        {
            cout<<">>>Invalid Age\n";
            isValid = false;
            continue;
        }
        for (const char& i : age)
        {
            if(!isdigit(i))
            {
                cout<<">>>Invalid Age\n";
                isValid = false;
                break;
            }
        }
    }
    return age;
}

//---------------------------------------------

void storeUser(const Data& userData)
{
    //store user to the files and MAP

    string password = userData.password;
    password=encryptPassword(password);
    //updating file that stores IDs
    ofstream file;
    file.open("Registered.txt",ios::app);
    file<<endl<<userData.ID;
    file.close();

    //Making a new file that stores the data for the new user
    string id=userData.ID+".txt";
    file.open(id,ios::app);

    file<<userData.fullName<<'\n';
    file<<userData.ID<<'\n';
    file<<userData.email<<'\n';
    file<<password<<'\n';
    file<<userData.phoneNumber<<'\n';
    file<<userData.gender<<'\n';
    file<<userData.age<<'\n';

    file.close();

    //updating the map that stores the IDs Registered
    stored.insert({userData.ID,userData});
    IDs.push_back(userData.ID);
}

//---------------------------------------------

void login()
{
    //getting login ID
    string ID=loginID();

    // getting password and see if it's matching to the stored password
    bool attempt = loginPassword(ID);
    if(attempt)
    {
        loginMenu(ID);
    }
    else
    {
        menu();
        checkChoice();
    }
}

//---------------------------------------------

string loginID()
{
    string ID;
    bool isValid = false;
    cout<<"ID\n";
    while (!isValid)
    {
        isValid = true;
        cout<<"Enter your ID : ";
        cin>>ID;
        
        if(stored.find(ID)==stored.end())
        {
            cout<<">>>This ID isn't Registered in the system\n";
            isValid = false;
            continue;
        }
    }
    return ID;
}

//---------------------------------------------

bool loginPassword(const string& ID)
{
    //get password when logging in and check if it macthes the stored password
    string password;
    bool matching = false;
    cout<<"\n";
    cout<<"Password\n";
    for (int i = 3; i>0 ; --i)
    {
        cout<<">>>You have "<<i<<" attempts to Enter your Password successfully\n";
        cout<<">>>Enter your Password : ";
        cin>>password;
        if(password!=stored[ID].password)
        {
            cout<<">>>Password incorrect ,Try Again \n";
        }
        else
        {
            matching = true;
            break;
        }
    }
    if(matching)
    {
        cout<<">>>successful Login Welcome "<<stored[ID].fullName<<" to the system\n";
        return true;
    }
    else
    {
        cout<<">>>Unsuccessful Login attempt \n";
        return false;
    }
}

//---------------------------------------------

void loginMenu(const string&ID)
{
    // displays menu after logging in
    string choice;
    bool isValid = false;
    cout<<"\n";
    cout<<"1-View your ProfileData \n";
    cout<<"2-Menu\n";
    cout<<"3-EXIT\n";

    while (!isValid)
    {
        isValid = true;
        cout<<">>>Enter your choice : ";
        cin>>choice;
        if(choice.size()>1||choice.empty()||choice[0]>'2'||choice[0]<'1')
        {
            cout<<">>>Invalid choice\n";
            isValid = false;
        }
    }
    if(choice[0]=='1')
    {
        cout<<stored[ID];
        loginMenu(ID);
    }
    else if(choice[0]=='2')
    {
        menu();
        checkChoice();
    }
    else
    {
        exit(0);
    }
}

//---------------------------------------------

void changePassword()
{
    //changing old password
    string ID = loginID();
    //user login first
    bool attempt = loginPassword(ID);
    //if logged in successfully we get the new password
    if(attempt)
    {
        string password = newPassword(ID);
        updatePassword(ID,password);
        cout<<">>>Password successfully updated\n";
        loginMenu(ID);
    }
    // else return to main menu
    else
    {
        menu();
        checkChoice();
    }
}

//---------------------------------------------

string newPassword(const string& ID)
{
    //getting new password
    string newPassword;
    string oldPassword;
    bool matching = false;
    cout<<"\n";

    cout<<"Changing Password\n";
    cout<<">>>oldPassword\n";
    //getting old one first
    for (int i = 3; i >0 ; --i)
    {
        cout<<">>>You have "<<i<<" attempts to Enter your old password\n";
        cout<<">>>Enter your old password : ";
        cin>>oldPassword;
        if(oldPassword==stored[ID].password)
        {
            matching = true;
            break;
        }
    }
    // if old password was successfully entered , we take the new Password
    if(matching)
    {
        cout<<"\n";
        cout<<">>>New";
        newPassword = verifyPassword();
        return newPassword;
    }
    // else if it was wrong we go back to the main menu
    else
    {
        cout<<">>>cannot change the password\n";
        menu();
        checkChoice();
    }
}

//---------------------------------------------

void updatePassword(const string& ID,const string& password)
{
    // updates password in the map and store the newPassword encrypted in the files

    //updates MAP
    stored[ID].password = password ;

    //Encrypts password to be stored in the file
    string Encrypted = password;
    Encrypted= encryptPassword(Encrypted);

    string fileName = ID+".txt";
    ofstream file;
    file.open(fileName);

    //updates Files
    file<<stored[ID].fullName<<'\n';
    file<<stored[ID].ID<<'\n';
    file<<stored[ID].email<<'\n';
    file<<Encrypted<<'\n';
    file<<stored[ID].phoneNumber<<'\n';
    file<<stored[ID].gender<<'\n';
    file<<stored[ID].age<<'\n';

    file.close();
}