#include <hellomake.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>


static int RECORD_COUNT=0; 
static int array_place=0;
static int dirt_flag;
IndexF book_index[10];

void printMenu(int* answer){
	printf("     MY ADDRESS BOOK APPLICATION \n");
	printf("Main Menu \n");
	printf("========================== \n");
	printf("(1) Add New Record \n");
	printf("(2) Update a Record \n");
	printf("(3) Delete a Record \n");
	printf("(4) Find a Record\n");
	printf("(5) List Records\n");
	printf("(6) Quit \n");
	printf("==========================\n");
	printf("\n");
	printf("Enter your choice ==>\n");
	scanf("%d", answer);
}

int compareBooks(const void* a, const void* b){
	return (strcmp(((IndexF*)a)->key, ((IndexF*)b)->key));
}


void AddData(){
	
	FILE* fd;
	
	fd = fopen("data.dat", "rb+");
	
	
	AddressBook book;
	
	printf("Enter the name :\n");  fgets(book.name, sizeof(book.name),stdin); fgets(book.name, sizeof(book.name),stdin);
	printf("Enter the surname :\n");  fgets(book.surname, sizeof(book.surname),stdin);
	printf("Enter the address :\n");  fgets(book.address, sizeof(book.address),stdin);
	printf("Enter the city :\n");  fgets(book.city, sizeof(book.city),stdin);
	printf("Enter the zipcode :\n");  fgets(book.zipcode, sizeof(book.zipcode),stdin);
	printf("Enter the phone numbers \n");
	printf("Phone1 :  \n");  fgets(book.phone_numbers[0].phone, sizeof(book.phone_numbers[0].phone),stdin);
	printf("Phone2 :  \n");  fgets(book.phone_numbers[1].phone, sizeof(book.phone_numbers[1].phone),stdin);
	printf("Enter the birth date :\n");  fgets(book.birth_date, sizeof(book.birth_date),stdin);
	printf("Enter the notes :\n");  fgets(book.notes, sizeof(book.notes),stdin);
		
	fseek(fd,0,SEEK_END);	
	
	fwrite(&book, sizeof(AddressBook) , 1, fd);
	
	   strcpy(book_index[RECORD_COUNT].key,book.name);
	   book_index[RECORD_COUNT].value=RECORD_COUNT;
	   
	  RECORD_COUNT++;
	 qsort(book_index, RECORD_COUNT, sizeof(IndexF), compareBooks);
	fclose(fd);
	
	

}

	void  AddIndexArrayfromDATA()
{      
	
	
	FILE* dataFile;
	dataFile = fopen("data.dat", "rb+");
	
        AddressBook p;
	
	int value_count=0;
	int count=0;
	
	fseek(dataFile, 0, SEEK_SET);
	
	while(fread(&p, sizeof(AddressBook), 1, dataFile)!=0){
      
	
	  
	  if(p.name[0]!= '!')
	  {
	  
	    strcpy(book_index[count].key,p.name);
	  
	    book_index[count].value=value_count;
	 
       
       
       count++;
	  }
	   value_count++;
	}
	
	RECORD_COUNT=count;
	qsort(book_index, count, sizeof(IndexF), compareBooks);
	fclose(dataFile);
	

	
	
}



void  AddIndexArrayfromINDEX()
{      
	
	
	FILE* index_file;
	index_file = fopen("index.idx", "rb+");
	
        IndexF indx;
	int f;
	
	int count_index=0;
	
	
	fseek(index_file, 0, SEEK_SET);
	fread(&f, sizeof(dirt_flag), 1, index_file);
		
	while(fread(&indx, sizeof(IndexF), 1, index_file)!=0){
      
	
	  book_index[count_index]=indx;
	 
	 
	  count_index++;
	  
	   
	}
	
	RECORD_COUNT=count_index;
		dirt_flag=1;  // read from data
		fseek(index_file, 0, SEEK_SET);
                fwrite(&dirt_flag,sizeof(dirt_flag),1,index_file);
	fclose(index_file);
	

	
}




  void AddIndexFilefromARRAY(){
    
  FILE* fi;
	
	fi = fopen("index.idx", "wb");
	
	
	        dirt_flag=0;  // read from index
		fseek(fi, 0, SEEK_SET);
                fwrite(&dirt_flag,sizeof(dirt_flag),1,fi);
	
		fseek(fi,0,SEEK_END);
		int k;
		for(k=0;k<RECORD_COUNT;k++){
		  
		   if(strcmp(&book_index[k].key[0], "!") != 0){
		  
		  fwrite(&book_index[k], sizeof(book_index[k]), 1, fi);}
		  
		  fseek(fi, 0, SEEK_END);
		}
		
	
	fclose(fi);
    
 }
 

IndexF binaryFileSearch(const char ID[22], int firstIdx, int lastIdx){
	
	
	IndexF returnData;

	// Calculate the middle Index
	int middleIdx = (firstIdx + lastIdx) / 2;
	printf("%d    ",middleIdx);

	// Read first record and return if it is the searched one.
	
	if (strcmp(book_index[firstIdx].key, ID) == 0)
	{
		
		returnData = book_index[firstIdx];
		array_place=firstIdx;
		return returnData;
	}
	// Read last record and return if it is the searched one.
	
	else if (strcmp(book_index[lastIdx].key, ID) == 0)
	{
		returnData = book_index[lastIdx];
		array_place = lastIdx;
		return returnData;
	}
	// Recursion exit condition, If middle index is equal to first or last index
	// required comparisons are already made, so record is not found.
	// Create and return an empty person.
	else if (middleIdx == firstIdx || middleIdx == lastIdx) {
		
	     printf("-----------NO RESULT----------\n");
	     IndexF r;
	     strcpy(r.key,"NORESULT");
	     return r;
	}

	// Read the middle record and return if it is the searched one.
	
	else if (strcmp(book_index[middleIdx].key, ID) == 0)
	{

		returnData = book_index[middleIdx];
		array_place  = middleIdx;
		return returnData;
	}
	// Determine the record position and recursively call with appropriate attributes.
	else if (strcmp(book_index[middleIdx].key, ID) > 0) {
		return binaryFileSearch( ID, firstIdx + 1, middleIdx - 1);
	}
	else {
		return binaryFileSearch( ID, middleIdx + 1, lastIdx - 1);
	}
}

