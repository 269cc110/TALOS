/*	Copyright (c) 2016 condorcraft110
 *	
 *	Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *	
 *	The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *	
 *	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <stdint.h>
#include <stdlib.h>

#define _ALLOC_USED 1

typedef struct
{
	uint32_t size;
} unit;

typedef struct
{
	unit *heap;
	unit *free;
} system_memory;

static system_memory msys;

static unit *compact(unit *p, uint32_t nsize)
{
	uint32_t bsize = 0;
	uint32_t psize;
	unit *best = p;
	
	while(psize = p->size, psize)
	{
		if(psize & _ALLOC_USED)
		{
			if(bsize != 0)
			{
				best->size = bsize;
				
				if(bsize >= nsize)
				{
					return best;
				}
			}
			
			bsize = 0;
			best = p = (unit *)((uint32_t)p + (psize & ~_ALLOC_USED));
		}
		else
		{
			bsize += psize;
			
			if(bsize >= nsize)
			{
				return best;
			}
		}
	}
	
	if(bsize != 0)
	{
		best->size = bsize;
		
		if(bsize >= nsize)
		{
			return best;
		}
	}
	
	return 0;
}

void free(void *ptr)
{
	if(ptr)
	{
		unit *p = (unit *)((uint32_t)ptr - sizeof(unit));
		
		p->size &= ~_ALLOC_USED;
	}
}

void *malloc(uint32_t size)
{
	uint32_t fsize;
	unit *p;
	
	if(size == 0) return 0;
	
	size += 3 + sizeof(unit);
	
	size <<= 2;
	size >>= 2;
	
	if(msys.free == 0 || size > msys.free->size)
	{
		msys.free = compact(msys.heap, size);
		if(msys.free == 0) return 0;
	}
	
	p = msys.free;
	fsize = msys.free->size;
	
	if(fsize >= size + sizeof(unit))
	{
		msys.free = (unit *)((uint32_t)p + size);
		msys.free->size = fsize - size;
	}
	else
	{
		msys.free = 0;
		size = fsize;
	}
	
	p->size = size | _ALLOC_USED;
	
	return (void *)((uint32_t)p + sizeof(unit));
}

void msys_init(void *heap, uint32_t len)
{
	len += 3;
	len <<= 2;
	len >>= 2;
	
	msys.free = msys.heap = (unit *)heap;
	msys.free->size = msys.heap->size = len - sizeof(unit);
	*(uint32_t *)((char *)heap + len - 4) = 0;
}

void msys_compact()
{
	msys.free = compact(msys.heap, 0x7FFFFFFF);
}

