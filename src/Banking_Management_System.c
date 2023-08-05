#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct node
{
    int curr_amt, sav_amt, fd_amt, rec_amt, id;
    char name[10], pass[10];
    struct node *prev;
    struct node *next;
};

struct loan
{
    int id;
    float ratio;
    int amt;
};

struct transfer
{
    int amount, id1, id2;
    struct transfer *prev;
    struct transfer *next;
};

struct node *head = NULL;
struct node *tail;

struct transfer *trans_queue_t;
struct transfer *trans_queue_r;

void insert(int id, char name[], char pass[])
{
    struct node *new;
    new = (struct node *)malloc(sizeof(struct node));
    new->id = id;
    new->curr_amt = 0;
    new->sav_amt = 0;
    new->fd_amt = 0;
    new->rec_amt = 0;
    strcpy(new->name, name);
    strcpy(new->pass, pass);

    if (head == NULL)
    {
        head = new;
        new->prev = NULL;
        new->next = NULL;
    }
    if (new->id < head->id)
    {
        head->prev = new;
        new->next = head;
        new->prev = NULL;
        head = new;
    }
    else
    {
        struct node *temp = head;
        while (temp->next != NULL)
        {
            if (temp->id > id)
            {
                (temp->prev)->next = new;
                new->next = temp;
                new->prev = temp->prev;
                temp->prev = new;
                break;
            }
            temp = temp->next;
        }
        if (temp->next == NULL)
        {
            if (temp->id > id)
            {
                (temp->prev)->next = new;
                new->next = temp;
                new->prev = temp->prev;
                temp->prev = new;
            }
            else
            {
                temp->next = new;
                new->prev = temp;
                new->next = NULL;
            }
        }
    }
}

void withdraw(int a, int amt)
{
    int n;
    int flag = 0;
    struct node *temp = head;
    printf("\n1:Savings Account\n2:Current Account\n3:Recurring Account\n4:Fixed Deposit\n");
    printf("Please enter the type of account or bank deposit you want to withdraw from : ");
    scanf("%d", &n);
    switch (n)
    {
    case 1:
    {
        while (temp != NULL)
        {
            if (temp->id == a)
            {
                temp->sav_amt = temp->sav_amt - amt;
                if ((temp->sav_amt) < 0)
                {
                    printf("\nInsufficient value!!!\n");
                    temp->sav_amt = temp->sav_amt + amt;
                    break;
                }
                else
                {
                    printf("\nAmount has been withdrawn!!!\n");
                    printf("Saving account has Rs.%d\n", temp->sav_amt);
                    break;
                }
            }
            temp = temp->next;
        }

        break;
    }
    case 2:
    {
        while (temp != NULL)
        {
            if (temp->id == a)
            {
                temp->curr_amt = temp->curr_amt - amt;
                if ((temp->curr_amt) < 0)
                {
                    printf("\nInsufficient value!!!\n");
                    temp->curr_amt = temp->curr_amt + amt;
                    break;
                }
                else
                {
                    printf("\nAmount has been withdrawn!!!\n");
                    printf("Current account has Rs.%d\n", temp->curr_amt);
                    break;
                }
            }
            temp = temp->next;
        }

        break;
    }
    case 3:
    {
        while (temp != NULL)
        {
            if (temp->id == a)
            {
                temp->rec_amt = temp->rec_amt - amt;
                if ((temp->rec_amt) < 0)
                {
                    printf("\nInsufficient value!!!\n");
                    temp->rec_amt = temp->rec_amt + amt;
                    break;
                }
                else
                {
                    printf("\nAmount has been withdrawn!!!\n");
                    printf("Reccuring account has Rs.%d\n", temp->rec_amt);
                    break;
                }
            }
            temp = temp->next;
        }

        break;
    }
    case 4:
    {
        while (temp != NULL)
        {
            if (temp->id == a)
            {
                temp->fd_amt = temp->fd_amt - amt;
                if ((temp->fd_amt) < 0)
                {
                    printf("\nInsufficient value!!!\n");
                    temp->fd_amt = temp->fd_amt + amt;
                    break;
                }
                else
                {
                    printf("\nAmount has been withdrawn!!!\n");
                    printf("Fixed Deposit account has Rs.%d\n", temp->fd_amt);
                    break;
                }
            }
            temp = temp->next;
        }

        break;
    }
    default:
    {
        printf("Please enter valid input!!!\n");
        break;
    }
    }
}
void deposit(int id, int amt)
{
    int n;
    struct node *temp = head;
    printf("1:Savings Account\n2:Current Account\n3:Recurring Account\n4:Fixed Deposit\n");
    printf("Please enter the type of account or bank deposit you want to deposit into : ");

    scanf("%d", &n);
    if (n == 1)
    {
        while (temp != NULL)
        {
            if (temp->id == id)
            {
                temp->sav_amt += amt;
                printf("\nSuccessfully deposited\n");
                printf("Saving account has Rs.%d\n", temp->sav_amt);
                break;
            }
            temp = temp->next;
        }
    }
    else if (n == 2)
    {
        while (temp != NULL)
        {
            if (temp->id == id)
            {
                temp->curr_amt += amt;
                printf("\nSuccessfully deposited\n");
                printf("Current account has Rs.%d\n", temp->curr_amt);
                break;
            }
            temp = temp->next;
        }
    }
    else if (n == 3)
    {
        while (temp != NULL)
        {
            if (temp->id == id)
            {
                temp->rec_amt += amt;
                printf("\nSuccessfully deposited\n");
                printf("Recurring account has Rs.%d\n", temp->rec_amt);
                break;
            }
            temp = temp->next;
        }
    }
    else if (n == 4)
    {
        while (temp != NULL)
        {
            if (temp->id == id)
            {
                temp->fd_amt += amt;
                printf("\nSuccessfully deposited\n");
                printf("Fixed Deposit account has Rs.%d\n", temp->fd_amt);
                break;
            }
            temp = temp->next;
        }
    }
    else
    {
        printf("Please enter valid input!!!\n");
    }
}

