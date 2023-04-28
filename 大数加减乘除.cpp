#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*
	ʹ��ԭ��������㣬����ʹ�ò���
	��ˣ��Զ����������Ϊ����λ�;���ֵ�Ķ������ַ��� 
*/
typedef struct {
    char* Binary; // �������ַ���
    int sign; // ����λ��1 ��ʾ������-1��ʾ����
} BigInt;

//�ͷ��ڴ溯��
void BigIntFree(BigInt* bigint) {
    if (bigint == NULL) return;
    free(bigint->Binary);
}

//��������Ϊbool�ж��Ƿ�����ɹ� 
/*  ʮ����ת�����ƺ���
	���裺1.ȷ�����ţ���������len
	2.��ʮ��������ÿһλ��ת��Ϊ��λ�Ķ������� 
	3.��������Ϊ4 * len + 1�������ַ�����,���ҳ�ʼ��Ϊ0
	4. 
*/
bool BigIntToBinary(char bigint_num[],BigInt* &binary_num) {
    if (bigint_num == NULL) {
    	printf("����Ϊ��\n");
    	return false;
	}
//ȷ�����ţ��������ţ���ʹ�ò��룬�ö����ƾ���ֵ���㣩 
    int sign = bigint_num[0] == '-' ? -1 : 1; 
    if (sign == -1) {
        bigint_num++; 
    }
    int len = strlen(bigint_num);
//����������ڴ�����Ҫ��ʼ��Ϊ0��ʹ��calloc()���ӷ���
    char* bin_num = (char*)calloc(len * 4 + 1, sizeof(char)); 
    int bin_idx = 0;
// ����2�������̣��������Ż��� 
    while (1) {
    	// ��ʼ����λֵ
        int carry = 0; 
        // ��ʼ����־����ʾ�Ƿ��ҵ�����ֵ
        int found = 0; 

        // ���α���ʮ���������ַ�����ÿһλ
        for (int i = 0; i < len; ++i) {
        	// ʹ��ASCII��ֵת�������ַ�ת��Ϊ����ֵ
            int d = bigint_num[i] - '0'; 
            // �����λֵ�͵�ǰֵ�Ĳ������
            int temp = carry * 10 + d; 
            // ����ʮ�������ֵĵ�ǰλ������2�Ľ����
            bigint_num[i] = temp / 2 + '0';
			// ���½�λֵ������2�������� 
            carry = temp % 2; 

            // ����ҵ�����ֵ�����±�־
            if (bigint_num[i] != '0') {
                found = 1;
            }
        }
        // ����λֵ��ӵ������ƽ���Ŀ�ͷ
        bin_num[bin_idx++] = carry + '0';

        // ���û���ҵ�����ֵ��˵��ʮ���������Ѿ��������˳�ѭ��
        if (!found) {
            break;
        }
    }
    // ��ת�������ַ������Ż����ԣ�ʹ��λ���㽻���� 
    for (int i = 0, j = bin_idx - 1; i < j; ++i, --j) {
        bin_num[i] = bin_num[i] ^ bin_num[j];
        bin_num[j] = bin_num[i] ^ bin_num[j];
        bin_num[i] = bin_num[i] ^ bin_num[j];
    }
    
    //�޸���������binary_num��ֵ 
    binary_num->Binary = bin_num;
    binary_num->sign = sign;
    return true;
}

// �����ƴ���תʮ�����ַ�������
char* BinaryToBigInt(BigInt* bigint) {
    if (bigint == NULL) return NULL;

    int len = strlen(bigint->Binary);
    // ÿ��������λ����Ӧ3λʮ������
    char* bigint_num = (char*)calloc(len * 3 + 1, sizeof(char)); 
    bigint_num[0] = '0';

    // ���� 2 �ĵ������̣��������Ż��� 
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

    // ��תʮ�����ַ�����ʹ��ӵ�λ����λ
    int dec_len = strlen(bigint_num);
    for (int i = 0, j = dec_len - 1; i < j; ++i, --j) {
        bigint_num[i] = bigint_num[i] ^ bigint_num[j];
        bigint_num[j] = bigint_num[i] ^ bigint_num[j];
        bigint_num[i] = bigint_num[i] ^ bigint_num[j];
    }

    // ��Ӹ���
    if (bigint->sign == -1) {
        strcpy(bigint_num + 1, bigint_num);
        bigint_num[0] = '-';
    }

    return bigint_num;
}


