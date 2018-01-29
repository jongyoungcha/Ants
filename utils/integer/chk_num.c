#include "chk_num.h"

int ants_is_decimal_str(char* str)
{
    int ret = 0;
    int len = strlen(str);
    char* pos_curr = NULL;
    int i = 0;

    pos_curr = str;

    if ( *pos_curr <= 48 &&  57 >= *pos_curr ) 
    {
	return -1;
    }
    
    for (i=0; i<len; i++)
    {
	ret = ants_is_decimal_ch(*(pos_curr + i));
	if(ret == -1)
	{
	    return -1;
	}
    }
    
    return 0;
}


int ants_is_decimal_ch(char ch)
{
    if (48 <= ch && ch <= 57)
    {
	return 0;
    }
	
    return -1;
}




