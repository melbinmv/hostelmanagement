#include<fstream.h>
#include<conio.h>
#include<graphics.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<dos.h>
 int i,x,y;
 int flag=0;
 char sys[]=" System Starting.";
 void graphics(void);
 void mainmenu();
 void start(void)
 {
  clrscr();
  x=getmaxx();
  y=getmaxy();
  char password[]="saps",pass[20],ch='a';
  int p;
  gotoxy(30,12);
  cout<<"\n\t\tEnter Password:   ";
  i=0;
  while(ch!=13)
    {
      ch=getch();
      if(ch!=13)
      {
	cout<<"*";

	pass[i]=ch;
      }
    i++;
    }
    pass[i-1]='\0';
    p=strcmp(password,pass);
    if(p!=0)
    {
      clrscr();
      gotoxy(30,12);
      cout<<"\nAcces Denied";
      getch();
      delay(100);
      exit(0);
    }
 clrscr();
 delay(20);
 gotoxy(30,12);
 delay(0);
 clrscr();
 gotoxy(30,12);
 for(i=0;i<sizeof(sys);i++)
   {
     textcolor(i);
     cprintf("%c",sys[i]);
     delay(300);
   }
   cout<<"\n\n\n\n\n\n\n\t\t\tPress Enter Key to Continue";
   getch();
   closegraph();
 }
void graphics(void)
{
  int gdriver=DETECT,gmode,errorcode;
  initgraph(&gdriver, &gmode," ");
  int xx,yy,color;
  x=getmaxx();
  y=getmaxy();
  randomize();
  for(int i=0;i<2000;i++) //dots..background
  {
    xx=random(x);
    yy=random(y);
    color=random(15);
    putpixel(xx,yy,color);
    delay(5);
   }
   for(i=0;i<50;i++)
   {
    setcolor(i);
    settextstyle(0,0,2);
    outtextxy(230,290,"AKARSH JOICE");
    outtextxy(290,350,"ALPHONSE S JOSEPH");
    outtextxy(210,270,"HARIKRISHNAN K.V");
    outtextxy(250,310,"MANU PRATHAP");
    outtextxy(270,330,"MELBIN MARTIN");
    outtextxy(210,370,"Press any key to continue");
    settextstyle(0,0,3);
    outtextxy(10,10,"St.Antony's Public School&");
    outtextxy(100,35,"JUNIOR COLLEGE");
    outtextxy(100,100,"Hostel Management");
    outtextxy(190,210,"PROJECT DONE by....");
    delay(20);
   }
   getch();
   closegraph();
}
//Class of Hostler
class hostler
{
char sname[50],fname[20],mname[20],add[100];
char phno[12];
int acno;
public:
hostler()
{}
void creation();
void append(hostler);
int search(int);
void search(char*);
void modify(int);
void remove(int);
void display();
void list();
};
//****************************************************************************
//CREATION OF HOSTLER
//****************************************************************************
void hostler::creation()
{
cout<<"\n\tAC NUMBER:";
cin>>acno;
cout<<"\n\t\tNAME:";
gets(sname);
cout<<"\n\t\tFATHER'S NAME:";
gets(fname);
cout<<"\n\t\tMOTHER'S NAME:";
gets(mname);
cout<<"\n\t\tMOBILE NUMBER:";
gets(phno);
cout<<"\n\t\tPERMENANT ADRESS:";
gets(add);
}
//**************************************************************************
//APPENDING TO THE END
//**************************************************************************
void hostler::append(hostler obj)
{ ofstream outfile;
  outfile.open("host.dat",ios::app|ios::binary);
  outfile.write((char*)&obj,sizeof(obj));
  outfile.close();
 }
