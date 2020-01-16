#pragma warning (disable:4996)
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
 typedef struct bookinformation {
	char bkname[30];			//책이름
	char qtity[30];				//재고
	char price[30];				//가격
	struct bookinformation* ptr;	
}bkinfo;
 typedef struct Authorinformation {
	 char Lname[30];			//성
	 char Fname[30];			//이름
	 bkinfo* ptr;
 }Author;
int search(Author A[], char L[], char F[]);	//성과 이름으로 Author배열에 입력된 저자가 있는지 확인 완료
void greeting();							//환영 완료
void readDatabase(Author* inven);			//데이터 베이스 읽어들어오기 완료
int printMenu();							//메뉴 완료
void displayinventory(Author A[]);			//1번 완료
void displayAuthorsWork(Author A[]);		//2번 완료
void addBook(Author* A);					//3번 입력된 qty가 정수인지 예외 처리 완료,입력된 price가 실수인지 예외 처리 완료
void ChangePrice(Author* A);				//4번 입력된 price가 실수인지 예외 처리 완료
void ChangeQty(Author* A);					//5번 입력된 qty가 정수인지 예외 처리 완료
void totalQty(Author A[]);					//6번 완료
void CalculateTotalAmount(Author A[]);		//7번 완료 책들의 가격의 합인지 책가격*재고의 합인지 몰라서 일단 전자의 경우로 코딩
int check_int(char string[]);				//문자열이 정수인지 아닌지 확인하는 함수,정수일시 1,아닐시 0출력
int check_double(char string[]);			//문자열이 실수인지 아닌지 확인하는 함수,실수일시 1,아닐시 0출력
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

void readDatabase(Author* inven)															//처음 데이터 베이스로 입력
{
	char filename[20];																		//파일이름
	char* Cptr;																				//자른 문자열의 위치
	bkinfo* lptr;																			//bkinfo의 위치
	bkinfo* newbk;																			//bkinfo공간 생성
	char lname[30], fname[30], name[30], qty[30], much[30];				
	int i = 0;																				//Author배열의 마지막 위치를 나타냄
	int loc=0;																				//Author배열에서 이미입력된 저자의 위치를 나타냄
	char info[100];																			//입력받은 문자열
	FILE* fp=NULL;
	while (fp == NULL)
	{
		printf("Enter the name of the file:");													//파일 이름 입력
		scanf("%s", filename);
		fp = fopen(filename, "r");
		if (fp == NULL) printf("invalid file\n");
	}
	for (int j = 0; j < 20; j++)															//Author배열의 ptr을 전부 초기화
	{
		inven[j].ptr = NULL;
	}
	while (!feof(fp))																		//파일의 끝까지
	{
		Cptr=fgets(info,100,fp);															//파일의 정보를 받아와서 변수에 저장
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
		loc = search(inven, lname, fname);													//Author배열에 입력된 작가가 이미 있는지 확인
		newbk = (bkinfo*)malloc(sizeof(bkinfo));											//bkinfo동적 할당
		newbk->ptr = NULL;
		if (loc == -1)																		//Author배열에 입력되지 않은 작가라면 
		{
			strcpy(inven[i].Lname, lname);											
			strcpy(inven[i].Fname, fname);
			inven[i].ptr = newbk;
			strcpy(newbk->bkname, name);
			strcpy(newbk->qtity, qty);
			strcpy(newbk->price, much);
			i++;
		}
		else																				//Author배열에 이미 있는 작가라면
		{
			lptr = inven[loc].ptr;
			while (lptr->ptr != NULL)														//연결리스트의 가장 마지막에 새로운 bkinfo를 붙임
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
void displayinventory(Author A[]) {			//리스트 안에 있는 내역을 보여주는 함수 1번 기능
	bkinfo* Nptr = NULL;					//출력,정렬을 위한 포인터
	bkinfo* Hptr = NULL;
	Author temp;
	int i = 0,j=0;
	while (A[i].ptr != NULL)				//버블정렬을 이용하여 저자배열의 위치 바꿈
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
	i = 0;															//출력
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

void displayAuthorsWork(Author A[])												//입력된 작가의 책들을 출력
{
	int loc = 0;																//Author배열에서 입력된 작가의 인덱스
	bkinfo* Nptr;																//출력 정렬을 위한 포인터
	char Last[30], First[30];													//성,이름
	printf("Enter the author's first name:");
	scanf("%s", First);
	printf("Enter the author's last name:");
	scanf("%s", Last);
	loc = search(A, Last, First);												//입력된 작가의 이름과 성으로 Author 배열의 몇번째에 위치해 있는지 확인
	if (loc == -1)																//입력된 정보와 매칭되는 작가가 없다면
		printf("Sorry,but no books by %s, %s in the inventory\n",Last,First);		
	else																		//입력된 정보와 매칭되는 작가가 있다면
	{
		Nptr = A[loc].ptr;														//Nptr은 입력된 작가의 head bkinfo를 가리킴
		do																		//연결리스트의 끝까지 출력
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
	int check_i = 0; //정수인지 확인
	int check_d = 0; //실수인지 확인
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
	if (loc == -1)							//새로운 저자의 책
	{
		while (A[i].ptr != NULL)
		{
			i++;
		}
		strcpy(A[i].Fname, fname);
		strcpy(A[i].Lname, lname);
		A[i].ptr = newbk;
	}
	else							//기존저자의 책
	{
		Nptr = A[loc].ptr;
		while (Nptr->ptr != NULL)
		{
			if (strcmp(Nptr->bkname, bkname) == 0)					//추가하려는 책이 이미 있는경우
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
	while (check_i == 0)				//qty에 정수가 입력되는지exception handling
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
	while (check_d == 0)				//price에 실수가 입력되는지exception handling
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
	if (loc == -1)						//저자가 없는경우
	{
		printf("No such author in your database. So you cannot change the price\n");
	}
	else								//있는경우
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
		if (Nptr == NULL)														//책이 없는경우
		{
			printf("No book with the title %s by %s,%s\n", name, lname, fname);
		}
		else																	//책이 있는경우
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
	while (A[i].ptr != NULL)								//전체 책의 개수 출력
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
	while (A[i].ptr != NULL)									//전체 책의 가격 출력
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

int check_int(char string[])					//문자열이 정수가 아니면 0을 반환 
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
