#include<iostream>
#include<fstream>
using namespace std;

class Hotel {
 private :
     struct Node{
        int id,dat;
        string name,roomtype;
        Node*next;
     };
public:
  Node*head=NULL;
  void insert();
  void menu();
  void update();
  void search();
  void del();
  void sort();
  void show();
 
 void saveToFile();       // NEW
    void loadFromFile();     // NEW

};


void Hotel::menu(){

    int choice;
    cout<<"\n\tWelcome To Hotel Management System Application\n:"<<endl;
    cout<<"\n\t_____HOTEL MANAGEMENT SYSTEM_____";
    cout<<"\n\nS.NO      FUNCTION      DESCRIPTION"<<endl;
    cout<<"\n1.\tAllocate Room\t\t\tInsert New Room";
    cout<<"\n2.\tSearch Room\t\t\tSearch Room With Room ID";
    cout<<"\n3.\tUpdate Room\t\t\tUpdate Room Record";
    cout<<"\n4.\tDelete Room\t\t\tDelete Room with Room ID";
    cout<<"\n5.\tShow Room Records\t\t\tShow Room Records that (we added)";
    cout<<"\n6.\tExit"<<endl;

    cout<<"Enter your choice :"<<endl;
    cin>>choice;
    switch(choice){
        case 1 : 
           insert();
           menu();
           break;
        case 2 : 
           search();
           menu();
           break;
        case 3 : 
           update();
            menu();
           break;
        case 4 : 
           del();
            menu();
           break;
        case 5 : 
           sort();
           show();
            menu();
           break;
         case 6 :
           break;
         default :
            cout<<"Invalid";
        
    }

}

void Hotel::insert(){
    cout<<"\n\t_____HOTEL MANAGEMENT SYSTEM_____";

    Node *newNode = new Node;
    newNode->next = NULL;

    cout<<"\nEnter Room ID : ";
    cin>>newNode->id;

    cout<<"\nEnter Allocated Date: ";
    cin>>newNode->dat;

    cin.ignore(); // discard newline after integer input

    cout<<"\nEnter Customer Name: ";
    getline(cin, newNode->name);

    cout<<"\nEnter Room Type (single/double/twin): ";
    getline(cin, newNode->roomtype);

    Node* temp = head;
    while (temp != NULL) {
        if (temp->id == newNode->id) {
            cout << "\nRoom ID already exists. Insertion failed.\n";
            delete newNode;
            return;
        }
        temp = temp->next;
    }

    if(head == NULL){
        head = newNode;
    }
     else {
        Node* temp = head;
        while(temp->next != NULL){    //agr null nhi hai toh last ke node me insert krdo 
            temp = temp->next;
        }
        temp->next = newNode;
    }
    cout<<"\n\n\t\tNew Room Allocated Successfully.\n";
}


void Hotel::search() {
    cout << "\n\t_____HOTEL MANAGEMENT SYSTEM_____";

    if (head == NULL) {
        cout << "\n\nLinked List Empty\n";
        return;
    }

    int t_id;
    cout << "\n\nEnter Room ID to search: ";
    cin >> t_id;

    Node* temp = head;
    bool found = false;

    while (temp) {
        if (temp->id == t_id) {
            cout << "\nRoom Id: " << temp->id;
            cout << "\nCustomer Name: " << temp->name;
            cout << "\nAllocated Date: " << temp->dat;
            cout << "\nRoom Type: " << temp->roomtype << endl;
            found = true;
            break;
        }
        temp = temp->next;
    }

    if (!found) {
        cout << "\nRoom ID not found.\n";
    }
}


void Hotel::update() {
    cout << "\n\t_____HOTEL MANAGEMENT SYSTEM_____";

    if (head == NULL) {
        cout << "\n\nLinked List Empty\n";
        return;
    }

    int t_id;
    cout << "\n\nEnter Room ID to update: ";
    cin >> t_id;

    Node* temp = head;
    bool found = false;

    while (temp != NULL) {
        if (temp->id == t_id) {
            cout << "\nCurrent Data:";
            cout << "\nRoom Id: " << temp->id;
            cout << "\nCustomer Name: " << temp->name;
            cout << "\nAllocated Date: " << temp->dat;
            cout << "\nRoom Type: " << temp->roomtype << endl;

            cout << "\n\nEnter new Allocated Date: ";
            cin >> temp->dat;

            cin.ignore(); // clear leftover newline

            cout << "\nEnter new Customer Name: ";
            getline(cin, temp->name);

            cout << "\nEnter new Room Type: ";
            getline(cin, temp->roomtype);

            cout << "\n\n\t\tUpdated Record Successfully.\n";

            found = true;
            break;
        }
        temp = temp->next;
    }

    if (!found) {
        cout << "\nRoom ID not found.\n";
    }
}


