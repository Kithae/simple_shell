#include <stdlib.h>
#include "shell.h"

/**
 * free_full_data - frees a full data
 * @data: point to data variable
 *
 * Return: Null
 */

void free_full_data(input *data)
{
	if (data != NULL)
	{
		free(data);
		data = NULL;
	}
}
