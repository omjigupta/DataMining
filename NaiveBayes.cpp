#include<iostream>
#include<conio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include<fstream>
#include<sstream>
using namespace std;

void nv(char Data[100][100][30],int,int,int dom[30],int,int);


void nv(char Data[100][100][30],int test_sz,int training_sz,int dom[30],int n,int d)
{
	char test[test_sz][d][30],trng[training_sz][d][30];
	int i=0,j=0,i1=0;
	cout<<"\nTest data set :\n";						
	for(i=0;i<test_sz;i++)
    {
    	for(j=0;j<d;j++)
    	{
    		strcpy(test[i][j],Data[i][j]);
    		cout<<test[i][j]<<" ";
    	}
    	cout<<endl;
	}
	cout<<"\nTraining data set :\n";					
	for(i=test_sz;i<n;i++)
    {	
    	for(j=0;j<d;j++)
    	{	
    		strcpy(trng[i1][j],Data[i][j]);
    		cout<<trng[i1][j]<<" ";
    	}
    	i1++;
    	cout<<endl;
	}
	
	char cl1[30],cl2[30];
	float c1count=0,c2count=0;
	float Pc1,Pc2;
	strcpy(cl1,Data[0][d-1]);							
	for(i=1;i<n;i++)
	{
		if(strcmp(cl1,Data[i][d-1])!=0)
		{
			strcpy(cl2,Data[i][d-1]);
			break;
		}
	}
	for(i=0;i<training_sz;i++)
	{
		if(strcmp(cl1,trng[i][d-1])==0)
			c1count+=1;
		else
			c2count+=1;
	}
	Pc1=c1count/training_sz;
	Pc2=c2count/training_sz;
	
	
	float Px[d-1],Pc1x=1,Pc2x=1;
	for(i=0;i<d-1;i++)
		Px[i]=0;
	
	for(i=0;i<test_sz;i++)							
	{
		for(j=0;j<d-1;j++)
		{
			for(i1=0;i1<training_sz;i1++)
			{
				if((strcmp(test[i][j],trng[i1][j])==0)&&(strcmp(trng[i1][d-1],cl1)==0))
					Px[j]+=1;
			}
			if(Px[j]==0)
				Px[j]=1/(c1count+dom[j]);
			else
				Px[j]=(Px[j]/c1count);
			Pc1x*=Px[j];
			Px[j]=0;
		}
		Pc1x*=Pc1;
		cout<<"\n"<<Pc1x<<" ";
		
		for(j=0;j<d-1;j++)
		{
			for(i1=0;i1<training_sz;i1++)
			{
				if((strcmp(test[i][j],trng[i1][j])==0)&&(strcmp(trng[i1][d-1],cl2)==0))
					Px[j]+=1;
			}
			if(Px[j]==0)
				Px[j]=1/(c2count+dom[j]);
			else
				Px[j]=(Px[j]/c2count);
			Pc2x*=Px[j];
			Px[j]=0;
		}
		Pc2x*=Pc2;
		cout<<Pc2x;
		if(Pc1x>Pc2x)										
			strcpy(test[i][d-1],cl1);
		else
			strcpy(test[i][d-1],cl2);
		Pc1x=1;
		Pc2x=1;
	}
	cout<<"\nTest set after classification:\n";
	for(i=0;i<test_sz;i++)
	{
		for(j=0;j<d;j++)
		{
			cout<<test[i][j]<<" ";
		}
		cout<<"\n";
	}
	
	float Tc1=0,Tc2=0,Fc1=0,Fc2=0;
	for(i=0;i<test_sz;i++)
	{
		if((strcmp(Data[i][d-1],cl1)==0)&&(strcmp(test[i][d-1],cl1)==0))
			Tc1+=1;
			
		if((strcmp(Data[i][d-1],cl1)==0)&&(strcmp(test[i][d-1],cl2)==0))
			Fc2+=1;
			
		if((strcmp(Data[i][d-1],cl2)==0)&&(strcmp(test[i][d-1],cl1)==0))
			Fc1+=1;
			
		if((strcmp(Data[i][d-1],cl2)==0)&&(strcmp(test[i][d-1],cl2)==0))
			Tc2+=1;
	}
	
	
	float confusion_matrix[2][2]={Tc1,Fc2,Fc1,Tc2};	
	cout<<"\nConfusion Matrix \t\t\t\t:\n\n";
	cout<<cl1<<" "<<cl2<<"\n";
	
	for(i=0;i<2;i++)
	{
		for(j=0;j<2;j++)
		{
			cout<<confusion_matrix[i][j]<<" ";
		}
		cout<<"\n";
	}
	
	
	

	float pre_c1=0,rec_c1=0,F_measure1=0;
	float pre_c2=0,rec_c2=0,F_measure2=0;
						
	pre_c1=Tc1/(Tc1+Fc1);
	cout<<"\t\t\n Precision for cl1"<<cl1<<"is :"<<pre_c1<<"\n\n";
	
	rec_c1=Tc1/(Tc1+Fc2);
	cout<<"\t\t\n Recall for cl1"<<cl1<<"is :"<<rec_c1<<"\n\n";
	
	F_measure1=(2*rec_c1*pre_c1)/(rec_c1+pre_c1);
    cout<<"\t\t\n F-measure for cl1"<<cl1<<"is :"<<F_measure1<<"\n\n";
    
	pre_c2=Tc2/(Tc2+Fc2);
	cout<<"\t\t\n Precision for cl2 "<<cl2<<"is :"<<pre_c2<<"\n\n";
	
	rec_c2=Tc2/(Tc2+Fc1);
	cout<<"\t\t\n Recall for cl2"<<cl2<<"is :"<<rec_c2<<"\n\n";
	
	F_measure2=(2*rec_c2*pre_c2)/(rec_c2+pre_c2);	
	
	cout<<"\t\t\n F-measure for cl2 "<<cl2<<"is :"<<F_measure2<<"\n\n";

}
int main()
{
	int i=0,j=0,j1=0,n=0,d=0;
	string lines,line1;
	char db[20], d_set[20],line[300],Data[100][100][30];
	
	int test_sz,training_sz;				
	
	
	
	cout<<"enter the filename of the d_set\n";
	cin>>d_set;
	
	strcpy(db,d_set);
	strcat(db,".csv");
	
	ifstream is1(db);
	
	if(!is1)
	{
		cout<<"Dataset is not available so can't proceed further\n\n TRY AGAIN!!!'\n";
		exit(0);
	}
	
	while(getline(is1,lines))						
	{
		n++;
	}
	
   	 ifstream is(db);
   	 getline(is,line1);
    
	while(line1[i]!='\0')							
		{
				cout<<line1[i];
				if(line1[i]==',')
					d++;
				i++;
		}
	cout<<endl;
		
	char *end=0;
	stringstream  linestr;
	double temp;
	char  cell[50];
	
	i=0,j=0;
	while (is.getline(line,2500,'\n'))						
    {
    	cout<<line<<endl;
        linestr<<line;
        
        while(linestr.getline(cell,100,','))
        {
        	
			  strcpy(Data[i][j],cell);
             j++;
        }
     	j=0;
     	i++;
     	linestr.clear();
    }
   /* for(i=0;i<n-1;i++)
    {
    	for(j=0;j<d+1;j++)
    	{
    	
    		cout<<Data[i][j]<<" ";
    	}
    	cout<<endl;
	}*/
	cout<<endl;
        cout<<"\n\n no of attributes in d_set:"<<d+1<<endl;
	cout<<"\n\n no of instances d_set:"<<n-1;

	int dom[d+1],flag=0;					
	for(i=0;i<d+1;i++)
		dom[i]=0;
	for(i=0;i<d+1;i++)
	{
		for(j=0;j<n-1;j++)
		{
			j1=0,flag=0;
			while(j1!=j)
			{
				if(strcmp(Data[j][i],Data[j1][i])==0)
					flag=1;
				j1++;
			}
			if(flag==0)
				dom[i]+=1;
		}
	}
	

   	 test_sz=(n-1)/4;
	training_sz=(n-1)-test_sz;
	nv(Data,test_sz,training_sz,dom,n-1,d+1);
	return 0;
	getch();
}
