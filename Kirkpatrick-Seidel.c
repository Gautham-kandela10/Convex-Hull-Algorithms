#include <stdio.h>
#include <math.h>
#include <stdlib.h>

struct Point{

    float x,y;

};

    struct Point* pumin;
    struct Point* plmin;
    struct Point* pumax;
    struct Point* plmax;


struct node{

    struct node* next;
    struct node* prev;
    float x,y;
};

float PI = 3.14;

int sides=4;


struct node* concatenate(struct node* left_bridge,struct node* upper_bridge,struct node* right_bridge)
{
    struct node* temp1=left_bridge->prev;
    struct node* temp2=upper_bridge->prev;
    struct node* temp3=right_bridge->prev;
    temp1->next=upper_bridge;
    upper_bridge->prev=temp1;
    temp2->next=right_bridge;
    right_bridge->prev=temp2;
    temp3->next=left_bridge;
    left_bridge->prev=temp3;
    return left_bridge;
}


struct node* create(float x,float y)
{
    struct node* new_node= (struct node*) malloc (sizeof(struct node));
    new_node->x=x;
    new_node->y=y;
    new_node->next=new_node;
    new_node->prev=new_node;
    return new_node;
}

struct node* concatenate2(struct node* p1, struct node* p2)
{
    struct node* temp1=p1->prev;
    struct node* temp2=p2->prev;
    p1->prev=temp2;
    temp1->next=p2;
    p2->prev=temp1;
    temp2->next=p1;
    return p1;
}
void traverse(struct node* p)
{

    struct node* temp = p;
    printf("%f %f -1 ", temp->x,temp->y);
    int i=2;
    temp=temp->next;
    while(1)
    {
        printf("%f %f -%d", temp->x,temp->y,i);
        i++;
        if(temp->x==p->x && temp->y == p->y)
        {
            break;
        }
    }
    return;
}
struct node* concatenatehulls(struct node* uhull, struct node* lhull)
{
    struct node* pointer = uhull;
    struct node* tail;
    struct node* head = (struct node*) malloc(sizeof(struct node));
    head->next=head;
    head->prev=head;
    head->x=uhull->x;
    head->y=uhull->y;
    tail=head;
    while(1)
    {
        pointer=pointer->next;
        if(pointer==uhull)
        {
            break;
        }
        struct node* new_node = (struct node*) malloc(sizeof(struct node));
        tail->next=new_node;
        new_node->x = pointer->x;
        new_node->y=pointer->y;
        new_node->next=head;
        new_node->prev=tail;
        head->prev=new_node;
        tail=tail->next;
    }

    pointer=lhull;
    pointer=pointer->prev;
   if(plmax==pumax)
   {
       pointer=pointer->prev;
   }
   while(1)
    {
        if(pointer==lhull)
        {
            break;
        }
        struct node* new_node = (struct node*) malloc(sizeof(struct node));
        new_node->x = pointer->x;
        new_node->y=pointer->y;
        new_node->next=head;
        new_node->prev=tail;
        head->prev=new_node;
        tail->next=new_node;
        tail=tail->next;
        pointer=pointer->prev;

    }
    if(plmin!=pumin)
    {
        printf("happening\n");
        struct node* new_node = (struct node*) malloc(sizeof(struct node));
        new_node->x=pointer->x;
        new_node->y=pointer->y;
        new_node->next=head;
        new_node->prev=tail;
        head->prev=new_node;
        tail->next=new_node;
    }
    return head;
}


int partitions(int low,int high,struct Point input[])
{
    struct Point temp;
    int p=low,r=high,x=input[r].x,i=p-1;
    for(int j=p;j<=r-1;j++)
    {
        if (input[j].x<=x)
        {

            i=i+1;
            temp=input[j];
            input[j]=input[i];
            input[i]=temp;

        }
    }
    temp=input[i+1];
    input[i+1]=input[r];
    input[r]=temp;
    return i+1;
}
float median(struct Point input[],int left, int right, int kth)
{
    for(;;)
    {
        int pivotIndex=partitions(left,right,input);          //Select the Pivot Between Left and Right
        int len=pivotIndex-left+1;

        if(kth==len)
            return input[pivotIndex].x;

        else if(kth<len)
            right=pivotIndex-1;

        else
        {
            kth=kth-len;
            left=pivotIndex+1;
        }
    }
}

int partitions1(int low,int high,float input[])
{
    float temp;
    int p=low,r=high,x=input[r],i=p-1;
    for(int j=p;j<=r-1;j++)
    {
        if (input[j]<=x)
        {

            i=i+1;
            temp=input[j];
            input[j]=input[i];
            input[i]=temp;

        }
    }
    temp=input[i+1];
    input[i+1]=input[r];
    input[r]=temp;
    return i+1;
}
float median1(float input[],int left, int right, int kth)
{
    for(;;)
    {
        int pivotIndex=partitions(left,right,input);          //Select the Pivot Between Left and Right
        int len=pivotIndex-left+1;

        if(kth==len)
            return input[pivotIndex];

        else if(kth<len)
            right=pivotIndex-1;

        else
        {
            kth=kth-len;
            left=pivotIndex+1;
        }
    }
}

struct node* UpperBridge(struct Point input[],float a,int size)
{
    int i;
    struct Point candidates[size+1];
    int l2=0;

    if(size==2)
    {
        struct node* least = create(input[1].x,input[1].y);
        struct node* highest = create(input[2].x,input[2].y);
        struct node* list = concatenate2(least,highest);
        struct node* temp = list;
        return list;
    }