IndexF findRecordByKey(char key[22]) {
	

	int firstIdx = 0;
	int lastIdx =RECORD_COUNT-1;
	

	// Initiate the search.
	IndexF result = binaryFileSearch(key, firstIdx, lastIdx);
	
	return result;
}

AddressBook Search(IndexF *who)
{
    
    
    AddressBook data;
		
        FILE* ff;
	ff = fopen("data.dat", "rb+");
    
	
	fseek(ff, who->value*sizeof(AddressBook), SEEK_SET);
	fread(&data, sizeof(data), 1, ff);
    

    
       fclose(ff);
  
       return data;
  
  
}

void printList(char key5[3]){
  bool control=false;
  int o;
  for(o=0;o<RECORD_COUNT;o++){
    
    if(book_index[o].key[0]==key5[0]){
      printf("%s",book_index[o].key);
      control=true;
    }
    
  }
  
  if(control==false){printf("---No REsult---\n");}
  
}


void UpdateRecords(IndexF *who_update){
  int answer_phone;
   int answer_update;
   char new[22];
  printf("Select number to update a record's part :\n");
  printf("1)Name\n");
    printf("2)Surname\n");
     printf("3)Address\n");
      printf("4)City\n");
       printf("5)Zipcode\n");
        printf("6)Phone Numbers\n");
	 printf("7)Birth Date\n");
	  printf("8)Notes\n");
	   scanf("%d", &answer_update);
	 
	   if(answer_update!=6){
	  
	  printf("Enter new words : \n");
	  fgets(new, sizeof(new),stdin); 
	   fgets(new, sizeof(new),stdin); 	   
	   }
	  
		   
		    AddressBook data_update;
		
                 FILE* fff;
	         fff = fopen("data.dat", "rb+");
    
	        fseek(fff, 0, SEEK_SET);
	        fseek(fff, who_update->value*sizeof(AddressBook), SEEK_SET);
	        fread(&data_update, sizeof(data_update), 1, fff);
                
		switch (answer_update)
	{
		 case 1:  strcpy(data_update.name,new);
		          strcpy(book_index[array_place].key,new);
		          qsort(book_index, RECORD_COUNT, sizeof(IndexF), compareBooks);
		 break;
		 case 2:  strcpy(data_update.surname,new);
		 break;
		 case 3:  strcpy(data_update.address,new);
		 break;
		 case 4:  strcpy(data_update.city,new);
		 break;
		 case 5:  strcpy(data_update.zipcode,new);
		 break;
		 case 6:  
		   
		   printf("Select number to phone :\n");
		   printf("1)Phone1\n");
	           printf("2)Phone2\n");
	           scanf("%d", &answer_phone);
		  
	          printf("Enter new phone : \n");
	          fgets(new, sizeof(new),stdin); 
	          fgets(new, sizeof(new),stdin); 
		   
		   if(answer_phone==1){strcpy(data_update.phone_numbers[0].phone,new);}
		   else {strcpy(data_update.phone_numbers[1].phone,new);}
		   
		   
		 break;
		 case 7:  strcpy(data_update.birth_date,new);
		 break;
		 case 8:  strcpy(data_update.notes,new);
		 break;
		
	}
	
	
		 fseek(fff, 0, SEEK_SET);
	         fseek(fff, who_update->value*sizeof(AddressBook), SEEK_SET);
		 fwrite(&data_update, sizeof(AddressBook), 1, fff);
		 fclose(fff);
	
			printf("the name : %s\n",data_update.name);  
			printf("the surname : %s\n",data_update.surname);  
			printf("the address : %s\n",data_update.address);  
			printf("the city : %s\n",data_update.city);  
			printf("the zipcode : %s\n",data_update.zipcode);  
			printf("the phone numbers :\n");  
			printf("%s\n",data_update.phone_numbers[0].phone); 
			printf("%s\n",data_update.phone_numbers[1].phone);
			printf("the birth date : %s\n",data_update.birth_date);  
			printf("the notes : %s\n",data_update.notes);
  
  
}



void deleteRecordByID(IndexF *who7)
{
	
	 AddressBook data9;
		
        FILE* ff;
	ff = fopen("data.dat", "rb+");
    
	fseek(ff, 0, SEEK_SET);
	fseek(ff, who7->value*sizeof(AddressBook), SEEK_SET);
	fread(&data9, sizeof(data9), 1, ff);
      data9.name[0]= '!';
          fseek(ff, 0, SEEK_SET);
          fseek(ff, who7->value*sizeof(AddressBook), SEEK_SET);
          fwrite(&data9,sizeof(AddressBook),1,ff);
       fclose(ff);
       
        strcpy(&book_index[array_place].key[0],"!");
        qsort(book_index, RECORD_COUNT, sizeof(IndexF), compareBooks);
       
}



