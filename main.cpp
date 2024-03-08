// @@@         @@@        @
//@   @       @   @       @        TM
//@      @@@  @      @@@  @   @@@
//@ @@@ @   @ @         @ @  @   @
//@   @ @@@@@ @      @@@@ @  @
//@   @ @     @   @ @   @ @  @   @   by T0astForeveR & Faver
// @@@   @@@@  @@@   @@@@  @  @@@    (c) MMXXIV

#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cfloat>
#include <cstdlib>
#include <random>
#include <windows.h>
#include <cstring>

const std::string ver = "0.2.3";
const std::string build = "202403081";

time_t timeStamp = time(nullptr);

double x1, x2, prevResult = DBL_MAX; //Solutions to quadratic equation, floating numbers.
int luckinessLevel, crossSolveResult[2][2]={{0, 0}, {0, 0}}; //Cross-solve solutions to quadratic equation, floating numbers.
bool luckiness = false;

static std::string luckinessCall(const int callLevel){
    if(100 == callLevel) return "Supercalifragilisticexpialidocious!";
    if(95 < callLevel) return "Incredible!";
    if(90 < callLevel) return "Excellent!";
    if(85 < callLevel) return "Fantastic!";
    if(80 < callLevel) return "Fabulous!";
    if(75 < callLevel) return "Wonderful!";
    if(70 < callLevel) return "Superior!";
    if(65 < callLevel) return "Decent~";
    if(60 < callLevel) return "Fine~";
    if(50 < callLevel) return "Acceptable";
    if(30 < callLevel) return "Not That Bad...";
    if(0 < callLevel) return "Misfortunate...";
    if(0 == callLevel) return "God Bless You...";
    return "This should not happen......";
}

static void vPrint(const std::vector<double>& vec){   //Vector printing, used for debugging
    for(double i : vec) printf("%lf ", i);
    printf("\n");
}

static void ePrint(double a,double b,double c){    //Equation printing
    printf("%lfx ^ 2 ",a);
    if(b>0) printf("+ %lfx ",b);
    else if(b<0) printf("- %lfx ",-b);
    if((b==0&&c==0)||c==0) printf("= 0\n");
    else if(c>0) printf("+ %lf = 0\n",c);
    else if(c<0) printf("- %lf = 0\n",-c);
}

static void quadEquationSolve(double a,double b,double c){
    double d=pow(b,2)-4*a*c;
    x1=(-b+std::sqrt(d))/2*a;
    x2=(-b-std::sqrt(d))/2*a;
}

static void crossSolve(int a,int b,int c){
    for(int i=-abs(int(std::sqrt(a)));i<=abs(int(std::sqrt(a)));i++){
        if((i!=0)&&(a%i==0)){
            for(int j=-abs(c);j<=abs(c);j++){
                if((j!=0)&&(c%j==0)){
                    if(i*(c/j)+j*(a/i)==b){
                        crossSolveResult[0][0]=i;
                        crossSolveResult[0][1]= a / i;
                        crossSolveResult[1][0]=j;
                        crossSolveResult[1][1]= c / j;
                        break;
                    }
                }
            }
        }
    }
}

static void clearScreen() {
    system("CLS");
    //printf("----------------------------------\n");
}

static void init(){    //Initializing splash
    clearScreen();
    printf(" @@@         @@@        @          \n");
    printf("@   @       @   @       @        TM\n");
    printf("@      @@@  @      @@@  @   @@@    \n");
    printf("@ @@@ @   @ @         @ @  @   @   \n");
    printf("@   @ @@@@@ @      @@@@ @  @       \n");
    printf("@   @ @     @   @ @   @ @  @   @   \n");
    printf(" @@@   @@@@  @@@   @@@@  @  @@@    \n");
    printf("----------------------------------\n");
    printf("General Calculator by T0astForeveR & Faver\nVersion %s\tBuild %s\tSystemTime %lld\n", ver.c_str(), build.c_str(), timeStamp);
    Sleep(1500);
    clearScreen();
}

