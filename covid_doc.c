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

struct docPat{
	int docID;
	int patID;
};

struct area{
	char area[20];
	int c;	
};

struct Doctor{
	int id;
	char fname[20];
	char lname[20];
	int age;
	char gender;
	char area[20];
};


//Functions used
void inputP(struct Patient p);
void inputD(struct Doctor d);
void inputdp();
//---------------------
void readD();
void readDP();
void readP();
//---------------------
void countPatients();
void countGender();
void countAge();
void countArea();
//---------------------
int ispresent(int val,int arr[],int n);
int areaPresent(struct Patient p,struct area a[],int i);
void add(struct Patient p,struct area a[],int i);
//---------------------
void adDate();
void disDate();
void list(struct Patient p);
void patientsUnderDoc();
void patientsUnderMaleDoc();
void patientsUnderFemaleDoc();
//--------------------
void leastp();

//MAIN FUNCTION--------
int main(){
	int ch,id,c;
	struct date date;
	struct Patient p;
	struct Doctor d;
	printf("******COVID PATIENT RECORDS******\n");
	printf("1.Add a patient record\n2.Add a doctor record\n3.Add doctor-patient ids\n");
	printf("4.Read entries\n5.Doctor having the least number of patients\n6.Count data\n7.");
	printf("List all the patient records of the file in ascending order\n8.Exit\n");
	while(1){
		printf("\n\n================================================\n");
		printf("Enter a choice: ");
		scanf("%d",&ch);
		switch(ch){
			case 1:
				inputP(p);
				break;
			case 2:
				inputD(d);
				break;
			case 3:
				inputdp();
				break;
			case 4:
				printf("\t1.Doctor file\n\t2.Patient file\n\t3.Common file\n");
				printf("\nEnter choice: ");
				scanf("%d",&c);
				switch(c){
					case 1:
						readD();
						break;
					case 2:
						readP();
						break;
					case 3:
						readDP();
						break;
					default:
						printf("Enter valid choice.\n");
				}
				break;
			case 5:
				leastp();
				break;
			case 6:
				printf("\t1.Count patients doctorwise\n\t2.Count patients gender doctorwise\n");
				printf("\t3.Count patients age doctorwise\n\t4.Count patients area doctorwise\n");
				printf("\nEnter choice: ");
				scanf("%d",&c);
				switch(c){
					case 1:
						countPatients();
						break;
					case 2:
						countGender();
						break;
					case 3:
						countAge();
						break;
					case 4:
						countArea();
						break;
					default:
						printf("Enter valid choice.\n");
				}
				break;
			case 7:
				printf("\t1.Admitted on same date\n\t2.Discharged on same date\n");
				printf("\t3.Patients treated under the doctor\n\t4.Patients treated under the male doctor\n");
				printf("\t5.Patients treated under the female doctor area wise\n");
				printf("\nEnter choice: ");
				scanf("%d",&c);
				switch(c){
					case 1:
						adDate();
						break;
					case 2:
						disDate();
						break;
					case 3:
						patientsUnderDoc();
						break;
					case 4:
						patientsUnderMaleDoc();
						break;
					case 5:
						patientsUnderFemaleDoc();
						break;
					default:
						printf("Enter valid choice.\n");
				}
				break;
			case 8:
				exit(0);
			default:
				printf("Wrong choice.\n");
		}
	}
	return 0;
}