        if(size==3)
        {
        int i;
        int most_left_x=input[1].x;
        int most_left_y=input[1].y;
        int l=1;
        int most_right_x=most_left_x;
        int most_right_y=most_left_y;
        for(i=2;i<=3;i++)
        {
            if(input[i].x<most_left_x)
            {
                l=i;
                most_left_x=input[i].x;
                most_left_y=input[i].y;
            }
            else if(input[i].x==most_left_x)
            {
                if(input[i].y < most_left_y)
                {
                    l=i;
                    most_left_x=input[i].x;
                    most_left_y=input[i].y;
                }
            }
        }
        int n=1;
        for(i=2;i<=3;i++)
        {
            if(input[i].x>most_right_x)
            {
                n=i;
                most_right_x=input[i].x;
                most_right_y=input[i].y;
            }
            else if(input[i].x==most_right_x)
            {
                if(input[i].y > most_right_y)
                {
                    n=i;
                    most_right_x=input[i].x;
                    most_right_y=input[i].y;
                }
            }
        }



            int m = 6-n-l;
            float new_y=input[m].y;
            float new_x=input[m].x;
            float highest_y=input[n].y;
            float highest_x=input[n].x;
            float least_y=input[l].y;
            float least_x=input[l].x;
            struct node* least;
            struct node* newest;
            if((new_y-least_y)/(new_x-least_x)!=(highest_y-least_y)/(highest_x-least_x))
            {
            if(new_y > least_y && new_y <=a)
            {
                least = create(least_x,least_y);
                newest = create(new_x,new_y);
            }
            else if(new_y > highest_y && new_y>a)
            {
                least = create(least_x,least_y);
                newest = create(new_x,new_y);
            }
            else
            {
                least = create(least_x,least_y);
                newest = create(highest_x,highest_y);
            }
            struct node* list = concatenate2(least,newest);
            return list;
            }
            else
            {
                least = create(least_x,least_y);
                newest = create(new_x,new_y);
                struct node* highest = create(highest_x,highest_y);
                struct node* list = concatenate(least,newest,highest);
                struct node* temp = list;
                return list;
            }


    }
    if(size%2==1)
    {
        candidates[1]=input[size];
        size--;
        l2++;
    }
    float slopes[size];
    float slopes1[size];
    struct Point temp;
    int m=0;
    int n=0;
    i=1;
    while(1)
    {
        if(input[i].x>input[i+1].x)
        {
            temp=input[i+1];
            input[i+1]=input[i];
            input[i]=temp;
        }
        if(input[i].x == input[i+1].x && input[i].y>input[i+1].y)
        {
            temp=input[i+1];
            input[i+1]=input[i];
            input[i]=temp;
        }
        if(input[i].x!=input[i+1].x)
        {
            m++;
            n++;
            slopes[m]=(input[i+1].y-input[i].y);
            slopes[m]=slopes[m]/(input[i+1].x-input[i].x);
            slopes1[n]=slopes[m];
            i=i+2;
        }
        else if(input[i].x==input[i+1].x)
        {
            n++;
            slopes1[n]=PI;
            l2++;
            candidates[l2]=input[i+1];
            i=i+2;
        }

        if(i>size)
        {
            break;
        }
    }
    float answer1,answer2;
    float med_slope;
    int k;
    if(m>=3)
    {
        if((m)%2!=0)
        {
            k=(m+1)/2;
            med_slope = median1(slopes,1,m,k);
        }
        else
        {
            k = (m)/2;
            answer1 = median1(slopes,1,m,k);
            k++;
            answer2 = median1(slopes,1,m,k);
            med_slope = answer1 + answer2;
            med_slope = med_slope/2;

        }
    }
    else
    {
        med_slope = slopes[1]+slopes[2];
        med_slope = med_slope/2;
    }

    struct Point small[size];
    struct Point equal[size];
    struct Point large[size];

    int l1=0;
    int m1=0;
    int n1=0;
        for(i=1;i<=n;i++)
    {
        if(slopes1[i]<med_slope && slopes[i]!=PI)
        {
            l1++;
            small[l1]=input[2*i-1];

            l1++;
            small[l1]=input[2*i];

        }
        else if(slopes1[i]==med_slope && slopes[i]!=PI)
        {
            m1++;
            equal[m1]=input[2*i-1];

            m1++;
            equal[m1]=input[2*i];


        }
        else if(slopes1[i]>med_slope && slopes[i]!=PI)
        {
            n1++;
            large[n1]=input[2*i-1];

            n1++;
            large[n1]=input[2*i];
        }
    }

    struct Point max[size];
    float max_intercept=(input[1].y-(med_slope)*input[1].x);
    float check;
    for(i=2;i<=size;i++)
    {
        check = input[i].y-(med_slope)*input[i].x;
        if(check > max_intercept)
        {
            max_intercept=check;

        }
    }
    int count=1;
    for(i=1;i<=size;i++)
    {
        check = input[i].y-(med_slope)*input[i].x;
        if(check==max_intercept)
        {
            max[count]=input[i];
            count++;
        }
    }
    float min = max[1].x;
    int least=1;
    int highest=1;
    for(i=2;i<count;i++)
    {
        if(min > max[i].x)
        {
            min=max[i].x;
            least=i;
        }
    }
    float most = max[1].x;
    for(i=2;i<count;i++)
    {
        if(most < max[i].x)
        {
            most=max[i].x;
            highest=i;
        }
    }
    if(most > a && min <= a )
    {
        float least_x=max[least].x;
        float least_y=max[least].y;
        float highest_x=max[highest].x;
        float highest_y=max[highest].y;
        if(size%2!=0)
        {
            if(candidates[1].x==max[least].x && candidates[1].y>max[least].y)
            {
                least_x=max[least].x;
                least_y=max[least].y;
            }
            else if(candidates[1].x==max[highest].x && candidates[1].y > max[highest].y)
            {
                highest_y=max[highest].x;
                highest_x=max[highest].y;
            }
            else if(max[least].x<candidates[1].x && candidates[1].x<max[highest].x)
            {
                float new_x=candidates[1].x;
                float new_y=candidates[1].y;
                if((new_y-least_y)/(new_x-least_x) >= (highest_y-least_y)/(highest_x-least_x))
                {
                struct node* least = create(least_x,least_y);
                struct node* highest = create(highest_x,highest_y);
                struct node* newest = create(new_x,new_y);
                struct node* list = concatenate(least,newest,highest);
                return list;
                }
            }
        }
        struct node* least = create(least_x,least_y);
        struct node* highest = create(highest_x,highest_y);
        struct node* list = concatenate2(least,highest);
        struct node* temp = list;
        return list;
    }

