#include <stdio.h>
#include <math.h>
#define PI 3.14159265
float val = 180.00000 / PI;
struct Point{

    float x,y;
    float angle;

};

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
    if(angle2>angle1)
    {
        output=angle2-angle1;
    }
    else{output=angle1-angle2;}
    return output;
}


float anglegenerator(struct Point *p1, struct Point *lowest) // Generates the angle of a line joining bottom-most point and point chosen w.r.t the positive x-axis.
{
    float slope_y,slope_x,degrees;
    float output;
    if(lowest->x!=p1->x)
    {
        slope_y = (p1->y)-(lowest->y);
        slope_x = (p1->x)-(lowest->x);
        degrees = atan2(slope_y,slope_x) * val;
        output = degrees;
    }
    else{output=90.00000;}

    return output;
}

int main()
{
    int n,i,l;
    struct Point temp;
    scanf("%d",&n);
    struct Point input[n];
    for(i=0;i<n;i++)
    {
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
        if(input[i].y==minx)
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

    struct Point convexhull[n];
    convexhull[0]=input[0];
    float angle;
    int m;
    int min=100000000000;
    int new_point;

    for(m=1;m<n;m++)
    {
        angle = anglegenerator(&convexhull[0],&input[m]);
        if(angle<min)
        {
             min=angle;
             new_point=m;
        }
    }

    for(i=0;i<n;i++)
    {
        printf("%f ",input[i].x);
        printf("%f\n",input[i].y);
    }

    convexhull[1]=input[m];
    int size=1;
    int j,k;
    min=100000000000;
    new_point=0;
    i=0;
    while(1)
    {
     for(m=0;m<n;m++)
     {
         angle = direction(&convexhull[i],&convexhull[i+1],&input[m]);
         if(angle<min&&m!=i&&m!=i+1)
         {
             min=angle;
             new_point=m;
         }
     }
     i++;
     if(new_point==0)
     {
         break;
     }

     convexhull[i+1]=input[new_point];
     size++;
    }
for(i=0;i<=size;i++)
{
    printf("%d - (%f,%f) \n",i,convexhull[i].x,convexhull[i].y);
}


}
