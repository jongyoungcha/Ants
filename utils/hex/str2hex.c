#include "str2hex.h"

int ants_ch2hex(unsigned char ch, char* chs_hex)
{
    int ret = 0;

    if (chs_hex == NULL)
    {
		return -1;
    }

    if (0 < ch && ch < 255)
    {
		sprintf(chs_hex, "%x", ch);
    }
    else
    {
		return -1;
    }
    
    return ret;
}


int ants_str2hex(char* str, char* str_hex, int len_limit, char* delimit)
{
    int ret = 0;
    int len_hex = 0;
    
    unsigned char* offs_str = NULL;

    if (str == NULL || str_hex == NULL || len_limit <= 0)
    {
		/* fprintf(stderr, "checking error\n"); */
		return  -1;
    }

    for (offs_str = (unsigned char*)str;
		 *offs_str != '\0';
		 offs_str++)
    {
		if (++len_hex > len_limit)
		{
			/* fprintf(stderr, "Length of hex was longer than limit.\n"); */
			return -1;
		}
	
		sprintf(str_hex + strlen(str_hex), "%x", *offs_str);
	
		if (delimit)
		{
			if (( len_hex += strlen(delimit )) > len_limit)
			{
				return -1;
			}
	    
			sprintf(str_hex + strlen(str_hex), "%s", delimit);
		}
    }

    return ret;
}