void display()
{
    struct node *temp = head;
    while (temp != NULL)
    {
        printf("%d    %s\n", temp->id, temp->name);
        temp = temp->next;
    }
}

void display_all(int id)
{
    struct node *temp = head;
    while (temp != NULL)
    {
        if (temp->id == id)
        {
            printf("\nSavings account has Rs.%d\n", temp->sav_amt);
            printf("Current account has Rs.%d\n", temp->curr_amt);
            printf("Reccuring account has Rs.%d\n", temp->rec_amt);
            printf("Fixed Deposit account has Rs.%d\n", temp->fd_amt);
        }
        temp = temp->next;
    }
}

struct node *search(int id, char *pass)
{
    struct node *temp = head;
    while (temp != NULL)
    {
        if (id == temp->id && (strcmp(pass, temp->pass) == 0))
            return temp;
        temp = temp->next;
    }
    return NULL;
}

struct node *search_user(int id)
{
    struct node *temp = head;
    while (temp != NULL)
    {
        if (id == temp->id)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

void transfer_enqueue(int id1, int id2, int amt)
{
    struct transfer *new;
    new = (struct transfer *)malloc(sizeof(struct transfer));
    new->amount = amt;
    new->id1 = id1;
    new->id2 = id2;
    if (trans_queue_r == NULL)
    {
        trans_queue_t = new;
        trans_queue_r = new;
        new->next = NULL;
        new->prev = NULL;
    }
    else
    {
        trans_queue_r->next = new;
        new->prev = trans_queue_r;
        trans_queue_r = new;
        new->next = NULL;
    }
}

void transfer_dequeue()
{
    if (trans_queue_t == NULL)
    {
        printf("\nALL TRANSFERS COMPLETED\n");
        return;
    }
    struct node *temp = search_user(trans_queue_t->id1);
    if (temp->curr_amt < trans_queue_t->amount)
    {
        printf("\nTransfer failed due to insufficent balance : \n");
        printf("Amount in %d : %d \n", temp->id, temp->id);
        printf("Transfer request made : %d\n", trans_queue_t->amount);
        return;
    }
    printf("\nTransfer successful\n");
    printf("Rs.%d were transfered from %d to %d\n", trans_queue_t->amount, trans_queue_t->id1, trans_queue_t->id2);
    temp = search_user(trans_queue_t->id2);
    temp->curr_amt += trans_queue_t->amount;
    temp = search_user(trans_queue_t->id1);
    temp->curr_amt -= trans_queue_t->amount;
    if (trans_queue_r == trans_queue_t)
    {
        trans_queue_t = NULL;
        trans_queue_r = NULL;
        return;
    }
    else
    {
        trans_queue_t = trans_queue_t->next;
        trans_queue_t->prev = NULL;
        return;
    }
}

void min_heap(struct loan *a, int n, int i)
{
    int small = i;
    int l = (2 * i);
    int r = (2 * i) + 1;

    if (l <= n && (a[l].ratio < a[small].ratio))
    {
        small = l;
    }
    if (r <= n && (a[r].ratio < a[small].ratio))
    {
        small = r;
    }
    if (small != i)
    {
        int id = a[i].id;
        a[i].id = a[small].id;
        a[small].id = id;
        int ratio = a[i].ratio;
        a[i].ratio = a[small].ratio;
        a[small].ratio = ratio;
        int amt = a[i].amt;
        a[i].amt = a[small].amt;
        a[small].amt = amt;

        min_heap(a, n, small);
    }
}

void loan(struct loan *ln, int i, int id, int amt)
{
    float l_amt = 0;
    ln[i].amt = amt;
    ln[i].id = id;
    printf("\nEnter amount of loan:");
    scanf("%f", &l_amt);
    float bal = (float)ln[i].amt;
    float r = l_amt / bal;
    ln[i].ratio = r;
    int n = i;

    for (int j = (n / 2); j > 0; j--)
    {
        min_heap(ln, n, j);
    }
}

void loan_allote(struct loan *ln, int n)
{

    int id = ln[1].id;
    ln[1].id = ln[n].id;
    ln[n].id = id;
    float ratio = ln[1].ratio;
    ln[1].ratio = ln[n].ratio;
    ln[n].ratio = ratio;
    int amt = ln[1].amt;
    ln[1].amt = ln[n].amt;
    ln[n].amt = amt;
    n = n - 1;
    for (int i = (n / 2); i > 0; i--)
    {
        min_heap(ln, n, i);
    }
    ln = (struct loan *)realloc(ln, (n - 1) * (sizeof(struct loan)));
}

struct loan *pro;
int loan_size = 1;

void banker()
{

    while (1)
    {
        int n;
        printf("1.Transfer  2.Loan Request  3.Exit\n");
        printf("Enter choice : ");
        scanf("%d", &n);
        if (n == 1)
        {
            transfer_dequeue();
        }
        else if (n == 2)
        {
            int n = loan_size - 1;
            if (n > 0)
            {
                printf("Id : %d\n Amount : %d  \nratio : %f\n", pro[1].id, pro[1].amt, pro[1].ratio);
                loan_allote(pro, n);
                n--;
                loan_size--;
            }
            else
            {
                printf("\nNO REQUESTS PENDING\n");
            }
        }

        else if (n == 3)
        {
            break;
        }
        else
        {
            printf("\nINVALID\n");
        }
    }
}

void user(struct node *temp)
{
    int n;
    while (1)
    {
        printf("\n1.Deposit  2.Withdraw  3.Transfer amount  4.Request Loan  5.Display  6.Exit\n");
        printf("Enter choice : ");
        scanf("%d", &n);
        if (n == 1)
        {
            int amt;
            printf("Amount to be deposited : ");
            scanf("%d", &amt);
            deposit(temp->id, amt);
        }
        else if (n == 2)
        {
            int amt;
            printf("Amount to be withdrawn : ");
            scanf("%d", &amt);
            withdraw(temp->id, amt);
        }
        else if (n == 3)
        {
            int amt, t_id;
            printf("Enter id to be transfered to : ");
            scanf("%d", &t_id);
            struct node *temp_r = search_user(t_id);
            if (temp_r == NULL)
            {
                printf("\nID doesn't exist\n");
                continue;
            }
            printf("Amount to be transfered : ");
            scanf("%d", &amt);
            if (amt > temp->curr_amt)
            {
                printf("\nINSUFFICIENT BALANCE\n");
                continue;
            }
            transfer_enqueue(temp->id, t_id, amt);
        }
        else if (n == 4)
        {
            pro = (struct loan *)realloc(pro, (loan_size + 1) * sizeof(struct loan));
            loan(pro, loan_size, temp->id, temp->curr_amt);
            loan_size++;
        }
        else if (n == 5)
        {
            display_all(temp->id);
        }
        else if (n == 6)
        {
            break;
        }
        else
        {
            printf("\nINVALID INPUT\n");
        }
    }
}

int main()
{
    int n, id;
    char pass[20], name[20];
    insert(10, "aarnav", "1234");
    insert(11, "harsh", "6666");
    insert(12, "ved", "1234");
    insert(13, "yash", "6666");
    insert(14, "aditya", "1234");
    insert(15, "chinmay", "6666");
    insert(16, "abdullah", "1234");
    insert(17, "yuvraj", "6666");
    insert(18, "jenil", "1234");
    insert(19, "yogi", "6666");
    insert(20, "fenil", "1234");
    pro = (struct loan *)malloc(sizeof(struct loan));
    while (1)
    {
        printf("\n1.Existing User  2.New User  3.Banker  4.Display available ids 5.exit\n");
        printf("Enter option : ");
        scanf("%d", &n);
        if (n == 1)
        {
            printf("Enter id : ");
            scanf("%d", &id);
            printf("Enter pass : ");
            scanf("%s", pass);
            struct node *temp = search(id, pass);
            if (temp != NULL)
            {
                user(temp);
            }
            else
            {
                printf("\nINVALID CREDENTIALS\n");
            }
        }
        else if (n == 2)
        {
            printf("Enter id : ");
            scanf("%d", &id);
            printf("Enter name: ");
            scanf("%s", name);
            printf("Enter pass : ");
            scanf("%s", pass);
            struct node *temp = search_user(id);
            if (temp != NULL)
            {
                printf("User already exists!!!\n");
            }
            else
            {
                insert(id, name, pass);
            }
        }
        else if (n == 3)
        {
            banker();
        }
        else if (n == 4)
        {
            display();
        }
        else if (n == 5)
        {
            break;
        }
        else
        {
            printf("\nINVALID INPUT\n");
        }
    }
}