// �޷��Ŷ����Ƽӷ�
void Bin_Unadd(BigInt* bin_num1, BigInt* bin_num2,BigInt* &binary_num) {
    if (bin_num1 == NULL || bin_num2 == NULL) return ;
    int len1 = strlen(bin_num1->Binary);
    int len2 = strlen(bin_num2->Binary);
    int max_len = len1 > len2 ? len1 : len2;
    // �����һ���ֽڴ洢���ܵĽ�λ
    char* result = (char*)calloc(max_len + 2, sizeof(char)); 
    int carry = 0;

    // ��λ��ӣ��ӵ�λ����λ
    for (int i = 0; i < max_len; ++i) {
        int bit1 = i < len1 ? bin_num1->Binary[len1 - 1 - i] - '0' : 0;
        int bit2 = i < len2 ? bin_num2->Binary[len2 - 1 - i] - '0' : 0;
        int sum = bit1 + bit2 + carry;
        carry = sum / 2;
        result[max_len - i] = sum % 2 + '0';
    }
//���ܵĽ�λ
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

// ���������������ƴ����ȽϺ���
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


//�޷��Ŷ����Ƽ���
void Bin_Unsub(BigInt* bin_num1, BigInt* bin_num2,BigInt* &binary_num) {
    if (bin_num1 == NULL || bin_num2 == NULL) return ;
    int len1 = strlen(bin_num1->Binary);
    int len2 = strlen(bin_num2->Binary);
    int max_len = len1 > len2 ? len1 : len2;
    // �����һ���ֽڴ洢���ܵĽ�λ
    char* result = (char*)calloc(max_len + 1, sizeof(char));
	// ȷ��result�Կ��ַ���β 
    result[max_len] = '\0'; 
    int borrow = 0;

    // ��λ������ӵ�λ����λ
    for (int i = 0; i < max_len; ++i) {

        int bit1 = i < len1 ? bin_num1->Binary[len1 - 1 - i] - '0' : 0;
        int bit2 = i < len2 ? bin_num2->Binary[len2 - 1 - i] - '0' : 0;
        //diff�ǲ�ֵ borrow�Ƿ��λ 
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
    ʹ��memmove(num1,num2,n)�����ƶ��ֽڣ��������λ�� 
    num��ָ��Ҫ�ƶ����ݵ�Ŀ��λ�õ�ָ�롣
	num+1��ָ��Ҫ�ƶ����ݵ�Դλ�õ�ָ�롣
	strlen(num)��Ҫ�ƶ���λ����
    */
    memmove(result, result + 1, max_len);
	// ��ӿ��ַ���β 
    result[max_len] = '\0'; 
    // ȥ��ǰ����
    while (*result == '0' && *(result + 1) != '\0') {
        memmove(result, result + 1, strlen(result));
    }

    binary_num->Binary = result;
    binary_num->sign = 1; // �޷������������Ϊ��

    return ;
}

// �����Ƽӷ�����
void Bin_Add(BigInt* bin_num1, BigInt* bin_num2,BigInt* &binary_num) {
    if (bin_num1 == NULL || bin_num2 == NULL) return ;

    // �жϷ���λ
    if (bin_num1->sign == bin_num2->sign) {
        // ����������ķ���λ��ͬ����ô��ӵĽ��������һ��
        Bin_Unadd(bin_num1, bin_num2,binary_num);
        binary_num->sign = bin_num1->sign;
    }
    else {
        // ����������ķ���λ��ͬ����ô��ӵĽ���������о���ֵ�ϴ��һ��
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
            // �������������ֵ��ȣ���ô��ӵĽ��Ϊ�㣬����λΪ��
            binary_num->sign = 1;
            // �������ֵ��ȣ������������෴�����Ϊ0
            binary_num->Binary = (char*)calloc(2, sizeof(char));
            binary_num->Binary[0] = '0';
        }
    }
    return ;
}
// �����Ƽ�������
void Bin_Sub(BigInt bin_num1, BigInt bin_num2,BigInt* &binary_num) {
    bin_num2.sign = -bin_num2.sign;
    Bin_Add(&bin_num1, &bin_num2,binary_num);
 
}

// �����ƴ����˷�����
void Bin_Mul(BigInt* bin_num1, BigInt* bin_num2,BigInt* &binary_num) {
    if (bin_num1 == NULL || bin_num2 == NULL) return;

    int len1 = strlen(bin_num1->Binary);
    int len2 = strlen(bin_num2->Binary);
    // ����λ���
    binary_num->sign = bin_num1->sign * bin_num2->sign; 
    // �����㹻���ڴ�
    binary_num->Binary = (char*)calloc(len1 + len2 + 1, sizeof(char)); 
    // ��ʼ��Ϊ'0'
    memset(binary_num->Binary, '0', len1 + len2); 

    // ��λ��ˣ�Ȼ���ۼ�
    for (int i = len1 - 1; i >= 0; --i) {
        for (int j = len2 - 1; j >= 0; --j) {
        	// ���㵱ǰλ�ĳ˻�
            int product = (bin_num1->Binary[i] - '0') * (bin_num2->Binary[j] - '0');
			// ���㵱ǰλ�ĺͣ�������λ�� 
            int carry = (binary_num->Binary[i + j + 1] - '0') + product;
			// ���µ�ǰλ��ֵ 
            binary_num->Binary[i + j + 1] = carry % 2 + '0';
			// ���½�λ 
            binary_num->Binary[i + j] += carry / 2; 
        }
    }

    // ȥ��ǰ����
    int idx = 0;
    while (binary_num->Binary[idx] == '0' && binary_num->Binary[idx + 1] != '\0') {
        ++idx;
    }
    memmove(binary_num->Binary, binary_num->Binary + idx, strlen(binary_num->Binary) - idx + 1);
    return;
}
//�����ƴ�����������
BigInt* Bin_Div(BigInt* bin_num1, BigInt* bin_num2, BigInt**remainder) {
    if (bin_num1 == NULL || bin_num2 == NULL) return NULL;
    if (strcmp(bin_num2->Binary, "0") == 0) {
        *remainder = NULL; 
		return NULL;
    }
	// ���ڴ洢��
    BigInt* quotient = (BigInt*)malloc(sizeof (BigInt)); 
    // �����̵ķ���λ
    quotient->sign = bin_num1->sign * bin_num2->sign; 
//�������ĳ���
    int dividend_len = strlen(bin_num1->Binary);
    // ��������
    int divisor_len = strlen(bin_num2->Binary); 
    // �������̵ĳ���
    int quotient_len = abs(dividend_len - divisor_len) + 2; 
    quotient->Binary = (char*)calloc(quotient_len, sizeof(char));
   
// ���ڴ洢��ǰ������ 
    BigInt* dividend = (BigInt*)malloc(sizeof(BigInt)); 
    dividend->sign = 1;
    dividend->Binary = (char*)calloc(dividend_len + 1, sizeof(char));
    strcpy(dividend->Binary, bin_num1->Binary);
// ���ڴ洢����
    BigInt* divisor = (BigInt*)malloc(sizeof(BigInt)); 
    divisor->sign = 1;
    divisor->Binary = (char*)calloc(divisor_len + 1, sizeof(char));
    strcpy(divisor->Binary, bin_num2->Binary);

    // �������������ֵС�ڳ�������ֵ������Ϊ0������Ϊ������
    if (Bin_Cmp(dividend,divisor) < 0) {
        strcpy(quotient->Binary, "0");
        dividend->sign = bin_num1->sign;
        *remainder = dividend;

        return quotient;
    }
    // ������������ڳ���������Ϊ1������Ϊ'+'0
    else if (Bin_Cmp(dividend, divisor) == 0) { 
        strcpy(quotient->Binary, "1");
        BigInt* tmp = (BigInt*)malloc(sizeof(BigInt));
        tmp->sign = 1; tmp->Binary[0] = '0'; 
        *remainder = tmp;
        return quotient;
    }

    /*
    ˼�룺ALU��λ����
		1.�жϵ�ǰ ��������dividend�� �Ƿ���� ������divisor��
		2.����1�������̵��������Ϊ0 ����1 ֱ�ӵ�7  
		3.��¼���ƶ��뱻������ĳ��� 
		4. �ü���ģ��������� 
		5.ת1�жϽ�� 
		6.��󱻳���ʣ�µľ���������
	*/
// ������Ҫ���������Ƶ�λ��
    int shift = dividend_len - divisor_len; 
// �洢���ƺ�ĳ���
    BigInt* shifted_divisor = (BigInt*)malloc(sizeof(BigInt)); 
    shifted_divisor->sign = 1;
    shifted_divisor->Binary = (char*)calloc(divisor_len + shift + 1, sizeof(char));
    strcpy(shifted_divisor->Binary, divisor->Binary);

    // ���������ƣ���0
    for (int i = 0; i < shift; ++i) {
        strcat(shifted_divisor->Binary, "0");
    }

    // �ü���ģ���������
    int quotient_pos = 0;
    while (shift >= 0) {
        // �����������ڵ������ƺ�ĳ���ʱ�����±��������̵Ķ�Ӧλ 
        quotient->Binary[quotient_pos] += '0';
        while (Bin_Cmp(dividend, shifted_divisor) >= 0) {
        	// ���±�����
            Bin_Sub(*dividend, *shifted_divisor,dividend); 
			// �����̵Ķ�Ӧλ
            quotient->Binary[quotient_pos]++; 
            
        }
        // ����������һλ
        shifted_divisor->Binary[strlen(shifted_divisor->Binary) - 1] = '\0'; 
        --shift;
        ++quotient_pos;
      
    }
// ����ַ�����ֹ��
    quotient->Binary[quotient_pos] = '\0'; 
    dividend->sign = bin_num1->sign;
// ��������
    *remainder = dividend; 
    return quotient;
}
int main(){
	char num1[100],num2[100];
	int expression = 0;
	printf("����������еĲ���:1.�ӷ�2.����3.�˷�4.����:\n");
	while(scanf("%d", &expression)){   
    printf("�������һ����������\n");
    scanf("%s", num1);
    BigInt* binary_num1 = (BigInt*)malloc(sizeof(BigInt));
    BigIntToBinary(num1,binary_num1);
    
   	printf("������ڶ�����������\n");
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
			printf("��Ϊ��%s\n",BinaryToBigInt(quotient));
		    printf("����Ϊ��%s\n",BinaryToBigInt(remainder));
		    BigIntFree(binary_num1);
		    BigIntFree(binary_num2);
		    BigIntFree(quotient);
		    BigIntFree(remainder);
		    break;
		}
	    default:
	    	return 0;
		}
		printf("����������еĲ���:1.�ӷ�2.����3.�˷�4.����:\n");
	}
}
