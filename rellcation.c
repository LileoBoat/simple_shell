#include "shell.h"

/**
**cust_mem_set – will fill memory some no change byte value
*@sh_cke: it points to where the memory is located
*@bit: shows where the size in bytes is filled fill *sh_cke with
*@n: having a size bytes that will be filled.
*Return: (sh_cke) points to memory location sh_cke
*/
char *cust_mem_set(char *sh_cke, char bit, unsigned int n)

{
unsigned int i;

for (i = 0; i < n; i++)
sh_cke[i] = bit;
return (sh_cke);
}

/**
* allocate_custom_free - release the memory occupied by a str array
* @point_p: arrays containing strs
*/
void allocate_custom_free(char **point_p)
{
char **a = point_p;

if (!point_p)
return;
while (*point_p)
free(*point_p++);
free(a);
}

/**

* custom_rellocmemory – changes where memory is allocated.
* @_pointer: in the previous block it mallocate
* @prev_sz: gives size in bytes of the initial code
* @nxt_sz: gives the size of new code in bytes
*
* Return: return points to the block name.
*/
void *custom_rellocmemory(void *_pointer, unsigned int prev_sz, unsigned int nxt_sz)
{
char *jl;

if (!_pointer)
return (malloc(nxt_sz));
if (!nxt_sz)
return (free(_pointer), NULL);
if (nxt_sz == prev_sz)
return (_pointer);

jl = malloc(nxt_sz);
if (!jl)
return (NULL);

prev_sz = prev_sz < nxt_sz ? prev_sz : nxt_sz;
while (prev_sz--)

jl[prev_sz] = ((char *)_pointer)[prev_sz];
free(_pointer);
return (jl);
}
