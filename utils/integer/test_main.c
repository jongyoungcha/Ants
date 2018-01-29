#include "chk_num.h"


int main(int argc, char* argv[])
{
    int ret = 0;

    const char* num_str = "10000000";
    const char* non_num_str1 = "0000022";
    const char* non_num_str2 = "testtest";
    const char* non_num_str3 = "0test001";

    ret = ants_is_decimal_str(num_str);
    if (ret == -1)
    {
	printf("test1 failed....\n");
    }

    ret = ants_is_decimal_str(non_num_str1);
    if (ret == -1)
    {
	printf("test2 failed....\n");
    }

    ret = ants_is_decimal_str(non_num_str2);
    if (ret == -1)
    {
	printf("test3 failed....\n");
    }

    ret = ants_is_decimal_str(non_num_str3);
    if (ret == -1)
    {
	printf("test4 failed....\n");
    }
    
    return ret;
}
    
