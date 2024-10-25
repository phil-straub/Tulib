#ifndef TULIB_H
#define TULIB_H

#include <stddef.h>
#include <inttypes.h>
#include <stdint.h>
#include <uchar.h>
#include <stdio.h>

/*
 * Basic Unsigned Integer Types
 */

typedef size_t tulib_size;
typedef unsigned int tulib_width;

/*
 * Character Types
 */

/* Unicode character */
typedef uint32_t tulib_char;

constexpr tulib_char tulib_char_max = 5000; // FIXME

/* UTF-8 character (encoded Unicode character) */
constexpr tulib_size tulib_max_enc_size = 4;

typedef char8_t tulib_enc[tulib_max_enc_size];

/*
 * Database Entry Type
 */

typedef struct TulibCharData {
    int dummy; // FIXME just a dummy entry for now
} TulibCharData;

/* unicode character database */
extern const TulibCharData tulib_ucd[tulib_char_max];

/*
 * Basic Encoding and Decoding Functions
 */

/* byte width of a character / of an encoded character (0 for invalid character) */
static inline tulib_width tulib_char_width(tulib_char ch);
static inline tulib_width tulib_enc_width(const char8_t * enc);

/* similar, but performs additional checks to make sure that the character is fully valid */
static inline tulib_width tulib_char_is_valid(tulib_char ch);
static inline tulib_width tulib_enc_is_valid(const char8_t * enc);

/* similar, but actually encodes/decodes */
static inline tulib_width tulib_encode(tulib_char ch, char8_t * enc);
static inline tulib_width tulib_decode(const char8_t * enc, tulib_char * ch);

/*
 * Display Functions
 */

static inline void tulib_display_char(FILE * stream, tulib_char ch);
static inline void tulib_display_enc(FILE * stream, const char8_t * enc);

/*
 * Auxiliary Functions
 */

static inline int tulib_char_is_invalid(tulib_char ch) {return !tulib_char_is_valid(ch);}
static inline int tulib_enc_is_invalid(const char8_t * enc) {return !tulib_enc_is_valid(enc);}

static inline int tulib_char_is_null(tulib_char ch) {return (ch == 0);}
static inline int tulib_enc_is_null(const char8_t * enc) {return (enc[0] == 0);}

static inline int tulib_char_is_ascii(tulib_char ch) {return (tulib_char_is_valid(ch) == 1);}
static inline int tulib_enc_is_ascii(const char8_t * enc) {return (tulib_enc_is_valid(enc) == 1);}

static inline int tulib_char_is_multibyte(tulib_char ch) {return (tulib_char_is_valid(ch) > 1);}
static inline int tulib_enc_is_multibyte(const char8_t * enc) {return (tulib_enc_is_valid(enc) > 1);}

/****************************************************************************************************
 *
 * Implementation of Some Longer Functions
 *
 ***************************************************************************************************/

// TODO

static inline tulib_width tulib_char_width(tulib_char ch)
{
    return 0;
}

static inline tulib_width tulib_enc_width(const char8_t * enc)
{
    return 0;
}

/* similar, but performs additional checks to make sure that the character is fully valid */
static inline tulib_width tulib_char_is_valid(tulib_char ch)
{
    return tulib_char_width(ch);
}

static inline tulib_width tulib_enc_is_valid(const char8_t * enc)
{
    const tulib_width width = tulib_enc_width(enc);
    // TODO verify tail bytes

    return width;
}

/* similar, but actually encodes/decodes */
static inline tulib_width tulib_encode(tulib_char ch, char8_t * enc)
{
    const tulib_width width = tulib_char_width(ch);
    // TODO compute enc[0], ..., enc[width-1]
    
    return width;
}

static inline tulib_width tulib_decode(const char8_t * enc, tulib_char * ch)
{
    const tulib_width width = tulib_enc_width(enc);
    // TODO computer *ch

    return width;
}

/*
 * Display Functions
 */

static inline void tulib_display_char(FILE * stream, tulib_char ch)
{
    tulib_enc enc;
    tulib_encode(ch, enc);
    tulib_display_enc(stream, enc);
}

static inline void tulib_display_enc(FILE * stream, const char8_t * enc)
{
    const tulib_width width = tulib_enc_width(enc);
    for (tulib_width i=0; i<width; ++i) {
        fputc(enc[i], stream);
    }
}

#endif
