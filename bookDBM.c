#pragma warning (disable:4996)
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
 typedef struct bookinformation {
	char bkname[30];			//å�̸�
	char qtity[30];				//���
	char price[30];				//����
	struct bookinformation* ptr;	
}bkinfo;
 typedef struct Authorinformation {
	 char Lname[30];			//��
	 char Fname[30];			//�̸�
	 bkinfo* ptr;
 }Author;
int search(Author A[], char L[], char F[]);	//���� �̸����� Author�迭�� �Էµ� ���ڰ� �ִ��� Ȯ�� �Ϸ�
void greeting();							//ȯ�� �Ϸ�
void readDatabase(Author* inven);			//������ ���̽� �о������ �Ϸ�
int printMenu();							//�޴� �Ϸ�
void displayinventory(Author A[]);			//1�� �Ϸ�
void displayAuthorsWork(Author A[]);		//2�� �Ϸ�
void addBook(Author* A);					//3�� �Էµ� qty�� �������� ���� ó�� �Ϸ�,�Էµ� price�� �Ǽ����� ���� ó�� �Ϸ�
void ChangePrice(Author* A);				//4�� �Էµ� price�� �Ǽ����� ���� ó�� �Ϸ�
void ChangeQty(Author* A);					//5�� �Էµ� qty�� �������� ���� ó�� �Ϸ�
void totalQty(Author A[]);					//6�� �Ϸ�
void CalculateTotalAmount(Author A[]);		//7�� �Ϸ� å���� ������ ������ å����*����� ������ ���� �ϴ� ������ ���� �ڵ�
int check_int(char string[]);				//���ڿ��� �������� �ƴ��� Ȯ���ϴ� �Լ�,�����Ͻ� 1,�ƴҽ� 0���
int check_double(char string[]);			//���ڿ��� �Ǽ����� �ƴ��� Ȯ���ϴ� �Լ�,�Ǽ��Ͻ� 1,�ƴҽ� 0���
int main()
{
	int choice;
	int flag = 1;
	greeting();
	Author theInventory[20];
	readDatabase(theInventory);
	while (flag) {
		choice = printMenu();
		if (choice == 1)
			displayinventory(theInventory);
		else if (choice == 2)
			displayAuthorsWork(theInventory);
		else if (choice == 3)
			addBook(theInventory);
		else if (choice == 4)
			ChangePrice(theInventory);
		else if (choice == 5)
			ChangeQty(theInventory);
		else if (choice == 6)
			totalQty(theInventory);
		else if (choice == 7)
			CalculateTotalAmount(theInventory);
		else if (choice == 8)
		{
			printf("Thank you for using this program");
			flag = 0;
		}
		else
			printf("invalid choice\n");
	}
	return 0;
}

int search(Author A[], char L[], char F[])
{
	for (int i = 0; i < 20; i++)
	{
		if (strcmp(A[i].Lname,L)==0 && strcmp(A[i].Fname,F)==0)
		{
			return i;
		}
	}
	return -1;
}

void greeting() {
	printf("Welcome to the bookstore program!\n");
}

void readDatabase(Author* inven)															//ó�� ������ ���̽��� �Է�
{
	char filename[20];																		//�����̸�
	char* Cptr;																				//�ڸ� ���ڿ��� ��ġ
	bkinfo* lptr;																			//bkinfo�� ��ġ
	bkinfo* newbk;																			//bkinfo���� ����
	char lname[30], fname[30], name[30], qty[30], much[30];				
	int i = 0;																				//Author�迭�� ������ ��ġ�� ��Ÿ��
	int loc=0;																				//Author�迭���� �̹��Էµ� ������ ��ġ�� ��Ÿ��
	char info[100];																			//�Է¹��� ���ڿ�
	FILE* fp=NULL;
	while (fp == NULL)
	{
		printf("Enter the name of the file:");													//���� �̸� �Է�
		scanf("%s", filename);
		fp = fopen(filename, "r");
		if (fp == NULL) printf("invalid file\n");
	}
	for (int j = 0; j < 20; j++)															//Author�迭�� ptr�� ���� �ʱ�ȭ
	{
		inven[j].ptr = NULL;
	}
	while (!feof(fp))																		//������ ������
	{
		Cptr=fgets(info,100,fp);															//������ ������ �޾ƿͼ� ������ ����
		Cptr = strtok(info, ",");
		strcpy(lname, Cptr);
		Cptr = strtok(NULL, ",");
		strcpy(fname, Cptr);
		Cptr = strtok(NULL, ",");
		strcpy(name, Cptr);
		Cptr = strtok(NULL, ",");
		strcpy(qty, Cptr);
		Cptr = strtok(NULL, ",");
		strcpy(much, Cptr);
		loc = search(inven, lname, fname);													//Author�迭�� �Էµ� �۰��� �̹� �ִ��� Ȯ��
		newbk = (bkinfo*)malloc(sizeof(bkinfo));											//bkinfo���� �Ҵ�
		newbk->ptr = NULL;
		if (loc == -1)																		//Author�迭�� �Էµ��� ���� �۰���� 
		{
			strcpy(inven[i].Lname, lname);											
			strcpy(inven[i].Fname, fname);
			inven[i].ptr = newbk;
			strcpy(newbk->bkname, name);
			strcpy(newbk->qtity, qty);
			strcpy(newbk->price, much);
			i++;
		}
		else																				//Author�迭�� �̹� �ִ� �۰����
		{
			lptr = inven[loc].ptr;
			while (lptr->ptr != NULL)														//���Ḯ��Ʈ�� ���� �������� ���ο� bkinfo�� ����
				lptr = lptr->ptr;
			lptr->ptr = newbk;
			strcpy(newbk->bkname, name);
			strcpy(newbk->qtity, qty);
			strcpy(newbk->price, much);
		}
	}
	return;
}

