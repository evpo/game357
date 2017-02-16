#include "game_intellect.h"
#include <algorithm>
#include <vector>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include "adapter_2003.h"

using namespace std;
using namespace Game357;

namespace
{
    // ************************************************************************************
    // DISCLAIMER:
    // The code below is of very low quality and has memory leaks.
    // It was written in 2003 and has historical value.
    // ************************************************************************************
    int piMaxLevel=1;

    void ZeroMemory(void *ptr, size_t size)
    {
        memset(ptr, 0, size);
    }

    class Element
    {
        public:
            void AddNextItem();
            Element* Prev;
            Element* Next;
            Element* Current[100];
            int BestPos[100]; //Оценка позиции
            int Levels[100]; //Кол-во уровней
            int Aindex;
            int Acount;
            char clState[100][18]; //Позиции
            Element();
            virtual ~Element();
    };

    Element::Element()
    {
        ZeroMemory(Levels,sizeof(int)*100);
        ZeroMemory(BestPos,sizeof(int)*100);
        ZeroMemory(clState,100*18);
        ZeroMemory(Current,sizeof(Element*)*100);
        Acount=Aindex=-1;
        Prev=0x0;
        Next=0x0;
    }

    Element::~Element()
    {

    }

    void Element::AddNextItem()
    {
        Acount++;
        Aindex=Acount;
    }

    //**********************************
    //* проверяет является ли ход правильным
    //* парам: строка, нач. клетека, длина многочлена 
    //* на выходе является ли это ходом или нет
    bool IsStep(char lcState[], int nBeg, int nRazm)
    {
        for(int i=nBeg;i<=nBeg+nRazm-1;i++)
        {
            if(lcState[i]!='0')
                return false;
        }

        return true;
    }

    int CalcSumSteps(char lcState[])
    {
        int liSumSteps=0,i=0;
        int nBegin=0,nEnd=0,N;
        char lmState[18];
        char *pos1;

        memcpy(lmState,lcState,18); 
        pos1=strstr(lmState,"0");

        while(pos1!=NULL)
        {
            nBegin=pos1-lmState;
            nEnd=nBegin;

            while(lmState[nEnd]=='0')
                nEnd++;

            memcpy(lmState,lmState+nEnd,18-nEnd);

            N=nEnd-nBegin;
            for(int j=0;j<N;j++)
                liSumSteps+=N-j;

            pos1=strstr(lmState,"0");
        }
        return liSumSteps;
    }

    bool tHreeChlen(int aCh[],int x1, int x2, int x3)
    {
        bool lbOther=false; 
        for(int i=1;i<=7;i++)
        {
            if(i!=x1 && i!=x2 && i!=x3 && aCh[i]>0)
                lbOther=true;
        }

        if(aCh[x1]==1 && aCh[x2]==1 && aCh[x3]==1 && lbOther==false)
            return true;

        return false;
    }

    //*********************************************
    //анализ ситуации, на выходе количество баллов
    int Analiz(char lcState[])
    {
        int aChlen[8];
        int liRazm=0,i;
        bool lbMchlen,lbmChetnoe,lbOther;

        for(i=0;i<=7;i++)
            aChlen[i]=0;

        i=0;
        while(i<=17)
        {
            if(lcState[i]=='0')
            {
                //посчитаем размерность
                liRazm=0;
                while(lcState[i]=='0')
                {
                    liRazm++;
                    i++;
                }
                aChlen[liRazm]++;
            }
            i++;
        }

        /*
           проверка на осуществление 1го правила: 
           1. Оставлять после своего хода нечетное количество одночленов и ни одного многочлена.
           1.1. Если есть один многочлен и несколько одночленов, то нужно закрыть столько клеток этого многочлена,
           чтобы осталось только нечетное количество одночленов.
         */

        lbMchlen=true;
        for(i=2;i<=7;i++)
        {
            if(aChlen[i]>0)
                lbMchlen=false;
        }

        if(aChlen[1]>0 && (float)aChlen[1]/2!=ceil((float)aChlen[1]/2) && lbMchlen==true) //если нечетное и нету многочленов
            return 10;

        /*
           проверка на осуществление 2го правила
           2. Оставлять после своего хода только два многочлена (2-2,3-3,4-4) (5-5?)
           2.1. Всю строчку сразу закрывать нельзя _при первом ходе_
           2.2. В _первый ход_ нельзя закрывать две правые клетки в нижнем ряду
         */
        lbmChetnoe=false;
        lbOther=false;
        for(i=2;i<=5;i++)
        {
            if(aChlen[i]==2)
            {
                lbmChetnoe=true;
                lbOther=false; //другие многочлены, кроме i-тых есть
                for(int iOther=2;iOther<=7;iOther++)
                {
                    if(aChlen[iOther]>0 && iOther!=i)
                    {
                        lbOther=true;
                        break;
                    }
                }
                if(lbOther==false)
                    break;
            }
        }

        if(aChlen[1]==0 && lbmChetnoe==true && lbOther==false)
            return 8;

        if(aChlen[1]>0 && (float)aChlen[1]/2==ceil((float)aChlen[1]/2) && lbmChetnoe==true && lbOther==false) //третье правило действует
            return 6;

        /*
           проверка на осуществление 3го правила   
           3. Оставлять четное колво многочленов одинак длины и четное колво одночленов
           для отладки
         */
        lbmChetnoe=false;
        lbOther=false;

        double fTemp;
        for(i=2;i<=5;i++)
        {
            if(aChlen[i]!=0 && (float)aChlen[i]/2==ceil((float)aChlen[i]/2))
            {
                lbmChetnoe=true; // есть четное кол-во какого-либо вида многочленов
                lbOther=false;
                for(int j=2;j<=7;j++)
                {
                    if(aChlen[j]>0 && j!=i)
                    {
                        //Если другие многочлены есть и их нечетное кол-во
                        if((float)aChlen[j]/2!=ceil((float)aChlen[j]/2))
                            lbOther=true; //другие многочлены, кроме i-тых есть
                        break;
                    }
                }
                if(lbOther==false) //Если других многочленов нет
                    break;
            }
        }

        //если ни одного одночл. тоже сработает
        if((float)aChlen[1]/2==ceil((float)aChlen[1]/2) && lbmChetnoe==true && lbOther==false)
            return 6;

        //правило x1-x2-x3
        //*****************
        if(tHreeChlen(aChlen,1,2,3) || tHreeChlen(aChlen,1,5,4))
            return 7;
        if(tHreeChlen(aChlen,3,4,7) || tHreeChlen(aChlen,2,5,7) || tHreeChlen(aChlen,3,5,6) || tHreeChlen(aChlen,2,4,6))
            return 4;

        //в остальных случаях
        return 0;
    }

