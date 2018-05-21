#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
struct food
{
    int x;
    int y;
    char value;
}*food;
struct snake
{
    int x;
    int y;
    struct snake *next;
    char value;
}*head,*tail,*t;
struct f_hash
{
    int x;
    int y;
    struct f_hash *next;
};
struct f_hash *hash[10];
int f_x=10,f_y=10;
int f_f=0;
void change_direction(int a,int b,int flag);
void update_body(int c,int d);
void up();
void down();
void left();
void right();
void print();
void initialize_food();
void body_touch();
void board_init();
void init_hash();
void insert_hash(int a,int b,int key);
void del_hash(int a,int b,int key);
int search_hash(int a,int b,int key);
void search_hash1();
     char board[20][40];
     int result=0;
     int game_score=0;
//     hash[10000]={0};
void insert_hash(int a,int b,int key)
{
   struct f_hash *w=(struct f_hash *)malloc(sizeof(struct f_hash));
    w->x=a;
    w->y=b;
    w->next=NULL;
    if(hash[key]==NULL)
        hash[key]=w;
    else{
        w->next=hash[key];
        hash[key]=w;
    }

}
void del_hash(int a,int b,int key)
{
     struct f_hash *current;
      struct f_hash *previous;
      current=hash[key];
      previous=hash[key];
      current=previous->next;
      if((previous->x==a)&&(previous->y==b))
      {
        hash[key]=previous->next;
        free(previous);
      }
      else{
        while(current!=NULL)
        {
            if((current->x==a)&&(current->y==b))
            {
                previous->next=current->next;
                free(current);
                break;

            }
            current=current->next;

        }
      }

}
int search_hash(int a,int b,int key)
{

     struct f_hash *w;
     w=hash[key];
     while(w!=NULL)
     {
         if((w->x==a)&&(w->y==b))
         {
             return 1;

         }
         w=w->next;

     }
     return 0;

}
void init_hash()
{
    int i;
    for(i=0;i<10;i++)
        hash[i]=NULL;
}
    void initialize_food()
{

    food=(struct food *)malloc(sizeof(struct food));

    if(f_f==0)
    {
    f_x=(rand()%(18-1))+1;
    f_y=(rand()%(38-1))+1;
    int ab=search_hash(f_x,f_y,(f_x+f_y)%10);
    while(ab==1)
         ab=search_hash(f_x,f_y,(f_x+f_y)%10);
    f_f=1;
    game_score++;
    }
     food->x=f_x;
    food->y=f_y;
    food->value='$';
     board[food->x][food->y]=food->value;
}
void initialize()
{
    struct snake *hd=(struct snake*)malloc(sizeof(struct snake));
   hd->x=4;
   hd->y=10;
   hd->value='A';
   insert_hash(hd->x,hd->y,((hd->x)+(hd->y)%10));
   hd->next=NULL;
   head=hd;
    board[head->x][head->y]=head->value;
   struct snake *temp=(struct snake*)malloc(sizeof(struct snake));
   temp=head;
   int z=11;
   int i;
   for(i=0;i<3;i++)
   {
       struct snake *n=(struct snake*)malloc(sizeof(struct snake));
       n->x=4;
       n->y=z;
       n->value='o';
       insert_hash(n->x,n->y,((n->x)+(n->y)%10));
       n->next=NULL;
       temp->next=n;
       board[n->x][n->y]=n->value;
       temp=temp->next;
       z++;
   }
    struct snake *tl=(struct snake*)malloc(sizeof(struct snake));
    tail=tl;
    temp->next=tail;
    tail->x=4;
    tail->y=z;
    tail->value='E';
    insert_hash(tail->x,tail->y,((tail->x)+(tail->y)%10));

    tl->next=NULL;
    board[tail->x][tail->y]=tail->value;
    initialize_food();

}
void change_direction(int a,int b,int flag)
{
    int c,d;
      t=head->next;
    while(t!=NULL)
    {
        c=t->x;
        d=t->y;
        t->x=a;
        t->y=b;
        a=c;
        b=d;
        board[t->x][t->y]=t->value;
        t=t->next;
    }
     board[c][d]=' ';
     del_hash(c,d,(c+d)%10);
     if(flag==1)
        update_body(c,d);
    print();

}
void update_body(int c,int d)
{
        struct snake *temp=(struct snake *)malloc(sizeof(struct snake));
        temp->x=c;
        temp->y=d;
        board[tail->x][tail->y]='o';
        tail->value='o';
        temp->value='E';
        temp->next=NULL;
        tail->next=temp;
        tail=temp;
        board[c][d]='E';
        f_f=0;
        insert_hash(c,d,((c+d)%10));
        initialize_food();
}
void print()
{int i,j;
    system("cls");
  for(i=0;i<20;i++)
  {
    for(j=0;j<40;j++)
      {
        printf("%c ",board[i][j]);
      }
      printf("\n");
  }
}
void down()
{
    t=(struct snake*)malloc(sizeof(struct snake));
    t=head;
    int a,b,c,d;
    a=t->x;
    b=t->y;
    int flag=0;
    t->x=t->x+1;
       if(t->x>18)
    {
        t->x=1;
        a=18;
    }
    if(t->x==2)
        a=1;
    int ab=search_hash(t->x,t->y,((t->x)+(t->y))%10);
    result=ab;
    if(ab==1)
       {

        printf("GAME OVER\n");
        printf("YOUR GAME SCORE IS:%d",game_score);
         exit(0);
       }
    else
    {
        insert_hash(t->x,t->y,((t->x)+(t->y))%10);
    }
    board_init();
    board[t->x][t->y]=t->value;
    if((t->x==food->x)&&(t->y==food->y))
    {
        flag=1;

    }
  change_direction(a,b,flag);
}
void up()
{
     t=(struct snake*)malloc(sizeof(struct snake));
    t=head;
    int a,b,c,d;
    int flag=0;
    a=t->x;
    b=t->y;
    t->x=t->x-1;
       if(t->x<1)
    {
        t->x=18;
        a=1;
    }
    if(t->x==17)
        a=18;
        int ab=search_hash(t->x,t->y,((t->x)+(t->y))%10);
      result=ab;
    if(ab==1)
       {
            printf("GAME OVER\n");
        printf("YOUR GAME SCORE IS:%d",game_score);
         exit(0);
       }
    else
    {
        insert_hash(t->x,t->y,((t->x)+(t->y))%10);
    }
    board_init();
    board[t->x][t->y]=t->value;
     if((t->x==food->x)&&(t->y==food->y))
    {
        flag=1;

    }
  change_direction(a,b,flag);

}
void left()
{
     t=(struct snake*)malloc(sizeof(struct snake));
    t=head;
    int a,b,c,d;
    a=t->x;
    b=t->y;
    t->y=t->y-1;
    int flag=0;
     if(t->y<1)
    {
        t->y=38;
        b=1;
    }
    if(t->y==37)
        b=38;
    int ab=search_hash(t->x,t->y,((t->x)+(t->y))%10);
      result=ab;
    if(ab==1)
      {

       printf("GAME OVER\n");
        printf("YOUR GAME SCORE IS:%d",game_score);
         exit(0);
      }
    else
    {
        insert_hash(t->x,t->y,((t->x)+(t->y))%10);
    }
    board_init();
    board[t->x][t->y]=t->value;
     if((t->x==food->x)&&(t->y==food->y))
    {
        flag=1;

    }
  change_direction(a,b,flag);

}
void right()
{

 t=(struct snake*)malloc(sizeof(struct snake));
    t=head;
    int a,b,c,d;
    a=t->x;
    b=t->y;
    int flag;
    t->y=t->y+1;
     if(t->y>38)
    {
        t->y=2;
        b=38;
    }
    if(t->y==3)
        b=2;
    int ab=search_hash(t->x,t->y,((t->x)+(t->y))%10);
      result=ab;
    if(ab==1)
       {
            printf("GAME OVER\n");
        printf("YOUR GAME SCORE IS:%d",game_score);
         exit(0);
       }
    else
    {
        insert_hash(t->x,t->y,((t->x)+(t->y))%10);
    }
    board_init();
    board[t->x][t->y]=t->value;
     if((t->x==food->x)&&(t->y==food->y))
    {
        flag=1;

    }
  change_direction(a,b,flag);

}
void get_input()
{
    char input;
   l: input=getche();
   if(input!='d' && input!='u' && input!='l' && input!='r')
   {
       printf("PLEASE ENTER A VALID INPUT");
       goto l;
   }
   while(input=='d'||input=='u'||input=='l'||input=='r')
   {
   if(input=='d')
   {
        if(((head->x+1)==(head->next)->x))

   {
       while(!_kbhit())
        up();
   }
        while(!_kbhit())
        down();
        }
   else if(input=='u')
   {
      if(((head->x-1)==(head->next)->x))

   {
       while(!_kbhit())
        down();
   }     while(!_kbhit())
        up();
        }
    else if(input=='l')
      {
      if(((head->y-1)==(head->next)->y))

   {
      while(!_kbhit())
        right();
   }     while(!_kbhit())
        left();
        }
     else if(input=='r')
     {
      if(((head->y+1)==(head->next)->y))

   {
      while(!_kbhit())
        left();

   }     while(!_kbhit())
        right();
        }
    input=getche();
     if(input!='d' && input!='u' && input!='l' && input!='r')
   {
       printf("PLEASE ENTER A VALID INPUT");
       goto l;
   }
   }
}
void board_init()
{
     int i,j;
    for(i=0;i<20;i++)
    {

        for(j=0;j<40;j++)
        {
            if(i==0 || i==19)
            {
                board[i][j]=' ';

            }
            else if(j==0 || j==39)
            {
                board[i][j]=' ';

            }
            else
                board[i][j]=' ';
        }
    }
        initialize_food();
}
void search_hash1()
{

      struct snake *w;
     w=head;
      FILE *fp;
     fp=fopen("file_handling.txt","a+");
     char arr[1000]="";
     int i=0;
     while(w!=NULL)
     {
         arr[i]=w->x;
         i++;
         arr[i]=w->y;
         i++;
         arr[i]=w->value;
         i++;
         w=w->next;

     }
}
void main()
{
    board_init();
    initialize();
    print();
    get_input();
    search_hash1();
}
