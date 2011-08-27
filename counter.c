#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

int main(){
    int i;
    char dig;
    char *rec1 = "Aug 23 00:00:11 ns1 dhcpd: DHCPACK on 128.193.94.168 to ff:ff:ff:ff:ff:ff via 128.193.94.1";

    char *rec2 = "Aug 23 00:00:02 ns1 dhcpd: DHCPNAK on 10.0.0.79 to ff:ff:ff:ff:ff:ff via 10.196.8.1";
    char * o_buff = (char *)malloc(200);
    int written = 0;

    printf("%s\n%s\n",rec1,rec2);

    /*
    for( i=0; i < strlen(rec1) ; i++) {
        printf("%i %c \n ",i,rec1[i]);
    }
    printf("===================\n");
    for( i=0; i < strlen(rec2) ; i++) {
        printf("%i %c \n ",i,rec2[i]);
    }
    i=0;
    for ( i=3, dig = rec1[i]; dig != 'n'; i++, dig = rec1[i] ){
        printf("i: %d, dig: %c\n",i,dig);
    }
     *
     */
    printf("ACK\n");
    // timestap plus extra space
    memcpy(o_buff+written , rec1, 16);
    written += 16;
    // "ACK "
    memcpy(o_buff+written, "ACK ", 4);
    written += 4;
    // IP - ip start on character 38
    for( i= 38, dig = rec1[i] ; dig != ' ' ; i++, dig = rec1[i] ){
        continue;
    }
    memcpy(o_buff+written, rec1+38, i-38 );
    written += i-37; // We want to catch that extra space.
    // Mac we stopped at space after ip. Add four bytes and we are at mac.
    memcpy(o_buff+written,rec1+i+4, 17);
    written += 17; //12 hex + 5 colons
    o_buff[++written] = '\n';
    o_buff[++written] = '0';
    printf("Line parse: %s\n",o_buff);
}
