//  A menu driven program that demonstrate the functionality of Files and directories. The menu displays
//  option to perform oprations like get system date, set system date, retrieve the attributes of the file.
//
//  File : source.cpp
//
/*Program : Files and Directories.
This programms perform following operations of files and directories :
1. A's Logic
2. B's Logic
3. C's Logic
4. D's Logic
*/
//  Name : Priyanka Chordia.
//  Date : 10/24/14
//  Course : CSCI 511
//
//  
//  Change Log:
//  User    Date    Description
//  --------------------------------------------------------
//  PC  10/19/2014  Started with program. Created source.cpp
//  PC  10/20/2014  Created Alogic(), Blogic() function in source.cpp
//  PC  10/21/2014  Created Clogic(), Dlogic()function in source.cpp
//  PC  10/21/2014  Created removeback(),displayfront() and displayback() function in source.cpp 
//  PC  10/22/2014  Updated Alogic() code as required.
//  PC  10/22/2014  Updated Blogic() code as required.
//  PC  10/23/2014  Updated Clogic() code as required.
//  PC  10/23/2014  Updated Dlogic() code as required.
//  PC  10/24/2014  Updated the code file final which is ready to execute.

///////////////////////////////////////////////////////////////////////////////
//Header Files used for the program
#include <iostream>
#include <ctime>
#include <vector>
#include <map>
#include <string>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <glob.h>
#include <fstream>
#include <sys/time.h>

///////////////////////////////////////////////////////////////////////////////
// Standard namespace used so that we don't need to define a definition for every variable.

using namespace std;

// A global variable to store the data.
char buffer[80];

// Global function for performing the various logics of the code.

void Alogic(); // Function for performing the basic functionalities of files and directories.
void Blogic(); // Function to set date and time for a given file.
void Clogic(); // Function to set the date and time for all files in a specified directory.
void Dlogic(); // Function to implement a 'Compare file' and perform the various files and directories operations.
void compare_files(); // For comparing the files in a directory.
string getFilePermission(class stat statBuf); //To recieve the permission of accessing a file.
vector<vector <string> > getFileAttributeOfDir(string dir_name); // To recieve the attributes of a directory.

///////////////////////////////////////////////////////////////////////////////
/*Fn: displayMenu()

Description: This function displays the menu options present for executing the code.

In: N/A

Out: Message of getting a choice for menu.

*/


void displayMenu()
{
   cout << "================= Files and directories ===================" << endl;
   cout << "1. A's logic " << endl;
   cout << "2. B's logic " << endl;
   cout << "3. C's logic " << endl;
   cout << "4. D's logic " << endl;
   cout << "5. Exit" << endl;
   cout << "===========================================================" << endl;
   cout << "Enter your choice ";
}

///////////////////////////////////////////////////////////////////////////////
/*Fn: main()

Description: This function is the entry point of the program and all the operations of the program are performed from this code.

In: menuChoice- to accept the choice from the user for menu.

Out: N/A

*/


