//Program to Handle Covid Patients in C: U19CS048
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct date{
	int dd;
	int mm;
	int yy;
};
struct Patient{
	int id;
	char fname[20];
	char lname[20];
	int age;
	char gender;
	struct date adate;
	struct date ddate;
	char area[20];
} ;
struct area{
	char area[20];
};

//Functions used
void input(struct Patient p);
void deletef(int id);
void update();
void read();
int count();
void genderCount();
void ageCount();
void areaCount();
void seperateRecords();
void nextTenLetters();
void list(struct Patient p);
void nextTenDates();
void nextFiveMonths(struct date);
int ispresent(int[],int,int);
void nextTenDates(struct date);
int monthType(int,int);
void sortAge(int);
void sortfname(int);
void sortlname(int);
void sortDate(int);
int areaPresent(struct area a[],char ar[],int *n);
void addstr(struct area a[],char ar[],int *n);
int compareDates(struct date d1,struct date d2);

int main(){
	int ch,id,c;
	struct date d;
	struct Patient p;
	printf("******COVID PATIENT RECORDS******\n");
	printf("1.Add a record\n2.Delete a record\n3.Modify a record\n4.Summary\n5.Seperate Records\n");
	printf("6.Read\n7.List sorted records\n8.List records on various conditions\n9.Exit\n");
	while(1){
		printf("\n\n================================================\n");
		printf("Enter a choice: ");
		scanf("%d",&ch);
		switch(ch){
			case 1:
				//Add input in the record
				input(p);
				break;
			case 2:
				//Delete a particular record
				printf("Enter the patient id you want to delete: ");
				scanf("%d",&id);
				deletef(id);
				break;
			case 3:
				//Update the record
				update();
				break;
			case 4:
				//Create sumarry of the records
				printf("Which Summary report you want?\n");
				printf("   1.Count\n");
				printf("   2.Count based on gender\n");
				printf("   3.Count based on age\n");
				printf("   4.Count based on area\n");
				int cho;
				printf("\nEnter choice: ");
				scanf("%d",&cho);
				switch(cho){
					case 1:
						c=count();
						printf("The count of the patients till now is: %d\n",c);
						break;
					case 2:
						genderCount();
						break;
					case 3:
						ageCount();
						break;
					case 4:
						areaCount();
						break;
					default:
						printf("Wrong choice!\n");
				}
				break;
			case 5:
				//Seperate records into male and female
				seperateRecords();
				printf("Records have been seperated!\n");
				break;
			case 6:
				//Read the records entered till now
				read();
				break;
			case 7:
				//Sort records
				printf("Sort Records:\n");
				printf("   1.Based on age\n");
				printf("   2.Based on first name\n");
				printf("   3.Based on last name\n");
				printf("   4.Based on date\n");
				printf("Enter choice: ");
				scanf("%d",&cho);
				printf("      1) Ascending Order ->\n");
				printf("      2) Descending Order ->\n");
				printf("Enter choice of order: ");
				scanf("%d",&c);
				if(c!=1 && c!=2){
					printf("Wrong choice");
					break;
				}
				switch(cho){
					case 1:
						//Sort record according to age
						sortAge(c);
						break;
					case 2:
						//Sort record according to first name
						sortfname(c);
						break;
					case 3:
						//Sort record according to last name
						sortlname(c);
						break;
					case 4:
						//Sort record according to date
						sortDate(c);
						break;
					default:
						printf("Wrong choice!\n");
				}
				break;
			case 8:
				//List records on the following conditions
				printf("List Operations\n");
				printf("   1.Patient names with next 10 letters\n");
				printf("   2.Admission date to next 10 dates\n");
				printf("   3.Next 5 months\n");
				printf("\nEnter choice: ");
				scanf("%d",&cho);
				switch(cho){
					case 1:
						nextTenLetters();
						break;
					case 2:
						printf("Enter date to get next 10 dates data (dd mm yy): ");
						scanf("%d %d %d",&d.dd,&d.mm,&d.yy);
						nextTenDates(d);
						break;
					case 3:
						printf("Enter date to get next 5 months data (dd mm yy): ");
						scanf("%d %d %d",&d.dd,&d.mm,&d.yy);
						nextFiveMonths(d);
						break;
					default:
						printf("Wrong choice!\n");
				}
				break;
			case 9:
				exit(0);
			default:
				printf("\n\nEnter valid choice.\n");
		}
	}
	return 0;
}