int printMenu()
{
	int choice;
	printf("-----------------------------------------------------\n");
	printf("Enter 1 to display the inventory\n");
	printf("Enter 2 to display the books by one author\n");
	printf("Enter 3 to add a book\n");
	printf("Enter 4 to change the price\n");
	printf("Enter 5 to change the Qty\n");
	printf("Enter 6 to view the total number of book in the inventory\n");
	printf("Enter 7 to see total amount of entire inventory\n");
	printf("Enter 8 to exit\n");
	printf("Enter your choice:");
	rewind(stdin);
	scanf("%d", &choice);
	return choice;
}
void displayinventory(Author A[]) {			//����Ʈ �ȿ� �ִ� ������ �����ִ� �Լ� 1�� ���
	bkinfo* Nptr = NULL;					//���,������ ���� ������
	bkinfo* Hptr = NULL;
	Author temp;
	int i = 0,j=0;
	while (A[i].ptr != NULL)				//���������� �̿��Ͽ� ���ڹ迭�� ��ġ �ٲ�
	{
		while (A[j].ptr != NULL)
		{
			if (strncmp(A[i].Lname,A[j].Lname,1)>0)
			{
				temp = A[j];
				A[j] = A[i];
				A[i] = temp;
			}
			j = j + 1;
		}
		i = i + 1;
		j = i + 1;
	}
	i = 0;															//���
	while(A[i].ptr!=NULL)
	{
		printf("The author is :%s,%s\n", A[i].Lname, A[i].Fname);				
		Nptr = A[i].ptr;														
		do
		{																		
			printf("\n\tThe title is : %s\n", Nptr->bkname);
			printf("\tThe qty is :%s\n", Nptr->qtity);
			printf("\tThe price is :%s\n", Nptr->price);
			printf("\t------------------\n");
			Nptr = Nptr->ptr;													
		} while (Nptr != NULL);													
		i = i + 1;
	}
}

void displayAuthorsWork(Author A[])												//�Էµ� �۰��� å���� ���
{
	int loc = 0;																//Author�迭���� �Էµ� �۰��� �ε���
	bkinfo* Nptr;																//��� ������ ���� ������
	char Last[30], First[30];													//��,�̸�
	printf("Enter the author's first name:");
	scanf("%s", First);
	printf("Enter the author's last name:");
	scanf("%s", Last);
	loc = search(A, Last, First);												//�Էµ� �۰��� �̸��� ������ Author �迭�� ���°�� ��ġ�� �ִ��� Ȯ��
	if (loc == -1)																//�Էµ� ������ ��Ī�Ǵ� �۰��� ���ٸ�
		printf("Sorry,but no books by %s, %s in the inventory\n",Last,First);		
	else																		//�Էµ� ������ ��Ī�Ǵ� �۰��� �ִٸ�
	{
		Nptr = A[loc].ptr;														//Nptr�� �Էµ� �۰��� head bkinfo�� ����Ŵ
		do																		//���Ḯ��Ʈ�� ������ ���
		{
			printf("\n\tThe title is : %s\n", Nptr->bkname);
			printf("\tThe qty is :%s\n", Nptr->qtity);
			printf("\tThe price is :%s\n\n", Nptr->price);
			printf("\t------------------\n");
			Nptr = Nptr->ptr;
		} while (Nptr != NULL);

	}
	return;
}

void addBook(Author * A)
{
	int loc = 0;
	int i = 0;
	int check_i = 0; //�������� Ȯ��
	int check_d = 0; //�Ǽ����� Ȯ��
	bkinfo* Nptr;
	bkinfo* newbk=(bkinfo*)malloc(sizeof(bkinfo));
	char lname[30], fname[30],bkname[30];
	printf("Enter the author's first name:");
	scanf("%s", fname);
	printf("Enter the author's last name:");
	scanf("%s", lname);
	printf("Enter the title:");
	rewind(stdin);
	scanf("%[^\n]s", bkname);
	rewind(stdin);
	loc = search(A, lname, fname);
	if (loc == -1)							//���ο� ������ å
	{
		while (A[i].ptr != NULL)
		{
			i++;
		}
		strcpy(A[i].Fname, fname);
		strcpy(A[i].Lname, lname);
		A[i].ptr = newbk;
	}
	else							//���������� å
	{
		Nptr = A[loc].ptr;
		while (Nptr->ptr != NULL)
		{
			if (strcmp(Nptr->bkname, bkname) == 0)					//�߰��Ϸ��� å�� �̹� �ִ°��
			{
				printf("This book is already in the Inventory and cannot be added again\n");
				free(newbk);
				return;
			}
			Nptr = Nptr->ptr;
		}
		Nptr->ptr = newbk;
	}
	strcpy(newbk->bkname, bkname);
	while (check_i == 0)				//qty�� ������ �ԷµǴ���exception handling
	{
		printf("Enter the qty:");
		rewind(stdin);
		scanf("%s", &newbk->qtity);
		check_i=check_int(newbk->qtity);
		if (check_i == 0)
		{
			printf("invalid input for qty\n");
		}
	}
	while (check_d == 0)				//price�� �Ǽ��� �ԷµǴ���exception handling
	{
		printf("Enter the price:");
		rewind(stdin);
		scanf("%s", &newbk->price);
		check_d=check_double(newbk->price);
		if (check_d == 0)
		{
			printf("invalid input for price\n");
		}
	}
	newbk->ptr = NULL;
}

