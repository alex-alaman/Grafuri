#include <iostream>
#include <fstream>
#include <graphics.h>
#include <cmath>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int viz[20];

ifstream fin("graf.in");
#define PI 3.1415
#define WINDOW_MAX_X 1000
#define WINDOW_MAX_Y 600

int m[7], i_loadbar=0;
struct pct
{
    int x,y;
};
struct graf
{
    int M[50][50];
    int n,orientat;
    pct centru[50];
};
char* itoa(int value, char* result, int base)
{
    // check that the base if valid
    if (base < 2 || base > 36)
    {
        *result = '\0';
        return result;
    }

    char* ptr = result, *ptr1 = result, tmp_char;
    int tmp_value;

    do
    {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
    }
    while ( value );

    // Apply negative sign
    if (tmp_value < 0) *ptr++ = '-';
    *ptr-- = '\0';
    while(ptr1 < ptr)
    {
        tmp_char = *ptr;
        *ptr--= *ptr1;
        *ptr1++ = tmp_char;
    }
    return result;
}
void grafResetM(graf &x)
{
    for(int i=1; i<=49; i ++)
        for(int j=1; j<=49; j++)
            x.M[i][j]=0;
    x.n=0;
    x.orientat=0;
}
void init(int viz[50])
{
    for(int i=0; i<50; i++)
        viz[i]=0;
}
void DFS(graf a, int nod, int viz[50], int clr)
{
    viz[nod] = clr;
    for(int i = 1; i <= a.n; i++)
        if(viz[i]==0 && a.M[nod][i])
            DFS(a,i,viz,clr);
}
void DFStare(graf a, int nod, int viz[50], int ok)
{
    viz[nod] = 1;
    for(int i =1 ; i <= a.n ; i ++)
        if(viz[i] == 0)
        {
            if(ok==0&&a.M[nod][i]==1)
            {
                DFStare(a,i,viz,0);
            }
            else if(ok==1&&a.M[i][nod]==1)
            {
                DFStare(a,i,viz,1);
            }
        }
}
int esteOrientat(graf &x)
{
    for(int i=1; i<=x.n; i++)
        for(int j=1; j<=x.n; j++)
            if(x.M[i][j]!=x.M[j][i])
                return 1;
    return 0;
}
void citeste_desen(graf &a, int orientat);
int citireConsola(graf &X)
{
    int opt;
    do
    {

        cout<<"\nInserare prin muchii (1) sau prin matrice de adiacenta (2) ( abandon = 0 )?\n";
        cin>>opt;
        if(opt!=1&&opt!=2&&opt!=0)
            cout<<"\nAlegeti o optiune valabila\n";
    }
    while(opt!=1&&opt!=2&&opt!=0);
    if(opt==0)
        return -1;
    if(opt==1)
    {
//        cout<<"\nOrientat?\n";
//        do
//        {
//            cin>>X.orientat;
//        }
        X.orientat=1;
        while(X.orientat!=0&&X.orientat!=1);
        cout<<"\nCitirea muchiilor se termina prin inserarea '0'.";
        if(X.orientat)
            cout<<" Pentru grafuri orientate, perechea (i,j) citita indica existenta arcului i->j";
        cout<<"\n";
        int i,j;
        cin>>i;
        while(i!=0)
        {
            cin>>j;
            if(j==0)
                break;
            X.M[i][j]=1;
            if(!X.orientat)
                X.M[j][i]=1;
            cin>>i;
        }
        return 1;
    }
    if(opt==2)
    {
        cout<<"\nSe admit NUMAI 1 si 0 (1 = exista muchie/arc, 0 = nu)\n";
        for(int i=1; i<=X.n; i++)
            for(int j=1; j<=X.n; j++)
            {
                cin>>X.M[i][j];
                if(X.M[i][j]!=1&&X.M[i][j]!=0)
                {
                    cout<<"\nSE ADMIT NUMAI 0 SI 1!\n";
                    return 0;
                }
            }
        for(int i=1; i<=X.n; i++)
            if(X.M[i][i])
            {
                cout<<"\nUn nod nu are voie sa fie vecin cu el insusi\n";
                system("pause");
                return 0;
            }
        X.orientat=esteOrientat(X);
        return 1;
    }
    cout<<"Nu imi dau seama cum ai ajuns la eroarea asta, felicitari.";
    return 0;
}
int citireFisier(graf &X)
{
    int a,b;
    if(fin>>a)
    {
        if(fin>>b)
        {
            if(a==0||b==0||(a==1&&b==1))
            {
                X.M[1][1]=a;
                X.M[1][2]=b;
                for(int i=1; i<=X.n; i++)
                    for(int j=1; j<=X.n; j++)
                    {
                        if(i!=1||j>2)
                        {
                            if(fin>>X.M[i][j])
                            {
                                if(X.M[i][j]!=1&&X.M[i][j]!=0)
                                {
                                    cleardevice();
                                    setcolor(RED);
                                    settextstyle(GOTHIC_FONT,HORIZ_DIR,1);
                                    outtextxy(50,100,"Matrice de adiacenta definita gresit in graf.in.");
                                    return 0;
                                }

                            }
                            else
                            {
                                cleardevice();
                                setcolor(RED);
                                settextstyle(GOTHIC_FONT,HORIZ_DIR,1);
                                outtextxy(50,100,"Matricea de adiacenta din fisierul de intrare este incompleta.");
                                return 0;
                            }

                        }
                    }
                for(int i=1; i<=X.n; i++)
                    if(X.M[i][i])
                    {
                        cleardevice();
                        setcolor(RED);
                        settextstyle(GOTHIC_FONT,HORIZ_DIR,1);
                        outtextxy(50,100,"Matrice de adiacenta definita gresit in graf.in.");
                        return 0;
                    }
                X.orientat=esteOrientat(X);
                return 1;
            }
            else
            {
                if(a==b||a<=0||b<=0||a>X.n||b>X.n)
                {
                    cleardevice();
                    setcolor(RED);
                    settextstyle(GOTHIC_FONT,HORIZ_DIR,1);
                    outtextxy(50,100,"Muchii incorect definite in graf.in.");
                    return 0;
                }
                settextstyle(GOTHIC_FONT,HORIZ_DIR,1);
                setcolor(BLACK);
                outtextxy(WINDOW_MAX_X/2-50, WINDOW_MAX_Y/2-50,"Orientat?");
                ///////////
                setcolor(BLUE);
                rectangle(WINDOW_MAX_X/2-250,WINDOW_MAX_Y/2+30,WINDOW_MAX_X/2,WINDOW_MAX_Y/2+130);
                setfillstyle(SOLID_FILL,BLUE);
                floodfill(WINDOW_MAX_X/2-50,WINDOW_MAX_Y/2+80,BLUE);
                setcolor(WHITE);
                setbkcolor(BLUE);
                outtextxy(WINDOW_MAX_X/2-200,WINDOW_MAX_Y/2+80,"ORIENTAT");
                setbkcolor(WHITE);
                ///////////
                setcolor(YELLOW);
                rectangle(WINDOW_MAX_X/2+10,WINDOW_MAX_Y/2+30,WINDOW_MAX_X/2+260,WINDOW_MAX_Y/2+130);
                setfillstyle(SOLID_FILL,YELLOW);
                floodfill(WINDOW_MAX_X/2+60,WINDOW_MAX_Y/2+80,YELLOW);
                setcolor(BLACK);
                setbkcolor(YELLOW);
                outtextxy(WINDOW_MAX_X/2+40,WINDOW_MAX_Y/2+80,"NEORIENTAT");
                setbkcolor(WHITE);
                ///////////
                int tempok=0;
                while(tempok==0)
                {
                    while(!ismouseclick(WM_LBUTTONDOWN))
                        delay(10);
                    int tempx, tempy;
                    getmouseclick(WM_LBUTTONDOWN,tempx,tempy);
                    if(tempx<=WINDOW_MAX_X/2&&tempx>=WINDOW_MAX_X/2-250&&tempy<=WINDOW_MAX_Y/2+130&&tempy>=WINDOW_MAX_Y/2+30)
                    {
                        tempok=1;
                        X.orientat=1;
                    }
                    if(tempx<=WINDOW_MAX_X/2+260&&tempx>=WINDOW_MAX_X/2+10&&tempy<=WINDOW_MAX_Y/2+130&&tempy>=WINDOW_MAX_Y/2+30)
                    {
                        tempok=1;
                        X.orientat=0;
                    }
                }
                //////////////
                X.M[a][b]=1;
                if(!X.orientat)
                    X.M[b][a]=1;
                while(fin>>a)
                {
                    if(fin>>b)
                    {
                        if(a==b||a<=0||b<=0||a>X.n||b>X.n)
                        {
                            cleardevice();
                            setcolor(RED);
                            settextstyle(GOTHIC_FONT,HORIZ_DIR,1);
                            outtextxy(50,100,"Muchii incorect definite in graf.in.");
                            return 0;
                        }
                        X.M[a][b]=1;
                        if(!X.orientat)
                            X.M[b][a]=1;
                    }
                    else
                    {
                        system("pause");
                        cleardevice();
                        setcolor(RED);
                        settextstyle(GOTHIC_FONT,HORIZ_DIR,1);
                        outtextxy(50,100,"Muchii incorect definite in graf.in.");
                        return 0;
                    }
                }
                return 1;
            }
        }
        else
        {
            cleardevice();
            setcolor(RED);
            outtextxy(50,100,"Fisierul de intrare nu contine matrice de adiacenta sau lista");
            outtextxy(50,120,"de muchii. Corectati datele din graf.in sau goliti fisierul.");
            return 0;
        }
    }
    else
    {
        cleardevice();
        setcolor(RED);
        outtextxy(50,100,"Matricea data in fisierul graf.in nu are muchii.");
        if(getch())
            return 1;
    }

}
int citire(graf &X)
{
    grafResetM(X);
    int t;
    if(fin>>t)
    {
        X.n=t;
        if(X.n<=0)
        {
            cleardevice();
            setcolor(RED);
            outtextxy(50,100,"Numarul de noduri (Primul numar introdus in fisier) trebuie sa fie");
            outtextxy(50,120,"STRICT mai mare ca 0!");
            return 0;
        }
        return citireFisier(X);
    }
    else
    {
        fin.close();
        cleardevice();
        setcolor(BLACK);
        settextstyle(GOTHIC_FONT,HORIZ_DIR,1);
        outtextxy(WINDOW_MAX_X/2-200, WINDOW_MAX_Y/2-50,"Fisierul graf.in este gol. Ce doriti?");
        //////////
        setcolor(RED);
        rectangle(WINDOW_MAX_X/2-250,WINDOW_MAX_Y/2+30,WINDOW_MAX_X/2,WINDOW_MAX_Y/2+130);
        setfillstyle(SOLID_FILL,RED);
        floodfill(WINDOW_MAX_X/2-50,WINDOW_MAX_Y/2+80,RED);
        setcolor(WHITE);
        setbkcolor(RED);
        outtextxy(WINDOW_MAX_X/2-170,WINDOW_MAX_Y/2+80,"IESIRE");
        setbkcolor(WHITE);
        ///////////
        setcolor(BLUE);
        rectangle(WINDOW_MAX_X/2+10,WINDOW_MAX_Y/2+30,WINDOW_MAX_X/2+300,WINDOW_MAX_Y/2+130);
        setfillstyle(SOLID_FILL,BLUE);
        floodfill(WINDOW_MAX_X/2+60,WINDOW_MAX_Y/2+80,BLUE);
        setcolor(WHITE);
        setbkcolor(BLUE);
        outtextxy(WINDOW_MAX_X/2+40,WINDOW_MAX_Y/2+80,"CITIRE CONSOLA");
        setbkcolor(WHITE);
        ///////////
        setcolor(GREEN);
        rectangle(WINDOW_MAX_X/2-250,WINDOW_MAX_Y/2+140,WINDOW_MAX_X/2+300,WINDOW_MAX_Y/2+240);
        setfillstyle(SOLID_FILL,GREEN);
        floodfill(WINDOW_MAX_X/2+60,WINDOW_MAX_Y/2+190,GREEN);
        setcolor(WHITE);
        setbkcolor(GREEN);
        outtextxy(WINDOW_MAX_X/2-100,WINDOW_MAX_Y/2+190,"DESENARE GRAF");
        setbkcolor(WHITE);
        ///////////
//        cin>>c;
//        while(c!=0&&c!=1&&c!=2)
//        {
//            cout<<"\nAlege o optiune valabila\n";
//            cin>>c;
//        }
        int tempok=0;
        while(tempok==0)
        {
            while(!ismouseclick(WM_LBUTTONDOWN))
                delay(10);
            int tempx, tempy;
            getmouseclick(WM_LBUTTONDOWN,tempx,tempy);
            if(tempx<=WINDOW_MAX_X/2&&tempx>=WINDOW_MAX_X/2-250&&tempy<=WINDOW_MAX_Y/2+130&&tempy>=WINDOW_MAX_Y/2+30)
            {
                tempok=1;
                return -1;
            }
            if(tempx<=WINDOW_MAX_X/2+260&&tempx>=WINDOW_MAX_X/2+10&&tempy<=WINDOW_MAX_Y/2+130&&tempy>=WINDOW_MAX_Y/2+30)
            {
                tempok=1;
                //////////////
                setbkcolor(WHITE);
                cleardevice();
                setcolor(BLACK);
                settextstyle(GOTHIC_FONT,HORIZ_DIR,1);
                outtextxy(50, 100, "Se asteapta introducerea datelor despre graf in consola.");
                //////////////
                system("cls");
                cout<<"\nNumarul de noduri:\n";
                cin>>X.n;
                while(X.n<=0)
                {
                    cout<<"\nNumarul de noduri trebuie sa fie diferit de 0!\n";
                    cin>>X.n;
                }
                return citireConsola(X);
            }
            if(tempx<=WINDOW_MAX_X/2+300&&tempx>=WINDOW_MAX_X/2-250&&tempy<=WINDOW_MAX_Y/2+240&&tempy>=WINDOW_MAX_Y/2+140)
            {
                setbkcolor(WHITE);
                cleardevice();
                tempok=1;
                settextstyle(GOTHIC_FONT,HORIZ_DIR,1);
                setcolor(BLACK);
                outtextxy(WINDOW_MAX_X/2-50, WINDOW_MAX_Y/2-50,"Orientat?");
                ///////////
                setcolor(BLUE);
                rectangle(WINDOW_MAX_X/2-250,WINDOW_MAX_Y/2+30,WINDOW_MAX_X/2,WINDOW_MAX_Y/2+130);
                setfillstyle(SOLID_FILL,BLUE);
                floodfill(WINDOW_MAX_X/2-50,WINDOW_MAX_Y/2+80,BLUE);
                setcolor(WHITE);
                setbkcolor(BLUE);
                outtextxy(WINDOW_MAX_X/2-200,WINDOW_MAX_Y/2+80,"ORIENTAT");
                setbkcolor(WHITE);
                ///////////
                setcolor(YELLOW);
                rectangle(WINDOW_MAX_X/2+10,WINDOW_MAX_Y/2+30,WINDOW_MAX_X/2+260,WINDOW_MAX_Y/2+130);
                setfillstyle(SOLID_FILL,YELLOW);
                floodfill(WINDOW_MAX_X/2+60,WINDOW_MAX_Y/2+80,YELLOW);
                setcolor(BLACK);
                setbkcolor(YELLOW);
                outtextxy(WINDOW_MAX_X/2+40,WINDOW_MAX_Y/2+80,"NEORIENTAT");
                setbkcolor(WHITE);
                ///////////
                int temptempok=0;
                while(temptempok==0)
                {
                    while(!ismouseclick(WM_LBUTTONDOWN))
                        delay(10);
                    int temptempx, temptempy;
                    getmouseclick(WM_LBUTTONDOWN,temptempx,temptempy);
                    if(temptempx<=WINDOW_MAX_X/2&&temptempx>=WINDOW_MAX_X/2-250&&temptempy<=WINDOW_MAX_Y/2+130&&temptempy>=WINDOW_MAX_Y/2+30)
                    {
                        temptempok=1;
                        citeste_desen(X,1);
                    }
                    if(temptempx<=WINDOW_MAX_X/2+260&&temptempx>=WINDOW_MAX_X/2+10&&temptempy<=WINDOW_MAX_Y/2+130&&temptempy>=WINDOW_MAX_Y/2+30)
                    {
                        temptempok=1;
                        citeste_desen(X,0);
                    }
                }
                return 1;
            }
        }
    }
}
void grafAfisareM(graf &x)
{
    for(int i=1; i<=x.n; i++)
    {
        for(int j=1; j<=x.n; j++)
            cout<<x.M[i][j]<<" ";
        cout<<endl;
    }
}
void deseneaza_arc(graf &a, int nod1, int nod2, int lant)
{
    double unghi;
    const int r=40;
    if(lant)
        setcolor(RED);
    else
        setcolor(BLUE);
    if(a.centru[nod1].y!=a.centru[nod2].y)
        unghi=atan(((double)(a.centru[nod1].x-a.centru[nod2].x))/((double)(a.centru[nod1].y-a.centru[nod2].y)));
    else
        unghi=PI/2;
    int ax1,ay1,ax2,ay2,bx1,bx2,by1,by2;
    ax1=a.centru[nod1].x-r*sin(unghi);
    ay1=a.centru[nod1].y-r*cos(unghi);
    ax2=a.centru[nod2].x+r*sin(unghi);
    ay2=a.centru[nod2].y+r*cos(unghi);
    bx1=a.centru[nod1].x+r*sin(unghi);
    by1=a.centru[nod1].y+r*cos(unghi);
    bx2=a.centru[nod2].x-r*sin(unghi);
    by2=a.centru[nod2].y-r*cos(unghi);
    if(sqrt((ax1-ax2)*(ax1-ax2)+(ay1-ay2)*(ay1-ay2))<sqrt((bx1-bx2)*(bx1-bx2)+(by1-by2)*(by1-by2)))
    {
        line(ax1,ay1,ax2,ay2);
        if(a.orientat)
        {
            line(ax2,ay2,ax2+20*sin(unghi+0.4),ay2+20*cos(unghi+0.4));
            line(ax2,ay2,ax2+20*sin(unghi-0.4),ay2+20*cos(unghi-0.4));
        }

    }
    else
    {
        line(bx1,by1,bx2,by2);
        if(a.orientat)
        {
            line(bx2,by2,bx2-20*sin(unghi+0.4),by2-20*cos(unghi+0.4));
            line(bx2,by2,bx2-20*sin(unghi-0.4),by2-20*cos(unghi-0.4));
        }
    }
}
void deseneaza_graf(graf &a)
{
    cleardevice();
    int R=200,r=40;
    double x=250,y=300;
    double alfa;
    alfa=2*PI/a.n;
    for(int i=0; i<a.n; i++)
    {
        a.centru[i+1].x=x+R*sin(i*alfa);
        a.centru[i+1].y=y+R*cos(i*alfa);
        setcolor(BLACK);
        setbkcolor(WHITE);
        circle(a.centru[i+1].x,a.centru[i+1].y,r);
        setfillstyle(SOLID_FILL,BLACK);
        fillellipse(a.centru[i+1].x,a.centru[i+1].y,r,r);
        setfillstyle(SOLID_FILL,WHITE);
        fillellipse(a.centru[i+1].x,a.centru[i+1].y,r-7,r-7);
        char s[3];
        itoa(i+1,s,10);
        setcolor(BLACK);
        outtextxy((a.centru[i+1].x-r/2+15),(a.centru[i+1].y-r/2)+10,s);
    }
    for(int i=1; i<=a.n; i++)
        for(int j=1; j<=a.n; j++)
            if(a.M[i][j]==1)
                deseneaza_arc(a,i,j,0);
}