//**************************************************************************
//SEARCH BY NUMBER
//**************************************************************************
 int hostler::search(int n)
{
int found=0;
fstream infile;
hostler obj;
infile.open("host.dat",ios::in|ios::binary);
while(!infile.eof())
{	infile.read((char*)&obj,sizeof(obj));
	if(obj.acno==n)
	{
		found=1;
		obj.display();
		getch();
		 break;

	}
}

if(found==0)
{
cout<<"NO RECORD FOUND";

}
infile.close();
     return 0;
}
//**************************************************************************
//DISPLAY THE DETAILS
//**************************************************************************
void hostler::display()
{
cout<<"\n\t\tDETAILS OF STUDENT";
cout<<"\n\tAC NUMBER:"<<acno;
cout<<"\n\t\tNAME:";
puts(sname);
cout<<"\n\t\tFATHER'S NAME:";
puts(fname);
cout<<"\n\t\tMOTHER'S NAME:";
puts(mname);
cout<<"\n\t\tMOBILE NUMBER:";
puts(phno);
cout<<"\n\t\tPERMENANT ADRESS:";
puts(add);
}
//**************************************************************************
//SEARCH BY NAME
//**************************************************************************
void hostler::search(char*name)
{
int found=0,n;
fstream infile;
hostler obj;
infile.open("host.dat",ios::in|ios::binary);
while(!infile.eof()&&found==0)
{	infile.read((char*)&obj,sizeof(obj));
	if(strcmp(obj.sname,name)==0)
	{
		found=1;
	}
}
if(found==0)
{
cout<<"\n\tNO RECORD FOUND";
}
else
{
obj.display();
}
infile.close();
}
//**************************************************************************
//MODIFY
//**************************************************************************
void hostler::modify(int no)
{
clrscr();
cout<<"\t\t\tMODIFY STUDENT DETAILS"<<endl;
cout<<"\t\t-----------------------------------";
hostler st,obj;
int found=0,count=0;
fstream inout;
inout.open("host.dat" ,ios::in|ios::out|ios::binary);
while(!inout.eof()&&found==0)
{
 count++;
 inout.read((char*)&obj,sizeof(obj));
 if(obj.acno==no)
 {
  cout<<"\n\nTHE CURRENT DETAILS :\n";
  obj.display();
  cout<<"\n\n Enter the new details\n";
  st.creation();
  inout.seekp((count-1)*sizeof(hostler));
  inout.write((char*)&st,sizeof(st));
  found=1;
  cout<<"\n\t RECORD MODIFIED";
 }
}
if(found==0)
cout<<"\n\aSuch a record does not exit";
inout.close();
}
//**************************************************************************
//REMOVE A STUDENT
//**************************************************************************
void hostler::remove(int no)
{
hostler st;
int count=0;
char source[25],dest[25];
fstream inout("host.dat",ios::in|ios::out|ios::binary);
inout.seekg(0,ios::end);
int size=inout.tellg();
int records=size/sizeof(hostler);
fstream inout_temp("tem.dat",ios::out|ios::noreplace);
inout.seekg(0,ios::beg);
inout_temp.seekp(0,ios::beg);
while(inout && count<=(records-1))
{ inout.read((char*)&st,sizeof(st));
  if(st.acno!=no)
  inout_temp.write((char*)&st,sizeof(st));
  }
  cout<<"\n\tRecord Deleted....";
  inout.close();
  inout_temp.close();
  strcpy(source,"host.dat");
  strcpy(dest,"tem.dat");
  unlink(source);
  rename(dest,source);
  }
//**************************************************************************
//LIST THE STUDENTS
//**************************************************************************
 void hostler::list()
{
    ifstream infile;
    hostler obj;
    infile.open("host.dat",ios::in|ios::binary);
    infile.seekg(0,ios::end);
    int size=infile.tellg();
    int no=size/sizeof(hostler);
    int i=0;
    infile.seekg(0);
    while(!infile.eof()&&(i<no))
    {   infile.read((char*)&obj,sizeof(obj));
	obj.display();
	i++;
    }
    infile.close();
 }