/*********************************************************/
//Function that helps to take input
void input(struct Patient p){
	FILE *fp;
	fp=fopen("patient.txt","a+");
	printf("Enter patient id: ");
	scanf("%d",&p.id);
	printf("Enter patient first name: ");
	fflush(stdin);
	gets(p.fname);
	printf("Enter patient last name: ");
	fflush(stdin);
	gets(p.lname);
	printf("Enter patient age: ");
	fflush(stdin);
	scanf("%d",&p.age);
	printf("Enter patient gender (M/F): ");
	fflush(stdin);
	scanf(" %c",&p.gender);
	printf("Enter Admission date (format : dd mm yyyy ) : ");
	fflush(stdin);
	scanf("%d %d %d",&p.adate.dd,&p.adate.mm,&p.adate.yy);
	printf("Enter Discharge date (format : dd mm yyyy ) : ");
	fflush(stdin);
	scanf("%d %d %d",&p.ddate.dd,&p.ddate.mm,&p.ddate.yy);
	printf("Enter patient area: ");
	fflush(stdin);
	gets(p.area);
	fwrite(&p,sizeof(struct Patient),1,fp);
    printf("--------------------------------------\n\n");
    fclose(fp);
    
}

/****************************************************************/
//Function to delete any entry
void deletef(int id){
	struct Patient p;
	int flag=0;
	FILE *fp1;
	FILE *fp2;
	fp1=fopen("patient.txt","r+");
	fp2=fopen("temp.txt","a+");
	if(fp1==NULL)
		printf("Unable to load the file.\n");
	else
	{   
		   while(fread(&p,sizeof(struct Patient),1,fp1))
		   {
		   		if(p.id!=id) fwrite(&p,sizeof(struct Patient),1,fp2);
		   		else flag=1;
		   }
		   if(flag==0) printf("The record not found!\n");
		   else printf("The record has been deleted\n");
		   fclose(fp1);
		   fclose(fp2);
		   remove("patient.txt");
		   rename("temp.txt","patient.txt");
		   
	}
}

/**********************************************************************/
//Function to update any entry
void update(){
	struct Patient p,p1;
	FILE *fp1;
	FILE *fp2;
	fp1=fopen("patient.txt","r+");
	fp2=fopen("temp.txt","a+");
	if(fp1==NULL)
		printf("Unable to load the file.\n");
	else{
		int ID;
		printf("Enter the patient id to be updated: ");
		scanf("%d",&ID);
		p.id=ID;
		printf("Enter patient first name: ");
		fflush(stdin);
		gets(p.fname);
		printf("Enter patient last name: ");
		fflush(stdin);
		gets(p.lname);
		printf("Enter patient age: ");
		fflush(stdin);
		scanf("%d",&p.age);
		printf("Enter patient gender (M/F): ");
		fflush(stdin);
		scanf(" %c",&p.gender);
		printf("Enter Admission date (format : dd mm yyyy ) : ");
		fflush(stdin);
		scanf("%d %d %d",&p.adate.dd,&p.adate.mm,&p.adate.yy);
		printf("Enter Discharge date (format : dd mm yyyy ) : ");
		fflush(stdin);
		scanf("%d %d %d",&p.ddate.dd,&p.ddate.mm,&p.ddate.yy);
		printf("Enter patient area: ");
		fflush(stdin);
		gets(p.area);
		
		
		while(fread(&p1,sizeof(struct Patient),1,fp1))
		   {
		   		if(p1.id!=ID)
				{
					fwrite(&p1,sizeof(struct Patient),1,fp2);
				}
				else
				{
					fwrite(&p,sizeof(struct Patient),1,fp2);
				}
		   }
		   fclose(fp1);
		   fclose(fp2);
		   remove("patient.txt");
		   rename("temp.txt","patient.txt");
		   printf("The record has been updated.\n");
		
	}
}

