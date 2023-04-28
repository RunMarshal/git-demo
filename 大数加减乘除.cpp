#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*
	使用原码进行运算，不是使用补码
	因此，自定义大数类型为符号位和绝对值的二进制字符串 
*/
typedef struct {
    char* Binary; // 二进制字符串
    int sign; // 符号位，1 表示正数，-1表示负数
} BigInt;

//释放内存函数
void BigIntFree(BigInt* bigint) {
    if (bigint == NULL) return;
    free(bigint->Binary);
}

//函数声明为bool判断是否操作成功 
/*  十进制转二进制函数
	步骤：1.确定符号，大数长度len
	2.将十进制数的每一位数转换为四位的二进制数 
	3.创建长度为4 * len + 1二进制字符数组,并且初始化为0
	4. 
*/
bool BigIntToBinary(char bigint_num[],BigInt* &binary_num) {
    if (bigint_num == NULL) {
    	printf("大数为空\n");
    	return false;
	}
//确定符号，跳过负号（不使用补码，用二进制绝对值运算） 
    int sign = bigint_num[0] == '-' ? -1 : 1; 
    if (sign == -1) {
        bigint_num++; 
    }
    int len = strlen(bigint_num);
//分配大量的内存且需要初始化为0，使用calloc()更加方便
    char* bin_num = (char*)calloc(len * 4 + 1, sizeof(char)); 
    int bin_idx = 0;
// 除以2迭代过程（后期再优化） 
    while (1) {
    	// 初始化进位值
        int carry = 0; 
        // 初始化标志，表示是否找到非零值
        int found = 0; 

        // 依次遍历十进制数字字符串的每一位
        for (int i = 0; i < len; ++i) {
        	// 使用ASCII码值转换法将字符转换为整数值
            int d = bigint_num[i] - '0'; 
            // 计算进位值和当前值的操作结果
            int temp = carry * 10 + d; 
            // 更新十进制数字的当前位（除以2的结果）
            bigint_num[i] = temp / 2 + '0';
			// 更新进位值（除以2的余数） 
            carry = temp % 2; 

            // 如果找到非零值，更新标志
            if (bigint_num[i] != '0') {
                found = 1;
            }
        }
        // 将进位值添加到二进制结果的开头
        bin_num[bin_idx++] = carry + '0';

        // 如果没有找到非零值，说明十进制数字已经除尽，退出循环
        if (!found) {
            break;
        }
    }
    // 反转二进制字符串（优化策略：使用位运算交换） 
    for (int i = 0, j = bin_idx - 1; i < j; ++i, --j) {
        bin_num[i] = bin_num[i] ^ bin_num[j];
        bin_num[j] = bin_num[i] ^ bin_num[j];
        bin_num[i] = bin_num[i] ^ bin_num[j];
    }
    
    //修改引用类型binary_num的值 
    binary_num->Binary = bin_num;
    binary_num->sign = sign;
    return true;
}

// 二进制大数转十进制字符串函数
char* BinaryToBigInt(BigInt* bigint) {
    if (bigint == NULL) return NULL;

    int len = strlen(bigint->Binary);
    // 每个二进制位最多对应3位十进制数
    char* bigint_num = (char*)calloc(len * 3 + 1, sizeof(char)); 
    bigint_num[0] = '0';

    // 乘以 2 的迭代过程（后期再优化） 
    for (int i = 0; i < len; ++i) {
        int carry = bigint->Binary[i] - '0';
        for (int j = 0; j < strlen(bigint_num); ++j) {
            int temp = (bigint_num[j] - '0') * 2 + carry;
            carry = temp / 10;
            bigint_num[j] = temp % 10 + '0';
        }
        if (carry) {
            int dec_len = strlen(bigint_num);
            bigint_num[dec_len] = carry + '0';
            bigint_num[dec_len + 1] = '\0';
        }
    }

    // 反转十进制字符串，使其从低位到高位
    int dec_len = strlen(bigint_num);
    for (int i = 0, j = dec_len - 1; i < j; ++i, --j) {
        bigint_num[i] = bigint_num[i] ^ bigint_num[j];
        bigint_num[j] = bigint_num[i] ^ bigint_num[j];
        bigint_num[i] = bigint_num[i] ^ bigint_num[j];
    }

    // 添加负号
    if (bigint->sign == -1) {
        strcpy(bigint_num + 1, bigint_num);
        bigint_num[0] = '-';
    }

    return bigint_num;
}


