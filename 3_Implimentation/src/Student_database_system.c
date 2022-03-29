#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iomanip>

using namespace std;


    struct student
    {
        char name[50],email[30] ;
        char dob[30],course[100],address[30],branch[30];
        long int id,phone;
    };



void title(int width){
		printf("%*s\t",width,"Student ID");
		printf("%*s\t",width,"Name");
		printf("%*s\t",width,"Email ID");
		printf("%*s\t",width,"DOB");
		printf("%*s\t",width,"Phone");
		printf("%*s\t",width,"Address");
		printf("%*s\t",width,"Course");
		printf("%*s\t",width,"Branch");
}


void inputRecords(struct student *e){
        cout << "Enter your Student Id : ";
        cin >> e->id;
        cout << "Enter the Student Name : ";
        cin >> e->name;
        cout << "Enter the DOB(dd-mm-yyyy): ";
        cin >> e->dob;
        cout << "Enter the email address  : ";
        cin >> e->email;
        cout << "Enter the Phone Number  : ";
        cin >> e->phone;
        cout << "Enter the Address   : ";
        cin >> e->address; 
        cout << "Enter the Course Name   : ";
        cin >> e->course; 
        cout << "Enter the Branch Name   : ";
        cin >> e->branch; 
}


void displayRecords(struct student e,int width){
        cout<<endl;
    	printf("%*ld",width,e.id);
    	cout<<"\t";
  		printf("%*.10s",width,e.name);
  		cout<<"\t";
  		printf("%*.10s",width,e.dob);
  		cout<<"\t";
  		printf("%*.10s",width,e.email);
  		cout<<"\t";
  		printf("%*ld",width,e.phone);
  		cout<<"\t";
  		printf("%*.10s",width,e.address);
  		cout<<"\t";
  		printf("%*.10s",width,e.course);
  		cout<<"\t";
  		printf("%*.10s",width,e.branch);
  		cout<<"\t";
}

int main()
{
    FILE *fp, *ft;
    char another, choice;

    struct student e;
    char input[50];
    long int recsize;
    int width=10,flag=0,count=0;

    fp=fopen("studentdata.txt","rb+");

    if (fp == NULL)
    {
        fp = fopen("studentdata.txt","wb+");

        if (fp==NULL)
        {
            puts("Cannot open file");
            return 0;
        }
    }

    recsize = sizeof(e);

    while(1)
    {
    	cout<<"\n\n";
        cout << "\t\t\t\t**** STUDENT DATABASE MANAGEMENT SYSTEM ***";
        cout << "\n\n";
        cout << "\n \t\t\t\t 1. Add    Records";
        cout << "\n \t\t\t\t 2. Search Record";
        cout << "\n \t\t\t\t 3. Update Records";
        cout << "\n \t\t\t\t 4. Delete Records";
        cout << "\n \t\t\t\t 5. List   Records";
        cout << "\n \t\t\t\t 6. Exit ";
        cout << "\n\n";
        cout << "\t\t\t\t Select Your Choice >> ";

        cin>>choice;
        
        switch(choice)
        {
        case '1' :
            fseek(fp,0,SEEK_END);
            another ='Y';
            while(another == 'Y' || another == 'y')
            {
                
                inputRecords(&e);           	
                fwrite(&e,recsize,1,fp);
                cout << "\n Add Another Record (Y/N) ";
                fflush(stdin);
                cin>>another;
            }
            break;
        case '2':
        	another = 'Y';
            while (another == 'Y'|| another == 'y')
            {
                cout << "\n Enter the ID of the student : ";
                cin >> input;

                rewind(fp);
                while (fread(&e,recsize,1,fp) == 1)
                {
                    if ((e.id==stoi(input)))
                    {
						title(width);
						displayRecords(e,width);
						flag=1;
                        break;
                    }
                }
                if(flag==0){
                cout<<"\t\tRecord Not Found";
                }
                flag=0;
                cout << "\n Search Another Record (Y/N) ";
 
                cin>>another;
            }
            break;



        case '3' :

            another = 'Y';
            while (another == 'Y'|| another == 'y')
            {
                cout << "\n Enter the ID of the student : ";
                cin >> input;

                rewind(fp);
                while (fread(&e,recsize,1,fp) == 1)
                {
                    if ((e.id==stoi(input)))
                    {
						inputRecords(&e);
                        fseek(fp, -recsize, SEEK_CUR);
                        fwrite(&e,recsize,1,fp);
                        break;
                    }
                    else
                        cout<<"\t\tRecord not found";
                }
                cout << "\n Modify Another Record (Y/N) ";

                cin>>another;
            }
            break;


        case '4':
      
            another = 'Y';
            while (another == 'Y'|| another == 'y')
            {
                cout << "\n Enter the ID of the student : ";
                cin >> input;

                ft = fopen("temp.dat", "wb");

                rewind(fp);
                while (fread (&e, recsize,1,fp) == 1)
				{
                    if (!(e.id==stoi(input)))
                    {
                        fwrite(&e,recsize,1,ft);
                    }else{
                    	flag=1;
                    }
                }
                fclose(fp);
                fclose(ft);
                remove("studentdata.txt");
                rename("temp.dat","studentdata.txt");

                fp=fopen("studentdata.txt","rb+");
				if(flag==0){
				cout<<"\t\tRecord not found";
				}else{
				cout<<"\t\tRecord Deleted successfully";
				}
				flag=0;
                cout << "\n Delete Another Record (Y/N) : ";
                cin>>another;
            }
			
            break;

		case '5':
			rewind(fp);
            cout << "\n\n\t\t\t\t\t===Records in the Database ===\n\n";
            cout << "\n";
            count=0;
            title(width);
            while (fread(&e,recsize,1,fp) == 1)
            {
				displayRecords(e,width);
				count+=1;
            }
            if(count==0){
            cout<<"\n\n\t\t\t\t\t\t\t No Records Present";
        	}
        	count=0;
            cout << "\n\n";
            break;
			
        case '6':
            fclose(fp);
            cout << "\n\n";
            cout << "\t\t\t\t\t *****    THE END     ****";
            cout << "\n\n";
            exit(0);
        }
    }



    return 0;
}
