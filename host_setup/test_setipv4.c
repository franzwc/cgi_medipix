#include <stdio.h>
#include "../utils/net_utils.h"
#include "../utils/global.h"


int main (int argc, char **argv)
{
  printf ("Testando troca de ip\n");
  host_network_param_t host;
  if (argc < 4)
    {
      printf ("Invalid argument number\n");
      return -1;
    }
  strcpy (host.ip_address, argv[1]);
  strcpy (host.mask, argv[2]);
  strcpy (host.gateway, argv[3]);
  printf ("Configuracao aplicada com sucesso? %d\n", setIPV4 (&host));
  return 0;

}
