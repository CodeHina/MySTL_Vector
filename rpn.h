#ifndef RPNLIB_H_INCLUDED
#define RPNLIB_H_INCLUDED

#include <cmath>

using std::string;



//进制转换
void convert(V_Stack<char> & S,long long i, int base)   //将某个正整数转换为某个进制的数
{
    static char digit[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};    // X % 8 = 0~7某个数
    while (i > 0)   //最后一次取余会变成0
    {
        S.push(digit[i % base]);   //将余数压入栈中
        i /= base;
    }
    return;
}


//栈混洗 - 判断一个栈中的数字是否满足栈混洗



//括号匹配
bool paren(const char exp[],int lo,int hi)  //判断一个字符数组是否括号匹配 - 三种括号[]/{}/()
{
    V_Stack<char> S;                //储存在栈中
    for(int i = lo; i < hi; ++i)    //[lo,hi)
    {
        switch(exp[i])
        {
            case '{' : case '[' : case '(' : S.push(exp[i]); break;
            case ')' : if ((S.IsEmpty()) || ('(' != S.pop())) return false; break;  //当前栈为空或者栈顶元素不是左括号是肯定不匹配
            case ']' : if ((S.IsEmpty()) || ('[' != S.pop())) return false; break;
            case '}' : if ((S.IsEmpty()) || ('{' != S.pop())) return false; break;

            default: break;     //非目标字符一律忽略
        }
    }
    return false;
}






//中缀运算符的计算
typedef enum {ADD, SUB, MUL, DVI, POW, FAC, L_P, R_P, EOE} Optr;    //运算符集合
#define N_OPTR 9        //运算符的个数

const char pri[N_OPTR][N_OPTR] = {  //运算符的优先等级[栈顶][当前]

    /*          --- 当   前   运   算   符       -------  */
    /*          +     -     *   /    ^    !    (    )   \0*/
    /* -  + */  '>', '>', '<', '<', '<', '<', '<', '>', '>',

    /* |  - */  '>', '>', '<', '<', '<', '<', '<', '>', '>',

    /* 栈 * */  '>', '>', '>', '>', '<', '<', '<', '>', '>',

    /* 顶 / */  '>', '>', '>', '>', '<', '<', '<', '>', '>',

    /* 运 ^ */   '>', '>', '>', '>', '>', '<', '<', '>', '>',

    /* 算 ! */   '>', '>', '>', '>', '>', '>', ' ', '>', '>',

    /* 符 ( */   '<', '<', '<', '<', '<', '<', '<', '=', ' ',

    /* |  ) */   ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',

    /* -  \0*/   '<', '<', '<', '<', '<', '<', '<', ' ', '=',
};

//中缀表达式的计算函数及逆波兰表达式的计算

void readNumber(char* & S,V_Stack<double> & opnd);                //将当前数读入操作数栈中
void append(string & RPN,double opnd);                           //RPN表达式操作数的添加
void append(string & RPN,char oper);                             //RPN表达式运算符的添加
double calcu(const char oper,int opnd);                          //单目运算符的计算 - 这里只涉及阶乘,故采用整数
double calcu(double f_opnd,const char oper,double b_opnd);      //双目运算符的计算
char orderBetween(const char,const char);                       //栈顶运算符和当前运算符的比较




