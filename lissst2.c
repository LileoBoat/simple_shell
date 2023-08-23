#include "shell.h"

/**
* add_point - insert a point to the list start
* @lead: locate a ptr referring to initial point
* @str: string value of point
* @number: index of point used in logs
*
* Return: len of lists
*/
list_t *add_point(list_t **lead, const char *str, int number)
{
list_t *frs_lead;

if (!lead)
return (NULL);
frs_lead = malloc(sizeof(list_t));

if (!frs_lead)
return (NULL);
cust_mem_set((void *)frs_lead, 0, sizeof(list_t));
frs_lead->number = number;
if (str)
{
frs_lead->str = duplicat_str(str);
if (!frs_lead->str)
{
free(frs_lead);
return (NULL);
}
}
frs_lead->next = *lead;
*lead = frs_lead;
return (frs_lead);
}

/**
* append_point - insert a point to the list end
* @lead: locate a ptr referring to initial point
* @str: string value of point
* @number: index of point used in logs
*

* Return: len of lists
*/
list_t *append_point(list_t **lead, const char *str, int number)
{
list_t *frs_point, *point;

if (!lead)
return (NULL);

point = *lead;
frs_point = malloc(sizeof(list_t));
if (!frs_point)
return (NULL);
cust_mem_set((void *)frs_point, 0, sizeof(list_t));
frs_point->number = number;
if (str)
{
frs_point->str = duplicat_str(str);
if (!frs_point->str)
{
free(frs_point);
return (NULL);
}
}

if (point)
{
while (point->next)
point = point->next;
point->next = frs_point;
}
else
*lead = frs_point;
return (frs_point);
}

/**
* display_list_str -display every string element in a linked list
* @bob: ptr to start point
*
* Return: len of lists
*/
size_t display_list_str(const list_t *bob)
{
size_t i = 0;

while (bob)
{
_puts(bob->str ? bob->str : "(nil)");

_puts("\n");
bob = bob->next;
i++;
}
return (i);
}

/**
* del_env_node_index - remove the point located at provided index
* @lead: locate a ptr referring to initial point
* @index: the point index to be remove
*
* Return: return 1 if successful, else return -1 if failed
*/
int del_env_node_index(list_t **lead, unsigned int index)
{
list_t *point, *bfr_point;
unsigned int i = 0;

if (!lead || !*lead)
return (0);

if (!index)
{

point = *lead;
*lead = (*lead)->next;
free(point->str);
free(point);
return (1);
}
point = *lead;
while (point)
{
if (i == index)
{
bfr_point->next = point->next;
free(point->str);
free(point);
return (1);
}
i++;
bfr_point = point;
point = point->next;
}
return (0);
}

/**

* allocate_free_list - release the point with rel_all_resources
* @lead_pointer: Mem location of a ptr tot the start point
*
* Return: void
*/
void allocate_free_list(list_t **lead_pointer)
{
list_t *point, *afr_point, *lead;

if (!lead_pointer || !*lead_pointer)
return;
lead = *lead_pointer;
point = lead;
while (point)
{
afr_point = point->next;
free(point->str);
free(point);
point = afr_point;
}
*lead_pointer = NULL;
}
