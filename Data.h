#ifndef CS112_2022_2ND_S25_S26_20210069_20210216_20210084_A4_USERDATA_H
#define CS112_2022_2ND_S25_S26_20210069_20210216_20210084_A4_USERDATA_H
#include <iostream>
using namespace std;
#include <map>
struct Data{
    string fullName;
    string ID;
    string email;
    string password;
    string phoneNumber;
    string gender;
    string age;

    Data()
    {
        fullName="Not Specified";
        ID="Not Specified";
        email="Not Specified";
        password="Not Specified";
        phoneNumber="Not Specified";
        gender="Not Specified";
        age="Not Specified";
    }
};
ostream& operator<<(ostream& out,Data&data);
void menu();
void checkChoice();
void generateFile();
void fetchIDs();
void fetchData();
void registerUser();
string verifyFirstName();
string verifyMiddleName();
string verifyLastName();
string verifyID();
string verifyEmail();
string verifyPassword();
string encryptPassword(string& password);
string decryptPassword(string& password);
string verifyPhoneNumber();
string verifyGender();
string verifyAge();
void storeUser(const Data& userData);
void login();
string loginID();
bool loginPassword(const string& ID);
void loginMenu();
void loginMenu(const string& ID);
void changePassword();
string newPassword(const string& ID);
void updatePassword(const string& ID,const string& password);
#endif //CS112_2022_2ND_S25_S26_20210069_20210216_20210084_A4_USERDATA_H
