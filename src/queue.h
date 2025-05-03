#ifndef __INCLUDED_QUEUE_H__
#define __INCLUDED_QUEUE_H__

#include "util.h"
#include "vec.h"

// refer to kfifo in kernel, would be MP-safe in scene of single producer and
// single comsumer

static inline void *queue_alloc (uint32_t ele_size, uint32_t size);
static inline void queue_free (void *queue) {vec_free (queue);}
static inline void queue_reset (void *queue);
static inline uint32_t queue_len (void *queue);
static inline uint32_t queue_size (void *queue) {return vec_size (queue);}
static inline uint32_t queue_avail (void *queue);
static inline uint32_t queue_in (void *queue, const void *from, uint32_t len);
static inline uint32_t queue_out (void *queue, void *to, uint32_t len);
static inline uint32_t queue_in1 (void *queue, const void *from);
static inline uint32_t queue_out1 (void *queue, void *to);

static inline void *
queue_alloc (uint32_t ele_size, uint32_t size)
{
  void *ret = vec_alloc (ele_size, size);
  queue_reset (ret);
  return ret;
}

static inline void
queue_reset (void *queue)
{
  ((uint64_t *)(vec_userdata (queue)))[0] = 0;
  return;
}

static inline uint32_t
queue_len (void *queue)
{
  uint32_t* queue_data = (uint32_t *)(vec_userdata (queue));
  uint32_t in = queue_data[0];
  uint32_t out = queue_data[1];

  return in < out ? in + queue_size(queue) - out: in - out;
}

static inline uint32_t
queue_avail (void *queue)
{
  return queue_size (queue) - queue_len (queue);
}


static inline void
__queue_in_data (void *queue, const void *from, uint32_t len)
{
  uint32_t l = 0;
  /*
  * Ensure that we sample the queue->out index -before- we
  * start putting bytes into the queue.
  */
 COMPILER_BARRIER ();
 uint32_t in = (uint32_t *)(vec_userdata (queue))[0];

  /* first put the data starting from queue->in to buffer end */
  l = min (len, queue_size(queue) - in);
  _my_memcpy_imp (queue + in, from, l);

  /* then put the rest (if any) at the beginning of the buffer */
  _my_memcpy_imp (queue, from + l, len - l);
  return;
}

static inline void
__queue_out_data (void *queue, void *to, uint32_t len)
{
  uint32_t l = 0;

  /*
   * Ensure that we sample the fifo->in index -before- we
   * start removing bytes from the kfifo.
   */
  COMPILER_BARRIER ();
  uint32_t out = (uint32_t *)(vec_userdata (queue))[1];

  /* first get the data from fifo->out until the end of the buffer */
  l = min (len, queue_size(queue) - out);
  _my_memcpy_imp (to, queue + out, l);

  /* then get the rest (if any) from the beginning of the buffer */
  _my_memcpy_imp (to + l, queue, len - l);
  return;
}

static inline void
__queue_add_in (void *queue, uint32_t off)
{
  COMPILER_BARRIER ();
  uint32_t in = (uint32_t *)(vec_userdata (queue))[0];
  uint32_t size = queue_size(queue);
  (uint32_t *)(vec_userdata (queue))[0] = in + off <= size ? in + off : off - (size - in);
  COMPILER_BARRIER ();
  return;
}

static inline void
__queue_add_out (void *queue, uint32_t off)
{
  COMPILER_BARRIER ();
  uint32_t out = (uint32_t *)(vec_userdata (queue))[1];
  uint32_t size = queue_size(queue);
  (uint32_t *)(vec_userdata (queue))[1] = out + off <= size
                   ? out + off
                   : off - (size - out);
  COMPILER_BARRIER ();
  return;
}

static inline uint32_t
queue_in (void *queue, const void *from, uint32_t len)
{
  uint32_t i = 0;
  uint32_t ele_len = 0;
  uint32_t in_len = 0;
  uint32_t total_len = 0;
  uint32_t ele_size = _vec_find(queue)->ele_size;

  for (; i < len; i++)
    {
      if (queue_avail (queue) < ele_len)
        break;
      in_len = queue_in_byte (queue, from + total_len, ele_len);
      total_len += in_len;
    }
  return total_len;
}

static inline uint32_t
queue_in_byte (void *queue, const void *from, uint32_t len)
{
  len = min (queue_avail (queue), len);
  __queue_in_data (queue, from, len);
  __queue_add_in (queue, len);
  return len;
}

static inline uint32_t
queue_out (void *queue, void *to, uint32_t len)
{
  uint32_t i = 0;
  uint32_t ele_len = 0;
  uint32_t out_len = 0;
  uint32_t total_len = 0;
  uint32_t ele_size = _vec_find(queue)->ele_size;

  for (; i < len; i++)
    {
      if (queue_len (queue) < ele_len)
        break;
      out_len = queue_out_byte (queue, to + total_len, ele_len);
      total_len += out_len;
    }
  return total_len;
}

static inline uint32_t
queue_out_byte (void *queue, void *to, uint32_t len)
{
  len = min (queue_len (queue), len);
  __queue_out_data (queue, to, len);
  __queue_add_out (queue, len);
  return len;
}

#endif /* __INCLUDED_LIST_H__ */