// 无符号二进制加法
void Bin_Unadd(BigInt* bin_num1, BigInt* bin_num2,BigInt* &binary_num) {
    if (bin_num1 == NULL || bin_num2 == NULL) return ;
    int len1 = strlen(bin_num1->Binary);
    int len2 = strlen(bin_num2->Binary);
    int max_len = len1 > len2 ? len1 : len2;
    // 多分配一个字节存储可能的进位
    char* result = (char*)calloc(max_len + 2, sizeof(char)); 
    int carry = 0;

    // 逐位相加，从低位到高位
    for (int i = 0; i < max_len; ++i) {
        int bit1 = i < len1 ? bin_num1->Binary[len1 - 1 - i] - '0' : 0;
        int bit2 = i < len2 ? bin_num2->Binary[len2 - 1 - i] - '0' : 0;
        int sum = bit1 + bit2 + carry;
        carry = sum / 2;
        result[max_len - i] = sum % 2 + '0';
    }
//可能的进位
    if (carry) {
        result[0] = '1';
    }
    else {
        strcpy(result, result + 1);
    }

    binary_num->Binary = result;
    binary_num->sign = 1;
    return ;
}

// 辅助函数：二进制大数比较函数
int Bin_Cmp(BigInt* bin_num1, BigInt* bin_num2) {
    if (bin_num1 == NULL || bin_num2 == NULL) return NULL;
    int len1 = strlen(bin_num1->Binary);
    int len2 = strlen(bin_num2->Binary);

    if (len1 > len2) {
        return 1;
    }
    else if (len1 < len2) {
        return -1;
    }
    else {
        for (int i = 0; i < len1; ++i) {
            if (bin_num1->Binary[i] > bin_num2->Binary[i]) {
                return 1;
            }
            else if (bin_num1->Binary[i] < bin_num2->Binary[i]) {
                return -1;
            }
        }
    }

    return 0;
}


//无符号二进制减法
void Bin_Unsub(BigInt* bin_num1, BigInt* bin_num2,BigInt* &binary_num) {
    if (bin_num1 == NULL || bin_num2 == NULL) return ;
    int len1 = strlen(bin_num1->Binary);
    int len2 = strlen(bin_num2->Binary);
    int max_len = len1 > len2 ? len1 : len2;
    // 多分配一个字节存储可能的借位
    char* result = (char*)calloc(max_len + 1, sizeof(char));
	// 确保result以空字符结尾 
    result[max_len] = '\0'; 
    int borrow = 0;

    // 逐位相减，从低位到高位
    for (int i = 0; i < max_len; ++i) {

        int bit1 = i < len1 ? bin_num1->Binary[len1 - 1 - i] - '0' : 0;
        int bit2 = i < len2 ? bin_num2->Binary[len2 - 1 - i] - '0' : 0;
        //diff是差值 borrow是否借位 
        int diff = bit1 - bit2 - borrow;
        if (diff < 0) {
            diff += 2;
            borrow = 1;
        }
        else {
            borrow = 0;
        }
        result[max_len - i] = diff + '0';
    }
    /*
    使用memmove(num1,num2,n)函数移动字节，清零符号位。 
    num：指向要移动数据的目标位置的指针。
	num+1：指向要移动数据的源位置的指针。
	strlen(num)：要移动的位数。
    */
    memmove(result, result + 1, max_len);
	// 添加空字符结尾 
    result[max_len] = '\0'; 
    // 去掉前导零
    while (*result == '0' && *(result + 1) != '\0') {
        memmove(result, result + 1, strlen(result));
    }

    binary_num->Binary = result;
    binary_num->sign = 1; // 无符号数减法结果为正

    return ;
}

