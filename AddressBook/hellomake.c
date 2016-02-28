#include <hellomake.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>


static int dirt_flag;


int main(){
    

  FILE* begin_fileDATA;
	
	begin_fileDATA = fopen("data.dat", "rb+");
	
	FILE* begin_fileINDEX;
	
	if (!begin_fileDATA){
	    begin_fileDATA = fopen("data.dat", "wb");
	    begin_fileINDEX = fopen("index.idx", "wb");
	    dirt_flag=1;  // read from data file
	    fseek(begin_fileINDEX, 0, SEEK_SET);
            fwrite(&dirt_flag,sizeof(dirt_flag),1,begin_fileINDEX);
	}
        else{
	  
	         
	
	         begin_fileINDEX = fopen("index.idx", "rb+");
	
	
	
	        if (!begin_fileINDEX){
		AddIndexArrayfromDATA();
	        begin_fileINDEX = fopen("index.idx", "wb");
	        dirt_flag=1;  // read from data file
		fseek(begin_fileINDEX, 0, SEEK_SET);
                fwrite(&dirt_flag,sizeof(dirt_flag),1,begin_fileINDEX);
		}
	       else{
		 int f;
		 fseek(begin_fileINDEX, 0, SEEK_SET);
		 fread(&f, sizeof(f), 1, begin_fileINDEX);
		 
		 if(f==1){   AddIndexArrayfromDATA();  }
		 else if(f==0){	 AddIndexArrayfromINDEX();  }
		 
		 
	      }
	  
	 }
  
            fclose(begin_fileDATA);
	    fclose(begin_fileINDEX);
  
  
  
  
	int answer;
	

ab:
	
	printMenu(&answer);

	while (answer > 6 || answer < 1)
	{
		printf("\nEnter a valid choice by pressing ENTER key again");
		printMenu(&answer);
	}

	switch (answer)
	{
	case 1: AddData();
	       
		goto ab;
		break;
	case 2: printf("Enter the name to UPDATE RECORD :");
		char key3[22];
		fgets(key3, sizeof(key3),stdin);
		fgets(key3, sizeof(key3),stdin);
		
		 
		   IndexF who_update;
                who_update = findRecordByKey(key3);
		  if (strcmp(who_update.key, "NORESULT") != 0){   UpdateRecords(&who_update);}
 
		goto ab;
		break;
	case 3: printf("Enter the name to DELETE:");
	
		char key1[22];
		fgets(key1, sizeof(key1),stdin);
		fgets(key1, sizeof(key1),stdin);
		
		
		IndexF who7;
                who7 = findRecordByKey(key1);
            
		if (strcmp(who7.key, "NORESULT") != 0){  deleteRecordByID(&who7); }
		
		 
		goto ab;
		break;
	case 4: printf("Enter the name to SEARCH :");
		char key2[22];
		fgets(key2, sizeof(key2),stdin);
		fgets(key2, sizeof(key2),stdin);
		IndexF who5;
		who5 = findRecordByKey(key2);
		
		if (strcmp(who5.key, "NORESULT") != 0){
		AddressBook data3=Search(&who5);
			printf("*********Search Result**********\n");
			printf("the name : %s\n",data3.name);  
			printf("the surname : %s\n",data3.surname);  
			printf("the address : %s\n",data3.address);  
			printf("the city : %s\n",data3.city);  
			printf("the zipcode : %s\n",data3.zipcode);  
			printf("the phone numbers :\n");  
			printf("%s\n",data3.phone_numbers[0].phone); 
			printf("%s\n",data3.phone_numbers[1].phone);
			printf("the birth date : %s\n",data3.birth_date);  
			printf("the notes : %s\n",data3.notes); 
		}
		    
		goto ab;
		break;
	case 5: printf("List of the sorted File \n");
		char key5[3];
		fgets(key5, sizeof(key5),stdin);
		fgets(key5, sizeof(key5),stdin);
		printList(key5);
		goto ab;
		break;
	case 6: printf("Program is terminating \n");
		AddIndexFilefromARRAY();
		break;
	}
}
