#ifndef __INCLUDED_QUEUE_H__
#define __INCLUDED_QUEUE_H__

#include "util.h"

// refer to kfifo in kernel, would be MP-safe in scene of single producer and
// single comsumer
typedef struct _queue_node_t
{
  uint64_t struct_size;
} queue_node_t;

typedef struct
{
  uint8_t *buffer;
  uint64_t size;
  uint64_t in;
  uint64_t out;
} queue_t;

static inline void queue_init (queue_t *queue, uint8_t *buffer, uint64_t size);
static inline uint64_t queue_len (queue_t *queue);
static inline uint64_t queue_size (queue_t *queue);
static inline uint64_t queue_avail (queue_t *queue);
static inline void queue_reset (queue_t *queue);
static inline uint64_t queue_in (queue_t *queue, const void *from,
                                 uint64_t len, uint64_t queue_node_offset);
static inline uint64_t queue_in_byte (queue_t *queue, const void *from,
                                      uint64_t len);
static inline uint64_t queue_out (queue_t *queue, void *to,
                                 uint64_t len, uint64_t queue_node_offset);
static inline uint64_t queue_out_byte (queue_t *queue, void *to,
                                      uint64_t len);

static inline void
__queue_in_data (queue_t *queue, const void *from, uint64_t len)
{
  uint64_t l = 0;

  /*
   * Ensure that we sample the queue->out index -before- we
   * start putting bytes into the queue.
   */
  COMPILER_BARRIER ();

  /* first put the data starting from queue->in to buffer end */
  l = min (len, queue->size - queue->in);
  _my_memcpy_imp (queue->buffer + queue->in, from, l);

  /* then put the rest (if any) at the beginning of the buffer */
  _my_memcpy_imp (queue->buffer, from + l, len - l);
  return;
}

static inline void
__queue_out_data (queue_t *queue, void *to, uint64_t len)
{
  uint64_t l = 0;

  /*
   * Ensure that we sample the fifo->in index -before- we
   * start removing bytes from the kfifo.
   */
  COMPILER_BARRIER ();

  /* first get the data from fifo->out until the end of the buffer */
  l = min (len, queue->size - queue->out);
  _my_memcpy_imp (to, queue->buffer + queue->out, l);

  /* then get the rest (if any) from the beginning of the buffer */
  _my_memcpy_imp (to + l, queue->buffer, len - l);
  return;
}

static inline void
__queue_add_in (queue_t *queue, uint64_t off)
{
  COMPILER_BARRIER ();
  queue->in = queue->in + off <= queue->size ? queue->in + off
                                             : off - (queue->size - queue->in);
  COMPILER_BARRIER ();
  return;
}

static inline void
__queue_add_out (queue_t *queue, uint64_t off)
{
  COMPILER_BARRIER ();
  queue->out = queue->out + off <= queue->size ? queue->out + off
                                             : off - (queue->size - queue->out);
  COMPILER_BARRIER ();
  return;
}

static inline void
queue_init (queue_t *queue, uint8_t *buffer, uint64_t size)
{
  queue->buffer = buffer;
  queue->size = size;
  queue_reset (queue);
  return;
}

static inline uint64_t
queue_size (queue_t *queue)
{
  return queue->size;
}

static inline uint64_t
queue_len (queue_t *queue)
{
  return queue->in < queue->out ? queue->in + queue->size - queue->out
                                : queue->in - queue->out;
}

static inline uint64_t
queue_avail (queue_t *queue)
{
  return queue_size (queue) - queue_len (queue);
}

static inline void
queue_reset (queue_t *queue)
{
  queue->in = 0;
  queue->out = 0;
  return;
}

static inline uint64_t
queue_in (queue_t *queue, const void *from, uint64_t len,
          uint64_t queue_node_offset)
{
  uint64_t i = 0;
  uint64_t ele_len = 0;
  uint64_t in_len = 0;
  uint64_t total_len = 0;

  for (; i < len; i++)
    {
      ele_len = ((queue_node_t *)(from + queue_node_offset))->struct_size;
      if (queue_avail (queue) < ele_len)
        break;
      in_len = queue_in_byte (queue, from + total_len, ele_len);
      total_len += in_len;
    }
  return total_len;
}

static inline uint64_t
queue_in_byte (queue_t *queue, const void *from, uint64_t len)
{
  len = min (queue_avail (queue), len);
  __queue_in_data (queue, from, len);
  __queue_add_in (queue, len);
  return len;
}

static inline uint64_t
queue_out (queue_t *queue, void *to, uint64_t len,
          uint64_t queue_node_offset)
{
  uint64_t i = 0;
  uint64_t ele_len = 0;
  uint64_t out_len = 0;
  uint64_t total_len = 0;

  for (; i < len; i++)
    {
      ele_len = ((queue_node_t *)(to + queue_node_offset))->struct_size;
      if (queue_len (queue) < ele_len)
        break;
      out_len = queue_out_byte (queue, to + total_len, ele_len);
      total_len += out_len;
    }
  return total_len;
}

static inline uint64_t
queue_out_byte (queue_t *queue, void *to, uint64_t len)
{
  len = min (queue_len (queue), len);
  __queue_out_data (queue, to, len);
  __queue_add_out (queue, len);
  return len;
}

#endif /* __INCLUDED_LIST_H__ */