static void about(){   //About page
    clearScreen();
    printf(" @@@         @@@        @          \n");
    printf("@   @       @   @       @        TM\n");
    printf("@      @@@  @      @@@  @   @@@    \n");
    printf("@ @@@ @   @ @         @ @  @   @   \n");
    printf("@   @ @@@@@ @      @@@@ @  @       \n");
    printf("@   @ @     @   @ @   @ @  @   @   \n");
    printf(" @@@   @@@@  @@@   @@@@  @  @@@    \n");
    printf("----------------------------------\n");
    printf("General Calculator by T0astForeveR & Faver\nVersion %s\tBuild %s\tSystem Time %lld\n", ver.c_str(), build.c_str(), timeStamp);
    printf("----------------------------------\n");
    printf("CrossSolve - by Faver @ https://space.bilibili.com/501018696\n");
    printf("C++ Coding - by T0astForeveR @ https://space.bilibili.com/225255578\n");
    printf("----------------------------------\n");
    printf("Project URL - https://github.com/EDU-Group/GeCalc\n");
    printf("This calculator follows CC BY-SA 4.0 license.\n");
    system("pause");
}

static double deg2rad(double a){   //Angle to radian
    const double PI = 3.14159265;
    return a*PI/180;
}

static bool isInt(double a){
    double b = pow(10,-6.0);
    if((a-(int)a<b) && (a-(int)a>-b)) return true;
    else return false;
}

static bool isSquare(double a){
    return std::sqrt(a)*std::sqrt(a) == a;
}

static double variance(const std::vector<double>& data){
    double accumulate = 0;
    for(double i : data) accumulate += i;
    double m = 0, average = accumulate / (double)data.size();
    for(double i : data) m += pow(i-average,2);
    return m / (double)data.size();
}

static void bubbleSort(std::vector<double>& data){
    for(int i=(int)data.size()-1;i>0;i--)
        for(int j=0;j<i;j++)
            if (data[j]>data[static_cast<std::vector<double, std::allocator<double>>::size_type>(j) + 1]) std::swap(data[j], data[static_cast<std::vector<double, std::allocator<double>>::size_type>(j) + 1]);
}

static double median(std::vector<double>& oriData){
    std::vector<double> data(oriData.begin(),oriData.end());
    bubbleSort(data);
    if(data.size()%2==0) return ((data[data.size()/2-1]+data[data.size()/2])/2);
    else return data[(data.size()+1)/2-1];
}

