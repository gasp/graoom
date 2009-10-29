/*
** sha1.c for sha1 in /home/rannou_s/work/sha1
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Mon Aug 10 12:59:34 2009 sebastien rannou
** Last update Thu Oct  1 12:49:14 2009 sebastien rannou
*/

#ifndef _BSD_SOURCE
#define _BSD_SOURCE
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**!
 * @author	rannou_s
 * This implementation of SHA1 uses the first method defined in the RFC3174
 * http://www.faqs.org/rfcs/rfc3174.html
 * each variables defined here follows the convention used in the
 * document of reference, so let's have a look at it, it's well explained.
 */

typedef unsigned long	ulong;
typedef unsigned int	uint;
typedef unsigned char	uchar;

typedef struct		sha1_s		/* sha1 structure */
{
  uint			w[80];		/* 16 + 64, used to compute */
  uint			h[5];		/* contains H0 H1 H2 H3 H4 H5*/
  uint			a[5];		/* contains A B C D E */
}			sha1_t;

#define	W(x)		sha1->w[x]
#define	H(x)		sha1->h[x]

#define	A		sha1->a[0]
#define	B		sha1->a[1]
#define	C		sha1->a[2]
#define	D		sha1->a[3]
#define	E		sha1->a[4]

/**!
 * @author	rannou_s
 * Performs a circular left shift
 * S^n(X)  =  (X << n) OR (X >> 32-n)
 */

static  uint
sha1_op_left_shift(uint n, uint x)
{
  return (x << n) | (x >> (32 - n));
}

/**!
 * @author	rannou_s
 * Performs the F function (returns a different bitwise according to t)
 */

static  uint
sha1_f(int t, sha1_t *sha1)
{
  if (t < 20)
    return (B & C) | ((~B) & D);
  if (t < 40)
    return B ^ C ^ D;
  if (t < 60)
    return (B & C) | (B & D) | (C & D);
  return B ^ C ^ D;
}

/**!
 * @author	rannou_s
 * Performs the K function (returns a different constant according to t)
 */

static  uint
sha1_k(int t)
{
  if (t < 20)
    return 0x5A827999;
  if (t < 40)
    return 0x6ED9EBA1;
  if (t < 60)
    return 0x8F1BBCDC;
  return 0xCA62C1D6;
}

/**!
 * @author	rannou_s
 * Computes one `n block` of 16 words
 * assuming strlen(input) is equal to 64 and padded
 */

static  void
sha1_compute_block(uchar *input, sha1_t *sha1)
{
  int			i, t;
  uint			tmp;

  for (t = 0; t < 16; t++)
    {
      W(t) = input[t * 4] << 24;
      W(t) |= input[t * 4 + 1] << 16;
      W(t) |= input[t * 4 + 2] << 8;
      W(t) |= input[t * 4 + 3];
    }
  for (t = 16; t < 80; t++)
    {
      W(t) = sha1_op_left_shift(1, W(t - 3) ^ W(t - 8) ^ W(t - 14) ^ W(t - 16));
    }
  for (i = 0; i < 5; i++)
    {
      sha1->a[i] = sha1->h[i];
    }
  for (t = 0; t < 80; t++)
    {
      tmp = sha1_op_left_shift(5, A) + sha1_f(t, sha1) + E + W(t) + sha1_k(t);
      E = D;
      D = C;
      C = sha1_op_left_shift(30, B);
      B = A;
      A = tmp;
    }
  for (i = 0; i < 5; i ++)
    {
      sha1->h[i] += sha1->a[i];
    }
}

/**!
 * @author	rannou_s
 * Let's initialize sha1 structure with some constants
 */

static  void
sha1_initialize(sha1_t *sha1)
{
  sha1->h[0] = 0x67452301;
  sha1->h[1] = 0xEFCDAB89;
  sha1->h[2] = 0x98BADCFE;
  sha1->h[3] = 0x10325476;
  sha1->h[4] = 0xC3D2E1F0;
}

/**!
 * @author	rannou_s
 * Let's copy the small-len at the end of the word
 */

static  void
sha1_set_len(char *word, int len)
{
  uint			ulen = len & 0xFFFFFFFF;

  word[60] = ulen >> 24;
  word[61] = ulen >> 16;
  word[62] = ulen >> 8;
  word[63] = ulen;
}

/**!
 * @author	rannou_s
 * Let's return the hash according to the sha1 structure
 */

static  char *
sha1_get_hash(sha1_t *sha1)
{
  char			result[140 + 1];

  snprintf(result, 140, "%8x%8x%8x%8x%8x", H(0), H(1), H(2), H(3), H(4));
  return (strdup(result));
}

/**!
 * @author	rannou_s
 * Returns an allocated string representing the hash of the string
 * It assumes that the len of the string is less than 2^32 bytes
 * If it's not the case, the way we store the len in the last block is incorrect
 */

char *
sha1_string(char *input)
{
  sha1_t		sha1;
  char			word[64];
  int			i, len, computed, flag;

  if (input == NULL)
    return (NULL);
  sha1_initialize(&sha1);
  len = strlen(input);
  flag = 0;
  for (i = 0; i <= len; i += 64)
    {
      computed = i + 64 > len ? len % 64 : 64;
      strncpy(word, &input[i], computed);
      if (computed != 64)
	{
	  memset(&word[computed], 0, 64 - computed);
	  word[computed] = (char) 0x80;
	  if (computed < 56)
	    sha1_set_len(word, len * 8);
	  else	    
	    ++flag;
	}
      sha1_compute_block((uchar *) word, &sha1);
    }
  if (flag > 0)
    {
      memset(word, 0, 64);
      sha1_set_len(word, len * 8);
      sha1_compute_block((uchar *) word, &sha1);
    }
  return (sha1_get_hash(&sha1));
}



/**!
 * @author	rannou_s
 * Quite the same function as sha1_string with the difference that it 
 * computes the hash on a file, that may length 2^32 bytes, RFC defines more
 * but it's not yet handled
 */

#define	READ_FILE_BUF	1024	/* Must be a multiple of 2 
				   undefined behavior if not the case */

char *
sha1_file(char *path)
{
  FILE			*handle;
  sha1_t		sha1;
  char			buffer[READ_FILE_BUF];
  char			word[64];
  int			nb_read, i, computed, len = 0, flag = 0;

  if (path == NULL || (handle = fopen(path, "r")) == NULL)
    {
      return (NULL);
    }
  sha1_initialize(&sha1);
  while ((nb_read = fread(buffer, READ_FILE_BUF, 1, handle)) > 0)
    {
      len += nb_read;
      buffer[nb_read] = '\0';
      for (i = 0; i <= nb_read; i += 64)
	{
	  computed = i + 64 > len ? len % 64 : 64;
	  strncpy(word, &buffer[i], computed);
	  if (computed != 64)	/* next read will return 0 */
	    {
	      memset(&word[computed], 0, 64 - computed);
	      word[computed] = (char) 0x80;
	      if (computed < 56)
		sha1_set_len(word, len * 8);
	      else	    
		++flag;
	    }
	  sha1_compute_block((uchar *) word, &sha1);
	}
    }
  if (flag > 0)
    {
      memset(word, 0, 64);
      sha1_set_len(word, len * 8);
      sha1_compute_block((uchar *) word, &sha1);
    }
  return (sha1_get_hash(&sha1));
}
