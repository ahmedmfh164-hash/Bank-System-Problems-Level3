#include<string>
#include<vector>
#include <iostream>
#include<iomanip>
#include <fstream>
using namespace std;

const string ClientsFileName = "Clients.txt";

enum enMainMenueList {
    ShowAllClients = 1, AddClient = 2, DeleteClient = 3,
    UpdateClient = 4, FindClient = 5, Exit = 6
};

struct stClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelete = false;
};

void GoBackToMainMenue(vector<stClient>& vClient);

vector<string> SplitString(string S1, string delim)
{
    vector<string>vString;

    short pos = 0;
    string sword;//define a string variable

    //use find() function to get the position of the delimiters
    while ((pos = S1.find(delim)) != std::string::npos)
    {
        sword = S1.substr(0, pos);//store the word
        if (sword != "")
        {
            vString.push_back(sword);
        }
        S1.erase(0, pos + delim.length());//erase() until position and move to next word

    }
    if (S1 != "")
    {
        vString.push_back(S1);//it print last word of the string
    }

    return vString;
}

stClient ConvertLineToRecord(string Line, string sperator = "#//#")
{
    stClient Data;
    vector<string>vString;

    vString = SplitString(Line, sperator);

    if (vString.size() < 5)
        return Data;

    Data.AccountNumber = vString[0];
    Data.PinCode = vString[1];
    Data.Name = vString[2];
    Data.Phone = vString[3];
    Data.AccountBalance = stod(vString[4]);//cast string to double

    return Data;

}

vector<stClient> LoadClientsDataFromFile(string FileName)
{
    vector<stClient>vClient;
    fstream MyFile;
    MyFile.open(FileName, ios::in);

    if (MyFile.is_open())
    {
        string Line;
        stClient Client;

        while (getline(MyFile, Line))
        {
            Client = ConvertLineToRecord(Line);
            vClient.push_back(Client);
        }

        MyFile.close();

    }

    return vClient;
}

void PrintClientRecord(stClient Client)
{
    cout << "| " << setw(18) << left << Client.AccountNumber;
    cout << "| " << setw(14) << left << Client.PinCode;
    cout << "| " << setw(33) << left << Client.Name;
    cout << "| " << setw(17) << left << Client.Phone;
    printf("| %.f", Client.AccountBalance);
}

void PrintAllClientData(vector<stClient>& vClient)
{
    stClient Client;

    cout << "\n\t\t\t\t\t1Client List (" << vClient.size() << ") Client (s).";
    cout << "\n========================================================";
    cout << "========================================================\n";

    cout << "| " << left << setw(18) << "Account Number";
    cout << "| " << left << setw(14) << "Pin Code";
    cout << "| " << left << setw(33) << "Client Name";
    cout << "| " << left << setw(17) << "Phone";
    cout << "| " << left << setw(15) << "Balance";

    cout << "\n========================================================";
    cout << "========================================================\n";

    if (vClient.size() == 0)
    {
        cout << "\n\t\t\tNo Clients Available In the System!\n";
    }
    else
        for (stClient Client : vClient)
        {
            PrintClientRecord(Client);
            cout << endl;
        }
    cout << "--------------------------------------------------";
    cout << "--------------------------------------------------------------\n";

    cout << "\n";



}

string ConvertRecordToLine(stClient Client, string sperator = "#//#")
{
    string stClientRecord = "";

    stClientRecord += Client.AccountNumber + sperator;
    stClientRecord += Client.PinCode + sperator;
    stClientRecord += Client.Name + sperator;
    stClientRecord += Client.Phone + sperator;
    stClientRecord += to_string(Client.AccountBalance);

    return stClientRecord;

}

void AddClientToFile(string FileName, string DataLine)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app);

    if (MyFile.is_open())
    {

        MyFile << DataLine << endl;

        MyFile.close();
    }

}

bool ClientExistsByAccountNumber(string AccountNumber, string FileName)
{
    vector<stClient>vClient;
    fstream MyFile;
    MyFile.open(FileName, ios::in);

    if (MyFile.is_open())
    {
        string Line;
        stClient Client;

        while (getline(MyFile, Line))
        {
            Client = ConvertLineToRecord(Line);
            if (Client.AccountNumber == AccountNumber)
            {
                MyFile.close();
                return true;
            }
            vClient.push_back(Client);
        }

        MyFile.close();

    }

    return false;
}

stClient ReadClientData()
{
    stClient Client;

    cout << "--------------------------------------------------------------\n";

    cout << "\nEnter Account Number : ";
    getline(cin >> ws, Client.AccountNumber);

    while (ClientExistsByAccountNumber(Client.AccountNumber, ClientsFileName))
    {
        cout << "\nClient with [" << Client.AccountNumber << "] already exists, Enter another Account Number : ";
        getline(cin >> ws, Client.AccountNumber);
    }

    cout << "--------------------------------------------------------------\n";

    cout << "\nEnter PinCode        : ";
    getline(cin >> ws, Client.PinCode);

    cout << "--------------------------------------------------------------\n";

    cout << "\nEnter Name           : ";
    getline(cin, Client.Name);

    cout << "--------------------------------------------------------------\n";

    cout << "\nEnter Phone          : ";
    getline(cin, Client.Phone);

    cout << "--------------------------------------------------------------\n";

    cout << "\nEnter Account Balance: ";
    cin >> Client.AccountBalance;

    cout << "--------------------------------------------------------------\n";

    return Client;

}

