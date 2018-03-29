#include "str2hex.h"

int main(){
    
    int ret = 0;

    char ch_origin = 'a';
    char chs_hex[2];
    
    char* str_origin="test test message\n";
    char str_hex[8192] = {0};
    ants_ch2hex(ch_origin, chs_hex);
    printf("hex : %s\n", chs_hex);
 
    ants_str2hex(str_origin, str_hex, 8192, NULL);
    printf("hex : %s\n", str_hex);

    str_hex[0] = '\0';
    printf("hex : %s\n", str_hex);
    memset(str_hex, 0x00, sizeof(str_hex));
    
    if(ants_str2hex(str_origin, str_hex, 8192, "||") == -1)
    {
		printf("failed...\n");
    }

    printf("hex : %s\n", str_hex);
    
    return ret;
}
