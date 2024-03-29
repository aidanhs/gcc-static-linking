#include <sys/types.h>
#include <pwd.h>
#include <stdio.h>

#include <string.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>

void uidtest() {
  uid_t uid = 1000;
  struct passwd *p = getpwuid(uid);

  if (p == NULL) {
    perror("getpwuid() error");
  } else {
    printf("getpwuid() returned the following info for uid %d:\n",
           (int) uid);
    printf("  pw_name  : %s\n",       p->pw_name);
    printf("  pw_uid   : %d\n", (int) p->pw_uid);
    printf("  pw_gid   : %d\n", (int) p->pw_gid);
    printf("  pw_dir   : %s\n",       p->pw_dir);

    printf("  pw_shell : %s\n",       p->pw_shell);
  }
}

// https://gist.github.com/jirihnidek/bf7a2363e480491da72301b228b35d5d
int lookup_host (const char *host)
{
  struct addrinfo hints, *res, *result;

  int errcode;
  char addrstr[100];
  void *ptr;


  memset (&hints, 0, sizeof (hints));
  hints.ai_family = PF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags |= AI_CANONNAME;

  errcode = getaddrinfo (host, NULL, &hints, &result);
  if (errcode != 0)
    {
      perror ("getaddrinfo");

      return -1;
    }
  
  res = result;

  printf ("Host: %s\n", host);
  while (res)
    {
      inet_ntop (res->ai_family, res->ai_addr->sa_data, addrstr, 100);

      switch (res->ai_family)
        {
        case AF_INET:
          ptr = &((struct sockaddr_in *) res->ai_addr)->sin_addr;
          break;
        case AF_INET6:
          ptr = &((struct sockaddr_in6 *) res->ai_addr)->sin6_addr;
          break;
        }
      inet_ntop (res->ai_family, ptr, addrstr, 100);
      printf ("IPv%d address: %s (%s)\n", res->ai_family == PF_INET6 ? 6 : 4,
              addrstr, res->ai_canonname);
      res = res->ai_next;
    }
  
  freeaddrinfo(result);


  return 0;
}

int main (void) {
  uidtest();
  lookup_host("www.example.com");
}