void deseneaza_bf(graf &a, int nod)
{
    initwindow(1000,1000);
    int R=200,r=40;
    double x=600,y=400,xi,yi;

    double alfa= 2*3.1415/a.n;
    for(int i=0; i<a.n; i++)
    {
        xi=x+R*sin(i*alfa);
        yi=y+R*cos(i*alfa);
        a.centru[i+1].x=xi;
        a.centru[i+1].y=yi;
        setcolor(RED);
        circle(xi,yi,r);
        ///setfillpattern(pattern, MAGENTA);
        setfillstyle(SOLID_FILL,MAGENTA);
        fillellipse(xi,yi,r,r);
        ///setfillpattern(pattern, CYAN);
        setfillstyle(SOLID_FILL,CYAN);
        fillellipse(xi,yi,r-7,r-7);
        char s[3];
        itoa(i+1,s,10);
        setcolor(7);
        outtextxy((xi-r/2+17),(yi-r/2)+10,s);
    }
}


void CitireLant(int lant[50],int &l)
{
    setbkcolor(WHITE);
    settextstyle(GOTHIC_FONT,HORIZ_DIR,1);
    setcolor(BLACK);
    cleardevice();
    outtextxy(50, 100, "Introduceti datele cerute in consola...");
    int i=1,nod;
    cout<<"\nDati o secventa de noduri care se termina cu 0:\n";
    cin>>nod;
    while(nod)
    {
        lant[i]=nod;
        cin>>nod;
        i++;
    }
    l=i-1;
}
void analizaLant(int v[50], int l, graf &x)
{
    setbkcolor(WHITE);
    settextstyle(GOTHIC_FONT,HORIZ_DIR,1);
    setcolor(BLACK);
    cleardevice();
    system("cls");
    deseneaza_graf(x);
    ////
    setcolor(BLUE);
    rectangle(500,1,WINDOW_MAX_X-1, WINDOW_MAX_Y-1);
    setfillstyle(SOLID_FILL,BLUE);
    floodfill(502,4,BLUE);
    setcolor(WHITE);
    setbkcolor(BLUE);
    ////
    if(l<=1)
    {
        cout<<"Lant prea mic\n";
        system("pause");
    }
    else
    {
        int exista=1;
        for(int i=1; i<l; i++)
            if(v[i]>x.n||v[i]<1||v[i+1]<1||v[i+1]>x.n||x.M[v[i]][v[i+1]]==0)
                exista=0;
        if(!exista)
        {
            if(x.orientat)
                outtextxy((500+WINDOW_MAX_X-1)/2-50, 10,"Nu exista acest drum");
            else
                outtextxy((500+WINDOW_MAX_X-1)/2-50, 10,"Nu exista acest lant");

        }
        else
        {
            for(int i=1; i<l; i++)
                deseneaza_arc(x,v[i],v[i+1],1);
            setcolor(WHITE);
            if(x.orientat)
                outtextxy((500+WINDOW_MAX_X-1)/2-50, 10,"Drumul exista in graf");
            else
                outtextxy((500+WINDOW_MAX_X-1)/2-50, 10,"Lantul exista in graf");
            //deseneaza_lant(v,l,x.M,x.n);
            int elementar=1, simplu=1, ciclu=0,nr=0,viz[50],muchii[50][50];
            init(viz);
            for(int i=1; i<l; i++)
                for(int j=i+1; j<=l; j++)
                {
                    if(v[i]==v[j])
                    {
                        nr++;
                        elementar=0;
                        if(i==1&&j==l)
                            ciclu=1;
                    }
                    viz[i]++;
                    viz[j]++;
                }
            for(int i=1; i<l-1; i++)
                for(int j=i+1; j<l; j++)
                    if((v[i]==v[j] && v[i+1]==v[j+1]) || (v[i]==v[j+1] && v[i+1]==v[j]))
                    {
                        simplu=0;
                        break;
                    }
            char aa[30],bb[5];
            strcpy(aa,"Este de lungime ");
            itoa(l-1,bb,10);
            strcat(aa,bb);
            outtextxy(520, 50, aa);
            if(elementar)
                outtextxy(520, 100, "Este elementar");
            else
            {
                if(ciclu)
                {
                    if(x.orientat)
                        outtextxy(520, 100, "Este circuit");
                    else
                        outtextxy(520, 100, "Este ciclu");
                    if(nr==1)
                        outtextxy(520, 150, "Este elementar");
                    else
                        outtextxy(520, 150, "Nu este elementar");
                }
                else
                {
                    outtextxy(520, 100, "Nu este elementar");
                    outtextxy(520, 150, "Nu este ciclu/circuit");
                }

            }
            if(simplu)
                outtextxy(520, 200, "Este simplu");
            else
                outtextxy(520, 200, "Nu este simplu");
            for(int i=1; i<l; i++)
                deseneaza_arc(x,v[i],v[i+1],1);
        }

    }

}
void desen_nod(int x, int y, int nrcrt, graf a)
{
    const float r=40;
    circle(x,y,r);
    setfillstyle(SOLID_FILL,BLACK);
    fillellipse(x,y,r,r);
    setfillstyle(SOLID_FILL,WHITE);
    fillellipse(x,y,r-7,r-7);
    char s[3];
    itoa(nrcrt,s,10);
    setcolor(BLACK);
    outtextxy((x-r/2+17),(y-r/2)+10,s);
}
void citeste_desen(graf &a, int orientat)
{
    a.n=0;
    a.orientat=orientat;
    for(int i=1; i<=49; i++)
        for(int j=1; j<=49; j++)
            a.M[i][j]=0;
    setbkcolor(WHITE);
    setcolor(BLACK);
    settextstyle(GOTHIC_FONT,HORIZ_DIR,1);
    cleardevice();
    setcolor(GREEN);
    rectangle(1,WINDOW_MAX_Y-30,WINDOW_MAX_X-2,WINDOW_MAX_Y-2);
    setfillstyle(SOLID_FILL,GREEN);
    floodfill(WINDOW_MAX_X/2,WINDOW_MAX_Y-25,GREEN);
    setcolor(WHITE);
    setbkcolor(GREEN);
    outtextxy(WINDOW_MAX_X/2-50,WINDOW_MAX_Y-25,"FINALIZARE");
    setbkcolor(WHITE);
    int x, y, stop=0, k=1, nodSelectat=-1;
    while(!stop)
    {
        while(!ismouseclick(WM_LBUTTONDOWN))
            delay(10);
        getmouseclick(WM_LBUTTONDOWN,x,y);
        if(x>=4&&y>=40&&x<=WINDOW_MAX_X-10&&y<=WINDOW_MAX_Y-40)
        {
            int penod=0, i;
            for(i=1; i<=a.n; i++)
                if(sqrt((a.centru[i].x-x)*(a.centru[i].x-x)+(a.centru[i].y-y)*(a.centru[i].y-y))<80)
                {
                    penod=1;
                    break;
                }
            if(penod)
            {
                if(sqrt((a.centru[i].x-x)*(a.centru[i].x-x)+(a.centru[i].y-y)*(a.centru[i].y-y))<=40)
                {
                    if(nodSelectat==i)
                    {
                        nodSelectat=-1;
                        setfillstyle(SOLID_FILL,WHITE);
                        floodfill(a.centru[i].x-7,a.centru[i].y-7,BLACK);
                    }
                    else
                    {
                        if(nodSelectat!=-1)
                        {
                            deseneaza_arc(a,nodSelectat,i,0);
                            a.M[nodSelectat][i]=1;
                            if(!orientat)
                                a.M[i][nodSelectat]=1;
                            setfillstyle(SOLID_FILL,WHITE);
                            floodfill(a.centru[nodSelectat].x-7,a.centru[nodSelectat].y-7,BLACK);
                            nodSelectat=-1;
                        }
                        else
                        {
                            nodSelectat=i;
                            setfillstyle(SOLID_FILL,BLUE);
                            floodfill(a.centru[i].x-7,a.centru[i].y-7,BLACK);
                        }
                    }
                }
            }
            else
            {
                desen_nod(x,y,k,a);
                a.n++;
                a.centru[k].x=x;
                a.centru[k].y=y;
                k++;
            }
        }
        if(1<=x&&x<=WINDOW_MAX_X-2&&WINDOW_MAX_Y-30<=y&&y<=WINDOW_MAX_Y-2)
            stop=1;
    }
}
void BF(graf p,int nodstart)
{
    setbkcolor(YELLOW);
    setcolor(BLACK);
    double alfa=2*3.1415/p.n;
    double x=250,y=300,xi,yi;
    int R=200,r=40;
    int parc[50], viz[50],in=1,sf=1 ;
    for(int i=0; i<=p.n; i++)
    {
        parc[i]=0;
        viz[i]=0;
    }
    parc[1]=nodstart;
    viz[nodstart]=1;
    while(in<=sf)
    {
        for (int j=1; j<=p.n; j++)
            if(p.M[parc[in]][j]==1 && viz[j]==0)
            {
                parc[++sf]=j;
                viz[j]=1 ;
            }
        in++;
    }
    for(int i=1; i<=sf; i++)
    {
        settextstyle(EUROPEAN_FONT, HORIZ_DIR,2);
        xi=x+R*sin((parc[i]-1)*alfa);
        yi=y+R*cos((parc[i]-1)*alfa);
        setfillstyle(SOLID_FILL,YELLOW);
        fillellipse(xi,yi,r-7,r-7);
        char s[3];
        itoa(parc[i],s,10);
        outtextxy((xi-r/2+17),(yi-r/2)+10,s);
        delay(700);
    }
    for(int i=1; i<=p.n; i++)
        cout<<parc[i]<<" ";
    cout<<endl;

}

