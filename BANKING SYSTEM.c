#include <stdio.h>
#include <string.h>
#include <stdlib.h>
static int accountNumber;

struct Bank
{
    char name[20];
    char pass[20];
    int acc_no;
    float bal;
    float Loan;
    int withdraws;
    float intrestrate;
};
//here we have declared an user defined varible//
void createAccount(void);
void showAccount(void);
void depositMoney(void);
void withdrawMoney(void);
void deleteAccount(void);
void view(void);
void loanApplication(void);
void loanPayment(void);
void loanAmountCheck(void);
void editname(void);
void loanintrestPayment(void);
void refreshwithdraws(void);
//here we have declared all the reqired functions in program//
int main()
{
    int choice,options;

    while(1)
    {
        printf("\n\n                                          BANK MANAGEMENT SYSTEM MENU \n");
        printf("\n1. New Account creation \n2. Existing user\n3.to view all accounts \n4.quit\n");
        printf("\nEnter your choice: ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                createAccount();
                break;
            case 2:
                showAccount();

                printf("select a option \n 1.deposit money\n 2.withdraw money\n 3.loan application\n 4.loan payment\n 5.intrest payment\n 6.loan amount check\n 7.Deleting the account\n 8.edit name\n 9.logout\n");
                printf("\nEnter your choice: ");
                scanf("%d",&options);
                switch(options)
                {
                    case 1:
                        depositMoney();
                        break;
                    case 2:
                        withdrawMoney();
                        break;
                    case 7:
                        deleteAccount();
                        break;
                    case 9:
                        main();
                        break;
                    case 3:
                        loanApplication();
                        break;
                    case 4:
                        loanPayment();
                        break;
                    case 5:
                        loanintrestPayment();
                        break;
                    case 6:
                        loanAmountCheck();
                        break;
                    case 8:
                        editname();
                        break;
                    default:
                        printf("\nPlease enter correct choice\n");
                        //here we hve given all the options for selection//
                }
                
            case 3:
                view();
                break;
            case 5:
                refreshwithdraws();
                break;
            case 4:
                exit(0);
                break;
        }
    }

    return 0;
}
int uniqueaccount(int a)
{
    FILE *fp;
    struct Bank b;
    int tempaccountno=0;
    int found =0;

    fp = fopen("Bankrecord5.dat","rb+");
    while(fread(&b,sizeof(b),1,fp)>0)
    {
        if(b.acc_no==a)
        {
            tempaccountno=rand();
            found=1;
        }
    }
    if(found==0)
    {
        tempaccountno=a;
    }
    return tempaccountno;
    
}

void createAccount()
{
    FILE *fp;
    struct Bank b;
    int accountno;

    fp = fopen("Bankrecord5.dat","ab+");

    printf("\nEnter Name: ");
    scanf("%s",b.name);
    printf("\ncreate the password of the account:");
    scanf("%s",b.pass);
    printf("\nEnter Balance: ");
    scanf("%f",&b.bal);
    accountno = rand();
    accountno=uniqueaccount(accountno);
    b.acc_no=accountno;
    printf("Your account number is %d\n", accountno);
    b.Loan=0;
    b.withdraws=0;
    b.intrestrate=0;
    
    fwrite(&b,sizeof(b),1,fp);
    fclose(fp);

    printf("\nAccount Created Successfully\n");
    //here we have opened an file and recorded all the data of an account in it//
}

void showAccount()
{
    struct Bank b;
    char password[20];
    int found=0;
    FILE *fp;
    fp=fopen("Bankrecord5.dat","rb");
    printf("\nenter account number :");
    scanf("%d",&accountNumber);
    printf("\nenter the password : ");
    scanf("%s",password);
    while(fread(&b,sizeof(b),1,fp)>0)
    {
        if(accountNumber==b.acc_no && strcmp(b.pass, password)==0)
        {
            printf("\nAccount Number : %d\nName : %s\nBalance : %.2f\nLoan : %.2f\n\n",b.acc_no,b.name,b.bal,b.Loan);
            found=1;
            break;
        }
        
    }
    fclose(fp);
    if(found==0)
    {
        printf("\nNo account was there with that account number\n");
        main();
    }
}

void depositMoney()
{
    FILE *fp;
    struct Bank b;
    int found=0;
    float amount;
  
    fp = fopen("Bankrecord5.dat","rb+");

    while(fread(&b,sizeof(b),1,fp))
    {
        if(b.acc_no==accountNumber)
        {
            found = 1;
            printf("\nEnter Amount to Deposit: ");
            scanf("%f",&amount);
            b.bal += amount;
            fseek(fp,-1*sizeof(b),SEEK_CUR);
            //fseek is used to change the
            fwrite(&b,sizeof(b),1,fp);
            break;
        }
    }

    fclose(fp);
    
    if(found == 1)
        printf("\nDeposit Successful\n");
    main();
}

void withdrawMoney()
{
    FILE *fp;
    int i=0;
    struct Bank b;
    int found=0;
    float amount;

    fp = fopen("Bankrecord5.dat","rb+");
    
    while(fread(&b,sizeof(b),1,fp))
    {
        if(b.acc_no==accountNumber)
        {
            if(b.withdraws<2)
            {
                found = 1;
                printf("\nEnter Amount to Withdraw: ");
                scanf("%f",&amount);
                if(b.bal < amount&&amount <40000)
                {
                    printf("\nInsufficient Balance\n");
                }
                else
                {
                    b.bal -= amount;
                    fseek(fp,-1*sizeof(b),SEEK_CUR);
                    b.withdraws++;
                    fwrite(&b,sizeof(b),1,fp);
                    printf("\nWithdraw Successful\n");
                }
                break;
                
            }
            else
            {
                printf("you are only allowed to do with draw twice a day");
            }
        }
        
    }

    fclose(fp);
    i++;
    
    main();
}