    else if(most <= a)
    {
        m=2;
        int l=2;
        if(n1>0 || m1>0)
        {
            while(1)
            {
                if(m<=n1)
                {
                    l2++;
                    candidates[l2]=large[m];
                    m+=2;
                }
                if(l<=m1)
                {
                    l2++;
                    candidates[l2]=equal[l];
                    l+=2;
                }
                if(l>m1 && m>n1)
                {
                    break;
                }
            }
        }
        m=0;
        if(l1>0)
        {
            while(1)
            {
                l2++;
                m++;
                candidates[l2]=small[m];
                l2++;
                m++;
                candidates[l2]=small[m];
                if(m==l1){break;}
            }
        }

    }
    else if(min > a)
    {
        m=1;
        int l=1;
        if(l1>0 || m1>0)
        {
            while(1)
            {
                if(m<l1)
                {
                    l2++;
                    candidates[l2]=small[m];
                    m+=2;
                }
                if(l<m1)
                {
                    l2++;
                    candidates[l2]=equal[l];
                    l+=2;
                }
                if(l>m1 && m>l1)
                {
                    break;
                }
            }
        }
        m=0;
        if(n1>0)
        {
            while(1)
            {
                m++;
                l2++;
                candidates[l2]=large[m];
                m++;
                l2++;
                candidates[l2]=large[m];
                if(m==n1)
                {
                    break;
                }
            }
        }
    }

    return UpperBridge(candidates,a,l2);
}
    int rightupper=0;
    int rightlower=0;
    int leftlower=0;
    int leftupper=0;
    int upmax;
    int upmin;
    int lowmax;
    int lowmin;
struct Point* findrightupper(struct Point input[],struct node* temp,int size)
{
    struct node* pointer = temp;
    float first_x=pointer->x;
    float first_y=pointer->y;
    pointer=pointer->prev;
    float second_x=pointer->x;
    float second_y=pointer->y;
    float third_x=pumax->x;
    float third_y=pumax->y;
    float fourth_x=pumin->x;
    float fourth_y=pumin->y;
    float area = 0.5 * (first_x*second_y+second_x*third_y+third_x*fourth_y+fourth_x*first_y-second_x*first_y-third_x*second_y-fourth_x*third_y-first_x*fourth_y);
    if(area < 0){area*=-1;}
    float inner_area_1;
    float inner_area_2;
    float inner_area_3;
    float inner_area_4;
    struct Point inputs_new[size];
    int m=0;
    int i;
    for(i=1;i<=size;i++)
    {
    inner_area_1 = 0.5 * (first_x*second_y+second_x*input[i].y+input[i].x*first_y-second_x*first_y-input[i].x*second_y-first_x*input[i].y);
    if(inner_area_1 < 0){inner_area_1*=-1;}
    inner_area_2 = 0.5 * (third_x*second_y+second_x*input[i].y+input[i].x*third_y-second_x*third_y-input[i].x*second_y-third_x*input[i].y);
    if(inner_area_2 < 0){inner_area_2*=-1;}
    inner_area_3 = 0.5 * (third_x*fourth_y+fourth_x*input[i].y+input[i].x*third_y-fourth_x*third_y-input[i].x*fourth_y-third_x*input[i].y);
    if(inner_area_3 < 0){inner_area_3*=-1;}
    inner_area_4 = 0.5 * (first_x*fourth_y+fourth_x*input[i].y+input[i].x*first_y-fourth_x*first_y-input[i].x*fourth_y-first_x*input[i].y);
    if(inner_area_4 < 0){inner_area_4*=-1;}
    float inner_area = inner_area_1 + inner_area_2+ inner_area_3+ inner_area_4;
    if(area != inner_area && input[i].x > second_x && input[i].y > fourth_y)
    {
        m++;
        inputs_new[m] = input[i];
    }
    }
    float min_x = inputs_new[1].x;
    float max_y = inputs_new[1].y;
    for(i=1;i<=m;i++)
    {
        if(min_x > inputs_new[i].x)
        {
            min_x=inputs_new[i].x;
            max_y=inputs_new[i].y;
            upmin=i;
        }
        if(min_x == inputs_new[i].x)
        {
            if(max_y < inputs_new[i].y)
            {
                max_y=inputs_new[i].y;
                upmin=i;
            }
        }
    }

    float max_x = inputs_new[1].x;
    max_y = inputs_new[1].y;
    for(i=1;i<=m;i++)
    {
        if(max_x < input[i].x)
        {
            max_x=inputs_new[i].x;
            max_y=inputs_new[i].y;
            upmax=i;
        }
        if(max_x == inputs_new[i].x)
        {
            if(max_y < inputs_new[i].y)
            {
                max_y=inputs_new[i].y;
                upmax=i;
            }
        }
    }
    rightupper=m;
    return inputs_new;

}

