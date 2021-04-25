#include "asymmetric.h"
#include <stdio.h>
#include <stdint.h>

void RSA_get(uint32_t p,uint32_t q, uint32_t *ret_N, uint32_t *ret_e, uint32_t *ret_d)
{
    uint32_t N;
    uint32_t r;
    uint32_t e;
    uint32_t i;
    N = p*q;
    r = (p-1)*(q-1);
    e = 1;
    while((r%e)==0)
    {
        e++;
    }
    i = 1;
    while((i*r+1)%e!=0)
    {
        i++;
    }
    *ret_N = N;
    *ret_d = (i*r+1)/e;
    *ret_e = e;
#ifdef DEBUG_RSA
    printf("\nN:\n----------------------------------\n| N = p*q -> %u*%u = %u\n\n",p,q,*ret_N);
    printf("r:\n----------------------------------\n| r = (p-1)*(q-1) -> (%u-1)*(%u-1) = %u\n\n",p,q,r);
    printf("e:\n----------------------------------\n| r mod e != 0 -> %u mod %u = %u\n\n",r,*ret_e,(r%(*ret_e)));
    printf("d:\n----------------------------------\n| (e*d) mod r = 1 -> (%u*%u) mod %u = 1\n\n\n",*ret_e,*ret_d,r);
    printf("----------------------------------\n- p: %u\n- q: %u\n- N: %u\n- r: %u\n- e: %u\n- d: %u\n",p,q,*ret_N,r,*ret_e,*ret_d);
    printf("----------------------------------\npublic: (N: %u, e: %u)\nprivate: (N: %u, d: %u)\n",*ret_N,*ret_e,*ret_N,*ret_d);
#endif // DEBUG_RSA
}