void view()
{
    struct Bank b;
    int i=1;
    FILE *fp=fopen("Bankrecord5.dat","rb");
    
    while(fread(&b,sizeof(b),1,fp)>0)
    {
        printf("\naccount-%d",i);
        printf("\nAccount Number : %d\nName : %s\nBalance : %.2f\nLoan : %.2f\npassword:%s\nwithdraws:%d\ninterest rate: %.2f\n",b.acc_no,b.name,b.bal,b.Loan,b.pass,b.withdraws,b.intrestrate);
        i++;
    }
    fclose(fp);
    main();
}
void deleteAccount()
{
    struct Bank b;
    FILE *fp,*temp;
    fp=fopen("Bankrecord5.dat","r");
    temp=fopen("Bankrecord6.dat","w");
    int found=0;
   
    while(fread(&b,sizeof(b),1,fp))
    {
        if(accountNumber==b.acc_no)
        {
            printf("\nAccount Deleted Successfully\n");
            found=1;
            continue;
        }
        else
        {
            fwrite(&b,sizeof(b),1,temp);
           
        }
    }
    if(found==0)
    {
        printf("\n no account is available with that account number please create a account");
    }
    fclose(fp);
    fclose(temp);
    remove("Bankrecord5.dat");
    rename("Bankrecord6.dat","Bankrecord5.dat");
    main();
}
void loanApplication()
{
    struct Bank b;
    int amount;
    FILE *fp;
    int intrestrate,time;
    fp=fopen("Bankrecord5.dat","rb+");
    while(fread(&b,sizeof(b),1,fp))
    {
        if(accountNumber==b.acc_no)
        {
            if(accountNumber==b.acc_no)
            {
                printf("\nEnter the Loan Amount : ");
                scanf("%d",&amount);
                printf("\n enter the intrest rate : ");
                scanf("%d",&intrestrate);
                printf("\n enter the time period : ");
                scanf("%d",&time);
                b.intrestrate=amount*intrestrate*time/100;
                
                b.Loan+=amount;
                fseek(fp,-1*sizeof(b),SEEK_CUR);
                fwrite(&b,sizeof(b),1,fp);
                break;
            }
        }
    }
    fclose(fp);
    
    main();
}

void loanPayment()
{
    struct Bank b;
    float amount;
    FILE *fp;
    fp=fopen("Bankrecord5.dat","rb+");
    while(fread(&b,sizeof(b),1,fp))
    {
        if(accountNumber==b.acc_no)
        {
            printf("\nEnter the Loan Payment : ");
            scanf("%f",&amount);
            if(b.Loan>=amount)
            {
                b.Loan-=amount;
                fseek(fp,-1*sizeof(b),SEEK_CUR);
                fwrite(&b,sizeof(b),1,fp);
                printf("loan payment suceesfull");
                break;
            }
            else
            {
                printf("\nInsufficient Loan Amount\n");
                break;
            }
        }
            
    }
    fclose(fp);
    main();
}
    

void loanAmountCheck()
{
    struct Bank b;
    FILE *fp;
    fp=fopen("Bankrecord5.dat","r");
    while(fread(&b,sizeof(b),1,fp))
    {
        if(accountNumber==b.acc_no)
        {
            printf("\nThe Loan Amount is %f\n",b.Loan);
            break;
        }
    }
    fclose(fp);
    main();
   
}
void editname()
{
    FILE *fp;
    struct Bank b;
    int found=0;
    
    fp = fopen("Bankrecord5.dat","rb+");
    
    while(fread(&b,sizeof(b),1,fp))
    {
        if(b.acc_no==accountNumber)
        {
            found = 1;
            printf("\nenter the chnaged name: ");
            scanf("%s",b.name);
            fseek(fp,1*sizeof(b),SEEK_CUR);
            fwrite(&b,sizeof(b),1,fp);
            break;
        }
    }
    
    fclose(fp);
    
    main();
}
void loanintrestPayment()
{
    struct Bank b;
    float amount;
    FILE *fp;
    fp=fopen("Bankrecord5.dat","rb+");
    while(fread(&b,sizeof(b),1,fp))
    {
        if(accountNumber==b.acc_no)
        {
            printf("\nthe amount to Paid %.2f: ",b.intrestrate);
            scanf("%f",&amount);
            if(b.intrestrate>=amount)
            {
                b.intrestrate-=amount;
                fseek(fp,-1*sizeof(b),SEEK_CUR);
                fwrite(&b,sizeof(b),1,fp);
                printf("loan payment suceesfull");
                break;
            }
            else
            {
                printf("\nInsufficient Loan Amount\n");
                break;
            }
        }
        
    }
    fclose(fp);
    main();
    
}
void refreshwithdraws(void)
{
    struct Bank b;
    FILE *fp;
    fp=fopen("Bankrecord5.dat","rb+");
    while(fread(&b,sizeof(b),1,fp)>0)
    {
        b.withdraws=0;
        fseek(fp,-1*sizeof(b),SEEK_CUR);
        fwrite(&b,sizeof(b),1,fp);
        
    }
    fclose(fp);
}