//**************************************************************************
//HOSTLER_MENU
//**************************************************************************
void hostler_menu()
{
   char na[100];
   clrscr();
   hostler s;
   int choice ;
   int a;
   char cho,ch;
    do
     {
     clrscr();
     cout<<"\n\n";
     cout<<"\n\t\t...........STUDENT MANAGEMENT PORTAL...........\n";
     cout<<"\t_____________________________________________________________\n";
     cout <<  "\n\t\t\t1.) CREATE STUDENT" << endl ;
     cout <<  "\n\t\t\t2.) LIST THE STUDENTS" << endl ;
     cout <<  "\n\t\t\t3.) SEARCH BY NUMBER" << endl;
     cout <<  "\n\t\t\t4.) SEARCH BY NAME" << endl;
     cout <<  "\n\t\t\t5.) MODIFY STUDENT DETAILS" << endl ;
     cout <<  "\n\t\t\t6.) DELETE A STUDENT" << endl ;
     cout <<  "\n\t\t\t7.) RETURN TO MAIN MENU" << endl;
     cout <<  "\n\t\t\t\tEnter Your choice::\t";
   cin >> choice;
   switch(choice)
   { case 1:
	    do
	   {
	     clrscr();
	     cout<<"\t\t\tCREATE YOUR STUDENT\n";
	     cout<<"\t\t\-----------------------------------";
	     s.creation();
	     s.append(s);
	     cout<<"\n\tDo you want to create more?(y/n)\t";
	     cin>>ch;
	  }while(ch=='y');
	     getch();
	     clrscr();
	     break;
     case 2: clrscr();
	     s.list();
	     getch();
	     clrscr();
	     break;
     case 3:  do
	   {
	     clrscr();
	     cout<<"\nENTER THE AC NUMBER OF STUDENT::\t";
	     cin>>a;
	     s.search(a);
	     cout<<"\n\tDo you want to search more?(y/n)\t";
	     cin>>ch;
		   }while(ch=='y');
	     getch();
	     clrscr();
	     break;
     case 4: do
	     {
	     clrscr();
	     cout<<"\nENTER NAME OF STUDENT TO BE SEARCHED::\t";
	     gets(na);
	     s.search(na);
	     cout<<"\n\n\tDo you want to search more?(y/n)\t";
	     cin>>ch;
	      }while(ch=='y');
	     getch();
	     clrscr();
	     break;
     case 5: do
	    {
	     clrscr();
	     cout<<"\nENTER THE AC NUMBER OF STUDENT TO BE MODIFIED::\t";
	     cin>>a;
	     s.modify(a);
	     cout<<"\n\n\tDo you want to modify more?(y/n)\t";
	     cin>>ch;
	      }while(ch=='y');
	      getch();
	     clrscr();
	     break;
     case 6: do
	    {
	     clrscr();
	     cout<<"\nENTER THE AC NUMBER OF STUDENT TO BE REMOVED::\t";
	     cin>>a;
	     s.remove(a);
	     cout<<"\n\n\tDo you want to remove more?(y/n)\t";
	     cin>>ch;
	      }while(ch=='y');
	     getch();
	     clrscr();
	     break;
    case 7:  mainmenu();
	     clrscr();
	     getch();
	     break;
     default:clrscr();
	     cout<<"\n\tWrong Choice\n";
	     cout<<"\n\tPlease Enter a Valid Input";
	     getch();
	     clrscr();
	     }
   cout<<"\nDo You Want to Continue with the Student Portal";
   cout<<"\nIf Yes Press 'y' else Press 'n':\t";
   cin>>cho;
  }while(cho=='y');
  getch();
}
class staff
{
char stname[50],fname[20],mname[20],add[100],pst[100];
char phno[12];
int no;
float pay;
public :
void creation();
void append(staff);
int search(int);
void search(char*);
void modify(int);
void remove(int);
void display();
void list();
};
//****************************************************************************
//CREATION OF STAFF
//****************************************************************************
void staff::creation()
{
int opt;
cout<<"\n\tSTAFF ID:";
cin>>no;
cout<<"\n\t\tNAME:";
gets(stname);
cout<<"\n\t\tFATHER'S NAME:";
gets(fname);
cout<<"\n\t\tMOTHER'S NAME:";
gets(mname);
cout<<"\n\t\tMOBILE NUMBER:";
gets(phno);
cout<<"\n\t\tPERMENANT ADRESS:";
gets(add);
cout<<"\n\t\tPOST:";
gets(pst);
cout<<"\n\t\tENTER THE MODE OF PAYMENT:";
cout<<"\n\t\t\t1.) Per Month";
cout<<"\n\t\t\t2.) Per Week";
cout<<"\n\t\t\t3.) Per Day";
cout<<"\n\t\t\tYour Choice::\t";
 cin>>opt;
 if(opt==1)
   {
   cout<<"\n\t\tSALARY:";
   cin>>pay;
   flag=1;
   }
else if(opt==2)
   {
      cout<<"\n\t\tSALARY:";
   cin>>pay;
   flag=2;
   }
else if(opt==3)
{
   cout<<"\n\t\tSALARY:";
   cin>>pay;
   flag=3;
   }
}
//**************************************************************************
//APPENDING TO THE END
//**************************************************************************
void staff::append(staff obj)
{
  ofstream outfile;
  outfile.open("staff.dat",ios::app|ios::binary);
  outfile.write((char*)&obj,sizeof(obj));
  outfile.close();
 }
 //**************************************************************************
 //SEARCH BY NUMBER
 //**************************************************************************
 int staff::search(int n)
{
int found=0;
ifstream infile;
staff obj;
infile.open("staff.dat",ios::in|ios::binary);
while(!infile.eof()&&found==0)
{	infile.read((char*)&obj,sizeof(obj));
	if(obj.no==n)
	{
		found=1;
	}
}
if(found==1)
{     obj.display();
}
else
{
cout<<"NO RECORD FOUND";

}
infile.close();
     return 0;
}
 //**************************************************************************
 //DISPLAY THE DETAILS
 //**************************************************************************