int main() {
    init();
    while(1){
        if(luckiness)
            printf(">>\n\n"

                   "Enter calculation type\n"
                   "> 1 | arithmetics\n"
                   "> 2 | tri-function\n"
                   "> 3 | quad-equation\n"
                   "> 4 | statistics\n"
                   "> - | luckiness: %d%% (%s)\n"
                   "> 9 | about\n"
                   "> 0 | exit\n\n"

                   "> "
                   ,luckinessLevel,luckinessCall(luckinessLevel).c_str());
        else
            printf(">>\n\n"

                   "Enter calculation type\n"
                   "> 1 | arithmetics\n"
                   "> 2 | tri-function\n"
                   "> 3 | quad-equation\n"
                   "> 4 | statistics\n"
                   "> 5 | luckiness\n"
                   "> 9 | about\n"
                   "> 0 | exit\n\n"

                   "> ");
        int t; scanf_s("%d", &t);
        switch (t) {
            case 0: return 0;
            case 9: {
                about();
                break;
            }
            case 1: {   //Arithmetics
                arith:
                clearScreen();
                printf(">> arithmetics\n");
                if(prevResult != DBL_MAX) printf("----------------------------------\nPrevious result = %lf\n----------------------------------", prevResult);
                printf("\nEnter arithmetic type\n> 1 | add(+)\n> 2 | subtract(-)\n> 3 | multiply(*)\n> 4 | divide(/)\n> 5 | power(^)\n> 6 | sq-root(^(1/2))\n> 7 | cb-root(^(1/3))\n> 0 | return\n\n>");
                int u; scanf_s("%d", &u);
                switch (u) {
                    case 0: break;
                    case 1: {
                        clearScreen();
                        printf(">> arithmetics >> add(+)\n");
                        if(prevResult != DBL_MAX) printf("Previous result = %lf", prevResult);
                        printf("\nEnter data > ");
                        scanf_s("%lf", &prevResult);
                        clearScreen();
                        add:
                        printf(">> arithmetics >> add(+)\n\n");
                        printf("%lf + ", prevResult);
                        double b;
                        scanf_s("%lf", &b);
                        clearScreen();
                        opAdd:
                        printf(">> arithmetics >> add(+) >> result\n\n");
                        printf("%lf + %lf = %lf\n", prevResult, b, prevResult + b);
                        prevResult += b;
                        printf("----------------------------------\n");
                        printf("> 1 | add(+) again\n> 0 | return\n\n> ");
                        int v;
                        scanf_s("%d",&v);
                        switch(v){
                            case 0:{
                                clearScreen();
                                goto arith;
                            }
                            case 1:{
                                clearScreen();
                                goto add;
                            }
                            default: {
                                clearScreen();
                                printf("Are you stupid or something? (Exception.unexpectedInput)\n");
                                system("pause");
                                clearScreen();
                                goto opAdd;
                            }
                        }
                    }
                    case 2: {
                        clearScreen();
                        printf(">> arithmetics >> subtract(-)\n");
                        if(prevResult != DBL_MAX) printf("Previous result = %lf", prevResult);
                        printf("\nEnter data > ");
                        scanf_s("%lf", &prevResult);
                        clearScreen();
                        min:
                        printf(">> arithmetics >> subtract(-)\n\n");
                        printf("%lf - ", prevResult);
                        double b;
                        scanf_s("%lf", &b);
                        clearScreen();
                        opMin:
                        printf(">> arithmetics >> subtract(-) >> result\n\n");
                        printf("%lf - %lf = %lf\n", prevResult, b, prevResult - b);
                        prevResult -= b;
                        printf("----------------------------------\n");
                        printf("> 1 | subtract(-) again\n> 0 | return\n\n> ");
                        int v;
                        scanf_s("%d",&v);
                        switch(v){
                            case 0:{
                                clearScreen();
                                goto arith;
                            }
                            case 1:{
                                clearScreen();
                                goto min;
                            }
                            default: {
                                clearScreen();
                                printf("Are you stupid or something? (Exception.unexpectedInput)\n");
                                system("pause");
                                clearScreen();
                                goto opMin;
                            }
                        }
                    }
                    case 3: {
                        clearScreen();
                        printf(">> arithmetics >> multiply(*)\n");
                        if(prevResult != DBL_MAX) printf("Previous result = %lf", prevResult);
                        printf("\nEnter data > ");
                        scanf_s("%lf", &prevResult);
                        clearScreen();
                        mul:
                        printf(">> arithmetics >> multiply(*)\n\n");
                        printf("%lf * ", prevResult);
                        double b;
                        scanf_s("%lf", &b);
                        clearScreen();
                        opMul:
                        printf(">> arithmetics >> multiply(*) >> result\n\n");
                        printf("%lf * %lf = %lf\n", prevResult, b, prevResult * b);
                        prevResult *= b;
                        printf("----------------------------------\n");
                        printf("> 1 | multiply(*) again\n> 0 | return\n\n> ");
                        int v;
                        scanf_s("%d",&v);
                        switch(v){
                            case 0:{
                                clearScreen();
                                goto arith;
                            }
                            case 1:{
                                clearScreen();
                                goto mul;
                            }
                            default: {
                                clearScreen();
                                printf("Are you stupid or something? (Exception.unexpectedInput)\n");
                                system("pause");
                                clearScreen();
                                goto opMul;
                            }
                        }
                    }
                    case 4: {
                        clearScreen();
                        printf(">> arithmetics >> divide(/)\n");
                        if(prevResult != DBL_MAX) printf("Previous result = %lf", prevResult);
                        printf("\nEnter data > ");
                        scanf_s("%lf", &prevResult);
                        clearScreen();
                        div:
                        printf(">> arithmetics >> divide(/)\n\n");
                        printf("%lf / ", prevResult);
                        double b;
                        scanf_s("%lf", &b);
                        clearScreen();
                        opDiv:
                        printf(">> arithmetics >> divide(/) >> result\n\n");
                        printf("%lf / %lf = %lf\n", prevResult, b, prevResult / b);
                        prevResult /= b;
                        printf("----------------------------------\n");
                        printf("> 1 | divide(/) again\n> 0 | return\n\n> ");
                        int v;
                        scanf_s("%d",&v);
                        switch(v){
                            case 0:{
                                clearScreen();
                                goto arith;
                            }
                            case 1:{
                                clearScreen();
                                goto div;
                            }
                            default: {
                                clearScreen();
                                printf("Are you stupid or something? (Exception.unexpectedInput)\n");
                                system("pause");
                                clearScreen();
                                goto opDiv;
                            }
                        }
                    }
                    case 5: {
                        clearScreen();
                        printf(">> arithmetics >> power(^)\n");
                        if(prevResult != DBL_MAX) printf("Previous result = %lf", prevResult);
                        printf("\nEnter data > ");
                        scanf_s("%lf", &prevResult);
                        clearScreen();
                        pow:
                        printf(">> arithmetics >> power(^)\n\n");
                        printf("%lf ^ ", prevResult);
                        double b;
                        scanf_s("%lf", &b);
                        clearScreen();
                        opPow:
                        printf(">> arithmetics >> power(^) >> result\n\n");
                        printf("%lf ^ %lf = %lf\n", prevResult, b, pow(prevResult, b));
                        prevResult = pow(prevResult, b);
                        printf("----------------------------------\n");
                        printf("> 1 | power(^) again\n> 0 | return\n\n> ");
                        int v;
                        scanf_s("%d",&v);
                        switch(v){
                            case 0:{
                                clearScreen();
                                goto arith;
                            }
                            case 1:{
                                clearScreen();
                                goto pow;
                            }
                            default: {
                                clearScreen();
                                printf("Are you stupid or something? (Exception.unexpectedInput)\n");
                                system("pause");
                                clearScreen();
                                goto opPow;
                            }
                        }
                    }
                    case 6: {
                        clearScreen();
                        printf(">> arithmetics >> sq-root(^(1/2))\n");
                        if(prevResult != DBL_MAX) printf("Previous result = %lf", prevResult);
                        printf("\nEnter data > ");
                        scanf_s("%lf", &prevResult);
                        clearScreen();
                        printf(">> arithmetics >> sq-root(^(1/2)) >> result\n\n");
                        printf("%lf ^ (1/2) = %lf\n", prevResult, std::sqrt(prevResult));
                        prevResult = std::sqrt(prevResult);
                        system("pause");
                        goto arith;
                    }
                    case 7: {
                        clearScreen();
                        printf(">> arithmetics >> cb-root(^(1/3))\n");
                        if(prevResult != DBL_MAX) printf("Previous result = %lf", prevResult);
                        printf("\nEnter data > ");
                        scanf_s("%lf", &prevResult);
                        clearScreen();
                        printf(">> arithmetics >> cb-root(^(1/3)) >> result\n\n");
                        printf("%lf ^ (1/3) = %lf\n", prevResult, std::cbrt(prevResult));
                        prevResult = std::sqrt(prevResult);
                        system("pause");
                        goto arith;
                    }
                    default: {
                        clearScreen();
                        printf("Are you stupid or something? (Exception.unexpectedInput)\n");
                        system("pause");
                        goto arith;
                    }
                }
                break;
            }
            case 2:{
                fun:
                clearScreen();
                bool rad = false;
                printf(">> tri-functions\n\n");
                printf("Select unit\n> 1 | angle(deg)\n> 2 | radian(rad)\n> 0 | return\n\n> ");
                int r; scanf_s("%d",&r);
                switch(r){
                    case 0: goto arith;
                    case 1: break;
                    case 2: {
                        rad = true;
                        break;
                    }
                    default: {
                        clearScreen();
                        printf("Are you stupid or something? (Exception.unexpectedInput)\n");
                        system("pause");
                        goto fun;
                    }
                }
                tri:
                clearScreen();
                if(rad) printf(">> tri-functions >> radian\n\n");
                else printf(">> tri-functions >> angle\n\n");
                printf("Enter function type\n> 1 | sine\n> 2 | cosine\n> 3 | tangent\n> 4 | cotangent\n> 5 | secant\n> 6 | cosecant\n> 0 | return\n\n> ");
                int u; scanf_s("%d",&u);
                switch (u) {
                    case 0: goto fun;
                    case 1:{    //Tri-functions
                        clearScreen();
                        if(rad) printf(">> tri-functions >> radian >> sine\n\n");
                        else printf(">> tri-functions >> angle >> sine\n\n");
                        printf("Enter data > ");
                        double a; scanf_s("%lf", &a);
                        clearScreen();
                        if(rad) printf(">> tri-functions >> radian >> sine >> result\n\n");
                        else printf(">> tri-functions >> angle >> sine >> result\n\n");
                        if(rad) printf("sin(%lf(rad)) = %lf\n", a, sin(a));
                        else printf("sin(%lf(deg)) = %lf\n", a, sin(deg2rad(a)));
                        system("pause");
                        goto tri;
                    }
                    case 2:{
                        clearScreen();
                        if(rad) printf(">> tri-functions >> radian >> cosine\n\n");
                        else printf(">> tri-functions >> angle >> cosine\n\n");
                        printf("Enter data > ");
                        double a; scanf_s("%lf", &a);
                        clearScreen();
                        if(rad) printf(">> tri-functions >> radian >> cosine >> result\n\n");
                        else printf(">> tri-functions >> angle >> cosine >> result\n\n");
                        if(rad) printf("cos(%lf(rad)) = %lf\n", a, cos(a));
                        else printf("cos(%lf(deg)) = %lf\n", a, cos(deg2rad(a)));
                        system("pause");
                        goto tri;
                    }
                    case 3:{
                        clearScreen();
                        if(rad) printf(">> tri-functions >> radian >> tangent\n\n");
                        else printf(">> tri-functions >> angle >> tangent\n\n");
                        printf("Enter data > ");
                        double a; scanf_s("%lf", &a);
                        clearScreen();
                        if(rad) printf(">> tri-functions >> radian >> tangent >> result\n\n");
                        else printf(">> tri-functions >> angle >> tangent >> result\n\n");
                        if(rad) printf("tan(%lf(rad)) = %lf\n", a, tan(a));
                        else printf("tan(%lf(deg)) = %lf\n", a, tan(deg2rad(a)));
                        system("pause");
                        goto tri;
                    }
                    case 4:{
                        clearScreen();
                        if(rad) printf(">> tri-functions >> radian >> cotangent\n\n");
                        else printf(">> tri-functions >> angle >> cotangent\n\n");
                        printf("Enter data > ");
                        double a; scanf_s("%lf", &a);
                        clearScreen();
                        if(rad) printf(">> tri-functions >> radian >> cotangent >> result\n\n");
                        else printf(">> tri-functions >> angle >> cotangent >> result\n\n");
                        if(rad) printf("cot(%lf(rad)) = %lf\n", a, 1/tan(a));
                        else printf("cot(%lf(deg)) = %lf\n", a, 1/tan(deg2rad(a)));
                        system("pause");
                        goto tri;
                    }
                    case 5:{
                        clearScreen();
                        if(rad) printf(">> tri-functions >> radian >> secant\n\n");
                        else printf(">> tri-functions >> angle >> secant\n\n");
                        printf("Enter data > ");
                        double a; scanf_s("%lf", &a);
                        clearScreen();
                        if(rad) printf(">> tri-functions >> radian >> secant >> result\n\n");
                        else printf(">> tri-functions >> angle >> secant >> result\n\n");
                        if(rad) printf("sec(%lf(rad)) = %lf\n", a, 1/cos(a));
                        else printf("sec(%lf(deg)) = %lf\n", a, 1/cos(deg2rad(a)));
                        system("pause");
                        goto tri;
                    }
                    case 6:{
                        clearScreen();
                        if(rad) printf(">> tri-functions >> radian >> cosecant\n\n");
                        else printf(">> tri-functions >> angle >> cosecant\n\n");
                        printf("Enter data > ");
                        double a; scanf_s("%lf", &a);
                        clearScreen();
                        if(rad) printf(">> tri-functions >> radian >> cosecant >> result\n\n");
                        else printf(">> tri-functions >> angle >> cosecant >> result1\n\n");
                        if(rad) printf("csc(%lf(rad)) = %lf\n", a, 1/sin(a));
                        else printf("csc(%lf(deg)) = %lf\n", a, 1/sin(deg2rad(a)));
                        system("pause");
                        goto tri;
                    }
                    default: {
                        clearScreen();
                        printf("Are you stupid or something? (Exception.unexpectedInput)\n");
                        system("pause");
                        goto tri;
                    }
                }
            }
            case 3:{    //Equations
                clearScreen();
                printf(">> quad-equation\n\n");
                printf("The Original Formula : ax^2+bx+c (a!=0)\n");
                double a,b,c;
                printf("Enter a: "); scanf_s("%lf",&a);
                if(a==0){
                    clearScreen();
                    printf("Are you stupid or something?  (Exception.invalidQuadraticCoefficient)\n");
                    system("pause");
                    break;
                }
                printf("Enter b: "); scanf_s("%lf",&b);
                printf("Enter c: "); scanf_s("%lf",&c);
                double d=pow(b,2)-4*a*c;
                if(d<0){
                    clearScreen();
                    printf("There's no real solution to this equation (Exception.deltaUnderZero)\nwith delta value %lf\n",d);
                    system("pause");
                    break;
                }
                clearScreen();
                quad:
                printf(">> quad-equation >> solving\n\n");
                ePrint(a,b,c);
                printf("with delta value %lf\n----------------------------------\n",d);
                if(!isInt(a)||!isInt(b)||!isInt(c)) printf("Enter solving type\n> 1 | numeric\n> - | cross-solve (disabled: integer coefficients only)\n> 0 | return\n\n> ");
                else if(c==0) printf("Enter solving type\n> 1 | numeric\n> - | cross-solve (disabled: c = 0)\n> 0 | return\n\n> ");
                else if(!isSquare(d)) printf("Enter solving type\n> 1 | numeric\n> - | cross-solve (disabled: delta is not a square number)\n> 0 | return\n\n> ");
                else printf("Enter solving type\n> 1 | numeric\n> 2 | cross-solve\n> 0 | return\n\n> ");
                int u; scanf_s("%d",&u);
                switch (u) {
                    case 0: break;
                    case 1:{
                        clearScreen();
                        printf(">> quad-equation >> solving >> numeric\n\n");
                        ePrint(a,b,c);
                        quadEquationSolve(a,b,c);
                        printf("Solution: ");
                        if(x1==x2) printf("x1 = x2 = %lf\n",x1);
                        else printf("x1 = %lf , x2 = %lf\n",x1,x2);
                        system("pause");
                        clearScreen();
                        goto quad;
                    }
                    case 2:{
                        if(!isInt(a)||!isInt(b)||!isInt(c)||c==0||!isSquare(d)){
                            clearScreen();
                            printf("Are you stupid or something? (Exception.unexpectedInput)\n");
                            system("pause");
                            clearScreen();
                            goto quad;
                        }
                        clearScreen();
                        printf(">> quad-equation >> solving >> cross-solve\n\n");
                        ePrint(a,b,c);
                        crossSolve((int)a,(int)b,(int)c);
                        printf("Solution:\n");
                        printf("%d\t%d\n%d\t%d\n", crossSolveResult[0][0], crossSolveResult[1][0], crossSolveResult[0][1], crossSolveResult[1][1]);
                        system("pause");
                        clearScreen();
                        goto quad;
                    }
                    default: {
                        clearScreen();
                        printf("Are you stupid or something? (Exception.unexpectedInput)\n");
                        system("pause");
                        clearScreen();
                        goto quad;
                    }
                }
                break;
            }
            case 4:{    //Statistics
                clearScreen();
                printf(">> statistics\n\n");
                printf("Enter amount of data: ");
                int amount=0;
                scanf_s("%d",&amount);
                if (!amount) {
                    clearScreen();
                    printf("Are you stupid or something? (Exception.unexpectedInput)\n");
                    system("pause");
                    break;
                }
                clearScreen();
                printf(">> statistics\n\n");
                printf("Enter data\n");
                std::vector<double> data;
                for (int i = 0; i < amount; ++i) {
                    double input = 0;
                    printf("data[%d/%d] = ",i+1,amount);
                    scanf_s("%lf", &input);
                    data.push_back(input);
                }
                clearScreen();
                printf(">> statistics >> result\n\n");
                int weighted = 0;
                stat:
                if(!weighted) printf("Data:\n");
                else printf("Data(%d):\n",weighted+1);
                for(int i=0;i<amount;i++) printf("data[%d] = %lf\n",i+1,data[i]);
                if(amount-1){
                    printf("----------------------------------\n");
                    double accumulate = 0, var = variance(data);
                    for (double i: data) accumulate += i;
                    printf("Accumulate\n%+33lf\n", accumulate);
                    printf("Average\n%+33lf\n", accumulate / amount);
                    printf("Variance\n%+33lf\n", var);
                    printf("Std. Deviation\n%+33lf\n", std::sqrt(var));
                    printf("Median\n%+33lf\n", median(data));
                    if (weighted) {
                        printf("----------------------------------\n");
                        printf("> 1 | set weightings again\n> 0 | return\n\n> ");
                    } else {
                        printf("----------------------------------\n");
                        printf("> 1 | set weightings\n> 0 | return\n\n> ");
                    }
                }
                else{
                    if (weighted) {
                        printf("----------------------------------\n");
                        printf("> 1 | go multiplying again\n> 0 | return\n\n> ");
                    } else {
                        printf("----------------------------------\n");
                        printf("> 1 | go multiplying\n> 0 | return\n\n> ");
                    }
                }
                int v;
                scanf_s("%d",&v);
                switch(v){
                    case 0: break;
                    case 1:{
                        clearScreen();
                        if(amount-1) printf(">> statistics >> set weightings\n\n");
                        else printf(">> statistics >> multiplying\n\n");
                        for(int i=0;i<amount;i++){
                            double alt;
                            printf("data[%d] = %lf * ",i+1,data[i]);
                            scanf_s("%lf",&alt);
                            data[i] *= alt;
                        }
                        weighted++;
                        clearScreen();
                        goto stat;
                    }
                    default: {
                        clearScreen();
                        printf("Are you stupid or something? (Exception.unexpectedInput)\n");
                        system("pause");
                        clearScreen();
                        goto stat;
                    }
                }
                break;
            }
            case 5:{
                if(!luckiness){
                    clearScreen();
                    std::random_device rd;
                    std::mt19937 gen(rd());
                    luckinessLevel = abs((int)gen()) % 101;
                    luckiness = true;
                    break;
                    [[fallthrough]];
                }
            }
            default: {
                clearScreen();
                printf("Are you stupid or something? (Exception.unexpectedInput)\n");
                system("pause");
                break;
            }
        }
        printf("\n");
        clearScreen();
    }
}