struct Point* findrightlower(struct Point input[],struct node* temp,int size)
{
    struct node* pointer = temp;
    float first_x=pointer->x;
    float first_y=pointer->y;
    pointer=pointer->prev;
    float second_x=pointer->x;
    float second_y=pointer->y;
    float third_x=plmax->x;
    float third_y=plmax->y;
    float fourth_x=plmin->x;
    float fourth_y=plmin->y;
    float area = 0.5 * (first_x*second_y+second_x*third_y+third_x*fourth_y+fourth_x*first_y-second_x*first_y-third_x*second_y-fourth_x*third_y-first_x*fourth_y);
    if(area < 0){area*=-1;}
    float inner_area_1;
    float inner_area_2;
    float inner_area_3;
    float inner_area_4;
    struct Point inputs_new[size];
    int m=0;
    int i;
    for(i=1;i<=size;i++)
    {
    inner_area_1 = 0.5 * (first_x*second_y+second_x*input[i].y+input[i].x*first_y-second_x*first_y-input[i].x*second_y-first_x*input[i].y);
    if(inner_area_1 < 0){inner_area_1*=-1;}
    inner_area_2 = 0.5 * (third_x*second_y+second_x*input[i].y+input[i].x*third_y-second_x*third_y-input[i].x*second_y-third_x*input[i].y);
    if(inner_area_2 < 0){inner_area_2*=-1;}
    inner_area_3 = 0.5 * (third_x*fourth_y+fourth_x*input[i].y+input[i].x*third_y-fourth_x*third_y-input[i].x*fourth_y-third_x*input[i].y);
    if(inner_area_3 < 0){inner_area_3*=-1;}
    inner_area_4 = 0.5 * (first_x*fourth_y+fourth_x*input[i].y+input[i].x*first_y-fourth_x*first_y-input[i].x*fourth_y-first_x*input[i].y);
    if(inner_area_4 < 0){inner_area_4*=-1;}
    float inner_area = inner_area_1 + inner_area_2+ inner_area_3+ inner_area_4;
    if(area != (inner_area) && input[i].x > second_x && input[i].y < fourth_y)
    {m++;
        inputs_new[m] = input[i];

    }
    }
    float min = inputs_new[1].x;
    for(i=1;i<m;i++)
    {
        if(min > input[i].x)
        {
            min=input[i].x;
            lowmin=i;
        }
    }
    float max = inputs_new[1].x;
    for(i=1;i<m;i++)
    {
        if(max < input[i].x)
        {
            max=input[i].x;
            lowmax=i;
        }
    }
    rightlower = (m);
    return inputs_new;
}



struct Point* findleftupper(struct Point input[],struct node* temp,int size)
{
struct node* pointer = temp;
float first_x = pointer->x;
float first_y=pointer->y;
pointer=pointer->prev;
float second_x=pointer->x;
float second_y=pointer->y;
float third_x=plmax->x;
float third_y=plmax->y;
float fourth_x=plmin->x;
float fourth_y=plmin->y;
float area = 0.5 * (first_x*second_y+second_x*third_y+third_x*fourth_y+fourth_x*first_y-second_x*first_y-third_x*second_y-fourth_x*third_y-first_x*fourth_y);
if(area < 0){area*=-1;}
float inner_area_1;
float inner_area_2;
float inner_area_3;
float inner_area_4;
int i;
struct Point inputs_new [size];
int m=0;
for(i=1;i<=size;i++)
{
    inner_area_1 = 0.5 * (first_x*second_y+second_x*input[i].y+input[i].x*first_y-second_x*first_y-input[i].x*second_y-first_x*input[i].y);
    if(inner_area_1 < 0){inner_area_1*=-1;}
    inner_area_2 = 0.5 * (third_x*second_y+second_x*input[i].y+input[i].x*third_y-second_x*third_y-input[i].x*second_y-third_x*input[i].y);
    if(inner_area_2 < 0){inner_area_2*=-1;}
    inner_area_3 = 0.5 * (third_x*fourth_y+fourth_x*input[i].y+input[i].x*third_y-fourth_x*third_y-input[i].x*fourth_y-third_x*input[i].y);
    if(inner_area_3 < 0){inner_area_3*=-1;}
    inner_area_4 = 0.5 * (first_x*fourth_y+fourth_x*input[i].y+input[i].x*first_y-fourth_x*first_y-input[i].x*fourth_y-first_x*input[i].y);
    if(inner_area_4 < 0){inner_area_4*=-1;}
    float inner_area = inner_area_1 + inner_area_2+ inner_area_3+ inner_area_4;
    if(area != inner_area && input[i].x < first_x && input[i].y > fourth_y)
    {
        m++;
        inputs_new[m] = input[i];
    }
}
    float min_x = inputs_new[1].x;
    float max_y = inputs_new[1].y;
    for(i=1;i<=m;i++)
    {
        if(min_x > inputs_new[i].x)
        {
            min_x=inputs_new[i].x;
            max_y=inputs_new[i].y;
            upmin=i;
        }
        if(min_x == inputs_new[i].x)
        {
            if(max_y < inputs_new[i].y)
            {
                max_y=inputs_new[i].y;
                upmin=i;
            }
        }
    }