double evaluate(char * S,string & RPN){  //对S字符串进行处理,并将S字符串转换成一个逆波兰表达式
    V_Stack<double> opnd;//操作数的栈
    V_Stack<char> optr;  //运算符的栈

    optr.push('\0');    //运算符栈的初始化,用'\0'做栈底(隐式的括号)




    while (!optr.IsEmpty()){        //运算符栈非空之前对数据进行处理 -- 只有扫描到字符串的末尾'\0'时才会变空从而中止运算

        if(isdigit( *S ))           //当前扫描字符为操作数时 - 操作数进栈
        {
            readNumber(S,opnd);     //读数进栈接口       --- 未实现
            //std::cout << "s" << std::endl;
            append(RPN,opnd.top()); //逆波兰数表达式（后缀表达式）的操作数进栈接口    --- 未实现
        }
        else    //为操作符时
        {

            switch( orderBetween(optr.top(),*S) )   //比较接口返回一个比较字符 -- 根据上述字符表得来 - 栈顶字符与当前字符进行比较     --- 未实现
            {
                case '<' :  //栈顶运算符优先级小于当前运算符优先级 - 当前运算符进栈
                    {
                        optr.push(*S);  //推迟计算,当前运算符进栈
                        S++;            //字符串指针移动
                    }
                break;

                case '=' :  //只有'('遇到')'或者'\0'遇到'\0' - 表示被这两者所夹的部分运算完毕
                    {
                        optr.pop(); //栈顶的这两种运算符出栈
                        S++;       //考察下一元素
                    }
                break;

                case '>' :  //栈顶运算符高于当前扫描到的运算符时 - 对栈顶运算符进行按照其性质计算
                    {
                        char op = optr.pop();   //出栈保存
                        append(RPN,op);         //逆波兰表达式（后缀表达式）的运算符进栈  --- 未实现

                        //对此运算符进行判断
                        if (op == '!')    //是单目的！
                        {
                            double p_opnd = opnd.pop();     //操作数出栈保存
                            opnd.push( calcu(op,p_opnd) );  //将计算结果再压入操作数栈中  -- calcu函数     --- 未实现
                        }
                        else              //双目运算符
                        {
                            double b_opnd = opnd.pop(), f_opnd = opnd.pop();  //取出后、前操作数
                            opnd.push( calcu(f_opnd,op,b_opnd) );             //计算结果压入操作数栈中     --- 未实现
                        }
                    }
                break;

                default:
         void append(char* & RPN,char oper);            exit(-1);   //扫描到非运算符的语法错误直接退出当前程序
            }//switch


        }



    }//while

    return opnd.pop();          //弹出并返回当前计算结果
}


//辅助函数的实现

//读数函数--------------------------------------------
void readNumber(char* &S,V_Stack<double> & opnd)
{
    opnd.push(double(*S - '0'));    //当前的读入的数字入栈
    while( isdigit(*++S))           //当前读入的元素是数字时
    {
        opnd.push( opnd.pop() * 10 + (*S - '0') );  //将入栈的数字出栈乘以10加上其后继的元素
    }

    if(*S != '.') return;           //当前的字符不是小数点也不是数字时,说明已经读到当前操作数的末尾,直接返回

    //是小数点时,当其后继是数字时 -- 考虑到其后继不是每次都乘以10而是乘以0.1/0.01/0.001等
    double k = 1;                   //小数部分的系数
    while( isdigit( * (++S) ) )     //逐位加入
    {
        opnd.push( opnd.pop() + (*S - '0') * (k /= 10) );   //涉及到字符转数字
    }
    return;
}

void read_rpn(string::iterator i, V_Stack<double> & opnd)
{

    return;
}


//RPN表达式的字符串的添加函数------------------------
void append(string & RPN,double opnd)    //操作数字符的添加
{
    char buf[64];
    if (opnd != (double)(int)opnd)       //操作数有小数部分
        sprintf(buf,"%.2f ",opnd);
    else                                 //操作数无小数部分
        sprintf(buf,"%d ",int(opnd));

    RPN.append(buf);                    //string类的append函数
    return;
}
void append(string & RPN,char oper)
{
    char buf[5];
    sprintf(buf,"%c ",oper);
    RPN.append(buf);
    return;
}

//calcu计算函数------------------------------------
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
        //或者只是^
    }
}


//orderBetween()函数

Optr optr_to_rank(char op)  //由运算符转译出其在运算符集合的位置 -- 再转至运算符数组的位置
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
        case '\0': return EOE;  //起始符和终止符
        default : exit(-1);     //其他符号终止程序
    }
}




char orderBetween(const char c_top,const char c_now)
{
    return pri[optr_to_rank(c_top)][optr_to_rank(c_now)];   //栈顶运算符和当前运算符的比较
}





#endif // RPNLIB_H_INCLUDED