void DF(graf p,int nodstart)
{
    setbkcolor(YELLOW);
    setcolor(BLACK);
    double alfa= 2*3.1415/p.n;
    double x=250,y=300,xi,yi;
    int R=200,r=40;
    int st[50],viz[50],vf,ct=1,parc[50];
    init(viz);
    viz[nodstart]=1;
    vf=1;
    st[vf]=nodstart;
    parc[vf]=nodstart;
    cout<<nodstart<<" ";
    while(vf!=0)
    {
        int i=1,k=st[vf];
        while(i<=p.n && (p.M[k][i]==0 || (p.M[k][i]==1 && viz[i]==1)))
            i++;
        if(i==p.n+1)
            vf--;
        else
        {
            cout<<i<<" ";
            vf++;
            parc[++ct]=i;
            st[vf]=i;
            viz[i]=1;
        }
    }
    for(int i=1; i<=ct; i++)
    {
        settextstyle(EUROPEAN_FONT, HORIZ_DIR, 2);
        xi=x+R*sin((parc[i]-1)*alfa);
        yi=y+R*cos((parc[i]-1)*alfa);
        if(viz[i]==1)
            setfillstyle(SOLID_FILL,YELLOW);
        fillellipse(xi,yi,r-7,r-7);
        char s[3];
        itoa(parc[i],s,10);
        outtextxy((xi-r/2+17),(yi-r/2)+10,s);
        delay(700);
    }
}
int main()
{
    graf A;
    initwindow(WINDOW_MAX_X,WINDOW_MAX_Y);
    setbkcolor(15);
    cleardevice();
start:
    setcolor(0);
    settextstyle(4,HORIZ_DIR,1);
    outtextxy(50, 100, "Se incarca graf.in");
    int err=citire(A);
    if(err==-1)
    {
        return 0;
    }
    else if(err==0)
    {
        settextstyle(BOLD_FONT,HORIZ_DIR,1);
        outtextxy(50,200,"EROARE LA CITIRE");
        if(getch())
            return 0;
    }
startb:
    setbkcolor(WHITE);
    settextstyle(GOTHIC_FONT,HORIZ_DIR,1);
    setcolor(BLACK);
    cleardevice();
    system("cls");
    deseneaza_graf(A);
    cout<<"Matricea de adiacenta\n";
    grafAfisareM(A);
    ////
    setcolor(BLUE);
    rectangle(500,1,WINDOW_MAX_X-1, WINDOW_MAX_Y-1);
    setfillstyle(SOLID_FILL,BLUE);
    floodfill(502,4,BLUE);
    setcolor(WHITE);
    setbkcolor(BLUE);
    outtextxy((500+WINDOW_MAX_X-1)/2-50, 10,"MENU");
    ////
    outtextxy(520, 50, "1) Analiza unui lant/drum");
    outtextxy(520, 100, "2) BF");
    outtextxy(520, 150, "3) DF");
    if(A.orientat==0)
        outtextxy(520, 200, "4) Componente conexe");
    else
        outtextxy(520, 200, "4) Componente tare conexe");
    outtextxy(520, 250, "5) Introdu graf grafic");
    outtextxy(520, 300, "6) Citeste alt graf");
    setcolor(BLACK);
    outtextxy((500+WINDOW_MAX_X-1)/2-50, WINDOW_MAX_Y-90, "INAPOI");
    setcolor(RED);
    outtextxy((500+WINDOW_MAX_X-1)/2-50, WINDOW_MAX_Y-40, "IESIRE");

    int tempok=0;
    while(tempok==0)
    {
        while(!ismouseclick(WM_LBUTTONDOWN))
            delay(10);
        int tempx, tempy;
        getmouseclick(WM_LBUTTONDOWN,tempx,tempy);
        if(500<=tempx&&tempx<=WINDOW_MAX_X-1&&30<=tempy&&tempy<=74) //1)
        {
            tempok=1;
            ///////
            int lant[500], l;
            CitireLant(lant, l);
            analizaLant(lant, l, A);
            ///////
            setcolor(YELLOW);
            outtextxy((500+WINDOW_MAX_X-1)/2-50, WINDOW_MAX_Y-90, "INAPOI");
            int temptempok=0;
            while(temptempok==0)
            {
                while(!ismouseclick(WM_LBUTTONDOWN))
                    delay(10);
                int temptempx, temptempy;
                getmouseclick(WM_LBUTTONDOWN,temptempx,temptempy);
                if(500<=temptempx&&temptempx<=WINDOW_MAX_X-1&&WINDOW_MAX_Y-110<=temptempy&&temptempy<=WINDOW_MAX_Y-60)
                {
                    temptempok=1;
                }
            }
            goto startb;
        }
        if(500<=tempx&&tempx<=WINDOW_MAX_X-1&&75<=tempy&&tempy<=124) //2)
        {
            tempok=1;
            //////////
            setbkcolor(WHITE);
            settextstyle(GOTHIC_FONT,HORIZ_DIR,1);
            setcolor(BLACK);
            deseneaza_graf(A);
            ////
            setcolor(BLUE);
            rectangle(500,1,WINDOW_MAX_X-1, WINDOW_MAX_Y-1);
            setfillstyle(SOLID_FILL,BLUE);
            floodfill(502,4,BLUE);
            setcolor(WHITE);
            setbkcolor(BLUE);
            outtextxy((500+WINDOW_MAX_X-1)/2-50, 10,"MENU");
            setcolor(YELLOW);
            outtextxy((500+WINDOW_MAX_X-1)/2-50, WINDOW_MAX_Y-90, "INAPOI");
            outtextxy(520, 100, "Selectati nodul din care doriti DF");
            ////
            int temptempok=0;
            while(temptempok==0)
            {
                while(!ismouseclick(WM_LBUTTONDOWN))
                    delay(10);
                int temptempx, temptempy;
                getmouseclick(WM_LBUTTONDOWN,temptempx,temptempy);
                for(int tempnod=1; tempnod<=A.n; tempnod++)
                {
                    if((temptempx-A.centru[tempnod].x)*(temptempx-A.centru[tempnod].x)+(temptempy-A.centru[tempnod].y)*(temptempy-A.centru[tempnod].y)<=40*40)
                    {
                        temptempok=1;
                        ////
                        setcolor(BLUE);
                        outtextxy(520, 100, "Selectati nodul din care doriti BF");
                        setcolor(WHITE);
                        char l[30],r[5];
                        strcpy(l,"BF din ");
                        itoa(tempnod,r,10);
                        strcat(l,r);
                        outtextxy(520, 100, l);
                        ////
                        BF(A,tempnod);
                        break;
                    }
                }
                if(500<=temptempx&&temptempx<=WINDOW_MAX_X-1&&WINDOW_MAX_Y-110<=temptempy&&temptempy<=WINDOW_MAX_Y-60)
                {
                    temptempok=1;
                }
            }
            goto startb;
        }
        if(500<=tempx&&tempx<=WINDOW_MAX_X-1&&125<=tempy&&tempy<=174) //3)
        {
            tempok=1;
            //////////
            setbkcolor(WHITE);
            settextstyle(GOTHIC_FONT,HORIZ_DIR,1);
            setcolor(BLACK);
            deseneaza_graf(A);
            ////
            setcolor(BLUE);
            rectangle(500,1,WINDOW_MAX_X-1, WINDOW_MAX_Y-1);
            setfillstyle(SOLID_FILL,BLUE);
            floodfill(502,4,BLUE);
            setcolor(WHITE);
            setbkcolor(BLUE);
            outtextxy((500+WINDOW_MAX_X-1)/2-50, 10,"MENU");
            setcolor(YELLOW);
            outtextxy((500+WINDOW_MAX_X-1)/2-50, WINDOW_MAX_Y-90, "INAPOI");
            outtextxy(520, 150, "Selectati nodul din care doriti DF");
            ////
            int temptempok=0;
            while(temptempok==0)
            {
                while(!ismouseclick(WM_LBUTTONDOWN))
                    delay(10);
                int temptempx, temptempy;
                getmouseclick(WM_LBUTTONDOWN,temptempx,temptempy);
                for(int tempnod=1; tempnod<=A.n; tempnod++)
                {
                    if((temptempx-A.centru[tempnod].x)*(temptempx-A.centru[tempnod].x)+(temptempy-A.centru[tempnod].y)*(temptempy-A.centru[tempnod].y)<=40*40)
                    {
                        temptempok=1;
                        ////
                        setcolor(BLUE);
                        outtextxy(520, 150, "Selectati nodul din care doriti DF");
                        setcolor(WHITE);
                        char l[30],r[5];
                        strcpy(l,"DF din ");
                        itoa(tempnod,r,10);
                        strcat(l,r);
                        outtextxy(520, 150, l);
                        ////
                        DF(A,tempnod);
                        break;
                    }
                }
                if(500<=temptempx&&temptempx<=WINDOW_MAX_X-1&&WINDOW_MAX_Y-110<=temptempy&&temptempy<=WINDOW_MAX_Y-60)
                {
                    temptempok=1;
                }
            }
            goto startb;
        }
        if(500<=tempx&&tempx<=WINDOW_MAX_X-1&&175<=tempy&&tempy<=224) //4)
        {
            tempok=1;
            int  vizt[50];
            init(vizt);
            /////////////
            if(A.orientat==0)
            {
                int clr=1;
                for(int i = 1; i <= A.n; i++)
                    if(!vizt[i])
                    {
                        DFS(A,i,vizt,clr);
                        clr++;
                    }
            }
            else
            {
                int nrc=1, s[50], p[50];
                for(int i=1; i<=A.n; ++i)
                    if(vizt[i]==0)
                    {
                        for(int j=1; j<=A.n; ++j)
                            s[j]=p[j]=0;
                        nrc++;
                        DFStare(A,i,s,0);
                        DFStare(A,i,p,1);
                        for(int j=1; j<=A.n; ++j)
                            if(s[j]==1 && p[j]==1)
                                vizt[j]=nrc;
                    }
            }
            //////////
            setbkcolor(WHITE);
            settextstyle(GOTHIC_FONT,HORIZ_DIR,1);
            setcolor(BLACK);
            deseneaza_graf(A);
            ////
            setcolor(BLUE);
            rectangle(500,1,WINDOW_MAX_X-1, WINDOW_MAX_Y-1);
            setfillstyle(SOLID_FILL,BLUE);
            floodfill(502,4,BLUE);
            setcolor(WHITE);
            setbkcolor(BLUE);
            outtextxy((500+WINDOW_MAX_X-1)/2-50, 10,"MENU");
            setcolor(YELLOW);
            outtextxy((500+WINDOW_MAX_X-1)/2-50, WINDOW_MAX_Y-90, "INAPOI");
            ////
            for(int i=1; i<=A.n; i++)
            {
                setfillstyle(SOLID_FILL, vizt[i]);
                floodfill(A.centru[i].x-7, A.centru[i].y-7, BLACK);
            }
            ////
            int temptempok=0;
            while(temptempok==0)
            {
                while(!ismouseclick(WM_LBUTTONDOWN))
                    delay(10);
                int temptempx, temptempy;
                getmouseclick(WM_LBUTTONDOWN,temptempx,temptempy);
                if(500<=temptempx&&temptempx<=WINDOW_MAX_X-1&&WINDOW_MAX_Y-110<=temptempy&&temptempy<=WINDOW_MAX_Y-60)
                {
                    temptempok=1;
                }
            }
            goto startb;
            /////////////
        }
        if(500<=tempx&&tempx<=WINDOW_MAX_X-1&&225<=tempy&&tempy<=274) //5)
        {
            tempok=1;
            int ori;
            ///////////////
            setbkcolor(WHITE);
            setcolor(BLACK);
            cleardevice();
            settextstyle(GOTHIC_FONT,HORIZ_DIR,1);
            setcolor(BLACK);
            outtextxy(WINDOW_MAX_X/2-50, WINDOW_MAX_Y/2-50,"Orientat?");
            ///////////
            setcolor(BLUE);
            rectangle(WINDOW_MAX_X/2-250,WINDOW_MAX_Y/2+30,WINDOW_MAX_X/2,WINDOW_MAX_Y/2+130);
            setfillstyle(SOLID_FILL,BLUE);
            floodfill(WINDOW_MAX_X/2-50,WINDOW_MAX_Y/2+80,BLUE);
            setcolor(WHITE);
            setbkcolor(BLUE);
            outtextxy(WINDOW_MAX_X/2-200,WINDOW_MAX_Y/2+80,"ORIENTAT");
            setbkcolor(WHITE);
            ///////////
            setcolor(YELLOW);
            rectangle(WINDOW_MAX_X/2+10,WINDOW_MAX_Y/2+30,WINDOW_MAX_X/2+260,WINDOW_MAX_Y/2+130);
            setfillstyle(SOLID_FILL,YELLOW);
            floodfill(WINDOW_MAX_X/2+60,WINDOW_MAX_Y/2+80,YELLOW);
            setcolor(BLACK);
            setbkcolor(YELLOW);
            outtextxy(WINDOW_MAX_X/2+40,WINDOW_MAX_Y/2+80,"NEORIENTAT");
            setbkcolor(WHITE);
            ///////////
            int tempok=0;
            while(tempok==0)
            {
                while(!ismouseclick(WM_LBUTTONDOWN))
                    delay(10);
                int tempx, tempy;
                getmouseclick(WM_LBUTTONDOWN,tempx,tempy);
                if(tempx<=WINDOW_MAX_X/2&&tempx>=WINDOW_MAX_X/2-250&&tempy<=WINDOW_MAX_Y/2+130&&tempy>=WINDOW_MAX_Y/2+30)
                {
                    tempok=1;
                    ori=1;
                }
                if(tempx<=WINDOW_MAX_X/2+260&&tempx>=WINDOW_MAX_X/2+10&&tempy<=WINDOW_MAX_Y/2+130&&tempy>=WINDOW_MAX_Y/2+30)
                {
                    tempok=1;
                    ori=0;
                }
            }
            citeste_desen(A,ori);
            goto startb;
            /////////////
        }
        if(500<=tempx&&tempx<=WINDOW_MAX_X-1&&275<=tempy&&tempy<=325) //6)
        {
            tempok=1;
            ////////////
            system("cls");
            fin.close();
            setbkcolor(WHITE);
            cleardevice();
            settextstyle(GOTHIC_FONT,HORIZ_DIR,1);
            setcolor(BLACK);
            outtextxy(WINDOW_MAX_X/2-130, WINDOW_MAX_Y/2-50,"Puteti modifica graf.in");
            ///////////
            setcolor(GREEN);
            rectangle(WINDOW_MAX_X/2-125,WINDOW_MAX_Y/2+30,WINDOW_MAX_X/2+125,WINDOW_MAX_Y/2+130);
            setfillstyle(SOLID_FILL,GREEN);
            floodfill(WINDOW_MAX_X/2,WINDOW_MAX_Y/2+80,GREEN);
            setcolor(WHITE);
            setbkcolor(GREEN);
            outtextxy(WINDOW_MAX_X/2-50,WINDOW_MAX_Y/2+80,"GATA");
            setbkcolor(WHITE);
            ///////////
            int temptempok=0;
            while(temptempok==0)
            {
                while(!ismouseclick(WM_LBUTTONDOWN))
                    delay(10);
                int temptempx, temptempy;
                getmouseclick(WM_LBUTTONDOWN,temptempx,temptempy);
                if(temptempx<=WINDOW_MAX_X/2+125&&temptempx>=WINDOW_MAX_X/2-125&&temptempy<=WINDOW_MAX_Y/2+130&&temptempy>=WINDOW_MAX_Y/2+30)
                {
                    temptempok=1;
                }
            }
            ///////////
            fin.open("graf.in", std::fstream::in);
            setbkcolor(WHITE);
            setcolor(BLACK);
            cleardevice();
            goto start;
            ///////////
        }
        if(500<=tempx&&tempx<=WINDOW_MAX_X-1&&WINDOW_MAX_Y-90+25<=tempy&&tempy<=WINDOW_MAX_Y)   //IESIRE
        {
            return -1;
        }
    }

    return 0;
}