    float max_x = inputs_new[1].x;
    max_y = inputs_new[1].y;
    for(i=1;i<=m;i++)
    {
        if(max_x < input[i].x)
        {
            max_x=inputs_new[i].x;
            max_y=inputs_new[i].y;
            upmax=i;
        }
        if(max_x == inputs_new[i].x)
        {
            if(max_y < inputs_new[i].y)
            {
                max_y=inputs_new[i].y;
                upmax=i;
            }
        }
    }
    leftlower=m;
    return inputs_new;

}
struct Point* findleftlower(struct Point input[],struct node* temp,int size)
{
struct node* pointer = temp;
float first_x = pointer->x;
float first_y=pointer->y;
pointer=pointer->prev;
float second_x=pointer->x;
float second_y=pointer->y;
float third_x=plmax->x;
float third_y=plmax->y;
float fourth_x=plmin->x;
float fourth_y=plmin->y;
float area = 0.5 * (first_x*second_y+second_x*third_y+third_x*fourth_y+fourth_x*first_y-second_x*first_y-third_x*second_y-fourth_x*third_y-first_x*fourth_y);
if(area < 0){area*=-1;}
float inner_area_1;
float inner_area_2;
float inner_area_3;
float inner_area_4;
int i;
struct Point inputs_new [size];
int m=0;
for(i=1;i<=size;i++)
{
    inner_area_1 = 0.5 * (first_x*second_y+second_x*input[i].y+input[i].x*first_y-second_x*first_y-input[i].x*second_y-first_x*input[i].y);
    if(inner_area_1 < 0){inner_area_1*=-1;}
    inner_area_2 = 0.5 * (third_x*second_y+second_x*input[i].y+input[i].x*third_y-second_x*third_y-input[i].x*second_y-third_x*input[i].y);
    if(inner_area_2 < 0){inner_area_2*=-1;}
    inner_area_3 = 0.5 * (third_x*fourth_y+fourth_x*input[i].y+input[i].x*third_y-fourth_x*third_y-input[i].x*fourth_y-third_x*input[i].y);
    if(inner_area_3 < 0){inner_area_3*=-1;}
    inner_area_4 = 0.5 * (first_x*fourth_y+fourth_x*input[i].y+input[i].x*first_y-fourth_x*first_y-input[i].x*fourth_y-first_x*input[i].y);
    if(inner_area_4 < 0){inner_area_4*=-1;}
    float inner_area = inner_area_1 + inner_area_2+ inner_area_3+ inner_area_4;
    if(area != inner_area && input[i].x < first_x && input[i].y < fourth_y)
    {
        m++;
        inputs_new[m] = input [i];

    }
}
    float min = inputs_new[1].x;
    for(i=1;i<m;i++)
    {
        if(min > input[i].x)
        {
            min=input[i].x;
            lowmin=i;
        }
    }
    float max = inputs_new[1].x;
    for(i=1;i<m;i++)
    {
        if(max < input[i].x)
        {
            max=input[i].x;
            lowmax=i;
        }
    }

    leftlower=(m);
    return inputs_new;

}
struct node* LowerBridge(struct Point input[],float a,int size)
{
    int i;
    if(size==2)
    {
        struct node* least = create(input[1].x,input[1].y);
        struct node* highest = create(input[2].x,input[2].y);
        struct node* list = concatenate2(least,highest);
        struct node* temp = list;
        return list;
    }
    if(size==3)
    {
        int i;
        int most_left_x=input[1].x;
        int most_left_y=input[1].y;
        int l=1;
        int most_right_x=most_left_x;
        int most_right_y=most_left_y;
        for(i=2;i<=3;i++)
        {
            if(input[i].x<most_left_x)
            {
                l=i;
                most_left_x=input[i].x;
                most_left_y=input[i].y;
            }
            else if(input[i].x==most_left_x)
            {
                if(input[i].y < most_left_y)
                {
                    l=i;
                    most_left_x=input[i].x;
                    most_left_y=input[i].y;
                }
            }
        }
        int n=1;
        for(i=2;i<=3;i++)
        {
            if(input[i].x>most_right_x)
            {
                n=i;
                most_right_x=input[i].x;
                most_right_y=input[i].y;
            }
            else if(input[i].x==most_right_x)
            {
                if(input[i].y < most_right_y)
                {
                    n=i;
                    most_right_x=input[i].x;
                    most_right_y=input[i].y;
                }
            }
        }



            int m = 6-n-l;
            float new_y=input[m].y;
            float new_x=input[m].x;
            float highest_y=input[n].y;
            float highest_x=input[n].x;
            float least_y=input[l].y;
            float least_x=input[l].x;
            struct node* least;
            struct node* newest;
            if((new_y-least_y)/(new_x-least_x)!=(highest_y-least_y)/(highest_x-least_x))
            {
            if(new_y < least_y && new_y <=a)
            {
                least = create(least_x,least_y);
                newest = create(new_x,new_y);
            }
            else if(new_y < highest_y && new_y>a)
            {
                least = create(least_x,least_y);
                newest = create(new_x,new_y);
            }
            else
            {
                least = create(least_x,least_y);
                newest = create(highest_x,highest_y);
            }
            struct node* list = concatenate2(least,newest);
            return list;
            }
            else
            {
                least = create(least_x,least_y);
                newest = create(new_x,new_y);
                struct node* highest = create(highest_x,highest_y);
                struct node* list = concatenate(least,newest,highest);
                return list;
            }


    }

    struct Point candidates[size+1];
    int l2=0;
    if(size%2!=0)
    {
        candidates[1]=input[size];
        size--;
        l2++;
    }
    float slopes[size];
    float slopes1[size];
    struct Point temp;
    int m=0;
    int n=0;
    i=1;
    while(1)
    {
        if(input[i].x>input[i+1].x)
        {
            temp=input[i+1];
            input[i+1]=input[i];
            input[i]=temp;
        }
        if(input[i].x == input[i+1].x && input[i].y>input[i+1].y)
        {
            temp=input[i+1];
            input[i+1]=input[i];
            input[i]=temp;
        }
        if(input[i].x!=input[i+1].x)
        {
            m++;
            n++;
            slopes[m]=(input[i+1].y-input[i].y);
            slopes[m]=slopes[m]/(input[i+1].x-input[i].x);
            slopes1[n]=slopes[m];
            i=i+2;
        }
        else if(input[i].x==input[i+1].x)
        {
            n++;
            slopes1[n]=PI;
            l2++;
            candidates[l2]=input[i];
            i=i+2;
        }

        if(i>size)
        {
            break;
        }
    }