void ChangePrice(Author * A)
{
	int loc = 0;
	int i = 0;
	int check = 0;
	char lname[30], fname[30],name[30],price[30];
	bkinfo* Nptr;
	printf("Enter the author's first name:");
	scanf("%s", fname);
	printf("Enter the author's last name:");
	scanf("%s", lname);
	loc=search(A, lname, fname);
	if (loc == -1)						//���ڰ� ���°��
	{
		printf("No such author in your database. So you cannot change the price\n");
	}
	else								//�ִ°��
	{
		Nptr = A[loc].ptr;
		printf("Enter the Bookname:");
		rewind(stdin);
		scanf("%[^\n]s", name);
		while (Nptr!=NULL)
		{
			if (strcmp(Nptr->bkname, name) == 0)
			{
				break;
			}
			Nptr = Nptr->ptr;
		}
		if (Nptr == NULL)														//å�� ���°��
		{
			printf("No book with the title %s by %s,%s\n", name, lname, fname);
		}
		else																	//å�� �ִ°��
		{
			while (check == 0)
			{
				printf("Enter the price:");
				scanf("%s", price);
				check = check_double(price);
				if (check == 0)
				{
					printf("invalid input for price\n");
				}
			}
			strcpy(Nptr->price,price);
		}
	}
}
void ChangeQty(Author* A)
{
	int loc = 0;
	int i = 0;
	int check = 0;
	char lname[30], fname[30], name[30], qty[30];
	bkinfo* Nptr;
	printf("Enter the author's first name:");
	scanf("%s", fname);
	printf("Enter the author's last name:");
	scanf("%s", lname);
	loc = search(A, lname, fname);
	if (loc == -1)
	{
		printf("No such author in your database. So you cannot change the qty\n");
	}
	else
	{
		Nptr = A[loc].ptr;
		printf("Enter the Bookname:");
		rewind(stdin);
		scanf("%[^\n]s", name);
		while (Nptr != NULL)
		{
			if (strcmp(Nptr->bkname, name) == 0)
			{
				break;
			}
			Nptr = Nptr->ptr;
		}
		if (Nptr == NULL)
		{
			printf("No book with the title %s by %s,%s\n", name, lname, fname);
		}
		else
		{
			while (check == 0)
			{
				printf("Enter the Qty:");
				scanf("%s", qty);
				strcpy(Nptr->qtity, qty);
				check=check_int(Nptr->qtity);
				if (check == 0)
					printf("invalid input for qty\n");
			}
		}
	}
}

void totalQty(Author A[])
{
	int i = 0;
	bkinfo* temp;
	int totalqty = 0;
	while (A[i].ptr != NULL)								//��ü å�� ���� ���
	{
		temp = A[i].ptr;
		while (temp != NULL)
		{
			totalqty = totalqty + atoi(temp->qtity);
			temp = temp->ptr;
		}
		i = i + 1;
	}
	printf("The total number of book is %d\n", totalqty);
}

void CalculateTotalAmount(Author A[])
{
	int i = 0;
	bkinfo* temp;
	double totalprice = 0;
	while (A[i].ptr != NULL)									//��ü å�� ���� ���
	{
		temp = A[i].ptr;
		while (temp != NULL)
		{
			totalprice = totalprice + atof(temp->price);
			temp = temp->ptr;
		}
		i = i + 1;
	}
	printf("The total amount of entire book is %.2lf\n", totalprice);
}

int check_int(char string[])					//���ڿ��� ������ �ƴϸ� 0�� ��ȯ 
{
	int check;
	int i = 0;
	while (string[i]!='\0')
	{
		check = 1;
		if (!isdigit(string[i]))
		{
			check = 0;
			break;
		}
		i++;
	}
	return check;
}

int check_double(char string[])
{
	int check;
	int comma = 0;
	int i = 0;
	while (string[i] != '\0')
	{
		check = 1;
		if (!isdigit(string[i]))
		{
			if (string[i] == '.')
			{
				comma+= 1;
			}
			else
			{
				check = 0;
				break;
			}
		}
		i++;
	}
	if (check == 1 && comma == 1)
	{
		return 1;
	}
	else
		return 0;
}
