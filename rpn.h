#ifndef RPNLIB_H_INCLUDED
#define RPNLIB_H_INCLUDED

#include <cmath>

using std::string;



//����ת��
void convert(V_Stack<char> & S,long long i, int base)   //��ĳ��������ת��Ϊĳ�����Ƶ���
{
    static char digit[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};    // X % 8 = 0~7ĳ����
    while (i > 0)   //���һ��ȡ�����0
    {
        S.push(digit[i % base]);   //������ѹ��ջ��
        i /= base;
    }
    return;
}


//ջ��ϴ - �ж�һ��ջ�е������Ƿ�����ջ��ϴ



//����ƥ��
bool paren(const char exp[],int lo,int hi)  //�ж�һ���ַ������Ƿ�����ƥ�� - ��������[]/{}/()
{
    V_Stack<char> S;                //������ջ��
    for(int i = lo; i < hi; ++i)    //[lo,hi)
    {
        switch(exp[i])
        {
            case '{' : case '[' : case '(' : S.push(exp[i]); break;
            case ')' : if ((S.IsEmpty()) || ('(' != S.pop())) return false; break;  //��ǰջΪ�ջ���ջ��Ԫ�ز����������ǿ϶���ƥ��
            case ']' : if ((S.IsEmpty()) || ('[' != S.pop())) return false; break;
            case '}' : if ((S.IsEmpty()) || ('{' != S.pop())) return false; break;

            default: break;     //��Ŀ���ַ�һ�ɺ���
        }
    }
    return false;
}






//��׺������ļ���
typedef enum {ADD, SUB, MUL, DVI, POW, FAC, L_P, R_P, EOE} Optr;    //���������
#define N_OPTR 9        //������ĸ���

const char pri[N_OPTR][N_OPTR] = {  //����������ȵȼ�[ջ��][��ǰ]

    /*          --- ��   ǰ   ��   ��   ��       -------  */
    /*          +     -     *   /    ^    !    (    )   \0*/
    /* -  + */  '>', '>', '<', '<', '<', '<', '<', '>', '>',

    /* |  - */  '>', '>', '<', '<', '<', '<', '<', '>', '>',

    /* ջ * */  '>', '>', '>', '>', '<', '<', '<', '>', '>',

    /* �� / */  '>', '>', '>', '>', '<', '<', '<', '>', '>',

    /* �� ^ */   '>', '>', '>', '>', '>', '<', '<', '>', '>',

    /* �� ! */   '>', '>', '>', '>', '>', '>', ' ', '>', '>',

    /* �� ( */   '<', '<', '<', '<', '<', '<', '<', '=', ' ',

    /* |  ) */   ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',

    /* -  \0*/   '<', '<', '<', '<', '<', '<', '<', ' ', '=',
};

//��׺���ʽ�ļ��㺯�����沨�����ʽ�ļ���

void readNumber(char* & S,V_Stack<double> & opnd);                //����ǰ�����������ջ��
void append(string & RPN,double opnd);                           //RPN���ʽ�����������
void append(string & RPN,char oper);                             //RPN���ʽ����������
double calcu(const char oper,int opnd);                          //��Ŀ������ļ��� - ����ֻ�漰�׳�,�ʲ�������
double calcu(double f_opnd,const char oper,double b_opnd);      //˫Ŀ������ļ���
char orderBetween(const char,const char);                       //ջ��������͵�ǰ������ıȽ�




double evaluate(char * S,string & RPN){  //��S�ַ������д���,����S�ַ���ת����һ���沨�����ʽ
    V_Stack<double> opnd;//��������ջ
    V_Stack<char> optr;  //�������ջ

    optr.push('\0');    //�����ջ�ĳ�ʼ��,��'\0'��ջ��(��ʽ������)




    while (!optr.IsEmpty()){        //�����ջ�ǿ�֮ǰ�����ݽ��д��� -- ֻ��ɨ�赽�ַ�����ĩβ'\0'ʱ�Ż��մӶ���ֹ����

        if(isdigit( *S ))           //��ǰɨ���ַ�Ϊ������ʱ - ��������ջ
        {
            readNumber(S,opnd);     //������ջ�ӿ�       --- δʵ��
            //std::cout << "s" << std::endl;
            append(RPN,opnd.top()); //�沨�������ʽ����׺���ʽ���Ĳ�������ջ�ӿ�    --- δʵ��
        }
        else    //Ϊ������ʱ
        {

            switch( orderBetween(optr.top(),*S) )   //�ȽϽӿڷ���һ���Ƚ��ַ� -- ���������ַ������ - ջ���ַ��뵱ǰ�ַ����бȽ�     --- δʵ��
            {
                case '<' :  //ջ����������ȼ�С�ڵ�ǰ��������ȼ� - ��ǰ�������ջ
                    {
                        optr.push(*S);  //�Ƴټ���,��ǰ�������ջ
                        S++;            //�ַ���ָ���ƶ�
                    }
                break;

                case '=' :  //ֻ��'('����')'����'\0'����'\0' - ��ʾ�����������еĲ����������
                    {
                        optr.pop(); //ջ�����������������ջ
                        S++;       //������һԪ��
                    }
                break;

                case '>' :  //ջ����������ڵ�ǰɨ�赽�������ʱ - ��ջ����������а��������ʼ���
                    {
                        char op = optr.pop();   //��ջ����
                        append(RPN,op);         //�沨�����ʽ����׺���ʽ�����������ջ  --- δʵ��

                        //�Դ�����������ж�
                        if (op == '!')    //�ǵ�Ŀ�ģ�
                        {
                            double p_opnd = opnd.pop();     //��������ջ����
                            opnd.push( calcu(op,p_opnd) );  //����������ѹ�������ջ��  -- calcu����     --- δʵ��
                        }
                        else              //˫Ŀ�����
                        {
                            double b_opnd = opnd.pop(), f_opnd = opnd.pop();  //ȡ����ǰ������
                            opnd.push( calcu(f_opnd,op,b_opnd) );             //������ѹ�������ջ��     --- δʵ��
                        }
                    }
                break;

                default:
         void append(char* & RPN,char oper);            exit(-1);   //ɨ�赽����������﷨����ֱ���˳���ǰ����
            }//switch


        }



    }//while

    return opnd.pop();          //���������ص�ǰ������
}


//����������ʵ��

//��������--------------------------------------------
void readNumber(char* &S,V_Stack<double> & opnd)
{
    opnd.push(double(*S - '0'));    //��ǰ�Ķ����������ջ
    while( isdigit(*++S))           //��ǰ�����Ԫ��������ʱ
    {
        opnd.push( opnd.pop() * 10 + (*S - '0') );  //����ջ�����ֳ�ջ����10�������̵�Ԫ��
    }

    if(*S != '.') return;           //��ǰ���ַ�����С����Ҳ��������ʱ,˵���Ѿ�������ǰ��������ĩβ,ֱ�ӷ���

    //��С����ʱ,������������ʱ -- ���ǵ����̲���ÿ�ζ�����10���ǳ���0.1/0.01/0.001��
    double k = 1;                   //С�����ֵ�ϵ��
    while( isdigit( * (++S) ) )     //��λ����
    {
        opnd.push( opnd.pop() + (*S - '0') * (k /= 10) );   //�漰���ַ�ת����
    }
    return;
}

void read_rpn(string::iterator i, V_Stack<double> & opnd)
{

    return;
}


//RPN���ʽ���ַ�������Ӻ���------------------------
void append(string & RPN,double opnd)    //�������ַ������
{
    char buf[64];
    if (opnd != (double)(int)opnd)       //��������С������
        sprintf(buf,"%.2f ",opnd);
    else                                 //��������С������
        sprintf(buf,"%d ",int(opnd));

    RPN.append(buf);                    //string���append����
    return;
}
void append(string & RPN,char oper)
{
    char buf[5];
    sprintf(buf,"%c ",oper);
    RPN.append(buf);
    return;
}

//calcu���㺯��------------------------------------
double calcu(const char oper,int opnd)
{
    int result = 1;
    while (opnd > 1)
    {
        result *= opnd;
        opnd--;
    }
    return result;
}

double calcu(double f_opnd,const char oper,double b_opnd)
{
    switch(oper)
    {
        case '+' : return f_opnd + b_opnd;
        break;
        case '-' : return f_opnd - b_opnd;
        break;
        case '*' : return f_opnd * b_opnd;
        break;
        case '/' : return f_opnd / b_opnd;
        break;
        default  :  return pow(f_opnd,b_opnd);
        //����ֻ��^
    }
}


//orderBetween()����

Optr optr_to_rank(char op)  //�������ת���������������ϵ�λ�� -- ��ת������������λ��
{
    switch(op)
    {
        case '+' : return ADD;
        case '-' : return SUB;
        case '*' : return MUL;
        case '/' : return DVI;
        case '^' : return POW;
        case '!' : return FAC;
        case '(' : return L_P;
        case ')' : return R_P;
        case '\0': return EOE;  //��ʼ������ֹ��
        default : exit(-1);     //����������ֹ����
    }
}




char orderBetween(const char c_top,const char c_now)
{
    return pri[optr_to_rank(c_top)][optr_to_rank(c_now)];   //ջ��������͵�ǰ������ıȽ�
}





#endif // RPNLIB_H_INCLUDED
