# AddressBook
Address book application  with simple indexing

The application should be able to store information for typical address book entries, such as Name, Surname, Address, City, Zip code, several Phone numbers, Birth Date and additional Notes.

In order to index the file, I use simple indexing approach, as shown in Figure 1. In this approach the records are stored in data file in entry-sequenced order.  It means that new records are appended to end of file as they are entered.Additionally, the primary key of the system will be name+surname.
![ScreenShot](http://imageshack.com/a/img921/7908/ynlmOP.png)

Beside, a separate index file must be created with keysorting approach. It means that the index file only keeps primary key field and the pointer to the data file records. Index file is kept in sorted order, and when the application is started the whole file is read into RAM memory. Then all operations are handled through index file in RAM. When the user wants to exit, flush the whole index file into disk.  Deletion will simply mark a record to be deleted. Record will not be actually deleted from the data file. However it will actually be deleted from the index file.
![ScreenShot](http://imageshack.com/a/img922/4574/ldRayN.png) ![ScreenShot](http://imageshack.com/a/img922/6076/ocsNYy.png)
If the application encounters a run-time error, at that time synchronization between index and data file may fail since last update on index file on RAM not flushed into disk. I implement a solution can be adding a dirty-flag into index file header. During the program execution, in case of add, update or delete operations index structure in the RAM will change. Subsequent to this change, dirt-flag in the index file must be set. Therefore following a successful flushing of index file, I should re-set the dirty-flag. When you open the data file in next time, check this flag. If it is set it means the file is not closed properly so it requires reorganization (i.e., re-creation of the index file)
*******
I write a make file for my program.You can write "make" on program's directory to run  program
![ScreenShot](http://imageshack.com/a/img922/7786/yiYnoI.png)
![ScreenShot](http://imageshack.com/a/img923/2158/klHw37.png)
![ScreenShot](http://imageshack.com/a/img923/2366/OiCz8D.png)
![ScreenShot](http://imageshack.com/a/img922/7206/nD7I4v.png)
