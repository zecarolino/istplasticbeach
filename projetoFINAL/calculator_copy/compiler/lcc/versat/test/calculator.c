volatile int *RegBT0;
volatile int *RegBT1;
volatile int *RegBT2;
volatile int *RegDigit0;
volatile int *RegDigit1;
volatile int *RegDigit2;
volatile int *RegDigit3;

void printDigitOn7Seg(int i, int number);
int buttonPressed (volatile int * bt);
int chooseOperand();
int computeResult(int A,int operator,int B);
int _mul(int a, int b);
int _div(int a, int b);
int _mod(int a, int b);

int main() {
    int A;
    int operator;
    int B;
    int C;
    int i;
    int aux;
    int flag_1stoperand = 0;
    int wait = 1;
    
    while (1 == 1) {
        wait = 1;
        
        // choose 1st operand
        if (flag_1stoperand == 1)
            A = chooseOperand();
        else
            A = C;

        flag_1stoperand = 0;

        // choose operator
        operator = chooseOperator();
             
        // choose 2st operand
        B = chooseOperand();

        // compute the result
        C = computeResult(A,operator,B);
        
        // print Result on 7 seg display
        for (i = 0; i < 4; i++) {
            aux = C<<i;
            printDigitOn7Seg(i,aux);
        }
        
        //wait Enter(resuse resukt as 1st operand) or Clear
        while (wait == 1) {
            // Enter pressed
            if ( buttonPressed(RegBT0) == 1 ) {
                flag_1stoperand = 1;
                wait = 0;
            } else if (buttonPressed(RegBT2) == 1) {
                wait = 0;
            }
        }
    }
    return 0;
}

int buttonPressed (volatile int * bt) {
    if (*bt == 0) return 0;
    while (*bt != 0);
    return 1;
}

void printDigitOn7Seg(int i, int number) {
    if (i == 0) {
        *RegDigit0 = number;
    } else if (i == 1){
        *RegDigit1 = number;
    } else if (i == 2){
        *RegDigit2 = number;
    } else {
        *RegDigit3 = number;
    }
}

int chooseOperand() {
    int i = 0;
    int number = 0;
    int operand = 0;
    *RegDigit0 = 0;
    *RegDigit1 = 0;
    *RegDigit2 = 0;
    *RegDigit3 = 0;
    while (i != 4) {
        if ( buttonPressed(RegBT0) == 1 ) {
            operand = operand + (number<<i);
            i = i + 1;
            i = i%4;
            number = 0;
        }
        if ( buttonPressed(RegBT1) == 1 ) {
            number = number + 1;
            number = number % 16;
        }
        printDigitOn7Seg(i,number);
    }
    return operand;
}

int chooseOperator() {
    int operator = 0;
    *RegDigit0 = 0;
    *RegDigit1 = 0;
    *RegDigit2 = 0;
    *RegDigit3 = 0;
    
    while (buttonPressed(RegBT0) != 1) {
        if ( buttonPressed(RegBT1) == 1) {
            operator = operator + 1;
            operator = operator % 8;
        }
    }
    
    return operator;
}

int computeResult(int A,int operator,int B) {
    if (operator == 0) return A + B;
    else if (operator == 1) return A - B;
    else if (operator == 2) return A * B;
    else if (operator == 3) return A / B;
    else return A % B;
}

int _mul(int a, int b) {
	int mul;
	for (mul = 0; b; b >>= 1, a <<= 1)
		if (b & 1)
			mul += a;
	return mul;
}
int _div(int a, int b) {
	int c = 1, neg = 0, aux;
	if (!a) return 0;
	if (!b) return 2147483647; /* divide by zero */
	if (a < 0) a = -a, neg = 1;
	if (b < 0) b = -b, neg = 1 - neg;
	aux = b;
	if (a && b && b < a) {
		while ((aux << 1) - a < 0)
			aux <<= 1, c <<= 1;
		while (aux + b <= a)
			aux += b, c++;
	}
	if (neg) c = -c;
	return c;
}

int _mod(int a, int b) { return a - (a / b) * b; }

