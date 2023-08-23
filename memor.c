#include "shell.h"

/**
 * free_buffer – it will be for giving out pointer and nulling the adress
 * @_pointer: location of the ptr to be freed
 *
 * Return: return 1 for the succes , else 0.
 */
int free_buffer(void **_pointer)
{
  if (_pointer && *_pointer)
  {
    free(*_pointer);
    *_pointer = NULL;
    return (1);
  }
  return (0);
}