/*********************************************************/
//Reads and displays all the patient entries
void read()
{
	struct Patient p1;
	FILE *fp;
	fp=fopen("patient.txt","r+");
	if(fp==NULL)
		printf("Failed to load!!!");
	else
	{
	while(fread(&p1,sizeof(struct Patient),1,fp))
	  {	
		printf("\n--------------------------------------------------------------"); 
		printf("\nPatient id : %d",p1.id); 
	    printf("\nFirst Name     : %s",p1.fname);
	    printf("\nLast Name      : %s",p1.lname);
	    printf("\nAge            : %d",p1.age);
	    printf("\nGender         : %c",p1.gender);
	    printf("\nArea           : %s",p1.area);
	    printf("\nAdmission Date : %d / %d / %d",p1.adate.dd,p1.adate.mm,p1.adate.yy);
	    printf("\nDischarge Date : %d / %d / %d",p1.ddate.dd,p1.ddate.mm,p1.ddate.yy);
	   }
	}
fclose(fp);
}

/*********************************************************/
//Counts the total patient entries
int count(){
	int count=0;
	struct Patient p1;
	FILE *fp;
	fp=fopen("patient.txt","r+");
	if(fp==NULL)
		printf("Failed to load!!!");
	else
	{
		while(fread(&p1,sizeof(struct Patient),1,fp))
	 	{	
			count++;
	   	}
	}
	fclose(fp);
	return count;
}

/***************************************************************/
//Counts the number of males and females
void genderCount(){
	int countM=0,countF=0;
	struct Patient p1;
	FILE *fp;
	fp=fopen("patient.txt","r+");
	if(fp==NULL) printf("Failed to load!!!");
	else
	{
		while(fread(&p1,sizeof(struct Patient),1,fp))
	 	{	
			if(p1.gender=='F'||p1.gender=='f') countF++;
			else countM++;
	   	}
	}
	fclose(fp);
	printf("MALES: %d     FEMALES: %d\n",countM,countF);
}

/*******************************************************************/
//Counts the different age groups available in the list
void ageCount(){
	int age[100]={0};
	int i;
	struct Patient p1;
	FILE *fp;
	fp=fopen("patient.txt","r+");
	if(fp==NULL) {
		printf("Failed to load!!!");
		return;
	}
	else
	{
		while(fread(&p1,sizeof(struct Patient),1,fp))
	 	{	
			age[p1.age%100]++;
	   	}
	}
	fclose(fp);
	for(i=0;i<100;i++){
		if(age[i]!=0) printf("Age of %d years: %d\n",i,age[i]);
	}
}

/********************************************************************/
//Seperates the records of males and females in two different text files
void seperateRecords(){
	FILE *fp,*fp1,*fp2;
	struct Patient p1;
	fp=fopen("patient.txt","r+");
	fp2=fopen("patientMale.txt","a+");
	fp1=fopen("patientFemale.txt","a+");
	if(fp==NULL) printf("Failed to load!!!");
	else
	{
		while(fread(&p1,sizeof(struct Patient),1,fp))
	 	{	
			if(p1.gender=='f'||p1.gender=='F') fwrite(&p1,sizeof(struct Patient),1,fp1);
			else fwrite(&p1,sizeof(struct Patient),1,fp2);
	   	}
	}
	fclose(fp);
	fclose(fp1);
	fclose(fp2);
	printf("The records have been separated.\n");
	//---------------------------------------------------------
	fp1=fopen("patientFemale.txt","r+");
	if(fp1==NULL) printf("Failed to load!!!");
	else{
		printf("\n\nTHE FEMALE RECORDS ARE AS FOLLOWS:\n");
		while(fread(&p1,sizeof(struct Patient),1,fp1)) list(p1);	
	}
	fclose(fp1);
	//---------------------------------------------------------
	fp1=fopen("patientMale.txt","r+");
	if(fp1==NULL) printf("Failed to load!!!");
	else{
		printf("\n\nTHE MALE RECORDS ARE AS FOLLOWS:\n");
		while(fread(&p1,sizeof(struct Patient),1,fp1)) list(p1);	
	}
	fclose(fp1);
}