void staff::display()
{
cout<<"\n\t\tDETAILS OF STAFFS";
cout<<"\n\tSTAFF ID:"<<no;
cout<<"\n\t\tNAME:";
puts(stname);
cout<<"\n\t\tFATHER'S NAME:";
puts(fname);
cout<<"\n\t\tMOTHER'S NAME:";
puts(mname);
cout<<"\n\t\tMOBILE NUMBER:";
puts(phno);
cout<<"\n\t\tPERMENANT ADRESS:";
puts(add);
cout<<"\n\t\tPOST:";
puts(pst);
if(flag==1)
{
cout<<"\n\t\tMONTHLY SALARY:";
cout<<pay;
}
else if(flag==2)
{
cout<<"\n\t\tWEEKLY SALARY:";
cout<<pay;
}
else if(flag==3)
{
cout<<"\n\t\tDAILY SALARY:";
cout<<pay;
}
}
//**************************************************************************
//SEARCH BY NAME
//**************************************************************************
void staff::search(char*name)
{
int found=0,n;
ifstream infile;
staff obj;
infile.open("staff.dat",ios::in|ios::binary);
while(!infile.eof()&&found==0)
{	infile.read((char*)&obj,sizeof(obj));
	if(strcmp(obj.stname,name)==0)
	{
		found=1;
	}
}
if(found==0)
{

cout<<"\n\tNO RECORD FOUND";
}
else
{   obj.display();
}
infile.close();
}
 //**************************************************************************
 //MODIFY
 //**************************************************************************

void staff::modify(int no)
{
clrscr();
 cout<<"\t\t\tMODIFY STAFF DETAILS"<<endl;;
  cout<<"\t\t-----------------------------------";
staff st,obj;
int found=0,count=0;
fstream inout;
inout.open("staff.dat" ,ios::in|ios::out|ios::binary);
while(!inout.eof()&&found==0)
{
 count++;
 inout.read((char*)&obj,sizeof(obj));
 if(obj.no==no)
 {
  cout<<"\n\nTHE CURRENT DETAILS :\n";
  obj.display();
  cout<<"\n\n Enter the new details\n";
  st.creation();
  inout.seekp((count-1)*sizeof(staff));
  inout.write((char*)&st,sizeof(st));
  found=1;
  cout<<"\n\t RECORD MODIFIED";
 }
}
if(found==0)
cout<<"\n\aSuch a record does not exit";
inout.close();
}
//**************************************************************************
 //REMOVE A STAFF
 //**************************************************************************
 void staff::remove(int no)
{
staff st;
int count=0;
char source[25],dest[25];
fstream inout("staff.dat",ios::in|ios::out|ios::binary);
inout.seekg(0,ios::end);
int size=inout.tellg();
int records=size/sizeof(staff);
fstream inout_temp("tempe.dat",ios::out|ios::noreplace);
inout.seekg(0,ios::beg);
inout_temp.seekp(0,ios::beg);
while(inout && count<=(records-1))
{ inout.read((char*)&st,sizeof(st));
  if(st.no!=no)
  inout_temp.write((char*)&st,sizeof(st));
  }
  cout<<"\n\tRecord Deleted....";
  inout.close();
  inout_temp.close();
  strcpy(source,"staff.dat");
  strcpy(dest,"tempe.dat");
  unlink(source);
  rename(dest,source);
  }

