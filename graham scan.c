#include <stdio.h>
#include <math.h>
#define PI 3.14159265
float val = 180.00000 / PI;
struct Point{

    float x,y;
    float angle;

};

void merge(struct Point input[], int l, int m, int r) // sorts all points on the basis of the angle of the line joining the point and the bottom most point w.r.t to the +ve x-axis.
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    struct Point L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = input[l + i];
    for (j = 0; j < n2; j++)
        R[j] = input[m + 1+ j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i].angle < R[j].angle)
        {
            input[k] = L[i];
            i++;
        }
        else if(L[i].angle == R[j].angle)
        {
            if(L[i].x < R[j].x)
            {
                input[k]=L[i];
                i++;
                k++;
                input[k]=R[j];
                j++;
            }
            else
            {
                input[k]=R[j];
                j++;
                k++;
                input[k]=L[i];
                i++;
            }
        }
        else
        {
            input[k] = R[j];
            j++;
        }
        k++;
    }


    while (i < n1)
    {
        input[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        input[k] = R[j];
        j++;
        k++;
    }
}


void mergeSort(struct Point arr[], int l, int r)  // sort all points w.r.t the angle they make with the x axis when joined to lowest point.
{
    if (l < r)
    {
        int m = l+(r-l)/2;
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
        merge(arr, l, m, r);
    }
}

float direction(struct Point *p1,struct Point *p2,struct Point *p3)  /* Helps us determine if the three points, if traversed in order p1->p2->p3 forms a right turn or left turn. */
{


    float angle1,angle2;
    float slope_y,slope_x;
    float output;
    if(p1->x!=p2->x)       // finding angle subtended by line segment (p2,p1) when x co-ordinates are not equal.
    {
        slope_y = (p2->y)-(p1->y);
        slope_x = (p2->x)-(p1->x);
        angle1 = atan2(slope_y,slope_x) * val;
    }
    else{angle1=90.0000;}
    if(p2->x!=p3->x)    // finding angle subtended by line segment (p3,p2) when x co-ordinates are not equal.
    {
        slope_y = (p3->y)-(p2->y);
        slope_x = (p3->x)-(p2->x);
        angle2 = atan2(slope_y,slope_x) * val;
    }
    else{angle2=90.0000;}
    if(angle1<0)
    {
        angle1=angle1+360;
    }
    if(angle2<0)
    {
        angle2=angle2+360;
    }
    if(angle2>=angle1)   // Indicates a left turn. As the angle subtended by line segment (p3,p2) exceeds the angle subtended by (p2,p1)
    {
       output = -1;
    }
    else   // Indicates a left turn. As the angle subtended by line segment (p2,p1) exceeds the angle subtended by (p3,p2)
    {
        output = 1;
    }

    return output;
}

void anglegenerator(struct Point *p1, struct Point *lowest) // Generates the angle of a line joining bottom-most point and point chosen w.r.t the positive x-axis.
{
    float slope_y,slope_x,degrees;

    if(lowest->x!=p1->x)
    {
        slope_y = (p1->y)-(lowest->y);
        slope_x = (p1->x)-(lowest->x);
        degrees = atan2(slope_y,slope_x) * val;
        p1->angle = degrees;
    }
    else{p1->angle=90.00000;}


}


int main()
{
    int n,i,l;
    struct Point temp;
    scanf("%d",&n);
    struct Point input[n];
    for(i=0;i<n;i++){

        scanf("%f",&input[i].x);
        scanf("%f",&input[i].y);
    }

    float miny=input[0].y;
    float minx=input[0].x;
    for(i=1;i<n;i++)
    {
        if(input[i].y<miny)
        {
            miny=input[i].y;
            minx=input[i].x;
            l=i;
        }
        if(input[i].y==miny)
        {
            if(input[i].x<minx)
            {
                miny=input[i].y;
                minx=input[i].x;
                l=i;
            }
        }
    }

    temp=input[l];
    input[l]=input[0];
    input[0]=temp;

for(i=1;i<n;i++)
{
    anglegenerator(&input[i],&input[0]);
}

mergeSort(input,1, n-1);

struct Point convexhull[n];

convexhull[0]=input[0];
convexhull[1]=input[1];
convexhull[2]=input[2];

int size=2,m=2;

while(1)
{
    float orientation = direction(&convexhull[size-2],&convexhull[size-1],&input[m]);
    if(orientation==-1) //indicates a left turn
    {
        convexhull[size]=input[m];
        if(m==n-1){break;}
        size++;
        m++;
     }
    if(orientation==1)
    {
        size--;

    }
}

for(i=0;i<=size;i++)
{
    printf("%d - (%f,%f) \n",i,convexhull[i].x,convexhull[i].y);
}


}