/********************************************************************/
//Used to print the next ten letters from S 
void nextTenLetters(){
	struct Patient p1;
	FILE *fp;
	fp=fopen("patient.txt","r+");
	if(fp==NULL) {
		printf("Failed to load!!!");
		return;
	}
	else
	{
		while(fread(&p1,sizeof(struct Patient),1,fp))
	 	{	
			if((p1.fname[0]>'S'&&p1.fname[0]<='Z')||(p1.fname[0]>='A'&&p1.fname[0]<='C')||(p1.fname[0]>'s'&&p1.fname[0]<='z')||(p1.fname[0]>='a'&&p1.fname[0]<='c'))
			list(p1);
	   	}
	}
	fclose(fp);
}

/********************************************************************/
//Just helps to list all the parameters of the structure entered as argument
void list(struct Patient p){
	printf("\n--------------------------------------------------------------"); 
		printf("\nPatient id : %d",p.id); 
	    printf("\nFirst Name     : %s",p.fname);
	    printf("\nLast Name      : %s",p.lname);
	    printf("\nAge            : %d",p.age);
	    printf("\nGender         : %c",p.gender);
	    printf("\nArea           : %s",p.area);
	    printf("\nAdmission Date : %d / %d / %d",p.adate.dd,p.adate.mm,p.adate.yy);
	    printf("\nDischarge Date : %d / %d / %d",p.ddate.dd,p.ddate.mm,p.ddate.yy);
}

/********************************************************************/
//Find any admission in the following 5 months of the entered date-- if date 3/4/2020 is entered that means: data of months 
// MAY, JUNE, JULY, AUGUST, SEPTEMBER will be found (excluding april)
void nextFiveMonths(struct date d){
	int year=d.yy,month=d.mm,date=d.dd;
	int y[5],i;
	for(i=0;i<5;i++){
		 y[i]=(month+i+1)%12;
		 if (y[i]==0) y[i]=12;
	}
	struct Patient p1;
	FILE *fp;
	fp=fopen("patient.txt","r+");
	if(fp==NULL) {
		printf("Failed to load!!!");
		fclose(fp);
		return;
	}
	else
	{
		while(fread(&p1,sizeof(struct Patient),1,fp))
	 	{	
			if((p1.adate.yy==year&&ispresent(y,p1.adate.mm,5)&&p1.adate.mm>month)||(p1.adate.yy==year+1&&ispresent(y,p1.adate.mm,5)&&p1.adate.mm<month)){
				list(p1);
			}
	   	}
	}
	fclose(fp);
}

/********************************************************************/
int ispresent(int arr[],int val,int n){
	int i=0;
	for(i=0;i<n;i++){
		if(val==arr[i]) return 1;
	}
	return 0;
}

/********************************************************************/
//Find any admission in the following 10 dates of the entered date
void nextTenDates(struct date d){
	int year=d.yy,month=d.mm,date=d.dd,i;
	int m[2]={month,(month+1)%12},dy[10];
	m[1]=month==11?12:(month+1)%12;
	int type=monthType(month,year);
	for(i=0;i<10;i++){
		dy[i]=(date+i+1)%type;
		if(dy[i]==0) dy[i]=type;
	}
	struct Patient p1;
	FILE *fp;
	fp=fopen("patient.txt","r+");
	if(fp==NULL) {
		printf("Failed to load!!!");
		fclose(fp);
		return;
	}
	else
	{
		while(fread(&p1,sizeof(struct Patient),1,fp))
	 	{	
			if(ispresent(dy,p1.adate.dd,10)){
				if((p1.adate.dd>date&&p1.adate.mm==month&&p1.adate.yy==year)||(p1.adate.dd<date&&p1.adate.mm==m[1]&&p1.adate.yy==year&&m[1]!=1)||(p1.adate.dd<date&&p1.adate.mm==m[1]&&p1.adate.yy==year+1&&m[1]==1))
				list(p1);
			}
	   	}
	}
	fclose(fp);
}