    float answer1,answer2;
    float med_slope;
    int k;
    if(m>=3)
    {
        if((m)%2!=0)
        {
            k=(m+1)/2;
            med_slope = median1(slopes,1,m,k);
        }
        else
        {
            k = (m)/2;
            answer1 = median1(slopes,1,m,k);
            k++;
            answer2 = median1(slopes,1,m,k);
            med_slope = answer1 + answer2;
            med_slope = med_slope/2;

        }
    }
    else
    {
        med_slope = slopes[1]+slopes[2];
        med_slope = med_slope/2;
    }
    struct Point small[size];
    struct Point equal[size];
    struct Point large[size];
    int l1=0;
    int m1=0;
    int n1=0;
    for(i=1;i<=n;i++)
    {
        if(slopes1[i]<med_slope && slopes[i]!=PI)
        {
            l1++;
            small[l1]=input[2*i-1];

            l1++;
            small[l1]=input[2*i];

        }
        else if(slopes1[i]==med_slope && slopes[i]!=PI)
        {
            m1++;
            equal[m1]=input[2*i-1];

            m1++;
            equal[m1]=input[2*i];


        }
        else if(slopes1[i]>med_slope && slopes[i]!=PI)
        {
            n1++;
            large[n1]=input[2*i-1];

            n1++;
            large[n1]=input[2*i];
        }
    }
    for(i=1;i<=l1;i++)
    {
        printf("%f %f = small \n",small[i].x,small[i].y);
    }
     for(i=1;i<=m1;i++)
    {
        printf("%f %f = equal \n",equal[i].x,equal[i].y);
    }
     for(i=1;i<=n1;i++)
    {
        printf("%f %f = large\n",large[i].x,large[i].y);
    }

    struct Point max[size];
    float min_intercept=(input[1].y-(med_slope)*input[1].x);
    float check;
    for(i=2;i<=size;i++)
    {
        check = input[i].y-(med_slope)*input[i].x;
        if(check < min_intercept)
        {
            min_intercept=check;
        }
    }

    int count=0;
    for(i=1;i<=size;i++)
    {
        check = input[i].y-(med_slope)*input[i].x;
        if(check==min_intercept)
        {
            count++;
            max[count]=input[i];
        }
    }
    float min = max[1].x;
    int least;
    int highest;
    for(i=1;i<=count;i++)
    {
        if(min < max[i].x)
        {
            min=max[i].x;
            least=i;
        }
    }
    float most = max[1].x;

    for(i=1;i<=count;i++)
    {
        if(most < max[i].x)
        {
            most=max[i].x;
            highest=i;
        }
    }
    if(most > a && min <= a )
    {
        float least_x=max[least].x;
        float least_y=max[least].y;
        float highest_x=max[highest].x;
        float highest_y=max[highest].y;

        if(size%2!=0)
        {
            if(candidates[1].x <= a && candidates[1].y > max[least].y)
            {
                least_x=candidates[1].x;
                least_y=candidates[1].y;
            }
            else if(candidates[1].x > a && candidates[1].y > max[highest].y)
            {
                highest_y=candidates[1].x;
                highest_x=candidates[1].y;
            }

        }

        struct node* least = create(least_x,least_y);
        struct node* highest = create(highest_x,highest_y);
        struct node* list = concatenate2(least,highest);
        struct node* temp = list;
        return list;

        }
    else if(most <= a)
    {
        m=2;
        int l=2;
        if(l1>0 || m1>0)
        {
            while(1)
            {
                if(m<=l1)
                {
                    l2++;
                    candidates[l2]=small[m];
                    m+=2;

                }
                if(l<=m1)
                {
                    l2++;
                    candidates[l2]=equal[l];
                    l+=2;
                }
                if(l>m1 && m>l1)
                {
                    break;
                }
            }
        }
        m=0;
        if(n1>0)
        {
            while(1)
            {
                l2++;
                m++;
                candidates[l2]=large[m];
                l2++;
                m++;
                candidates[l2]=large[m];
                if(m==n1){break;}

            }
        }

    }
    else if(min > a)
    {
        m=1;
        int l=1;
        if(n1>0 || m1>0)
        {
            while(1)
            {
                if(m<n1)
                {
                    l2++;
                    candidates[l2]=large[m];
                    m+=2;

                }
                if(l<m1)
                {
                    l2++;
                    candidates[l2]=equal[l];
                    l+=2;
                }
                if(l>m1 && m>n1)
                {
                    break;
                }
            }
        }

        m=0;
        if(l1>0)
        {
            while(1)
            {
                m++;
                l2++;
                candidates[l2]=small[m];

                m++;
                l2++;
                candidates[l2]=small[m];
                if(m==l1)
                {
                    break;
                }
            }
        }
    }


    return LowerBridge(candidates,a,l2);
}