// 二进制加法函数
void Bin_Add(BigInt* bin_num1, BigInt* bin_num2,BigInt* &binary_num) {
    if (bin_num1 == NULL || bin_num2 == NULL) return ;

    // 判断符号位
    if (bin_num1->sign == bin_num2->sign) {
        // 如果两个数的符号位相同，那么相加的结果和它们一致
        Bin_Unadd(bin_num1, bin_num2,binary_num);
        binary_num->sign = bin_num1->sign;
    }
    else {
        // 如果两个数的符号位不同，那么相加的结果和它们中绝对值较大的一致
        int cmp = Bin_Cmp(bin_num1, bin_num2);
        if (cmp > 0) {   
            Bin_Unsub(bin_num1, bin_num2,binary_num);
            binary_num->sign = bin_num1->sign;
        }
        else if (cmp < 0) {        
            Bin_Unsub(bin_num2, bin_num1,binary_num); 
            binary_num->sign = bin_num2->sign;
        }
        else {
            // 如果两个数绝对值相等，那么相加的结果为零，符号位为正
            binary_num->sign = 1;
            // 如果绝对值相等，且两数符号相反，结果为0
            binary_num->Binary = (char*)calloc(2, sizeof(char));
            binary_num->Binary[0] = '0';
        }
    }
    return ;
}
// 二进制减法函数
void Bin_Sub(BigInt bin_num1, BigInt bin_num2,BigInt* &binary_num) {
    bin_num2.sign = -bin_num2.sign;
    Bin_Add(&bin_num1, &bin_num2,binary_num);
 
}

