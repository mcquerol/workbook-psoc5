/*
 * ringbuffer.c
 *
 *  Created on: 13 Mar 2023
 *      Author: Mateo Ceballos Querol
 */

#include "Ringbuffer.h"
#include <stdlib.h>
#include <stdio.h>

RC_t ringbuffer_init(ringbuffer_t *const me, uint8_t size)
{
	me->m_size = size;
	me->m_buffer = (uint8_t*)malloc(size * sizeof(uint8_t));

	ringbuffer_clear(me);


	return RC_SUCCESS;
}

RC_t ringbuffer_deinit(ringbuffer_t *const me)
{
	free(me->m_buffer);

	return RC_SUCCESS;
}

RC_t ringbuffer_write(ringbuffer_t *const me, uint8_t data)
{
    
	if (me->m_fillLevel < me->m_size)
	{
		me->m_buffer[me->m_writeIndex] = data;
		me->m_writeIndex %= me->m_size;
		me->m_writeIndex++;
		me->m_fillLevel++;


		return RC_SUCCESS;
	}
	else
	{
		return RC_ERROR_BUFFER_FULL;
	}

	return RC_SUCCESS;
}

RC_t ringbuffer_read(ringbuffer_t *const me, uint8_t *const data)
{
	if(me->m_fillLevel > 0)
	{
		*data = me->m_buffer[me->m_readIndex];
		me->m_readIndex++;
		me->m_readIndex %= me->m_size;
		me->m_fillLevel--;

	}
	else
	{
		return RC_ERROR_BUFFER_EMTPY;
	}

	return RC_SUCCESS;
}

RC_t ringbuffer_clear(ringbuffer_t *const me)
{
	me->m_fillLevel = 0;
	me->m_readIndex = 0;
	me->m_writeIndex = 0;

	return RC_SUCCESS;
}