/********************************************************************/
//Find whether the month has 30 days or 31
int monthType(int m,int y){
	if(m==1||m==3||m==5||m==8||m==10||m==12) return 31;
	else if(m==4||m==6||m==7||m==9||m==11) return 30;
	if(y%4==0&&m==2) return 29;
	return 28;
}

/********************************************************************/
//Sort records according to age
void sortAge(int choice){
	int len=count();
	struct Patient p[len];
	struct Patient p1;
	FILE *fp;
	fp=fopen("patient.txt","r+");
	if(fp==NULL){
		 printf("Failed to load!!!");
		 fclose(fp);
		 return;
	}
	else
	{
		int i=0;
		while(fread(&p1,sizeof(struct Patient),1,fp))
	 	{	
			p[i]=p1;
			i++;
	   	}
	}
	fclose(fp);
	
	//Sorting process using bubble sort:
	int i,j,flag;
	struct Patient temp;
	if(choice==1){  //ASCENDING ORDER
		for(i=0;i<len-1;i++){
			flag=0;
			for(j=0;j<len-1-i;j++){
				if(p[j].age>p[j+1].age){
					temp=p[j];
					p[j]=p[j+1];
					p[j+1]=temp;
					flag=1;
				}
			}
			if(flag==0) break;
		}
	}else{  //DESCENDING ORDER
		for(i=0;i<len-1;i++){
			flag=0;
			for(j=0;j<len-1-i;j++){
				if(p[j].age<p[j+1].age){
					temp=p[j];
					p[j]=p[j+1];
					p[j+1]=temp;
					flag=1;
				}
			}
			if(flag==0) break;
		}
	}
	
	printf("Sorted data is: ---->");
	for(i=0;i<len;i++){
		list(p[i]);
	}
}

/********************************************************************/
//Sort records according to first name
void sortfname(int choice){
	int len=count();
	struct Patient p[len];
	struct Patient p1;
	FILE *fp;
	fp=fopen("patient.txt","r+");
	if(fp==NULL){
		 printf("Failed to load!!!");
		 fclose(fp);
		 return;
	}
	else
	{
		int i=0;
		while(fread(&p1,sizeof(struct Patient),1,fp))
	 	{	
			p[i]=p1;
			i++;
	   	}
	}
	fclose(fp);
	
	//Sorting process using bubble sort:
	int i,j,flag;
	struct Patient temp;
	if(choice==1){  //ASCENDING ORDER
		for(i=0;i<len-1;i++){
			flag=0;
			for(j=0;j<len-1-i;j++){
				if(strcmp(p[j].fname,p[j+1].fname)>0){
					temp=p[j];
					p[j]=p[j+1];
					p[j+1]=temp;
					flag=1;
				}
			}
			if(flag==0) break;
		}
	}else{  //DESCENDING ORDER
		for(i=0;i<len-1;i++){
			flag=0;
			for(j=0;j<len-1-i;j++){
				if(strcmp(p[j].fname,p[j+1].fname)<0){
					temp=p[j];
					p[j]=p[j+1];
					p[j+1]=temp;
					flag=1;
				}
			}
			if(flag==0) break;
		}
	}
	
	printf("Sorted data is according to first name is: ---->");
	for(i=0;i<len;i++){
		list(p[i]);
	}
}