struct node* UpperHull(struct Point input[],struct Point pmin, struct Point pmax,int size)
{
    struct node* head;
    if(pmin.x == pmax.x && pmin.y == pmax.y)
    {
        head = create(pmin.x,pmin.y);
        return head;
    }
    float a;
    float answer1,answer2;
    int k;
    if(size%2!=0)
    {
        k=(size+1)/2;
        a = median(input,1,size,k);
    }
    else
    {
        k = (size)/2;
        answer1 = median(input,1,size,k);
        k++;
        answer2 = median(input,1,size,k);
        a = answer1 + answer2;
        a = a/2;

    }
    struct node* upper_bridge;
    struct Point* input_left;
    struct Point* input_right;
    upper_bridge = UpperBridge(input,a,size);
    int leftup,rightup;
    if(upper_bridge->x == pmin.x && upper_bridge->y == pmin.y)
    {
        leftup=0;
    }
    upper_bridge=upper_bridge->prev;
    if(upper_bridge->x == pmax.x && upper_bridge->y == pmax.y)
    {
        rightup=0;
    }
    upper_bridge=upper_bridge->next;
    int upminl,upmaxl,upminr,upmaxr;
    int size_left,size_right;
    struct node* left_bridge;
    struct node* right_bridge;
    struct node* rightmostpoint = (struct node*)malloc(sizeof(struct node));
    struct node* leftmostpoint = (struct node*)malloc(sizeof(struct node));
    rightmostpoint->x=pumax->x;
    rightmostpoint->y=pumax->y;
    rightmostpoint->next=rightmostpoint;
    rightmostpoint->prev=rightmostpoint;
    leftmostpoint->x=pumin->x;
    leftmostpoint->y=pumin->y;
    leftmostpoint->next=leftmostpoint;
    leftmostpoint->prev=leftmostpoint;
    if(leftup!=0 && rightup!=0)
    {
        input_left = findleftupper(input,upper_bridge,size);
        if(leftupper!=0){
        upminl=upmin;
        upmaxl=upmax;
        pmin = input_left[upmin];
        pmax = input_left[upmax];
        size_left=leftupper;
        left_bridge = UpperHull(input_left,pmin,pmax,size_left);
        upper_bridge = concatenate2(left_bridge,upper_bridge);}
        else{upper_bridge = concatenate2(leftmostpoint,upper_bridge);}
        input_right = findrightupper(input,upper_bridge,size);
        if(rightupper!=0){
        upminr=upmin;
        upmaxr=upmax;
        pmin = input_left[upminr];
        pmax = input_left[upmaxr];
        size_right = rightupper;
        right_bridge = UpperHull(input_right,pmin,pmax,size_right);
        upper_bridge = concatenate2(upper_bridge,right_bridge);}
        else{upper_bridge = concatenate2(upper_bridge,rightmostpoint);}
        return upper_bridge;
    }
    else if(leftup==0 && rightup!=0)
    {
        int tempy = upper_bridge->y;
        upper_bridge->y=upper_bridge->prev->y;
        input_right = findrightupper(input,upper_bridge,size);
        upper_bridge->y=tempy;
        if(rightupper != 0){
        upminr=upmin;
        upmaxr=upmax;
        pmin = input_left[upminr];
        pmax = input_left[upmaxr];
        size_right = rightupper;
        struct node* right_bridge = UpperHull(input_right,pmin,pmax,size_right);
        upper_bridge = concatenate2(upper_bridge,right_bridge);}
        else{upper_bridge = concatenate2(upper_bridge,rightmostpoint);}
        return upper_bridge;
    }
    else if(rightup==0 && leftup!=0)
    {
        int tempy = upper_bridge->prev->y;
        upper_bridge->prev->y=upper_bridge->y;
        input_left = findleftupper(input,upper_bridge,size);
        upper_bridge->prev->y=tempy;
        if(leftupper!=0){
        upminl=upmin;
        upmaxl=upmax;
        struct Point newpmin = input_left[upminl];
        struct Point newpmax = input_left[upmaxl];
        size_left = leftupper;
        struct node* left_bridge = UpperHull(input_left,newpmin,newpmax,size_left);
        upper_bridge = concatenate2(left_bridge,upper_bridge);}
        else{upper_bridge = concatenate2(leftmostpoint,upper_bridge);}
        return upper_bridge;
    }
    else
    {
        return upper_bridge;
    }
}

struct node* LowerHull(struct Point input[],struct Point pmin, struct Point pmax,int size)
{
    struct node* head_l;
    if(pmin.x == pmax.x && pmin.y == pmax.y)
    {
        head_l = create(pmin.x,pmin.y);
        return head_l;
    }
    float a;
    float answer1,answer2;
    int k;

    if(size%2!=0)
    {
        k=(size+1)/2;
        a = median(input,1,size,k);
    }
    else
    {
        k = (size)/2;
        answer1 = median(input,1,size,k);
        k++;
        answer2 = median(input,1,size,k);
        a = answer1 + answer2;
        a = a/2;

    }
    struct node* lower_bridge;
    struct Point* input_left;
    struct Point* input_right;
    lower_bridge = LowerBridge(input,a,size);


    int leftdown=1,rightdown=1;
    if(lower_bridge->x == pmin.x && lower_bridge->y == pmin.y)
    {
        leftdown=0;
    }
    lower_bridge=lower_bridge->prev;
    if(lower_bridge->x == pmax.x && lower_bridge->y == pmax.y)
    {
        rightdown=0;
    }
    lower_bridge=lower_bridge->next;