void AddNewClient()
{

    cout << "================================================================================\n";
    cout << "\n\t\t\tShow Add New Client Screen\n\n";
    cout << "================================================================================\n";

    stClient Client = ReadClientData();
    AddClientToFile(ClientsFileName, ConvertRecordToLine(Client));


}

void ShowAddNewClientsScreen(vector<stClient>& vClient)
{
    char AddMore = 'Y';

    do
    {
        system("cls");

        AddNewClient();
        vClient = LoadClientsDataFromFile(ClientsFileName);

        cout << "\nClient Added Successfully !\nDo you want to add more clients? Y/N ? ";
        cin >> AddMore;
    } while (toupper(AddMore) == 'Y');


}

void PrintClientCard(stClient& Client)
{
    cout << "\n==============================================================\n";
    cout << "\n\tThe following are the client details : \n";
    cout << "\n==============================================================\n";

    cout << "# Account number : " << Client.AccountNumber;
    cout << "\n--------------------------------------------------------------\n";
    cout << "# Pin Code       : " << Client.PinCode;
    cout << "\n--------------------------------------------------------------\n";
    cout << "# Client Name    : " << Client.Name;
    cout << "\n--------------------------------------------------------------\n";
    cout << "# Phone          : " << Client.Phone;
    cout << "\n--------------------------------------------------------------\n";
    printf("# Account Balance: %.f", Client.AccountBalance);
    cout << "\n--------------------------------------------------------------\n";

}

bool FindClientDataByAccountNumber(string AccountNumber, vector<stClient>& vClient, stClient& Client)
{

    for (const stClient& C : vClient)
    {
        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }
    }
    return false;
}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector<stClient>& vClient)
{
    for (stClient& C : vClient)
    {
        if (C.AccountNumber == AccountNumber)
        {
            C.MarkForDelete = true;
            return true;
        }
    }
    return false;
}

vector<stClient>SaveClientDataToFile(string FileName, vector<stClient>& vClient)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out);//overWrite

    string DataLine;

    if (MyFile.is_open())
    {
        for (stClient C : vClient)
        {
            if (C.MarkForDelete == false) {
                //we only write records that are not marked for delete

                DataLine = ConvertRecordToLine(C);
                MyFile << DataLine << endl;

            }

        }
        MyFile.close();
    }
    return vClient;

}

bool DeleteClientByAccountNumber(string AccountNumber, vector<stClient>& vClient)
{
    stClient Client;
    char Answer = 'n';

    if (FindClientDataByAccountNumber(AccountNumber, vClient, Client))
    {
        PrintClientCard(Client);

        cout << "\n\nAre sure you want delete this client ? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            MarkClientForDeleteByAccountNumber(AccountNumber, vClient);
            SaveClientDataToFile(ClientsFileName, vClient);

            //refresh Clints
            vClient = LoadClientsDataFromFile(ClientsFileName);

            cout << "\n\nClient Deleted Succefully . \n";
            return true;
        }

    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found ! ";
        return false;
    }


}

string ReadClientAccountNumber()
{
    string AccountNumber = "";

    cout << "\nPlease enter AccountNumber ? ";
    cin >> AccountNumber;

    return AccountNumber;
}

void ShowDeleteClientScreen(vector<stClient>& vClient)
{

    cout << "================================================================================\n";
    cout << "\n\t\t\t\tShow Delete Screen\n\n";
    cout << "================================================================================\n";

    string AccountNumber=ReadClientAccountNumber();
    DeleteClientByAccountNumber(AccountNumber, vClient);
    
}

void DeleteClients(vector<stClient>& vClient)
{
    stClient Client;
    char DeleteMore = 'Y';

    do
    {
        ShowDeleteClientScreen(vClient);
        cout << "\n\nDo you want to delete another client? Y/N ? ";
        cin >> DeleteMore;
    } while (toupper(DeleteMore) == 'Y');

}

void FindClientByAccountNumber(string AccountNumber, vector<stClient>& vClient, stClient& Client)
{

    if (FindClientDataByAccountNumber(AccountNumber, vClient, Client))
    {
        PrintClientCard(Client);
    }
    else
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found ! ";


}

void ShowFindClientScreen(vector<stClient>& vClient)
{
    cout << "=============================================================================\n";
    cout << "\n\t\t\t\tShow Find Screen\n\n";
    cout << "=============================================================================\n";

    stClient Client;

    string AccountNumber = ReadClientAccountNumber();

    FindClientByAccountNumber(AccountNumber, vClient, Client);

}