    //*********************************************
    //*записывает в объект класса element все возможные ходы с их анализом
    //*вход: позиция; выход: элемент
    Element *StrToElem(char lcState[])
    {
        Element *loObj,*loEl;
        int liSumSteps,liRazm,i;
        char loState[18];
        bool ttt;
        static int riLevel=0;

        riLevel++;
        loObj=new(Element);
        liSumSteps=CalcSumSteps(lcState);

        liRazm=1;
        while(liRazm<=7)
        {
            i=0;
            while(i<=16-liRazm+1)
            {
                if(IsStep(lcState,i,liRazm)==true)
                {
                    ZeroMemory(loState,18);

                    memcpy(loState,lcState,i);
                    memset(loState+i,'1',liRazm);
                    memcpy(loState+i+liRazm,lcState+i+liRazm,18-(i+liRazm+1));

                    loObj->AddNextItem();
                    memcpy(loObj->clState[loObj->Acount],loState,18);
                    loObj->BestPos[loObj->Acount]=Analiz(loState);
                    if(riLevel<=piMaxLevel && CalcSumSteps(loState)!=0) //макс уровень или нет больше ходов
                    {
                        loEl=StrToElem(loState);
                        loEl->Prev=loObj;
                        loObj->Current[loObj->Acount]=loEl;
                    }
                }
                i++;
            }
            liRazm++;
        }
        riLevel--;
        return loObj;           
    }

    int GetBestStep(Element *poObj)
    {
        int liMax=-100,liCountMaxElem,liRandSelect,liCurMaxElem;

        int i = 0;
        for(i=0;i<=poObj->Acount;i++)
        {
            if(poObj->BestPos[i]>liMax)
                liMax=poObj->BestPos[i];
        }

        liCountMaxElem=0;
        for(i=0;i<=poObj->Acount;i++)
        {
            if(poObj->BestPos[i]==liMax)
            {
                liCountMaxElem++;
                //return i;
            }
        }

        //Если максимальных элементов несколько, то выбираем случайно
        srand( (unsigned)time( NULL ) );
        // liRandSelect = rand() % liCountMaxElem;
        liRandSelect=ceil((liCountMaxElem-1)*rand());
        liRandSelect=liRandSelect/RAND_MAX+1;

        liCurMaxElem=0;
        for(i=0;i<=poObj->Acount;i++)
        {
            if(poObj->BestPos[i]==liMax)
                liCurMaxElem++;
            if(liCurMaxElem==liRandSelect)
                return i;
        }

        return -1;
    }

    //*********************************************
    //*делает ход, преобразует переданную строку
    //*на выходе преобразованная строка
    void DoStep(char lcState[])
    {
        Element *loAnal,*loGlobAnal,*loCurElem;
        bool lbCompStep;
        char *lcRet;
        char cState[18];

        int liBestStep=0,nSum;

        lcRet=cState;

        loAnal=StrToElem(lcState);
        loGlobAnal=new(Element);

        for(int i=0;i<=loAnal->Acount;i++)
        {
            loGlobAnal->AddNextItem();
            strcpy((char*)loGlobAnal->clState+i*18,(char*)loAnal->clState+i*18);
            loGlobAnal->BestPos[i]=loAnal->BestPos[i];
            loGlobAnal->Levels[i]=1; //теперь это количество уровней

            //собираем сумму по всем веткам в loGlobAnal
            loCurElem=loAnal->Current[i];
            lbCompStep=true;
            while(loCurElem!=0x0)
            {
                lbCompStep=!lbCompStep;
                liBestStep=GetBestStep(loCurElem);

                if(lbCompStep==false)
                    nSum=-loCurElem->BestPos[liBestStep];
                else
                    nSum=loCurElem->BestPos[liBestStep];

                loGlobAnal->BestPos[i]=loGlobAnal->BestPos[i]+nSum;
                loGlobAnal->Levels[i]++;
                loCurElem=loCurElem->Current[liBestStep];
            }
        }

        //усредняем суммы баллов в loGlobAnal
        for(int i=0;i<=loGlobAnal->Acount;i++)
            loGlobAnal->BestPos[i]=loGlobAnal->BestPos[i]/loGlobAnal->Levels[i];
        memcpy(lcRet,loGlobAnal->clState[GetBestStep(loGlobAnal)],18);
        memcpy(lcState, lcRet, 18);
        return;
    }
}

namespace Game357
{
    //*********************************************
    //*делает ход, преобразует переданную строку
    //*на выходе преобразованная строка
    std::tuple<CellStatesIt, CellStatesIt> FindBestMove(GameState &game_state)
    {
        State2003 buffer = ConvertTo2003(game_state);
        DoStep(buffer.data());
        return FindNewMove(game_state, buffer);
    }
}