/********************************************************************/
//Sort records according to last name
void sortlname(int choice){
	int len=count();
	struct Patient p[len];
	struct Patient p1;
	FILE *fp;
	fp=fopen("patient.txt","r+");
	if(fp==NULL){
		 printf("Failed to load!!!");
		 fclose(fp);
		 return;
	}
	else
	{
		int i=0;
		while(fread(&p1,sizeof(struct Patient),1,fp))
	 	{	
			p[i]=p1;
			i++;
	   	}
	}
	fclose(fp);
	
	//Sorting process using bubble sort:
	int i,j,flag;
	struct Patient temp;
	if(choice==1){  //ASCENDING ORDER
		for(i=0;i<len-1;i++){
			flag=0;
			for(j=0;j<len-1-i;j++){
				if(strcmp(p[j].lname,p[j+1].lname)>0){
					temp=p[j];
					p[j]=p[j+1];
					p[j+1]=temp;
					flag=1;
				}
			}
			if(flag==0) break;
		}
	}else{  //DESCENDING ORDER
		for(i=0;i<len-1;i++){
			flag=0;
			for(j=0;j<len-1-i;j++){
				if(strcmp(p[j].lname,p[j+1].lname)<0){
					temp=p[j];
					p[j]=p[j+1];
					p[j+1]=temp;
					flag=1;
				}
			}
			if(flag==0) break;
		}
	}
	
	printf("Sorted data according to last name is: ---->");
	for(i=0;i<len;i++){
		list(p[i]);
	}
}

/********************************************************************/
//Count based on area
void areaCount(){
	int len=count(),n=0,pos=0,j;
	struct area a[len];
	int counts[20]={0};
	struct Patient p1;
	FILE *fp;
	fp=fopen("patient.txt","r+");
	if(fp==NULL){
		 printf("Failed to load!!!");
		 fclose(fp);
		 return;
	}
	else
	{
		int i=0;
		while(fread(&p1,sizeof(struct Patient),1,fp))
	 	{	
			if(!(pos=areaPresent(a,p1.area,&n))){
				addstr(a,p1.area,&n);
				counts[n-1]++;
			}else{
				counts[pos-1]++;
			}
	   	}
	}
	fclose(fp);
	
	printf("The count based on area is:-------->\n");
	for(j=0;j<n;j++){
		printf("   %s: %d\n",a[j].area,counts[j]);
	}
}

/*******Auxillary functions********/
int areaPresent(struct area a[],char ar[],int *n){
	int i=0;
	for(i=0;i<(*n);i++){
		if(strcmp(a[i].area,ar)==0) return i+1;
	}
	return 0;
}

void addstr(struct area a[],char ar[],int *n){
	*n=*n+1;
	strcpy(a[*n-1].area,ar);
}
/**********************************/

/********************************************************************/
//Sorting based on dates
void sortDate(int choice){
	int j,i,flag;
	int len=count();
	struct Patient p1,p[len],temp;
	FILE *fp;
	fp=fopen("patient.txt","r+");
	if(fp==NULL){
		 printf("Failed to load!!!");
		 fclose(fp);
		 return;
	}
	else
	{
		int i=0;
		while(fread(&p1,sizeof(struct Patient),1,fp))
	 	{	
			p[i]=p1;
			i++;
	   	}
	}
	fclose(fp);
	
	//sorting
	if(choice==1){
		for(i=0;i<len-1;i++){
			flag=0;
			for(j=0;j<len-1-i;j++){
				if(compareDates(p[j+1].adate,p[j].adate)<0){
					temp=p[j];
					p[j]=p[j+1];
					p[j+1]=temp;
					flag=1;
				}
			}
			if(flag==0) break;
		}
	}else{
		for(i=0;i<len-1;i++){
			flag=0;
			for(j=0;j<len-1-i;j++){
				if(compareDates(p[j+1].ddate,p[j].ddate)>0){
					temp=p[j];
					p[j]=p[j+1];
					p[j+1]=temp;
					flag=1;
				}
			}
			if(flag==0) break;
		}
	}

	printf("\nSorted data is: \n");
	for(j=0;j<len;j++){
		list(p[j]);
	}
}

/*******Auxillary functions********/
int compareDates(struct date d1,struct date d2){
	if(d1.yy>d2.yy){
		return 1;
	}else if(d1.yy<d2.yy){
		return -1;
	}else{
		if(d1.mm>d2.mm){
			return 1;
		}else if(d1.mm<d2.mm){
			return -1;
		}else{
			if(d1.dd>d2.dd){
				return 1;
			}else if(d1.dd<d2.dd){
				return -1;
			}else{
				return 0;
			}
		}
	}
}

/*********END OF PROGRAMME***********/
