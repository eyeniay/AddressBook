
struct _PhoneNumbers{
  char phone[15];
};

typedef struct _PhoneNumbers PhoneNumbers;

struct _AddressBook {
	char name[22];
	char surname[22];
	char address[22];
	char city[10];
	char zipcode[10];
	PhoneNumbers phone_numbers[2];
	char birth_date[10];
	char notes[22];
	
};



struct _IndexF {
	char key[22];
	int value;
	
	
};



typedef struct _AddressBook AddressBook;

typedef struct _IndexF IndexF;

void  AddIndexArrayfromDATA();
void  AddIndexArrayfromINDEX();
void  AddIndexFilefromARRAY();
void  printIndexArray();
void  deleteRecordByID(IndexF *who7);
void AddData();
IndexF binaryFileSearch(const char ID[22], int firstIdx, int lastIdx);
IndexF findRecordByKey(char key[22]);
AddressBook Search(IndexF *who);
void printList(char key5[3]);
void UpdateRecords(IndexF *who_update);
void deleteRecordByID(IndexF *who7);
void printMenu(int* answer);