// 二进制大数乘法函数
void Bin_Mul(BigInt* bin_num1, BigInt* bin_num2,BigInt* &binary_num) {
    if (bin_num1 == NULL || bin_num2 == NULL) return;

    int len1 = strlen(bin_num1->Binary);
    int len2 = strlen(bin_num2->Binary);
    // 符号位相乘
    binary_num->sign = bin_num1->sign * bin_num2->sign; 
    // 分配足够的内存
    binary_num->Binary = (char*)calloc(len1 + len2 + 1, sizeof(char)); 
    // 初始化为'0'
    memset(binary_num->Binary, '0', len1 + len2); 

    // 逐位相乘，然后累加
    for (int i = len1 - 1; i >= 0; --i) {
        for (int j = len2 - 1; j >= 0; --j) {
        	// 计算当前位的乘积
            int product = (bin_num1->Binary[i] - '0') * (bin_num2->Binary[j] - '0');
			// 计算当前位的和（包含进位） 
            int carry = (binary_num->Binary[i + j + 1] - '0') + product;
			// 更新当前位的值 
            binary_num->Binary[i + j + 1] = carry % 2 + '0';
			// 更新进位 
            binary_num->Binary[i + j] += carry / 2; 
        }
    }

    // 去除前导零
    int idx = 0;
    while (binary_num->Binary[idx] == '0' && binary_num->Binary[idx + 1] != '\0') {
        ++idx;
    }
    memmove(binary_num->Binary, binary_num->Binary + idx, strlen(binary_num->Binary) - idx + 1);
    return;
}
//二进制大数除法函数
BigInt* Bin_Div(BigInt* bin_num1, BigInt* bin_num2, BigInt**remainder) {
    if (bin_num1 == NULL || bin_num2 == NULL) return NULL;
    if (strcmp(bin_num2->Binary, "0") == 0) {
        *remainder = NULL; 
		return NULL;
    }
	// 用于存储商
    BigInt* quotient = (BigInt*)malloc(sizeof (BigInt)); 
    // 计算商的符号位
    quotient->sign = bin_num1->sign * bin_num2->sign; 
//被除数的长度
    int dividend_len = strlen(bin_num1->Binary);
    // 除数长度
    int divisor_len = strlen(bin_num2->Binary); 
    // 二进制商的长度
    int quotient_len = abs(dividend_len - divisor_len) + 2; 
    quotient->Binary = (char*)calloc(quotient_len, sizeof(char));
   
// 用于存储当前被除数 
    BigInt* dividend = (BigInt*)malloc(sizeof(BigInt)); 
    dividend->sign = 1;
    dividend->Binary = (char*)calloc(dividend_len + 1, sizeof(char));
    strcpy(dividend->Binary, bin_num1->Binary);
// 用于存储除数
    BigInt* divisor = (BigInt*)malloc(sizeof(BigInt)); 
    divisor->sign = 1;
    divisor->Binary = (char*)calloc(divisor_len + 1, sizeof(char));
    strcpy(divisor->Binary, bin_num2->Binary);

    // 如果被除数绝对值小于除数绝对值，则商为0，余数为被除数
    if (Bin_Cmp(dividend,divisor) < 0) {
        strcpy(quotient->Binary, "0");
        dividend->sign = bin_num1->sign;
        *remainder = dividend;

        return quotient;
    }
    // 如果被除数等于除数，则商为1，余数为'+'0
    else if (Bin_Cmp(dividend, divisor) == 0) { 
        strcpy(quotient->Binary, "1");
        BigInt* tmp = (BigInt*)malloc(sizeof(BigInt));
        tmp->sign = 1; tmp->Binary[0] = '0'; 
        *remainder = tmp;
        return quotient;
    }

    /*
    思想：ALU移位运算
		1.判断当前 被除数（dividend） 是否大于 除数（divisor）
		2.根据1，讨论商的情况，若为0 或者1 直接到7  
		3.记录左移对齐被除数后的除数 
		4. 用减法模拟除法过程 
		5.转1判断结果 
		6.最后被除数剩下的就是余数。
	*/
// 计算需要将除数左移的位数
    int shift = dividend_len - divisor_len; 
// 存储左移后的除数
    BigInt* shifted_divisor = (BigInt*)malloc(sizeof(BigInt)); 
    shifted_divisor->sign = 1;
    shifted_divisor->Binary = (char*)calloc(divisor_len + shift + 1, sizeof(char));
    strcpy(shifted_divisor->Binary, divisor->Binary);

    // 将除数左移，补0
    for (int i = 0; i < shift; ++i) {
        strcat(shifted_divisor->Binary, "0");
    }

    // 用减法模拟除法过程
    int quotient_pos = 0;
    while (shift >= 0) {
        // 当被除数大于等于左移后的除数时，更新被除数和商的对应位 
        quotient->Binary[quotient_pos] += '0';
        while (Bin_Cmp(dividend, shifted_divisor) >= 0) {
        	// 更新被除数
            Bin_Sub(*dividend, *shifted_divisor,dividend); 
			// 更新商的对应位
            quotient->Binary[quotient_pos]++; 
            
        }
        // 将除数右移一位
        shifted_divisor->Binary[strlen(shifted_divisor->Binary) - 1] = '\0'; 
        --shift;
        ++quotient_pos;
      
    }
// 添加字符串终止符
    quotient->Binary[quotient_pos] = '\0'; 
    dividend->sign = bin_num1->sign;
// 更新余数
    *remainder = dividend; 
    return quotient;
}
int main(){
	char num1[100],num2[100];
	int expression = 0;
	printf("请输入想进行的操作:1.加法2.减法3.乘法4.除法:\n");
	while(scanf("%d", &expression)){   
    printf("请输入第一个大整数：\n");
    scanf("%s", num1);
    BigInt* binary_num1 = (BigInt*)malloc(sizeof(BigInt));
    BigIntToBinary(num1,binary_num1);
    
   	printf("请输入第二个大整数：\n");
    scanf("%s", num2);
    BigInt* binary_num2 = (BigInt*)malloc(sizeof(BigInt));
    BigIntToBinary(num2,binary_num2);
    
	switch(expression){
	    case 1:
	    {
		    BigInt* sum = (BigInt*)malloc(sizeof(BigInt));
		    Bin_Add(binary_num1,binary_num2,sum);
		    printf("%s\n",BinaryToBigInt(sum));
		    BigIntFree(binary_num1);
		    BigIntFree(binary_num2);
		    BigIntFree(sum);
		    
		    break;
		}
	    case 2:
	    {
		    BigInt* sub = (BigInt*)malloc(sizeof(BigInt));
		    Bin_Sub(*binary_num1,*binary_num2,sub);
		    printf("%s\n",BinaryToBigInt(sub));
		    BigIntFree(binary_num1);
		    BigIntFree(binary_num2);
		    BigIntFree(sub);
		    break;
		}
		case 3:
	    {
		    BigInt* mul = (BigInt*)malloc(sizeof(BigInt));
		    Bin_Mul(binary_num1,binary_num2,mul);
		    printf("%s\n",BinaryToBigInt(mul));
		    BigIntFree(binary_num1);
		    BigIntFree(binary_num2);
		    BigIntFree(mul);
		    break;
		}
		case 4:
	    {
		    BigInt *quotient = 0;
		    BigInt *remainder = 0;
		    quotient = Bin_Div(binary_num1,binary_num2,&remainder);
			printf("商为：%s\n",BinaryToBigInt(quotient));
		    printf("余数为：%s\n",BinaryToBigInt(remainder));
		    BigIntFree(binary_num1);
		    BigIntFree(binary_num2);
		    BigIntFree(quotient);
		    BigIntFree(remainder);
		    break;
		}
	    default:
	    	return 0;
		}
		printf("请输入想进行的操作:1.加法2.减法3.乘法4.除法:\n");
	}
}