/*********************************************************/
//Function that helps to take patient input
void inputP(struct Patient p){
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

/*********************************************************/
//Function that helps to take doctor input
void inputD(struct Doctor d){
	FILE *fp;
	fp=fopen("doctor.txt","a+");
	printf("Enter doctor id: ");
	scanf("%d",&d.id);
	printf("Enter doctor first name: ");
	fflush(stdin);
	gets(d.fname);
	printf("Enter doctor last name: ");
	fflush(stdin);
	gets(d.lname);
	printf("Enter doctor age: ");
	fflush(stdin);
	scanf("%d",&d.age);
	printf("Enter doctor gender (M/F): ");
	fflush(stdin);
	scanf(" %c",&d.gender);
	printf("Enter doctor area: ");
	fflush(stdin);
	gets(d.area);
	fwrite(&d,sizeof(struct Doctor),1,fp);
    printf("--------------------------------------\n\n");
    fclose(fp);
}


/*********************************************************/
//Inputs data in doctor-patient file
void inputdp(){
	int flag1=0,flag2=0;
	FILE *fp;
	struct docPat dp;
	struct Patient p;
	struct Doctor d;
	printf("Enter doctor id: ");
	scanf("%d",&dp.docID);
	printf("Enter patient id: ");
	scanf("%d",&dp.patID);
	
	//Checking if doctor with that id is present
   fp=fopen("doctor.txt","a+");
	while(fread(&d,sizeof(struct Doctor),1,fp))
   {
   		if(d.id==dp.docID){
   		 	flag2=1;
			break;	
		}
   }
   if(!flag2){
   		printf("ALERT: ");
   		printf("Doctor with that id not present. First make an entry in the doctor file.\n");
   		return;
   }
   fclose(fp);
	
	//Checking if patient with that id is present
	fp=fopen("patient.txt","a+");
	while(fread(&p,sizeof(struct Patient),1,fp))
   {
   		if(p.id==dp.patID){
   		 	flag1=1;
			break;	
		}
   }
   if(!flag1){
   		printf("ALERT: ");
   		printf("Patient with that id not present. First make an entry in the patient file.\n");
   		return;
   }
   fclose(fp);
   
   //Making entry in doctor-patient file	
	fp=fopen("doctor_patient.txt","a+");
	if(fp==NULL){
		printf("Unable to open file.\n");
		return;
	}
	fwrite(&dp,sizeof(struct docPat),1,fp);
	fclose(fp);
	printf("Entry has been done successfully.\n");
}

//##########################################################//
//READ FUNCTIONS

//Reads and displays all the doctor entries
void readD(){
	struct Doctor d;
	FILE *fp;
	fp=fopen("doctor.txt","r+");
	if(fp==NULL)
		printf("Failed to load!!!");
	else{
			printf("\nENTRIES ARE:");
			while(fread(&d,sizeof(struct Doctor),1,fp))
			  {	
				printf("\n----------------------"); 
				printf("\nDoctor id : %d",d.id); 
			    printf("\nFirst Name     : %s",d.fname);
			    printf("\nLast Name      : %s",d.lname);
			    printf("\nAge            : %d",d.age);
			    printf("\nGender         : %c",d.gender);
			    printf("\nArea           : %s",d.area);
			   }
	}
	fclose(fp);
}

//Reads and displays all the patient entries
void readP()
{
	struct Patient p1;
	FILE *fp;
	fp=fopen("patient.txt","r+");
	if(fp==NULL)
		printf("Failed to load!!!");
	else
	{
		printf("\nENTRIES ARE:");
		while(fread(&p1,sizeof(struct Patient),1,fp))
		  {	
			printf("\n----------------------"); 
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

//Reads and displays all the common file entries
void readDP(){
	struct docPat dp;
	FILE *fp;
	fp=fopen("doctor_patient.txt","r+");
	if(fp==NULL){
		printf("Unable to open file.\n");
		return;
	}
	else
	{
		printf("\nENTRIES ARE:");
		while(fread(&dp,sizeof(struct docPat),1,fp))
		  {	
			printf("\n----------------------"); 
			printf("\nPatient id : %d",dp.patID); 
			printf("\nDoctor id : %d",dp.docID); 
		   }
		}
	fclose(fp);
}

//##########################################################//
//COUNT FUNCTIONS
void countPatients(){
	struct docPat dp;
	struct Doctor d;
	FILE *fp,*fp1;
	fp=fopen("doctor_patient.txt","r+");
	if(fp==NULL){
		printf("Unable to open file.\n");
		return;
	}
	else
	{
		int doc[100]={0};
		while(fread(&dp,sizeof(struct docPat),1,fp))
	   {	
			doc[dp.docID]++;
	   }
		
		//========================
		int i=0;
		while(i<100){
			if(doc[i]!=0){
				fp1=fopen("doctor.txt","r+");
			    if(fp1==NULL){
					printf("Unable to open doctor file.\n");
					return;
				}
				while(fread(&d,sizeof(struct Doctor),1,fp1)){
					if(d.id==i){
						printf("Name of Doctor: %s %s",d.fname,d.lname);
						printf(" | Patient Count: %d\n",doc[i]);
					}
				}
				fclose(fp1);
			}
			i++;
		}
	}
	fclose(fp);
}

/******************************************/
//Counting patients based on gender
void countGender(){
	struct docPat dp;
	struct Doctor d;
	struct Patient p;
	FILE *fp,*fp1;
	fp=fopen("doctor.txt","r+");
	while(fread(&d,sizeof(struct Doctor),1,fp)){
		int countM=0,countF=0,pat[20]={0},i=0;
		printf("Name of doctor: %s %s | ",d.fname,d.lname);
		
		//Reading patients associated with that doctor
		fp1=fopen("doctor_patient.txt","r+");
		while(fread(&dp,sizeof(struct docPat),1,fp1)){
			if(dp.docID==d.id){
				pat[i]=dp.patID;
				i++;
			}
		}
		fclose(fp1);
		
		//Checking if patient is male or female
		fp1=fopen("patient.txt","r+");
		while(fread(&p,sizeof(struct Patient),1,fp1)){
			if(ispresent(p.id,pat,i)){
				if(p.gender=='M'||p.gender=='m') countM++;
				else countF++;
			}
		}
		fclose(fp1);
		
		//Printing count
		printf("Male Patients - %d | Female Patients - %d\n",countM,countF);
	}
	fclose(fp);
}

//Auxillary function
int ispresent(int val,int arr[],int n){
	int i=0;
	for(i=0;i<n;i++){
		if(val==arr[i]) return 1;
	}
	return 0;
}

/******************************************/
//Counting patients based on area
void countArea(){
	struct docPat dp;
	struct Doctor d;
	struct Patient p;
	FILE *fp,*fp1;
	fp=fopen("doctor.txt","r+");
	while(fread(&d,sizeof(struct Doctor),1,fp)){
		int pat[20]={0},i=0,j=0,t;
		printf("\n-> Name of doctor: %s %s  Doctor id: %d\n",d.fname,d.lname,d.id);
		
		//Reading patients associated with that doctor
		fp1=fopen("doctor_patient.txt","r+");
		while(fread(&dp,sizeof(struct docPat),1,fp1)){
			if(dp.docID==d.id){
				pat[i]=dp.patID;
				i++;
			}
		}
		fclose(fp1);
		printf("\tTotal patients under consultation are %d. ",i);
		printf("Area of the patients is as follows:\n");
		int k=i;
		
		//Checking area of patient
		struct area a[20]={0,0};
		i=0;
		fp1=fopen("patient.txt","r+");
		while(fread(&p,sizeof(struct Patient),1,fp1)){
			if(ispresent(p.id,pat,k)){
				if((t=areaPresent(p,a,i))!=-1){
					a[t].c++;
				}else{
					add(p,a,i);
					a[i].c++;
					i++;	
				}
			}
		}
		fclose(fp1);
		
		//Printing count area
		for(j=0;j<i;j++){
			printf("\t%s : %d patients\n",a[j].area,a[j].c);
		}
		
	}
	fclose(fp);
}

int areaPresent(struct Patient p,struct area a[],int i){
	int j;
	for(j=0;j<i;j++){
		if(!strcmp(p.area,a[j].area)) return j;
	}
	return -1;
}

void add(struct Patient p,struct area a[],int i){
	strcpy(a[i].area,p.area);
}

/******************************************/
//Counting patients based on age
void countAge(){
	struct docPat dp;
	struct Doctor d;
	struct Patient p;
	FILE *fp,*fp1;
	fp=fopen("doctor.txt","r+");
	while(fread(&d,sizeof(struct Doctor),1,fp)){
		int countM=0,countF=0,pat[20]={0},i=0;
		printf("\n-> Name of doctor: %s %s\n",d.fname,d.lname);
		
		//Reading patients associated with that doctor
		fp1=fopen("doctor_patient.txt","r+");
		while(fread(&dp,sizeof(struct docPat),1,fp1)){
			if(dp.docID==d.id){
				pat[i]=dp.patID;
				i++;
			}
		}
		fclose(fp1);
		
		//Checking if patient is male or female
		fp1=fopen("patient.txt","r+");
		int age[100]={0};
		while(fread(&p,sizeof(struct Patient),1,fp1)){
			if(ispresent(p.id,pat,i)){
				age[p.age]++;
			}
		}
		fclose(fp1);
		
		//Printing count age
		i=0;
		while(i<100){
			if(age[i]!=0){
				printf("\tPatients of age %d: %d\n",i,age[i]);
			}
			i++;
		}
	}
	fclose(fp);
}

//##########################################################//
//ASCENDING ORDER FUNCTIONS
void adDate(){
	struct Patient p1,p2[20];
	struct Doctor d;
	struct date dy;
	int i=0;
	printf("Enter admission date (dd mm yy): ");
	scanf("%d %d %d",&dy.dd,&dy.mm,&dy.yy);
	FILE *fp;
	fp=fopen("patient.txt","r+");
	if(fp==NULL){
		printf("Unable to open file.\n");
		return;
	}
	while(fread(&p1,sizeof(struct Patient),1,fp)){
		if(p1.adate.dd==dy.dd&&p1.adate.mm==dy.mm&&p1.adate.yy==dy.yy){
			p2[i]=p1;
			i++;
		}
	}
	fclose(fp);
	
	if(i==0){
		printf("No patients were admitted on that date.\n");
		return;
	}
	printf("\nASCENDING ORDER BASED ON PATIENT IDs:");
	//Sorting based on id
	int j,flag,k;
	struct Patient temp;
		for(k=0;k<i-1;k++){
			flag=0;
			for(j=0;j<i-1-k;j++){
				if(p2[j].id>p2[j+1].id){
					temp=p2[j];
					p2[j]=p2[j+1];
					p2[j+1]=temp;
					flag=1;
				}
			}
			if(flag==0) break;
		}
		
	for(j=0;j<i;j++){
		list(p2[j]);
	}
}

void disDate(){
	struct Patient p1,p2[20];
	struct Doctor d;
	struct date dy;
	int i=0;
	printf("Enter discharge date (dd mm yy): ");
	scanf("%d %d %d",&dy.dd,&dy.mm,&dy.yy);
	FILE *fp;
	fp=fopen("patient.txt","r+");
	if(fp==NULL){
		printf("Unable to open file.\n");
		return;
	}
	while(fread(&p1,sizeof(struct Patient),1,fp)){
		if(p1.ddate.dd==dy.dd&&p1.ddate.mm==dy.mm&&p1.ddate.yy==dy.yy){
			p2[i]=p1;
			i++;
		}
	}
	fclose(fp);
	
	if(i==0){
		printf("No patients were admitted on that date.\n");
		return;
	}
	printf("\nASCENDING ORDER BASED ON PATIENT IDs:");
	//Sorting based on id
	int j,flag,k;
	struct Patient temp;
		for(k=0;k<i-1;k++){
			flag=0;
			for(j=0;j<i-1-k;j++){
				if(p2[j].id>p2[j+1].id){
					temp=p2[j];
					p2[j]=p2[j+1];
					p2[j+1]=temp;
					flag=1;
				}
			}
			if(flag==0) break;
		}
		
	for(j=0;j<i;j++){
		list(p2[j]);
	}
}

/********************************************************************/
//Just helps to list all the parameters of the structure entered as argument
void list(struct Patient p){
	printf("\n---------------------------------"); 
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
//Arranges patient under each doc in ascending order
void patientsUnderDoc(){
	struct docPat dp;
	struct Doctor d;
	struct Patient p;
	FILE *fp,*fp1;
	fp=fopen("doctor.txt","r+");
	while(fread(&d,sizeof(struct Doctor),1,fp)){
		int pat[20]={0},i=0,j=0;
		struct Patient p1[20];
		printf("\n\n#########################################\n");
		printf("--> NAME OF DOCTOR: %s %s    DOCTOR ID: %d\n",d.fname,d.lname,d.id);
		
		//Reading patients associated with that doctor
		fp1=fopen("doctor_patient.txt","r+");
		while(fread(&dp,sizeof(struct docPat),1,fp1)){
			if(dp.docID==d.id){
				pat[i]=dp.patID;
				i++;
			}
		}
		fclose(fp1);
		printf("Total patients under consultation are: %d",i);
		printf("\nASCENDING ORDER BASED ON PATIENT IDs:--->");
		
		fp1=fopen("patient.txt","r+");
		while(fread(&p,sizeof(struct Patient),1,fp1)){
			if(present(p,pat,i)){
				p1[j]=p;
				j++;
			}
		}
		fclose(fp1);
		
		//Sorting based on id
		int l,flag,k;
		struct Patient temp;
			for(k=0;k<j-1;k++){
				flag=0;
				for(l=0;l<j-1-k;l++){
					if(p1[l].id>p1[l+1].id){
						temp=p1[l];
						p1[l]=p1[l+1];
						p1[l+1]=temp;
						flag=1;
					}
				}
				if(flag==0) break;
			}
			
		for(k=0;k<j;k++){
			list(p1[k]);
		}
		
	}
	fclose(fp);
}

int present(struct Patient p,int pat[],int i){
	int j=0;
	for(j=0;j<i;j++){
		if(p.id==pat[j]) return 1;
	}
	return 0;
}

/********************************************************************/
//Arranges patient under each male doc in ascending order
void patientsUnderMaleDoc(){
	struct docPat dp;
	struct Doctor d;
	struct Patient p;
	FILE *fp,*fp1;
	fp=fopen("doctor.txt","r+");
	while(fread(&d,sizeof(struct Doctor),1,fp)){
		if(d.gender=='M'||d.gender=='m'){
			int pat[20]={0},i=0,j=0;
			struct Patient p1[20];
			printf("\n\n#########################################\n");
			printf("--> NAME OF DOCTOR: %s %s    \n--> DOCTOR ID: %d\n",d.fname,d.lname,d.id);
			printf("--> GENDER: %c\n",d.gender);
			
			//Reading patients associated with that doctor
			fp1=fopen("doctor_patient.txt","r+");
			while(fread(&dp,sizeof(struct docPat),1,fp1)){
				if(dp.docID==d.id){
					pat[i]=dp.patID;
					i++;
				}
			}
			fclose(fp1);
			printf("Total patients under consultation are: %d",i);
			printf("\nASCENDING ORDER BASED ON PATIENT IDs:--->");
			
			fp1=fopen("patient.txt","r+");
			while(fread(&p,sizeof(struct Patient),1,fp1)){
				if(present(p,pat,i)){
					p1[j]=p;
					j++;
				}
			}
			fclose(fp1);
			
			//Sorting based on id
			int l,flag,k;
			struct Patient temp;
				for(k=0;k<j-1;k++){
					flag=0;
					for(l=0;l<j-1-k;l++){
						if(p1[l].id>p1[l+1].id){
							temp=p1[l];
							p1[l]=p1[l+1];
							p1[l+1]=temp;
							flag=1;
						}
					}
					if(flag==0) break;
				}
				
			for(k=0;k<j;k++){
				list(p1[k]);
			}
		
		}
	}
	fclose(fp);
}

/********************************************************************/
//Arranges patient under each female doc in areawise ascending order
void patientsUnderFemaleDoc(){
	struct docPat dp;
	struct Doctor d;
	struct Patient p;
	FILE *fp,*fp1;
	fp=fopen("doctor.txt","r+");
	while(fread(&d,sizeof(struct Doctor),1,fp)){
		if(d.gender=='F'||d.gender=='f'){
			int pat[20]={0},i=0,j=0;
			struct Patient p1[20];
			printf("\n\n#########################################\n");
			printf("--> NAME OF DOCTOR: %s %s    \n--> DOCTOR ID: %d\n",d.fname,d.lname,d.id);
			printf("--> GENDER: %c\n",d.gender);
			
			//Reading patients associated with that doctor
			fp1=fopen("doctor_patient.txt","r+");
			while(fread(&dp,sizeof(struct docPat),1,fp1)){
				if(dp.docID==d.id){
					pat[i]=dp.patID;
					i++;
				}
			}
			fclose(fp1);
			printf("Total patients under consultation are: %d",i);
			printf("\nASCENDING ORDER BASED ON PATIENT AREAs:--->");
			
			fp1=fopen("patient.txt","r+");
			while(fread(&p,sizeof(struct Patient),1,fp1)){
				if(present(p,pat,i)){
					p1[j]=p;
					j++;
				}
			}
			fclose(fp1);
			
			//Sorting based on id
			int l,flag,k;
			struct Patient temp;
				for(k=0;k<j-1;k++){
					flag=0;
					for(l=0;l<j-1-k;l++){
						if(strcmp(p1[l].area,p1[l+1].area)>0){
							temp=p1[l];
							p1[l]=p1[l+1];
							p1[l+1]=temp;
							flag=1;
						}
					}
					if(flag==0) break;
				}
				
			for(k=0;k<j;k++){
				list(p1[k]);
			}
		
		}
	}
	fclose(fp);
}

/********************************************************************/
//Finds doc having least number of patients and adds entry
void leastp(){
	struct docPat dp;
	struct Doctor d,d1[20];
	int count[20],i=0,min;
	struct Patient p;
	FILE *fp,*fp1;
	fp=fopen("doctor.txt","r+");
	while(fread(&d,sizeof(struct Doctor),1,fp)){
		fp1=fopen("doctor_patient.txt","r+");
		while(fread(&dp,sizeof(struct docPat),1,fp1)){
			if(dp.docID==d.id){
				count[i]++;
			}
		}
		fclose(fp1);
		d1[i]=d;
		i++;
	}
	fclose(fp);
	
	//Sorting doctor name according to ascending order
	int l,flag,k,t;
	struct Doctor temp;
	for(k=0;k<i-1;k++){
		flag=0;
		for(l=0;l<i-1-k;l++){
			if(strcmp(d1[l].fname,d1[l+1].fname)>0){
				temp=d1[l];
				d1[l]=d1[l+1];
				d1[l+1]=temp;
				t=count[l];
				count[l]=count[l+1];
				count[l+1]=t;
				flag=1;
			}
		}
		if(flag==0) break;
	}
	
	//Finding doctor with minimum patient count
	min=0;
	for(k=0;k<i;k++){
		if(count[k]<count[min]) min=k; 
	}
	printf("Doctor with minimum patients: %s %s",d1[min].fname,d1[min].lname);
	printf(" | Doctor ID: %d\n",d1[min].id);
	printf("Make an entry with doctor id - %d and a new patient consulting the doctor.\n\n",d1[min].id);
	printf("Enter the information again:\n");
	inputdp();
}

/*********END OF PROGRAMME**********/