int main()
{
   int menuChoice;   // Variable to input the choice of the menu.
   do
   {
      displayMenu(); // Call to the displayMenu() function.
      cin >> menuChoice; // Accept the choice
      switch(menuChoice) // Switch case to select from menu options provided.
      {
         case 1:
            {
            Alogic(); // Function call to the basic functionalities of files and directories.
            break;
            }

         case 2:
            {
            Blogic(); // Function to set date and time for a file in directory.
            break;
            }

         case 3:
            {
            Clogic(); // Function to set date and time for all the files in the directory.
            break;
            }

         case 4:
            {
            Dlogic(); // Function to implement 'Compare File' for the files in the directories.
            break;
            }

         case 5:
            {
            cout << "Exiting ... " << endl; // To exit from the program.
            break;
            }

         default:
            {
            cout << "Wrong menu choice " << endl;
            break;
            }
      }
   }while(menuChoice != 5);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
/*Fn: Alogic()

Description: This function performs the basic functionalities of files and directories.

In: start_time,End_time - To store the start and end time of a file.

     dir-name - to store the name of the directory.

Out: Displays the time, date of directory and files.

*/

void Alogic()
{
   timeval start_time, end_time; // Stores the start and end time of a file.
	gettimeofday(&start_time, NULL);
   //get system date and time
   time_t rawtime;
   time(&rawtime);
   cout << " Current Date and Time " << ctime(&rawtime) << endl;

   //get directory name
   //string dir_name("/Users/511/idfiles/test2");
   string dir_name; // To store the name of the directory.
   cout<<" Enter directory name : ";
   cin>>dir_name;

   //get files attribute 
   vector<vector <string> > file_attr_vect  = getFileAttributeOfDir(dir_name);

   //iterate over vector and print out values
   vector<vector <string> >:: iterator row;
   vector<string>:: iterator col;
   ofstream myFile; // Creates a output file.
   myFile.open("output.txt");
   cout<<"Name \t Attributes\t Date of Creation\t\t Date of Modification\n";
   myFile <<"Name \t Size\t Attributes\t Date of Creation\t\t Date of Modification\n";
   for(row = file_attr_vect.begin(); row != file_attr_vect.end(); row++)
   {
      for(col = row->begin(); col != row->end(); col++)
      {
         string str = *col;
         str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
         //Print output directory
         cout << str <<"\t" ;
         myFile << str;
         myFile << "\t\t";
      }
      cout<<endl;
      myFile << "\n";
   }
   myFile.close();
	gettimeofday(&end_time, NULL);
   
   //compare files
   compare_files();
	double temp_time ;
   temp_time = (end_time.tv_sec - start_time.tv_sec) * 1000.0;
	temp_time += (end_time.tv_usec - start_time.tv_usec) / 1000.0;
   cout << "Time taken to execute A's logic " << temp_time << endl;
}

///////////////////////////////////////////////////////////////////////////////
/*Fn: comapre_files()

Description: This function comapres the contents of two files.

In: opFile - output file handler.
   
    compareFile - comapre file handler.

Out: Comapres the contents of the file.

*/

void compare_files()
{
  //output file handler
  ifstream opFile; 
  //compare file handler
  ifstream compareFile; 

  opFile.open("output.txt");
  compareFile.open("compare.txt");
  string opLine,compareLine;
  //map<string, vector<string> > opMap;
  //map<string, vector<string> > compareMap;
  map<string,string> opMap;
  map<string,string> compareMap;
  int line_number =0;
  while(std::getline(opFile, opLine))
  {
        string key;
        //opVector.push_back(opLine); 
        char *pch=NULL;
        pch = strtok(&opLine[0], "\t");
        if(pch!=NULL)
        {
           key = pch; 
           opMap[key] = opLine;
        }
  }
  int counter = 0;
  while(std::getline(compareFile, compareLine))
  {
        //In order to avoid first 2 lines
        if(counter < 3)
        {
           counter++;
           continue;
        }
        string key;
        //compareVector.push_back(compareLine); 
        char *pch=NULL;
        pch = strtok(&compareLine[0], "\t");
        if(pch!=NULL)
        {
           key = pch; 
           compareMap[key] = compareLine;
        }
  }
  opFile.close();
  compareFile.close();

  ofstream changeFile; 
  changeFile.open("changefile.txt");

  map<string, string>::iterator op_it;
  changeFile << "output.txt\n";
  for(op_it = opMap.begin() ; op_it != opMap.end() ; ++op_it)
  {
      string key = op_it->first;
      map<string, string>::iterator compare_it = compareMap.find(key);
      if(compare_it == compareMap.end() )
      {
         changeFile << op_it->second;
         changeFile << "\n";
      }
      else
      {
         string opValue = op_it->second;
         string compareValue = compare_it->second;

         opValue.erase(std::remove(opValue.begin(), opValue.end(), '\n'), opValue.end());
         opValue.erase(std::remove(opValue.begin(), opValue.end(), '\t'), opValue.end());

         compareValue.erase(std::remove(compareValue.begin(), compareValue.end(), '\n'), compareValue.end());
         compareValue.erase(std::remove(compareValue.begin(), compareValue.end(), '\t'), compareValue.end());

         if(opValue.compare(compareValue) != 0)
         {
            changeFile << op_it->second;
            changeFile << "\n";
         }

      }
  }

  
  map<string, string>::iterator compare_it;
  changeFile << "compare.txt\n";

  for(compare_it = compareMap.begin() ; compare_it != compareMap.end() ; ++compare_it)
  {
      string key = compare_it->first;
      op_it = opMap.find(key);
      if(op_it == opMap.end() )
      {
         changeFile << compare_it->second;
         changeFile << "\n";
      }
      else
      {
         string opValue = op_it->second;
         string compareValue = compare_it->second;

         opValue.erase(std::remove(opValue.begin(), opValue.end(), '\n'), opValue.end());
         opValue.erase(std::remove(opValue.begin(), opValue.end(), '\t'), opValue.end());

         compareValue.erase(std::remove(compareValue.begin(), compareValue.end(), '\n'), compareValue.end());
         compareValue.erase(std::remove(compareValue.begin(), compareValue.end(), '\t'), compareValue.end());

         if(compareValue.compare(opValue) != 0)
         {
            changeFile << compare_it->second;
            changeFile << "\n";
         }

      }
  }
  changeFile.close();
  
}


vector<vector <string> > getFileAttributeOfDir(string path)
{
   //TODO replace it with dynamic varibles
   glob_t gl;
   size_t num = 0;
   string search_pattern = path;
   search_pattern.append("/*");
   if(glob(search_pattern.c_str(), GLOB_NOSORT, NULL, &gl) == 0)
     num = gl.gl_pathc;
   globfree(&gl);

   vector<vector<string> > arr(num+2, vector<string>(6));
   DIR * dr = opendir(path.c_str());
   struct dirent * drnt;
   
   //file index
   int i =0;
   while( (drnt = readdir(dr) ) != NULL )
   {
      //attribute index
      int j =0;
      class stat statBuf;
      int isFolder;
      char fullPath[PATH_MAX];

      strcpy(fullPath, path.c_str());
      strcat(fullPath, "/");
      strcat(fullPath, drnt->d_name);

      if( stat(fullPath, &statBuf) < 0 )
         //return false;

      isFolder = S_ISDIR(statBuf.st_mode);

      //add elements to vector
      arr[i][j++] = drnt->d_name;
      arr[i][j++] = std::to_string(statBuf.st_size);
      arr[i][j++] = getFilePermission(statBuf);
      arr[i][j++] = ctime(&statBuf.st_birthtime);
      arr[i][j++] = ctime(&statBuf.st_mtime);

      i++;
   }

   return arr;
}

///////////////////////////////////////////////////////////////////////////////
/*Fn: getFilePermission()

Description: This function obtains the permission of the file.

In: str - to get the input.

Out: N/A

*/

string getFilePermission(class stat statBuf)
{
   string str = "";
   str.append( (S_ISDIR(statBuf.st_mode)) ? "d" : "-");
   str.append( (statBuf.st_mode & S_IRUSR) ? "r" : "-");
   str.append( (statBuf.st_mode & S_IWUSR) ? "w" : "-");
   str.append( (statBuf.st_mode & S_IXUSR) ? "x" : "-");
   str.append( (statBuf.st_mode & S_IRGRP) ? "r" : "-");
   str.append( (statBuf.st_mode & S_IWGRP) ? "w" : "-");
   str.append( (statBuf.st_mode & S_IXGRP) ? "x" : "-");
   str.append( (statBuf.st_mode & S_IROTH) ? "r" : "-");
   str.append( (statBuf.st_mode & S_IWOTH) ? "w" : "-");
   str.append( (statBuf.st_mode & S_IXOTH) ? "x" : "-");
   
   return str;
}

void Blogic()
{
   string file_name;
   cout<<" Enter file name : ";
   cin>>file_name;
   time_t currentTime;
   time(&currentTime);
   //Date format
   //[[CC]YY]MMDDhhmm.SS
   string year, month, date, hour, min, seconds;
   cout << "Enter Year(YYYY) :" ;
   cin >> year;
   cout << "\nEnter Month(MM) : " ;
   cin >> month;
   cout << "\nEnter Date(DD) : " ;
   cin >> date;
   cout << "\nEnter Hour(HH) : ";
   cin >> hour;
   cout << "\nEnter Min(MM) : ";
   cin >> min;
   cout << "\nEnter Sec(SS) : ";
   cin >> seconds;

   /*
   char str[15];// = std::to_string(year);
   sprintf(str,"%d%d%d%d.%d",year,month, date, hour, min, seconds);
   str = str + std::to_string(month);
   str = str + std::to_string(date);
   str = str + std::to_string(hour);
   str = str + std::to_string(min);
   str = str + std::to_string(seconds);
   */
   

   //string str = "201410101740.45";
   string str = year + month + date + hour + min + "." + seconds;
   string command = "touch -mt " + string(str) + " " + file_name;
   //TODO remove cout
   system(command.c_str());
}

void Clogic()
{
   string dir_name;
   cout<<" Enter directory name : ";
   cin>>dir_name;
   //Date format
   //[[CC]YY]MMDDhhmm.SS

   DIR * dr = opendir(dir_name.c_str());
   struct dirent * drnt;

   string year, month, date, hour, min, seconds;
   cout << "Enter Year(YYYY) :" ;
   cin >> year;
   cout << "\nEnter Month(MM) : " ;
   cin >> month;
   cout << "\nEnter Date(DD) : " ;
   cin >> date;
   cout << "\nEnter Hour(HH) : ";
   cin >> hour;
   cout << "\nEnter Min(MM) : ";
   cin >> min;
   cout << "\nEnter Sec(SS) : ";
   cin >> seconds;

   string str = year + month + date + hour + min + "." + seconds;
  
   //file index
   while( (drnt = readdir(dr) ) != NULL )
   {
      //attribute index
      class stat statBuf;
      int isFolder;
      char fullPath[PATH_MAX];

      strcpy(fullPath, dir_name.c_str());
      strcat(fullPath, "/");
      strcat(fullPath, drnt->d_name);

      string command = "touch -mt " + string(str) + " " + fullPath;
      //cout<<"command : " <<command<<endl;
      system(command.c_str());
   }
}

void Dlogic()
{
   string path;
   cout<<" Enter directory name : ";
   cin>>path;

   DIR * dr = opendir(path.c_str());
   struct dirent * drnt;
   
   ofstream myFile;
   myFile.open("compare.txt");
   {
      class stat statBuf_dir;
      stat(path.c_str(), &statBuf_dir);
      //Creation time
      myFile << "Creation time:";
      myFile << ctime(&statBuf_dir.st_birthtime);
      myFile << "\n";
      //Current directory size
      myFile << "Current folder size:";
      myFile << statBuf_dir.st_size;
      myFile << "\n";
   }
   myFile <<"Name \t\t Size\t\t Attributes\t\t Date of Creation\t\t Date of Modification\n";
   while( (drnt = readdir(dr) ) != NULL )
   {
      class stat statBuf;
      int isFolder;
      char fullPath[PATH_MAX];

      strcpy(fullPath, path.c_str());
      strcat(fullPath, "/");
      strcat(fullPath, drnt->d_name);

      if( stat(fullPath, &statBuf) < 0 )
         //return false;

      isFolder = S_ISDIR(statBuf.st_mode);

      string str(drnt->d_name);
      str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
      myFile << str;
      myFile << "\t\t";

      str = std::to_string(statBuf.st_size);
      myFile << str;
      myFile << "\t\t";

      myFile << getFilePermission(statBuf);
      myFile << "\t\t";

      str = ctime(&statBuf.st_birthtime);
      str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
      myFile << str;
      myFile << "\t\t";
      str = ctime(&statBuf.st_mtime);
      str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
      myFile << str;
      myFile << "\n";
   }
   myFile.close();

}
