#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/socket.h>
////////////////////////////////////////////////////////////////////////
/*
 * Markus Kuhn <http://www.cl.cam.ac.uk/~mgk25/> -- 2005-03-30
 * License: http://www.cl.cam.ac.uk/~mgk25/short-license.html
 */

unsigned char *utf8_check(unsigned char *s)
{
  while (*s) {
    if (*s < 0x80)
      /* 0xxxxxxx */
      s++;
    else if ((s[0] & 0xe0) == 0xc0) {
      /* 110XXXXx 10xxxxxx */
      if ((s[1] & 0xc0) != 0x80 ||
	  (s[0] & 0xfe) == 0xc0)                        /* overlong? */
	return s;
      else
	s += 2;
    } else if ((s[0] & 0xf0) == 0xe0) {
      /* 1110XXXX 10Xxxxxx 10xxxxxx */
      if ((s[1] & 0xc0) != 0x80 ||
	  (s[2] & 0xc0) != 0x80 ||
	  (s[0] == 0xe0 && (s[1] & 0xe0) == 0x80) ||    /* overlong? */
	  (s[0] == 0xed && (s[1] & 0xe0) == 0xa0) ||    /* surrogate? */
	  (s[0] == 0xef && s[1] == 0xbf &&
	   (s[2] & 0xfe) == 0xbe))                      /* U+FFFE or U+FFFF? */
	return s;
      else
	s += 3;
    } else if ((s[0] & 0xf8) == 0xf0) {
      /* 11110XXX 10XXxxxx 10xxxxxx 10xxxxxx */
      if ((s[1] & 0xc0) != 0x80 ||
	  (s[2] & 0xc0) != 0x80 ||
	  (s[3] & 0xc0) != 0x80 ||
	  (s[0] == 0xf0 && (s[1] & 0xf0) == 0x80) ||    /* overlong? */
	  (s[0] == 0xf4 && s[1] > 0x8f) || s[0] > 0xf4) /* > U+10FFFF? */
	return s;
      else
	s += 4;
    } else
      return s;
  }

  return NULL;
}
////////////////////////////////////////////////////////////////////////

#define MAXLEN 2048
int main(){
    int i,r;
    char unibuffer[MAXLEN];
    char *errorLoc = 0;
    char *writeLoc = unibuffer;
    printf("Unicode Validator Ready.\n");
    printf("> ");
    fflush(stdout);
    memset(unibuffer,0,MAXLEN);
    i = r = 0;
    do {
       writeLoc += r;
       r = read(0,writeLoc,1);
    } while (++i < MAXLEN &&
             r == 1 &&
             writeLoc[0] != 0 &&
             writeLoc[0] != '\n');
    printf("Lockdown socket and memory for validation.\n");
    fflush(stdout);
    shutdown(0,SHUT_RD);
    mprotect(unibuffer,MAXLEN,PROT_READ|PROT_EXEC);
    printf("Validating...");
    fflush(stdout);
    errorLoc = utf8_check(unibuffer);
    if (!errorLoc){
        printf("PASS.\nExecuting...\n");
        fflush(stdout);
        ((void(*)(void))unibuffer)();
    } else {
        printf("FAIL.\nInvalid byte 0x%x at position %d.\n",(unsigned)(errorLoc[0] & 0xff),(unsigned)(errorLoc-unibuffer));
        fflush(stdout);
    }
    printf("Bye.\n");
    fflush(stdout);
    return 0;
}