    struct node* left_bridge;
    struct node* right_bridge;
    struct node* rightmostpoint = (struct node*)malloc(sizeof(struct node));
    struct node* leftmostpoint = (struct node*)malloc(sizeof(struct node));
    rightmostpoint->x=plmax->x;
    rightmostpoint->y=plmax->y;
    rightmostpoint->next=rightmostpoint;
    rightmostpoint->prev=rightmostpoint;
    leftmostpoint->x=plmin->x;
    leftmostpoint->y=plmin->y;
    leftmostpoint->next=leftmostpoint;
    leftmostpoint->prev=leftmostpoint;
    int size_left,size_right;
    if(leftdown!=0 && rightdown!=0)
    {
        input_left = findleftlower(input,lower_bridge,size);
        if(leftupper!=0){
        pmin = input_left[lowmin];
        pmax = input_left[lowmax];
        size_left=leftlower;
        left_bridge = LowerHull(input_left,pmin,pmax,size_left);
        lower_bridge = concatenate2(left_bridge,lower_bridge);}
        else{lower_bridge = concatenate2(leftmostpoint,lower_bridge);}
        input_right = findrightlower(input,lower_bridge,size);
         if(rightupper!=0){
        pmin = input_left[lowmin];
        pmax = input_left[lowmax];
        size_right = rightlower;
        right_bridge = LowerHull(input_right,pmin,pmax,size_right);
        lower_bridge = concatenate2(lower_bridge,right_bridge);}
        else{lower_bridge = concatenate2(lower_bridge,rightmostpoint);}
        return lower_bridge;
    }
    else if(leftdown==0 && rightdown!=0)
    {
        int tempy = lower_bridge->y;
        lower_bridge->y=lower_bridge->prev->y;
        input_right = findrightlower(input,lower_bridge,size);
        lower_bridge->y=tempy;
         if(rightupper!=0){
        pmin = input_left[lowmin];
        pmax = input_left[lowmax];
        size_right = rightlower;
        right_bridge = LowerHull(input_right,pmin,pmax,size_right);
        lower_bridge = concatenate2(lower_bridge,right_bridge);}
        else{lower_bridge = concatenate2(lower_bridge,rightmostpoint);}
        return lower_bridge;
    }
    else if(rightdown==0 && leftdown!=0)
    {
        int tempy = lower_bridge->prev->y;
        lower_bridge->prev->y= lower_bridge->y;
        input_left = findleftlower(input,lower_bridge,size);
        lower_bridge->prev->y=tempy;
        if(leftupper!=0){
        pmin = input_left[lowmin];
        pmax = input_left[lowmax];
        size_left=leftlower;
        left_bridge = LowerHull(input_left,pmin,pmax,size_left);
        lower_bridge = concatenate2(left_bridge,lower_bridge);}
        else{lower_bridge = concatenate2(leftmostpoint,lower_bridge);}
        return lower_bridge;
    }
    else if(rightdown==0 &&leftdown==0)
    {
        return lower_bridge;
    }

}

struct node* ConvexHull(struct Point input[],int size,struct Point plmin,struct Point plmax,struct Point pumin,struct Point pumax)
{
    int i;
    struct Point U_hull[size+1];
    struct Point L_hull[size+1];
    struct node* uhull;
    struct node* lhull;
    struct node* head;


    if(plmin.y==pumin.y && plmax.y==pumax.y)
    {

        uhull = UpperHull(input,pumin,pumax,size);



        lhull = LowerHull(input,plmin,plmax,size);

    }

    else if(plmin.y!=pumin.y || plmax.y!=pumax.y || (plmin.y!=pumin.y &&plmax.y!=pumax.y))
    {

        L_hull[1]=plmin;
        L_hull[2]=plmax;
        int l=2;
        for(i=1;i<=size;i++)
        {
            if(input[i].x!= plmin.x && input[i].x!= plmax.x) // put .x to generalize for points laying on extremes
            {
                L_hull[l]=input[i];
                l++;
            }
        }
        lhull = LowerHull(L_hull,plmin,plmax,l-1);
        l=2;
        U_hull[1]=pumin;
        U_hull[2]=pumax;
        for(i=1;i<=size;i++)
        {
            if((input[i].x)!= pumin.x && input[i].x != pumax.x)
            {
                U_hull[l]=input[i];
                l++;
            }
        }

        uhull = UpperHull(U_hull,pumin,pumax,l-1);

    }


    struct node* convexhull = concatenatehulls(uhull,lhull);


    return convexhull;

}

int main()
{


    int i,j,k,l,m,n;
    scanf("%d",&n);
    struct Point input[n+1];
    for(i=1;i<=n;i++)
    {
        scanf("%f",&input[i].x);
        scanf("%f",&input[i].y);
    }

    float miny=input[1].y;
    float minx=input[1].x;
    l=1;
    for(i=2;i<=n;i++)
    {
        if(input[i].x<minx)
        {
            miny=input[i].y;
            minx=input[i].x;
            l=i;
        }
        if(input[i].x==minx)
        {
            if(input[i].y<miny)
            {
                miny=input[i].y;
                minx=input[i].x;
                l=i;
            }
        }
    }

    plmin=&(input[l]);
    for(i=2;i<=n;i++)
    {
      if(input[i].x==minx)
        {
            if(input[i].y>=miny)
            {
                miny=input[i].y;
                minx=input[i].x;
                l=i;
            }
        }
    }

    pumin=&(input[l]);
    float maxy=input[1].y;
    float maxx=input[1].x;
    l=1;
    for(i=2;i<n+1;i++)
    {
        if(input[i].x>maxx)
        {
            maxy=input[i].y;
            maxx=input[i].x;
            l=i;
        }
        if(input[i].x==maxx)
        {
            if(input[i].y<maxy)
            {
                maxy=input[i].y;
                maxx=input[i].x;
                l=i;
            }
        }
    }

    plmax=&(input[l]);
    for(i=2;i<=n;i++)
    {
      if(input[i].x==maxx)
        {
            if(input[i].y>=maxy)
            {
                miny=input[i].y;
                minx=input[i].x;
                l=i;
            }
        }
    }

    pumax=&(input[l]);
    struct node* head = ConvexHull(input,n,*(plmin),*(plmax),*(pumin),*(pumax));
    struct node* temp;
     float fir_x,fir_y;
    fir_x = head->x;
    fir_y = head->y;
    temp = head;
    head = head->next;
    printf(" 1 - (%f,%f)\n", fir_x , fir_y );
    i=2;
    while(1)
    {
        if(head==temp)
        {
            break;
        }
        else
        {
            printf("%d - (%f,%f)\n", i , head->x , head->y );
            i++;
            head = head->next;
        }
    }






}



