
#line 1 "redis.rl"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

typedef struct Msg {
    int             argc;       // if argc < 0, means this msg is not used
    char          **argv;
} Msg;

Msg            *
msg_new(int argc)
{
    Msg            *msg;
    msg = malloc(sizeof(Msg));
    msg->argc = argc;
    msg->argv = malloc(sizeof(char *) * msg->argc);
    return msg;
}

void
dump(uint8_t * buf, uint32_t len)
{

}

#line 71 "redis.rl"

#line 33 "redis.c"
static const char _redis_actions[] = {
    0, 1, 0, 1, 1, 1, 2, 1,
    3, 1, 4, 1, 5, 1, 6, 1,
    7, 2, 2, 1, 2, 5, 1
};

static const char _redis_key_offsets[] = {
    0, 0, 1, 3, 6, 7, 8, 10,
    13, 14, 14, 15, 17, 20, 23, 25,
    27
};

static const char _redis_trans_keys[] = {
    42, 48, 57, 60, 48, 57, 62, 36,
    48, 57, 60, 48, 57, 62, 60, 60,
    62, 60, 48, 57, 60, 48, 57, 60,
    62, 36, 60, 36, 60, 0
};

static const char _redis_single_lengths[] = {
    0, 1, 0, 1, 1, 1, 0, 1,
    1, 0, 1, 2, 1, 1, 2, 2,
    2
};

static const char _redis_range_lengths[] = {
    0, 0, 1, 1, 0, 0, 1, 1,
    0, 0, 0, 0, 1, 1, 0, 0,
    0
};

static const char _redis_index_offsets[] = {
    0, 0, 2, 4, 7, 9, 11, 13,
    16, 18, 19, 21, 24, 27, 30, 33,
    36
};

static const char _redis_trans_targs[] = {
    2, 0, 3, 0, 4, 3, 0, 5,
    0, 6, 0, 7, 0, 8, 7, 0,
    9, 0, 10, 11, 10, 11, 15, 10,
    11, 13, 10, 14, 13, 10, 11, 16,
    10, 12, 11, 10, 12, 11, 10, 0
};

static const char _redis_trans_actions[] = {
    9, 0, 15, 0, 7, 0, 0, 0,
    0, 0, 0, 13, 0, 5, 0, 0,
    0, 0, 11, 3, 0, 3, 0, 0,
    3, 13, 0, 17, 0, 0, 3, 0,
    0, 0, 3, 0, 11, 20, 11, 0
};

static const char _redis_eof_actions[] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 1,
    1
};

static const int redis_start = 1;
static const int redis_first_final = 15;
static const int redis_error = 0;

static const int redis_en_main = 1;

#line 74 "redis.rl"

Msg            *
msg_parse(uint8_t * buf, uint32_t len)
{
    int             cs;         //used by ragel
    uint8_t        *p, *pe, *eof;   //used by ragel

    char           *c;

    p = buf;
    eof = pe = buf + len;

#line 112 "redis.c"
    {
        cs = redis_start;
    }

#line 117 "redis.c"
    {
        int             _klen;
        unsigned int    _trans;
        const char     *_acts;
        unsigned int    _nacts;
        const char     *_keys;

        if (p == pe)
            goto _test_eof;
        if (cs == 0)
            goto _out;
      _resume:
        _keys = _redis_trans_keys + _redis_key_offsets[cs];
        _trans = _redis_index_offsets[cs];

        _klen = _redis_single_lengths[cs];
        if (_klen > 0) {
            const char     *_lower = _keys;
            const char     *_mid;
            const char     *_upper = _keys + _klen - 1;
            while (1) {
                if (_upper < _lower)
                    break;

                _mid = _lower + ((_upper - _lower) >> 1);
                if ((*p) < *_mid)
                    _upper = _mid - 1;
                else if ((*p) > *_mid)
                    _lower = _mid + 1;
                else {
                    _trans += (unsigned int)(_mid - _keys);
                    goto _match;
                }
            }
            _keys += _klen;
            _trans += _klen;
        }

        _klen = _redis_range_lengths[cs];
        if (_klen > 0) {
            const char     *_lower = _keys;
            const char     *_mid;
            const char     *_upper = _keys + (_klen << 1) - 2;
            while (1) {
                if (_upper < _lower)
                    break;

                _mid = _lower + (((_upper - _lower) >> 1) & ~1);
                if ((*p) < _mid[0])
                    _upper = _mid - 2;
                else if ((*p) > _mid[1])
                    _lower = _mid + 2;
                else {
                    _trans += (unsigned int)((_mid - _keys) >> 1);
                    goto _match;
                }
            }
            _trans += _klen;
        }

      _match:
        cs = _redis_trans_targs[_trans];

        if (_redis_trans_actions[_trans] == 0)
            goto _again;

        _acts = _redis_actions + _redis_trans_actions[_trans];
        _nacts = (unsigned int)*_acts++;
        while (_nacts-- > 0) {
            switch (*_acts++) {
            case 1:
#line 32 "redis.rl"
                {
                    printf("%20s state: %2d ### at %.*s \n", "end_arg", cs, (int)(p - buf), buf);
                }
                break;
            case 2:
#line 36 "redis.rl"
                {
                    printf("%20s state: %2d ### at %.*s \n", "end_arglen", cs, (int)(p - buf), buf);
                }
                break;
            case 3:
#line 39 "redis.rl"
                {
                    printf("%20s state: %2d ### at %.*s \n", "end_argc", cs, (int)(p - buf), buf);
                }
                break;
            case 4:
#line 43 "redis.rl"
                {
                    printf("%20s state: %2d ### at %.*s \n", "start_cmd", cs, (int)(p - buf), buf);
                }
                break;
            case 5:
#line 47 "redis.rl"
                {
                    printf("%20s state: %2d ### at %.*s \n", "start_arg", cs, (int)(p - buf), buf);
                }
                break;
            case 6:
#line 51 "redis.rl"
                {
                    printf("%20s state: %2d ### at %.*s \n", "start_arglen", cs, (int)(p - buf), buf);
                }
                break;
            case 7:
#line 54 "redis.rl"
                {
                    printf("%20s state: %2d ### at %.*s \n", "start_argc", cs, (int)(p - buf), buf);
                }
                break;
#line 232 "redis.c"
            }
        }

      _again:
        if (cs == 0)
            goto _out;
        if (++p != pe)
            goto _resume;
      _test_eof:{
        }
        if (p == eof) {
            const char     *__acts = _redis_actions + _redis_eof_actions[cs];
            unsigned int    __nacts = (unsigned int)*__acts++;
            while (__nacts-- > 0) {
                switch (*__acts++) {
                case 0:
#line 28 "redis.rl"
                    {
                        printf("%20s state: %2d ### at %.*s \n", "end_cmd", cs, (int)(p - buf), buf);
                    }
                    break;
#line 254 "redis.c"
                }
            }
        }

      _out:{
        }
    }

#line 87 "redis.rl"

}

int
main()
{
    uint8_t         buf[] = "*3<>$3<>SET<>$5<>mykey<>$7<>myvalue<>";
    uint32_t        buflen = strlen(buf);
    msg_parse(buf, buflen);
}