//**************************************************************************
 //LIST STAFFS
 //**************************************************************************
 void staff::list()
{
    ifstream infile;
    staff obj;
    infile.open("staff.dat",ios::in|ios::binary);
    infile.seekg(0,ios::end);
    int size=infile.tellg();
    int no=size/sizeof(staff);
    int i=0;
    infile.seekg(0);
    while(!infile.eof()&&(i<no))
    {   infile.read((char*)&obj,sizeof(obj));
	obj.display();
	i++;
    }
    infile.close();
}

//**************************************************************************
//STAFF_MENU
//**************************************************************************
void staff_menu()
{
   char na[100];
   clrscr();
   staff st;
   int choice ;
   int a;
   char cho,ch;
   do
     {
     clrscr();
     cout<<"\n\n";
     cout<<"\n\t\t...........STAFF MANAGEMENT PORTAL...........\n";
     cout<<"\t_____________________________________________________________\n";
     cout <<  "\n\t\t\t1.) CREATE STAFF" << endl ;
     cout <<  "\n\t\t\t2.) LIST STAFFS" << endl ;
     cout <<  "\n\t\t\t3.) SEARCH BY NUMBER" << endl;
     cout <<  "\n\t\t\t4.) SEARCH BY NAME" << endl;
     cout <<  "\n\t\t\t5.) MODIFY STAFF DETAILS" << endl ;
     cout <<  "\n\t\t\t6.) DELETE A STAFF" << endl ;
     cout <<  "\n\t\t\t7.) RETURN TO MAIN MENU" << endl;
     cout <<  "\n\t\t\t\tEnter Your choice::\t";
   cin >> choice;
   switch(choice)
   {
     case 1:
	    do
	   {
	     clrscr();
	     cout<<"\t\t\tCREATE YOUR STAFF\n";
	     cout<<"\t\t\-----------------------------------";
	     st.creation();
	     st.append(st);
	     cout<<"\n\tDo you want to create more?(y/n)\t";
	     cin>>ch;
	   }while(ch=='y');
	     getch();
	     clrscr();
	     break;

     case 2:  clrscr();
	      st.list();
	      getch();
	      clrscr();
	      break;
     case 3:  do
	   {
	     getch();
	     closegraph();
	     clrscr();
	     cout<<"\nENTER THE STAFF ID::\t";
	     cin>>a;
	     st.search(a);
	      cout<<"\n\tDo you want to search more?(y/n)\t";
	     cin>>ch;
		   }while(ch=='y');
	     getch();
	     clrscr();
	     break;
     case 4: do
	     {
	     clrscr();
	     cout<<"\nENTER NAME OF THE STAFF TO BE SEARCHED::\t";
	      gets(na);
	     st.search(na);
	      cout<<"\n\n\tDo you want to search more?(y/n)\t";
	     cin>>ch;
	      }while(ch=='y');
	     getch();
	     clrscr();
	     break;
     case 5: do
	    {
	     clrscr();
	     cout<<"\nENTER THE ID NUMBER OF STAFF TO BE MODIFIED::\t";
	     cin>>a;
	     st.modify(a);
	     cout<<"\n\n\tDo you want to modify more?(y/n)\t";
	     cin>>ch;
	      }while(ch=='y');
	      getch();
	     clrscr();
	     break;
     case 6:do
	    {
	     getch();
	     closegraph();
	     clrscr();
	     cout<<"\nENTER THE ID NUMBER OF STAFF TO BE REMOVED::\t";
	     cin>>a;
	     st.remove(a);
	       cout<<"\n\n\tDo you want to remove more?(y/n)\t";
	     cin>>ch;
	      }while(ch=='y');
	     getch();
	     clrscr();
	     break;
    case 7:  mainmenu();
	     clrscr();
	     getch();
	     break;
   default:clrscr();
	     cout<<"\n\tWrong Choice\n";
	     cout<<"\n\tPlease Enter a Valid Input";
	     getch();
	     clrscr();
	     }
   cout<<"\nDo You Want to Continue with Staff Portal";
   cout<<"\nIf Yes Press 'y' else Press 'n':";
   cin>>cho;
  }while(cho=='y');
  getch();
 }
 void credits()
{
  clrscr();
  cout<<"\t\t:::::::::::::::::::CREDITS:::::::::::::::::::\n";
  cout<<"\n\t\tPROGRAM DEVELOPED BY:\n";
  cout<<"\n\t\t\tAKARSH JOICE\n";
  cout<<"\n\t\t\tALPHONSE S JOSEPH\n";
  cout<<"\n\t\t\tHARIKRISHNAN K.V\n";
  cout<<"\n\t\t\tMANU PRATHAP\n";
  cout<<"\n\t\t\tMELBIN MARTIN\n";
  cout<<"\n\t\tDEVELOPED AT:\n";
  cout<<"\n\t\t\tST.ANTONY'S PUBLIC SCHOOL ANAKKAL,KANJIRAPALLY\n";
  cout<<"\n\t\tSINCERE THANKS TO:\n";
  cout<<"\n\t\t\tCHERIAN K ABRAHAM\n";
  cout<<"\n\t\t\tTHANUJA MATHEW\n";

 }
