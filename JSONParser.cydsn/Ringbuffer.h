/*
 * ringbuffer.h
 *
 *  Created on: 13 Mar 2023
 *      Author: robom
 */

#include "global.h"

#ifndef RINGBUFFER_H_
#define RINGBUFFER_H_

	struct ringbuffer
	{
		uint8_t *m_buffer;
		uint8_t m_size;
		uint8_t m_readIndex;
		uint8_t m_writeIndex;
		uint8_t m_fillLevel;
	};

	typedef struct ringbuffer ringbuffer_t;

	RC_t ringbuffer_init(ringbuffer_t *const me, uint8_t size);
	RC_t ringbuffer_deinit(ringbuffer_t *const me);
	RC_t ringbuffer_write(ringbuffer_t *const me, uint8_t data);
	RC_t ringbuffer_read(ringbuffer_t *const me, uint8_t *const data);
	RC_t ringbuffer_clear(ringbuffer_t *const me);

#endif /* RINGBUFFER_H_ */