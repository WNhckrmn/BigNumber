#include <iostream>
#include <cstring>
#include <fstream>
#include <ctime>

typedef unsigned short int BASE;
#define BAZE_SIZE (sizeof(BASE) * 8)//размер типа BASE в битах

using namespace std;

class BigNum
{
    BASE *coef;
    int len;            //Число используемых коэфициентов
    int max_len;        //выделенная память
public:
    BigNum()
    {  
        max_len = 1; 
        len = max_len;
        coef = new BASE[max_len];
        coef[0]=0;
    }

    BigNum(int maxlen, int k )
    {
        max_len = maxlen;
        if( k == 1)
        {
            len = 1;
            coef = new BASE[maxlen];
            memset(coef,0,max_len);
        }
        if(k == 2)
        {
            coef = new BASE[max_len];
            len = max_len;
            for(int i = 0; i < len; i++)
            {
                coef[i] = rand();
            }
        }
    }

    BigNum(const BigNum& arr)
    {
        max_len = arr.max_len;
        len = arr.len;
        coef = new BASE[max_len];
        for (int i = 0; i < max_len; i++)
        {
            coef[i]=arr.coef[i];
        }
    }

    ~BigNum()
    {
        delete[]coef;
    }

    BigNum& operator =(const BigNum& arr)
    {
        if(this != &arr)//при каком присваивании это условие не выполняется
        {
            if(coef != nullptr)
            {
                delete[] coef;
            }

            len=arr.len;
            max_len = arr.max_len;
            coef = new BASE [max_len];
            for (int i = 0; i < max_len; i++)
            {
                coef[i]=arr.coef[i];
            }
        }
        
        return *this;
    }

    int printNum16 ()
    {
        // int k = BAZE_SIZE - 4;
        // int tmp = 0;
        // int i = 0;
        // char* str = new char [((len-1)*BAZE_SIZE*4)+1];
        // // while (j >= 0)
        // // {
        // //     tmp = (coef[j] >> k ) & (0xf);
        // //     if (0<=tmp<=9)
        // //     {
        // //         str[i] = tmp + '0';
        // //     }
        // //     else if(10<=tmp<=15)
        // //     {
        // //         str[i] = tmp - 10 + 'a';
        // //     }
        // //     i++;
        // //     k-=4;
        // //     if (k < 0)
        // //     {
        // //         j--;
        // //         k = BAZE_SIZE - 4; 
        // //     }
        // // }
        // for(int j = len; j>=0; j--)
        // {
        //     while(k > 0)
        //     {
        //         tmp = (coef[j] >> k ) & (0xf);
        //         if (0<=tmp<=9)
        //         {
        //             str[i] = tmp + '0';
        //         }
        //         else if(10<=tmp<=15)
        //         {
        //             str[i] = tmp - 10 + 'a';
        //         }
        //         else
        //         {
        //             cout<<"Некорректное большое число"<<endl;
        //         }
        //         i++;
        //         k-=4;
        //     }
        //     k = BAZE_SIZE - 4;
        // }
        //return str;
        // for (int j = ; j >= 0; j--)
        // {
        //     cout.width(BAZE_SIZE/4);
        //     cout.fill('0');
        //     cout<<hex<<coef[j];
        // }
        // for(int i = strlen(str)-1;i>=0;i--)
        // {
        //     cout<<str[i];
        // }
        // cout<<endl;
        for (int i = len-1; i >= 0 ; i--)
        {
            cout.width(BAZE_SIZE/4);
            cout.fill('0');
            cout<<hex<<coef[i];
        }
        
        cout<<dec<<endl;
        return 1;
    }

    BigNum inputNum16(const char* str)
    {
        int j = 0;
        int k = 0;
        max_len = (strlen(str) - 1)/(BAZE_SIZE/4)+1;
        len = max_len;
        delete[]coef;
        coef=new BASE[max_len];
        memset(coef,0,BAZE_SIZE);
        int tmp = 0;
        for (int i = strlen(str) - 1; i >= 0; i--)
        {
    
            if( k >= (BAZE_SIZE / 4))
            {
                k = 0;
                j++;
            }

            if(('0'<=str[i])&&(str[i]<='9'))
            {
                tmp = str[i] - '0';
            }
            else if(('a'<=str[i])&&(str[i]<='f'))
            {
                tmp = str[i]-'a' + 10;
            }
            else if (('A'<=str[i])&&(str[i]<='F'))
            {
                tmp = str[i] - 'A' + 10;
            }
            else
            {
                cout<<"Некорректная строка"<<endl;
               // return 0;//прописать ошибку
            }
            coef[j]|=(tmp << (k*4));
            k++;
            //нужен len_norm!!!//сделать проверку ввода-вывода
        }
        return *this;
    }

    int cmp_BigNum(const BigNum& num)//сдедлать перегрузку операторов << && >>
    {
        if (len > num.len)
        {
            return 1;
        }

        if(len < num.len)
        {
            return -1;
        }
        
        for(int i = len; i >= 0; i--)
        {
            if(num.coef[i]>coef[i])
            {
                return -1;
            }

            if(num.coef[i] < coef[i])
            {
                return 1;
            }
        }
        
        return 0;
    }
};


int main()
{
    srand(time(NULL));
    BigNum num1;
    BigNum num2;
    num1.inputNum16("111111");
    num2.inputNum16("111111");
    int res = num1.cmp_BigNum(num2);
    cout<< res<<endl;
    num1.printNum16();
    num2.printNum16();
    return 0;
}

