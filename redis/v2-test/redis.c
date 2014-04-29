
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

#line 86 "redis.rl"

#line 33 "redis.c"
static const char _redis_actions[] = {
    0, 1, 1, 1, 2, 2, 0, 2
};

static const char _redis_cond_offsets[] = {
    0, 0, 1, 2, 2
};

static const char _redis_cond_lengths[] = {
    0, 1, 1, 0, 0
};

static const short _redis_cond_keys[] = {
    -128, 127, -128, 127, 0
};

static const char _redis_cond_spaces[] = {
    0, 0, 0
};

static const char _redis_key_offsets[] = {
    0, 0, 2, 5, 6
};

static const short _redis_trans_keys[] = {
    384, 639, 316, 384, 639, 62, 0
};

static const char _redis_single_lengths[] = {
    0, 0, 1, 1, 0
};

static const char _redis_range_lengths[] = {
    0, 1, 1, 0, 0
};

static const char _redis_index_offsets[] = {
    0, 0, 2, 5, 7
};

static const char _redis_trans_targs[] = {
    2, 0, 3, 2, 0, 4, 0, 0,
    0
};

static const char _redis_trans_actions[] = {
    5, 0, 1, 3, 0, 0, 0, 0,
    0
};

static const int redis_start = 1;
static const int redis_first_final = 4;
static const int redis_error = 0;

static const int redis_en_main = 1;

#line 89 "redis.rl"

Msg            *
msg_parse(uint8_t * buf, uint32_t len)
{
    int             cs;         //used by ragel
    uint8_t        *p, *pe, *eof;   //used by ragel

    uint8_t        *last;       //last pos
    uint32_t        argc;
    uint32_t        arglen = 7;

    p = buf;
    eof = pe = buf + len;

#line 107 "redis.c"
    {
        cs = redis_start;
    }

#line 112 "redis.c"
    {
        int             _klen;
        unsigned int    _trans;
        short           _widec;
        const char     *_acts;
        unsigned int    _nacts;
        const short    *_keys;

        if (p == pe)
            goto _test_eof;
        if (cs == 0)
            goto _out;
      _resume:
        _widec = (*p);
        _klen = _redis_cond_lengths[cs];
        _keys = _redis_cond_keys + (_redis_cond_offsets[cs] * 2);
        if (_klen > 0) {
            const short    *_lower = _keys;
            const short    *_mid;
            const short    *_upper = _keys + (_klen << 1) - 2;
            while (1) {
                if (_upper < _lower)
                    break;

                _mid = _lower + (((_upper - _lower) >> 1) & ~1);
                if (_widec < _mid[0])
                    _upper = _mid - 2;
                else if (_widec > _mid[1])
                    _lower = _mid + 2;
                else {
                    switch (_redis_cond_spaces[_redis_cond_offsets[cs] + ((_mid - _keys) >> 1)]) {
                    case 0:{
                            _widec = (short)(128 + ((*p) - -128));
                            if (
#line 70 "redis.rl"
                                   (printf("test_arglen %c %d  arglen>0:%d\n", *p, arglen, arglen > 0)
                                    && (arglen-- > 0)))
                                _widec += 256;
                            break;
                        }
                    }
                    break;
                }
            }
        }

        _keys = _redis_trans_keys + _redis_key_offsets[cs];
        _trans = _redis_index_offsets[cs];

        _klen = _redis_single_lengths[cs];
        if (_klen > 0) {
            const short    *_lower = _keys;
            const short    *_mid;
            const short    *_upper = _keys + _klen - 1;
            while (1) {
                if (_upper < _lower)
                    break;

                _mid = _lower + ((_upper - _lower) >> 1);
                if (_widec < *_mid)
                    _upper = _mid - 1;
                else if (_widec > *_mid)
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
            const short    *_lower = _keys;
            const short    *_mid;
            const short    *_upper = _keys + (_klen << 1) - 2;
            while (1) {
                if (_upper < _lower)
                    break;

                _mid = _lower + (((_upper - _lower) >> 1) & ~1);
                if (_widec < _mid[0])
                    _upper = _mid - 2;
                else if (_widec > _mid[1])
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
            case 0:
#line 56 "redis.rl"
                {
                    printf("%20s state: %2d ### at %.*s \n", "start_arg", cs, (int)(p - buf), buf);
                }
                break;
            case 1:
#line 59 "redis.rl"
                {
                    printf("%20s state: %2d ### at %.*s \n", "end_arg", cs, (int)(p - buf), buf);
                }
                break;
            case 2:
#line 62 "redis.rl"
                {
                    printf("%20s state: %2d ### at %.*s \n", "-----all", cs, (int)(p - buf), buf);
                }
                break;
#line 235 "redis.c"
            }
        }

      _again:
        if (cs == 0)
            goto _out;
        if (++p != pe)
            goto _resume;
      _test_eof:{
        }
      _out:{
        }
    }

#line 105 "redis.rl"

}

int
main()
{
    /*uint8_t buf[] = "*3<>$3<>SET<>$5<>mykey<>$7<>myva<>e<>"; */
    uint8_t         buf[] = "myva<>e<>";
    uint32_t        buflen = strlen(buf);
    msg_parse(buf, buflen);
}