void mainmenu()
{
   clrscr();
   int ch;
   char cho;
   do
   {
       clrscr();
       cout<<"\n\n\n\t\t:::::::::::::::::MAIN MENU::::::::::::::::::::::\n";
       cout<<"\n\t\t\t1.) Student Management\n"<<endl;
       cout<<"\t\t\t2.) Staff Management\n"<<endl;
       cout<<"\t\t\t3.) Credits\n"<<endl;
       cout<<"\t\t\t4.) How to Use?\n"<<endl;
       cout<<"\t\t\t5.) Quit\n"<<endl;
  cout<<"\t\t\tSelect Your Choice::\t";
  cin>>ch;
  switch(ch)
   {
     case 1: hostler_menu();
	     clrscr();
	     getch();
	     break;
     case 2: staff_menu();
	     clrscr();
	     getch();
	     break;
     case 3: credits();
	     getch();
	     break;
     case 4: clrscr();
	     cout<<"\t\t\t::INSTRUCTIONS FOR USE::\n";
	     cout<<"\n* To select your choice, enter the number indicated against it.\n";
	     cout<<"\n* Press Enter Key to confirm your choice.\n";
	     cout<<"\n* Press Enter Key every time for next instructions.\n";
	     cout<<"\n\n\t:::Press Enter Key for next instruction:::";
	    getch();
	     break;
     case 5: clrscr();
	     char q;
	     cout<<"\n\tDo you really want to Quit the Program\n";
	     cout<<"\tIf Yes Press 'y' else Press 'n'::";
	     cin>>q;
	     if(q=='y')
	     {
	     {
	      clrscr();
	      cout<<"\n\n\t\t\tTHANKU FOR USING THE PROGRAM";
	      cout<<"\n\t\t\tEXITING FROM PROGRAM";
	      delay(700);
	      }
	       exit(0);
	      }
	      else
	      {

		clrscr();
		puts("\t\t\tRETURNING TO MAIN MENU");
		cout<<"\n\tLOADING...\n";
		for(int i=0;i<80;i++)
		{
		 cout<<"_";
		 delay(20);
		 }
		delay(1000);
		mainmenu();
		}
		break;
     default:clrscr();
	   cout<<"\n\t\tWrong Choice";
	     cout<<"\n\t\tPlease Enter a Valid Input";
	      getch();
	     }
	     clrscr();
   cout<<"\nDo You Want to Continue With the Program" ;
   cout<<"\nIf Yes Press 'y' else Press 'n':";
   cin>>cho;
  }while(cho=='y');
  getch();
     }
////////////////////main
void main()
{ clrscr();
 start();
 graphics();
 mainmenu();
 getch();
  }