void Hotel::del() {
    cout << "\n\t_____HOTEL MANAGEMENT SYSTEM_____";

    if (head == NULL) {
        cout << "\n\nLinked List Empty\n";
        return;
    }

    int t_id;
    cout << "\n\nEnter Room ID to delete: ";
    cin >> t_id;

    // Case 1: head node matches
    if (t_id == head->id) {
        Node* temp = head;
        head = head->next;
        delete temp;
        cout << "Deleted Record Successfully\n";
        return;
    }

    // Case 2: search rest of list
    Node* prev = head;
    Node* curr = head->next;
    bool found = false;

    while (curr != NULL) {
        if (curr->id == t_id) {
            prev->next = curr->next;
            delete curr;
            cout << "Deleted Record Successfully\n";
            found = true;
            break;
        }
        prev = curr;
        curr = curr->next;
    }

    if (!found) {
        cout << "Room ID not found.\n";
    }
}


void Hotel::show() {
    cout << "\n\t_____HOTEL MANAGEMENT SYSTEM_____";

    if (head == NULL) {
        cout << "\n\nNo records to display.\n";
        return;
    }

    Node* ptr = head;
    cout << "\n\n--- Room Records ---\n";

    while (ptr != NULL) {
        cout << "--------------------------------\n";
        cout << "Room ID         : " << ptr->id << endl;
        cout << "Customer Name   : " << ptr->name << endl;
        cout << "Allocated Date  : " << ptr->dat << endl;
        cout << "Room Type       : " << ptr->roomtype << endl;
        cout << "--------------------------------\n";
        ptr = ptr->next;
    }
}

void Hotel::saveToFile() {
    ofstream fout("hotel_data.txt");

    Node* ptr = head;
    while (ptr != NULL) {
        fout << ptr->id << endl;
        fout << ptr->dat << endl;
        fout << ptr->name << endl;
        fout << ptr->roomtype << endl;
        fout << "---" << endl;  // separator between records
        ptr = ptr->next;
    }

    fout.close();
    cout << "\nData saved to hotel_data.txt\n";
}

void Hotel::loadFromFile() {
    ifstream fin("hotel_data.txt");

    if (!fin.is_open()) {
        cout << "\nNo existing data file found. Starting fresh.\n";
        return;
    }

    while (!fin.eof()) {
        Node* newNode = new Node;
        string separator;

        fin >> newNode->id;
        fin >> newNode->dat;
        fin.ignore();
        getline(fin, newNode->name);
        getline(fin, newNode->roomtype);
        getline(fin, separator);

        if (fin.fail()) {
            delete newNode;
            break;
        }

        newNode->next = NULL;

        if (head == NULL) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    fin.close();
    cout << "\nData loaded from hotel_data.txt\n";
}


void Hotel::sort() {
    if (head == NULL) {
        cout << "\n\nLinked list Empty\n";
        return;
    }

    Node* i = head;

    while (i != NULL) {
        Node* minNode = i;
        Node* j = i->next;

        // Find minimum ID node in the unsorted part
        while (j != NULL) {
            if (j->id < minNode->id) {
                minNode = j;
            }
            j = j->next;
        }

        // Swap data between i and minNode if needed
        if (minNode != i) {
            swap(i->id, minNode->id);
            swap(i->dat, minNode->dat);
            swap(i->name, minNode->name);
            swap(i->roomtype, minNode->roomtype);
        }

        i = i->next;
    }

    cout << "\n\nList sorted by Room ID successfully.\n";
}

int main(){
   Hotel h;
   h.loadFromFile();  // Load existing data from file at start
    h.menu();
    h.saveToFile();    // Save data to file when exiting menu
    return 0;
}