void FindClients(vector<stClient>& vClient)
{
   
    char FindMore = 'Y';

    do
    {
        ShowFindClientScreen(vClient);
       
        cout << "\n\nDo you want to find another client? Y/N ? ";
        cin >> FindMore;
    } while (toupper(FindMore) == 'Y');

}

stClient ChangeClientRecord(string AccountNumber)
{
    stClient Client;

    Client.AccountNumber = AccountNumber;

    cout << "\n--------------------------------------------------------------\n";

    cout << "\nEnter PinCode        : ";
    getline(cin >> ws, Client.PinCode);

    cout << "--------------------------------------------------------------\n";

    cout << "\nEnter Name           : ";
    getline(cin, Client.Name);

    cout << "--------------------------------------------------------------\n";

    cout << "\nEnter Phone          : ";
    getline(cin, Client.Phone);

    cout << "--------------------------------------------------------------\n";

    cout << "\nEnter Account Balance: ";
    cin >> Client.AccountBalance;

    cout << "--------------------------------------------------------------\n";

    return Client;

}

bool UpdateClientByAccountNumber(string AccountNumber, vector<stClient>& vClient)
{
    stClient Client;
    char Answer = 'n';

    if (FindClientDataByAccountNumber(AccountNumber, vClient, Client))
    {
        PrintClientCard(Client);

        cout << "\n\nAre sure you want update this client ? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            for (stClient& C : vClient)
            {
                if (C.AccountNumber == AccountNumber)
                {
                    C = ChangeClientRecord(AccountNumber);
                    break;
                }
            }


            SaveClientDataToFile(ClientsFileName, vClient);
            vClient = LoadClientsDataFromFile(ClientsFileName);

            cout << "\n\nClient Updated Succefully . \n";
            return true;
        }

    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found ! ";
        return false;
    }


}

void ShowUpdateClientScreen()
{
    cout << "==============================================================================\n";
    cout << "\n\t\t\t\tShow Update Screen\n\n";
    cout << "==============================================================================\n";

    vector<stClient>vClient = LoadClientsDataFromFile(ClientsFileName);

    string AccountNumber = ReadClientAccountNumber();

    UpdateClientByAccountNumber(AccountNumber, vClient);


}

void ShowEndScreen()
{
    system("cls");
    cout << "============================================================\n";
    cout << "\n\n\t\t\tEXIT PROGRAM\n\n";
    cout << "\n============================================================\n";
}

void PerformMainMenueOption(vector<stClient>& vClient)
{
    int Choose;

    cout << "\nChoose what do you want to do ? [1 to 6] ?    ";
    cin >> Choose;

    switch (Choose)
    {

    case enMainMenueList::ShowAllClients:
        system("cls");
        PrintAllClientData(vClient);
        GoBackToMainMenue(vClient);
        break;

    case enMainMenueList::AddClient:
        
        ShowAddNewClientsScreen(vClient);
        GoBackToMainMenue(vClient);
        break;

    case enMainMenueList::DeleteClient:
        system("cls");
        DeleteClients(vClient);
        GoBackToMainMenue(vClient);
        break;

    case enMainMenueList::UpdateClient:
        system("cls");
        ShowUpdateClientScreen();
        GoBackToMainMenue(vClient);
        break;

    case enMainMenueList::FindClient:
        system("cls");
        FindClients(vClient);
        GoBackToMainMenue(vClient);
        break;

    case enMainMenueList::Exit:
        system("cls");
        ShowEndScreen();
        break;

    default:
    {
        cout << "\nSorry, this choice does not exist.\n";
        PerformMainMenueOption(vClient);
    }

    }

}

void ShowMainMenueScreen(vector<stClient>& vClient)
{

    cout << "================================================================\n\n";
    cout << "\t\t\tMain Menue Screen\n\n";
    cout << "================================================================\n\n";
    cout << "\t\t[1] Show All Clients List.\n\n";
    cout << "\t\t[2] Add New Client.\n\n";
    cout << "\t\t[3] Delete Client.\n\n";
    cout << "\t\t[4] Update Client Info.\n\n";
    cout << "\t\t[5] Find Client.\n\n";
    cout << "\t\t[6] Exit.\n\n";
    cout << "================================================================\n\n";

    PerformMainMenueOption(vClient);

}

void GoBackToMainMenue(vector<stClient>& vClient)
{
    /* char Back = 'B';

     do
     {
         cout << "\n\nEnter [B Or b] To Back To Main Menue List : ";
         cin >> Back;
         system("cls");

         ShowMainMenueScreen(vClient,Client);

     } while (toupper(Back) == 'B');*/

    cout << "\n\nPress any Key go back to main menue ...";
    system("pause>0");
    system("cls");
    ShowMainMenueScreen(vClient);

}

int main()
{

    vector<stClient>vClient = LoadClientsDataFromFile(ClientsFileName);

        ShowMainMenueScreen(vClient);
    

    system("pause>0");
}
